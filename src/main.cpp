#include "mainwindow.h"

#include <QApplication>
#include "baseoperand.h"
#include "distribution.h"
#include "exponentialdistribution.h"
#include "GaussianDistribution.h"
#include "uniformdistribution.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
