//
// Created by tomtom on 08/02/19.
//

#include "FlipCard.h"

//Namespace---------------------------------
using namespace std;

const std::string FlipCard::FLIP_SIGN = " <~> ";

FlipCard::FlipCard(int left, int right) : DualCard(abs(left), abs(right)) {}

int FlipCard::play(vector<int> &playedCards, int currentScore, int opponentScore) const {
    for (int &card : playedCards) //TODO CHECK THIS' FUNCTIONALITY
        if (card == values.first || card == values.second)
            card = -card;

    return 0;
}

string FlipCard::getDescription() const {
    return Card::PLUS_SIGN + to_string(values.first) + FlipCard::FLIP_SIGN +
           Card::MINUS_SIGN + to_string(values.first) + " " + Card::DUAL_DELIMITER + " " +
           Card::PLUS_SIGN + to_string(values.second) + FlipCard::FLIP_SIGN +
           Card::MINUS_SIGN + to_string(values.second);
}




