#include "SentimentClassifier.h"

SentimentClassifier::SentimentClassifier() {}

void SentimentClassifier::train(const char* train_dataset_20k) {
    std::ifstream train(train_dataset_20k);

    if (!train.is_open()) {
        std::cerr << "Error: Cannot open file " << train_dataset_20k << std::endl;
        return;
    }

    DSString line;
    line.getLine(train, '\n');  // Skip the header line

    // Read the rest of the file
    while (line.getLine(train, '\n')) {
        std::istringstream trainStream(line.c_str());
        DSString element;

        // Read the sentiment
        element.getLine(trainStream, ',');
        auto str = element.toString();
        int sentiment = std::stoi(str);

        // Skip the tweet id, date, query status, and username
        for (int i = 0; i < 3; ++i) {
            element.getLine(trainStream, ',');
        }

        // Read the tweet text (everything after the comma)
        element.getLine(trainStream, '\n');

        // Create a Tweet object
        Tweet tweet("", element);
        tweet.setSentiment(sentiment);

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

    train.close();
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
        if (combinedScore >= 0) {
            currTweet.setSentiment(4);
        } else {
            currTweet.setSentiment(0);
        }

        // Write the sentiment label and tweet ID to the results file
        resultsFile << currTweet.getSentiment() << "," << currTweet.getTweetID() << std::endl;
    }

    // Close the files
    testDataFile.close();
    resultsFile.close();
}

void SentimentClassifier::evaluate(char* test_dataset_sentiment_10k, char* results, char* accuracy) {
    std::ifstream truthFile(test_dataset_sentiment_10k);
    std::ifstream resultFile(results);
    std::ofstream accuracyFile(accuracy);

    if (!truthFile.is_open() || !resultFile.is_open() || !accuracyFile.is_open()) {
        std::cerr << "Error: Cannot open files" << std::endl;
        return;
    }

    // Skip the first line of each file
    std::string truthLine, resultsLine;
    std::getline(truthFile, truthLine);

    int totalTweets = 0;
    int correctPredictions = 0;

    // Process the rest of the files
    while (std::getline(truthFile, truthLine) && std::getline(resultFile, resultsLine)) {
        // Extract predicted sentiment from results file
        int predictedSentiment;
        std::istringstream resultStream(resultsLine);
        std::string token;
        std::getline(resultStream, token, ',');
        predictedSentiment = std::stoi(token);

        // Extract ground truth sentiment from ground truth file
        int groundTruthSentiment;
        std::istringstream truthStream(truthLine);
        std::getline(truthStream, token, ',');
        groundTruthSentiment = std::stoi(token);

        DSString tweetID;
        std::string tweetIDString;
        std::getline(resultStream, tweetIDString, ',');
        tweetID = DSString(tweetIDString.c_str());

        // Check if prediction matches ground truth
        if (predictedSentiment == groundTruthSentiment) {
            correctPredictions++;
        } else {
            // Write incorrectly classified tweet to accuracy file
            accuracyFile << predictedSentiment << ", " << groundTruthSentiment << ", " << tweetID << std::endl;
        }

        totalTweets++;
    }

    // Calculate accuracy
    double accuracyDecimal = (static_cast<double>(correctPredictions) / totalTweets);

    // Write accuracy to accuracy file
    accuracyFile << std::fixed << std::setprecision(2) << accuracyDecimal << std::endl;

    // Close the files
    truthFile.close();
    resultFile.close();
    accuracyFile.close();
}