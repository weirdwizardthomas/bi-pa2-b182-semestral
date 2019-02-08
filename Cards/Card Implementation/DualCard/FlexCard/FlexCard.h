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


class FlexCard : public DualCard {
private:
    string getSignedAttribute() const;

    string chooseSign() const;

public:
    //Constructor---------------------------
    FlexCard();

    //Methods-------------------------------
    int play(int currentScore, vector<int> playedCards) const override;

    string getDescription() const override;

};


#endif //TMPPAZAAK_PLUSMINUSONETWOCARD_H
