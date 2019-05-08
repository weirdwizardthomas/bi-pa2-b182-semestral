//
// Created by tomtom on 03/02/19.
//

#include "Card.h"

//Namespaces--------------------------------
using namespace std;


const char *Card::PLUS_SIGN{"+"};
const char *Card::MINUS_SIGN{"-"};
const int Card::LOWER_BOUND = -10;
const int Card::UPPER_BOUND = 10;



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
            invalidSignMessage();

    }
    return sign;
}

void Card::invalidSignMessage() const { cout << "Invalid sign, please try again."; }

