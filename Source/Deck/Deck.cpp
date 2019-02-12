//
// Created by tomtom on 08/02/19.
//

#include <algorithm>
#include "Deck.h"

Deck::Deck(const vector<Card *> &cards) : cards(cards) {}

Hand *Deck::drawCards(Hand *currentHand) {

    for (size_t i = 0; i < 4; i++) {
        if (this->cards.empty()) //no more cards to be drawn
            break;

        size_t cardIndex = generateBoundIndex();

        currentHand->addCard(this->cards[cardIndex]);
        this->cards.erase(this->cards.begin() + cardIndex);
    }

    return currentHand;
}

//copied from https://stackoverflow.com/a/19666713
size_t Deck::generateBoundIndex() const {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(0, this->cards.size());
    return (size_t) dist(mt);
}

void Deck::shuffle() {
    auto rng = default_random_engine{};
    std::shuffle(std::begin(this->cards), std::end(this->cards), rng);
}

//TODO probably throw an exception
int Deck::playCard(size_t cardIndex, vector<int> &playedCards, int currentScore, int opponentScore) {
    int effect = this->cards[cardIndex]->play(playedCards, currentScore, opponentScore);

    this->cards.erase(this->cards.begin() + cardIndex);

    return effect;
}

ostream &operator<<(ostream &out, const Deck &deck) {
    int i = 0;

    for (Card *card : deck.cards) {
        cout << "(" << i << ") " << *card << endl;
        i++;
    }

    return out;
}

size_t Deck::getDeckSize() const {
    return this->cards.size();
}

void Deck::addCard(Card *card) {
    this->cards.push_back(card);
}


