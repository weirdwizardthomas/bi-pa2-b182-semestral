//
// Created by tomtom on 02/05/19.
//

#ifndef PAZAAK_RANDOMNUMBERGENERATOR_H
#define PAZAAK_RANDOMNUMBERGENERATOR_H

#include <random>

/**
 * Random number generator for generating random indices
 */
class RandomNumberGenerator {
private:
    //Attributes---------------------------------------------------------
    std::mt19937 generator;
    std::uniform_int_distribution <size_t> distribution;
public:
    RandomNumberGenerator(size_t min, size_t max, unsigned int seed = std::random_device()());

    /**
     * Generates a random number from the min - max range.
     * @return Randomly generated number from the 'min'-'max' range.
     */
    size_t operator()();

    /**
     * Reduces the maximal value of the generator to the max value.
     * @param max Value to which the generator is to be reduced to.
     */
    void lowerCeiling(size_t max);
};


#endif //PAZAAK_RANDOMNUMBERGENERATOR_H
