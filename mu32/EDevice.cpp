// ------------------------------------------------------------------
// Mutabor 3, 1998, R.Krauï¬‚e
// Oberflâ€°chen Devices
// ------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>

#include "EDevice.h"
#include "DevMidi.h"


const wxChar* DevTypeName[] = { 
  N_("Unknown"),
  N_("Midi Port"), 
  N_("Midi File"), 
  N_("GUIDO .gmn File")
};


EDevice *InEDevices = 0;
EDevice *OutEDevices = 0;

// EDevice ----------------------------------------------------------

ERoute *EDevice::GetRoute(int nr)   // Nummern beginnen mit 0
{
  for (ERoute *R = Routes; R; R = R->Next)
  {
    if ( !nr ) return R;
    nr--;
  }
  return 0;
}

// Anzahl der Routen
int EDevice::nRoutes()
{
  int n = 0;
  for (ERoute *R = Routes; R; R = R->Next)
    n++;
  return n;
}

// Neue Route am Ende anhâ€°ngen (damit RTelse O.K. geht)
void EDevice::AddRoute(ERoute *route)
{
  ERoute **R = &Routes;
  while ( *R )
  	R = &(*R)->Next;
    *R = route;
}

wxString EDevice::GetName()
{
	wxString s = Name;
	s.Replace(_T(" "), _T("_"));
	return s;
}

// Hilfe fÂ¸r Verkettung: Wenn Outgerâ€°t gekillt wird,
// sollten die Verweise in den Routen verbogen werden

void ChangeOutReferences(EDevice *from, EDevice *to)
{
  for (EDevice *In = InEDevices; In; In = In->Next)
    for (ERoute *R = In->Routes; R; R = R->Next)
      if ( R->Out == from )
        R->Out = to;
}

// Verkettung in den Listen -----------------------------------------

// fügt neues Device in Liste,
// wenn Device schon existiert, dann wird nicht neu eingefügt
// oldPos wird entfernt
// einfügen auf newPos
// bei dt == -1 und keinem newPlace wird nur gelöscht
EDevice* NewDevice(EDevice **List, 
		   DevType dt, 
		   const wxString& name, 
		   int devId, 
		   EDevice *oldPos, 
		   EDevice *newPos)
{
#ifdef DEBUG
  std::cerr << "test" << std::endl <<
    (wxString(_T("::NewDevice(")).ToUTF8()) << List << ", " 
	    << dt << ", " 
	    << (name.ToUTF8()) << ", " 
	    << oldPos << ", " 
	    << newPos << ")" << std::endl;
#endif

  // Position finden zum Daten abladen
  EDevice *Pos = 0;
  ERoute *R = 0;
  if ( oldPos == newPos && oldPos )
  {
    Pos = oldPos;
    Pos->DT = dt;
#ifdef WX
	Pos->Name = name;
#else
    strcpy(Pos->Name, name);
#endif
    Pos->DevId = devId;
    Pos->Mode = MutaborDeviceUnregistered;
  } else {
    if ( oldPos ) {
      // Position von oldPos als Adresse finden
      EDevice **PreOldPos = List;
      for (;*PreOldPos; PreOldPos = &((*PreOldPos)->Next))
        if ( *PreOldPos == oldPos )
          break;
      // oldPos löschen, Routen retten
      R = oldPos->Routes;
      oldPos->Routes = 0;
      *PreOldPos = (*PreOldPos)->Next;
      oldPos->Next = 0;
      delete oldPos;
    }
    // evtl. nur löschen
    if ( dt == -1 )
    {
      if ( R )
        delete R;
      return 0;
    }
    // Position von newPos als Adresse finden
    EDevice **PreNewPos = List;
    for (;*PreNewPos; PreNewPos = &((*PreNewPos)->Next))
      if ( *PreNewPos == newPos )
        break;

    // Device einfügen
    Pos = new EDevice(dt, name, devId);
    Pos->Routes = R;
    Pos->Next = *PreNewPos;
    *PreNewPos = Pos;
  }
  // Testen, ob Device schon so existiert
  for (EDevice **Dev = List ; *Dev; Dev = &((*Dev)->Next))
    if ( *Dev != Pos &&
         (*Dev)->DT == dt &&
#ifdef WX
         ( ( !(*Dev)->Name.Cmp(name) ) ||
#else
         ( ( !strcmp((*Dev)->Name, name) ) ||
#endif
		 ( dt == DTMidiPort && (*Dev)->DevId == devId ) ) )
    {
      // doppeltes Device gefunden, Routen Â¸bertragen und lË†schen
      EDevice *Dev1 = *Dev;
      if ( Dev1->Routes )
      {
        Pos->AddRoute(Dev1->Routes);
        Dev1->Routes = 0;
      }
      *Dev = Dev1->Next;
      Dev1->Next = 0;
      ChangeOutReferences(Dev1, Pos);
      delete Dev1;
      break;
    }
  return Pos;
}

// Scannen und schreiben der Routen als Streams ---------------------

// Hilfsfunktionen --------------------------------------------------

#ifndef WX
DevType Str2DT(char *type)
{
  char *DTName[] =  { "", "MIDIPORT", "MIDIFILE", "GMN" };
  int i;
  for (i = 3; i > 0; i--)
    if ( !strncmp(type, DTName[i], strlen(DTName[i])) )
      break;
  return (DevType)i;
}
#else
DevType Str2DT(const wxString& type)
{
	wxString DTName[] =  { _T(""), _T("MIDIPORT"), _T("MIDIFILE"), _T("GMN") };
	int i;
#ifdef DEBUG
	std::cerr << "Comparing " << ( type.ToUTF8() ) << std::endl;
#endif
	for (i = 3; i > 0; i--) {
#ifdef DEBUG
		std::cerr << "Testing " << ( DTName[i].ToUTF8() ) << std::endl;
#endif
		if ( type.StartsWith(DTName[i]) )
			break;
	}
	return (DevType)i;
}
#endif

 
const mutChar * RTName[] =  { _T("ALL"), _T("ELSE"), _T("CHANNEL"), _T("STAFF") };

/// parse a string representation of a route type
/** This function returns the numeric route type to a string representation
    \param type String (array of \c mutChar)
    \return numeric id of the route type
*/
RouteType Str2RT(mutChar *type)
{
  int i;
  for (i = 3; i > 0; i--)
#ifndef WX
    if ( !strncmp(type, RTName[i], strlen(RTName[i])) )
#else 
    if ( !wxStricmp(type, RTName[i])) //, strlen(RTName[i])) )
#endif
      break;
  return (RouteType) i;
}

EDevice *GetEOut(int nr)
{
  if ( nr < 0 )
    return 0;
  EDevice *Out = OutEDevices;
  while ( Out && nr )
  {
    Out = Out->Next;
    nr--;
  }
  return Out;
}

#if defined(WX)

// aus p eine Zeile in s lesen, i wird verschoben
bool GetELine(const wxString& p, size_t& i, wxString &s)
{
	size_t l = p.Length();
start:
	if ( i >= l )
		return false;
	while ( i < l && wxString(_T(" \t\n\r")).Find(p.GetChar(i)) != -1 )
		i++;
	if ( i >= l )
		return false;
	size_t i1 = i;
	int i2 = p.find(_T("\n"), i1);
	if ( i2 == -1 )
	{
		i = l;
		s = p.Mid(i1);
	}
	else
	{
		s = p.Mid(i1, i2-i1);
		i = (size_t) i2;
    }
	s = s.Trim();
	if ( s.Length() == 0 || s.StartsWith(_T("#")) )
		goto start;
	return true;
}

#define GETLINE \
  if ( !GetELine(config, i, s) ) \
    return

// Routen scannen
void ScanRoutes(const wxString& config)
{
	// Listen sâ€°ubern
	if ( InEDevices )
	{
		delete InEDevices;
		InEDevices = 0;
	}
	if ( OutEDevices )
	{
		delete OutEDevices;
		OutEDevices = 0;
	}
	// Zerlegen von config
	wxString s;
	size_t i = 0;
	GETLINE;
#ifdef DEBUG
	std::cerr << "+" << s.ToUTF8() << std::endl;
#endif

	while ( !s.StartsWith(_T("OUTPUT")) )
	{
		GETLINE;
#ifdef DEBUG
	std::cerr << "+" << s.ToUTF8() << std::endl;
#endif
	}
	GETLINE;
#ifdef DEBUG
	std::cerr << "+" << s.ToUTF8() << std::endl;
#endif
	// Output lesen
	while ( !s.StartsWith(_T("INPUT")) )
	{
		wxChar Type[80], Name[400];
		//wxString Type, Name;
		int DevId, BendingRange;
		
#ifdef DEBUG
		std::cout << (sizeof(char)) << " "
			  << sizeof(wxChar) << std::endl;
		std::cout << "a" << (s.fn_str()) << std::endl;
		std::cout << "=" << (s.ToUTF8()) << std::endl;
#endif
#if (wxUSE_UNICODE)
		int test = SSCANF(s.c_str(), _T("%ls \"%l[^\"]\" %d %d"),
				  Type, Name, &DevId, &BendingRange);
		if ( test < 2 )
			test = SSCANF(s.c_str(), _T("%ls %ls %d %d"), 
				      Type, Name, &DevId, &BendingRange);
		if ( test < 2 )
		{
		  //3 ??
		}
#else
		int test = SSCANF(s.c_str(), _T("%s \"%[^\"]\" %d %d"), 
				  Type, Name, &DevId, &BendingRange);
		if ( test < 2 )
			test = SSCANF(s.c_str(), _T("%s %s %d %d"), 
				      Type, Name, &DevId, &BendingRange);
		if ( test < 2 )
		{
		  //3 ??
		}
#endif
		std::cout << (wxString(Name).ToUTF8()) << std::endl;
		EDevice *Out = NewDevice(&OutEDevices, Str2DT(muT(Type)), Name, DevId);
		if ( test == 4 )
			Out->BendingRange = BendingRange;
		GETLINE;
#ifdef DEBUG
	std::cerr << "+" << s.ToUTF8() << std::endl;
#endif
	}
	GETLINE;
#ifdef DEBUG
	std::cerr << "+" << s.ToUTF8() << std::endl;
#endif
	// Input lesen
	while ( 1 ) {
		// Device lesen
		wxChar Type[40], Name[400];
		//wxString Type, Name;
		int DevId = -1;
#if (wxUSE_UNICODE)
		int test = SSCANF(s, _T("%ls \"%l[^\"]\" %d"), 
				  Type, Name, &DevId);
		if ( test < 2 )
			test = SSCANF(s, _T("%ls %ls %d"), 
				      Type, Name, &DevId);
		if ( test < 2 )
		{
		  //3 ??
		}
#else
		int test = SSCANF(s, _T("%s \"%[^\"]\" %d"), 
				  Type, Name, &DevId);
		if ( test < 2 )
			test = SSCANF(s, _T("%s %s %d"), 
				      Type, Name, &DevId);
		if ( test < 2 )
		{
		  //3 ??
		}
#endif
		EDevice *In = NewDevice(&InEDevices, Str2DT(muT(Type)), Name, DevId);
		GETLINE;
#ifdef DEBUG
	std::cerr << "+" << s.ToUTF8() << std::endl;

#endif
		// Routen lesen
		while ( Str2DT(s) == DTUnknown )
		{
			// Route lesen
			wxChar Type[40];
			int IFrom = 0, ITo = 0, Box = 0, BoxActive = 0, 
			  OutDev = -1, OFrom = -1, OTo = -1, ONoDrum = 1;
#if (wxUSE_UNICODE)
			test = SSCANF(s.c_str(),
				      _T("%ls %d %d %d %d %d %d %d %d"),
				      Type, &IFrom, &ITo, &Box, &BoxActive, 
				      &OutDev, &OFrom, &OTo, &ONoDrum);
			if ( test < 2 )
			{
				//3 ??
			}
#else
			test = SSCANF(s.c_str(), 
				      _T("%s %d %d %d %d %d %d %d %d"),
				      Type, &IFrom, &ITo, &Box, 
				      &BoxActive, &OutDev, &OFrom, &OTo,
				      &ONoDrum);
			if ( test < 2 )
			{
				//3 ??
			}
#endif
			In->AddRoute(new ERoute(Str2RT(Type), 
						IFrom, ITo, Box, 
						BoxActive, GetEOut(OutDev), 
						OFrom, OTo, ONoDrum));
			GETLINE;
#ifdef DEBUG
	std::cerr << "+" << s.ToUTF8() << std::endl;
#endif
		}
	}
}


/* old default routing file:
OUTPUT
  MIDIPORT MIDIPORT_OUT 0 2
INPUT
  MIDIPORT MIDIPORT_IN 0
    ALL 0 0 0 1 0 0 15
 */
// Routen scannen
void ScanRoutes(wxConfigBase * config)
{
  if (! config->HasGroup(_T("Input"))) return;

  // Listen sâ€°ubern
  if ( InEDevices ) {
    delete InEDevices;
    InEDevices = 0;
  }

  if ( OutEDevices ) {
    delete OutEDevices;
    OutEDevices = 0;
  }
  // Zerlegen von config

  wxString group;
  wxString defaultPortName = rtmidiout->getPortCount()? 
    muT(rtmidiout->getPortName(0).c_str()):wxString(_("Unknown"));
  long group_number;

  // read output devices
  config->SetPath(_T("Output"));
  config->GetFirstGroup(group,group_number);
  for (bool test = true; // we have a default output device
       test; test = config->GetNextGroup(group,group_number)){
    config->SetPath(group);
    wxString name; 
    long type, id; 
    config->Read(_T("Name"), &name, defaultPortName);

    config->Read(_T("Type"), &type, 1);

    if (type <= 0 || type >= DeviceMaxType) {
      // Bad device type; try to recover
      wxString type_name;
      config->Read(_T("Type_Name"), &type_name, _("Midi Port"));
      
      int i;
      for (i = 1; i < DeviceMaxType; i++) 
	if (wxGetTranslation(DevTypeName[i]) == type_name) break;
      if (i == DeviceMaxType) type = 0;
      else type = i;
    }
    
    config->Read(_("Device_Id"), &id, 0);

    EDevice *out = NewDevice(&OutEDevices, (DevType) type, name, id);

    out->BendingRange = config->Read(_("Bending_Range"), 
				     (long)out->BendingRange);
    
    config->SetPath(_T(".."));
  }
  config->SetPath(_T(".."));

  // read input devices
  config->SetPath(_T("Input"));
  config->GetFirstGroup(group,group_number);
  for (bool test = true; // we have a default output device
       test; test = config->GetNextGroup(group,group_number)){
    config->SetPath(group);

    wxString name; 
    long type, id; 
    config->Read(_T("Name"), &name, defaultPortName);

    config->Read(_T("Type"), &type, 1);

    if (type <= 0 || type >= DeviceMaxType) {
      // Bad device type; try to recover
      wxString type_name;
      config->Read(_T("Type_Name"), &type_name, _("Midi Port"));

      int i;
      for (i = 1; i < DeviceMaxType; i++) 
	if (wxGetTranslation(DevTypeName[i]) == type_name) break;
      if (i == DeviceMaxType) i = 0;
    }
    
    config->Read(_("Device_Id"), &id, 0);

    EDevice *in = NewDevice(&InEDevices, (DevType) type, name, id);

    config->SetPath(_T("Routes"));
    wxString route_group;
    long route_iterator;
    config->GetFirstGroup(route_group,route_iterator);
    for (bool test2 = true; // we need a default route
	 test2; test2 = config->GetNextGroup(route_group,route_iterator)){
      config->SetPath(route_group);

      long type; 
      
      config->Read(_T("Type"), &type, 0);

      if (type < 0 || type > 3) {

	// Route type; try to recover
	wxString type_name;
	config->Read(_T("Type_Name"), &type_name, _("Midi Port"));
	int i; 
	for (i = 1; i < 4; i++) 
	  if (muT(RTName[i]) == type_name) break;
	if (i == 4) type = 0;
	else type = i;
      }
	
      long IFrom, ITo, Box, Active, OutDev, OFrom, OTo, ONoDrum;
      config->Read(_T("Input_from"), &IFrom, 0);
      config->Read(_T("Input_to"), &ITo, 0);
      config->Read(_T("Box"), &Box, 0);
      config->Read(_T("Active"), &Active, 1);
      config->Read(_T("Output_device"), &OutDev, 0);
      config->Read(_T("Output_from"), &OFrom, 0);
      config->Read(_T("Output_to"), &OTo, 15);
      config->Read(_T("No_Drum"), &ONoDrum, 1);
      
      in->AddRoute(new ERoute((RouteType) type, IFrom, ITo, Box, Active,
			      GetEOut(OutDev), OFrom, OTo, ONoDrum));
      
      config->SetPath(_T(".."));
    }

    config->SetPath(_T("../.."));
  }
  config->SetPath(_T(".."));
}
#else // no WX

// aus p eine Zeile in s lesen, p wird verschoben
char GetELine(char **p, char *s)
{
start:
  if ( !p || !(*p)[0] )
    return 0;
  while ( (*p)[0] == ' ' || (*p)[0] == '\n' || (*p)[0] == '\r' )
    *p = &(*p)[1];
  if ( !(*p)[0] )
    return 0;
  char *p1 = *p;
  *p = strchr(p1, '\n');
  if ( !p )
    *p = &p1[strlen(p1)];
  while ( *p1 && strchr("\n\r\t ", *p1) )
    p1 = &p1[1];
  int i = (*p)-p1;
  strncpy(s, p1, i);
  s[i] = 0;
  while ( i > 0 && strchr("\n\r\t ", s[i-1]) )
    s[--i] = 0;
  if ( !s[0] || s[0] == '#' )
    goto start;
  return 1;
}

#define GETLINE \
  if ( !GetELine(&p1, s) ) \
    return

// Routen scannen
void ScanRoutes(char *config)
{
  // Listen sâ€°ubern
  if ( InEDevices )
  {
    delete InEDevices;
    InEDevices = 0;
  }
  if ( OutEDevices )
  {
    delete OutEDevices;
    OutEDevices = 0;
  }
  // Zerlegen von config
  char s[200], *p1 = config;
  GETLINE;
  while ( strncmp(s, "OUTPUT", 6) )
  {
    GETLINE;
  }
  GETLINE;
  // Output lesen
  while ( strncmp(s, "INPUT", 5) )
  {
    char Type[20], Name[200];
    int DevId, BendingRange;
    //    int test = sscanf (s, "%s %s %d %d", Type, Name,
    //		       &DevId, &BendingRange);
    int test = sscanf (s, "%s \"%[^\"]^^\" %d %d", Type, Name,
		       &DevId, &BendingRange);
    if ( test < 2 )
      test = sscanf (s, "%s %s %d %d", Type, Name, &DevId, &BendingRange);
    if ( test < 2 )
      {
	//3 ??
      }
    EDevice *Out = NewDevice(&OutEDevices, Str2DT(Type), Name, DevId);
    if ( test == 4 )
      Out->BendingRange = BendingRange;
    GETLINE;
  }
  GETLINE;
  // Input lesen
  while ( 1 )
  {
    // Device lesen
    char Type[20], Name[200];
    int DevId = -1;
		int test = sscanf (s, "%s \"%[^\"]\" %d", Type, Name, &DevId);
    if ( test < 2 )
      test = sscanf (s, "%s %s %d", Type, Name, &DevId);
		if ( test < 2 )
		{
		  //3 ??
		}
    EDevice *In = NewDevice(&InEDevices, Str2DT(Type), Name, DevId);
    GETLINE;
    // Routen lesen
    while ( Str2DT(s) == DTUnknown )
    {
      // Route lesen
      char Type[20];
      int IFrom = 0, ITo = 0, Box = 0, BoxActive = 0, OutDev = -1, OFrom = -1, OTo = -1, ONoDrum = 1;
      test = sscanf(s, "%s %d %d %d %d %d %d %d %d",
        Type, &IFrom, &ITo, &Box, &BoxActive, &OutDev, &OFrom, &OTo, &ONoDrum);
      if ( test < 2 )
      {
        //3 ??
      }
      In->AddRoute(new ERoute(Str2RT(Type), IFrom, ITo, Box, BoxActive, GetEOut(OutDev), OFrom, OTo, ONoDrum));
      GETLINE;
    }
  }
}

#endif

#ifdef WX

// Routen schreiben
void WriteRoutes(wxString &config)
{
	// config sâ€°ubern
	config = wxEmptyString;
	// UnbenË†tigte Out Devices entfernen
	EDevice *Out;
	EDevice *In;
	for (Out = OutEDevices; Out; Out = Out->Next)
		Out->Nr = 0;
	for (In = InEDevices; In; In = In->Next)
		for (ERoute *R = In->Routes; R; R = R->Next)
			if ( R->Out )
				R->Out->Nr = 1;
	Out = OutEDevices;
	while ( Out )
	{
		if ( !Out->Nr )
		{
			NewDevice(&OutEDevices, DTNotSet, _T(""), 0, Out, 0);
			Out = OutEDevices;
			continue;
		}
		Out = Out->Next;
	}
	// Output schreiben
	config << _T("OUTPUT\n");
	int nr = 0;
	for ( Out = OutEDevices; Out; Out = Out->Next) {
	  Out->Nr = nr++; // Nummerierung zur bequemen Referenzierung
			  // beim Input schreiben
	  wxString sName = Out->Name;
	  if ( sName.Find(_T(" ")) )
	    sName.Prepend(_T("\"")) << _T("\"");
	  switch ( Out->DT ) {
	  case DTUnknown:
	    config << wxString::Format(_T("  UNKNOWN %s\n"), 
				       sName.c_str());
	    break;
	  case DTMidiPort:
	    config << wxString::Format(_T("  MIDIPORT %s %d %d\n"), 
				       sName.c_str(), Out->DevId, 
				       Out->BendingRange);
	    break;
	  case DTMidiFile:
	    config << wxString::Format(_T("  MIDIFILE %s %d %d\n"), 
				       sName.c_str(), 0, 
				       Out->BendingRange);
	    break;
	  case DTGis:
	    config << wxString::Format(_T("  GMN %s\n"), sName.c_str());
	    break;
	  case DTNotSet:
	    wxLogWarning(_("Device found, but device type not set."));
	  }
	}
#ifdef DEBUG
	std::cerr << "WriteConfig: " << (config.ToUTF8()) << std::endl;
#endif
	// Input schreiben
	nr = 0;
	config << _T("INPUT\n");
	for ( In = InEDevices; In; In = In->Next)
	{
	  // Device schreiben
	  In->Nr = nr++; // Nummern zur Referenz bei Play/Stop
	  In->Mode = MutaborDeviceStop; // Mode auf "registriert" setzen
	  wxString sName = In->Name;
	  if ( sName.Find(_T(" ")) )
	    sName.Prepend(_T("\"")) << _T("\"");
	  switch ( In->DT ) {
	  case DTUnknown:
	    config << wxString::Format(_T("  UNKNOWN %s\n"), sName.c_str());
	    break;
	  case DTGis:
	    config << wxString::Format(_T("  GMN %s\n"), sName.c_str());
	    break;
	  case DTMidiPort:
	    config << wxString::Format(_T("  MIDIPORT %s %d\n"), sName.c_str(), In->DevId);
	    break;
	  case DTMidiFile:
	    config << wxString::Format(_T("  MIDIFILE %s\n"), sName.c_str());
	    break;
	  case DTNotSet:
	    wxLogWarning(_("Device found but device type not set."));
	    break;
	  }
	  // Routen schreiben
	  for (ERoute *R = In->Routes; R; R = R->Next) {
	    int OutNr = ( R->Out ) ?  R->Out->Nr : -1;
	    config << wxT("    ") << muT(RTName[R->Type]) << 
	      wxString::Format(_T(" %d %d  %d %d  %d  %d %d %d\n"),
			       R->IFrom, R->ITo, R->Box, R->Active, OutNr,
			       R->OFrom, R->OTo, R->ONoDrum ? 1 : 0);
	  }
	}
#ifdef DEBUG
	std::cout << "WriteRoutes: " << (config.ToUTF8()) << std::endl;
#endif
}

// Routen schreiben
void WriteRoutes(wxConfigBase *config)
{
	// clean configuration
	// delete unused output devices
	EDevice *Out;
	EDevice *In;
	for (Out = OutEDevices; Out; Out = Out->Next)
		Out->Nr = 0;
	for (In = InEDevices; In; In = In->Next)
		for (ERoute *R = In->Routes; R; R = R->Next)
			if ( R->Out )
				R->Out->Nr = 1;
	Out = OutEDevices;
	while ( Out )
	{
		if ( !Out->Nr )
		{
			NewDevice(&OutEDevices, DTNotSet, _T(""), 0, Out, 0);
			Out = OutEDevices;
			continue;
		}
		Out = Out->Next;
	}
	config -> DeleteGroup(_T("Input"));
	config -> DeleteGroup(_T("Output"));
	// Output schreiben
	config -> SetPath(_T("Output"));
	int nr = 0;
	for ( Out = OutEDevices; Out; Out = Out->Next)
	{
		Out->Nr = nr++; 
		// Nummerierung zur bequemen Referenzierung beim Input schreiben
#ifdef DEBUG
		std::cerr << "Trying to save output device Nr. " 
			  << Out->Nr << std::endl;
#endif
		config->SetPath(wxString(_T("")) << Out->Nr);
		
		config->Write(_T("Name"), Out->Name);

		mutAssertMsg((Out->DT >= 0) && (Out->DT < DeviceMaxType),
			     wxString(_("Internal Error: Forbidden output device type: ")) << Out->DT);

		config->Write(_T("Type"), Out->DT);
		config->Write(_T("Type_Name"), wxGetTranslation(DevTypeName[Out->DT]));

		switch ( Out->DT )
		{
		case DTNotSet:
		case DTUnknown:
		case DTGis:
		  break;
		case DTMidiPort:
		  config -> Write(_T("Device_Id"), Out->DevId);
		  config -> Write(_T("Bending_Range"), Out->BendingRange);
		  break;
		case DTMidiFile:
		  config -> Write(_T("Device_Id"), 0);
		  config -> Write(_T("Bending_Range"), Out->BendingRange);
		  break;
		}
		config -> SetPath(_T(".."));
	}
	// Input schreiben
	nr = 0;
	config -> SetPath(_T("../Input"));
	for ( In = InEDevices; In; In = In->Next)
	{
		// Device schreiben
		In->Nr = nr++; // Nummern zur Referenz bei Play/Stop

		DEBUGLOGBASE("",
			     _T("Trying to save input device Nr. %d"),
			     In->Nr);
		In->Mode = MutaborDeviceStop; // Mode auf "registriert" setzen
		config->SetPath(wxString(_T("")) << In->Nr);
		
		config->Write(_T("Name"), In->Name);

		mutAssertMsg((In->DT >= 0) && (In->DT <= DeviceMaxType),
			_("Internal Error: Forbidden input device type."));

		config->Write(_T("Type"), In->DT);
#ifdef DEBUG
		std::cerr << "Type Name, " << std::endl;
#endif
		config->Write(_T("Type_Name"), wxGetTranslation(DevTypeName[In->DT]));

		switch ( In->DT ) {
		case DTNotSet:
		case DTMidiFile:
		case DTGis:
		case DTUnknown:
		  break;
		case DTMidiPort:
#ifdef DEBUG
		  std::cerr << "Device Id " << std::endl;
#endif
		  config -> Write(_T("Device_Id"), In->DevId);
		  break;
		default:
		  wxLogError(_("Undefined device type %d."), In->DT);
		}
		config -> SetPath(_T("Routes"));
		
		// Routen schreiben
		int routenr=0;
		for (ERoute *R = In->Routes; R; R = R->Next, routenr++)
		{
#ifdef DEBUG
			std::cerr << "Trying to save Route Nr: " << routenr << std::endl;
#endif
			config -> SetPath(wxString(_T("")) << routenr);
			config -> Write(_T("Type"), R->Type);
			config -> Write(_T("Type_Name"), muT(RTName[R->Type]));
			config -> Write(_T("Input_from"),R->IFrom);
			config -> Write(_T("Input_to"), R->ITo);
			config -> Write(_T("Box"), R->Box);
			config -> Write(_T("Active"), R->Active);
			config -> Write(_T("Output_device"), 
					( R->Out ) ?  R->Out->Nr : -1 );
			config -> Write(_T("Output_from"), R->OFrom);
			config -> Write(_T("Output_to"), R->OTo);
			config -> Write(_T("No_Drum"), R->ONoDrum);
			config -> SetPath(_T(".."));
		}
		config -> SetPath(_T("..")); // Routes
		config -> SetPath(_T("..")); // Input dev Counter
	}
	config -> SetPath(_T(".."));
#ifdef DEBUG
	std::cerr << "Done." << std::endl;
#endif
}
#else // no WX

// Routen schreiben
void WriteRoutes(char **config)
{
  char *s = (char*) malloc(30000), s1[200];
  s[0] = 0;
  // config sâ€°ubern
  if ( *config )
    free(*config);
  // UnbenË†tigte Out Devices entfernen
  EDevice *Out;
  EDevice *In;
  for (Out = OutEDevices; Out; Out = Out->Next)
    Out->Nr = 0;
  for (In = InEDevices; In; In = In->Next)
    for (ERoute *R = In->Routes; R; R = R->Next)
      if ( R->Out )
        R->Out->Nr = 1;
  Out = OutEDevices;
  while ( Out )
  {
    if ( !Out->Nr )
    {
      NewDevice(&OutEDevices, DTNotSet, "", 0, Out, 0);
      Out = OutEDevices;
      continue;
    }
    Out = Out->Next;
  }
  // Output schreiben
  strcat(s, "OUTPUT\n");
  int nr = 0;
  for ( Out = OutEDevices; Out; Out = Out->Next)
  {
    Out->Nr = nr++; // Nummerierung zur bequemen Referenzierung beim Input schreiben
    char s2[200];
	  if ( strchr(Out->Name, ' ') )
      sprintf(s2, "\"%s\"", Out->Name);
    else
      strcpy(s2, Out->Name);
    switch ( Out->DT )
    {
      case DTUnknown:
        sprintf(s1, "  UNKNOWN %s\n", s2);
        break;
      case DTMidiPort:
        sprintf(s1, "  MIDIPORT %s %d %d\n", s2, Out->DevId, Out->BendingRange);
        break;
      case DTMidiFile:
        sprintf(s1, "  MIDIFILE %s %d %d\n", s2, 0, Out->BendingRange);
        break;
      case DTGis:
        sprintf(s1, "  GMN %s\n", s2);
        break;
    }
    strcat(s, s1);
  }
  // Input schreiben
  nr = 0;
  strcat(s, "INPUT\n");
  for ( In = InEDevices; In; In = In->Next)
  {
    // Device schreiben
    In->Nr = nr++; // Nummern zur Referenz bei Play/Stop
    In->Mode = 0; // Mode auf "registriert" setzen
    char s2[200];
	  if ( strchr(In->Name, ' ') )
      sprintf(s2, "\"%s\"", In->Name);
    else
      strcpy(s2,In->Name);
    switch ( In->DT )
    {
      case DTUnknown:
        sprintf(s1, "  UNKNOWN %s\n", s2);
        break;
      case DTGis:
       sprintf(s1, "  GMN %s\n", s2);
        break;
      case DTMidiPort:
        sprintf(s1, "  MIDIPORT %s %d\n", s2, In->DevId);
        break;
      case DTMidiFile:
        sprintf(s1, "  MIDIFILE %s\n", s2);
        break;
    }
    strcat(s, s1);
    // Routen schreiben
    for (ERoute *R = In->Routes; R; R = R->Next)
    {
      int OutNr = ( R->Out ) ?  R->Out->Nr : -1;
      sprintf(s1, "    %s  %d %d  %d %d  %d  %d %d %d\n",
        RTName[R->Type], R->IFrom, R->ITo, R->Box, R->Active, OutNr,
        R->OFrom, R->OTo, R->ONoDrum ? 1 : 0);
      strcat(s, s1);
    }
  }
  *config = strdup(s);
  free(s);
}

#endif

// Boxes used

bool BoxUsed[MAX_BOX];

void CheckBoxesUsed()
{
  for (int i = 0; i < MAX_BOX; i++)
    BoxUsed[i] = false;
  for (EDevice *In = InEDevices; In; In = In->Next)
    for (ERoute *R = In->Routes; R; R = R->Next)
      if ( R->Box >= 0 )
        BoxUsed[R->Box] = true;
}


int SmallestBoxUsed()
{
  int Box = 256;
  for (EDevice *In = InEDevices; In; In = In->Next)
    for (ERoute *R = In->Routes; R; R = R->Next)
      if ( R->Box >= 0 )
        Box = STD_PRE::min(Box, R->Box);
  if ( Box == 256 )
    return 0;
  else
    return Box;
}

void ScanDevices()
{
  /** \TODO make devices and routes so that we can avoid this 
      function
      \TODO enable changes on line
  */

  // clean device lists
  if ( InDevices )
  {
    delete InDevices;
    InDevices = NULL;
  }

  if ( OutDevices )
  {
    delete OutDevices;
    OutDevices = NULL;
  }

  // handle output devices
  OutDevice **PreOut = &OutDevices;
  for (EDevice * oute = OutEDevices; oute ; oute = oute->Next) {
    OutDevice *Out = oute->newOutDevice();
    *PreOut = Out;
    PreOut = &(Out->Next);
  }

  // handle input devices
  InDevice **PreIn = &InDevices;
  for (EDevice * ine = InEDevices; ine ; ine = ine->Next) {
    
    InDevice *In = ine->newInDevice();
    *PreIn = In;
    PreIn = &(In->Next);

    // handle routes
    for (ERoute * routee = ine->Routes; routee; routee = routee->Next) {
      In->AddRoute(routee->newRoute());
    }
  }
}
