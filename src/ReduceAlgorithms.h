#ifndef REDUCEALGORITHMS_H
#define REDUCEALGORITHMS_H

#include <ifloat.h>
#include <matrix.h>
#include <utilityenum.h>
#include <queue>

// pointer to function definition
template <typename dtype>
using AlgoFunction = iFloat(*)(const vector<dtype>&, Op);


//--------------------------
template <typename dtype>
inline iFloat linearAlgo(const vector<dtype>& inputs, Op op) {
    dtype summer = inputs[0];
    for (int i=1; i<inputs.size(); i++) summer = numOperate(summer, inputs[i], op);
    return iFloat(summer);
}

//----------------------------------------------    SPLIT/MERGE ALGORITHM
template <typename dtype>
inline dtype splitMerge(const vector<dtype> &inputs, Op op, int l, int r) {
    if (l==r) return inputs[l];
    int mid = (l+r)/2;
    return numOperate(splitMerge(inputs, op, l, mid), splitMerge(inputs, op, mid+1, r), op);
}

template <typename dtype>
inline iFloat splitMergeAlgo(const vector<dtype> &inputs, Op op) {
    dtype res = splitMerge(inputs, op, 0, inputs.size() - 1);
    return iFloat(res);
}

template <typename dtype>
inline iFloat sortAlgo(const vector<dtype>& inputs, Op op) {
    vector<dtype> data = inputs;

    std::sort(data.begin(), data.end());
    dtype res = data[0];
    for (int i=1; i<data.size(); i++) res = numOperate(res, data[i], op);

    return iFloat(res);
}

// first, sort the array. Then repeat N-1 times:
// 1. get 2 smallest number, sum them and remove them from array.
// 2. Push the sum back into the array
// 3. repeat
template<typename dtype>
inline iFloat sortAppendAlgo(const vector<dtype>& inputs, Op op) {
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

    return iFloat(res);
}

//---------------
template<typename dtype>
inline AlgoFunction<dtype> algo2functor(AlgoName algoName) {
    if (algoName==GROUND_TRUTH) throw("algo2functor: algoName==GROUND_TRUTH is not allowed"); // this should never happen
    if (algoName==LINEAR) return linearAlgo;
    if (algoName==SPLIT_MERGE) return splitMergeAlgo;
    if (algoName==SORT) return sortAlgo;
    if (algoName==SORT_APPEND) return sortAppendAlgo;
}

inline bool forMatrix(AlgoName algoName) {
    if (algoName==GROUND_TRUTH) return true;
    if (algoName==LINEAR) return true;
    if (algoName==SPLIT_MERGE) return true;
    if (algoName==SORT) return false;
    if (algoName==SORT_APPEND) return false;
}

template <typename dtype>
class Algorithm
{
public:
    const AlgoName algo;
    //const std::variant<AlgoFunction<float>, AlgoFunction<double>  functor;
    const AlgoFunction<dtype> functor;

public:
    Algorithm(AlgoName newAlgo, AlgoFunction<dtype> newFunctor) : algo(newAlgo), functor(newFunctor) {

    }
};

#endif // REDUCEALGORITHMS_H
