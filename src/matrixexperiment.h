#pragma once
#ifndef MATRIXEXPERIMENT_H
#define MATRIXEXPERIMENT_H

#include <baseexperiment.h>
#include <vector>
#include <matrix.h>
#include <ifloat.h>
#include <randomgenerator.h>
using std::vector;


struct MatrixExperimentException : public std::exception {
private:
    QString msg;

public:
    MatrixExperimentException(QString mess) {
        msg = mess;
    }
    const char* what() const throw() {
        return msg.toStdString().c_str();
    }
};

class MatrixExperiment : public BaseExperiment
{
public:
    MatrixExperiment();

    vector<Matrix<iFloat> > double2iFloat(vector<Matrix<double> > matdv);

    Matrix<double> randomMatrix(unsigned height, unsigned width, RandomGenerator& rander);    

    iFloat linearTest(vector<Matrix<double> > inputMats, Op op);

    iFloat splitMergeTest(vector<Matrix<double> > inputMats, Op op);

    iFloat groundTruth(vector<Matrix<double> >, Op op);

    vector<Result> experiment(vector<Matrix<double> > inputMats, Op op, unsigned nTest, vector<Algo> testAlgos);

};

#endif //MATRIXEXPERIMENT_H
