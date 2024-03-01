#ifndef SENTIMENTCLASSIFIER_H
#define SENTIMENTCLASSIFIER_H

#include <fstream>
#include <iomanip>
#include <map>

#include "DSString.h"
#include "Tweet.h"

class SentimentClassifier {
   private:
    std::map<DSString, int> sentimentsOfWords;  // Map of sentiments

   public:
    SentimentClassifier();  // Default Constructor

    void train(const char* train_dataset_20k);  // Train the map to hold each word with their sentiment

    int findSentiment(const DSString& word) const;  // Find the sentiment associated with a word

    void predict(char* test_dataset_10k, char* results);  // Predict the sentiment of tweets

    void evaluate(char* test_dataset_sentiment_10k, char* results, char* accuracy);  // Evaluate the predictions
};

#endif