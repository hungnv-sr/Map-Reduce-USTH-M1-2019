#include "mainwindow.h"
#include <iostream>
#include <QApplication>
#include "baseoperand.h"
#include "distribution.h"
#include "exponentialdistribution.h"
#include "GaussianDistribution.h"
#include "uniformdistribution.h"

#include "ifloat.h"
#include "randomgenerator.h"
#include "matrix.h"
#include "matrixexperiment.h"
#include <Eigen/Dense>

void matTest()
{

    Matrix<double> a(3, 3, 1.5);
    Matrix<int> b(3, 3, 1);
    Matrix<float> c(3,3,2.7);

    Matrix<double> d(3, 3, 0);
    d = c + 3.5;//a + b*c + c*3.5;
    d.print();

    iFloat x = 5.3;
    std::cout << (2.1 + x*3.5 - x) << "\n";
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    matTest();

    MainWindow w;
    w.show();
    return a.exec();
}
