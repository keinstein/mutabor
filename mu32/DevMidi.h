// ------------------------------------------------------------------
// Mutabor 3, 1998, R.Krau�e
// MidiPort Klassen
// ------------------------------------------------------------------

#ifndef DEVMIDI_H
#define DEVMIDI_H

#include "Device.h"
#ifdef RTMIDI
  #include "RtMidi.h"
#else
#ifndef H_MMSYSTEM
//  #define WINVER 0x030a
  #include <mmsystem.h>
  #define H_MMSYSTEM
#endif
#endif

// OutMidiPort ------------------------------------------------------

typedef struct TAK {
  int taste;
	int key;
	DWORD id;         // (channel << 24) + (Route->Id << 16) + (Box << 8) + Taste
                    // zum Identifizieren f�rs korrekte Ausschalten
} TonAufKanal;

class OutMidiPort : public OutDevice
{
  public:
    char *Name;
    int DevId;
    int bending_range;
	  OutMidiPort(char *name, int devId, int bendingRange = 1)
	  : OutDevice()
	  {
      Name = strdup(name);
	    DevId = devId;
      bending_range = bendingRange;
	  }
	  ~OutMidiPort() {};
	  virtual bool Open();
	  virtual void Close();
	  virtual void NoteOn(int Box, int taste, int velo, Route *r, int channel, ChannelData *cd);
	  virtual void NoteOff(int Box, int taste, int velo, Route *r, int channel);
	  virtual void NotesCorrect(int box);
	  virtual void Sustain(char on, int channel);
	  virtual int  GetChannel(int taste);
	  virtual void Gis(GisToken *token, char turn) {};
	  virtual void AddTime(frac time) {};
	  virtual void MidiOut(DWORD data, char n);
	  virtual void MidiOut(BYTE *p, char n) {};
    virtual void Quite(Route *r);
    virtual void Panic();
    virtual bool NeedsRealTime() { return true; }
	  virtual char* GetName() { return Name; }
	  virtual DevType GetType() const { return DTMidiPort; }
  private:
#ifdef RTMIDI
    RtMidiOut *hMidiOut;
#else
    HMIDIOUT hMidiOut;
#endif
    ChannelData Cd[16];
    char KeyDir[16];
    TonAufKanal ton_auf_kanal[16];
    int nKeyOn;
};

// InMidiPort -------------------------------------------------------

class InMidiPort : public InDevice
{
  public:
    char *Name;
    int DevId;
    InMidiPort *NextMidiPort;
	  InMidiPort(char *name, int devId)
	  : InDevice()
	  {
      Name = strdup(name);
	    DevId = devId;
      NextMidiPort = 0;
	  }
	  virtual bool Open();
	  virtual void Close();
	  virtual void Stop() {};
	  virtual void Play() {};
	  virtual void Pause() {};
//	   void Proceed(GisReadArtHead *h, char turn, Route *route) {};
//	   void ProceedRoute(GisReadArtHead *h, char turn) {};
	  virtual frac ReadOn(frac time) { return frac(0,0); };
    virtual bool NeedsRealTime() { return true; }
	  virtual char* GetName() { return Name; }
	  virtual DevType GetType() const { return DTMidiPort; }
#ifdef RTMIDI
    RtMidiIn *hMidiIn;
#else
    HMIDIIN hMidiIn;
#endif
    void Proceed(DWORD midiCode);
  private:
    ChannelData Cd[16];
    void ProceedRoute(DWORD midiCode, Route *route);
};

void MidiInit();
#endif
