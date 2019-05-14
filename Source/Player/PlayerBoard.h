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
    std::vector<BasicCard> mainDeck;
    RandomNumberGenerator randomNumberGenerator;

    /**
     *
     */
    void generateMainDeck();

    /**
     *
     * @param file
     * @return
     */
    static std::vector<int> loadPlayedCards(std::ifstream &file);

    /**
     *
     * @param file
     * @return
     */
    static int loadCurrentScore(std::ifstream &file);

    /**
     *
     * @param file
     * @return
     */
    static size_t loadRoundsWon(std::ifstream &file);

    /**
     *
     * @param file
     * @return
     */
    static bool loadStanding(std::ifstream &file);

    /**
     *
     */
    static std::vector<BasicCard> loadMainDeck(std::ifstream &file);

    /**
     *
     * @param field
     * @param file
     * @return
     */
    static std::string loadValue(const std::string &field, std::ifstream &file);

    /**
     *
     */
    void recalculateScore();

    /**
     *
     */
    void resetPlayedCards();

public:
    static const size_t TABLE_SIZE;
    static const size_t MAIN_DECK_CARD_COPIES;
    static const char *PLAYED_CARDS_DELIMITER;
    static const char *ROUNDS_WON_LEAD;
    static const char *CURRENT_SCORE_LEAD;
    static const char *FIELD_VALUE_DELIMITER;
    static const char *ITEM_LIST_DELIMITER;
    static const char *MAIN_DECK_LEAD;
    static const char *CARDS_PLAYED_LEAD;
    static const char *IS_STANDING_LEAD;
    static const char *IS_STANDING_VALUE;
    static const char *IS_NOT_STANDING_VALUE;
    static const char *ITEM_INDEX_LEAD;


    PlayerBoard();

    /**
     *
     * @param out
     */
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
     * @param file
     * @param database
     * @return
     */
    static PlayerBoard loadFromFile(std::ifstream &file, const CardDatabase &database);

    /**
     *
     */
    void reset();

    /**
     *
     */
    void stand();
};


#endif //TMPPAZAAK_PLAYERBOARD_H
