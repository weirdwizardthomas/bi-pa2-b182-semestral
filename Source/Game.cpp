//
// Created by tomtom on 11/02/19.
//

#include "Game.h"
#include "Cards/CardDatabase.h"

#include <iostream>
#include <iomanip>

//Namespaces--------------------------
using namespace std;

const string Game::SAVES_FOLDER = "../Data/Games/";
const string Game::CURRENT_SCORE_LEAD = "Current score:";

Game::Game(Player *player1, Player *player2, const CardDatabase &allCards) : players({player1, player2}) {
    chooseDecks(allCards);
    selectStartingPlayer();
}

Game::~Game() {
    delete players.first;
    delete players.second;
}

void Game::play() {
    size_t roundNumber = 1;
    gameStartMessage();


    while (roundNumber <= ROUNDS) {
        autoSave(roundNumber);
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

        if (currentlyPlaying()->getCurrentRoundScore() == Game::TARGET_SCORE)
            currentlyPlaying()->stand();
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

bool Game::bothPlayersStanding() const { return players.first->isStanding() && players.second->isStanding(); }

void Game::chooseDecks(const CardDatabase &allCards) const {
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
    //out << setfill('\n') << setw(rowsCleared) << endl;
    for (size_t i = 0; i < rowsCleared; ++i)
        out << endl;
    out.flags(f);
}

void Game::currentScoreMessage() const {
    cout << "Current score: "
         << players.first->getName() << ":" << players.first->getRoundsWon() << " |"
         << players.second->getName() << ":" << players.second->getRoundsWon() << endl;
}

void Game::gameStartMessage() const {
    Game::clearScreen(cout);
    //TODO more ZAZ around here
    cout << "Starting a game of Pazaak between "
         << players.first->getName() << " and "
         << players.second->getName() << "." << endl;
}

void Game::gameVictorMessage() const { cout << getGameVictor()->getName() << " won the game!" << endl; }

void Game::roundPrompt(size_t roundNumber) const { cout << "Starting round #" << roundNumber << endl; }

void Game::roundTieMessage() const { cout << "Tie" << endl; }

void Game::roundVictorMessage(const Player *victor) const { cout << victor->getName() << " won the round!" << endl; }

void Game::turnPrompt() const { cout << players.first->getName() << "'s turn to play!" << endl; }

void Game::manualSave(size_t roundNumber) const {
    cout << "Enter a file name to save the game ['Q' to quit]: " << endl;
    string filename;
    cin >> filename;
    if (filename == "Q")
        return;
    saveToFile(Game::SAVES_FOLDER + filename, roundNumber);
}


void Game::saveToFile(const string &outputPath, size_t roundNumber) const {
    fstream file;

    file.open(outputPath, fstream::out);
    if (!file.is_open())
        cout << "wtf" << endl; //TODO something here

    file << CURRENT_SCORE_LEAD << roundNumber << endl;
    players.first->saveToFile(file);
    players.second->saveToFile(file);

    file.close();
}

void Game::autoSave(size_t roundNumber) const {
    string output = Game::SAVES_FOLDER + "autosave_";

    if (players.first->getName() < players.second->getName())
        output.append(players.first->getName() + "_" + players.second->getName());
    else
        output.append(players.second->getName() + "_" + players.first->getName());

    saveToFile(output, roundNumber);
}
