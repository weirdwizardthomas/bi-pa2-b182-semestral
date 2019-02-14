//
// Created by tomtom on 03/02/19.
//


#include "BasicCard.h"

BasicCard::BasicCard(int value) {
    if (!validInput(value))
        throw "Invalid card value.";

    this->value = value;
}

int BasicCard::play(vector<int> &playedCards, int currentScore, int opponentScore) const {
    playedCards.push_back(this->value);

    return currentScore + this->value;
}

string BasicCard::getDescription() const {
    return offsetPositiveNumber(this->value);
}

map<string, Card *> BasicCard::loadFromFile() {
    map<string, Card *> cards;

    /*TODO
     * 1. OPEN THE FILE
     * 2. READ LINES
     * 3. CHECK EACH LINE FOR VALIDATION
     * 4. IGNORE COMMENTS AND EMPTY LINES
     * 5. CREATE A CARD - CALL CONSTRUCTOR
     * 6. ADD THE CARD TO THE MAP
     * 7. RETURN MAP
     * 1,2,3,4,6,7 are same for each child
     */

    vector<string> lines = Card::getFileLines();


    return cards;
}


