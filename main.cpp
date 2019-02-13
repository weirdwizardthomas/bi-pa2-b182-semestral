
#include <cmath>

#include "Source/Player/PlayerBoard/PlayerBoard.h"
#include "Source/Game/Game.h"
#include "Source/Cards/CardImplementations/BasicCard/BasicCard.h"
#include "Source/Cards/CardImplementations/DualCard/DualCard.h"
#include "Source/Cards/CardImplementations/DualCard/FlipCard/FlipCard.h"
#include "Source/Cards/CardImplementations/DualCard/FlexCard/FlexCard.h"
#include "Source/Cards/CardImplementations/DoubleCard/DoubleCard.h"

#include <map>

int generate(int i) { return static_cast<int>((i % 7) * pow(-1, i)); }


//TODO REPLACE THIS WITH FILES
map<string, Card *> getAllCards() {
    map<string, Card *> allCards;

    for (int i = -6; i <= 6; i++) {
        if (i != 0) {
            Card *dummy = new BasicCard(i);
            allCards.insert(pair<string, Card *>(dummy->getDescription(), dummy));
        }
    }

    for (int i = -6; i <= 6; i++) {
        if (i != 0) {
            for (int j = -6; j <= 6; j++) {
                if (j != 0 && i != j) {
                    Card *dummy = new DualCard(i, j);
                    allCards.insert(pair<string, Card *>(dummy->getDescription(), dummy));
                }
            }
        }
    }

    for (int i = 1; i <= 6; i++) {
        for (int j = 1; j <= 6; j++) {
            if (i != j) {
                Card *dummy = new FlipCard(i, j);
                allCards.insert(pair<string, Card *>(dummy->getDescription(), dummy));
            }
        }
    }

    Card *dummy = new FlexCard();
    allCards.insert(pair<string, Card *>(dummy->getDescription(), dummy));
    dummy = new DoubleCard();
    allCards.insert(pair<string, Card *>(dummy->getDescription(), dummy));

    return allCards;
}

//TODO PROPER EXCEPTIONS

int main() {

    string name1, name2;


    /* cout <<"Enter the name of the player:";
     cin >> name1;
     cout << "Created a player with the name " << name1 << endl;

     cout <<"Enter the name of the player:";
     cin>> name2;
     cout << "Created a player with the name " << name2 << endl;

     Game * game = new Game(new Player(name1), new Player(name2));*/

    map<string, Card *> cardMap = getAllCards();

    auto it = cardMap.begin();
    size_t i = 0;

    for (it = cardMap.begin(); it != cardMap.end(); it++)
        cout << (i < 10 ? " " : "") <<"(" << i++ << ")" << " " << (it->second)->getDescription() << endl;



    // game->play();

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

