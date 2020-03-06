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
            qDebug() << "Array Controller in single " << inputs.size();

            floatExperiment = new ArrayExperiment<float>(inputs, distribution);
            connect(floatExperiment, &ArrayExperiment<float>::signalExperimentFinish,
                    this, &ArrayExperimentController::slotExperimentFinish);
            connect(floatExperiment, &ArrayExperiment<float>::signalUpdateProgress,
                    this, &ArrayExperimentController::slotUpdateProgress);
        }

        if (precision==PDOUBLE) {
            qDebug() << "Array Controller in double\n";
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
    void slotRunArrayExperiment(Op op, unsigned nTest, vector<AlgoName> requiredAlgos, bool shuffle) {
        // we need to make sure each algorithm only appears once
        std::map<AlgoName, bool> algoNames;
        std::map<AlgoName, bool>::iterator it;
        algoNames.clear();

        for (unsigned i=0; i<requiredAlgos.size(); i++) algoNames[requiredAlgos[i]] = 1;

        if (precision==PSINGLE) {
            vector<Algorithm<float> > algos;

            for (it = algoNames.begin(); it!=algoNames.end(); it++) {
                AlgoName thisAlgoName = it->first;
                algos.push_back(Algorithm<float>(thisAlgoName, algo2functor<float>(thisAlgoName)));
            }

            floatExperiment->experiment(op, nTest, algos, shuffle);
        }

        if (precision==PDOUBLE) {
            vector<Algorithm<double> > algos;

            for (it = algoNames.begin(); it!=algoNames.end(); it++) {
                AlgoName thisAlgoName = it->first;
                algos.push_back(Algorithm<double>(thisAlgoName, algo2functor<double>(thisAlgoName)));
            }

            doubleExperiment->experiment(op, nTest, algos, shuffle);
        }
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
