#include "Fraction.h"
#include<iostream>
#include<cassert>
#include<Eigen/Core>

using namespace std;

ostream& operator<< (ostream& o, const Fraction& c) {
    o << c.m_numerator << "/" << c.m_denominator;
    return o;
}

Fraction::Fraction() {
    m_numerator = 0;
    m_denominator = 1;
}

Fraction::Fraction(int numerator, int denominator) {
    assert(denominator != 0);
    int i = 2; 
    int max = sqrt(numerator < denominator ? numerator : denominator);
    while(i <= max) {
        if(numerator % i == 0 && denominator % i == 0) {
            numerator /= i;
            denominator /= i;
            max = sqrt(numerator < denominator ? numerator : denominator);
        } else {
            i++;
        }
    }
}