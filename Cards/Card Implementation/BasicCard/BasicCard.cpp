//
// Created by tomtom on 03/02/19.
//

#include "BasicCard.h"

BasicCard::BasicCard(int value) {
    if (!validInput(value))
        throw "Invalid card value.";

    this->value = value;
}

int BasicCard::play(int currentScore, vector<Card *> &playedCards) const {
    return currentScore + this->value;
}

string BasicCard::getDescription() const {
    return offsetPositiveNumber(this->value);
}


