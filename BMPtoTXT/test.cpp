#include "bmpHolder.h"
#include<iostream>
#include<string>
#include<sstream>

using namespace std;

int main(int argc, char** argv) {
    if(argc != 4 && argc != 6) {
        cout << "Args invalid." << endl;
        return -1;
    }
    bmpHolder holder;
    string op(argv[1]);
    if(op == "ttob") {
        if(argc != 6) {
            cout << "Args invalid." << endl;
            return -1;
        }
        string path = string(argv[2]) + string("/") + string(argv[3]) + string(".txt");
        string savepath = string(argv[2]) + string("/") + string(argv[3]) + string(".bmp");
        string rows(argv[4]);
        stringstream rowss(rows);
        string cols(argv[5]);
        stringstream colss(cols);
        unsigned int col = 0, row = 0;
        rowss >> row;
        colss >> col;
        if(!holder.readTXT(path.c_str(), row, col)) {
            cout << "Failed reading." << endl;
            return -1;
        }
        if(!holder.save(savepath.c_str())) {
            cout << "Failed saving." << endl;
            return -1;
        }
    } else if(op == "btot") {
        if(argc != 4) {
            cout << "Args invalid." << endl;
            return -1;
        }
        string path = string(argv[2]) + string("/") + string(argv[3]) + string(".bmp");
        string savepath = string(argv[2]) + string("/") + string(argv[3]) + string(".txt");
        if(!holder.read(path.c_str())) {
            cout << "Failed reading." << endl;
            return -1;
        }
        if(!holder.saveTXT(savepath.c_str())) {
            cout << "Failed saving." << endl;
            return -1;
        }
    }
    return 0;
}