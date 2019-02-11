//
// Created by tomtom on 08/02/19.
//

#ifndef TMPPAZAAK_PLAYERBOARD_H
#define TMPPAZAAK_PLAYERBOARD_H


#include <vector>
#include "../../Cards/CardInterface/Card.h"
#include "../Player.h"


using namespace std;

class PlayerBoard {

private:
    //Attributes--------------------------
    int currentScore;
    vector<Card *> playedCards;
    int roundsWon;
    bool standing;
    Player * currentOpponent;

public:
    //Constructor------------------------
    PlayerBoard(Player *currentOpponent);

    //Getters----------------------------
    int getCurrentScore() const;

    Player * getCurrentOpponent() const;
    vector<Card *> getPlayedCards() const;


    bool isStanding() const;

    //Setters----------------------------
    void addPoint();

    void addPlayedCard(Card *card);

    void setPlayedCards(const vector<Card *> &playedCards);

    void setCurrentScore(int currentScore);

    void setStanding(bool standing);

    void stand();
};


#endif //TMPPAZAAK_PLAYERBOARD_H
