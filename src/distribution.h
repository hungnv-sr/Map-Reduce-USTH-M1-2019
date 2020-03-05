#ifndef DISTRIBUTION_H
#define DISTRIBUTION_H
#include <QDebug>
#include <ifloat.h>
#include <fstream>
#include <utils.h>
#include <vector>
using std::vector;

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

// Sampling Exception is reserved for cases when the probability value
// underflows.
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

// We use inverse transform sampling:
// https://stephens999.github.io/fiveMinuteStats/inverse_transform_sampling.html
class Distribution
{
protected:
    // Note: we use pointer for cdf/pdf because they are very large array.
    long long binNumber;            // number of rectangles to perform numerical integration
    iFloat lowerBound, upperBound;  // Measurement range. For example, we can measure U(-5,5) in the range(-100,100)
    iFloat* pdf;                    // Probability MASS function. Because we converted continuous functions to an array
    iFloat* cdf;                    // Discrete cumulative mass function

    void cleanup() {
        delete[] pdf;
        delete[] cdf;
    }

    // the = operator    must perform cleanup() then copy
    void copy(const Distribution& b) {
        binNumber = b.binNumber;
        lowerBound = b.lowerBound;
        upperBound = b.upperBound;
        pdf = new iFloat[binNumber];
        cdf = new iFloat[binNumber];
        for (unsigned i=0;i<binNumber;i++) {pdf[i] = b.pdf[i]; cdf[i] = b.cdf[i];}
    }

    // binNumber is the number of rectangles, so it must be > 0
    // But we make it > 1 because 1 rectangle doesn't make sense for integral
    Distribution(long long newBinNumber, iFloat newLowerBound, iFloat newUpperBound) {
        binNumber = newBinNumber;
        lowerBound = newLowerBound;
        upperBound = newUpperBound;

        // UPDATE: now Distribution() is place-holder. this constructor is only used by children classes
        if (binNumber==0) binNumber = 1; // Distribution(0,0,0) is place-holder distribution variable.
        else {
            if (binNumber < 0)
                throw DistributionException("Constructor: bin number < 0");
        }

        try {
            pdf = new iFloat[binNumber];
            cdf = new iFloat[binNumber];
            //for (int i=0;i<binNumber;i++) {pdf[i] = 0; cdf[i] = 0;} // sub class will assign value to pdf/cdf
        }
        catch (std::bad_alloc ex) {
            qDebug() << " Distribution constructor bad_alloc " << ex.what() << "\n";
            throw (ex);
        }
    }

public:
    //----------    CONSTRUCTOR, COPY CONSTRUCTOR, DESTRUCTOR, ASSIGNMENT OPERATOR
    //----------    These are needed to make the class canonical

    // place-holder empty constructor. This is needed to make the class compatible with QObject/Qt function
    Distribution() {
        binNumber = 1;
        lowerBound = 0;
        upperBound = 0;
        pdf = new iFloat[1]; // we need to initialize place-holder pdf/cdf
        cdf = new iFloat[1]; // so that destructor does not cause crash
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
    //--------------    MATH OPERATORS
    iFloat& operator[](int i) {
        return pdf[i];
    }

    iFloat operator[](int i) const {
        return pdf[i];
    }

    Distribution operator + (const Distribution& b) const  {
        if (binNumber != b.binNumber) {
            qDebug() << "Operator + : Distribution must have same histogram size";
            throw DistributionException("Operator + error: different bin number sizes");
        }
        Distribution res(binNumber, lowerBound, upperBound);
        for (long long i=0;i<binNumber;i++) res[i] = pdf[i] + b[i];

        return res;
    }

    Distribution operator - (const Distribution& b) const {
        if (binNumber != b.binNumber) {
            qDebug() << "Operator - : Distribution must have same histogram size";
            throw DistributionException("Operator - error: different bin number sizes");
        }
        Distribution res(binNumber, lowerBound, upperBound);
        for (long long i=0;i<binNumber;i++) res[i] = pdf[i] - b[i];

        return res;
    }

    Distribution operator * (const Distribution& b) const {
        if (binNumber != b.binNumber) {
            qDebug() << "Operator * : Distribution must have same histogram size";
            throw DistributionException("Operator * error: different bin number sizes");
        }
        Distribution res(binNumber, lowerBound, upperBound);
        for (long long i=0;i<binNumber;i++) res[i] = pdf[i] * b[i];

        return res;
    }

    Distribution operator / (const Distribution& b) const {
        if (binNumber != b.binNumber) {
            qDebug() << "Operator / : Distribution must have same histogram size";
            throw DistributionException("Operator * error: different bin number sizes");
        }
        Distribution res(binNumber, lowerBound, upperBound);
        for (long long i=0;i<binNumber;i++) res[i] = pdf[i] / b[i];

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

    // find the first value "res" such that
    // cdf[res] > cumulative using binary search
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

        // if we cannot find a valid res, there's a 99.99% chance that
        // it's because sum(pdf) < 1, and res > sum(pdf).
        // This happens because some distribution function require super high precision (normal, exponential, ...)
        // and some values underflow and become 0.
        // We fix this by using iFloat for both PDF and CDF. If the error happens again,
        // we are sure that sum(pdf) is close to 1, so we just set res = binNumber - 1 (the max value).

        //if (res==-1)
        //    throw SamplingException("Inverse sampling failed because sum(cdf) < cumulative <= 1");
        if (res==-1) {
            res = binNumber - 1;
            qDebug() << "CRITICAL ERROR: INVERSE SAMPLING FAIL.";
        }

        return res;
    }

    // sometimes sum(pdf) < 1 due to float underflow.
    // so we normalize it
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
    // This checks if a distribution is usable or not
    // Also it checks for place-holder Distribution().
    bool valid() {
        return binNumber > 1 && upperBound > lowerBound;
    }    
};

#endif // DISTRIBUTION_H
