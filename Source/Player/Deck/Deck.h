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
#include "../../Cards/Card.h"
#include "../../Cards/CardImplementations/BasicCard/BasicCard.h"
#include "../../Cards/CardImplementations/DoubleCard/DoubleCard.h"
#include "../../Cards/CardImplementations/DualCard/FlexCard/FlexCard.h"
#include "../../Cards/CardImplementations/DualCard/FlipCard/FlipCard.h"

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

    static bool fileAlreadyExists(const std::vector<std::string> &files, const std::string &filename);

public:
    static const char NEWLINE;

    static const std::string DECKS_DIRECTORY_PATH;
    static const std::string FOLDER_DELIMITER;
    static const std::string FILE_CARD_VALUE_DELIMITER;
    static const std::string CARD_TYPE_VALUE_DELIMITER;
    static const int DECK_SIZE = 10;
    static const int MAX_CARDS_DRAWN = 4;
    static const std::string BASIC_CARD_LEAD;
    static const std::string DOUBLE_CARD_LEAD;
    static const std::string DUAL_CARD_LEAD;
    static const std::string FLEX_CARD_LEAD;
    static const std::string FLIP_CARD_LEAD;

    //Constructors--------------------------------------------
    Deck() = default;

    explicit Deck(const std::map<std::string, Card *> &allCards);

    explicit Deck(std::vector<Card *> cards);

    //Methods--------------------------------------------------

    /**
     * Shows Deck's container's size
     * @return number of Cards in the deck
     */
    size_t getDeckSize() const;

    /**
     * Analyses the deck's cards and splits them based on their card type
     * @return
     */
    std::vector<std::string> parseDeckForCards() const;

    /**
     * Saves the deck's contents to a readable form in the DECKS_DIRECTORY_PATH to be reconstructed later
     */
    void saveToFile() const;

    /**
     * Randomly selects up to four cards(if there are enough, otherwise fewer), removes them from the Deck and passes them
     * @return Up to four random Cards
     */
    std::vector<Card *> drawCardsFromDeck();

    /**
     * Displays contents of the cards' container in the stream
     * @param out stream in which the Deck will be placed
     * @param deck Deck to be streamed
     * @return the input stream
     */
    friend std::ostream &operator<<(std::ostream &out, const Deck &deck);

//--------------------------------------------------------------------------------------------------------------------//
//Static methods------------------------------------------------------------------------------------------------------//
//--------------------------------------------------------------------------------------------------------------------//
public:
    /**
     * Constructs a deck based on contents of a user chosen file within the Data/Decks directory
     * @param allCards Map of all available cards, used as a database
     * @return Deck containing cards corresponding to records in a file
     */
    static Deck loadFromFile(const std::map<std::string, Card *> &allCards);

private:
    /**
     * Adds the leading categories(card types) to each category in the vector to meet the required format
     * @param categorised
     */
    static void addLeadingCategories(std::vector<std::string> *categorised);

    /**
     * Converts FlipCards to their in-file form
     */
    static void convertFlipCardToFileFormat(std::vector<std::string> *categorised);

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
     * @param cardCount
     */
    static void
    insertFlexCards(const std::map<std::string, Card *> &allCards, std::vector<Card *> &cards, int cardCount);

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
     * Finds all non-trivial (excluding current and parent folder references) files in the /Data/Decks directory
     * @return names of files within /Data/Decks/ directory
     */
    static std::vector<std::string> getDecksFromDirectory();

    /**
     * Given a string, extracts two values per delimiter and converts them into integers
     * @param value String to be parsed
     * @return Pointer to a 2 element array of the parsed integers
     */
    static int *getDualValuesFromString(const std::string &value);

    /**
     * loads content of a single file in DECKS_DIRECTORY_PATH
     * @param file name of the file to be opened
     * @return individual lines of the file
     */
    static std::vector<std::string> loadFileContent(const std::string& file);

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
     * Extracts a single integer representing the card count of the constant, valueless cards - Double, Flip
     * @param lineValues String to be processed
     * @return Count of cards of the given type to be added
     */
    static int singleParameterValue(const std::vector<std::string> &lineValues);

    /**
     * Splits the phrase string by the delimiter string into substrings
     * @param phrase Line to be parsed by the delimiter
     * @param delimiter Delimiter by which the string will be split
     * @return Vector of substring lying between delimiters
     */
    static std::vector<std::string> splitStringByDelimiter(std::string phrase, const std::string &delimiter);

    /**
     *
     * @param files
     * @return
     */
    static std::string QueryUserInputFilename(const std::vector<std::string> &files);

    /**
     * Queries the user with deck name to pick from
     * @param files Contents of the /Data/Decks directory
     * @return index of the deck chosen
     */
    static size_t userDeckIndexInput(const std::vector<std::string> &files);

};

#endif //PAZAAK_DECK_H
