
#include <cmath>
#include "Source/Player/PlayerBoard/PlayerBoard.h"
#include "Source/Utilities/CardParser.h"


int generate(int i) { return static_cast<int>((i % 7) * pow(-1, i)); }

//TODO PROPER EXCEPTIONS

int main() {

    vector<Card *> cards = CardParser::loadCards();

    for(Card * card : cards)
        cout << *card << endl;

/*
    PlayerBoard *playerBoard1 = new PlayerBoard();

    //Generate basic cards
    for (int i = 0; i < 20; i++)
        playerBoard1->addPlayedCard(new BasicCard(generate(i)));

    //Generate dual cards
    for (int i = 0; i < 20; i++)
        playerBoard1->addPlayedCard(new DualCard(generate(i), generate(20 - i)));

    //Generate flex cards
    for (int i = 0; i < 2; i++)
        playerBoard1->addPlayedCard(new FlexCard());

    //Generate flip cards
    for (int i = 1; i < 6; i++)
        playerBoard1->addPlayedCard(new FlipCard(i, generate(6 - i)));

    //Generate double cards
    for (int i = 0; i < 6; i++)
        playerBoard1->addPlayedCard(new DoubleCard());

    cout << "--------------------" << endl;


    int currentScore = playerBoard1->getCurrentScore();
    vector<Card *> playedCards = playerBoard1->getPlayedCards();

    for (Card *card : playerBoard1->getPlayedCards())
        cout << *card << endl;
*/

    cout << "--------------------" << endl;

}

