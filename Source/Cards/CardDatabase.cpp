//
// Created by tomtom on 04/05/19.
//

#include "CardDatabase.h"
#include "FlipCard.h"
#include "BasicCard.h"
#include "DoubleCard.h"
#include "FlexCard.h"
#include "../Utilities/Exceptions.h"

using namespace std;

const char *CardDatabase::CARD_DIRECTORY{"./Data/Cards/"};
const char *CardDatabase::BASIC_CARD{"BasicCards"};
const char *CardDatabase::DUAL_CARD{"DualCards"};
const char *CardDatabase::FLIP_CARD{"FlipCards"};


CardDatabase::CardDatabase() {
    loadBasicCards();
    loadDualCards();
    loadFlipCards();
    loadDoubleCard();
    loadFlexCard();
}

CardDatabase::~CardDatabase() {
    for (auto &record: cards)
        delete record.second;
}

void CardDatabase::loadFlipCards() {
    vector<string> fileLines = getFileLines(pathOf(CardDatabase::FLIP_CARD));
    validLines(fileLines);

    for (const string &line : fileLines) {
        pair<int, int> extractedValues = getDualValues(line);
        Card *dummy = new FlipCard(extractedValues.first, extractedValues.second);
        cards.insert(pair<string, Card *>(dummy->getDescription(), dummy));
    }
}

void CardDatabase::loadDualCards() {
    vector<string> fileLines = getFileLines(pathOf(DUAL_CARD));
    validLines(fileLines);

    for (const string &line : fileLines) {
        pair<int, int> extractedValues = getDualValues(line);
        Card *dummy = new DualCard(extractedValues.first, extractedValues.second);
        cards.insert(pair<string, Card *>(dummy->getDescription(), dummy));
    }
}

void CardDatabase::loadBasicCards() {
    vector<string> fileLines = getFileLines(pathOf(BASIC_CARD));
    validLines(fileLines, BASIC_CARD);

    for (const string &line : fileLines) {
        Card *dummy = new BasicCard(stoi(line));
        cards.insert(pair<string, Card *>(dummy->getDescription(), dummy));
    }
}

void CardDatabase::loadDoubleCard() {
    Card *dummy = new DoubleCard();
    cards.insert(pair<string, Card *>(dummy->getDescription(), dummy));
}

void CardDatabase::loadFlexCard() {
    Card *dummy = new FlexCard();
    cards.insert(pair<string, Card *>(dummy->getDescription(), dummy));
}

Card *CardDatabase::get(const string &key) const { return cards.at(key); }

pair<int, int> CardDatabase::getDualValues(const string &line) {
    auto tokenisedLine = split(line, DualCard::DUAL_DELIMITER);
    return {stoi(tokenisedLine.front()), stoi(tokenisedLine.back())};
}

vector<string> CardDatabase::getFileLines(const string &filePath) {
    fstream cardFile;
    cardFile.open(filePath, ios::in);

    if (!cardFile.is_open())
        throw InvalidFileException();

    string line;
    vector<string> lines;

    while (getline(cardFile, line))
        if (line.find_first_not_of(' ') != string::npos) //not an empty line
            lines.push_back(line);

    return lines;
}

string CardDatabase::pathOf(const string &filename) { return CARD_DIRECTORY + filename; }

size_t CardDatabase::size() const { return cards.size(); }

list<string> CardDatabase::split(string phrase, const string &delimiter) {
    //Copied from https://stackoverflow.com/a/44495206'
    list<string> list;
    string s = string(move(phrase));
    size_t pos = 0;
    string token;
    while ((pos = s.find(delimiter)) != string::npos) {
        token = s.substr(0, pos);
        list.push_back(token);
        s.erase(0, pos + delimiter.length());
    }
    list.push_back(s);

    //Added a modification to ensure that the line contained only one delimiter
    if (list.size() != 2)
        throw InvalidFileException();

    return list;
}

string CardDatabase::loadValue(const string &field, const string &delimiter, ifstream &file) {
    string input;
    getline(file, input);
    list<string> parsed = split(input, delimiter);
    if (parsed.front() != field)
        throw ParseError();

    return parsed.back();
}

std::vector<Card *> CardDatabase::toVector() const {
    vector<Card *> asVector;
    asVector.reserve(cards.size());

    for (const auto &card : cards)
        asVector.push_back(card.second);

    return asVector;
}

void CardDatabase::validLines(const vector<string> &fileLines, const string &mode) {
    if (mode == BASIC_CARD)
        for (const string &line : fileLines)
            stoi(line);
    else {
        for (const string &line : fileLines) {
            size_t delimiterIndex = line.find(DualCard::DUAL_DELIMITER);
            if (delimiterIndex == string::npos)
                throw InvalidFileException();
        }
    }
}

ostream &operator<<(ostream &out, const CardDatabase &cardDatabase) {
    size_t i = 0;
    for (auto &card : cardDatabase.cards) {
        cout << (i < 10 ? " " : "") //Offsets single digit indices
             << (i < 100 ? " " : "")  //Offsets double digit indices
             << "(" << i << ")" << ": " << (card.second)->getDescription() << endl;
        i++;
    }

    return out;
}

std::map<std::string, Card *>::const_iterator CardDatabase::cbegin() const { return cards.cbegin(); }

std::map<std::string, Card *>::const_iterator CardDatabase::cend() const { return cards.cend(); }

std::map<std::string, Card *>::iterator CardDatabase::begin() { return cards.begin(); }

std::map<std::string, Card *>::iterator CardDatabase::end() { return cards.end(); }