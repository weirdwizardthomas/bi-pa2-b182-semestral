//
// Created by tomtom on 03/02/19.
//

#include "FlexCard.h"

using namespace std;

FlexCard::FlexCard() : DualCard(A, B) {}

int FlexCard::play(vector<int> &playedCards, int currentScore, int opponentScore) const {
    cout << "Choose sign: " << PLUS_SIGN << SIGN_DELIMITER << MINUS_SIGN << endl;

    string sign = chooseSign();
    int input = chooseEffect();

    int value = (sign == PLUS_SIGN ? 1 : -1) * input;
    //int value = (int) pow(-1.(sign != PLUS_SIGN)) * input;

    return value;
}


string FlexCard::getDescription() const {
    return getSignedAttribute() + "\t" + to_string(A) + string(DUAL_DELIMITER) + to_string(B);
}

string FlexCard::getSignedAttribute() const {
    return string(PLUS_SIGN) + string(SIGN_DELIMITER) + string(MINUS_SIGN);
}



