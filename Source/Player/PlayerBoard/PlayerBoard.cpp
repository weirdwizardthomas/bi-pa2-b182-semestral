//
// Created by tomtom on 08/02/19.
//

#include "PlayerBoard.h"

PlayerBoard::PlayerBoard() {
    this->currentScore = 0;
    this->roundsWon = 0;
    this->standing = false;
}

int PlayerBoard::getCurrentScore() const {
    return this->currentScore;
}

void PlayerBoard::setCurrentScore(int currentScore) {
    this->currentScore = currentScore;
}

bool PlayerBoard::isStanding() const {
    return standing;
}

vector<int> PlayerBoard::getPlayedCards() const {
    return this->playedCards;
}

void PlayerBoard::addPlayedCard(int value) {
    this->playedCards.push_back(value);
}

void PlayerBoard::addPoint() {
    this->roundsWon++;
}

void PlayerBoard::setStanding(bool standing) {
    this->standing = standing;
}

void PlayerBoard::stand() {
    this->setStanding(true);
}
