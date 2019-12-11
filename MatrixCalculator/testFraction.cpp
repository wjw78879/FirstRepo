#include "Fraction.h"
#include<iostream>

int main() {
    int num = 0, deno = 0;
    cin >> num >> deno;
    Fraction f1(num, deno);
    std::cout << f1 << std::endl;
    return 0;
}