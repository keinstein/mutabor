// ##################################################################
// header file of GIS (GMN Intern Structur)
// ##################################################################

#ifndef GIS_H
#define GIS_H

#include "Defs.h"

// Stream und cout unterdr¸cken
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

extern mutString Tags[NTAGS];
extern mutString TagShorts[NTAGSHORTS];

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

int GetTagId(const mutString name, mutString &registered);

// ##################################################################
// GIS types

enum GisType { 
	GTNull, 
	GTUnknown, 
	GTSequenz, 
	GTSegment, 
	GTTag, 
	GTTagBegin,
	GTTagEnd, 
	GTNote, 
	GTParaInt, 
	GTParaReal, 
	GTParaStr, 
	GTComma
};

// basic type -------------------------------------------------------
class GisToken
{
	public:
		GisToken *Next;
		mutString Sep;
		GisToken(const mutString sep = mutEmptyString, GisToken *next = 0)
		{
			CHECKDUP(Sep, sep);
			Next = next;
		}
		~GisToken()
		{
			mutFreeString(Sep);
			if ( Next ) delete Next;
		}
		virtual GisType Type() const { return GTUnknown; }
		virtual GisToken *Copy() { return new GisToken(Sep, 0); }
#ifndef FOR_MUTWIN
		virtual void Stream(ostream &out, char sep);
		virtual void Echo() { cout << "?? "; }
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
		Contents = contents; Sep2 = mutEmptyString;
	 }
	 ~GisSequenz()
	 {
		mutFreeString(Sep2);
		if ( Contents ) delete Contents;
	 }
	 GisType Type() const { return GTSequenz; }
#ifndef FOR_MUTWIN
	 virtual void Stream(ostream &out, char sep);
	 virtual void Echo() { cout << "[ "; }
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
		Contents = contents; Sep2 = mutEmptyString;
	 }
	 
	 ~GisSegment()
	 {
		mutFreeString(Sep2);
		if ( Contents ) delete Contents;
	 }
	 
	 virtual GisType Type() const { return GTSegment; }
#ifndef FOR_MUTWIN
	 virtual void Stream(ostream &out, char sep);
   virtual void Echo() { cout << "{ "; }
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
			if ( !Id && Name ) mutFreeString(Name);
			if ( Para ) delete Para;
		}
		
		virtual GisType Type() const { return GTTag; }
		virtual GisToken *Copy() { return new GisTag(Name, CopyPara(Para), Sep, 0); }
		GisType GetParaType(int nr);  // counting from 1
		GisToken *GetPara(int nr);
#ifndef FOR_MUTWIN
		virtual void Stream(ostream &out, char sep);
		virtual void Echo() { cout << "Tag: " << Name <<" "; }
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
		
		virtual GisType Type() const { return GTTagBegin; }
		virtual GisToken *Copy() { return new GisTagBegin(Name, CopyPara(Para), Sep, 0); }
#ifndef FOR_MUTWIN
		virtual void Stream(ostream &out, char sep);
		virtual void Echo() { cout << "Tag: " << Name << "( "; }
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
	 virtual GisType Type() const { return GTTagEnd; }
#ifndef FOR_MUTWIN
	 virtual void Stream(ostream &out, char sep);
   virtual void Echo() { cout << ") "; }
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
#if 0
		CHECKDUP(Name, name);
		CHECKDUP(Accedentials, accedentials);
#endif
		Octave = octave;
		Duration = duration;
	 }
	 GisNote(int key, int octave, int acc, const mutString sep = mutEmptyString, GisToken *next = 0);
    int GetKey();
	 virtual GisType Type() const { return GTNote; }
#ifndef FOR_MUTWIN
	 virtual void Stream(ostream &out, mutChar sep);
	 virtual void Echo() { cout << "Note: " << Name << Accedentials << Octave <<" "; }
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
		
		virtual GisType Type() const { return GTParaInt; }
		virtual GisToken *Copy() { return new GisParaInt(i, Sep, 0); }
#ifndef FOR_MUTWIN
		virtual void Stream(ostream &out, mutChar sep);
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
		
		virtual GisType Type() const { return GTParaReal; }
		virtual GisToken *Copy() { return new GisParaReal(x, Sep, 0); }
#ifndef FOR_MUTWIN
		virtual void Stream(ostream &out, char sep);
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
		if ( s ) delete s;
	 }
	 virtual GisType Type() const { return GTParaStr; }
	 virtual GisToken *Copy() { return new GisParaStr(s, Sep, 0); }
#ifndef FOR_MUTWIN
	 virtual void Stream(ostream &out, mutChar sep);
#endif
};

// comma (in chord as separator) ------------------------------------
class GisComma : public GisToken
{
  public:
	 GisComma(const mutString sep = mutEmptyString, GisToken *next = 0)
		: GisToken(sep, next) { };
	 virtual GisType Type() const { return GTComma; }
#ifndef FOR_MUTWIN
	 virtual void Stream(ostream &out, mutChar sep);
	 virtual void Echo() { cout << ", "; }
#endif
};

// ##################################################################
// functions

GisType GetGisType(GisToken* token);

GisToken *GisParse(const mutString FileName);

#endif

