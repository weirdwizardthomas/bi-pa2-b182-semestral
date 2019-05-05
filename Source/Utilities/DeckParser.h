//
// Created by tomtom on 03/05/19.
//

#ifndef PAZAAK_DECKPARSER_H
#define PAZAAK_DECKPARSER_H


#include <vector>
#include <string>
#include <map>
#include "../Player/Deck/Deck.h"

class DeckParser {

private:

    /**
     * loads content of a single file in DECKS_DIRECTORY_PATH
     * @param file name of the file to be opened
     * @return individual lines of the file
     */
    static const std::vector<std::string> loadFileContent(const std::string &file);

    /**
     * Based on the chosen file inserts appropriate card into a vector
     * @param allCards Map of all available cards
     * @param fileLines File from which the cards will be extracted
     * @return Vector of cards based on the file
     */
    static std::vector<Card *>
    parseLinesForCards(const CardDatabase &allCards, const std::vector<std::string> &fileLines);

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

    /**
     *
     */
    static void invalidInputMessage();

public:
    static const char NEWLINE;
    static const char * FOLDER_DELIMITER;
    static const char * FILE_CARD_VALUE_DELIMITER;
    static const char * CARD_DESCRIPTION_DELIMITER;
    static const char * DECKS_DIRECTORY_PATH;
    static const char * BASIC_CARD_LEAD;
    static const char * DOUBLE_CARD_LEAD;
    static const char * DUAL_CARD_LEAD;
    static const char * FLEX_CARD_LEAD;
    static const char * FLIP_CARD_LEAD;


    /**
    * Constructs a deck based on contents of a user chosen file within the Data/Decks directory
    * @param allCards Map of all available cards, used as a database
    * @return Deck containing cards corresponding to records in a file
    */
    static Deck loadFromFile(const CardDatabase &allCards);

    /**
     * Finds all non-trivial (excluding current and parent folder references) files in the /Data/Decks directory
     * @return names of files within /Data/Decks/ directory
     */
    static std::vector<std::string> getDecksFromDirectory();

    /**
     *
     * @param phrase
     * @param delimiter
     * @return
     */
    static std::list<std::string> splitStringByDelimiter(std::string phrase, const std::string &delimiter);

};


#endif //PAZAAK_DECKPARSER_H
