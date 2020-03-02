#include "matrixgenerator.h"

MatrixGenerator::MatrixGenerator(Distribution distribution) : rander(distribution)
{

}

Matrix<double> MatrixGenerator::randomMatrix(unsigned int height, unsigned int width) {
    Matrix<double> res(height, width);
    for (unsigned i=0; i<height*width; i++) res[i] = rander.rand();
    return res;
}

void  MatrixGenerator::generateMatrix(int nData, int matSize, vector<Matrix<double> > &mats) {
    mats.clear();

    for (int i=0; i<nData; i++) mats.push_back(randomMatrix(matSize, matSize));
}

void MatrixGenerator::slotGenerateMatrix(int nData, int matSize) {
    vector<Matrix<double> > mats;
    mats.clear();

    for (int i=0; i<nData; i++) mats.push_back(randomMatrix(matSize, matSize));

    emit signalGenerateFinish(mats);
}
