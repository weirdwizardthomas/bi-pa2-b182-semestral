//
// Created by tomtom on 03/05/19.
//

#ifndef PAZAAK_DECKPARSER_H
#define PAZAAK_DECKPARSER_H


#include <vector>
#include <string>
#include <map>
#include "../Player/Deck/Deck.h"

/**
 * Tools responsible for loading a Deck from its text representation in a file to an instance
 */
class DeckParser {

private:
    /**
     * Loads content of a single file, represented by a file in DeckParser::DECKS_DIRECTORY_PATH
     * @param[in] file Name of the file to be opened
     * @throws InvalidFileException if the file does not exist or is corrupted
     * @return Individual lines of the file
     */
    static const std::vector <std::string> loadFileContent(const std::string &file);

    /**
     * Loads all the cards represented from file lines to their respective Card instances.
     * @param[in] cardDatabase Map of all available cards
     * @param[in] fileLines File from which the cards will be extracted
     * @return Vector of cards based on the file.
     */
    static std::vector<Card *>
    parseLinesForCards(const CardDatabase &cardDatabase, const std::vector <std::string> &fileLines);

    /**
     * Lists all existing decks within DeckParser::DECK_DIRECTORY directory
     * and queries the user  to pick a file's index
     * @param[in] files Contents of the DeckParser::DECKS_DIRECTORY
     * @return index of the file chosen
     */
    static size_t userDeckIndexInput(const std::vector <std::string> &files);

    //Messages-and-prompts-----------------------------------------------
    /**
     * Displays all files' names in the DeckParser::DECK_DIRECTORY directory
     * @param[in] files Container of all the names of files in DeckParser::DECK_DIRECTORY directory
     */
    static void listDecksMessage(const std::vector <std::string> &files);

    /**
     * Prompts the user to select a deck
     */
    static void selectDeckPrompt();

    /**
     * Informs the user that the input is not valid for the given scenario
     */
    static void invalidInputMessage();

public:
    static const char *FOLDER_DELIMITER;
    static const char *CARD_DESCRIPTION_DELIMITER;
    static const char *DECKS_DIRECTORY;
    static const char *BASIC_CARD_LEAD;
    static const char *DOUBLE_CARD_LEAD;
    static const char *DUAL_CARD_LEAD;
    static const char *FLEX_CARD_LEAD;
    static const char *FLIP_CARD_LEAD;

    /**
     * Constructs a deck based on contents of a user chosen file within the DeckParser::DECK_DIRECTORY directory
     * @param[in] cardDatabase Database of all the current cards
     * @throws InvalidFileException if the file cannot be opened or is corrupted
     * @return Deck containing cards corresponding to records in a file
     */
    static Deck loadFromFile(const CardDatabase &cardDatabase);

    /**
     * Finds all non-trivial (excluding current and parent folder references) files in the DeckParser::DECK_DIRECTORY directory
     * @return names of files within DeckParser::DECK_DIRECTORY directory
     */
    static std::vector <std::string> getDecksFromDirectory();
};


#endif //PAZAAK_DECKPARSER_H
