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
     *
     * @param opponentScore
     */
    void boardStatusMessage(int opponentScore) const;

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


public:
    static const char *NAME_FILE_LEAD;
    static const char *NAME_DELIMITER;

    Player() = default;

    virtual ~Player() = default;

    explicit Player(std::string name);

    virtual void chooseDeck(const CardDatabase &allCards) = 0;

    /**
     *
     */
    virtual void drawHand() = 0;

    /**
     *
     * @param opponentScore
     */
    virtual void takeTurn(int opponentScore) = 0;

    //Setters------------------------------------------------------------
    /**
     *
     */
    void addPoint();

    /**
     *
     */
    void resetBoard();

    /**
     *
     */
    void stand();

    //Getters------------------------------------------------------------
    /**
     *
     * @return
     */
    int getCurrentRoundScore() const;

    /**
     *
     * @return
     */
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

    /**
     *
     * @return
     */
    bool isStanding() const;


    /**
     *
     */
    virtual void saveToFile(std::ofstream &file) const = 0;

    /**
     *
     * @param file
     * @param cardDatabase
     * @return
     */
    static Player *loadFromFile(std::ifstream &file, const CardDatabase &cardDatabase, Player *opponent = nullptr);

    /**
     *
     * @param file
     */
    virtual void saveNameToFile(std::ofstream &file) const = 0;
};

#endif //PAZAAK_PLAYER_H