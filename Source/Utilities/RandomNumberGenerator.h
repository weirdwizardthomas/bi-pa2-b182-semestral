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
    RandomNumberGenerator(size_t min, size_t max, unsigned int seed = std::random_device()()) :
            generator(seed), distribution(min, max) {}

    size_t operator()() { return distribution(generator); }

    void lowerCeiling(size_t max) {
        distribution = std::uniform_int_distribution<size_t>(distribution.min(), max);
    }
};


#endif //PAZAAK_RANDOMNUMBERGENERATOR_H
