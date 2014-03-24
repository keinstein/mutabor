/** \file
********************************************************************
* main file of gsp (GMN Soft Parser)
*
* Copyright:   (c) 2008 TU Dresden
* \author Volker Abel or someone else
* \author Tobias Schlemmer
* \license GPL
*
*
*
********************************************************************
* \addtogroup route
* \{
********************************************************************/
// ##################################################################
//
// ##################################################################

#include "GSP.h"
#include "GSP_File.h"
#include <string>
#include <cctype>
using namespace mutabor;

// global data

int GspCurrentLineNr;    // curent line parser deals with
int GspErrorLineNr;      // line of occured error
int GspErrorPos;         // column of occured error in line
std::string GspErrorLine;      // text of error line
int GspError;            // error id

// last saved position (before an error occurs)
int PossibleErrorLineNr;
int PossibleErrorPos;
std::string PossibleErrorLine; //[GSP_MAX_LINE];

std::string Sep = "";
inline size_t SepPos()
{
	size_t a =  (Sep.length());
	return a;
}

#define SepPos SepPos()
#if 0
char Sep[GSP_MAX_SEP];
int  SepPos;
#endif

// local data
char ParaMode;
char Komma;
int  NumberLength;
std::string Brackets = "";
#define BracketDeep						      \
	(Brackets.length())
#if 0
int  BracketDeep;
char Brackets[200];
#endif
char LastTag;
// last note

static int octave;

static std::string accedentials /*[GSP_MAX_LINE]*/;

static frac duration;

#define NEW_LINE "\n"
char SepChars[] = " \t\r\n";
char DelimitChars[] = "{}[]()";

#define uchar unsigned char

// ##################################################################
// Work with strings

inline void AddStr(std::string & Target, int Pos, const std::string& Source)
{
	mutUnused(Pos);
	DEBUGLOG2(other,("%s + %s"), Target.c_str(), Source.c_str());
	Target += Source;
	DEBUGLOG2(other,("=%s"), Target.c_str());
}

inline int CharIn(char c, const char * s)
{
	DEBUGLOG2(other,("'%c' is in '%s' at position %d, returning %d"),
	          c, s, (int)(strchr(s, c)-s), (int)(strchr(s, c) != NULL));
	return strchr(s, c) != NULL;
}

inline int IsLetter(char c)
{
	return (('a' <= c) && (c <= 'z')) ||
		(('A' <= c) && (c <= 'Z')) ||
		( c == ('_') );
}

/*
  inline int IsNumber(mutChar c)
  {
  return (mutIsDigit(c));
  }
*/
#if 0
void AddStr(char *Target, int &Pos, char *Source)
{
	for (int i = 0; Source[i]; i++) {
		Target[Pos++] = Source[i];
	}

	Target[Pos] = 0;
}

int CharIn(mutChar c, const std::string s)
{
	return mutStrChr(s, c) != 0;
}

int IsLetter(mutChar c)

{
	return ((('a') <= c) && (c <= ('z'))) ||
		((('A') <= c) && (c <= ('Z'))) ||
		( c == ('_') );
}

int IsNumber(mutChar c)
{
	return (('0') <= c) && (c <= ('9'));
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
	PossibleErrorLine = CurrentLine;
}

// ##################################################################
// reading separator chars

#define CHAR0 CurrentLine[CurrentPos]
#define CHAR1 CurrentLine[CurrentPos+1]
inline std::string & takesep()
{
	Sep += CurrentLine[CurrentPos++];
	DEBUGLOG2(other,("New Sep: %s"), Sep.c_str());
	return Sep;
}

#define TAKESEP takesep()


// reading separator string
int GetSep()
{
	Sep = "";
#if 0
	SepPos = 0;
#endif
	Komma = 0;
	int RemDeep = 0;
	int RemLine = 0;

	while ( !Eof && !GspError ) {
		DEBUGLOG2(other,("%d >= %d? Sep.Len=%d"),
			  (int)CurrentPos,(int)CurrentLine.length(),(int)Sep.length());
		DEBUGLOG2(other,("%s"),CurrentLine.c_str());
		if (CurrentPos >= CurrentLine.length())	{

			if ( ReadNewLine() ) {
				DoError(32);
				Sep = Sep.substr(0,1);
				DEBUGLOG2(other,("Returning 1 at with (%d) '%s'"),
					  (int)SepPos, Sep.c_str());
				return Sep.length();
			}

			RemLine = 0;
			if ( GspCurrentLineNr != 1 )
				Sep += NEW_LINE;
			continue;
		}

		char c = CHAR0;

		// comment start
		if ( c == '(' && CHAR1 == '*' ) {
				TAKESEP;
				TAKESEP;
				RemDeep++;
				continue;
		}

		// during a comment
		if ( RemDeep ) {
			if ( c == '*' && CHAR1 == ')' )	{
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

		// line comment
		if ( c == '%' ) {
			RemLine = 1;
			continue;
		}

		// separating chars
		if ( CharIn(c, SepChars) ) {
			TAKESEP;
			continue;
		}

		// sequenz separator
		if ( c == ',' && ParaMode ) {
			TAKESEP;
			Komma = 1;
			continue;
		}

		break;
	}

	DEBUGLOG2(other,("Returning with (%d) '%s'"),(int)Sep.length(),Sep.c_str());

	Sep += "\0";
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
		DEBUGLOG2(other,("Sign char %c?"), CHAR0);

		if ( CHAR0 == ('+') ) CurrentPos++;
		else if ( CHAR0 == ('-') ) {
			CurrentPos++;
			minus = true;
		}
	}

	GetSep();

	while ( isdigit(CHAR0) && Sep.empty() ) {
		DEBUGLOG2(other,("Number char %c? (a=%ld)"), CHAR0, a);
		a = a*10 + (CurrentLine[CurrentPos++]-('0'));
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
	if ( !Sep.empty() || CHAR0 != ('.') ) // integer
		return CheckError(TagParaInt(a));

	// real
	CurrentPos++; // comma position
	GetSep();
	char minus1 = minus;
	double r = (double)a;
	if ( !Sep.empty() ) // real without fraction part
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
	std::string s = "";
#if 0
	mutChar s[GSP_MAX_LINE] = "";
#endif
	CurrentPos++;

	while ( (CHAR0 != '"' || CHAR1 == '"') && !Eof ) {
		// new Line
		if ( !CHAR0 ) {
			ReadNewLine();
			s += NEW_LINE;
			continue;
		}
		if ( CHAR0 == ('"') )
			CurrentPos++;

		s += CurrentLine[CurrentPos++];
#if 0
		s[i++] = CurrentLine[CurrentPos++];

#endif
	}

	if ( CHAR0 == ('"') ) CurrentPos++;

	s += (char)0;
	GetSep();

	return CheckError(TagParaStr(s));
}

// reads a tag
int ReadTag()
{
	std::string Name = "";
	int i = 0;
	LastTag = 2; // to have an indicator, wether the last token was a tag
	CurrentPos++;
	GetSep();
	i = CurrentPos;

	while ( IsLetter(CHAR0) && !SepPos ) {
		CurrentPos++;
#if 0
		Name[i++] = CurrentLine[CurrentPos++];
#endif
		GetSep();
	}

	Name = CurrentLine.substr (i,CurrentPos-i);

#if 0
	Name[i] = 0;

#endif
	if ( !GspError ) CheckError(Tag(Name));

	if ( CHAR0 == '<' ) {
		CurrentPos++;
		GetSep();

		if ( !GspError ) CheckError(BeginParameter());

		ParaMode = 1;
	}

	if ( CHAR0 == '>' ) {
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
	int i = 0;
	std::string Name = "";
	accedentials = "";
#if 0
	mutChar Name[GSP_MAX_LINE] = ("");
	accedentials[0] = 0;
#endif

	GetSep();


	for (i = CurrentPos; IsLetter(CHAR0) && !SepPos; CurrentPos++)
		GetSep();

	Name = CurrentLine.substr(i,CurrentPos-i);

	GetSep();

#if 0
	while ( IsLetter(CHAR0) && !SepPos ) {
		Name[i++] = CurrentLine[CurrentPos++];
		GetSep();
		std::string Name /* [GSP_MAX_LINE]*/ = ("");

	}

	Name[i] = 0;

#endif

	DEBUGLOG2(other,("SepPos: %d"),(int)SepPos);

	if ( SepPos )
		return CheckError(Note(Name, accedentials, octave, duration));

	i = 0; // accedentials

	while ( CharIn(CHAR0, "#&") && !SepPos ) {
		accedentials += CurrentLine[CurrentPos++];
#if 0
		accedentials[i++] = CurrentLine[CurrentPos++];
#endif
		GetSep();
	}

#if 0
	accedentials[i] = 0;

#endif

	DEBUGLOG2(other,("SepPos: %d"),(int)SepPos);

	if ( SepPos )
		return CheckError(Note(Name, accedentials, octave, duration));

	size_t cp = CurrentPos; // octave
	int oct = ReadLong(1);
	if ( cp != CurrentPos ) octave = oct;
	if ( SepPos || !CharIn(CHAR0, "/*.") )
		return CheckError(Note(Name, accedentials, octave, duration));

	int DurOk = 0; // duration
	duration = frac(1,1);
	if ( CHAR0 == ('*') ) {
		DurOk = 1;
		CurrentPos++;
		duration = frac(ReadLong(0));

		if ( !duration )
			return DoError(21); // error: nominator expected
	}

	if ( SepPos || !CharIn(CHAR0, "/.") )
		return CheckError(Note(Name, accedentials, octave, duration));

	if ( CHAR0 == '/' ) {
		DurOk = 1;
		CurrentPos++;
		duration /= ReadLong(0);

		if ( !duration )
			return DoError(22); // error: denominator expected
	}

	if ( SepPos )
		return CheckError(Note(Name, accedentials, octave, duration));

	if ( CHAR0 == '.' && !DurOk )
		return DoError(23); // error: dotting wihtout duration

	frac add = duration;

	while ( CHAR0 == '.' && !SepPos ) {
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
		char c = CHAR0;
		SavePos();
		Komma = 0;

		if ( ParaMode ) {
			if ( isdigit(c) || ( c == '+') || ( c == '-') ) {
				// number parameter
				if ( ReadParaNumber() ) return GspError;
			}
			else if ( c == ('"') ) {
				// string parameter
				if ( ReadParaStr() ) return GspError;
			}
			else {
				// wrong parameter
				return DoError(10);
			}

			// end of parameterlist
			if ( CHAR0 == '>' ) {
				CurrentPos++;
				GetSep();
				if ( CheckError(EndParameter()) ) return GspError;
				ParaMode = 0;
				continue;
			}

			// , or > expected
			if ( !Komma ) {
				return DoError(11);
			}
		}
		else {
		// not ParaMode
			if ( LastTag ) LastTag --;
			if ( CharIn(c, DelimitChars) ) {
				int i = 0;
				while ( DelimitChars[(size_t)i] != c ) i++;
				if ( i & 1 ) {
					// closing bracket
					if ( !BracketDeep )
						return DoError(1);

					DEBUGLOGBASE (other,(""),
						      ("brackets: %s, i= %d, last = %d"),
						      Brackets.c_str(),
						      i,
						      Brackets[Brackets.length()-1]);

					if ( Brackets[Brackets.length()-1] != i-1 )
						return DoError(2 + (int) Brackets[BracketDeep-1]/2);

					Brackets = Brackets.substr(0,Brackets.length()-1);

#if 0
					if ( Brackets[--BracketDeep] != i-1 )
						return DoError(2 + Brackets[BracketDeep]/2);

#endif
				} else // opening bracket
					Brackets += i;

#if 0
				Brackets[BracketDeep++] = i;

#endif
#ifdef GMN_STRICT
				if ( !LastTag && c == '(' )
					return DoError(41); // error: range without tag

#endif
				CurrentPos++;
				GetSep();
				switch ( c ) {
				case '{': if ( CheckError(BeginSegment()) ) return GspError;
					break;
				case '}': if ( CheckError(EndSegment()) ) return GspError;
					break;

				case '[': if ( CheckError(BeginSequenz()) ) return GspError;
					break;

				case ']': if ( CheckError(EndSequenz()) ) return GspError;
					break;

				case '(': if ( CheckError(BeginRange()) ) return GspError;
					break;

				case ')': if ( CheckError(EndRange()) ) return GspError;
					break;
				}

				/*		  if ( Komma )
						  if ( CheckError(NextSequenz()) ) return GspError; */
				continue;
			}

			if ( c == '\\' ) {
				if ( ReadTag() ) return GspError;
				/*		  if ( !ParaMode && Komma )
						  if ( CheckError(NextSequenz()) ) return GspError; */
				continue;
			}

			if ( c == '|' ) {
				CurrentPos++;
				GetSep();
#ifdef NO_SHORT_BAR
				if ( CheckError(Tag("bar")) ) return GspError;

#else
				if ( CheckError(Tag("|")) ) return GspError;
#endif
				/*		  if ( Komma )
						  if ( CheckError(NextSequenz()) ) return GspError; */
				continue;
			}

			if ( c == ',' ) {
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

int GspParse(const std::string &FileName)
{
	GspCurrentLineNr = 0;
	CurrentPos = 0;
	CurrentLine = "";

	GspErrorLineNr = 0;
	GspErrorPos = 0;
	GspErrorLine = "";
	GspError = 0;

	Eof = 0;
#ifdef WX
	Brackets = "";
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
}

///\}
