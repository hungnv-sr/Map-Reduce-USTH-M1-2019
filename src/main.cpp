#include "mainwindow.h"
#include "logconsole.h"
#include <iostream>
#include <QApplication>
#include "distribution.h"
#include "exponentialdistribution.h"
#include "NormalDistribution.h"
#include "uniformdistribution.h"

#include "ifloat.h"
#include <ReduceAlgorithms.h>
#include "randomgenerator.h"
#include "matrix.h"
#include "matrixexperiment.h"
using std::cout;

#include <iostream>
#include <boost/multiprecision/cpp_dec_float.hpp>
#include <boost/multiprecision/cpp_int.hpp>
using boost::multiprecision::number;
using boost::multiprecision::cpp_dec_float;
using boost::multiprecision::cpp_dec_float_50;
using boost::numeric_cast;
using std::cout;
using std::vector;


int main(int argc, char *argv[])
{
    srand(time(NULL));
    QApplication a(argc, argv);
    qRegisterMetaType<vector<double> >("vector<double>");
    qRegisterMetaType<Op>("Op");
    qRegisterMetaType<Result>("Result");
    qRegisterMetaType<vector<Result> >("vector<Result>");
    qRegisterMetaType<AlgoName>("Algo");
    qRegisterMetaType<vector<AlgoName> >("vector<Algo>");
    qRegisterMetaType<Matrix<double> >("Matrix<double>");
    qRegisterMetaType<vector<Matrix<double> > >("vector<Matrix<double> >");
    qRegisterMetaType<Distribution>("Distribution");
    qRegisterMetaType<vector<AlgoName> >("vector<AlgoName>");


    /*
    std::cout << std::setprecision(std::numeric_limits<cpp_dec_float_50>::digits10);
    cpp_dec_float_50 x = cpp_dec_float_50(0.0001);
    cpp_dec_float_50 y = x*x*x*x;
    std::string s = y.str(25);
    std::cout << s << "\n";
    */


    MainWindow w;
    w.show();

    return a.exec();
}
