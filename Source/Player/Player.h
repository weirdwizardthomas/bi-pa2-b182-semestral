//
// Created by tomtom on 08/02/19.
//

#ifndef PAZAAK_PLAYER_H
#define PAZAAK_PLAYER_H

#include <cstdlib>
#include <string>
#include <map>
#include <sstream>


#include "Deck/Deck.h"
#include "PlayerBoard/PlayerBoard.h"

class Player {
private:
    std::string name;
    Deck deck;
    PlayerBoard board;
    //Statistics statistics; TODO, games played, victories, cards played, favourite card,...

    void createDeck(const map<string, Card *> &allCards);

    void loadDeck(const map<string, Card *> &allCards);

public:
    //Constructors----------------------
    Player() = default;

    explicit Player(string name);

    void play(int opponentScore);

    void chooseDeck(const std::map<std::string, Card *> &allCards);

    //Setters--------------------------
    void addPoint();

    const std::string &getName() const;

    //Getters--------------------------
    int getScore() const;

    bool isStanding() const;

    size_t getPlayedCardsCount() const;

    const Deck &getDeck() const;
};


#endif //PAZAAK_PLAYER_H
