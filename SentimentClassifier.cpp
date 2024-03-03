#include "SentimentClassifier.h"

SentimentClassifier::SentimentClassifier() {}

void SentimentClassifier::train(const char* train_dataset_20k) {
    std::ifstream train(train_dataset_20k);

    if (!train.is_open()) {
        std::cerr << "Error: Cannot open file " << train_dataset_20k << std::endl;
        return;
    }

    DSString line;
    // Skip the header line
    line.getLine(train, '\n');

    // Read the rest of the file
    while (line.getLine(train, '\n')) {
        DSString element;

        // Read the sentiment
        size_t pos = line.find(',', 1);
        element = line.substring(0, pos);
        int sentiment = std::stoi(element.toString());

        // Skip the ID, date, query status, and username
        pos = line.find(',', 5);

        // Read the tweet text (everything after the comma)
        element = line.substring(pos + 1, line.length() - pos - 1);

        // Create a Tweet object
        Tweet tweet("", element, sentiment);

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

int SentimentClassifier::findSentiment(const DSString& word) const {
    auto a = sentimentsOfWords.find(word);
    if (a != sentimentsOfWords.end()) {
        return a->second;  // Returns element at key
    } else {
        return 0;  // Assuming sentiment of 0 for words not found
    }
}

void SentimentClassifier::predict(char* test_dataset_10k, char* results) {
    std::ifstream test(test_dataset_10k);
    std::ofstream result(results);

    // Check if files are open
    if (!result.is_open() || !test.is_open()) {
        std::cerr << "Error: Cannot open files" << results << std::endl;
        return;
    }

    // Skip the first line of file
    DSString line;
    line.getLine(test, '\n');

    // Process each tweet in the test dataset
    while (line.getLine(test, '\n')) {
        // Extract tweet ID
        DSString tweetID;
        size_t pos = line.find(',', 1);
        tweetID = line.substring(0, pos);

        // Skip the date, query status, and username
        pos = line.find(',', 4);

        // Extract tweet text
        DSString tweetText = line.substring(pos + 1, line.length() - pos - 1);

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
    std::ofstream newAccuracy("new.txt");
    std::ifstream accuracyif(accuracy);

    // Check if files are open
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
        element = resultLine.substring(0, resultLine.find(',', 1));
        int predictedSentiment = std::stoi(element.toString());

        // Extract ground truth sentiment from ground truth file
        element = truthLine.substring(0, truthLine.find(',', 1));
        int groundTruthSentiment = std::stoi(element.toString());

        // Extract tweetID from results file
        DSString tweetID = resultLine.substring(resultLine.find(',', 1), resultLine.length() - 1);  // Skip the first comma

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

    // Write accuracy to top of new file
    newAccuracy << std::fixed << std::setprecision(3) << accuracyDecimal << std::endl;

    DSString accuracyLine;
    while (accuracyLine.getLine(accuracyif, '\n')) {
        // Write the entire line to the output file
        newAccuracy << accuracyLine << std::endl;
    }

    // Close the files
    truth.close();
    result.close();
    accuracyof.close();
    newAccuracy.close();

    // Rename temporary file to replace the original accuracy file
    std::rename("new.txt", accuracy);
}