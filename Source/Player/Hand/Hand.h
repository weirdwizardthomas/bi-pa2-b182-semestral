//
// Created by tomtom on 09/02/19.
//

#ifndef PAZAAK_HAND_H
#define PAZAAK_HAND_H

#include <iostream>

#include "../../Cards/CardInterface/Card.h"

class Hand {
private:
    std::vector<Card *> cards;

public:
    void addCard(Card *card);

    int playCard(size_t cardIndex, std::vector<int> &playedCards, int currentScore, int opponentScore);

    friend std::ostream &operator<<(std::ostream &out, const Hand &hand);
};


#endif //PAZAAK_HAND_H
