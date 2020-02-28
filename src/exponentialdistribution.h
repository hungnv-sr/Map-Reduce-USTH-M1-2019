#ifndef EXPONENTIALDISTRIBUTION_H
#define EXPONENTIALDISTRIBUTION_H

#include "distribution.h"

// TODO: this is not finished. I skipped this because I have to do the other part first for the program to run
class ExponentialDistribution : public Distribution
{
public:
    ExponentialDistribution(long long newBinNumber, double newLowerBound, double newUpperBound, double lambda) : Distribution(newBinNumber, newLowerBound, newUpperBound) {
        double binSize = (upperBound - lowerBound) / binNumber;

        for (long long i=0; i<binNumber; i++) {
            double leftX = lowerBound + i*binSize;
            double rightX = leftX + binSize;

            if (leftX < 0) pdf[i] = 0;
            else pdf[i] = (utils::expoPdf(lambda, leftX) + utils::expoPdf(lambda, rightX)) / 2;

            if (i==0) cdf[i] = pdf[i];
            else cdf[i] = cdf[i-1] + pdf[i];
        }
    }
};

#endif // EXPONENTIALDISTRIBUTION_H
