#include<iostream>
#include<vector>
#include<cassert>
#include<string>
#include<sstream>
#include<cmath>
#include "Matrix.h"

using namespace std;

Matrix operator* (double lhs, Matrix rhs) {
    Matrix result(rhs);
    for(int r = 0; r < rhs.rows(); r++) {
        for(int c = 0; c < rhs.cols(); c++) {
            result.set(result[r][c] * lhs, r, c);
        }
    }
    return result;
}

ostream& operator<< (ostream& o, const Matrix& mat) {
    vector<vector<string>> strVec;
    for(int r = 0; r < mat.m_rows; r++) {
        vector<string> temp;
        for(int c = 0; c < mat.m_cols; c++) {
            double num = mat.m_data[r][c];
            if(fabs(num) < epsilon)num = 0.0f;
            ostringstream strs;
            strs << num;
            temp.push_back(strs.str());
        }
        strVec.push_back(temp);
    }
    vector<int> maxLength(mat.m_cols, 0);
    for(int c = 0; c < mat.m_cols; c++) {
        maxLength[c] = strVec[0][c].length();
        for(int r = 1; r < mat.m_rows; r++) {
            size_t temp = strVec[r][c].length();
            if(temp > maxLength[c])maxLength[c] = temp;
        }
    }
    size_t lineLength = 3;
    for(int c = 0; c < mat.m_cols; c++)lineLength += (maxLength[c] + 1);
    cout << "/ ";
    for(int i = 0; i < lineLength - 4; i++)cout << " ";
    cout << " \\" << endl;
    for(int r = 0; r < mat.m_rows; r++) {
        cout << "| ";
        for(int c = 0; c < mat.m_cols; c++) {
            size_t strLen = strVec[r][c].length();
            int times = 0;
            if((maxLength[c] - strLen) % 2 == 0)times = (maxLength[c] - strLen) / 2;
            else times = (maxLength[c] - strLen) / 2 + 1;
            for(int i = 0; i < times; i++)cout << " ";
            cout << strVec[r][c];
            for(int i = 0; i < maxLength[c] - strLen - times + 1; i++)cout << " ";
        }
        cout << "|" << endl;
    }
    cout << "\\";
    for(int i = 0; i < lineLength - 2; i++)cout << " ";
    cout << "/" << endl;
    return o;
}

Matrix::Matrix() {
    m_rows = 0;
    m_cols = 0;
}

Matrix::Matrix(int rows, int cols) {
    assert(rows > 0 && cols > 0);
    m_rows = rows;
    m_cols = cols;
    m_data.reserve(rows);
    for(int r = 0; r < rows; r++) {
        vector<double> row;
        row.reserve(cols);
        for(int c = 0; c < cols; c++) {
            row.push_back(0);
        }
        m_data.push_back(row);
    }
}

Matrix::Matrix(double* values, int rows, int cols) {
    assert(rows > 0 && cols > 0);
    assert(values != nullptr);
    m_rows = rows;
    m_cols = cols;
    m_data.reserve(rows);
    for(int r = 0; r < rows; r++) {
        vector<double> row;
        row.reserve(cols);
        for(int c = 0; c < cols; c++) {
            row.push_back(values[r * cols + c]);
        }
        m_data.push_back(row);
    }
}

Matrix::Matrix(vector<vector<double>>& values, int rows, int cols) {
    assert(rows > 0 && cols > 0);
    m_rows = rows;
    m_cols = cols;
    m_data.reserve(rows);
    for(int r = 0; r < rows; r++) {
        vector<double> row;
        row.reserve(cols);
        for(int c = 0; c < cols; c++) {
            row.push_back(values[r][c]);
        }
        m_data.push_back(row);
    }
}

Matrix::Matrix(const Matrix& other) {
    m_data = other.data();
    m_rows = other.rows();
    m_cols = other.cols();
}

Matrix::Matrix(const double value) {
    vector<double> row;
    row.push_back(value);
    m_data.push_back(row);
    m_rows = 1;
    m_cols = 1;
}

Matrix::~Matrix() {}

void Matrix::set(double value, int row, int col) {
    assert(row >= 0 && col >= 0 && row < m_rows && col < m_cols);
    m_data[row][col] = value;
}

int Matrix::rows() const {
    return m_rows;
}

int Matrix::cols() const {
    return m_cols;
}

vector<vector<double>> Matrix::data() const {
    return m_data;
}

vector<double>& Matrix::operator[] (int rhs) {
    return m_data[rhs];
}

Matrix& Matrix::operator= (const Matrix& rhs) {
    m_rows = rhs.rows();
    m_cols = rhs.cols();
    m_data = rhs.data();
    return *this;
}

Matrix Matrix::operator+ (Matrix rhs) {
    assert(m_rows == rhs.rows() && m_cols == rhs.cols());
    Matrix result(*this);
    for(int r = 0; r < m_rows; r++) {
        for(int c = 0; c < m_cols; c++) {
            result.set(m_data[r][c] + rhs[r][c], r, c);
        }
    }
    return result;
}

Matrix Matrix::operator- (Matrix rhs) {
    assert(m_rows == rhs.rows() && m_cols == rhs.cols());
    Matrix result(*this);
    for(int r = 0; r < m_rows; r++) {
        for(int c = 0; c < m_cols; c++) {
            result.set(m_data[r][c] - rhs[r][c], r, c);
        }
    }
    return result;
}

Matrix Matrix::operator* (Matrix rhs) {
    if(m_rows == m_cols && m_rows == 1) {
        return rhs * m_data[0][0];
    } else if(rhs.rows() == rhs.cols() && rhs.rows() == 1) {
        return (*this) * rhs[0][0];
    }
    assert(m_cols == rhs.rows());
    Matrix result(m_rows, rhs.cols());
    for(int r = 0; r < m_rows; r++) {
        for(int c = 0; c < rhs.cols(); c++) {
            for(int i = 0; i < m_cols; i++) {
                result.set(result[r][c] + m_data[r][i] * rhs[i][c], r, c);
            }
        }
    }
    return result;
}

Matrix Matrix::operator* (double rhs) {
    Matrix result(*this);
    for(int r = 0; r < m_rows; r++) {
        for(int c = 0; c < m_cols; c++) {
            result.set(m_data[r][c] * rhs, r, c);
        }
    }
    return result;
}

Matrix Matrix::subMatrix(int row, int col) {
    assert(col >= 0 && row >= 0 && col < m_cols && row < m_rows);
    vector<vector<double>> subMat;
    for(int r = 0; r < m_rows; r++) {
        if(r == row)continue;
        vector<double> row;
        for(int c = 0; c < m_cols; c++) {
            if(c == col)continue;
            row.push_back(m_data[r][c]);
        }
        subMat.push_back(row);
    }
    Matrix result(subMat, m_rows - 1, m_cols - 1);
    return result;
}

double Matrix::cofactor(int row, int col) {
    assert(col >= 0 && row >= 0 && col < m_cols && row < m_rows);
    double minor = detCal(subMatrix(row, col), m_rows - 1, m_cols - 1);
    if((row + col) % 2 == 0)return minor;
    else return -minor;
}

double Matrix::detCal(Matrix matrix, int rows, int cols) {
    if(rows == 1)return matrix[0][0];
    double result = 0;
    for(int i = 0; i < rows; i++) {
        result += matrix[i][0] * matrix.cofactor(i, 0);
    }
    return result;
}

double Matrix::det() {
    assert(m_cols == m_rows);
    return detCal(*this, m_rows, m_cols);
}

Matrix Matrix::transpose() {
    Matrix result(m_cols, m_rows);
    for(int r = 0; r < m_rows; r++) {
        for(int c = 0; c < m_cols; c++) {
            result.set(m_data[r][c], c, r);
        }
    }
    return result;
}

Matrix Matrix::adjoint() {
    assert(m_cols == m_rows);
    Matrix cofMat(m_rows, m_cols);
    for(int r = 0; r < m_rows; r++) {
        for(int c = 0; c < m_cols; c++) {
            cofMat.set(cofactor(r, c), r, c);
        }
    }
    return cofMat.transpose();
}

Matrix Matrix::inverse() {
    double determinant = det();
    assert(determinant != 0);
    return (1.0f / determinant) * adjoint();
}

Matrix& Matrix::rowOperationMultiply(double scalar, int row) {
    assert(scalar != 0 && row >= 0 && row < m_rows);
    for(int c = 0; c < m_cols; c++) {
        m_data[row][c] *= scalar;
    }
    return (*this);
}

Matrix& Matrix::rowOperationInterchange(int row1, int row2) {
    assert(row1 >= 0 && row2 >= 0 && row1 < m_rows && row2 < m_rows && row1 != row2);
    double temp = 0;
    for(int c = 0; c < m_cols; c++) {
        temp = m_data[row1][c];
        m_data[row1][c] = m_data[row2][c];
        m_data[row2][c] = temp;
    }
    return (*this);
}

Matrix& Matrix::rowOperationAdd(double scalar, int from, int to) {
    assert(from >=0 && to >=0 && from < m_rows && to < m_rows && from != to);
    for(int c = 0; c < m_cols; c++) {
        m_data[to][c] += (scalar * m_data[from][c]);
    }
    return (*this);
}

Matrix Matrix::rowEchelonForm() {
    return rowEchelon((*this), 0, 0);
}

Matrix Matrix::reducedRowEchelonForm() {
    return reducedRowEchelon(*this);
}

void Matrix::print() {
    double epsilon = 0.000001f;
    vector<vector<string>> strVec;
    for(int r = 0; r < m_rows; r++) {
        vector<string> temp;
        for(int c = 0; c < m_cols; c++) {
            double num = m_data[r][c];
            if(fabs(num) < epsilon)num = 0.0f;
            ostringstream strs;
            strs << num;
            temp.push_back(strs.str());
        }
        strVec.push_back(temp);
    }
    vector<int> maxLength(m_cols, 0);
    for(int c = 0; c < m_cols; c++) {
        maxLength[c] = strVec[0][c].length();
        for(int r = 1; r < m_rows; r++) {
            size_t temp = strVec[r][c].length();
            if(temp > maxLength[c])maxLength[c] = temp;
        }
    }
    size_t lineLength = 3;
    for(int c = 0; c < m_cols; c++)lineLength += (maxLength[c] + 1);
    cout << "/ ";
    for(int i = 0; i < lineLength - 4; i++)cout << " ";
    cout << " \\" << endl;
    for(int r = 0; r < m_rows; r++) {
        cout << "| ";
        for(int c = 0; c < m_cols; c++) {
            size_t strLen = strVec[r][c].length();
            int times = 0;
            if((maxLength[c] - strLen) % 2 == 0)times = (maxLength[c] - strLen) / 2;
            else times = (maxLength[c] - strLen) / 2 + 1;
            for(int i = 0; i < times; i++)cout << " ";
            cout << strVec[r][c];
            for(int i = 0; i < maxLength[c] - strLen - times + 1; i++)cout << " ";
        }
        cout << "|" << endl;
    }
    cout << "\\";
    for(int i = 0; i < lineLength - 2; i++)cout << " ";
    cout << "/" << endl;
}

Matrix rowEchelon(Matrix matrix, int proceedRows, int proceedCols) {
    //cout << "currently executing: " << endl << matrix << "Proceed rows: " << proceedRows << endl << "Proceed cols: " << proceedCols << endl;
    //cout << "checking leading 1s..." << endl;
    for(int r = proceedRows; r < matrix.rows(); r++) {
        if(fabs(matrix[r][proceedCols] - 0) > epsilon) {
            if(r != proceedRows)matrix.rowOperationInterchange(proceedRows, r);
            break;
        }
    }
    //cout << "checking 0 cols..." << endl;
    if(fabs(matrix[proceedRows][proceedCols] - 0) < epsilon) {
        if(proceedCols == (matrix.cols() - 1))return matrix;
        return rowEchelon(matrix, proceedRows, proceedCols + 1);
    }
    //cout << "operating..." << endl;
    matrix.rowOperationMultiply(1.0f / matrix[proceedRows][proceedCols], proceedRows);
    for(int r = proceedRows + 1; r < matrix.rows(); r++) {
        matrix.rowOperationAdd(-1.0f * matrix[r][proceedCols] / matrix[proceedRows][proceedCols], proceedRows, r);
    }
    //cout << "checking end of execute..." << endl;
    if(proceedRows == (matrix.rows() - 1) || proceedCols == (matrix.cols() - 1))return matrix;
    //cout << "No." << endl << endl;
    return rowEchelon(matrix, proceedRows + 1, proceedCols + 1);
}

Matrix reducedRowEchelon(Matrix matrix) {
    matrix = rowEchelon(matrix, 0, 0);
    for(int r = matrix.rows() - 1; r >= 0; r--) {
        for(int c = 0; c < matrix.cols(); c++) {
            if(matrix[r][c] == 1) {
                for(int r2 = 0; r2 < r; r2++) {
                    matrix.rowOperationAdd(-1.0f * matrix[r2][c], r, r2);
                }
                break;
            }
        }
    }
    return matrix;
}