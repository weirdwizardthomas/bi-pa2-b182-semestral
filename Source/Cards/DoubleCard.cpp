//
// Created by tomtom on 03/02/19.
//

#include "DoubleCard.h"

using namespace std;

int DoubleCard::play(std::vector<int> &playedCards, int currentScore, int opponentScore) const {
    int lastPlayedCard = playedCards.back();
    lastPlayedCard *= 2;
    playedCards.erase(playedCards.end() - 1);
    return lastPlayedCard;
}

string DoubleCard::getDescription() const { return "Double the value of the last played card."; }