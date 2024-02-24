#include "SentimentClassifier.h"

SentimentClassifier::SentimentClassifier() {
}

void SentimentClassifier::train(const char* train_dataset_20k) {
    std::ifstream file(train_dataset_20k);

    if (!file.is_open()) {
        std::cerr << "Error: Cannot open file " << train_dataset_20k << std::endl;
        return;
    }

    std::string line;
    std::getline(file, line);  // Skip the header line

    // Read the rest of the file
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string token;

        // Read the sentiment
        std::getline(iss, token, ',');
        int sentiment = std::stoi(token);

        // Skip the tweet id
        std::getline(iss, token, ',');

        // Read the tweet text (everything after the comma)
        std::getline(iss, token);
        DSString tweetText(token.c_str());

        // Create a Tweet object
        Tweet tweet("", tweetText);
        tweet.setSentiment(sentiment);

        // Tokenize the tweet text
        std::vector<DSString> tokens = tweet.tokenizeTweet();

        // Update the sentiment of words in the tweet
        for (const auto& word : tokens) {
            if (sentiment == 4) {
                sentimentsOfWords[word]++;
            } else {
                sentimentsOfWords[word]--;
            }
        }
    }

    file.close();
}

// finds sentiment of word in map
int SentimentClassifier::findSentiment(const DSString& word) const {
    auto a = sentimentsOfWords.find(word);
    if (a != sentimentsOfWords.end()) {
        return a->second;  // returns element at key
    } else {
        return 0;  // assuming sentiment of 0 for words not found
    }
}


