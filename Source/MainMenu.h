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

    void listItems() const;

    size_t selectItem() const;

    bool invoke(size_t itemIndex) const;

public:
    static const char LEFT_INDEX_WRAPPER;
    static const char RIGHT_INDEX_WRAPPER;

    MainMenu();

    void loop() const;

    void printHeader() const;

    void playerNameQuery() const;

    std::string getPlayerName() const;
};


#endif //PAZAAK_MAINMENU_H
