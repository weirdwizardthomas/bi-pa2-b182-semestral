//
// Created by tomtom on 03/02/19.
//

#ifndef TMPPAZAAK_DOUBLECARD_H
#define TMPPAZAAK_DOUBLECARD_H


#include "Card.h"

/**
 * Multiplies the value of the last played card by 2. Does not add any new value on its own
 */
class DoubleCard : public Card {

public:
    ~DoubleCard() override = default;

    std::string getDescription() const override;

    /**
     * Removes the last played card and returns a card with a value double of it
     * @param playedCards Cards previously played by the current player
     * @param currentScore Current player's current round's score
     * @param opponentScore Opponent's current round's score
     * @see PlayerBoard::playedCards
     * @see PlayerBoard::currentScore
     * @return Value of the last card doubled
     */
    int play(std::vector<int> &playedCards, int currentScore, int opponentScore) const override;
};


#endif //TMPPAZAAK_DOUBLECARD_H
