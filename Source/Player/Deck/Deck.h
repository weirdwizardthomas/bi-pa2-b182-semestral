//
// Created by tomtom on 08/02/19.
//

#ifndef PAZAAK_DECK_H
#define PAZAAK_DECK_H

//Libraries---------------------------------
#include <vector>
#include <random>
#include <algorithm>
#include <cstdlib>
#include <dirent.h>

//Classes-----------------------------------
#include "../../Cards/CardInterface/Card.h"
#include "../../Cards/CardImplementations/BasicCard/BasicCard.h"
#include "../../Cards/CardImplementations/DoubleCard/DoubleCard.h"
#include "../../Cards/CardImplementations/DualCard/FlexCard/FlexCard.h"
#include "../../Cards/CardImplementations/DualCard/FlipCard/FlipCard.h"
#include "../Hand/Hand.h"

//Definitions-------------------------------
#define NEWLINE '\n'
#define SPACE " "

#define DECKS_DIRECTORY_PATH "../Data/Decks"
#define FOLDER_DELIMITER "/"
#define FILE_CARD_VALUE_DELIMITER ","
#define CARD_TYPE_VALUE_DELIMITER ":"

#define DECK_SIZE 10

#define BASIC_CARD_LEAD "BasicCards"
#define DOUBLE_CARD_LEAD "DoubleCards"
#define DUAL_CARD_LEAD "DualCards"
#define FLEX_CARD_LEAD "FlexCards"
#define FLIP_CARD_LEAD "FlipCards"

class Deck {
private:
    //Attributes----------------------------------------------
    std::vector<Card *> cards;

    /**
     * Queries the player with a choice of card indices to add to the deck
     * @param allCards All Cards eligible to be placed in the a deck
     */
    void loadCardsFromUser(const std::map<std::string, Card *> &allCards);

    /**
     * Adds the Card pointer to the Deck's container
     * @param card Pointer to a card to be added
     */
    void addCard(Card *card);

    void addLeadingCategories(std::vector<std::string> *categorised) const;

    bool fileAlreadyExists(const std::vector<std::string> &files, const std::string &filename) const;

public:
    Deck() = default;

    Deck(const std::map<std::string, Card *> &allCards);

    Deck(const std::vector<Card *> &cards);

    /**
     * Assuming a shuffled deck, moves HAND_SIZE number of cards from deck to the hand
     * @param currentHand Deck owner's current hand to be endowed with a set of cards
     * @return updated hand with up to four cards from the deck
     */
    Hand *drawCards(Hand *currentHand);

    int playCard(size_t cardIndex, std::vector<int> &playedCards, int currentScore, int opponentScore);

    /**
     * Shows Deck's container's size
     * @return number of Cards in the deck
     */
    size_t getDeckSize() const;

    /**
     * Displays contents of the cards' container in the stream
     * @param out stream in which the Deck will be placed
     * @param deck Deck to be streamed
     * @return the input stream
     */
    friend std::ostream &operator<<(std::ostream &out, const Deck &deck);

    void saveToFile() const;

//-----------------------------------------------------------------------------------------
//Deck loading from file
public:
    /**
     * Constructs a deck based on contents of a user chosen file within the Data/Decks directory
     * @param allCards Map of all available cards, used as a database
     * @return Deck containing cards corresponding to records in a file
     */
    static Deck loadFromFile(const std::map<std::string, Card *> &allCards);

private:
    /**
     * Finds all non-trivial (excluding current and parent folder references) files in the /Data/Decks directory
     * @return names of files within /Data/Decks/ directory
     */
    static std::vector<std::string> getDecksFromDirectory();

    /**
     * loads content of a single file in DECKS_DIRECTORY_PATH
     * @param file name of the file to be opened
     * @return individual lines of the file
     */
    static std::vector<std::string> loadFileContent(std::string file);

    /**
     * Splits the phrase string by the delimiter string into substrings
     * @param phrase Line to be parsed by the delimiter
     * @param delimiter Delimiter by which the string will be split
     * @return Vector of substring lying between delimiters
     */
    static std::vector<std::string> splitStringByDelimiter(std::string phrase, const std::string &delimiter);

    /**
     * Processes the text file and splits it by the delimiter CARD_TYPE_VALUE_DELIMITER into key and value
     * @param deckFileContent Text file to be processed
     * @return Map of lines of the text file split by the CARD_TYPE_VALUE_DELIMITER
     */
    static std::map<std::string, std::vector<std::string>> parseAllFileLines(std::vector<std::string> &deckFileContent);

    /**
     * Based on the chosen file inserts appropriate card into a vector
     * @param allCards Map of all available cards
     * @param deckFileContent File from which the cards will be extracted
     * @return Vector of cards based on the file
     */
    static std::vector<Card *>
    parseLinesForCards(const std::map<std::string, Card *> &allCards, std::vector<std::string> &deckFileContent);

    /**
     * Given a string, extracts two values per delimiter and converts them into integers
     * @param value String to be parsed
     * @return Pointer to a 2 element array of the parsed integers
     */
    static int *getDualValuesFromString(const std::string &value);

    /**
     * Extracts a single integer representing the card count of the constant, valueless cards - Double, Flip
     * @param lineValues String to be processed
     * @return Count of cards of the given type to be added
     */
    static int singleParameterValue(const std::vector<std::string> &lineValues);

    /**
     *
     * @param allCards
     * @param cards
     * @param cardCount
     */
    static void
    insertDoubleCards(const std::map<std::string, Card *> &allCards, std::vector<Card *> &cards, int cardCount);

    /**
     *
     * @param allCards
     * @param cards
     * @param cardcount
     */
    static void
    insertFlexCards(const std::map<std::string, Card *> &allCards, std::vector<Card *> &cards, int cardcount);

    /**
     *
     * @param allCards
     * @param cards
     * @param currentLineValues
     */
    static void insertBasicCards(const std::map<std::string, Card *> &allCards, std::vector<Card *> &cards,
                                 const std::vector<std::string> &currentLineValues);

    /**
     *
     * @param cards
     * @param currentLineValues
     * @param allCards
     */
    static void
    insertDualCards(const std::map<std::string, Card *> &allCards, std::vector<Card *> &cards,
                    const std::vector<std::string> &currentLineValues);

    /**
     *
     * @param cards
     * @param currentLineValues
     * @param allCards
     */
    static void
    insertFlipCards(const std::map<std::string, Card *> &allCards, std::vector<Card *> &cards,
                    const std::vector<std::string> &currentLineValues);

    /**
     * Queries the user with deck name to pick from
     * @param files Contents of the /Data/Decks directory
     * @return index of the deck chosen
     */
    static size_t userDeckIndexInput(const std::vector<std::string> &files);

    std::vector<std::string> parseDeckForCards() const;

    std::string QueryUserInputFilename(const std::vector<std::string> &files) const;

    void convertFlipCardToFileFormat(std::vector<std::string> *categorised) const;
};

#endif //PAZAAK_DECK_H