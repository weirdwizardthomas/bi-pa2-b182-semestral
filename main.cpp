#include <iostream>
#include <cmath>
#include <cstdlib>
#include <vector>

#include "Cards/Card Interface/Card.h"
#include "Cards/Card Implementation/BasicCard/BasicCard.h"
#include "Cards/Card Implementation/DualCard/DualCard.h"
#include "PlayerBoard.h"
#include "Cards/Card Implementation/DualCard/PlusMinusOneTwoCard/PlusMinusOneTwoCard.h"


int generate(int i) { return static_cast<int>((i % 7) * pow(-1, i)); }

int main() {

    PlayerBoard *playerBoard1 = new PlayerBoard();


    //Generate dual cards
    for (int i = 0; i < 20; i++)
        playerBoard1->addPlayedCard(new DualCard(generate(i), generate(20 - i)));


    //Generate basic cards
    for (int i = 0; i < 20; i++)
        playerBoard1->addPlayedCard(new BasicCard(generate(i)));

    //Generate +-12 cards
    for(int i = 0; i <2; i++)
        playerBoard1->addPlayedCard(new PlusMinusOneTwoCard());


    cout << "--------------------" << endl;


    int currentScore = playerBoard1->getCurrentScore();
    vector<Card *> playedCards = playerBoard1->getPlayedCards();

    for (Card *card : playerBoard1->getPlayedCards())
        cout << *card << endl;


    cout << "--------------------" << endl;

}

