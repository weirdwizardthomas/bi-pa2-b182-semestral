//
// Created by tomtom on 03/02/19.
//

#include "BasicCard.h"


BasicCard::BasicCard(int value) {
    if (!validInput(value))
        throw "Invalid argument in card creation.";

    this->value = value;
}

BasicCard::BasicCard(BasicCard &source) {
    this->value = source.getValue();
}

int BasicCard::getValue() {
    return this->value;
}

string BasicCard::getDescription() {
    return this->description;
}
