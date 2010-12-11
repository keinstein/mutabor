// -*- C++ -*-

/** \file
 ********************************************************************
 * Devices for routing. Mutabor Core.
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/mu32/routing/Device.cpp,v 1.3 2010/12/11 02:10:08 keinstein Exp $
 * \author Rüdiger Krauße <krausze@mail.berlios.de>,
 * Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 1998
 * $Date: 2010/12/11 02:10:08 $
 * \version $Revision: 1.3 $
 *
 * $Log: Device.cpp,v $
 * Revision 1.3  2010/12/11 02:10:08  keinstein
 * make 2.9.1 build but Mutabor crashes still at runtime in an infinite recursion :-(
 *
 * Revision 1.2  2010-11-21 13:15:45  keinstein
 * merged experimental_tobias
 *
 * Revision 1.1.2.5  2010-09-30 16:26:26  keinstein
 * remove global variables routewindow and frame
 * move route loading and route saving into MutRouteWnd
 * implement MutRouteWnd::InitShapes.
 * Destroy Route children before loading new route configuration (still some crashes)
 *
 *
 ********************************************************************
 *\addtogroup route
 *\{
 ********************************************************************/
// ------------------------------------------------------------------
// Mutabor 3, 1998, R.Krauße
// Devices Basisklassen
// ------------------------------------------------------------------

#include "Device.h"
#include "DevMidi.h"
#include "DevMidF.h"
#include "DevGIS.h"


WATCHEDPTR(OutDevice,routing,OutDevice) OutDevice::deviceList(NULL,_T("OutDevice::deviceList"));


char InDevChanged = 0;

// CurrentTime ------------------------------------------------------

//DWORD CurrentTime;
CurrentTimer CurrentTime;
//UINT CurrentTimeId;

/* Obsoleted by CurrentTime Class
// CallBack Funktion
void CALLBACK _export CurrentTimeFunc(UINT wTimerID, UINT wMsg, DWORD dwUser, DWORD dw1, DWORD dw2)
{
  CurrentTime++;
}
*/
// set timer
void StartCurrentTime()
{
	CurrentTime.Start(0);
	//  CurrentTimeId = timeSetEvent(2, 1, CurrentTimeFunc, 0, TIME_PERIODIC);
}

// reset timer
void StopCurrentTime()
{
	// not needed any more
	//CurrentTime.Stop();
}

// OutDevice
OutDevice * OutDevice::CreateDevice (DevType type)
{
        switch (type) {
        case DTMidiPort:
                return new OutMidiPort();
                break;
        case DTMidiFile:
                return new OutMidiFile();
                break; 
        case DTGis:
                return new OutGis();
                break;
        case DTNotSet:
        case DTUnknown:
        default:
                return NULL;
        }
}

OutDevice * OutDevice::CreateDevice(DevType type, const mutString & name, int id)
{
        switch (type) {
		case DTMidiPort:
			return new OutMidiPort(name, id);
			break;
		case DTMidiFile:
			return new OutMidiFile(name, id);
			break; 
		case DTGis:
			return new OutGis(name, id);
			break;
		case DTNotSet:
		case DTUnknown:
		default:
			return NULL;
        }
}

void OutDevice::InitializeIds()
{
	OutDevice * out = GetDeviceList();
	int i = 0;
	while (out) {
		out->Device::SetId(i++);
		out = out->GetNext();
	}
}

void OutDevice::SaveDevices(tree_storage & config)
{
	config.toLeaf(_T("OutDevices"));
	
	for (OutDevice * out = GetDeviceList(); out; out = out->GetNext()) {
		config.toLeaf(_T("Device"),static_cast<Device *>(out)->GetId());
		config.Write(_T("Type"),out->GetType());
		config.Write(_T("Type Name"),out->GetTypeName());
		out -> Save (config);
		config.toParent();
	}
	
	config.toParent();
}

void OutDevice::LoadDevices(tree_storage & config)
{
	config.toLeaf(_T("OutDevices"));
	
	int i = config.toFirstLeaf(_T("Device"));
	while (i != wxNOT_FOUND) {
		DEBUGLOGTYPE(config,OutDevice,_T("Loading output device with id %d"),i);
		DevType type = (DevType) config.Read(_T("Type"), DTMidiPort);
		OutDevice * out = OutDevice::CreateDevice(type);
		if (!out) continue;
		out -> Device::SetId(i);
		wxString name = config.Read(_T("Type Name"),_T("Midi output device"));
		wxASSERT(name == out->GetTypeName());
		out -> Load(config);
		i = config.toNextLeaf(_T("Device"));
	}
	
	config.toParent(2);
}

OutDevice * OutDevice::GetDevice(int id)
{
	OutDevice * out = GetDeviceList();
	while (out && out->Device::GetId() != id) 
		out = out->Next;
	return out;
}

void OutDevice::AppendToDeviceList (OutDevice * dev) 
{
        if (!deviceList) {
                deviceList = dev; 
                return;
        }
	
        OutDevice * d = GetDeviceList() ;
	OutDevice * d2;
        while ((d2 = d->GetNext())) d = d2;
        d->SetNext(dev);
}

void OutDevice::RemoveFromDeviceList (OutDevice * dev) 
{
        if (!deviceList) return;
        
        if (deviceList == dev) {
                deviceList = dev -> GetNext(); 
                dev -> SetNext(NULL);
                return;
        }
	
        OutDevice * d = deviceList ;
        while (d -> GetNext() != dev && d -> GetNext()) d = d -> GetNext();
        if (d -> GetNext()) {
                d -> SetNext(dev -> GetNext());
                dev -> SetNext(NULL);
        }
}

void OutDevice::TruncateDeviceList (OutDevice * dev) 
{
        if (!deviceList) return;
        
        if (deviceList == dev) {
                deviceList = NULL; 
                return;
        }
	
        OutDevice * d = deviceList ;
        while (d->GetNext() && d->GetNext() != dev) {
                d = d->GetNext();
        }
        if (d->GetNext()) {
                d -> SetNext(NULL);
        }
}

OutDevice * OutDevice::GetInDeviceList(int devid) 
{	
	OutDevice * dev = deviceList;
	while (dev && dev->GetDevId() != devid) dev = dev->GetNext();
	return dev;
}


// InDevice ---------------------------------------------------------

WATCHEDPTR(InDevice,routing,InDevice) InDevice::deviceList(NULL, _T("InDevice::deviceList"),NULL);

InDevice * InDevice::CreateDevice (DevType type)
{
        switch (type) {
        case DTMidiPort:
                return new InMidiPort();
                break;
        case DTMidiFile:
                return new InMidiFile();
                break; 
        case DTGis:
                return new InGis();
                break;
        case DTNotSet:
        case DTUnknown:
        default:
                return NULL;
        }
}
InDevice * InDevice::CreateDevice(DevType type, const mutString & name, int id)
{
	DEBUGLOGTYPE(routing,InDevice,_T("Creating device `%s´ (Type = %d, id = %d)"),name.c_str(), type,id);
        switch (type) {
		case DTMidiPort:
			return new InMidiPort(name, id);
			break;
		case DTMidiFile:
			return new InMidiFile(name, id);
			break; 
		case DTGis:
			return new InGis(name, id);
			break;
		case DTNotSet:
		case DTUnknown:
		default:
			return NULL;
        }
}


Route* InDevice::GetMoveRoutes()
{
	Route *R = GetRoutes();
	SetRoute(NULL);
	return R;
};

Route *InDevice::GetRoute(int nr)   // Nummern beginnen mit 0
{

	for (Route *R = Routes; R; R = R->GetNext())
	{
		if ( !nr ) return R;

		nr--;
	}

	return 0;
}

// Anzahl der Routen
int InDevice::nRoutes()
{
	int n = 0;

	for (Route *R = Routes; R; R = R->GetNext())
		n++;

	return n;
}

// Neue Route am Ende anhängen (damit RTelse O.K. geht)
void InDevice::AddRoute(Route *route)
{

	if (!Routes) {
		Routes = route;
		route->SetInDevice(this);
		return;
	}
	
	Route *R = Routes;
	wxASSERT(R->GetInDevice() == this);
	Route * next;
	while ( (next = R -> GetNext()) )
		R = next;

	R -> SetNext(route);
}

void InDevice::Quite()
{
	for (Route *R = Routes; R; R = R->GetNext())
		if ( R->GetOutDevice() )
			R->GetOutDevice()->Quite(R);
}

Route * InDevice::ReplaceDevice (InDevice * dev) 
{
	// we don't replace the position in the device list since it is
	// already appended and we don't rely on the order in this list.
#ifdef DEBUG
	if (debugFlags::flags[debugFlags::routing]) {
		InDevice * test = GetDeviceList();
		while (test && test != dev) test = test->GetNext();
		wxASSERT(test);
	}
#endif
        SetRoute(dev->GetRoutes());
        dev -> SetRoute(NULL);
        return GetRoutes();
}

void InDevice::InitializeIds()
{
	InDevice * in = GetDeviceList();
	int i = 0;
	while (in) {
		int id = i++;
		in->Device::SetId(id);
		for (Route * route = in->GetRoutes(); route; route = route->GetNext())
			route -> SetInputId(id);
		in = in->GetNext();
	}
}

void InDevice::SaveDevices(tree_storage & config)
{
	config.toLeaf(_T("InDevices"));
	
	for (InDevice * in = GetDeviceList(); in; in = in->GetNext()) {
		config.toLeaf(_T("Device"),in->Device::GetId());
		config.Write(_T("Type"),in->GetType());
		config.Write(_T("Type Name"),in->GetTypeName());
		in -> Save (config);
		config.toParent();
	}
	
	config.toParent();
}

void InDevice::LoadDevices(tree_storage & config)
{
	config.toLeaf(_T("InDevices"));
	
	int i = config.toFirstLeaf(_T("Device"));
	while (i != wxNOT_FOUND) {
		DevType type = (DevType) config.Read(_T("Type"), DTMidiPort);
		InDevice * in = InDevice::CreateDevice(type);
		in -> Device::SetId(i);
		wxString name = config.Read(_T("Type Name"),_T("Midi input device"));
		wxASSERT(name == in -> GetTypeName());
		in -> Load(config);
		i = config.toNextLeaf(_T("Device"));
	}
	
	config.toParent(2);
}

InDevice * InDevice::GetDevice(int id)
{
	InDevice * in = GetDeviceList();
	while (in && in->Device::GetId() != id) 
		in = in->Next;
	return in;
}


void InDevice::AppendToDeviceList (InDevice * dev) 
{
        if (!GetDeviceList()) {
                deviceList = dev; 
                return;
        }

        InDevice * d = deviceList ;
	InDevice * next;
        while ( (next = d->GetNext()) ) d = next;
        d->SetNext(dev);
}

void InDevice::RemoveFromDeviceList (InDevice * dev) 
{
        if (!deviceList) return;
        
        if (deviceList == dev) {
                deviceList = dev -> GetNext(); 
                dev -> SetNext(NULL);
                return;
        }

        InDevice * d = deviceList, *next ;
        while ((next = d->GetNext()) != dev && next) d = next;
        if (next) {
                d->SetNext(dev -> GetNext());
                dev -> SetNext(NULL);
        }
}

void InDevice::TruncateDeviceList (InDevice * dev) 
{
        if (!deviceList) return;
        
        if (deviceList == dev) {
                deviceList = NULL; 
                return;
        }

        InDevice * d = deviceList;
	InDevice * next = d->GetNext();
        while (next && next != dev) {
                d = next;
		next = d -> GetNext();
        }
        if (next) {
                d -> SetNext(NULL);
        }
}


// functions --------------------------------------------------------

void OutNotesCorrect(int box)
{
	for (OutDevice *Out = OutDevice::GetDeviceList(); Out; Out = Out->GetNext())
		Out->NotesCorrect(box);
}

bool OutOpen()
{
	for (OutDevice *Out = OutDevice::GetDeviceList(); Out; Out = Out->GetNext())
		if ( !Out->Open() ) {
			for (OutDevice *Out1 = OutDevice::GetDeviceList(); Out1 && Out1 != Out; Out1 = Out1->GetNext())
				Out1->Close();

			return false;
		}

	return true;
}

void OutClose()
{
	for (OutDevice *Out = OutDevice::GetDeviceList(); Out; Out = Out->GetNext())
		Out->Close();
}

void OutAddTime(frac time)
{
	for (OutDevice *Out = OutDevice::GetDeviceList(); Out; Out = Out->GetNext())
		Out->AddTime(time);
}

bool InOpen()
{
	DEBUGLOGBASE(other,"",_T(""));

	for (InDevice *In = InDevice::GetDeviceList(); In; In = In->GetNext())
		if ( !In->Open() ) {
			for (InDevice *In1 = InDevice::GetDeviceList(); In1 && In1 != In; 
                             In1 = In1->GetNext())
				In1->Close();

			DEBUGLOGBASE(other,"",_T("Opening failed"));

			return false;
		}

	return true;
}

void InClose()
{
	for (InDevice *In = InDevice::GetDeviceList(); In; In = In->GetNext())
		In->Close();
}

bool NeedsRealTime()
{
	for (OutDevice *Out = OutDevice::GetDeviceList(); Out; Out = Out->GetNext())
		if ( Out->NeedsRealTime() )
			return true;

	for (InDevice *In = InDevice::GetDeviceList(); In; In = In->GetNext())
		if ( In->NeedsRealTime() )
			return true;

	return false;
}


/*
frac InReadOn(frac time)
{
  frac z = frac(-1, 1);
  for (InDevice *In = InDevices; In; In = In->Next)
  {
	  frac z1 = In->ReadOn(time);
	  if ( z == frac(-1, 1) || z1 < z )
		  z = z1;
  }
  return z;
}
*/

void MidiOut(int box, DWORD data, char n)
{
	for (InDevice *In = InDevice::GetDeviceList(); In; In = In->GetNext()) {
		for (Route *R = In->GetRoutes(); R; R = R->GetNext()) {
			OutDevice * out;
			if ( R->Box == box && (out = R->GetOutDevice())) {
				out -> MidiOut(data, n);
			}
		}
	}
}

void NotesCorrect(int box)
{
	for (OutDevice *Out = OutDevice::GetDeviceList(); Out; Out = Out->GetNext())
		Out->NotesCorrect(box);
}

int GetChannel(int box, int taste)
{
	for (InDevice *In = InDevice::GetDeviceList(); In; In = In->GetNext()) {
		for (Route *R = In->GetRoutes(); R; R = R->GetNext()) {
			OutDevice * out;
			if ( R->Box == box && (out = R->GetOutDevice())) {
				int c = out->GetChannel(taste);

				if ( c != -1 )
					return c;
			}
		}
	}
	return -1;
}

/// \}

