//Libraries---------------------------------
#include <cmath>
#include <iostream>
#include <map>
#include <typeinfo>

//Classes-----------------------------------
#include "Source/Game.h"
#include "Source/Cards/CardDatabase.h"
#include "Source/MainMenu.h"

//Definitions-------------------------------
#define LEFT_INDEX_WRAPPER "("
#define RIGHT_INDEX_WRAPPER ")"

//Namespaces--------------------------------
using namespace std;

int main() {
    MainMenu mainMenu;
    mainMenu.loop();
    return EXIT_SUCCESS;

}

