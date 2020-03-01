#ifndef BASEEXPERIMENT_H
#define BASEEXPERIMENT_H

#include <ifloat.h>
#include <randomgenerator.h>


enum Algo {LINEAR, SPLIT_MERGE, SORT, SORT_APPEND, GROUND_TRUTH};

struct Result {
    iFloat value;
    Algo algoUsed;
    Result(iFloat v, Algo algo) {value = v; algoUsed = algo;}
};

class BaseExperiment
{
protected:
    BaseExperiment() {};
};

#endif // BASEEXPERIMENT_H
