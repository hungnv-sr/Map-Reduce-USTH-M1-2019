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

public:
    RandomGenerator(Distribution newDistribution);

    double rand();
};

#endif // RANDOMGENERATOR_H
