//
// Created by tomtom on 03/02/19.
//

#include "DualCard.h"


DualCard::DualCard(int left, int right) {
    if (!validInput(left) || !validInput(right))
        throw "Invalid card value."; //TODO extract this

    this->effects[0] = left <= right ? left : right;
    this->effects[1] = left <= right ? right : left;
}

int DualCard::play(int currentScore, vector<int> playedCards) const {

    int input = chooseEffect();
    cout << "You've chosen: " << this->effects[input] << endl;

    return currentScore + this->effects[input];
}

int DualCard::chooseEffect() const {
    bool invalidInput = true;
    int input = -1;

    while (invalidInput) {
        cout << "Choose an effect " << "[0 for the first choice/1 for the second choice]";
        cout << endl;
        cout << "[" << effects[0] << DUAL_DELIMITER << effects[1] << "]: ";
        cin >> input;
        invalidInput = (input != 0 && input != 1);
        if (invalidInput)
            cout << "Invalid choice, please try again." << endl << endl;
    }
    return input;
}

string DualCard::getDescription() const {
    return offsetPositiveNumber(this->effects[0]) + DUAL_DELIMITER + offsetPositiveNumber(this->effects[1]);
}


