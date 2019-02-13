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
#include "../../CardInterface/Card.h"
//Namespaces--------------------------------
using namespace std;

/**
 * Dual cards present the current player with two effects to choose from when played
 */
class DualCard : public Card {

protected:
    //Attributes----------------------------
    int effects[2];

    /**
     * queries the user for a card effect choice
     * @return numeric value of the chosen effect
     */
    int chooseEffect() const;

public:
    //Constructor---------------------------
    DualCard(int left, int right);

    //Methods-------------------------------
   /**
    * Presents the player with two values to choose from to be played
    * @param playedCards Cards previously played by the current player
    * @param currentScore Current player's current round's score
    * @param opponentScore Opponent's current round's score
    * @return current player's score updated by playing a card
    */
    int play(vector<int> &playedCards, int currentScore, int opponentScore) const override;

    string getDescription() const override;

};


#endif //TMPPAZAAK_DUALCARD_H
