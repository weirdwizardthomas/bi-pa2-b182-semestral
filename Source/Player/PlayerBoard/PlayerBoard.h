//
// Created by tomtom on 08/02/19.
//

#ifndef TMPPAZAAK_PLAYERBOARD_H
#define TMPPAZAAK_PLAYERBOARD_H

#include <vector>

#include "../../Cards/CardInterface/Card.h"
#include "../../Cards/CardImplementations/BasicCard/BasicCard.h"

#define TABLE_SIZE 9
#define MAIN_DECK_CARD_COPIES 4

#define SPACE " "

class PlayerBoard {

private:
    //Attributes--------------------------
    int currentScore;
    std::vector<int> playedCards;
    std::vector<BasicCard *> mainDeck;
    size_t roundsWon;
    bool standing;

    BasicCard *getRandomCard(size_t index) const;


public:
    //Constructors-----------------------
    PlayerBoard();

    //Destructors------------------------
    ~PlayerBoard();

    //Getters----------------------------
    int getCurrentScore() const;

    std::vector<int> &getPlayedCards();

    size_t getPlayedCardsCount() const;

    bool isStanding() const;

    std::string showCardsPlayed() const;

    size_t getRoundsWon() const;


    int getOpener() const;

    int drawCardFromMainDeck();

    //Setters----------------------------
    void addPoint();

    void setStanding(bool standing);

    void stand();

    void addPlayedCard(int cardValue);

    void recalculateScore();

    unsigned long getRandomBoundIndex() const;
};


#endif //TMPPAZAAK_PLAYERBOARD_H
