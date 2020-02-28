#include "matrixexperiment.h"

MatrixExperiment::MatrixExperiment()
{

}

// Convert a vector of Matrix<double> to vector of Matrix<iFloat>
vector<Matrix<iFloat> > MatrixExperiment::double2iFloat(vector<Matrix<double> > matdv) {
    vector<Matrix<iFloat> > matfv;

    for (unsigned t=0; t<matdv.size(); t++) {
        unsigned height = matdv[t].getHeight(), width = matdv[t].getWidth();
        Matrix<iFloat> tmp(height, width, 0.0);

        for (unsigned i=0; i<height*width; i++) tmp[i] = matdv[t][i];

        matfv.push_back(tmp);
    }

    return matfv;
}

// generate a random matrix using the random generator rander
Matrix<double> MatrixExperiment::randomMatrix(unsigned height, unsigned width, RandomGenerator& rander) {
    Matrix<double> res(height, width, 0);
    for (unsigned i=0; i<height*width; i++) res[i] = rander.rand();
    return res;
}


//----------------------------------------------    LINEAR ALGORITHM
iFloat MatrixExperiment::linearTest(vector<Matrix<double> > inputMats,Op op) {
    if (inputMats.size()==0)
        throw MatrixExperimentException("Linear test error: input vector is empty");

    Matrix<double> res = inputMats[0];
    for (unsigned i=1; i<inputMats.size(); i++) res = matOperate(res, inputMats[i], op);

    return res.sum<iFloat>();
}

//----------------------------------------------    SPLIT/MERGE ALGORITHM
Matrix<double> splitMerge(const vector<Matrix<double> > &inputMats,Op op, int l, int r) {
    if (l>r)
        throw MatrixExperimentException("SplitMerge error: l can't be > r for valid inputs");
    if (l==r) return inputMats[l];
    int mid = (l+r)/2;
    return matOperate(splitMerge(inputMats, op, l, mid), splitMerge(inputMats, op, mid+1, r), op);
}

iFloat MatrixExperiment::splitMergeTest(vector<Matrix<double> > inputMats,Op op) {
    if (inputMats.size()==0)
        throw MatrixExperimentException("Split merge test error: input vector is empty");

    Matrix<double> res = splitMerge(inputMats, op, 0, inputMats.size() - 1);

    return res.sum<iFloat>();
}

//---------------------------------------------     EXPERIMENTING
// for an experiment, we random shuffle the input nTest times.
// For each shuffle, we calculate the result of each algorithm

iFloat MatrixExperiment::groundTruth(vector<Matrix<double> > inputMats, Op op)  {
    if (inputMats.size()==0)
        throw MatrixExperimentException("GroundTruth: input vector size 0");

    vector<Matrix<iFloat> > hfInput = double2iFloat(inputMats);
    Matrix<iFloat> res = hfInput[0];
    for (unsigned i=1; i<hfInput.size(); i++) res = matOperate(res, hfInput[i], op);
    return res.sum<iFloat>();
}

vector<Result> MatrixExperiment::experiment(vector<Matrix<double> > inputMats,Op op, unsigned nTest, vector<Algo> testAlgos) {
    vector<Result> res;
    res.clear();

    bool linear = 0, splitMerge = 0;
    for (unsigned i=0; i<testAlgos.size(); i++) {
        if (testAlgos[i]==Algo::LINEAR) linear = true;
        if (testAlgos[i]==Algo::SPLIT_MERGE) splitMerge = true;
    }

    for (unsigned t=1; t<=nTest; t++) {
        if (linear) res.push_back(Result(linearTest(inputMats, op), Algo::LINEAR));
        if (splitMerge) res.push_back(Result(splitMergeTest(inputMats, op), Algo::SPLIT_MERGE));

        std::random_shuffle(inputMats.begin(), inputMats.end());
    }

    return res;
}

