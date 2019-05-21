//
// Created by tomtom on 03/02/19.
//

#include <exception>

#include "BasicCard.h"

using namespace std;


BasicCard::BasicCard(int value) : value(value) {
    if (!validInput(value))
        throw invalid_argument("Invalid Basic Card value");
}

int BasicCard::play(std::vector<int> &playedCards, int currentScore, int opponentScore) const { return value; }

int BasicCard::play() const { return value; }

string BasicCard::getDescription() const { return offsetPositiveNumber(value); }

