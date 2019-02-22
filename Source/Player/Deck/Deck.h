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
#include "../Hand/Hand.h"

//Definitions-------------------------------
#define NEWLINE '\n'
#define SPACE ' '
#define DECKS_DIRECTORY_PATH "../Data/Decks"
#define DECK_SIZE 10
#define FILE_CARD_VALUE_DELIMITER ","
#define CARD_TYPE_VALUE_DELIMITER ":"

#define BASIC_CARD_LEAD "BasicCard:"
#define DOUBLE_CARD_LEAD "DoubleCards:"
#define DUAL_CARD_LEAD "DualCards:"
#define FLEX_CARD_LEAD "FlexCards:"
#define FlIP_CARD_LEAD "FlipCards:"


class Deck {
private:
    std::vector<Card *> cards;

    void getCardChoicesFromUser(const std::map<std::string, Card *> &allCards);

    /**
     * Adds the Card pointer to the Deck's container
     * @param card Pointer to a card to be added
     */
    void addCard(Card *card);

    /**
     * finds all non-trivial (excluding current and parent folder references) files in the /Data/Decks directory
     * @return names of files within /Data/Decks/ directory
     */
    static std::vector<std::string> getDecksFromDirectory();

    /**
     * loads content of a single file in DECKS_DIRECTORY_PATH
     * @param file name of the file to be opened 
     * @return individual lines of the file
     */
    static std::vector<std::string> loadFileContent(std::string file);

    static std::vector<std::string> parseCardValues(std::string phrase, const std::string &delimiter);

    static std::map<std::string,std::vector<std::string>> parseAllFileLines(std::vector<std::string> &deckFileContent);

public:
    Deck() = default;

    Deck(std::map<std::string, Card *> &allCards);

    Deck(const std::vector<Card *> &cards);

    /**
     * Assuming a shuffled deck, moves HAND_SIZE number of cards from deck to the hand
     * @param currentHand Deck owner's current hand to be endowed with a set of cards
     * @return updated hand with up to four cards from the deck
     */
    Hand *drawCards(Hand *currentHand);

    int playCard(size_t cardIndex, std::vector<int> &playedCards, int currentScore, int opponentScore);

    /**
     *
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

    /**
     * Queries the user with deck name to pick from
     * @param files Contents of the /Data/Decks directory
     * @return index of the deck chosen
     */
    static size_t userDeckIndexInput(const std::vector<std::string> &files);

    static Deck loadFromFile();


};


#endif //PAZAAK_DECK_H
