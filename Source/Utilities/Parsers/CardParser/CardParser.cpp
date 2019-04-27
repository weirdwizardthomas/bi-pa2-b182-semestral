//
// Created by tomtom on 14/02/19.
//

#include "CardParser.h"

//Namespaces--------------------------------
using namespace std;

//Definitions-------------------------------
const string CardParser::CARD_FOLDER_PATH = "../Data/Cards/";
const string CardParser::BASIC_CARD = "BasicCards";
const string CardParser::DUAL_CARD = "DualCards";
const string CardParser::FLIP_CARD = "FlipCards";
const string CardParser::DUAL_DELIMITER = "|";


//Copied from https://stackoverflow.com/a/44495206'
//TODO Can't move it to ParserStringUtilities.cpp, fix!
vector<string> split(string phrase, const string &delimiter) {
    vector<string> list;
    string s = string(std::move(phrase));
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
        throw "INVALID ARGUMENT EXCEPTION";

    return list;
}

vector<string> CardParser::getFileLines(const string &filePath) {
    fstream cardFile;
    cardFile.open(filePath, ios::in);

    if (!cardFile.is_open())
        throw "FILE EXCEPTION";

    string line;
    vector<string> lines;

    while (getline(cardFile, line))
        if (line.find_first_not_of(' ') != string::npos) //not an empty line
            lines.push_back(trim(line));


    return lines;
}

//TODO refactor this, it works but is fugly, there has to be a more elegant way. Class type as a parameter?
map<string, Card *> CardParser::loadAllCards() {
    map<string, Card *> cards;

    loadBasicCards(cards);
    loadDualCards(cards);
    loadFlipCards(cards);
    addDoubleCards(cards);
    addFlexCards(cards);

    return cards;
}

void CardParser::loadFlipCards(map<string, Card *> &cards) {

    vector<string> fileLines = getFileLines(pathOf(FLIP_CARD));
    validLines(fileLines, FLIP_CARD);

    for (const string &line : fileLines) {
        pair<int, int> extractedValues = getDualValues(line);

        Card *dummy = new FlipCard(extractedValues.first, extractedValues.second);

        cards.insert(pair<string, Card *>(dummy->getDescription(), dummy));
    }
}

void CardParser::loadDualCards(map<string, Card *> &cards) {
    vector<string> fileLines = getFileLines(pathOf(DUAL_CARD));
    validLines(fileLines, DUAL_CARD);

    for (const string &line : fileLines) {
        pair<int, int> extractedValues = getDualValues(line);

        Card *dummy = new DualCard(extractedValues.first, extractedValues.second);

        cards.insert(pair<string, Card *>(dummy->getDescription(), dummy));
    }
}

void CardParser::loadBasicCards(map<string, Card *> &cards) {
    vector<string> fileLines = getFileLines(pathOf(BASIC_CARD)); //TODO CONCATENATE STRINGS
    validLines(fileLines, BASIC_CARD);

    for (const string &line : fileLines) {
        Card *dummy = new BasicCard(stoi(line));

        cards.insert(pair<string, Card *>(dummy->getDescription(), dummy));
    }
}

pair<int, int> CardParser::getDualValues(const string &line) {
    pair<int, int> values;

    vector<string> tokenisedLine = split(line, DUAL_DELIMITER);

    values.first = stoi(tokenisedLine[0]);
    values.second = stoi(tokenisedLine[1]);

    return values;
}

//TODO need to reconsider this method's implementation
void CardParser::validLines(vector<string> fileLines, const string& mode) {

    if (mode == BASIC_CARD) {
        for (const string &line : fileLines)
            stoi(line); //TODO throws an exception when NaN - maybe TRY CATCH ?

    } else {
        for (const string &line : fileLines) {
            size_t delimiterIndex = line.find(DUAL_DELIMITER);
            if (delimiterIndex == string::npos)
                throw "INVALID DUAL CARD FORMAT, MISSING DELIMITER"; //TODO proper exception
        }
    }
}

void CardParser::addDoubleCards(map<string, Card *> &cards) {
    Card *dummy = new DoubleCard();
    cards.insert(pair<string, Card *>(dummy->getDescription(), dummy));
}

void CardParser::addFlexCards(map<string, Card *> &cards) {
    Card *dummy = new FlexCard();
    cards.insert(pair<string, Card *>(dummy->getDescription(), dummy));
}

string CardParser::pathOf(const string &filename) { return CARD_FOLDER_PATH + filename; }
