//
// Created by tomtom on 11/02/19.
//

#include "Game.h"

#include <iostream>
#include <iomanip>

//Namespaces--------------------------
using namespace std;

//TODO rework players to be a pair and change appropriate calls
Game::Game(Player *player1, Player *player2, const map<string, Card *> &allCards) : players({player1, player2}) {
    chooseDecks(allCards);
    selectStartingPlayer();
    gameStartMessage();
}

Game::~Game() {
    delete players.first;
    delete players.second;
}

//--------------------------------------------------------------------------------------------------------------------//
//Gameplay------------------------------------------------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------------------------//
void Game::play() {
    size_t roundNumber = 1;

    while (roundNumber <= ROUNDS) {
        currentScoreMessage();
        roundPrompt(roundNumber);
        Player *roundVictor = round();
        if (roundVictor == nullptr) {
            Game::clearScreen(cout);
            roundTieMessage();
        } else {
            roundVictor->addPoint();
            ++roundNumber;
            Game::clearScreen(cout);
            roundVictorMessage(roundVictor);
        }
    }

    Game::clearScreen(cout);
    gameVictorMessage();
}

Player *Game::round() {
    resetBoards();
    drawHands();

    while (!bothPlayersStanding()) {
        turn(currentlyPlaying());

        //Player broke the threshold
        if (currentlyPlaying()->getCurrentRoundScore() > Game::TARGET_SCORE)
            return currentlyNotPlaying();

        //Player managed to fill the board without breaking the threshold
        if (currentlyPlaying()->getPlayedCardsCount() == PlayerBoard::TABLE_SIZE &&
            currentlyPlaying()->getCurrentRoundScore() <= Game::TARGET_SCORE)
            return currentlyPlaying();

        swapPlayers();
    }


    return getRoundVictor();
}

void Game::drawHands() const {
    players.first->drawHand();
    players.second->drawHand();
}

void Game::turn(Player *currentPlayer) {
    turnPrompt();
    const int opponentScore = players.second->getCurrentRoundScore();
    currentPlayer->takeTurn(opponentScore);
}

//--------------------------------------------------------------------------------------------------------------------//
//Supportive-methods--------------------------------------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------------------------//
bool Game::bothPlayersStanding() const {
    return players.first->isStanding() && players.second->isStanding();
}

void Game::chooseDecks(const map<string, Card *> &allCards) const {
    players.first->chooseDeck(allCards);
    players.second->chooseDeck(allCards);
}

Player *Game::currentlyNotPlaying() const { return players.second; }

Player *Game::currentlyPlaying() const { return players.first; }

Player *Game::getGameVictor() const {
    return players.first->getRoundsWon() > players.second->getRoundsWon() ? players.first : players.second;
}

Player *Game::getRoundVictor() const {
    if (roundIsTie())
        return nullptr;

    return players.first->getCurrentRoundScore() > players.second->getCurrentRoundScore() ? players.first
                                                                                          : players.second;
}

void Game::resetBoards() {
    players.first->resetBoard();
    players.second->resetBoard();
}

bool Game::roundIsTie() const {
    return players.first->getCurrentRoundScore() == players.second->getCurrentRoundScore();
}

void Game::selectStartingPlayer() {
    if (players.first->getOpener() < players.second->getOpener())
        swapPlayers();
}

void Game::swapPlayers() { swap(players.first, players.second); }

//--------------------------------------------------------------------------------------------------------------------//
//Queries and prompts-------------------------------------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------------------------//
const int rowsCleared = 18;

void Game::clearScreen(ostream &out) {
    ios_base::fmtflags f(out.flags());
    out << setfill('\n') << setw(rowsCleared) << endl;
    out.flags(f);
}

void Game::currentScoreMessage() const {
    cout << "Current score: " << endl;
    cout << players.first->getName() << ":" << players.first->getCurrentRoundScore() << endl;
    cout << players.second->getName() << ":" << players.second->getCurrentRoundScore() << endl;
}

void Game::gameStartMessage() const {
    Game::clearScreen(cout);
    //TODO more ZAZ around here
    cout << "Starting a game of Pazaak between " << players.first->getName() << " and " << players.second->getName()
         << "." << endl;
    cout << players.first->getName() << " goes first." << endl;
}

void Game::gameVictorMessage() const { cout << getGameVictor()->getName() << " won the game!" << endl; }

void Game::roundPrompt(size_t roundNumber) const { cout << "Starting round #" << roundNumber << endl; }

void Game::roundTieMessage() const { cout << "Tie" << endl; }

void Game::roundVictorMessage(const Player *victor) const { cout << victor->getName() << " won the round!" << endl; }

void Game::turnPrompt() const { cout << players.first->getName() << "'s turn to play." << endl; }
