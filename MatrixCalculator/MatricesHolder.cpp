#include "MatricesHolder.h"
#include<iostream>
#include<vector>
#include<string>

using namespace std;

MatricesHolder::MatricesHolder() {}

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

void MatricesHolder::cal() {}

void MatricesHolder::run() {
    int op = 0;
    while(1) {
        if(m_matrices.size() > 0) {
            cout << "Stored matrices: " << endl;
            for(int i = 0; i < m_matrices.size(); i++) {
                cout << "Matrix #" << i << ":" << endl;
                m_matrices[i].print();
            }
        } else {
            cout << "No matrices stored." << endl;
        }
        cout << "What do you want to do?" <<endl;
        cout << "1. Add a new matrix" <<endl;
        cout << "2. Set an existed matrix" << endl;
        cout << "3. Do calculations" << endl;
        cout << "0. Quit" << endl;
        cout << ": ";
        op = getInt(0, 3);
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
        case 0: {
            exit(0);
        }
        }
    }
}