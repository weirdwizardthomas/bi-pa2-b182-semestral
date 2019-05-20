//
// Created by tomtom on 09/02/19.
//

#ifndef PAZAAK_HAND_H
#define PAZAAK_HAND_H

#include <iostream>

#include "../Cards/Card.h"
#include "../Cards/CardDatabase.h"

class Hand {
private:
    std::vector<Card *> cards;

public:
    static const char *HAND_FILE_LEAD;
    static const char *RIGHT_INDEX_WRAPPER;
    static const char *LEFT_INDEX_WRAPPER;

    /**
     * Adds the 'card' pointer to 'cards' container.
     * @param card Card pointer to be added.
     */
    void addCard(Card *card);

    /**
     * Loads the Hand from its text representation from the 'file' stream with the aid of 'cardDatabase'.
     * @param file File from which the Hand is loaded.
     * @param cardDatabase Database containing all the available cards.
     * @return Hand instance built from 'file's' contents.
     */
    static Hand loadFromFile(std::ifstream &file, const CardDatabase &cardDatabase);

    /**
     * Plays a single card from the 'cards' container at the 'cardIndex' index and removes it from 'cards'.
     * @param cardIndex Index of the card to be played.
     * @param playedCards Cards played by the this instance's owner so far.
     * @param currentScore Instance's owner's current score.
     * @param opponentScore Instance's owner's opponent's current score.
     * @return Value of the played card, 0 if the card does not add any value.
     */
    int playCard(size_t cardIndex, std::vector<int> &playedCards, int currentScore, int opponentScore);

    /**
     * Saves the hand's content in a text representation to the file represented by the 'file' stream
     * @param file Stream representing the output file
     */
    void saveToFile(std::ofstream &file) const;

    /**
       * Puts the hand's 'cards' in the 'out' stream.
       * @param out Stream in which the hand is being placed.
       * @param hand Hand to be put in the 'out' stream.
       * @return Ostream 'out' containing the 'hand'.
       */
    friend std::ostream &operator<<(std::ostream &out, const Hand &hand);

};


#endif //PAZAAK_HAND_H
