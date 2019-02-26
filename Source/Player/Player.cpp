//
// Created by tomtom on 08/02/19.
//

#include "Player.h"

//Definitions-------------
using namespace std;

Player::Player(string name) : name(name) {
    cout << "Welcome player " << name << endl;
}

void Player::play(int opponentScore) {
    //TODO query what card to play, give the option to stand or quit the game
    if (this->board.isStanding()) {
        cout << "Player " << this->name << " is standing." << endl;
        return;
    }

    cout << "Your turn to play! Your score: " << this->getScore();
    cout << " | Your opponent's score: " << opponentScore << endl;
    cout << "Your board: ";

    for (int cardValue : this->board.getPlayedCards())
        cout << cardValue << " ";

    //TODO ADD HELP QUERY

    cout << "[P]ick a card to play or [S]tand" << endl;
    cout << this->deck;
    cout << "(S) Stand";

    //TODO Need to treat input
    string input;
    cin >> input;
    if (input == "S") {
        this->board.stand();
    } else { //play a card based on the number
        stringstream extractChoice(input);
        size_t choice;
        extractChoice >> choice;
        if (choice > this->deck.getDeckSize())
            throw "INVALID INPUT OUT OF BOUNDS";
        // this->deck.playCard(choice,this->board.getPlayedCards(),this->board.getCurrentScore(), opponentScore);
    }
}

int Player::getScore() const {
    return this->board.getCurrentScore();
}

void Player::addPoint() {
    this->board.addPoint();
}

void Player::createDeck(const map<string, Card *> &allCards) {
    this->deck = Deck(allCards);
    cout << this->deck;
}

void Player::chooseDeck(const map<string, Card *> &allCards) {

    cout << this->name << ": [F]orge a new deck or [L]oad an existing one?" << endl;

    string input;
    cin >> input;
    while (cin.fail() || (input != "F" && input != "L")) { //TODO add more input choices
        cout << "Invalid input, try again." << endl;
        cin >> input;
    }

    if (input == "F")
        this->createDeck(allCards);
    else
        this->loadDeck(allCards);

}

void Player::loadDeck(const map<string, Card *> &allCards) {
    this->deck = Deck::loadFromFile(allCards);
}

const Deck &Player::getDeck() const {
    return this->deck;
}

size_t Player::getPlayedCardsCount() const {
    return this->board.getPlayedCards().size();
}

const string &Player::getName() const {
    return name;
}

bool Player::isStanding() const {
    return this->board.isStanding();
}