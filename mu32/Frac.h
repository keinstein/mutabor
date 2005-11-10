// ##################################################################
// frac ... calculating with fractions
// ##################################################################

#ifndef FRAC_H
#define FRAC_H

#include <iostream>
#include "Defs.h"

class frac
{
  public:
	 long n, d;
	 frac() { n = 0; d = 1; }
	 frac(long nominator, long denominator)
	 {
		n = nominator;
		d = denominator;
	 }
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

	 frac& operator =(const int &i);

	 long gcd(long a, long b);

	 friend STD_PRE::ostream& operator<<(STD_PRE::ostream& os, const frac f);
};

#endif

