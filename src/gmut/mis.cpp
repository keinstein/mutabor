// ##################################################################
// MIS (MIDI Intern Structur)
// ##################################################################

#include "mis.h"

int bending_range = 2;

#ifdef SIMPLE_PITCH

  #define ADDPITCH(channel, pitch) \
	 AddMidi3(0xE0+channel, 1, 64+(pitch / 128)/bending_range)

#else

  #define ADDPITCH(channel, pitch) \
	 int pitchbend = (pitch) / bending_range + 0x2000; \
	 AddMidi3(0xE0+channel, pitchbend & 0x7F, (pitchbend >> 7))

#endif

int lMidiCode[8] = { 3, 3, 3, 3, 2, 2, 3, 1 };

// ##################################################################
// help procedures

DWORD ReadLength(istream &is)
{
  BYTE a1, a2, a3, a4;
  is >> a1 >> a2 >> a3 >> a4;
  return (((DWORD)a1) << 24) + (((DWORD)a2) << 16) +
	 (((DWORD)a3) << 8) + ((DWORD)a4);
}

void WriteLength(ostream &os, DWORD l)
{
  os.put((BYTE) ((l >> 24) & 0xFF));
  os.put((BYTE) ((l >> 16) & 0xFF));
  os.put((BYTE) ((l >> 8) & 0xFF));
  os.put((BYTE) (l & 0xFF));
}

// ------------------------------------------------------------------

// dummy procedure for MisReadOn
void MisReadDummy(MisTrack*, DWORD)
{
  // just a dummy
}

// ##################################################################
// MisNote

class MisNote
{
  public:
	 MisNote *Next;
    char Key;
    int InstrumentId;
    char Channel;
    MisNote(char key, int instrumentId, char channel, MisNote* next = 0)
    {
      Key = key;
		InstrumentId = instrumentId;
      Channel = channel;
      Next = next;
	 }
};

// ##################################################################
// Instrument

class Instrument
{
  public:
	 Instrument *Next;
	 int Id;
	 char Von, Bis;
	 signed char Sound;
    Instrument(int id, char von, char bis, Instrument *next = 0)
	 {
      Id = id;
      Von = von;
      Bis = bis;
      Sound = -1;
      Next = next;
    }
};

Instrument *GetInstrument(Instrument *root, int id)
{
  while ( root )
  {
	 if ( root->Id == id ) return root;
	 root = root->Next;
  }
  return root;
}

// ##################################################################
// methods of MIS structures

// MisFile ----------------------------------------------------------

int MisFile::Load(char *fileName)
{
  ifstream is(fileName, ios::in | ios::binary);
  if ( is.bad() )
	 return is.bad();
  // header mark
  char Header[5];
  is.get(Header, 5);
  DWORD l = ReadLength(is);
  BYTE a, b;
  // file type
  is >> a >> Type;
  // number of tracks
  is >> a >> b;
  int NTrack = (((int)a) << 8) + b;
  // speed info
  is >> a >> b;
  Speed = (((int)a) << 8) + b;
  //  rest of header
  for (DWORD i = 6; i < l && !is.eof() && !is.bad(); i++ )
  {
	 is.get(a);
	 Add(a);
  }
  int res = is.bad();
  // read tracks
  MisTrack **CurrentTrack = &Tracks;
  for (i = 0; i < NTrack && !res; i++ )
  {
	 MisTrack *Track = new MisTrack(this, i);
	 res = Track->Load(is);
	 *CurrentTrack = Track;
    CurrentTrack = &Track->Next;
  }
  if ( !res ) is.close();
  return res;
}

// save Midi as file
int MisFile::Save(char *fileName)
{
  // open file
  ofstream os(fileName, ios::out | ios::binary);
  if ( os.bad() )
	 return os.bad();
  // write header
  os << "MThd";
  WriteLength(os, GetItemsInContainer()+6);
  // write Type
  os << (char) 0 << Type;
  // write number of tracks
  os << (char) (nTrack >> 8) << (char) (nTrack & 0xFF);
  // write speed info
  os << (char) (Speed >> 8) << (char) (Speed & 0xFF);
  // rest of header
  for (DWORD i = 0; i < GetItemsInContainer(); i++)
	 os.put(Get(i));
  // write tracks
  int res = 0;
  if ( Tracks ) res = Tracks->Save(os);
  // close file
  if ( !res ) os.close();
  return res;
}

// init before reading
void MisFile::ReadInit()
{
  Time = 0;
  if ( Tracks )
	 Tracks->ReadInit();
}

// read all events in the given delta time
DWORD MisFile::ReadOn(DWORD deltaTime, MisReadProceed *proceed)
{
  Time += deltaTime;
  if ( Tracks )
	 return Tracks->ReadOn(deltaTime, proceed);
  else
	 return 0;
}

void MisFile::WriteInit()
{
  // reset tracks
  nTrack = 0;
  delete Tracks;
  Tracks = 0;
  // reset time
  Time = 0;
  // reset channels
  for (int i = 0; i < 16; i++)
  {
    Channels[i].Pitch = 0;
	 Channels[i].Sound = -1;
	 Channels[i].Track = -1;
    Channels[i].nNotesOn = 0;
  }
  // reset time
  Time = 0;
  // speed ???
  Speed = 96;
  Type = 1;
}

MisTrack *MisFile::GetTrack(int id)
{
  // search track
  MisTrack **t = &Tracks;
  while ( *t )
  {
	 if ( (*t)->Id == id )
		return *t;
	 if ( (*t)->Id > id )
		break;
	 t = &((*t)->Next);
  }
  // not found, so build a new
  *t = new MisTrack(this, id, *t);
  (*t)->CurrentTime = Time;
  return *t;
}

int MisFile::WriteMis(DWORD midi, MisTrack* track, int trackId)
{
  return GetTrack(trackId)->WriteMis(midi, track);
}

void MisFile::CountOnDeltaTime(DWORD deltaTime)
{
  Time += deltaTime;
  if ( Tracks )
	 Tracks->CountOnDeltaTime(deltaTime);
}

void MisFile::AddInstrument(int id, char von, char bis)
{
  Instruments = new Instrument(id, von, bis, Instruments);
}

MisNote **MisFile::GetNote(int key, int pitch, int instrumentId)
{
  MisNote **note = &Notes;
  while ( *note )
  {
    if ( (*note)->Key == key && (*note)->InstrumentId == instrumentId &&
		Channels[(*note)->Channel].Pitch == pitch )
      break;
    note = &(*note)->Next;
  }
  return note;
}

char MisFile::GetChannel(int instrument, int pitch, signed char sound)
{
  // get instrument
  Instrument *Inst = GetInstrument(Instruments, instrument);
  if ( !Inst ) return -1;
  // check for channels with same pitch and sound
  for (int i = Inst->Von; i <= Inst->Bis; i++)
	 if ( Channels[i].Pitch == pitch && Channels[i].Sound == sound )
		return i;
  // get that channel, that was free for the longest time
  int ch = Inst->Von;
  int value = Channels[ch].nNotesOn;
  for (i = ch+1; i <= Inst->Bis; i++)
	 if ( Channels[i].nNotesOn < value )
	 {
		ch = i;
		value = Channels[i].nNotesOn;
	 }
  if ( value <= 0 )
	 return ch;
  // nothing free
  return -1;
}

int MisFile::NoteOn(int key, int pitch, char intensity, int id)
{
  int Sound = GetInstrument(Instruments, id)->Sound;
  char ch = GetChannel(id, pitch, Sound);
  if ( ch == -1 ) return 1; // no free channel
  GetTrack(Channels[ch].Track)->AddNoteOn(ch, key, pitch, intensity,
	 GetInstrument(Instruments, id)->Sound);
  // add a note
  Notes = new MisNote(key, id, ch, Notes);
  // notes on channel info
  Channels[ch].nNotesOn++;
  return 0;
}

int MisFile::NoteOff(int key, int pitch, char intensity, int id)
{
  MisNote **np = GetNote(key, pitch, id);
  MisNote *n = *np;
  if ( !n ) return 1; // note not on
  char ch = n->Channel;
  GetTrack(Channels[ch].Track)->AddNoteOff(ch, key, intensity);
  // delete corresponding note
  *np = n->Next;
  delete n;
  // notes on channel info
  if ( !(--Channels[ch].nNotesOn) )
  {
    Instrument *Inst = GetInstrument(Instruments, id);
    for (int i = Inst->Von; i <= Inst->Bis; i++)
      if ( i != ch && Channels[i].nNotesOn <= 0 )
		  Channels[i].nNotesOn--;
  }
  return 0;
}

int MisFile::WriteGis(GisReadArtHead *head, GisToken *token, char turn, int id)
{
  switch ( GetGisType(token) )
  {
	 case GTTag:
		break;
	 case GTNote:
		if ( turn == 2 ) return 0;
		int Key = ((GisNote*)token)->GetKey();
		if ( Key == -1 ) return 1;
		Key += head->GetOctave() * 12;
		if ( !turn ) // note on
		  NoteOn(Key, head->GetAlter(), head->GetIntensity(turn), id);
		else
		  NoteOff(Key, head->GetAlter(), head->GetIntensity(turn), id);
		break;
  }
///  return GetMatchingTrack(id)->WriteGis(token, turn, intensity);
  return 0;
}

// MisTrack ---------------------------------------------------------

int MisTrack::Load(ifstream &is)
{
  // header mark
  char Header[5];
  is.get(Header, 5);
  DWORD l = ReadLength(is);
  BYTE a;
  // data
  for (DWORD i = 0; i < l && !is.eof() && !is.bad(); i++ )
  {
	 is.get(a);
	 Add(a);
  }
  // remove the "end of track" tag
  DWORD Pos = 0, StartPos;
  BYTE Nr = 0;
  while ( NextMeta(Pos, Nr, StartPos) )
	 if ( Nr == 0x2F )
	 {
		while ( GetItemsInContainer() > StartPos )
        Detach((int)StartPos);
      break;
	 }
  return is.bad();
}

// write track into file
int MisTrack::Save(ofstream &os)
{
  // write header
  os << "MTrk";
  WriteLength(os, GetItemsInContainer() + 4);
  // write data
  for (DWORD i = 0; i < GetItemsInContainer(); i++)
	 os.put(Get(i));
  // write end of track tag
  os << (BYTE) 0x00;
  os << (BYTE) 0xFF;
  os << (BYTE) 0x2F;
  os << (BYTE) 0x00;
  // write next track
  if ( Next ) Next->Save(os);
  return os.bad();
}

void MisTrack::AddMidiText(char midiNr, char *text)
{
  Add(0x00);
  Add(0xFF);
  Add(midiNr);
  Add(strlen(text)+1);
  for (int i = 0; i < strlen(text); i++)
	 Add(text[i]);
  Add(0x00);
}

void MisTrack::AddDeltaTime(DWORD delta)
{
  BYTE w[5];
  int i = 0;
  w[0] = (BYTE)delta & 0x7F;
  delta >>= 7;
  while ( delta )
  {
	 i++;
	 w[i] = 0x80 | (BYTE) (delta & 0x7F);
	 delta >>= 7;
  }
  for (;i>=0;i--)
	 Add(w[i]);
}

void MisTrack::AddMidi(DWORD para, int length)
{
/*  if ( LastTimeStamp[nr] == NOTIME )
	 RecordTime(nr, 0);
  else
	 RecordTime(nr, CurrentTimeStamp - LastTimeStamp[nr]);
  LastTimeStamp[nr] = CurrentTimeStamp;  */
  if ( length == -1 )
	 length = lMidiCode[(BYTE)(para >> 4) & 07];
  BYTE a = para & 0xFF;
#ifndef NO_RUNNING_STATUS
  if ( a != StatusByte || a >= 0xF0 )
    Add(StatusByte = a);
#else
  Add(a);
#endif
  for ( int i = 1; i < length; i++ )
  {
	 para >>= 8;
	 Add(para & 0xFF);
  }
}

void MisTrack::AddMidi3(BYTE a1, BYTE a2, BYTE a3)
{
#ifndef NO_RUNNING_STATUS
  if ( a1 != StatusByte || a1 >= 0xF0 )
    Add(StatusByte = a1);
#else
  Add(a1);
#endif
  Add(a2);
  Add(a3);
}

void MisTrack::Copy(MisTrack *from, int &position, int length)
{
  for (int j = 0; j < length; j++)
	 Add((*from)[position++]);
}

DWORD MisTrack::ReadDeltaTime(DWORD &pos)
{
  DWORD l = 0;
  BYTE a;
  do
  {
	 a = Get(pos++);
	 l = (l << 7) + (a & 0x7F);
  }
  while ( a & 0x80 );
  return l;
}

// reads the next midi event
DWORD MisTrack::ReadMidi(DWORD &pos)
{
  DWORD a = Get(pos++);
  if ( a & 0x80 )
	 StatusByte = a;
  else
  {
	 pos--;
	 a = StatusByte;
  }
  if ( StatusByte <  0xF0 ) // normaler midi code
  {
	 int l = lMidiCode[(StatusByte >> 4) & 07];
	 int shift = 8;
    for (int i = 1; i < l; i++)
    {
		a += (DWORD)Get(pos++) << shift;
		shift += 8;
	 }
  }
  else if ( StatusByte == 0xF0 || StatusByte == 0xF7 ) // SysEx I, SysEx II
  {
    EventLength = ReadDeltaTime(pos); // length
	 EventPos = pos;               // position of Data
    pos += EventLength;
  }
  else if ( StatusByte == 0xFF ) // meta event
  {
	 a += Get(pos++) << 8;         // event number
	 EventLength = ReadDeltaTime(pos); // length
	 EventPos = pos;               // position of Data
    pos += EventLength;
  }
  else if ( StatusByte == 0xF2 ) // song position pointer
  {
	 a += Get(pos++) << 8;
	 a += Get(pos++) << 16;
  }
  else if ( StatusByte == 0xF3 ) // song select
	 a += Get(pos++) << 8;
  return a;
}

// looks for the next meta event, returns 0, if there is no
char MisTrack::NextMeta(DWORD &pos, BYTE &nr, DWORD &startPos)
{
  while ( pos < GetItemsInContainer() )
  {
	 startPos = pos;
	 ReadDeltaTime(pos);
	 DWORD midi = ReadMidi(pos);
	 if ( (midi & 0xFF) == 0xFF )
	 {
		nr = midi >> 8;
		return 1;
	 }
  }
  return 0;
}

// prepare reading
void MisTrack::ReadInit()
{
  Pos = 0;
  if ( Pos < GetItemsInContainer() )
	 CurrentTime = ReadDeltaTime(Pos);
  if ( Next ) Next->ReadInit();
}

// read on track on deltaTime, returns minimum free delta time token
DWORD MisTrack::ReadOn(DWORD deltaTime, MisReadProceed *proceed)
{
  DWORD DeltaTime = deltaTime;
  while ( CurrentTime <= DeltaTime && Pos < GetItemsInContainer() )
  {
	 DWORD Midi = ReadMidi(Pos);
	 proceed(this, Midi);
	 DeltaTime -= CurrentTime;
	 if ( Pos < GetItemsInContainer() )
		CurrentTime = ReadDeltaTime(Pos);
  }
  if ( Pos < GetItemsInContainer() )
	 CurrentTime -= DeltaTime;
  else
	 CurrentTime = 0;
  DWORD NextTime = 0;
  if ( Next )
	 NextTime = Next->ReadOn(deltaTime, proceed);
  if ( !CurrentTime )
	 return NextTime;
  if ( !NextTime )
	 return CurrentTime;
  return min(CurrentTime, NextTime);
}

// write data from another MisFile
int MisTrack::WriteMis(DWORD midi, MisTrack* track)
{
  // write delta time
  AddDeltaTime(CurrentTime);
  CurrentTime = 0;
  // write midi
#ifndef NO_RUNNING_STATUS
  BYTE a = (BYTE)midi & 0xFF;
  if ( StatusByte != a || a >= 0xF0 )
  {
	 StatusByte = a;
	 Add(StatusByte);
  }
#else
  Add(midi & 0xFF);
  StatusByte = midi & 0xFF;
#endif
  if ( StatusByte <  0xF0 ) // normaler midi code
  {
	 int l = lMidiCode[(StatusByte >> 4) & 07];
	 int shift = 8;
	 for (int i = 1; i < l; i++)
	 {
		Add((BYTE)(midi >> shift) & 0xFF);
		shift += 8;
	 }
  }
  else if ( StatusByte == 0xF0 || StatusByte == 0xF7 ) // SysEx I, SysEx II
  {
	 AddDeltaTime(track->EventLength);
	 DWORD Pos = track->EventPos;
	 for (int i = 0; i < track->EventLength; i++)
		Add((*track)[Pos++]);
  }
  else if ( StatusByte == 0xFF ) // meta event
  {
	 Add(midi >> 8);         // event number
	 AddDeltaTime(track->EventLength);
	 DWORD Pos = track->EventPos;
	 for (int i = 0; i < track->EventLength; i++)
		Add((*track)[Pos++]);
  }
  else if ( StatusByte == 0xF2 ) // song position pointer
  {
	 Add(midi >> 8);
	 Add(midi >> 16);
  }
  else if ( StatusByte == 0xF3 ) // song select
	 Add(midi >> 8);
  return 0;
}

void MisTrack::CountOnDeltaTime(DWORD deltaTime)
{
  CurrentTime += deltaTime;
  if ( Next )
	 Next->CountOnDeltaTime(deltaTime);
}

int MisTrack::AddNoteOn(char channel, int key, int pitch, char intensity, signed char sound)
{
  Channel *Ch = &(File->Channels[channel]);
  // write sound
  if ( Ch->Sound != sound || sound != -1)
  {
	 AddDeltaTime(CurrentTime);
    CurrentTime = 0;
    AddMidi(0xC0+channel + (sound << 8), 2);
	 Ch->Sound = sound;
  }
  // write pitch
  if ( Ch->Pitch != pitch )
  {
    AddDeltaTime(CurrentTime);
    CurrentTime = 0;
	 ADDPITCH(channel, pitch);
	 Ch->Pitch = pitch;
  }
  // write note on
  AddDeltaTime(CurrentTime);
  CurrentTime = 0;
  AddMidi3(0x90+channel, key, intensity);
  return 0;
}

int MisTrack::AddNoteOff(char channel, int key, char intensity)
{
  // write delta time
  AddDeltaTime(CurrentTime);
  CurrentTime = 0;
  // write note off
  AddMidi(0x80+channel + (key<<8) + (intensity<<16), 3);
  return 0;
}
/*
int MisTrack::WriteGis(GisToken *token, char turn, char intensity)
{
  if ( GetGisType(token) == GTNote )
  {
    if ( !turn )
    {
      AddDeltaTime(CurrentTime);
      CurrentTime = 0;
      int key = Name2Key(((GisNote*)token)->Name);
      key += Acc2Int(((GisNote*)token)->Name);
      AddMidi(0x90+Id + (key << 8) + (intensity <<16), 3);
    }
    else if ( turn == 1 )
    {
      AddDeltaTime(CurrentTime);
      CurrentTime = 0;
      int key = Name2Key(((GisNote*)token)->Name);
      key += Acc2Int(((GisNote*)token)->Name);
      AddMidi(0x80+Id + (key << 8) + (intensity <<16), 3);
    }

  }


}


/*
//#define RECORDDATAOFFSET (22 + 27)
#define RECORDDATAOFFSET (22 + 12)
#define JOINDATAOFFSET 22
#define NOTIME 0xFFFFFFFF
//#define NOT_TRIMM

char RecordMode = REC_NO;
char MidiTmpFile[100] = "MIDI.$$$";

DWORD LastTimeStamp[2] = {NOTIME, NOTIME};
DWORD CurrentTimeStamp = NOTIME;


void pascal _export GetMidiInfo(MIDIINFO &midiinfo)
{
  strncpy(midiinfo.FileName, MidiFileName, 100);
  // Durchsucht die Tracks nach MetaEvents
  strncpy(midiinfo.Title, "", 100);
  strncpy(midiinfo.Copyright, "", 100);
  strncpy(midiinfo.Mutabor, "", 100);
  char s[100];
  // FileDaten
  midiinfo.Type = (Data[0][8] << 8) + Data[0][9];
  midiinfo.nTrack = (Data[0][10] << 8) + Data[0][11];
  // Header überlesen
  DWORD i = 4;
  DWORD lTrack = ReadLength(i);

  i += lTrack + 4;
  DWORD lFile = Data[0].GetItemsInContainer();
  while ( i < lFile )
  {
	 // Track lesen
	 i += 4;
	 lTrack = ReadLength(i) + i + 4;
	 i += 4;
	 // Schleife für die einzelnen Daten
	 BYTE StatusByte;
	 while ( i < lTrack )
	 {
		BYTE EventNr = 0xFF;
		ReadDelta(i);
		BYTE a = Data[0][i++];
		if ( a & 0x80 )
		  StatusByte = a;
		else
		  i--;
		// Anhand des Statusbyte Befehl verarbeiten
		/// auf Kanal 0 trimmen
		if ( StatusByte <  0xF0 )
		{
			// "normaler" MidiCode
			int l = lMidiCode[(StatusByte >> 4) & 07];
			i += l - 1;
		}
		else if ( StatusByte == 0xF0 || StatusByte == 0xF7 )
		{
		  // SysEx I, SysEx II
		  DWORD l = ReadDelta(i);            // Länge
		  i += l;
		}
		else if ( StatusByte == 0xFF )
		{
		  // Meta-Event
		  EventNr = Data[0][i++];            // Event-Nr.
		  DWORD l = ReadDelta(i);            // Länge
        if ( l + i >= lFile ) return;      // bei Fehler in Datei
		  for (int j = 0; j < l; j++)        // Daten
		  {
			 if ( j < 99 ) s[j] = Data[0][i];
			 i++;
		  }
		  if ( j < 99 ) s[j] = 0; else s[99] = 0;
		}
		else if ( StatusByte == 0xF2 )
		  i += 2;  // Song Position Pointer
		else if ( StatusByte == 0xF3 )
		  i++;  // Song Select
		if ( EventNr == 3 && !midiinfo.Title[0] )
		  strncpy(midiinfo.Title, s, 100);
		if ( EventNr == 2 && !midiinfo.Copyright[0] )
		  strncpy(midiinfo.Copyright, s, 100);
		if ( EventNr == 1 && !midiinfo.Mutabor[0] && !strncmp(s, "MUTABOR: ", 9) )
		  strncpy(midiinfo.Mutabor, &(s[9]), 100);
	 }
	 if ( midiinfo.Title[0] && midiinfo.Copyright[0] &&
      midiinfo.Mutabor[0]) return;
  }
}

BOOL pascal _export MidiFileThere()
{
  return Data[0].GetItemsInContainer() != 0;
}

int pascal _export GetMidiTrackNumber()
{
  if ( !MidiFileThere() )
    return 0;
  int Type = (Data[0][8] << 8) + Data[0][9];
  if ( Type == 0 ) return 1;
  return (Data[0][10] << 8) + Data[0][11];
}

void TranslateSystemMessages(DWORD &i, BYTE StatusByte)
{
  // DeltaTime schreiben
  RecordTime(1, CurrentTimeStamp - LastTimeStamp[1]);
  LastTimeStamp[1] = CurrentTimeStamp;
  Data[1].Add(StatusByte);           // StatusByte schreiben
  // entspechend der Messages bearbeiten
  if ( StatusByte == 0xF0 || StatusByte == 0xF7 )
  {
	 // SysEx I, SysEx II
	 DWORD l = ReadDelta(i);            // Länge
	 RecordTime(1, l);
	 for (int j = 0; j < l; j++)        // Daten
		Data[1].Add(Data[0][i++]);
  }
  else if ( StatusByte == 0xFF )
  {
	 // Meta-Event
	 BYTE nr = Data[0][i++];            // Event-Nr.
	 Data[1].Add(nr);
	 DWORD l = ReadDelta(i);            // Länge
	 RecordTime(1, l);
	 for (int j = 0; j < l; j++)        // Daten
		Data[1].Add(Data[0][i++]);
  }
  else if ( StatusByte == 0xF2 )
  {
	 // Song Position Pointer
	 Data[1].Add(Data[0][i++]);
	 Data[1].Add(Data[0][i++]);
  }
  else if ( StatusByte == 0xF3 )
  {
	 // Song Select
	 Data[1].Add(Data[0][i++]);
  }
}

void pascal _export TranslateMidi()
{
  // die Daten in Data[0] werden durch den Automaten geschickt ,
  // in Data[1] gespeichtert und als MidiTmpFile gespeichert
  if ( !MidiFileThere() ) return;
  // Translate-Modus einstellen
  char RecordModeOld = RecordMode;
  RecordMode = REC_TRAN;
  // Data[1] löschen
  Data[1].Flush();
  // Header übernehmen
  DWORD i = 0;
  CopyData(i, 4);
  DWORD Length = ReadLength(i);
  CopyData(i, Length + 4);
  // große Schleife: Tracks Kopieren
  DWORD lFile = Data[0].GetItemsInContainer();
  while ( i < lFile )
  {
	 // TrackHeader kopieren
	 CopyData(i, 4);
	 // Platz für Längenangabe
	 DWORD iLength = Data[1].GetItemsInContainer();
	 Data[1].Add(0);
	 Data[1].Add(0);
	 Data[1].Add(0);
	 Data[1].Add(0);
	 DWORD lTrack = ReadLength(i) + i + 4;
	 i += 4;
	 CurrentTimeStamp = 0;
	 LastTimeStamp[1] = 0;
	 // Schleife für die einzelnen Daten
	 BYTE StatusByte;
	 while ( i < lTrack )
	 {
		// DeltaTime lesen
		CurrentTimeStamp += ReadDelta(i);
		// Statusbyte lesen, vorsicht: evtl. running status
		BYTE a = Data[0][i++];
		if ( a & 0x80 )
		  StatusByte = a;
		else
		  i--;
		// Anhand des Statusbyte Befehl verarbeiten
		// auf Kanal 0 trimmen
#ifdef NOT_TRIMM
      if ( StatusByte < 0xF0 ) StatusByte &= 0xF0;
#endif
		DWORD w = StatusByte;
      int sel = StatusByte & 0xF0;
		switch ( sel )
		{
		  case 0x80: // MisNote off
						 ;
		  case 0x90: // MisNote on
						 w += Data[0][i++] << 8;
						 w += (DWORD)Data[0][i++] << 16;
						 midi_automat(w);
						 break;
		  case 0xA0: // Polyphonic after touch
						 ;
		  case 0xB0: // Control change
	 					 w += Data[0][i++] << 8;
						 w += (DWORD)Data[0][i++] << 16;
						 midi_automat(w);
						 break;
		  case 0xC0: // Program change
                   w += Data[0][i++] << 8;
                   midi_automat(w);
						 break;
		  case 0xD0: // After touch
						 w += Data[0][i++] << 8;
						 midi_automat(w);
						 break;
		  case 0xE0: // Pitch bend
						 w += Data[0][i++] << 8;
						 w += (DWORD)Data[0][i++] << 16;
						 midi_automat(w);
						 break;
		  case 0xF0: TranslateSystemMessages(i, StatusByte);
		}
	 }
	 // Länge der Tracks schreiben
	 Length = Data[1].GetItemsInContainer() - 4 - iLength;
	 for (int j = 3; j >= 0; j--)
	 {
		Data[1][iLength + j] = Length & 0xFF;
		Length >>= 8;
	 }
  }
  // alten Recordmodus wiederherstellen
  RecordMode = RecordModeOld;
  // speichern
  SaveTArray(1, MidiTmpFile);
}


DWORD MidiStartPos; // Position der ersten echten Daten zum Test,
                    // ob überhaupt etwas gespielt wurde

void pascal _export StartRecord()
{
  char Header[RECORDDATAOFFSET] =
	 { 'M', 'T', 'h', 'd', 0, 0, 0, 6, 0, 1, 0, 2, 1, 0xE0,
//      'M', 'T', 'r', 'k', 0, 0, 0, 19,
      'M', 'T', 'r', 'k', 0, 0, 0, 4,
//      0, 0xFF, 0x58, 0x04, 0x04, 0x02, 0x18, 0x08,
//      0, 0xFF, 0x51, 0x03, 0x05, 0xB8, 0xD8,
      0, 0xFF, 0x2F, 0x00,
		'M', 'T', 'r', 'k', 0, 0, 0, 0};
  char Title[] =  "MIDI file recorded by Mutabor 2.win";
  char Copyright[] = "(C) (don't know)";
  char Mutabor0[] = "MUTABOR: direct input";
  char Mutabor1[] = "MUTABOR: online mutated";
  Data[0].Flush();
  for (int i = 0; i < RECORDDATAOFFSET; i++)
	 Data[0].Add(Header[i]);
  MidiTextInTArray(0, 3, Title);
  MidiTextInTArray(0, 2, Copyright);
  MidiTextInTArray(0, 1, Mutabor0);
  Data[1].Flush();
  for (i = 0; i < RECORDDATAOFFSET; i++)
	 Data[1].Add(Header[i]);
  MidiTextInTArray(1, 3, Title);
  MidiTextInTArray(1, 2, Copyright);
  MidiTextInTArray(1, 1, Mutabor1);
  // Zeiten auf 0 setzen
  LastTimeStamp[0] = NOTIME; LastTimeStamp[1] = NOTIME;
  RecordMode = REC_NORM;
  MidiStartPos = Data[0].GetItemsInContainer();
}

void pascal _export StopRecord()
{
  RecordMode = REC_NO;
  // Testen, ob überhaupt gespielt wurde
  if ( MidiStartPos == Data[0].GetItemsInContainer() )
  {
	 // nix gespielt, Track leer
    Data[0].Flush();
    Data[1].Flush();
    return;
  }
  // Abschluß-Meta-Befehl
  Data[0].Add(0x00);
  Data[0].Add(0xFF);
  Data[0].Add(0x2F);
  Data[0].Add(0x00);
  Data[1].Add(0x00);
  Data[1].Add(0xFF);
  Data[1].Add(0x2F);
  Data[1].Add(0x00);
  // TrackLaenge
  for (int i = 0; i < 2; i++)
  {
	 DWORD l = Data[i].GetItemsInContainer()-RECORDDATAOFFSET;
	 Data[i][RECORDDATAOFFSET-1] = l & 0xFF;
	 Data[i][RECORDDATAOFFSET-2] = (l >> 8) & 0xFF;
	 Data[i][RECORDDATAOFFSET-3] = (l >> 16) & 0xFF;
	 Data[i][RECORDDATAOFFSET-4] = (l >> 24) & 0xFF;
  }
///  SaveTArray(1, MidiTmpFile);
  strcpy(MidiFileName, "<noname>");
  RecordedSaved = 0;
}

// Join Tracks - Tracks zu einem verschmelzen

#define MAX_TRACKS 30

void pascal _export JoinTracks()
{
  // Tracks aus Data[0] nach Data[1] und zurück nach Data[0]
  DWORD TrackPos[MAX_TRACKS];
  DWORD TrackDelta[MAX_TRACKS];
  DWORD TrackStatus[MAX_TRACKS];
  // Datei-Typ
  int j = (Data[0][8] << 8) + Data[0][9];
  if ( j == 0 ) return;      // sowieso nur ein Track
  int nTrack = (Data[0][10] << 8) + Data[0][11];
  if ( nTrack == 1 ) return; // nur ein Track
  // MUTABOR-Text vorbereiten
  MIDIINFO MidiInfo;
  GetMidiInfo(MidiInfo);
  char sMutabor[100] = "MUTABOR: ";
  strcat(sMutabor, MidiInfo.Mutabor);
  if ( MidiInfo.Mutabor[0] ) strcat(sMutabor, ", ");
  strcat(sMutabor, "Tracks joined");
  // Header kopieren
  Data[1].Flush();
  DWORD i = 0;
  CopyData(i, 4);
  DWORD lTrack = ReadLength(i);
  Data[1].Add(0);            // Header-länge
  Data[1].Add(0);
  Data[1].Add(0);
  Data[1].Add(6);
  Data[1].Add(0);            // Typ 0
  Data[1].Add(0);
  Data[1].Add(0);            // 1 Track
  Data[1].Add(1);
  i += 8;
  CopyData(i, 2);
  i += lTrack - 6 ;
  // Track-Kopf schreiben
  char TrackHeader[8] = {'M', 'T', 'r', 'k', 0, 0, 0, 0};
  for (j = 0; j < 8; j++)
    Data[1].Add(TrackHeader[j]);
  // Mutabor-Text schreiben
  MidiTextInTArray(1, 1, sMutabor);
  // Track-Anfänge ermitteln
  for (j = 0; j < nTrack; j++ )
  {
  	 // Track lesen
	 i += 4;
  	 lTrack = ReadLength(i);
    i += 4;
    TrackPos[j] = i;
    i += lTrack;
  }
  // Erste DeltaTime lesen
  for (j = 0; j < nTrack; j++)
	 TrackDelta[j] = ReadDelta(TrackPos[j]);
  while ( true )
  {
    // "aktuellsten" Track ermitteln
    int jMin = 0; // aktueller Track
    for (j = 0; j < nTrack; j++)
      if ( TrackDelta[j] < TrackDelta[jMin] ) jMin = j;
    DWORD delta = TrackDelta[jMin];
    if (  delta == NOTIME ) break; // fertig
    // Testen, ob nur TrackEnde
    if ( Data[0][TrackPos[jMin]] == 0xFF &&
         Data[0][TrackPos[jMin]+1] == 0x2F )
	 {
      // ein Track zu Ende
      TrackDelta[jMin] = NOTIME;
      continue;
	 }
    // Delta Time schreiben
    RecordTime(1, delta);
    // delta bei den anderen Tracks abziehen
    for (j = 0; j < nTrack; j++)
      if ( TrackDelta[j] != NOTIME )
        TrackDelta[j] -= delta;
    // Midibefehl übertragen
	 int lCode;
    // StatusByte lesen
    BYTE a = Data[0][TrackPos[jMin]++];
	 if ( a & 0x80 )
      TrackStatus[jMin] = a;
    else
      TrackPos[jMin]--;
    DWORD i = TrackPos[jMin];
	 BYTE StatusByte = TrackStatus[jMin];
    Data[1].Add(StatusByte);
    // Anhand des Statusbyte Befehl verarbeiten
    if ( StatusByte <  0xF0 )
		// "normaler" MidiCode
      lCode = lMidiCode[(StatusByte >> 4) & 07] - 1;
    else if ( StatusByte == 0xF0 || StatusByte == 0xF7 )
    {
		// SysEx I, SysEx II
      lCode = ReadDelta(i);            // Länge
		lCode += i - TrackPos[jMin];
    }
    else if ( StatusByte == 0xFF )
    {
      // Meta-Event
      lCode = ReadDelta(++i);              // Länge
		lCode += i - TrackPos[jMin];
    }
    else if ( StatusByte == 0xF2 )
      lCode = 2;  // Song Position Pointer
    else if ( StatusByte == 0xF3 )
      lCode = 1;  // Song Select
    else
      lCode = 0;
	 CopyData(TrackPos[jMin], lCode);
	 // neues Delta lesen;
    TrackDelta[jMin] = ReadDelta(TrackPos[jMin]);
  }
  // Trackende schreiben
  // TrackLaenge
  DWORD l = Data[1].GetItemsInContainer()-JOINDATAOFFSET;
  Data[1][JOINDATAOFFSET-1] = l & 0xFF;
  Data[1][JOINDATAOFFSET-2] = (l >> 8) & 0xFF;
  Data[1][JOINDATAOFFSET-3] = (l >> 16) & 0xFF;
  Data[1][JOINDATAOFFSET-4] = (l >> 24) & 0xFF;
  // in Data[0] übertragen
  Data[0].Flush();
  for (i = 0; i < Data[1].GetItemsInContainer(); i++)
    Data[0].Add(Data[1][i]);
}
*/
