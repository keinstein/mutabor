// #################################################################
// provides read header for GIS (GMN Intern Structur)
// ##################################################################

#include "GIS_Head.h"
#include <stdlib.h>

#if defined(WX)
  #include <wx/string.h>
#else
  #include <string.h>
  #define muT(x) x
#endif

char ArticulationHold[5] = { 80, 100, 90, 90, 60 }; // range: 0-100
char ArticulationOff[5] = { 80, 80, 60, 127, 127 }; // range: 0-127

// ------------------------------------------------------------------
// help functions

double GetReal(GisToken *token)
{
  if ( GetGisType(token) == GTParaInt )
	 return (double) ((GisParaInt*)token)->i;
  else if ( GetGisType(token) == GTParaReal )
	 return ((GisParaReal*)token)->x;
  return 0;
}

char GetMidiInstrument(GisToken *token)
{
  if ( token && GetGisType(token) == GTParaStr )
  {
   mutString t;
#if defined(WX) 
   mutString v;
   long value;
   t=(((GisParaStr*)token)->s).Upper();
   DEBUGLOG2(_T("t= %s"), t.c_str());
   if (t.StartsWith(mutT("MIDI"),&v)) {
     v.ToLong(&value);
     DEBUGLOG2(_T("v= %s"), v.c_str());
     return (char) value;
   }
#else
   strncpy(t, ((GisParaStr*)token)->s, 30);
   strupr(t);
   if ( !strncmp(t, "MIDI", 4) )
	   return atoi(&t[4]);
#endif
  }
  return 0;
}

#define ZIFFER (mutT('0') <= t[i] && t[i] <= mutT('9'))
int GetTheSpeedFactor(GisToken *token)
{
  DEBUGLOG2(_T("%p"),token);
  if ( token && GetGisType(token) == GTParaStr )
  {
    const mutString &t = ((GisParaStr*) token) -> s;
    DEBUGLOG2(_T("%s"),t.c_str());
    int i = 0;
    long n=0, d=0, bpm=0;
    while ( !ZIFFER && t[i] )
      i++;
    while ( ZIFFER )
      n = n*10 + (t[i++]-mutT('0'));
    while ( !ZIFFER && t[i] )
      i++;
    while ( ZIFFER )
      d = d*10 + (t[i++]-mutT('0'));
    while ( !ZIFFER && t[i] )
      i++;
    while ( ZIFFER )
      bpm = bpm*10 + (t[i++]-mutT('0'));
    DEBUGLOG2(_T("%d * 30000 / %d / %d"),d,n,bpm);
    if ( !n || !d || bpm < 4 )
      return 2000;
    else
      return d * 30000 / n / bpm;
  }
  return 2000;
}

// ##################################################################
// methods of GisReadHead

GisReadHead* GisReadHead::InsertInfrontOf(GisReadHead *position)
{
  DEBUGLOG(_T("pos = %p; this = %p"),position,this);
  if ( !position )
  {
	 Next = NULL;
	 Prev = this;
	 return this;
  }
#if 1
  // *(position->Prev) == position
  if ( *(position->PrevPtr) == position ) { // first position
      DEBUGLOG(_T("first position %p, Prev: %p, Next: %p, cmp: %p"),
	       position,
	       position->Prev,
	       position->Next,
	       *((position->PrevPtr))
	       );
      *(position->PrevPtr) = this;
    } else { // normal position in list
      DEBUGLOG(_T("first position %p, Prev: %p, Next: %p, cmp: %p"),
	       position,
	       position->Prev,
	       position->Next,
	       *((GisReadHead**)(position->PrevPtr))
	       );
      (*(position->PrevPtr))->Next = this;
    }
    PrevPtr = position->PrevPtr;
    Next = position;
    *(position->PrevPtr) = this;
    return this;
#else
  DEBUGLOG(_T("pos = %p, prev = %p"),position, position->Prev);
  if ( (position -> Prev) == position) {
    Prev = this;
  } else {
    Prev = position -> Prev; 
    position->Prev->Next = this;
  }
  Next = position;
  Next->Prev = this;
  return this;
#endif
}

GisReadHead* GisReadHead::CutOut()
{
#if 1
  if ( *(PrevPtr) == this ) // first of list
  {
    *PrevPtr = Next;
  }
  else // normal list postition
  {
    (*PrevPtr)->Next = Next;
  }
  if ( Next ) Next->PrevPtr = PrevPtr;
  Next = NULL;
  PrevPtr = &Prev;
  return this;
#else
  if ( Prev == this ) // first of list
  {
    if (Next) Next->Prev = Next;
  } else {  // normal list postition
    Prev->Next = Next;
    if ( Next ) Next->Prev = Prev;
  }
  Next = 0;
  Prev = 0;
  return this;
#endif
}

// create segment subs, insert infront of this
void GisReadHead::CreateSegmentSubs()
{
  GisSegment *Seg = (GisSegment*)Cursor;
  GisToken *Cont = Seg->Contents;
#ifdef WX
  mutString id = Id + mutT("*");
#else
  char *id = (char*)malloc(strlen(Id)+2);
  strcpy(id, Id);
  strcat(id, "*");
#endif
  nSub = 0;
  while ( Cont ) // create the single token subs
  {
	 nSub++;
	 id[mutLen(Id)] = nSub;
	 DEBUGLOG(_T("Creating Sub for %p (%d, %s)"),Cont,nSub,id.c_str());
	 
	 GisReadHead *Sub = Build(this, Cont, id, 1);
	 Cont = Cont->Next;
	 while ( Cont ) // read until end or comma
	 {
		if ( Cont->Type() == GTComma )
		{
		  Cont = Cont->Next;
		  break;
		}
		Cont = Cont->Next;
	 }
  }
}

// create sequenz subs, insert infront of this
void GisReadHead::CreateSequenzSubs()
{
  GisSegment *Seq = (GisSegment*)Cursor;
#ifdef WX
  mutString id = Id + mutT("\x01");
#else
  char *id = (char*)malloc(strlen(Id)+2);
  strcpy(id, Id);
  strcat(id, "\x01");
#endif
  nSub = 1;
  GisReadHead *Sub = Build(this, Seq->Contents, id);
}

// reading the token at the cursor
void GisReadHead::Read()
{
  DEBUGLOG(_T("Cursor: %p"),Cursor);
  if ( !Cursor ) return;
  switch ( Cursor->Type() )
  {
	 case GTSegment: CreateSegmentSubs(); break;
	 case GTSequenz: CreateSequenzSubs(); break;
	 case GTNote: 
	   DEBUGLOG(_T("Setting time"));
	   Time = ((GisNote*)Cursor)->Duration; 
	   break;
  }
  // the other tokens dont influenz the way of reading
}

#ifdef WX
wxString GisReadHead::ToString() {
  wxString ret = wxString::Format(_T("GisReadHead: {\nthis: %p; Boss: %p; Next: %p; Prev: %p; PrevPtr: %p; *PrevPtr: %p;\n"
				     "nSub: %d; Cursor: {\n"),
				  this, Boss, Next, Prev, 
				  PrevPtr, *PrevPtr, nSub) +
    (Cursor?((wxString) *Cursor):wxString(_T(""))) + _T("}\nTime: ") + ((wxString) Time) + 
    wxString::Format(_T("; Id: '%s'; Turn: %d; SingleToken: %d\n}\n"),
		     Id.c_str(), Turn, SingleToken);
  return ret;
}
#endif

// ##################################################################
// procedures with GisReadHead

// dummy procedure for GisReadHeadOn
void GisReadDummy(GisReadHead*, char)
{
  // just a dummy
}

// ReadOn the GisReadHead, chained
frac GisReadHeadOn(GisReadHead **Head, frac dTime, GisReadProceed *proceed)
{
  frac MinTime = frac(-1, 1);
  beginloop:
  while ( *Head )
  {
	 GisReadHead *h = *Head;
	 if ( h->nSub > 0 ) // header has subs
	 {
		Head = &(h->Next);
		continue;
	 }
	 if ( h->nSub == 0 ) // all subs has finished
	 {
		proceed(h, 1);
		h->CursorNext();
		h->Time = 0;
	 }
	 if ( h->Time != frac(0, 1) ) // header in normal state
	 {
		h->Time -= dTime;
		if ( h->Time <= frac(0, 1) )
		{
		  proceed(h, 1);
		  h->CursorNext();
		}
	 }
	 h->nSub = -1; // normal header
	 // now check, wether count down Time is 0
	 // if h->time = 0 then h->Cursor points to the GisToken next to proceed
	 while ( h->Time.n == 0 ) // read next tokens
	 {
		if ( !h->Cursor ) // header finished, kick away
		{
		  h->CutOut();
		  if ( h->Boss ) h->Boss->nSub--; // inform the boss
		  delete h;
		  goto beginloop;
		}
		// proceed
		proceed(h, 0);
		h->Read();
		if ( h->nSub != -1 ) goto beginloop;
		if ( h->Time.n == 0 ) // token without duration
		  h->CursorNext();
	 }
	 // check MinTime
	 if ( MinTime == frac(-1,1) || h->Time < MinTime )
		MinTime = h->Time;
	 // next Header
	 Head = &(h->Next);
  }
  return MinTime;
}

// ##################################################################
// GisReadArtHead

// TagList ----------------------------------------------------------

TagList *Copy(TagList *list)
{
  if ( !list ) return 0;
  TagList *List = new TagList;
  List->Next = 0;
  List->Tag = list->Tag;
  List->Data = list->Data;
  return List;
}

void Erase(TagList *list)
{
  while ( list )
  {
	 TagList *TopTag = list;
	 list = TopTag->Next;
	 delete TopTag;
  }
}

TagList *RemoveTag(TagList **list)
{
  if ( *list )
  {
	 TagList *TopTag = *list;
	 *list = TopTag->Next;
	 delete TopTag;
  }
  return *list;
}

TagList *AddTag(TagList **list, GisTag *tag)
{
  if ( *list && (*list)->Tag->Type() == GTTag && tag->Type() == GTTag )
	 RemoveTag(list);
  TagList *TopTag = new TagList;
  TopTag->Next = *list;
  TopTag->Tag = tag;
  *list = TopTag;
  return *list;
}

TagList *EndTag(TagList **list, GisTagEnd *tagEnd)
{
  TagList *Pos = *list;
  if ( Pos && Pos->Tag->Type() == GTTag )
	 Pos = Pos->Next;
  if ( Pos && tagEnd->Begin == Pos->Tag )
  {
	 if ( Pos != *list )
		RemoveTag(list);
	 RemoveTag(list);
  }
  return *list;
}

#define TAG ((GisTag*)Cursor)
#define TAGEND ((GisTagEnd*)Cursor)
// reading the token at the cursor
void GisReadArtHead::Read()
{
  int Id = 0;
  DEBUGLOG(_T("Id: %d; Cursor: %p"), Id, Cursor);
  if ( !Cursor ) return;
  Turn = 3;
  DEBUGLOG(_T("Cursor->Type %d"), Cursor->Type());
  switch ( Cursor->Type() )
    {
    case GTSegment: CreateSegmentSubs(); Turn = 2; break;
    case GTSequenz: CreateSequenzSubs(); Turn = 2; break;
    case GTNote:
      Time2 = ((GisNote*)Cursor)->Duration;
      Time = Time2 * frac(ArticulationHold[GetArticulation()], 100);
      DEBUGLOG(_T("Time: %d/%d; Time2: %d/%d"),
	       Time.n,Time.d,Time2.n,Time2.d);
      Time2 -= Time;
      DEBUGLOG(_T("Time: %d/%d; Time2: %d/%d"),
	       Time.n,Time.d,Time2.n,Time2.d);
      Turn = 1;
      break;
    case GTTag:
    case GTTagBegin:
      Id = TAG->Id;
      if ( Id == TTintens )
	{
	  if ( TAG->GetParaType(2) == GTParaInt || TAG->GetParaType(2) == GTParaReal)
	    AddTag(&Intensity, TAG)->Data.ch = (char) (GetReal(TAG->GetPara(2)) * 127);
	}
      else if ( Id == TTaccent )
	{
	  AddTag(&Intensity, TAG)->Data.ch = 120; // ???  what value
	}
      else if ( Id == TTstacc )
	{
	  AddTag(&Articulation, TAG)->Data.ch = ARStaccatto;
	}
      else if ( Id == TTten )
	{
	  AddTag(&Articulation, TAG)->Data.ch = ARTenuto;
	}
      else if ( Id == TToct )
	{
	  if ( TAG->GetParaType(1) == GTParaInt )
	    AddTag(&Octave, TAG)->Data.i = ((GisParaInt*)TAG->GetPara(1))->i;
	}
      else if ( Id == TTalter )
	{
	  if ( TAG->GetParaType(1) != GTParaStr )
	    AddTag(&Alter, TAG)->Data.i = (int) (GetReal(TAG->GetPara(1)) * 0x1FFF) ;
	}
      else if ( Id == TTinstr )
	{
	  if ( TAG->GetParaType(2) == GTParaStr )
	    AddTag(&Instr, TAG)->Data.ch = GetMidiInstrument(TAG->GetPara(2));
	}
      else if ( Id == TTtempo )
	{
	  if ( TAG->GetParaType(2) == GTParaStr ) {
	    long int speed = 
	      (AddTag(&Tempo, TAG)->Data.i = 
	       GetTheSpeedFactor(TAG->GetPara(2)));
	    DEBUGLOG(_T("Got speed factor %ld"),speed); 
	  }
	}
      break;
    case GTTagEnd:
      DEBUGLOG(_T("Ended tag."));
      if ( !TAGEND->Begin )
	break;
      DEBUGLOG(_T("Tag Id was %d."),TAGEND->Begin->Id);
      Id = TAGEND->Begin->Id;
      if ( Id == TTintens || Id == TTaccent )
	EndTag(&Intensity, TAGEND);
      else if ( Id == TTstacc || Id == TTten )
	EndTag(&Articulation, TAGEND);
      else if ( Id == TToct )
	EndTag(&Octave, TAGEND);
      else if ( Id == TTalter )
	EndTag(&Alter, TAGEND);
      else if ( Id == TTinstr )
	EndTag(&Instr, TAGEND);
      else if ( Id == TTtempo )
	EndTag(&Tempo, TAGEND);
    }
  // the other tokens don't influenz the way of reading
}

#ifdef WX
wxString GisReadArtHead::ToString() {
  wxString ret = _T("GisReadArtHead: {\n") ;
  ret += GisReadHead::ToString();
  ret += _T("Time2: ") + ((wxString) Time2);
  ret += 
    wxString::Format(_T("; Delta: %ld; Box: %d\n"
			"Intensity: %p; Articulation: %p; Octave: %p\n"
			"Alter: %p; Instr: %p; Tempo: %p\n"
			"}\n"),
		     Delta,Box,
		     Intensity,Articulation,Octave,Alter,Instr,Tempo);
  return ret;
}
#endif


// ##################################################################
// procedures with GisReadHead

// dummy procedure for GisReadArtHeadOn
void GisReadArtDummy(GisReadArtHead*, char)
{
  // just a dummy
}

// ReadOn the GisReadArtHead, chained
frac GisReadArtHeadOn(GisReadArtHead **Head, frac dTime, GisReadArtProceed *proceed)
{
  DEBUGLOG2(_T(""));
  frac MinTime = frac(-1, 1);
  beginloop:
  while ( *Head )
  {
    GisReadArtHead *h = *Head;
    if ( h->nSub > 0 ) // header has subs
      {
	Head = (GisReadArtHead**)&(h->Next);
	continue;
      }
    if ( h->nSub == 0 ) // all subs has finished
      {
	proceed(h, h->Turn++);   // end of segment or sequenz
	h->CursorNext();
	h->Time = 0;
      }
    if ( h->Time != frac(0, 1) ) // header in normal state
      {
	h->Time -= dTime;
	if ( h->Time <= frac(0, 1) )
	  {
	    proceed(h, h->Turn++);
	    if ( h->Turn == 2 )
	      {
		h->Time = h->Time2;
		h->Time2 = 0;
	      }
	    if ( h->Turn > 2 )
	      h->CursorNext();
	  }
      }
    h->nSub = -1; // normal header
    // now check, wether count down Time is 0
    // if h->time = 0 then h->Cursor points to the GisToken next to proceed
    while ( h->Time.n == 0 ) // read next tokens
      {
	if ( h->Turn)
	  {
	    proceed(h, h->Turn++);
	    if ( h->Turn == 2 )
	      {
		h->Time = h->Time2;
		h->Time2 = 0;
	      }
	    if ( h->Turn > 2 )
	      h->CursorNext();
	    else
	      continue;
	  }
	if ( !h->Cursor ) // header finished, kick away
	  {
	    h->CutOut();
	    if ( h->Boss ) h->Boss->nSub--; // inform the boss
	    delete h;
	    goto beginloop;
	  }
	// proceed
	proceed(h, 0);
	h->Read();
	if ( h->nSub != -1 ) goto beginloop;
	if ( h->Time.n == 0 ) // token without duration
	  h->CursorNext();
      }
    // check MinTime
    if ( MinTime == frac(-1,1) || h->Time < MinTime )
      MinTime = h->Time;
    // next Header
    Head = (GisReadArtHead**)&(h->Next);
  }
  return MinTime;
}

// ##################################################################
// help procedures

#define NOTE1 ((GisNote*)note1)
#define NOTE2 ((GisNote*)note2)

#ifdef WX
int StrCmp(const mutString &s1, const mutString &s2)
{
	return s1.Cmp(s2);
}
#else
char StrCmp(const char *s1, const char *s2)
{
  if ( s1 )
  {
	 if ( s2 )
		return strcmp(s1, s2);
	 else
		return 1;
  }
  else
	 return s2 != 0;
}
#endif


int CmpNote(GisToken *note1, GisToken *note2)
{
  if ( note1->Type() != GTNote || note2->Type() != GTNote )
	 return 0;
  if ( StrCmp(NOTE1->Name, NOTE2->Name)
		 || StrCmp(NOTE1->Accedentials, NOTE2->Accedentials)
		 || NOTE1->Octave != NOTE2->Octave )
	 return 0;
  return 1;

}
// ##################################################################
// ChordNote

ChordNote::ChordNote(ChordNote *first) // not the first ChordNote
{
  // copy data from first
  Boss = first->Boss;
  BossPos = first->BossPos;
  Next = 0;
  Data = 0;
  Cursor = &Data;
  TotalTime = Boss->TotalTime;
  if ( TotalTime.n )
	 AddGis(new GisNote(mutT("_"), mutEmptyString, 0, TotalTime, mutT(" "), 0));
  CurrentTime = 0;
  Boss->ChordPos = Boss->Cursor;
  Status =0;
  TieBegin = 0;
  nTie = 0;
  LastSep = 0;
  InstrId = -1;
  Taste = NO_KEY;
  Key = NO_KEY;
  Pitch = 0;
}

void ChordNote::CountOnTime(frac dTime)
{
  CurrentTime += dTime;
  TotalTime += dTime;
  if ( Next ) Next->CountOnTime(dTime);
}

#define NOTE ((GisNote*)note)
void ChordNote::SetNoteOn(GisToken *note) // returns 1, when note was added; else 0
{
  *Cursor = new GisNote(NOTE->Name, NOTE->Accedentials, NOTE->Octave,
	 frac(0, 1), NOTE->Sep, 0);
  Status += CNNoteOn;
  Boss->NoteOn++;
}

int ChordNote::SetNoteOff(GisToken *note) // returns 1, when note was finished, else 0
{
  if ( (Status & CNNoteOn) && CmpNote(*Cursor, note) )
  {
	 ((GisNote*)*Cursor)->Duration = CurrentTime;
	 Cursor = &((*Cursor)->Next);
	 CurrentTime = frac(0,1);
	 Status -= CNNoteOn;
	 Boss->NoteOn--;
	 return 1;
  }
  if ( Next ) return Next->SetNoteOff(note);
  return 0;
}

void ChordNote::AddGis(GisToken *token)
{
  *Cursor = token;
  Cursor = &((*Cursor)->Next);
  LastSep = &(token->Sep);
  CurrentTime = 0;
}

void ChordNote::CheckCloseAlter()
{
  if ( Status & CNAlter )
  {
	 mutString s = mutEmptyString;
	 mutString *Sep = LastSep;
	 if ( !LastSep ) Sep = &s;
	 AddGis(new GisTagEnd((GisTagBegin*)*AlterBegin, *Sep));
#ifdef WX
	 if ( *Sep )
	 {
		*Sep = wxEmptyString;
	 }
#else
	 if ( *Sep )
	 {
		free(*Sep);
		*Sep = 0;
	 }
#endif
	 Status -= CNAlter;
	 Pitch = 0;
  }
}

void ChordNote::CheckCloseTie()
{
  if ( nTie > 1 )
  {
	 // close alter
	 CheckCloseAlter();
	 // insert begin range
	 *TieBegin = new GisTagBegin(TTtie, 0, 0, mutT("("), *TieBegin);
	 // add end range
	 mutString s = mutEmptyString;
	 mutString *Sep = LastSep;
	 if ( !LastSep ) Sep = &s;
	 AddGis(new GisTagEnd((GisTagBegin*)*TieBegin, *Sep));
#ifdef WX
	 if ( *Sep )
	 {
	   *Sep=mutEmptyString;
	 }
#else
	 if ( *Sep )
	 {
		free(*Sep);
		*Sep = 0;
	 }
#endif
  }
  TieBegin = Cursor;
  nTie = 0;
}

int ChordNote::MutNoteOn(int key, double pitch, int instrId, int taste, mutString sep)
{
  if ( Status & CNNoteOn )
  	return 1;
  if ( pitch != Pitch && key != NO_KEY )
  {
	 CheckCloseAlter();
	 AlterBegin = Cursor;
	 AddGis(new GisTagBegin(TTalter, 0, new GisParaReal(pitch, mutT(">(")), mutT("<"), 0));
	 Status |= CNAlter;
	 Pitch = pitch;
  }
  GisToken *Note = new GisNote(key, Boss->GetOctave(), Boss->GetKey(), sep);
  *Cursor = Note;
  LastSep = &Note->Sep;
  InstrId = instrId;
  Taste = taste;
  Key = key;
  Status |= CNNoteOn;
  Boss->NoteOn++;
  if ( nTie ) nTie++;
  return 0;
}

int ChordNote::MutNoteOff()
{
  if ( !(Status & CNNoteOn) )
	 return 1;
  if ( GetGisType(*Cursor) != GTNote )
	 return 1;
  if ( CurrentTime.n )
  {
	 ((GisNote*)(*Cursor))->Duration = CurrentTime;
	 Cursor = &(*Cursor)->Next;
  }
  else // note with no duration
  {
	 // delete empty note
	 delete *Cursor;
	 *Cursor = 0;
	 // delete alter
	 if ( Status & CNAlter && !(*AlterBegin)->Next )
	 {
		delete *AlterBegin;
		Cursor = AlterBegin;
		*Cursor = 0;
		Status -= CNAlter;
	 }
	 LastSep = 0;
	 if ( nTie ) nTie--;
  }
  CurrentTime = 0;
  Status -= CNNoteOn;
  Boss->NoteOn--;
  return 0;
}

// ##################################################################
// methods of GisWriteHead

GisWriteHead *GisWriteHead::InsertAfter(GisWriteHead *position)
{
  if ( !position )
  {
	 Next = 0;
	 Prev = 0;
	 return this;
  }
  if ( position->Next ) // not last position
	 position->Next->Prev = this;
  Next = position->Next;
  Prev = position;
  position->Next = this;
  return this;
}

GisWriteHead *GisWriteHead::CutOut()
{
  if ( *(GisWriteHead**)Prev == this ) // first of list
  {
	 *(GisWriteHead**)Prev = Next;
  }
  else // normal list postition
  {
	 Prev->Next = Next;
  }
  if ( Next ) Next->Prev = Prev;
  Next = 0;
  Prev = 0;
  return this;
}

// get free chord note
ChordNote *GisWriteHead::GetFreeNote()
{
  if ( !ChordNotes )
	 return ChordNotes = new ChordNote(this);
  ChordNote **ANote = &ChordNotes;
  while ( *ANote )
  {
	 if ( !((*ANote)->Status & CNNoteOn) )
	 {
		if ( (*ANote)->CurrentTime.n )
		  (*ANote)->AddGis(new GisNote(mutT("_"), mutEmptyString, 0, (*ANote)->CurrentTime, mutT(" "), 0));
		return *ANote;
	 }
	 ANote = &(*ANote)->Next;
  }
  *ANote = new ChordNote(ChordNotes);
  return *ANote;
}


ChordNote *GisWriteHead::GetNote(int instrId, int taste)
{
  ChordNote *ANote = ChordNotes;
  while ( ANote )
  {
	 if ( ANote->CheckId(instrId, taste) )
	   break;
	 ANote = ANote->Next;
  }
  return ANote;
}


// prepare for taking over by boss
int GisWriteHead::ReadyForBoss()
{
  CloseCurrentToken(0); //+ zu hart: bei Unknown muß keine Note eingefügt werden (zumindest nur beim ersten
  // put in Sequenz, when single token mode
#ifdef GMN_STRICT
  if ( SingleToken && Data && &Data->Next != Cursor && Data->Type() != GTSequenz )
  {
	 char isSingle = 2;
	 GisToken *Token = Data, LastToken = 0;
	 while ( 1 )
	 {
		if ( Token->Type() == GTNote )
			 if ( isSingle ) isSingle--;
		if ( Token->Next )
		  Token = Token->Next;
		else
		  break;
	 }
	 if ( !isSingle )
	 {
		GisToken **Comma = 0;
		if ( CommaAtEnd ) // get right position
		{
		  Comma = &Data;
		  GisToken **Comma = &Data;
		  while ( (*Comma)->Next )
			 Comma = &((*Comma)->Next);
		  *Comma = 0;
		}
		Data = new GisSequenz(Data, " ");
		Cursor = &Data->Next;
		if ( Comma )
		{
		  *Cursor = *Comma;
		  Cursor = &(*Comma)->Next;
		}
	 }
  }
#endif
  return 0;
}

void GisWriteHead::RemoveComma()
{
  if ( CommaAtEnd )
  {
	 GisToken **H = &Data;
	 while ( &(*H)->Next != Cursor )
		H = &(*H)->Next;
	 GisToken *SaveNext = (*H)->Next;
	 delete *H;
	 *H = SaveNext;
	 Cursor = H;
  }
}


// end of segment or sequenz, close all corresponding subs
int GisWriteHead::CloseSubs(GisToken **cont)
{
  GisWriteHead *h = Next;
  GisToken **Cont = &(((GisSegment*)*Cursor)->Contents);
  if ( cont ) Cont = cont;
  while ( h && nSub > 0 && h->Boss == this )
  {
	 h->ReadyForBoss();
	 if ( nSub == 1 && h->CommaAtEnd )
		h->RemoveComma();
	 *Cont = h->Data;
	 if ( Data )
		Cont = h->Cursor;
	 if ( nSub > 1 && !h->CommaAtEnd )
	 {
		*Cont = new GisComma(mutT(" "), 0);
		Cont = &((*Cont)->Next);
	 }
	 nSub--;
	 h->CutOut();
	 delete h;
	 h = Next;
  }
  return nSub;
}

// closes current token automaticaly, to be ready for a new
int GisWriteHead::CloseCurrentToken(char insertRest)
{
  if ( ChordNotes )
  {
	 WriteChord();
	 return 0;
  }
  switch ( State() )
  {
	 case GTNull:
		if ( insertRest && CurrentTime.n ) // write a rest
		{
		  *Cursor = new GisNote(mutT("_"), mutT(""), 0, CurrentTime, mutT(" "));
		  Cursor = &((*Cursor)->Next);
		  CurrentTime = 0;
		}
		break;
	 case GTUnknown:
		return 1; // impossible
	 case GTSequenz:
		CloseSubs();
		CurrentTime = 0;
      Cursor = &((*Cursor)->Next);
		break;
	 case GTSegment:
		CloseSubs();
		CurrentTime = 0;
		Cursor = &((*Cursor)->Next);
      break;
	 case GTTag:
		return 1; // impossible
	 case GTTagBegin:
		return 1; // impossible
	 case GTTagEnd:
		return 1; // impossible
/*    case GTNote:
		((GisNote*)(*Cursor))->Duration = CurrentTime;
		Cursor = &(*Cursor)->Next;
		CurrentTime = frac(0, 1);
		// das hier muß anders sein, um mehrere Noten gleichzeitig zu schaffen
		break;  */
	 case GTParaInt:
		return 1; // impossible
	 case GTParaReal:
		return 1; // impossible
	 case GTParaStr:
      return 1; // impossible
  }
  return 0;
}

#define WTAG    ((GisTag*)(*Cursor))
#define WTAGEND ((GisTagEnd*)token)

int GisWriteHead::ProceedGis(GisToken *token, char turn)
{
///  cout << "[" << Id << "," << (int)turn << "]"; token->Echo();
///  cout << " ";
  int Res = 0;
  int Id;
  if ( turn == 1 ) return 0;
  CommaAtEnd = 0;
  if ( !turn ) // this token first time
  {
	 Res = CloseCurrentToken(); // close the current Token
	 if ( Res ) return Res;
	 switch ( token->Type() )
	 {
		case GTNull:
		  return 3; // impossible
		case GTUnknown:
		  *Cursor = new GisToken(token->Sep);
		  Cursor = &((*Cursor)->Next);
		  break;
		case GTSequenz:
		  *Cursor = new GisSequenz(0, token->Sep);
		  ((GisSequenz*)*Cursor)->Sep2 = ((GisSequenz*)token)->Sep2;
		  break;
		case GTSegment:
		  *Cursor = new GisSegment(0, token->Sep);
		  ((GisSegment*)*Cursor)->Sep2 = ((GisSegment*)token)->Sep2;
		  break;
		case GTTag:
		case GTTagBegin:
/*		  if ( token->Type() == GTTag )
			 *Cursor = new GisTag(((GisTag*)token)->Name, ((GisTag*)token)->Para,
				token->Sep);
		  else
			 *Cursor = new GisTagBegin(((GisTag*)token)->Name, ((GisTag*)token)->Para,
				token->Sep); */
		  *Cursor = token->Copy();
		  Id = WTAG->Id;
		  if ( Id == TToct )
		  {
			 if ( WTAG->GetParaType(1) == GTParaInt )
				AddTag(&Octave, WTAG)->Data.i = ((GisParaInt*)WTAG->GetPara(1))->i;
		  }
		  else if ( Id == TTkey )
		  {
			 if ( WTAG->GetParaType(1) == GTParaInt )
				AddTag(&Key, WTAG)->Data.i = ((GisParaInt*)WTAG->GetPara(1))->i;
		  }
		  Cursor = &((*Cursor)->Next);
		  break;
		case GTTagEnd:
		  *Cursor = new GisTagEnd(0, token->Sep);
		  Cursor = &((*Cursor)->Next);
		  if ( WTAGEND->Begin )
		  {
			 Id = WTAGEND->Begin->Id;
			 if ( Id == TToct )
				EndTag(&Octave, WTAGEND);
			 else if ( Id == TTkey )
				EndTag(&Key, WTAGEND);
		  }
		  break;
		case GTParaInt:
		case GTParaReal:
		case GTParaStr: return 4;
		case GTComma:
		  *Cursor = new GisComma(token->Sep);
		  Cursor = &((*Cursor)->Next);
		  CommaAtEnd = 1;
		  break;
		case GTNote:
		  ChordNote *ANote = GetFreeNote();
		  if ( ANote )
			 ANote->SetNoteOn(token);
		  else
			 return 1;
		  break;
	 }
  }
  else // second call
  {
	 if ( State() != token->Type() && token->Type() != GTNote) return 2;
	 if ( token->Type() != GTNote )
		Res = CloseCurrentToken();
	 else
	 {
		if ( ChordNotes )
		{
		  Res = !ChordNotes->SetNoteOff(token);
		}
		if ( !NoteOn ) // write the Chord
		  WriteChord();
	 }
  }
  return Res;
}

void GisWriteHead::WriteChord()
{
  if ( !ChordNotes ) return;
  // close open ties
  ChordNote *ANote = ChordNotes;
  while ( ANote )
  {
	 ANote->CheckClose();
	 ANote = ANote->Next;
  }
  char BossLine = 1; // wether in Boss data also data for Chord;
  char SingleLine = 0; // wether there is in fact only one Line (no real chord)
  if ( Cursor == ChordPos )
	 BossLine = 0;
  if ( !ChordNotes->Next && !BossLine )
	 SingleLine = 1;
#ifdef CHORDS_WITH_REST
  ChordNotes->AddRest();
#endif
  if ( SingleLine ) // only one line (no real chord)
  {
	 *(ChordNotes->Cursor) = *ChordPos;
	 *ChordPos = ChordNotes->Data;
	 if ( Cursor == ChordPos )
		Cursor = ChordNotes->Cursor;
	 ChordNotes->Data = 0;
  }
  else
  {
  }
  delete ChordNotes;
  ChordNotes = 0;
  CurrentTime = 0;
}

void GisWriteHead::AddTime(frac dTime)
{
  TotalTime += dTime;
  CurrentTime += dTime;
  if ( ChordNotes ) ChordNotes->CountOnTime(dTime);
  if ( Next ) Next->AddTime(dTime);
}


// ##################################################################
// procedures with GisWriteHead

// search the header with the matching Id
GisWriteHead *GetMatchingHeader(GisWriteHead **head, const mutString id)
{
  GisWriteHead *h = *head, *LastHead = 0;
  GisWriteHead *Boss = h;
  size_t  BossIdLength = mutLen(h->Id);
  char CmpRes = 0;
  // search header
  while ( h )
  {
  
#ifdef WX
	 if ( (id.StartsWith(h->Id)) && (mutLen(h->Id) >= BossIdLength) )
	 {
		Boss = h; BossIdLength = mutLen(h->Id) + 1;
	 }
	 CmpRes = mutStrCmp(h->Id, id);
	 if ( CmpRes >= 0 ) break;
#else
	 if ( !strncmp(h->Id, id, strlen(h->Id)) && (strlen(h->Id) >= BossIdLength) )
	 {
		Boss = h; BossIdLength = strlen(h->Id) + 1;
	 }
	 CmpRes = strcmp(h->Id, id);
	 if ( CmpRes >= 0 ) break;
#endif
	 LastHead = h;
	 h = h->Next;
  }
  if ( CmpRes ) // insert a new header
  {
	 h = new GisWriteHead(Boss, id);
	 if ( LastHead ) // not at the first position
		h->InsertAfter(LastHead);
	 else // first position in header list
	 {
		h->Prev = (GisWriteHead*)head;
		h->Next = *head;
		if ( *head ) (*head)->Prev = h;
		*head = h;
	 }
  }
  return h;
}

// write from a GisToken
int GisWriteHeadGis(GisWriteHead **head,  mutString id, GisToken *token, char turn)
{
  return GetMatchingHeader(head, id)->ProceedGis(token, turn);
}

// close subheads
void CloseAllSubs(GisWriteHead *head)
{
  while ( 1 )
  {
	 // search the lowest boss
	 GisWriteHead *Boss = 0;
	 for (GisWriteHead *H = head; H; H = H->Next)
		if ( H->nSub > 0 )
		  Boss = H;
	 if ( !Boss ) break;
	 // check for "empty" boss
	 if ( !Boss->Data && Boss->nSub == 1 )
	 {
		GisWriteHead *h = Boss->Next;
		Boss->Data = h->Data;
      Boss->nSub = 0;
		h->Data = 0;
		h->CutOut();
		delete h;
		continue;
	 }
	 // check for segment
	 if ( GetGisType(*Boss->Cursor) != GTSegment )
	 {
		if ( Boss->Data && !Boss->CommaAtEnd )
		{
		  *Boss->Cursor = new GisComma(mutT(" "), 0);
		  Boss->Cursor = &((*Boss->Cursor)->Next);
		}
		Boss->Data = new GisSegment(Boss->Data, mutT(" "), 0);
		GisToken **Cont = Boss->Cursor;
		if ( Boss->Cursor == &Boss->Data )
		  Cont = 0;
		Boss->Cursor = &Boss->Data;
		Boss->CloseSubs(Cont);
	 }
	 else
		Boss->CloseSubs();
  }
/*  // check wether there are parallel heads
  if ( head->Next ) */
  // remove comma at end
  head->RemoveComma();
}
/*
#define zugriff  ((unsigned char*) &freq)

int GisWriteAlteredNoteOn(GisWriteHead **head,  char *id, long freq, int noteId,
  int octave, int acc, char *Sep)
{
  GisWriteHead *h = GetMatchingHeader(head, id);
  if ( !h ) return 1;
  h->CommaAtEnd = 0;
  GisToken *Note = new GisNote(zugriff[3]&0x7f, octave, acc, Sep);
  ChordNote *ANote = h->GetFreeNote();
  ANote->CheckCloseTie();
  ANote->TieBegin = ANote->Cursor;
  double pitch = (double)(freq & 0x00FFFFFF) / 0x01000000;
  if ( pitch != 0.0 )
  {
	 ANote->AddGis(new GisTagBegin(TTalter, 0, new GisParaReal(pitch, ">( "), "<", 0));
	 ANote->Status |= CNAlter;
  }
  *(ANote->Cursor) = Note;
  ANote->LastSep = &Note->Sep;
  ANote->Id = noteId;
  ANote->Status |= CNNoteOn;
  ANote->Boss->NoteOn++;
  return 0;
}

int GisWriteAlteredNoteOff(GisWriteHead **head,  char *id, int noteId)
{
  GisWriteHead *h = GetMatchingHeader(head, id);
  if ( !h ) return 1;
  ChordNote *ANote = h->GetNoteId(noteId);
  if ( !ANote )
	 return 1;
  if ( !(ANote->Status & CNNoteOn) )
	 return 1;
  if ( GetGisType(*ANote->Cursor) != GTNote )
	 return 1;
  ((GisNote*)(*ANote->Cursor))->Duration = ANote->CurrentTime;
  char **Sep = &(*ANote->Cursor)->Sep;
  ANote->Cursor = &((*ANote->Cursor)->Next);
  ANote->CurrentTime = 0;
  ANote->Status -= CNNoteOn;
  ANote->Boss->NoteOn--;
  if ( ANote->Status & CNAlter )
  {
	 ANote->AddGis(new GisTagEnd(0, *Sep));
	 if ( *Sep )
	 {
		free(*Sep);
		*Sep = strdup(" ");
	 }
	 ANote->Status -= CNAlter;
  }
  if ( !ANote->Boss->NoteOn ) ANote->Boss->WriteChord();
  return 0;
} */
/*
// write from midi
int GisWriteHeadMis(GisWriteHead **head,  char *id, DWORD midi, MisTrack* track)
{
  GisToken *Token = 0;
  int Turn = 0;
  BYTE StatusByte = midi & 0xFF;
  if ( StatusByte < 0xF0 )
	 StatusByte = StatusByte & 0xF0;
  switch ( StatusByte )
  {
  }
  return GetMatchingHeader(head, id)->ProceedGis(Token, Turn);
}
;
  switch ( StatusByte )
  {
  }
  return GetMatchingHeader(head, id)->ProceedGis(Token, Turn);
} */
