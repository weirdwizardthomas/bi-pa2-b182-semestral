//
// Created by tomtom on 08/02/19.
//

#ifndef PAZAAK_PLAYER_H
#define PAZAAK_PLAYER_H


#include <cstdlib>
#include <string>
#include <map>
#include <sstream>

#include "../Deck/Deck.h"
#include "../PlayerBoard.h"
#include "../Hand.h"
#include "../../Cards/CardDatabase.h"


/**
 * Representation of a party of the Game
 */
class Player {
protected:
    //Attributes---------------------------------------------------------
    std::string name;
    PlayerBoard board;

    //Methods------------------------------------------------------------
    /**
     * Plays a random card from the main deck
     * @return BasicCard::value of the picked card
     */
    int autoPlayCard();

    //Messages-and-prompts-----------------------------------------------
    /**
     * Displays information about the player's in-game objects
     * @param[in] opponentScore Opposing player's score
     */
    void boardStatusMessage(int opponentScore) const;

    /**
     * Informs the players that this player is standing and thus skipping their turns for this round
     */
    void playerIsStandingMessage() const;

    /**
     * Displays a message informing the user of their opening card
     * @param[in] opener Value of the opening card
     */
    void openerMessage(int opener) const;

    /**
     * Queries the user to pick whether they want to stand in this round
     */
    void standPrompt() const;

    /**
     * Informs the user that they are passing their turn
     */
    void isPassingTurnMessage() const;


public:
    static const char *NAME_FILE_LEAD;
    static const char *PLAYER_TYPE_DELIMITER;

    virtual ~Player() = default;

    /**
     * Creates an instance with the 'name' as its Player::name
     * @param[in] name Name to be added as a member of the instance
     */
    explicit Player(std::string name);

    /**
     * Adds a specific Deck for the player
     * @param[in] cardDatabase Database of all available cards
     */
    virtual void chooseDeck(const CardDatabase &cardDatabase) = 0;

    /**
     * Adds the ability to play more cards to the player.
     */
    virtual void drawHand() = 0;

    /** If the user is not 'standing' = skipping their turn,
     * queries the user to stand up or play, plays the top card of the playerBoard::mainDeck
     * and prompts the user to choose a card to play from their hand
     * The player may choose to stand up before the playerBoard::mainDeck card is auto-played, and may choose not to play a card
     * from their hand
     * @param[in] opponentScore Opposing player's current round score
     */
    virtual void takeTurn(int opponentScore) = 0;

    //Setters------------------------------------------------------------
    /**
     * Increments the player's counter of rounds won
     */
    void addPoint();

    /**
     * Resets all the round related attributes of the player to default values -
     * PlayerBoard::currentScore, PlayerBoard::playedCards, PlayerBoard::standing
     */
    void resetBoard();

    /**
     * Sets the PlayerBoard::standing attribute to true
     */
    void stand();

    //Getters------------------------------------------------------------
    /**
     * Gets the current round's score
     * @return Current round's score
     */
    int getCurrentRoundScore() const;

    /**
     * Gets the 'name' attribute
     * @return name
     */
    const std::string &getName() const;

    /**
     * Gets the top card of the player's main deck
     * @return Value of the deck's top card
     */
    int getOpener();

    /**
     * Gets the number of cards played in current round
     * @return Number of cards played in the current round
     */
    size_t getPlayedCardsCount() const;

    /**
     * Gets the total rounds won in the current game
     * @return Number of rounds won in the current game
     */
    size_t getRoundsWon() const;

    /**
     * Shows whether the player is standing(skipping all their turns within the current round) or not
     * @return True if is standing, false otherwise
     */
    bool isStanding() const;

    /**
     * Saves the instance in a text representation in a file
     * @param[in] file Output file into which the instance is being saved
     */
    virtual void saveToFile(std::ofstream &file) const = 0;

    /**
     * Loads the player from its text representation from a file
     * The type of player and the subsequent specific attributes are determined by the leading text in the file
     * Cards are found by the their description in the file within the database
     * @param[in] file File from which the player data will be read
     * @param[in] cardDatabase Database of all cards
     * @param[in] opponent Pointer to the opposing player
     * @return A dynamically allocated instance of the player
     */
    static Player *loadFromFile(std::ifstream &file, const CardDatabase &cardDatabase, Player *opponent = nullptr);

    /**
     * Saves the string identifying the specific child class of this class within a file,
     * and the specific name of the instance.
     * @param[in] file Stream in which the identifier and the name are to be saved
     */
    virtual void saveNameToFile(std::ofstream &file) const = 0;
};

#endif //PAZAAK_PLAYER_H