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

void GetKeyPitch(int taste, ton_system *tonsystem, int &key, double &pitch)
{
	int Index = (taste - tonsystem->anker) % tonsystem->breite;
	int Abstand = (taste - tonsystem->anker) / tonsystem->breite;

	if ( Index < 0 ) {
		Index += tonsystem->breite;
		Abstand--;
	}

	long Tone = (tonsystem)->ton[Index];

	if ( !Tone ) {
		key = NO_KEY;
		pitch = 0;
		return;
	}

	pitch = ((double)(tonsystem)->periode) / 0x01000000 * Abstand + ((double)Tone) / 0x01000000;

	key = (int) pitch;
	pitch -= key;

	if ( pitch < -0.5 ) {
		pitch++;
		key--;
	} else if ( pitch > 0.5 ) {
		pitch--;
		key++;
	}

	ROUND(pitch);
}

// ##################################################################
// OutGis
/*
void OutGis::NoteOn(int instr, ton_system * tonsys, int taste, int velo)
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

void OutGis::NotesCorrect(int instr, ton_system * tonsys)
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
	STUBC;
}

// InGis ------------------------------------------------------------
/*
void CALLBACK _export GisTimeFunc(UINT wTimerID, UINT wMsg, DWORD dwUser, DWORD dw1, DWORD dw2)
{
  ((InGis*)dwUser)->IncDelta();
}
*/

/// Save current device settings in a tree storage
/** \argument config (tree_storage) storage class, where the data will be saved.
 */
void OutGis::Save (tree_storage & config) 
{
	config.Write(_T("File Name"),Name);
}

/// Save route settings (filter settings) for a given route
/** Some route settings (e.g. filter settings) are device type 
 * specific. This function saves them in a tree storage.
 * \argument config (tree_storage *) Storage class, where the data will be saved.
 * \argument route (Route *) Route whos data shall be saved.
 */
void OutGis::Save (tree_storage & config, const Route * route)
{
	STUBC;
}


/// Load current device settings from a tree storage
/** \argument config (tree_storage) storage class, where the data will be loaded from.
 */
void OutGis::Load (tree_storage & config)
{
	Name = config.Read(_T("File Name"), mutEmptyString);
}

/// Load route settings (filter settings) for a given route
/** Some route settings (e.g. filter settings) are device type 
 * specific. This function loads them from a tree storage.
 * \argument config (tree_storage *) Storage class, where the data will be restored from.
 * \argument route (Route *) Route whos data shall be loaded.
 */
void OutGis::Load (tree_storage & config, Route * route)
{
	STUBC;
}


/// Save current device settings in a tree storage
/** \argument config (tree_storage) storage class, where the data will be saved.
 */
void InGis::Save (tree_storage & config) 
{
	config.Write(_T("File Name"),Name);
}

/// Save route settings (filter settings) for a given route
/** Some route settings (e.g. filter settings) are device type 
 * specific. This function saves them in a tree storage.
 * \argument config (tree_storage *) Storage class, where the data will be saved.
 * \argument route (Route *) Route whos data shall be saved.
 */
void InGis::Save (tree_storage & config, const Route * route)
{
}


/// Load current device settings from a tree storage
/** \argument config (tree_storage) storage class, where the data will be loaded from.
 */
void InGis::Load (tree_storage & config)
{
	Name = config.Read(_T("File Name"),mutEmptyString);
}

/// Loade route settings (filter settings) for a given route
/** Some route settings (e.g. filter settings) are device type 
 * specific. This function loads them from a tree storage.
 * \argument config (tree_storage *) Storage class, where the data will be restored from.
 * \argument route (Route *) Route whos data shall be loaded.
 */
void InGis::Load (tree_storage & config, Route * route)
{
}


bool InGis::Open()
{
	DEBUGLOG (other, _T(""));
	Data = GisParse(Name);

	if ( GspError ) {
		/* //4    *Echo << "\n  Parsing interupted !\n";
		    *Echo << "  ErrorNr: " << GspError << " - " << GspErrorText[GspError] << "\n";
		    *Echo << "  Line: " << GspErrorLineNr << ", " << GspErrorPos << "\n";
		    *Echo << "  " << GspErrorLine << "\n  "; */

		DEBUGLOG (other, _T("Issuing Compiler warning 9..."));

		compiler_warning(9, C_STR(Name), GspErrorLineNr, GspErrorPos, mutC_STR(GspErrorText[GspError]));

		DEBUGLOG (other, _T("... done"));
		Mode = MutaborDeviceCompileError;
		InDevChanged = 1;
		return false;
	}

	/*  Head = new GisReadArtHead(NULL, Data, Id);
	DEBUGLOG (other, _T("Head = %p"),Head);
	Head->Box = 0; /// hier muﬂ noch was hin
	Head->PrevPtr = (GisReadHead **)&Head;
	//  Head->Prev = Head;
	DEBUGLOG (other, _T("Head = %p"),Head);
	// Mode setzen
	Mode = MutaborDeviceStop; 
	*/
	// initialisieren
	Stop();

	DEBUGLOG (other, _T("Head = %p"),Head);

	return true;
}

void InGis::Close()
{
	Stop();
	// Speicher freigeben

	if ( Mode == MutaborDeviceCompileError )
		return;

	if ( Head ) {
		delete Head;
		Head = 0;
	}

	if ( Data ) {
		delete Data;
		Data = 0;
	}

	delete Data;
}

void InGis::Stop()
{
	if ( Mode == MutaborDevicePlay || Mode == MutaborDeviceTimingError )
		Pause();

	// OK ?
	if ( Mode == MutaborDeviceCompileError )
		return;

	// Header auf Start setzen
	if ( Head ) {
		delete Head;
		Head = 0;
	}

	Head = new GisReadArtHead(NULL, Data, Id);

	DEBUGLOG (other, _T("Head = %p"),Head);
	Head->Box = 0; /// hier muﬂ noch was hin
	DEBUGLOG (other, _T("Head = %p"),Head);
	//  Head->Prev = Head;
	Head->PrevPtr = (GisReadHead**)&Head;
	DEBUGLOG (other, _T("Head = %p"),Head);
	// Delta-Times lesen
	minDelta = 0;
	actDelta = -1;
	Mode = MutaborDeviceStop;
}

/* Shall GIS support batch processing? */
void InGis::Play()
{
	timer.Start(2,wxTIMER_CONTINUOUS);
	Busy = FALSE;
	Mode = MutaborDevicePlay;
}

void InGis::Pause()
{
	timer.Stop();
	Mode = MutaborDevicePause;
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

	DEBUGLOG (other, _T("Next tone. Mindelta = %d"),minDelta);

	minDelta = ReadOn(actDelta);

	// while ((minDelta = ReadOn(actDelta)) == -1)
	//  if (!(Head->Cursor)) break;

	DEBUGLOG (other, _T("Calculating next step"));

	actDelta = 0;

	if ( minDelta == -1 ) {
		DEBUGLOG (other, _T("Stopping"));
		Mode = MutaborDeviceTimingError;
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

	if ( mutStrEq(ParaName, mutT("key")) ) {
		if ( GetGisType(Para) == GTParaStr )
///		KeyboardIn(Box, ((GisParaStr*)Para)->s);
			KeyboardIn(box, ((GisParaStr*)Para)->s);
	}

	if ( mutStrEq(ParaName, mutT("box")) || mutStrEq(ParaName, mutT("instrument")) ) {
		if ( GetGisType(Para) == GTParaInt )
			h->Box = ((GisParaInt*)Para)->i;
	}
}

ChannelData Cd(0, 0);

void InGis::Proceed(GisReadArtHead *h, char turn, Route *route)
{
	wxASSERT(h->Cursor);
	CurrentId = h->Id;
	CurrentSep = h->Cursor->Sep;
	// calculate box
	int Box = route->Box;

	if ( Box == -1 )
		Box = h->Box;

	DEBUGLOG (other, _T("Id: %s, Box: %d, Sep: %s"),
	         CurrentId.c_str(), Box, CurrentSep.c_str());

	OutDevice *out = route->GetOutDevice();

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
				DeleteKey(Box, Key, route->GetId());
			else

				AddKey(Box, Key, route->GetId());
		}

		if ( turn != 2 && route->GetOutDevice() ) {
			if ( turn )
				route->GetOutDevice()->NoteOff(Box, Key, h->GetIntensity(turn), route, 0); //4 ?? channelid aus staff
			else {
				Cd.Sound = h->GetInstr();
				route->GetOutDevice()->NoteOn(Box, Key, h->GetIntensity(turn), route, 0, &Cd);
			}
		}

		break;

	default:
		if ( out ) out->Gis(h->Cursor, turn);
	}
}

void InGis::ProceedRoute(GisReadArtHead *h, char turn)
{
	wxASSERT(h);
	wxASSERT(h->Cursor);
	DEBUGLOG (other, _T("h->Id = '%s' (%d), Id = '%s' (%d)"),
	         (h->Id).c_str(),(h->Id).Len(), Id.c_str(), Id.Len());
	mutChar staff = h->Id[mutLen(Id)];
	bool DidOut = false;
	DEBUGLOG (other, _T("staff: %d, DidOut: %d"),staff, DidOut);

	for (Route *R = GetRoutes(); R; R = R->GetNext()) {
		DEBUGLOG (other, _T("Route type: %d, DidOut: %d"),R->Type, DidOut);

		switch ( R->Type ) {

		case RTstaff:
			if ( R->Check(staff) ) {
				Proceed(h, turn, R);
				DidOut = true;
			}

			break;

		case RTchannel:
			if ( R->Check(h->Box) ) {
				Proceed(h, turn, R);
				DidOut = true;
			}

			break;

		case RTelse:
			if ( DidOut )
				break;

		case RTall:
			Proceed(h, turn, R);
		}
	}
}


#ifdef DEBUG

static void printHeadChain(std::ostream & f,GisReadHead *H)
{
	f << "  ";

	if (H)
		if (H->PrevPtr) {
			f << "[" << (void *)(H->PrevPtr) << std::flush;

			if (*(H->PrevPtr)) {
				f << "->(" << std::flush
				<< (void *)(*(H->PrevPtr)) << ")" << std::flush;
			}

			f << "]";
		}

	while (H) {
		f << "->" << typeid(*H).name() << "(" << (void *)H << ")" << std::flush;
		H = H->Next;
	}

	f << std::endl;
}

#else
#define printHeadChain(a,b)
#endif
// return -1 heißt Ende der GMN
// ein und ausgabe in ticks
// Sinn der ticks: verschiedene Tempi in den Spuren
long InGis::ReadOn(long delta)
{
	GisReadHead **H = (GisReadHead **)&Head;
	long MinDelta = -1;

beginloop:

	//  printHeadChain(DEBUGLOG (other, _T("Head Chain:")), *H);

	while ( *H ) {

		GisReadArtHead *h = dynamic_cast<GisReadArtHead *> (*H);
		DEBUGLOG (other, _T("H = %p; h = %p"),H,
		         dynamic_cast<GisReadArtHead *>(*H));

		wxASSERT(h);
		DEBUGLOG (other, _T("h->nSub = %d"),h->nSub);

		if ( h->nSub > 0) { // header has subsGisReadHead
			H =  &(h->Next);
			continue;
		}

		// printHeadChain(DEBUGLOG (other, _T("Working Chain:")), *H);
		//DEBUGLOG (other, _T("Reading on with %p\n%s"), *H, (GISPrettyPrint(*Head).c_str()));

		if ( h->nSub == 0 ) { // all subs has finished
			ProceedRoute(h, h->Turn++);   // end of segment or sequenz
			DEBUGLOG (other, _T("CursorNext()"));
			h->CursorNext();
			h->Time = 0;
			h->Delta = 0;
		}

		DEBUGLOG (other, _T("h->Delta = %d"),h->Delta);

		if ( h->Delta > 0 ) {// header in normal state
			DEBUGLOG (other, _T("Time: %d/%d, delta: %d, speed: %d"),
			         h->Time.numerator(),h->Time.denominator(), delta,
			         h->GetSpeedFactor());
			h->Time -= frac(delta, h->GetSpeedFactor());
			h->Delta -= delta;

			if ( h->Delta <= 0 ) {
				ProceedRoute(h, h->Turn++);

				if ( h->Turn == 2 ) {
					h->Time = h->Time2;
					h->Time2 = 0;
				}

				if ( h->Turn > 2 ) {
					DEBUGLOG (other, _T("CursorNext()"));
					h->CursorNext();
				}
			}

			h->Delta = (h->GetSpeedFactor() * h->Time.numerator())

			           / h->Time.denominator();
			DEBUGLOG (other, _T("Time: %d/%d, Time2: %d/%d, delta: %d, speed: %d"),
			         h->Time.numerator(),h->Time.denominator(),
			         h->Time2.numerator(),h->Time2.denominator(),
			         delta,
			         h->GetSpeedFactor());
		}

		h->nSub = -1; // normal header

		// now check, wether count down Time is 0
		// if h->time = 0 then h->Cursor points to the GisToken next to proceed

		DEBUGLOG (other, _T("h->Delta = %d"),h->Delta);

		while ( h->Delta == 0 ) { // read next tokens
			DEBUGLOG (other, _T("h->Turn = %d"),h->Turn);

			if ( h->Turn) {
				ProceedRoute(h, h->Turn++);
				DEBUGLOG (other, _T("h->Delta = %d, h->Turn = %d"),h->Delta, h->Turn);

				if ( h->Turn == 2 ) {
					h->Time = h->Time2;
					h->Time2 = 0;
					h->Delta = (h->GetSpeedFactor() * h->Time.numerator())
					           / h->Time.denominator();
					DEBUGLOG (other, _T("h->Delta = %d * %d / %d = %d"), h->GetSpeedFactor(),
					         h->Time.numerator(), h->Time.denominator(), h->Delta);
				}

				if ( h->Turn > 2 ) {
					h->CursorNext();
				} else {
					DEBUGLOG2(other,_T("continue loop"));
					continue;
				}
			}

			if ( !h->Cursor ) { // header finished, kick away
				h->CutOut();

				if ( h->Boss ) h->Boss->nSub--; // inform the boss

				delete h;

				DEBUGLOG2(other,_T("goto beginloop"));

				goto beginloop;
			}

			// proceed
			DEBUGLOG (other, _T("Proceed with Turn 0"));

			ProceedRoute(h, 0);

			DEBUGLOG (other, _T("h->Read()"));

			h->Read();

			DEBUGLOG (other, _T("Time: %d/%d, Time2: %d/%d, delta: %d"),
			         h->Time.numerator(),h->Time.denominator(),
			         h->Time2.numerator(),h->Time2.denominator(),
			         delta);

			h->Delta = (h->GetSpeedFactor() * h->Time.numerator())
			           / h->Time.denominator();

			DEBUGLOG (other, _T("h->Delta = %d * %d / %d = %d"), h->GetSpeedFactor(),
			         h->Time.numerator(), h->Time.denominator(), h->Delta);

			DEBUGLOG (other, _T("Time: %d/%d, Time2: %d/%d, delta: %d, speed: %d"),
			         h->Time.numerator(),h->Time.denominator(),
			         h->Time2.numerator(),h->Time2.denominator(),
			         delta,
			         h->GetSpeedFactor());

			if ( h->nSub != -1 ) {
				DEBUGLOG2(other,_T("goto beginloop"));
				goto beginloop;
			}

			if ( !(h->Time) ) {// token without duration
				DEBUGLOG (other, _T("CursorNext()"));
				h->CursorNext();
			}
		}

		// check MinTime
		DEBUGLOG (other, _T("h->Delta = %d, MinDelta = %d"),h->Delta,MinDelta);

		if ( MinDelta == -1 || h->Delta < MinDelta )
			MinDelta = h->Delta;

		// next Header
		H = &(h->Next);
	}

	DEBUGLOG2(other,_T("returning %d"),MinDelta);

	return MinDelta;
}





