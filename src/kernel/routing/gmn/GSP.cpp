/** \file 
 ********************************************************************
 * Description
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/src/kernel/routing/gmn/GSP.cpp,v 1.6 2011/11/02 14:31:57 keinstein Exp $
 * Copyright:   (c) 2008 TU Dresden
 * \author  Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 
 * $Date: 2011/11/02 14:31:57 $
 * \version $Revision: 1.6 $
 * \license GPL
 *
 * $Log: GSP.cpp,v $
 * Revision 1.6  2011/11/02 14:31:57  keinstein
 * fix some errors crashing Mutabor on Windows
 *
 * Revision 1.5  2011-09-27 20:13:22  keinstein
 * * Reworked route editing backend
 * * rewireing is done by RouteClass/GUIRoute now
 * * other classes forward most requests to this pair
 * * many bugfixes
 * * Version change: We are reaching beta phase now
 *
 * Revision 1.4  2011-02-20 22:35:56  keinstein
 * updated license information; some file headers have to be revised, though
 *
 *
 *
 ********************************************************************
 * \addtogroup route
 * \{
 ********************************************************************/
// ##################################################################
// main file of gsp (GMN Soft Parser)
// ##################################################################

#include "GSP.h"
#include "GSP_File.h"
#ifdef WX
#include "wx/wxchar.h"
#else
#include <string.h>
#endif

// global data

int GspCurrentLineNr;    // curent line parser deals with
int GspErrorLineNr;      // line of occured error
int GspErrorPos;         // column of occured error in line
mutString GspErrorLine;      // text of error line
int GspError;            // error id

// last saved position (before an error occurs)
int PossibleErrorLineNr;
int PossibleErrorPos;
mutString PossibleErrorLine; //[GSP_MAX_LINE];

#ifdef WX
mutString Sep = mutEmptyString;
inline size_t SepPos()
{
	size_t a =  (Sep.Len());
	return a;
}

#define SepPos SepPos()
#else
char Sep[GSP_MAX_SEP];
int  SepPos;
#endif

// local data
char ParaMode;
char Komma;
int  NumberLength;
#ifdef WX
mutString Brackets = mutEmptyString;
#define BracketDeep \
  (Brackets.Len())
#else
int  BracketDeep;
char Brackets[200];
#endif
char LastTag;
// last note

static int octave;

static mutString accedentials /*[GSP_MAX_LINE]*/;

static frac duration;

#define NEW_LINE mutT("\n")
mutChar SepChars[] = mutT(" \t\r\n");

mutChar DelimitChars[] = mutT("{}[]()");

#define uchar unsigned char

// ##################################################################
// Work with strings

#ifdef WX
inline void AddStr(mutString & Target, int Pos, const mutString& Source)
{
	mutUnused(Pos);
	DEBUGLOG2(other,_T("%s + %s"), Target.c_str(), Source.c_str());
	Target += Source;
	DEBUGLOG2(other,_T("=%s"), Target.c_str());
}

inline int CharIn(mutChar c, const mutChar * s)

{
	DEBUGLOG2(other,_T("'%c' is in '%s' at position %d, returning %d"),
	          c, s, mutStrChr(s, c), mutStrChr(s, c) != NULL);
	return mutStrChr(s, c) != NULL;
}

inline int IsLetter(mutChar c)

{
	return ((mutT('a') <= c) && (c <= mutT('z'))) ||
	       ((mutT('A') <= c) && (c <= mutT('Z'))) ||
	       ( c == mutT('_') );
}

/*
inline int IsNumber(mutChar c)
{
  return (mutIsDigit(c));
}
*/
#else
void AddStr(char *Target, int &Pos, char *Source)
{
	for (int i = 0; Source[i]; i++) {
		Target[Pos++] = Source[i];
	}

	Target[Pos] = 0;
}

int CharIn(mutChar c, const mutString s)
{
	return mutStrChr(s, c) != 0;
}

int IsLetter(mutChar c)

{
	return ((mutT('a') <= c) && (c <= mutT('z'))) ||
	       ((mutT('A') <= c) && (c <= mutT('Z'))) ||
	       ( c == mutT('_') );
}

int IsNumber(mutChar c)
{
	return (mutT('0') <= c) && (c <= mutT('9'));
}

#endif
// ##################################################################
// dealing with errors

// produces an error at CurrentPos
int DoError(int nr, int pos = -1)
{
	if ( GspError ) return GspError;

	GspError = nr;

	GspErrorLineNr = GspCurrentLineNr;

	if ( pos == -1 )
		GspErrorPos = CurrentPos;
	else
		GspErrorPos = pos;

	GspErrorLine = CurrentLine;

	return nr;
}

// produces an error at the last saved position
int CheckError(int nr)
{
	if ( !nr ) return 0; // no error

	if ( GspError ) return GspError;

	GspError = nr;

	GspErrorLineNr = PossibleErrorLineNr;

	GspErrorPos = PossibleErrorPos;

	GspErrorLine = PossibleErrorLine;

	return nr;
}

// save current position (for CheckError)
void SavePos()
{
	PossibleErrorLineNr = GspCurrentLineNr;
	PossibleErrorPos = CurrentPos;
	mutCopyIntoString(PossibleErrorLine, CurrentLine);
}

// ##################################################################
// reading separator chars

#define CHAR0 CurrentLine[CurrentPos]
#define CHAR1 CurrentLine[CurrentPos+1]
inline wxString & takesep()
{
	Sep += CurrentLine[CurrentPos++];
	DEBUGLOG2(other,_T("New Sep: %s"), Sep.c_str());
	return Sep;
}

#define TAKESEP takesep()


// reading separator string
int GetSep()
{
#ifdef WX
	Sep = mutEmptyString;
#else
	SepPos = 0;
#endif
	Komma = 0;
	int RemDeep = 0;
	int RemLine = 0;

	while ( !Eof && !GspError ) {
#ifdef WX
		DEBUGLOG2(other,_T("%d >= %d? Sep.Len=%d"),CurrentPos,CurrentLine.Len(),Sep.Len());
		DEBUGLOG2(other,_T("%s"),CurrentLine.c_str());

		if (CurrentPos >= CurrentLine.Len())
#else
		mutChar c = CHAR0;

		if ( !c ) // new Line
#endif
		{

			if ( ReadNewLine() )
			{
				DoError(32);
#ifdef WX
				Sep = Sep.Left(1);
				DEBUGLOG2(other,_T("Returning 1 at with (%d) '%s'"),
				          SepPos, Sep.c_str());
				return SepPos;
#else
				return ( SepPos = 1 );
#endif
			}

			RemLine = 0;

			if ( GspCurrentLineNr != 1 )
				AddStr(Sep, SepPos, NEW_LINE);

			continue;
		}

#ifdef WX
		mutChar c = CHAR0;

#endif

		if ( c == mutT('(') && CHAR1 == mutT('*') )  // comment start
		{
			TAKESEP;
			TAKESEP;
			RemDeep++;
			continue;
		}

		if ( RemDeep ) // during a comment
		{

			if ( c == mutT('*') && CHAR1 == mutT(')') )
			{
				TAKESEP;
				TAKESEP;
				RemDeep--;
			} else
				TAKESEP;

			continue;
		}

		if ( RemLine ) {
			TAKESEP;
			continue;
		}

		if ( c == mutT('%') ) // line comment
		{
			RemLine = 1;
			continue;
		}

		if ( CharIn(c, SepChars) ) // separating chars
		{
			TAKESEP;
			continue;
		}

		if ( c == mutT(',') && ParaMode ) // sequenz separator
		{
			TAKESEP;
			Komma = 1;
			continue;
		}

		break;
	}

	DEBUGLOG2(other,_T("Returning with (%d) '%s'"),SepPos,Sep.c_str());

#ifndef WX
	Sep[SepPos] = 0;
#endif
	return SepPos;
}

// ##################################################################
// subfunctions of parsing process

bool minus;

// reads an integer
long ReadLong(int SignAllowed)
{
	long a = 0;
	NumberLength = 0;
	minus = false;

	if ( SignAllowed ) {
		DEBUGLOG2(other,_T("Sign char %c?"), CHAR0);

		if ( CHAR0 == mutT('+') ) CurrentPos++;
		else if ( CHAR0 == mutT('-') ) {
			CurrentPos++;
			minus = true;
		}
	}

	GetSep();

	while ( mutIsdigit(CHAR0) && !SepPos ) {
		DEBUGLOG2(other,_T("Number char %c? (a=%d)"), CHAR0, a);
		a = a*10 + (CurrentLine[CurrentPos++]-mutT('0'));
		NumberLength++;
		GetSep();
	}

	if ( minus ) return -a;

	return a;
}

// reads a number parameter (int or real)
int ReadParaNumber()
{
	long a = ReadLong(1);

	if ( SepPos || CHAR0 != mutT('.') ) // integer
		return CheckError(TagParaInt(a));

	// real
	CurrentPos++; // comma position

	GetSep();

	mutChar minus1 = minus;

	double r = (double)a;

	if ( SepPos ) // real without fraction part
		return CheckError(TagParaReal(r));

	float b = (double) ReadLong(0);

	for (int i = 1; i <= NumberLength; i++)
		b = b / 10;

	if ( minus1 ) b = -b;

	return CheckError(TagParaReal(r+b));
}

// reads a parameter string
int ReadParaStr()
{
#ifdef WX
	mutString s /*[GSP_MAX_LINE]*/ = mutT("");
#else
	mutChar s[GSP_MAX_LINE] = "";
#endif
	int i = 0;
	CurrentPos++;

	while ( (CHAR0 != mutT('"') || CHAR1 == mutT('"')) && !Eof ) {
		if ( !CHAR0 ) // new Line
		{
			ReadNewLine();
			AddStr(s, i, NEW_LINE);
			continue;
		}
		if ( CHAR0 == mutT('"') ) CurrentPos++;

#ifdef WX
		s += CurrentLine[CurrentPos++];

#else
		s[i++] = CurrentLine[CurrentPos++];

#endif
	}

	if ( CHAR0 == mutT('"') ) CurrentPos++;

#ifndef WX
	s[i] = 0;

#endif
	GetSep();

	return CheckError(TagParaStr(s));
}

// reads a tag
int ReadTag()
{
	mutString Name/* [GSP_MAX_LINE] */ = mutT("");
	mutChar i = 0;
	LastTag = 2; // to have an indicator, wether the last token was a tag
	CurrentPos++;
	GetSep();
#ifdef WX
	i = CurrentPos;
#endif

	while ( IsLetter(CHAR0) && !SepPos ) {
#ifdef WX
		CurrentPos++;
#else
		Name[i++] = CurrentLine[CurrentPos++];
#endif
		GetSep();
	}

#ifdef WX
	Name = CurrentLine (i,CurrentPos-i);

#else
	Name[i] = 0;

#endif
	if ( !GspError ) CheckError(Tag(Name));

	if ( CHAR0 == mutT('<') ) {
		CurrentPos++;
		GetSep();

		if ( !GspError ) CheckError(BeginParameter());

		ParaMode = 1;
	}

	if ( CHAR0 == mutT('>') ) {
		CurrentPos++;
		GetSep();

		if ( !GspError ) CheckError(EndParameter());

		ParaMode = 0;
	}

	return GspError;
}

// reads a note
int ReadNote()
{
	mutChar i = 0;
#ifdef WX
	mutString Name /* [GSP_MAX_LINE]*/ = wxEmptyString;
	accedentials = wxEmptyString;
#else
	mutChar Name[GSP_MAX_LINE] = mutT("");
	accedentials[0] = 0;
#endif

	GetSep();

#ifdef WX

	for (i = CurrentPos; IsLetter(CHAR0) && !SepPos; CurrentPos++)
		GetSep();

	Name = CurrentLine(i,CurrentPos-i);

	GetSep();

#else
	while ( IsLetter(CHAR0) && !SepPos ) {
		Name[i++] = CurrentLine[CurrentPos++];
		GetSep();
		mutString Name /* [GSP_MAX_LINE]*/ = mutT("");

	}

	Name[i] = 0;

#endif

	DEBUGLOG2(other,_T("SepPos: %d"),SepPos);

	if ( SepPos )
		return CheckError(Note(Name, accedentials, octave, duration));

	i = 0; // accedentials

	while ( CharIn(CHAR0, mutT("#&")) && !SepPos ) {
#ifdef WX
		accedentials += CurrentLine[CurrentPos++];
#else
		accedentials[i++] = CurrentLine[CurrentPos++];
#endif
		GetSep();
	}

#ifndef WX
	accedentials[i] = 0;

#endif

	DEBUGLOG2(other,_T("SepPos: %d"),SepPos);

	if ( SepPos )
		return CheckError(Note(Name, accedentials, octave, duration));

	size_t cp = CurrentPos; // octave

	int oct = ReadLong(1);

	if ( cp != CurrentPos ) octave = oct;

	if ( SepPos || !CharIn(CHAR0, mutT("/*.")) )
		return CheckError(Note(Name, accedentials, octave, duration));

	int DurOk = 0; // duration

	duration = frac(1,1);

	if ( CHAR0 == mutT('*') ) {
		DurOk = 1;
		CurrentPos++;
		duration = frac(ReadLong(0));

		if ( !duration )
			return DoError(21); // error: nominator expected
	}

	if ( SepPos || !CharIn(CHAR0, mutT("/.")) )
		return CheckError(Note(Name, accedentials, octave, duration));

	if ( CHAR0 == mutT('/') ) {
		DurOk = 1;
		CurrentPos++;
		duration /= ReadLong(0);

		if ( !duration )
			return DoError(22); // error: denominator expected
	}

	if ( SepPos )
		return CheckError(Note(Name, accedentials, octave, duration));

	if ( CHAR0 == mutT('.') && !DurOk )
		return DoError(23); // error: dotting wihtout duration

	frac add = duration;

	while ( CHAR0 == mutT('.') && !SepPos ) {
		add *= frac(1,2);

		duration += add;

		CurrentPos++;

		GetSep();
	}

	return CheckError(Note(Name, accedentials, octave, duration));
}

// ##################################################################
// parsing process

// the parsing loop
int DoParse()
{
	ParaMode = 0;

	while ( !Eof ) {
		mutChar c = CHAR0;
		SavePos();
		Komma = 0;

		if ( ParaMode ) {
			if ( mutIsdigit(c) || ( c == mutT('+')) || ( c == mutT('-')) ) // number parameter
			{

				if ( ReadParaNumber() ) return GspError;
			} else if ( c == mutT('"') ) // string parameter
			{

				if ( ReadParaStr() ) return GspError;
			} else // wrong parameter
			{
				return DoError(10);
			}

			if ( CHAR0 == mutT('>') ) // end of parameterlist
			{
				CurrentPos++;
				GetSep();

				if ( CheckError(EndParameter()) ) return GspError;

				ParaMode = 0;

				continue;
			}
			if ( !Komma ) // , or > expected
			{
				return DoError(11);
			}
		} else // not ParaMode
		{
			if ( LastTag ) LastTag --;

			if ( CharIn(c, DelimitChars) ) {
				mutChar i = 0;

				while ( DelimitChars[i] != c ) i++;

				if ( i & 1 ) // closing bracket
				{

					if ( !BracketDeep )
						return DoError(1);

#ifdef WX
					DEBUGLOGBASE (other,_T(""),
					              _T("brackets: %s, i= %d, last = %d"),
					              Brackets.c_str(),
					              i,
					              Brackets[Brackets.Len()-1]);

					if ( Brackets[Brackets.Len()-1] != i-1 )
						return DoError(2 + (int) Brackets[BracketDeep-1]/2);

					Brackets = Brackets.Left(Brackets.Len()-1);

#else
					if ( Brackets[--BracketDeep] != i-1 )
						return DoError(2 + Brackets[BracketDeep]/2);

#endif
				} else // opening bracket
#ifdef WX
					Brackets += i;

#else
					Brackets[BracketDeep++] = i;

#endif
#ifdef GMN_STRICT
				if ( !LastTag && c == mutT('(') ) return DoError(41); // error: range without tag

#endif
				CurrentPos++;

				GetSep();

				switch ( c ) {
				case mutT('{'): if ( CheckError(BeginSegment()) ) return GspError;

					break;

				case mutT('}'): if ( CheckError(EndSegment()) ) return GspError;

					break;

				case mutT('['): if ( CheckError(BeginSequenz()) ) return GspError;

					break;

				case mutT(']'): if ( CheckError(EndSequenz()) ) return GspError;

					break;

				case mutT('('): if ( CheckError(BeginRange()) ) return GspError;

					break;

				case mutT(')'): if ( CheckError(EndRange()) ) return GspError;

					break;
				}

				/*		  if ( Komma )
							 if ( CheckError(NextSequenz()) ) return GspError; */
				continue;
			}

			if ( c == mutT('\\') ) {
				if ( ReadTag() ) return GspError;

				/*		  if ( !ParaMode && Komma )
							 if ( CheckError(NextSequenz()) ) return GspError; */
				continue;
			}

			if ( c == mutT('|') ) {
				CurrentPos++;
				GetSep();
#ifdef NO_SHORT_BAR

				if ( CheckError(Tag(mutT("bar"))) ) return GspError;

#else
				if ( CheckError(Tag(mutT("|"))) ) return GspError;

#endif
				/*		  if ( Komma )
							 if ( CheckError(NextSequenz()) ) return GspError; */
				continue;
			}

			if ( c == mutT(',') ) {
				if ( Brackets[BracketDeep-1] != 0 )
					return DoError(24); // unexpected comma

				CurrentPos++;

				GetSep();

				if ( CheckError(Comma()) ) return GspError;

				continue;
			}

			if ( IsLetter(c) ) {
				if ( ReadNote() ) return GspError;

				if ( Komma )
					if ( CheckError(NextSequenz()) ) return GspError;

				continue;
			}

			// unallowed char
			return DoError(20);
		}
	}

	return 0;
}

// ##################################################################
// main procedure

int GspParse(const mutString &FileName)
{
	GspCurrentLineNr = 0;
	CurrentPos = 0;
	CurrentLine = _T("");

	GspErrorLineNr = 0;
	GspErrorPos = 0;
	GspErrorLine = mutEmptyString;
	GspError = 0;

	Eof = 0;
#ifdef WX
	Brackets = mutEmptyString;
#else
	BracketDeep = 0;
#endif
	LastTag = 0;

	octave = 1;
	duration = frac(1,4);

	if ( OpenFile(FileName) )
		return DoError(30); // couldn't open file

	GetSep();

	if ( CheckError(StartSep()) )
		return GspError;

#ifdef GMN_STRICT
	if ( !Eof && CHAR0 != '[' && CHAR0 != '{' )
		DoError(40);

#endif
	if ( !GspError) DoParse();

	if ( CloseFile() )
		return DoError(31); // couldn't close file

	return GspError;
};

///\}
