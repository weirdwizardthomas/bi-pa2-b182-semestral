#include "Source/Game.h"
#include "Source/Cards/CardDatabase.h"
#include "Source/MainMenu.h"

//Namespaces--------------------------------
using namespace std;


int main() {
    MainMenu mainMenu;
    mainMenu.loop();
    cout << "Exiting." << endl;
    return EXIT_SUCCESS;
}

