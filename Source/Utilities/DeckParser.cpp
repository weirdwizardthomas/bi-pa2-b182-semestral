//
// Created by tomtom on 03/05/19.
//

#include "DeckParser.h"
#include "Utilities.cpp"

using namespace std;

const char DeckParser::NEWLINE = '\n';
const string DeckParser::FOLDER_DELIMITER = "/";
const string DeckParser::FILE_CARD_VALUE_DELIMITER = ",";
const string DeckParser::CARD_TYPE_VALUE_DELIMITER = ":";
const string DeckParser::DECKS_DIRECTORY_PATH{"../Data/Decks"};
const string DeckParser::BASIC_CARD_LEAD{"BasicCards"};
const string DeckParser::DOUBLE_CARD_LEAD{"DoubleCards"};
const string DeckParser::DUAL_CARD_LEAD{"DualCards"};
const string DeckParser::FLEX_CARD_LEAD{"FlexCards"};
const string DeckParser::FLIP_CARD_LEAD{"FlipCards"};

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

class InvalidLine : public exception {
    const char *what() const noexcept override {
        return ("Error reading file");
    }
};

class ParseError : public exception {
    const char *what() const noexcept override {
        return ("Error reading file");
    }
};


vector<string> DeckParser::loadFileContent(const string &file) {
    fstream deckFile;

    string path;
    path.append(DeckParser::DECKS_DIRECTORY_PATH).append(DeckParser::FOLDER_DELIMITER).append(file);

    deckFile.open(path);
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

void DeckParser::insertBasicCards(const std::map<string, Card *> &allCards, std::vector<Card *> &cards,
                                  const std::vector<string> &currentLineValues) {
    for (const auto &value : currentLineValues) {
        Card *dummy = new BasicCard(stoi(value));
        cards.push_back(allCards.at(dummy->getDescription()));
        delete dummy;
    }
}

void DeckParser::insertDoubleCards(const map<string, Card *> &allCards, vector<Card *> &cards, int cardCount = 0) {
    Card *dummy = new DoubleCard();
    for (int i = 0; i < cardCount; i++)
        cards.push_back(allCards.at(dummy->getDescription()));
    delete dummy;
}

void DeckParser::insertDualCards(const map<string, Card *> &allCards, vector<Card *> &cards,
                                 const vector<string> &currentLineValues) {
    for (const auto &value : currentLineValues) {
        int *effects = getDualValuesFromString(value);
        Card *dummy = new DualCard(effects[0], effects[1]);
        cards.push_back(allCards.at(dummy->getDescription()));
        delete[] effects;
        delete dummy;
    }
}

void DeckParser::insertFlipCards(const map<string, Card *> &allCards, vector<Card *> &cards,
                                 const vector<string> &currentLineValues) {

    for (const auto &value : currentLineValues) {
        int *effects = getDualValuesFromString(value);
        Card *dummy = new FlipCard(effects[0], effects[1]);
        cards.push_back(allCards.at(dummy->getDescription()));
        delete[] effects;
        delete dummy;
    }
}

void DeckParser::insertFlexCards(const map<string, Card *> &allCards, vector<Card *> &cards, int cardCount = 0) {
    Card *dummy = new FlexCard();
    for (int i = 0; i < cardCount; i++)
        cards.push_back(allCards.at(dummy->getDescription()));
    delete dummy;
}

Deck DeckParser::loadFromFile(const map<string, Card *> &allCards) {
    //Select a file
    vector<string> files = DeckParser::getDecksFromDirectory(); //Find all files in a directory
    string loadedFile = files[DeckParser::userDeckIndexInput(files)]; //pick a file in the directory

    //Parse the file
    vector<string> deckFileContent = DeckParser::loadFileContent(loadedFile); //load the picked file's content
    vector<Card *> cards = parseLinesForCards(allCards, deckFileContent); //Load the cards from the 'database'

    return Deck(cards); //forge the deck
}

map<string, vector<string>> DeckParser::parseAllFileLines(vector<string> &deckFileContent) {

    map<string, vector<string>> parsedLines;
    for (const auto &line : deckFileContent) {
        size_t delimiterPosition = line.find(DeckParser::CARD_TYPE_VALUE_DELIMITER);
        if (delimiterPosition == string::npos) //contains delimiter?
            throw InvalidLine();
        else {
            string dummy = line.substr(0, delimiterPosition);
            string cardType = trim(dummy);

            dummy = line.substr(delimiterPosition + 1, string::npos);
            string cardValues = trim(dummy);

            vector<string> parsedValues = splitStringByDelimiter(cardValues, DeckParser::FILE_CARD_VALUE_DELIMITER);
            pair<string, vector<string>> parsedLine = make_pair(cardType, parsedValues);
            parsedLines.insert(parsedLine);
        }
    }
    return parsedLines;
}

vector<Card *> DeckParser::parseLinesForCards(const map<string, Card *> &allCards, vector<string> &deckFileContent) {
    vector<Card *> cards;
    map<string, vector<string>> parsedLines = DeckParser::parseAllFileLines(deckFileContent);
    insertBasicCards(allCards, cards, parsedLines.at(DeckParser::BASIC_CARD_LEAD));
    insertDualCards(allCards, cards, parsedLines.at(DeckParser::DUAL_CARD_LEAD));
    insertFlipCards(allCards, cards, parsedLines.at(DeckParser::FLIP_CARD_LEAD));
    insertDoubleCards(allCards, cards, singleParameterValue(parsedLines.at(DeckParser::DOUBLE_CARD_LEAD)));
    insertFlexCards(allCards, cards, singleParameterValue(parsedLines.at(DeckParser::FLEX_CARD_LEAD)));

    //TODO try catch the stoi, might be an extra comma - no value to be parsed after a comma
    //TODO if card count doesn't match, ask to remove/add more cards - bleeding edge, do later
    if (cards.size() != Deck::DECK_SIZE)
        throw ParseError();

    return cards;
}

int DeckParser::singleParameterValue(const vector<string> &lineValues) {
    if (lineValues.size() != 1)
        throw ParseError();

    int flexCardCount = stoi(lineValues[0]);
    if (flexCardCount < 0)
        throw ParseError();

    return flexCardCount;
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

int *DeckParser::getDualValuesFromString(const string &value) {
    vector<string> parsedValue = splitStringByDelimiter(value, " ");

    if (parsedValue.size() != 2)
        throw ParseError();

    auto effects = new int[2];
    effects[0] = stoi(parsedValue[0]);
    effects[1] = stoi(parsedValue[1]);

    return effects;
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