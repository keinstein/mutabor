/** \file
 ********************************************************************
 * MIDI-File als Device.
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/mu32/Attic/DevMidF.cpp,v 1.5 2005/11/07 19:42:54 keinstein Exp $
 * \author Rüdiger Krauße <krausze@mail.berlios.de>
 * \date $Date: 2005/11/07 19:42:54 $
 * \version $Revision: 1.5 $
 *
 * $Log: DevMidF.cpp,v $
 * Revision 1.5  2005/11/07 19:42:54  keinstein
 * Some additional changes
 *
 ********************************************************************/
// ------------------------------------------------------------------
// Mutabor 3, 1998, R.Krauße
// MIDI-File als Device
// ------------------------------------------------------------------
#include "Defs.h"
#if defined(MUTWIN) && !defined(WX)
#include <owl/pch.h>
#endif

#ifdef RTMIDI
#  include "RtMidi.h"
#else
#ifndef H_MMSYSTEM
//  #define WINVER 0x030a
  #include <mmsystem.h>
  #define H_MMSYSTEM
#endif
#endif

#include "DevMidF.h"
#include "Execute.h"
#include "GrafKern.h"

/* berechnet die Tonigkeit einer Taste bzgl. tonsystem */
#define GET_INDEX(taste,tonsystem)                \
 ((int)((taste)-( (tonsystem)->anker % (tonsystem)->breite )) \
			  % (tonsystem)->breite )


// berechnet die 'Oktavlage' einer taste bzgl. tonsystem
#define GET_ABSTAND(taste,tonsystem) \
     ( (int)((taste)-( (tonsystem)->anker % (tonsystem)->breite ))  \
           / (tonsystem)->breite -((int) (tonsystem)->anker         \
           / (tonsystem)->breite ))

// berechnet die Frequenz in Midi-Form
#define GET_FREQ(taste,tonsystem)  \
	( ( (tonsystem)->ton[GET_INDEX(taste,(tonsystem))]==0) ?       \
	  (long) 0 :                                       \
     (long)( (tonsystem)->periode *                   \
              GET_ABSTAND(taste,(tonsystem))  +                         \
                   (tonsystem)->ton[GET_INDEX(taste,(tonsystem))]))

#define ZWZ 1.059463094 /* 12.Wurzel 2 */
#define LONG_TO_HERTZ( x ) (440.0*pow(ZWZ,((((float)x)/(double)16777216.0))-69))
#define LONG_TO_CENT( x ) ( ((float)x)/(double)167772.13  )

// Midi-Ausgabe
#define MIDI_OUT3(code1, code2, code3) \
  Tracks.MidiOut3(code1, code2, code3)

#define MIDI_OUT2(code1, code2) \
  Tracks.MidiOut2(code1, code2)

// Zugriffe
#define zugriff  ((unsigned char*) &freq)
#define zgf  ((unsigned char*) &pb)

// Pitch
#define MIDI_PITCH(i) \
	int pb = ( (((int)zugriff[2])<<6) + (zugriff[1]>>2) ) / bending_range; \
	MIDI_OUT3(0xE0+i, zgf[0] >> 1 , 64+(ton_auf_kanal[i].fine=(zgf[1])))

// Sound
#define MIDI_SOUND(i, sound) \
  if ( sound != -1 ) MIDI_OUT2(0xC0+i, sound)

// ID errechnen
#define MAKE_ID(route, box, taste, channel) \
 ((((DWORD)channel) << 24) + (((DWORD)route->Id) << 16) + ((DWORD)box << 8) + taste)

#define NO_DELTA 16000 //2147483647  // long max-Zahl

int lMidiCode[8] = { 3, 3, 3, 3, 2, 2, 3, 1 };

// Daten übergeben für NoRealTime-Übersetzungen
BYTE *pData;
int nData;
long NRT_Speed;

DWORD ReadLength(STD_PRE::ifstream &is)
{
  BYTE a[4];
  is.read((char*)a, 4);
  return (((DWORD)a[0]) << 24) + (((DWORD)a[1]) << 16) +
	  (((DWORD)a[2]) << 8) + ((DWORD)a[3]);
}

void WriteLength(STD_PRE::ofstream &os, DWORD l)
{
  os.put((BYTE) ((l >> 24) & 0xFF));
  os.put((BYTE) ((l >> 16) & 0xFF));
  os.put((BYTE) ((l >> 8) & 0xFF));
  os.put((BYTE) (l & 0xFF));
}

// CurrentTime ------------------------------------------------------

DWORD CurrentTime;
UINT CurrentTimeId;

// CallBack Funktion
void CALLBACK _export CurrentTimeFunc(UINT wTimerID, UINT wMsg, DWORD dwUser, DWORD dw1, DWORD dw2)
{
  CurrentTime++;
}

// Timer setzen
void StartCurrentTime()
{
  CurrentTime = 0;
#if !defined(WX) || defined(__WXMSW__)
  CurrentTimeId = timeSetEvent(2, 1, CurrentTimeFunc, 0, TIME_PERIODIC);
#endif
}

// Timer löschen
void StopCurrentTime()
{
#if !defined(WX) || defined(__WXMSW__)
  timeKillEvent(CurrentTimeId);
#endif
}

// Tracks -----------------------------------------------------------

void Track::WriteDelta()
{
  BYTE w[5];
  int i = 0;
  DWORD Delta = CurrentTime - Time;
  Time = CurrentTime;
  w[0] = Delta & 0x7F;
  Delta >>= 7;
  while ( Delta )
  {
	  i++;
	  w[i] = 0x80 | (Delta & 0x7F);
	  Delta >>= 7;
  }
  for (;i>=0;i--)
	  Data->Add(w[i]);
}

void Track::Save(STD_PRE::ofstream &os)
{
  os << "MTrk";
  WriteLength(os, Data->GetItemsInContainer()+4);
  for (DWORD i = 0; i < Data->GetItemsInContainer(); i++)
	  os.put((BYTE)(*Data)[i]);
  os.put((BYTE)0x00);
  os.put((BYTE)0xFF);
  os.put((BYTE)0x2F);
  os.put((BYTE)0x00);
}

// OutMidiFile ------------------------------------------------------

bool OutMidiFile::Open()
{
  Tracks.Data->Flush();
  return true;
}

void OutMidiFile::Close()
{
  // alle liegenden Töne ausschalten
  for (int i = 0; i < 16; i++)
    if ( KeyDir[i] >= 16 )  // benutzt
      MIDI_OUT3(0x80+i, ton_auf_kanal[i].key, 64);
  // Datei speichern
	STD_PRE::ofstream os(Name, STD_PRE::ios::out | STD_PRE::ios::binary/*0, filebuf::openprot*/);
  BYTE Header[41] =
	  { 'M', 'T', 'h', 'd', 0, 0, 0, 6, 0, 1, 0, 2, 1, 0x00,
      'M', 'T', 'r', 'k', 0, 0, 0, 0x13, 0x00, 0xFF, 0x51, 0x03, 0x07, 0xD0, 0x00,
      0x00, 0xFF, 0x58, 0x04, 0x04, 0x02, 0x18, 0x08, 0x00, 0xFF, 0x2F, 0x00 };
  if ( !RealTime )
  {
    Header[12] = ((WORD)(NRT_Speed >> 8)) & 0xFF;
    Header[13] = ((WORD)(NRT_Speed)) & 0xFF;
  }
  os.write((char*)Header, 41);
  Tracks.Save(os);
}

void OutMidiFile::NoteOn(int box, int taste, int velo, Route *r, int channel, ChannelData *cd)
{
  int i = 0, s;
  DWORD p;
  long freq;
  if ( box == -2 )
  {
    freq = ((long)taste) << 24;
    box = 255;
  }
  else
    freq = GET_FREQ (taste, tonsystem[box]);
  // testen, ob nicht belegte Taste
  if ( !freq )
    return;
  int help = r->OTo;
  i = r->OFrom; // "irgendein" Startwert im gültigen Bereich
  if ( i == DRUMCHANNEL && r->ONoDrum && i < r->OTo )
    i++;
  int j;
  for (j = r->OFrom; j <= r->OTo; j++ )
   if ( j != DRUMCHANNEL || !r->ONoDrum )
    if ( KeyDir[j] < KeyDir[i] )
      i = j;
  if ( KeyDir[i] >= 16 )  // keinen freien gefunden
  {
    // "mittelste Taste weglassen"
    int AM = 0; // arithmetisches Mittel der Tasten
    for (REUSE(int) j =r->OFrom; j <= r->OTo; j++)
     if ( j != DRUMCHANNEL || !r->ONoDrum )
      AM += ton_auf_kanal[j].taste;
    AM /= help + 1 - r->OFrom;
    for (REUSE(int) j = r->OFrom; j <= r->OTo; j++ )
     if ( j != DRUMCHANNEL || !r->ONoDrum )
      if ( abs(AM - ton_auf_kanal[j].taste) < abs(AM - ton_auf_kanal[i].taste) )
        i = j;
    // Ton auf Kanal i ausschalten
    MIDI_OUT3(0x80+i, ton_auf_kanal[i].key, 64);
    // KeyDir umsortieren
    BYTE oldKeyDir = KeyDir[i];
    for (int k = 0; k < 16; k++)
      if ( KeyDir[k] > oldKeyDir ) KeyDir[k]--;
    KeyDir[i] = 15+nKeyOn;
  }
  else
  {
    nKeyOn++;
    KeyDir[i] = 15 + nKeyOn;
  }

  // freier Kanal = i

  // Sound testen
  if ( (s = cd->Sound) != Cd[i].Sound )
  {
    MIDI_SOUND(i, s);
    Cd[i].Sound = s;
  }
  // Bank testen
  if ( (s = cd->BankSelectMSB) != Cd[i].BankSelectMSB && s != -1 )
  {
    MIDI_OUT3(0xB0+i, 0, (BYTE) s);
    Cd[i].BankSelectMSB = s;
  }
  if ( (s = cd->BankSelectLSB) != Cd[i].BankSelectLSB && s != -1 )
  {
    MIDI_OUT3(0xB0+i, 32, (BYTE) s);
    Cd[i].BankSelectLSB = s;
  }
  // Pitch testen
  if ( (p = freq & 0xFFFFFF) != Cd[i].Pitch )
  {
    MIDI_PITCH(i);
    Cd[i].Pitch = p;
  }
  ton_auf_kanal[i].key = zugriff[3] & 0x7f;
  ton_auf_kanal[i].taste = taste;
  ton_auf_kanal[i].id = MAKE_ID(r, box, taste, channel);
  MIDI_OUT3(0x90+i, ton_auf_kanal[i].key, velo);
}

void OutMidiFile::NoteOff(int box, int taste, int velo, Route *r, int channel)
{
  if ( box == -2 )
    box = 255;
  DWORD id = MAKE_ID(r, box, taste, channel);
  if ( !velo ) //3 ?? notwendig?
    velo = 64;
  for (int i = r->OFrom; i <= r->OTo; i++)
   if ( i != DRUMCHANNEL || !r->ONoDrum )
    if ( ton_auf_kanal[i].id == id )
    {
      ton_auf_kanal[i].taste=0;
      ton_auf_kanal[i].id=0;
      MIDI_OUT3(0x80+i, ton_auf_kanal[i].key, velo);
      // KeyDir umsortieren
      int oldKeyDir = KeyDir[i];
      for (int k = 0; k < 16; k++)
        if ( KeyDir[k] > oldKeyDir || KeyDir[k] < 16) KeyDir[k]--;
      nKeyOn--;
      KeyDir[i] = 15;
    }
}

inline long LongAbs(long x)
{
  return (x < 0)? -x : x;
}

void OutMidiFile::NotesCorrect(int box)
{
  for (int i = 0; i < 16; i++)
    if ( KeyDir[i] >= 16 && ton_auf_kanal[i].id )
    {
      int Box = (ton_auf_kanal[i].id >> 8) & 0xFF;
      if ( Box != box )
        break;
      long freq = GET_FREQ(ton_auf_kanal[i].taste, tonsystem[Box]);
      // hier kann ein evtl. größerer bending_range genutzt werden, um
      // Ton aus und einschalten zu vermeiden
      if ( ton_auf_kanal[i].key == (zugriff[3] & 0x7f) &&
        Cd[i].Pitch == (freq & 0xFFFFFF) )
        continue;
      long Delta = freq - ((long)ton_auf_kanal[i].key << 24);
      char SwitchTone = (LongAbs(Delta) >= ((long)bending_range << 24));
      // evtl. Ton ausschalten
      if ( SwitchTone )
      {
        MIDI_OUT3(0x80+i, ton_auf_kanal[i].key, 0x7F);
        ton_auf_kanal[i].key = zugriff[3] & 0x7f;
        Delta = freq - ((DWORD)ton_auf_kanal[i].key << 24);
      }
      else if ( Delta == Cd[i].Pitch )
        continue;
      // Spezialbending (großer Range)
      Cd[i].Pitch = Delta;
      Delta /= (4*bending_range);
      Delta += 0x400000;
      MIDI_OUT3(0xE0+i, ((BYTE*)&Delta)[1] >> 1, (((BYTE*)&Delta)[2]));
      // evtl. Ton einschalten
      if ( SwitchTone )
        MIDI_OUT3(0x90+i, ton_auf_kanal[i].key, 64);  //3 velo speichern ??
    }
}

void OutMidiFile::Sustain(char on, int channel)
{
}

void OutMidiFile::MidiOut(DWORD data, char n)
{
  Tracks.WriteDelta();
  if ( n == -1 )
    n = lMidiCode[(data & 0xF0) >> 5];
  for (int i = 0; i < n; i++)
  {
    Tracks.Add(data & 0xFF);
    data >>= 8;
  }
}

void OutMidiFile::MidiOut(BYTE *p, char n)
{
  Tracks.WriteDelta();
  for (int i = 0; i < n; i++)
    Tracks.Add(p[i]);
}

void OutMidiFile::Quite(Route *r)
{
  for (int i = 0; i < 16; i++)
    if ( (char)((ton_auf_kanal[i].id >> 16) & 0x0FF) == r->Id )
      NoteOff(r->Box, ton_auf_kanal[i].id % 256, 64, r, ton_auf_kanal[i].id >> 24);
}

// InMidiFile -------------------------------------------------------

void CALLBACK _export MidiTimeFunc(UINT wTimerID, UINT wMsg, DWORD dwUser, DWORD dw1, DWORD dw2)
{
  ((InMidiFile*)dwUser)->IncDelta();
}

long ReadDelta(BYTE *data, DWORD *i)
{
  long l = 0;
  BYTE a;
  do
  {
	  a = data[*i];
    (*i)++;
	  l = (l << 7) + (a & 0x7F);
  }
  while ( a & 0x80 );
  return l;
}

bool InMidiFile::Open()
{
  Track = 0;
  curDelta = 0;
  TrackPos = 0;
  StatusByte = 0;
  TicksPerQuater = 0;
  MMSPerQuater = (long) 1000000;
  // Datei lesen
  STD_PRE::ifstream is(Name, STD_PRE::ios::in | STD_PRE::ios::binary/*, 0/*filebuf::openprot*/);
  if ( is.bad() )
  {
    Mode = 3;
    InDevChanged = 1;
    LAUFZEIT_ERROR1("Can not open Midi input file '%s'.", GetName());
    return false;
  }
  // Header Chunk
  char Header[5];
  is.read(Header, 4);
  DWORD l = ReadLength(is);
  BYTE a, b;
  // file type
  a = is.get(); //is.get(a);

  FileType = is.get(); //is.get(FileType);
  // number of tracks
  a = is.get(); //is.get(a);
  b = is.get(); // is.get(b);
  nTrack = (((int)a) << 8) + b;
  // speed info
  a = is.get(); //is.get(a);
  b = is.get(); //is.get(b);
  Speed = (((int)a) << 8) + b;
  NRT_Speed = Speed;
  // rest of header
  DWORD i;
  for (i = 6; i < l && !is.eof() && !is.bad(); i++ )
 	  a = is.get();// is.get(a);
  // Tracks lesen
  Track = (BYTE**)malloc(nTrack*sizeof(BYTE*));
  for (i = 0; i < nTrack; i++ )
  {
    is.read(Header, 4);
    l = ReadLength(is);
    if ( l > (long) 64000 )
    {
      Mode = 3;
      InDevChanged = 1;
    	LAUFZEIT_ERROR1("Midi input file '%s' is to long.", GetName());
      return false;
    }
    Track[i] = (BYTE*)malloc(l*sizeof(BYTE));
    if ( l > 32000 )
    {
      is.read((char*)Track[i], 32000);
      is.read((char*)&Track[i][32000], l-32000);
    }
    else
      is.read((char*)Track[i], l);
    if ( /*is.gcount() != l ||*/ is.bad() )
    {
      Mode = 3;
      InDevChanged = 1;
      LAUFZEIT_ERROR1("Midi input file '%s' produces errors.", GetName());
      return false;
    }
  }
  is.close();
  // Daten vorbereiten
  curDelta = (long*)malloc(nTrack*sizeof(long));
  TrackPos = (DWORD*)malloc(nTrack*sizeof(DWORD));
  StatusByte = (BYTE*)malloc(nTrack*sizeof(BYTE));
  // Mode setzen
  Mode = 0;
  // initialisieren
  Stop();
  return true;
}

void InMidiFile::Close()
{
  Stop();
  // Speicher freigeben
  if ( Mode == 3 )
    return;
  for (int i = 0; i < nTrack; i++ )
    free(Track[i]);
  free(Track);
  free(TrackPos);
  free(curDelta);
  free(StatusByte);
}

void InMidiFile::Stop()
{
  if ( Mode == 1 || Mode == 4 )
    Pause();
  // OK ?
  if ( Mode == 3 )
    return;
  // Delta-Times lesen
  minDelta = 0;
  long NewMinDelta = NO_DELTA;
  MMSPerQuater = (long)1000000;
  for (int i = 0; i < nTrack; i++ )
  {
    TrackPos[i] = 0;
    curDelta[i] = ReadDelta(Track[i], &(TrackPos[i]));
    if ( curDelta[i] < NewMinDelta )
      NewMinDelta = curDelta[i];
  }
  minDelta = NewMinDelta;
  actDelta = -1;
  Mode = 0;
}

void InMidiFile::Play()
{
#if !defined(WX) || defined(__WXMSW__)
  if ( RealTime )
    TimerId = timeSetEvent(2, 1, MidiTimeFunc, (DWORD)this, TIME_PERIODIC);
#endif
  Busy = FALSE;
  Mode = 1;
}

void InMidiFile::Pause()
{
#if !defined(WX) || defined(__WXMSW__)
  if ( RealTime )
    timeKillEvent(TimerId);
#endif
  Mode = 2;
  Quite();
}

void InMidiFile::IncDelta()
{
  actDelta++;
  if ( Busy )
    return;
  if ( actDelta < minDelta )
    return;
  // Zeitpunkt ist ran, also verarbeiten
  Busy = TRUE;
  actDelta -= minDelta;
  long passedDelta = minDelta;
  long NewMinDelta = NO_DELTA;
  for (int i = 0; i < nTrack; i++ )
  {
    if ( curDelta[i] != NO_DELTA )
    {
      if ( curDelta[i] <= passedDelta )
        curDelta[i] = ReadMidiProceed(i, passedDelta-curDelta[i]);
      else
        curDelta[i] -= passedDelta;
      if ( curDelta[i] < NewMinDelta )
        NewMinDelta = curDelta[i];
    }
  }
  if ( NewMinDelta == NO_DELTA )
  {
    Mode = 4;
    InDevChanged = 1;
  }
  minDelta = NewMinDelta;
  Busy = FALSE;
}

long InMidiFile::ReadMidiProceed(int nr, long time)
{
  long Delta = 0;
  long OldPos;
  while ( time >= Delta )
  {
    time -= Delta;
    pData = &(Track[nr][TrackPos[nr]]);
    OldPos = TrackPos[nr];
    DWORD a = Track[nr][TrackPos[nr]++];
    if ( a & 0x80 )
      StatusByte[nr] = a;
    else
    {
      TrackPos[nr]--;
      a = StatusByte[nr];
    }
    BYTE SB = StatusByte[nr];
    if ( SB <  0xF0 ) // normaler midi code
    {
      int l = lMidiCode[(SB >> 4) & 07];
      int shift = 8;
      for (int i = 1; i < l; i++)
      {
        a += (DWORD)Track[nr][TrackPos[nr]++] << shift;
        shift += 8;
      }
    }
    else if ( SB == 0xF0 || SB == 0xF7 ) // SysEx I, SysEx II
    {
      DWORD EventLength = ReadDelta(Track[nr], &(TrackPos[nr])); // length
      TrackPos[nr] += EventLength;
    }
    else if ( SB == 0xFF ) // meta event
    {
      a += Track[nr][TrackPos[nr]++] << 8;         // event number
      DWORD EventLength = ReadDelta(Track[nr], &(TrackPos[nr])); // length
      if ( (a >> 8) == 0x58 ) // Time Signature
      {
        TicksPerQuater = Track[nr][TrackPos[nr]+2];
      }
      else if ( (a >> 8) == 0x51 ) // Tempo
      {
        long NewMMSPerQuater =
          (((DWORD)Track[nr][TrackPos[nr]]) << 16) +
          (((DWORD)Track[nr][TrackPos[nr]+1]) << 8) +
          ((DWORD)Track[nr][TrackPos[nr]]);
        for (int j = 0; j < nr; j++ )
          if ( curDelta[j] != NO_DELTA )
            curDelta[j] = curDelta[j] * NewMMSPerQuater / MMSPerQuater;
        for (REUSE(int) j = nr+1; j < nTrack; j++ )
          if ( curDelta[j] != NO_DELTA && curDelta[j] >= minDelta)
            curDelta[j] = (curDelta[j]-minDelta) * NewMMSPerQuater / MMSPerQuater +minDelta;
        MMSPerQuater = NewMMSPerQuater;
      }
      TrackPos[nr] += EventLength;
    }
    else if ( SB == 0xF2 ) // song position pointer
    {
     a += Track[nr][TrackPos[nr]++] << 8;
     a += Track[nr][TrackPos[nr]++] << 16;
    }
    else if ( SB == 0xF3 ) // song select
     a += Track[nr][TrackPos[nr]++] << 8;
    // ausführen
    nData = TrackPos[nr] - OldPos;
//9    if ( *((BYTE*)(&a)) < 0xF0 )
    if ( a == 0x2FFF )
    {
      TrackPos[nr] = 0xFFFFFFFF;
      return NO_DELTA;
    }
    else
      Proceed(a, nr);
    // Delta Time
    Delta = ReadDelta(Track[nr], &(TrackPos[nr]));
    if ( RealTime )
      Delta = MMSPerQuater / 2000 * Delta / Speed;
  }
  return Delta - time;
}

#define MIDICODE(i) \
  (((BYTE*)(&midiCode))[i])

// für bestimmte Route Codeverarbeitung
void InMidiFile::ProceedRoute(DWORD midiCode, Route *route)
{
  int Box = route->Box;
  BYTE MidiChannel = MIDICODE(0) & 0x0F;
  BYTE MidiStatus = MIDICODE(0) & 0xF0;
  switch ( MidiStatus )
  {
	  case 0x90: // Note On
		  if ( MIDICODE(2) > 0 )
      {
        if ( route->Active )
          AddKey(Box, MIDICODE(1), route->Id);
        if ( route->Out )
          route->Out->NoteOn(Box, MIDICODE(1), MIDICODE(2), route, MidiChannel, &Cd[MidiChannel]);
        break;
      }
 	  case 0x80: // Note Off
      if ( route->Active )
  		  DeleteKey(Box, MIDICODE(1), route->Id);
      if ( route->Out )
        route->Out->NoteOff(Box, MIDICODE(1), MIDICODE(2), route, MidiChannel);
		  break;
 	  case 0xC0: // Programm Change
      Cd[MidiChannel].Sound = MIDICODE(1);
  		break;
	  case 0xB0:
      if ( MIDICODE(1) == 64 )
      {
        Cd[MidiChannel].Sustain = MIDICODE(2);
        if ( route->Out )
          route->Out->Sustain(Cd[MidiChannel].Sustain, MidiChannel);
        break;
      }
      else if ( MIDICODE(1) == 0 ) // BankSelectMSB
      {
        Cd[MidiChannel].BankSelectMSB = MIDICODE(2);
        break;
      }
      else if ( MIDICODE(1) == 32 ) // BankSelectLSB
      {
        Cd[MidiChannel].BankSelectLSB = MIDICODE(2);
        break;
      }
	  case 0xA0:
	  case 0xD0: // Key Pressure, Controler, Channel Pressure
      //3 ??
  		break;
	  case 0xF0:
      if ( route->Out )
        route->Out->MidiOut(pData, nData);

  }
  if ( Box >= 0 && route->Active )
    for (int i = 0; i < lMidiCode[MidiStatus >> 5]; i++)
    {
      MidiAnalysis(Box, MIDICODE(0));
      midiCode >>= 8;
    }
}

// Routen testen und jenachdem entsprechend Codeverarbeitung
void InMidiFile::Proceed(DWORD midiCode, int track)
{
  char DidOut = 0;
  for (Route *R = Routes; R; R = R->Next)
 	  switch ( R->Type )
	  {
		  case RTchannel:
		    if ( R->Check(((BYTE*)&midiCode)[0] & 0x0F) )
		    {
			    ProceedRoute(midiCode, R);
			    DidOut = 1;
		    }
		    break;
		  case RTstaff:
		    if ( R->Check(track) )
		    {
			    ProceedRoute(midiCode, R);
			    DidOut = 1;
		    }
		    break;
		  case RTelse:
		    if ( DidOut )
			    break;
		  case RTall:
		    ProceedRoute(midiCode, R);
	 }
   FLUSH_UPDATE_UI;
}
