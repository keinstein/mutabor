/** \file 
 ********************************************************************
 * Description
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/src/kernel/Frac.cpp,v 1.6 2011/02/20 22:35:55 keinstein Exp $
 * Copyright:   (c) 2008 TU Dresden
 * \author  Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 
 * $Date: 2011/02/20 22:35:55 $
 * \version $Revision: 1.6 $
 * \license GPL
 *
 * $Log: Frac.cpp,v $
 * Revision 1.6  2011/02/20 22:35:55  keinstein
 * updated license information; some file headers have to be revised, though
 *
 * Revision 1.2  2010-11-21 13:15:51  keinstein
 * merged experimental_tobias
 *
 * Revision 1.1.2.1  2010-01-11 10:12:59  keinstein
 * added some .cvsignore files
 *
 *
 ********************************************************************
 * \addtogroup kernel
 * \{
 ********************************************************************/
// ##################################################################
// frac ... calculating with fractions
// ##################################################################

#include "Frac.h"

#ifndef HAVE_BOOST_RATIONAL_HPP


long absLong(const long x)
{
	if ( x >= 0 ) return x;
	else return -x;
}

frac& frac::operator =(const frac& f)

{
	n = f.n;
	d = f.d;
	return *this;
}

frac& frac::operator +=(const frac& f)

{
	if ( !d  || !f.d ) {
		n = 1;
		d = 0;
	} else {
		long cd = d * (f.d / gcd(d, f.d));
		long cn = n * (cd/d)+ f.n * (cd/f.d);
		long gd = gcd(cd, cn);

		if ( gd != 1 ) {
			cn /= gd;
			cd /= gd;
		}

		n = cn;

		d = cd;
	}

	return *this;
}

frac& frac::operator -=(const frac& f)

{
	if ( !d  || !f.d ) {
		n = 1;
		d = 0;
	} else {
		long cd = d * (f.d / gcd(d, f.d));
		long cn = n * (cd/d) - f.n * (cd/f.d);
		long gd = gcd(cd, cn);

		if ( gd != 1 ) {
			cn /= gd;
			cd /= gd;
		}

		n = cn;

		d = cd;
	}

	return *this;
}

frac& frac::operator *=(const frac& f)

{
	n *= f.n;
	d *= f.d;
	long gd = gcd(n, d);

	if ( gd != 1 ) {
		n /= gd;
		d /= gd;
	}

	return *this;
}

frac& frac::operator /=(const frac& f)

{
	n *= f.d;
	d *= f.n;
	long gd = gcd(n, d);

	if ( gd != 1 ) {
		n /= gd;
		d /= gd;
	}

	return *this;
}

frac frac::operator +(const frac s)

{
	if ( !d  || !s.d ) return frac(1,0);

	long cd = d * (s.d / gcd(d, s.d));

	long cn = n * (cd/d)+ s.n * (cd/s.d);

//  long cd = gcd(d, s.d);
//  long cn = n * (s.d/cd)+ s.n * (d/cd);
	long gd = gcd(cd, cn);

	if ( gd != 1 ) {
		cn /= gd;
		cd /= gd;
	}

	return frac(cn, cd);
}

frac frac::operator -(const frac s)

{
	if ( !d  || !s.d ) return frac(1,0);

	long cd = d * (s.d / gcd(d, s.d));

	long cn = n * (cd/d)- s.n * (cd/s.d);

	long gd = gcd(cd, cn);

	if ( gd != 1 ) {
		cn /= gd;
		cd /= gd;
	}

	return frac(cn, cd);
}

frac frac::operator *(const frac s)

{
	long cn = n * s.n;
	long cd = d * s.d;
	long gd = gcd(cd, cn);

	if ( gd != 1 ) {
		cn /= gd;
		cd /= gd;
	}

	return frac(cn, cd);
}

frac frac::operator /(const frac s)

{
	long cn = n * s.d;
	long cd = d * s.n;
	long gd = gcd(cd, cn);

	if ( gd != 1 ) {
		cn /= gd;
		cd /= gd;
	}

	return frac(cn, cd);
}

int frac::operator <(const frac &f)

{
	char s = 0;

	if ( d < 0 ) s++;

	if ( f.d < 0 ) s++;

	if ( s == 1 )
		return n * f.d > d * f.n;
	else
		return n * f.d < d * f.n;
}

int frac::operator <=(const frac &f)

{
	char s = 0;

	if ( d < 0 ) s++;

	if ( f.d < 0 ) s++;

	if ( s == 1 )
		return n * f.d >= d * f.n;
	else
		return n * f.d <= d * f.n;
}

int frac::operator ==(const frac &f)

{
	return d * f.n == n * f.d;
}


int frac::operator !=(const frac &f)

{
	return d * f.n != n * f.d;
}

int frac::operator >=(const frac &f)

{
	char s = 0;

	if ( d < 0 ) s++;

	if ( f.d < 0 ) s++;

	if ( s == 1 )
		return n * f.d <= d * f.n;
	else
		return n * f.d >= d * f.n;
}

int frac::operator >(const frac &f)

{
	char s = 0;

	if ( d < 0 ) s++;

	if ( f.d < 0 ) s++;

	if ( s == 1 )
		return n * f.d < d * f.n;
	else
		return n * f.d > d * f.n;
}

frac& frac::operator =(const int &i)

{
	n = i;
	d = 1;
	return *this;
}



long frac::gcd(long a, long b)

{
	long p, q, r = 1;
	a = absLong(a);
	b = absLong(b);

	if ( a > b ) {
		p = a;
		q = b;
	} else {
		p = b;
		q = a;
	}

	if ( !q ) return 1;

	while ( r ) {
		r = p % q;
		p = q;
		q = r;
	}

	return p;
}


#endif


///\}