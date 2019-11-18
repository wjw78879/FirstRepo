#include<iostream>
#include<vector>
#include<cassert>
#include "Matrix.h"
#include "MatricesHolder.h"

using namespace std;

int main() {
    double dat1[] = {1, 3, 5, 2, 4, 6, 3, 5, 7, 4, 6, 8, 5, 7, 9};
	double dat2[] = {1, 3, 5, 7, 9, 2, 4, 6, 8, 10, 3, 5, 7, 9, 11};
    double dat3[] = {2, 1, 3, 6, 1, -1, 2, 11, 4, 3, 5, 6};
    double dat4[] = {2, 0, 0, 2, 0, 1, 2, 3, 1};
    double dat5[] = {2, 3, -1, 2, 1, -1, 0, 3, 0, 5, 2, -7, 3, 2, 1, 3};
    Matrix mat1(dat1, 5, 3);
	Matrix mat2(dat2, 3, 5);
    Matrix mat3(dat3, 3, 4);
    Matrix mat4(dat4, 3, 3);
    Matrix mat5(dat5, 4, 4);
    cout << "origin: " << endl;
    mat1.print();
    //cout << "determinant: " << mat1.det() << endl; 
    cout << "transpose: " << endl;
    mat1.transpose().print();
    //cout << "adjoint: " << endl;
    //mat1.adjoint().print();
    //cout << "inverse: " << endl;
    //mat1.inverse().print();
	cout << "1 * 2: " << endl;
	(mat1 * mat2).print();

    mat3.reducedRowEchelonForm().print();
    cout << mat4.det() << endl;
    mat5.rowEchelonForm().print();
    return 0;
}