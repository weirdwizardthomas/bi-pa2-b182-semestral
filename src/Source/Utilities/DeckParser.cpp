//
// Created by tomtom on 03/05/19.
//

#include <list>
#include "DeckParser.h"
#include "Exceptions.h"
#include "../MainMenu.h"

using namespace std;

const char *DeckParser::FOLDER_DELIMITER{"/"};
const char *DeckParser::CARD_DESCRIPTION_DELIMITER{": "};
const char *DeckParser::DECKS_DIRECTORY{"./src/Data/Decks"};
const char *DeckParser::BASIC_CARD_LEAD{"Basic Cards: "};
const char *DeckParser::DOUBLE_CARD_LEAD{"Double Cards: "};
const char *DeckParser::DUAL_CARD_LEAD{"Dual Card: "};
const char *DeckParser::FLEX_CARD_LEAD{"Flex Card: "};
const char *DeckParser::FLIP_CARD_LEAD{"Flip Card: "};


const vector <string> DeckParser::loadFileContent(const string &file) {
    fstream deckFile;

    string path;
    path.append(DeckParser::DECKS_DIRECTORY).append(DeckParser::FOLDER_DELIMITER).append(file);

    deckFile.open(path, fstream::in);
    if (!deckFile.is_open())
        throw InvalidFileException(path);

    string line;
    vector <string> fileContent;

    while (getline(deckFile, line))
        if (line.find_first_not_of(' ') != string::npos) //not an empty line
            fileContent.push_back(line);

    deckFile.close();

    return fileContent;
}

Deck DeckParser::loadFromFile(const CardDatabase &cardDatabase) {

    vector <string> files = DeckParser::getDecksFromDirectory(); //Find all files in a directory
    string loadedFile = files[DeckParser::userDeckIndexInput(files)]; //pick a file in the directory

    try {
        vector < Card * > cards = parseLinesForCards(cardDatabase, DeckParser::loadFileContent(loadedFile));
        return Deck(cards);
    }
    catch (ParseError &e) {
        throw InvalidFileException(string(DeckParser::DECKS_DIRECTORY) + DeckParser::FOLDER_DELIMITER + loadedFile);
    }
}

vector<Card *> DeckParser::parseLinesForCards(const CardDatabase &cardDatabase, const vector <string> &fileLines) {
    list < Card * > cards;

    for (const string &line: fileLines) {
        auto splitLine = CardDatabase::split(line, DeckParser::CARD_DESCRIPTION_DELIMITER);
        if (splitLine.size() != 2)
            throw ParseError();

        try { cards.push_back(cardDatabase.get(splitLine.back())); }
        catch (out_of_range &e) {
            throw ParseError();
        }
    }

    if (cards.size() != Deck::DECK_SIZE)
        throw ParseError();

    return vector<Card *>(cards.begin(), cards.end());
}

//Adapted from https://stackoverflow.com/a/612176
vector <string> DeckParser::getDecksFromDirectory() {
    vector <string> files;

    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir(DeckParser::DECKS_DIRECTORY)) != nullptr) {
        /* print all the files and directories within directory */
        while ((ent = readdir(dir)) != nullptr) {
            string fileName = ent->d_name;
            if (fileName != "." && fileName != "..")
                files.emplace_back(ent->d_name);
        }
        closedir(dir);
    } else
        /* could not open directory */
        throw CannotOpenDirectory(DeckParser::DECKS_DIRECTORY);

    return files;
}


size_t DeckParser::userDeckIndexInput(const vector <string> &files) {
    listDecksMessage(files);
    selectDeckPrompt();

    size_t input = 0;

    while (!(cin >> input) || input >= files.size()) {
        invalidInputMessage(); //NaN
        cin.clear();
        //ignores the entire cin until a newline is encountered
        cin.ignore(numeric_limits<streamsize>::max(), MainMenu::NEWLINE);
    }

    return input;
}

void DeckParser::selectDeckPrompt() { cout << "Select a deck:"; }

void DeckParser::listDecksMessage(const vector <string> &files) {
    cout << "Decks available" << endl;
    size_t i = 0;
    for (const auto &file : files)
        cout << "(" << i++ << ") " << file << endl;
}

void DeckParser::invalidInputMessage() { cout << "Invalid input, please try again." << endl; }
