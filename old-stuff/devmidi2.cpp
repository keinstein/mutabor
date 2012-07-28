// ------------------------------------------------------------------
// Mutabor 3, 1998, R.Krauße
// MidiPort Klassen
// ------------------------------------------------------------------

#include "devmidi.h"
#include "execute.h"

// OutMidiPort ------------------------------------------------------

//static long freq ;

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
  midiOutShortMsg(hMidiOut, \
    ((DWORD) (code3) << 16) + \
    ((DWORD) (code2) << 8) +   \
    ((DWORD) (code1)))

#define MIDI_OUT2(code1, code2) \
  midiOutShortMsg(hMidiOut, \
    ((DWORD) (code2) << 8) +   \
    ((DWORD) (code1)))


// Zugriffe
#define zugriff  ((unsigned char*) &freq)
#define zgf  ((unsigned char*) &pb)

// Pitch
#define MIDI_PITCH(i) \
	int pb = ( (((int)zugriff[2])<<6) + (zugriff[1]>>2) ) / bending_range; \
	MIDI_OUT3(0xE0+i, zgf[0] >> 1 , 64+zgf[1])

// Sound
#define MIDI_SOUND(i, sound) \
  if ( sound != -1 ) MIDI_OUT2(0xC0+i, sound)

// ID errechnen
#define MAKE_ID(route, box, taste, channel) \
 ((((DWORD)channel) << 24) + (((DWORD)route->Id) << 16) + ((DWORD)box << 8) + taste)

void OutMidiPort::Open()
{
  int i;
  for (i = 0; i < 16; i++)
  {
    Cd[i].Reset();
    ton_auf_kanal[i].taste = 0;
    ton_auf_kanal[i].id = 0;
  }

  nKeyOn = 0;
  for (i = 0; i < 15; i++)
    KeyDir[i] = i; // alle nicht benutzt
  midiOutOpen(&hMidiOut, DevId, NULL, NULL, NULL);
  for (i = 0; i < 16; i++)
  {
    MIDI_OUT3(0xE0+i, 0, 0); // pitch auf 0
  	 MIDI_OUT3(0xB0+i, 122, 0);  // local off
	 MIDI_OUT3(0xB0+i, 125, 0);  // omni on
	 MIDI_OUT3(0xB0+i, 127, 0);  // poly on
	 MIDI_OUT3(0xB0+i, 7, 127);  // main volume
    // sound piano
    MIDI_OUT2(0xC0+i, 0);
  }
}

void OutMidiPort::Close()
{
  // alle liegenden Töne ausschalten
  for (int i = 0; i < 16; i++)
    if ( KeyDir[i] >= 16 )  // benutzt
      MIDI_OUT3(0x80+i, ton_auf_kanal[i].key, 64);
/*  for (int i = 0; i < 16; i++)
	 MidiOut3(176+i, 122, 1);  // local on */
  // Device schließen
  midiOutClose(hMidiOut);
}

void OutMidiPort::NoteOn(int box, int taste, int velo, Route *r, int channel, ChannelData *cd)
{
  int free = 16, freeSus = r->OTo, freeV = 64, freeSusV = 64, s;
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
  for ( int j = r->OFrom; j <= r->OTo; j++ )
    if ( Cd[j].Sustain )
    {
      if ( KeyDir[j] < freeSusV )
      {
        freeSus = j;
        freeSusV = KeyDir[j];
      }
    }
    else
    {
      if ( KeyDir[j] < freeV )
      {
        free = j;
        freeV = KeyDir[j];
      }
    }
  if ( freeV >= 16 )
  {
    free = freeSus;
    freeV = freeSusV;
  }
  if ( freeV >= 16 )  // keinen freien gefunden
  {
    // "mittelste Taste weglassen"
    int AM = 0; // arithmetisches Mittel der Tasten
    int j;
    for (j = r->OFrom; j <= r->OTo; j++)
      AM += ton_auf_kanal[j].taste;
    AM /= r->OTo + 1 - r->OFrom;
    for ( j = r->OFrom; j <= r->OTo; j++ )
      if ( abs(AM - ton_auf_kanal[j].taste) < abs(AM - ton_auf_kanal[free].taste) )
        free = j;
    // Ton auf Kanal free ausschalten
    MIDI_OUT3(0x80+free, ton_auf_kanal[free].key, 64);
    // evtl. Sustain ausschalten
    if ( Cd[free].Sustain )
      MIDI_OUT3(0xB0+free, 64, 0);
    // KeyDir umsortieren
    BYTE oldKeyDir = KeyDir[free];
    for (int k = 0; k < 16; k++)
      if ( KeyDir[k] > oldKeyDir ) KeyDir[k]--;
    KeyDir[free] = 15+nKeyOn;
  }
  else
  {
    nKeyOn++;
    KeyDir[free] = 15 + nKeyOn;
  }

  // freier Kanal = free

  // evtl. Sustain ausschalten
  if ( Cd[free].Sustain )
  {
    MIDI_OUT3(0xB0+free, 64, 0);
    Cd[free].Sustain = 0;
  }

  // Sound testen
  if ( (s = cd->Sound) != Cd[free].Sound )
  {
    MIDI_SOUND(free, s);
    Cd[free].Sound = s;
  }
  // Pitch testen
  if ( (p = freq & 0xFFFFFF) != Cd[free].Pitch )
  {
    MIDI_PITCH(free);
    Cd[free].Pitch = p;
  }
  ton_auf_kanal[free].key = zugriff[3] & 0x7f;
  ton_auf_kanal[free].taste = taste;
  ton_auf_kanal[free].id = MAKE_ID(r, box, taste, channel);
  MIDI_OUT3(0x90+free, ton_auf_kanal[free].key, velo);
  if ( cd->Sustain )
  {
    MIDI_OUT3(0xB0+free, 64, cd->Sustain);
    Cd[free].Sustain = cd->Sustain;
  }
};

void OutMidiPort::NoteOff(int box, int taste, int velo, Route *r, int channel)
{
  if ( box == -2 )
    box = 255;
  DWORD id = MAKE_ID(r, box, taste, channel);
  if ( !velo ) //3 ?? notwendig?
    velo = 64;
  for (int i = r->OFrom; i <= r->OTo; i++)
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

void OutMidiPort::NotesCorrect(int box)
{
  for (int i = 0; i < 16; i++)
    if ( KeyDir[i] >= 16 || Cd[i].Sustain )
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
      long Delta = freq - ((DWORD)ton_auf_kanal[i].key << 24);
      char SwitchTone = (LongAbs(Delta) >= ((DWORD)bending_range << 24));
      // evtl. Ton ausschalten
      if ( SwitchTone )
      {
        if ( Cd[i].Sustain )
        {
          MIDI_OUT3(0xB0+i, 64, 0);
          Cd[i].Sustain = 0;
          if ( KeyDir[i] < 16 )
            continue;
        }
        MIDI_OUT3(0x80+i, ton_auf_kanal[i].key, 0x7F);
        ton_auf_kanal[i].key = zugriff[3] & 0x7F;
        Delta = freq - ((DWORD)ton_auf_kanal[i].key << 24);
      }
      else if ( Delta == Cd[i].Pitch )
        continue;
      // Spezialbending (großer Range)
      Delta /= (4*bending_range);
      MIDI_OUT3(0xE0+i, ((BYTE*)&Delta)[1] >> 1, 64 + (((BYTE*)&Delta)[2]));
      Cd[i].Pitch = Delta;
      // evtl. Ton einschalten
      if ( SwitchTone )
        MIDI_OUT3(0x90+i, ton_auf_kanal[i].key, 64);  //3 velo speichern ??
    }
}

void OutMidiPort::Sustain(char on, int channel)
{
  for (int i = 0; i < 16; i++)
    if ( ton_auf_kanal[i].id && (ton_auf_kanal[i].id >> 24) == channel )
    {
 	    MIDI_OUT3(0xB0+i, 64, on);
      Cd[i].Sustain = on;
    }
}

//void Gis(GisToken *token, char turn) {};

void OutMidiPort::MidiOut(DWORD data, char n)
{
  midiOutShortMsg(hMidiOut, data);
}

void OutMidiPort::Quite(Route *r)
{
  for (int i = 0; i < 16; i++)
    if ( ((ton_auf_kanal[i].id >> 16) & 0x0FF) == r->Id )
      NoteOff(r->Box, ton_auf_kanal[i].id % 256, 64, r,  ton_auf_kanal[i].id >> 24);
}

// InMidiPort -------------------------------------------------------

void CALLBACK _export MidiInPortFunc(HMIDIIN hMidiIn, UINT wMsg, DWORD dwInstance, DWORD dwParam1, DWORD dwParam2)
{
//  CurrentTimeStamp = dwParam2;
  if ( wMsg != MIM_DATA || dwParam1 % 256 > 240 ) return;
  // Daten in Midi-Automat
  ((InMidiPort*)dwInstance)->Proceed(dwParam1);
}

// InMidiPort -------------------------------------------------------

void InMidiPort::Open()
{
  for (int i = 0; i < 16; i++)
    Cd[i].Reset();
  midiInOpen(&hMidiIn, DevId, (DWORD)MidiInPortFunc, (DWORD)this, CALLBACK_FUNCTION);
  midiInStart(hMidiIn);
}

void InMidiPort::Close()
{
  midiInStop(hMidiIn);
  midiInReset(hMidiIn);
  midiInClose(hMidiIn);
  Quite();
};

#define MIDICODE(i) \
  (((BYTE*)(&midiCode))[i])

// für bestimmte Route Codeverarbeitung
void InMidiPort::ProceedRoute(DWORD midiCode, Route *route)
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
	  case 0xA0:
	  case 0xD0: // Key Pressure, Controler, Channel Pressure
      //3 ??
  		break;
  }
  // Midianalyse
  int lMidiCode[8] = { 3, 3, 3, 3, 2, 2, 3, 1 };
  for (int i = 0; i < lMidiCode[MidiStatus >> 5]; i++)
  {
    MidiAnalysis(Box, midiCode && 0xFF);
    midiCode >>= 8;
  }
}

// Routen testen und jenachdem entsprechend Codeverarbeitung
void InMidiPort::Proceed(DWORD midiCode)
{
  char DidOut = 0;
  for (Route *R = Routes; R; R = R->Next)
 	  switch ( R->Type )
	  {
		  case RTchannel:
		    if ( R->Check(midiCode & 0x0F) )
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
}

