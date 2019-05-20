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
     *
     * @param file
     */
    void saveNameToFile(std::ofstream &file) const override;

public:

    static const char *COMPUTER_FILE_LEAD;
    static const char *REMAINING_CARDS_LEAD;

    explicit ComputerPlayer(Player *opponent);

    /**
     *
     */
    void drawHand() override;

    /**
     *
     * @param file
     */
    void saveToFile(std::ofstream &file) const override;

    /**
     *
     * @param opponentScore
     */
    void takeTurn(int opponentScore) override;

    /**
     *
     * @param allCards
     */
    void chooseDeck(const CardDatabase &allCards) override;

    /**
     *
     * @param opponentScore
     * @param currentScore
     */
    void findPositive(int opponentScore, int currentScore);

    /**
     *
     * @param currentScore
     */
    void findNegative(int currentScore);

    /**
     *
     * @param file
     * @param cardDatabase
     * @param opponent
     * @return
     */
    static Player *loadFromFile(std::ifstream &file, const CardDatabase &cardDatabase, Player *opponent);
};


#endif //PAZAAK_COMPUTERPLAYER_H
