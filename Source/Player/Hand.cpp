//
// Created by tomtom on 09/02/19.
//

#include "Hand.h"

//Namespaces--------------------------------
using namespace std;

ostream &operator<<(ostream &out, const Hand &hand) {
    size_t i = 0;
    for (auto &card : hand.cards)
        cout << "(" << i++ << ") " << *card << endl;
    return out;
}

int Hand::playCard(size_t cardIndex, vector<int> &playedCards, int currentScore, int opponentScore) {
    const int cardValue = cards[cardIndex]->play(playedCards, currentScore, opponentScore);
    cards.erase(cards.begin() + cardIndex);
    return cardValue;
}

void Hand::addCard(Card *card) { cards.push_back(card); }
