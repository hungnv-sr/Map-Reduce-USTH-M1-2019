
#include <QApplication>
#include "mainwindow.h"
#include "logconsole.h"

#include <iostream>
#include "ifloat.h"
#include <iostream>
using std::cout;
using std::vector;


float knuth2sum(float a, float b) {
    float s = a + b;
    float a2 = s - b;
    float b2 = s - a;
    float da = a - a2;
    float db = b - b2;
    float r = da + db;
    return r;
}

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
