#ifndef MATRICESHOLDER_H
#define MATRICESHOLDER_H

#include<iostream>
#include<vector>
#include "Matrix.h"

using namespace std;

enum errs {no_err, bad_bracket_pairing, no_such_matrix, no_such_temp};

class MatricesHolder {
public:
    MatricesHolder();
    ~MatricesHolder();

    void add();
    void set();
    void cal();
    Matrix execute(string expr);
    void ref();
    void rref();
    void det();

    void run();
private:
    errs m_errcode;
    vector<Matrix> m_matrices;
    vector<Matrix> m_temp;
};

int getInt(int lowerBound, int upperBound);
double getDouble();

#endif