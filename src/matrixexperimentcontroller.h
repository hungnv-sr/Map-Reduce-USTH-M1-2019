#ifndef MATRIXEXPERIMENTCONTROLLER_H
#define MATRIXEXPERIMENTCONTROLLER_H

#include <matrixexperiment.h>

class MatrixExperimentController : public QObject
{
    Q_OBJECT

    Precision precision;
    MatrixExperiment<float> *floatExperiment;
    MatrixExperiment<double> *doubleExperiment;

public:
    MatrixExperimentController(const vector<Matrix<double> > &inputs, const Distribution &distribution, Precision prec) {
        precision = prec;

        if (precision==PSINGLE) {
            floatExperiment = new MatrixExperiment<float>(inputs, distribution);
            connect(floatExperiment, &MatrixExperiment<float>::signalExperimentFinish,
                    this, &MatrixExperimentController::slotExperimentFinish);
            connect(floatExperiment, &MatrixExperiment<float>::signalUpdateProgress,
                    this, &MatrixExperimentController::slotUpdateProgress);
        }

        if (precision==PDOUBLE) {
            doubleExperiment = new MatrixExperiment<double>(inputs, distribution);

            connect(doubleExperiment, &MatrixExperiment<double>::signalExperimentFinish,
                    this, &MatrixExperimentController::slotExperimentFinish);
            connect(doubleExperiment, &MatrixExperiment<double>::signalUpdateProgress,
                    this, &MatrixExperimentController::slotUpdateProgress);
        }
    }

    ~MatrixExperimentController() {
        if (precision==PSINGLE) delete floatExperiment;
        else if (precision==PDOUBLE) delete doubleExperiment;
    }

public slots:
    void slotRunMatrixExperiment(Op op, unsigned nTest, vector<Algo> testAlgos, bool shuffle) {
        if (precision==PSINGLE)
            floatExperiment->experiment(op, nTest, testAlgos, shuffle);
        if (precision==PDOUBLE)
            doubleExperiment->experiment(op, nTest, testAlgos, shuffle);
    }

    void slotExperimentFinish(vector<Result> res) {
        emit signalExperimentFinish(res);
    }

    void slotUpdateProgress(int value) {
        emit signalUpdateProgress(value);
    }


signals:
    void signalExperimentFinish(vector<Result> res);
    void signalUpdateProgress(int value);
};

#endif // MATRIXEXPERIMENTCONTROLLER_H
