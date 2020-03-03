#include "arraygenerator.h"

ArrayGenerator::ArrayGenerator(Distribution distribution) : rander(distribution)
{

}

void  ArrayGenerator::generateArray(int nData, vector<double> &arr) {
    arr.clear();

    for (int i=0; i<nData; i++) arr.push_back(rander.rand());
}

void ArrayGenerator::slotGenerateArray(int nData) {
    vector<double> arr;
    arr.clear();

    for (int i=0; i<nData; i++) {
        arr.push_back(rander.rand());
        emit signalUpdateProgress(i*100/nData);
    }

    emit signalGenerateFinish(arr);
}
