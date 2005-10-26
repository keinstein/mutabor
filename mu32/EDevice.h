// ------------------------------------------------------------------
// Mutabor 3, 1998, R.Krauﬂe
// Devices Basisklassen
// ------------------------------------------------------------------

#ifndef EDEVICE_H
#define EDEVICE_H

#include <string.h>
#include "Global.h"

#ifdef WX
#include "Device.h"
#endif

#ifndef WX
// Device Typen
enum DevType { DTNotSet = -1, DTUnknown, DTMidiPort, DTMidiFile, DTGis };
#endif

class EDevice;

extern EDevice *InEDevices;
extern EDevice *OutEDevices;

// Routen als Stream
extern char *RouteConfig;

#define INIT_BENDINGRANGE 2

// Route ------------------------------------------------------------

#define NoBox  -2
#define GmnBox -1

#ifndef WX
enum RouteType { RTall, RTelse, RTchannel, RTstaff };
#endif

class ERoute
{
  public:
	  ERoute *Next;
	  char Id;
	  RouteType Type;
	  int IFrom, ITo;
	  int Box;
    bool Active;
	  EDevice *Out;
    int OFrom, OTo;
    bool ONoDrum;
	  ERoute(RouteType type, int iFrom, int iTo, int box, bool active, EDevice *out,
    int oFrom = -1, int oTo = -1, bool oNoDrum = true)
	  {
	    Type = type;
	    IFrom = iFrom;
	    ITo = iTo;
	    Box = box;
      Active = active;
		  Out = out;
		  OFrom = oFrom;
		  OTo = oTo;
      ONoDrum = oNoDrum;
      Next = 0;
	  }
	  ~ERoute()
	  {
		  if ( Next ) delete Next;
	  }
};

// Oberfl‰chen Devices ---------------------------------------------------

class EDevice
{
  public:
    EDevice *Next;
    char Name[200];
    DevType DT;
  	ERoute *Routes;
    int DevId;
    int BendingRange;
    int Nr;
    int Mode;
    EDevice(DevType dt, char *name = "", int devId = 0)
	  {
      DT = dt;
      strcpy(Name, name);
      Next = 0;
      Routes = 0;
      DevId = devId;
      BendingRange = INIT_BENDINGRANGE;
      Mode = -1;
      Nr = -1;
	  }
    ~EDevice()
    {
      if ( Routes )
        delete Routes;
      if ( Next )
        delete Next;
    }
    ERoute *GetRoute(int nr);
    int nRoutes();
	  void AddRoute(ERoute *route);
    char *GetName(); // mit ' ' -> '_'
};

// Funktionen -------------------------------------------------------

EDevice* NewDevice(EDevice **List, DevType dt, char *name, int devId, EDevice *oldPos = 0, EDevice *newPos = 0);

void ScanRoutes(char *config);
void WriteRoutes(char **config);

extern bool BoxUsed[MAX_BOX];
void CheckBoxesUsed();
#endif
