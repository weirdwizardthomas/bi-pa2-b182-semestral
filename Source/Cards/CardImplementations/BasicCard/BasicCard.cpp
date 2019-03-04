//
// Created by tomtom on 03/02/19.
//


#include "BasicCard.h"

using namespace std;

BasicCard::BasicCard(int value) {
    if (!validInput(value))
        throw "Invalid card value.";

    this->value = value;
}

int BasicCard::play(vector<int> &playedCards, int currentScore, int opponentScore) const {
    return this->value;
}

string BasicCard::getDescription() const {
    return offsetPositiveNumber(this->value);
}

