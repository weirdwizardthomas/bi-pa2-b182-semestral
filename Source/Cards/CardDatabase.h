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

    /**
     * Reads the 'BasicCards' file in the 'CARDS_DIRECTORY' directory
     * and processes them into elements of the 'cards' container.
     */
    void loadBasicCards();

    /**
     * Reads the 'DualCards' file in the 'CARDS_DIRECTORY' directory
     * and processes them into elements of the 'cards' container.
     */
    void loadDualCards();

    /**
     * Adds a single 'DoubleCard' class instance to 'cards' container.
     */
    void loadDoubleCard();

    /**
     * Adds a single 'FlexCard' class instance to the 'cards' container.
     */
    void loadFlexCard();

    /**
     * Reads the 'FlipCards' file in the 'CARDS_DIRECTORY' directory
     * and processes them into elements of the 'cards' container.
     */
    void loadFlipCards();

    /**
     * Reads two numerical values from the 'line'.
     * Throws invalid_argument exception if either is not found.
     * @param line Text to be parsed for the values.
     * @return A pair of two different integer values.
     */
    static std::pair<int, int> getDualValues(const std::string &line);

    /**
     * Checks whether the elements of 'fileLines' represent valid file lines for the card type 'mode'.
     * Throws invalid_argument exception if the line is not valid.
     * @param fileLines Lines representing individual cards.
     * @param mode Mode by which the lines are validated.
     */
    static void validLines(const std::vector<std::string> &fileLines, const std::string &mode = "");

    /**
     * Constructs a path to the 'filename' file in the 'CARD_DIRECTORY' DIRECTORY.
     * @param filename Name of the file for which the path is constructed.
     * @return Path to the 'filename' file.
     */
    static std::string pathOf(const std::string &filename);

    /**
     * Loads the file at 'filePath' and splits it into individual lines.
     * @param filePath Path to the file to be processed.
     * @return Container of individual lines of the 'filePath' file.
     */
    static std::vector<std::string> getFileLines(const std::string &filePath);

public:
    static const char *CARD_DIRECTORY;
    static const char *BASIC_CARD;
    static const char *DUAL_CARD;
    static const char *FLIP_CARD;

    CardDatabase();

    ~CardDatabase();

    /**
     * Finds and returns a pointer to an element stored by the 'key'.
     * @param key Key by which the element will be found.
     * @return A Card pointer which has a key equal to 'key'.
     */
    Card *get(const std::string &key) const;

    /**
     * Converts the database into vector representation.
     * @return Vector of pointers to Cards in the database.
     */
    std::vector<Card *> toVector() const;

    /**
     * Gets the 'cards' container's element count.
     * @return size of 'cards'.
     */
    size_t size() const;

    /**
     * Splits the 'phrase' string into substring delimited by the 'delimiter'.
     * @param phrase Text to be split.
     * @param delimiter Text by which the 'phrase' will be split.
     * @return Container of substrings split by the 'delimiter'.
     */
    static std::list<std::string> split(std::string phrase, const std::string &delimiter);

    /**
     * Reads a line from the 'file' stream and parses it for a pair of field-value.
     * Throws a 'ParseError' exception if 'field' and the parsed value mismatch.
     * @param field Field to be found in the line.
     * @param delimiter Delimiter by which the line is parsed.
     * @param file File from which the line will be read.
     * @return The value of the 'field'.
     */
    static std::string loadValue(const std::string &field, const std::string &delimiter, std::ifstream &file);

    /**
     * Places the 'cards' container's elements in the 'out' stream.
     * @param out Stream into which 'cards' will be placed.
     * @param cardDatabase Database whose 'cards' will be placed in the stream.
     * @return 'out' stream with the 'cards' container placed into it.
     */
    friend std::ostream &operator<<(std::ostream &out, const CardDatabase &cardDatabase);

    /**
     * Grants a constant iterator to the instance's 'cards' first element.
     * @return Constant iterator pointing to the first element of 'cards'.
     */
    std::map<std::string, Card *>::const_iterator cbegin() const;

    /**
     * Grants a constant iterator to the instance's 'cards' after-last element.
     * @return Constant iterator pointing to the first element of 'cards'.
     */
    std::map<std::string, Card *>::const_iterator cend() const;

    /**
     * Grants a iterator to the instance's 'cards' first element.
     * @return iterator pointing to the first element of 'cards'.
     */
    std::map<std::string, Card *>::iterator begin();

    /**
     * Grants an iterator to the instance's 'cards' after-last element.
     * @return Iterator pointing to the first element of 'cards'.
     */
    std::map<std::string, Card *>::iterator end();
};

#endif //PAZAAK_CARDDATABASE_H
