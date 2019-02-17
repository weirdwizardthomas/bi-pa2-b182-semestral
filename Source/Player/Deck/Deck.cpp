//
// Created by tomtom on 08/02/19.
//

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

//TODO is this actually random?
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

Deck::Deck(map<string, Card *> &allCards) {
    size_t i = 0;
    //TODO Have pages and a fixed amount per page?
    for (auto &card : allCards)
        cout << (i < 10 ? " " : "") << "(" << i++ << ")" << " " << (card.second)->getDescription() << endl;

    //TODO exit query here
    cout << "Select ten cards to add to your deck." << endl;


    getCardChoicesFromUser(allCards);
    cout << "Deck successfully forged." << endl;
}


vector<Card *> copyMapToVector(const map<string, Card *> &allCards) {
    vector<Card *> allCardsVector;
    allCardsVector.reserve(allCards.size());

    for (const auto &allCard : allCards)
        allCardsVector.push_back(allCard.second);

    return allCardsVector;
}

//TODO allow replacing cards during the selection using cin.fail && cin.clear and cin >> string/char
void Deck::getCardChoicesFromUser(const map<string, Card *> &allCards) {

    vector<Card *> allCardsVector = copyMapToVector(allCards);

    size_t i = 1;

    while (i != 10) {
        cout << "(" << i << "):";

        size_t input;
        cin >> input;

        if (!cin.fail()) {
            if (input < allCards.size()) {
                this->addCard(allCardsVector[input]);
                cout << "You've selected: " << *(this->cards[i - 1]) << endl;
                i++;

            } else {
                cout << "Invalid choice, please try again." << endl; //out of bounds
            }

        } else {
            cout << "Invalid input, please try again." << endl; //NaN
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),
                       NEWLINE); //ignores the entire cin until a newline is encountered
        }


    }
}