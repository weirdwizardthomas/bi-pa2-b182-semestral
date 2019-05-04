//
// Created by tomtom on 03/02/19.
//

#include "DualCard.h"

//Namespaces--------------------------------
using namespace std;

const std::string DualCard::DUAL_DELIMITER = "|";

DualCard::DualCard(int left, int right) : values({left, right}) {
    if (!validInput(left) || !validInput(right))
        throw invalid_argument("Invalid Dual Card value");

    if (abs(values.first) <= abs(values.second))
        swap(values.first, values.second);
}

int DualCard::play(vector<int> &playedCards, int currentScore, int opponentScore) const {

    int value = chooseEffect() == 0 ? values.first : values.second;
    valueChosenMessage(value);
    return value;
}

void DualCard::valueChosenMessage(int value) const { cout << "You've chosen: " << value << endl; }

int DualCard::chooseEffect() const {
    bool invalidInput = true;
    int input = -1;

    while (invalidInput) {
        chooseEffectPrompt();
        effectChoicesMessage();
        cin >> input;
        invalidInput = (input != 0 && input != 1);
        if (invalidInput)
            invalidInputMessage();
    }
    return input;
}

string DualCard::getDescription() const {
    return Card::offsetPositiveNumber(values.first) + " " +
           DualCard::DUAL_DELIMITER + " " +
           Card::offsetPositiveNumber(values.second);
}

void DualCard::invalidInputMessage() const { cout << "Invalid choice, please try again." << endl << endl; }

void DualCard::effectChoicesMessage() const { cout << "[" << values.first << DUAL_DELIMITER << values.second << "]: "; }

void DualCard::chooseEffectPrompt() const {
    cout << "Choose an effect [0 for the first choice/1 for the second choice]" << endl;
}

