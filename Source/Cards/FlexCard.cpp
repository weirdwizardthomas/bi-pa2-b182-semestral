//
// Created by tomtom on 03/02/19.
//

#include "FlexCard.h"

//Namespaces-------------------------------
using namespace std;


const int FlexCard::LEFT = 1;
const int FlexCard::RIGHT = 2;
const char *FlexCard::SIGN_DELIMITER{"/"};

FlexCard::FlexCard() : DualCard(FlexCard::LEFT, FlexCard::RIGHT) {}

int FlexCard::play(std::vector<int> &playedCards, int currentScore, int opponentScore) const {
    chooseSignPrompt();

    return (chooseSign() == Card::PLUS_SIGN ? 1 : -1) * chooseEffect();
}

string FlexCard::getDescription() const {
    return getSignedAttribute() + "\t" + to_string(LEFT) + string(DualCard::DUAL_DELIMITER) + to_string(RIGHT);
}

string FlexCard::getSignedAttribute() const {
    return string(Card::PLUS_SIGN) + string(FlexCard::SIGN_DELIMITER) + string(Card::MINUS_SIGN);
}

void FlexCard::chooseSignPrompt() const {
    cout << "Choose sign: " << PLUS_SIGN << SIGN_DELIMITER << MINUS_SIGN << endl;
}

