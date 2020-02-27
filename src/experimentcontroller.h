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


    void loadData(std::string fileName) {
        unsigned height, width;
        unsigned n;
        Matrix<double> tmp(0, 0);

        std::ifstream fin(fileName.c_str());
        if (testDataType==VECTOR) {height = 1; width = matSize;}
        testList.clear();


        fin >> n;
        for (unsigned t=0; t<n; t++) {
            for (unsigned i=0; i<height; i++)
                for (unsigned j=0; j<width; j++)
                    fin >> tmp(i,j);
            testList.push_back(tmp);
        }
    }


public:

};

#endif // EXPERIMENTCONTROLLER_H
