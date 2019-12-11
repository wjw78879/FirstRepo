#ifndef FRACTION_H
#define FRACTION_H

#include<iostream>
#include<string>

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
    string str();

    Fraction operator+ (const Fraction& rhs);
    Fraction operator- (const Fraction& rhs);
    Fraction operator* (const Fraction& rhs);
    Fraction operator/ (const Fraction& rhs);
private:
    Fraction& reduction();

    bool m_positive;
    unsigned int m_numerator;
    unsigned int m_denominator;
};

unsigned int gcd(unsigned int m, unsigned int n);

#endif