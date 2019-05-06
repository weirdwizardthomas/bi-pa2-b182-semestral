//
// Created by tomtom on 08/02/19.
//

#include <sstream>
#include "PlayerBoard.h"
#include "../Utilities/Exceptions.h"

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
            mainDeck.emplace_back(i);
}


int PlayerBoard::drawCardFromMainDeck() {
    size_t index = randomNumberGenerator();
    int value = mainDeck[index].play();
    mainDeck.erase(mainDeck.begin() + index);
    randomNumberGenerator.lowerCeiling(mainDeck.size());
    return value;
}

int PlayerBoard::getCurrentScore() const { return currentScore; }

int PlayerBoard::getOpener() { return mainDeck[randomNumberGenerator()].play(); }

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
        out << "(" << i << ") " << mainDeck[i] << endl;
}

PlayerBoard PlayerBoard::loadFromFile(ifstream &file, const CardDatabase &database) {
    PlayerBoard playerBoard;

    playerBoard.roundsWon = loadRoundsWon(file);
    playerBoard.currentScore = loadCurrentScore(file);
    playerBoard.playedCards = loadPlayedCards(file);
    playerBoard.standing = loadStanding(file);
    playerBoard.mainDeck = loadMainDeck(file);

    return playerBoard;
}

bool PlayerBoard::loadStanding(ifstream &file) {
    string input;
    getline(file, input);
    list<string> parsed = CardDatabase::split(input, ": ");//is standing
    return parsed.back() == "True";
}

size_t PlayerBoard::loadRoundsWon(ifstream &file) {
    string input;
    getline(file, input);
    list<string> parsed = CardDatabase::split(input, ": ");
    if (parsed.front() != "Rounds won")
        throw ParseError();
    return stoull(parsed.back());
}

int PlayerBoard::loadCurrentScore(ifstream &file) {
    string input;
    getline(file, input);
    list<string> parsed = CardDatabase::split(input, ": ");
    if (parsed.front() != "Current round score")
        throw ParseError();
    return stoi(parsed.back());
}

vector<int> PlayerBoard::loadPlayedCards(ifstream &file) {
    string input;
    getline(file, input);
    list<string> parsed = CardDatabase::split(input, ": ");
    //get the cards played
    stringstream playedCards;
    playedCards.str(parsed.back());

    int loadedCard = 0;
    vector<int> cards;
    while (playedCards >> loadedCard)
        cards.push_back(loadedCard);

    return cards;
}

vector<BasicCard> PlayerBoard::loadMainDeck(ifstream &file) {
    string input;
    getline(file, input);
    list<string> parsed = CardDatabase::split(input, ": ");
    if (parsed.front() != "Main deck")
        throw ParseError();
    size_t cardCount = stoull(parsed.back());

    vector<BasicCard> cards;
    for (size_t i = 0; i < cardCount; ++i) {
        getline(file, input);
        parsed = CardDatabase::split(input, ") ");
        cards.emplace_back(stoi(parsed.back()));
    }
    return cards;
}

