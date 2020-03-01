#include "arraydatagenerator.h"

ArrayGenerator::ArrayGenerator(Distribution distribution) : rander(distribution)
{

}

void  ArrayGenerator::generateArray(int nData, vector<double> &res) {
    res.clear();

    for (int i=0; i<nData; i++) res.push_back(rander.rand());
}
