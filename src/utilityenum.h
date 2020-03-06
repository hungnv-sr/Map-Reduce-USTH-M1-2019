#ifndef UTILITYENUM_H
#define UTILITYENUM_H

#include <ifloat.h>
using std::vector;

//
enum Op{ADD, SUB, MUL, DIV, MATMUL};

const Op OpList[5] = {ADD, SUB, MUL, DIV, MATMUL};

//
enum Precision {PHALF, PSINGLE, PDOUBLE};

const vector<Precision> PrecisionList = {PHALF, PSINGLE, PDOUBLE};

//
enum DataType{ARRAY, MATRIX};

const vector<DataType> DataTypeList = {ARRAY, MATRIX};

//
enum AlgoName {GROUND_TRUTH, LINEAR, SPLIT_MERGE, SORT, SORT_APPEND, KNUTH, TESTING};

const vector<AlgoName> AlgoNameList = {GROUND_TRUTH, LINEAR, SPLIT_MERGE, SORT, SORT_APPEND, KNUTH, TESTING};

//
struct Result {
    iFloat value;
    AlgoName algoUsed;
    Result(iFloat v, AlgoName algo) {value = v; algoUsed = algo;}

    Result() {value = 0; algoUsed = GROUND_TRUTH;}
};

inline QString algo2String(AlgoName algoName) {
    if (algoName==GROUND_TRUTH) return "GROUND_TRUTH";
    if (algoName==LINEAR) return "LINEAR";
    if (algoName==SPLIT_MERGE) return "SPLIT_MERGE";
    if (algoName==SORT) return "SORT";
    if (algoName==SORT_APPEND) return "SORT_APPEND";
    if (algoName==KNUTH) return "KNUTH";
    if (algoName==TESTING) return "TESTING";
    return "unknown";
}

inline AlgoName string2Algo(QString algoName) {
    if (algoName=="GROUND_TRUTH") return GROUND_TRUTH;
    if (algoName=="LINEAR") return LINEAR;
    if (algoName=="SPLIT_MERGE") return SPLIT_MERGE;
    if (algoName=="SORT") return SORT;
    if (algoName=="SORT_APPEND") return SORT_APPEND;
    if (algoName=="KNUTH") return KNUTH;
    if (algoName=="TESTING") return KNUTH;
}


#endif // UTILITYENUM_H
