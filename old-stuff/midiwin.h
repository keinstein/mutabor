// ------------------------------------------------------------------
// Mutabor 2.win, 1997, R.Krauﬂe
// Midi-Windows-Funktionen
// ------------------------------------------------------------------

#if ! defined (__MIDIWIN_H_INCLUDED)
#define __MIDIWIN_H_INCLUDED

// #include "defs.h"

extern "C"
{
  void pascal MidiOpen(void);
  void pascal MidiClose(void);
}

void MidiOut1(BYTE code);
void MidiOut2(BYTE code1, BYTE code2);
void MidiOut3(BYTE code1, BYTE code2, BYTE code3);
void MidiOut4(BYTE code1, BYTE code2, BYTE code3, BYTE code4);
void MidiOut(DWORD code);

extern int OutputDevice;
extern int InputDevice;

#define MT_CONTROL 0
#define MT_CHANGE  1

#endif

