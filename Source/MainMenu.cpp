//
// Created by tomtom on 05/05/19.
//

#include <iostream>
#include "MainMenu.h"
#include "Game.h"

using namespace std;

const char *MainMenu::LEFT_INDEX_WRAPPER{"("};
const char *MainMenu::RIGHT_INDEX_WRAPPER{")"};


MainMenu::MainMenu() : items({"Play", "Load game", "Craft a deck", "Quit"}), database(CardDatabase()) {}

size_t MainMenu::selectItem() const {
    cout << "Select a menu option: ";
    size_t choice = 0;
    while (choice >= items.size()) {
        cin >> choice;
        if (choice >= items.size()) {
            cout << "Invalid choice, please select an option in range 0-" << items.size() - 1 << endl;
            cout << "Select a menu option: ";
        }
    }
    return choice;
}

bool MainMenu::invoke(size_t itemIndex) const {
    switch (itemIndex) {
        case 0: {
            string name1, name2;
            cout << "Enter the name of the player:";
            cin >> name1;
            cout << "Enter the name of the player:";
            cin >> name2;
            Game *game = new Game(new Player(name1), new Player(name2), database);
            game->play();
            delete game;
            break;
        }
        case 1: {
            Game *game = Game::loadFromFile();
            game->play();
            delete game;
            break;
        }
        case 2: {
            Deck deck(database);
            deck.saveToFile();
            break;
        }
        default:
            return true;
    }
}

void MainMenu::loop() const {
    Game::clearScreen(cout); //TODO move from game to main menu
    do {
        printHeader();
        listItems();
    } while (invoke(selectItem()));
}


void MainMenu::listItems() const {
    size_t i = 0;
    for (const auto &item : items)
        cout << LEFT_INDEX_WRAPPER << i++ << RIGHT_INDEX_WRAPPER << " " << item << endl;
}

void MainMenu::printHeader() const {
    cout << "Pazaak, a card game from Star Wars: Knights of the Old Republic"
         << "by Tomas Koristka - koristo1@fit.cvut.cz" << endl;
}
