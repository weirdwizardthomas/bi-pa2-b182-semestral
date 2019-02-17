//
// Created by tomtom on 08/02/19.
//

#include <sstream>

#include "Player.h"


Player::Player(string name) : name(name) {}

void Player::play(int opponentScore) {
    //TODO query what card to play, give the option to stand or quit the game
    if (this->board.isStanding())
        return;

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

const string &Player::getName() const {
    return name;
}

int Player::getScore() const {
    return this->board.getCurrentScore();
}

void Player::addPoint() {
    this->board.addPoint();
}

void Player::createDeck(map<string, Card *> &allCards) {
    this->deck = Deck(allCards);
    cout << this->deck;
}

bool Player::isStanding() {
    return this->board.isStanding();
}

size_t Player::getPlayedCardsCount() {
    return this->board.getPlayedCards().size();
}

void Player::chooseDeck(map<string, Card *> &allCards) {

    cout << "[F]orge a new deck or [L]oad an existing one?" << endl;

    string input;
    cin >> input;
    while (cin.fail() || (input != "F" && input != "L")) { //TODO add more input choices
        cout << "Invalid input, try again." << endl;
        cin >> input;
    }

    if(input == "F")
        this->createDeck(allCards);
    else
        this->loadDeck();

}

void Player::loadDeck() {

}
