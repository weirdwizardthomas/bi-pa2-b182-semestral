//
// Created by tomtom on 03/02/19.
//

#ifndef TMPPAZAAK_PLUSMINUSONETWOCARD_H
#define TMPPAZAAK_PLUSMINUSONETWOCARD_H

//Classes-----------------------------------
#include "DualCard.h"


/**
 * A special case of the Dual card, Flex cards offer the choice of four choices: +/- 1/2
 */
class FlexCard : public DualCard {
private:
    std::string getSignedAttribute() const;

    void chooseSignPrompt() const;

public:
    static const int LEFT = 1;
    static const int RIGHT = 2;
    static const char *SIGN_DELIMITER;

    //Constructor---------------------------
    FlexCard();

    //Methods-------------------------------
    /**
     * Presents the player with a choice of sign and 1/2 to be played
     * @param playedCards Cards previously played by the current player
     * @param currentScore Current player's current round's score
     * @param opponentScore Opponent's current round's score
     * @return current player's score updated by flipping the respective cards' sign
     * @return currentScore updated by incrementing the chosen effects
     */
    int play(std::vector<int> &playedCards, int currentScore, int opponentScore) const override;

    std::string getDescription() const override;

};

#endif //TMPPAZAAK_PLUSMINUSONETWOCARD_H
