// ------------------------------------------------------------------
// Mutabor 2.win, 1997, R.Krauﬂe
// Midi-Interupt-Funktion
// ------------------------------------------------------------------

#if ! defined (__MIDIAUTO_H_INCLUDED)
#define __MIDIAUTO_H_INCLUDED

#include <mmsystem.h>

void CALLBACK MidiInFunc(HMIDIIN hMidiIn, UINT wMsg, DWORD dwInstance, DWORD dwParam1, DWORD dwParam2);

#endif
