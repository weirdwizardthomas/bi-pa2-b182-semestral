//
// Created by tomtom on 03/02/19.
//

#ifndef TMPPAZAAK_CARD_H
#define TMPPAZAAK_CARD_H

//Libraries---------------------------------
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <map>

//Definitions-------------------------------
#define LOWER_BOUND -10
#define UPPER_BOUND 10
#define DUAL_DELIMITER "|"
#define PLUS_SIGN "+"
#define MINUS_SIGN "-"

class Card {

protected:
    /**
     *
     * @param x Integer to be checked as a valid card value
     * @return Whether the input satisfies the constraint
     */
    bool validInput(int x) const;

    /**
     *
     * @param x Integer to be formatted based on its sign
     * @return the input number with a sign (+ for positive, -for negative)
     */
    std::string offsetPositiveNumber(int x) const;

    /**
     * queries the user to choose between a positive and negative sign - used at flip cards,...
     * @return chosen sign
     */
    std::string chooseSign() const;

public:

    /**
     * Puts the card's effect in play
     * @param playedCards Cards previously played by the current player
     * @param currentScore Current player's current round's score
     * @param opponentScore Opponent's current round's score
     * @return current player's score updated by playing a card
     */
    virtual int play(std::vector<int> &playedCards, int currentScore, int opponentScore) const = 0;

    /**
     * generates card's effect's description
     * @return a verbose effect of the card
     */
    virtual std::string getDescription() const = 0;

    /**
     *
     * @param out the std::ostream
     * @param card card to be placed into the stream
     * @return getDescription()
     */

    friend std::ostream &operator<<(std::ostream &out, const Card &card);
};


#endif //TMPPAZAAK_CARD_H
