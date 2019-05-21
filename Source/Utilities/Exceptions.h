//
// Created by tomtom on 04/05/19.
//

#ifndef PAZAAK_EXCEPTIONS_H
#define PAZAAK_EXCEPTIONS_H

#include <exception>

using namespace std;

/**
 * Directory has not been found or needs special permission to access
 */
class CannotOpenDirectory : public exception {
public:
    const char *what() const noexcept override {
        return "Cannot open a directory.";
    }
};

/**
 * File does not fit the prescribed format
 */
class ParseError : public exception {
    const char *what() const noexcept override { return ("Error reading file"); }
};

/**
 * File has not been found or needs special permission to open
 */
class InvalidFileException : public exception {
    const char *what() const noexcept override { return "Error loading file."; }
};


#endif //PAZAAK_EXCEPTIONS_H
