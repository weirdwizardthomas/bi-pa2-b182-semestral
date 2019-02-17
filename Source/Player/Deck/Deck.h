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

//Namespaces--------------------------------
using namespace std;

class Deck {
private:
    vector<Card *> cards;

    size_t generateBoundIndex() const;

    void getCardChoicesFromUser(const map<string, Card *> &allCards);

    void shuffle();


public:
    Deck() = default;

    Deck(map<string, Card *> &allCards);

    Deck(const vector<Card *> &cards);

    Hand *drawCards(Hand *currentHand);

    int playCard(size_t cardIndex, vector<int> &playedCards, int currentScore, int opponentScore);

    void addCard(Card *card);

    size_t getDeckSize() const;

    static Deck loadFromFile();
    static vector<string> getDeckFiles();

    friend ostream &operator<<(ostream &out, const Deck &deck);

};


#endif //PAZAAK_DECK_H
