#ifndef GAUSSIANDISTRIBUTION_H
#define GAUSSIANDISTRIBUTION_H

#include "distribution.h"
#include <cmath>

// TODO: this is not finished. I skipped this because I have to do the other part first for the program to run
class NormalDistribution : public Distribution
{
public:
    NormalDistribution(long long newBinNumber, double newLowerBound, double newUpperBound, double mean, double variance) : Distribution(newBinNumber, newLowerBound, newUpperBound) {
        double binSize = (upperBound - lowerBound) / binNumber;

        for (long long i=0; i<binNumber; i++) {
            double leftX = lowerBound + i*binSize;
            double rightX = leftX + binSize;
            pdf[i] = (utils::gaussPdf(mean, variance, leftX) + utils::gaussPdf(mean, variance, rightX)) / 2;

            if (i==0) cdf[i] = pdf[i];
            else cdf[i] = cdf[i-1] + pdf[i];
        }
    }
};


#endif // GAUSSIANDISTRIBUTION_H
