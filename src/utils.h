#ifndef UTILS_H
#define UTILS_H

#include <cstdlib>
#include <cmath>
#include <random>

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

    //*************
    static double rand01();

};

#endif // UTILS_H
