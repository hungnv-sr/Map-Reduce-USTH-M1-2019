#ifndef UTILS_H
#define UTILS_H

#include <iomanip>      // std::setprecision
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <random>
#include <QString>
#include <vector>
#include <QDebug>
#include <ifloat.h>
#include <matrix.h>
using std::vector;
const double pi = M_PI;

class utils
{
private:
    utils() {}
public:

    // we don't allow inputs that are too large
    static double str2double(QString numberStr, bool &valid) {
        if (numberStr.length() > 15) {
            valid = 0;
            return 0;
        }
        return numberStr.toDouble(&valid);
    }

    static bool floatEqual(double a, double b, double error) {
        return fabs(a-b) <= error;
    }

    static double sqr(double x) {
        return x*x;
    }

    static iFloat isqr(iFloat x) {
        return x*x;
    }

    static iFloat isqrt(const iFloat &x) {
        return iFloat(boost::multiprecision::sqrt(x.getValue()));
    }

    static iFloat iexp(const iFloat &x) {
        return iFloat(boost::multiprecision::exp(x.getValue()));
    }


    static double powerf(double x, int n) {
        if (n==0) return 1;
        double midpow = powerf(x, n/2);
        if (n%2==0) return midpow*midpow;
        else return midpow*midpow*x;
    }

    static iFloat gaussPdf(iFloat mean, iFloat variance, iFloat x) {
        static iFloat sqrt2pi = isqrt(2*pi);
        iFloat stddev = isqrt(variance);
        return 1/(stddev * sqrt2pi) * iexp(-0.5*isqr((x-mean)/stddev));
    }


    static iFloat expoPdf(iFloat lambda, iFloat x) {
        if (x < 0) return 0;
        return lambda * iexp(-lambda*x);
    }

    static bool isnan(iFloat x) {
        return boost::math::isnan(x.getValue());
    }

    static bool isinf(iFloat x) {
        return boost::math::isinf(x.getValue());
    }

    static double rand01() {
        static std::default_random_engine generator;
        static std::uniform_real_distribution<double> distribution(0.0,1.0);

        return distribution(generator);
    }


    //---------------
    static bool saveArray(QString filename, const vector<double> &data, unsigned precision) {
        if (data.size()==0) return 0;
        std::ofstream fo;
        try {
            std::setprecision(precision);

            fo = std::ofstream(filename.toStdString().c_str());
            fo << std::setprecision(precision);

            qDebug() << "filename = " << filename << "\n";

            fo << data.size() << "\n";
            for (unsigned i=0; i<data.size(); i++) fo << std::fixed << data[i] << " ";
            fo << "\n";
            fo.close();
        } catch (std::exception ex) {
            qDebug() << "File crash " << ex.what() << "\n";
            fo.close();
            return 0;
        }

        return 1;
    }

    static bool saveMatrix(QString filename, const vector<Matrix<double> > &data, unsigned int precision) {
        if (data.size()==0) return 0;
        std::ofstream fo;
        try {
            std::setprecision(precision);

            fo = std::ofstream(filename.toStdString().c_str());
            fo << std::setprecision(precision);

            qDebug() << "filename = " << filename << "\n";

            fo << data.size() << " " << data[0].getHeight() << " " << data[0].getWidth() << "\n";
            for (unsigned i=0; i<data.size(); i++) {
                for (unsigned t=0; t<data[i].getLength(); t++) fo << std::fixed << data[i][t] << " ";
                fo << "\n";
            }
            fo.close();
        } catch (std::exception ex) {
            fo.close();
            return 0;
        }

        return 1;
    }

    template <typename dtype, typename inputType>
    static vector<dtype> convertArray(const vector<inputType> &arr) {
        vector<dtype> res;
        for (long long i=0; i<arr.size(); i++) res.push_back(dtype(arr[i]));
        return res;
    }

    template <typename dtype, typename inputType>
    static vector<Matrix<dtype> > convertMatrices(const vector<Matrix<inputType> > inputs) {
        vector<Matrix<dtype> > res;
        for (long long i=0; i<inputs.size(); i++) res.push_back(Matrix<dtype>(inputs[i]));
        return res;
    }


    //-----
    static void outputFile(QString filename, vector<Result> results) {
        int n;
        vector<QString> algoNames;
        vector<AlgoName> algoTypes;
        std::map<AlgoName, bool> mp;

        mp.clear();
        algoTypes.clear();
        algoNames.clear();

        qDebug() << "Reached before results.size() \n";

        n = results.size();
        for (int i=0; i<n;i++) {
            if (!mp[results[i].algoUsed] && results[i].algoUsed!=GROUND_TRUTH) {
                mp[results[i].algoUsed] = 1;

                algoTypes.push_back(results[i].algoUsed);
                if (results[i].algoUsed==LINEAR) algoNames.push_back("LINEAR");
                else if (results[i].algoUsed==SPLIT_MERGE) algoNames.push_back("SPLIT_MERGE");
                else if (results[i].algoUsed==SORT) algoNames.push_back("SORT_LINEAR");
                else if (results[i].algoUsed==SORT_APPEND) algoNames.push_back("SORT_APPEND");
            }
        }

        std::ofstream fo(filename.toStdString().c_str());
        qDebug() << "Reached after openining file \n";
        fo << std::setprecision(std::numeric_limits<float50>::digits10);
        qDebug() << "Reached after setprecision \n";


        fo << "Number of Algorithm Type" << ", " << algoTypes.size() << "\n";
        qDebug() << "Reached after algotypes.size() \n";
        if (results[0].value == 1){
            fo << "Using shuffle dataset" << "\n";
            fo << "Ground Truth" << ", "<< results[1].value << "\n";
        } else fo << "Using original dataset" << "\n";

        qDebug() << "Reached after results[0] and 1 \n";

        // qDebug() << "algoTypes.size() = " << algoTypes.size() << " - " << "algoNames.size() = " << algoNames.size() << "\n";
        qDebug() << "Reached after algosNames print\n";
        fo << "\n";
        qDebug() << "output file before loop\n";
        for (unsigned t=0; t<algoTypes.size(); t++) {
            iFloat mean = 0;
            int nSample = 0;
            fo << algoNames[t].toStdString() << "\n ";
            for (int i=0;i<n;i++) if (results[i].algoUsed==algoTypes[t]) {
                mean = mean + results[i].value;
                nSample++;
            }
            mean = mean/nSample;

            iFloat variance = 0;
            for (int i=0;i<n;i++) if (results[i].algoUsed==algoTypes[t]) {
                iFloat dX = (results[i].value - mean);
                variance = variance + dX * dX;
            }
            variance = variance / nSample;
            fo << "Mean" << ", " << "Variance" << ", " << "Standard Deviation"<< "\n";
            fo << mean << ", " << variance << ", " << isqrt(variance) << "\n";
            fo << "Result of " << (n-2)/algoTypes.size() << " experiments" << "\n";
            for (int i=0; i<n; i++) if (results[i].algoUsed==algoTypes[t]) fo << results[i].value << ", ";
            fo << "\n" << "\n";
        }
        fo.close();
    }
};

#endif // UTILS_H
