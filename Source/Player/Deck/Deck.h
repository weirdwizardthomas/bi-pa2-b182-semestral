//
// Created by tomtom on 08/02/19.
//

#ifndef PAZAAK_DECK_H
#define PAZAAK_DECK_H


#include <vector>
#include <list>
#include <random>
#include <algorithm>
#include <cstdlib>
#include <dirent.h>

#include "../../Cards/Card.h"
#include "../../Cards/BasicCard.h"
#include "../../Cards/DoubleCard.h"
#include "../../Cards/FlexCard.h"
#include "../../Cards/FlipCard.h"
#include "../../Utilities/RandomNumberGenerator.h"
#include "../../Cards/CardDatabase.h"

/**
 *
 */
class Deck {
private:
    //Attributes----------------------------------------------
    std::vector<Card *> cards;
    RandomNumberGenerator randomGenerator;

    //Methods-------------------------------------------------
    /**
     * Adds a Card pointer to the 'cards' container
     * @param card Pointer to a card to be added
     */
    void addCard(Card *card);

    /**
     * Queries the player with a choice of card indices to add to the deck.
     * @param allCards All Cards eligible to be placed in the a deck.
     */
    void loadCardsFromUser(const CardDatabase &allCards);

    /**
     * Removes a single card at the'pickedCardIndex' from the 'cards' container.
     * @param pickedCardIndex Index of the card to be removed from the 'cards' container
     */
    void removeCardFromDeck(size_t pickedCardIndex);

    /**
     * Determines whether a file @param filename already exists in a directory.
     * @param files Names of existing files.
     * @param filename Name of the saving file to be compared to the existing ones.
     * @return True if a file @param filename already exists, false otherwise.
     */
    static bool fileAlreadyExists(const std::vector<std::string> &files, const std::string &filename);

    //Messages and prompts----------------------------------------------------------------------------------------------
    /**
     * Prompts the user to enter a name for the file representing the deck.
     */
    static void deckNamePrompt();

    /**
     * Informs the user that the custom deck has been created successfully.
     */
    static void deckForgedMessage();

    /**
     * Displays all the deck files, represented by @param files to the user.
     * @param files Names of the deck files.
     */
    static void displayDecksMessage(const std::vector<std::string> &files);

    /**
     * Informs the user that a file already exists.
     */
    static void fileExistsMessage();

    /**
     * Informs the user that the input is not valid for the given scenario.
     */
    static void invalidInputMessage();

    /**
       * Queries the user to enter a filename for the saving file.
       * @param files Existing file names.
       * @return name of the saving file.
       */
    static std::string QueryUserInputFilename(const std::vector<std::string> &files);

    /**
     * Informs the user of how many cards they are to add to their deck.
     */
    static void selectCardsDeckSizePrompt();

    /**
     * Displays the card at the @param index of the deck's 'cards' container to the user.
     * @param index Index of the card to be displayed.
     */
    void selectedCardMessage(size_t index) const;

public:
    static const size_t DECK_SIZE;
    static const size_t MAX_CARDS_DRAWN;
    static const char *DECK_FILE_LEAD;
    static const char *LEFT_INDEX_BRACKET;
    static const char *RIGHT_INDEX_BRACKET;

    //Constructors--------------------------------------------
    Deck();

    /**
     * Creates a new @class Deck instance by querying the user to pick individual cards from the @param cardDatabase database
     * @param cardDatabase
     * @overload
     */
    explicit Deck(const CardDatabase &cardDatabase);

    /**
     * Creates a @class Deck instance with the @param cards parameter as its 'cards' container.
     * @param cards Card container to represent the deck.
     * @overload
     */
    explicit Deck(std::vector<Card *> cards);

    //Methods--------------------------------------------------
    /**
     * Randomly selects up to four cards(if there are enough, otherwise fewer), removes them from the Deck and passes them.
     * @return Up to 'MAX_CARDS_DRAWN' random Cards.
     */
    std::vector<Card *> drawCardsFromDeck();

    /**
     * Converts the deck's contents to a format suitable for saving to a file.
     * @return Container of lines, each representing a single card from the deck.
     */
    std::list<std::string> toLines() const;

    /**
     * Saves the deck's contents to a readable form in the DECKS_DIRECTORY_PATH to be reconstructed later.
     */
    void saveToFile() const;

    /**
     * Saves the deck's contents to a readable form into the @param file stream to be reconstructed later.
     * @param file Stream representing the output file.
     */
    void saveToFile(std::ofstream &file) const;

    /**
     * Displays contents of the cards' container in the @param out stream.
     * @param out Stream in which the Deck will be placed.
     * @param deck Deck to be placed into the stream.
     * @return @param out stream containing the deck's contents
     */
    friend std::ostream &operator<<(std::ostream &out, const Deck &deck);

    /**
     * Loads the deck from its text representation in @param file with the aid of @param cardDatabase database.
     * @param file File containing the deck's text representation.
     * @param cardDatabase Database of all available cards.
     * @return Instance of the @class Deck loaded from @param file
     */
    static Deck loadFromFile(std::ifstream &file, const CardDatabase &cardDatabase);

};

#endif //PAZAAK_DECK_H
