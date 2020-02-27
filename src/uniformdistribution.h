#ifndef UNIFORMDISTRIBUTION_H
#define UNIFORMDISTRIBUTION_H
#include "distribution.h"
#include <fstream>


// TODO: this is not finished. I skipped this because I have to do the other part first for the program to run
// U(a,b): uniform distribution from a->b
class UniformDistribution : public Distribution
{

public:
    UniformDistribution(long long newBinNumber, double newLowerBound, double newUpperBound, double a, double b) : Distribution(newBinNumber, newLowerBound, newUpperBound) {
        double binSize = (upperBound - lowerBound) / binNumber;
        double p = binSize/(b-a);

        for (long long i=0; i<binNumber; i++) {
            double x = lowerBound + i*binSize;
            if (x<a || x>b) pdf[i] = 0;
            else pdf[i] = p;

            if (i>0) cdf[i] = cdf[i-1] + pdf[i];
        }
    }

    static void uniformDistributionTest() {

        int nTest = 10;
        int binNumber = 1000000;
        double lowerBound, upperBound, a, b, c;
        std::ofstream fo("uniformDistributionTest.txt");
        std::setprecision(10);

        fo << nTest << "\n";
        for (int t=1; t<=10; t++) {
            lowerBound = (rand()%10000) * (rand()%10000);
            upperBound = (lowerBound+1)*2;
            a = utils::rand01();
            b = utils::rand01();
            if (a > b) {c = a; a = b; b = c;}

            a = lowerBound + a*(upperBound - lowerBound);
            b = lowerBound + b*(upperBound - lowerBound);

            UniformDistribution u(binNumber, lowerBound, upperBound, a, b);
            double binSize = u.getBinSize();

            /*--------------------------------*/
            fo << std::fixed << binNumber << " " << lowerBound << " " << upperBound << " " << a << " " << b << "\n";

            // x array
            for (int i=0; i<binNumber; i++) fo << std::fixed << (lowerBound + double(i)*binSize) << " ";
            fo << "\n";

            // p(x) array
            for (int i=0; i<binNumber; i++) fo << std::fixed << u[i] << " ";
            fo << "\n";

            qDebug() << "Uniform Distribution test " << int(float(t)/nTest*100) << "% completed\n";
        }

        fo.close();
    }
};

#endif // UNIFORMDISTRIBUTION_H
