#ifndef RANDOMGENERATOR_H
#define RANDOMGENERATOR_H

#include <distribution.h>
#include <random>
using std::default_random_engine;
using std::uniform_real_distribution;



struct RandomGeneratorException : public std::exception {
private:
    QString msg;

public:
    RandomGeneratorException(QString mess) {
        msg = mess;
    }
    const char* what() const throw() {
        return msg.toStdString().c_str();
    }
};


class RandomGenerator
{
private:
    Distribution distribution;
    std::random_device randomDevice;
    std::mt19937 generator;
    std::uniform_real_distribution<double> dist01;

    // since the distribution doesn't change, we don't want to calculate the
    // bin size each time we run the random generator
    double binSize;

public:
    RandomGenerator(Distribution newDistribution) : distribution(newDistribution), generator(randomDevice()), dist01(0,1) {
        binSize = double(distribution.getBinSize());
    }

    double rand() {
        if (!distribution.valid())
            throw RandomGeneratorException("rand(): invalid distribution");

        // inverse sampling method: since Y = CDF(X) is in range (0,1),
        // we generate y first then find x
        iFloat U = dist01(generator);
        long long bin = distribution.inverseSampling(U);
        return binSize * bin + dist01(generator)*binSize;
    }
};

#endif // RANDOMGENERATOR_H
