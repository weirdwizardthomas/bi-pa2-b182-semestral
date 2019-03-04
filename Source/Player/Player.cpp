//
// Created by tomtom on 08/02/19.
//

#include "Player.h"

//Definitions-------------
using namespace std;

Player::Player(string name) : name(name) {}

void Player::takeTurn(const int opponentScore) {
    //TODO query what card to play, give the option to stand or quit the game
    if (this->board.isStanding()) {
        playerIsStandingMessage();
        return;
    }

    boardStatusMessage(opponentScore);
    actionPrompt();

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

        int cardResult = this->hand.playCard(choice, this->board.getPlayedCards(), this->board.getCurrentScore(),
                                             opponentScore);
        //insert the value at the end
        this->board.addPlayedCard(cardResult);

    }
}

const string &Player::getName() const {
    return name;
}

int Player::getCurrentRoundScore() const {
    return this->board.getCurrentScore();
}

void Player::addPoint() {
    this->board.addPoint();
}

bool Player::isStanding() const {
    return this->board.isStanding();
}

size_t Player::getPlayedCardsCount() const {
    return this->board.getPlayedCardsCount();
}

void Player::chooseDeck(const map<string, Card *> &allCards) {
    const string deckQuery = "[F]orge a new deck or [L]oad an existing one?";
    const size_t messageLength = deckQuery.length();

    cout << this->name << "s turn to pick a deck" << endl;

    bool confirmed = false;

    while (!confirmed) {
        for (size_t i = 0; i < messageLength; i++)
            cout << "=";
        cout << endl;
        cout << deckQuery << endl;

        string input;
        cin >> input;
        while (cin.fail() || (input != "F" && input != "L")) { //TODO add more input choices
            invalidInputMessage();
            cin >> input;
        }

        //Construct the deck, assign it and show it
        this->deck = (input == "F" ? Deck(allCards) : Deck::loadFromFile(allCards));
        cout << deck << endl;
        deckApprovalQuery();

        //Ask for approval
        cin >> input;
        while (cin.fail() || (input != "Y" && input != "N" && input != "E")) {
            invalidInputMessage();
            deckApprovalQuery();
            cin >> input;
        }
        confirmed = (input == "Y");
    }
}

//--------------------------------------------------------------------------------------------------------------------//
//Messages------------------------------------------------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------------------------//
void Player::invalidInputMessage() const { cout << "Invalid input, try again." << endl; }

//TODO exit
void Player::deckApprovalQuery() const { cout << "Do you want to use this deck? [Y]es/[N]o/[E]xit?" << endl; }

void Player::boardStatusMessage(const int opponentScore) const {
    cout << "Your turn to play! Your score: " << getCurrentRoundScore();
    cout << " | Your opponent's score: " << opponentScore << endl;
    cout << "Your board: ";
    cout << (this->board.showCardsPlayed().empty() ? "No cards played so far." : this->board.showCardsPlayed());
}

void Player::playerIsStandingMessage() const { cout << getName() << " is standing." << endl; }

void Player::actionPrompt() const {
    //TODO ADD HELP QUERY
    cout << endl << "[P]ick a card to play or [S]tand" << endl;
    cout << this->hand;
    cout << "(S) Stand" << endl;
}

void Player::drawHand() {
    vector<Card *> drawnFromHand = this->deck.drawCardsFromDeck();

    for (auto &card : drawnFromHand)
        this->hand.addCard(card);
}

size_t Player::getRoundsWon() const {
    return this->board.getRoundsWon();
}
