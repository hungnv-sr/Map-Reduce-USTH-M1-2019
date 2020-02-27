#ifndef DISTRIBUTION_H
#define DISTRIBUTION_H
#include <QDebug>
#include "utils.h"
#include <ifloat.h>

// TODO: this is not finished so please don't read.
// I skipped this because I have to do the other part first for the program to run
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
    iFloat* cdf;

    void cleanup() {
        delete[] pdf;
        delete[] cdf;
    }

    void copy(const Distribution& b) {
        binNumber = b.binNumber;
        lowerBound = b.lowerBound;
        upperBound = b.upperBound;
        pdf = new double[binNumber];
        cdf = new iFloat[binNumber];
        for (unsigned i=0;i<binNumber;i++) {pdf[i] = b.pdf[i]; cdf[i] = b.cdf[i];}
    }

    // solve cases where pdf[i] < 0. Allow the usage of operator *, -, /
    void normalize() {
        iFloat sum = 0;
        for (int i=0; i<binNumber; i++) {
            if (pdf[i] < 0) pdf[i] = 0;
            sum = sum + pdf[i];
        }

        for (int i=0; i<binNumber; i++) {
            pdf[i] = double(iFloat(pdf[i]) / sum);
            if (i==0) cdf[i] = pdf[i];
            else cdf[i] = cdf[i-1] + pdf[i];
        }
    }

public:
    Distribution(long long newBinNumber, double newLowerBound, double newUpperBound) {
        binNumber = newBinNumber;
        lowerBound = newLowerBound;
        upperBound = newUpperBound;

        if (binNumber==0) binNumber = 1; // place-holder distribution variable
        try {
            pdf = new double[binNumber];
            cdf = new iFloat[binNumber];
            for (int i=0;i<binNumber;i++) {pdf[i] = 0; cdf[i] = 0;}
        }
        catch (std::exception const &ex) {
            qDebug() << ex.what() << "\n";
        }
    }

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

    Distribution operator + (const Distribution& b) const  {
        if (binNumber != b.binNumber) {
            qDebug() << "Operator + : Distribution must have same histogram size";
            throw DistributionException("Operator + error: different group sizes");
        }
        Distribution res(binNumber, lowerBound, upperBound);
        for (int i=0;i<binNumber;i++) res[i] = pdf[i] + b[i];
        res.normalize();
        return res;
    }

    Distribution operator - (const Distribution& b) const {
        if (binNumber != b.binNumber) {
            qDebug() << "Operator - : Distribution must have same histogram size";
            throw DistributionException("Operator - error: different group sizes");
        }
        Distribution res(binNumber, lowerBound, upperBound);
        for (int i=0;i<binNumber;i++) res[i] = pdf[i] - b[i];
        res.normalize();
        return res;
    }

    Distribution operator * (const Distribution& b) const {
        if (binNumber != b.binNumber) {
            qDebug() << "Operator * : Distribution must have same histogram size";
            throw DistributionException("Operator * error: different group sizes");
        }
        Distribution res(binNumber, lowerBound, upperBound);
        for (int i=0;i<binNumber;i++) res[i] = pdf[i] * b[i];
        res.normalize();
        return res;
    }

    Distribution operator / (const Distribution& b) const {
        if (binNumber != b.binNumber) {
            qDebug() << "Operator / : Distribution must have same histogram size";
            throw DistributionException("Operator * error: different group sizes");
        }
        Distribution res(binNumber, lowerBound, upperBound);
        for (int i=0;i<binNumber;i++) res[i] = pdf[i] / b[i];
        res.normalize();
        return res;
    }

    /*****************************      GETTER/SETTER/INVERSE SAMPLING*/
    long long getBinNumber() const {
        return binNumber;
    }

    double getLowerBound() const {
        return lowerBound;
    }

    double getUpperBound() const {
        return upperBound;
    }

    double getBinSize() const {
        return (upperBound - lowerBound) / binNumber;
    }

    long long inverseSampling(iFloat cumulative) {
        if (cumulative < iFloat(0) || cumulative > iFloat(1))
            throw DistributionException("Inverse sampling error: invalid cumulative value");
        long long l = 0, r = binNumber-1, res = -1;
        while (l<=r) {
            long long mid = (l+r) / 2;
            if (cdf[mid] >= cumulative) {
                res = mid;
                r = mid-1;
            }
            else l = mid+1;
        }

        if (res==-1)
            throw DistributionException("Something wrong with inverse sampling binary search");

        return res;
    }

    /*********************************************************/
    bool valid() {
        return utils::floatEqual(lowerBound, upperBound, 0.000001);
    }
};

#endif // DISTRIBUTION_H
