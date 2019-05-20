//
// Created by tomtom on 03/02/19.
//

#ifndef TMPPAZAAK_DOUBLECARD_H
#define TMPPAZAAK_DOUBLECARD_H


#include "Card.h"

/**
 * Double cards double the value of the current player's last played card when played
 */
class DoubleCard : public Card {

public:

    ~DoubleCard() override = default;

    /**
     * Removes the last played card and returns a card with a value double of it.
     * @param playedCards Cards previously played by the current player.
     * @param currentScore Current player's current round's score.
     * @param opponentScore Opponent's current round's score.
     * @return Value of the last card doubled.
     */
    int play(std::vector<int> &playedCards, int currentScore, int opponentScore) const override;

    std::string getDescription() const override;

};


#endif //TMPPAZAAK_DOUBLECARD_H
