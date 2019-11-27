#ifndef FRACTION_H
#define FRACTION_H

#include<iostream>

using namespace std;

class Fraction {
    friend ostream& operator<< (ostream& o, const Fraction& c);
public:
    Fraction();
    Fraction(int numerator, int denominator);
    Fraction(int integer);
    Fraction(const Fraction& other);

    Fraction reciprocal();
    double decimals();

    Fraction operator+ (const Fraction& rhs);
    Fraction operator- (const Fraction& rhs);
    Fraction operator* (const Fraction& rhs);
    Fraction operator/ (const Fraction& rhs);
private:
    int m_numerator;
    int m_denominator;
};

#endif