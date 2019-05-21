//
// Created by tomtom on 11/02/19.
//

#include <iostream>
#include <iomanip>

#include "Game.h"
#include "Cards/CardDatabase.h"
#include "Utilities/Exceptions.h"

using namespace std;

const char *Game::SAVES_FOLDER{"./Data/Games/"};
const char *Game::CURRENT_SCORE_LEAD{"Current score"};
const char *Game::FILE_FIELD_VALUE_DELIMITER{": "};
const char *Game::FILE_NAME_ITEMS_DELIMITER{"_"};
const char *Game::AUTOSAVE_LEADING{"autosave"};
const int Game::ROUNDS = 3;
const int Game::TARGET_SCORE = 20;
const int Game::ROWS_CLEARED = 100;


Game::Game(Player *player1, Player *player2, const CardDatabase &cardDatabase) : players({player1, player2}),
                                                                             roundNumber(1) {
    chooseDecks(cardDatabase);
    selectStartingPlayer();
}

Game::Game() : players(nullptr, nullptr), roundNumber(0) {}

Game::~Game() {
    delete players.first;
    delete players.second;
}

void Game::autoSave() const {
    string output = string(Game::SAVES_FOLDER)
                    + string(Game::AUTOSAVE_LEADING)
                    + string(Game::FILE_NAME_ITEMS_DELIMITER);

    if (players.first->getName() < players.second->getName())
        output.append(players.first->getName() + Game::FILE_NAME_ITEMS_DELIMITER + players.second->getName());
    else
        output.append(players.second->getName() + Game::FILE_NAME_ITEMS_DELIMITER + players.first->getName());

    saveToFile(output);
}

bool Game::bothPlayersStanding() const { return players.first->isStanding() && players.second->isStanding(); }

void Game::chooseDecks(const CardDatabase &cardDatabase) const {
    players.first->chooseDeck(cardDatabase);
    players.second->chooseDeck(cardDatabase);
}

Player *Game::currentlyNotPlaying() const { return players.second; }

Player *Game::currentlyPlaying() const { return players.first; }

void Game::drawHands() const {
    players.first->drawHand();
    players.second->drawHand();
}

string Game::getGameFileName(const vector<string> &savedGames) {
    size_t choice = 0;
    bool invalidInput = true;
    string fileNumber;

    while (invalidInput) {
        cin >> fileNumber;
        choice = stoull(fileNumber);
        invalidInput = (choice >= savedGames.size());
        if (invalidInput)
            invalidInputMessage();
    }

    return SAVES_FOLDER + savedGames[choice];
}

Player *Game::getGameVictor() const {
    return players.first->getRoundsWon() > players.second->getRoundsWon() ? players.first : players.second;
}

Player *Game::getRoundVictor() const {
    if (roundIsTie())
        return nullptr;

    return players.first->getCurrentRoundScore() > players.second->getCurrentRoundScore() ? players.first
                                                                                          : players.second;
}

vector<string> Game::getSavedGames() {
    vector<string> files;

    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir(SAVES_FOLDER)) != nullptr) {
        while ((ent = readdir(dir)) != nullptr) {
            string fileName = ent->d_name;
            if (fileName != "." && fileName != "..")
                files.emplace_back(ent->d_name);
        }
        closedir(dir);
    } else
        throw CannotOpenDirectory();

    return files;
}


Game *Game::loadFromFile(const CardDatabase &cardDatabase) {
    vector<string> savedGames = getSavedGames();
    listGamesInDirectory(savedGames);
    string outputPath(getGameFileName(savedGames));

    ifstream file;
    file.open(outputPath, fstream::in);
    if (!file.is_open())
        throw InvalidFileException();

    string currentScore;
    getline(file, currentScore);

    list<string> parsed = CardDatabase::split(currentScore, FILE_FIELD_VALUE_DELIMITER);
    if (parsed.front() != CURRENT_SCORE_LEAD)
        throw ParseError();

    Game *game = new Game();
    game->roundNumber = stoull(parsed.back());
    game->loadPlayersFromFile(file, cardDatabase);
    file.close();
    return game;
}

void Game::manualSave() const {
    enterFileNameQuery();
    string filename;
    cin >> filename;
    if (filename == "Q")
        return;
    saveToFile(Game::SAVES_FOLDER + filename);
}

void Game::play() {
    gameStartMessage();

    while (roundNumber <= ROUNDS) {
        currentScoreMessage();
        roundPrompt();
        Player *roundVictor = round();
        if (!roundVictor) {
            Game::clearScreen(cout);
            roundTieMessage();
        } else {
            roundVictor->addPoint();
            ++roundNumber;
            Game::clearScreen(cout);
            roundVictorMessage(roundVictor);
        }
        autoSave();

    }
    Game::clearScreen(cout);
    gameVictorMessage();
    returnToMainMenu();
}

void Game::returnToMainMenu() {
    anyKeyToContinueQuery();
    string anyKey;
    cin >> anyKey;
}

void Game::resetBoards() {
    players.first->resetBoard();
    players.second->resetBoard();
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

bool Game::roundIsTie() const {
    return players.first->getCurrentRoundScore() == players.second->getCurrentRoundScore();
}

void Game::selectStartingPlayer() {
    if (players.first->getOpener() < players.second->getOpener())
        swapPlayers();
}

void Game::swapPlayers() { swap(players.first, players.second); }

void Game::saveToFile(const string &outputPath) const {
    ofstream file;

    file.open(outputPath, fstream::out);
    if (!file.is_open())
        throw CannotOpenFile();

    file << CURRENT_SCORE_LEAD << FILE_FIELD_VALUE_DELIMITER << roundNumber << endl;
    players.first->saveToFile(file);
    players.second->saveToFile(file);

    file.close();
}

void Game::turn(Player *currentPlayer) {
    turnPrompt();
    const int opponentScore = players.second->getCurrentRoundScore();
    currentPlayer->takeTurn(opponentScore);
}

//--------------------------------------------------------------------------------------------------------------------//
//Queries and prompts-------------------------------------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------------------------//
void Game::anyKeyToContinueQuery() { cout << "Press any key to return to main menu" << endl; }

void Game::clearScreen(ostream &out) {
    ios_base::fmtflags f(out.flags());
    //out << setfill('\n') << setw(ROWS_CLEARED) << endl;
    for (size_t i = 0; i < Game::ROWS_CLEARED; ++i)
        out << endl;
    out.flags(f);
}

void Game::currentScoreMessage() const {
    cout << "Current score: "
         << players.first->getName() << ":" << players.first->getRoundsWon() << " |"
         << players.second->getName() << ":" << players.second->getRoundsWon() << endl;
}

void Game::enterFileNameQuery() { cout << "Enter a file name to save the game ['Q' to quit]: " << endl; }

void Game::gameStartMessage() const {
    Game::clearScreen(cout);
    cout << "Starting a game of Pazaak between "
         << players.first->getName() << " and "
         << players.second->getName() << "." << endl;
}

void Game::gameVictorMessage() const { cout << getGameVictor()->getName() << " won the game!" << endl; }

void Game::invalidInputMessage() { cout << "Invalid input, please try again," << endl; }

void Game::listGamesInDirectory(const vector<string> &savedGames) {
    size_t i = 0;
    for (const auto &game : savedGames)
        cout << "(" << i++ << ") " << game << endl;
}

void Game::loadPlayersFromFile(ifstream &file, const CardDatabase &cardDatabase) {
    players.first = Player::loadFromFile(file, cardDatabase, nullptr);
    players.second = Player::loadFromFile(file, cardDatabase, players.first);
}

void Game::turnPrompt() const { cout << players.first->getName() << "'s turn to play!" << endl; }

void Game::roundPrompt() const { cout << "Starting round #" << roundNumber << endl; }

void Game::roundTieMessage() { cout << "Tie" << endl; }

void Game::roundVictorMessage(const Player *victor) { cout << victor->getName() << " won the round!" << endl; }
