#pragma once
#ifndef MATRIXEXPERIMENT_H
#define MATRIXEXPERIMENT_H


#include <vector>
#include <matrix.h>
#include <ifloat.h>
#include <randomgenerator.h>
using std::vector;


struct MatrixExperimentException {
  std::string m_msg;
  MatrixExperimentException(const char*const msg) : m_msg(msg) {}
  MatrixExperimentException(const MatrixException& me) : m_msg(me.m_msg) {}
};

enum MatAlgo {LINEAR, SPLIT_MERGE};

struct Result {
    iFloat value;
    MatAlgo algoUsed;
    Result(iFloat v, MatAlgo algo) {value = v; algoUsed = algo;}
};

class MatrixExperiment
{
public:
    MatrixExperiment();

    vector<Matrix<iFloat> > double2iFloat(vector<Matrix<double> > matdv);

    Matrix<double> randomMatrix(unsigned height, unsigned width, RandomGenerator rander);


    iFloat linearTest(vector<Matrix<double> > inputMats, MatOp op);

    iFloat splitMergeTest(vector<Matrix<double> > inputMats, MatOp op);

    iFloat sortTest(vector<Matrix<double> > inputMats, MatOp op);

    vector<Result> experiment(vector<Matrix<double> > inputMats, MatOp op, unsigned nTest, vector<MatAlgo> testAlgos);

};

#endif //MATRIXEXPERIMENT_H
