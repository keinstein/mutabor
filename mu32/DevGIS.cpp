// #################################################################
// Mutabor, GIS - Devices
// #################################################################

#include "DevGIS.h"
#include "GSP.h"
#include <math.h>
#include "MidiKern.h"
#include "GrafKern.h"

#ifdef RTMIDI
#else
#ifndef MMSYSTEM_H
  #define MMSYSTEM_H
//  #define WINVER 0x030a
  #include <mmsystem.h>
#endif
#endif
#include "Execute.h"

//int ausgabe_instrument[16][4];

mutString CurrentId;
mutString CurrentSep;

#define ROUND_FACTOR 1000000
#define ROUND(x) x = (floor(x*ROUND_FACTOR+0.5)) / ROUND_FACTOR
//#define ROUND(x) x=x

void GetKeyPitch(int taste, TONSYSTEM *tonsystem, int &key, double &pitch)
{
  int Index = (taste - tonsystem->anker) % tonsystem->breite;
  int Abstand = (taste - tonsystem->anker) / tonsystem->breite;
  if ( Index < 0 )
  {
	 Index += tonsystem->breite;
	 Abstand--;
  }
  long Tone = (tonsystem)->ton[Index];
  if ( !Tone )
  {
	 key = NO_KEY;
	 pitch = 0;
	 return;
  }
  pitch = ((double)(tonsystem)->periode) / 0x01000000 * Abstand + ((double)Tone) / 0x01000000;
  key = (int) pitch;
  pitch -= key;
  if ( pitch < -0.5 )
  {
	 pitch++;
	 key--;
  }
  else if ( pitch > 0.5 )
  {
	 pitch--;
	 key++;
  }
  ROUND(pitch);
}

// ##################################################################
// OutGis
/*
void OutGis::NoteOn(int instr, TONSYSTEM * tonsys, int taste, int velo)
{
  int Key;
  double Pitch;
  GetKeyPitch(taste, tonsys, Key, Pitch);
  GisWriteHead *h = GetMatchingHeader(&Head, CurrentId);
  if ( !h ) return ;
  h->CommaAtEnd = 0;
  ChordNote *ANote = h->GetFreeNote();
  ANote->CheckCloseTie();
  ANote->MutNoteOn(Key, Pitch, instr, taste, CurrentSep);
}

void OutGis::NoteOff(int instr, int taste, int velo)
{
  GisWriteHead *h = GetMatchingHeader(&Head, CurrentId);
  if ( !h ) return;
  ChordNote *ANote = h->GetNote(instr, taste);
  if ( !ANote )
	 return;
  ANote->MutNoteOff();
  ANote->CheckCloseTie();
  if ( !ANote->Boss->NoteOn ) ANote->Boss->WriteChord();
}

void OutGis::NotesCorrect(int instr, TONSYSTEM * tonsys)
{
  // search sounding notes of instrument instr
  for (GisWriteHead *h = Head; h; h = h->Next)
	 for (ChordNote *ANote = h->ChordNotes; ANote; ANote = ANote->Next)
		if ( ANote->InstrId == instr && ANote->Status & CNNoteOn )
		{
		  // check, wether pitch has changed
		  int Key;
		  double Pitch;
		  GetKeyPitch(ANote->Taste, tonsys, Key, Pitch);
		  if ( ANote->Cmp(Key, Pitch) )
			 continue;
		  // look for the old key
		  int OldKey = ANote->Key;
		  char *OldSep = (*ANote->Cursor)->Sep;
		  (*ANote->Cursor)->Sep = strdup(" ");
		  int Taste = ANote->Taste;
		  // insert tie
		  ANote->nTie++;
		  // finish the note
		  ANote->MutNoteOff();
		  // calculate new values
		  if ( Key != NO_KEY )
		  {
			 Pitch += (Key - OldKey);
			 Key = OldKey;
		  }
		  // start the new note
		  ANote->MutNoteOn(Key, Pitch, instr, Taste, OldSep);
		  // correct nTie (MutNoteOn does nTie++)
		  ANote->nTie--;
		  // clear old separator
		  if ( OldSep )
			 free(OldSep);
		}
}
*/
void OutGis::Gis(GisToken *token, char turn)
{
  GisWriteHeadGis(&Head, CurrentId, token, turn);
}

// InGis ------------------------------------------------------------

void CALLBACK _export GisTimeFunc(UINT wTimerID, UINT wMsg, DWORD dwUser, DWORD dw1, DWORD dw2)
{
  ((InGis*)dwUser)->IncDelta();
}

bool InGis::Open()
{
  Data = GisParse(Name);
  if ( GspError )
  {
/* //4    *Echo << "\n  Parsing interupted !\n";
    *Echo << "  ErrorNr: " << GspError << " - " << GspErrorText[GspError] << "\n";
    *Echo << "  Line: " << GspErrorLineNr << ", " << GspErrorPos << "\n";
    *Echo << "  " << GspErrorLine << "\n  "; */
#ifdef DEBUG
	std::cerr << "Issuing Compiler warning 9..." << std::endl;
#endif
    compiler_warning(9, Name.c_str(), GspErrorLineNr, GspErrorPos, GspErrorText[GspError]);
#ifdef DEBUG
	std::cerr << "done.";
#endif
    Mode = 3;
    InDevChanged = 1;
    return false;
  }
  Head = new GisReadArtHead(0, Data, Id);
  Head->Box = 0; /// hier muﬂ noch was hin
  Head->Prev = (GisReadHead*)(&Head);
  // Mode setzen
  Mode = 0;
  // initialisieren
  Stop();
  return true;
}

void InGis::Close()
{
  Stop();
  // Speicher freigeben
  if ( Mode == 3 )
    return;
  if ( Head )
  {
    delete Head;
    Head = 0;
  }
  if ( Data )
  {
    delete Data;
    Data = 0;
  }
  delete Data;
}

void InGis::Stop()
{
  if ( Mode == 1 || Mode == 4 )
    Pause();
  // OK ?
  if ( Mode == 3 )
    return;
  // Header auf Start setzen
  if ( Head )
  {
    delete Head;
    Head = 0;
  }
  Head = new GisReadArtHead(0, Data, Id);
  Head->Box = 0; /// hier muﬂ noch was hin
  Head->Prev = (GisReadHead*)&Head;
  // Delta-Times lesen
  minDelta = 0;
  actDelta = -1;
  Mode = 0;
}

void InGis::Play()
{
#if !defined(WX) || defined(__WXMSW__)
	TimerId = timeSetEvent(2, 1, GisTimeFunc, (DWORD)this, TIME_PERIODIC);
#endif
	Busy = FALSE;
	Mode = 1;
}

void InGis::Pause()
{
#if !defined(WX) || defined(__WXMSW__)
  timeKillEvent(TimerId);
#endif
  Mode = 2;
  Quite();
}


// Gis arbeitet auf "tick" - Basis, ein tick = 2ms
void InGis::IncDelta()
{
  actDelta++;
  if ( Busy )
    return;
  if ( actDelta < minDelta )
    return;
  // Zeitpunkt ist ran, also verarbeiten
  Busy = TRUE;
  minDelta = ReadOn(actDelta);
  actDelta = 0;
  if ( minDelta == -1 )
  {
    Mode = 4;
    Stop();
    InDevChanged = 1;
  }
  Busy = FALSE;
}

void MutaborTag(GisReadArtHead *h, GisToken *Para, int box)
{
  if ( !Para || Para->Type() != GTParaStr )
	 return; // strange parameters
  mutString ParaName = ((GisParaStr*)Para)->s;
  Para = Para->Next;
  if ( mutStrEq(ParaName, mutT("key")) )
  {
	 if ( GetGisType(Para) == GTParaStr )
///		KeyboardIn(Box, ((GisParaStr*)Para)->s);
		KeyboardIn(box, ((GisParaStr*)Para)->s.c_str());
  }
  if ( mutStrEq(ParaName, mutT("box")) || mutStrEq(ParaName, mutT("instrument")) )
  {
	 if ( GetGisType(Para) == GTParaInt )
		h->Box = ((GisParaInt*)Para)->i;
  }
}

ChannelData Cd(0, 0);

void InGis::Proceed(GisReadArtHead *h, char turn, Route *route)
{
	CurrentId = h->Id;
	CurrentSep = h->Cursor->Sep;
	// calculate box
	int Box = route->Box;
	if ( Box == -1 )
		Box = h->Box;
	OutDevice *out = route->Out;
	// check wether no box should be used
	if ( Box == -2 ) {
		if ( out )
			out->Gis(h->Cursor, turn);
		return;
	}	
	// proceed the token
	int Key;
	switch ( GetGisType(h->Cursor)) {
	case GTTag:
	case GTTagBegin:
		if ( ((GisTag*)(h->Cursor))->Id == TTmutabor )
			MutaborTag(h, ((GisTag*)(h->Cursor))->Para, Box);
		if ( ((GisTag*)(h->Cursor))->Id == TTalter ) return;
		if ( out ) out->Gis(h->Cursor, turn);
		break;
	case GTTagEnd:
		if ( (((GisTagEnd*)(h->Cursor))->Begin)->Id == TTalter ) return;
		if ( out )out->Gis(h->Cursor, turn);
		break;
	case GTNote:
		Key = ((GisNote*)(h->Cursor))->GetKey();
		if ( Key == -1 ) return ;
		Key += h->GetOctave()*12;
		if ( turn != 1 && route->Active ) {
			if ( turn )
				DeleteKey(Box, Key, route->Id);
			else
				AddKey(Box, Key, route->Id);
		}
		if ( turn != 2 && route->Out ) {
			if ( turn )
				route->Out->NoteOff(Box, Key, h->GetIntensity(turn), route, 0); //4 ?? channelid aus staff
			else {
				Cd.Sound = h->GetInstr();
				route->Out->NoteOn(Box, Key, h->GetIntensity(turn), route, 0, &Cd);
			}
		}
		break;
	default:
		if ( out ) out->Gis(h->Cursor, turn);
	}
}

void InGis::ProceedRoute(GisReadArtHead *h, char turn)
{
  mutChar staff = mutStrLast(h->Id);
  char DidOut = 0;
  for (Route *R = Routes; R; R = R->Next)
	 switch ( R->Type )
	 {
		case RTstaff:
		  if ( R->Check(staff) )
		  {
			 Proceed(h, turn, R);
			 DidOut = 1;
		  }
		  break;
		case RTchannel:
		  if ( R->Check(h->Box) )
		  {
			 Proceed(h, turn, R);
			 DidOut = 1;
		  }
		  break;
		case RTelse:
		  if ( DidOut )
			 break;
		case RTall:
		  Proceed(h, turn, R);
	 }
}

// return -1 heiﬂt Ende der GMN
// ein und ausgabe in ticks
// Sinn der ticks: verschiedene Tempi in den Spuren
long InGis::ReadOn(long delta)
{
  GisReadArtHead **H = &Head;
  long MinDelta = -1;
  beginloop:
  while ( *H )
  {
	 GisReadArtHead *h = *H;
	 if ( h->nSub > 0 ) // header has subs
	 {
		H = (GisReadArtHead**)&(h->Next);
 		continue;
	 }
	 if ( h->nSub == 0 ) // all subs has finished
	 {
		ProceedRoute(h, h->Turn++);   // end of segment or sequenz
		h->CursorNext();
		h->Time = 0;
    h->Delta = 0;
	 }
	 if ( h->Delta > 0 ) // header in normal state
	 {
		h->Time -= frac(delta, h->GetSpeedFactor());
    h->Delta -= delta;
		if ( h->Delta <= 0 )
		{
		  ProceedRoute(h, h->Turn++);
		  if ( h->Turn == 2 )
		  {
 			  h->Time = h->Time2;
			  h->Time2 = 0;
		  }
		  if ( h->Turn > 2 )
			  h->CursorNext();
		}
    h->Delta = h->GetSpeedFactor() * h->Time.n / h->Time.d;
	 }
	 h->nSub = -1; // normal header
	 // now check, wether count down Time is 0
	 // if h->time = 0 then h->Cursor points to the GisToken next to proceed
	 while ( h->Delta == 0 ) // read next tokens
	 {
		if ( h->Turn)
		{
		  ProceedRoute(h, h->Turn++);
		  if ( h->Turn == 2 )
		  {
			 h->Time = h->Time2;
			 h->Time2 = 0;
       h->Delta = h->GetSpeedFactor() * h->Time.n / h->Time.d;
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
		ProceedRoute(h, 0);
		h->Read();
    h->Delta = h->GetSpeedFactor() * h->Time.n / h->Time.d;
		if ( h->nSub != -1 ) goto beginloop;
		if ( h->Time.n == 0 ) // token without duration
		  h->CursorNext();
	 }
	 // check MinTime
	 if ( MinDelta == -1 || h->Delta < MinDelta )
		MinDelta = h->Delta;
	 // next Header
	 H = (GisReadArtHead**)&(h->Next);
  }
  return MinDelta;
}





