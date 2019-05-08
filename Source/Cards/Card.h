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

//TODO input stream as a parameter

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

    /**
     *
     */
    void invalidSignMessage() const;

public:
    static const int LOWER_BOUND;
    static const int UPPER_BOUND;
    static const char *PLUS_SIGN;
    static const char *MINUS_SIGN;

    virtual ~Card() = default;

    /**
     * Generates card's effect's description
     * @return String representing a verbose effect of the card
     */
    virtual std::string getDescription() const = 0;

    /**
     * Puts the card's effect in play
     * @param playedCards Cards previously played by the current player
     * @param currentScore Current player's current round's score
     * @param opponentScore Opponent's current round's score
     * @return current player's score updated by playing a card
     */
    virtual int play(std::vector<int> &playedCards, int currentScore, int opponentScore) const = 0;

    /**
     * Prints the 'card''s description into the 'out' stream
     * @param out The tream into which the 'card''s description will be sent
     * @param card Card to be placed into the stream
     * @return getDescription()
     */
    friend std::ostream &operator<<(std::ostream &out, const Card &card);

};


#endif //TMPPAZAAK_CARD_H
