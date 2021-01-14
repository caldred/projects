#include <iostream>
#include <cstdlib>
#include <cassert>
#include "Rational.h"

using namespace std;

Rational::Rational() : numerator(0), denominator(1) {}

Rational::Rational(int val) : numerator(val), denominator(1) {}

Rational::Rational(int numerator_in, int denominator_in)
  :numerator(numerator_in), denominator(denominator_in) {
  if (denominator == 0 && numerator > 0) numerator = 1;
  else if (denominator == 0 && numerator < 0) numerator = -1;
  else if (numerator == 0 && denominator != 0) denominator = 1;
  else {
    int GCD = 1;
    int first = 1;
    int second= 1;
    if (numerator > denominator) {
      first = denominator;
      second = numerator;
    }
    else {
      first = numerator;
      second = denominator;
    }
    int rem = 1;
    while (1) {
      rem = second % first;
      if (rem == 0) break;
      second = first;
      first = rem;
    }
    GCD = first;
    numerator = numerator/GCD;
    denominator = denominator/GCD;
  }
  if (denominator < 0) {
    denominator *= -1;
    numerator *= -1;
  }
}

int Rational::get_numerator() const {
  return numerator;
}

int Rational::get_denominator() const {
  return denominator;
}
  
// MODIFIES: output stream os
// EFFECTS: Prints out a rational number in reduced form
// without any spaces or newlines.
// Printing is done as
// follows. If the rational number is equivalent to an integer, just
// print the the integer value.
// Otherwise, print out numerator/denominator.
// For example, if numerator is 3 and denominator is 1, then print out 3.
// If numerator is 3 and denominator
// is 2, print out 3/2. If numerator is -4 and denominator is 3, print out -4/3.
// The function should also return the output stream os as its result
// so that << operations can be chained on a single line.
std::ostream& operator<<(std::ostream& os, const Rational& obj){
  if (obj.get_denominator() == 1)   os << obj.get_numerator();
  else os << obj.get_numerator() << "/" << obj.get_denominator();
  return os;
}

// EFFECTS: Returns a rational number equivalent to lhs + rhs.
// Note that (a/b + c/d) is algebraically equivalent to (ad+bc)/bd.
Rational operator+(const Rational &lhs, const Rational &rhs){
  int num =  lhs.get_numerator()*rhs.get_denominator() + lhs.get_denominator()*rhs.get_numerator();
  int den = lhs.get_denominator()*rhs.get_denominator();
  return Rational(num, den);
}

// EFFECTS: Returns a rational number equivalent to lhs - rhs.
//   Note that (a/b + c/d) is algebraically
// equivalent to (ad-bc)/bd.
Rational operator-(const Rational &lhs, const Rational &rhs){
  int num =  lhs.get_numerator()*rhs.get_denominator() - lhs.get_denominator()*rhs.get_numerator();
  int den = lhs.get_denominator()*rhs.get_denominator();
  return Rational(num, den);
}

// EFFECTS: Returns a rational number equivalent to lhs * rhs.
//   Note that (a/b * c/d) is algebraically
// equivalent to ac/bd.
Rational operator*(const Rational &lhs, const Rational &rhs){
  int num = rhs.get_numerator() * lhs.get_numerator();
  int den = rhs.get_denominator() * lhs.get_denominator();
  return Rational(num, den);
}

// EFFECTS: Returns a rational number equivalent to lhs / rhs.
//   Note that (a/b / c/d) is algebraically
// equivalent to ad/bc.
Rational operator/(const Rational &lhs, const Rational &rhs){
  int num = rhs.get_denominator() * lhs.get_numerator();
  int den = rhs.get_numerator() * lhs.get_denominator();
  return Rational(num, den);
}

// EFFECTS: Returns true if the two rational numbers are equal.  Otherwise,
//   returns false.
bool operator==(const Rational &lhs, const Rational &rhs){
  return (rhs.get_denominator() == lhs.get_denominator() && rhs.get_numerator() == lhs.get_numerator());
}
