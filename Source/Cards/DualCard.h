//
// Created by tomtom on 03/02/19.
//

#ifndef TMPPAZAAK_DUALCARD_H
#define TMPPAZAAK_DUALCARD_H


//Libraries---------------------------------
#include <iostream>
#include <cstdlib>
#include <cmath>
//Classes-----------------------------------
#include "Card.h"

/**
 * Dual cards present the current player with two effects to choose from when played
 */
class DualCard : public Card {

protected:
    //Attributes----------------------------
    std::pair<int, int> values;

    /**
     * queries the user for a card effect choice
     * @return numeric value of the chosen effect
     */
    int chooseEffect() const;

    void valueChosenMessage(int value) const;

    void chooseEffectPrompt() const;

    void effectChoicesMessage() const;

    void invalidInputMessage() const;

public:
    static const char *DUAL_DELIMITER;

    //Constructor---------------------------
    DualCard(int left, int right);

    ~DualCard() override = default;
    //Methods-------------------------------
    /**
     * Presents the player with two values to choose from to be played
     * @param playedCards Cards previously played by the current player
     * @param currentScore Current player's current round's score
     * @param opponentScore Opponent's current round's score
     * @return current player's score updated by playing a card
     */
    int play(std::vector<int> &playedCards, int currentScore, int opponentScore) const override;

    std::vector<int> getValues() const override;

    std::string getDescription() const override;

};


#endif //TMPPAZAAK_DUALCARD_H
