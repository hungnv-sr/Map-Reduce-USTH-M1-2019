#ifndef BASEDATATYPE_H
#define BASEDATATYPE_H

enum Op{ADD, SUB, MUL, DIV, MATMUL};

enum DataType{NUMERIC, ARRAY, MATRIX};

class BaseDataType
{
protected:
    BaseDataType() {} ;
};

#endif // BASEDATATYPE_H
