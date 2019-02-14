//
// Created by tomtom on 03/02/19.
//

#include "Card.h"

ostream &operator<<(ostream &out, const Card &card) {
    out << card.getDescription();

    return out;
}

bool Card::validInput(int x) const {
    return (x >= LOWER_BOUND && x <= UPPER_BOUND);
}

string Card::offsetPositiveNumber(int x) const {
    return ((x < 0 ? "" : PLUS_SIGN) + to_string(x));
}

string Card::chooseSign() const {
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

