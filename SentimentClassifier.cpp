#include "SentimentClassifier.h"

SentimentClassifier::SentimentClassifier() {
}

void SentimentClassifier::train(const char* train_dataset_20k) {
    std::ifstream file(train_dataset_20k);

    //check open file
    if (!file.is_open()) {
        std::cerr << "Error: Cannot open file" << train_dataset_20k << std::endl;
        return;
    }

    std::string line;
    std::getline(file, line);
    // Read the rest of the file
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string token;

        // Read the sentiment
        std::getline(iss, token, ',');
        int sentiment = std::stoi(token);

        // Skip the tweet id, date, query status, and username
        for (int i = 0; i < 4; ++i) {
            std::getline(iss, token, ',');
        }

        // Read the tweet text (everything after the fourth comma)
        std::getline(iss, token);

        // Tokenize the tweet
        DSString tweet(token.c_str());
        std::vector<DSString> tokens = tweet.tokenize();

        //add word to map annd +/- to word based on sentiment
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
