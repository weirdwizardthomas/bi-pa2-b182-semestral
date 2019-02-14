//
// Created by tomtom on 03/02/19.
//

#ifndef TMPPAZAAK_BASICCARD_H
#define TMPPAZAAK_BASICCARD_H

//Libraries---------------------------------
#include <fstream>

//Headers-----------------------------------
#include "../../CardInterface/Card.h"


/**
 * Basic cards add their value to the player's current score when played.
 */
class BasicCard : public Card {

private:
    int value;

protected:
    map<string, Card *> loadFromFile() override;

public:
    explicit BasicCard(int value);
/**
 * Puts the card's effect in play
 * @param playedCards Cards previously played by the current player
 * @param currentScore Current player's current round's score
 * @param opponentScore Opponent's current round's score
 * @return currentScore incremented by the card's value
 */
    int play(vector<int> &playedCards, int currentScore, int opponentScore) const override;

public:

    string getDescription() const override;
};


#endif //TMPPAZAAK_BASICCARD_H