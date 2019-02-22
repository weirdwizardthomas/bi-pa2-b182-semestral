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

//This doesn't need to be a class, it could be a regular cpp with functions, TODO consult whether a class is better than just functions
class CardParser {

private:
    const std::string files[3] = {BASIC_CARD, DUAL_CARD, FLIP_CARD};

    std::vector<std::string> getFileLines(std::string filePath) const;

    void validLines(std::vector<std::string> fileLines, std::string mode) const;

    pair<int, int> getDualValues(const std::string &line) const;

    void loadBasicCards(std::map<std::string, Card *> &cards) const;

    void loadDualCards(std::map<std::string, Card *> &cards) const;

    void loadFlipCards(std::map<std::string, Card *> &cards) const;

public:
    std::map<std::string, Card *> loadAllCards();

};


#endif //PAZAAK_CARDPARSER_H
