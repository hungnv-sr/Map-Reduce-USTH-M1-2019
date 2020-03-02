#ifndef ARRAYEXPERIMENT_H
#define ARRAYEXPERIMENT_H

#include <baseexperiment.h>
#include <numerical.h>
#include <vector>
#include <matrix.h>
#include <ifloat.h>
#include <randomgenerator.h>
#include <algorithm>
#include <queue>
#include <arraygenerator.h>
using std::vector;

struct ArrayExperimentException : public std::exception {
private:
    QString msg;

public:
    ArrayExperimentException(QString mess) {
        msg = mess;
    }
    const char* what() const throw() {
        return msg.toStdString().c_str();
    }
};

//********************************************

class ArrayExperiment : public QObject
{
    Q_OBJECT

    vector<double> inputs;
    Distribution distribution;


public:
    ArrayExperiment(vector<double> newInputs, Distribution newDistribution);

    iFloat linearTest(const vector<double> &inputs, Op op);

    double splitMerge(const vector<double> &inputs, Op op, int l, int r);

    iFloat splitMergeTest(const vector<double> &input, Op op);

    iFloat sortTest(vector<double> inputs, Op op);

    iFloat sortAppendTest(vector<double> inputs, Op op);

    iFloat groundTruth(const vector<double> &inputs, Op op);

    vector<Result> experiment(Op op, unsigned nTest, vector<Algo> testAlgos, bool shuffle);

public slots:
    void slotRunArrayExperiment(Op op, unsigned nTest, vector<Algo> testAlgos, bool shuffle);

signals:
    void signalExperimentFinish(vector<Result> res);
};

#endif // ARRAYEXPERIMENT_H
