#ifndef EXPERIMENTCONTROLLER_H
#define EXPERIMENTCONTROLLER_H

#include <ifloat.h>
#include <matrix.h>
#include <vector.h>
#include <matrixexperiment.h>
#include <map>
#include <vector>
#include <QFile>
#include <fstream>

using std::map;
using std::vector;

class ExperimentController
{
    enum DataType{VECTOR, MATRIX};

    DataType testDataType;
    MatOp op;
    map<MatAlgo, bool> testAlgos;
    unsigned matSize;
    unsigned dataLength;
    vector<Matrix<double> > testList;
    MatrixExperiment matrixEx;

    ExperimentController() {}

protected:
    void generateData() {
        RandomGenerator rander;

        for (unsigned i=0; i<dataLength; i++) {
            if (testDataType==VECTOR) testList.push_back(matrixEx.randomMatrix(1, matSize, rander));
            else testList.push_back(matrixEx.randomMatrix(matSize, matSize, rander));
        }
    }

    /*
    void loadData(std::string fileName) {
        unsigned width, height;
        unsigned n;
        Matrix<double> tmp(0, 0);

        std::ifstream fin(fileName.c_str());
        if (testDataType==VECTOR) {width = 1; height = matSize;}


        fin >> n;
        for (unsigned t=0; t<n; t++) {
            for (unsigned i=0; i<width; i++)

        }
    }
    */

public:

};

#endif // EXPERIMENTCONTROLLER_H
