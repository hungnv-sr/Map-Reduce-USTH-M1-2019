#pragma once
#ifndef MATRIXEXPERIMENT_H
#define MATRIXEXPERIMENT_H

#include <utilityenum.h>
#include <ReduceAlgorithms.h>
#include <vector>
#include <matrix.h>
#include <ifloat.h>
#include <randomgenerator.h>
#include <matrixgenerator.h>
using std::vector;


struct MatrixExperimentException : public std::exception {
private:
    QString msg;

public:
    MatrixExperimentException(QString mess) {
        msg = mess;
    }
    const char* what() const throw() {
        return msg.toStdString().c_str();
    }
};

class QMatrixExperiment : public QObject
{
    Q_OBJECT

public:
    explicit QMatrixExperiment(QObject *parent = 0) :
        QObject(parent) {}

    virtual vector<Result> experiment(Op op, unsigned nTest, vector<AlgoName> testAlgos, bool shuffle) {}

public slots:
    void slotRunArrayExperiment(Op op, unsigned nTest, vector<AlgoName> testAlgos, bool shuffle) {
        vector<Result> res = experiment(op, nTest, testAlgos, shuffle);
        emit signalExperimentFinish(res);
    }

signals:
    void signalExperimentFinish(vector<Result> res);
    void signalUpdateProgress(int value);
};

template <typename dtype>
class MatrixExperiment : public QMatrixExperiment
{
   // Q_OBJECT

    vector<Matrix<dtype> > inputMats;
    Distribution distribution;

public:
    MatrixExperiment(const vector<Matrix<dtype> > &newInputMats, const Distribution &newDistribution)
        : inputMats(newInputMats)
        , distribution(newDistribution)
    {
        if (newInputMats.size() == 0)
            qDebug() << "MATRIX EXPERIMENT CRITICAL ERROR: INPUT VECTOR SIZE 0";
            //throw MatrixExperimentException("Constructor: input vector size 0");
    }

    template <typename inputType>
    MatrixExperiment(const vector<Matrix<inputType> > &newInputMats, const Distribution &newDistribution)
        : distribution(newDistribution)
    {
        if (newInputMats.size() == 0)
            throw MatrixExperimentException("Constructor: input vector size 0");

        for (int i=0; i<newInputMats.size(); i++) inputMats.push_back(Matrix<dtype>(newInputMats[i]));
    }

    // Convert a vector of Matrix<dtype> to vector of Matrix<iFloat>
    vector<Matrix<iFloat> > dtype2iFloat(vector<Matrix<dtype> > matdv) {
        vector<Matrix<iFloat> > matfv;

        for (unsigned t=0; t<matdv.size(); t++) {
            unsigned height = matdv[t].getHeight(), width = matdv[t].getWidth();
            Matrix<iFloat> tmp(height, width, 0.0);

            for (unsigned i=0; i<height*width; i++) tmp[i] = matdv[t][i];

            matfv.push_back(tmp);
        }

        return matfv;
    }

    /*
    //----------------------------------------------    LINEAR ALGORITHM
    iFloat linearTest(const vector<Matrix<dtype> > &inputMats, Op op) {
        Matrix<dtype> res = inputMats[0];
        for (unsigned i=1; i<inputMats.size(); i++) res = matOperate(res, inputMats[i], op);

        return res.template sum<iFloat>();
    }

    //----------------------------------------------    SPLIT/MERGE ALGORITHM
    Matrix<dtype> splitMerge(const vector<Matrix<dtype> > &inputMats,Op op, long long l, long long r) {
        if (l>r)
            throw MatrixExperimentException("SplitMerge error: l can't be > r for valid inputs");
        if (l==r) return inputMats[l];
        long long mid = (l+r)/2;
        return matOperate(splitMerge(inputMats, op, l, mid), splitMerge(inputMats, op, mid+1, r), op);
    }

    iFloat splitMergeTest(const vector<Matrix<dtype> > &inputMats, Op op) {
        Matrix<dtype> res = splitMerge(inputMats, op, 0, inputMats.size() - 1);
        return res.template sum<iFloat>();
    }
    */

    //---------------------------------------------     EXPERIMENTING
    // for an experiment, we random shuffle the input nTest times.
    // For each shuffle, we calculate the result of each algorithm
    iFloat groundTruth(const vector<Matrix<dtype> > &inputMats, Op op) {
        vector<Matrix<iFloat> > hfInput = dtype2iFloat(inputMats);
        Matrix<iFloat> res = hfInput[0];
        for (unsigned i=1; i<hfInput.size(); i++) res = matOperate(res, hfInput[i], op);
        return iFloat(res);
    }

    vector<Result> experiment(Op op, unsigned nTest, vector<Algorithm<Matrix<dtype> > > algorithms, bool shuffle) {
        MatrixGenerator matrixGen(distribution);
        vector<Result> res;
        res.clear();

        res.push_back(Result(shuffle, GROUND_TRUTH)); // if we use shuffle it means a ground truth exist, so output 1
        res.push_back(Result(groundTruth(inputMats, op), GROUND_TRUTH));
        qDebug() << "After matrix ground truth\n";


        for (unsigned t=1; t<=nTest; t++) {
            for (int i=0; i<algorithms.size(); i++)
                res.push_back(Result(algorithms[i].functor(inputMats, op), algorithms[i].algo));

            if (shuffle) std::random_shuffle(inputMats.begin(), inputMats.end());
            else {
                inputMats = utils::convertMatrices<dtype>(matrixGen.createMatrices(inputMats.size(), inputMats[0].getHeight()));
            }
            emit signalUpdateProgress(t*100/nTest);
        }

        emit signalExperimentFinish(res);
        return res;
    }

};

#endif //MATRIXEXPERIMENT_H
