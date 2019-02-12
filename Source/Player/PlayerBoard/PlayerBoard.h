//
// Created by tomtom on 08/02/19.
//

#ifndef TMPPAZAAK_PLAYERBOARD_H
#define TMPPAZAAK_PLAYERBOARD_H



#include <vector>
#include "../../Cards/CardInterface/Card.h"


using namespace std;

class PlayerBoard {

private:
    //Attributes--------------------------
    int currentScore;
    vector<int> playedCards;
    int roundsWon;
    bool standing;

public:
    //Constructor------------------------
    PlayerBoard();

    //Getters----------------------------
    int getCurrentScore() const;

    vector<int> getPlayedCards() const;

    bool isStanding() const;

    //Setters----------------------------
    void addPoint();

    void addPlayedCard(int value);

    void setCurrentScore(int currentScore);

    void setStanding(bool standing);

    void stand();
};


#endif //TMPPAZAAK_PLAYERBOARD_H
