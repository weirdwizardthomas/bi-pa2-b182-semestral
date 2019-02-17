//
// Created by tomtom on 08/02/19.
//

#ifndef PAZAAK_PLAYER_H
#define PAZAAK_PLAYER_H

#include <cstdlib>
#include <string>
#include <map>

#include "Deck/Deck.h"
#include "PlayerBoard/PlayerBoard.h"

using namespace std;

class Player {
private:
    string name;
    Deck deck;
    PlayerBoard board;
    //Statistics statistics; TODO, games played, victories, cards played, favourite card,...



    void createDeck(map<string, Card *> & allCards);
public:

    Player() = default;
    Player(string name);

    void play(int opponentScore);
    void chooseDeck(map<string, Card *> & allCards);

    const string &getName() const;
    int getScore() const;
    void addPoint();
    bool isStanding();

    size_t getPlayedCardsCount();

    void loadDeck();
};


#endif //PAZAAK_PLAYER_H
