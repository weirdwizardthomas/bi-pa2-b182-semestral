//
// Created by tomtom on 09/02/19.
//

#ifndef PAZAAK_HAND_H
#define PAZAAK_HAND_H

#include <iostream>

#include "../Cards/Card.h"
#include "../Cards/CardDatabase.h"

/**
 * Collection of cards available to be played during a round.
 */
class Hand {
private:
    std::vector<Card *> cards;

public:
    static const char *HAND_FILE_LEAD;
    static const char *RIGHT_INDEX_WRAPPER;
    static const char *LEFT_INDEX_WRAPPER;

    /**
     * Adds a card pointer to Hand::cards container
     * @param[in] card Card pointer to be added
     */
    void addCard(Card *card);

    /**
     * Loads the Hand from its text representation from a file
     * @param[in] file File from which the Hand is loaded
     * @param[in] cardDatabase Database containing all the available cards
     * @return Hand instance built from a file's contents
     */
    static Hand loadFromFile(std::ifstream &file, const CardDatabase &cardDatabase);

    /**
     * Plays a single card from Hand::cards at a specific index and removes it from Hand::cards
     * @param[in] cardIndex Index of the card to be played
     * @param[in] playedCards Cards played by the this instance's owner so far
     * @param[in] currentScore Instance's owner's current score
     * @param[in] opponentScore Instance's owner's opponent's current score
     * @return Value of the played card, 0 if the card does not add any value
     */
    int playCard(size_t cardIndex, std::vector<int> &playedCards, int currentScore, int opponentScore);

    /**
     * Saves the Hand content in a text representation to a file within DeckParser::DECKS_DIRECTORY
     * @param[in] file Stream representing the output file
     */
    void saveToFile(std::ofstream &file) const;

    /**
     * Puts Hand::cards into an output stream
     * @param[in,out] out Stream in which the hand is being placed
     * @param[in] hand Hand to be put in the  output stream
     * @return output stream containing Hand::cards
     */
    friend std::ostream &operator<<(std::ostream &out, const Hand &hand);

};


#endif //PAZAAK_HAND_H
