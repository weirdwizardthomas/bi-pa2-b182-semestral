//
// Created by tomtom on 08/02/19.
//

#ifndef TMPPAZAAK_PLAYERBOARD_H
#define TMPPAZAAK_PLAYERBOARD_H


#include <vector>
#include "Cards/Card Interface/Card.h"


using namespace std;

class PlayerBoard {

private:
    int currentScore;
    vector<Card *> playedCards;

public:

    PlayerBoard();

    int getCurrentScore() const;

    void setCurrentScore(int currentScore);

    vector<Card *> getPlayedCards() const;

    void setPlayedCards(const vector<Card *> &playedCards);

    void addPlayedCard(Card *card);

};


#endif //TMPPAZAAK_PLAYERBOARD_H
