//
// Created by tomtom on 08/02/19.
//

#ifndef TMPPAZAAK_PLAYERBOARD_H
#define TMPPAZAAK_PLAYERBOARD_H

#include <vector>

#include "../Cards/Card.h"
#include "../Cards/BasicCard.h"
#include "../Utilities/RandomNumberGenerator.h"
#include "../Cards/CardDatabase.h"


class PlayerBoard {

private:
    //Attributes--------------------------
    int currentScore;
    size_t roundsWon;
    bool standing;
    std::vector<int> playedCards;
    std::vector<BasicCard *> mainDeck;
    RandomNumberGenerator randomNumberGenerator;

    /**
     *
     */
    void generateMainDeck();


    /**
     *
     */
    void recalculateScore();

    /**
     *
     */
    void resetPlayedCards();

public:
    static const int TABLE_SIZE = 9;
    static const int MAIN_DECK_CARD_COPIES = 4;
    static const char *PLAYED_CARDS_DELIMITER;

    PlayerBoard();

    ~PlayerBoard();

    void saveToFile(std::ofstream &out) const;

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
    int getOpener();

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

    static PlayerBoard loadFromFile(std::ifstream &ifstream, const CardDatabase &database);
};


#endif //TMPPAZAAK_PLAYERBOARD_H
