#ifndef UTILS_H
#define UTILS_H

#include <cstdlib>
#include <cmath>

const double pi = M_PI;

class utils
{
private:
    utils();
public:
    static bool floatEqual(double a, double b, double error);

    static double sqr(double x);

    static double powerf(double x,int n);

    //*************
    static double gaussPdf(double mean, double variance, double x);

    static double expoPdf(double lambda, double x);
};

#endif // UTILS_H
