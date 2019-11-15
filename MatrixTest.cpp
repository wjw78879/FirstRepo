#include<iostream>
#include<vector>
#include<cassert>
#include "Matrix.h"
#include "MatricesHolder.h"

using namespace std;

int main() {
    double dat1[] = {1, 3, 1, 1, 2, 5, 2, 2, 1, 3, 8, 9, 1, 3, 2, 2};
    Matrix mat1(dat1, 4, 4);
    cout << "origin: " << endl;
    mat1.print();
    cout << "determinant: " << mat1.det() << endl; 
    cout << "transpose: " << endl;
    mat1.transpose().print();
    cout << "adjoint: " << endl;
    mat1.adjoint().print();
    cout << "inverse: " << endl;
    mat1.inverse().print();
    return 0;
}