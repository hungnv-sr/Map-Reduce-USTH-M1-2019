#ifndef ARRAYEXPERIMENT_H
#define ARRAYEXPERIMENT_H

#include <utilityenum.h>
#include <vector>
#include <ifloat.h>
#include <randomgenerator.h>
#include <algorithm>
#include <queue>
#include <arraygenerator.h>
#include <ReduceAlgorithms.h>
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

//--------------- template class can't inherit QObject, so we do it indirectly
class QArrayExperiment : public QObject
{
    Q_OBJECT

public:
    explicit QArrayExperiment(QObject *parent = 0) :
        QObject(parent) {}

    virtual vector<Result> experiment(Op op, unsigned nTest, vector<AlgoName> testAlgos, bool shuffle) {
        Q_UNUSED(op);
        Q_UNUSED(nTest);
        Q_UNUSED(testAlgos);
        Q_UNUSED(shuffle);
    }

public slots:
    void slotRunArrayExperiment(Op op, unsigned nTest, vector<AlgoName> testAlgos, bool shuffle) {
        vector<Result> res = experiment(op, nTest, testAlgos, shuffle);
        emit signalExperimentFinish(res);
    }

signals:
    void signalExperimentFinish(vector<Result> res);
    void signalUpdateProgress(int value);
};


//********************************************

template <typename dtype>
class ArrayExperiment : public QArrayExperiment
{
    //Q_OBJECT

    vector<dtype> inputs;
    Distribution distribution;


public:
    ArrayExperiment(const vector<dtype> &newInputs, const Distribution &newDistribution) : inputs(newInputs), distribution(newDistribution) {
        if (newInputs.empty())
            throw ArrayExperimentException("Constructor: input vector is empty");
    }

    template <typename inputType>
    ArrayExperiment(const vector<inputType> &newInputs, const Distribution &newDistribution) : distribution(newDistribution) {
        if (newInputs.empty())
            throw ArrayExperimentException("Constructor: input vector is empty");
        for (long long i=0; i<newInputs.size(); i++) inputs.push_back(dtype(newInputs[i]));
    }

    //---------------------------------------------     EXPERIMENTING
    // for an experiment, we random shuffle the input nTest times.
    // For each shuffle, we calculate the result of each algorithm

    iFloat groundTruth(const vector<dtype> &inputs, Op op) {
        iFloat res = 0;
        for (unsigned i=0; i<inputs.size(); i++) res = numOperate(res, iFloat(inputs[i]), op);
        return res;
    }

    // shuffle = true means after each test, the dataset is shuffled
    // shuffle = false means after each test, the dataset is created new using the distribution
    vector<Result> experiment(Op op, int nTest, vector<Algorithm<dtype> > algorithms, bool shuffle) {
        ArrayGenerator arrGen(distribution);
        vector<Result> res;
        res.clear();

        res.push_back(Result(shuffle, GROUND_TRUTH)); // if we use shuffle it means a ground truth exist, so output 1; else 0
        res.push_back(Result(groundTruth(inputs, op), GROUND_TRUTH));

        for (int t=1; t<=nTest; t++) {
            for (int i=0; i<algorithms.size(); i++)
                res.push_back(Result(algorithms[i].functor(inputs, op), algorithms[i].algo));

            if (shuffle) std::random_shuffle(inputs.begin(), inputs.end());
            else {                
                inputs = utils::convertArray<dtype>(arrGen.createArray(inputs.size()));
            }
            emit signalUpdateProgress(double(t)*100/nTest);
        }

        emit signalExperimentFinish(res);
        return res;
    }

};

#endif // ARRAYEXPERIMENT_H
