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
#define DECKS_DIRECTORY_PATH "../Data/Decks"
#define CARD_DELIMITER ","
#define BASIC_CARD_LEAD "BasicCard:"
#define DOUBLE_CARD_LEAD "DoubleCards:"
#define DUAL_CARD_LEAD "DualCards:"
#define FLEX_CARD_LEAD "FlexCards:"
#define FlIP_CARD_LEAD "FlipCards:"

//Namespaces--------------------------------
#define SPACE ' '
using namespace std;

class Deck {
private:
    vector<Card *> cards;

    size_t generateBoundIndex() const;

    void getCardChoicesFromUser(const map<string, Card *> &allCards);

    void shuffle();

    static vector<string> getDecksFromDirectory();

    static vector<string> loadFileContent(string file);


public:
    Deck() = default;

    Deck(map<string, Card *> &allCards);

    Deck(const vector<Card *> &cards);

    Hand *drawCards(Hand *currentHand);

    int playCard(size_t cardIndex, vector<int> &playedCards, int currentScore, int opponentScore);

    void addCard(Card *card);

    size_t getDeckSize() const;

    friend ostream &operator<<(ostream &out, const Deck &deck);

    static size_t selectDeckFile(const vector<string> &files);

    static vector<string> getDeckFiles();

    static Deck loadFromFile();


};


#endif //PAZAAK_DECK_H
