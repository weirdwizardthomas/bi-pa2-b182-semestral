//
// Created by tomtom on 03/02/19.
//

#include "Card.h"

ostream &operator<<(ostream &out, const Card &card) {

    out << card.getDescription();

    return out;
}

bool Card::validInput(int value) const {
    return (value <= UPPER_BOUND && value >= LOWER_BOUND);
}
