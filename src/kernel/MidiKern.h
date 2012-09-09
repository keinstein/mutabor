/** \file 
 ********************************************************************
 * Some MIDI macros
 *
 * Copyright:   (c) 1998-2011 TU Dresden
 * \author  R.Krauße
 * Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 
 * $Date: 2011/09/27 20:13:21 $
 * \version $Revision: 1.6 $
 * \license GPL
 *
 ********************************************************************
 * \addtogroup templates
 * \{
 ********************************************************************/
// ------------------------------------------------------------------
// ------------------------------------------------------------------

/* we guard a little bit complicated to ensure the references are set right
 */

#if (!defined(MU32_MIDIKERN_H) && !defined(PRECOMPILE)) \
	|| (!defined(MU32_MIDIKERN_H_PRECOMPILED))
#ifndef PRECOMPILE
#define MU32_MIDIKERN_H
#endif

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

#include "Defs.h"
#include "box.h"

#ifndef MU32_MIDIKERN_H_PRECOMPILED
#define MU32_MIDIKERN_H_PRECOMPILED

// system headers which do seldom change


#define DRUMCHANNEL 9  // Schlagzeugkanal bei General Midi (Kanal 9, bzw. 10)


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

#define ZWZ pow(2.0l,1.0l/12.0l)// 12 √ 2

#define LONG_TO_HERTZ( freq ) (440.0*pow(2.0l,((double)(freq-69*0x01000000) / ((double) (0x01000000*12)))))
/* 440 * (12 √ 2) ^ (pitch difference to “a440” in half tones)  */

/** Despite its name the following macro translates a long value into halftones.
 *  Cents are easy to deduce: they are the first two decimals.
 */
#define LONG_TO_CENT( freq ) ( (double)(freq) / ((double) 0x01000000))

#endif /* precompiled */
#endif



///\}
