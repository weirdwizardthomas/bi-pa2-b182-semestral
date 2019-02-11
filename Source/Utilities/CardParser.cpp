//
// Created by tomtom on 10/02/19.
//

#include <sstream>
#include "CardParser.h"

//TODO FIX THIS SHITE
//TODO LEARN HOW TO PASS CLASS TYPE AS A PARAMETER AND THEN EXTRACT THE METHOD TO A SINGLE ONE
vector<Card *> CardParser::loadCards() {
   /* string filenames[] = {"BasicCards", "DoubleCards", "DualCards", "FlexCards", "FlipCards"};
    vector<Card *> cards;


    //BasicCards---------------------------
    string filePath = FOLDER_PATH + filenames[0];


    ifstream myFile();

    myFile.open(filePath);

    if(!myFile.is_open())
        throw "File not found"; //TODO LEARN EXCEPTIONS AND REPLACE

    string line;
    while(getline(myFile,line))
    {
        stringstream iss(line);
        int value;
        if(!(iss >> value ))
            throw "NaN"; //TODO LEARN EXCEPTIONS IN CPP AND REPLACE

        cards.push_back(new BasicCard(value));
    }

    myFile.close();
    //--------------------------------------
*/
    return vector<Card *>();
}
