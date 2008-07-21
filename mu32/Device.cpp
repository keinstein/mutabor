// ------------------------------------------------------------------
// Mutabor 3, 1998, R.Krauße
// Devices Basisklassen
// ------------------------------------------------------------------

#include "Device.h"

OutDevice* OutDevices = 0;
InDevice* InDevices = 0;

char InDevChanged = 0;

// Route ------------------------------------------------------------

int RouteIds = 1;

char NextRouteId()
{
  return RouteIds++;;
}

// InDevice ---------------------------------------------------------

Route* InDevice::GetMoveRoutes()
{
  Route *R = Routes;
  Routes = 0;
  return R;
};

Route *InDevice::GetRoute(int nr)   // Nummern beginnen mit 0
{
  for (Route *R = Routes; R; R = R->Next)
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
  for (Route *R = Routes; R; R = R->Next)
    n++;
  return n;
}

// Neue Route am Ende anhängen (damit RTelse O.K. geht)
void InDevice::AddRoute(Route *route)
{
  Route **R = &Routes;
  while ( *R )
  	R = &(*R)->Next;
  *R = route;
}

void InDevice::Quite()
{
  for (Route *R = Routes; R; R = R->Next)
  	if ( R->Out )
      R->Out->Quite(R);
}

// functions --------------------------------------------------------

void OutNotesCorrect(int box)
{
  for (OutDevice *Out = OutDevices; Out; Out = Out->Next)
 	  Out->NotesCorrect(box);
}

bool OutOpen()
{
  for (OutDevice *Out = OutDevices; Out; Out = Out->Next)
	  if ( !Out->Open() )
    {
  	  for (OutDevice *Out1 = OutDevices; Out1 && Out1 != Out; Out1 = Out1->Next)
	      Out1->Close();
      return false;
    }
  return true;
}

void OutClose()
{
  for (OutDevice *Out = OutDevices; Out; Out = Out->Next)
	  Out->Close();
}

void OutAddTime(frac time)
{
  for (OutDevice *Out = OutDevices; Out; Out = Out->Next)
	  Out->AddTime(time);
}

bool InOpen()
{
  DEBUGLOGBASE("",_T(""));
  for (InDevice *In = InDevices; In; In = In->Next)
    if ( !In->Open() ) {
      for (InDevice *In1 = InDevices; In1 && In1 != In; In1 = In1->Next)
	In1->Close();
      DEBUGLOGBASE("",_T("Opening failed"));
      return false;
    }
  return true;
}

void InClose()
{
  for (InDevice *In = InDevices; In; In = In->Next)
	  In->Close();
}

bool NeedsRealTime()
{
  for (OutDevice *Out = OutDevices; Out; Out = Out->Next)
	  if ( Out->NeedsRealTime() )
      return true;
  for (InDevice *In = InDevices; In; In = In->Next)
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
  for (InDevice *In = InDevices; In; In = In->Next)
  {
 	  for (Route *R = In->GetRoutes(); R; R = R->Next)
      if ( R->Box == box && R->Out)
      {
        R->Out->MidiOut(data, n);
      }
  }
}

void NotesCorrect(int box)
{
  for (OutDevice *Out = OutDevices; Out; Out = Out->Next)
	  Out->NotesCorrect(box);
}

int GetChannel(int box, int taste)
{
  for (InDevice *In = InDevices; In; In = In->Next)
  {
 	  for (Route *R = In->GetRoutes(); R; R = R->Next)
      if ( R->Box == box && R->Out)
      {
        int c = R->Out->GetChannel(taste);
        if ( c != -1 )
          return c;
      }
  }
  return -1;
}


