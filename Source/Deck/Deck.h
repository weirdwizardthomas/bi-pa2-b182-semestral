//
// Created by tomtom on 08/02/19.
//

#ifndef PAZAAK_DECK_H
#define PAZAAK_DECK_H


//Libraries---------------------------------
#include <vector>
#include <random>
#include <cstdlib>

//Classes-----------------------------------
#include "../Cards/CardInterface/Card.h"
#include "../Player/Hand/Hand.h"


//Namespace--------------------------------
using namespace std;

class Deck {
private:
    vector<Card *> cards;

    size_t generateBoundIndex() const;

public:
    Deck() = default;

    Deck(const vector<Card *> &cards);

    ~Deck() = default;

    Hand *drawCards(Hand *currentHand);

    void shuffle();

    int playCard(size_t cardIndex, vector<int> &playedCards, int currentScore, int opponentScore);

    size_t getDeckSize() const;

    friend ostream &operator<<(ostream &out, const Deck &deck);


};


#endif //PAZAAK_DECK_H
