#ifndef EXPONENTIALDISTRIBUTION_H
#define EXPONENTIALDISTRIBUTION_H

#include "distribution.h"
#include <fstream>

// TODO: this is not finished. I skipped this because I have to do the other part first for the program to run
class ExponentialDistribution : public Distribution
{
public:
    ExponentialDistribution(long long newBinNumber, double newLowerBound, double newUpperBound, double lambda) : Distribution(newBinNumber, newLowerBound, newUpperBound) {
        if (newBinNumber <= 1)
            throw DistributionException("Exponential Distribution: bin Number <= 1");
        if (newUpperBound <= newLowerBound)
            throw DistributionException("Exponential Distribution: upper bound < lower bound");
        if (lambda <= 0)
            throw DistributionException("Exponential Distribution: lambda <= 0");


        double binSize = (upperBound - lowerBound) / binNumber;

        for (long long i=0; i<binNumber; i++) {
            double leftX = lowerBound + i*binSize;
            double rightX = leftX + binSize;

            if (leftX < 0) pdf[i] = 0;
            else pdf[i] = (utils::expoPdf(lambda, leftX) + utils::expoPdf(lambda, rightX)) / 2;

            if (i==0) cdf[i] = pdf[i];
            else cdf[i] = cdf[i-1] + pdf[i];
        }

        normalize();
    }

    static bool validParams(long long newBinNumber, double newLowerBound, double newUpperBound, vector<double> params) {
        if (newBinNumber <= 1 || newUpperBound <= newLowerBound) return false;
        if (params.size() != 1) return false;
        if (params[0] <= 0) return false;
        return true;
    }

    static void exponentialDistributionTest() {

        int nTest = 10;
        int binNumber = 1000000;
        double lowerBound, upperBound, lambda;
        std::ofstream fo("exponentialDistributionTest.txt");
        std::setprecision(10);

        fo << nTest << "\n";
        for (int t=1; t<=10; t++) {
            lowerBound = -50;
            upperBound = 50;

            lambda = 0.0001 + utils::rand01();

            ExponentialDistribution E(binNumber, lowerBound, upperBound, lambda);
            double binSize = E.getBinSize();

            /*--------------------------------*/
            fo << std::fixed << binNumber << " " << lowerBound << " " << upperBound << " " << lambda << " " << lambda << "\n";

            // x array
            for (int i=0; i<binNumber; i++) fo << std::fixed << (lowerBound + double(i)*binSize) << " ";
            fo << "\n";

            // p(x) array
            for (int i=0; i<binNumber; i++) fo << std::fixed << E[i] << " ";
            fo << "\n";

            qDebug() << "Normal Distribution test " << int(float(t)/nTest*100) << "% completed\n";
        }

        fo.close();
    }
};

#endif // EXPONENTIALDISTRIBUTION_H
