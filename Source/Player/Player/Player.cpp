#include <utility>

//
// Created by tomtom on 08/02/19.
//

#include "Player.h"
#include "../../Game.h"
#include "../../Utilities/DeckParser.h"
#include "../../Utilities/Exceptions.h"
#include "HumanPlayer.h"
#include "ComputerPlayer.h"

using namespace std;

const char *Player::NAME_FILE_LEAD{"Name"};
const char *Player::PLAYER_TYPE_DELIMITER{" - "};

Player::Player(string name) : name(std::move(name)) {}

int Player::autoPlayCard() { return board.drawCardFromMainDeck(); }

void Player::addPoint() { board.addPoint(); }

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

Player *Player::loadFromFile(std::ifstream &file, const CardDatabase &cardDatabase, Player *opponent) {
    string nameField;
    getline(file, nameField);
    list<string> parsed = CardDatabase::split(nameField, Game::FILE_FIELD_VALUE_DELIMITER);
    if (parsed.front() != Player::NAME_FILE_LEAD)
        throw ParseError();

    parsed = CardDatabase::split(parsed.back(), PLAYER_TYPE_DELIMITER);
    Player *player;

    if (parsed.front() == HumanPlayer::HUMAN_FILE_LEAD)
        player = HumanPlayer::loadFromFile(file, cardDatabase);
    else
        player = ComputerPlayer::loadFromFile(file, cardDatabase, opponent);

    player->name = parsed.back();
    return player;
}

void Player::resetBoard() { return board.reset(); }

void Player::stand() { board.stand(); }


//--------------------------------------------------------------------------------------------------------------------//
//Messages------------------------------------------------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------------------------//

void Player::boardStatusMessage(const int opponentScore) const {
    cout << "Your score: " << getCurrentRoundScore();
    cout << " | Your opponent's score: " << opponentScore << endl;
    cout << "Your board: ";
    cout << (board.showCardsPlayed().empty() ? "No cards played so far." : board.showCardsPlayed()) << endl;
}

void Player::playerIsStandingMessage() const { cout << getName() << " is standing." << endl; }

void Player::isPassingTurnMessage() const { cout << name << " is passing their turn." << endl; }

void Player::standPrompt() const { cout << "Would you like to Stand([S]tand/[Y]es/[N]o)?" << endl; }

void Player::openerMessage(int opener) const { cout << "Player " << name << "'s opener:" << opener << endl; }