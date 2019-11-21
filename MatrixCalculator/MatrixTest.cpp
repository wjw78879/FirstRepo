#include<iostream>
#include<vector>
#include<cassert>
#include "Matrix.h"
#include "MatricesHolder.h"

using namespace std;

int main() {
    Matrix n(4000, 4000);
    for(int i = 0; i < 4000; i++) {
        for(int j = 0; j < 4000; j++) {
            n[i][j] = (i + j) % 30;
        }
    }
    cout << "test" << endl;
    n.reducedRowEchelonForm();
    MatricesHolder holder;
    holder.run();
    return 0;
}