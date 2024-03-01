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
    std::ifstream test(test_dataset_10k);
    if (!test.is_open()) {
        std::cerr << "Error: Cannot open test dataset file " << test_dataset_10k << std::endl;
        return;
    }

    // Open the results file for writing
    std::ofstream result(results);
    if (!result.is_open()) {
        std::cerr << "Error: Cannot open results file " << results << std::endl;
        return;
    }

    // Skip the first line of file
    DSString line;
    line.getLine(test, '\n');

    // Process each tweet in the test dataset
    while (line.getLine(test, '\n')) {
        std::istringstream tweetStream(line.c_str());

        // Extract tweet ID
        DSString tweetID;
        tweetID.getLine(tweetStream, ',');

        // Skip the date, query status, and username
        for (int i = 0; i < 3; ++i) {
            line.getLine(tweetStream, ',');
        }

        // Extract tweet text
        DSString tweetText;
        tweetText.getLine(tweetStream, '\n');

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
        result << currTweet.getSentiment() << "," << currTweet.getTweetID() << std::endl;
    }

    // Close the files
    test.close();
    result.close();
}

void SentimentClassifier::evaluate(char* test_dataset_sentiment_10k, char* results, char* accuracy) {
    std::ifstream truth(test_dataset_sentiment_10k);
    std::ifstream result(results);
    std::ofstream accuracyof(accuracy);

    if (!truth.is_open() || !result.is_open() || !accuracyof.is_open()) {
        std::cerr << "Error: Cannot open files" << std::endl;
        return;
    }

    DSString truthLine;
    DSString resultLine;
    // Skip the first line of truth file
    truthLine.getLine(truth, '\n');

    int totalTweets = 0;
    int correctPredictions = 0;

    // Process the rest of the files
    while (truthLine.getLine(truth, '\n') && resultLine.getLine(result, '\n')) {
        DSString element;
        // Extract predicted sentiment from results file
        int predictedSentiment;
        std::istringstream resultStream(resultLine.c_str());
        element.getLine(resultStream, ',');
        auto str = element.toString();
        predictedSentiment = std::stoi(str);

        // Extract ground truth sentiment from ground truth file
        int groundTruthSentiment;
        std::istringstream truthStream(truthLine.c_str());
        element.getLine(truthStream,',');
        str = element.toString();
        groundTruthSentiment = std::stoi(str);

        DSString tweetID;
        tweetID.getLine(resultStream, ',');

        // Check if prediction matches ground truth
        if (predictedSentiment == groundTruthSentiment) {
            correctPredictions++;
        } else {
            // Write incorrectly classified tweet to accuracy file
            accuracyof << predictedSentiment << ", " << groundTruthSentiment << ", " << tweetID << std::endl;
        }

        totalTweets++;
    }

    // Calculate accuracy
    double accuracyDecimal = (static_cast<double>(correctPredictions) / totalTweets);

    // Write accuracy to accuracy file
    accuracyof << std::fixed << std::setprecision(3) << accuracyDecimal << std::endl;

    // Close the files
    truth.close();
    result.close();
    accuracyof.close();
}