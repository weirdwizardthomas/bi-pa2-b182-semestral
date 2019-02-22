//
// Created by tomtom on 03/02/19.
//

#include "DoubleCard.h"

using namespace std;

int DoubleCard::play(vector<int> &playedCards, int currentScore, int opponentScore) const {

    int tmp = playedCards.back();
    playedCards.back() *=2;
    return tmp;
}

string DoubleCard::getDescription() const {
    return "Double the value of the last played card.";
}
