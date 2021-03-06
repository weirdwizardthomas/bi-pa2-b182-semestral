#ifndef PAZAAK_HUMANPLAYER_H
#define PAZAAK_HUMANPLAYER_H


#include "Player.h"

/**
 * Representation of the user as a player of the game, allowing them to interact with the game.
 */
class HumanPlayer : public Player {
protected:
    Deck deck;
    Hand hand;

    /**
     * Queries the player whether they want to stand or not, i.e. forfeiting any further turns in the current round
     * @return True if the player chooses to stand, false otherwise
     */
    bool isStandingUp() const;

    /**
     * Takes input from the player and either passes the turn or plays a card from the player's hand
     * @param opponentScore Opponent's current score
     * @return True if player is passing their turn or selects a valid Card to play, false otherwise
     */
    bool playCard(int opponentScore);

    /**
     * Saves the instance to a file
     * @param file File into which the instance is to be saved
     */
    void saveToFile(std::ofstream &file) const override;

    /**
     * Shows the deck's elements to the player
     */
    void printDeck() const;

    /**
     * Informs the user that the input is not valid for the given scenario
     */
    void invalidInputMessage() const;

    /**
     * Prompts the user to confirm their deck selection
     */
    void deckApprovalPrompt() const;

    /**
     * Prompts the player to select a card to play or to pass their turn
     */
    void actionPrompt() const;

    /**
     * Prompts the player to create a new deck or load an existing one from a file
     */
    void deckChoicePrompt() const;

    /**
     * Informs the players which player is to pick their deck
     */
    void choosingDeckMessage() const;

public:
    static const char *HUMAN_FILE_LEAD;

    explicit HumanPlayer(const std::string &name);

    /**
     * Queries the player to either create a new deck of cards, or load an existing one from DeckParser::DECK_DIRECTORY
     * @param cardDatabase Database of all available cards
     */
    void chooseDeck(const CardDatabase &cardDatabase) override;

    /**
     * Moves up to Deck::MAX_CARDS_DRAWN Card from the player's Player::deck to their Player::hand
     */
    void drawHand() override;

    /**
     * Loads the instance from a file
     * @param file Stream containing the contents of the game from which the player data will be read
     * @param cardDatabase Database of all the available cards
     * @param opponent Pointer to the opposing player.
     * @return Dynamically allocated instance of HumanPlayer with data read from the file
     */
    static Player *loadFromFile(std::ifstream &file, const CardDatabase &cardDatabase, Player *opponent = nullptr);

    /**
     * Saves the string identifying the HumanPlayer class and instance within a file
     * @param file File to which the class identifier and instance identifier is saved to
     */
    void saveNameToFile(std::ofstream &file) const override;

    /**
     * Queries the current player to take their turn. The player decides whether they want to stand
     * a card is automatically played from their main deck' and then the player picks a card from their hand to play
     * @param opponentScore The opposing side's current score
     */
    void takeTurn(int opponentScore) override;
};


#endif //PAZAAK_HUMANPLAYER_H
