// #################################################################
// header file for read header for GIS (GMN Intern Structur)
// ##################################################################

#ifndef GIS_HEAD_H
#define GIS_HEAD_H

#include "GIS.h"

// arcticulation modes
enum ARType { ARNormal, ARSlur, ARTenuto, ARPortato, ARStaccatto };

// GisReadHead ------------------------------------------------------

class GisReadHead
{
  public:
	 GisReadHead *Next, *Prev; // double chained, first Prev points to its own adress
	 GisReadHead *Boss;
	 int nSub;
	 GisToken *Cursor;
	 frac Time;
	 char *Id;
    char Turn;
	 char SingleToken; // proceed only one token (in accords)
	 GisReadHead(GisReadHead *boss, GisToken *cursor, char *id, char singleToken = 0)
	 {
		Cursor = cursor;
		Id = strdup(id);
		InsertInfrontOf(boss);
		Boss = boss;
		nSub = -1;
		Time = frac(0, 1);
		SingleToken = singleToken;
	 }
	 ~GisReadHead()
	 {
		if ( Id ) free(Id);
		if ( Next ) delete Next; // only the following will be deleted
	 }
    virtual GisReadHead *Build(GisReadHead *boss, GisToken *cursor, char *id, char singleToken = 0)
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
};

typedef void GisReadProceed(GisReadHead*, char) ;

extern GisReadProceed GisReadDummy;

frac GisReadHeadOn(GisReadHead **Head, frac dTime = frac(0, 1), GisReadProceed *proceed = GisReadDummy);

// TagList ----------------------------------------------------------

typedef struct TagListData
{
  struct TagListData *Next;
  GisTag *Tag;
  union data
  {
    char ch;
	  int i;
  } Data;
} TagList;

TagList *Copy(TagList *tag);
void Erase(TagList *tag);

// GisReadArtHead -----------------------------------------------------

class GisReadArtHead : public GisReadHead
{
  public:
	 frac Time2;
   long Delta; // in 2ms-Ticks
	 int Box;
  private:
	 TagList *Intensity;
	 TagList *Articulation;
	 TagList *Octave;
	 TagList *Alter;
	 TagList *Instr;
	 TagList *Tempo;
  public:
	 GisReadArtHead(GisReadArtHead *boss, GisToken *cursor, char *id, char singleToken = 0)
	 : GisReadHead(boss, cursor, id, singleToken)
	 {
		if ( boss )
		{
		  Intensity = Copy(boss->Intensity);
		  Articulation = Copy(boss->Articulation);
		  Octave = Copy(boss->Octave);
		  Alter = Copy(boss->Alter);
		  Instr = Copy(boss->Instr);
		  Tempo = Copy(boss->Tempo);
		  Box = boss->Box;
		}
		else
		{
		  Intensity = 0;
		  Articulation = 0;
		  Octave = 0;
		  Alter = 0;
		  Instr = 0;
		  Tempo = 0;
		  Box = 0;
		}
		Time2 = 0;
		Delta = 0;
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
	 virtual GisReadHead *Build(GisReadHead *boss, GisToken *cursor, char *id, char singleToken = 0)
    {
      return new GisReadArtHead((GisReadArtHead*)boss, cursor, id, singleToken);
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
      if ( !noteOff )
      {
		  if ( Intensity )
          return Intensity->Data.ch;
		  else
          return 80;
      }
      else
      {
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
      if ( Tempo )
        return Tempo->Data.i;
 		  else
        return 2000;
	  }
};

typedef void GisReadArtProceed(GisReadArtHead* token, char turn) ;

extern GisReadArtProceed GisReadArtDummy;

frac GisReadArtHeadOn(GisReadArtHead **Head, frac dTime = frac(0, 1), GisReadArtProceed *proceed = GisReadArtDummy);

// GisWriteHead -----------------------------------------------------

class ChordNote;

class GisWriteHead
{
  public:
	 GisWriteHead *Next, *Prev; // double chained, first Prev points to its on adress
	 GisWriteHead *Boss;
	 int nSub;
    GisToken *Data, **Cursor;
	 frac TotalTime, CurrentTime;
	 char *Id;
	 char SingleToken; // proceed only one token (in accords)
	 GisToken **ChordPos;
	 ChordNote *ChordNotes;
	 char NoteOn;
	 char CommaAtEnd;
	 TagList *Octave;
	 TagList *Key;
	 GisWriteHead(GisWriteHead *boss, char *id)
	 {
		Prev = 0;
		Next = 0;
		Data = 0;
		Cursor = &Data;
		CHECKDUP(Id, id);
		Boss = boss;
		if ( boss )
		  if ( boss->nSub == -1 )
			 boss->nSub = 1;
		  else
			 boss->nSub++;
		nSub = -1;
		TotalTime = frac(0, 1);
		CurrentTime = frac(0, 1);
		SingleToken = (boss && boss->State() == GTSegment);
		ChordNotes = 0;
		NoteOn = 0;
		CommaAtEnd = 0;
		Octave = 0;
		Key = 0;
	 }
	 ~GisWriteHead()
	 {
		if ( Id ) free(Id);
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
	 void AddTime(frac dTime);
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


int GisWriteHeadGis(GisWriteHead **head, char *id, GisToken *token, char turn);
/*
int GisWriteAlteredNoteOn(GisWriteHead **head,  char *id, long freq, int noteId,
  int octave, int acc, char *Sep);
int GisWriteAlteredNoteOff(GisWriteHead **head,  char *id, int noteId);
*/
// search the header with the matching Id
GisWriteHead *GetMatchingHeader(GisWriteHead **head, char *id);
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
	 frac CurrentTime;
	 frac TotalTime;
	 GisToken **BossPos;
	 int InstrId;
	 char Status;
	 GisToken **AlterBegin;
	 GisToken **TieBegin;
	 int nTie;  // number of notes in tie
	 char **LastSep;
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
		if ( TotalTime.n )
		  AddGis(new GisNote("_", 0, 0, TotalTime, " ", 0));
		CurrentTime = 0;
		Boss->ChordPos = Boss->Cursor;
		Status = 0;
		TieBegin = 0;
		nTie = 0;
		LastSep = 0;
		InstrId = -1;
		Taste = NO_KEY;
		Key = NO_KEY;
		Pitch = 0;
	 }
	 ChordNote(ChordNote *first); // not the first ChordNote
	 ~ChordNote()
	 {
		if ( Data ) delete Data;
		if ( Next ) delete Next;
	 }
	 void CountOnTime(frac dTime);
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
	 int MutNoteOn(int key, double pitch, int instrId, int taste, char *sep);
	 int MutNoteOff();
	 char CheckId(int instrId, int taste)
	 {
		return (InstrId == instrId) && (Taste == taste);
	 }
	 char Cmp(int key, double pitch)
	 {
		if ( key != NO_KEY )
		  return Key == NO_KEY;
		if ( (double)key + pitch == (double)Key + Pitch )
		  return 1;
		else
		  return 0;
	 }
};


#endif

