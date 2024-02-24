#include "Tweet.h"

// Default constructor
Tweet::Tweet() {}

// Constructor with parameters
Tweet::Tweet(const DSString& tweetID, DSString& text, int sentiment) {
    this->tweetID = tweetID;
    this->text = text;
    this->sentiment = sentiment;
}

// Getter for tweet ID
DSString Tweet::getTweetID() const {
    return tweetID;
}

// Getter for tweet text
DSString Tweet::getText() const {
    return text;
}

// Getter for sentiment
int Tweet::getSentiment() const {
    return sentiment;
}

// Setter for sentiment
void Tweet::setSentiment(int sentiment) {
    this->sentiment = sentiment;
}

// Tokenize the tweet text
std::vector<DSString> Tweet::tokenizeTweet() {
    return text.tokenize();
}

