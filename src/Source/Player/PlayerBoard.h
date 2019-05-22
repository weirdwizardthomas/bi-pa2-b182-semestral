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

/**
 * Contains all the player's information bound to the current round of the Game
 */
class PlayerBoard {

private:
    //Attributes--------------------------
    int currentScore; /*<! Amount of points scored in the current round */
    size_t roundsWon; /*<! Amount of rounds won in the current game*/
    bool standing; /*<! If the player is standing, they are skipping all of their turns within the current round */
    std::vector<int> playedCards; /*<! Numerical values of all the cards played in the current round */
    std::vector <BasicCard> mainDeck; /*<! Remaining auto-played cards in a given round */
    RandomNumberGenerator randomNumberGenerator; /*<! Generator for picking cards from the mainDeck */

    /**
     * Populates the main deck with copies of each BasicCard
     * @see PlayerBoard::MAIN_DECK_CARD_COPIES
     */
    void generateMainDeck();

    /**
     * Loads the line representing PlayerBoard::playedCards from a file
     * @param[in] file Game file to be read from
     * @return Container of numerical values of all played cards in play order
     */
    static std::vector<int> loadPlayedCards(std::ifstream &file);

    /**
     * Loads the PlayerBoard::currentScore from a file
     * @param[in] file Game file to be read from
     * @return Current score loaded from the file
     */
    static int loadCurrentScore(std::ifstream &file);

    /**
     * Load the PlayerBoard::roundsWon from a file
     * @param[in] file Game file to be read from
     * @return Rounds won loaded from the  file
     */
    static size_t loadRoundsWon(std::ifstream &file);

    /**
     * Load the PlayerBoard::standing attribute from the file
     * @param[in] file Game file to be read from
     * @return True if the value read was PlayerBoard::IS_STANDING_VALUE, false otherwise
     */
    static bool loadStanding(std::ifstream &file);

    /**
     * Loads a PlayerBoard::mainDeck from its text representation from a file
     * @param[in] file Game file to be read from
     * @return Container representing PlayerBoard::mainDeck
     */
    static std::vector <BasicCard> loadMainDeck(std::ifstream &file);

    /**
     * Adds all the values of the PlayerBoard::playedCards' together and assigns the result to PlayerBoard::currentScore
     */
    void recalculateScore();

    /**
     * Empties the PlayerBoard::playedCards contents.
     */
    void resetPlayedCards();

public:
    static const size_t TABLE_SIZE;/*<! Maximum number of Cards that can be played in a round */
    static const size_t MAIN_DECK_CARD_COPIES; /*<! Number of identical copies of each card in the mainDeck */
    static const char *PLAYED_CARDS_DELIMITER; /*<! Delimiter to separate
                                                * individual numerical values of elements of 'playedCards' in a file */
    static const char *ROUNDS_WON_LEAD;/*<! Leading string for the 'roundsWon'  member in a file */
    static const char *CURRENT_SCORE_LEAD;/*<! Leading string for the 'currentScore' member in a file */
    static const char *ITEM_LIST_DELIMITER;/*<! String that separates the item index in a list from a value */
    static const char *MAIN_DECK_LEAD;/*< Leading string for the 'mainDeck' member size in a file! */
    static const char *CARDS_PLAYED_LEAD;/*<! Leading string for the 'playedCards' member in a file */
    static const char *IS_STANDING_LEAD;/*<! Leading string for the 'standing' member in a file */
    static const char *IS_STANDING_VALUE;/*<! Text representation of the 'true' state of 'standing*/
    static const char *IS_NOT_STANDING_VALUE;/*<! Text representation of the 'false' state of 'standing*/
    static const char *ITEM_INDEX_LEAD;/*<! Leading string for item index in a file */

    /**
     * Creates an instance  with a generated main deck, with other attributes set to default.
     */
    PlayerBoard();

    /**
     * Saves the board's contents to a text representation within a file
     * @param file Stream in which the board is to be saved
     */
    void saveToFile(std::ofstream &file) const;

    /**
     * Gets a random BasicCard from the main deck and then removes it
     * @return Value of the removed card
     */
    int drawCardFromMainDeck();

    /**
     * Gets the current round's score
     * @see PlayerBoard::currentScore
     * @return Current round's score
     */
    int getCurrentScore() const;

    /**
     * Gets a random card from the main deck and shows its value without removing the card
     * @see PlayerBoard::mainDeck
     * @return Value of a randomly selected card from the main deck
     */
    int getOpener();

    /**
     * Gets the container of all the cards played so far withing the current round
     * @see PlayerBoard::playedCards
     * @return A container of played cards
     */
    std::vector<int> &getPlayedCards();

    /**
     * Gets the number of cards played in current round
     * @see PlayerBoard::playedCards
     * @return count of cards played in the current round
     */
    size_t getPlayedCardsCount() const;

    /**
     * Gets the total rounds won in the current game
     * @see PlayerBoard::roundsWon
     * @return Current game's rounds won by the instance owner
     */
    size_t getRoundsWon() const;

    /**
     * Shows whether the player is standing(skipping all their turns within the current round) or not
     * @see PlayerBoard::standing
     * @return True if is standing, false otherwise
     */
    bool isStanding() const;

    /**
     * Creates a text representation of the PlayerBoard::playedCards container
     * @return Text representation of all the cards played so far in the current round
     */
    std::string showCardsPlayed() const;

    /**
     * Adds a card's value to PlayerBoard::playedCards
     * @param cardValue Value to be added to the end of PlayerBoard::playedCards
     */
    void addPlayedCard(int cardValue);

    /**
     * Increments the 'roundsWon' counter
     * @see PlayerBoard::roundsWon
     */
    void addPoint();

    /**
     * Loads the instance from its text representation from a file
     * @param file File from which the instance will be instantiated
     * @param database Database containing all the available cards
     * @return PlayerBoard instance loaded from the file
     */
    static PlayerBoard loadFromFile(std::ifstream &file, const CardDatabase &database);

    /**
     * Resets the current round's score, cards played and standing to their default values
     */
    void reset();

    /**
     * Changes the PlayerBoard::standing attribute to true
     * The player will be skipping all their turns in the current round as a result
     */
    void stand();
};


#endif //TMPPAZAAK_PLAYERBOARD_H
