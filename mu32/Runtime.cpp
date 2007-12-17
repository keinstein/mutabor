// ------------------------------------------------------------------
// Mutabor 2.win, 1997, R.Krauﬂe
// Laufzeitfunktionen der DLL
// ------------------------------------------------------------------
#include "Defs.h"

#include "Global.h"
#ifndef WX
#include <owl\dialog.h>
#else
  #include "EDevice.h"
#endif

#include "Hilfs.h"
#include "GrafKern.h"

#include "Runtime.h"
#include "Execute.h"
#include "Mutabor.rh"
#include <setjmp.h>

#include "Device.h"
#include "DevGIS.h"
#include "DevMidi.h"
#include "DevMidF.h"

bool RealTime = false;

jmp_buf weiter_gehts_nach_compilerfehler;

#ifdef WX
char pascal _export Compile(CompDlg *compDia, const wxChar *name)
{
  InitCompDia(compDia);

  if (!setjmp(weiter_gehts_nach_compilerfehler))
  {
	 loesche_syntax_speicher();
	 init_yylex ();

	 mutabor_programm_einlesen ( name );

	 calc_declaration_numbers();

	 compDia->SetText(IDC_COMP_LOGICS, sd1);
	 compDia->SetText(IDC_COMP_TONES, sd2);
	 compDia->SetText(IDC_COMP_TUNES, sd3);
	 compDia->SetText(IDC_COMP_TONESYST, sd4);
	 compDia->SetText(IDC_COMP_INTERVALS, sd5);
	 compDia->SetText(IDC_COMP_READCHARS, sd6);

	 show_line_number(-1);

	 compDia->SetText(wxID_OK, _("Generating tables"));

	 mutabor_tabellen_generator();


	 compDia->SetText(wxID_OK, _("Translation successful !"));
	 compDia->SetText(IDC_COMP_MESSAGE, _("No error occured !"));

	 return 1;
  }
  else
  {
	 show_line_number(-1);
#ifdef GERMAN
	 compDia->SetText(wxID_OK, _("Abbruch wegen Fehler !"));
#else
	 compDia->SetText(wxID_OK, _("Translation interrupted !"));
#endif
	 std::cout << (Fmeldung.ToUTF8()) << std::endl;
	 compDia->SetText(IDC_COMP_MESSAGE, Fmeldung);
	 return 0;
  }
}
#else
char pascal _export Compile(TDialog *compDia, char *name)
{
  InitCompDia(compDia->GetDlgItem(IDS_COMP2));

  if (!setjmp(weiter_gehts_nach_compilerfehler))
  {
	 loesche_syntax_speicher();
	 init_yylex ();

	 mutabor_programm_einlesen ( name );

	 calc_declaration_numbers();
	 ::SetWindowText(compDia->GetDlgItem(IDS_COMP3), sd1);
	 ::SetWindowText(compDia->GetDlgItem(IDS_COMP4), sd2);

	 show_line_number(-1);

	 ::SetWindowText(compDia->GetDlgItem(IDOK), "Generating tables");

	 mutabor_tabellen_generator();


	 ::SetWindowText(compDia->GetDlgItem(IDOK), "Translation successful !");
	 ::SetWindowText(compDia->GetDlgItem(IDS_COMP5), "No error occured !");

	 return 1;
  }
  else
  {
	 show_line_number(-1);
#ifdef GERMAN
	 ::SetWindowText(compDia->GetDlgItem(IDOK), "Abbruch wegen Fehler !");
#else
	 ::SetWindowText(compDia->GetDlgItem(IDOK), "Translation interrupted !");
#endif
	 std::cout << (char *)Fmeldung.c_str() << endl;
	 ::SetWindowText(compDia->GetDlgItem(IDS_COMP5), Fmeldung);
	 return 0;
  }
}
#endif

extern DWORD CurrentTime;
UpdateUICallback* updateUIcallback;

bool pascal _export Activate(bool realTime, UpdateUICallback* callback)
{
  RealTime = realTime;
  GlobalReset();
  AktionenInit();
  updateUIcallback = callback;
#if !defined(WX) || defined(__WXMSW__)
  if ( RealTime )
    timeBeginPeriod(1);
#endif
  bool ok = OutOpen();
  if ( ok && !InOpen() )
  {
    ok = false;
    OutClose();
  }
  if ( !ok )
  {
#if !defined(WX) || defined(__WXMSW__)
    if ( RealTime )
      timeEndPeriod(1);
#endif
#ifdef MUTWIN
    #if defined(WX)
      wxMessageBox(Fmeldung, _("Activation error"), wxOK | wxICON_ASTERISK );
    #else
      MessageBox(0, Fmeldung, "Activation error", MB_OK | MB_ICONASTERISK );
    #endif
#endif
    return false;
  }
  if ( RealTime )
    StartCurrentTime();
  else
    CurrentTime = 0;
  return true;
}

void pascal _export Stop()
{
  if ( RealTime )
    StopCurrentTime();
  InClose();
  OutClose();
#if !defined(WX) || defined(__WXMSW__)
  if ( RealTime )
    timeEndPeriod(1);
#endif
  GlobalReset();
}

void FlushUpdateUI()
{
  if ( keys_changed_sum && updateUIcallback )
  {
    keys_changed_sum = 0;
    updateUIcallback();
  }
}

// NoRealTime - Aktionen

void NRT_Play()
{
  // alles starten
  for (InDevice *In = InDevices; In; In = In->Next)
    In->Play();
  // Zeitscheiben
  bool Working = true;
  while ( Working )
  {
    Working = false;
    for (InDevice *In = InDevices; In; In = In->Next)
      if ( In->Mode == 1 && In->GetType() == DTMidiFile )
      {
        ((InMidiFile*)In)->IncDelta();
        Working = true;
      }
    CurrentTime++;
  }
  // alles schlieﬂen
  for (InDevice *In1 = InDevices; In1; In1 = In1->Next)
    In1->Stop();
  InDevChanged = 1;
}

void pascal _export InDeviceAction(int inDevNr, char action)
{
//  return; entkoppeln (zum debuggen)
  if ( !RealTime )
  {
    NRT_Play();
    return;
  }
  InDevice *In = InDevices;
  while ( In && inDevNr )
  {
    In = In->Next;
    inDevNr--;
  }
  if ( !In || In->Mode == 3 ) return;
  switch ( action )
  {
    case 0:
      In->Stop();
      break;
    case 1:
      In->Play();
      break;
    case 2:
      In->Pause();
      break;
  }
}

void pascal _export Panic()
{
  OutDevice *Out = OutDevices;
  while ( Out )
  {
    Out->Panic();
    Out = Out->Next;
  }
}

bool pascal _export CheckNeedsRealTime()
{
  return NeedsRealTime();
}

struct keyboard_ereignis *last;

char pascal _export GetMutTag(char &isLogic, char *text, char *einsttext, char &key, int box)
{
  if ( box != -1 )
	  last = first_keyboard[box];
  else
  	if ( last ) last = last->next;
  if ( !last ) return 0;
  key = last->taste;
  strncpy(text, last->aktion->name, 20);
  isLogic = ( last->the_logik_to_expand != NULL );
  if ( isLogic && last->the_logik_to_expand->einstimmungs_name )
	 strncpy(einsttext, last->the_logik_to_expand->einstimmungs_name, 20);
  else
	 strcpy(einsttext, "");
  return 1;
}

char pascal _export IsLogicKey(char key)
{
  struct keyboard_ereignis *last = first_keyboard[aktuelles_keyboard_instrument];
  while ( last )
  {
	 if ( key == last->taste )
		return last->the_logik_to_expand != NULL;
	 last = last->next;
  }
  return 2;
}

bool pascal _export KeyChanged(int box)
{
  int flag = keys_changed[box];
  keys_changed[box] = 0;
  return flag;
}

TONSYSTEM last_tonsystem[MAX_BOX];

bool pascal _export TSChanged(int box)
{
  int flag = memcmp(&(last_tonsystem[box]),
	  tonsystem[box],
	  (2*sizeof(int)) + sizeof(long) +
	  (tonsystem[box]->breite*
	  sizeof(long)) );
  last_tonsystem[box] = *tonsystem[box];
  return flag;
}

bool pascal _export InDevicesChanged()
{
  char flag = InDevChanged;
  InDevChanged = 0;
  return flag;
}

void pascal _export GetInDevicesMode(char *mode)
{
  int nr = 0;
  for (InDevice *In = InDevices; In; In = In->Next,nr++)
    mode[nr] = (char)In->Mode;
}

struct instrument * lauf_instrument;

char pascal _export GetChannels(char start, int &base, int &from, int &to, int &thru)
{
  if ( start )
    lauf_instrument = list_of_config_instrumente;
  else if ( lauf_instrument )
    lauf_instrument = lauf_instrument -> next;
  if ( !lauf_instrument ) return 0;
  base = lauf_instrument -> midi_in;
  from = lauf_instrument -> midi_von;
  to 	 = lauf_instrument -> midi_bis;
  thru = lauf_instrument -> midi_umleit;
  return 1;
}

void pascal _export SetChannels(int base, int from, int to, int thru)
{
  get_instrument_dekl (base, from, to, thru, &list_of_config_instrumente);
}

void pascal _export SetAktuellesKeyboardInstrument(int instr)
{
  aktuelles_keyboard_instrument = instr;
}

int pascal _export GetAktuellesKeyboardInstrument()
{
  return aktuelles_keyboard_instrument;
}

// scan-Hilfsfunktionen ---------------------------------------------
#ifdef WX
bool GetELine(const wxString& p, size_t& i, wxString &s);
DevType Str2DT(const wxString& type);
#else 
DevType Str2DT(char *type)
{
  char * DTName[] =  { "", "MIDIPORT", "MIDIFILE", "GMN" };
  int i;
  for (i = 3; i > 0; i--)
    if ( !strncmp(type, DTName[i], strlen(DTName[i])) )
      break;
  return (DevType)i;
}
#endif

// aus p eine Zeile in s lesen, p wird verschoben
bool GetLine(char **p, char *s)
{
  if ( !p || !(*p)[0] )
    return FALSE;
  while ( (*p)[0] == ' ' || (*p)[0] == '\n' || (*p)[0] == '\r' )
    *p = &(*p)[1];
  if ( !(*p)[0] )
    return FALSE;
  char *p1 = *p;
  *p = strchr(p1, '\n');
  if ( !p )
    *p = &p1[strlen(p1)];
  int i = (*p)-p1;
  strncpy(s, p1, i);
  s[i] = 0;
  return TRUE;
}

#define GETLINE \
  if ( !GetELine(config, i, s) ) \
    return


wxChar *RTName[] =  { _T("ALL"), _T("ELSE"), _T("CHANNEL"), _T("STAFF") };
 
RouteType Str2RT(wxChar * type)
{
  int i;
  for (i = 3; i > 0; i--)
    if ( !wxStricmp(type, RTName[i])) //, strlen(RTName[i])) )
      break;
  return (RouteType) i;
}

// das nr-ste Output Device
OutDevice *GetOut(int nr)
{
  if ( nr < 0 )
    return 0;
  OutDevice *Out = OutDevices;
  while ( Out && nr )
  {
    Out = Out->Next;
    nr--;
  }
  return Out;
}

// Device aus einem String scannen
void pascal _export ScanDevices(const wxString &config)
{
  // Listen s‰ubern
  if ( InDevices )
  {
    delete InDevices;
    InDevices = 0;
  }
  if ( OutDevices )
  {
    delete OutDevices;
    OutDevices = 0;
  }
  // Zerlegen von config
  wxString s;
  size_t i = 0;
  GETLINE;
  while ( !s.StartsWith(_T("OUTPUT" )))
  {
    GETLINE;
  }
  GETLINE;
  // Output lesen
  OutDevice **PreOut = &OutDevices;
  while ( !s.StartsWith(_T("INPUT") ))
  {
    wxChar Type[80], Name[400];
    int DevId, BendingRange;
#if (wxUSE_UNICODE)
	int test = SSCANF (s, _T("%ls \"%l[^\"]\" %d %d"), Type, Name, &DevId, &BendingRange);
    if ( test < 2 )
		test = SSCANF (s, _T("%ls %ls %d %d"), Type, Name, &DevId, &BendingRange);
#else
		int test = SSCANF (s, _T("%s \"%[^\"]\" %d %d"), Type, Name, &DevId, &BendingRange);
    if ( test < 2 )
      test = SSCANF (s, _T("%s %s %d %d"), Type, Name, &DevId, &BendingRange);
#endif
		if ( test < 2 )
		{
 		  //3 ??
		}
    OutDevice *Out;
    switch ( Str2DT(Type) )
    {
      case DTUnknown:
	std::cerr << "Unknown device: " << Type << std::endl;
        //3 ??
      case DTGis:
        Out = new OutGis(Name);
        break;
      case DTMidiPort:
        Out = new OutMidiPort(Name, DevId, BendingRange);
        break;
      case DTMidiFile:
        Out = new OutMidiFile(Name, DevId, BendingRange);
        break;
    }
    *PreOut = Out;
    PreOut = &(Out->Next);
    GETLINE;
  }
  GETLINE;
  // Input lesen
  InDevice **PreIn = &InDevices;
  while ( 1 )
  {
    // Device lesen
    wxChar Type[80], Name[400];
    int DevId = -1;
#if (wxUSE_UNICODE)
	int test = SSCANF (s, _T("%ls \"%l[^\"]\" %d"), Type, Name, &DevId);
    if ( test < 2 )
		test = SSCANF (s, _T("%ls %ls %d"), Type, Name, &DevId);
#else
	int test = SSCANF (s, _T("%s \"%[^\"]\" %d"), Type, Name, &DevId);
    if ( test < 2 )
		test = SSCANF (s, _T("%s %s %d"), Type, Name, &DevId);
#endif
	if ( test < 2 )
	{
		  //3 ??
	}
    InDevice *In;
    switch ( Str2DT(muT(Type)) )
    {
      case DTUnknown:
        //3 ??
      case DTGis:
        In = new InGis(Name, _T("GIS"));
        break;
      case DTMidiPort:
        In = new InMidiPort(Name, DevId);
        break;
      case DTMidiFile:
        In = new InMidiFile(Name, 0);
        break;
    }
    *PreIn = In;
    PreIn = &(In->Next);
    GETLINE;
    // Routen lesen
    while ( Str2DT(s) == DTUnknown )
    {
      // Route lesen
      wxChar Type[40];
      int IFrom = 0, ITo = 0, Box = 0, BoxActive = 0, OutDev = -1, OFrom = -1, OTo = -1, ONoDrum = 1;
#if (wxUSE_UNICODE)
      test = SSCANF(s, _("%ls %d %d %d %d %d %d %d %d"),
			Type, &IFrom, &ITo, &Box, &BoxActive, &OutDev, &OFrom, &OTo, &ONoDrum);
#else
      test = SSCANF(s, _("%s %d %d %d %d %d %d %d %d"),
			Type, &IFrom, &ITo, &Box, &BoxActive, &OutDev, &OFrom, &OTo, &ONoDrum);
#endif
      if ( test < 2 )
      {
        //3 ??
      }
      if ( Box == -2 ) // zur Sicherheit
        BoxActive = 0;
      In->AddRoute(new Route(Str2RT(Type), IFrom, ITo, Box, BoxActive, GetOut(OutDev), OFrom, OTo, ONoDrum));
      GETLINE;
    }
  }
}

// Timerdaten
void pascal _export GetTimerData(UINT &min, UINT &max)
{
#if !defined(WX) || defined(__WXMSW__)
  TIMECAPS TimeCaps;
  timeGetDevCaps(&TimeCaps, sizeof(TIMECAPS));
  min = TimeCaps.wPeriodMin;
  max = TimeCaps.wPeriodMax;
#else
  //TODO
#endif
}


