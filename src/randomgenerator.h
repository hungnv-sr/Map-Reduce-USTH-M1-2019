#ifndef RANDOMGENERATOR_H
#define RANDOMGENERATOR_H

#include <distribution.h>
#include <random>
using std::default_random_engine;
using std::uniform_real_distribution;

// TODO: this random generator is temporary only.
class RandomGenerator
{
private:
    Distribution distribution;
    std::random_device randomDevice;
    std::mt19937 generator;
    std::uniform_real_distribution<double> dist01;

public:
    RandomGenerator(Distribution newDistribution);

    double rand();
};

#endif // RANDOMGENERATOR_H
