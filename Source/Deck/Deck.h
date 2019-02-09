//
// Created by tomtom on 08/02/19.
//

#ifndef PAZAAK_DECK_H
#define PAZAAK_DECK_H

#include <vector>
#include <cstdlib>

#include "../Cards/CardInterface/Card.h"
#include "../Player/Hand/Hand.h"

using namespace std;

class Deck {
private:
    vector<Card *> cards;

public:

    Hand * drawCards(Hand *currentHand);
};


#endif //PAZAAK_DECK_H
