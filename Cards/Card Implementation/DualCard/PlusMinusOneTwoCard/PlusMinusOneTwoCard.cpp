//
// Created by tomtom on 03/02/19.
//

#include "PlusMinusOneTwoCard.h"

int PlusMinusOneTwoCard::play(int currentScore, vector<Card *> &playedCards) const {
    cout << "Choose sign: " << PLUS_SIGN << SIGN_DELIMITER << MINUS_SIGN << endl;

    string sign = chooseSign();
    int input = chooseEffect();

    return (sign == PLUS_SIGN ? input : input * -1);
}

string PlusMinusOneTwoCard::chooseSign() const {
    bool invalidInput = true;
    string sign;
    while (invalidInput) {
        cin >> sign;

        invalidInput = (sign != PLUS_SIGN && sign != MINUS_SIGN);

        if (invalidInput)
            cout << "Invalid sign, please try again.";

    }
    return sign;
}

string PlusMinusOneTwoCard::getDescription() const {
    return getSignedAttribute() + "\t" + to_string(A) + string(DUAL_DELIMITER) + to_string(B);
}

string PlusMinusOneTwoCard::getSignedAttribute() const {
    return string(PLUS_SIGN) + string(SIGN_DELIMITER) + string(MINUS_SIGN);
}

PlusMinusOneTwoCard::PlusMinusOneTwoCard() : DualCard(A, B) {}


