//
// Created by tomtom on 09/02/19.
//

#ifndef PAZAAK_HAND_H
#define PAZAAK_HAND_H

#include "../../Cards/CardInterface/Card.h"

class Hand {
private:
    std::vector <Card *> cards;

public:
    void addCard(Card * card);
};


#endif //PAZAAK_HAND_H
