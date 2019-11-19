#ifndef MATRICESHOLDER_H
#define MATRICESHOLDER_H

#include<iostream>
#include<vector>
#include "Matrix.h"

using namespace std;

class MatricesHolder {
public:
    MatricesHolder();
    ~MatricesHolder();

    void add();
    void set();
    void cal();

    void run();
private:
    vector<Matrix> m_matrices;
    Matrix m_answer;
};

int getInt(int lowerBound, int upperBound);
    double getDouble();

#endif