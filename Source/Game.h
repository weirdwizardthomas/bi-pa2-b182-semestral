//
// Created by tomtom on 11/02/19.
//

#ifndef PAZAAK_GAME_H
#define PAZAAK_GAME_H

#include "Player/Player/Player.h"
#include "Utilities/RandomNumberGenerator.h"

class Game {
private:
    //Attributes------------------------------
    std::pair<Player *, Player *> players;
    //Methods--------------------------------

    /**
     * Determines whether both players are standing, and effectively ends the current round if so
     * @return True if both are standing, False if at least one isn't
     */
    bool bothPlayersStanding() const;

    /**
     * Queries both players to select an existing deck of cards or to build a new one
     * @param allCards Database of all available cards
     */
    void chooseDecks(const CardDatabase &allCards) const;

    /**
     * Returns the player who is not currently on turn
     * @return Pointer to an element of the players container, which is not currently playing
     */
    Player *currentlyNotPlaying() const;

    /**
     * Returns the player who is currently on turn
     * @return Pointer to an element of the players container, which is  currently playing
     */
    Player *currentlyPlaying() const;

    void drawHands() const;

    /**
     * Examines the score and determines the victor of the round
     * @return Victorious player, nullptr if the round was a draw
     */
    Player *getRoundVictor() const;

    /**
     * Examines the round scores of either players and determines the victor of the game
     * @return Player with a higher score than the other one
     */
    Player *getGameVictor() const;

    /**
     * Resets the board for both players
     */
    void resetBoards();

    /**
     * Plays a round between the two players
     * @return Player who won the round, nullptr if the round was a draw
     */
    Player *round();

    /**
     * Determines whether the finished round ended in a tie, e.g. equal score of both players
     * @return True if players have equal score, False otherwise
     */
    bool roundIsTie() const;

    /**
 * Swaps between currently playing and not playing player
 */
    void swapPlayers();

    /**
     * Determines the starting player by examining the first card of either player's main deck. Higher value goes first
     * @return
     */
    void selectStartingPlayer();

    /**
     *
     * @param currentPlayer
     */
    void turn(Player *currentPlayer);

    /**
     *
     * @param roundNumber
     */
    void autoSave(size_t roundNumber) const;

    /**
     *
     * @param roundNumber
     */
    void manualSave(size_t roundNumber) const;

    /**
     *
     * @param outputPath
     * @param roundNumber
     */
    void saveToFile(const std::string &outputPath, size_t roundNumber) const;

    static std::vector<std::string> getSavedGames();

    //Messages & prompts-----------------------
    void currentScoreMessage() const;

    /**
     * Shows a message to tell players the game has commenced
     */
    void gameStartMessage() const;

    /**
     * Shows a message to tell players who the victor is
     */
    void gameVictorMessage() const;

    /**
     * Shows a message that a round is commencing
     * @param roundNumber current round's number to be displayed
     */
    void roundPrompt(size_t roundNumber) const;

    /**
     * Shows a message to tell players that the round ended in a tie
     */
    void roundTieMessage() const;

    /**
     * Shows a message to tell the players who won the round
     * @param victor
     */
    void roundVictorMessage(const Player *victor) const;

    /**
     * Shows a message to tell the player he is eligible to take his turn
     */
    void turnPrompt() const;

public:
    static const int ROUNDS = 3;
    static const int TARGET_SCORE = 20;
    static const char *SAVES_FOLDER;
    static const char *CURRENT_SCORE_LEAD;

    //Constructor----------------------------
    Game(Player *player1, Player *player2, const CardDatabase &allCards);

    ~Game();

    //Methods--------------------------------
    void play();

    /**
     *
     * @return
     */
    static Game *loadFromFile();

    /**
     * Clears the 'out' stream by sending a number of new lines into it
     * @param out Output stream to be cleared
     */
    static void clearScreen(std::ostream &out);

    static void invalidInputMessage();

    static void listGamesInDirectory(const std::vector<std::string> &savedGames);

    static std::string getGameFileName(const std::vector<std::string> &savedGames);
};

#endif //PAZAAK_GAME_H
