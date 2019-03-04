//
// Created by tomtom on 08/02/19.
//

#include "PlayerBoard.h"

using namespace std;

PlayerBoard::PlayerBoard() {
    this->currentScore = 0;
    this->roundsWon = 0;
    this->playedCards.reserve(TABLE_SIZE);
    this->sidedeck.reserve(SIDEDECK_SIZE);
    this->standing = false;
}

//Getters------------------------------------------
int PlayerBoard::getCurrentScore() const {
    return this->currentScore;
}

vector<int> &PlayerBoard::getPlayedCards() {
    return this->playedCards;
}

size_t PlayerBoard::getRoundsWon() const {
    return this->roundsWon;
}

bool PlayerBoard::isStanding() const {
    return this->standing;
}

string PlayerBoard::showCardsPlayed() const {
    string output;
    for (auto &cardValue : this->playedCards) {
        output.append(to_string(cardValue));
        if (cardValue != *(this->playedCards.end())) //places a SPACE between each substring of the output string
            output.append(SPACE);
    }

    return output;
}

//Setters-----------------------------------------
void PlayerBoard::addPoint() {
    this->roundsWon++;
}

void PlayerBoard::setStanding(bool standing) {
    this->standing = standing;
}

void PlayerBoard::stand() {
    this->setStanding(true);
}

size_t PlayerBoard::getPlayedCardsCount() const {
    return this->playedCards.size();
}

void PlayerBoard::addPlayedCard(int cardValue) {
    //No added value, card was either a double or a flip, which isn't recorded as played
    if (cardValue == 0)
        return;
    this->playedCards.push_back(cardValue);
    this->recalculateScore();
}

//Other methods------------------------------------
void PlayerBoard::recalculateScore() {
    this->currentScore = 0;
    for (auto playedCard : this->playedCards)
        currentScore += playedCard;
}

