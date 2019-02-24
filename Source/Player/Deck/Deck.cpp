//
// Created by tomtom on 08/02/19.
//

#include "Deck.h"

//Namespaces--------------------------------
using namespace std;

ostream &operator<<(ostream &out, const vector<string> &a) {
    size_t i = 0;
    for (const auto &file : a) {
        out << "(" << i << ") " << file << endl;
        i++;
    }
    return out;
}

ostream &operator<<(ostream &out, const vector<Card *> &a) {
    size_t i = 0;
    for (const auto &card : a) {
        out << "(" << i << ") " << card << endl;
        i++;
    }

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

size_t Deck::getDeckSize() const {
    return this->cards.size();
}

void Deck::addCard(Card *card) {
    this->cards.push_back(card);
}

Deck::Deck(const map<string, Card *> &allCards) {
    size_t i = 0;
    //TODO Have pages and a fixed amount per page?
    for (auto &card : allCards) {
        cout << (i < DECK_SIZE ? " " : "") << "(" << i << ")" << " " << (card.second)->getDescription() << endl;
        i++;
    }

    //TODO exit query here ?
    cout << "Select ten cards to add to your deck." << endl;

    loadCardsFromUser(allCards);

    cout << "Deck forged." << endl;
}

bool containsSubstring(const string &master, const string &slave) {
    return master.find(slave) != string::npos;
}

void Deck::saveToFile() const {

    //Setup ostream-------------------
    fstream deckFile;

    vector<string> files = getDecksFromDirectory(); //TODO Change to a set?

    string filename = QueryUserInputFilename(files);

    string path;
    path.append(DECKS_DIRECTORY_PATH).append(FOLDER_DELIMITER).append(filename);

    deckFile.open(path, fstream::out);
    if (!deckFile.is_open())
        throw "File error"; //TODO proper exception

    vector<string> cardLines = parseDeckForCards();
    for (size_t i = 0; i < cardLines.size(); i++)
        deckFile << cardLines[i] << endl;

    deckFile.close();

}

string Deck::QueryUserInputFilename(const vector<string> &files) const {
    cout << "Saved decks" << endl;
    cout << files;

    string filename;
    cout << "Save deck as:";
    cin >> filename;

    while (fileAlreadyExists(files, filename)) {
        cout << "File already exists, please try another name: ";
        cin >> filename;
    }
    return filename;
}

void removeSubstring(string &master, const string &pattern) {
    string::size_type n = pattern.length();
    for (string::size_type i = master.find(pattern);
         i != string::npos;
         i = master.find(pattern))
        master.erase(i, n);
}

vector<string> Deck::parseDeckForCards() const {
    vector<string> fileLines;

    vector<string> categorised[5];
    addLeadingCategories(categorised);

    size_t DoubleCardCounter = 0;
    size_t FlexCardCounter = 0;

    for (Card *card : cards) {
        const string &cardDescription = card->getDescription();
        //TODO make this prettier - extract a 'Contains substring' method and use switch?
        if (containsSubstring(cardDescription, "Double the value of the last played card")) //DOUBLE
            DoubleCardCounter++;
        else if (containsSubstring(cardDescription, "+/-")) //FLEX
            FlexCardCounter++;
        else if (containsSubstring(cardDescription, "<~>")) //FLIP
            categorised[3].push_back(cardDescription);
        else if (containsSubstring(cardDescription, "|"))
            categorised[2].push_back(cardDescription); //DUAL
        else
            categorised[0].push_back(cardDescription); //BASIC
    }

    //add the counters of the unique cards
    categorised[1].push_back(to_string(DoubleCardCounter));
    categorised[4].push_back(to_string(FlexCardCounter));

    convertFlipCardToFileFormat(categorised);

    //Remove the delimiters
    for (auto &category : categorised)
        for (auto &currentValue : category) {
            removeSubstring(currentValue, "+");
            removeSubstring(currentValue, "|");
            removeSubstring(currentValue, "<~>");
        }

    //Construct the line in the output vector
    for (auto &i : categorised) {
        string line;
        for (size_t j = 0; j < i.size(); j++)
            line.append(i[j]).append((j == 0 || j == i.size() - 1 ? "" : FILE_CARD_VALUE_DELIMITER));
        fileLines.push_back(line);
    }

    return fileLines;
}

void Deck::convertFlipCardToFileFormat(vector<string> *categorised) const {
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

bool Deck::fileAlreadyExists(const vector<string> &files, const string &filename) const {
    for (const string &currentFile : files)
        if (currentFile == filename)
            return true;
    return false;
}

void Deck::addLeadingCategories(vector<string> *categorised) const {
    string leads[5] = {BASIC_CARD_LEAD, DOUBLE_CARD_LEAD, DUAL_CARD_LEAD, FLIP_CARD_LEAD, FLEX_CARD_LEAD};
    for (size_t k = 0; k < 5; k++)
        categorised[k].push_back(leads[k] + CARD_TYPE_VALUE_DELIMITER);
}

vector<Card *> copyMapToVector(const map<string, Card *> &allCards) {
    vector<Card *> allCardsVector;
    allCardsVector.reserve(allCards.size());

    for (const auto &allCard : allCards)
        allCardsVector.push_back(allCard.second);

    return allCardsVector;
}

//TODO allow replacing cards during the selection using cin.fail && cin.clear and cin >> string/char
void Deck::loadCardsFromUser(const map<string, Card *> &allCards) {
    vector<Card *> allCardsVector = copyMapToVector(allCards);

    size_t i = this->getDeckSize() + 1;

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

Deck Deck::loadFromFile(const map<string, Card *> &allCards) {

    //Select a file
    vector<string> files = Deck::getDecksFromDirectory(); //Find all files in a directory
    string loadedFile = files[Deck::userDeckIndexInput(files)]; //pick a file in the directory

    //Parse the file
    vector<string> deckFileContent = Deck::loadFileContent(loadedFile); //load the picked file's content
    vector<Card *> cards = parseLinesForCards(allCards, deckFileContent); //Load the cards from the 'database'

    return Deck(cards); //forge the deck
}

//TODO better method name
vector<Card *> Deck::parseLinesForCards(const map<string, Card *> &allCards, vector<string> &deckFileContent) {
    vector<Card *> cards;
    map<string, vector<string>> parsedLines = Deck::parseAllFileLines(deckFileContent);//TODO TRIM

    insertBasicCards(allCards, cards, parsedLines.at(BASIC_CARD_LEAD));
    insertDualCards(allCards, cards, parsedLines.at(DUAL_CARD_LEAD));
    insertFlipCards(allCards, cards, parsedLines.at(FLIP_CARD_LEAD));
    insertDoubleCards(allCards, cards, singleParameterValue(parsedLines.at(DOUBLE_CARD_LEAD)));
    insertFlexCards(allCards, cards, singleParameterValue(parsedLines.at(FLEX_CARD_LEAD)));

    //TODO try catch the stoi, might be an extra comma - no value to be parsed after a comma
    //TODO if card count doesn't match, ask to remove/add more cards - bleeding edge, do later
    if (cards.size() != DECK_SIZE)
        throw "Error parsing"; //TODO PROPER EXCEPTION - not enough cards in a deck

    return cards;
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

void Deck::insertBasicCards(const std::map<string, Card *> &allCards, std::vector<Card *> &cards,
                            const std::vector<string> &currentLineValues) {
    for (const auto &value : currentLineValues) {
        Card *dummy = new BasicCard(stoi(value));
        cards.push_back(allCards.at(dummy->getDescription()));
        delete dummy;
    }
}

void Deck::insertFlexCards(const map<string, Card *> &allCards, vector<Card *> &cards, int cardCount = 0) {
    Card *dummy = new FlexCard();
    for (int i = 0; i < cardCount; i++)
        cards.push_back(allCards.at(dummy->getDescription()));
    delete dummy;
}

void Deck::insertDoubleCards(const map<string, Card *> &allCards, vector<Card *> &cards, int cardCount = 0) {
    Card *dummy = new DoubleCard();
    for (int i = 0; i < cardCount; i++)
        cards.push_back(allCards.at(dummy->getDescription()));
    delete dummy;
}

int Deck::singleParameterValue(const vector<string> &lineValues) {
    if (lineValues.size() != 1)
        throw "Parse error"; //TODO PROPER EXCEPTION - invalid amount of arguments

    int flexCardCount = stoi(lineValues[0]);
    if (flexCardCount < 0)
        throw "Parse error"; //TODO PROPER EXCEPTION, invalid count of doubling cards

    return flexCardCount;
}

int *Deck::getDualValuesFromString(const string &value) {
    //TODO CAN MAKE PAIR
    vector<string> parsedValue = splitStringByDelimiter(value, SPACE);

    if (parsedValue.size() != 2)
        throw "Parse error"; //TODO PROPER EXCEPTION, invalid count of doubling cards

    int *effects = new int[2];
    effects[0] = stoi(parsedValue[0]);
    effects[1] = stoi(parsedValue[1]);

    return effects;
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
    fstream deckFile;

    string path;
    path.append(DECKS_DIRECTORY_PATH).append(FOLDER_DELIMITER).append(file);

    deckFile.open(path);
    if (!deckFile.is_open())
        throw "File opening error"; //TODO proper exception

    string line;
    vector<string> fileContent;

    while (getline(deckFile, line))
        if (line.find_first_not_of(SPACE) != string::npos) //not an empty line
            fileContent.push_back(line);

    deckFile.close();

    return fileContent;
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

map<string, vector<string>> Deck::parseAllFileLines(vector<string> &deckFileContent) {

    map<string, vector<string>> parsedLines;
    for (const auto &line : deckFileContent) {
        size_t delimiterPosition = line.find(CARD_TYPE_VALUE_DELIMITER);
        if (delimiterPosition == string::npos) //contains delimiter?
            throw "Invalid line";  //TODO PROPER EXCEPTION
        else {
            string cardType = line.substr(0, delimiterPosition); //TODO trim
            string cardValues = line.substr(delimiterPosition + 1, string::npos); //TODO trim

            vector<string> parsedValues = splitStringByDelimiter(cardValues, FILE_CARD_VALUE_DELIMITER); //TODO trim
            pair<string, vector<string>> parsedLine = make_pair(cardType, parsedValues);
            parsedLines.insert(parsedLine);
        }
    }
    return parsedLines;
}

ostream &operator<<(ostream &out, const Deck &deck) {
    size_t i = 0;

    for (Card *card : deck.cards)
        cout << "(" << i++ << ") " << *card << endl;

    return out;
}