//
// Created by tomtom on 09/02/19.
//

#include <list>
#include "Hand.h"
#include "../Cards/CardDatabase.h"
#include "../Utilities/Exceptions.h"
#include "../Game.h"

//Namespaces--------------------------------
using namespace std;

const char *Hand::HAND_FILE_LEAD{"Hand"};
const char *Hand::RIGHT_INDEX_WRAPPER{") "};
const char *Hand::LEFT_INDEX_WRAPPER{"("};


ostream &operator<<(ostream &out, const Hand &hand) {
    size_t i = 0;
    for (const auto &card : hand.cards)
        out << Hand::LEFT_INDEX_WRAPPER << i++ << Hand::RIGHT_INDEX_WRAPPER << *card << endl;
    return out;
}

void Hand::addCard(Card *card) { cards.push_back(card); }

Hand Hand::loadFromFile(std::ifstream &file, const CardDatabase &cardDatabase) {
    string input;
    getline(file, input);
    list<string> parsed = CardDatabase::split(input, Game::FILE_FIELD_VALUE_DELIMITER);
    if (parsed.front() != Hand::HAND_FILE_LEAD)
        throw ParseError();

    size_t cardCount = stoull(parsed.back());
    Hand hand;
    hand.cards.reserve(cardCount);

    //TODO add try-catch here - check whether all have been read
    for (size_t i = 0; i < cardCount; ++i) {
        getline(file, input);
        parsed = CardDatabase::split(input, Hand::RIGHT_INDEX_WRAPPER);
        hand.cards.push_back(cardDatabase.get(parsed.back()));
    }

    return hand;
}

int Hand::playCard(size_t cardIndex, vector<int> &playedCards, int currentScore, int opponentScore) {
    if (cardIndex >= cards.size())
        throw invalid_argument("Index out of range");
    const int cardValue = cards[cardIndex]->play(playedCards, currentScore, opponentScore);
    cards.erase(cards.begin() + cardIndex);
    return cardValue;
}

void Hand::saveToFile(ofstream &file) const {
    file << Hand::HAND_FILE_LEAD << Game::FILE_FIELD_VALUE_DELIMITER << cards.size() << endl;
    file << *this;
}
