#ifndef GAUSSIANDISTRIBUTION_H
#define GAUSSIANDISTRIBUTION_H

#include "distribution.h"
#include <cmath>

class NormalDistribution : public Distribution
{
public:
    NormalDistribution(long long newBinNumber, double newLowerBound, double newUpperBound, double mean, double variance) : Distribution(newBinNumber, newLowerBound, newUpperBound) {
        if (newBinNumber <= 1)
            throw DistributionException("Normal Distribution: bin Number <= 1");
        if (newUpperBound <= newLowerBound)
            throw DistributionException("Normal Distribution: upper bound < lower bound");
        if (mean < newLowerBound  || mean > newUpperBound)
            throw DistributionException("Normal Distribution: mean out of range");
        if (variance <= 0)
            throw DistributionException("Normal Distribution: Variance <= 0");

        /*
        for (long long i=0; i<binNumber; i++) {
            iFloat leftX = lowerBound + i*binSize;
            iFloat rightX = leftX + binSize;
            pdf[i] = (utils::gaussPdf(mean, variance, leftX) + utils::gaussPdf(mean, variance, rightX)) / 2;

            if (i==0) cdf[i] = pdf[i];
            else cdf[i] = cdf[i-1] + pdf[i];
        }*/

        // optimized code.
        iFloat binSize = (upperBound - lowerBound) / binNumber;
        iFloat leftX = lowerBound, leftPdf = utils::gaussPdf(mean, variance, leftX);
        iFloat rightX = lowerBound + binSize, rightPdf = utils::gaussPdf(mean, variance, rightX);
        for (long long i=0; i<binNumber; i++) {
            pdf[i] = (leftPdf + rightPdf) / 2;
            leftPdf = rightPdf;
            rightX = rightX + binSize;
            rightPdf = utils::gaussPdf(mean, variance, rightX);

            if (i==0) cdf[i] = pdf[i];
            else cdf[i] = cdf[i-1] + pdf[i];
        }

        normalize();
    }

    static bool validParams(long long newBinNumber, double newLowerBound, double newUpperBound, vector<double> params) {
        if (newBinNumber <= 1 || newUpperBound <= newLowerBound) return false;
        if (params.size() != 2) return false;
        if (params[0] < newLowerBound || params[0] > newUpperBound) return false;
        if (params[1] <= 0) return false;
        return true;
    }

    static void normalDistributionTest() {

        int nTest = 10;
        int binNumber = 1000000;
        double lowerBound, upperBound, a, b;
        std::ofstream fo("normalDistributionTest.txt");
        std::setprecision(10);

        fo << nTest << "\n";
        for (int t=1; t<=10; t++) {
            lowerBound = -50;
            upperBound = 50;

            a = utils::rand01();
            b = utils::rand01();

            a = -50 + a*100;
            b = 10 + b*100;

            NormalDistribution N(binNumber, lowerBound, upperBound, a, b);
            iFloat binSize = N.getBinSize();

            /*--------------------------------*/
            fo << std::fixed << binNumber << " " << lowerBound << " " << upperBound << " " << a << " " << b << "\n";

            // x array
            for (int i=0; i<binNumber; i++) fo << std::fixed << (lowerBound + double(i)*binSize) << " ";
            fo << "\n";

            // p(x) array
            for (int i=0; i<binNumber; i++) fo << std::fixed << N[i] << " ";
            fo << "\n";

            qDebug() << "Normal Distribution test " << int(float(t)/nTest*100) << "% completed\n";
        }

        fo.close();
    }

};


#endif // GAUSSIANDISTRIBUTION_H
