//Libraries---------------------------------
#include <cmath>
#include <iostream>
#include <map>

//Classes-----------------------------------
#include "Source/Player/PlayerBoard/PlayerBoard.h"
#include "Source/Game/Game.h"
#include "Source/Utilities/CardParser.h"

//Namespaces--------------------------------
using namespace std;

int main() {


    CardParser cardParser;
    map<string, Card *> cards = cardParser.loadAllCards();
    size_t i = 0;
    for (auto &card : cards)
        cout << (i < 10 ? " " : "") << "(" << i++ << ")" << " " << (card.second)->getDescription() << endl;
/*
    string name1, name2;


     cout <<"Enter the name of the player:";
     cin >> name1;
     cout << "Created a player with the name " << name1 << endl;

     cout <<"Enter the name of the player:";
     cin>> name2;
     cout << "Created a player with the name " << name2 << endl;

     Game * game = new Game(new Player(name1), new Player(name2));


    // game->play();*/

    cout << "--------------------" << endl;

}

