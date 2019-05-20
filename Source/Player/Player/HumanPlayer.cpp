//
// Created by tomtom on 04/05/19.
//

#include "HumanPlayer.h"
#include "../../Game.h"
#include "../../Utilities/DeckParser.h"
#include "../../Utilities/Exceptions.h"

using namespace std;

const char *HumanPlayer::HUMAN_FILE_LEAD{"Human"};

HumanPlayer::HumanPlayer(const string &name) : Player(name) {}

void HumanPlayer::drawHand() {
    vector<Card *> drawnFromHand = deck.drawCardsFromDeck();

    for (auto &card : drawnFromHand)
        hand.addCard(card);
}

void HumanPlayer::takeTurn(const int opponentScore) {
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

void HumanPlayer::saveNameToFile(std::ofstream &file) const {
    file << NAME_FILE_LEAD << Game::FILE_FIELD_VALUE_DELIMITER << HumanPlayer::HUMAN_FILE_LEAD
         << Player::PLAYER_TYPE_DELIMITER << name << endl;
}

bool HumanPlayer::isStandingUp() const {
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

bool HumanPlayer::playCard(const int opponentScore) {
    string input;
    cin >> input;
    if (input == "P" || input == "PASS" || input == "Y" || input == "YES") {
        isPassingTurnMessage();
        return true;
    }

    try {
        size_t choice = stoull(input);
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

void HumanPlayer::chooseDeck(const CardDatabase &cardDatabase) {
    choosingDeckMessage();

    bool confirmed = false;

    while (!confirmed) {
        deckChoicePrompt();

        string input;
        cin >> input;
        while (cin.fail() || (input != "F" && input != "L")) {
            invalidInputMessage();
            cin >> input;
        }

        deck = (input == "F" ? Deck(cardDatabase) : DeckParser::loadFromFile(cardDatabase));
        Game::clearScreen(cout);
        printDeck();
        deckApprovalPrompt();

        //Ask for approval
        cin >> input;
        while (cin.fail() || (input != "Y" && input != "N" && input != "E")) {
            Game::clearScreen(cout);
            invalidInputMessage();
            deckApprovalPrompt();
            cin >> input;
        }
        confirmed = (input == "Y");
    }
}

void HumanPlayer::saveToFile(ofstream &file) const {
    saveNameToFile(file);
    hand.saveToFile(file);
    deck.saveToFile(file);
    board.saveToFile(file);
}

Player *HumanPlayer::loadFromFile(std::ifstream &file, const CardDatabase &cardDatabase, Player *opponent) {
    HumanPlayer *player = new HumanPlayer("dummy");
    player->hand = Hand::loadFromFile(file, cardDatabase);
    player->deck = Deck::loadFromFile(file, cardDatabase);
    player->board = PlayerBoard::loadFromFile(file, cardDatabase);

    return player;
}

void HumanPlayer::printDeck() const { cout << deck << endl; }

void HumanPlayer::invalidInputMessage() const { cout << "Invalid input, try again." << endl; }

void HumanPlayer::deckApprovalPrompt() const { cout << "Do you want to use this deck? [Y]es/[N]o/[E]xit?" << endl; }

void HumanPlayer::actionPrompt() const {
    cout << endl << "Pick a card to play or [P]ass" << endl;
    cout << hand;
    cout << "(P)ass" << endl;
}

void HumanPlayer::deckChoicePrompt() const {
    cout << "Forge a new deck or Load an existing one([F]orge/[L]oad)?" << endl;
}

void HumanPlayer::choosingDeckMessage() const {
    Game::clearScreen(cout);
    cout << name << "'s turn to pick a deck." << endl;
}
