#include "mainwindow.h"
#include <iostream>
#include <QApplication>
#include "baseoperand.h"
#include "distribution.h"
#include "exponentialdistribution.h"
#include "GaussianDistribution.h"
#include "uniformdistribution.h"

typedef long long ll;
long long *arr;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
