#ifndef NUMERIC_H
#define NUMERIC_H

#include <utilityenum.h>

class Numerical
{
protected:
    Numerical() {} ;
};

template <class dtype>
inline dtype numOperate(const dtype &a, const dtype &b, Op op) {
    if (op==ADD) return a + b;
    if (op==SUB) return a - b;
    if (op==MUL) return a * b;
    if (op==DIV) return a / b;

    throw ("NumOperate: Unknown Op");
}

#endif // NUMERIC_H
