// ##################################################################
// frac ... calculating with fractions
// ##################################################################

#ifndef FRAC_H
#define FRAC_H

#include "Defs.h"
#include "wx/string.h"

#ifdef HAVE_BOOST_RATIONAL_HPP
#include <boost/rational.hpp>

typedef boost::rational<long> frac;

inline wxString TowxString(frac f) {
  return wxString::Format(_T("%d/%d"),f.numerator(),f.denominator());
}


#else


#include <iostream>

class frac
{
private:
  long n, d;
public:
  frac() { n = 0; d = 1; }
  frac(long numerator, long denominator)
  {
    n = numerator;
    d = denominator;
  }

  long numerator() const (return n);
  long denominator() const (return d);
  frac& operator =(const frac& f);
  frac& operator +=(const frac& f);
  frac& operator -=(const frac& f);
  frac& operator *=(const frac& f);
  frac& operator /=(const frac& f);
  frac operator +(const frac s);
  frac operator -(const frac s);
  frac operator *(const frac s);
  frac operator /(const frac s);
  int operator <(const frac &f);
  int operator <=(const frac &f);
  int operator ==(const frac &f);
  int operator !=(const frac &f);
  int operator >=(const frac &f);
  int operator >(const frac &f);
  operator bool() { return n; }
  bool operator !() {return !n;}

  frac& operator =(const int &i);
  
  long gcd(long a, long b);
  
  friend STD_PRE::ostream& operator<<(STD_PRE::ostream& os, const frac f);

#ifdef WX
  operator wxString() {
    return wxString::Format(_T("%d/%d"),n,d);
  }
#endif
};

inline wxString TowxString(frac f) {
  return (wxString) f;
}

#endif /* HAVE_BOOST_RATIONAL_H */

#endif

