/** \file 
 ********************************************************************
 * Description
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/mu32/routing/gmn/GIS.h,v 1.3 2011/02/20 22:35:56 keinstein Exp $
 * Copyright:   (c) 2008 TU Dresden
 * \author  Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 
 * $Date: 2011/02/20 22:35:56 $
 * \version $Revision: 1.3 $
 * \license GPL
 *
 * $Log: GIS.h,v $
 * Revision 1.3  2011/02/20 22:35:56  keinstein
 * updated license information; some file headers have to be revised, though
 *
 *
 *
 ********************************************************************
 * \addtogroup route
 * \{
 ********************************************************************/
/// ##################################################################
// header file of GIS (GMN Intern Structur)
// ##################################################################

#ifndef GIS_H
#define GIS_H

#include "Defs.h"

// Stream und cout unterdrücken
#define FOR_MUTWIN

#ifndef FOR_MUTWIN
#include <iostream.h>
#endif

#include <string.h>
#include <stdlib.h>
#include "Frac.h"


#ifdef WX
#define CHECKDUP(target, source) target = source;
#else
#define CHECKDUP(target, source) \
  if ( source )	               \
	 target = mutStrdup(source);     \
  else                           \
	 target = 0

#endif

// regisered tags ---------------------------------------------------

#define NTAGS 52
#define NTAGSHORTS 6

extern const mutChar * Tags[NTAGS];

extern const mutChar * TagShorts[NTAGSHORTS];

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

#define NO_KEY -32000

// ------------------------------------------------------------------

int GetTagId(const mutString &name, mutString &registered);

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
	mutString Sep;

	GisToken(const mutString &sep = mutEmptyString, GisToken *next = 0)
	{
		CHECKDUP(Sep, sep);
		DEBUGLOG(other, _T("New Token: %s (was %s)"),Sep.c_str(),sep.c_str());
		Next = next;
	}

	virtual ~GisToken()

	{
		mutFreeString(Sep);

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
#ifdef WX
	operator wxString()
	{
		if (Next)
			return ToString() + ((wxString) *Next);
		else
			return ToString();
	}

	virtual wxString ToString()
	{
		return _T("GisToken: { Sep: '") + Sep + _T("' }\n");
	}

#endif
};

GisToken *CopyPara(GisToken *para);

// sequenz

class GisSequenz : public GisToken
{

public:
	mutString Sep2;
	GisToken *Contents;

	GisSequenz(GisToken *contents = 0, const mutString sep = mutEmptyString, GisToken *next = 0) :
			GisToken(sep, next)
	{
		Contents = contents;
		Sep2 = mutEmptyString;
	}

	~GisSequenz()

	{
		mutFreeString(Sep2);

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
#ifdef WX
	virtual wxString ToString()
	{
		return _T("GisSequenz: {\n") + GisToken::ToString() +
		       _T("Sep2: '") + Sep2 + _T("'; Contents: {\n") +
		       (Contents?((wxString) *Contents):wxString(_T(""))) + _T("}\n}\n");
	}

#endif
};

// segment

class GisSegment : public GisToken
{

public:
	mutString Sep2;

	GisToken *Contents;

	GisSegment(GisToken *contents = 0, const mutString sep = mutEmptyString, GisToken *next = 0) :
			GisToken(sep, next)
	{
		Contents = contents;
		Sep2 = mutEmptyString;
	}

	~GisSegment()

	{
		mutFreeString(Sep2);

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
#ifdef WX
	virtual wxString ToString()
	{
		return _T("GisSegment: {\n") + GisToken::ToString() +
		       _T("Sep2: '") + Sep2 + _T("'; Contents: {\n") +
		       (Contents?((wxString) *Contents):wxString(_T(""))) + _T("}\n}\n");
	}

#endif
};

// tag --------------------------------------------------------------

class GisTag : public GisToken
{

public:
	int Id;     // 0 ... no registered id
	mutString Name;
	GisToken *Para;

	GisTag(mutString name = mutEmptyString, GisToken *para = 0,
	       mutString sep = mutEmptyString, GisToken *next = 0)
			: GisToken(sep, next)
	{
		DEBUGLOG(other, _T("name.len %d"),name.Len());
		Id = GetTagId(name, Name);

		if ( Id == -1 ) {
			Id = 0;
			CHECKDUP(Name, name);
		}

		Para = para;
	}

	GisTag(int id, char shortForm, GisToken *para = 0, mutString sep = mutEmptyString, GisToken *next = 0)
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
		if ( !Id && Name.size() ) mutFreeString(Name);

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
#ifdef WX
	virtual wxString ToString()
	{
		return _T("GisTag: {\n") + GisToken::ToString() +
		       wxString::Format(_T("Id: %d\nName: '"),Id) + Name + _T("'; Para: {\n") +
		       (Para?((wxString) *Para):wxString(_T(""))) + _T("}\n}\n");
	}

#endif
};

// begin ranged tag -------------------------------------------------

class GisTagBegin : public GisTag
{

public:
	GisToken *End;

	GisTagBegin(mutString name = mutEmptyString, GisToken *para = 0,
	            mutString sep = mutEmptyString, GisToken *next = 0)
			: GisTag(name, para, sep, next)
	{
		End = 0;
	}

	GisTagBegin(int id, char shortForm, GisToken *para = 0,
	            mutString sep = mutEmptyString, GisToken *next = 0)
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
#ifdef WX
	virtual wxString ToString()
	{
		return _T("GisTagBegin: {\n") + GisTag::ToString() +
		       wxString::Format(_T("End: %p\n}\n"),End);
	}

#endif
};

// end ranged tag ---------------------------------------------------

class GisTagEnd : public GisToken
{

public:
	GisTagBegin *Begin;
	GisTagEnd(GisTagBegin *begin = 0, mutString sep = mutEmptyString, GisToken *next = 0)
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
#ifdef WX
	virtual wxString ToString()
	{
		return _T("GisTagEnd: {\n") + GisToken::ToString() +
		       wxString::Format(_T("Begin: %p\n}\n"),Begin);
	}

#endif
};

// note -------------------------------------------------------------

class GisNote : public GisToken
{

public:
	mutString Name;
	mutString Accedentials;
	int Octave;
	frac Duration;

	GisNote(const mutString &name = mutEmptyString, const mutString &accedentials = mutEmptyString, int octave = 0,
	        frac duration = frac(1,4), const mutString &sep = mutEmptyString, GisToken *next = 0)
			: GisToken(sep, next),Name(name),Accedentials(accedentials)
	{
		CHECKDUP(Name, name);
		CHECKDUP(Accedentials, accedentials);
		Octave = octave;
		Duration = duration;
	}

	GisNote(int key, int octave, int acc, const mutString sep = mutEmptyString, GisToken *next = 0);

	int GetKey();

	virtual GisType Type() const
	{
		return GTNote;
	}

#ifndef FOR_MUTWIN
	virtual void Stream(ostream &out, mutChar sep);

	virtual void Echo()
	{
		cout << "Note: " << Name << Accedentials << Octave <<" ";
	}

#endif
#ifdef WX
	virtual wxString ToString()
	{
		return _T("GisNote: {\n") + GisToken::ToString() +
		       wxString::Format(_T("Name: '%s'; Accedentials: '%s'; Octave: %d; Duration: "),
		                        Name.c_str(),Accedentials.c_str(),Octave) +
		       (TowxString(Duration)) + _T("\n}\n");
	}

#endif
};

// integer parameter ------------------------------------------------

class GisParaInt : public GisToken
{

public:
	int i;

	GisParaInt(int value = 0, mutString sep = mutEmptyString, GisToken *next = 0)
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
	virtual void Stream(ostream &out, mutChar sep);
#endif
#ifdef WX
	virtual wxString ToString()
	{
		return _T("GisParaInt: { ") + GisToken::ToString() +
		       wxString::Format(_T("i: %d }\n"),i);
	}

#endif
};

// real parameter ---------------------------------------------------

class GisParaReal : public GisToken
{

public:
	double x;

	GisParaReal(double value = 0, mutString sep = mutEmptyString, GisToken *next = 0)
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
#ifdef WX
	virtual wxString ToString()
	{
		return _T("GisParaReal: { ") + GisToken::ToString() +
		       wxString::Format(_T("x: %g }\n"),x);
	}

#endif
};

// string parameter -------------------------------------------------

class GisParaStr : public GisToken
{

public:
	mutString s;

	GisParaStr(const mutString value = mutEmptyString, mutString sep = mutEmptyString, GisToken *next = 0)
			: GisToken(sep, next)
	{
		CHECKDUP(s, value);
	}

	~GisParaStr()

	{
#ifdef WX
#else

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
	virtual void Stream(ostream &out, mutChar sep);
#endif
#ifdef WX
	virtual wxString ToString()
	{
		return _T("GisParaStr: { ") + GisToken::ToString() +
		       wxString::Format(_T("s: '%s' }\n"),s.c_str());
	}

#endif
};

// comma (in chord as separator) ------------------------------------

class GisComma : public GisToken
{

public:

	GisComma(const mutString sep = mutEmptyString, GisToken *next = 0)
			: GisToken(sep, next)
	{ };

	virtual GisType Type() const
	{
		return GTComma;
	}

#ifndef FOR_MUTWIN
	virtual void Stream(ostream &out, mutChar sep);

	virtual void Echo()
	{
		cout << ", ";
	}

#endif
#ifdef WX
	virtual wxString ToString()
	{
		return _T("GisComma: { ") + GisToken::ToString() +
		       _T(" }\n");
	}

#endif
};

// ##################################################################
// functions

GisType GetGisType(GisToken* token);

GisToken *GisParse(const mutString FileName);

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

extern int Tag(mutString tagName);

extern int TagParaInt(long i);

extern int TagParaReal(double x);

extern int TagParaStr(mutString s);

extern int Comma();

int Note(const mutString name, const mutString accedentials, int octave, frac duration);

#ifdef WX
wxString GISPrettyPrint(wxString s);

#endif


#endif


///\}
