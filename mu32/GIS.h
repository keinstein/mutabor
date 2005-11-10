// ##################################################################
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

#define CHECKDUP(target, source) \
  if ( source )	               \
	 target = strdup(source);     \
  else                           \
	 target = 0

// regisered tags ---------------------------------------------------

#define NTAGS 52
#define NTAGSHORTS 6

extern char *Tags[NTAGS];
extern char *TagShorts[NTAGSHORTS];

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

int GetTagId(const char *name, char **registered);

// ##################################################################
// GIS types

enum GisType { GTNull, GTUnknown, GTSequenz, GTSegment, GTTag, GTTagBegin,
  GTTagEnd, GTNote, GTParaInt, GTParaReal, GTParaStr, GTComma};

// basic type -------------------------------------------------------
class GisToken
{
  public:
	 GisToken *Next;
	 char *Sep;
	 GisToken(char *sep = 0, GisToken *next = 0)
	 {
		CHECKDUP(Sep, sep);
		Next = next;
	 }
	 ~GisToken()
	 {
		if ( Sep ) free(Sep);
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
	 char *Sep2;
	 GisToken *Contents;
	 GisSequenz(GisToken *contents = 0, char *sep = 0, GisToken *next = 0) :
		GisToken(sep, next)
	 {
		Contents = contents; Sep2 = 0;
	 }
	 ~GisSequenz()
	 {
		if ( Sep2 ) free(Sep2);
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
	 char *Sep2;
	 GisToken *Contents;
	 GisSegment(GisToken *contents = 0, char *sep = 0, GisToken *next = 0) :
		GisToken(sep, next)
	 {
		Contents = contents; Sep2 = 0;
	 }
	 ~GisSegment()
	 {
		if ( Sep2 ) free(Sep2);
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
	 char *Name;
	 GisToken *Para;
	 GisTag(char *name = 0, GisToken *para = 0, char *sep = 0, GisToken *next = 0)
		: GisToken(sep, next)
	 {
      Id = GetTagId(name, &Name);
		if ( Id == -1 )
		{
        Id = 0;
        CHECKDUP(Name, name);
      }
		Para = para;
	 }
	 GisTag(int id, char shortForm, GisToken *para = 0, char *sep = 0, GisToken *next = 0)
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
		if ( !Id && Name ) free(Name);
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
	 GisTagBegin(char *name = 0, GisToken *para = 0, char *sep = 0, GisToken *next = 0)
		: GisTag(name, para, sep, next)
	 {
		End = 0;
	 }
	 GisTagBegin(int id, char shortForm, GisToken *para = 0, char *sep = 0, GisToken *next = 0)
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
	 GisTagEnd(GisTagBegin *begin = 0, char *sep = 0, GisToken *next = 0)
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
	 char *Name;
	 char *Accedentials;
	 int Octave;
	 frac Duration;
	 GisNote(char *name = 0, char *accedentials = 0, int octave = 0,
		frac duration = frac(1,4), char *sep = 0, GisToken *next = 0)
		: GisToken(sep, next)
	 {
		CHECKDUP(Name, name);
		CHECKDUP(Accedentials, accedentials);
		Octave = octave;
		Duration = duration;
	 }
	 GisNote(int key, int octave, int acc, char *sep = 0, GisToken *next = 0);
    int GetKey();
	 virtual GisType Type() const { return GTNote; }
#ifndef FOR_MUTWIN
	 virtual void Stream(ostream &out, char sep);
	 virtual void Echo() { cout << "Note: " << Name << Accedentials << Octave <<" "; }
#endif
};

// integer parameter ------------------------------------------------
class GisParaInt : public GisToken
{
  public:
	 int i;
	 GisParaInt(int value = 0, char *sep = 0, GisToken *next = 0)
		: GisToken(sep, next)
	 {
		i = value;
	 }
	 virtual GisType Type() const { return GTParaInt; }
	 virtual GisToken *Copy() { return new GisParaInt(i, Sep, 0); }
#ifndef FOR_MUTWIN
	 virtual void Stream(ostream &out, char sep);
#endif
};

// real parameter ---------------------------------------------------
class GisParaReal : public GisToken
{
  public:
	 double x;
	 GisParaReal(double value = 0, char *sep = 0, GisToken *next = 0)
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
	 char *s;
	 GisParaStr(const char *value = 0, char *sep = 0, GisToken *next = 0)
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
	 virtual void Stream(ostream &out, char sep);
#endif
};

// comma (in chord as separator) ------------------------------------
class GisComma : public GisToken
{
  public:
	 GisComma(char *sep = 0, GisToken *next = 0)
		: GisToken(sep, next) { };
	 virtual GisType Type() const { return GTComma; }
#ifndef FOR_MUTWIN
	 virtual void Stream(ostream &out, char sep);
	 virtual void Echo() { cout << ", "; }
#endif
};

// ##################################################################
// functions

GisType GetGisType(GisToken* token);

GisToken *GisParse(const char *FileName);

#endif

