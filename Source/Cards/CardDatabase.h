#ifndef PAZAAK_CARDDATABASE_H
#define PAZAAK_CARDDATABASE_H

#include <string>
#include <vector>
#include <list>
#include <map>

#include "Card.h"

/**
 * A pseudo-database wrapper of all the available cards within the game. This class's instances offer access
 * to pointers of the Cards and is responsible for the life cycle of individual Card's ,loading them from their respective files, offering
 * access to them and their destruction.
 */
class CardDatabase {

private:
    std::map<std::string, Card *> cards; /*<! Collection of all the available cards in game*/

    /**
     * Reads the CardDatabase::BasicCards file in the CardDatabase::CARDS_DIRECTORY directory
     * and processes them into elements of the CardDatabase::cards
     */
    void loadBasicCards();

    /**
     * Reads the CardDatabase::DualCards file in the CardDatabase::CARDS_DIRECTORY directory
     * and processes them into elements of the CardDatabase::cards
     */
    void loadDualCards();

    /**
     * Adds a single DoubleCard instance to CardDatabase::cards
     */
    void loadDoubleCard();

    /**
     * Adds a single FlexCard instance to the CardDatabase::cards
     */
    void loadFlexCard();

    /**
     * Reads the CardDatabase::FlipCards file in the CardDatabase::CARDS_DIRECTORY directory
     * and processes them into elements of the CardDatabase::cards
     */
    void loadFlipCards();

    /**
     * Reads two numerical values from the a given line
     * @throws invalid_argument  if either is not found
     * @param[in] line Text to be parsed for the values
     * @return A pair of two different integer values
     */
    static std::pair<int, int> getDualValues(const std::string &line);

    /**
     * Checks whether the elements of a line represent valid file under card specific constraints
     * @throws invalid_argument if the line is not valid
     * @param[in] fileLines Lines representing individual cards
     * @param mode Mode by which the lines are validated
     */
    static void validLines(const std::vector <std::string> &fileLines, const std::string &mode = "");

    /**
     * Constructs a path to the file in the CardDatabase::CARDS_DIRECTORY directory
     * @param[in] filename Name of the file for which the path is constructed
     * @return Path to a file
     */
    static std::string pathOf(const std::string &filename);

    /**
     * Loads a file and splits it into individual lines
     * @param[in] filePath Path to the file to be processed
     * @return Container of individual lines of the file
     */
    static std::vector <std::string> getFileLines(const std::string &filePath);

public:
    static const char *CARD_DIRECTORY; /*<! Path to the directory containing card files */
    static const char *BASIC_CARD; /*<! Name of the file containing BasicCard records */
    static const char *DUAL_CARD; /*<! Name of the file containing DualCard records */
    static const char *FLIP_CARD; /*<! Name of the file containing FlipCard records */

    CardDatabase();

    ~CardDatabase();

    /**
     * Finds and returns a pointer to an element stored by the 'key' in CardDatabase::cards
     * @param[in] key Key by which the element will be found.
     * @return A pointer to Card instance which has a key equal to  'key'
     */
    Card *get(const std::string &key) const;

    /**
     * Converts the CardDatabase::cards into vector representation.
     * @return Vector of pointers to Card in the database
     */
    std::vector<Card *> toVector() const;

    /**
     * Gets the CardDatabase::cards element count
     * @return size of cards container
     */
    size_t size() const;

    /**
     * Splits text into substrings delimited by the delimiter
     * @param[in] phrase Text to be split
     * @param[in] delimiter Text by which the phrase is to be split
     * @return Container of substrings split by the delimiter
     */
    static std::list <std::string> split(std::string phrase, const std::string &delimiter);

    /**
     * Reads a line from a  file stream and parses it for a pair of field-value
     * @throws ParseError if field and the parsed value mismatch
     * @param[in] field Field to be found in the line
     * @param[in] delimiter Delimiter by which the line is parsed
     * @param[in] file File from which the line will be read
     * @return The value of the field's complement
     */
    static std::string loadValue(const std::string &field, const std::string &delimiter, std::ifstream &file);

    /**
     * Places the cards container's elements in the output stream
     * @param[in,out] out Stream into which CardDatabase::cards will be placed
     * @param[in] cardDatabase Database whose CardDatabase::cards will be placed in the stream
     * @return output stream with the CardDatabase::cards elements placed into it
     */
    friend std::ostream &operator<<(std::ostream &out, const CardDatabase &cardDatabase);

    /**
     * Grants a constant iterator to the instance's CardDatabase::cards first element
     * @return Constant iterator pointing to the first element of CardDatabase::cards
     */
    std::map<std::string, Card *>::const_iterator cbegin() const;

    /**
     * Grants a constant iterator to the instance's CardDatabase::cards after-last element
     * @return Constant iterator pointing to the first element of CardDatabase::cards
     */
    std::map<std::string, Card *>::const_iterator cend() const;

    /**
     * Grants a iterator to the instance's CardDatabase::cards first element
     * @return iterator pointing to the first element of CardDatabase::cards
     */
    std::map<std::string, Card *>::iterator begin();

    /**
     * Grants an iterator to the instance's CardDatabase::cards after-last element
     * @return Iterator pointing to the first element of CardDatabase::cards
     */
    std::map<std::string, Card *>::iterator end();
};

#endif //PAZAAK_CARDDATABASE_H
