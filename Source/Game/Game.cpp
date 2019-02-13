//
// Created by tomtom on 11/02/19.
//

#include "Game.h"

Game::Game(Player *a, Player *b) {
    this->players[0] = *a;
    this->players[1] = *b;
    this->currentlyPlaying = selectStartingPlayer();

    this->players[0].createDeck();

    gameStartMessage();
}

size_t Game::selectStartingPlayer() {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(0, 2);
    return (size_t) dist(mt);
}

void Game::swapPlayers() {
    this->currentlyPlaying = otherPlayerIndex();
}

Player *Game::currentlyNotPlaying() {
    return &(players[(currentlyPlaying == 0 ? 1 : 0)]);
}

size_t Game::otherPlayerIndex() const { return (size_t) !(currentlyPlaying); }

void Game::play() {

    int roundNumber = 1;
    Player *victor = nullptr;

    while (roundNumber <= BASE_ROUND_COUNT) {
        roundPrompt(roundNumber);
        victor = round();
        if (victor == nullptr) //tie
            roundTieMessage();
        else {
            victor->addPoint();
            roundNumber++;
            roundVictorMessage(victor);
        }
    }

    cout << victor->getName() << " won the game!" << endl;

}

Player *Game::round() {

    Player *currentPlayer = &(this->players[currentlyPlaying]);

    while (!bothPlayersStan ding()) {
        this->turn();

        if (currentPlayer->getScore() > TARGET)
            return currentlyNotPlaying();

        if (currentPlayer->playedCardsCount() == TABLE_SIZE && currentPlayer->getScore() <= 20)
            return currentPlayer;

        swapPlayers();
    }

    if (roundIsTie())
        return nullptr;

    return getVictor();
}

Player *Game::getVictor() { return &(players[(players[0].getScore() > players[1].getScore() ? 0 : 1)]); }

void Game::turn() {
    turnPrompt();
    this->players[currentlyPlaying].play(0);
}

//Queries and prompts---------------------------------
void Game::gameStartMessage() const {
    cout << endl << endl;
    cout << "Starting a game of Pazaak between " << players[0].getName() << " and " << players[1].getName()
         << "." << endl;
    cout << players[currentlyPlaying].getName() << " goes first." << endl;
}

void Game::roundTieMessage() const { cout << "Tie"; }

void Game::roundVictorMessage(const Player *victor) const { cout << victor->getName() << " won the round!" << endl; }

bool Game::roundIsTie() const { return players[0].getScore() == players[1].getScore(); }

void Game::roundPrompt(int roundNumber) const { cout << "Starting round number " << roundNumber << endl; }

void Game::turnPrompt() const {
    cout << "Player " + this->players[currentlyPlaying].getName() + "'s turn to play." << endl;
}

bool Game::bothPlayersStanding() {
    return this->players[0].isStanding() && this->players[0].isStanding();
}

