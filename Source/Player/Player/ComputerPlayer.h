//
// Created by tomtom on 04/05/19.
//

#ifndef PAZAAK_COMPUTERPLAYER_H
#define PAZAAK_COMPUTERPLAYER_H


#include "Player.h"

#include <queue>

class ComputerPlayer : public Player {
private:
    std::vector<std::pair<BasicCard, BasicCard>> deck;
    int remainingCards;
    Player *opponent;

    /**
     * Saves the string identifying the specific child class of the 'Player' class and instance within the file.
     * @param file File to which the class identifier and instance identifier is saved to.
     */
    void saveNameToFile(std::ofstream &file) const override;

public:

    static const char *COMPUTER_FILE_LEAD;
    static const char *REMAINING_CARDS_LEAD;

    explicit ComputerPlayer(Player *opponent);

    /**
     * Increases the remaningCards counter by up to MAX_CARDS_DRAWN.
     */
    void drawHand() override;

    /**
     * Saves the instance to the @param file.
     * @param file File into which the instance will be saved.
     */
    void saveToFile(std::ofstream &file) const override;

    /**
     * Evaluates the next auto-played card and the possible remaining cards in deck to stand
     * or play a card from the deck.
     * Finds the most optimal card to play to stay ahead of the opponent without breaking the threshold.
     * @param opponentScore
     */
    void takeTurn(int opponentScore) override;

    /**
     * Loads a set of flexible cards to 'deck'.
     * @param cardDatabase Database of all available cards.
     */
    void chooseDeck(const CardDatabase &cardDatabase) override;

    /**
     * Finds the lowest Card to play to attain a score higher than @param currentScore without crossing the threshold,
     * and plays it.
     * @param opponentScore Score to surpass.
     * @param currentScore Computer's current score to raise above @param opponentScore.
     */
    void findPositive(int opponentScore, int currentScore);

    /**
     * Finds lowest negative value to bring the score below the threshold.
     * If no such value can be found the computer stands.
     * @param currentScore Computer's current score to bring below the threshold.
     */
    void findNegative(int currentScore);

    /**
     * Loads the instance from the @param file.
     * @param file File from which the data to construct the instance is loaded.
     * @param cardDatabase Database of all the available cards.
     * @param opponent Pointer to the opposing player.
     * @return Dynamically allocated instance of the Player's child class ComputerPlayer.
     */
    static Player *loadFromFile(std::ifstream &file, const CardDatabase &cardDatabase, Player *opponent);
};


#endif //PAZAAK_COMPUTERPLAYER_H
