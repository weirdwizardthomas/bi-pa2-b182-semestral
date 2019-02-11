//
// Created by tomtom on 11/02/19.
//

#include "Game.h"


Game::Game(Player *a, Player *b) {
    this->players[0] = *a;
    this->players[1] = *b;
    this->currentlyPlaying = selectStartingPlayer();

    cout << endl << endl;
    cout << "Starting a game of Pazaak between " << this->players[0].getName() << " and " << this->players[1].getName()
         << "." << endl;
    cout << this->players[currentlyPlaying].getName() << " goes first." << endl;
}

size_t Game::selectStartingPlayer() {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(0, 2);
    return (size_t) dist(mt);
}


void Game::turn() {
    turnPrompt();
    this->players[currentlyPlaying].play(0);
    swapPlayers();
}

void Game::swapPlayers() {
   this->currentlyPlaying = !(this->currentlyPlaying);
}

void Game::turnPrompt() const {
    cout << "Player " + this->players[currentlyPlaying].getName() + "'s turn to play." << endl;
}

void Game::play() {

    int roundNumber = 1;
    Player *victor = nullptr;

    while (roundNumber <= BASE_ROUND_COUNT) {
        roundPrompt(roundNumber);
        victor = round();
        if (roundIsTie()) //tie
            roundTieMessage();
        else {
            victor->addPoint();
            roundNumber++;
            roundVictorMessage(victor);
        }
    }

    cout << victor->getName() << " won the game!" << endl;

}

void Game::roundTieMessage() const { cout << "Tie"; }

void Game::roundVictorMessage(const Player *victor) const { cout << victor->getName() << " won the round!" << endl; }

bool Game::roundIsTie() const { return players[0].getScore() == players[1].getScore(); }

void Game::roundPrompt(int roundNumber) const { cout << "Starting round number " << roundNumber << endl; }

Player *Game::round() {

    while (1) {
        this->turn();

    }
}
