
//
// Created by tomtom on 08/02/19.
//

#include <list>
#include "Deck.h"
#include "../../Cards/CardType.h"
#include "../../Utilities/DeckParser.h"
#include "../../Utilities/Exceptions.h"

//Namespaces--------------------------------
using namespace std;

const int Deck::DECK_SIZE = 10;
const int Deck::MAX_CARDS_DRAWN = 4;

const char *Deck::DECK_FILE_LEAD{"Deck"};
const char *Deck::DECK_HEADER_DELIMITER{": "};


ostream &operator<<(ostream &out, const Deck &deck) {
    size_t i = 0;
    for (const Card *card : deck.cards)
        out << "(" << i++ << ") " << *card << endl;
    return out;
}

Deck::Deck() : randomGenerator(0, DECK_SIZE - 1) {}

Deck::Deck(vector<Card *> cards) : cards(std::move(cards)), randomGenerator(0, DECK_SIZE - 1) {}

Deck::Deck(const CardDatabase &allCards) : randomGenerator(0, DECK_SIZE - 1) {
    cout << allCards;
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

void Deck::loadCardsFromUser(const CardDatabase &allCards) {
    vector<Card *> allCardsVector = allCards.toVector();

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

list<string> Deck::toLines() const {
    list<string> fileLines;
    for (const auto &card: cards) {
        string line;

        if (typeid(*card) == typeid(BasicCard))
            line.append(DeckParser::BASIC_CARD_LEAD);
        if (typeid(*card) == typeid(DualCard))
            line.append(DeckParser::DUAL_CARD_LEAD);
        if (typeid(*card) == typeid(DoubleCard))
            line.append(DeckParser::DOUBLE_CARD_LEAD);
        if (typeid(*card) == typeid(FlexCard))
            line.append(DeckParser::FLEX_CARD_LEAD);
        if (typeid(*card) == typeid(FlipCard))
            line.append(DeckParser::FLIP_CARD_LEAD);

        line.append(card->getDescription());
        fileLines.emplace_back(line);
    }

    return fileLines;
}

void Deck::removeCardFromDeck(size_t pickedCardIndex) {
    cards.erase(cards.begin() + pickedCardIndex);
    randomGenerator.lowerCeiling(cards.size() - 1);
}

void Deck::saveToFile() const {
    vector<string> files = DeckParser::getDecksFromDirectory();
    string filename = QueryUserInputFilename(files);

    string path;
    path.append(DeckParser::DECKS_DIRECTORY_PATH).append(DeckParser::FOLDER_DELIMITER).append(filename);

    fstream deckFile;
    deckFile.open(path, fstream::out);
    if (!deckFile.is_open())
        throw CannotOpenFile();

    auto cardLines = toLines();

    for (const auto &cardLine : cardLines)
        deckFile << cardLine << endl;

    deckFile.close();
}

void Deck::saveToFile(ofstream &file) const {
    file << DECK_FILE_LEAD << ": " << cards.size() << endl;
    file << *this;
}

bool Deck::fileAlreadyExists(const vector<string> &files, const string &filename) {
    for (const string &currentFile : files)
        if (currentFile == filename)
            return true;
    return false;
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

Deck Deck::loadFromFile(std::ifstream &file, const CardDatabase &cardDatabase) {
    Deck deck;

    string input;
    getline(file, input);

    list<string> parsed = CardDatabase::split(input, Deck::DECK_HEADER_DELIMITER);
    if (parsed.front() != Deck::DECK_FILE_LEAD)
        throw ParseError();

    size_t cardCount = stoull(parsed.back());

    deck.cards.reserve(cardCount);
    for (size_t i = 0; i < cardCount; ++i) {
        getline(file, input);
        parsed = CardDatabase::split(input, ") ");
        deck.cards.push_back(cardDatabase.get(parsed.back()));

    }

    return deck;
}


