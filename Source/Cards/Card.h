//
// Created by tomtom on 03/02/19.
//

#ifndef TMPPAZAAK_CARD_H
#define TMPPAZAAK_CARD_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <map>

/**
 * Represents an interface for playable Cards.
 */
class Card {

protected:
    /**
     * Checks whether a number satisfies all the constraints.
     * @param[in] x Integer to be checked as a valid card value
     * @return True if the input satisfies the constraints, false otherwise.
     */
    bool validInput(int x) const;

    /**
     * Uniforms a numbers's text format by prefixing it with a PLUS_SIGN if the number is positive.
     * @param[in] x Integer to be formatted based on its sign.
     * @return the input number with a sign (+ for positive, -for negative)
     */
    std::string offsetPositiveNumber(int x) const;

    /**
     * Queries the user to choose between a positive and negative sign.
     * @return PLUS_SIGN or MINUS_SIGN.
     */
    std::string chooseSign() const;

    /**
     * Informs the user that the input does not match either of PLUS_SIGN, MINUS_SIGN.
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
     * @param[in,out] playedCards Cards previously played by the current player.
     * @param[in] currentScore Current player's current round's score.
     * @param[in] opponentScore Opponent's current round's score.
     * @return Card's value, 0 if the card doesn't add a new value.
     */
    virtual int play(std::vector<int> &playedCards, int currentScore, int opponentScore) const = 0;

    /**
     * Prints the Card's description into the output stream
     * @param[in,out] out Stream into which the  Card's description will be sent.
     * @param[in] card Card to be placed into the stream.
     * @return @param out containing Card's description.
     */
    friend std::ostream &operator<<(std::ostream &out, const Card &card);

};


#endif //TMPPAZAAK_CARD_H
