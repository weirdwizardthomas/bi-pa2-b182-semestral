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

class Player {
protected:
    //Attributes---------------------------------------------------------
    std::string name;
    PlayerBoard board;

    //Methods------------------------------------------------------------
    /**
     * Plays a random card from the Main deck
     * @return Value of the 'BasicCard' played
     */
    int autoPlayCard();

    //Messages-and-prompts-----------------------------------------------
    /**
     * Displays information about the player's in-game objects.
     * @param opponentScore
     */
    void boardStatusMessage(int opponentScore) const;

    /**
     * Informs the players that this player is standing and thus skipping their turns for this round.
     */
    void playerIsStandingMessage() const;

    /**
     * Displays a message informing the user of their opening card.
     * @param opener
     */
    void openerMessage(int opener) const;

    /**
     * Queries the user to pick whether they want to stand in this round.
     */
    void standPrompt() const;

    /**
     * Informs the user that they are passing their turn.
     */
    void isPassingTurnMessage() const;


public:
    static const char *NAME_FILE_LEAD;
    static const char *PLAYER_TYPE_DELIMITER;

    virtual ~Player() = default;

    explicit Player(std::string name);

    /**
     * Adds a specific deck for the player.
     * @param cardDatabase Database of all available cards.
     */
    virtual void chooseDeck(const CardDatabase &cardDatabase) = 0;

    /**
     * Adds the ability to play more cards to the player.
     */
    virtual void drawHand() = 0;

    /** If the user is not 'standing' = skipping their turn,
     * queries the user to stand up or play, plays the top card of the 'mainDeck' element of the 'currentPlayer'
     * and prompts the user to choose a card to play from their hand.
     * The player may choose to stand up before the 'mainDeck' card is auto-played, and may choose not to play a card
     * from their hand.
     * @param opponentScore Opposing player's current round score.
     */
    virtual void takeTurn(int opponentScore) = 0;

    //Setters------------------------------------------------------------
    /**
     * Increments the player's counter of rounds won.
     */
    void addPoint();

    /**
     * Resets all the round related attributes of the player to default values - current score, cards played, standing.
     */
    void resetBoard();

    /**
     * Sets the 'standing' attribute to 'true'.
     */
    void stand();

    //Getters------------------------------------------------------------
    /**
     * Gets the current round's score.
     * @return
     */
    int getCurrentRoundScore() const;

    /**
     * Gets the 'name' attribute.
     * @return
     */
    const std::string &getName() const;

    /**
     * Gets the top card of the player's main deck.
     * @return Value of the deck's top card.
     */
    int getOpener();

    /**
     * Gets the number of cards played in current round.
     * @return Number of cards played by this instance of 'Player' in the current round.
     */
    size_t getPlayedCardsCount() const;

    /**
     * Gets the total rounds won in the current game.
     * @return Number of rounds won by this instance of 'Player' in the current game.
     */
    size_t getRoundsWon() const;

    /**
     * Shows whether the player is standing(skipping all their turns within the current round) or not.
     * @return True if is standing, false otherwise.
     */
    bool isStanding() const;

    /**
     * Saves the instance in a text representation in the @param file file.
     * @param file Output file into which the 'Player' instance is being saved.
     */
    virtual void saveToFile(std::ofstream &file) const = 0;

    /**
     * Loads the player from its text representation from the @param file file. The type of player and the subsequent
     * specific attributes are determined by the leading text in the @param file file. Cards are found by the clues in the
     * @param file file within the @param cardDatabase database.
     * @param file File from which the player data will be read.
     * @param cardDatabase Database of all cards.
     * @param opponent Pointer to the opposing Player.
     * @return A dynamically allocated instance of the player.
     */
    static Player *loadFromFile(std::ifstream &file, const CardDatabase &cardDatabase, Player *opponent = nullptr);

    /**
     * Saves the string identifying the specific child class of the 'Player' class within the @param file file,
     * and the specific name of the instance.
     * @param file Stream in which the identifier and the name are to be saved.
     */
    virtual void saveNameToFile(std::ofstream &file) const = 0;
};

#endif //PAZAAK_PLAYER_H