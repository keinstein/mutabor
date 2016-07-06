/** \file
 ********************************************************************
 * main file of GIS (GMN Internal Structure)
 *
 * Copyright:   (c) 2008 TU Dresden
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

#ifndef FOR_MUTWIN
#include <iostream>
#endif

#include "src/kernel/Frac.h"
#include "src/kernel/routing/gmn/GIS.h"
#include "src/kernel/routing/gmn/GSP.h"
using namespace mutabor;

// registered tags

const char * Tags[NTAGS] =
        {
                (""),
		("intens"),
		("slur"),
		("beam"),
		("text"),
                ("bar"),
		("cresc"),
		("dim"),
		("crescBegin"),
		("crescEnd"),
                ("dimBegin"),
		("dimEnd"),
		("tempo"),
		("accel"),
		("rit"),
                ("accelBegin"),
		("accelEnd"),
		("ritBegin"),
		("ritEnd"),
		("instr"),
                ("tie"),
		("stacc"),
		("accent"),
		("ten"),
		("marcato"),
                ("trill"),
		("mord"),
		("turn"),
		("trem"),
		("fermata"),
                ("grace"),
		("cue"),
		("repeatBegin"),
		("repeatEnd"),
		("clef"),
                ("meter"),
		("key"),
		("oct"),
		("staff"),
		("beamsAuto"),
                ("beamsOff"),
		("stemsAuto"),
		("stemsUp"),
		("stemsDown"),
		("doubleBar"),
                ("tactus"),
		("title"),
		("composer"),
		("mark"),
		("label"),
                ("alter"),
		("mutabor")
        };

const char * TagShorts[NTAGSHORTS] =
        {
                (""),
		("i"),
		("sl"),
		("bm"),
		("t"),
		("|")
        };

GisToken *Root;
GisToken **Current, *LastOpenBracket;
GisTagBegin *LastOpenRange;
char TagMode;
std::string TagName;
std::string TagSep;
GisToken *Para, *LastPara;
int LastOctave;
mutabor::frac LastDuration;

#ifdef DEBUG
int debugcount = 0;
#endif
/*
*/

// ##################################################################
// stream methods of GIS structurs
/*
char RequiresKomma(GisToken *p)
{
  if ( !p ) return 0;
  GisType pt = p->Type();
  return ( pt == GTSegment || pt == GTSequenz || pt == GTTag
			  || pt == GTTagBegin || pt == GTNote );
}
*/

#ifndef FOR_MUTWIN

void GisToken::Stream(ostream &out, char sep)
{
	if ( sep ) out << Sep;

	if ( Next ) Next->Stream(out, sep);
}

void GisSegment::Stream(ostream &out, char sep)

{
	if ( sep )
		out << "{" << Sep;
	else
		out << "{ ";

	if ( Contents ) Contents->Stream(out, sep);

	if ( sep )
		out << "}" << Sep2;
	else
		out << "} ";

	if ( Next ) Next->Stream(out, sep);
}

void GisSequenz::Stream(ostream &out, char sep)
{
	if ( sep )
		out << "[" << Sep;
	else
		out << "[ ";

	LastOctave = 1;

	LastDuration = frac(1, 4);

	if ( Contents ) Contents->Stream(out, sep);

	if ( sep )
		out << "]" << Sep2;
	else
		out << "] ";

	if ( Next ) Next->Stream(out, sep);
}

void GisTag::Stream(ostream &out, char sep)
{
	if ( !strcmp(Name, "|") )
		out << "|";
	else
		out << "\\" << Name;

	if ( sep )
		out << Sep;
	else
		if ( Para ) out << "<";

	if ( Para ) Para->Stream(out, sep);

	if ( !sep &&  Para )
		out << ">";

	if ( Next ) Next->Stream(out, sep);
}

#endif

GisType GisTag::GetParaType(int nr)
{
	GisToken *P = Para;

	while ( P ) {
		if ( nr <= 1 ) break;

		P = P->Next;

		nr--;
	}

	if ( P )
		return P->Type();
	else
		return GTNull;
}

GisToken *GisTag::GetPara(int nr)
{
	GisToken *P = Para;

	while ( P ) {
		if ( nr <= 1 ) break;

		P = P->Next;

		nr--;
	}

	return P;
}

#ifndef FOR_MUTWIN

void GisTagBegin::Stream(ostream &out, char sep)
{
	if ( Name && Name[0] ) out << "\\";  // extra, enable tagless brackets

	if ( sep )
		out << Name << Sep;
	else {
		out << Name;

		if ( Para ) out << "<";
	}

	if ( Para ) Para->Stream(out, sep);

	if ( !sep ) {
		if ( Para )
			out << ">";

		out << "( ";
	}

	if ( Next ) Next->Stream(out, sep);
}

void GisTagEnd::Stream(ostream &out, char sep)
{
	if ( sep )
		out << ")" << Sep;
	else
		out << ") ";

	if ( Next ) Next->Stream(out, sep);
}

#endif

int Name2Key(const std::string name)
{
	char notes[] = "c d ef g a b";
	size_t l = name.length();
	int i = 11;

	if ( l == 1 ) {
		while ( i >= 0 ) {
			if ( notes[i] == name[0] )
				break;

			i--;
		}

		if ( name[0] == 'h' )
			return 11;
		else
			return i;
	} else if ( l == 3 ) {
		while ( i >= 0 ) {
			if ( notes[i] == name[0] )
				break;

			i--;
		}

		if ( i != -1 ) i++;

		return i;
	} else
		return -1;
}

int Acc2Int(const std::string &acc)

{
	if ( acc.empty() ) return 0;

	int i = 0;

#ifdef WX
	for (size_t j = 0; j < acc.length(); j++)
#else
	for (int j = 0; acc[j]; j++)
#endif
	{

		if ( acc[j] == '&' )
			i--;
		else if ( acc[j] == '#' )
			i++;
	}
	return i;
}

#ifdef WX
#define strdupchr(a) (a)
#else
char *strdupchr(char a)
{
	// Flawfinder: ignore
	char s[2] = "w";
	s[0] = a;
	return strdup(s);
}

#endif

GisNote::GisNote(int key,
		 int octave,
		 int acc,
		 const std::string & sep,
		 GisToken *next)
		: GisToken(sep, next)
{
	if ( key == GMN_NO_KEY ) {
		Name = "_";
		Accedentials = "";
		;
		Octave = 0;
	} else {
		char Flats[]   = "cddeefggaabb";
		char FlatsA[]  = " & &  & & & ";
		char Sharps[]  = "ccddeffggaab";
		char SharpsA[] = " # #  # # # ";
		char accs;
		int Index = key % 12;
		int Abstand = key /12;

		if ( Index < 0 ) {
			Index += 12;
			Abstand--;
		}

		if ( acc < 0 ) {
			Name = Flats[Index];
			accs = FlatsA[Index];
		} else {
			Name = strdupchr(Sharps[Index]);
			accs = SharpsA[Index];
		}

		if ( accs != ' ' )
			Accedentials = strdupchr(accs);
		else
			Accedentials = "";

		Octave = Abstand - 5 - octave;
	}

	Duration = 0;
}

int GisNote::GetKey()

{
	int Key = Name2Key(Name);

	if ( Key == -1 ) return -1;

	Key += ( Octave + 5) * 12;

	Key += Acc2Int(Accedentials);

	return Key;
}

#ifndef FOR_MUTWIN

void GisNote::Stream(ostream &out, char sep)
{
	out << Name << Accedentials;

	if ( Name[0] != '_' )
		if ( Octave != LastOctave ) {
			out << Octave;
			LastOctave = Octave;
		}

	if ( Duration != LastDuration ) {
		if ( Duration.n != 1 || Duration == frac(1,1) )
			out << "*" << Duration.n;

		if ( Duration.d != 1 )
			out << "/" << Duration.d;

		LastDuration = Duration;
	}

	if ( sep )
		out << Sep;
	else
		out << " ";

	if ( Next ) Next->Stream(out, sep);
}


void GisParaInt::Stream(ostream &out, char sep)
{
	if ( sep )
		out << i << Sep;
	else {
		out << i;

		if ( Next ) out << ", ";
	}

	if ( Next ) Next->Stream(out, sep);
}

void GisParaReal::Stream(ostream &out, char sep)
{
	if ( sep )
		out << x << Sep;
	else {
		out << x;

		if ( Next ) out << ", ";
	}

	if ( Next ) Next->Stream(out, sep);
}

void GisParaStr::Stream(ostream &out, char sep)
{
	if ( sep )
		out << '"' << s << '"' << Sep;
	else {
		out << '"' << s << '"';

		if ( Next ) out << ", ";
	}

	if ( Next ) Next->Stream(out, sep);
}

void GisComma::Stream(ostream &out, char sep)
{
	out << ",";

	if ( sep )
		out << Sep;
	else
		out << " ";

	if ( Next ) Next->Stream(out, sep);
}

#endif

// ##################################################################
// help procedures for GIS structures

// frees string pointer and sets it 0

#ifdef WX
#define AddStr(s1,s2,s3) (s1 += s2 + s3)
void Clear(std::string * s)
{
	*s = "";
}

#else
void Clear(char **s)
{
	if ( *s ) {
		free(*s);
		*s = 0;
	}
}

// add 2 strings to 1, caring for memory

char *AddStr(char **s1, const char *s2, const char *s3)
{
	int l = strlen(*s1) + strlen(s2) + strlen(s3) + 1;
	char *s = (char*) malloc(l);
	s[0] = 0;

	if ( *s1 ) strcat(s, *s1);

	if ( s2 ) strcat(s, s2);

	if ( s3 ) strcat(s, s3);

	Clear(s1);

	*s1 = s;

	return *s1;
}

#endif

int BuildTag()
{
	DEBUGLOG2(gmnfile,("TagName.len %d, '%s'"),(int)TagName.length(),TagName.c_str());
	GisTag *Tag = new GisTag(TagName, Para, TagSep);
	*Current = Tag;
	Current = &(Tag->Next);
	Clear(&TagName);
	Clear(&TagSep);
	Para = 0;
	LastPara = 0;
	TagMode = 0;
	return 0;
}

// ##################################################################
// callback procedures for GSP

int StartSep()
{
	DEBUGLOG2(gmnfile,("saving Sep %s"),Sep.c_str());
	*Current = new GisToken(Sep, 0);
	Current = &((*Current)->Next);
	return 0;
}

int BeginSegment()
{
	DEBUGLOG2(gmnfile,("{"));

	if ( TagMode ) BuildTag();

	GisSegment *Seg = new GisSegment(0, Sep, LastOpenBracket);

	LastOpenBracket = Seg;

	*Current = Seg;

	Current = &(Seg->Contents);

	return 0;
}

int EndSegment()
{
	DEBUGLOG2(gmnfile,("}"));

	if ( TagMode ) BuildTag();
	*Current = 0;
	((GisSegment*)(LastOpenBracket))->Sep2 = Sep;
	Current = &(LastOpenBracket->Next);
	LastOpenBracket = LastOpenBracket->Next;

	return 0;
}

int BeginSequenz()
{
	DEBUGLOG2(gmnfile,("["));

	if ( TagMode ) BuildTag();

	GisSequenz *Seq = new GisSequenz(0, Sep, LastOpenBracket);

	LastOpenBracket = Seq;

	*Current = Seq;

	Current = &(Seq->Contents);

	return 0;
}

int EndSequenz()
{
	DEBUGLOG2(gmnfile,("]"));

	if ( TagMode ) BuildTag();

	*Current = 0;

	((GisSequenz*)LastOpenBracket)->Sep2 =Sep;

	Current = &(LastOpenBracket->Next);

	LastOpenBracket = LastOpenBracket->Next;

	return 0;
}

int BeginParameter()
{
	DEBUGLOG2(gmnfile,("<"));
	AddStr(TagSep, ("<"), Sep);
	return 0;
}

int EndParameter()
{
	DEBUGLOG2(gmnfile,(">"));

	if ( Para )
		AddStr((LastPara->Sep), (">"), Sep);
	else
		AddStr(TagSep, (">"), Sep);

	return 0;
}

int BeginRange()
{
	DEBUGLOG2(gmnfile,("( "));

	if ( LastPara )
		AddStr(LastPara->Sep, ("("), Sep);
	else if ( Para )
		AddStr(Para->Sep, ("("), Sep);
	else
		AddStr(TagSep, ("("), Sep);

	GisTagBegin *Tag = new GisTagBegin(TagName, Para, TagSep, 0);

	*Current = Tag;

	Current = &(Tag->Next);

	Tag->End = LastOpenRange;

	LastOpenRange = Tag;

	Clear(&TagName);

	Clear(&TagSep);

	Para = 0;

	LastPara = 0;

	TagMode = 0;

	return 0;
}

int EndRange()
{
	DEBUGLOG2(gmnfile,(")\n"));

	if ( TagMode ) BuildTag();

	GisTagEnd *Tag = new GisTagEnd(LastOpenRange, Sep);

	*Current = Tag;

	Current = &(Tag->Next);

	LastOpenRange = (GisTagBegin*) LastOpenRange->End;

	(Tag->Begin)->End = Tag;

	return 0;
}

int NextSequenz()
{
	DEBUGLOG2(gmnfile,(", "));

	if ( TagMode ) BuildTag();

	return 0;
}

int Note(const std::string &name,
	 const std::string &accedentials,
	 int octave,
	 const mutabor::frac & duration)
{
	DEBUGLOG2(gmnfile,("%s%s%d*%s: Note '%s' %s Oktave %d, Duration: %s "),
	          name.c_str(),
	          accedentials.c_str(),
	          octave,
		  str(duration).c_str(),
	          name.c_str(),
	          accedentials.c_str(),
	          octave,
		  str(duration).c_str());

	if ( TagMode ) BuildTag();

	GisNote *Note = new GisNote(name, accedentials, octave, duration, Sep);

	*Current = Note;

	Current = &(Note->Next);

	return 0;
}

int Tag(const std::string &tagName)
{
	DEBUGLOG2(gmnfile,("\\%s"),tagName.c_str());

	if ( TagMode ) BuildTag();

	TagName =  tagName;

	TagSep = Sep;

	TagMode = 1;

	return 0;
}

int TagParaInt(long i)
{
	DEBUGLOG2(gmnfile,("ParaInt: %ld"),i);
	GisParaInt *p = new GisParaInt(i, Sep);

	if ( LastPara )
		LastPara->Next = p;
	else
		Para = p;

	LastPara = p;

	return 0;
}

int TagParaReal(double x)
{
	DEBUGLOG2(gmnfile,("ParaReal: %g"), x);
	GisParaReal *p = new GisParaReal(x, Sep, 0);

	if ( LastPara )
		LastPara->Next = p;
	else
		Para = p;

	LastPara = p;

	return 0;
}

int TagParaStr(const std::string &s)
{
	DEBUGLOG2(gmnfile,("ParaStr: %s"), s.c_str());
	GisParaStr *p = new GisParaStr(s, Sep, 0);

	if ( LastPara )
		LastPara->Next = p;
	else
		Para = p;

	LastPara = p;

	return 0;
}

int Comma()
{
	DEBUGLOG2(gmnfile,(","));

	if ( TagMode ) BuildTag();

	*Current = new GisComma(Sep, 0);

	Current = &((*Current)->Next);

	return 0;
}

// ##################################################################
// clean up procedures (after errors)

// correct all Next pointers to avoid troubles when deleting
void UnRavel()
{
	*Current = 0;
	// unravel Next pointers

	while ( LastOpenBracket ) {
		GisToken *p = LastOpenBracket;
		LastOpenBracket = p->Next;
		p->Next = 0;
	}

	// clear TagName
	if ( TagName.size() ) Clear(&TagName);

	// clear Para
	if ( Para ) delete Para;
}

// ##################################################################
// main procedures

GisType GetGisType(GisToken* token)
{
	if ( token )
		return token->Type();
	else
		return GTNull;
}

int GetTagId(const std::string &name, std::string &registered)

{
	if (name.empty()) {
		registered = Tags[0];
		return 0;
	}

	// check normal form
	int i;

	for (i = 0; i < NTAGS; i++) {
		DEBUGLOG2(gmnfile,("comparing '%s' with tag'%s'"),name.c_str(),Tags[i]);
		if ( name == Tags[i]) {
			registered = Tags[i];
			return i;
		} ;
	}

	// check short form
	for (i = 0; i < NTAGSHORTS; i++) {
		DEBUGLOG2(gmnfile,("comparing '%s' with tag'%s'"),name.c_str(),TagShorts[i]);

		if ( name == TagShorts[i] ) {
			registered = TagShorts[i];
			return i;
		}
	}

	// no registered tag
	registered = "";

	return -1;
}

GisToken *CopyPara(GisToken *para)

{
	GisToken *C = 0;
	GisToken **Cursor = &C;

	while ( para ) {
		*Cursor = para->Copy();
		Cursor = &(*Cursor)->Next;
		para = para->Next;
	}

	return C;
}

GisToken *GisParse(const std::string FileName)
{
	Root = 0;
	Current = &Root;
	LastOpenBracket = 0;
	LastOpenRange = 0;
	TagMode = 0;
	TagName = "";
	TagSep = "";
	Para = 0;
	LastPara = 0;
	DEBUGLOG2(gmnfile,("TagName.len %d, '%s'"),(int)TagName.length(),TagName.c_str());

	if ( GspParse(FileName) ) {
		UnRavel();
		delete Root;
		Root = 0;
	}

	return Root;
}

std::string GISPrettyPrint(std::string s)
{
	std::string ret = "";
	std::string pre = "";

	for (size_t start = 0, current = 0 ; current < s.length(); current++) {
		char c = s[current];

		if (c == ('{')) {
			pre += ("  ");
		} else if (c == ('}')) {
			if (pre.length() >= 2) pre = pre.substr(0,pre.length()-2);
		} else if (c == ('\n')) {
			ret += s.substr (start, current - start + 1) + pre;
			start = current + 1;
		}
	}

	return ret;
}

///\}
