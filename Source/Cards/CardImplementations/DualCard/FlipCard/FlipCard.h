//
// Created by tomtom on 08/02/19.
//

#ifndef PAZAAK_FLIPCARD_H
#define PAZAAK_FLIPCARD_H


//Libraries---------------------------------

#include <cstdlib>

//Classes-----------------------------------
#include "../DualCard.h"

//Definitions-------------------------------
#define FLIP_SIGN  " <~> "

//Namespace---------------------------------
using namespace std;

class FlipCard : public DualCard {

public:
    FlipCard(int a, int b);

    int play(vector<int> playedCards, int currentScore, int opponentScore) const override;

    string getDescription() const override;
};


#endif //PAZAAK_FLIPCARD_H
