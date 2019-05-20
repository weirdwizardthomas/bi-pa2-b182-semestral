//
// Created by tomtom on 08/02/19.
//

#ifndef PAZAAK_FLIPCARD_H
#define PAZAAK_FLIPCARD_H


#include <cstdlib>

#include "DualCard.h"


/**
 * Flip cards negate the signs of two values on all cards of the current player when played
 */
class FlipCard : public DualCard {

public:
    static const char *FLIP_SIGN;

    FlipCard(int left, int right);

    /**
     * Swaps the signs on all cards with  value equal to this card's effects.
     * @param playedCards Cards previously played by the current player.
     * @param currentScore Current player's current round's score.
     * @param opponentScore Opponent's current round's score.
     * @return 0, as the card itself does not add any new value.
     */
    int play(std::vector<int> &playedCards, int currentScore, int opponentScore) const override;

    std::string getDescription() const override;
};


#endif //PAZAAK_FLIPCARD_H
