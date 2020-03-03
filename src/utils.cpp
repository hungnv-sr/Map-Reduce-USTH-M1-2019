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
