//
// Created by tomtom on 09/02/19.
//

#include "Hand.h"

using namespace std;

ostream &operator<<(ostream &out, const Hand &hand) {
    size_t i = 0;
    for (auto card : hand.cards) {
        cout << "(" << i << ") " << *card << endl;
        i++;
    }
}

int Hand::playCard(size_t cardIndex, vector<int> &playedCards, int currentScore, int opponentScore ){
    const int cardValue = this->cards[cardIndex]->play(playedCards, currentScore, opponentScore);

    //Remove the played card
    this->cards.erase(this->cards.begin() + cardIndex);
    return cardValue;
}

void Hand::addCard(Card *card) {
    this->cards.push_back(card);
}
