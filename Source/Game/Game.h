//
// Created by tomtom on 11/02/19.
//

#ifndef PAZAAK_GAME_H
#define PAZAAK_GAME_H


//Definitions-----------------------
#define BASE_ROUND_COUNT 3
#define TARGET 20
#define TABLE_SIZE 9

#include "../Player/Player.h"

class Game {

private:
    Player players[2];
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

    Player *round();

    Player *currentlyNotPlaying();

    bool bothPlayersStanding();

    /**
     * Provides the 'players' array index of the player not currently playing
     * @return Negation of currentlyPlaying
     */
    size_t otherPlayerIndex() const;

    Player *getVictor();

    void turn();

    //Messages & prompts--------------------
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
    //Constructor----------------------------
    Game(Player *a, Player *b, const map<string, Card*> &allCards);

    //Methods--------------------------------
    void play();

};

#endif //PAZAAK_GAME_H
