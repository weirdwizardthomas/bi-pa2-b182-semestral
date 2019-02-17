//
// Created by tomtom on 11/02/19.
//

#ifndef PAZAAK_GAME_H
#define PAZAAK_GAME_H

#define BASE_ROUND_COUNT 3
#define TARGET 20
#define TABLE_SIZE 9

#include "../Player/Player.h"

class Game {

private:

    //Attributes------------------------------
    Player players[2];
    size_t currentlyPlaying;
    //int timeElapsed;

    //Methods--------------------------------
    void swapPlayers();

    size_t selectStartingPlayer();

    Player *round();

    Player *currentlyNotPlaying();

    bool bothPlayersStanding();

    size_t otherPlayerIndex() const;

    Player *getVictor();

    void turn();

    //Messages & prompts--------------------
    void gameStartMessage() const;

    bool roundIsTie() const;

    void roundPrompt(size_t roundNumber) const;

    void roundTieMessage() const;

    void roundVictorMessage(const Player *victor) const;

    void turnPrompt() const;

public:
    //Constructor----------------------------
    Game(Player *a, Player *b);

    //Methods--------------------------------
    void play();

};
#endif //PAZAAK_GAME_H
