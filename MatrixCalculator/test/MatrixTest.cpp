#include<iostream>
#include<vector>
#include<cassert>
#include "Matrix.h"
#include "MatricesHolder.h"
#include "MatrixConfig.h"

using namespace std;

int main() {
    cout << "Version:" << MATRIX_VERSION_MAJOR << "." << MATRIX_VERSION_MINOR << endl;
    MatricesHolder holder;
    holder.run();
    return 0;
}