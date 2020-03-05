#ifndef ARRAYEXPERIMENTCONTROLLER_H
#define ARRAYEXPERIMENTCONTROLLER_H

#include <arrayexperiment.h>

class ArrayExperimentController : public QObject
{
    Q_OBJECT

    Precision precision;
    ArrayExperiment<float> *floatExperiment;
    ArrayExperiment<double> *doubleExperiment;

public:
    ArrayExperimentController(const vector<double> &inputs, const Distribution &distribution, Precision prec) {
        precision = prec;

        if (precision==PSINGLE) {
            qDebug() << "Controller in single " << inputs.size();

            floatExperiment = new ArrayExperiment<float>(inputs, distribution);
            connect(floatExperiment, &ArrayExperiment<float>::signalExperimentFinish,
                    this, &ArrayExperimentController::slotExperimentFinish);
            connect(floatExperiment, &ArrayExperiment<float>::signalUpdateProgress,
                    this, &ArrayExperimentController::slotUpdateProgress);
        }

        if (precision==PDOUBLE) {
            qDebug() << "Controller in double\n";
            doubleExperiment = new ArrayExperiment<double>(inputs, distribution);
            connect(doubleExperiment, &ArrayExperiment<double>::signalExperimentFinish,
                    this, &ArrayExperimentController::slotExperimentFinish);
            connect(doubleExperiment, &ArrayExperiment<double>::signalUpdateProgress,
                    this, &ArrayExperimentController::slotUpdateProgress);
        }
    }

    ~ArrayExperimentController() {
        if (precision==PSINGLE) delete floatExperiment;
        else if (precision==PDOUBLE) delete doubleExperiment;
    }

public slots:
    void slotRunArrayExperiment(Op op, unsigned nTest, vector<Algo> testAlgos, bool shuffle) {
        if (precision==PSINGLE)
            floatExperiment->experiment(op, nTest, testAlgos, shuffle);
        if (precision==PDOUBLE)
            doubleExperiment->experiment(op, nTest, testAlgos, shuffle);
    }

    void slotExperimentFinish(vector<Result> res) {
        qDebug() << "Controller received experiment finished\n";
        emit signalExperimentFinish(res);
    }

    void slotUpdateProgress(int value) {
        emit signalUpdateProgress(value);
    }


signals:
    void signalExperimentFinish(vector<Result> res);
    void signalUpdateProgress(int value);

};

#endif // ARRAYEXPERIMENTCONTROLLER_H
