// ------------------------------------------------------------------
// Mutabor 3, 1998, R.Krauße
// MIDI-File als Device
// ------------------------------------------------------------------

#ifndef DEVMIDF_H
#define DEVMIDF_H

#include <fstream>

#include "Device.h"

#ifdef WX
#include "mhArray.h"
  WX_DEFINE_ARRAY_INT(BYTE, TBYTEBase1);
  DEF_MHARRAY(BYTE, TByteArray, TBYTEBase1);
#else
  #include <classlib/arrays.h>
  typedef TArray<BYTE> TByteArray;
#endif

// Track ------------------------------------------------------------

class Track
{
  public:
    DWORD Time;
    TByteArray *Data;
    Track()
    {
      Time = 0;
      Data = new TByteArray(100, 0, 100);
    }
    ~Track()
    {
      delete Data;
    }
    void WriteDelta();
    void MidiOut3(BYTE c1, BYTE c2, BYTE c3)
    {
      WriteDelta();
      Data->Add(c1);
      Data->Add(c2);
      Data->Add(c3);
    }
    void MidiOut2(BYTE c1, BYTE c2)
    {
      WriteDelta();
      Data->Add(c1);
      Data->Add(c2);
    }
    void Save(mutOFstream &os);
    void Add(BYTE c)
    {
      Data->Add(c);
    }
};

typedef struct TAK1 {
  int taste;
	int key;
	int fine;
	DWORD id;         // (channel << 24) +(Route->Id << 16) + (Box << 8) + Taste
                    // zum Identifizieren fürs korrekte Ausschalten
} TonAufKanal1;

// OutMidiFile ------------------------------------------------------

class OutMidiFile : public OutDevice
{
  public:
    wxString Name;
    int DevId;
    int bending_range;
    OutMidiFile(wxString name, int devId, int bendingRange = 1)
	  : OutDevice(),Name(name)
	  {
	    DevId = devId;
      bending_range = bendingRange;
	  }
	  virtual ~OutMidiFile() {};
	  virtual bool Open();
	  virtual void Close();
	  virtual void NoteOn(int box, int taste, int velo, Route *r, int channel, ChannelData *cd);
	  virtual void NoteOff(int box, int taste, int velo, Route *r, int channel);
	  virtual void NotesCorrect(int box);
	  virtual void Sustain(char on, int channel);
 	  virtual int  GetChannel(int taste) { return -1; } // hier kˆnnte man auch den richtigen Wett ausgeben, macht aber nixcht so viel Sinn
	  virtual void Gis(GisToken *token, char turn) {};
	  virtual void AddTime(frac time) {};
	  virtual void MidiOut(DWORD data, char n);
	  virtual void MidiOut(BYTE *p, char n);
    virtual void Quite(Route *r);
	  virtual wxString &GetName() { return Name; }
	  virtual DevType GetType() const { return DTMidiFile; }
  protected:
    Track Tracks;
    ChannelData Cd[16];
    char KeyDir[16];
    TonAufKanal1 ton_auf_kanal[16];
    int nKeyOn;
};

// InMidiFile -------------------------------------------------------

class InMidiFile : public InDevice
{
 public:
  wxString Name;
  int DevId;
 InMidiFile(wxString name, int devId): InDevice(),Name(name) {
    DevId = devId;
  }
  virtual ~InMidiFile() {};

  virtual bool Open();
  virtual void Close();
  virtual void Stop();
  virtual void Play();
  virtual void Pause();
//	   void Proceed(GisReadArtHead *h, char turn, Route *route) {};
//	   void ProceedRoute(GisReadArtHead *h, char turn) {};
  virtual frac ReadOn(frac time) { return frac(0, 1); }
  virtual wxString & GetName() { return Name; }
  virtual DevType GetType() const { return DTMidiFile; }
  void IncDelta();
 protected:
  BYTE FileType;
  size_t nTrack;
  int Speed;
  BYTE **Track;
  DWORD *TrackPos;
  long *curDelta;
  long minDelta;
  long actDelta;
  BYTE *StatusByte;
  ChannelData Cd[16];
  UINT TimerId;
  BOOL Busy;
  DWORD TicksPerQuater;
  long MMSPerQuater;
  void Proceed(DWORD midiCode, int track);
  void ProceedRoute(DWORD midiCode, Route *route);
  long ReadMidiProceed(size_t nr, long time);
};

// Function ---------------------------------------------------------

void StartCurrentTime();
void StopCurrentTime();

#endif
