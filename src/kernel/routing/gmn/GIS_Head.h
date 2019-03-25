//     -*- C++ -*-
/** \file
********************************************************************
* Description
*
* Copyright:   (c) 2008 TU Dresden
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
*
********************************************************************
* \addtogroup route
* \{
********************************************************************/

// #################################################################
// header file for read header for GIS (GMN Intern Structur)
// ##################################################################

/* we guard a little bit complicated to ensure the references are set right
 */

#if (!defined(MU32_ROUTING_GMN_GIS_HEAD_H) && !defined(PRECOMPILE))	\
	|| (!defined(MU32_ROUTING_GMN_GIS_HEAD_H_PRECOMPILED))
#ifndef PRECOMPILE
#define MU32_ROUTING_GMN_GIS_HEAD_H
#endif

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

#include "src/kernel/Defs.h"
#include "src/kernel/Frac.h"
#include "src/kernel/routing/Box.h"
#include "src/kernel/routing/gmn/GIS.h"

#ifndef MU32_ROUTING_GMN_GIS_HEAD_H_PRECOMPILED
#define MU32_ROUTING_GMN_GIS_HEAD_H_PRECOMPILED

// system headers which do seldom change

#include "stdint.h"

// arcticulation modes
enum ARType { ARNormal, ARSlur, ARTenuto, ARPortato, ARStaccatto };

// GisReadHead ------------------------------------------------------

class GisReadHead
{

public:
	GisReadHead *Next, **PrevPtr, *Prev; // double chained, first Prev points to its own adress
	GisReadHead *Boss;
	int nSub;
	GisToken *Cursor;
	mutabor::frac Time;
	std::string Id;
	char Turn;
	bool SingleToken; // proceed only one token (in accords)

	GisReadHead(GisReadHead *boss, GisToken *cursor, const std::string &id, bool singleToken = false):
		Turn (0)
		{
			PrevPtr = &Prev;
			DEBUGLOG (gmnfile, "boss = %p" ,(void *)boss);
			Next = Prev = NULL;
			Cursor = cursor;
			Id = id;
			InsertInfrontOf(boss);
			Boss = boss;
			nSub = -1;
			Time = mutabor::frac(0, 1);
			SingleToken = singleToken;
		}

	virtual ~GisReadHead()

		{
			if ( Next ) delete Next; // only the following will be deleted
		}

	virtual GisReadHead *Build(GisReadHead *boss, GisToken *cursor, const std::string &id, bool singleToken = false)
		{
			return new GisReadHead(boss, cursor, id, singleToken);
		}

	GisReadHead *InsertInfrontOf(GisReadHead *position);

	GisReadHead *CutOut();
	GisToken *CursorNext() // move Cursor, care for single token mode
		{
			Turn = 0;

			if ( !Cursor )
				return 0;

			if ( SingleToken && Cursor->Type() == GTComma)
				Cursor = 0;
			else
				Cursor = Cursor->Next;

			return Cursor;
		}
	void CreateSegmentSubs();
	void CreateSequenzSubs();
	void Read();
	operator std::string()
		{
			if (Next)
				return ToString() + (std::string) (*Next) ;
			else
				return ToString();
		}

	virtual std::string ToString();

};

typedef void GisReadProceed(GisReadHead*, char) ;

extern GisReadProceed GisReadDummy;

mutabor::frac GisReadHeadOn(GisReadHead **Head,
			    mutabor::frac dTime = mutabor::frac(0, 1),
			    GisReadProceed *proceed = GisReadDummy);

// TagList ----------------------------------------------------------

typedef struct TagListData
{

	struct TagListData *Next;
	GisTag *Tag;
	union data
	{
		char ch;
		mutint64 i; ///\todo find a more efficient way to do this
	} Data;
} TagList;

TagList *Copy(TagList *tag);
void Erase(TagList *tag);

// GisReadArtHead -----------------------------------------------------

class GisReadArtHead : public GisReadHead
{

public:
	mutabor::frac Time2;
	boost::chrono::microseconds Delta; // in μs
	mutabor::Box Box;

private:
	TagList *Intensity;
	TagList *Articulation;
	TagList *Octave;
	TagList *Alter;
	TagList *Instr;
	TagList *Tempo;

public:

	GisReadArtHead(GisReadArtHead *boss, GisToken *cursor, const std::string id, bool singleToken = false)
		: GisReadHead(boss, cursor, id, singleToken)
		{
			DEBUGLOG (gmnfile, "boss = %p" , (void *)boss);
			DEBUGLOG (gmnfile, "cursor = %p" , (void *)cursor);

			if ( boss ) {
				Intensity = Copy(boss->Intensity);
				Articulation = Copy(boss->Articulation);
				Octave = Copy(boss->Octave);
				Alter = Copy(boss->Alter);
				Instr = Copy(boss->Instr);
				Tempo = Copy(boss->Tempo);
				Box = boss->Box;
			} else {
				Intensity = NULL;
				Articulation = NULL;
				Octave = NULL;
				Alter = NULL;
				Instr = NULL;
				Tempo = NULL;
				Box.reset();
			}

			Time2 = 0;

			Delta = boost::chrono::microseconds::zero();
			Turn = 0;
		}

	~GisReadArtHead()

		{
			Erase(Intensity);
			Erase(Articulation);
			Erase(Octave);
			Erase(Alter);
			Erase(Instr);
			Erase(Tempo);
		}

	virtual GisReadHead *Build(GisReadHead *boss, GisToken *cursor, const std::string & id, bool singleToken = false)
		{
			mutASSERT(!boss
				  || dynamic_cast<GisReadArtHead*>(boss));
			return new GisReadArtHead(static_cast<GisReadArtHead*>(boss),
						  cursor, id, singleToken);
		}

	void Read();

	ARType GetArticulation()
		{
			if ( Articulation )
				return (ARType) Articulation->Data.ch;
			else
				return ARNormal;
		}

	char GetIntensity(char noteOff = 0)
		{
			if ( !noteOff ) {
				if ( Intensity )
					return Intensity->Data.ch;
				else
					return 80;
			} else {
				if ( GetArticulation() >= ARPortato )
					return 127;
				else
					return 60;
			}
		}

	int GetOctave()
		{
			if ( Octave )
				return Octave->Data.i;
			else
				return 0;
		}

	int GetAlter()
		{
			if ( Alter )
				return Alter->Data.i;
			else
				return 0;
		}

	int GetInstr()
		{
			if ( Instr )
				return Instr->Data.ch;
			else
				return -1;
		}

	int GetSpeedFactor()
		{
			DEBUGLOG (gmnfile, "Tempo: %p" ,(void *)Tempo);

			if (Tempo) {
				DEBUGLOG (gmnfile, "Tempo->Data.i: %ld" ,Tempo->Data.i);
				return Tempo->Data.i;
			}
			else
				return 2000;
		}

	operator std::string()
		{
			if (Next)
				return ToString() + (std::string) (*Next) ;
			else
				return ToString();
		}

	virtual std::string ToString();
};

typedef void GisReadArtProceed(GisReadArtHead* token, char turn) ;

extern GisReadArtProceed GisReadArtDummy;

mutabor::frac GisReadArtHeadOn(GisReadArtHead **Head,
			       mutabor::frac dTime = mutabor::frac(0, 1),
			       GisReadArtProceed *proceed = GisReadArtDummy);

// GisWriteHead -----------------------------------------------------

class ChordNote;

class GisWriteHead
{

public:
	GisWriteHead *Next, *Prev; // double chained, first Prev points to its on adress
	GisWriteHead *Boss;
	int nSub;
	GisToken *Data, **Cursor;
	mutabor::frac TotalTime, CurrentTime;
	std::string Id;
	char SingleToken; // proceed only one token (in accords)
	GisToken **ChordPos;
	ChordNote *ChordNotes;
	char NoteOn;
	char CommaAtEnd;
	TagList *Octave;
	TagList *Key;

	GisWriteHead(GisWriteHead *boss, const std::string id):
		ChordPos(0)
		{
			Prev = 0;
			Next = 0;
			Data = 0;
			Cursor = &Data;
			CHECKDUP(Id, id);
			Boss = boss;

			if ( boss ) {
				if ( boss->nSub == -1 )
					boss->nSub = 1;
				else
					boss->nSub++;
			}

			nSub = -1;

			TotalTime = mutabor::frac(0, 1);
			CurrentTime = mutabor::frac(0, 1);
			SingleToken = (boss && boss->State() == GTSegment);
			ChordNotes = 0;
			NoteOn = 0;
			CommaAtEnd = 0;
			Octave = 0;
			Key = 0;
		}

	~GisWriteHead()

		{
			Erase(Octave);
			Erase(Key);

			if ( Next ) delete Next; // only the following will be deleted
		}

	GisWriteHead *InsertAfter(GisWriteHead *position);
	GisWriteHead *CutOut();
	GisType State()
		{
			if ( *Cursor )
				return (*Cursor)->Type();
			else
				return GTNull;
		}

	ChordNote *GetFreeNote();
	ChordNote *GetNote(int instrId, int taste);
	int ReadyForBoss();
	void RemoveComma();
	int CloseSubs(GisToken **cont = 0);
	int CloseCurrentToken(char insertRest = 1);
	int ProceedGis(GisToken *token, char turn = 0);  // returns error code, 0 means OK
	void WriteChord();
	void AddTime(mutabor::frac dTime);
	int GetOctave()
		{
			if ( Octave )
				return Octave->Data.i;
			else
				return 0;
		}

	int GetKey()
		{
			if ( Key )
				return Key->Data.i;
			else
				return 0;
		}
};


int GisWriteHeadGis(GisWriteHead **head, std::string id, GisToken *token, char turn);

/*
  int GisWriteAlteredNoteOn(GisWriteHead **head,  char *id, long freq, int noteId,
  int octave, int acc, char *Sep);
  int GisWriteAlteredNoteOff(GisWriteHead **head,  char *id, int noteId);
*/
// search the header with the matching Id
GisWriteHead *GetMatchingHeader(GisWriteHead **head, std::string id);

void CloseAllSubs(GisWriteHead *head);

/*
  class MisTrack;

  int GisWriteHeadMis(GisWriteHead **head, char *id, DWORD midi, MisTrack* track);
*/

#define CNAlter  1  // ChordNote - status
#define CNNoteOn 2

// ------------------------------------------------------------------
// ChordNote - buffer element for writing notes
// The identity of a ChordNote depends on InstrId, Key and Pitch.

class ChordNote
{

public:
	ChordNote *Next;
	GisToken *Data;
	GisToken **Cursor;
	GisWriteHead *Boss;
	mutabor::frac CurrentTime;
	mutabor::frac TotalTime;
	GisToken **BossPos;
	int InstrId;
	char Status;
	GisToken **AlterBegin;
	GisToken **TieBegin;
	int nTie;  // number of notes in tie
	std::string *LastSep;
	int Taste;     // original pressed key
	int Key;       // outputed key
	double Pitch;  // corresponding pitch
	ChordNote(GisWriteHead *boss) // first ChordNote of a WriteHead
	{
		Boss = boss;
		BossPos = Boss->Cursor;
		Next = 0;
		TotalTime = Boss->CurrentTime;
		Data = 0;
		Cursor = &Data;

		if ( (bool) TotalTime )
			AddGis(new GisNote("_",
					   "",
					   0,
					   TotalTime,
					   " ", 0));

		CurrentTime = 0;
		Boss->ChordPos = Boss->Cursor;
		Status = 0;
		TieBegin = 0;
		AlterBegin = 0;
		nTie = 0;
		LastSep = 0;
		InstrId = -1;
		Taste = GMN_NO_KEY;
		Key = GMN_NO_KEY;
		Pitch = 0;
	}

	ChordNote(ChordNote *first); // not the first ChordNote
	~ChordNote()
		{
			if ( Data ) delete Data;

			if ( Next ) delete Next;
		}

	void CountOnTime(mutabor::frac dTime);
	void SetNoteOn(GisToken *note);
	int SetNoteOff(GisToken *note); // returns 1, when note was finished, else 0
	void AddGis(GisToken *token);
	void CheckCloseAlter();
	void CheckCloseTie();
	void CheckClose()
		{
			CheckCloseAlter();
			CheckCloseTie();
		}

	int MutNoteOn(int key, double pitch, int instrId, int taste, std::string sep);
	int MutNoteOff();
	char CheckId(int instrId, int taste)
		{
			return (InstrId == instrId) && (Taste == taste);
		}

	char Cmp(int key, double pitch)
		{
			if ( key != GMN_NO_KEY )
				return Key == GMN_NO_KEY;

			if ( (double)key + pitch == (double)Key + Pitch )
				return 1;
			else
				return 0;
		}
};


#endif /* precompiled */
#endif


///\}
