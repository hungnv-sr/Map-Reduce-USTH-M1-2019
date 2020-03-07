#pragma once
#ifndef MATRIX_H
#define MATRIX_H

#include <utilityenum.h>
#include <ifloat.h>
#include <QDebug>

// Standard std::exception subclass
// that implements string constructor
struct MatrixException : public std::exception {
private:
    QString msg;

public:
    MatrixException(QString mess) {
        msg = mess;
    }
    const char* what() const throw() {
        return msg.toStdString().c_str();
    }
};


//--------------------------------------------------------------------
template <class dtype>
class Matrix
{
private:
    unsigned height, width;

protected:
    dtype *values;

    unsigned offset(unsigned row, unsigned col) const {
        return row*width + col;
    }

    void cleanup() {
        delete[] values;
    }

    void allocate() {
        if (height==0 || width==0)
            throw MatrixException("Can't allocate matrix with size 0");
        values = new dtype[height*width];
    }

    void copyArray(const dtype* const v) {
        for (unsigned i=0; i<height*width; i++) values[i] = v[i];
    }

    void copy(const Matrix& m) {
        height = m.height;
        width = m.width;        
        allocate();
        copyArray(m.values);
    }

public:
    Matrix() {
        height = 0;
        width = 0;
    }

    //-------------------       CANONICAL FORM
    Matrix(const unsigned newHeight, const unsigned newWidth, const dtype init=0.0) {
        height = newHeight;
        width = newWidth;        
        allocate();
        for (unsigned i=0; i<height*width; i++) values[i] = init;
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
        height = m.getHeight();
        width = m.getWidth();
        allocate();
        for (unsigned i=0; i<height*width; i++) values[i] = numeric_cast<dtype>(m[i]);

        return *this;
    }

    template<class dtypeOther>
    operator Matrix<dtypeOther>() const {
        Matrix<dtypeOther> res(height, width, 0);
        for (unsigned i=0; i<height*width; i++) res[i] = numeric_cast<dtypeOther>(values[i]);
        return res;
    }

    // Experiment result is represented by 1 number.
    // So we need a function that convert a matrix into 1 number -> use Sum
    // Also, the data result type must be common -> use iFloat
    template <class CalculationType>
    iFloat sum() const {
        CalculationType res = 0;
        for (unsigned i=0; i<height*width;i++) res = res + CalculationType(values[i]);
        return res;
    }

    explicit operator iFloat() const {
        return (*this).template sum<iFloat>();
    }


    //--------------------- UTILITY ACCESS OPERATOR
    dtype& operator [] (unsigned index) {
        if (index < 0 || index >= height*width)
            throw MatrixException("Operator [] out of range access");
        return values[index];
    }

    dtype operator [] (unsigned index) const {
        if (index < 0 || index >= height*width)
            throw MatrixException("Operator [] const out of range access");
        return values[index];
    }

    dtype& operator () (unsigned row, unsigned col) {
        if (row < 0 || col < 0 || row >= height || col >= width)
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
        if (height!=m.height || width!=m.width)
            throw MatrixException("Operator +: dimension doesn't match");
        Matrix res(height, width, 0);
        for (unsigned i=0;i<height*width;i++) res[i] = values[i] + m[i];
        return res;
    }

    Matrix operator - (const Matrix& m) const {
        if (height!=m.height || width!=m.width)
            throw MatrixException("Operator -: dimension doesn't match");
        Matrix res(height, width, 0);
        for (unsigned i=0;i<height*width;i++) res[i] = values[i] - m[i];
        return res;
    }

    Matrix operator * (const Matrix& m) const {
        if (height!=m.height || width!=m.width)
            throw MatrixException("Operator *: dimension doesn't match");
        Matrix res(height, width, 0);
        for (unsigned i=0;i<height*width;i++) res[i] = values[i] * m[i];
        return res;
    }

    Matrix operator / (const Matrix& m) const {
        if (height!=m.height || width!=m.width)
            throw MatrixException("Operator /: dimension doesn't match");
        Matrix res(height, width, 0);
        for (unsigned i=0;i<height*width;i++) res[i] = values[i] / m[i];
        return res;
    }

    Matrix matmul(const Matrix& mat) const {
        unsigned m = height, n = width, p = mat.width;
        if (width != mat.height)
            throw MatrixException("Matmul: matrix sizes mismatch");
        Matrix res(m, p, 0);
        for (unsigned i=0;i<m;i++)
            for (unsigned j=0;j<p;j++)
                for (unsigned k=0;k<n;k++) res(i,j) = res(i,j) + (*this)(i,k) * mat(k,j);
        return res;
    }

    // comparing matrices is useless, so just return true for < and false for >
    // it will never be used. But we need to add it to make class matrix compatible with "SORT" ReduceAlgorithm
    // if a programmer somehow accidentally use SORT on Matrix datatype, it will be the same as using the Linear algorithm. So no error
    bool operator < (const Matrix& mat) const {
        Q_UNUSED(mat);
        return true;
    }

    bool operator > (const Matrix& mat) const {
        Q_UNUSED(mat);
        return false;
    }

    // comparing matrix to number doesn't make sense, so just return true.
    // this is to make matrix compatible with other numeric classes
    template <typename anyType>
    bool operator < (const anyType &x) const {
        Q_UNUSED(x);
        return true;
    }

    template <typename anyType>
    bool operator > (const anyType &x) const {
        Q_UNUSED(x);
        return false;
    }

    //--------------------------    SCALAR CALCULATION OPERATOR
    template<class dtype2>
    Matrix operator + (const dtype2& v) const {
        Matrix res(height, width, 0);
        for (unsigned i=0;i<height*width;i++) res[i] = values[i] + v;
        return res;
    }

    template<class dtype2>
    Matrix operator - (const dtype2& v) const {
        Matrix res(height, width, 0);
        for (unsigned i=0;i<height*width;i++) res[i] = values[i] - v;
        return res;
    }

    template<class dtype2>
    Matrix operator * (const dtype2& v) const {
        Matrix res(height, width, 0);
        for (unsigned i=0;i<height*width;i++) res[i] = values[i] * v;
        return res;
    }

    template<class dtype2>
    Matrix operator / (const dtype2& v) const {
        Matrix res(height, width, 0);
        for (unsigned i=0;i<height*width;i++) res[i] = values[i] / v;
        return res;
    }

    Matrix operator - () const {
        Matrix res(height, width, 0);
        for (unsigned i=0;i<height*width;i++) res[i] = -values[i];
        return res;
    }

    //-----------------------   GETTER/SETTER, PRINT SCREEN
    unsigned getHeight() const {
        return height;
    }

    unsigned getWidth() const {
        return width;
    }

    unsigned getLength() const {
        return height*width;
    }


    void print() const {
        for (unsigned i=0; i<height; i++)
        {
            for (unsigned j=0; j<width; j++) cout << values[offset(i,j)] << " ";
            cout << "\n";
        }
    }

    template <typename Any, typename MatType>
    friend bool operator < (const Any &x, const Matrix &mat);

    template <typename Any, typename MatType>
    friend bool operator > (const Any &x, const Matrix &mat);
};

template <typename Any, typename MatType>
bool operator < (const Any &x, const Matrix<MatType> &mat) {
    Q_UNUSED(mat);
    Q_UNUSED(x);
    return true;
}

template <typename Any, typename MatType>
bool operator > (const Any &x, const Matrix<MatType> &mat) {
    Q_UNUSED(mat);
    Q_UNUSED(x);
    return false;
}



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
/*
template <typename dtype>
inline Matrix<dtype> matOperate(const Matrix<dtype> &mat1, const Matrix<dtype> &mat2, Op op) {
    if (op==ADD) return mat1 + mat2;
    if (op==SUB) return mat1 - mat2;
    if (op==MUL) return mat1 * mat2;
    if (op==DIV) return mat1 / mat2;
    if (op==MATMUL) return mat1.matmul(mat2);

    throw MatrixException("Operate: Unknown Op");
}
*/


#endif // MATRIX_H
