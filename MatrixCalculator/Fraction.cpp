#include "Fraction.h"
#include<iostream>
#include<cassert>
#include<math.h>

using namespace std;

unsigned int gcd(unsigned int m, unsigned int n) {
    unsigned int rem;
    while(n > 0) {
        rem = m % n;
        m = n;
        n = rem;
    }
    return m;
}

ostream& operator<< (ostream& o, const Fraction& c) {
    if(!c.m_positive)o << "-";
    if(c.m_denominator == 1)o << c.m_numerator;
    else o << c.m_numerator << "/" << c.m_denominator;
    return o;
}

Fraction::Fraction() {
    m_numerator = 0;
    m_denominator = 1;
}

Fraction::Fraction(int numerator, int denominator) {
    assert(denominator != 0);
    if(numerator * denominator >= 0)m_positive = true;
    else m_positive = false;
    if(numerator < 0)numerator *= -1;
    if(denominator < 0)denominator *= -1;
    m_numerator = numerator;
    m_denominator = denominator;
    this->reduction();
}

Fraction& Fraction::reduction() {
    unsigned int n = gcd(m_numerator, m_denominator);
    while(n > 1) {
        m_numerator /= n;
        m_denominator /= n;
        n = gcd(m_numerator, m_denominator);
    }
    return (*this);
}