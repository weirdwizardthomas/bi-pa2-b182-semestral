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

    void saveNameToFile(std::ofstream &file) const override;

public:

    static const char *COMPUTER_FILE_LEAD;
    static const char *REMAINING_CARDS_LEAD ;
    static const char *FIELD_VALUE_DELIMITER;

    explicit ComputerPlayer(Player *opponent);

    void drawHand() override;

    void saveToFile(std::ofstream &file) const override;

    void takeTurn(int opponentScore) override;

    void chooseDeck(const CardDatabase &allCards) override;

    void findPositive(int opponentScore, int currentScore);

    void findNegative(int currentScore);

    static Player *loadFromFile(std::ifstream &file, const CardDatabase &cardDatabase, Player *opponent);
};


#endif //PAZAAK_COMPUTERPLAYER_H
