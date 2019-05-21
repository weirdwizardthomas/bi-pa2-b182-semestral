//
// Created by tomtom on 04/05/19.
//

#ifndef PAZAAK_EXCEPTIONS_H
#define PAZAAK_EXCEPTIONS_H

#include <exception>
#include <cstring>

using namespace std;

/**
 * Directory has not been found or needs special permission to access
 */
class CannotOpenDirectory : public exception {
private:
    string message;
public:
    CannotOpenDirectory(const string &message) : message(message) {}

    const char *what() const throw() { return message.c_str(); }

};

/**
 * File does not fit the prescribed format
 */
class ParseError : public exception {
};

/**
 * File has not been found or is corrupted
 */
class InvalidFileException : public exception {
    string message;
public:
    InvalidFileException(const string &message) : message(message) {
    }

    const char *what() const throw() {
        return message.c_str();
    }
};


#endif //PAZAAK_EXCEPTIONS_H
