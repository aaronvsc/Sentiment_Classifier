#include "Tweet.h"

// Default constructor
Tweet::Tweet() {}

// Constructor with parameters
Tweet::Tweet(const DSString& tweetID, const DSString& text) {
    this->tweetID = tweetID;
    this->text = text;
}

// Getter for tweet ID
DSString Tweet::getTweetID() const {
    return tweetID;
}

// Getter for tweet text
DSString Tweet::getText() const {
    return text;
}

