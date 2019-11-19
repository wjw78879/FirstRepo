#include "MatricesHolder.h"
#include "Matrix.h"
#include<iostream>
#include<vector>
#include<string>
#include<sstream>

using namespace std;

MatricesHolder::MatricesHolder() : m_errcode(no_err) {}

MatricesHolder::~MatricesHolder() {}

int getInt(int lowerBound, int upperBound) {
    int res = 0;
    while(1) {
        cin >> res;
        if(res < lowerBound || res > upperBound) {
            cout << "Illegal input." << endl;
            continue;
        }
        string line;
        getline(cin, line);
        if(line.length() > 0) {
            cout << "Illegal input." << endl;
        } else {
            return res;
        }
    }
}

double getDouble() {
    double res = 0;
    while(1) {
        cin >> res;
        string line;
        getline(cin, line);
        if(line.length() > 0) {
            cout << "Illegal input." << endl;
        } else {
            return res;
        }
    }
}

void MatricesHolder::add() {
    int rows, cols;
    cout << "Rows: ";
    rows = getInt(1, 2000000000);
    cout << "Cols: ";
    cols = getInt(1, 2000000000);
    double* data = new double[rows * cols];
    cout << "Please enter the entries in order:" << endl;
    for(int r = 0; r < rows; r++) {
        for(int c = 0; c < cols; c++) {
            cout << "row " << r << ", col " << c << ": ";
            data[cols * r + c] = getDouble();
        }
    }
    m_matrices.push_back(Matrix(data, rows, cols));
    cout << "Matrix stored." << endl;
    delete[] data;
}

void MatricesHolder::set() {
    int no = 0;
    cout << "Enter which matrix would you like to set: ";
    no = getInt(0, m_matrices.size() - 1);
    int rows, cols;
    cout << "Rows: ";
    rows = getInt(1, 2000000000);
    cout << "Cols: ";
    cols = getInt(1, 2000000000);
    double* data = new double[rows * cols];
    cout << "Please enter the entries in order:" << endl;
    for(int r = 0; r < rows; r++) {
        for(int c = 0; c < cols; c++) {
            cout << "row " << r << ", col " << c << ": ";
            data[cols * r + c] = getDouble();
        }
    }
    m_matrices[no] = Matrix(data, rows, cols);
    cout << "Matrix stored." << endl;
    delete[] data;
}

void MatricesHolder::cal() {
    cout << "Enter the expression you want to calculate: ";
    string expr;
    getline(cin, expr);
    Matrix ans(execute(expr));
    if(m_errcode != no_err) {
        cout << "Error: ";
        switch(m_errcode) {
        case bad_bracket_pairing: cout << "Bad bracket pairing."; break;
        case no_such_matrix: cout << "No such matrix."; break;
        case no_such_temp: cout << "No such temp."; break;
        }
        cout << endl;
        m_errcode = no_err;
    } else {
        cout << "Answer:" << endl << ans;
    }
}

Matrix MatricesHolder::execute(string expr) {
    //execute ()s
    //finds
    vector<int> leftParenthesesPos;
    vector<int> rightParenthesesPos;
    for(int i = 0; i < expr.length(); i++) {
        if(expr[i] == '(') {
            leftParenthesesPos.push_back(i);
        }
        if(expr[i] == ')') {
            rightParenthesesPos.push_back(i);
        }
    }
    //checks
    if(leftParenthesesPos.size() != rightParenthesesPos.size()) {
        m_errcode = bad_bracket_pairing;
        return Matrix();
    }
    if(leftParenthesesPos.size() != 0) {
        string next(expr.substr(leftParenthesesPos[0] + 1, rightParenthesesPos[0] - leftParenthesesPos[0] - 1));
        expr.erase(leftParenthesesPos[0], rightParenthesesPos[0] - leftParenthesesPos[0] + 1);
        string sign("t");
        sign.append(to_string(m_temp.size()));
        if(expr.length() > leftParenthesesPos[0]) {
            expr.insert(leftParenthesesPos[0], sign);
        } else {
            expr.append(sign);
        }
        m_temp.push_back(Matrix(execute(next)));
        return execute(expr);
    }
    //execute +,-s
    //finds
    int plusMinusPos = -1;
    bool isPlus;
    for(int i = 0; i < expr.length(); i++) {
        if(expr[i] == '+') {
            plusMinusPos = i;
            isPlus = true;
            break;
        } else if(expr[i] == '-') {
            plusMinusPos = i;
            isPlus = false;
            break;
        }
    }
    //checks
    if(plusMinusPos != -1) {
        string left(expr.substr(0, plusMinusPos));
        string right(expr.substr(plusMinusPos + 1, expr.length() - plusMinusPos - 1));
        if(isPlus)return execute(left) + execute(right);
        else return execute(left) - execute(right);
    }
    //execute *s
    //finds
    int multiplePos = -1;
    for(int i = 0; i < expr.length(); i++) {
        if(expr[i] == '*') {
            multiplePos = i;
            break;
        }
    }
    //checks
    if(multiplePos != -1) {
        string left(expr.substr(0, multiplePos));
        string right(expr.substr(multiplePos + 1, expr.length() - multiplePos - 1));
        return execute(left) * execute(right);
    }
    //execute signs
    for(int i= 0; i < expr.length(); i++) {
        if(expr[i] == 'm') {
            stringstream strs(expr.substr(i + 1, expr.length() - i - 1));
            int number = 0;
            strs >> number;
            if(number < 0 || number >= m_matrices.size()) {
                m_errcode = no_such_matrix;
                return Matrix();
            }
            return m_matrices[number];
        } else if(expr[i] == 't') {
            stringstream strs(expr.substr(i + 1, expr.length() - i - 1));
            int number = 0;
            strs >> number;
            if(number < 0 || number >= m_matrices.size()) {
                m_errcode = no_such_temp;
                return Matrix();
            }
            return m_temp[number];
        }
    }
    //execute numbers
    double scalar = 0;
    stringstream strs(expr);
    strs >> scalar;
    return Matrix(&scalar, 1, 1);
}

void MatricesHolder::ref() {
    if(m_matrices.size() == 0) {
        cout << "No matrix stored." << endl;
        return;
    }
    cout << "Which matrix do you want to see in REF?: ";
    cout << m_matrices[getInt(0, m_matrices.size() - 1)].rowEchelonForm();
}

void MatricesHolder::rref() {
    if(m_matrices.size() == 0) {
        cout << "No matrix stored." << endl;
        return;
    }
    cout << "Which matrix do you want to see in RREF?: ";
    cout << m_matrices[getInt(0, m_matrices.size() - 1)].reducedRowEchelonForm();
}

void MatricesHolder::det() {
    if(m_matrices.size() == 0) {
        cout << "No matrix stored." << endl;
        return;
    }
    cout << "Which matrix do you want to calculate the determinant?: ";
    int choice = getInt(0, m_matrices.size() - 1);
    if(m_matrices[choice].rows() != m_matrices[choice].cols()) {
        cout << "This matrix is not a square matrix!" << endl;
        return;
    }
    cout << m_matrices[choice].det() << endl;
}

void MatricesHolder::run() {
    int op = 0;
    while(1) {
        if(m_matrices.size() > 0) {
            cout << "Stored matrices: " << endl;
            for(int i = 0; i < m_matrices.size(); i++) {
                cout << "Matrix #" << i << ":" << endl;
                cout << m_matrices[i];
            }
        } else {
            cout << "No matrices stored." << endl;
        }
        cout << "What do you want to do?" <<endl;
        cout << "1. Add a new matrix" <<endl;
        cout << "2. Set an existed matrix" << endl;
        cout << "3. Do calculations" << endl;
        cout << "4. See row-echelon form" <<endl;
        cout << "5. See reduced row-echelon form" << endl;
        cout << "6. Calculate determinant" << endl;
        cout << "0. Quit" << endl;
        cout << ": ";
        op = getInt(0, 6);
        switch(op) {
        case 1: {
            this->add();
            break;
        }
        case 2: {
            this->set();
            break;
        }
        case 3: {
            this->cal();
            break;
        }
        case 4: {
            this->ref();
            break;
        }
        case 5: {
            this->rref();
            break;
        }
        case 6: {
            this->det();
            break;
        }
        case 0: {
            exit(0);
        }
        }
    }
}