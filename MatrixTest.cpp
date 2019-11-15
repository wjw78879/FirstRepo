#include<iostream>
#include<vector>
#include<cassert>

using namespace std;

class Matrix {
public:
    Matrix(int rows, int cols);
    Matrix(vector<vector<double>>& values, int rows, int cols);
    Matrix(double* values, int rows, int cols);
    ~Matrix();

    void set(double value, int row, int col);

    int rows() const;
    int cols() const;
    vector<double>& operator[] (int rhs) const;
    Matrix& operator= (const Matrix& rhs);
    Matrix& operator+ (const Matrix& rhs) const;
    Matrix& operator- (const Matrix& rhs) const;
    Matrix& operator* (const Matrix& rhs) const;

    double det() const;
    Matrix& inverse() const;
private:
    int m_rows;
    int m_cols;
    vector<vector<double>> m_data;
}

Matrix::Matrix(int rows, int cols) {
    assert(rows > 0 && cols > 0);
    m_rows = rows;
    m_cols = cols;
    for(int r = 0; r < rows; r++) {
        vector<double> row;
        for(int c = 0; c < cols; c++) {
            row.push_back(0);
        }
        m_data.push_back(row);
    }
}

Matrix::Matrix(double* values, int rows, int cols) {
    ssert(rows > 0 && cols > 0);
    assert(values != nullptr);
    m_rows = rows;
    m_cols = cols;
    for(int r = 0; r < rows; r++) {
        vector<double> row;
        for(int c = 0; c < cols; c++) {
            row.push_back(values[r * cols + c]);
        }
        m_data.push_back(row);
    }
}

Matrix::Matrix(vector<vector<double>>& values, int rows, int cols) {
    ssert(rows > 0 && cols > 0);
    m_rows = rows;
    m_cols = cols;
    for(int r = 0; r < rows; r++) {
        vector<double> row;
        for(int c = 0; c < cols; c++) {
            row.push_back(values[r][c]);
        }
        m_data.push_back(row);
    }
}

Matrix::~Matrix() {}

void set(double value, int row, int col) {
    ssert(row >= 0 && col >= 0 && row < m_rows && col < m_cols);
    m_data[row][col] = value;
}

int Matrix::rows() const {
    return m_rows;
}

int Matrix::cols() const {
    return m_cols;
}

vector<double>& Matrix::operator[] (int rhs) const {
    return m_data[rhs];
}

Matrix& Matrix::operator= (const Matrix& rhs) {
    m_rows = rhs.rows();
    m_cols = rhs.cols();
    m_data.clear();
    for(int r = 0; r < m_rows; r++) {
        vector<double> row;
        for(int c = 0; c < m_cols; c++) {
            row.push_back(rhs[r][c]);
        }
        m_data.push_back(row);
    }
    return *this;
}

Matrix& Matrix::operator+ (const Matrix& rhs) const {
    assert(m_rows = rhs.rows() && m_cols = rhs.cols());
    Matrix* result = new Matrix(*this);
    for(int r = 0; r < m_rows; r++) {
        for(int c = 0; c < cols; c++) {
            (*result)[r][c] = m_data[r][c] + rhs[r][c];
        }
    }
    return (*result);
}

Matrix& Matrix::operator- (const Matrix& rhs) const {
    assert(m_rows = rhs.rows() && m_cols = rhs.cols());
    Matrix* result = new Matrix(*this);
    for(int r = 0; r < m_rows; r++) {
        for(int c = 0; c < cols; c++) {
            (*result)[r][c] = m_data[r][c] - rhs[r][c];
        }
    }
    return (*result);
}

Matrix& Matrix::operator* (const Matrix& rhs) const {
    
}