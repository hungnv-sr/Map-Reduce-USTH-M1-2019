#ifndef MATRIXEXPERIMENTCONTROLLER_H
#define MATRIXEXPERIMENTCONTROLLER_H

#include <utilityenum.h>
#include <ReduceAlgorithms.h>
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
            qDebug() << "Matrix Controller in single " << inputs.size();

            floatExperiment = new MatrixExperiment<float>(inputs, distribution);

            connect(floatExperiment, &MatrixExperiment<float>::signalExperimentFinish,
                    this, &MatrixExperimentController::slotExperimentFinish);
            connect(floatExperiment, &MatrixExperiment<float>::signalUpdateProgress,
                    this, &MatrixExperimentController::slotUpdateProgress);
        }

        if (precision==PDOUBLE) {
            qDebug() << "Matrix Controller in single " << inputs.size();

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
    void slotRunMatrixExperiment(Op op, unsigned nTest, vector<AlgoName> requiredAlgos, bool shuffle) {
        // we need to make sure each algorithm only appears once
        std::map<AlgoName, bool> algoNames;
        std::map<AlgoName, bool>::iterator it;
        algoNames.clear();

        for (unsigned i=0; i<requiredAlgos.size(); i++) algoNames[requiredAlgos[i]] = 1;


        if (precision==PSINGLE) {
            vector<Algorithm<Matrix<float> > > algos;

            for (it = algoNames.begin(); it!=algoNames.end(); it++) {
                AlgoName thisAlgoName = it->first;
                if (forMatrix(thisAlgoName)) // only add if this algorithm can be used with matrix
                    algos.push_back(Algorithm<Matrix<float> >(thisAlgoName, algo2functor<Matrix<float> >(thisAlgoName)));
            }

            floatExperiment->experiment(op, nTest, algos, shuffle);
        }

        if (precision==PDOUBLE) {
            vector<Algorithm<Matrix<double> > > algos;

            for (it = algoNames.begin(); it!=algoNames.end(); it++) {
                AlgoName thisAlgoName = it->first;
                if (forMatrix(thisAlgoName))
                    algos.push_back(Algorithm<Matrix<double> >(thisAlgoName, algo2functor<Matrix<double> >(thisAlgoName)));
            }

            doubleExperiment->experiment(op, nTest, algos, shuffle);
        }
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
