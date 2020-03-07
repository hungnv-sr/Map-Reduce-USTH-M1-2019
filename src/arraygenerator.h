#ifndef ARRAYDATAGENERATOR_H
#define ARRAYDATAGENERATOR_H

#include <ifloat.h>
#include <distribution.h>
#include <randomgenerator.h>
#include <vector>
#include <fstream>
using std::vector;

typedef long long ll;

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

        int checkPoint = nData / 100;
        int cnt = 0;
        for (int i=0; i<nData; i++) {
            arr.push_back(rander.rand());
            cnt++;
            if (cnt==checkPoint) {
                qDebug() << "i = " << i << "\n";
                signalUpdateProgress(double(i+1)/nData*100);
                cnt = 0;
            }
        }

        emit signalGenerateFinish(arr);
    }

signals:
    void signalGenerateFinish(const vector<double>& arr);

    void signalUpdateProgress(int value);
};

#endif // ARRAYDATAGENERATOR_H
