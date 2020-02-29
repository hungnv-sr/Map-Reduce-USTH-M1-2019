#include "mainwindow.h"
#include <iostream>
#include <QApplication>
#include "distribution.h"
#include "exponentialdistribution.h"
#include "NormalDistribution.h"
#include "uniformdistribution.h"

#include "ifloat.h"
#include "randomgenerator.h"
#include "matrix.h"
#include "matrixexperiment.h"
#include <Eigen/Dense>
using std::cout;

#include <boost/multiprecision/cpp_dec_float.hpp>
#include <boost/multiprecision/cpp_int.hpp>
using boost::multiprecision::number;
using boost::multiprecision::cpp_dec_float;
using boost::multiprecision::cpp_dec_float_50;
using boost::numeric_cast;
using std::cout;


void matTest()
{

    Matrix<double> a(3, 3, 1.5);
    Matrix<int> b(3, 3, 1);
    Matrix<float> c(3,3,2.7);

    Matrix<double> d(3, 3, 0);
    d = c + 3.5;//a + b*c + c*3.5;
    d.print();
    std::cout << double(c.sum<int>()) << "\n";
    cpp_dec_float_50 x = 5.3;
    for (double t = 1; t<= 200; t++) x = x / t;
    //std::cout << (2.1 + x*3.5 - x) << "\n";
    std::cout << x << "\n";
    std::cout << numeric_cast<double>(x);
}

void distributionTest() {
    UniformDistribution::uniformDistributionTest();
}

void normalTest() {
    NormalDistribution::normalDistributionTest();
}

void expoTest() {
    ExponentialDistribution::exponentialDistributionTest();
}

int main(int argc, char *argv[])
{
    srand(time(NULL));
    QApplication a(argc, argv);
    //matTest();
    //distributionTest();
    //normalTest();
  //  expoTest();


    MainWindow w;
    w.show();
    return a.exec();
}
