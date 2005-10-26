// ------------------------------------------------------------------
// Mutabor 3, 1998, R.Krauße
// Oberflächen Devices
// ------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>

#include "EDevice.h"

EDevice *InEDevices = 0;
EDevice *OutEDevices = 0;

char *RouteConfig = 0;

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

// Neue Route am Ende anhängen (damit RTelse O.K. geht)
void EDevice::AddRoute(ERoute *route)
{
  ERoute **R = &Routes;
  while ( *R )
  	R = &(*R)->Next;
    *R = route;
}

char help[200];

// Name mit '_' aufgefüllt
char *EDevice::GetName()
{
  strcpy(help, Name);
  for (int i = 0; i < strlen(help); i++)
    if ( help[i] == ' ' )
      help[i] = '_';
  return help;
}

// Hilfe für Verkettung: Wenn Outgerät gekillt wird,
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
EDevice* NewDevice(EDevice **List, DevType dt, char *name, int devId, EDevice *oldPos, EDevice *newPos)
{
  // Position finden zum Daten abladen
  EDevice *Pos = 0;
  ERoute *R = 0;
  if ( oldPos == newPos && oldPos )
  {
    Pos = oldPos;
    Pos->DT = dt;
    strcpy(Pos->Name, name);
    Pos->DevId = devId;
    Pos->Mode = -1;
  }
  else
  {
    if ( oldPos )
    {
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
         ( ( !strcmp((*Dev)->Name, name) ) ||
           ( dt == DTMidiPort && (*Dev)->DevId == devId ) ) )
    {
      // doppeltes Device gefunden, Routen übertragen und löschen
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
DevType Str2DT(char *type);
#endif

#ifndef WX
char *RTName[] =  { "ALL", "ELSE", "CHANNEL", "STAFF" };
#else
extern char *RTName[];
#endif

#ifndef WX
RouteType Str2RT(char *type)
{
  int i;
  for (i = 3; i > 0; i--)
    if ( !strncmp(type, RTName[i], strlen(RTName[i])) )
      break;
  return (RouteType) i;
}
#else
RouteType Str2RT(char *type);
#endif

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

// Routen scannen
void ScanRoutes(char *config)
{
  // Listen säubern
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
//		int test = sscanf (s, "%s %s %d %d", Type, Name, &DevId, &BendingRange);
		int test = sscanf (s, "%s \"%[^\"]\" %d %d", Type, Name, &DevId, &BendingRange);
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

// Routen schreiben
void WriteRoutes(char **config)
{
  char *s = (char*) malloc(30000), s1[200];
  s[0] = 0;
  // config säubern
  if ( *config )
    free(*config);
  // Unbenötigte Out Devices entfernen
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

#ifdef WX
#if !defined(__WXMSW__)
  #define min(a, b)	((a) < (b) ? (a) : (b))
#endif
#endif

int SmallestBoxUsed()
{
  int Box = 256;
  for (EDevice *In = InEDevices; In; In = In->Next)
    for (ERoute *R = In->Routes; R; R = R->Next)
      if ( R->Box >= 0 )
        Box = min(Box, R->Box);
  if ( Box == 256 )
    return 0;
  else
    return Box;
}

