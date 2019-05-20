//
// Created by tomtom on 04/05/19.
//

#include "ComputerPlayer.h"
#include "../../Game.h"
#include "../../Utilities/Exceptions.h"

using namespace std;

const char *ComputerPlayer::COMPUTER_FILE_LEAD{"Computer"};
const char *ComputerPlayer::REMAINING_CARDS_LEAD{"Remaining cards"};

ComputerPlayer::ComputerPlayer(Player *opponent) : Player("Computer"), remainingCards(0), opponent(opponent) {}

void ComputerPlayer::saveNameToFile(std::ofstream &file) const {
    file << Player::NAME_FILE_LEAD << Game::FILE_FIELD_VALUE_DELIMITER
         << ComputerPlayer::COMPUTER_FILE_LEAD << Player::PLAYER_TYPE_DELIMITER << name << endl;
}

void ComputerPlayer::takeTurn(int opponentScore) {
    board.addPlayedCard(board.drawCardFromMainDeck());

    int currentScore = board.getCurrentScore();

    if (currentScore == Game::TARGET_SCORE) {
        board.stand();
        return;
    }

    if (opponent->isStanding() && currentScore < Game::TARGET_SCORE && currentScore > opponentScore) {
        board.stand();
        return;
    }


    if (currentScore < Game::TARGET_SCORE && currentScore > opponentScore)
        return;

    if (remainingCards != 0) {

        if (currentScore < Game::TARGET_SCORE && currentScore < opponentScore) {
            findPositive(opponentScore, currentScore);
            return;
        }

        if (currentScore > Game::TARGET_SCORE) {
            findNegative(currentScore);
            return;
        }

    }

}

void ComputerPlayer::findNegative(int currentScore) {
    int optimalValue = Game::TARGET_SCORE - currentScore;

    for (size_t i = 0; i < deck.size(); ++i)
        if (deck[i].second.play() == optimalValue) {
            board.addPlayedCard(deck[i].second.play());
            deck.erase(deck.begin() + i);
            --remainingCards;
            return;
        }
    board.stand();
}

void ComputerPlayer::findPositive(int opponentScore, int currentScore) {
    int optimalValue = opponentScore - currentScore + 1;

    while (optimalValue > 0) {
        for (size_t i = 0; i < deck.size(); ++i)
            if (deck[i].first.play() == optimalValue) {
                board.addPlayedCard(deck[i].first.play());
                deck.erase(deck.begin() + i);
                --remainingCards;
                return;
            }
        --optimalValue;
    }
}

void ComputerPlayer::chooseDeck(const CardDatabase &allCards) {
    for (int i = 1; i <= 6; ++i)
        deck.emplace_back(i, -i);
}

void ComputerPlayer::drawHand() {
    remainingCards += (deck.size() < Deck::MAX_CARDS_DRAWN ? deck.size() : Deck::MAX_CARDS_DRAWN);
}

void ComputerPlayer::saveToFile(std::ofstream &file) const {
    saveNameToFile(file);
    size_t i = 0;
    file << ComputerPlayer::REMAINING_CARDS_LEAD << Game::FILE_FIELD_VALUE_DELIMITER << remainingCards << endl;
    file << Deck::DECK_FILE_LEAD << Game::FILE_FIELD_VALUE_DELIMITER << deck.size() << endl;
    for (const auto &card : deck)
        file << Deck::LEFT_INDEX_BRACKET << i++ << Deck::RIGHT_INDEX_BRACKET << card.first << endl;

    board.saveToFile(file);
}

//TODO refactor this - need to extract loadValues and use it here and elsewhere
Player *ComputerPlayer::loadFromFile(std::ifstream &file, const CardDatabase &cardDatabase, Player *opponent) {
    auto *player = new ComputerPlayer(opponent);

    //load remaining
    string input;
    getline(file, input);
    list<string> parsed = CardDatabase::split(input, Game::FILE_FIELD_VALUE_DELIMITER);
    if (parsed.front() != ComputerPlayer::REMAINING_CARDS_LEAD)
        throw ParseError();
    player->remainingCards = stoi(parsed.back());

    //load deck
    getline(file, input);
    parsed = CardDatabase::split(input, Game::FILE_FIELD_VALUE_DELIMITER);
    if (parsed.front() != Deck::DECK_FILE_LEAD)
        throw ParseError();
    size_t cardCount = stoull(parsed.back());
    for (size_t i = 0; i < cardCount; ++i) {
        getline(file, input);
        parsed = CardDatabase::split(input, Deck::RIGHT_INDEX_BRACKET);
        int effect = stoi(parsed.back());
        player->deck.emplace_back(effect, -effect);
    }

    //load board
    player->board = PlayerBoard::loadFromFile(file, cardDatabase);
    return player;
}
