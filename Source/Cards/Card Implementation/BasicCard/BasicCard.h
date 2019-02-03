//
// Created by tomtom on 03/02/19.
//

#ifndef PAZAAK_BASICCARD_H
#define PAZAAK_BASICCARD_H

#include "../../Card Interface/Card.h"


class BasicCard : public Card {

private:
    //Attributes-----------------------------------------
    int value;
    string description;

    string getDescription();

public:

    //Constructors-&&-Destructor-------------------------
    BasicCard() = default;

    BasicCard(int value);

    BasicCard(BasicCard &source);

    ~BasicCard() = default;

    //Methods--------------------------------------------
    int getValue();
};


#endif //PAZAAK_BASICCARD_H
