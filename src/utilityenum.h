#ifndef BASEEXPERIMENT_H
#define BASEEXPERIMENT_H

#include <ifloat.h>
using std::vector;

enum Op{ADD, SUB, MUL, DIV, MATMUL};

enum DataType{NUMERIC, ARRAY, MATRIX};

enum Algo {LINEAR, SPLIT_MERGE, SORT, SORT_APPEND, GROUND_TRUTH};

struct Result {
    iFloat value;
    Algo algoUsed;
    Result(iFloat v, Algo algo) {value = v; algoUsed = algo;}

    Result() {value = 0; algoUsed = GROUND_TRUTH;}
};



#endif // BASEEXPERIMENT_H
