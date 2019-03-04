//
// Created by tomtom on 08/02/19.
//

#ifndef TMPPAZAAK_PLAYERBOARD_H
#define TMPPAZAAK_PLAYERBOARD_H


#define TABLE_SIZE 9
#define SPACE " "

#define SIDEDECK_SIZE 40

#include <vector>
#include "../../Cards/CardInterface/Card.h"


class PlayerBoard {

private:
    //Attributes--------------------------
    int currentScore;
    std::vector<int> playedCards;
    std::vector<Card *> sidedeck;
    size_t roundsWon;
    bool standing;

public:
    //Constructors-----------------------
    PlayerBoard();

    //Destructors------------------------
    ~PlayerBoard() = default;

    //Getters----------------------------
    int getCurrentScore() const;

    std::vector<int> &getPlayedCards();

    size_t getPlayedCardsCount() const;

    bool isStanding() const;

    std::string showCardsPlayed() const;

    size_t getRoundsWon() const;

    //Setters----------------------------
    void addPoint();

    void setStanding(bool standing);

    void stand();

    void addPlayedCard(int cardValue);

    void recalculateScore();
};


#endif //TMPPAZAAK_PLAYERBOARD_H
