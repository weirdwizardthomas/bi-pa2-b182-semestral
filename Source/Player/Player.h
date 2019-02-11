//
// Created by tomtom on 08/02/19.
//

#ifndef PAZAAK_PLAYER_H
#define PAZAAK_PLAYER_H

#include <cstdlib>
#include <string>
#include "../Deck/Deck.h"
#include "PlayerBoard/PlayerBoard.h"

using namespace std;

class Player {
private:
    string name;
    Deck deck;
    PlayerBoard board;
    //Statistics statistics; TODO, games played, victories, cards played, favourite card,...

public:
    void play();

    const string &getName() const;
};


#endif //PAZAAK_PLAYER_H
