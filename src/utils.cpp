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

double utils::powerf(double x, int n) {
    if (n==0) return 1;
    double midpow = powerf(x, n/2);
    if (n%2==0) return midpow*midpow;
    else return midpow*midpow*x;
}

double utils::gaussPdf(double mean, double variance, double x) {
    double stddev = sqrt(variance);
    return 1/(stddev * sqrt(2*pi)) * exp(-0.5*sqr((x-mean)/stddev));
}

double utils::expoPdf(double lambda, double x) {
    return lambda * exp(-lambda*x);
}

double utils::rand01() {
    static std::default_random_engine generator;
    static std::uniform_real_distribution<double> distribution(0.0,1.0);

    return distribution(generator);
}
