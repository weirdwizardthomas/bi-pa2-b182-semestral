//
// Created by tomtom on 08/02/19.
//

#ifndef PAZAAK_PLAYER_H
#define PAZAAK_PLAYER_H

#include <cstdlib>
#include <std::string>
#include <std::map>
#include <sstream>


#include "Deck/Deck.h"
#include "PlayerBoard/PlayerBoard.h"

class Player {
private:
    std::string name;
    Deck deck;
    PlayerBoard board;
    //Statistics statistics; TODO, games played, victories, cards played, favourite card,...

    void createDeck(std::map<std::string, Card *> &allCards);

public:

    Player() = default;

    Player(std::string name);

    void play(int opponentScore);

    void chooseDeck(std::map<std::string, Card *> &allCards);

    const std::string &getName() const;

    int getScore() const;

    void addPoint();

    bool isStanding();

    size_t getPlayedCardsCount();

    void loadDeck();
};


#endif //PAZAAK_PLAYER_H
