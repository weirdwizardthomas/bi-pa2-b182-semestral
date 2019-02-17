//
// Created by tomtom on 08/02/19.
//

#ifndef PAZAAK_DECK_H
#define PAZAAK_DECK_H

//Libraries---------------------------------
#define NEWLINE '\n'

#include <vector>
#include <random>
#include <algorithm>
#include <cstdlib>

//Classes-----------------------------------
#include "../../Cards/CardInterface/Card.h"
#include "../Hand/Hand.h"

//Namespaces-------------------------------
using namespace std;

class Deck {
private:
    vector<Card *> cards;

    size_t generateBoundIndex() const;

public:
    Deck() = default;
    Deck(map<string, Card*> & allCards);

    Deck(const vector<Card *> &cards);

    ~Deck() = default;

    Hand *drawCards(Hand *currentHand);

    void shuffle();

    int playCard(size_t cardIndex, vector<int> &playedCards, int currentScore, int opponentScore);

    void addCard(Card * card);

    size_t getDeckSize() const;

    friend ostream &operator<<(ostream &out, const Deck &deck);

    void getCardChoicesFromUser(const map<string, Card *> &allCards);
};


#endif //PAZAAK_DECK_H
