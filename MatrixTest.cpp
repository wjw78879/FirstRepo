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
    Matrix& operator= (const Matrix& rhs);

    int rows() const;
    int cols() const;

    vector<double> operator[] (int rhs) const;
    Matrix operator+ (const Matrix& rhs) const;
    Matrix operator- (const Matrix& rhs) const;
    Matrix operator* (const Matrix& rhs) const;
    Matrix operator* (double rhs) const;

    Matrix subMatrix(int row, int col) const;
    double detCal(Matrix matrix, int rows, int cols);
    double det();
    Matrix transpose() const;
    Matrix adjoint() const;
    Matrix inverse();

    void print();
private:
    int m_rows;
    int m_cols;
    vector<vector<double>> m_data;
};

Matrix operator* (double lhs, const Matrix& rhs) {
    Matrix result(rhs);
    for(int r = 0; r < rhs.rows(); r++) {
        for(int c = 0; c < rhs.cols(); c++) {
            result.set(rhs[r][c] * lhs, r, c);
        }
    }
    return result;
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
    assert(rows > 0 && cols > 0);
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
    assert(rows > 0 && cols > 0);
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

vector<double> Matrix::operator[] (int rhs) const {
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

Matrix Matrix::operator+ (const Matrix& rhs) const {
    assert(m_rows == rhs.rows() && m_cols == rhs.cols());
    Matrix result(*this);
    for(int r = 0; r < m_rows; r++) {
        for(int c = 0; c < m_cols; c++) {
            result.set(m_data[r][c] + rhs[r][c], r, c);
        }
    }
    return result;
}

Matrix Matrix::operator- (const Matrix& rhs) const {
    assert(m_rows == rhs.rows() && m_cols == rhs.cols());
    Matrix result(*this);
    for(int r = 0; r < m_rows; r++) {
        for(int c = 0; c < m_cols; c++) {
            result.set(m_data[r][c] - rhs[r][c], r, c);
        }
    }
    return result;
}

Matrix Matrix::operator* (const Matrix& rhs) const {
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

Matrix Matrix::operator* (double rhs) const {
    Matrix result(*this);
    for(int r = 0; r < m_rows; r++) {
        for(int c = 0; c < m_cols; c++) {
            result.set(m_data[r][c] * rhs, r, c);
        }
    }
    return result;
}

Matrix Matrix::subMatrix(int row, int col) const {
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

double Matrix::detCal(Matrix matrix, int rows, int cols) {
    if(rows == 1)return matrix[0][0];
    double result = 0;
    for(int i = 0; i < rows; i++) {
        Matrix subMat = matrix.subMatrix(i, 0);
        if(i % 2 == 0)result += matrix[i][0] * detCal(subMat, rows - 1, cols - 1);
        else result -= matrix[i][0] * detCal(subMat, rows - 1, cols - 1);
    }
    return result;
}

double Matrix::det() {
    assert(m_cols == m_rows);
    Matrix temp(*this);
    double result = detCal(temp, m_rows, m_cols);
    return result;
}

Matrix Matrix::transpose() const {
    Matrix result(m_cols, m_rows);
    for(int r = 0; r < m_rows; r++) {
        for(int c = 0; c < m_cols; c++) {
            result.set(m_data[r][c], c, r);
        }
    }
    return result;
}

Matrix Matrix::adjoint() const {
    assert(m_cols == m_rows);
    Matrix cofMat(m_rows, m_cols);
    for(int r = 0; r < m_rows; r++) {
        for(int c = 0; c < m_cols; c++) {
            cofMat.set(subMatrix(r, c).det(), r, c);
        }
    }
    return cofMat.transpose();
}

Matrix Matrix::inverse() {
    double determinant = det();
    assert(determinant != 0);
    return (1.0f / determinant) * adjoint();
}

void Matrix::print() {
    for(int r = 0; r < m_rows; r++) {
        for(int c = 0; c < m_cols; c++) {
            cout << m_data[r][c] << " ";
        }
        cout << endl;
    }
}

int main() {
    double dat1[] = {2, 5, 5, -1, -1, 0, 2, 4, 3};
    Matrix mat1(dat1, 3, 3);
    cout << mat1.det() << endl; 
    (mat1 * 2).print();
    return 0;
}