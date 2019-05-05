//
// Created by tomtom on 05/05/19.
//

#ifndef PAZAAK_DRAWCARD_H
#define PAZAAK_DRAWCARD_H


#include "Card.h"

class DrawCard : public Card {
public:
    std::string getDescription() const override;

    int play(std::vector<int> &playedCards, int currentScore, int opponentScore) const override;
};


#endif //PAZAAK_DRAWCARD_H
