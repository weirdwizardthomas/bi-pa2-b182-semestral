//
// Created by tomtom on 08/02/19.
//

#include "PlayerBoard.h"

using namespace std;

const int LOWER_BOUND = -10;
const int UPPER_BOUND = 10;

//--------------------------------------------------------------------------------------------------------------------//
//Constructor-Destructor----------------------------------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------------------------//
PlayerBoard::PlayerBoard() {
    this->currentScore = 0;
    this->roundsWon = 0;
    this->playedCards.reserve(TABLE_SIZE);
    this->mainDeck.reserve(UPPER_BOUND * MAIN_DECK_CARD_COPIES);
    this->standing = false;

    ///Generates MAIN_DECK_CARD_COPIES copies of 1-UPPER_BOUND cards
    for (size_t i = 1; i <= UPPER_BOUND; i++)
        for (size_t j = 0; j < MAIN_DECK_CARD_COPIES; j++)
            this->mainDeck.push_back(new BasicCard(i));
}

PlayerBoard::~PlayerBoard() {
    //TODO solve the virtual destructor thingy
    for (auto &i : this->mainDeck)
        delete i;
}

//--------------------------------------------------------------------------------------------------------------------//
//Getters-------------------------------------------------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------------------------//
int PlayerBoard::getCurrentScore() const {
    return this->currentScore;
}

int PlayerBoard::drawCardFromMainDeck() {
    size_t index = generateRandomBoundIndex();
    int value = this->getRandomCard(index)->play();
    delete this->mainDeck[index];
    this->mainDeck.erase(mainDeck.begin() + index);
    return value;
}

int PlayerBoard::getOpener() const {
    if (this->mainDeck.empty())
        throw "DECK IS EMPTY"; //TODO proper exception
    return this->getRandomCard(generateRandomBoundIndex())->play();
}

vector<int> &PlayerBoard::getPlayedCards() {
    return this->playedCards;
}

size_t PlayerBoard::getPlayedCardsCount() const {
    return this->playedCards.size();
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

//--------------------------------------------------------------------------------------------------------------------//
//Setters-------------------------------------------------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------------------------//
void PlayerBoard::addPlayedCard(int cardValue) {
    //No added value, card was either a double or a flip, which isn't recorded as played
    if (cardValue == 0)
        return;
    this->playedCards.push_back(cardValue);
    this->recalculateScore();
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

void PlayerBoard::reset() {
    this->currentScore = 0;
    this->resetPlayedCards();
    this->setStanding(false);
}

void PlayerBoard::resetPlayedCards() {
    this->playedCards.clear();
    this->playedCards.reserve(TABLE_SIZE);
}

//--------------------------------------------------------------------------------------------------------------------//
//Other methods-------------------------------------------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------------------------//
void PlayerBoard::recalculateScore() {
    this->currentScore = 0;
    for (auto playedCard : this->playedCards)
        currentScore += playedCard;
}

BasicCard *PlayerBoard::getRandomCard(size_t index) const {
    return this->mainDeck[index];
}

unsigned long PlayerBoard::generateRandomBoundIndex() const { return (size_t) rand() % mainDeck.size(); }

