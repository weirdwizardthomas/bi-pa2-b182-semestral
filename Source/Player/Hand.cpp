//
// Created by tomtom on 09/02/19.
//

#include <list>
#include "Hand.h"
#include "../Cards/CardDatabase.h"
#include "../Utilities/Exceptions.h"

//Namespaces--------------------------------
using namespace std;

const char *Hand::HAND_FILE_LEAD{"Hand"};
const char *Hand::FILE_VALUE_DELIMITER{": "};


ostream &operator<<(ostream &out, const Hand &hand) {
    size_t i = 0;
    for (const auto &card : hand.cards)
        out << "(" << i++ << ") " << *card << endl;
    return out;
}

int Hand::playCard(size_t cardIndex, vector<int> &playedCards, int currentScore, int opponentScore) {
    if (cardIndex >= cards.size())
        throw invalid_argument("");
    const int cardValue = cards[cardIndex]->play(playedCards, currentScore, opponentScore);
    cards.erase(cards.begin() + cardIndex);
    return cardValue;
}

void Hand::addCard(Card *card) { cards.push_back(card); }

void Hand::saveToFile(ofstream &file) const {
    file << HAND_FILE_LEAD << ": " << cards.size() << endl;
    file << *this;
}

Hand Hand::loadFromFile(std::ifstream &file, const CardDatabase &cardDatabase) {
    string input;
    getline(file, input);
    list<string> parsed = CardDatabase::split(input, FILE_VALUE_DELIMITER);
    if (parsed.front() != HAND_FILE_LEAD)
        throw ParseError();

    size_t cardCount = stoull(parsed.back());

    Hand hand;
    hand.cards.reserve(cardCount);

    //TODO add try-catch here - check whether all have been read
    //TODO this will repeat with each loaded card container
    for (size_t i = 0; i < cardCount; ++i) {
        getline(file, input);
        parsed = CardDatabase::split(input, ") ");
        hand.cards.push_back(cardDatabase.get(parsed.back()));
    }

    return hand;
}
