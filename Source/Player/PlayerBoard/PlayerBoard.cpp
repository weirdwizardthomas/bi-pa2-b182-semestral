//
// Created by tomtom on 08/02/19.
//

#include "PlayerBoard.h"

using namespace std;
const std::string PlayerBoard::PLAYED_CARDS_DELIMITER = " ";


//--------------------------------------------------------------------------------------------------------------------//
//Constructor-Destructor----------------------------------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------------------------//
PlayerBoard::PlayerBoard() {
    currentScore = 0;
    roundsWon = 0;
    playedCards.reserve(PlayerBoard::TABLE_SIZE);
    mainDeck.reserve(Card::UPPER_BOUND * PlayerBoard::MAIN_DECK_CARD_COPIES);
    standing = false;

    ///Generates MAIN_DECK_CARD_COPIES copies of 1-Card::UPPER_BOUND cards
    for (size_t i = 1; i <= Card::UPPER_BOUND; i++)
        for (size_t j = 0; j < PlayerBoard::MAIN_DECK_CARD_COPIES; j++)
            mainDeck.push_back(new BasicCard(i));
}

PlayerBoard::~PlayerBoard() {
    for (auto &i : mainDeck)
        delete i;
}

//--------------------------------------------------------------------------------------------------------------------//
//Getters-------------------------------------------------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------------------------//
int PlayerBoard::getCurrentScore() const { return currentScore; }

int PlayerBoard::drawCardFromMainDeck() {
    size_t index = generateRandomBoundIndex();
    int value = getCardAt(index)->play();
    delete mainDeck[index];
    mainDeck.erase(mainDeck.begin() + index);
    return value;
}

int PlayerBoard::getOpener() const {
    if (mainDeck.empty())
        throw "DECK IS EMPTY"; //TODO proper exception
    return getCardAt(generateRandomBoundIndex())->play();
}

vector<int> &PlayerBoard::getPlayedCards() { return playedCards; }

size_t PlayerBoard::getPlayedCardsCount() const { return playedCards.size(); }

size_t PlayerBoard::getRoundsWon() const { return roundsWon; }

bool PlayerBoard::isStanding() const { return standing; }

string PlayerBoard::showCardsPlayed() const {
    string output;
    for (auto &cardValue : playedCards) {
        output.append(to_string(cardValue));
        if (cardValue !=
            *(playedCards.end())) //places a PLAYED_CARDS_DELIMITER between each substring of the output string
            output.append(PlayerBoard::PLAYED_CARDS_DELIMITER);
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
    playedCards.push_back(cardValue);
    recalculateScore();
}

void PlayerBoard::addPoint() { roundsWon++; }

void PlayerBoard::setStanding(bool standing) { standing = standing; }

void PlayerBoard::stand() { setStanding(true); }

void PlayerBoard::reset() {
    currentScore = 0;
    resetPlayedCards();
    setStanding(false);
}

void PlayerBoard::resetPlayedCards() {
    playedCards.clear();
    playedCards.reserve(PlayerBoard::TABLE_SIZE);
}

//--------------------------------------------------------------------------------------------------------------------//
//Other methods-------------------------------------------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------------------------//
void PlayerBoard::recalculateScore() {
    currentScore = 0;
    for (auto playedCard : playedCards)
        currentScore += playedCard;
}

BasicCard *PlayerBoard::getCardAt(size_t index) const { return mainDeck[index]; }

unsigned long PlayerBoard::generateRandomBoundIndex() const { return (size_t) rand() % mainDeck.size(); }

