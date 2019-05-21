//
// Created by tomtom on 04/05/19.
//

#ifndef PAZAAK_EXCEPTIONS_H
#define PAZAAK_EXCEPTIONS_H

#include <exception>

#include "DeckParser.h"

using namespace std;

class CannotOpenDirectory : public exception {
public:
    const char *what() const noexcept override {
        return (string("Cannot open the") + DeckParser::DECKS_DIRECTORY + "directory.").c_str();
    }
};

class CannotOpenFile : public exception {
    const char *what() const noexcept override { return ("Cannot open file."); }
};

class ParseError : public exception {
    const char *what() const noexcept override { return ("Error reading file"); }
};

class InvalidFileException : public exception {
    const char *what() const noexcept override { return "Error loading file."; }
};


#endif //PAZAAK_EXCEPTIONS_H
