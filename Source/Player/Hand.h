//
// Created by tomtom on 09/02/19.
//

#ifndef PAZAAK_HAND_H
#define PAZAAK_HAND_H

#include <iostream>

#include "../Cards/Card.h"
#include "../Cards/CardDatabase.h"

class Hand {
private:
    std::vector<Card *> cards;

public:
    static const char *HAND_FILE_LEAD;
    static const char *FILE_VALUE_DELIMITER;

    /**
     *
     * @param card
     */
    void addCard(Card *card);

    /**
     *
     * @param cardIndex
     * @param playedCards
     * @param currentScore
     * @param opponentScore
     * @return
     */
    int playCard(size_t cardIndex, std::vector<int> &playedCards, int currentScore, int opponentScore);

    /**
     *
     */
    void saveToFile(std::ofstream &file) const;

    /**
     *
     * @param out
     * @param hand
     * @return
     */
    friend std::ostream &operator<<(std::ostream &out, const Hand &hand);

    /**
     *
     * @param file
     * @param cardDatabase
     * @return
     */
    static Hand loadFromFile(std::ifstream &file, const CardDatabase &cardDatabase);
};


#endif //PAZAAK_HAND_H
