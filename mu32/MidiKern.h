// ------------------------------------------------------------------
// Mutabor 3, 1998, R.Krauße
// MIDI-Makros
// ------------------------------------------------------------------

#ifndef MIDIKERN_H
#define MIDIKERN_H

#include "Interpre.h"
#include "Defs.h"

#define DRUMCHANNEL 9  // Schlagzeugkanal bei General Midi (Kanal 9, bzw. 10)

extern ton_system *tonsystem[MAX_BOX];

extern "C"
{
	void pascal _export KeyboardAnalyse(int box, int taste, char isLogic);
	void pascal _export KeyboardAnalyseSimple(int box, int taste);
}

// berechnet die Tonigkeit einer Taste bzgl. tonsystem
#define GET_INDEX(taste,tonsystem)                \
 ((int)((taste)-( (tonsystem)->anker % (tonsystem)->breite )) \
			  % (tonsystem)->breite )


// berechnet die 'Oktavlage' einer taste bzgl. tonsystem
#define GET_ABSTAND(taste,tonsystem) \
     ( (int)((taste)-( (tonsystem)->anker % (tonsystem)->breite ))  \
           / (tonsystem)->breite -((int) (tonsystem)->anker         \
           / (tonsystem)->breite ))


#define GET_FREQ(taste,tonsystem)  \
	( ( (tonsystem)->ton[GET_INDEX(taste,(tonsystem))]==0) ?       \
	  (long) 0 :                                       \
     (long)( (tonsystem)->periode *                   \
              GET_ABSTAND(taste,(tonsystem))  +                         \
                   (tonsystem)->ton[GET_INDEX(taste,(tonsystem))]))

#define ZWZ 1.059463094 // 12.Wurzel 2
#define LONG_TO_HERTZ( x ) (440.0*pow(ZWZ,((((float)x)/(double)16777216.0))-69))
#define LONG_TO_CENT( x ) ( ((float)x)/(double)167772.13  )

#endif


