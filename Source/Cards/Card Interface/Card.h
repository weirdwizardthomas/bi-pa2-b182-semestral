//
// Created by tomtom on 03/02/19.
//

#ifndef PAZAAK_CARD_H
#define PAZAAK_CARD_H
#endif //PAZAAK_CARD_H

//------------------------------------------------
#include <string>

//------------------------------------------------
#define LOWER_BOUND -6
#define UPPER_BOUND 6

using namespace std;

class Card {

private:
    //Methods--------------------------------------------
    virtual string getDescription() const = 0;

public:
    //Constructors-&&-Destructor-------------------------
    Card() = default;

    virtual ~Card() = default;

    virtual int getValue() const = 0;

    //Methods--------------------------------------------
    bool validInput(int value) const;

    friend ostream &operator<<(ostream &out, const Card &card);
};