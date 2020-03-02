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
#include <arraydatagenerator.h>
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

class ArrayExperiment : public BaseExperiment
{
public:
    ArrayExperiment();

    iFloat linearTest(const vector<double> &inputs, Op op);

    iFloat splitMergeTest(const vector<double> &input, Op op);

    iFloat sortTest(vector<double> inputs, Op op);

    iFloat sortAppendTest(vector<double> inputs, Op op);

    iFloat groundTruth(const vector<double> &inputs, Op op);

    vector<Result> experiment(vector<double> inputs, Op op, unsigned nTest, vector<Algo> testAlgos, bool shuffle, Distribution distribution);

};

#endif // ARRAYEXPERIMENT_H
