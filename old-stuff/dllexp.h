// ------------------------------------------------------------------
// Mutabor 2.win, 1997, R.Krauﬂe
// ÷ffentliche Funktionen der DLL
// ------------------------------------------------------------------

#ifndef DLLEXP_H
#define DLLEXP_H

#include <owl\dialog.h>
#include "setup.h"

extern "C"
{
  char pascal Compile( TDialog* compWin, char *name );
  void pascal Activate();
  void pascal Stop();
  void pascal Panic();

  void pascal keyboard_analyse(int taste, char isLogic);
//  char pascal GetMutTag(char &isLogic, char _far *text, char _far *einsttext, char &key, char first);
  char pascal GetMutTag(char &isLogic, char *text, char *einsttext, char &key, char first);
  char pascal IsLogicKey(char key);

  bool pascal KeyChanged();
  bool pascal TSChanged();
  bool pascal ActChanged();

  void pascal GetSetupData(TSetupData *data);
  void pascal SetSetupData(TSetupData *data);

  char* pascal GetKeyString(char asTS);
  char* pascal GetTSString(char asTS);
  char* pascal GetActString();

  int pascal GetLineNumbers();
  int pascal GetErrorLine();

  void pascal GetDrivers(int *driver);
  void pascal SetDrivers(int *driver);

  char pascal GetChannels(char start, int &base, int &from, int &to, int &thru);
  void pascal SetChannels(int base, int from, int to, int thru);

  void pascal SetAktuellesKeyboardInstrument(int instr);
  int  pascal GetAktuellesKeyboardInstrument();

//3  void pascal MidiOpen(void);
//3  void pascal MidiClose(void);
}

#endif
