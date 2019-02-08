//
// Created by tomtom on 03/02/19.
//

#ifndef TMPPAZAAK_DUALCARD_H
#define TMPPAZAAK_DUALCARD_H


//Libraries---------------------------------
#include <iostream>
#include <cstdlib>

//Classes-----------------------------------
#include "../../Card Interface/Card.h"

//Namespaces--------------------------------
using namespace std;


class DualCard : public Card {

protected:
    //Attributes----------------------------
    int effects[2];

    int chooseEffect() const;

public:
    //Constructor---------------------------
    DualCard(int left, int right);

    //Methods-------------------------------
    int play(vector<int> playedCards, int currentScore, int opponentScore) const override;

    string getDescription() const override;

};


#endif //TMPPAZAAK_DUALCARD_H
