//
// Created by tomtom on 05/05/19.
//

#ifndef PAZAAK_MAINMENU_H
#define PAZAAK_MAINMENU_H

#include <list>
#include <string>
#include <vector>
#include <functional>
#include "Cards/CardDatabase.h"

class MainMenu {
private:
    std::list<std::string> items;
    CardDatabase cardDatabase;

    /**
     * Displays all the 'items' choices to the user.
     */
    void listItems() const;

    /**
     * Queries the user to select an index in the 'items' container's range.
     * @return index of the selected item
     */
    size_t selectItem() const;

    /**
     * Triggers a specific item from the 'items' container, e.g. load a game.
     * @param itemIndex Specific case's number to trigger.
     * @return False if the shutdown('Quit') option was selected, True otherwise.
     */
    bool invoke(size_t itemIndex) const;

public:
    static const char LEFT_INDEX_WRAPPER;
    static const char RIGHT_INDEX_WRAPPER;

    MainMenu();

    /**
     * Shows the main menu's 'items' and queries the user to pick one of the items.
     * Loops forever until the 'Quit' item is selected.
     * */
    void loop() const;

    /**
     * Displays the basic information about the project to the user.
     */
    void printHeader() const;

    /**
     * Queries the user to input a name to represent them within the programme.
     */
    void playerNameQuery() const;

    /**
     * Gets a string representing the user in the game.
     * @return
     */
    std::string getPlayerName() const;
};


#endif //PAZAAK_MAINMENU_H
