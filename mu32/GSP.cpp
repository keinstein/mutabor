// ##################################################################
// main file of gsp (GMN Soft Parser)
// ##################################################################

#include "GSP.h"
#include "GSP_File.h"
#include <string.h>

// global data

int GspCurrentLineNr;    // curent line parser deals with
int GspErrorLineNr;      // line of occured error
int GspErrorPos;         // column of occured error in line
char *GspErrorLine;      // text of error line
int GspError;            // error id

// last saved position (before an error occurs)
int PossibleErrorLineNr;
int PossibleErrorPos;
char PossibleErrorLine[GSP_MAX_LINE];

char Sep[GSP_MAX_SEP];
int  SepPos;

// local data
char ParaMode;
char Komma;
int  NumberLength;
int  BracketDeep;
char Brackets[200];
char LastTag;
// last note

int octave;
char accedentials[GSP_MAX_LINE];
frac duration;

#define NEW_LINE "\n"
char SepChars[] = " \t";
char DelimitChars[] = "{}[]()";

#define uchar unsigned char

// ##################################################################
// Work with strings

void AddStr(char *Target, int &Pos, char *Source)
{
  for (int i = 0; Source[i]; i++)
  {
    Target[Pos++] = Source[i];
  }
  Target[Pos] = 0;
}

int CharIn(char c, const char *s)
{
  return strchr(s, c) != 0;
}

int IsLetter(char c)
{
  return (('a' <= c) && (c <= 'z')) ||
			(('A' <= c) && (c <= 'Z')) ||
         ( c == '_' );
}

int IsNumber(char c)
{
  return ('0' <= c) && (c <= '9');
}

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
  strcpy(PossibleErrorLine, CurrentLine);
}

// ##################################################################
// reading separator chars

#define CHAR0 CurrentLine[CurrentPos]
#define CHAR1 CurrentLine[CurrentPos+1]
#define TAKESEP Sep[SepPos++] = CurrentLine[CurrentPos++]


// reading separator string
int GetSep()
{
  SepPos = 0;
  Komma = 0;
  int RemDeep = 0;
  int RemLine = 0;
  while ( !Eof && !GspError )
  {
	 uchar c = CHAR0;
	 if ( !c ) // new Line
	 {
		if ( ReadNewLine() )
		{
		  DoError(32);
		  return ( SepPos = 1 );
		}
		RemLine = 0;
		if ( GspCurrentLineNr != 1 )
		  AddStr(Sep, SepPos, NEW_LINE);
		continue;
	 }

	 if ( c == '(' && CHAR1 == '*' )  // comment start
	 {
		TAKESEP; TAKESEP; RemDeep++;
		continue;
	 }

	 if ( RemDeep ) // during a comment
	 {
		if ( c == '*' && CHAR1 == ')' )
		{
		  TAKESEP; TAKESEP; RemDeep--;
		}
		else
		  TAKESEP;
		continue;
	 }

	 if ( RemLine )
	 {
		TAKESEP;
		continue;
	 }

	 if ( c == '%' ) // line comment
	 {
		RemLine = 1;
		continue;
	 }

	 if ( CharIn(c, SepChars) ) // separating chars
	 {
		TAKESEP;
		continue;
	 }

	 if ( c == ',' && ParaMode ) // sequenz separator
	 {
		TAKESEP;
		Komma = 1;
		continue;
	 }

	 break;
  }
  Sep[SepPos] = 0;
  return SepPos;
}

// ##################################################################
// subfunctions of parsing process

char minus;

// reads an integer
long ReadLong(int SignAllowed)
{
  long a = 0;
  NumberLength = 0;
  minus = 0;
  if ( SignAllowed )
  {
	 if ( CHAR0 == '+' ) CurrentPos++;
	 else if ( CHAR0 == '-' )
	 { CurrentPos++; minus = 1; }
  }
  GetSep();
  while ( IsNumber(CHAR0) && !SepPos )
  {
	 a = a*10 + (CurrentLine[CurrentPos++]-'0');
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
  if ( SepPos || CHAR0 != '.' ) // integer
	 return CheckError(TagParaInt(a));

  // real
  CurrentPos++; // comma position

  GetSep();
  char minus1 = minus;
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
  char s[GSP_MAX_LINE] = "";
  int i = 0;
  CurrentPos++;
  while ( (CHAR0 != '"' || CHAR1 == '"') && !Eof )
  {
	 if ( !CHAR0 ) // new Line
	 {
		ReadNewLine();
		AddStr(s, i, NEW_LINE);
		continue;
	 }
	 if ( CHAR0 == '"' ) CurrentPos++;
	 s[i++] = CurrentLine[CurrentPos++];
  }
  if ( CHAR0 == '"' ) CurrentPos++;
  s[i] = 0;
  GetSep();
  return CheckError(TagParaStr(s));
}

// reads a tag
int ReadTag()
{
  char Name[GSP_MAX_LINE] = "";
  char i = 0;
  LastTag = 2; // to have an indicator, wether the last token was a tag
  CurrentPos++;
  GetSep();
  while ( IsLetter(CHAR0) && !SepPos )
  {
	 Name[i++] = CurrentLine[CurrentPos++];
	 GetSep();
  }
  Name[i] = 0;
  if ( !GspError ) CheckError(Tag(Name));
  if ( CHAR0 =='<' )
  {
	 CurrentPos++; GetSep();
	 if ( !GspError ) CheckError(BeginParameter());
	 ParaMode = 1;
  }
  if ( CHAR0 =='>' )
  {
	 CurrentPos++; GetSep();
	 if ( !GspError ) CheckError(EndParameter());
	 ParaMode = 0;
  }
  return GspError;
}

// reads a note
int ReadNote()
{
  char Name[GSP_MAX_LINE] = "";
  char i = 0;
  accedentials[0] = 0;

  GetSep();
  while ( IsLetter(CHAR0) && !SepPos )
  {
	 Name[i++] = CurrentLine[CurrentPos++];
	 GetSep();
  }
  Name[i] = 0;

  if ( SepPos )
	 return CheckError(Note(Name, accedentials, octave, duration));

  i = 0; // accedentials
  while ( CharIn(CHAR0, "#&") && !SepPos )
  {
	 accedentials[i++] = CurrentLine[CurrentPos++];
	 GetSep();
  }
  accedentials[i] = 0;

  if ( SepPos )
	 return CheckError(Note(Name, accedentials, octave, duration));

  int cp = CurrentPos; // octave
  int oct = ReadLong(1);
  if ( cp != CurrentPos ) octave = oct;

  if ( SepPos || !CharIn(CHAR0, "/*.") )
	 return CheckError(Note(Name, accedentials, octave, duration));

  int DurOk = 0; // duration
  duration = frac(1,1);

  if ( CHAR0 == '*' )
  {
	 DurOk = 1;
	 CurrentPos++;
	 duration.n = ReadLong(0);
	 if ( !duration.n )
		return DoError(21); // error: nominator expected
  }

  if ( SepPos || !CharIn(CHAR0, "/.") )
	 return CheckError(Note(Name, accedentials, octave, duration));

  if ( CHAR0 == '/' )
  {
	 DurOk = 1;
	 CurrentPos++;
	 duration.d = ReadLong(0);
	 if ( !duration.d )
		return DoError(22); // error: denominator expected
  }

  if ( SepPos )
	 return CheckError(Note(Name, accedentials, octave, duration));

  if ( CHAR0 == '.' && !DurOk )
	 return DoError(23); // error: dotting wihtout duration

  frac add = duration;
  while ( CHAR0 == '.' && !SepPos )
  {
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

  while ( !Eof )
  {
	 char c = CHAR0;
	 SavePos();
	 Komma = 0;
	 if ( ParaMode )
	 {
		if ( IsNumber(c) || ( c == '+') || ( c == '-') ) // number parameter
		{
		  if ( ReadParaNumber() ) return GspError;
		}
		else if ( c == '"' ) // string parameter
		{
		  if ( ReadParaStr() ) return GspError;
		}
		else // wrong parameter
		{
		  return DoError(10);
		}
		if ( CHAR0 == '>' ) // end of parameterlist
		{
		  CurrentPos++; GetSep();
		  if ( CheckError(EndParameter()) ) return GspError;
		  ParaMode = 0;
		  continue;
		}
		if ( !Komma ) // , or > expected
		{
		  return DoError(11);
		}
	 }
	 else // not ParaMode
	 {
		if ( LastTag ) LastTag --;
		if ( CharIn(c, DelimitChars) )
		{
		  int i = 0;
		  while ( DelimitChars[i] != c ) i++;
		  if ( i & 1 ) // closing bracket
		  {
			 if ( !BracketDeep )
				return DoError(1);
			 if ( Brackets[--BracketDeep] != i-1 )
				return DoError(2 + Brackets[BracketDeep]/2);
		  }
		  else // opening bracket
			 Brackets[BracketDeep++] = i;
		  #ifdef GMN_STRICT
		  if ( !LastTag && c == '(' ) return DoError(41); // error: range without tag
		  #endif
		  CurrentPos++; GetSep();
		  switch ( c )
		  {
			 case '{': if ( CheckError(BeginSegment()) ) return GspError; break;
			 case '}': if ( CheckError(EndSegment()) ) return GspError; break;
			 case '[': if ( CheckError(BeginSequenz()) ) return GspError; break;
			 case ']': if ( CheckError(EndSequenz()) ) return GspError; break;
			 case '(': if ( CheckError(BeginRange()) ) return GspError; break;
			 case ')': if ( CheckError(EndRange()) ) return GspError; break;
		  }
/*		  if ( Komma )
			 if ( CheckError(NextSequenz()) ) return GspError; */
		  continue;
		}

		if ( c == '\\' )
		{
		  if ( ReadTag() ) return GspError;
/*		  if ( !ParaMode && Komma )
			 if ( CheckError(NextSequenz()) ) return GspError; */
		  continue;
		}

		if ( c == '|' )
		{
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

		if ( c == ',' )
		{
		  if ( Brackets[BracketDeep-1] != 0 )
			 return DoError(24); // unexpected comma
		  CurrentPos++;
		  GetSep();
		  if ( CheckError(Comma()) ) return GspError;
		  continue;
		}

		if ( IsLetter(c) )
		{
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

int GspParse(const char *FileName)
{
  GspCurrentLineNr = 0;
  CurrentPos = 0;
  CurrentLine[0] = 0;

  GspErrorLineNr = 0;
  GspErrorPos = 0;
  GspErrorLine = 0;
  GspError = 0;

  Eof = 0;
  BracketDeep = 0;
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
