#include "arrayexperiment.h"

ArrayExperiment::ArrayExperiment()
{

}

//----------------------------------------------    LINEAR ALGORITHM
iFloat ArrayExperiment::linearTest(const vector<double> &inputs, Op op) {
    if (inputs.size()==0)
        throw ArrayExperimentException("Linear test error: input vector is empty");

    double res = 0;
    for (unsigned i=0; i<inputs.size(); i++) res = numOperate(res, inputs[i], op);

    return res;
}


//----------------------------------------------    SPLIT/MERGE ALGORITHM
double splitMerge(const vector<double> &inputs, Op op, int l, int r) {
    if (l>r)
        throw ArrayExperimentException("SplitMerge error: l can't be > r for valid inputs");

    if (l==r) return inputs[l];
    int mid = (l+r)/2;
    return numOperate(splitMerge(inputs, op, l, mid), splitMerge(inputs, op, mid+1, r), op);
}

iFloat ArrayExperiment::splitMergeTest(const vector<double> &inputs, Op op) {
    if (inputs.size()==0)
        throw ArrayExperimentException("Split merge test error: input vector is empty");

    double res = splitMerge(inputs, op, 0, inputs.size() - 1);

    return res;
}

iFloat ArrayExperiment::sortTest(vector<double> inputs, Op op) {
    if (inputs.size()==0)
        throw ArrayExperimentException("Sort test error: input vector is empty");

    std::sort(inputs.begin(), inputs.end());

    double res = 0;
    for (unsigned i=0; i<inputs.size(); i++) res = numOperate(res, inputs[i], op);

    return res;
}

iFloat ArrayExperiment::sortAppendTest(vector<double> inputs, Op op) {
    if (inputs.size()==0)
        throw ArrayExperimentException("Sort test error: input vector is empty");

    std::priority_queue<double, vector<double>, std::greater<double> > minHeap;
    for (unsigned i=0; i<inputs.size(); i++) minHeap.push(inputs[i]);

    for (unsigned i=1; i<inputs.size(); i++) {
        double a = minHeap.top();
        minHeap.pop();
        double b = minHeap.top();
        minHeap.pop();
        minHeap.push(a+b);
    }

    return minHeap.top();
}


//---------------------------------------------     EXPERIMENTING
// for an experiment, we random shuffle the input nTest times.
// For each shuffle, we calculate the result of each algorithm

iFloat ArrayExperiment::groundTruth(vector<double> inputs, Op op) {
    iFloat res = 0;
    for (unsigned i=0; i<inputs.size(); i++) res = numOperate(res, iFloat(inputs[i]), op);
    return res;
}

vector<Result> ArrayExperiment::experiment(vector<double> inputs, Op op, unsigned int nTest, vector<Algo> testAlgos, bool shuffle=true, Distribution distribution=Distribution(0,0,0)) {
    ArrayGenerator arrGen(distribution);
    vector<Result> res;
    res.clear();

    res.push_back(Result(shuffle, GROUND_TRUTH)); // if we use shuffle it means a ground truth exist, so output 1
    res.push_back(Result(groundTruth(inputs, op), GROUND_TRUTH));

    bool linear = 0, splitMerge = 0, sortLinear = 0, sortAppend = 0;
    for (unsigned i=0; i<testAlgos.size(); i++) {
        if (testAlgos[i]==LINEAR) linear = true;
        if (testAlgos[i]==SPLIT_MERGE) splitMerge = true;
        if (testAlgos[i]==SORT) sortLinear = true;
        if (testAlgos[i]==SORT_APPEND) sortAppend = true;
    }

    for (unsigned t=1; t<=nTest; t++) {
        if (linear) res.push_back(Result(linearTest(inputs, op), LINEAR));
        if (splitMerge) res.push_back(Result(splitMergeTest(inputs, op), SPLIT_MERGE));
        if (sortLinear) res.push_back(Result(sortTest(inputs, op), SORT));
        if (sortAppend) res.push_back(Result(sortAppendTest(inputs, op), SORT_APPEND));

        if (shuffle) std::random_shuffle(inputs.begin(), inputs.end());
        else {
            arrGen.generateArray(inputs.size(), inputs);
        }
    }

    return res;
}
