
//
// Created by tomtom on 08/02/19.
//

#include <list>
#include "Deck.h"
#include "../../Utilities/DeckParser.h"
#include "../../Utilities/Exceptions.h"
#include "../../Game.h"

//Namespaces--------------------------------
using namespace std;

const size_t Deck::DECK_SIZE = 10;
const size_t Deck::MAX_CARDS_DRAWN = 4;
const char *Deck::DECK_FILE_LEAD{"Deck"};
const char *Deck::LEFT_INDEX_BRACKET{"("};
const char *Deck::RIGHT_INDEX_BRACKET{") "};


ostream &operator<<(ostream &out, const Deck &deck) {
    size_t i = 0;
    for (const Card *card : deck.cards)
        out << Deck::LEFT_INDEX_BRACKET << i++ << Deck::RIGHT_INDEX_BRACKET << *card << endl;
    return out;
}

Deck::Deck() : randomGenerator(0, DECK_SIZE - 1) {}

Deck::Deck(std::vector<Card *> cards) : cards(std::move(cards)), randomGenerator(0, DECK_SIZE - 1) {}

Deck::Deck(const CardDatabase &cardDatabase) : randomGenerator(0, DECK_SIZE - 1) {
    cout << cardDatabase;
    selectCardsDeckSizePrompt();
    loadCardsFromUser(cardDatabase);
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

void Deck::loadCardsFromUser(const CardDatabase &allCards) {
    vector<Card *> allCardsVector = allCards.toVector();

    this->cards.reserve(Deck::DECK_SIZE);
    size_t i = 0; //initial index

    while (i != Deck::DECK_SIZE) {
        cout << Deck::LEFT_INDEX_BRACKET << i << Deck::RIGHT_INDEX_BRACKET;

        size_t input = 0;
        cin >> input;

        if (!cin.fail()) { //is a positive number
            if (input >= allCards.size())
                invalidInputMessage();//out of bounds
            else { //valid input
                this->addCard(allCardsVector[input]);
                selectedCardMessage(i);
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
    path.append(DeckParser::DECKS_DIRECTORY).append(DeckParser::FOLDER_DELIMITER).append(filename);

    fstream deckFile;
    deckFile.open(path, fstream::out);
    if (!deckFile.is_open())
        throw CannotOpenFile();

    auto cardLines = toLines();

    for (const auto &cardLine : cardLines)
        deckFile << cardLine << endl;

    deckFile.close();
}

void Deck::saveToFile(std::ofstream &file) const {
    file << Deck::DECK_FILE_LEAD << Game::FILE_FIELD_VALUE_DELIMITER << cards.size() << endl;
    file << *this;
}

bool Deck::fileAlreadyExists(const vector<string> &files, const string &filename) {
    for (const string &currentFile : files)
        if (currentFile == filename)
            return true;
    return false;
}

Deck Deck::loadFromFile(std::ifstream &file, const CardDatabase &cardDatabase) {
    Deck deck;

    string input = CardDatabase::loadValue(Deck::DECK_FILE_LEAD, Game::FILE_FIELD_VALUE_DELIMITER, file);
    size_t cardCount = stoull(input);
    deck.randomGenerator.lowerCeiling(cardCount - 1);
    deck.cards.reserve(cardCount);

    for (size_t i = 0; i < cardCount; ++i) {
        getline(file, input);
        list<string> parsed = CardDatabase::split(input, Deck::RIGHT_INDEX_BRACKET);
        deck.cards.push_back(cardDatabase.get(parsed.back()));
    }

    return deck;
}

string Deck::QueryUserInputFilename(const vector<string> &files) {
    displayDecksMessage(files);
    deckNamePrompt();

    string filename;
    cin >> filename;

    while (Deck::fileAlreadyExists(files, filename)) {
        fileExistsMessage();
        cin >> filename;
    }
    return filename;
}

void Deck::fileExistsMessage() { cout << "File already exists, please try another name: "; }

void Deck::deckNamePrompt() { cout << "Save deck as:"; }

void Deck::deckForgedMessage() { cout << "Deck forged." << endl; }

void Deck::selectCardsDeckSizePrompt() { cout << "Select " << DECK_SIZE << " cards to add to your deck." << endl; }

void Deck::selectedCardMessage(size_t index) const { cout << "You've selected: " << *(cards[index]) << endl; }

void Deck::invalidInputMessage() { cout << "Invalid input, please try again." << endl; }

void Deck::displayDecksMessage(const vector<string> &files) {
    cout << "Saved decks" << endl;
    size_t i = 0;
    for (const auto &file : files)
        cout << Deck::LEFT_INDEX_BRACKET << i++ << Deck::RIGHT_INDEX_BRACKET << file << endl;
}
