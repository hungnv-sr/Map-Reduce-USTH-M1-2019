#ifndef IFLOAT_H
#define IFLOAT_H

#include <QDebug>
#include <boost/multiprecision/cpp_dec_float.hpp>
#include <boost/multiprecision/cpp_int.hpp>
using boost::multiprecision::number;
using boost::multiprecision::cpp_dec_float;
using boost::multiprecision::cpp_dec_float_50;
using boost::multiprecision::cpp_dec_float_100;
using boost::multiprecision::cpp_int;
using boost::numeric_cast;

typedef cpp_dec_float_100 float100;

struct iFloatException
{
    std::string m_msg;
    iFloatException( const char*const msg ) : m_msg(msg) {}
    iFloatException( const iFloatException& ve ) : m_msg(ve.m_msg) {}
};


//nhttps://www.boost.org/doc/libs/1_65_0/libs/multiprecision/doc/html/boost_multiprecision/tut/input_output.html
//https://www.boost.org/doc/libs/1_66_0/libs/math/doc/html/math_toolkit/high_precision/use_multiprecision.html
//https://www.boost.org/doc/libs/1_34_1/libs/numeric/conversion/doc/numeric_cast.html

class iFloat
{
private:
    float100 *value;

    void cleanup() {
        if (value==nullptr)
            throw iFloatException("NullPointerException: Object is destructed wrongly");
        delete value;
    }

    void copy(const iFloat& v) {
        value = new float100;
        *value = *(v.value);
    }

public:
    iFloat() {
        value = new float100;
        *value = 0;
    };

    iFloat(double x) {
        value = new float100;
        *value = x;
    }

    iFloat(const iFloat& v) {
        copy(v);
    }

    ~iFloat() {
        cleanup();
    }

    iFloat& operator = (const iFloat& v) {
        if (this!=&v) {
            cleanup();
            copy(v);
        }
        return *this;
    }

    iFloat& operator = (double x) {
        *value = x;
        return *this;
    }

    //--------------------------------- CAST OPERATORS
    operator int() const {return numeric_cast<int>(*value);}

    operator long long() const {return numeric_cast<long long>(*value);}

    operator float() const {return numeric_cast<float>(*value);}

    operator double() const {return numeric_cast<double>(*value);}


    //-------------------------------- CALCULATION OPERATORS
    iFloat operator + (const iFloat& v) {
        iFloat res;
        (*res.value) = (*value) + (*v.value);
        return res;
    }

    iFloat operator - (const iFloat& v) {
        iFloat res;
        (*res.value) = (*value) - (*v.value);
        return res;
    }

    iFloat operator * (const iFloat& v) {
        iFloat res;
        (*res.value) = (*value) * (*v.value);
        return res;
    }

    iFloat operator / (const iFloat& v) {
        iFloat res;
        (*res.value) = (*value) / (*v.value);
        return res;
    }
};

#endif // IFLOAT_H
