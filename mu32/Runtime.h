// ------------------------------------------------------------------
// Mutabor 2.win, 1997, R.Krauﬂe
// Laufzeitfunktionen der DLL
// ------------------------------------------------------------------

#if ! defined (__RUNTIME_H_INCLUDED)
#define __RUNTIME_H_INCLUDED

#include "Defs.h"

#include "wx/wxchar.h"
#include "CompDlg.h"
#if !defined(__WXMSW__) 
#ifndef UINT
  #define UINT unsigned int
#endif
  #define pascal
#endif

#include "Device.h"

typedef void UpdateUICallback();

extern "C"
{
#ifndef WX
  char pascal Compile( TDialog *compWin, const char *name );
#else
  char pascal Compile( CompDlg *compDia, const wxChar *name );
#endif
  bool pascal Activate(bool realTime, UpdateUICallback* callback = 0);
  void pascal Stop();
  void pascal Panic();

//  void pascal InDeviceActionAll(char action);
  void pascal InDeviceAction(int inDevNr, char action);

  bool pascal CheckNeedsRealTime();

  // box = -1 ... weiterlesen in angefangener Liste
  char pascal GetMutTag(char &isLogic, char *text, char *einsttext, char &key, int box = -1);
  char pascal IsLogicKey(char key);

  bool pascal KeyChanged(int box);
  bool pascal TSChanged(int box);
  bool pascal InDevicesChanged();

  void pascal GetInDevicesMode(char *mode);

  void pascal GetDrivers(int *driver);
  void pascal SetDrivers(int *driver);

  char pascal GetChannels(char start, int &base, int &from, int &to, int &thru);
  void pascal SetChannels(int base, int from, int to, int thru);

  void pascal SetAktuellesKeyboardInstrument(int instr);
  int  pascal GetAktuellesKeyboardInstrument();

#ifndef WX
  void pascal ScanDevices(char *config);

#endif

  OutDevice * GetOut(int nr);

  void pascal GetTimerData(UINT &min, UINT &max);
}

#endif

