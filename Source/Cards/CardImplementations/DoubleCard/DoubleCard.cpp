//
// Created by tomtom on 03/02/19.
//

#include "DoubleCard.h"

using namespace std;

int DoubleCard::play(vector<int> &playedCards, int currentScore, int opponentScore) const {
    //Replaces the last value
    int dummy = playedCards.back();
    dummy *= 2;
    playedCards.erase(playedCards.end());
    return dummy;
}

string DoubleCard::getDescription() const {
    return "Double the value of the last played card.";
}
