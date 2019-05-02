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
     * Puts the card's effect in play - doubles the effective value of the last played card
     * @param playedCards Cards previously played by the current player
     * @param currentScore Current player's current round's score
     * @param opponentScore Opponent's current round's score
     * @return current player's score updated by doubling last card's value
     */
    int play(std::vector<int> &playedCards, int currentScore, int opponentScore) const override;

    std::string getDescription() const override;

};


#endif //TMPPAZAAK_DOUBLECARD_H
