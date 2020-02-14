#pragma once
#ifndef MATRIX_H
#define MATRIX_H

#include <ifloat.h>
#include <QDebug>

struct MatrixException {
  std::string m_msg;
  MatrixException(const char*const msg) : m_msg(msg) {}
  MatrixException(const MatrixException& me) : m_msg(me.m_msg) {}
};


//--------------------------------------------------------------------
template <class dtype>
class Matrix
{
private:
    unsigned width, height;
    dtype *values;

    unsigned offset(unsigned row, unsigned col) const {
        return row*width + col;
    }

    void cleanup() {
        delete[] values;
    }

    void allocate() {
        if (width==0 || height==0)
            throw MatrixException("Can't allocate matrix with size 0");
        values = new dtype[width*height];
    }

    void copyArray(const dtype* const v) {
        for (unsigned i=0; i<width*height; i++) values[i] = v[i];
    }

    void copy(const Matrix& m) {
        width = m.width;
        height = m.height;
        allocate();
        copyArray(m.values);
    }

protected:
    Matrix() {}

public:
    //-------------------       CANONICAL FORM
    Matrix(const unsigned newWidth, const unsigned newHeight, const dtype init=0.0) {
        width = newWidth;
        height = newHeight;
        allocate();
        for (unsigned i=0; i<width*height; i++) values[i] = init;
    }

    Matrix(const Matrix& m) {
        copy(m);
    }

    ~Matrix() {
        cleanup();
    }

    Matrix& operator = (const Matrix& m) {
        if (this!=&m) {
            cleanup();
            copy(m);
        }
        return *this;
    }

    // for assignment of different matrix types. Matrix<iFloat> a; Matrix<double> b; a = b;
    template<class dtypeOther>
    Matrix<dtype>& operator = (const Matrix<dtypeOther>& m) {
        if ((void*)this == (void*)&m) // if self-assignment then return itself
            return *this;

        cleanup();
        width = m.getWidth();
        height = m.getHeight();
        allocate();
        for (unsigned i=0; i<width*height; i++) values[i] = numeric_cast<dtype>(m[i]);

        return *this;
    }

    // Only 1 of converting construct or converting operator is enough
    /*
    template<class dtypeOther>
    Matrix(Matrix<dtypeOther> mat) {
        width = mat.getWidth();
        height = mat.getHeight();
        allocate();
        for (unsigned i=0; i<width*height; i++) values[i] = numeric_cast<dtype>(mat[i]);
    }
    */

    template<class dtypeOther>
    operator Matrix<dtypeOther>() const {
        Matrix<dtypeOther> res(width, height, 0);
        for (unsigned i=0; i<width*height; i++) res[i] = numeric_cast<dtypeOther>(values[i]);
        return res;
    }

    //--------------------- UTILITY ACCESS OPERATOR
    dtype& operator [] (unsigned index) {
        if (index < 0 || index >= width*height)
            throw MatrixException("Operator [] out of range access");
        return values[index];
    }

    dtype operator [] (unsigned index) const {
        if (index < 0 || index >= width*height)
            throw MatrixException("Operator [] const out of range access");
        return values[index];
    }

    dtype& operator () (unsigned row, unsigned col) {
        if (row < 0 || col < 0 || row >= width || col>=height)
            throw MatrixException("Operator (i,j) out of range access");
        return values[offset(row,col)];
    }

    dtype operator () (unsigned row, unsigned col) const {
        if (row < 0 || col < 0 || row >= width || col>=height)
            throw MatrixException("Operator (i,j) const out of range access");
        return values[offset(row,col)];
    }

    //--------------------- CALCULATION OPERATOR
    Matrix operator + (const Matrix& m) const {
        if (width!=m.width || height!=m.height)
            throw MatrixException("Operator +: dimension doesn't match");
        Matrix res(width, height, 0);
        for (unsigned i=0;i<width*height;i++) res[i] = values[i] + m[i];
        return res;
    }

    Matrix operator - (const Matrix& m) const {
        if (width!=m.width || height!=m.height)
            throw MatrixException("Operator -: dimension doesn't match");
        Matrix res(width, height, 0);
        for (unsigned i=0;i<width*height;i++) res[i] = values[i] - m[i];
        return res;
    }

    Matrix operator * (const Matrix& m) const {
        if (width!=m.width || height!=m.height)
            throw MatrixException("Operator *: dimension doesn't match");
        Matrix res(width, height, 0);
        for (unsigned i=0;i<width*height;i++) res[i] = values[i] * m[i];
        return res;
    }

    Matrix operator / (const Matrix& m) const {
        if (width!=m.width || height!=m.height)
            throw MatrixException("Operator /: dimension doesn't match");
        Matrix res(width, height, 0);
        for (unsigned i=0;i<width*height;i++) res[i] = values[i] / m[i];
        return res;
    }

    Matrix matmul(const Matrix& mat) const {
        unsigned m = width, n = height, p = mat.height;
        if (height != mat.width)
            throw MatrixException("Matmul: matrix sizes mismatch");
        Matrix res(m, p, 0);
        for (unsigned i=0;i<m;i++)
            for (unsigned j=0;j<n;j++)
                for (unsigned k=0;k<p;k++) res(i,j) = res(i,j) + (*this)(i,k) * mat(k,j);
        return res;
    }

    //--------------------------    SCALAR CALCULATION OPERATOR
    template<class dtype2>
    Matrix operator + (const dtype2& v) const {
        Matrix res(width, height, 0);
        for (unsigned i=0;i<width*height;i++) res[i] = values[i] + v;
        return res;
    }

    template<class dtype2>
    Matrix operator - (const dtype2& v) const {
        Matrix res(width, height, 0);
        for (unsigned i=0;i<width*height;i++) res[i] = values[i] - v;
        return res;
    }

    template<class dtype2>
    Matrix operator * (const dtype2& v) const {
        Matrix res(width, height, 0);
        for (unsigned i=0;i<width*height;i++) res[i] = values[i] * v;
        return res;
    }

    template<class dtype2>
    Matrix operator / (const dtype2& v) const {
        Matrix res(width, height, 0);
        for (unsigned i=0;i<width*height;i++) res[i] = values[i] / v;
        return res;
    }

    Matrix operator - () const {
        Matrix res(width, height, 0);
        for (unsigned i=0;i<width*height;i++) res[i] = -values[i];
        return res;
    }


    //-----------------------   MORE MATH FUNCTIONS
    template <class CalculationType>
    iFloat sum() const {
        CalculationType res = 0;
        for (unsigned i=0; i<width*height;i++) res = res + values[i];
        return res;
    }

    //-----------------------   GETTER/SETTER, PRINT SCREEN
    unsigned getWidth() const {
        return width;
    }

    unsigned getHeight() const {
        return height;
    }

    void print() const {
        for (unsigned i=0; i<width; i++)
        {
            for (unsigned j=0; j<height; j++) qDebug() << values[offset(i,j)] << " ";
            qDebug() << "\n";
        }
    }
};

//-------------------------------   SCALAR OPERATOR a*b and b*a
template <class dtype, class dtype2>
Matrix<dtype> operator + (const dtype2& v, const Matrix<dtype>& source) {
    return source + v;
}

template <class dtype, class dtype2>
Matrix<dtype> operator - (const dtype2& v, const Matrix<dtype>& source) {
    return (-source) + v;
}

template <class dtype, class dtype2>
Matrix<dtype> operator * (const dtype2& v, const Matrix<dtype>& source) {
    return source * v;
}

//-------------------------------   GENERIC MATRIX CALCULATION FUNCTION

enum MatOp{ADD, SUB, MUL, DIV, MATMUL};

//template <class dtype1, class dtype2>
inline Matrix<iFloat> matOperate(Matrix<iFloat> mat1, Matrix<iFloat> mat2, MatOp op) {
    if (op==ADD) return mat1 + mat2;
    if (op==SUB) return mat1 - mat2;
    if (op==MUL) return mat1 * mat2;
    if (op==DIV) return mat1 / mat2;
    if (op==MATMUL) return mat1.matmul(mat2);

    throw MatrixException("MatOperate: Unknown MatOp");
}



#endif // MATRIX_H
