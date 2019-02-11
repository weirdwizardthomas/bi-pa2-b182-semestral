//
// Created by tomtom on 11/02/19.
//

#ifndef PAZAAK_GAME_H
#define PAZAAK_GAME_H


#include "Player/Player.h"

class Game {


private:

    //Attributes------------------------------
    Player players[2];
    Player * playerOnTurn;
    //int timeElapsed;


    //Methods--------------------------------
    void swapPlayers();
    void turnPrompt() const;
    Player * selectStartingPlayer();
public:

    Game(Player &a, Player &b);

    //Methods--------------------------------
    void turn();
};


#endif //PAZAAK_GAME_H
