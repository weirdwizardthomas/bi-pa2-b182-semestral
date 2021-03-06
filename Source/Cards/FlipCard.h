#ifndef PAZAAK_FLIPCARD_H
#define PAZAAK_FLIPCARD_H


#include <cstdlib>

#include "DualCard.h"


/**
 * Inverts all the signs with values equal to the Flip card's value for the Card player when played
 * Does not add any new value on its own
 */
class FlipCard : public DualCard {

public:
    static const char *FLIP_SIGN;

    /**
     * Initialises the FlipCard::values with two values
     * @param[in] left First value to be put into FlipCard::values
     * @param[in] right Second value to be put into FlipCard::values
     */
    FlipCard(int left, int right);

    /**
     * Swaps the signs on all cards with value equal to this card's effects
     * @param[in,out] playedCards Cards previously played by the current player
     * @param[in] currentScore Current player's current round's score
     * @param[in] opponentScore Opponent's current round's score
     * @return 0, as the card itself does not add any new value
     */
    int play(std::vector<int> &playedCards, int currentScore, int opponentScore) const override;

    std::string getDescription() const override;
};


#endif //PAZAAK_FLIPCARD_H
