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
#include "Hand/Hand.h"

class Player {
private:
    //Attributes---------------------------------------------------------
    std::string name;
    Deck deck;
    PlayerBoard board;
    Hand hand;
    //Statistics statistics; TODO, games played, victories, cards played, favourite card,...

    //Methods-------------------------------------

    int autoPlayCard();

    //Messages-and-prompts------------------------
    void actionPrompt() const;

    void boardStatusMessage(int opponentScore) const;

    void deckApprovalQuery() const;

    void invalidInputMessage() const;

    void playerIsStandingMessage() const;

public:
    Player() = default;

    explicit Player(std::string name);

    void takeTurn(int opponentScore);

    //Setters---------------------------------------
    void addPoint();

    void chooseDeck(const std::map<std::string, Card *> &allCards);

    void drawHand();

    //Getters---------------------------------------
    int getCurrentRoundScore() const;

    const std::string &getName() const;

    int getOpener() const;

    size_t getPlayedCardsCount() const;

    size_t getRoundsWon() const;

    bool isStanding() const;
};

#endif //PAZAAK_PLAYER_H