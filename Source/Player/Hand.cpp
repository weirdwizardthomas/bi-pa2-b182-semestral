//
// Created by tomtom on 09/02/19.
//

#include "Hand.h"

//Namespaces--------------------------------
using namespace std;

const string Hand::HAND_FILE_LEAD = "Hand:";


ostream &operator<<(ostream &out, const Hand &hand) {
    size_t i = 0;
    for (auto &card : hand.cards)
        out << "(" << i++ << ") " << *card << endl;
    return out;
}

int Hand::playCard(size_t cardIndex, vector<int> &playedCards, int currentScore, int opponentScore) {
    const int cardValue = cards[cardIndex]->play(playedCards, currentScore, opponentScore);
    cards.erase(cards.begin() + cardIndex);
    return cardValue;
}

void Hand::addCard(Card *card) { cards.push_back(card); }

void Hand::saveToFile(std::fstream &file) const {
    file << HAND_FILE_LEAD << endl;
    file << *this;
}
