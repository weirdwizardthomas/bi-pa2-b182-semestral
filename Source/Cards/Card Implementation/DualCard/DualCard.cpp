//
// Created by tomtom on 03/02/19.
//

#include "DualCard.h"


int DualCard::getValue() const {

    cout << this;
    return effects[chooseEffect()];

}

int DualCard::chooseEffect() const {
    bool invalidInput = true;
    int input = 0;

    while (invalidInput) {
        cin >> input;
        invalidInput = (input != 0 && input != 1);
    }

    return input;
}


string DualCard::getDescription() const {
    return this->description;
}

DualCard::DualCard(int firstEffect, int secondEffect) {

    if (!validInput(firstEffect) || !validInput(secondEffect))
        throw "Invalid argument in card creation."; //extract to superior so it isn't repeated in multiple source files

    this->effects[0] = firstEffect;
    this->effects[1] = secondEffect;
    this->description = to_string(this->effects[0]) + "|" + to_string(this->effects[1]);
}
