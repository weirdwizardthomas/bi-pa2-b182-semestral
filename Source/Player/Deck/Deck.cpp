//
// Created by tomtom on 08/02/19.
//

#include "Deck.h"

//Namespaces--------------------------------
using namespace std;

Deck::Deck(const vector<Card *> &cards) : cards(cards) {}

Hand *Deck::drawCards(Hand *currentHand) {

    for (size_t i = 0; i < 4; i++) {
        if (this->cards.empty()) //no more cards to be drawn
            break;

        size_t cardIndex = generateBoundIndex();

        currentHand->addCard(this->cards[cardIndex]);
        this->cards.erase(this->cards.begin() + cardIndex);
    }

    return currentHand;
}

//copied from https://stackoverflow.com/a/19666713
size_t Deck::generateBoundIndex() const {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(0, this->cards.size());
    return (size_t) dist(mt);
}

//TODO is this actually random?
void Deck::shuffle() {
    auto rng = default_random_engine{};
    std::shuffle(std::begin(this->cards), std::end(this->cards), rng);
}

//TODO probably throw an exception
int Deck::playCard(size_t cardIndex, vector<int> &playedCards, int currentScore, int opponentScore) {
    int effect = this->cards[cardIndex]->play(playedCards, currentScore, opponentScore);

    this->cards.erase(this->cards.begin() + cardIndex);

    return effect;
}

ostream &operator<<(ostream &out, const Deck &deck) {
    int i = 0;

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
        cout << (i < 10 ? " " : "") << "(" << i++ << ")" << " " << (card.second)->getDescription() << endl;

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

    while (i != 10) {
        cout << "(" << i << "):";

        size_t input;
        cin >> input;

        if (!cin.fail()) {
            if (input < allCards.size()) {
                this->addCard(allCardsVector[input]);
                cout << "You've selected: " << *(this->cards[i - 1]) << endl;
                i++;

            } else {
                cout << "Invalid choice, please try again." << endl; //out of bounds
            }

        } else {
            cout << "Invalid input, please try again." << endl; //NaN
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),
                       NEWLINE); //ignores the entire cin until a newline is encountered
        }


    }
}

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
    } else {
        /* could not open directory */

        throw "Couldn't open directory"; //TODO better exception
    }

    return files;
}

//TODO use <filesystem>
//Adapted from https://stackoverflow.com/a/612176
Deck Deck::loadFromFile() {
    vector<string> files = getDecksFromDirectory();

    size_t input = selectDeckFile(files);

    vector<string> deckFileContent = Deck::loadFileContent(files[input]);
    for (const auto &line : deckFileContent)
        cout << line << endl;

    cout << endl;
    return Deck();
}

size_t Deck::selectDeckFile(const vector<string> &files) {
    size_t i = 0;

    cout << "Decks available" << endl;

    for (const auto &file : files)
        cout << "(" << i++ << ") " << file << endl;

    cout << "Select a deck:";

    size_t input;

    while (!(cin >> input) || input >= i) {
        cout << "Invalid input, please try again:";
        cin.clear();
        cin.ignore(10000, '\n');
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

    if (!deckFile.is_open()) {
        throw "File opening error"; //TODO proper exception
    }


    while (getline(deckFile, line)) {
        if (line.find_first_not_of(SPACE) != string::npos) { //not an empty line
            fileContent.push_back(line);
        }
    }

    deckFile.close();

    return fileContent;
}
