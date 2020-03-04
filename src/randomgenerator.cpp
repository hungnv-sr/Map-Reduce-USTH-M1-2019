#include "randomgenerator.h"

using std::default_random_engine;
using std::uniform_real_distribution;


RandomGenerator::RandomGenerator(Distribution newDistribution) : distribution(newDistribution), generator(randomDevice()), dist01(0,1)
{    

}

double RandomGenerator::rand() {
    if (!distribution.valid())
        throw RandomGeneratorException("rand(): invalid distribution");

    // inverse sampling method: since Y = CDF(X) is in range (0,1),
    // we generate y first then find x
    iFloat U = dist01(generator);
    long long bin = distribution.inverseSampling(U);
    double binSize = double(distribution.getBinSize());
    return binSize * bin + dist01(generator)*binSize;
}
