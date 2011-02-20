/** \file 
 ********************************************************************
 * Description
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/mu32/Frac.h,v 1.8 2011/02/20 22:35:55 keinstein Exp $
 * Copyright:   (c) 2008 TU Dresden
 * \author  Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 
 * $Date: 2011/02/20 22:35:55 $
 * \version $Revision: 1.8 $
 * \license GPL
 *
 * $Log: Frac.h,v $
 * Revision 1.8  2011/02/20 22:35:55  keinstein
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

#ifndef FRAC_H
#define FRAC_H

#include "Defs.h"
#include "wx/string.h"

#ifdef HAVE_BOOST_RATIONAL_HPP
#include <boost/rational.hpp>

typedef boost::rational<long> frac;

inline wxString TowxString(frac f)
{
	return wxString::Format(_T("%ld/%ld"),f.numerator(),f.denominator());
}


#else


#include <iostream>

class frac
{

private:
	long n, d;

public:
	frac()
	{
		n = 0;
		d = 1;
	}

	frac(long integerval) 
	{
		n = integerval;
		d = 0;
	}
	
	frac(long numerator, long denominator)
	{
		n = numerator;
		d = denominator;
	}

	long numerator() const {return n;}

	long denominator() const {return d;}

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

	operator bool()
	{
		return n;
	}

	bool operator !()

	{
		return !n;
	}

	frac& operator =(const int &i);

	long gcd(long a, long b);

	friend STD_PRE::ostream& operator << (STD_PRE::ostream& os, const frac f);

#ifdef WX
	operator wxString() const
	{
		return wxString::Format(_T("%ld/%ld"),n,d);
	}

#endif
};

#ifdef WX
inline wxString TowxString(const frac &f)
{
	return (wxString) f;
}

inline STD_PRE::ostream& operator<<(STD_PRE::ostream& os, const frac f)
{
	return os << "(" << f.n << "/" << f.d << ")";
}
#endif

#endif /* HAVE_BOOST_RATIONAL_H */

#endif



///\}
