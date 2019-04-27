//
// Created by tomtom on 08/02/19.
//

#include "FlipCard.h"

//Namespace---------------------------------
using namespace std;

const std::string FlipCard::FLIP_SIGN = " <~> ";

FlipCard::FlipCard(int a, int b) : DualCard(abs(a) <= abs(b) ? abs(a) : abs(b), (abs(a) <= abs(b) ? abs(b) : abs(a))) {}

int FlipCard::play(vector<int> &playedCards, int currentScore, int opponentScore) const {
    for (int i : playedCards)
        if (i == effects[0] || i == effects[1])
            i = -i;

    return 0;
}

string FlipCard::getDescription() const {
    return Card::PLUS_SIGN + to_string(effects[0]) + FlipCard::FLIP_SIGN +
           Card::MINUS_SIGN + to_string(effects[0]) + " " + Card::DUAL_DELIMITER + " " +
           Card::PLUS_SIGN + to_string(effects[1]) + FlipCard::FLIP_SIGN +
           Card::MINUS_SIGN + to_string(effects[1]);
}




