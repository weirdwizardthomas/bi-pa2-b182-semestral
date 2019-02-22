//
// Created by tomtom on 08/02/19.
//

#ifndef PAZAAK_FLIPCARD_H
#define PAZAAK_FLIPCARD_H


//Libraries---------------------------------

#include <cstdlib>

//Classes-----------------------------------
#include "../DualCard.h"

//Definitions-------------------------------
#define FLIP_SIGN  " <~> "

//TODO reword this to be clearer
/**
 * Flip cards negate the signs of two values on all cards of the current player when played
 */
class FlipCard : public DualCard {

public:
    FlipCard(int a, int b);
   /**
    * Swaps the sign's on all cards with the value equal to this card's effects
    * @param playedCards Cards previously played by the current player
    * @param currentScore Current player's current round's score
    * @param opponentScore Opponent's current round's score
    * @return current player's score updated by flipping the respective cards' sign
    */
    int play(std::vector<int> &playedCards, int currentScore, int opponentScore) const override;

    std::string getDescription() const override;
};


#endif //PAZAAK_FLIPCARD_H
