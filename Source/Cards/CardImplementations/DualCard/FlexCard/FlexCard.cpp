//
// Created by tomtom on 03/02/19.
//

#include "FlexCard.h"

//Namespaces-------------------------------
using namespace std;

const string FlexCard::SIGN_DELIMITER = "/";


FlexCard::FlexCard() : DualCard(FlexCard::A, FlexCard::B) {}

int FlexCard::play(vector<int> &playedCards, int currentScore, int opponentScore) const {
    cout << "Choose sign: " << Card::PLUS_SIGN << FlexCard::SIGN_DELIMITER << Card::MINUS_SIGN
         << endl; //TODO extract into a method

    string sign = chooseSign();
    int input = chooseEffect();

    int value = (sign == Card::PLUS_SIGN ? 1 : -1) * input;
    //int value = (int) pow(-1.(sign != Card::PLUS_SIGN)) * input;

    return value;
}


string FlexCard::getDescription() const {
    return getSignedAttribute() + "\t" + to_string(A) + string(Card::DUAL_DELIMITER) + to_string(B);
}

string FlexCard::getSignedAttribute() const {
    return string(Card::PLUS_SIGN) + string(FlexCard::SIGN_DELIMITER) + string(Card::MINUS_SIGN);
}



