//
// Created by tomtom on 03/02/19.
//

#ifndef TMPPAZAAK_DUALCARD_H
#define TMPPAZAAK_DUALCARD_H


//Libraries---------------------------------
#include <iostream>
#include <stdlib.h>

//Classes-----------------------------------
#include "../../Card Interface/Card.h"

//Namespaces--------------------------------
using namespace std;


class DualCard : public Card {

private:
    //Attributes----------------------------
    int effects[2];

public:
    //Constructor---------------------------
    DualCard(int left, int right);

    //Methods-------------------------------
    int play(int currentScore, vector<Card *> &playedCards) const override;

    string getDescription() const override;

    int chooseEffect() const;
};


#endif //TMPPAZAAK_DUALCARD_H
