#ifndef BASEEXPERIMENT_H
#define BASEEXPERIMENT_H

#include <ifloat.h>
#include <QString>
#include <vector>
#include <fstream>
#include <utils.h>
#include <map>
using std::vector;

enum Algo {LINEAR, SPLIT_MERGE, SORT, SORT_APPEND, GROUND_TRUTH};

struct Result {
    iFloat value;
    Algo algoUsed;
    Result(iFloat v, Algo algo) {value = v; algoUsed = algo;}
};

class BaseExperiment
{
protected:
    BaseExperiment() {};

public:
    void outputFile(QString filename, vector<Result> results) {
        int n;
        vector<QString> algoNames;
        vector<Algo> algoTypes;
        std::map<Algo, bool> mp;

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


        fo << algoTypes.size() << "\n";
        qDebug() << "Reached after algotypes.size() \n";

        fo << results[0].value << " " << results[1].value << "\n";
        qDebug() << "Reached after results[0] and 1 \n";

        qDebug() << "algoTypes.size() = " << algoTypes.size() << " - " << "algoNames.size() = " << algoNames.size() << "\n";
        for (unsigned t=0; t<algoTypes.size(); t++) fo << algoNames[t].toStdString() << " ";
        fo << "\n";
        qDebug() << "Reached after algosNames print\n";

        qDebug() << "output file before loop\n";
        for (unsigned t=0; t<algoTypes.size(); t++) {
            iFloat mean = 0;
            int nSample = 0;

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

            fo << mean << " " << variance << " " << utils::isqrt(variance) << " ";
            for (int i=0; i<n; i++) if (results[i].algoUsed==algoTypes[t]) fo << results[i].value << " ";
            fo << "\n";
        }
        fo.close();
    }

};

#endif // BASEEXPERIMENT_H
