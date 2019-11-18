#include<iostream>
#include<vector>
#include<cassert>
#include "Matrix.h"
#include "MatricesHolder.h"

using namespace std;

int main() {
    double dat1[] = {1, 3, 5, 2, 4, 6, 3, 5, 7, 4, 6, 8, 5, 7, 9};
	double dat2[] = {1, 3, 5, 7, 9, 2, 4, 6, 8, 10, 3, 5, 7, 9, 11};
    Matrix mat1(dat1, 5, 3);
	Matrix mat2(dat2, 3, 5);
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
    return 0;
}