#ifndef ARRAYEXPERIMENT_H
#define ARRAYEXPERIMENT_H

#include <utilityenum.h>
#include <vector>
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

//--------------- template class can't inherit QObject, so we do it indirectly
class QArrayExperiment : public QObject
{
    Q_OBJECT

public:
    explicit QArrayExperiment(QObject *parent = 0) :
        QObject(parent) {}

    virtual vector<Result> experiment(Op op, unsigned nTest, vector<Algo> testAlgos, bool shuffle) {}

public slots:
    void slotRunArrayExperiment(Op op, unsigned nTest, vector<Algo> testAlgos, bool shuffle) {
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


    //----------------------------------------------    LINEAR ALGORITHM
    iFloat linearTest(const vector<dtype> &inputs, Op op) {
        dtype res = 0;
        for (unsigned i=0; i<inputs.size(); i++) res = numOperate(res, inputs[i], op);
        return res;
    }

    //----------------------------------------------    SPLIT/MERGE ALGORITHM
    dtype splitMerge(const vector<dtype> &inputs, Op op, long long l, long long r) {
        if (l>r)
            throw ArrayExperimentException("SplitMerge error: l can't be > r for valid inputs");

        if (l==r) return inputs[l];
        long long mid = (l+r)/2;
        return numOperate(splitMerge(inputs, op, l, mid), splitMerge(inputs, op, mid+1, r), op);
    }

    iFloat splitMergeTest(const vector<dtype> &inputs, Op op) {
        dtype res = splitMerge(inputs, op, 0, inputs.size() - 1);
        return res;
    }

    iFloat sortTest(vector<dtype> inputs, Op op) {
        std::sort(inputs.begin(), inputs.end());

        dtype res = 0;
        for (unsigned i=0; i<inputs.size(); i++) res = numOperate(res, inputs[i], op);

        return res;
    }

    // first, sort the array. Then repeat N-1 times:
    // 1. get 2 smallest number, sum them and remove them from array.
    // 2. Push the sum back into the array
    // 3. repeat
    iFloat sortAppendTest(vector<dtype> inputs, Op op) {
        std::priority_queue<dtype, vector<dtype>, std::greater<dtype> > minHeap;
        for (unsigned i=0; i<inputs.size(); i++) minHeap.push(inputs[i]);

        for (unsigned i=1; i<inputs.size(); i++) {
            dtype a = minHeap.top();
            minHeap.pop();
            dtype b = minHeap.top();
            minHeap.pop();
            minHeap.push(numOperate(a, b, op));
        }

        dtype res = minHeap.top();

        return res;
    }

    //---------------------------------------------     EXPERIMENTING
    // for an experiment, we random shuffle the input nTest times.
    // For each shuffle, we calculate the result of each algorithm

    iFloat groundTruth(const vector<dtype> &inputs, Op op) {
        iFloat res = 0;
        for (unsigned i=0; i<inputs.size(); i++) res = numOperate(res, iFloat(inputs[i]), op);
        return res;
    }

    vector<Result> experiment(Op op, unsigned nTest, vector<Algo> testAlgos, bool shuffle) {
        ArrayGenerator arrGen(distribution);
        vector<Result> res;
        res.clear();

        res.push_back(Result(shuffle, GROUND_TRUTH)); // if we use shuffle it means a ground truth exist, so output 1
        res.push_back(Result(groundTruth(inputs, op), GROUND_TRUTH));
        qDebug() << "After ground truth\n";

        bool linear = 0, splitMerge = 0, sortLinear = 0, sortAppend = 0;
        for (unsigned i=0; i<testAlgos.size(); i++) {
            if (testAlgos[i]==LINEAR) linear = true;
            if (testAlgos[i]==SPLIT_MERGE) splitMerge = true;
            if (testAlgos[i]==SORT) sortLinear = true;
            if (testAlgos[i]==SORT_APPEND) sortAppend = true;
        }

        qDebug() << "after boolean testAlgos\n";

        for (unsigned t=1; t<=nTest; t++) {
            if (linear) res.push_back(Result(linearTest(inputs, op), LINEAR));
            if (splitMerge) res.push_back(Result(splitMergeTest(inputs, op), SPLIT_MERGE));
            if (sortLinear) res.push_back(Result(sortTest(inputs, op), SORT));
            if (sortAppend) res.push_back(Result(sortAppendTest(inputs, op), SORT_APPEND));

            qDebug() << "after running algorithms\n";
            if (shuffle) std::random_shuffle(inputs.begin(), inputs.end());
            else {                
                inputs = utils::convertArray<dtype>(arrGen.createArray(inputs.size()));
            }
            emit signalUpdateProgress(t*100/nTest);
        }

        emit signalExperimentFinish(res);
        return res;
    }

};

#endif // ARRAYEXPERIMENT_H
