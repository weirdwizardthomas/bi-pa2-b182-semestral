//
// Created by tomtom on 03/02/19.
//

#ifndef TMPPAZAAK_BASICCARD_H
#define TMPPAZAAK_BASICCARD_H


//Libraries---------------------------------
#include "../../Card Interface/Card.h"

class BasicCard : public Card {

private:
    int value;

public:
    BasicCard(int value);

    int play(int currentScore, vector<int> playedCards) const override;

    string getDescription() const override;
};


#endif //TMPPAZAAK_BASICCARD_H
