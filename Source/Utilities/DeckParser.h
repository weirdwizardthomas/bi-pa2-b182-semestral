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
     * Loads content of a single file, represented by @param file in DECKS_DIRECTORY_PATH
     * @param file Name of the file to be opened
     * @return Individual lines of the file
     */
    static const std::vector<std::string> loadFileContent(const std::string &file);

    /**
     * Loads all the cards represented by @param fileLines to their respective @class Card instances.
     * @param cardDatabase Map of all available cards
     * @param fileLines File from which the cards will be extracted
     * @return Vector of cards based on the file.
     */
    static std::vector<Card *>
    parseLinesForCards(const CardDatabase &cardDatabase, const std::vector<std::string> &fileLines);


    /**
     * Lists all existing decks within DECK_DIRECTORY directory, represented by @param files
     * and queries the user  to pick a file's index
     * @param files Contents of the DECKS_DIRECTORY
     * @return index of the file chosen
     */
    static size_t userDeckIndexInput(const std::vector<std::string> &files);

    /**
     * Displays all files' names, represented by @param files
     * @param files Container of all the names of files in 'DECK_DIRECTORY' directory
     */
    static void listDecksMessage(const std::vector<std::string> &files);

    /**
     * Prompts the user to select a deck
     */
    static void selectDeckPrompt();

    /**
     * Informs the user that the input is not valid for the given scenario
     */
    static void invalidInputMessage();

public:
    static const char NEWLINE;
    static const char *FOLDER_DELIMITER;
    static const char *CARD_DESCRIPTION_DELIMITER;
    static const char *DECKS_DIRECTORY;
    static const char *BASIC_CARD_LEAD;
    static const char *DOUBLE_CARD_LEAD;
    static const char *DUAL_CARD_LEAD;
    static const char *FLEX_CARD_LEAD;
    static const char *FLIP_CARD_LEAD;

    /**
     * Constructs a deck based on contents of a user chosen file within the 'DECK_DIRECTORY' directory with the aid of
     * the @param cardDatabase
     * @param cardDatabase Database of all the current cards
     * @return Deck containing cards corresponding to records in a file
     */
    static Deck loadFromFile(const CardDatabase &cardDatabase);

    /**
     * Finds all non-trivial (excluding current and parent folder references) files in the 'DECK_DIRECTORY' directory
     * @return names of files within 'DECK_DIRECTORY' directory
     */
    static std::vector<std::string> getDecksFromDirectory();
};


#endif //PAZAAK_DECKPARSER_H
