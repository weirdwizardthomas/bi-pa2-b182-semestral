//
// Created by tomtom on 08/02/19.
//

#ifndef PAZAAK_DECK_H
#define PAZAAK_DECK_H

//Libraries---------------------------------
#include <vector>
#include <random>
#include <algorithm>
#include <cstdlib>
#include <dirent.h>

//Classes-----------------------------------
#include "../../Cards/CardInterface/Card.h"
#include "../Hand/Hand.h"

//Definitions-------------------------------
#define NEWLINE '\n'
#define SPACE ' '
#define DECKS_DIRECTORY_PATH "../Data/Decks"
#define CARD_DELIMITER ","
#define BASIC_CARD_LEAD "BasicCard:"
#define DOUBLE_CARD_LEAD "DoubleCards:"
#define DUAL_CARD_LEAD "DualCards:"
#define FLEX_CARD_LEAD "FlexCards:"
#define FlIP_CARD_LEAD "FlipCards:"

class Deck {
private:
    std::vector<Card *> cards;

    size_t generateBoundIndex() const;

    void getCardChoicesFromUser(const map<std::string, Card *> &allCards);

    void shuffle();

    static std::vector<std::string> getDecksFromDirectory();

    /**
     * loads content of a single file in DECKS_DIRECTORY_PATH
     * @param file name of the file to be opened 
     * @return individual lines of the file
     */
    static std::vector<std::string> loadFileContent(std::string file);


public:
    Deck() = default;

    Deck(map<std::string, Card *> &allCards);

    Deck(const std::vector<Card *> &cards);

    Hand *drawCards(Hand *currentHand);

    int playCard(size_t cardIndex, std::vector<int> &playedCards, int currentScore, int opponentScore);

    void addCard(Card *card);

    size_t getDeckSize() const;

    friend std::ostream &operator<<(std::ostream &out, const Deck &deck);

    /**
     * Queries the user with deck name to pick from
     * @param files Contents of the /Data/Decks directory
     * @return index of the deck chosen
     */
    static size_t selectDeckFile(const std::vector<std::string> &files);

    static std::vector<std::string> getDeckFiles();

    static Deck loadFromFile();


};


#endif //PAZAAK_DECK_H
