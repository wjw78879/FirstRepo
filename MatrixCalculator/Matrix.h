#ifndef MATRIX_H
#define MATRIX_H

#include<iostream>
#include<vector>

using namespace std;

class Matrix {
public:
    Matrix(int rows, int cols);
    Matrix(vector<vector<double>>& values, int rows, int cols);
    Matrix(double* values, int rows, int cols);
    ~Matrix();

    void set(double value, int row, int col);
    Matrix& operator= (const Matrix& rhs);

    int rows() const;
    int cols() const;

    vector<double> operator[] (int rhs) const;
    Matrix operator+ (const Matrix& rhs) const;
    Matrix operator- (const Matrix& rhs) const;
    Matrix operator* (const Matrix& rhs) const;
    Matrix operator* (double rhs) const;

    Matrix subMatrix(int row, int col) const;
    double cofactor(int row, int col);
    double detCal(Matrix matrix, int rows, int cols);
    double det();
    Matrix transpose() const;
    Matrix adjoint();
    Matrix inverse();

    void print();
private:
    int m_rows;
    int m_cols;
    vector<vector<double>> m_data;
};

Matrix operator* (double lhs, const Matrix& rhs);

#endif