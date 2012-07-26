// ------------------------------------------------------------------
// Mutabor 2.win, 1997, R.Krauﬂe
// MIDI-Interupt-Funktion
// ------------------------------------------------------------------

#include <stdlib.h>
#include "windows.h"
#include "midiauto.h"
#include <mmsystem.h>
#include "midikern.h"
#include "dllexp.h"
#include "record.h"

TModule *MidiDllLib;

void CALLBACK _export MidiInFunc(HMIDIIN hMidiIn, UINT wMsg, DWORD dwInstance, DWORD dwParam1, DWORD dwParam2)
{
  CurrentTimeStamp = dwParam2;
  if ( wMsg != MIM_DATA || dwParam1 % 256 > 240 ) return;
#ifdef RECORD
  if ( RecordMode != REC_NO )
    RecordMidi(0, dwParam1);
#endif
  // Daten in Mid-Automat
  midi_automat(dwParam1);
}

int FAR PASCAL LibMain(HINSTANCE hInstance, WORD /*wDataSeg*/,
  WORD /* cbHeapSize */, LPSTR lpCmdLine)
{
  int TheStatus;
  MidiDllLib = new TModule("MIDIAUTO", hInstance, lpCmdLine);
  TheStatus = MidiDllLib->Status;
  if ( TheStatus != 0 )
  {
	 delete MidiDllLib;
	 MidiDllLib = NULL;
  }
  return (TheStatus == 0);
}

int FAR PASCAL WEP ( int /*bSystemExit*/ )
{
  // don't delete Lib here.
  return 1;
}
