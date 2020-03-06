#ifndef MATRIXGENERATOR_H
#define MATRIXGENERATOR_H

#include <ifloat.h>
#include <distribution.h>
#include <randomgenerator.h>
#include <vector>
#include <fstream>
#include <matrix.h>

struct MatrixGeneratorException : public std::exception {
private:
    QString msg;

public:
    MatrixGeneratorException(QString mess) {
        msg = mess;
    }
    const char* what() const throw() {
        return msg.toStdString().c_str();
    }
};


class MatrixGenerator : public QObject
{
    Q_OBJECT

    RandomGenerator rander;

public:   
    MatrixGenerator(Distribution distribution) : rander(distribution) {

    }

    Matrix<double> randomMatrix(unsigned height, unsigned width) {
        Matrix<double> res(height, width);
        for (unsigned i=0; i<height*width; i++) res[i] = rander.rand();
        return res;
    }

    vector<Matrix<double> > createMatrices(int nData, int matSize) {
        vector<Matrix<double> > res;
        for (int i=0; i<nData; i++) res.push_back(randomMatrix(matSize, matSize));
        return res;
    }


    void generateMatrices(int nData, int matSize, vector<Matrix<double> > &mats) {
        mats.clear();
        for (int i=0; i<nData; i++) mats.push_back(randomMatrix(matSize, matSize));
    }

public slots:
    void slotGenerateMatrix(int nData, int matSize) {
        vector<Matrix<double> > mats;
        mats.clear();

        for (int i=0; i<nData; i++) {
            mats.push_back(randomMatrix(matSize, matSize));
            emit signalUpdateProgress(i*100/nData);
        }

        emit signalGenerateFinish(mats);
    }

signals:
    void signalGenerateFinish(const vector<Matrix<double> > &mats);

    void signalUpdateProgress(int value);
};

#endif // MATRIXGENERATOR_H
