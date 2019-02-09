//
// Created by tomtom on 03/02/19.
//

#ifndef TMPPAZAAK_DOUBLECARD_H
#define TMPPAZAAK_DOUBLECARD_H


#include "../../CardInterface/Card.h"

class DoubleCard : public Card {

public:
    int play(vector<int> &playedCards, int currentScore, int opponentScore) const override;

    string getDescription() const override;

};


#endif //TMPPAZAAK_DOUBLECARD_H
