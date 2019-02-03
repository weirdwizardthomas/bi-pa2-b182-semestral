//
// Created by tomtom on 03/02/19.
//

#ifndef PAZAAK_DUALCARD_H
#define PAZAAK_DUALCARD_H

#include <iostream>

#include "../../Card Interface/Card.h"

using namespace std;

class DualCard : public Card {

private:
    //Attributes-----------------------------------------
    int effects[2];
    string description;

    //Methods--------------------------------------------
    string getDescription() const override;

public:
    //Constructors-&&-Destructor-------------------------
    DualCard(int firstEffect, int secondEffect);

    ~DualCard() = default;

    //Methods--------------------------------------------
    int getValue() const override;

    int chooseEffect() const;
};


#endif //PAZAAK_DUALCARD_H
