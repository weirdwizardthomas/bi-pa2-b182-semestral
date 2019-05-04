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
        return ("Cannot open the" + DeckParser::DECKS_DIRECTORY_PATH + "directory.").c_str();
    }
};

class CannotOpenFile : public exception {
    const char *what() const noexcept override { return ("Cannot open file."); }
};

class ParseError : public exception {
    const char *what() const noexcept override { return ("Error reading file"); }
};

//TODO EXTRACT EXCEPTIONS TO A SEPARATE FILE
class InvalidFileException : public exception {//TODO add the file name
    const char *what() const noexcept override { return "Error loading that file."; }
};


#endif //PAZAAK_EXCEPTIONS_H
