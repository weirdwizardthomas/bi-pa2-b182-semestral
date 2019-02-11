//
// Created by tomtom on 11/02/19.
//

#include "Game.h"


Game::Game(Player &a, Player &b) {
    this->players[0] = a;
    this->players[1] = b;
    this->playerOnTurn = selectStartingPlayer();
}

Player *Game::selectStartingPlayer()  {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(0, 1);
    return &(this->players[(size_t) dist(mt)]);
}


void Game::turn() {
    turnPrompt();
    this->playerOnTurn->play();
    swapPlayers();
}

void Game::swapPlayers() {
    this->playerOnTurn = &(this->playerOnTurn == &(this->players[0]) ?
                           (this->players[1]) : (this->players[0]));
}

void Game::turnPrompt() const {
    cout << "Player " + this->playerOnTurn->getName() + "'s turn to play." << endl;
}
