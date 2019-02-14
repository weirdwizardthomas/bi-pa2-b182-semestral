//
// Created by tomtom on 14/02/19.
//

#ifndef PAZAAK_CARDPARSER_H
#define PAZAAK_CARDPARSER_H

#include <string>
#include <fstream>
#include <vector>
#include <map>

#include "../Cards/CardInterface/Card.h"

#define CARD_FOLDER_PATH "../../Data/Cards/"
#define BASIC_CARD "BasicCards"
#define DUAL_CARD "DualCards"
#define FLIP_CARD "FlipCards"

#define WHITE_SPACES " \t\n\r\f\v" //maybe define this instead of a global

using namespace std;

class CardParser {

private:
    string files[3] = {BASIC_CARD, DUAL_CARD, FLIP_CARD};

    vector<string> getFileLines(string filePath) const;
    void validLines(vector<string> fileLines, string mode) const;

public:
    map<string, Card *> loadAllCards();

    Card *callConstructor(const string &basic_string, vector<string> vector);
};


#endif //PAZAAK_CARDPARSER_H
