#ifndef UTILITYENUM_H
#define UTILITYENUM_H

#include <ifloat.h>
using std::vector;

//
enum Op{ADD, SUB, MUL, DIV, MATMUL};

const Op OpList[5] = {ADD, SUB, MUL, DIV, MATMUL};

//
enum Precision {PSINGLE, PDOUBLE};

const vector<Precision> PrecisionList = {PSINGLE, PDOUBLE};

//
enum DataType{ARRAY, MATRIX};

const vector<DataType> DataTypeList = {ARRAY, MATRIX};

//
enum AlgoName {GROUND_TRUTH, LINEAR, SPLIT_MERGE, SORT, SORT_APPEND, FAST2SUM, KNUTH2SUM};

const vector<AlgoName> AlgoNameList = {GROUND_TRUTH, LINEAR, SPLIT_MERGE, SORT, SORT_APPEND, FAST2SUM, KNUTH2SUM};

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
    if (algoName==FAST2SUM) return "FAST2SUM";
    if (algoName==KNUTH2SUM) return "KNUTH2SUM";

    throw("unknown algo2string");
}

inline AlgoName string2Algo(QString algoName) {
    if (algoName=="GROUND_TRUTH") return GROUND_TRUTH;
    if (algoName=="LINEAR") return LINEAR;
    if (algoName=="SPLIT_MERGE") return SPLIT_MERGE;
    if (algoName=="SORT") return SORT;
    if (algoName=="SORT_APPEND") return SORT_APPEND;
    if (algoName=="FAST2SUM") return FAST2SUM;
    if (algoName=="KNUTH2SUM") return KNUTH2SUM;

    throw("unknown string2algo");
}

inline QString prec2String(Precision precision) {
    if (precision==PDOUBLE) return "PDOUBLE";
    if (precision==PSINGLE) return "PSINGLE";
    throw("unknown precision type");
}

inline Precision string2prec(QString precision) {
    if (precision=="PDOUBLE") return PDOUBLE;
    if (precision=="PSINGLE") return PSINGLE;


    throw("unknown precision string");
}

#endif // UTILITYENUM_H
