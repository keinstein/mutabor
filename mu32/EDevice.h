/** \file
 ********************************************************************
 * Devices Basisklassen.
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/mu32/EDevice.h,v 1.3 2005/11/07 19:42:54 keinstein Exp $
 * \author Rüdiger Krauße <krausze@mail.berlios.de>
 * \date $Date: 2005/11/07 19:42:54 $
 * \version $Revision: 1.3 $
 *
 * $Log: EDevice.h,v $
 * Revision 1.3  2005/11/07 19:42:54  keinstein
 * Some additional changes
 *
 ********************************************************************/

#ifndef EDEVICE_H
#define EDEVICE_H

#include <cstring>
#include "Global.h"

#ifdef WX
#include <wx/string.h>
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
#if defined(WX)
	extern wxString RouteConfig;
#else
	extern char *RouteConfig;
#endif

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

// Oberflächen Devices ---------------------------------------------------

class EDevice
{
  public:
	EDevice *Next;
#if defined(WX)
	wxString Name;
#else
	char Name[200];
#endif
	DevType DT;
	ERoute *Routes;
	int DevId;
	int BendingRange;
	int Nr;
	int Mode;
#if defined(WX)
	EDevice(DevType dt, const wxString& name = wxEmptyString, int devId = 0)
#else
	EDevice(DevType dt, char *name = "", int devId = 0)
#endif
	{
		DT = dt;
#if defined(WX)
		Name = name;
#else
		strcpy(Name, name);
#endif
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
#if defined(WX)
	wxString GetName(); // mit ' ' -> '_'
#else
	char *GetName(); // mit ' ' -> '_'
#endif
};

// Funktionen -------------------------------------------------------

#if defined(WX)
EDevice* NewDevice(EDevice **List, DevType dt, const wxString& name, int devId, EDevice *oldPos = 0, EDevice *newPos = 0);
void ScanRoutes(const wxString& config);
void WriteRoutes(wxString &config);
#else
EDevice* NewDevice(EDevice **List, DevType dt, char *name, int devId, EDevice *oldPos = 0, EDevice *newPos = 0);
void ScanRoutes(char *config);
void WriteRoutes(char **config);
#endif


extern bool BoxUsed[MAX_BOX];
void CheckBoxesUsed();
#endif
