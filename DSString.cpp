#include "DSString.h"

DSString::DSString() {
    data = nullptr;
    len = 0;
}

DSString::DSString(const char *str) {
    len = 0;
    // 1. Dynamically allocate memory
    while (str[len] != '\0') {
        len++;
    }
    data = new char[len + 1];

    // 2. Copy string into memory
    for (size_t i = 0; i < len; i++) {
        data[i] = str[i];
    }
    // 3. Add null terminator to end
    data[len] = '\0';
}

DSString::DSString(const DSString &rhs) {
    len = rhs.len;
    data = new char[len + 1];
    // Copy each char from rhs
    for (size_t i = 0; i < len; i++) {
        data[i] = rhs.data[i];
    }
    data[len] = '\0';
}

DSString::~DSString() {
    delete[] data;
}

DSString &DSString::operator=(const DSString &rhs) {
    // 1. Check if lhs = rhs
    if (this != &rhs) {
        delete[] data;  // 2. Delete lhs old data
        len = rhs.len;
        data = new char[len + 1];  // 3. Allocate new memory
        for (size_t i = 0; i < len; i++) {
            data[i] = rhs.data[i];  // 4. Copy
        }
        data[len] = '\0';
    }
    return *this;  // Return reference to current object
}

size_t DSString::length() const {
    return len;
}

char &DSString::operator[](size_t a) {
    return data[a];
}

DSString DSString::operator+(const DSString &rhs) const {
    DSString combined;

    combined.len = len + rhs.len;
    combined.data = new char[combined.len + 1];

    size_t i = 0;
    // Copy first string's data to combined DSString
    for (; i < len; i++) {
        combined.data[i] = data[i];
    }
    // Copy second string's data to combined DSString
    for (size_t j = 0; j < rhs.len; j++, i++) {
        combined.data[i] = rhs.data[j];
    }

    combined.data[combined.len] = '\0';
    return combined;
}

bool DSString::operator==(const DSString &rhs) const {
    // Check lengths
    if (len != rhs.len) {
        return false;
    }
    // Check individual indices
    for (size_t i = 0; i < len; i++) {
        if (data[i] != rhs.data[i]) {
            return false;
        }
    }
    return true;
}

bool DSString::operator<(const DSString &rhs) const {
    size_t minLen = std::min(len, rhs.len);  // Find max length/index that is comparable
    for (size_t i = 0; i < minLen; i++) {
        if (data[i] != rhs.data[i]) {
            return data[i] < rhs.data[i];  // Returns true by character comparison
        }
    }
    return len < rhs.len;  // Returns true if length is less than rhs (prefixes)
}

DSString DSString::substring(size_t start, size_t numChars) const {
    // Check start index
    if (start >= len) {
        return DSString();
    }
    numChars = std::min(numChars, len - start);  // Ensure range
    DSString sub;
    sub.len = numChars;
    sub.data = new char[numChars+1];  // Accounting for null terminator
    // Copies from starting index
    for (size_t i = 0; i < numChars; i++) {
        sub.data[i] = data[start + i];
    }
    sub.data[numChars] = '\0'; // Add null terminator
    return sub;
}

DSString DSString::toLower() const {
    DSString lower;
    lower.len = len;
    lower.data = new char[len + 1];
    for (size_t i = 0; i < len; i++) {
        // Check upercase letter by ASCII range
        if (data[i] >= 'A' && data[i] <= 'Z') {
            lower.data[i] = data[i] + 32;  // Convert to lowercase
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

bool DSString::isEmpty() const {
    return len == 0;
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
            // If there is a space and the word isn't empty insert the new word into tokens
            if (c == ' ' && !word.isEmpty()) {
                // Check if the word is not a stopword
                if (!word.isStopword()) {
                    tokens.push_back(word);
                }
                word = "";
                // Else add the character to the current word
            } else {
                word = word + c;
            }
        }
    }
    // If there is a word by the end of the tweet then tokenize it
    if (!word.isEmpty() && !word.isStopword()) {
        tokens.push_back(word);
    }

    return tokens;
}

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
    for (const auto &stopword : stopwords) {
        if (lowercaseWord == stopword) {
            return true;
        }
    }
    return false;
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

std::istream &DSString::getLine(std::istream &is, char delim) {
    *this = "";  // Clear the existing content of the DSString
    char c;
    while (is.get(c) && c != delim) {
        *this = *this + c;  // Add character to the DSString
    }
    return is;  // Return the input stream reference
}

std::string DSString::toString() const {
    // Create a std::string object and copy the characters from DSString
    std::string result;
    for (size_t i = 0; i < length(); ++i) {
        result += data[i];
    }
    return result;
}

size_t DSString::find(char c, size_t n) const {
    size_t count = 0;
    // Checks all chars and increments count when matching char
    for (size_t i = 0; i < len; ++i) {
        if (data[i] == c) {
            count++;
            // Returns index of nth matching char
            if (count == n) {
                return i;
            }
        }
    }
    return 0;  // Not found
}

std::ostream &operator<<(std::ostream &os, const DSString &str) {
    os << str.data;
    return os;
}