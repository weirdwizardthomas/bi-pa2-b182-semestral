//
// Created by tomtom on 11/02/19.
//

#ifndef PAZAAK_GAME_H
#define PAZAAK_GAME_H


#include "Player/Player/Player.h"
#include "Utilities/RandomNumberGenerator.h"

/**
 * Contains the actual game logic, with players taking turns playing against each other in a set of rounds.
 */
class Game {
private:
    //Attributes------------------------------
    std::pair<Player *, Player *> players;
    size_t roundNumber;
    //Methods--------------------------------
    /**
     * Saves the game's current status, including all it's elements to a file to be re-constructable later
     */
    void autoSave() const;

    /**
     * Determines whether both players are standing, and effectively ends the current round if so
     * @return True if both are standing, False if at least one isn't
     */
    bool bothPlayersStanding() const;

    /**
     * Queries both players to select an existing deck of cards or to build a new one
     * @param cardDatabase Database of all available cards
     */
    void chooseDecks(const CardDatabase &cardDatabase) const;

    /**
     * Returns the player who is not currently on turn
     * @return Pointer to an element of the 'players' container, which is not currently playing
     */
    Player *currentlyNotPlaying() const;

    /**
     * Returns the player who is currently on turn
     * @return Pointer to an element of the 'players' container, which is  currently playing
     */
    Player *currentlyPlaying() const;

    /**
     * Draws cards for each player respectively
     */
    void drawHands() const;

    /**
     * Queries the user to select a deck from the the directory of saved games
     * @param[in] savedGames Container of all filenames within the directory of saved games
     * @return Relative path to the picked Game file
     */
    static std::string getGameFileName(const std::vector<std::string> &savedGames);

    /**
     * Examines the round scores of either players and determines the victor of the game
     * @return Player with the higher score
     */
    Player *getGameVictor() const;

    /**
     * Examines the score and determines the victor of the round
     * @return Victorious player, nullptr if the round was a draw
     */
    Player *getRoundVictor() const;

    /**
     * Locates all files, representing a game in progress, in the Game::SAVED_FOLDER directory
     * @return names of all files in the Game::SAVED_FOLDER directory
     */
    static std::vector<std::string> getSavedGames();

    /**
     * Queries the user to save a file with a custom filename within the Game::SAVED_FOLDER directory
     */
    void manualSave() const;

    /**
     * Loads both players based on the contents of input stream
     * @param[in] file File containing game's saved data
     * @param[in] cardDatabase Database of all cards
     */
    void loadPlayersFromFile(std::ifstream &file, const CardDatabase &cardDatabase);

    /**
     * Saves the current state of the game to a file
     * @param[in] outputPath Path to the saving file
     */
    void saveToFile(const std::string &outputPath) const;

    /**
     * Sets the Player::board element of either player to a default state
     */
    void resetBoards();

    /**
     * Plays a round between the two players
     * @return Player who won the round, nullptr if the round was a draw
     */
    Player *round();

    /**
     * Determines whether the finished round ended in a tie, i.e. equal playerBoard::currentScore of both players
     * @return True if players have equal score, false otherwise
     */
    bool roundIsTie() const;

    /**
     * Swaps between currently playing and currently not playing player
     */
    void swapPlayers();

    /**
     * Determines the starting player by examining the first card of either player's main deck. Higher value goes first
     */
    void selectStartingPlayer();

    /**
     * Queries current player to play their turn if they are not skipping it
     * @param currentPlayer Player to take their turn
     */
    void turn(Player *currentPlayer);

    /**
     * Stops the programme from any other actions until the user prompts it to continue
     */
    static void returnToMainMenu();

    //Messages & prompts-----------------------
    /**
     * Queries the user to press any key to return to main menu
     */
    static void anyKeyToContinueQuery();

    /**
     * Shows a message to tell players each player's score
     */
    void currentScoreMessage() const;

    /**
     * Queries the user for a name of the saved file
     */
    static void enterFileNameQuery();

    /**
     * Shows a message to tell players the game has commenced.
     */
    void gameStartMessage() const;

    /**
     * Shows a message to tell players who the victor is
     */
    void gameVictorMessage() const;

    /**
     * Informs the user that the input is not valid for the given scenario
     */
    static void invalidInputMessage();

    /**
     * Shows the filenames of all the decks within the Game::SAVED_FOLDER directory
     * @param savedGames Container of all the file names within the Game::SAVED_FOLDER directory
     */
    static void listGamesInDirectory(const std::vector<std::string> &savedGames);

    /**
     * Shows a message that a round is commencing
     */
    void roundPrompt() const;

    /**
     * Shows a message to tell players that the round ended in a tie
     */
    static void roundTieMessage();

    /**
     * Shows a message to tell the players who the victor of the round is
     * @param victor Pointer to the player who has scored higher than their opponent
     */
    static void roundVictorMessage(const Player *victor);

    /**
     * Shows a message to tell the player he is eligible to take his turn
     */
    void turnPrompt() const;

public:
    static const int ROUNDS;
    static const int TARGET_SCORE;
    static const int ROWS_CLEARED;
    static const char *SAVES_FOLDER;
    static const char *CURRENT_SCORE_LEAD;
    static const char *FILE_FIELD_VALUE_DELIMITER;
    static const char *AUTOSAVE_LEADING;
    static const char *FILE_NAME_ITEMS_DELIMITER;

    /**
     * Creates an instance with existing players
     * @param player1 Dynamically allocated instance of a first player
     * @param player2 Dynamically allocated instance of a second player
     * @param cardDatabase Database of all available cards
     */
    Game(Player *player1, Player *player2, const CardDatabase &cardDatabase);

    /**
     * Creates a default instance
     */
    Game();

    ~Game();

    //Methods--------------------------------
    /**
     * Starts a game between the two players. The game is divided into a set of rounds
     * in which players take turn alternatively
     * First player to win Game::ROUNDS number of rounds wins the game
     */
    void play();

    /**
     * Queries the user to select a save game and loads it to a playable state
     * @param[in] cardDatabase Database of all available cards
     * @return Dynamically allocated instance loaded from a selected file
     */
    static Game *loadFromFile(const CardDatabase &cardDatabase);

    /**
     * Clears the output stream by sending a Game::ROWS_CLEARED number of new lines into it
     * @param[in,out] out Output stream to be cleared
     */
    static void clearScreen(std::ostream &out);
};

#endif //PAZAAK_GAME_H
