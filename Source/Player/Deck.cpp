
//
// Created by tomtom on 08/02/19.
//

#include "Deck.h"
#include "../Cards/CardType.h"
#include "../Utilities/Utilities.cpp"
#include "../Utilities/DeckParser.h"

//Namespaces--------------------------------
using namespace std;

const int Deck::DECK_SIZE = 10;
const int Deck::MAX_CARDS_DRAWN = 4;


class CannotOpenFile : public exception {
    const char *what() const noexcept override {
        return ("Cannot open file.");
    }
};

ostream &operator<<(ostream &out, const Deck &deck) {
    size_t i = 0;
    for (const Card *card : deck.cards)
        cout << "(" << i++ << ") " << *card << endl;
    return out;
}

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

Deck::Deck() : randomGenerator(0, DECK_SIZE - 1) {}

Deck::Deck(vector<Card *> cards) : cards(std::move(cards)), randomGenerator(0, DECK_SIZE - 1) {}

Deck::Deck(const map<string, Card *> &allCards) : randomGenerator(0, DECK_SIZE - 1) {
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

void Deck::addCard(Card *card) { this->cards.push_back(card); }

vector<Card *> Deck::drawCardsFromDeck() {
    vector<Card *> drawnCards;

    for (size_t i = 0; i < MAX_CARDS_DRAWN; i++) {
        if (cards.empty())
            break;
        size_t pickedCardIndex = randomGenerator();
        drawnCards.push_back(this->cards[pickedCardIndex]);
        removeCardFromDeck(pickedCardIndex);
    }

    return drawnCards;
}

size_t Deck::getDeckSize() const { return this->cards.size(); }

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
            cin.ignore(numeric_limits<streamsize>::max(), DeckParser::NEWLINE);
        }
    }
}

vector<string> Deck::prepareDeckForSaving() const { //TODO refactor - use typeof
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
                    (j == 0 || j == currentCategory.size() - 1 ? "" : DeckParser::FILE_CARD_VALUE_DELIMITER));
        fileLines.push_back(line);
    }

    return fileLines;
}

void Deck::removeCardFromDeck(size_t pickedCardIndex) {
    cards.erase(cards.begin() + pickedCardIndex);
    randomGenerator.lowerCeiling(cards.size() - 1);
}

void Deck::saveToFile() const {

    fstream deckFile;

    vector<string> files = DeckParser::getDecksFromDirectory();

    string filename = QueryUserInputFilename(files);

    string path;
    path.append(DeckParser::DECKS_DIRECTORY_PATH).append(DeckParser::FOLDER_DELIMITER).append(filename);
    deckFile.open(path, fstream::out);
    if (!deckFile.is_open())
        throw CannotOpenFile();

    vector<string> cardLines = prepareDeckForSaving();

    for (const auto &cardLine : cardLines)
        deckFile << cardLine << endl;

    deckFile.close();

}

void Deck::addLeadingCategories(vector<string> *categorised) {
    string leads[5] = {DeckParser::BASIC_CARD_LEAD, DeckParser::DOUBLE_CARD_LEAD, DeckParser::DUAL_CARD_LEAD,
                       DeckParser::FLIP_CARD_LEAD,
                       DeckParser::FLEX_CARD_LEAD}; //TODO change this, it's too static
    for (size_t k = 0; k < 5; ++k)
        categorised[k].push_back(leads[k] + DeckParser::CARD_TYPE_VALUE_DELIMITER);
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
        vector<string> splitValues = DeckParser::splitStringByDelimiter(currentFlipCard, "|");
        //Extract the X from each substring
        string parsedFlipCard;
        for (size_t j = 0; j < 2; j++) {
            //Extract the first number from each operand
            string extractedValue = (DeckParser::splitStringByDelimiter(splitValues[j], "<~>")[0]);
            //Remove redundant symbols - sign and white spaces
            extractedValue = to_string(stoi(extractedValue));
            //Add to the line with a white space between if necessary
            parsedFlipCard.append(extractedValue).append((j == 0 ? " " : ""));
        }
        //replace the value
        categorised[3][i] = parsedFlipCard;
    }
}

void Deck::invalidInputMessage() { cout << "Invalid input, please try again." << endl; }

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

void Deck::fileExistsMessage() { cout << "File already exists, please try another name: "; }

void Deck::saveDeckAsPrompt() { cout << "Save deck as:"; }

void Deck::displayDecksMessage(const vector<string> &files) {
    cout << "Saved decks" << endl;
    size_t i = 0;
    for (const auto &file : files)
        cout << "(" << i++ << ") " << file << endl;
}

void Deck::deckForgedMessage() { cout << "Deck forged." << endl; }

void Deck::selectCardsDeckSizePrompt() { cout << "Select " << DECK_SIZE << " cards to add to your deck." << endl; }
