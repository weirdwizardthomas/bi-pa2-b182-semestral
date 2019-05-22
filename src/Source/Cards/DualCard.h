//
// Created by tomtom on 03/02/19.
//

#ifndef TMPPAZAAK_DUALCARD_H
#define TMPPAZAAK_DUALCARD_H


#include <iostream>
#include <cstdlib>
#include <cmath>

#include "Card.h"


/**
 * Offers a choice of two different values when played
 */
class DualCard : public Card {

protected:
    //Attributes---------------------------------------------------------
    std::pair<int, int> values;

    //Messages-and-prompts-----------------------------------------------
    /**
     * Queries the user to choose between the card's DualCard::values
     * @return User selected card value
     */
    int chooseEffect() const;

    /**
     * Informs the user of the value they have selected
     * @param[in] value Value to be displayed to the user
     */
    void valueChosenMessage(int value) const;

    /**
     * Prompts the user to select between the card's two DualCard::values
     */
    void chooseValuePrompt() const;

    /**
     * Displays the possible DualCard::values to select from
     */
    void listChoices() const;

    /**
     * Informs the user that the input is not valid for the given scenario
     */
    void invalidInputMessage() const;

public:
    static const char *DUAL_DELIMITER;

    /**
     * Creates an instance with two values as its members
     * @param[in] left First value to be added to the instance
     * @param[in] right Second value to be added to the instance
     */
    DualCard(int left, int right);

    ~DualCard() override = default;

    /**
     * Presents the player with two DualCard::values to choose from to be played
     * @param[in] playedCards Cards previously played by the current player
     * @param[in] currentScore Current player's current round's score
     * @param[in] opponentScore Opponent's current round's score
     * @return One of the user selected values
     */
    int play(std::vector<int> &playedCards, int currentScore, int opponentScore) const override;

    std::string getDescription() const override;
};


#endif //TMPPAZAAK_DUALCARD_H
