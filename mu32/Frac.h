// ##################################################################
// frac ... calculating with fractions
// ##################################################################

#include <iostream.h>

#ifndef FRAC_H
#define FRAC_H

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

	 friend ostream& operator<<(ostream& os, const frac f);
};

#endif
