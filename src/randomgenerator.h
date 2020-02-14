#ifndef RANDOMGENERATOR_H
#define RANDOMGENERATOR_H

#include <random>
using std::default_random_engine;
using std::uniform_real_distribution;

// TODO: this random generator is temporary only.
class RandomGenerator
{
private:
    default_random_engine generator;
    uniform_real_distribution<double> *dist;

public:
    RandomGenerator();

    double rand();
};

#endif // RANDOMGENERATOR_H
