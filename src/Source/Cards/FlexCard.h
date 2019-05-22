//
// Created by tomtom on 03/02/19.
//

#ifndef TMPPAZAAK_PLUSMINUSONETWOCARD_H
#define TMPPAZAAK_PLUSMINUSONETWOCARD_H


#include "DualCard.h"


/**
 * Offers a choice of one of four fixed values: +1,-1,+2,-2
 */
class FlexCard : public DualCard {
private:
    //Messages-and-prompts-----------------------------------------------
    /**
     * Constructs a string containing both signs split by FlexCard::SIGN_DELIMITER
     * @return string containing either sign
     */
    std::string getSignedSymbols() const;

    /**
     * Prompts the user to select a sign for the card's value
     */
    void chooseSignPrompt() const;

public:
    static const int LEFT;
    static const int RIGHT;
    static const char *SIGN_DELIMITER;

    /**
     * Constructs an instance with FlexCard::LEFT and FlexCard::RIGHT as its two member values
     */
    FlexCard();

    std::string getDescription() const override;

    /**
     * Presents the player with a choice of sign and FlexCard::LEFT or FlexCard::RIGHT to be played
     * @param[in] playedCards Cards previously played by the current player
     * @param[in] currentScore Current player's current round's score
     * @param[in] opponentScore Opponent's current round's score
     * @return A positive or negative FlexCard::LEFT or FlexCard::RIGHT value
     */
    int play(std::vector<int> &playedCards, int currentScore, int opponentScore) const override;


};

#endif //TMPPAZAAK_PLUSMINUSONETWOCARD_H
