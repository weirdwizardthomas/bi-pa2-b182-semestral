//
// Created by tomtom on 05/05/19.
//

#include <iostream>

#include "MainMenu.h"
#include "Game.h"
#include "Player/Player/HumanPlayer.h"
#include "Player/Player/ComputerPlayer.h"
#include "Utilities/Exceptions.h"

using namespace std;

const char MainMenu::LEFT_INDEX_WRAPPER = '(';
const char MainMenu::RIGHT_INDEX_WRAPPER = ')';
const char MainMenu::NEWLINE = '\n';

MainMenu::MainMenu() : items({"Play locally", "Play against a computer", "Load game", "Craft a deck", "Quit"}),
                       cardDatabase(CardDatabase()) {}

//TODO if invalid skip the input till newline
size_t MainMenu::selectItem() const {
    cout << "Select a menu option: ";
    size_t choice = items.size();
    while (choice >= items.size()) {
        cin >> choice;

        if (cin.fail() || choice >= items.size()) {
            cin.clear();
            //ignores the entire cin until a newline is encountered
            cin.ignore(numeric_limits<streamsize>::max(), MainMenu::NEWLINE);

            cout << "Invalid choice, please select an option in range 0-" << items.size() - 1 << endl;
            cout << "Select a menu option: ";
            choice = items.size();
            cin >> choice;
        }
    }
    return choice;
}

bool MainMenu::invoke(size_t itemIndex) const {
    Player *playerOne = nullptr;
    Player *playerTwo = nullptr;
    try {
        switch (itemIndex) {
            case 0: {
                playerOne = new HumanPlayer(getPlayerName());
                playerTwo = new HumanPlayer(getPlayerName());

                Game game(playerOne, playerTwo, cardDatabase);
                game.play();
                break;
            }

            case 1: {
                playerOne = new HumanPlayer(getPlayerName());
                playerTwo = new ComputerPlayer(playerOne);
                Game game(playerOne, playerTwo, cardDatabase);
                game.play();
                break;
            }

            case 2: {
                Game game = Game::loadFromFile(cardDatabase);
                game.play();
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
    }
    catch (CannotOpenDirectory &e) {
        cout << "Error opening " << e.what() << " directory." << endl;
        delete playerOne;
        delete playerTwo;
        return false;
    }
    catch (InvalidFileException &e) {
        cout << "Error accessing " << e.what() << "." << endl;
        delete playerOne;
        delete playerTwo;
        return false;
    }
    return true;
}

string MainMenu::getPlayerName() const {
    string name;
    playerNameQuery();
    cin >> name;
    return name;
}

void MainMenu::loop() const {

    do {
        Game::clearScreen(cout);
        printHeader();
        listItems();
    } while (invoke(selectItem()));
}


void MainMenu::playerNameQuery() const { cout << "Enter the name of the player:"; }

void MainMenu::listItems() const {
    size_t i = 0;
    for (const auto &item : items)
        cout << LEFT_INDEX_WRAPPER << i++ << RIGHT_INDEX_WRAPPER << " " << item << endl;
}

void MainMenu::printHeader() const {
    cout << "Pazaak, a card game from Star Wars: Knights of the Old Republic "
         << "by Tomas Koristka - koristo1@fit.cvut.cz" << endl;
}
