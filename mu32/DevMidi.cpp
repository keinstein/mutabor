// ------------------------------------------------------------------
// Mutabor 3, 1998, R.Krauﬂe
// MidiPort Klassen
// ------------------------------------------------------------------

#include "DevMidi.h"
#include "Execute.h"
#include "GrafKern.h"

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

#ifdef RTMIDI
  #include "RtMidi.h"
  extern RtMidiOut *rtmidiout;
  extern RtMidiIn *rtmidiin;
#endif

// Midi-Ausgabe
#ifdef RTMIDI
#define MIDI_OUT3(code1, code2, code3) \
  { std::vector<unsigned char> message; \
    message.push_back(code1);            \
    message.push_back(code2);            \
    message.push_back(code3);            \
    hMidiOut->sendMessage(&message); }

#define MIDI_OUT2(code1, code2) \
  { std::vector<unsigned char> message; \
    message.push_back(code1);            \
    message.push_back(code2);            \
    hMidiOut->sendMessage(&message); }
#else
#define MIDI_OUT3(code1, code2, code3) \
  midiOutShortMsg(hMidiOut, \
    ((DWORD) (code3) << 16) + \
    ((DWORD) (code2) << 8) +   \
    ((DWORD) (code1)))

#define MIDI_OUT2(code1, code2) \
  midiOutShortMsg(hMidiOut, \
    ((DWORD) (code2) << 8) +   \
    ((DWORD) (code1)))
#endif

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

bool OutMidiPort::Open()
{
  int i;
  for (i = 0; i < 16; i++)
  {
    Cd[i].Reset();
    ton_auf_kanal[i].taste = 0;
    ton_auf_kanal[i].id = 0;
  }

  nKeyOn = 0;
  for (i = 0; i < 16; i++)
    KeyDir[i] = (char)i; // alle nicht benutzt
#ifdef RTMIDI
  // RtMidiIn constructor
  try {
    hMidiOut = new RtMidiOut();
  }
  catch (RtError &error) {
    LAUFZEIT_ERROR0(_("Can not open ouput Midi devices."));
    return false;
  }
  try {
    hMidiOut->openPort(DevId);
  }
  catch (RtError &error) {
    LAUFZEIT_ERROR2(_("Can not open output Midi device nr. %d (%s)"), DevId, (GetName().c_str()));
    return false;
  }
#else
  midiOutOpen(&hMidiOut, DevId, NULL, NULL, NULL);
#endif
  for (i = 0; i < 16; i++)
  {
    MIDI_OUT3(0xE0+i, 0, 0); // pitch auf 0
  	 MIDI_OUT3(0xB0+i, 122, 0);  // local off
	 MIDI_OUT3(0xB0+i, 125, 0);  // omni on
	 MIDI_OUT3(0xB0+i, 127, 0);  // poly on
  }
  return true;
}

void OutMidiPort::Close()
{
  // alle liegenden Tˆne ausschalten
  for (int i = 0; i < 16; i++)
    if ( KeyDir[i] >= 16 )  // benutzt
      MIDI_OUT3(0x80+i, ton_auf_kanal[i].key, 64);
/*  for (int i = 0; i < 16; i++)
	 MidiOut3(176+i, 122, 1);  // local on */
  // Device schlieﬂen
#ifdef RTMIDI
  hMidiOut->closePort();
  delete hMidiOut;
#else
  midiOutClose(hMidiOut);
#endif
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
   if ( j != DRUMCHANNEL || !r->ONoDrum )
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
     if ( j != DRUMCHANNEL || !r->ONoDrum )
      AM += ton_auf_kanal[j].taste;
    AM /= r->OTo + 1 - r->OFrom;
    for ( j = r->OFrom; j <= r->OTo; j++ )
     if ( j != DRUMCHANNEL || !r->ONoDrum )
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
    KeyDir[free] = (char)(15+nKeyOn);
  }
  else
  {
    nKeyOn++;
    KeyDir[free] = (char)(15 + nKeyOn);
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
  // Bank testen
  if ( (s = cd->BankSelectMSB) != Cd[free].BankSelectMSB && s != -1 )
  {
    MIDI_OUT3(0xB0+free, 0, (BYTE) s);
    Cd[free].BankSelectMSB = s;
  }
  if ( (s = cd->BankSelectLSB) != Cd[free].BankSelectLSB && s != -1 )
  {
    MIDI_OUT3(0xB0+free, 32, (BYTE) s);
    Cd[free].BankSelectLSB = s;
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
   if ( i != DRUMCHANNEL || !r->ONoDrum )
    if ( KeyDir[i] >= 16 && ton_auf_kanal[i].id == id )
    {
      ton_auf_kanal[i].taste=0;
// ???     ton_auf_kanal[i].id=0;
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
    if ( (KeyDir[i] >= 16 && ton_auf_kanal[i].id) || Cd[i].Sustain )
    {
      int Box = (ton_auf_kanal[i].id >> 8) & 0xFF;
      if ( Box != box )
        break;
      long freq = GET_FREQ(ton_auf_kanal[i].taste, tonsystem[Box]);
      // hier kann ein evtl. grˆﬂerer bending_range genutzt werden, um
      // Ton aus und einschalten zu vermeiden
      if ( ton_auf_kanal[i].key == (zugriff[3] & 0x7f) &&
        Cd[i].Pitch == ((DWORD)freq & 0xFFFFFF) )
        continue;
      long Delta = freq - ((long)ton_auf_kanal[i].key << 24);
      bool SwitchTone = (LongAbs(Delta) >= ((long)bending_range << 24));
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
        Delta = freq - ((long)ton_auf_kanal[i].key << 24);
      }
      else if ( Delta == Cd[i].Pitch )
        continue;
      // Spezialbending (groﬂer Range)
      Cd[i].Pitch = Delta;
      Delta /= (4*bending_range);
      Delta +=  0x400000; // lieber hier addieren //9
      MIDI_OUT3(0xE0+i, ((BYTE*)&Delta)[1] >> 1, (((BYTE*)&Delta)[2]));
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

int OutMidiPort::GetChannel(int taste)
{
  for (int i = 0; i < 16; i++)
    if ( ton_auf_kanal[i].id && (ton_auf_kanal[i].taste == taste) )
      return i;
  return -1;
}

//void Gis(GisToken *token, char turn) {};

#ifdef RTMIDI
void OutMidiPort::MidiOut(DWORD data, char n)
{
  std::vector<unsigned char> message;
  while ( n-- )
  {
    message.push_back(data & 0xFF);
    data >>= 8;
  }
  hMidiOut->sendMessage(&message);
}

#else
void OutMidiPort::MidiOut(DWORD data, char n)
{
  midiOutShortMsg(hMidiOut, data);
}
#endif

void OutMidiPort::Quite(Route *r)
{
  for (int i = 0; i < 16; i++)
    if ( ((ton_auf_kanal[i].id >> 16) & 0x0FF) == r->Id )
      NoteOff(r->Box, ton_auf_kanal[i].id % 256, 64, r,  ton_auf_kanal[i].id >> 24);
}

void OutMidiPort::Panic()
{
  for (int i = 0; i < 16; i++)
  {
	  MIDI_OUT3(176+i, 123, 0);  // All notes off */
    MIDI_OUT3(0xB0+i, 7, 127);  // main volume
    // sound piano
    MIDI_OUT2(0xC0+i, 0);
    // Merker aufr‰umen
    ton_auf_kanal[i].taste=0;
    ton_auf_kanal[i].id=0;
    Cd[i].Sound = 0;
    Cd[i].Sustain = 0;
    KeyDir[i] = i; // alle nicht benutzt
  }
  nKeyOn = 0;
}

// InMidiPort -------------------------------------------------------

#ifdef RTMIDI

void mycallback( double deltatime, std::vector< unsigned char > *message, void *userData )
{
  DWORD data = 0;
  for (int i = message->size()-1; i >= 0; i--)
    data = ((data << 8) | ((unsigned char)(*message)[i]));
  ((InMidiPort*)userData)->Proceed(data);
}

#else

void CALLBACK _export MidiInPortFunc(HMIDIIN hMidiIn, UINT wMsg, DWORD dwInstance, DWORD dwParam1, DWORD dwParam2)
{
//  CurrentTimeStamp = dwParam2;
  if ( wMsg != MIM_DATA || dwParam1 % 256 > 240 ) return;
  // Daten in Midi-Automat
  ((InMidiPort*)dwInstance)->Proceed(dwParam1);
}

#endif

// InMidiPort -------------------------------------------------------

bool InMidiPort::Open()
{
  for (int i = 0; i < 16; i++)
    Cd[i].Reset();
#ifdef RTMIDI
  try {
    hMidiIn = new RtMidiIn();
  }
  catch (RtError &error) {
    LAUFZEIT_ERROR0(_("Can not open Midi input devices."));
    return false;
  }
  try {
    hMidiIn->openPort(DevId);
  }
  catch (RtError &error) {
    LAUFZEIT_ERROR2(_("Can not open Midi input device no. %d (%s)."), DevId, (GetName().c_str()));
    return false;
  }
  hMidiIn->setCallback(mycallback, this);
#else
  midiInOpen(&hMidiIn, DevId, (DWORD)MidiInPortFunc, (DWORD)this, CALLBACK_FUNCTION);
  midiInStart(hMidiIn);
#endif
  return true;
}

void InMidiPort::Close()
{
#ifdef RTMIDI
  hMidiIn->closePort();
  delete hMidiIn;
#else
  midiInStop(hMidiIn);
  midiInReset(hMidiIn);
  midiInClose(hMidiIn);
#endif
  Quite();
};

#define MIDICODE(i) \
  (((BYTE*)(&midiCode))[i])

// f¸r bestimmte Route Codeverarbeitung
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
  }
  // Midianalyse
  int lMidiCode[8] = { 3, 3, 3, 3, 2, 2, 3, 1 };
  if ( Box >= 0 && route->Active )
    for (int i = 0; i < lMidiCode[MidiStatus >> 5]; i++)
    {
      MidiAnalysis(Box, MIDICODE(0));
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
		  case RTstaff:
		    if ( ((midiCode & 0xF0) != 0x80 && (midiCode & 0xF0) != 0x90) || R->Check((midiCode >> 8) & 0xFF) )
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

#ifdef RTMIDI
  #include <string>
  using namespace std;
  #include "RtMidi.h"
  RtMidiOut *rtmidiout;
  RtMidiIn *rtmidiin;
#endif

void MidiInit()
{
#ifdef RTMIDI
  try {
    rtmidiout = new RtMidiOut();
  }
  catch (RtError &error) {
    error.printMessage();
    exit(EXIT_FAILURE);
  }
  try {
    rtmidiin = new RtMidiIn();
  }
  catch (RtError &error) {
    error.printMessage();
    exit(EXIT_FAILURE);
  }
#endif
}
