//
// Created by tomtom on 04/05/19.
//

#ifndef PAZAAK_CARDDATABASE_H
#define PAZAAK_CARDDATABASE_H

#include <string>
#include <vector>
#include <list>
#include <map>

#include "Card.h"


class CardDatabase {
private:
    std::map<std::string, Card *> cards;

    void loadFlipCards();

    void loadDualCards();

    void loadBasicCards();

    void loadDoubleCard();

    void loadFlexCard();

    static std::pair<int, int> getDualValues(const std::string &line);

    static void validLines(const std::vector<std::string> &fileLines, const std::string &mode);

    static std::string pathOf(const std::string &filename);

    static std::vector<std::string> getFileLines(const std::string &filePath);

    static std::list<std::string> split(std::string phrase, const std::string &delimiter);

public:
    static const char *CARD_FOLDER_PATH;
    static const char *BASIC_CARD;
    static const char *DUAL_CARD;
    static const char *FLIP_CARD;

    CardDatabase();

    ~CardDatabase();

    Card *get(const std::string &key) const;

    std::vector<Card *> toVector() const;

    size_t size() const;

    friend std::ostream &operator<<(std::ostream &out, const CardDatabase &cardDatabase);

    std::map<std::string, Card *>::const_iterator cbegin() const;

    std::map<std::string, Card *>::const_iterator cend() const;

    std::map<std::string, Card *>::iterator begin();

    std::map<std::string, Card *>::iterator end();
};


#endif //PAZAAK_CARDDATABASE_H
