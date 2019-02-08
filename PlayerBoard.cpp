//
// Created by tomtom on 08/02/19.
//

#include "PlayerBoard.h"

PlayerBoard::PlayerBoard() {
    this->currentScore = 0;
}

int PlayerBoard::getCurrentScore() const {
    return this->currentScore;
}

void PlayerBoard::setCurrentScore(int currentScore) {
    this->currentScore = currentScore;
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

