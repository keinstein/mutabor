// ##################################################################
// header file of MIS (MIDI Intern Structur)
// ##################################################################

#ifndef MIS_H
#define MIS_H

///#define OWN_BYTEARRAY
///#define SIMPLE_PITCH

#include <fstream.h>
#ifdef OWN_BYTEARRAY
  #include "barray.cpp"
#else
  #include <classlib\arrays.h>
  typedef TArray<BYTE> TByteArray;
#endif

#include "gis.h"
#include "gis_head.h"

class GisReadArtHead;

// ------------------------------------------------------------------

class MisTrack;
class MisNote;
class Instrument;

// ------------------------------------------------------------------

struct Channel
{
  WORD Pitch;
  signed char Sound;
  char Track;
  char nNotesOn; // >  0 ... number of sounding notes
};               // <= 0 ... as less as longer not used

// ------------------------------------------------------------------

typedef void MisReadProceed(MisTrack*, DWORD);

extern MisReadProceed MisReadDummy;

class MisFile : public TByteArray
{
  public:
	 char Type;
	 int nTrack;
	 int Speed;
	 char *Id;
	 DWORD Time;
	 MisTrack *Tracks;
    MisNote *Notes;
    Channel Channels[16];
    Instrument *Instruments;
	 MisFile(char *id)
		: TByteArray(100, 0, 100)
	 {
		Type = -1;
		Id = strdup(id);
		nTrack = 0;
      Speed = 0;
		Tracks = 0;
      Notes = 0;
      Instruments = 0;
		Time = 0;
	 }
	 ~MisFile()
	 {
		if ( Tracks ) delete Tracks;
	 }
	 BYTE Get(int i) { return ItemAt(i); }
	 int Load(char *fileName = "tmp.mid");
	 int Save(char *fileName = "tmp.mid");
	 void ReadInit();
	 DWORD ReadOn(DWORD deltaTime = 0, MisReadProceed *proceed = MisReadDummy);
	 void WriteInit();
	 MisTrack *GetTrack(int id);
	 int WriteMis(DWORD midi, MisTrack* track, int trackId);
	 void CountOnDeltaTime(DWORD deltaTime);
    void AddInstrument(int id, char von, char bis);
    MisNote **GetNote(int key, int pitch, int instrumentId);
    char GetChannel(int Instrument, int Pitch, signed char sound);
    int NoteOn(int key, int pitch, char intensity, int id);
    int NoteOff(int key, int pitch, char intensity, int id);
    int WriteGis(GisReadArtHead *head, GisToken *token, char turn, int id);
};

// ------------------------------------------------------------------

class MisTrack : public TByteArray
{
  public:
	 MisTrack *Next;
	 int Id;
	 MisFile *File;
	 DWORD EventLength;
	 DWORD EventPos;
	 DWORD Pos;
	 BYTE StatusByte;
	 DWORD CurrentTime;
	 MisTrack(MisFile *file, int id, MisTrack *next = 0)
		: TByteArray(100, 0, 100)
	 {
		File = file;
		File->nTrack++;
		Id = id;
		Next = next;
		CurrentTime = 0;
		StatusByte = 0;
	 }
	 ~MisTrack()
	 {
		if ( Next ) delete Next;
	 }
	 BYTE Get(int i) { return ItemAt(i); }
	 int Load(ifstream &is);
	 int Save(ofstream &os);
	 void AddMidiText(char MidiNr, char *Text);
	 void AddDeltaTime(DWORD delta);
	 void AddMidi(DWORD para, int length = -1);
	 void AddMidi3(BYTE a1, BYTE a2, BYTE a3);
	 void Copy(MisTrack *from, int &position, int length);
	 DWORD ReadDeltaTime(DWORD &pos);
	 DWORD ReadMidi(DWORD &pos);
	 char NextMeta(DWORD &pos, BYTE &nr, DWORD &startPos);
	 void ReadInit();
	 DWORD ReadOn(DWORD deltaTime, MisReadProceed *proceed);
	 int WriteMis(DWORD midi, MisTrack* track);
    void CountOnDeltaTime(DWORD deltaTime);
    int AddNoteOn(char channel, int key, int pitch, char intensity, signed char sound);
    int AddNoteOff(char channel, int key, char intensity);
//    int WriteGis(GisToken *token, char turn, char intensity);
};

#endif