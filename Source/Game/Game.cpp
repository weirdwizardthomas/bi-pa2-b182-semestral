//
// Created by tomtom on 11/02/19.
//

#include "Game.h"

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
         << " won the game!"
         << endl;
}

Player *Game::round() {

    Player *currentPlayer = this->players[currentlyPlaying];

    while (!bothPlayersStanding()) {
        this->turn();

        if (currentPlayer->getCurrentRoundScore() > TARGET_SCORE)
            return currentlyNotPlaying();

        if (currentPlayer->getPlayedCardsCount() == TABLE_SIZE && currentPlayer->getCurrentRoundScore() <= TARGET_SCORE)
            return currentPlayer;

        swapPlayers();
    }

    return getVictor();
}

void Game::turn() {
    turnPrompt();
    const int opponentScore = this->players[otherPlayerIndex()]->getCurrentRoundScore();
    this->players[currentlyPlaying]->takeTurn(opponentScore);
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

size_t Game::otherPlayerIndex() const { return (size_t) !(currentlyPlaying); }

size_t Game::selectStartingPlayer() {
    return (size_t) (this->players[0]->getOpener() < this->players[1]->getOpener());
}

void Game::swapPlayers() {
    this->currentlyPlaying = otherPlayerIndex();
}

//--------------------------------------------------------------------------------------------------------------------//
//Queries and prompts-------------------------------------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------------------------//
void Game::gameStartMessage() const {
    for (size_t i = 0; i < 2; i++)
        cout << endl;
    cout << "Starting a game of Pazaak between " << players[0]->getName() << " and " << players[1]->getName()
         << "." << endl;
    cout << players[currentlyPlaying]->getName() << " goes first." << endl;
}

void Game::roundTieMessage() const { cout << "Tie"; }

void Game::roundVictorMessage(const Player *victor) const { cout << victor->getName() << " won the round!" << endl; }

bool Game::roundIsTie() const { return players[0]->getCurrentRoundScore() == players[1]->getCurrentRoundScore(); }

void Game::roundPrompt(size_t roundNumber) const { cout << "Starting round number " << roundNumber << endl; }

void Game::turnPrompt() const {
    cout << "Player " + this->players[currentlyPlaying]->getName() + "'s turn to play." << endl;
}