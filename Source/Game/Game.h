//
// Created by tomtom on 11/02/19.
//

#ifndef PAZAAK_GAME_H
#define PAZAAK_GAME_H

#include "../Player/Player.h"

class Game {
private:
    //Attributes------------------------------
    Player *players[2];
    size_t currentlyPlaying;
    //int timeElapsed;

    //Methods--------------------------------
    /**
     * Swaps between currently playing and not playing players
     */
    void swapPlayers();

    /**
     * Generates a random index to determine which player will go first
     * @return random integer between 0 and 1
     */
    size_t selectStartingPlayer();

    /**
     * Plays a round between the two players
     * @return Player who won the round, nullptr if the round was a draw
     */
    Player *round();

    /**
     * Returns the player who is not currently on turn
     * @return Pointer to an element of the players container, which is not currently playing
     */
    Player *currentlyNotPlaying() const;

    /**
     * Determines whether both players are standing, and effectively ends the current round if so
     * @return True if both are standing, False if at least one isn't
     */
    bool bothPlayersStanding() const;

    /**
     * Provides the 'players' array index of the player not currently playing
     * @return Negation of currentlyPlaying
     */
    size_t otherPlayerIndex() const;

    /**
     * Examines the score and determines the victor of the round
     * @return Victorious player, nullptr if the round was a draw
     */
    Player *getVictor() const;

    void turn(Player *currentPlayer);

    //Messages & prompts-----------------------
    /**
     * Shows a message to tell players the game has commenced
     */
    void gameStartMessage() const;

    /**
     * Determines whether the finished round ended in a tie, e.g. equal score of both players
     * @return True if players have equal score, False otherwise
     */
    bool roundIsTie() const;

    /**
     * Informs the players that a round is commencing //TODO BETTER DESCRIPTION
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
    //Constructor----------------------------
    Game(Player *player1, Player *player2, const std::map<std::string, Card *> &allCards);

    ~Game();

    //Methods--------------------------------
    void play();

    void gameWinnerMessage() const;

    void resetBoards();
};

#endif //PAZAAK_GAME_H
