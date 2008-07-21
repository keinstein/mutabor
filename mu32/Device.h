// ------------------------------------------------------------------
// Mutabor 3, 1998, R.Krauﬂe
// Devices Basisklassen
// ------------------------------------------------------------------

#ifndef DEVICE_H
#define DEVICE_H

#define DRUMCHANNEL 9  // Schlagzeugkanal bei General Midi (Kanal 9, bzw. 10)

enum MutaborModeType {
  MutaborDeviceUnregistered = -1,
  MutaborDeviceStop,
  MutaborDevicePlay,
  MutaborDevicePause,
  MutaborDeviceCompileError,
  MutaborDeviceTimingError
};

#include "GIS.h"



class OutDevice;
class InDevice;

extern OutDevice *OutDevices;
extern InDevice *InDevices;

extern char InDevChanged;

// Device Typen
enum DevType { DTNotSet = -1, DTUnknown, DTMidiPort, DTMidiFile, DTGis };
#define DeviceMaxType DTGis

// channel data -----------------------------------------------------

class ChannelData
{
  public:
    int Sound;          // -1 = noch nicht verwendet
    char Sustain;
    int BankSelectMSB;  // -1 .. noch nicht benutzt
    int BankSelectLSB;  // -1 .. noch nicht benutzt
    long Pitch;         // 0 = ungepitcht, kann durchaus auch negativ sein
    ChannelData(int sound = -1, char sustain = 0)
    {
      Sound = sound;
      Sustain = sustain;
      BankSelectMSB = -1;
      BankSelectLSB = -1;
      Pitch = 0;
    }
    void Reset()
    {
      Sound = -1;
      Sustain = 0;
      BankSelectMSB = -1;
      BankSelectLSB = -1;
    }

    bool operator ==(ChannelData &cd)
    {
      return ( Sound == -1 || cd.Sound == -1 || Sound == cd.Sound ) &&
             ( Sustain == -1 || cd.Sustain == -1 || Sustain == cd.Sustain ) &&
             ( BankSelectMSB == -1 || cd.BankSelectMSB == -1 || BankSelectMSB == cd.BankSelectMSB ) &&
             ( BankSelectLSB == -1 || cd.BankSelectLSB == -1 || BankSelectLSB == cd.BankSelectLSB );
    }
};

// Route ------------------------------------------------------------

#define NoBox  -2
#define GmnBox -1

enum RouteType { RTall, RTelse, RTchannel, RTstaff };

char NextRouteId();

class Route
{
  public:
  Route *Next;
  char Id;
  RouteType Type;
  int IFrom, ITo;
  int Box;
  bool Active;
  OutDevice *Out;
  int OFrom, OTo;
  bool ONoDrum;
  Route(RouteType type, 
	int iFrom, 
	int iTo, 
	int box, 
	bool active, 
	OutDevice *out,
	int oFrom = -1, 
	int oTo = -1, 
	bool oNoDrum = true, 
	Route *next = 0){
    Type = type;
    IFrom = iFrom;
    ITo = iTo;
    Box = box;
    Active = active;
    Out = out;
    OFrom = oFrom;
    OTo = oTo;
    ONoDrum = oNoDrum;
    Next = next;
    Id = NextRouteId();
  }
  ~Route() {
    if ( Next ) delete Next;
  }
  char Check(int i) {
    return (IFrom <= i && i <= ITo);
  }
};

// Output devices ---------------------------------------------------

class OutDevice
{
  public:
    OutDevice *Next;
    OutDevice()
    {
      Next = 0;
    };
    virtual ~OutDevice()
    {
      if ( Next ) delete Next;
    }

    virtual bool Open() = 0;
    virtual void Close() = 0;
    virtual void NoteOn(int box, int taste, int velo, Route *r, int channel, ChannelData *cd) = 0;
    virtual void NoteOff(int box, int taste, int velo, Route *r, int channel) = 0;
    virtual void NotesCorrect(int box) = 0;
    virtual void Sustain(char on, int channel) = 0;
    virtual int  GetChannel(int taste) = 0;
    virtual void Gis(GisToken *token, char turn) = 0;
    virtual void AddTime(frac time) = 0;
    virtual void MidiOut(DWORD data, char n) = 0;
    virtual void MidiOut(BYTE *p, char n) = 0;
    virtual void Quite(Route *r) = 0;
    virtual void Panic() {};
    virtual bool NeedsRealTime() { return false; }
    virtual wxString &GetName() = 0;
    virtual DevType GetType() const { return DTUnknown; }
};

// Input devices ----------------------------------------------------

class InDevice
{
 public:
  InDevice *Next;
  enum MutaborModeType Mode;
 protected:
  Route *Routes;
 public:
  InDevice() {
    Mode = MutaborDeviceStop;
    Next = 0;
    Routes = 0;
  }
  virtual ~InDevice() {
    if ( Routes ) delete Routes;
    if ( Next ) delete Next;
  }
  Route *GetRoutes() { return Routes; }
  Route *GetMoveRoutes();
  Route *GetRoute(int nr);   // counting starts with 0
  int nRoutes();
  virtual bool Open() = 0;
  virtual void Close() = 0;
  virtual void Stop() = 0;
  virtual void Play() = 0;
  virtual void Pause() = 0;
  //	  virtual frac ReadOn(frac time) = 0;
  void AddRoute(Route *route);
  void Quite(); // all Routes quite
  virtual bool NeedsRealTime() { return false; }
  virtual wxString &  GetName() = 0;
  virtual DevType GetType() const { return DTUnknown; }
};

// functions --------------------------------------------------------

void OutNotesCorrect(int box);
bool OutOpen();
void OutClose();
void OutAddTime(frac time);

bool InOpen();
void InClose();

bool NeedsRealTime();
//frac InReadOn(frac time);

void MidiOut(int box, DWORD data, char n = -1);
void NotesCorrect(int box);

int GetChannel(int box, int taste);

#endif

