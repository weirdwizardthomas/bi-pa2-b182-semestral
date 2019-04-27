//
// Created by tomtom on 03/02/19.
//

#include "Card.h"

//Namespaces--------------------------------
using namespace std;

const std::string Card::DUAL_DELIMITER = "|";
const std::string Card::PLUS_SIGN = "+";
const std::string Card::MINUS_SIGN = "-";


ostream &operator<<(ostream &out, const Card &card) {
    out << card.getDescription();

    return out;
}

bool Card::validInput(int x) const { return (x >= Card::LOWER_BOUND && x <= Card::UPPER_BOUND); }

string Card::offsetPositiveNumber(int x) const { return ((x < 0 ? "" : Card::PLUS_SIGN) + to_string(x)); }

string Card::chooseSign() const {
    bool invalidInput = true;
    string sign;
    while (invalidInput) {
        cin >> sign;

        invalidInput = (sign != Card::PLUS_SIGN && sign != Card::MINUS_SIGN);

        if (invalidInput)
            cout << "Invalid sign, please try again.";

    }
    return sign;
}

