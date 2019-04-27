//
// Created by tomtom on 11/02/19.
//

#include "Game.h"

//Namespaces--------------------------
using namespace std;

//TODO rework players to be a pair and change appropriate calls
Game::Game(Player *player1, Player *player2, const map<string, Card *> &allCards) {
    this->players[0] = player1;
    this->players[1] = player2;
    this->currentlyPlaying = selectStartingPlayer();

    for (Player *player : this->players)
        player->chooseDeck(allCards);

    gameStartMessage();
}

Game::~Game() {
    delete this->players[0];
    delete this->players[1];
}

//--------------------------------------------------------------------------------------------------------------------//
//Gameplay------------------------------------------------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------------------------//
void Game::play() {
    size_t roundNumber = 1;

    while (roundNumber <= ROUNDS) {
        roundPrompt(roundNumber);
        Player *roundVictor = round();
        if (roundVictor == nullptr) //tie
            roundTieMessage();
        else {
            roundVictor->addPoint();
            roundNumber++;
            roundVictorMessage(roundVictor);
        }
    }

    gameWinnerMessage();
}

void Game::gameWinnerMessage() const {
    cout << players[(players[0]->getRoundsWon() > players[1]->getRoundsWon() ? 0 : 1)]->getName()
         << " won the game!" << endl;
}

Player *Game::round() {

    for (auto &player : players)
        player->drawHand();

    while (!bothPlayersStanding()) {
        Player *currentPlayer = this->players[currentlyPlaying];

        this->turn(currentPlayer);

        if (currentPlayer->getCurrentRoundScore() > TARGET_SCORE)
            return currentlyNotPlaying();

        if (currentPlayer->getPlayedCardsCount() == TABLE_SIZE && currentPlayer->getCurrentRoundScore() <= TARGET_SCORE)
            return currentPlayer;

        this->swapPlayers();
        //TODO change this, make it more elegant

    }

    this->resetBoards();
    return getVictor();
}

void Game::turn(Player *currentPlayer) {
    turnPrompt();
    const int opponentScore = this->players[otherPlayerIndex()]->getCurrentRoundScore();
    currentPlayer->takeTurn(opponentScore);
}

//--------------------------------------------------------------------------------------------------------------------//
//Supportive-methods--------------------------------------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------------------------//
bool Game::bothPlayersStanding() const {
    return this->players[0]->isStanding() && this->players[1]->isStanding();
}

Player *Game::currentlyNotPlaying() const {
    return players[otherPlayerIndex()];
}

Player *Game::getVictor() const {
    if (roundIsTie())
        return nullptr;
    return players[(players[0]->getCurrentRoundScore() > players[1]->getCurrentRoundScore() ? 0 : 1)];
}

size_t Game::otherPlayerIndex() const { return (size_t) (currentlyPlaying != 1); }

size_t Game::selectStartingPlayer() {
    return (size_t) (this->players[0]->getOpener() < this->players[1]->getOpener());
}

void Game::swapPlayers() {
    this->currentlyPlaying = otherPlayerIndex();
}

void Game::resetBoards() {
    for (auto &player : players)
        player->resetBoard();
}

//--------------------------------------------------------------------------------------------------------------------//
//Queries and prompts-------------------------------------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------------------------//
void Game::gameStartMessage() const {
    for (size_t i = 0; i < 2; i++)
        cout << endl;
    cout << "Starting a game of Pazaak between " << players[0]->getName() << " and " << players[1]->getName()
         << "." << endl;
    cout << players[currentlyPlaying]->getName() << " goes first." << endl << endl;
}

void Game::roundTieMessage() const { cout << "Tie"; }

void Game::roundVictorMessage(const Player *victor) const { cout << victor->getName() << " won the round!" << endl; }

bool Game::roundIsTie() const { return players[0]->getCurrentRoundScore() == players[1]->getCurrentRoundScore(); }

void Game::roundPrompt(size_t roundNumber) const { cout << "Starting round #" << roundNumber << endl; }

void Game::turnPrompt() const {
    cout << this->players[currentlyPlaying]->getName() << "'s turn to play." << endl;
}
