/** \file 
 ********************************************************************
 * Fraction class for Mutabor
 *
 * Copyright:   (c) 2008 TU Dresden
 * \author  Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 
 * $Date: 2011/09/27 20:13:21 $
 * \version $Revision: 1.9 $
 * \license GPL
 *
 * $Log: Frac.h,v $
 * Revision 1.9  2011/09/27 20:13:21  keinstein
 * * Reworked route editing backend
 * * rewireing is done by RouteClass/GUIRoute now
 * * other classes forward most requests to this pair
 * * many bugfixes
 * * Version change: We are reaching beta phase now
 *
 * Revision 1.8  2011-02-20 22:35:55  keinstein
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

/* we guard a little bit complicated to ensure the references are set right
 */

#if (!defined(MU32_FRAC_H) && !defined(PRECOMPILE))	\
	|| (!defined(MU32_FRAC_H_PRECOMPILED))
#ifndef PRECOMPILE
#define MU32_FRAC_H
#endif

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

#include "Defs.h"

#ifndef MU32_FRAC_H_PRECOMPILED
#define MU32_FRAC_H_PRECOMPILED

// system headers which do seldom change

#include "wx/string.h"

#ifdef HAVE_BOOST_RATIONAL_HPP
#include <boost/rational.hpp>

typedef boost::rational<mutint64> frac;

inline wxString TowxString(frac f)
{
	return wxString::Format(_T("%ld/%ld"),f.numerator(),f.denominator());
}


#else


#include <iostream>

class frac
{

private:
	mutint64 n, d;

public:
	frac()
	{
		n = 0;
		d = 1;
	}

	frac(mutint64 integerval) 
	{
		n = integerval;
		d = 0;
	}
	
	frac(mutint64 numerator, mutint64 denominator)
	{
		n = numerator;
		d = denominator;
	}

	mutint64 numerator() const {return n;}

	mutint64 denominator() const {return d;}

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

	mutint64 gcd(mutint64 a, mutint64 b);

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

#endif // PRECOMPILED
#endif 


///\}
