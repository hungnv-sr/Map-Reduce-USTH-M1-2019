#ifndef DISTRIBUTION_H
#define DISTRIBUTION_H
#include <QDebug>
#include "utils.h"
#include <algorithm>
#include <ifloat.h>

// TODO: this is not finished so please don't read.
// I skipped this because I have to do the other part first for the program to run
struct DistributionException : public std::exception {
private:
    QString msg;

public:
    DistributionException(QString mess) {
        msg = mess;
    }
    const char* what() const throw() {
        return msg.toStdString().c_str();
    }
};

struct SamplingException : public std::exception {
private:
    QString msg;

public:
    SamplingException(QString mess) {
        msg = mess;
    }
    const char* what() const throw() {
        return msg.toStdString().c_str();
    }
};

class Distribution
{
protected:
    long long binNumber;   
    iFloat lowerBound, upperBound;
    iFloat* pdf;
    iFloat* cdf;

    void cleanup() {
        delete[] pdf;
        delete[] cdf;
    }

    void copy(const Distribution& b) {
        binNumber = b.binNumber;
        lowerBound = b.lowerBound;
        upperBound = b.upperBound;
        pdf = new iFloat[binNumber];
        cdf = new iFloat[binNumber];
        for (unsigned i=0;i<binNumber;i++) {pdf[i] = b.pdf[i]; cdf[i] = b.cdf[i];}
    }

    // solve cases where pdf[i] < 0. Allow the usage of operator *, -, /    

public:
    Distribution() {
        binNumber = 0;
        lowerBound = 0;
        upperBound = 0;
    }

    Distribution(long long newBinNumber, iFloat newLowerBound, iFloat newUpperBound) {
        binNumber = newBinNumber;
        lowerBound = newLowerBound;
        upperBound = newUpperBound;

        if (binNumber==0) binNumber = 1; // place-holder distribution variable
        else {
            if (binNumber < 0)
                throw DistributionException("Constructor: bin number < 0");

        }

        try {
            pdf = new iFloat[binNumber];
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
        for (unsigned i=0; i<binNumber; i++) if (pdf[i] != b.pdf[i]) return false;
        return true;
    }

    /*********************************************************/
    iFloat& operator[](int i) {
        return pdf[i];
    }

    iFloat operator[](int i) const {
        return pdf[i];
    }

    Distribution operator + (const Distribution& b) const  {
        if (binNumber != b.binNumber) {
            qDebug() << "Operator + : Distribution must have same histogram size";
            throw DistributionException("Operator + error: different group sizes");
        }
        Distribution res(binNumber, lowerBound, upperBound);
        for (int i=0;i<binNumber;i++) res[i] = pdf[i] + b[i];

        return res;
    }

    Distribution operator - (const Distribution& b) const {
        if (binNumber != b.binNumber) {
            qDebug() << "Operator - : Distribution must have same histogram size";
            throw DistributionException("Operator - error: different group sizes");
        }
        Distribution res(binNumber, lowerBound, upperBound);
        for (int i=0;i<binNumber;i++) res[i] = pdf[i] - b[i];

        return res;
    }

    Distribution operator * (const Distribution& b) const {
        if (binNumber != b.binNumber) {
            qDebug() << "Operator * : Distribution must have same histogram size";
            throw DistributionException("Operator * error: different group sizes");
        }
        Distribution res(binNumber, lowerBound, upperBound);
        for (int i=0;i<binNumber;i++) res[i] = pdf[i] * b[i];

        return res;
    }

    Distribution operator / (const Distribution& b) const {
        if (binNumber != b.binNumber) {
            qDebug() << "Operator / : Distribution must have same histogram size";
            throw DistributionException("Operator * error: different group sizes");
        }
        Distribution res(binNumber, lowerBound, upperBound);
        for (int i=0;i<binNumber;i++) res[i] = pdf[i] / b[i];

        return res;
    }

    /*****************************      GETTER/SETTER/INVERSE SAMPLING*/
    long long getBinNumber() const {
        return binNumber;
    }

    iFloat getLowerBound() const {
        return lowerBound;
    }

    iFloat getUpperBound() const {
        return upperBound;
    }

    iFloat getBinSize() const {
        return (upperBound - lowerBound) / binNumber;
    }

    iFloat getCdf(long long i) {
        return cdf[i];
    }

    long long inverseSampling(iFloat cumulative) {
        if (cumulative < iFloat(0) || cumulative > iFloat(1))
            throw DistributionException("Inverse sampling error: invalid cumulative value");
        long long l = 0, r = binNumber-1, res = -1;
        while (l<=r) {
            long long mid = (l+r) / 2;
            if (cdf[mid] > cumulative) {
                res = mid;
                r = mid-1;
            }
            else l = mid+1;
        }

        //if (res==-1)
        //    throw SamplingException("Inverse sampling failed because sum(cdf) < cumulative <= 1");
        if (res==-1) {
            res = binNumber - 1;
            qDebug() << "CRITICAL ERROR: INVERSE SAMPLING FAIL";
        }

        return res;
    }

    void normalize() {
        iFloat sum = 0;
        for (long long i=0; i<binNumber; i++) {
            if (pdf[i] < 0) pdf[i] = 0;
            sum = sum + pdf[i];
        }

        for (long long i=0; i<binNumber; i++) {
            pdf[i] = pdf[i] / sum;
            if (i==0) cdf[i] = pdf[i];
            else cdf[i] = cdf[i-1] + pdf[i];
        }
    }

    /*********************************************************/
    bool valid() {
        return binNumber > 1 && upperBound > lowerBound;
    }
};

#endif // DISTRIBUTION_H
