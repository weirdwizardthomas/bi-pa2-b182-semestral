//
// Created by tomtom on 03/02/19.
//

#include "Card.h"

ostream &operator<<(ostream &out, const Card &card) {
    out << card.getDescription();

    return out;
}

bool Card::validInput(int value) const {
    return (value >= LOWER_BOUND && value <= UPPER_BOUND);
}

string Card::offsetPositiveNumber(int number) const {
    return ((number < 0 ? "" : PLUS_SIGN) + to_string(number));
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
