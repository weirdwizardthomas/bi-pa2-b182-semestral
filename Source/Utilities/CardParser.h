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

//This doesn't need to be a class, it could be a regular cpp with functions, TODO consult whether a class is better than just functions
class CardParser {

private:
    const string files[3] = {BASIC_CARD, DUAL_CARD, FLIP_CARD};

    vector<string> getFileLines(string filePath) const;

    void validLines(vector<string> fileLines, string mode) const;

    pair<int, int> getDualValues(const string &line) const;

    void loadBasicCards(map<string, Card *> &cards) const;

    void loadDualCards(map<string, Card *> &cards) const;

    void loadFlipCards(map<string, Card *> &cards) const;

public:
    map<string, Card *> loadAllCards();

};


#endif //PAZAAK_CARDPARSER_H
