#include "utils.h"

utils::utils()
{

}

bool utils::floatEqual(double a, double b, double error) {
    return fabs(a-b) <= error;
}

double utils::sqr(double x) {
    return x*x;
}

iFloat utils::isqr(iFloat x) {
    return x*x;
}

iFloat utils::isqrt(const iFloat &x) {
    return iFloat(boost::multiprecision::sqrt(x.getValue()));
}

iFloat utils::iexp(const iFloat &x) {
    return iFloat(boost::multiprecision::exp(x.getValue()));
}


double utils::powerf(double x, int n) {
    if (n==0) return 1;
    double midpow = powerf(x, n/2);
    if (n%2==0) return midpow*midpow;
    else return midpow*midpow*x;
}

iFloat utils::gaussPdf(iFloat mean, iFloat variance, iFloat x) {
    static iFloat sqrt2pi = isqrt(2*pi);
    iFloat stddev = isqrt(variance);
    return 1/(stddev * sqrt2pi) * iexp(-0.5*isqr((x-mean)/stddev));
}

iFloat utils::expoPdf(iFloat lambda, iFloat x) {
    if (x < 0) return 0;
    return lambda * iexp(-lambda*x);
}

double utils::rand01() {
    static std::default_random_engine generator;
    static std::uniform_real_distribution<double> distribution(0.0,1.0);

    return distribution(generator);
}

bool utils::saveArray(QString filename, const vector<double> &data, unsigned precision) {
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
        fo.close();
        return 0;
    }

    return 1;
}

bool utils::saveMatrix(QString filename, const vector<Matrix<double> > &data, unsigned int precision) {
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


void utils::outputFile(QString filename, vector<Result> results) {
    int n;
    vector<QString> algoNames;
    vector<Algo> algoTypes;
    std::map<Algo, bool> mp; // check if an Algo is used

    mp.clear();
    algoTypes.clear();
    algoNames.clear();

    //----------------  GET LIST OF ALGORITHMS USED
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

    //-----------------------   OUTPUT TO FILE
    std::ofstream fo(filename.toStdString().c_str());
    fo << std::setprecision(std::numeric_limits<float50>::digits10); //


    fo << algoTypes.size() << "\n";
    fo << results[0].value << " " << results[1].value << "\n";

    for (unsigned t=0; t<algoTypes.size(); t++) fo << algoNames[t].toStdString() << " ";
    fo << "\n";

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
