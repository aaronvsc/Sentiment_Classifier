#ifndef DSSTRING_H
#define DSSTRING_H

#include <iostream>
#include <vector>

class DSString {
   private:
    char *data;  // Pointer to a character array containing the string with a `\0` terminator
    size_t len;  // Length of the string (without the terminator)
                 // Note: we keep the terminator only so we can return a c-string version in function c_str().

   public:
    DSString();  // Default Constructor

    DSString(const char *);  // Constructor that converts a cstring

    DSString(const DSString &);             // Copy constructor
    ~DSString();                            // Destructor
    DSString &operator=(const DSString &);  // Assignment operator

    size_t length() const;  // Returns the length of the string

    char &operator[](size_t);  // Returns a reference to the character at the given index

    DSString operator+(const DSString &) const;  // Overloaded operator+ which appends the string in the argument to this string

    bool operator==(const DSString &) const;  // Standard relational operators ==
    bool operator<(const DSString &) const;   // Standard relational operators <

    DSString substring(size_t start, size_t numChars) const;  // Returns sequence of characters from this string object

    DSString toLower() const;  // Returns a new string object with all characters in lowercase

    char *c_str() const;  // Returns a pointer a null-terminated c-string

    bool isEmpty() const;  // Checks if DSString is empty

    std::vector<DSString> tokenize();  // Tokenizes DSString

    bool isStopword() const;  // Checks if DSString is a stopword

    DSString operator+(const char &rhs) const;  // Overloaded + operator for adding a char to a DSString

    std::istream &getLine(std::istream &is, char delim);  // Custom getLine function for DSStrings

    std::string toString() const;  // Conversion to std::string

    size_t find(char c, size_t n) const;  // Finds a character of nth occurance and returns the index

    friend std::ostream &operator<<(std::ostream &, const DSString &);  // Overloaded stream insertion operator to print
};

#endif
