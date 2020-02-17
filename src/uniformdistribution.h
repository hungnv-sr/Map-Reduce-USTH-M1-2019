#ifndef UNIFORMDISTRIBUTION_H
#define UNIFORMDISTRIBUTION_H
#include "distribution.h"

// TODO: this is not finished. I skipped this because I have to do the other part first for the program to run
// U(a,b): uniform distribution from a->b
class UniformDistribution : public Distribution
{

public:
    UniformDistribution(long long newBinNumber, double newLowerBound, double newUpperBound, double a, double b) : Distribution(newBinNumber, newLowerBound, newUpperBound) {
        double interval = (upperBound - lowerBound) / binNumber;
        long long validBin = (long long)(b-a) - 1;
        double p = 1/validBin;

        for (long long i=0; i<binNumber; i++) {
            double x = lowerBound + i*interval;
            if (x<a || x>b) pdf[i] = 0;
            else pdf[i] = p;

            if (i>0) cdf[i] = cdf[i-1] + pdf[i];
        }
    }


};

#endif // UNIFORMDISTRIBUTION_H
