//
// Created by tomtom on 03/02/19.
//

#ifndef TMPPAZAAK_BASICCARD_H
#define TMPPAZAAK_BASICCARD_H

//Libraries---------------------------------
#include <fstream>

//Headers-----------------------------------
#include "Card.h"

/**
 * Basic cards add their value to the player's current score when played.
 */
class BasicCard : public Card {

private:
    int value;

public:
    explicit BasicCard(int value);

    ~BasicCard() override = default;

    std::string getDescription() const override;

    /**
     * Gets the card's 'value'.
     * @param playedCards Cards previously played by the current player.
     * @param currentScore Current player's current round's score.
     * @param opponentScore Opponent's current round's score.
     * @return Card's Value.
     */
    int play(std::vector<int> &playedCards, int currentScore, int opponentScore) const override;

    /**
     * Gets the card's 'value' without taking any context in regard.
     * @return Card's value
     */
    int play() const;

};


#endif //TMPPAZAAK_BASICCARD_H
