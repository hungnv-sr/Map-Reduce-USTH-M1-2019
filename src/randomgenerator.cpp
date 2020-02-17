#include "randomgenerator.h"

using std::default_random_engine;
using std::uniform_real_distribution;


RandomGenerator::RandomGenerator()
{
   dist = new uniform_real_distribution<double>(0,1);
}

double RandomGenerator::rand() {
    return (*dist)(generator);
}
