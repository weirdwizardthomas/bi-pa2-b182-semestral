//
// Created by tomtom on 08/02/19.
//

#include <sstream>
#include "PlayerBoard.h"
#include "../Utilities/Exceptions.h"

using namespace std;

const char *PlayerBoard::ROUNDS_WON_LEAD{"Rounds won"};

const char *PlayerBoard::CURRENT_SCORE_LEAD{"Current round score"};

const char *PlayerBoard::FIELD_DELIMITER{":"};

const char *PlayerBoard::ITEM_LIST_DELIMITER{")"};

const char *PlayerBoard::MAIN_DECK_LEAD{"Main deck"};

const char *PlayerBoard::CARDS_PLAYED_LEAD{"Cards played"};

const char *PlayerBoard::IS_STANDING_LEAD{"Is standing"};

const char *PlayerBoard::PLAYED_CARDS_DELIMITER{" "};


PlayerBoard::PlayerBoard() : currentScore(0), roundsWon(0), standing(false),
                             randomNumberGenerator(0, Card::UPPER_BOUND * PlayerBoard::MAIN_DECK_CARD_COPIES) {
    playedCards.reserve(PlayerBoard::TABLE_SIZE);
    mainDeck.reserve(Card::UPPER_BOUND * PlayerBoard::MAIN_DECK_CARD_COPIES);
    generateMainDeck();
}

void PlayerBoard::generateMainDeck() {
    for (size_t cardValue = 1; cardValue <= Card::UPPER_BOUND; cardValue++)
        for (size_t cardCount = 0; cardCount < PlayerBoard::MAIN_DECK_CARD_COPIES; ++cardCount)
            mainDeck.emplace_back(cardValue);
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
    out << ROUNDS_WON_LEAD << FIELD_DELIMITER << roundsWon << endl;
    out << CURRENT_SCORE_LEAD << FIELD_DELIMITER << currentScore << endl;
    out << CARDS_PLAYED_LEAD << FIELD_DELIMITER << showCardsPlayed() << endl;
    out << IS_STANDING_LEAD << FIELD_DELIMITER << (standing ? "True" : "False") << endl;
    out << MAIN_DECK_LEAD << FIELD_DELIMITER << mainDeck.size() << endl;
    for (size_t i = 0; i < mainDeck.size(); ++i)
        out << "(" << i << ITEM_LIST_DELIMITER << mainDeck[i] << endl;
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
    return loadValue(IS_STANDING_LEAD, file) == "True";
}

size_t PlayerBoard::loadRoundsWon(ifstream &file) {
    return stoull(loadValue(ROUNDS_WON_LEAD, file));
}

//TODO extract higher
string PlayerBoard::loadValue(const string &field, ifstream &file) {
    string input;
    getline(file, input);
    list<string> parsed = CardDatabase::split(input, FIELD_DELIMITER);
    if (parsed.front() != field)
        throw ParseError();

    return parsed.back();
}

int PlayerBoard::loadCurrentScore(ifstream &file) {
    return stoi(loadValue(CURRENT_SCORE_LEAD, file));
}

vector<int> PlayerBoard::loadPlayedCards(ifstream &file) {
    stringstream playedCards;
    playedCards.str(loadValue(CARDS_PLAYED_LEAD, file));
    int loadedCard = 0;
    vector<int> cards;
    while (playedCards >> loadedCard)
        cards.push_back(loadedCard);

    return cards;
}

vector<BasicCard> PlayerBoard::loadMainDeck(ifstream &file) {
    size_t cardCount = stoull(loadValue(MAIN_DECK_LEAD, file));

    vector<BasicCard> cards;
    for (size_t i = 0; i < cardCount; ++i) {
        string input;
        getline(file, input);
        list<string> parsed = CardDatabase::split(input, ITEM_LIST_DELIMITER);
        cards.emplace_back(stoi(parsed.back()));
    }
    return cards;
}

