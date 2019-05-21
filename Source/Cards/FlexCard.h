//
// Created by tomtom on 03/02/19.
//

#ifndef TMPPAZAAK_PLUSMINUSONETWOCARD_H
#define TMPPAZAAK_PLUSMINUSONETWOCARD_H


#include "DualCard.h"


/**
 * A child of @class DualCard
 * A special case of the @class DualCard; offers a choice of one of four fixed values: +1,-1,+2,-2
 */
class FlexCard : public DualCard {
private:
    std::string getSignedAttribute() const;

    void chooseSignPrompt() const;

public:
    static const int LEFT;
    static const int RIGHT;
    static const char *SIGN_DELIMITER;

    FlexCard();

    //Methods-------------------------------
    /**
     * Presents the player with a choice of sign and LEFT-RIGHT to be played
     * @param playedCards Cards previously played by the current player
     * @param currentScore Current player's current round's score
     * @param opponentScore Opponent's current round's score
     * @return A positive or negative LEFT/RIGHT value
     */
    int play(std::vector<int> &playedCards, int currentScore, int opponentScore) const override;

    std::string getDescription() const override;

};

#endif //TMPPAZAAK_PLUSMINUSONETWOCARD_H
