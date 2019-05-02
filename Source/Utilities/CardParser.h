//
// Created by tomtom on 14/02/19.
//

#ifndef PAZAAK_CARDPARSER_H
#define PAZAAK_CARDPARSER_H

//Libraries---------------------------------
#include <fstream>
#include <map>

//Classes-----------------------------------
#include "Utilities.cpp"
#include "../Cards/Card.h"
#include "../Cards/FlipCard.h"
#include "../Cards/BasicCard.h"
#include "../Cards/DoubleCard.h"
#include "../Cards/FlexCard.h"


//This doesn't need to be a class, it could be a regular cpp with functions, TODO consult whether a class is better than just functions
class CardParser {

private:

    static void addDoubleCards(std::map<std::string, Card *> &cards);

    static void addFlexCards(std::map<std::string, Card *> &cards);

    static string pathOf(const std::string &filename);

    static pair<int, int> getDualValues(const std::string &line);

    static std::vector<std::string> getFileLines(const std::string &filePath);

    static void loadBasicCards(std::map<std::string, Card *> &cards);

    static void loadDualCards(std::map<std::string, Card *> &cards);

    static void loadFlipCards(std::map<std::string, Card *> &cards);

    static void validLines(std::vector<std::string> fileLines, const std::string& mode);

public:
    static const std::string CARD_FOLDER_PATH;
    static const std::string BASIC_CARD;
    static const std::string DUAL_CARD;
    static const std::string FLIP_CARD;
    static const std::string DUAL_DELIMITER;

    static std::map<std::string, Card *> loadAllCards();
};

#endif //PAZAAK_CARDPARSER_H
