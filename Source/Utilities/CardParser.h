//
// Created by tomtom on 14/02/19.
//

#ifndef PAZAAK_CARDPARSER_H
#define PAZAAK_CARDPARSER_H

//Libraries---------------------------------
#include <fstream>
#include <map>

//Classes-----------------------------------
#include "ParserStringUtilities.cpp"
#include "../Cards/CardInterface/Card.h"
#include "../Cards/CardImplementations/DualCard/FlipCard/FlipCard.h"
#include "../Cards/CardImplementations/BasicCard/BasicCard.h"

//Definitions-------------------------------
#define CARD_FOLDER_PATH "../Data/Cards/"
#define BASIC_CARD "BasicCards"
#define DUAL_CARD "DualCards"
#define FLIP_CARD "FlipCards"

//Namespaces--------------------------------
using namespace std;

class CardParser {

private:
    const string files[3] = {BASIC_CARD, DUAL_CARD, FLIP_CARD};

    vector<string> getFileLines(string filePath) const;

    void validLines(vector<string> fileLines, string mode) const;
    pair<int, int> getDualValues(const string &line) const;
public:
    map<string, Card *> loadAllCards();


};


#endif //PAZAAK_CARDPARSER_H
