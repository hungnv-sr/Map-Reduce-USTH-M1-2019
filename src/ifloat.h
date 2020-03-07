#pragma once
#ifndef IFLOAT_H
#define IFLOAT_H

#include <QDebug>
#include <boost/multiprecision/cpp_dec_float.hpp>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/number.hpp>
using boost::multiprecision::number;
using boost::multiprecision::cpp_dec_float;
using boost::multiprecision::cpp_dec_float_50;
using boost::numeric_cast;
using std::cout;

typedef number<cpp_dec_float<40> > float40;

struct iFloatException : public std::exception {
private:
    QString msg;

public:
    iFloatException(QString mess) {
        msg = mess;
    }
    const char* what() const throw() {
        return msg.toStdString().c_str();
    }
};

//----------------      TUTORIAL ON BOOST C++ FLOAT
// Download: https://stackoverflow.com/questions/18562603/how-to-configure-qt-creator-to-use-boost-in-windows
// https://www.boost.org/doc/libs/1_65_0/libs/multiprecision/doc/html/boost_multiprecision/tut/input_output.html
// https://www.boost.org/doc/libs/1_66_0/libs/math/doc/html/math_toolkit/high_precision/use_multiprecision.html
// https://www.boost.org/doc/libs/1_34_1/libs/numeric/conversion/doc/numeric_cast.html
//----------------------------------------------------------------------------------------------------------------------------------


// iFloat is the wrapper class for Boost C++ class cpp_dec_float_40 (float40), which is float that has 40 decimal places precision
// We need a wrapper class because float40 can use a lot of memory. In a function, it will cause stack overflow very quickly.
// Using a wrapper class, the memory is on the heap instead, so there's no problem.

// Usage:
// Use this class just like the normal numeric class: float. Operator =, +, -, *, /, and conversion to other numeric types are supported.

class iFloat
{
private:
    float40 *value;

    void cleanup() {
        if (value==nullptr)
            throw iFloatException("NullPointerException: Somehow object is destructed wrongly");
        delete value;
    }

    void copy(const iFloat& v) {
        value = new float40;
        *value = *(v.value);
    }

public:
    //--------------------  CANONICAL FORM FUNCTIONS
    iFloat() {
        value = new float40;
        *value = 0;
    };

    iFloat(float40 x) {
        value = new float40;
        *value = x;
    }

    iFloat(double x) {
        value = new float40;
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
            // usually we need to cleanup(), but Boost C++ class float40 use in-place memory, so there's no leak
            *value = *(v.value);
        }
        return *this;
    }


    //--------------------------------- CAST OPERATORS
    // Converting to double cause loss of information. So make it explicit
    explicit operator double() const {return (*value).convert_to<double>();}


    //-------------------------------- CALCULATION OPERATORS
    iFloat operator + (const iFloat& v) const {
        iFloat res;
        (*res.value) = (*value) + (*v.value);
        return res;
    }

    iFloat operator - (const iFloat& v) const {
        iFloat res;
        (*res.value) = (*value) - (*v.value);
        return res;
    }

    iFloat operator * (const iFloat& v) const {
        iFloat res;
        (*res.value) = (*value) * (*v.value);
        return res;
    }

    iFloat operator / (const iFloat& v) const {
        iFloat res;
        (*res.value) = (*value) / (*v.value);
        return res;
    }

    iFloat operator - () const {
        iFloat res;
        (*res.value) = -(*value);
        return res;
    }

    bool operator > (const iFloat& v) const {
        return (*value) > (*v.value);
    }

    bool operator < (const iFloat& v) const {
        return (*value) < (*v.value);
    }

    bool operator == (const iFloat &v) const {
        return (*value) == (*v.value);
    }

    bool operator != (const iFloat &v) const {
        return (*value) != (*v.value);
    }

    bool operator >= (const iFloat& v) const {
        return (*value) >= (*v.value);
    }

    bool operator <= (const iFloat& v) const {
        return (*value) <= (*v.value);
    }

    //-------------------------------- SCALAR CALCULATION OPERATORS
    float40 getValue() const {
        return *value;
    }

    QString toString() {
        return QString::fromStdString(value->str());
    }

    friend std::ostream & operator << (std::ostream &out, const iFloat &c);

};


//-------------------------------- SCALAR CALCULATION OPERATORS, opposite order
template<class dtype2>
iFloat operator + (const dtype2& v, const iFloat& num) {
    return num + iFloat(v);
}

template<class dtype2>
iFloat operator - (const dtype2& v, const iFloat& num) {
    return iFloat(v) - num;
}

template<class dtype2>
iFloat operator * (const dtype2& v, const iFloat& num) {
    return num * iFloat(v);
}

template<class dtype2>
iFloat operator / (const dtype2& v, const iFloat& num) {
    return iFloat(v) / num;
}

//------------------------------    OUTPUT OPERATOR
inline std::ostream & operator << (std::ostream &out, const iFloat &c)
{
    out << ((*c.value).str());
    return out;
}



#endif // IFLOAT_H
