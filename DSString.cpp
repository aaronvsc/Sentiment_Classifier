#include "DSString.h"

#include <iostream>
#include <vector>

// Constructor: initialize locals w/ values
DSString::DSString() {
    data = nullptr;
    len = 0;
}

// Constructor: initialize data character array with a string
DSString::DSString(const char *str) {
    len = 0;
    // 1. dynamically allocate memory
    while (str[len] != '\0') {
        len++;
    }
    data = new char[len + 1];

    // 2. copy string into memory
    for (size_t i = 0; i < len; i++) {
        data[i] = str[i];
    }
    data[len] = '\0';
}

// copy constructor, copies from rhs to data
DSString::DSString(const DSString &rhs) {
    len = rhs.len;
    data = new char[len + 1];
    for (size_t i = 0; i < len; i++) {
        data[i] = rhs.data[i];
    }
    data[len] = '\0';
}

// destructor
DSString::~DSString() {
    delete[] data;
}

// assignment operator
DSString &DSString::operator=(const DSString &rhs) {
    // 1. check if lhs = rhs
    if (this != &rhs) {
        delete[] data;  // delete lhs old data
        len = rhs.len;
        data = new char[len + 1];  // 3. allocate new memory
        for (size_t i = 0; i < len; i++) {
            data[i] = rhs.data[i];  // 4. copy
        }
        data[len] = '\0';
    }
    return *this;  // return reference to current object
}

// returns the length of the string
size_t DSString::length() const {
    return len;
}

// returns a reference to the character at the given index
char &DSString::operator[](size_t a) {
    return data[a];
}

// Overloaded operator+ which appends the string in the argument to this string
DSString DSString::operator+(const DSString &rhs) const {
    DSString combined;  // DSString to return

    combined.len = len + rhs.len;
    combined.data = new char[combined.len + 1];

    size_t i = 0;
    // copy first string's data to combined DSString
    for (; i < len; i++) {
        combined.data[i] = data[i];
    }
    // copy second string's data to combined DSString
    for (size_t j = 0; j < rhs.len; j++, i++) {
        combined.data[i] = rhs.data[j];
    }

    combined.data[combined.len] = '/0';
    return combined;
}

bool DSString::operator==(const DSString &rhs) const {
    // check lengths
    if (len != rhs.len) {
        return false;
    }
    // check individual indices
    for (size_t i = 0; i < len; i++) {
        if (data[i] != rhs.data[i]) {
            return false;
        }
    }
    return true;
}

bool DSString::operator<(const DSString &rhs) const {
    size_t minLen = std::min(len, rhs.len);  // find max length/index comparable
    for (size_t i = 0; i < minLen; i++) {
        if (data[i] != rhs.data[i]) {
            return data[i] < rhs.data[i];  // returns true by character comparison
        }
    }
    return len < rhs.len;  // returns true if length is less than rhs (prefixes)
}

DSString DSString::substring(size_t start, size_t numChars) const {
    // check start index
    if (start >= len) {
        return DSString();
    }
    numChars = std::min(numChars, len - start);  // checking numChars
    DSString sub;
    sub.len = numChars;
    sub.data = new char[numChars];  // not accounting for null terminator
    // copies from starting index
    for (size_t i = 0; i < numChars; i++) {
        sub.data[i] = data[start + i];
    }

    // sub.data[numChars] = '\0';
    return sub;
}

DSString DSString::toLower() const {
    DSString lower;
    lower.len = len;
    lower.data = new char[len + 1];
    for (size_t i = 0; i < len; i++) {
        // check upercase letter by ASCII range
        if (data[i] >= 'A' && data[i] <= 'Z') {
            lower.data[i] = data[i] + 32;  // convert to lowercase
        } else {
            lower.data[i] = data[i];
        }
    }
    lower.data[len] = '\0';
    return lower;
}

char *DSString::c_str() const {
    return data;
}

// Check if the string is empty
bool DSString::isEmpty() const {
    return len == 0;
}

std::ostream &operator<<(std::ostream &os, const DSString &str) {
    os << str.data;
    return os;
}

// Check if the word is a stopword
bool DSString::isStopword() const {
    // List of stopwords
    const char *stopwords[] = {"i", "me", "my", "myself", "we", "our", "ours", "ourselves", "you", "u", "r", "your", "yours", "yourself", "yourselves",
                               "he", "him", "his", "himself", "she", "her", "hers", "herself", "it", "its", "itself", "they", "them", "their",
                               "theirs", "themselves", "what", "which", "who", "whom", "this", "that", "these", "those", "a", "an", "the", "and",
                               "if", "or", "because", "as", "until", "while", "of", "at", "by", "for", "with", "about", "between",
                               "into", "through", "during", "before", "after", "to", "from", "up", "in", "out", "over", "under", "again", "further", "then", "once",
                               "here", "there", "theres", "when", "where", "why", "how", "all", "any", "both", "each", "more", "most", "other", "some", "such",
                               "only", "own", "same", "so", "do", "am", "has", "was", "is", "than", "too", "very", "can", "will", "just", "should", "now"};

    // Convert the current word to lowercase
    DSString lowercaseWord = this->toLower();

    // Check if the word is in the stopwords list
    for (size_t i = 0; i < sizeof(stopwords) / sizeof(stopwords[0]); ++i) {
        if (lowercaseWord == stopwords[i]) {
            return true;
        }
    }
    return false;
}

std::vector<DSString> DSString::tokenize() {
    std::vector<DSString> tokens;

    // Make the tweet lowercase
    DSString lowercaseTweet = this->toLower();

    // Clean the tweet and tokenize
    DSString word;
    for (size_t i = 0; i < lowercaseTweet.length(); ++i) {
        char c = lowercaseTweet[i];
        // Check if the character is alphanumeric or space
        if ((c >= 'a' && c <= 'z') || c == ' ') {
            // if there is a space and the word isn't empty insert the new word into tokens
            if (c == ' ' && !word.isEmpty()) {
                // Check if the word is not a stopword
                if (!word.isStopword()) {
                    tokens.push_back(word);
                }
                word = "";
                // else add the character to the current word
            } else {
                DSString temp = DSString(&c);
                word = word + temp.substring(0, 1);
            }
        }
    }
    // if there is a word by the end of the tweet then tokenize it
    if (!word.isEmpty() && !word.isStopword()) {
        tokens.push_back(word);
    }

    return tokens;
}

DSString DSString::operator+(const char &rhs) const {
    // Make new length for the char
    size_t newLen = len + 1;

    // Create a new DSString to hold the result
    DSString result;
    result.len = newLen;
    result.data = new char[newLen + 1];

    // Copy data from the left-hand side
    for (size_t i = 0; i < len; ++i) {
        result.data[i] = data[i];
    }

    // Add the character to the end
    result.data[len] = rhs;

    result.data[newLen] = '\0';  // Add null terminator after
    return result;
}

// Read a line from the input stream until a specific char is found
std::istream& DSString::getLine(std::istream &is, char delim) {
    *this = "";  // Clear the existing content of the DSString
    char c;
    while (is.get(c) && c != delim) {
        *this = *this + c;  // + character to the DSString
    }
    return is;  // Return the input stream reference
}

/*
 * Implement the functions defined in DSString.h. You may add more functions as needed
 * for the project.
 *
 * Note that c-strings don's store an explicit length but use `\0` as the terminator symbol
 * but your class should store its length in a member variable.
 * DDO NOT USE C-STRING FUNCTIONS <string.h> or <cstring>.
 */
