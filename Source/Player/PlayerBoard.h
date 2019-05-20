//
// Created by tomtom on 08/02/19.
//

#ifndef TMPPAZAAK_PLAYERBOARD_H
#define TMPPAZAAK_PLAYERBOARD_H


#include <vector>

#include "../Cards/Card.h"
#include "../Cards/BasicCard.h"
#include "../Utilities/RandomNumberGenerator.h"
#include "../Cards/CardDatabase.h"


class PlayerBoard {

private:
    //Attributes--------------------------
    int currentScore;
    size_t roundsWon;
    bool standing;
    std::vector<int> playedCards;
    std::vector<BasicCard> mainDeck;
    RandomNumberGenerator randomNumberGenerator;

    /**
     * Populates the main deck with 'MAIN_DECK_CARD_COPIES' of each BasicCard.
     */
    void generateMainDeck();

    /**
     * Loads the line representing 'playedCards' from the 'file' file.
     * @param file Game file to be read from.
     * @return
     */
    static std::vector<int> loadPlayedCards(std::ifstream &file);

    /**
     * Loads the current round's score from the 'file' file.
     * @param file Game file to be read from.
     * @return Current score loaded from the 'file'.
     */
    static int loadCurrentScore(std::ifstream &file);

    /**
     * Load the current game's rounds won from the 'file' file.
     * @param file Game file to be read from.
     * @return Rounds won loaded from the 'file'.
     */
    static size_t loadRoundsWon(std::ifstream &file);

    /**
     * Load the 'standing' attribute from the 'file' file.
     * @param file Game file to be read from.
     * @return True if the value read was 'IS_STANDING_VALUE', false otherwise.
     */
    static bool loadStanding(std::ifstream &file);

    /**
     * Loads the mainDeck from its text representation with the aid of the 'file' file.
     * @param file Game file to be read from.
     * @return Container representing the mainDeck from file.
     */
    static std::vector<BasicCard> loadMainDeck(std::ifstream &file);

    /**
     * Adds all the values of the 'playedCards' together and assigns the result to 'currentScore'
     */
    void recalculateScore();

    /**
     * Empties the 'playedCards' contents.
     */
    void resetPlayedCards();

public:
    static const size_t TABLE_SIZE;
    static const size_t MAIN_DECK_CARD_COPIES;
    static const char *PLAYED_CARDS_DELIMITER;
    static const char *ROUNDS_WON_LEAD;
    static const char *CURRENT_SCORE_LEAD;
    static const char *ITEM_LIST_DELIMITER;
    static const char *MAIN_DECK_LEAD;
    static const char *CARDS_PLAYED_LEAD;
    static const char *IS_STANDING_LEAD;
    static const char *IS_STANDING_VALUE;
    static const char *IS_NOT_STANDING_VALUE;
    static const char *ITEM_INDEX_LEAD;

    PlayerBoard();

    /**
     * Saves the board's contents to a text representation within the 'file' stream.
     * @param file Stream in which the board is to be saved.
     */
    void saveToFile(std::ofstream &file) const;

    //Getters----------------------------
    /**
     * Gets a random card from the main deck and then removes it.
     * @return Value of the removed card.
     */
    int drawCardFromMainDeck();

    /**
     * Gets the current round's score.
     * @return Current round's score.
     */
    int getCurrentScore() const;

    /**
     * Gets a random card from the 'mainDeck' and shows its value without removing the card.
     * @return Value of a randomly selected card from the 'mainDeck'.
     */
    int getOpener();

    /**
     * Gets the container of all the cards played so far withing the current round.
     * @return A container of cards identical to 'playedCards'
     */
    std::vector<int> &getPlayedCards();

    /**
     * Gets the number of cards played in current round.
     * @return size of 'playedCards'.
     */
    size_t getPlayedCardsCount() const;

    /**
     * Gets the total rounds won in the current game.
     * @return Current game's rounds won by the instance owner.
     */
    size_t getRoundsWon() const;

    /**
     * Shows whether the player is standing(skipping all their turns within the current round) or not.
     * @return True if is standing, false otherwise.
     */
    bool isStanding() const;

    /**
     * Creates a text representation of the 'playedCards' container.
     * @return Text representation of all the cards played so far in the current round.
     */
    std::string showCardsPlayed() const;

    //Setters----------------------------
    /**
     * Adds a card's value to the 'cardsPlayed' container.
     * @param cardValue Value to be added to the end of 'cardsPlayed' container.
     */
    void addPlayedCard(int cardValue);

    /**
     * Increments the 'roundsWon' counter.
     */
    void addPoint();

    /**
     * Loads the 'playerBoard' from its text representation from the 'file' stream.
     * @param file File from which the playerBoard will be instantiated.
     * @param database Database containing all the available cards.
     * @return PlayerBoard instance loaded from the 'file' file
     */
    static PlayerBoard loadFromFile(std::ifstream &file, const CardDatabase &database);

    /**
     * Resets the current round's score, cards played and standing to their default values
     */
    void reset();

    /**
     * Changes the 'standing' attribute to True.
     * The player will be skipping all their turns in the current round as a result.
     */
    void stand();
};


#endif //TMPPAZAAK_PLAYERBOARD_H
