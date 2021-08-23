#ifndef PAZAAK_COMPUTERPLAYER_H
#define PAZAAK_COMPUTERPLAYER_H


#include "Player.h"

#include <queue>

/**
 * Computer player representation that has a wider selection of flexible cards than the human player
 */
class ComputerPlayer : public Player {
private:
    std::vector <std::pair<BasicCard, BasicCard>> deck;
    int remainingCards;
    Player *opponent;

    /**
     * Saves the string identifying ComputerPlayer class and instance within a file
     * @param file File to which the class identifier and instance identifier is saved to
     */
    void saveNameToFile(std::ofstream &file) const override;

public:
    static const char *COMPUTER_FILE_LEAD;
    static const char *REMAINING_CARDS_LEAD;

    explicit ComputerPlayer(Player *opponent);

    /**
     * Increases the ComputerPlayer::remainingCards counter by up to Deck:MAX_CARDS_DRAWN.
     */
    void drawHand() override;

    /**
     * Saves the instance to a file
     * @param[in] file File into which the instance will be saved
     */
    void saveToFile(std::ofstream &file) const override;

    /**
     * Evaluates the next auto-played card and the possible remaining cards in deck to stand
     * or play a card from the deck
     * Finds the most optimal card to play to stay ahead of the opponent with the lowest advantage
     * without breaking the threshold
     * @param[in] opponentScore Score of the opposing player
     */
    void takeTurn(int opponentScore) override;

    /**
     * Loads a set of flexible BasicCard to ComputerPlayer::deck
     * @param[in] cardDatabase Database of all available cards
     */
    void chooseDeck(const CardDatabase &cardDatabase) override;

    /**
     * Finds the lowest Card to play to attain a score higher than
     * opponent's current score without crossing the threshold, and plays it
     * @param[in] opponentScore Score to surpass
     * @param[in] currentScore Computer's current score to raise above opponent's score
     */
    void findPositive(int opponentScore, int currentScore);

    /**
     * Finds lowest negative value to bring the score below the threshold
     * If no such value can be found the computer stands
     * @param[in] currentScore Computer's current score to bring below the threshold
     */
    void findNegative(int currentScore);

    /**
     * Loads the instance from the a file
     * @param[in] file File from which the data to construct the instance is loaded
     * @param[in] cardDatabase Database of all the available cards
     * @param[in] opponent Pointer to the opposing player
     * @return Dynamically allocated instance of ComputerPlayer
     */
    static Player *loadFromFile(std::ifstream &file, const CardDatabase &cardDatabase, Player *opponent);
};


#endif //PAZAAK_COMPUTERPLAYER_H
