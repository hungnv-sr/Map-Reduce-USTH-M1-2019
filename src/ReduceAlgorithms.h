#ifndef REDUCEALGORITHMS_H
#define REDUCEALGORITHMS_H

#include <ifloat.h>
#include <matrix.h>
#include <utilityenum.h>
#include <queue>

// pointer to function definition
template <typename dtype>
using AlgoFunction = iFloat(*)(const vector<dtype>&, Op);

// function to calculate given an input Op operator.
// It's easier to have one function than writing 4 if-statements each time
template <class dtype>
inline dtype numOperate(const dtype &a, const dtype &b, Op op) {
    if (op==ADD) return a + b;
    if (op==SUB) return a - b;
    if (op==MUL) return a * b;
    if (op==DIV) return a / b;

    throw ("NumOperate: Unknown Op");
}

// specializing for matrix
template<typename matType>
inline Matrix<matType> numOperate(const Matrix<matType> &a, const Matrix<matType> &b, Op op) {
    if (op==ADD) return a + b;
    if (op==SUB) return a - b;
    if (op==MUL) return a * b;
    if (op==DIV) return a / b;
    if (op==MATMUL) return a.matmul(b);

    throw ("NumOperate: Unknown Op");
}

//------------------------  LINEAR ALGORITHM
template <typename dtype>
inline iFloat linearAlgo(const vector<dtype>& inputs, Op op) {
    dtype summer = inputs[0];
    for (unsigned i=1; i<inputs.size(); i++) summer = numOperate(summer, inputs[i], op);
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
    for (unsigned i=1; i<data.size(); i++) res = numOperate(res, data[i], op);

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

//-- fast2sum and knuth2sum references: http://perso.ens-lyon.fr/jean-michel.muller/Conf-Journees-Knuth.pdf
// this 2 only make sense for addition, so this function will always do + regardless of the Op op
// We use compensated sum method

// for both algorithms, the idea is that we accumulate the error,
// then at the end, result = sum + errorSum.

// absolute value function that work with both matrix and number
template <typename dtype>
dtype anyAbs(const dtype& x) {
    if (x > 0.0) return x;
    else return -x;
}

template <typename dtype>
inline dtype fast2sum(const dtype &a, const dtype &b) {
    dtype s, z, r;
    if (anyAbs(a) < anyAbs(b)) {
        dtype tmp1 = b, tmp2 = a; // basically swap(a,b). But we have to do this because a, b are const
        s = tmp1 + tmp2;
        z = s - tmp1;
        r = tmp2 - z;
        return r;
    }

    s = a + b;
    z = s - a;
    r = b - z;
    return r; // return the error, because s can be calculated anywhere
}

template<typename dtype>
inline iFloat fast2sumAlgo(const vector<dtype>& inputs, Op op) {
    dtype summer = inputs[0];
    dtype errorSum = 0*inputs[0];   // we do this to make it compatible with matrix type,
                                    // because matrix1 = 0*matrix2 is possible, but matrix1 = 0 is not.
                                    // for correct input (float, double, etc) , it is the same as errorSum = 0

    for (unsigned i=1; i<inputs.size(); i++) {
        errorSum = errorSum + fast2sum(summer, inputs[i]);
        summer = summer + inputs[i];
    }
    return iFloat(summer + errorSum);
}

//----
template <typename dtype>
inline dtype knuth2sum(const dtype &a, const dtype &b) {
    dtype s, a2, b2, da, db, r;
    s = a + b;
    a2 = s - b;
    b2 = s - a;
    da = a - a2;
    db = b - b2;
    r = da + db;
    return r;
}

template<typename dtype>
inline iFloat knuth2sumAlgo(const vector<dtype>& inputs, Op op) {
    dtype summer = inputs[0];
    dtype errorSum = 0*inputs[0];

    for (unsigned i=1; i<inputs.size(); i++) {
        errorSum = errorSum + knuth2sum(summer, inputs[i]);
        summer = summer + inputs[i];
    }
    return iFloat(summer + errorSum);
}

//---------------
template<typename dtype>
inline AlgoFunction<dtype> algo2functor(AlgoName algoName) {
    if (algoName==GROUND_TRUTH) throw("algo2functor: algoName==GROUND_TRUTH is not allowed"); // this should never happen
    if (algoName==LINEAR) return linearAlgo;
    if (algoName==SPLIT_MERGE) return splitMergeAlgo;
    if (algoName==SORT) return sortAlgo;
    if (algoName==SORT_APPEND) return sortAppendAlgo;
    if (algoName==FAST2SUM) return fast2sumAlgo;
    if (algoName==KNUTH2SUM) return knuth2sumAlgo;

    throw("algo2functor algo not found");
}

inline bool forMatrix(AlgoName algoName) {
    if (algoName==GROUND_TRUTH) return true;
    if (algoName==LINEAR) return true;
    if (algoName==SPLIT_MERGE) return true;
    if (algoName==SORT) return false;
    if (algoName==SORT_APPEND) return false;
    if (algoName==FAST2SUM) return false;
    if (algoName==KNUTH2SUM) return false;

    throw("forMatrix algo not found");
}

template <typename dtype>
class Algorithm
{
public:
    const AlgoName algo;
    const AlgoFunction<dtype> functor;

public:
    Algorithm(AlgoName newAlgo, AlgoFunction<dtype> newFunctor) : algo(newAlgo), functor(newFunctor) {

    }
};

#endif // REDUCEALGORITHMS_H
