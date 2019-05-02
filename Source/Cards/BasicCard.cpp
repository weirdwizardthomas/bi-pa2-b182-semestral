//
// Created by tomtom on 03/02/19.
//

#include "BasicCard.h"

#include <exception>

using namespace std;

BasicCard::BasicCard(int value) : value(value) {
    if (!validInput(value))
        throw invalid_argument("Invalid Basic Card value");
}

int BasicCard::play(vector<int> &playedCards, int currentScore, int opponentScore) const { return play(); }

int BasicCard::play() const { return value; }

string BasicCard::getDescription() const { return offsetPositiveNumber(value); }


