//
// Created by tomtom on 08/02/19.
//

#include "Deck.h"


Hand *Deck::drawCards(Hand *currentHand) {

    for (int i = 0; i < 4; i++) {
        if (this->cards.empty()) //no more cards to be drawn
            break;

        int index = static_cast<int>(rand() % this->cards.size());

        currentHand->addCard(this->cards[index]);
        this->cards.erase(this.cards.begin() + index);
    }

    return currentHand;
}
