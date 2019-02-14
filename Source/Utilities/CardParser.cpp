//
// Created by tomtom on 14/02/19.
//

#include "CardParser.h"

//Trimming functions, gained from : https://stackoverflow.com/a/25385766

// trim from end of string (right)
inline std::string &rtrim(std::string &s) {
    s.erase(s.find_last_not_of(WHITE_SPACES) + 1);
    return s;
}

// trim from beginning of string (left)
inline std::string &ltrim(std::string &s) {
    s.erase(0, s.find_first_not_of(WHITE_SPACES));
    return s;
}

// trim from both ends of string (right then left)
inline std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}

vector<string> CardParser::getFileLines(string filePath) const {
    fstream cardFile;
    cardFile.open(filePath, ios::in);

    if (!cardFile.is_open())
        throw "FILE EXCEPTION";

    string line;
    vector<string> lines;

    while (getline(cardFile, line)) {
        if (line.find_first_not_of(' ') != string::npos) //not an empty line
            lines.push_back(trim(line));
    }

    return lines;
}

map<string, Card *> CardParser::loadAllCards() {

    for (const string &cardFileType: this->files) {
        vector<string> fileLines = getFileLines(CARD_FOLDER_PATH + cardFileType);
        fileLines = validLines(fileLines);
        //add to map
    }

}

//TODO need to reconsider this method's implementation
void CardParser::validLines(vector<string> fileLines, string mode) const {

    if (mode == BASIC_CARD) {
        for (const string &line : fileLines)
            stoi(line); //TODO throws an exception when NaN - maybe TRY CATCH ?

    } else {
        for (const string &line : fileLines) {
            size_t delimiterIndex = line.find(DUAL_DELIMITER);
            if(delimiterIndex == string::npos)
                throw "INVALID DUAL CARD FORMAT, MISSING DELIMITER"; //TODO proper exception
        }
    }
}

Card *CardParser::callConstructor(const string &cardFileType, vector<string> fileLines) {
    if(cardFileType == BASIC_CARD)

}

