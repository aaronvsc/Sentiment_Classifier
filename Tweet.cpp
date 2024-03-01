#include "Tweet.h"

Tweet::Tweet() {}

Tweet::Tweet(const DSString& tweetID, DSString& text, int sentiment) {
    this->tweetID = tweetID;
    this->text = text;
    this->sentiment = sentiment;
}

DSString Tweet::getTweetID() const {
    return tweetID;
}

DSString Tweet::getText() const {
    return text;
}

int Tweet::getSentiment() const {
    return sentiment;
}

void Tweet::setSentiment(int sentiment) {
    this->sentiment = sentiment;
}

std::vector<DSString> Tweet::tokenizeTweet() {
    return text.tokenize();
}
