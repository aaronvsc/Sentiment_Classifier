#ifndef TWEET_H
#define TWEET_H

#include "DSString.h"

class Tweet {
   private:
    DSString tweetID;
    DSString text;
    int sentiment;

   public:
    Tweet();                                                            // Default constructor
    Tweet(const DSString& tweetID, DSString& text, int sentiment = 0);  // Constructor with parameters

    DSString getTweetID() const;  // Getter for tweet ID
    DSString getText() const;     // Getter for tweet text
    int getSentiment() const;     // Getter for sentiment

    void setSentiment(int sentiment);  // Setter for sentiment

    std::vector<DSString> tokenizeTweet();  // Tokenize for tweets
};

#endif  // TWEET_H
