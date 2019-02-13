//
// Created by tomtom on 08/02/19.
//

#ifndef PAZAAK_PLAYER_H
#define PAZAAK_PLAYER_H

#include <cstdlib>
#include <string>
#include "../Deck/Deck.h"
#include "PlayerBoard/PlayerBoard.h"


#pragma once

using namespace std;

class Player {
private:
    string name;
    Deck deck;
    PlayerBoard board;
    //Statistics statistics; TODO, games played, victories, cards played, favourite card,...


public:

    Player() = default;
    Player(string name);

    void play(int opponentScore);
    void createDeck();

    const string &getName() const;
    int getScore() const;
    void addPoint();
    bool isStanding();

    int playedCardsCount();
};


#endif //PAZAAK_PLAYER_H
