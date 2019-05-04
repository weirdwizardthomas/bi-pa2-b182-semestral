//
// Created by tomtom on 03/05/19.
//

#ifndef PAZAAK_DECKPARSER_H
#define PAZAAK_DECKPARSER_H


#include <vector>
#include <string>
#include <map>
#include "../Player/Deck.h"

class DeckParser {

private:
    /**
     * Given a string, extracts two values per delimiter and converts them into integers
     * @param value String to be parsed
     * @return Pointer to a 2 element array of the parsed integers
     */
    static pair<int, int> getDualValuesFromString(const std::string &value);

    /**
     * loads content of a single file in DECKS_DIRECTORY_PATH
     * @param file name of the file to be opened
     * @return individual lines of the file
     */
    static std::vector<std::string> loadFileContent(const std::string &file);

    /**
     *
     * @param allCards
     * @param cards
     * @param currentLineValues
     */
    static void loadBasic(const std::map<std::string, Card *> &allCards, std::vector<Card *> &cards,
                          const std::vector<std::string> &currentLineValues);

    /**
     *
     * @param cards
     * @param currentLineValues
     * @param allCards
     */
    static void loadDual(const std::map<std::string, Card *> &allCards, std::vector<Card *> &cards,
                         const std::vector<std::string> &currentLineValues);

    /**
     *
     * @param allCards
     * @param cards
     * @param cardCount
     */
    static void
    loadDouble(const std::map<std::string, Card *> &allCards, std::vector<Card *> &cards, int cardCount);

    /**
     *
     * @param allCards
     * @param cards
     * @param cardCount
     */
    static void
    loadFlex(const std::map<std::string, Card *> &allCards, std::vector<Card *> &cards, int cardCount);

    /**
     *
     * @param cards
     * @param currentLineValues
     * @param allCards
     */
    static void
    loadFlip(const std::map<std::string, Card *> &allCards, std::vector<Card *> &cards,
             const std::vector<std::string> &currentLineValues);

    /**
     * Processes the text file and splits it by the delimiter CARD_TYPE_VALUE_DELIMITER into key and value
     * @param fileLines Text file to be processed
     * @return Map of lines of the text file split by the CARD_TYPE_VALUE_DELIMITER
     */
    static std::map<std::string, std::vector<std::string>> parseAllFileLines(std::vector<std::string> &fileLines);

    /**
     * Based on the chosen file inserts appropriate card into a vector
     * @param allCards Map of all available cards
     * @param fileLines File from which the cards will be extracted
     * @return Vector of cards based on the file
     */
    static std::vector<Card *>
    parseLinesForCards(const std::map<std::string, Card *> &allCards, std::vector<std::string> &fileLines);

    /**
  * Extracts a single integer representing the card count of the constant, valueless cards - Double, Flip
  * @param lineValues String to be processed
  * @return Count of cards of the given type to be added
  */
    static int singleParameterValue(const std::vector<std::string> &lineValues);

    /**
     * Queries the user with deck name to pick from
     * @param files Contents of the /Data/Decks directory
     * @return index of the deck chosen
     */
    static size_t userDeckIndexInput(const std::vector<std::string> &files);

    /**
   *
   * @param files
   */
    static void listDecksMessage(const std::vector<std::string> &files);

    /**
        *
        */
    static void selectDeckPrompt();

    static void invalidInputMessage();

public:
    static const char NEWLINE;
    static const std::string FOLDER_DELIMITER;
    static const std::string FILE_CARD_VALUE_DELIMITER;
    static const std::string CARD_TYPE_VALUE_DELIMITER;
    static const std::string DECKS_DIRECTORY_PATH;
    static const std::string BASIC_CARD_LEAD;
    static const std::string DOUBLE_CARD_LEAD;
    static const std::string DUAL_CARD_LEAD;
    static const std::string FLEX_CARD_LEAD;
    static const std::string FLIP_CARD_LEAD;


    /**
    * Constructs a deck based on contents of a user chosen file within the Data/Decks directory
    * @param allCards Map of all available cards, used as a database
    * @return Deck containing cards corresponding to records in a file
    */
    static Deck loadFromFile(const std::map<std::string, Card *> &allCards);

    /**
     * Finds all non-trivial (excluding current and parent folder references) files in the /Data/Decks directory
     * @return names of files within /Data/Decks/ directory
     */
    static std::vector<std::string> getDecksFromDirectory();

    static std::vector<std::string> splitStringByDelimiter(std::string phrase, const std::string &delimiter);

};


#endif //PAZAAK_DECKPARSER_H
