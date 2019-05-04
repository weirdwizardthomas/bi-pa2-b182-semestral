//
// Created by tomtom on 02/05/19.
//

#ifndef PAZAAK_RANDOMNUMBERGENERATOR_H
#define PAZAAK_RANDOMNUMBERGENERATOR_H

#include <random>

class RandomNumberGenerator {
private:
    std::mt19937 generator;
    std::uniform_int_distribution<size_t> distribution;
public:
    RandomNumberGenerator(size_t min, size_t max, unsigned int seed= std::random_device()());

    size_t operator()();

    void lowerCeiling(size_t max);
};


#endif //PAZAAK_RANDOMNUMBERGENERATOR_H
