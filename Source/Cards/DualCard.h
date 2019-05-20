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
     * Queries the user to choose between the card's two values.
     * @return User selected card value.
     */
    int chooseEffect() const;

    /**
     * Informs the user of the @param value they have selected.
     * @param value Value to be displayed to the user.
     */
    void valueChosenMessage(int value) const;

    /**
     * Prompts the user to select between the card's two values.
     */
    void chooseValuePrompt() const;

    /**
     * Displays the possible values to select from.
     */
    void listChoices() const;

    /**
     * Informs the user that the input is not valid for the given scenario.
     */
    void invalidInputMessage() const;

public:
    static const char *DUAL_DELIMITER;

    //Constructor---------------------------
    DualCard(int left, int right);

    ~DualCard() override = default;
    //Methods-------------------------------
    /**
     * Presents the player with two values to choose from to be played.
     * @param playedCards Cards previously played by the current player.
     * @param currentScore Current player's current round's score.
     * @param opponentScore Opponent's current round's score.
     * @return One of the user selected values.
     */
    int play(std::vector<int> &playedCards, int currentScore, int opponentScore) const override;

    std::string getDescription() const override;
};


#endif //TMPPAZAAK_DUALCARD_H
