//
// Created by tomtom on 08/02/19.
//

#include "PlayerBoard.h"

PlayerBoard::PlayerBoard(Player *currentOpponent) : currentOpponent(currentOpponent) {
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

vector<Card *> PlayerBoard::getPlayedCards() const {
    return this->playedCards;
}

void PlayerBoard::setPlayedCards(const vector<Card *> &playedCards) {
    this->playedCards = playedCards;
}

void PlayerBoard::addPlayedCard(Card *card) {
    this->playedCards.push_back(card);
}

void PlayerBoard::addPoint() {
    this->roundsWon++;
}

void PlayerBoard::setStanding(bool standing) {
    this.standing = standing;
}

void PlayerBoard::stand() {
    this->setStanding(true);
}

Player *PlayerBoard::getCurrentOpponent() const {
    return this->currentOpponent;
}

