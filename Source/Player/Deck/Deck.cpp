//
// Created by tomtom on 08/02/19.
//

#include "Deck.h"

//Namespaces--------------------------------
using namespace std;

ostream &operator<<(ostream &out, const vector<string> &a) {
    size_t i = 0;
    for (const auto &file : a)
        out << "(" << i++ << ") " << file << endl;

    return out;
}

Deck::Deck(const vector<Card *> &cards) : cards(cards) {}

Hand *Deck::drawCards(Hand *currentHand) {

    for (size_t i = 0; i < 4; i++) {
        if (this->cards.empty()) //no more cards to be drawn
            break;

        currentHand->addCard(this->cards[i]);
        this->cards.erase(this->cards.begin() + i);
    }

    return currentHand;
}

//TODO probably throw an exception - WHAT EXCEPTION?!
int Deck::playCard(size_t cardIndex, vector<int> &playedCards, int currentScore, int opponentScore) {
    int effect = this->cards[cardIndex]->play(playedCards, currentScore, opponentScore);

    this->cards.erase(this->cards.begin() + cardIndex);

    return effect;
}

ostream &operator<<(ostream &out, const Deck &deck) {
    size_t i = 0;

    for (Card *card : deck.cards)
        cout << "(" << i++ << ") " << *card << endl;

    return out;
}

size_t Deck::getDeckSize() const {
    return this->cards.size();
}

void Deck::addCard(Card *card) {
    this->cards.push_back(card);
}

Deck::Deck(map<string, Card *> &allCards) {
    size_t i = 0;
    //TODO Have pages and a fixed amount per page?
    for (auto &card : allCards)
        cout << (i < DECK_SIZE ? " " : "") << "(" << i++ << ")" << " " << (card.second)->getDescription() << endl;

    //TODO exit query here ?
    cout << "Select ten cards to add to your deck." << endl;

    getCardChoicesFromUser(allCards);

    cout << "Deck successfully forged." << endl;
}

vector<Card *> copyMapToVector(const map<string, Card *> &allCards) {
    vector<Card *> allCardsVector;
    allCardsVector.reserve(allCards.size());

    for (const auto &allCard : allCards)
        allCardsVector.push_back(allCard.second);

    return allCardsVector;
}

//TODO allow replacing cards during the selection using cin.fail && cin.clear and cin >> string/char
void Deck::getCardChoicesFromUser(const map<string, Card *> &allCards) {
    vector<Card *> allCardsVector = copyMapToVector(allCards);

    size_t i = 1;

    while (i != DECK_SIZE) {
        cout << "(" << i << "):";

        size_t input = 0;
        cin >> input;

        if (!cin.fail()) { //is a positive number
            if (input >= allCards.size())
                cout << "Invalid choice, please try again." << endl;  //out of bounds
            else { //valid input
                this->addCard(allCardsVector[input]);
                cout << "You've selected: " << *(this->cards[i - 1]) << endl;
                i++;
            }

        } else {
            cout << "Invalid input, please try again." << endl; //NaN
            cin.clear();
            //ignores the entire cin until a newline is encountered
            cin.ignore(numeric_limits<streamsize>::max(), NEWLINE);
        }
    }
}

//Adapted from https://stackoverflow.com/a/612176
vector<string> Deck::getDecksFromDirectory() {
    vector<string> files;

    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir(DECKS_DIRECTORY_PATH)) != nullptr) {
        /* print all the files and directories within directory */
        while ((ent = readdir(dir)) != nullptr) {
            string fileName = ent->d_name;
            if (fileName != "." && fileName != "..")
                files.emplace_back(ent->d_name);
        }
        closedir(dir);
    } else
        /* could not open directory */
        throw "Couldn't open directory"; //TODO better exception


    return files;
}

Deck Deck::loadFromFile() {
    vector<string> files = Deck::getDecksFromDirectory();

    size_t fileIndex = Deck::userDeckIndexInput(files);
    string loadedFile = files[fileIndex];

    vector<string> deckFileContent = Deck::loadFileContent(loadedFile);
    cout << deckFileContent << endl;

    map<string, vector<string>> parsedLines = Deck::parseAllFileLines(deckFileContent);
    for (auto &parsedLine : parsedLines)
        cout << parsedLine.second << endl;

    vector<Card *> cards;
    vector<string> currentLineValues;
    //TODO pass the Card * map to this method, find the approriate card based on the key, add it to the vector


    //first line - BASIC_CARDS
    currentLineValues = parsedLines.at(BASIC_CARD_LEAD);

    //second line - DOUBLE_CARDS

    //third line - DUAL_CARDS

    //fourth line - FLEX_CARDS

    //fifth line - FLIP_CARDS

    return Deck(cards);
}

size_t Deck::userDeckIndexInput(const vector<string> &files) {

    cout << "Decks available" << endl;
    cout << files;
    cout << "Select a deck:";

    size_t input = 0;

    while (!(cin >> input) || input >= files.size()) {
        cout << "Invalid input, please try again." << endl; //NaN
        cin.clear();
        //ignores the entire cin until a newline is encountered
        cin.ignore(numeric_limits<streamsize>::max(), NEWLINE);
    }

    return input;
}

vector<string> Deck::loadFileContent(string file) {
//TODO can prolly remove the string line and directly add the file's line in the cycle ?
    string path;
    path.append(DECKS_DIRECTORY_PATH).append("/").append(file);

    string line;
    vector<string> fileContent;

    fstream deckFile;

    deckFile.open(path);
    if (!deckFile.is_open())
        throw "File opening error"; //TODO proper exception

    while (getline(deckFile, line))
        if (line.find_first_not_of(SPACE) != string::npos) //not an empty line
            fileContent.push_back(line);

    deckFile.close();

    return fileContent;
}

/**
 * Parses the phrase string by the delimiter string into substrings
 * @param phrase Line to be parsed by the delimiter
 * @param delimiter Delimiter by which the string will be split
 * @return Vector of substring lying between delimiters
 */
std::vector<std::string> Deck::parseCardValues(string phrase, const string &delimiter) {
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

std::map<std::string, std::vector<std::string>> Deck::parseAllFileLines(vector<string> &deckFileContent) {

    map<string, vector<string>> parsedLines;
    for (const auto &line : deckFileContent) {
        size_t delimiterPosition = line.find(CARD_TYPE_VALUE_DELIMITER);
        if (delimiterPosition == string::npos)
            throw "Invalid line";  //TODO PROPER EXCEPTION
        else {
            string cardType = line.substr(0, delimiterPosition); //TODO trim
            string cardValues = line.substr(delimiterPosition + 1, string::npos);

            vector<string> parsedValues = parseCardValues(cardValues, FILE_CARD_VALUE_DELIMITER);
            pair<string, vector<string>> parsedLine = make_pair(cardType, parsedValues);
            parsedLines.insert(parsedLine);
        }
    }
    return parsedLines;
}
