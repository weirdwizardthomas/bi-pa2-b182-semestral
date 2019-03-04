//Libraries---------------------------------
#include <cmath>
#include <iostream>
#include <map>

//Classes-----------------------------------
#include "Source/Player/PlayerBoard/PlayerBoard.h"
#include "Source/Game/Game.h"
#include "Source/Utilities/Parsers/CardParser/CardParser.h"

//Definitions-------------------------------
#define LEFT_INDEX_WRAPPER "("
#define RIGHT_INDEX_WRAPPER ")"

//Namespaces--------------------------------
using namespace std;

int main() {

    CardParser cardParser;
    map<string, Card *> cards = cardParser.loadAllCards();


    /*//Main menu--------------------------------------------
    cout << "Pazaak, a game from the Old Republic, implemented by weirdwizardtom:koristo1@fit.cvut.cz" << endl;
*/
    /* size_t menuIndex = 0;

     cout << LEFT_INDEX_WRAPPER << menuIndex++ << RIGHT_INDEX_WRAPPER << " Play" << endl;
     cout << LEFT_INDEX_WRAPPER << menuIndex++ << RIGHT_INDEX_WRAPPER << " Craft a deck" << endl;
     cout << LEFT_INDEX_WRAPPER << menuIndex++ << RIGHT_INDEX_WRAPPER << " Quit" << endl;
     size_t menuChoice = menuIndex;
 */
    /*  //Menu item selection----------------------------------
      cout << "Select a menu option: ";
      while (menuChoice >= menuIndex) {
          cin >> menuChoice;
          if (menuChoice >= menuIndex)
              cout << "Invalid choice, please select an option in range 0-" << menuIndex - 1 << endl;
      }

      switch (menuChoice) {
          case 0:
              break;
          case 1: {
              Deck deck = Deck(cards);
              deck.saveToFile();
              break;
          }
          case 2: {
          }
              for (auto &card : cards)
                  free(card.second);

              return EXIT_SUCCESS;
      }

      //can do a switch whose default value is call of the method again with a warning*/

    string name1, name2;


    cout << "Enter the name of the player:";
    cin >> name1;
    cout << "Created a player with the name " << name1 << endl;
    cout << "Enter the name of the player:";
    cin >> name2;
    cout << "Created a player with the name " << name2 << endl;

    Game *game = new Game(new Player(name1), new Player(name2), cards);

    game->play();

    for (auto &card : cards)
        free(card.second);


    return EXIT_SUCCESS;

}

