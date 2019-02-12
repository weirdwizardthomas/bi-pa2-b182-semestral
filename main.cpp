
#include <cmath>
#include "Source/Player/PlayerBoard/PlayerBoard.h"
#include "Source/Game/Game.h"
#include "Source/Cards/CardImplementations/BasicCard/BasicCard.h"

#include <map>

int generate(int i) { return static_cast<int>((i % 7) * pow(-1, i)); }

map<string, Card *>  getAllCards(){
    map<string, Card *> allCards;

    for(int i = -6; i <= 6; i++)
    {
        Card * dummy = new BasicCard(i);
        allCards.insert(pair<string, Card*>(dummy->getDescription(),dummy));
    }

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

    for(it = cardMap.begin(); it != cardMap.end(); it++)
        cout << *(it->second) << endl;

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

