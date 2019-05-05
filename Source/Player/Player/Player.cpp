#include <utility>

//
// Created by tomtom on 08/02/19.
//

#include "Player.h"
#include "../../Game.h"
#include "../../Utilities/DeckParser.h"
#include "../../Utilities/Exceptions.h"

//Namespaces--------------------------------
using namespace std;

const char *Player::NAME_FILE_LEAD{"Name"};
const char *Player::NAME_DELIMITER{": "};


Player::Player(string name) : name(std::move(name)) {}

void Player::takeTurn(const int opponentScore) {
    if (board.isStanding()) {
        playerIsStandingMessage();
        return;
    }

    boardStatusMessage(opponentScore);
    standPrompt();

    if (isStandingUp()) {
        board.stand();
        Game::clearScreen(cout);
        return;
    }
    Game::clearScreen(cout);
    board.addPlayedCard(autoPlayCard());
    boardStatusMessage(opponentScore);
    actionPrompt();

    while (!playCard(opponentScore));

}

bool Player::playCard(const int opponentScore) {
    string input;
    cin >> input;
    if (input == "P" || input == "PASS") {
        isPassingTurnMessage();
        return true;
    }

    try {
        size_t choice = stoull(input);
        if (choice > deck.getDeckSize())
            return false;

        int cardResult = hand.playCard(choice, board.getPlayedCards(), board.getCurrentScore(), opponentScore);
        board.addPlayedCard(cardResult); //insert the value at the end
        Game::clearScreen(cout);
        return true;
    }
    catch (invalid_argument &e) {
        Game::clearScreen(cout);
        invalidInputMessage();
        boardStatusMessage(opponentScore);
        actionPrompt();
        return false;
    }

}

bool Player::isStandingUp() const {
    string input;
    bool invalidInput = true;
    while (invalidInput) {
        cin >> input;
        invalidInput = input != "Y" && input != "N" && input != "S";
        if (invalidInput) {
            Game::clearScreen(cout);
            invalidInputMessage();
            standPrompt();
        }
    }
    return input == "Y" || input == "S";
}

void Player::drawHand() {
    vector<Card *> drawnFromHand = deck.drawCardsFromDeck();

    for (auto &card : drawnFromHand)
        hand.addCard(card);
}

int Player::autoPlayCard() { return board.drawCardFromMainDeck(); }

void Player::addPoint() { board.addPoint(); }

void Player::chooseDeck(const CardDatabase &allCards) {
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
        deck = (input == "F" ? Deck(allCards) : DeckParser::loadFromFile(allCards));
        Game::clearScreen(cout);
        printDeck();
        deckApprovalQuery();

        //Ask for approval
        cin >> input;
        while (cin.fail() || (input != "Y" && input != "N" && input != "E")) {
            Game::clearScreen(cout);
            invalidInputMessage();
            deckApprovalQuery();
            cin >> input;
        }
        confirmed = (input == "Y");
    }
}

void Player::printDeck() const { cout << deck << endl; }

void Player::resetBoard() { return board.reset(); }

const string &Player::getName() const { return name; }

int Player::getCurrentRoundScore() const { return board.getCurrentScore(); }

int Player::getOpener() {
    int opener = board.getOpener();
    openerMessage(opener);
    return opener;

}

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
    cout << "=========================================================" << endl;
    cout << "Forge a new deck or Load an existing one([F]orge/[L]oad)?" << endl;
}

void Player::choosingDeckMessage() const {
    Game::clearScreen(cout);
    cout << name << "'s turn to pick a deck." << endl;
}

void Player::isPassingTurnMessage() const { cout << name << " is passing their turn." << endl; }

void Player::standPrompt() const { cout << "Would you like to Stand([S]tand/[Y]es/[N]o)?" << endl; }

void Player::openerMessage(int opener) const { cout << "Player " << name << "'s opener:" << opener << endl; }

void Player::stand() { board.stand(); }

void Player::saveToFile(ofstream &file) const {
    file << Player::NAME_FILE_LEAD << NAME_DELIMITER << name << endl;
    hand.saveToFile(file);
    deck.saveToFile(file);
    board.saveToFile(file);
}

Player *Player::loadFromFile(ifstream &file, const CardDatabase &cardDatabase) {
    //name
    string nameField;
    getline(file, nameField);
    list<string> parsed = CardDatabase::split(nameField, Player::NAME_DELIMITER);
    if (parsed.front() != Player::NAME_FILE_LEAD)
        throw ParseError();
    Player *player = new Player(parsed.back());
    //hand
    player->hand = Hand::loadFromFile(file, cardDatabase);
    //side deck
    player->deck = Deck::loadFromFile(file, cardDatabase);

    //board
    player->board = PlayerBoard::loadFromFile(file, cardDatabase);
    //rounds won


    //current round score
    //cards played
    //is standing
    //main deck
    return player;
}
