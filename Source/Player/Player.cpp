#include <utility>

//
// Created by tomtom on 08/02/19.
//

#include "Player.h"


//Namespaces--------------------------------
using namespace std;

Player::Player(string name) : name(std::move(name)) {}

void Player::takeTurn(const int opponentScore) {
    //TODO query what card to play, give the option to stand or quit the game
    if (board.isStanding()) {
        playerIsStandingMessage();
        return;
    }

    boardStatusMessage(opponentScore);
    standPrompt();
    //TODO Need to treat input
    string input;
    cin >> input;

    if (input != "Y" && input != "N" && input != "S")
        throw "INVALID INPUT"; //TODO proper exception

    if (input == "S") {
        board.stand();
        return;
    }

    board.addPlayedCard(autoPlayCard());
    boardStatusMessage(opponentScore);
    actionPrompt();

    //TODO ADD HELP QUERY
    cin >> input;
    if (input == "P") {
        isPassingTurnMessage();
        return;
    } else { //play a card based on the number
        stringstream extractChoice(input);
        size_t choice=0;
        extractChoice >> choice;
        if (choice > deck.getDeckSize())
            throw "INVALID INPUT OUT OF BOUNDS";

        int cardResult = hand.playCard(choice, board.getPlayedCards(), board.getCurrentScore(), opponentScore);
        //insert the value at the end
        board.addPlayedCard(cardResult);
        return;
    }
}

void Player::drawHand() {
    vector<Card *> drawnFromHand = deck.drawCardsFromDeck();

    for (auto &card : drawnFromHand)
        hand.addCard(card);
}

int Player::autoPlayCard() { return board.drawCardFromMainDeck(); }

//--------------------------------------------------------------------------------------------------------------------//
//Setters-------------------------------------------------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------------------------//
void Player::addPoint() { board.addPoint(); }

void Player::chooseDeck(const map<string, Card *> &allCards) {

    choosingDeckMessage();

    bool confirmed = false;

    while (!confirmed) {
       deckChoicePrompt();

        string input;
        cin >> input;
        while (cin.fail() || (input != "F" && input != "L")) { //TODO add more input choices
            invalidInputMessage();
            cin >> input;
        }

        //Construct the deck, assign it and show it
        deck = (input == "F" ? Deck(allCards) : Deck::loadFromFile(allCards));
        printDeck();
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

void Player::printDeck() const { cout << deck << endl; }

void Player::resetBoard() { return board.reset(); }

//--------------------------------------------------------------------------------------------------------------------//
//Getters-------------------------------------------------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------------------------//
const string &Player::getName() const { return name; }

int Player::getCurrentRoundScore() const { return board.getCurrentScore(); }

int Player::getOpener() const { return board.getOpener(); }

size_t Player::getPlayedCardsCount() const { return board.getPlayedCardsCount(); }

size_t Player::getRoundsWon() const { return board.getRoundsWon(); }

bool Player::isStanding() const { return board.isStanding(); }

//--------------------------------------------------------------------------------------------------------------------//
//Messages------------------------------------------------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------------------------//
void Player::invalidInputMessage() const { cout << "Invalid input, try again." << endl; }

void Player::deckApprovalQuery() const { cout << "Do you want to use this deck? [Y]es/[N]o/[E]xit?" << endl; }

void Player::boardStatusMessage(const int opponentScore) const {
    cout << "Your score: " << getCurrentRoundScore();
    cout << " | Your opponent's score: " << opponentScore << endl;
    cout << "Your board: ";
    cout << (board.showCardsPlayed().empty() ? "No cards played so far." : board.showCardsPlayed()) << endl;
}

void Player::playerIsStandingMessage() const { cout << getName() << " is standing." << endl; }

void Player::actionPrompt() const {
    cout << endl << "Pick a card to play or [P]ass" << endl;
    cout << hand;
    cout << "(P)ass" << endl;
}

void Player::deckChoicePrompt() const {
    cout << "==============================" << endl;
    cout << "[F]orge a new deck or [L]oad an existing one?" << endl;
}

void Player::choosingDeckMessage() const { cout << name << "'s turn to pick a deck" << endl; }

void Player::isPassingTurnMessage() const { cout << name << " is passing their turn." << endl; }

void Player::standPrompt() const { cout << "Would you like to [S]tand?" << endl; }
