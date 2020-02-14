#ifndef VECTOR_H
#define VECTOR_H

#include <ifloat.h>
#include <QDebug>

struct VectorException {
  std::string m_msg;
  VectorException(const char*const msg) : m_msg(msg) {}
  VectorException(const VectorException& me) : m_msg(me.m_msg) {}
};

template <class dtype>
class Vector
{
    unsigned len;
    dtype *values;

    void cleanup() {
        delete[] values;
    }

    void allocate() {
        if (len==0)
            throw VectorException("Can't allocate vector with size 0");
        values = new dtype[len];
    }

    void copy(const Vector& m) {
        len = m.len;
        allocate();
        for (unsigned i=0; i<len; i++) values[i] = m.values[i];
    }

protected:
    Vector() { }

public:
//-------------------       CANONICAL FORM
    Vector(unsigned length, const dtype init=0) {
        len = length;
        allocate();
        for (unsigned i=0; i<len; i++) values[i] = init;
    }

    Vector(const Vector& vec) {
        copy(vec);
    }

    ~Vector() {
        cleanup();
    }

    Vector& operator = (const Vector& vec) {
        if (this != &vec) {
            cleanup();
            copy(vec);
        }
        return *this;
    }

    template<class dtypeOther>
    Vector<dtype>& operator = (const Vector<dtypeOther>& vec) {
        if ((void*)this == (void*)&vec) // if self-assignment then return itself
            return *this;

        cleanup();
        len = vec.getLen();
        allocate();
        for (unsigned i=0; i<len; i++) values[i] = numeric_cast<dtype>(vec[i]);

        return *this;
    }

    template<class dtypeOther>
    operator Vector<dtypeOther>() const {
        Vector<dtypeOther> res(len);
        for (unsigned i=0; i<len; i++) res[i] = numeric_cast<dtypeOther>(values[i]);
        return res;
    }

    //--------------------- UTILITY ACCESS OPERATOR
    dtype& operator [] (unsigned i) {
        if (i<0 || i>=len)
            throw VectorException("Operator [] out of range access");
        return values[i];
    }

    dtype operator [] (unsigned i) const {
        if (i<0 || i>=len)
            throw VectorException("Operator [] const out of range access");
        return values[i];
    }

    //--------------------- CALCULATION OPERATOR
    Vector operator + (const Vector& vec) const {
        if (len != vec.len)
            throw VectorException("Operator +: vector length must match");
        Vector res(len);
        for (unsigned i=0; i<len; i++) res[i] = values[i] + vec[i];
        return res;
    }

    Vector operator - (const Vector& vec) const {
        if (len != vec.len)
            throw VectorException("Operator -: vector length must match");
        Vector res(len);
        for (unsigned i=0; i<len; i++) res[i] = values[i] - vec[i];
        return res;
    }

    Vector operator * (const Vector& vec) const {
        if (len != vec.len)
            throw VectorException("Operator *: vector length must match");
        Vector res(len);
        for (unsigned i=0; i<len; i++) res[i] = values[i] * vec[i];
        return res;
    }

    Vector operator / (const Vector& vec) const {
        if (len != vec.len  )
            throw VectorException("Operator /: vector length must match");
        Vector res(len);
        for (unsigned i=0; i<len; i++) res[i] = values[i] / vec[i];
        return res;
    }

    dtype dot(const Vector& vec) const {
        if (len != vec.len())
            throw VectorException("Operator dot: vector length must match");
        dtype res = 0;
        for (unsigned i=0; i<len; i++) res = res + values[i]*vec[i];
        return res;
    }

    //--------------------------    SCALAR CALCULATION OPERATOR
    Vector operator + (const iFloat v) const {
        Vector res(len);
        for (unsigned i=0;i<len;i++) res[i] = values[i] + v;
        return res;
    }

    Vector operator - (const iFloat v) const {
        Vector res(len);
        for (unsigned i=0;i<len;i++) res[i] = values[i] - v;
        return res;
    }

    Vector operator * (const iFloat v) const {
        Vector res(len);
        for (unsigned i=0;i<len;i++) res[i] = values[i] * v;
        return res;
    }

    Vector operator / (const iFloat v) const {
        Vector res(len);
        for (unsigned i=0;i<len;i++) res[i] = values[i] / v;
        return res;
    }

    Vector operator - () const {
        Vector res(len);
        for (unsigned i=0;i<len;i++) res[i] = -values[i];
        return res;
    }

    //-----------------------   GETTER/SETTER, PRINT SCREEN
    unsigned getLen() const {
        return len;
    }

    void print() const {
        for (unsigned i=0; i<len; i++) qDebug() << values[i] << " ";
    }
};


//-------------------------------   SCALAR OPERATOR a*b and b*a
template <class dtype, class dtype2>
Vector<dtype> operator + (const dtype2& v, const Vector<dtype>& source) {
    return source + v;
}

template <class dtype, class dtype2>
Vector<dtype> operator - (const dtype2& v, const Vector<dtype>& source) {
    return (-source) + v;
}

template <class dtype, class dtype2>
Vector<dtype> operator * (const dtype2& v, const Vector<dtype>& source) {
    return source * v;
}


//------------------------------    GENERAL OPERATOR CALCULATION FUNCTION
enum VecOp{ADD, SUB, MUL, DIV, DOT};

//template <class dtype1, class dtype2>
inline Vector<iFloat> vecOperate(Vector<iFloat> vec1, Vector<iFloat> vec2, VecOp op) {
    if (op==ADD) return vec1 + vec2;
    if (op==SUB) return vec1 - vec2;
    if (op==MUL) return vec1 * vec2;
    if (op==DIV) return vec1 / vec2;

    if (op==DOT) {
        Vector<iFloat> res(vec1.getLen(), 0);
        res[0] = vec1.dot(vec2);
        return res;
    }

    throw VectorException("vecOperate: Unknown vecOp");
}









#endif // VECTOR_H
