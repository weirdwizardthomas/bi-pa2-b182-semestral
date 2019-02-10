//
// Created by tomtom on 10/02/19.
//

#ifndef PAZAAK_CARDPARSER_H
#define PAZAAK_CARDPARSER_H

#include <cstdlib>
#include <string>
#include <vector>
#include <fstream>
#include <exception>

#include "../Cards/CardInterface/Card.h"

using namespace std;

#define FOLDER_PATH "Data/Cards/"

class CardParser {

public:
    static vector<Card *> loadCards();
};


#endif //PAZAAK_CARDPARSER_H
