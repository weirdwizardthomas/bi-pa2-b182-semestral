//
// Created by tomtom on 11/02/19.
//

#ifndef PAZAAK_GAME_H
#define PAZAAK_GAME_H

#define BASE_ROUND_COUNT 3

#include "Player/Player.h"

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

    void turn();

    //Messages & prompts--------------------
    bool roundIsTie() const;

    void roundPrompt(int roundNumber) const;

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
