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
private:
    //Attributes---------------------------------------------------------
    std::string name;
    Deck deck;
    Hand hand;
    PlayerBoard board;
    //Statistics statistics; TODO, games played, victories, cards played, favourite card,...

    //Methods------------------------------------------------------------

    /**
     * Plays a random card from the Main deck
     * @return Value of the 'BasicCard' played
     */
    int autoPlayCard();

    /**
     * Takes input from the player and either passes the turn or plays a card from the player's hand
     * @param opponentScore
     * @return
     */
    bool playCard(int opponentScore);

    //Messages-and-prompts-----------------------------------------------
    void actionPrompt() const;

    /**
     *
     * @param opponentScore
     */
    void boardStatusMessage(int opponentScore) const;

    /**
     *
     */
    void deckApprovalQuery() const;

    /**
     *
     */
    void invalidInputMessage() const;

    /**
     *
     */
    void playerIsStandingMessage() const;

    /**
     *
     * @param opener
     */
    void openerMessage(int opener) const;

    /**
     *
     */
    void standPrompt() const;

    /**
     *
     */
    void isPassingTurnMessage() const;

    /**
     *
     */
    void choosingDeckMessage() const;

    /**
     *
     */
    void deckChoicePrompt() const;


public:
    static const char *NAME_FILE_LEAD;

    Player() = default;

    explicit Player(std::string name);

    /**
     *
     * @param opponentScore
     */
    void takeTurn(int opponentScore);

    //Setters------------------------------------------------------------
    /**
     *
     */
    void addPoint();

    /**
     *
     * @param allCards
     */
    void chooseDeck(const CardDatabase &allCards);

    /**
     *
     */
    void drawHand();

    /**
     *
     */
    void resetBoard();

    void stand();

    //Getters------------------------------------------------------------
    int getCurrentRoundScore() const;

    const std::string &getName() const;

    /**
     *
     * @return
     */
    int getOpener();

    /**
     *
     * @return
     */
    size_t getPlayedCardsCount() const;

    /**
     *
     * @return
     */
    size_t getRoundsWon() const;

    bool isStanding() const;

    void printDeck() const;

    bool isStandingUp() const;

    void saveToFile(std::fstream &file) const;

};

#endif //PAZAAK_PLAYER_H