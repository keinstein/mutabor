// ------------------------------------------------------------------
// Mutabor 2.win, 1997, R.Krauﬂe
// Play-Window bei Midiwiedergabe
// ------------------------------------------------------------------

#if ! defined (__PLAYWIN_H_INCLUDED)
#define __PLAYWIN_H_INCLUDED

#include <owl\mdichild.h>

TMDIChild *newPlayWin(TMDIClient *parent, const char far* title, const char far* midiTitle);

extern char MidiFile[];

#endif

