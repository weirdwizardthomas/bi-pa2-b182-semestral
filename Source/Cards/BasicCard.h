#ifndef TMPPAZAAK_BASICCARD_H
#define TMPPAZAAK_BASICCARD_H


#include <fstream>

#include "Card.h"

/**
 * Adds its singular value to the player's current score when played
 */
class BasicCard : public Card {

private:
    int value;

public:
    explicit BasicCard(int value);

    ~BasicCard() override = default;

    /**
     * Gets the cards BasicCard::value
     * @param[in,out] playedCards Cards previously played by the current player
     * @param[in] currentScore Current player's current round's score
     * @param[in] opponentScore Opponent's current round's score
     * @return Card's BasicCard::value
     */
    int play(std::vector<int> &playedCards, int currentScore, int opponentScore) const override;

    /**
     * Gets the card's BasicCard::value without taking any context in regard
     * @return  BasicCard::value
     */
    int play() const;

    std::string getDescription() const override;
};


#endif //TMPPAZAAK_BASICCARD_H
