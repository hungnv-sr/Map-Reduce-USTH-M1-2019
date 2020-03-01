#ifndef UTILS_H
#define UTILS_H

#include <iomanip>      // std::setprecision
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <random>
#include <QString>
#include <vector>
#include <QDebug>
using std::vector;
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

    //**************
    static bool saveArray(QString filename, const vector<double> &data, unsigned precision);

};

#endif // UTILS_H
