#pragma once
#ifndef MATRIXEXPERIMENT_H
#define MATRIXEXPERIMENT_H

#include <utilityenum.h>
#include <vector>
#include <matrix.h>
#include <ifloat.h>
#include <randomgenerator.h>
#include <matrixgenerator.h>
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

class MatrixExperiment : public QObject
{
    Q_OBJECT

    vector<Matrix<double> > inputMats;
    Distribution distribution;

public:
    MatrixExperiment(vector<Matrix<double> > newInputMats, Distribution newDistribution);


    vector<Matrix<iFloat> > double2iFloat(vector<Matrix<double> > matdv);

    iFloat linearTest(const vector<Matrix<double> > &inputMats, Op op);

    Matrix<double> splitMerge(const vector<Matrix<double> > &inputMats,Op op, int l, int r);

    iFloat splitMergeTest(const vector<Matrix<double> > &inputMats, Op op);


    iFloat groundTruth(const vector<Matrix<double> > &inputMats, Op op);

    vector<Result> experiment(Op op, unsigned nTest, vector<Algo> testAlgos, bool shuffle);

public slots:
    void slotRunMatrixExperiment(Op op, unsigned nTest, vector<Algo> testAlgos, bool shuffle);

signals:
    void signalExperimentFinish(vector<Result> res);

    void signalUpdateProgress(int value);
};

#endif //MATRIXEXPERIMENT_H
