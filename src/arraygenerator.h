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


class ArrayGenerator : public QObject
{
    Q_OBJECT

    RandomGenerator rander;
public:
    ArrayGenerator(Distribution distribution);

    void generateArray(int nData, vector<double> &arr);

public slots:
    void slotGenerateArray(int nData);

signals:
    void signalGenerateFinish(const vector<double>& arr);

    void signalUpdateProgress(int value);
};

#endif // ARRAYDATAGENERATOR_H
