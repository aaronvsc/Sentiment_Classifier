#ifndef TWEET_H
#define TWEET_H

#include "DSString.h"

class Tweet {
private:
    DSString tweetID;
    DSString text;
    int sentiment;

public:
    // Constructors
    Tweet();
    Tweet(const DSString& tweetID, DSString& text);

    // Getters
    DSString getTweetID() const;
    DSString getText() const;
    int getSentiment() const;

    // Setters
    void setSentiment(int sentiment);

    std::vector<DSString> tokenize(Tweet& tweet);
};

#endif // TWEET_H
