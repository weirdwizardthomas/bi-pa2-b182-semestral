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
     * Loads content of a single file in DECKS_DIRECTORY_PATH.
     * @param file Name of the file to be opened.
     * @return Individual lines of the file.
     */
    static const std::vector<std::string> loadFileContent(const std::string &file);

    /**
     * Loads all the cards represented by 'fileLines' to their respective 'Card' instances.
     * @param allCards Map of all available cards.
     * @param fileLines File from which the cards will be extracted.
     * @return Vector of cards based on the file.
     */
    static std::vector<Card *>
    parseLinesForCards(const CardDatabase &allCards, const std::vector<std::string> &fileLines);


    /**
     * Queries the user with deck name to pick from.
     * @param files Contents of the /Data/Decks directory.
     * @return index of the deck chosen.
     */
    static size_t userDeckIndexInput(const std::vector<std::string> &files);

    /**
     * Displays all filenames of the 'DECK_DIRECTORY' directory.
     * @param files Container of all the names of files in 'DECK_DIRECTORY' directory.
     */
    static void listDecksMessage(const std::vector<std::string> &files);

    /**
     * Prompts the user to select a deck.
     */
    static void selectDeckPrompt();

    /**
     * Informs the user that the input is not valid for the given scenario.
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
     * the CardDatabase.
     * @param allCards Database of all the current cards.
     * @return Deck containing cards corresponding to records in a file.
     */
    static Deck loadFromFile(const CardDatabase &allCards);

    /**
     * Finds all non-trivial (excluding current and parent folder references) files in the 'DECK_DIRECTORY' directory.
     * @return names of files within 'DECK_DIRECTORY' directory.
     */
    static std::vector<std::string> getDecksFromDirectory();
};


#endif //PAZAAK_DECKPARSER_H
