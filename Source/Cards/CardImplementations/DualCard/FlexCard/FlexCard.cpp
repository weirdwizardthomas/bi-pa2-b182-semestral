//
// Created by tomtom on 03/02/19.
//

#include "FlexCard.h"

FlexCard::FlexCard() : DualCard(A, B) {}

int FlexCard::play(vector<int> &playedCards, int currentScore, int opponentScore) const {
    cout << "Choose sign: " << PLUS_SIGN << SIGN_DELIMITER << MINUS_SIGN << endl;

    string sign = chooseSign();
    int input = chooseEffect();


    int value = sign == PLUS_SIGN ? input : input * -1;
    playedCards.push_back(value);
    return currentScore + value;
}



string FlexCard::getDescription() const {
    return getSignedAttribute() + "\t" + to_string(A) + string(DUAL_DELIMITER) + to_string(B);
}

string FlexCard::getSignedAttribute() const {
    return string(PLUS_SIGN) + string(SIGN_DELIMITER) + string(MINUS_SIGN);
}



