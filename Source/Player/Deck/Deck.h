//
// Created by tomtom on 08/02/19.
//

#ifndef PAZAAK_DECK_H
#define PAZAAK_DECK_H

//Libraries---------------------------------
#include <vector>
#include <list>
#include <random>
#include <algorithm>
#include <cstdlib>
#include <dirent.h>

//Classes-----------------------------------
#include "../../Cards/Card.h"
#include "../../Cards/BasicCard.h"
#include "../../Cards/DoubleCard.h"
#include "../../Cards/FlexCard.h"
#include "../../Cards/FlipCard.h"
#include "../../Utilities/RandomNumberGenerator.h"
#include "../../Cards/CardDatabase.h"

class Deck {
private:
    //Attributes----------------------------------------------
    std::vector<Card *> cards;
    RandomNumberGenerator randomGenerator;

    //Methods-------------------------------------------------
    /**
     * Adds the Card pointer to the Deck's container
     * @param card Pointer to a card to be added
     */
    void addCard(Card *card);

    /**
     * Queries the player with a choice of card indices to add to the deck
     * @param allCards All Cards eligible to be placed in the a deck
     */
    void loadCardsFromUser(const CardDatabase &allCards);

    /**
     *
     * @param pickedCardIndex
     */
    void removeCardFromDeck(size_t pickedCardIndex);

    /**
     *
     * @param files
     * @param filename
     * @return
     */
    static bool fileAlreadyExists(const std::vector<std::string> &files, const std::string &filename);

    //Messages and prompts----------------------------------------------------------------------------------------------
    /**
     *
     */
    static void deckForgedMessage();

    /**
     *
     * @param files
     */
    static void displayDecksMessage(const std::vector<std::string> &files);

    /**
     *
     */
    static void fileExistsMessage();

    /**
     *
     */
    static void invalidInputMessage();

    /**
       * Queries the user to enter a filename for the saved file
       * @param files
       * @return
       */
    static std::string QueryUserInputFilename(const std::vector<std::string> &files);

    /**
     *
     */
    static void saveDeckAsPrompt();

    /**
     * 
     */
    static void selectCardsDeckSizePrompt();

public:
    static const int DECK_SIZE;
    static const int MAX_CARDS_DRAWN;


    //Constructors--------------------------------------------
    Deck();

    explicit Deck(const CardDatabase &allCards);

    explicit Deck(std::vector<Card *> cards);

    //Methods--------------------------------------------------
    /**
     * Randomly selects up to four cards(if there are enough, otherwise fewer), removes them from the Deck and passes them
     * @return Up to four random Cards
     */
    std::vector<Card *> drawCardsFromDeck();

    /**
     * Shows Deck's container's size
     * @return number of Cards in the deck
     */
    size_t getDeckSize() const;

    /**
     * Analyses the deck's cards and splits them based on their card type
     * @return
     */
    std::list<std::string> toLines() const;

    /**
     * Saves the deck's contents to a readable form in the DECKS_DIRECTORY_PATH to be reconstructed later
     */
    void saveToFile() const;

    /**
     * Displays contents of the cards' container in the stream
     * @param out stream in which the Deck will be placed
     * @param deck Deck to be streamed
     * @return the input stream
     */
    friend std::ostream &operator<<(std::ostream &out, const Deck &deck);

};

#endif //PAZAAK_DECK_H
