#ifndef DISTRIBUTION_H
#define DISTRIBUTION_H
#include <QDebug>
#include "utils.h"

struct DistributionException
{
    std::string m_msg;
    DistributionException( const char*const msg ) : m_msg(msg) {}
    DistributionException( const DistributionException& ve ) : m_msg(ve.m_msg) {}
};

class Distribution
{
protected:
    long long binNumber;
    double lowerBound, upperBound;
    double* pdf;
    double* cdf;

    Distribution(long long newBinNumber, double newLowerBound, double newUpperBound) {
        binNumber = newBinNumber;
        lowerBound = newLowerBound;
        upperBound = newUpperBound;

        try {
            pdf = new double[binNumber];
            for (int i=0;i<binNumber;i++) {pdf[i] = 0; cdf[i] = 0;}
        }
        catch (std::exception const &ex) {
            qDebug() << ex.what() << "\n";
        }
    }

    void cleanup() {
        delete[] pdf;
    }

    void copy(const Distribution& b) {
        binNumber = b.binNumber;
        lowerBound = b.lowerBound;
        upperBound = b.upperBound;
        for (unsigned i=0;i<binNumber;i++) pdf[i] = b.pdf[i];
    }

public:

    Distribution(const Distribution& b) {
        copy(b);
    }

    ~Distribution() {
        cleanup();
    }

    Distribution& operator=(const Distribution& b) {
        if (this != &b) {
            cleanup();
            copy(b);
        }
        return *this;
    }

    bool operator==(const Distribution& b) {
        if (binNumber!=b.binNumber || lowerBound!=b.lowerBound || upperBound!=b.upperBound)
            return false;
        for (unsigned i=0; i<binNumber; i++) if (!utils::floatEqual(pdf[i], b.pdf[i], 0.00000001)) return false;
        return true;
    }

    /*********************************************************/
    double& operator[](int i) {
        return pdf[i];
    }

    double operator[](int i) const {
        return pdf[i];
    }

    Distribution operator + (const Distribution& b) {
        if (binNumber != b.binNumber) {
            qDebug() << "Operator + : Distribution must have same histogram size";
            throw DistributionException("Operator + error: different group sizes");
        }
        Distribution res(binNumber, lowerBound, upperBound);
        for (int i=0;i<binNumber;i++) res[i] = pdf[i] + b[i];
        return res;
    }

    Distribution operator - (const Distribution& b) {
        if (binNumber != b.binNumber) {
            qDebug() << "Operator - : Distribution must have same histogram size";
            throw DistributionException("Operator - error: different group sizes");
        }
        Distribution res(binNumber, lowerBound, upperBound);
        for (int i=0;i<binNumber;i++) res[i] = pdf[i] - b[i];
        return res;
    }

    Distribution operator * (const Distribution& b) {
        if (binNumber != b.binNumber) {
            qDebug() << "Operator * : Distribution must have same histogram size";
            throw DistributionException("Operator * error: different group sizes");
        }
        Distribution res(binNumber, lowerBound, upperBound);
        for (int i=0;i<binNumber;i++) res[i] = pdf[i] * b[i];
        return res;
    }

    Distribution operator * (const int& k) {
        Distribution res(binNumber, lowerBound, upperBound);
        for (int i=0;i<binNumber;i++) res[i] = k*pdf[i];
        return res;
    }
};

#endif // DISTRIBUTION_H
