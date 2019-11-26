#ifndef MATRIX_H
#define MATRIX_H

#include<iostream>
#include<vector>

using namespace std;

class Matrix {
    friend ostream& operator<< (ostream& o, const Matrix& c);
public:
    Matrix();
    Matrix(int rows, int cols);
    Matrix(vector<vector<double>>& values, int rows, int cols);
    Matrix(double* values, int rows, int cols);
    Matrix(const Matrix& other);
    Matrix(const double value);
    ~Matrix();

    void set(double value, int row, int col);
    Matrix& operator= (const Matrix& rhs);

    int rows() const;
    int cols() const;
    vector<vector<double>> data() const;

    vector<double>& operator[] (int rhs);
    Matrix operator+ (Matrix rhs);
    Matrix operator- (Matrix rhs);
    Matrix operator* (Matrix rhs);
    Matrix operator* (double rhs);

    Matrix subMatrix(int row, int col);
    double cofactor(int row, int col);
    double detCal(Matrix matrix, int rows, int cols);
    double det();
    Matrix transpose();
    Matrix adjoint();
    Matrix inverse();
    Matrix& rowOperationMultiply(double scalar, int row);
    Matrix& rowOperationInterchange(int row1, int row2);
    Matrix& rowOperationAdd(double scalar, int from, int to);

    Matrix& rowEchelonForm();
    Matrix& reducedRowEchelonForm();

    void print();
private:
    int m_rows;
    int m_cols;
    vector<vector<double>> m_data;
};

Matrix operator* (double lhs, Matrix rhs);

Matrix rowEchelon(Matrix matrix, int proceedRows, int proceedCols);
Matrix reducedRowEchelon(Matrix matrix);

#endif