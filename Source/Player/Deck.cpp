
//
// Created by tomtom on 08/02/19.
//

#include "Deck.h"
#include "../Cards/CardType.h"

//Namespaces--------------------------------
using namespace std;

const char Deck::NEWLINE = '\n';
const string Deck::DECKS_DIRECTORY_PATH = "../Data/Decks";
const string Deck::FOLDER_DELIMITER = "/";
const string Deck::FILE_CARD_VALUE_DELIMITER = ",";
const string Deck::CARD_TYPE_VALUE_DELIMITER = ":";
const string Deck::BASIC_CARD_LEAD = "BasicCards";
const string Deck::DOUBLE_CARD_LEAD = "DoubleCards";
const string Deck::DUAL_CARD_LEAD = "DualCards";
const string Deck::FLEX_CARD_LEAD = "FlexCards";
const string Deck::FLIP_CARD_LEAD = "FlipCards";

class CannotOpenDirectory : public exception {
public:
    const char *what() const throw() override {
        return ("Cannot open the" + Deck::DECKS_DIRECTORY_PATH + "directory.").c_str();
    }
};

ostream &operator<<(ostream &out, const vector<string> &a) { //TODO make this into a method instead of an operator
    size_t i = 0;
    for (const auto &file : a)
        out << "(" << i++ << ") " << file << endl;
    return out;
}

ostream &operator<<(ostream &out, const Deck &deck) {
    size_t i = 0;
    for (const Card *card : deck.cards)
        cout << "(" << i++ << ") " << *card << endl;
    return out;
}

//Supportive-non-class-methods--------------
bool containsSubstring(const string &master, const string &slave) { return master.find(slave) != string::npos; }

vector<Card *> copyMapToVector(const map<string, Card *> &allCards) {
    vector<Card *> allCardsVector;
    allCardsVector.reserve(allCards.size());

    for (const auto &allCard : allCards)
        allCardsVector.push_back(allCard.second);

    return allCardsVector;
}

void removeSubstring(string &master, const string &pattern) {
    string::size_type n = pattern.length();
    for (string::size_type i = master.find(pattern);
         i != string::npos;
         i = master.find(pattern))
        master.erase(i, n);
}

//--------------------------------------------------------------------------------------------------------------------//
//Non-static-methods--------------------------------------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------------------------//

//Constructors
Deck::Deck(vector<Card *> cards) : cards(std::move(cards)) {}

Deck::Deck(const map<string, Card *> &allCards) {
    size_t i = 0;
    for (auto &card : allCards) {
        cout << (i < 10 ? " " : "") //Offsets single digit indices
             << (i < 100 ? " " : "")  //Offsets double digit indices
             << "(" << i << ")" << " " << (card.second)->getDescription() << endl;
        i++;
    }

    selectCardsDeckSizePrompt();
    loadCardsFromUser(allCards);
    deckForgedMessage();
}

void Deck::deckForgedMessage() { cout << "Deck forged." << endl; }

void Deck::selectCardsDeckSizePrompt() { cout << "Select " << DECK_SIZE << " cards to add to your deck." << endl; }

//Other-methods-----------------------
void Deck::addCard(Card *card) { this->cards.push_back(card); }

vector<Card *> Deck::drawCardsFromDeck() {
    vector<Card *> drawnCards;

    for (size_t i = 0; i < MAX_CARDS_DRAWN; i++) {
        if (cards.empty())
            break;
        size_t pickedCardIndex = rand() % this->cards.size(); //TODO change the randomness
        drawnCards.push_back(this->cards[pickedCardIndex]);
        this->cards.erase(this->cards.begin() + pickedCardIndex);
    }

    return drawnCards;
}

size_t Deck::getDeckSize() const { return this->cards.size(); }

//TODO allow replacing cards during the selection using cin.fail && cin.clear and cin >> string/char
void Deck::loadCardsFromUser(const map<string, Card *> &allCards) {
    vector<Card *> allCardsVector = copyMapToVector(allCards);

    this->cards.reserve(DECK_SIZE);
    size_t i = 0; //initial index

    while (i != DECK_SIZE) {
        cout << "(" << i << "): ";

        size_t input = 0;
        cin >> input;

        if (!cin.fail()) { //is a positive number
            if (input >= allCards.size())
                invalidInputMessage();//out of bounds
            else { //valid input
                this->addCard(allCardsVector[input]);
                cout << "You've selected: " << *(this->cards[i]) << endl;
                i++;
            }
        } else {
            invalidInputMessage(); //NaN
            cin.clear();
            //ignores the entire cin until a newline is encountered
            cin.ignore(numeric_limits<streamsize>::max(), NEWLINE);
        }
    }
}

void Deck::invalidInputMessage() { cout << "Invalid input, please try again." << endl; }

vector<string> Deck::prepareDeckForSaving() const { //TODO refactor
    vector<string> fileLines;

    vector<string> categorised[5];
    addLeadingCategories(categorised);

    size_t DoubleCardCounter = 0;
    size_t FlexCardCounter = 0;

    //categorise cards in the deck
    for (Card *card : cards) {
        const string &cardDescription = card->getDescription();
        if (containsSubstring(cardDescription, "Double the value of the last played card"))
            DoubleCardCounter++;
        else if (containsSubstring(cardDescription, "+/-"))
            FlexCardCounter++;
        else if (containsSubstring(cardDescription, FlipCard::FLIP_SIGN))
            categorised[FLIP].push_back(cardDescription);
        else if (containsSubstring(cardDescription, Card::DUAL_DELIMITER))
            categorised[DUAL].push_back(cardDescription);
        else
            categorised[BASIC].push_back(cardDescription);
    }

    //add the counters of the unique cards
    categorised[DOUBLE].push_back(to_string(DoubleCardCounter));
    categorised[FLEX].push_back(to_string(FlexCardCounter));

    //Prepare FlipCards for saving
    convertFlipCardToFileFormat(categorised);

    //Remove the card operands
    for (auto &category : categorised)
        for (auto &currentValue : category) {
            removeSubstring(currentValue, Card::PLUS_SIGN);
            removeSubstring(currentValue, Card::DUAL_DELIMITER);
            removeSubstring(currentValue, FlipCard::FLIP_SIGN);
        }

    //Construct the line in the output vector
    for (auto &currentCategory : categorised) {
        string line;
        for (size_t j = 0; j < currentCategory.size(); j++)
            line.append(currentCategory[j]).append(
                    (j == 0 || j == currentCategory.size() - 1 ? "" : Deck::FILE_CARD_VALUE_DELIMITER));
        fileLines.push_back(line);
    }

    return fileLines;
}

void Deck::saveToFile() const {

    fstream deckFile;

    vector<string> files = getDecksFromDirectory(); //TODO Change to a set?

    string filename = QueryUserInputFilename(files);

    string path;
    path.append(Deck::DECKS_DIRECTORY_PATH).append(Deck::FOLDER_DELIMITER).append(filename);
    deckFile.open(path, fstream::out);
    if (!deckFile.is_open())
        throw "File error"; //TODO proper exception

    vector<string> cardLines = prepareDeckForSaving();

    for (const auto &cardLine : cardLines)
        deckFile << cardLine << endl;

    deckFile.close();

}

//Static-methods----------------------
void Deck::addLeadingCategories(vector<string> *categorised) {
    string leads[5] = {Deck::BASIC_CARD_LEAD, Deck::DOUBLE_CARD_LEAD, Deck::DUAL_CARD_LEAD, Deck::FLIP_CARD_LEAD,
                       Deck::FLEX_CARD_LEAD}; //TODO change this, it's too static
    for (size_t k = 0; k < 5; ++k)
        categorised[k].push_back(leads[k] + Deck::CARD_TYPE_VALUE_DELIMITER);
}

bool Deck::fileAlreadyExists(const vector<string> &files, const string &filename) {
    for (const string &currentFile : files)
        if (currentFile == filename)
            return true;
    return false;
}

void Deck::convertFlipCardToFileFormat(vector<string> *categorised) {
    for (size_t i = 1; i < categorised[3].size(); i++) {
        string currentFlipCard = categorised[3][i];
        //Split the string (X <~> -X | Y <~> -Y) into X<~>-X and Y<~>-Y
        vector<string> splitValues = splitStringByDelimiter(currentFlipCard, "|"); //TODO replace with an array

        //Extract the X from each substring
        string parsedFlipCard;
        for (size_t j = 0; j < 2; j++) {
            //Extract the first number from each operand
            string extractedValue = (splitStringByDelimiter(splitValues[j], "<~>")[0]);
            //Remove redundant symbols - sign and white spaces
            extractedValue = to_string(stoi(extractedValue)); //TODO can be made easier, but this works for now
            //Add to the line with a white space between if necessary
            parsedFlipCard.append(extractedValue).append((j == 0 ? " " : ""));
        }
        //replace the value
        categorised[3][i] = parsedFlipCard;
    }
}

//Adapted from https://stackoverflow.com/a/612176
vector<string> Deck::getDecksFromDirectory() {
    vector<string> files;

    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir(Deck::DECKS_DIRECTORY_PATH.c_str())) != nullptr) {
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

int *Deck::getDualValuesFromString(const string &value) {
    //TODO CAN MAKE PAIR
    vector<string> parsedValue = splitStringByDelimiter(value, " ");

    if (parsedValue.size() != 2)
        throw "Parse error"; //TODO PROPER EXCEPTION, invalid count of doubling cards

    auto effects = new int[2];
    effects[0] = stoi(parsedValue[0]);
    effects[1] = stoi(parsedValue[1]);

    return effects;
}

vector<string> Deck::loadFileContent(const string &file) {
    fstream deckFile;

    string path;
    path.append(Deck::DECKS_DIRECTORY_PATH).append(Deck::FOLDER_DELIMITER).append(file);

    deckFile.open(path);
    if (!deckFile.is_open())
        throw "File opening error"; //TODO proper exception

    string line;
    vector<string> fileContent;

    while (getline(deckFile, line))
        if (line.find_first_not_of(' ') != string::npos) //not an empty line
            fileContent.push_back(line);

    deckFile.close();

    return fileContent;
}

void Deck::insertBasicCards(const std::map<string, Card *> &allCards, std::vector<Card *> &cards,
                            const std::vector<string> &currentLineValues) {
    for (const auto &value : currentLineValues) {
        Card *dummy = new BasicCard(stoi(value));
        cards.push_back(allCards.at(dummy->getDescription()));
        delete dummy;
    }
}

void Deck::insertDoubleCards(const map<string, Card *> &allCards, vector<Card *> &cards, int cardCount = 0) {
    Card *dummy = new DoubleCard();
    for (int i = 0; i < cardCount; i++)
        cards.push_back(allCards.at(dummy->getDescription()));
    delete dummy;
}

void Deck::insertDualCards(const map<string, Card *> &allCards, vector<Card *> &cards,
                           const vector<string> &currentLineValues) {
    for (const auto &value : currentLineValues) {
        int *effects = getDualValuesFromString(value);
        Card *dummy = new DualCard(effects[0], effects[1]);
        cards.push_back(allCards.at(dummy->getDescription()));
        delete[] effects;
        delete dummy;
    }
}

void Deck::insertFlipCards(const map<string, Card *> &allCards, vector<Card *> &cards,
                           const vector<string> &currentLineValues) {

    for (const auto &value : currentLineValues) {
        int *effects = getDualValuesFromString(value);
        Card *dummy = new FlipCard(effects[0], effects[1]);
        cards.push_back(allCards.at(dummy->getDescription()));
        delete[] effects;
        delete dummy;
    }
}

void Deck::insertFlexCards(const map<string, Card *> &allCards, vector<Card *> &cards, int cardCount = 0) {
    Card *dummy = new FlexCard();
    for (int i = 0; i < cardCount; i++)
        cards.push_back(allCards.at(dummy->getDescription()));
    delete dummy;
}

Deck Deck::loadFromFile(const map<string, Card *> &allCards) {
    //Select a file
    vector<string> files = Deck::getDecksFromDirectory(); //Find all files in a directory
    string loadedFile = files[Deck::userDeckIndexInput(files)]; //pick a file in the directory

    //Parse the file
    vector<string> deckFileContent = Deck::loadFileContent(loadedFile); //load the picked file's content
    vector<Card *> cards = parseLinesForCards(allCards, deckFileContent); //Load the cards from the 'database'

    return Deck(cards); //forge the deck
}

map<string, vector<string>> Deck::parseAllFileLines(vector<string> &deckFileContent) {

    map<string, vector<string>> parsedLines;
    for (const auto &line : deckFileContent) {
        size_t delimiterPosition = line.find(Deck::CARD_TYPE_VALUE_DELIMITER);
        if (delimiterPosition == string::npos) //contains delimiter?
            throw "Invalid line";  //TODO PROPER EXCEPTION
        else {
            string cardType = line.substr(0, delimiterPosition); //TODO trim
            string cardValues = line.substr(delimiterPosition + 1, string::npos); //TODO trim

            vector<string> parsedValues = splitStringByDelimiter(cardValues,
                                                                 Deck::FILE_CARD_VALUE_DELIMITER); //TODO trim
            pair<string, vector<string>> parsedLine = make_pair(cardType, parsedValues);
            parsedLines.insert(parsedLine);
        }
    }
    return parsedLines;
}

vector<Card *> Deck::parseLinesForCards(const map<string, Card *> &allCards, vector<string> &deckFileContent) {
    vector<Card *> cards;
    map<string, vector<string>> parsedLines = Deck::parseAllFileLines(deckFileContent);//TODO TRIM

    insertBasicCards(allCards, cards, parsedLines.at(Deck::BASIC_CARD_LEAD));
    insertDualCards(allCards, cards, parsedLines.at(Deck::DUAL_CARD_LEAD));
    insertFlipCards(allCards, cards, parsedLines.at(Deck::FLIP_CARD_LEAD));
    insertDoubleCards(allCards, cards, singleParameterValue(parsedLines.at(Deck::DOUBLE_CARD_LEAD)));
    insertFlexCards(allCards, cards, singleParameterValue(parsedLines.at(Deck::FLEX_CARD_LEAD)));

    //TODO try catch the stoi, might be an extra comma - no value to be parsed after a comma
    //TODO if card count doesn't match, ask to remove/add more cards - bleeding edge, do later
    if (cards.size() != DECK_SIZE)
        throw "Error parsing"; //TODO PROPER EXCEPTION - not enough cards in a deck

    return cards;
}

string Deck::QueryUserInputFilename(const vector<string> &files) {
    displayDecksMessage(files);
    saveDeckAsPrompt();

    string filename;
    cin >> filename;

    while (Deck::fileAlreadyExists(files, filename)) {
        fileExistsMessage();
        cin >> filename;
    }
    return filename;
}

int Deck::singleParameterValue(const vector<string> &lineValues) {
    if (lineValues.size() != 1)
        throw "Parse error"; //TODO PROPER EXCEPTION - invalid amount of arguments

    int flexCardCount = stoi(lineValues[0]);
    if (flexCardCount < 0)
        throw "Parse error"; //TODO PROPER EXCEPTION, invalid count of doubling cards

    return flexCardCount;
}

vector<string> Deck::splitStringByDelimiter(string phrase, const string &delimiter) {
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

size_t Deck::userDeckIndexInput(const vector<string> &files) {

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

void Deck::selectDeckPrompt() { cout << "Select a deck:"; }

void Deck::listDecksMessage(const vector<string> &files) { cout << "Decks available" << endl << files; }

void Deck::fileExistsMessage() { cout << "File already exists, please try another name: "; }

void Deck::saveDeckAsPrompt() { cout << "Save deck as:"; }

void Deck::displayDecksMessage(const vector<string> &files) { cout << "Saved decks" << endl << files; }
