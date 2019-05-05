//
// Created by tomtom on 08/02/19.
//

#include "PlayerBoard.h"

using namespace std;

const char *PlayerBoard::PLAYED_CARDS_DELIMITER{" "};


PlayerBoard::PlayerBoard() : currentScore(0), roundsWon(0), standing(false),
                             randomNumberGenerator(0, Card::UPPER_BOUND * PlayerBoard::MAIN_DECK_CARD_COPIES) {
    playedCards.reserve(PlayerBoard::TABLE_SIZE);
    mainDeck.reserve(Card::UPPER_BOUND * PlayerBoard::MAIN_DECK_CARD_COPIES);
    generateMainDeck();
}

void PlayerBoard::generateMainDeck() {
    for (size_t i = 1; i <= Card::UPPER_BOUND; i++)
        for (size_t j = 0; j < PlayerBoard::MAIN_DECK_CARD_COPIES; ++j)
            mainDeck.push_back(new BasicCard(i));
}

PlayerBoard::~PlayerBoard() {
    for (auto &i : mainDeck)
        delete i;
}

int PlayerBoard::drawCardFromMainDeck() {
    size_t index = randomNumberGenerator();
    int value = mainDeck[index]->play();
    delete mainDeck[index];
    mainDeck.erase(mainDeck.begin() + index);
    randomNumberGenerator.lowerCeiling(mainDeck.size());
    return value;
}

int PlayerBoard::getCurrentScore() const { return currentScore; }

int PlayerBoard::getOpener() { return mainDeck[randomNumberGenerator()]->play(); }

vector<int> &PlayerBoard::getPlayedCards() { return playedCards; }

size_t PlayerBoard::getPlayedCardsCount() const { return playedCards.size(); }

size_t PlayerBoard::getRoundsWon() const { return roundsWon; }

bool PlayerBoard::isStanding() const { return standing; }

string PlayerBoard::showCardsPlayed() const {
    string output;
    auto playedEnd = *(playedCards.end());
    for (auto &cardValue : playedCards) //places a PLAYED_CARDS_DELIMITER between each substring of the output string
        output.append(to_string(cardValue) + (cardValue != playedEnd ? PlayerBoard::PLAYED_CARDS_DELIMITER : ""));

    return output;
}

void PlayerBoard::addPlayedCard(int cardValue) {
    //No added value, card was either a double or a flip, which isn't recorded as played
    if (cardValue == 0) //A card whose value can't be added
        return;
    playedCards.push_back(cardValue);
    recalculateScore();
}

void PlayerBoard::addPoint() { ++roundsWon; }

void PlayerBoard::stand() { standing = true; }

void PlayerBoard::reset() {
    currentScore = 0;
    resetPlayedCards();
    standing = false;
}

void PlayerBoard::resetPlayedCards() {
    playedCards.clear();
    playedCards.reserve(PlayerBoard::TABLE_SIZE);
}

void PlayerBoard::recalculateScore() {
    currentScore = 0;
    for (auto playedCard : playedCards)
        currentScore += playedCard;
}

void PlayerBoard::saveToFile(ofstream &out) const {
    // round score
    out << "Rounds won: " << roundsWon << endl;
    // current score
    out << "Current round score: " << currentScore << endl;
    // played cards
    out << "Cards played: " << showCardsPlayed() << endl;
    // is standing
    out << "Is standing: " << (standing ? "True" : "False") << endl;
    // main deck
    out << "Main deck: " << mainDeck.size() << endl;
    for (size_t i = 0; i < mainDeck.size(); ++i)
        out << "(" << i << ") " << *mainDeck[i] << endl;
}

PlayerBoard PlayerBoard::loadFromFile(std::ifstream &ifstream, const CardDatabase &database) {
    PlayerBoard playerBoard;

    //rounds won
    //current score
    //cards played
    //is standing
    //main deck

    return playerBoard;
}

