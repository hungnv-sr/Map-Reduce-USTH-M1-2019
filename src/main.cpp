
#include <QApplication>
#include "mainwindow.h"
#include "logconsole.h"
#include "figurewindow.h"

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
    float40 ha = float40("0.1112223"), hb = float40("0.9996663"), hc = float40("0.435174"), hd = float40("0.675213");
    float fa = float(ha), fb = float(hb), fc = float(fc), fd = float(hd);

    cout << std::setprecision(20) << "\n";
    cout << fa << " " << fb << " " << fc << " " << fd << "\n";

    float40 truesum = ha + hb + hc + hd;
    float sumf = fa + fb + fc + fd;

    float sumf2 = 0, cumulator = 0;
    cumulator += knuth2sum(fa, fb); sumf2 = (fa + fb);
    cumulator += knuth2sum(sumf2, fc); sumf2 = sumf2 + fc;
    cumulator += knuth2sum(sumf2, fd); sumf2 = sumf2 + fd;

    float knuthsum = sumf2 + cumulator;
    float40 res1 = truesum - float40(sumf);
    float40 res2 = truesum - float40(knuthsum);

    cout << res1 << " " << res2 << "\n";
*/
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
