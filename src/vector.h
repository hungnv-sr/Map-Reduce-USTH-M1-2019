#ifndef VECTOR_H
#define VECTOR_H

#include <ifloat.h>
#include <matrix.h>
#include <QDebug>

struct VectorException {
  std::string m_msg;
  VectorException(const char*const msg) : m_msg(msg) {}
  VectorException(const VectorException& me) : m_msg(me.m_msg) {}
};

template <class dtype>
class Vector : public Matrix<dtype> {
private:
    unsigned len;

    Vector() {}

public:
    Vector(int length, dtype init = 0) : Matrix<dtype>(1, length, init){
        len = length;
    }


};







#endif // VECTOR_H
