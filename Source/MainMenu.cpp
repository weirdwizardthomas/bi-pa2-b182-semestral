//
// Created by tomtom on 05/05/19.
//

#include <iostream>
#include "MainMenu.h"
#include "Game.h"

using namespace std;

const char *MainMenu::LEFT_INDEX_WRAPPER{"("};
const char *MainMenu::RIGHT_INDEX_WRAPPER{")"};


MainMenu::MainMenu() : items({"Play locally", "Play against a computer", "Load game", "Craft a deck", "Quit"}),
                       cardDatabase(CardDatabase()) {}

size_t MainMenu::selectItem() const {
    cout << "Select a menu option: ";
    size_t choice = items.size();
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
            Game *game = new Game(new Player(getPlayerName()), new Player(getPlayerName()), cardDatabase);
            game->play();
            delete game;
            break;
        }

        case 1: {
            Game *game = new Game(new Player(getPlayerName()), new Player(getPlayerName()), cardDatabase);
            game->play();
            delete game;
            break;
        }

        case 2: {
            Game *game = Game::loadFromFile(cardDatabase);
            if (game)
                game->play();
            delete game;
            break;
        }


        case 3: {
            Deck deck(cardDatabase);
            deck.saveToFile();
            break;
        }
        default:
            return false;
    }
    return true;
}

string MainMenu::getPlayerName() const {
    string name1;
    playerNameQuery();
    cin >> name1;
    return name1;
}

void MainMenu::playerNameQuery() const { cout << "Enter the name of the player:"; }

void MainMenu::loop() const {
    do {
        Game::clearScreen(cout);
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
    cout << "Pazaak, a card game from Star Wars: Knights of the Old Republic "
         << "by Tomas Koristka - koristo1@fit.cvut.cz" << endl;
}
