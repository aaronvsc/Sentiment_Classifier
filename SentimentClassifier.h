#ifndef SENTIMENTCLASSIFIER_H
#define SENTIMENTCLASSIFIER_H

#include "DSString.h"
#include "Tweet.h"
#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <filesystem>


class SentimentClassifier{

private:

std::map<DSString, int> sentimentsOfWords;


public:

SentimentClassifier();

void train(const char* train_dataset_20k);

int findSentiment(const DSString& word) const;

void predict(char* test_dataset_10k, char* results);

void evaluate(char* test_dataset_sentiment_10k, char* results, char* accuracy);

};



#endif