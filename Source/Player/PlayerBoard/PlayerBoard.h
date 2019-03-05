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

    //Getters---------------------------
    /**
     *
     * @param index
     * @return
     */
    BasicCard *getRandomCard(size_t index) const;

    //Setters---------------------------
    /**
     *
     * @param standing
     */
    void setStanding(bool standing);

    //Supportive-methods------------------
    /**
     *
     * @return
     */
    size_t generateRandomBoundIndex() const;

    void recalculateScore();

    /**
     *
     */
    void resetPlayedCards();

public:
    //Constructors-----------------------
    PlayerBoard();

    //Destructors------------------------
    ~PlayerBoard();

    //Getters----------------------------
    /**
     *
     * @return
     */
    int drawCardFromMainDeck();

    /**
     *
     * @return
     */
    int getCurrentScore() const;

   /**
    *
    * @return
    */
    int getOpener() const;

    /**
     *
     * @return
     */
    std::vector<int> &getPlayedCards();
    /**
     *
     * @return
     */
    size_t getPlayedCardsCount() const;
    /**
     *
     * @return
     */
    size_t getRoundsWon() const;
    /**
     *
     * @return
     */
    bool isStanding() const;
    /**
     *
     * @return
     */
    std::string showCardsPlayed() const;

    //Setters----------------------------
    /**
     *
     * @param cardValue
     */
    void addPlayedCard(int cardValue);
    /**
     *
     */
    void addPoint();
    /**
     *
     */
    void stand();
    /**
     *
     */
    void reset();

};


#endif //TMPPAZAAK_PLAYERBOARD_H
