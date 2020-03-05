#ifndef BASEEXPERIMENT_H
#define BASEEXPERIMENT_H

#include <ifloat.h>
using std::vector;

//
enum Op{ADD, SUB, MUL, DIV, MATMUL};

const Op OpList[5] = {ADD, SUB, MUL, DIV, MATMUL};

//
enum Precision {PHALF, PSINGLE, PDOUBLE};

const Precision PrecisionList[5] = {PHALF, PSINGLE, PDOUBLE};

//
enum DataType{ARRAY, MATRIX};

const DataType DataTypeList[2] = {ARRAY, MATRIX};

//
enum Algo {GROUND_TRUTH, LINEAR, SPLIT_MERGE, SORT, SORT_APPEND};

const Algo AlgoList[5] = {GROUND_TRUTH, LINEAR, SPLIT_MERGE, SORT, SORT_APPEND};

//
struct Result {
    iFloat value;
    Algo algoUsed;
    Result(iFloat v, Algo algo) {value = v; algoUsed = algo;}

    Result() {value = 0; algoUsed = GROUND_TRUTH;}
};

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


#endif // BASEEXPERIMENT_H
