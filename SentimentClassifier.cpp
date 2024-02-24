#include "SentimentClassifier.h"

SentimentClassifier::SentimentClassifier() {}

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

        // Skip the tweet id, date, query status, and username
        for (int i = 0; i < 3; ++i) {
            std::getline(iss, token, ',');
        }


        // Read the tweet text (everything after the comma)
        std::getline(iss, token);
        DSString tweetText(token.c_str());

        // Create a Tweet object
        Tweet tweet(DSString(""), tweetText, sentiment);

        // Tokenize the tweet text
        std::vector<DSString> tokens = tweet.tokenizeTweet();

        // Update the sentiment of words in the tweet
        for (const auto& word : tokens) {
            if (tweet.getSentiment() == 4) {
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

void SentimentClassifier::predict(char* test_dataset_10k, char* results) {
    // Open the test dataset file
    std::ifstream testDataFile(test_dataset_10k);
    if (!testDataFile.is_open()) {
        std::cerr << "Error: Cannot open test dataset file " << test_dataset_10k << std::endl;
        return;
    }

    // Open the results file for writing
    std::ofstream resultsFile(results);
    if (!resultsFile.is_open()) {
        std::cerr << "Error: Cannot open results file " << results << std::endl;
        return;
    }

    // Skip the first line of file
    std::string skipLine;
    std::getline(testDataFile, skipLine);

    // Process each tweet in the test dataset
    std::string testLine;
    std::string sentimentLine;
    while (std::getline(testDataFile, testLine)) {
        std::istringstream tweetStream(testLine);

        // Extract tweet ID
        std::string stringID;
        std::getline(tweetStream, stringID, ',');

        // Skip the date, query status, and username
        for (int i = 0; i < 3; ++i) {
            std::getline(tweetStream, skipLine, ',');
        }

        // Extract tweet text
        std::string stringText;
        std::getline(tweetStream, stringText);

        // Convert tweetID and tweetText to DSStrings
        DSString tweetID(stringID.c_str());
        DSString tweetText(stringText.c_str());

        // Create a Tweet object
        Tweet currTweet(tweetID, tweetText);

        // Tokenize the tweet text
        std::vector<DSString> tokens = currTweet.tokenizeTweet();

        // Calculate combined sentiment score of the tweet
        int combinedScore = 0;
        for (const auto& word : tokens) {
            combinedScore += findSentiment(word);
        }

        // Determine sentiment label based on combined score
        int sentimentLabel;
        if (combinedScore >= 0) {
            sentimentLabel = 4;
        } else {
            sentimentLabel = 0;
        }

        // Write the sentiment label and tweet ID to the results file
        resultsFile << sentimentLabel << "," << currTweet.getTweetID() << std::endl;
    }

    // Close the files
    testDataFile.close();
    resultsFile.close();
}