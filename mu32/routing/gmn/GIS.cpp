/** \file 
 ********************************************************************
 * Description
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/mu32/routing/gmn/GIS.cpp,v 1.4 2011/02/20 22:35:56 keinstein Exp $
 * Copyright:   (c) 2008 TU Dresden
 * \author  Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 
 * $Date: 2011/02/20 22:35:56 $
 * \version $Revision: 1.4 $
 * \license GPL
 *
 * $Log: GIS.cpp,v $
 * Revision 1.4  2011/02/20 22:35:56  keinstein
 * updated license information; some file headers have to be revised, though
 *
 *
 *
 ********************************************************************
 * \addtogroup route
 * \{
 ********************************************************************/
// #################################################################
// main file of GIS (GMN Intern Structur)
// ##################################################################

#ifndef FOR_MUTWIN
#include <iostream>
#endif

#include "Frac.h"
#include "GIS.h"
#include "GSP.h"


// registered tags

const mutChar * Tags[NTAGS] =
        {
                mutT(""), mutT("intens"),  mutT("slur"),  mutT("beam"), mutT("text"),
                mutT("bar"), mutT("cresc"), mutT("dim"), mutT("crescBegin"), mutT("crescEnd"),
                mutT("dimBegin"), mutT("dimEnd"), mutT("tempo"), mutT("accel"), mutT("rit"),
                mutT("accelBegin"), mutT("accelEnd"), mutT("ritBegin"), mutT("ritEnd"), mutT("instr"),
                mutT("tie"), mutT("stacc"), mutT("accent"), mutT("ten"), mutT("marcato"),
                mutT("trill"), mutT("mord"), mutT("turn"), mutT("trem"), mutT("fermata"),
                mutT("grace"), mutT("cue"), mutT("repeatBegin"), mutT("repeatEnd"), mutT("clef"),
                mutT("meter"), mutT("key"), mutT("oct"), mutT("staff"), mutT("beamsAuto"),
                mutT("beamsOff"), mutT("stemsAuto"), mutT("stemsUp"), mutT("stemsDown"), mutT("doubleBar"),
                mutT("tactus"), mutT("title"), mutT("composer"), mutT("mark"), mutT("label"),
                mutT("alter"), mutT("mutabor")
        };

const mutChar * TagShorts[NTAGSHORTS] =
        {
                mutT(""), mutT("i"), mutT("sl"), mutT("bm"), mutT("t"), mutT("|")
        };

GisToken *Root;

GisToken **Current, *LastOpenBracket;

GisTagBegin *LastOpenRange;

char TagMode;

mutString TagName;

mutString TagSep;

GisToken *Para, *LastPara;

int LastOctave;

frac LastDuration;

#ifdef DEBUG
int debugcount = 0;

#define GISDEBUG(para) \
  DEBUGLOG2(other,_T("")); std::cerr << para << std::endl;
//cout << para;
#else
#define GISDEBUG(para)
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

int Name2Key(const mutString name)
{
	mutChar notes[] = mutT("c d ef g a b");
	size_t l = mutLen(name);
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

int Acc2Int(const mutString acc)

{
	if ( !acc ) return 0;

	int i = 0;

#ifdef WX
	for (size_t j = 0; j < mutLen(acc); j++)
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
	char s[2] = "w";
	s[0] = a;
	return strdup(s);
}

#endif

GisNote::GisNote(int key, int octave, int acc, mutString sep, GisToken *next)
		: GisToken(sep, next)
{
	if ( key == NO_KEY ) {
#ifdef WX
		Name = mutT("_");
#else
		Name = strdup("_");
#endif
		Accedentials = mutEmptyString;
		;
		Octave = 0;
	} else {
		mutChar Flats[]   = mutT("cddeefggaabb");
		mutChar FlatsA[]  = mutT(" & &  & & & ");
		mutChar Sharps[]  = mutT("ccddeffggaab");
		mutChar SharpsA[] = mutT(" # #  # # # ");
		mutChar accs;
		int Index = key % 12;
		int Abstand = key /12;

		if ( Index < 0 ) {
			Index += 12;
			Abstand--;
		}

		if ( acc < 0 ) {
			Name = strdupchr(Flats[Index]);
			accs = FlatsA[Index];
		} else {
			Name = strdupchr(Sharps[Index]);
			accs = SharpsA[Index];
		}

		if ( accs != mutT(' ') )
			Accedentials = strdupchr(accs);
		else
			Accedentials = mutEmptyString;

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
void Clear(mutString * s)
{
	*s = mutEmptyString;
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
	DEBUGLOG2(other,_T("TagName.len %d, '%s'"),TagName.Len(),TagName.c_str());
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
	DEBUGLOG2(other,_T("saving Sep %s"),Sep.c_str());
	*Current = new GisToken(Sep, 0);
	Current = &((*Current)->Next);
	return 0;
};

int BeginSegment()
{
	GISDEBUG("{")

	if ( TagMode ) BuildTag();

	GisSegment *Seg = new GisSegment(0, Sep, LastOpenBracket);

	LastOpenBracket = Seg;

	*Current = Seg;

	Current = &(Seg->Contents);

	return 0;
};

int EndSegment()
{
	GISDEBUG("}\n")

	if ( TagMode ) BuildTag();

	*Current = 0;

	mutCopyString(((GisSegment*)(LastOpenBracket))->Sep2, Sep);

	Current = &(LastOpenBracket->Next);

	LastOpenBracket = LastOpenBracket->Next;

	return 0;
};

int BeginSequenz()
{
	GISDEBUG("[")

	if ( TagMode ) BuildTag();

	GisSequenz *Seq = new GisSequenz(0, Sep, LastOpenBracket);

	LastOpenBracket = Seq;

	*Current = Seq;

	Current = &(Seq->Contents);

	return 0;
};

int EndSequenz()
{
	GISDEBUG("]\n")

	if ( TagMode ) BuildTag();

	*Current = 0;

	mutCopyString(((GisSequenz*)LastOpenBracket)->Sep2, Sep);

	Current = &(LastOpenBracket->Next);

	LastOpenBracket = LastOpenBracket->Next;

	return 0;
};

int BeginParameter()
{
	GISDEBUG("<")
	AddStr(TagSep, mutT("<"), Sep);
	return 0;
};

int EndParameter()
{
	GISDEBUG(">")

	if ( Para )
		AddStr((LastPara->Sep), mutT(">"), Sep);
	else
		AddStr(TagSep, mutT(">"), Sep);

	return 0;
};

int BeginRange()
{
	GISDEBUG("( ")

	if ( LastPara )
		AddStr(LastPara->Sep, mutT("("), Sep);
	else if ( Para )
		AddStr(Para->Sep, mutT("("), Sep);
	else
		AddStr(TagSep, mutT("("), Sep);

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
};

int EndRange()
{
	GISDEBUG(")\n")

	if ( TagMode ) BuildTag();

	GisTagEnd *Tag = new GisTagEnd(LastOpenRange, Sep);

	*Current = Tag;

	Current = &(Tag->Next);

	LastOpenRange = (GisTagBegin*) LastOpenRange->End;

	(Tag->Begin)->End = Tag;

	return 0;
};

int NextSequenz()
{
	GISDEBUG(", ");

	if ( TagMode ) BuildTag();

	return 0;
};

int Note(const mutString name, const mutString accedentials, int octave, frac duration)
{
	DEBUGLOG2(other,_T("Note '%s' %s Oktave %d "),
	          name.c_str(),
	          accedentials.c_str(),
	          octave);
	GISDEBUG(name << accedentials << octave << "*" << duration << " ")

	if ( TagMode ) BuildTag();

	GisNote *Note = new GisNote(name, accedentials, octave, duration, Sep);

	*Current = Note;

	Current = &(Note->Next);

	return 0;
};

int Tag(const mutString tagName)
{
	GISDEBUG("\n\\" << tagName)

	if ( TagMode ) BuildTag();

	mutCopyString(TagName, tagName);

	mutCopyString(TagSep, Sep);

	TagMode = 1;

	return 0;
};

int TagParaInt(long i)
{
	GISDEBUG("ParaInt: " << i << ", ")
	GisParaInt *p = new GisParaInt(i, Sep);

	if ( LastPara )
		LastPara->Next = p;
	else
		Para = p;

	LastPara = p;

	return 0;
};

int TagParaReal(double x)
{
	GISDEBUG("ParaReal: " << x << ", ")
	GisParaReal *p = new GisParaReal(x, Sep, 0);

	if ( LastPara )
		LastPara->Next = p;
	else
		Para = p;

	LastPara = p;

	return 0;
};

int TagParaStr(mutString s)
{
	GISDEBUG("ParaStr: " << """" << s << """" << ", ")
	GisParaStr *p = new GisParaStr(s, Sep, 0);

	if ( LastPara )
		LastPara->Next = p;
	else
		Para = p;

	LastPara = p;

	return 0;
};

int Comma()
{
	GISDEBUG(", ")

	if ( TagMode ) BuildTag();

	*Current = new GisComma(Sep, 0);

	Current = &((*Current)->Next);

	return 0;
};

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

int GetTagId(const mutString &name, mutString &registered)

{
	if (!name) {
		registered = Tags[0];
		return 0;
	}

	// check normal form
	int i;

	for (i = 0; i < NTAGS; i++) {
		if ( mutStrEq2(wxString(name), Tags[i]) ) {
			registered = Tags[i];
			return i;
		} ;
	}

	// check short form
	for (i = 0; i < NTAGSHORTS; i++) {
		DEBUGLOG2(other,_T("comparing '%s' with tag'%s'"),name.c_str(),Tags[i]);

		if ( mutStrEq2(name, TagShorts[i]) ) {
			registered = TagShorts[i];
			return i;
		}
	}

	// no registered tag
	registered = mutEmptyString;

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

GisToken *GisParse(const mutString FileName)
{
	Root = 0;
	Current = &Root;
	LastOpenBracket = 0;
	LastOpenRange = 0;
	TagMode = 0;
	TagName = mutEmptyString;
	TagSep = mutEmptyString;
	Para = 0;
	LastPara = 0;
	DEBUGLOG2(other,_T("TagName.len %d, '%s'"),TagName.Len(),TagName.c_str());

	if ( GspParse(FileName) ) {
		UnRavel();
		delete Root;
		Root = 0;
	}

	return Root;
}

#ifdef WX
wxString GISPrettyPrint(wxString s)
{
	wxString ret = wxEmptyString;
	wxString pre = wxEmptyString;

	for (size_t start = 0, current = 0 ; current < s.Len(); current++) {
		wxChar c = s[current];

		if (c == _T('{')) {
			pre += _T("  ");
		} else if (c == _T('}')) {
			if (pre.Len() >= 2) pre = pre.Left(pre.Len()-2);
		} else if (c == _T('\n')) {
			ret += s (start, current - start + 1) + pre;
			start = current + 1;
		}
	}

	return ret;
}

#endif

///\}
