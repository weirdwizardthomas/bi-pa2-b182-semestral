//
// Created by tomtom on 04/05/19.
//

#ifndef PAZAAK_HUMANPLAYER_H
#define PAZAAK_HUMANPLAYER_H


#include "Player.h"


class HumanPlayer : public Player {
protected:
    Deck deck;
    Hand hand;

    /**
     *
     * @return
     */
    bool isStandingUp() const;

    /**
     * Takes input from the player and either passes the turn or plays a card from the player's hand
     * @param opponentScore
     * @return
     */
    bool playCard(int opponentScore);

    /**
     *
     * @param file
     */
    void saveToFile(std::ofstream &file) const override;

    /**
     *
     */
    void printDeck() const;

    /**
     *
     */
    void invalidInputMessage() const;

    /**
     *
     */
    void deckApprovalQuery() const;

    /**
     *
     */
    void actionPrompt() const;

    /**
     *
     */
    void deckChoicePrompt() const;

    /**
     *
     */
    void choosingDeckMessage() const;

public:
    static const char *HUMAN_FILE_LEAD;


    explicit HumanPlayer(const std::string &name);

    /**
     *
     * @param allCards
     */
    void chooseDeck(const CardDatabase &allCards) override;

    /**
     *
     */
    void drawHand() override;

    /**
     *
     * @param file
     * @param cardDatabase
     * @param opponent
     * @return
     */
    static Player *loadFromFile(std::ifstream &file, const CardDatabase &cardDatabase, Player *opponent = nullptr);

    /**
     * Saves the string identifying the specific child class of the 'Player' class within the file.
     * @param file File to
     */
    void saveNameToFile(std::ofstream &file) const override;

    /**
     *
     * @param opponentScore
     */
    void takeTurn(int opponentScore) override;

};


#endif //PAZAAK_HUMANPLAYER_H
