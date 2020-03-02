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
    MatrixGenerator(Distribution distribution);

    Matrix<double> randomMatrix(unsigned height, unsigned width);

    void generateMatrix(int nData, int matSize, vector<Matrix<double> > &mats);

public slots:
    void slotGenerateMatrix(int nData, int matSize);

signals:
    void signalGenerateFinish(const vector<Matrix<double> > &mats);
};

#endif // MATRIXGENERATOR_H
