//
// Created by tomtom on 11/02/19.
//

#include "Game.h"

//Namespaces--------------------------
using namespace std;

//TODO rework players to be a pair and change appropriate calls
Game::Game(Player *player1, Player *player2, const map<string, Card *> &allCards) : players({player1, player2}) {

    selectStartingPlayer();
    chooseDecks(allCards);
    gameStartMessage();
}

Game::~Game() {
    delete this->players.first;
    delete this->players.second;
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

    gameVictorMessage();
}

Player *Game::round() {

    players.first->drawHand();
    players.second->drawHand();

    while (!bothPlayersStanding()) {


        this->turn(currentlyPlaying());

        if (currentlyPlaying()->getCurrentRoundScore() > TARGET_SCORE)
            return currentlyNotPlaying();

        if (currentlyPlaying()->getPlayedCardsCount() == TABLE_SIZE &&
            currentlyPlaying()->getCurrentRoundScore() <= TARGET_SCORE)
            return currentlyPlaying();

        this->swapPlayers();
        //TODO change this, make it more elegant

    }

    this->resetBoards();
    return getRoundVictor();
}

void Game::turn(Player *currentPlayer) {
    turnPrompt();
    const int opponentScore = this->players.second->getCurrentRoundScore();
    currentPlayer->takeTurn(opponentScore);
}

//--------------------------------------------------------------------------------------------------------------------//
//Supportive-methods--------------------------------------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------------------------//
bool Game::bothPlayersStanding() const {
    return this->players.first->isStanding() && this->players.second->isStanding();
}

void Game::chooseDecks(const map<string, Card *> &allCards) const {
    players.first->chooseDeck(allCards);
    players.second->chooseDeck(allCards);
}

Player *Game::currentlyNotPlaying() const { return players.second; }

Player *Game::currentlyPlaying() const { return this->players.first; }

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

size_t Game::selectStartingPlayer() {
    if (this->players.first->getOpener() < this->players.first->getOpener())
        this->swapPlayers();
}

void Game::swapPlayers() {
    auto dummy = this->players.first;
    this->players.first = this->players.second;
    this->players.second = dummy;
}

//--------------------------------------------------------------------------------------------------------------------//
//Queries and prompts-------------------------------------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------------------------//
void Game::gameStartMessage() const {
    for (size_t i = 0; i < 2; i++)
        cout << endl;
    cout << "Starting a game of Pazaak between " << players.first->getName() << " and " << players.second->getName()
         << "." << endl;
    cout << players.first->getName() << " goes first." << endl << endl;
}

void Game::gameVictorMessage() const {
    cout << getGameVictor()->getName() << " won the game!" << endl;
}

void Game::roundPrompt(size_t roundNumber) const { cout << "Starting round #" << roundNumber << endl; }

void Game::roundTieMessage() const { cout << "Tie"; }

void Game::roundVictorMessage(const Player *victor) const { cout << victor->getName() << " won the round!" << endl; }

void Game::turnPrompt() const {
    cout << this->players.first->getName() << "'s turn to play." << endl;
}

