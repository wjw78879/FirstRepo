#ifndef MATRICESHOLDER_H
#define MATRICESHOLDER_H

#include<iostream>
#include "Matrix.h"

class MatricesHolder {
public:
    MatricesHolder();
    ~MatricesHolder();

    Matrix& operator[] (int rhs) const;

    void add();
    void set(int number);

    void print(int number);
    void list();
private:
    vector<Matrix> m_matrices;
    int m_numMatrices;
};

#endif