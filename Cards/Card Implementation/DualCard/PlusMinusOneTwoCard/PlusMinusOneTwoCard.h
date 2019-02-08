//
// Created by tomtom on 03/02/19.
//

#ifndef TMPPAZAAK_PLUSMINUSONETWOCARD_H
#define TMPPAZAAK_PLUSMINUSONETWOCARD_H

//Classes-----------------------------------
#include "../DualCard.h"

//Definitions------------------------------
#define SIGN_DELIMITER "/"
#define A 1
#define B 2


class PlusMinusOneTwoCard : public DualCard {
private:
    string getSignedAttribute() const;

public:
    //Constructor---------------------------
    PlusMinusOneTwoCard();

    //Methods-------------------------------
    int play(int currentScore, vector<Card *> &playedCards) const override;

    string getDescription() const override;

    string chooseSign() const;
};


#endif //TMPPAZAAK_PLUSMINUSONETWOCARD_H
