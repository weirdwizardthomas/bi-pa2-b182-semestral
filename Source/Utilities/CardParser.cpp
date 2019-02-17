//
// Created by tomtom on 14/02/19.
//

#include "CardParser.h"


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

vector<string> CardParser::getFileLines(string filePath) const {
    fstream cardFile;
    cardFile.open(filePath, ios::in);

    if (!cardFile.is_open())
        throw "FILE EXCEPTION";

    string line;
    vector<string> lines;

    while (getline(cardFile, line)) {
        if (line.find_first_not_of(' ') != string::npos) //not an empty line
            lines.push_back(trim(line));
    }

    return lines;
}

//TODO refactor this, it works but is fugly, there has to be a more elegant way. Class type as a parameter?
map<string, Card *> CardParser::loadAllCards() {
    map<string, Card *> cards;

    loadBasicCards(cards);
    loadDualCards(cards);
    loadFlipCards(cards);
    
    return cards;
}

void CardParser::loadFlipCards(map<string, Card *> &cards) const {
    vector<string> fileLines = getFileLines(CARD_FOLDER_PATH + files[2]);
    validLines(fileLines, FLIP_CARD);

    for (const string &line : fileLines) {
        pair<int, int> extractedValues = getDualValues(line);

        Card *dummy = new FlipCard(extractedValues.first, extractedValues.second);

        cards.insert(pair<string, Card *>(dummy->getDescription(), dummy));
    }
}

void CardParser::loadDualCards(map<string, Card *> &cards) const {
    vector<string> fileLines = getFileLines(CARD_FOLDER_PATH + files[1]);
    validLines(fileLines, DUAL_CARD);

    for (const string &line : fileLines) {
        pair<int, int> extractedValues = getDualValues(line);

        Card *dummy = new DualCard(extractedValues.first, extractedValues.second);

        cards.insert(pair<string, Card *>(dummy->getDescription(), dummy));
    }
}

void CardParser::loadBasicCards(map<string, Card *> &cards) const {
    vector<string> fileLines = getFileLines(CARD_FOLDER_PATH + files[0]); //TODO CONCATENATE STRINGS
    validLines(fileLines, BASIC_CARD);

    for (const string &line : fileLines) {
        Card *dummy = new BasicCard(stoi(line));

        cards.insert(pair<string, Card *>(dummy->getDescription(), dummy));
    }
}

pair<int, int> CardParser::getDualValues(const string &line) const {
    pair<int, int> values;

    vector<string> tokenisedLine = split(line, DUAL_DELIMITER);

    values.first = stoi(tokenisedLine[0]);
    values.second = stoi(tokenisedLine[1]);

    return values;
}

//TODO need to reconsider this method's implementation
void CardParser::validLines(vector<string> fileLines, string mode) const {

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