#ifndef ARRAYDATAGENERATOR_H
#define ARRAYDATAGENERATOR_H

#include <ifloat.h>
#include <distribution.h>
#include <randomgenerator.h>
#include <vector>
#include <fstream>
using std::vector;

struct ArrayGeneratorException : public std::exception {
private:
    QString msg;

public:
    ArrayGeneratorException(QString mess) {
        msg = mess;
    }
    const char* what() const throw() {
        return msg.toStdString().c_str();
    }
};

//--------------- template class can't inherit QObject, so we do it indirectly
class QArrayGenerator : public QObject
{
    Q_OBJECT

public:
    explicit QArrayGenerator(QObject *parent = 0) :
        QObject(parent) {}

    virtual vector<Result> experiment(Op op, unsigned nTest, vector<Algo> testAlgos, bool shuffle) {}

public slots:
    virtual void slotRunArrayExperiment(Op op, unsigned nTest, vector<Algo> testAlgos, bool shuffle) {
        vector<Result> res = experiment(op, nTest, testAlgos, shuffle);
        emit signalExperimentFinish(res);
    }

signals:
    void signalExperimentFinish(vector<Result> res);
    void signalUpdateProgress(int value);
};



class ArrayGenerator : public QObject
{
    Q_OBJECT

    RandomGenerator rander;
public:
    ArrayGenerator(Distribution distribution) : rander(distribution) {

    }

    vector<double> createArray(int nData) {
        vector<double> res;
        for (int i=0; i<nData; i++) res.push_back(rander.rand());
        return res;
    }

    void generateArray(int nData, vector<double> &arr) {
        arr.clear();

        for (int i=0; i<nData; i++) arr.push_back(rander.rand());
    }

public slots:
    void slotGenerateArray(int nData) {
        vector<double> arr;
        arr.clear();

        for (int i=0; i<nData; i++) {
            arr.push_back(rander.rand());
            emit signalUpdateProgress(i*100/nData);
        }

        emit signalGenerateFinish(arr);
    }

signals:
    void signalGenerateFinish(const vector<double>& arr);

    void signalUpdateProgress(int value);
};

#endif // ARRAYDATAGENERATOR_H
