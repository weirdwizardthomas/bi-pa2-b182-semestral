#include <iostream>
#include <cmath>
#include <vector>

#include "Cards/Card Interface/Card.h"
#include "Cards/Card Implementation/BasicCard/BasicCard.h"
#include "Cards/Card Implementation/DualCard/DualCard.h"
#include "Cards/Card Implementation/DualCard/FlexCard/FlexCard.h"
#include "PlayerBoard.h"
#include "Cards/Card Implementation/DualCard/FlipCard/FlipCard.h"

int generate(int i) { return static_cast<int>((i % 7) * pow(-1, i)); }

int main() {

    PlayerBoard *playerBoard1 = new PlayerBoard();


    //Generate dual cards
    for (int i = 0; i < 20; i++)
        playerBoard1->addPlayedCard(new DualCard(generate(i), generate(20 - i)));


    //Generate basic cards
    for (int i = 0; i < 20; i++)
        playerBoard1->addPlayedCard(new BasicCard(generate(i)));

    //Generate flex cards
    for (int i = 0; i < 2; i++)
        playerBoard1->addPlayedCard(new FlexCard());

    //Generate flip cards
    for (int i = 1; i < 6; i++)
        playerBoard1->addPlayedCard(new FlipCard(i, generate(6 - i)));

    cout << "--------------------" << endl;


    int currentScore = playerBoard1->getCurrentScore();
    vector<Card *> playedCards = playerBoard1->getPlayedCards();

    for (Card *card : playerBoard1->getPlayedCards())
        cout << *card << endl;


    cout << "--------------------" << endl;

}

