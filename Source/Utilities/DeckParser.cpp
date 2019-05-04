//
// Created by tomtom on 03/05/19.
//

#include <list>
#include "DeckParser.h"
#include "Utilities.cpp"

using namespace std;

const char DeckParser::NEWLINE = '\n';
const string DeckParser::FOLDER_DELIMITER = "/";
const string DeckParser::FILE_CARD_VALUE_DELIMITER = ",";
const string DeckParser::CARD_TYPE_VALUE_DELIMITER = ":";
const string DeckParser::DECKS_DIRECTORY_PATH{"../Data/Decks"};
const string DeckParser::BASIC_CARD_LEAD{"Basic Cards: "};
const string DeckParser::DOUBLE_CARD_LEAD{"Double Cards: "};
const string DeckParser::DUAL_CARD_LEAD{"Dual Card: "};
const string DeckParser::FLEX_CARD_LEAD{"Flex Card: "};
const string DeckParser::FLIP_CARD_LEAD{"Flip Card: "};

class CannotOpenDirectory : public exception {
public:
    const char *what() const noexcept override {
        return ("Cannot open the" + DeckParser::DECKS_DIRECTORY_PATH + "directory.").c_str();
    }
};

class CannotOpenFile : public exception {
    const char *what() const noexcept override {
        return ("Cannot open file.");
    }
};

class ParseError : public exception {
    const char *what() const noexcept override {
        return ("Error reading file");
    }
};

const vector<string> DeckParser::loadFileContent(const string &file) {
    fstream deckFile;

    string path;
    path.append(DeckParser::DECKS_DIRECTORY_PATH).append(DeckParser::FOLDER_DELIMITER).append(file);

    deckFile.open(path, fstream::in);
    if (!deckFile.is_open())
        throw CannotOpenFile();

    string line;
    vector<string> fileContent;

    while (getline(deckFile, line))
        if (line.find_first_not_of(' ') != string::npos) //not an empty line
            fileContent.push_back(line);

    deckFile.close();

    return fileContent;
}

Deck DeckParser::loadFromFile(const map<string, Card *> &allCards) {
    //Select a file
    vector<string> files = DeckParser::getDecksFromDirectory(); //Find all files in a directory
    string loadedFile = files[DeckParser::userDeckIndexInput(files)]; //pick a file in the directory

    //Load the cards from the 'database' based on the ones in the file
    vector<Card *> cards = parseLinesForCards(allCards, DeckParser::loadFileContent(loadedFile));
    return Deck(cards); //forge the deck
}

vector<Card *> DeckParser::parseLinesForCards(const map<string, Card *> &allCards, const vector<string> &fileLines) {
    list < Card * > cards;

    for (const string &line: fileLines) {
        auto splitLine = splitStringByDelimiter(line, ": ");
        if (splitLine.size() != 2)
            throw ParseError();

        try {
            cards.push_back(allCards.at(splitLine[1]));
        }
        catch (out_of_range &e) {
            throw ParseError();
        }
    }

    if (cards.size() != Deck::DECK_SIZE)
        throw ParseError();

    return vector<Card *>(cards.begin(), cards.end());
}

//Adapted from https://stackoverflow.com/a/612176
vector<string> DeckParser::getDecksFromDirectory() {
    vector<string> files;

    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir(DeckParser::DECKS_DIRECTORY_PATH.c_str())) != nullptr) {
        /* print all the files and directories within directory */
        while ((ent = readdir(dir)) != nullptr) {
            string fileName = ent->d_name;
            if (fileName != "." && fileName != "..")
                files.emplace_back(ent->d_name);
        }
        closedir(dir);
    } else
        /* could not open directory */
        throw CannotOpenDirectory();

    return files;
}

vector<string> DeckParser::splitStringByDelimiter(string phrase, const string &delimiter) {
    vector<string> list;
    size_t pos = 0;
    string token;
    while ((pos = phrase.find(delimiter)) != string::npos) {
        token = phrase.substr(0, pos);
        list.push_back(token);
        phrase.erase(0, pos + delimiter.length());
    }
    list.push_back(phrase);

    return list;
}

size_t DeckParser::userDeckIndexInput(const vector<string> &files) {
    listDecksMessage(files);
    selectDeckPrompt();

    size_t input = 0;

    while (!(cin >> input) || input >= files.size()) {
        invalidInputMessage(); //NaN
        cin.clear();
        //ignores the entire cin until a newline is encountered
        cin.ignore(numeric_limits<streamsize>::max(), NEWLINE);
    }

    return input;
}

void DeckParser::selectDeckPrompt() { cout << "Select a deck:"; }

void DeckParser::listDecksMessage(const vector<string> &files) {
    cout << "Decks available" << endl;
    size_t i = 0;
    for (const auto &file : files)
        cout << "(" << i++ << ") " << file << endl;
}

void DeckParser::invalidInputMessage() { cout << "Invalid input, please try again." << endl; }
