#ifndef TWEET_H
#define TWEET_H

#include "DSString.h"

class Tweet {
private:
    DSString tweetID;
    DSString text;

public:
    // Constructors
    Tweet();
    Tweet(const DSString& tweetID, const DSString& text);

    // Getters
    DSString getTweetID() const;
    DSString getText() const;
};

#endif // TWEET_H
