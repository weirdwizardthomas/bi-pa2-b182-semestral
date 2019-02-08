//
// Created by tomtom on 03/02/19.
//

#ifndef TMPPAZAAK_CARD_H
#define TMPPAZAAK_CARD_H


//Libraries---------------------------------
#include <string>
#include <vector>

//Namespaces--------------------------------
using namespace std;


//Definitions-------------------------------
#define LOWER_BOUND -6
#define UPPER_BOUND 6
#define DUAL_DELIMITER "|"
#define PLUS_SIGN "+"
#define MINUS_SIGN "-"

class Card {

protected:
    bool validInput(int value) const;

    string offsetPositiveNumber(int number) const;

public:

    virtual int play(int currentScore, vector<int> playedCards) const = 0;

    virtual string getDescription() const = 0;

    friend ostream &operator<<(ostream &out, const Card &card);


};


#endif //TMPPAZAAK_CARD_H
