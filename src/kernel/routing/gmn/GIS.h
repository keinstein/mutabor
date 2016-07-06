/** \file               -*- C++ -*-
 ********************************************************************
 * header file of GIS (GMN Intern Structur)
 *
 * Copyright:   (c) 2008 Tobias Schlemmer
 * \author  Volker Abel
 * \author  Tobias Schlemmer <keinstein@users.sourceforge.net>
 * \license GPL
 *
 *    This program is free software; you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation; either version 2 of the License, or
 *    (at your option) any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this program; if not, write to the Free Software
 *    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *
 ********************************************************************
 * \addtogroup route
 * \{
 ********************************************************************/

/* we guard a little bit complicated to ensure the references are set right
 */

#if (!defined(MU32_ROUTING_GMN_GIS_H) && !defined(PRECOMPILE)) \
	|| (!defined(MU32_ROUTING_GMN_GIS_H_PRECOMPILED))
#ifndef PRECOMPILE
#define MU32_ROUTING_GMN_GIS_H
#endif

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

#include "src/kernel/Defs.h"
#include "src/kernel/Frac.h"

#ifndef MU32_ROUTING_GMN_GIS_H_PRECOMPILED
#define MU32_ROUTING_GMN_GIS_H_PRECOMPILED

// system headers which do seldom change


// Stream und cout unterdrücken
#define FOR_MUTWIN

#ifndef FOR_MUTWIN
#include <iostream.h>
#endif

#include <string.h>
#include <stdlib.h>


#define CHECKDUP(target, source) target = source;

// regisered tags ---------------------------------------------------

#define NTAGS 52
#define NTAGSHORTS 6

extern const char * Tags[NTAGS];

extern const char * TagShorts[NTAGSHORTS];

#define TTintens   1
#define TTslur     2
#define TTtempo   12
#define TTinstr   19
#define TTtie     20
#define TTstacc   21
#define TTaccent  22
#define TTten     23
#define TTkey     36
#define TToct     37
#define TTalter   50
#define TTmutabor 51

// ------------------------------------------------------------------0

#define GMN_NO_KEY -32000

// ------------------------------------------------------------------

int GetTagId(const std::string &name, std::string &registered);

// ##################################################################
// GIS types

enum GisType
{
        GTNull,
        GTUnknown,  // 1
        GTSequenz,  // 2
        GTSegment,
        GTTag,
        GTTagBegin, // 5
        GTTagEnd,
        GTNote,     // 7
        GTParaInt,
        GTParaReal,
        GTParaStr,  // 10
        GTComma
};

// basic type -------------------------------------------------------

class GisToken
{

public:
	GisToken *Next;
	std::string Sep;

	GisToken(const std::string &sep = "", GisToken *next = 0)
	{
		CHECKDUP(Sep, sep);
		DEBUGLOG(other, ("New Token: %s (was %s)"),Sep.c_str(),sep.c_str());
		Next = next;
	}

	virtual ~GisToken()

	{
		if ( Next ) delete Next;
	}

	virtual GisType Type() const
	{
		return GTUnknown;
	}

	virtual GisToken *Copy()

	{
		return new GisToken(Sep, 0);
	}

#ifndef FOR_MUTWIN
	virtual void Stream(ostream &out, char sep);
	virtual void Echo()
	{
		cout << "?? ";
	}

#endif

	virtual operator std::string() const
	{
		if (Next)
			return ToString() + ((std::string) *Next);
		else
			return ToString();
	}

	virtual std::string ToString() const
	{
		return ("GisToken: { Sep: '") + Sep + ("' }\n");
	}
};

GisToken *CopyPara(GisToken *para);

// sequenz

class GisSequenz : public GisToken
{

public:
	std::string Sep2;
	GisToken *Contents;

	GisSequenz(GisToken *contents = 0, const std::string sep = "", GisToken *next = 0) :
			GisToken(sep, next)
	{
		Contents = contents;
		Sep2 = "";
	}

	~GisSequenz()

	{
		if ( Contents ) delete Contents;
	}

	GisType Type() const
	{
		return GTSequenz;
	}

#ifndef FOR_MUTWIN
	virtual void Stream(ostream &out, char sep);

	virtual void Echo()
	{
		cout << "[ ";
	}

#endif
	virtual std::string ToString() const
	{
		return ("GisSequenz: {\n") + GisToken::ToString() +
		       ("Sep2: '") + Sep2 + ("'; Contents: {\n") +
			(Contents?((std::string) *Contents):std::string((""))) + ("}\n}\n");
	}

};

// segment

class GisSegment : public GisToken
{

public:
	std::string Sep2;

	GisToken *Contents;

	GisSegment(GisToken *contents = 0, const std::string sep = "", GisToken *next = 0) :
			GisToken(sep, next)
	{
		Contents = contents;
		Sep2 = "";
	}

	~GisSegment()

	{
		if ( Contents ) delete Contents;
	}

	virtual GisType Type() const
	{
		return GTSegment;
	}

#ifndef FOR_MUTWIN
	virtual void Stream(ostream &out, char sep);

	virtual void Echo()
	{
		cout << "{ ";
	}

#endif

	virtual std::string ToString() const
	{
		return ("GisSegment: {\n") + GisToken::ToString() +
		       ("Sep2: '") + Sep2 + ("'; Contents: {\n") +
			(Contents?((std::string) *Contents):std::string((""))) + ("}\n}\n");
	}

};

// tag --------------------------------------------------------------

class GisTag : public GisToken
{

public:
	int Id;     // 0 ... no registered id
	std::string Name;
	GisToken *Para;

	GisTag(std::string name = "", GisToken *para = 0,
	       std::string sep = "", GisToken *next = 0)
			: GisToken(sep, next)
	{
		DEBUGLOG(other, ("name.len %d"),(int)(name.length()));
		Id = GetTagId(name, Name);

		if ( Id == -1 ) {
			Id = 0;
			CHECKDUP(Name, name);
		}

		Para = para;
	}

	GisTag(int id, char shortForm, GisToken *para = 0, std::string sep = "", GisToken *next = 0)
			: GisToken(sep, next)
	{
		Id = id;

		if ( shortForm )
			Name = TagShorts[Id];
		else
			Name = Tags[Id];

		Para = para;
	}

	~GisTag()
	{
		if ( Para ) delete Para;
	}

	virtual GisType Type() const
	{
		return GTTag;
	}

	virtual GisToken *Copy()

	{
		return new GisTag(Name, CopyPara(Para), Sep, 0);
	}

	GisType GetParaType(int nr);  // counting from 1
	GisToken *GetPara(int nr);
#ifndef FOR_MUTWIN
	virtual void Stream(ostream &out, char sep);
	virtual void Echo()
	{
		cout << "Tag: " << Name <<" ";
	}

#endif

	virtual std::string ToString() const
	{
		return ("GisTag: {\n") + GisToken::ToString() +
			boost::str(boost::format("Id: %d\nName: '") % Id) + Name + ("'; Para: {\n") +
		       (Para?((std::string) *Para):std::string((""))) + ("}\n}\n");
	}
};

// begin ranged tag -------------------------------------------------

class GisTagBegin : public GisTag
{

public:
	GisToken *End;

	GisTagBegin(std::string name = "", GisToken *para = 0,
	            std::string sep = "", GisToken *next = 0)
			: GisTag(name, para, sep, next)
	{
		End = 0;
	}

	GisTagBegin(int id, char shortForm, GisToken *para = 0,
	            std::string sep = "", GisToken *next = 0)
			: GisTag(id, shortForm, para, sep, next)
	{
		End = 0;
	}

	virtual GisType Type() const
	{
		return GTTagBegin;
	}

	virtual GisToken *Copy()

	{
		return new GisTagBegin(Name, CopyPara(Para), Sep, 0);
	}

#ifndef FOR_MUTWIN
	virtual void Stream(ostream &out, char sep);
	virtual void Echo()
	{
		cout << "Tag: " << Name << "( ";
	}

#endif
	virtual std::string ToString() const
	{
		return ("GisTagBegin: {\n") + GisTag::ToString() +
			boost::str(boost::format("End: %p\n}\n")%(void *)End);
	}
};

// end ranged tag ---------------------------------------------------

class GisTagEnd : public GisToken
{

public:
	GisTagBegin *Begin;
	GisTagEnd(GisTagBegin *begin = 0, std::string sep = "", GisToken *next = 0)
			: GisToken(sep, next)
	{
		Begin = begin;
	}

	virtual GisType Type() const
	{
		return GTTagEnd;
	}

#ifndef FOR_MUTWIN
	virtual void Stream(ostream &out, char sep);

	virtual void Echo()
	{
		cout << ") ";
	}

#endif

	virtual std::string ToString() const
	{
		return ("GisTagEnd: {\n") + GisToken::ToString() +
			boost::str(boost::format("Begin: %p\n}\n") % (void *)Begin);
	}

};

// note -------------------------------------------------------------

class GisNote : public GisToken
{

public:
	std::string Name;
	std::string Accedentials;
	int Octave;
	mutabor::frac Duration;

	GisNote(const std::string &name = "",
		const std::string &accedentials = "",
		int octave = 0,
		const mutabor::frac & duration = mutabor::frac(1,4),
		const std::string &sep = "",
		GisToken *next = 0)
			: GisToken(sep, next),
		Name(name),
		Accedentials(accedentials),
		Octave(octave),
		Duration(duration)
	{
		CHECKDUP(Name, name);
		CHECKDUP(Accedentials, accedentials);
	}

	GisNote(int key,
		int octave,
		int acc,
		const std::string & sep = "",
		GisToken *next = 0);

	int GetKey();

	virtual GisType Type() const
	{
		return GTNote;
	}

#ifndef FOR_MUTWIN
	virtual void Stream(ostream &out, char sep);

	virtual void Echo()
	{
		cout << "Note: " << Name << Accedentials << Octave <<" ";
	}

#endif

	virtual std::string ToString() const
	{
		return ("GisNote: {\n") + GisToken::ToString() +
			boost::str(boost::format("Name: '%s'; Accedentials: '%s'; Octave: %d; Duration: ")
				   % Name.c_str() % Accedentials.c_str() % Octave) +
			mutabor::str(Duration) + ("\n}\n");
	}

};

// integer parameter ------------------------------------------------

class GisParaInt : public GisToken
{

public:
	int i;

	GisParaInt(int value = 0, std::string sep = "", GisToken *next = 0)
			: GisToken(sep, next)
	{
		i = value;
	}

	virtual GisType Type() const
	{
		return GTParaInt;
	}

	virtual GisToken *Copy()

	{
		return new GisParaInt(i, Sep, 0);
	}

#ifndef FOR_MUTWIN
	virtual void Stream(ostream &out, char sep);
#endif
	virtual std::string ToString() const
	{
		return ("GisParaInt: { ") + (GisToken::ToString()) +
			boost::str(boost::format("i: %d }\n") % i);
	}

};

// real parameter ---------------------------------------------------

class GisParaReal : public GisToken
{

public:
	double x;

	GisParaReal(double value = 0, std::string sep = "", GisToken *next = 0)
			: GisToken(sep, next)
	{
		x = value;
	}

	virtual GisType Type() const
	{
		return GTParaReal;
	}

	virtual GisToken *Copy()

	{
		return new GisParaReal(x, Sep, 0);
	}

#ifndef FOR_MUTWIN
	virtual void Stream(ostream &out, char sep);
#endif

	virtual std::string ToString() const
	{
		return ("GisParaReal: { ") + GisToken::ToString() +
			boost::str(boost::format("x: %g }\n") % x);
	}

};

// string parameter -------------------------------------------------

class GisParaStr : public GisToken
{

public:
	std::string s;

	GisParaStr(const std::string value = "", std::string sep = "", GisToken *next = 0)
			: GisToken(sep, next)
	{
		CHECKDUP(s, value);
	}

	~GisParaStr()

	{
#if 0
		if ( s ) delete s;
#endif
	}

	virtual GisType Type() const
	{
		return GTParaStr;
	}

	virtual GisToken *Copy()

	{
		return new GisParaStr(s, Sep, 0);
	}

#ifndef FOR_MUTWIN
	virtual void Stream(ostream &out, char sep);
#endif
	virtual std::string ToString() const
	{
		return ("GisParaStr: { ") + GisToken::ToString() +
			boost::str(boost::format("s: '%s' }\n")%s.c_str());
	}
};

// comma (in chord as separator) ------------------------------------

class GisComma : public GisToken
{

public:

	GisComma(const std::string sep = "", GisToken *next = 0)
			: GisToken(sep, next)
	{ };

	virtual GisType Type() const
	{
		return GTComma;
	}

#ifndef FOR_MUTWIN
	virtual void Stream(ostream &out, char sep);

	virtual void Echo()
	{
		cout << ", ";
	}

#endif
	virtual std::string ToString() const
	{
		return ("GisComma: { ") + GisToken::ToString() +
		       (" }\n");
	}

};

// ##################################################################
// functions

GisType GetGisType(GisToken* token);

GisToken *GisParse(const std::string FileName);

extern int StartSep();  // at the beginning, to get comments infront of the first token

extern int BeginSegment();

extern int EndSegment();

extern int BeginSequenz();

extern int EndSequenz();

extern int BeginParameter();

extern int EndParameter();

extern int BeginRange();

extern int EndRange();

extern int NextSequenz();

extern int Tag(const std::string & tagName);

extern int TagParaInt(long i);

extern int TagParaReal(double x);

extern int TagParaStr(const std::string &s);

extern int Comma();

int Note(const std::string & name,
	 const std::string & accedentials,
	 int octave,
	 const mutabor::frac & duration);

std::string GISPrettyPrint(std::string s);



#endif /* precompiled */
#endif


///\}
