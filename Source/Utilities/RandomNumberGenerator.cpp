#include "RandomNumberGenerator.h"

using namespace std;

RandomNumberGenerator::RandomNumberGenerator(size_t min, size_t max, unsigned int seed) :
        generator(seed), distribution(min, max) {}

size_t RandomNumberGenerator::operator()() {
    return distribution(generator);
}

void RandomNumberGenerator::lowerCeiling(size_t max) {
    distribution = std::uniform_int_distribution<size_t>(distribution.min(), max);
}