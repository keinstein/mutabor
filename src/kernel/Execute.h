/** \file 
 ********************************************************************
 * Execute tuning changes
 *
 * Copyright:   (c) 1998-2008 TU Dresden
 * \author  
 * R. Krauße, 
 * Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 
 * $Date: 2011/09/27 20:13:21 $
 * \version $Revision: 1.8 $
 * \license GPL
 *
 *
 ********************************************************************
 * \addtogroup kernel
 * \{
 ********************************************************************/
// ##################################################################
// Mutabor 3, Header execute file
// ##################################################################

/* we guard a little bit complicated to ensure the references are set right
 */

#if (!defined(MU32_EXECUTE_H) && !defined(PRECOMPILE)) \
	|| (!defined(MU32_EXECUTE_H_PRECOMPILED))
#ifndef PRECOMPILE
#define MU32_EXECUTE_H
#endif

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

#include "Defs.h"
#include "box.h"

#ifndef MU32_EXECUTE_H_PRECOMPILED
#define MU32_EXECUTE_H_PRECOMPILED

// system headers which do seldom change


void KeyboardIn(mutabor_box_type * box, const mutChar *keys);

void MutResetKeys();
void GlobalReset();

void AddKey(mutabor_box_type * box, int taste, size_t id, size_t channel, void * userdata);
void DeleteKey(mutabor_box_type * box, int taste, size_t id, size_t channel);
void MidiAnalysis(mutabor_box_type * box, BYTE midiByte);

void pascal _export KeyboardAnalyse(mutabor_box_type * box, int taste, char isLogic);
void pascal _export KeyboardAnalyseSimple(mutabor_box_type * box, int taste);

void FlushUpdateUI();


/* interal definitions */

#define FLUSH_UPDATE_UI FlushUpdateUI()

// berechnet die Tonigkeit einer Taste bzgl. tonsystem
inline int GET_INDEX(int key, tone_system * tonsystem) {
	 int retval = (key - tonsystem->anker) % tonsystem->breite;
	 return retval < 0 ? retval + tonsystem->breite : retval;
}

// berechnet die 'Oktavlage' einer taste bzgl. tonsystem
inline int GET_ABSTAND(int taste, tone_system * tonsystem) {
	int retval = (int)(taste - (tonsystem->anker % tonsystem->breite)) / tonsystem->breite;
	retval -= ((int)tonsystem->anker  / tonsystem->breite);
	return retval;
}

#if 0
#define GET_ABSTAND(taste,tonsystem)					\
	( (int)((taste)-( (tonsystem)->anker % (tonsystem)->breite ))	\
	  / (tonsystem)->breite -((int) (tonsystem)->anker		\
				  / (tonsystem)->breite ))
#endif

inline long GET_FREQ(int key,tone_system * tonsystem) {
	size_t index = GET_INDEX(key,tonsystem);
	if (tonsystem->ton[index]==0) 
		return 0;
	return tonsystem->periode 
		* GET_ABSTAND(key,(tonsystem))  
		+ (tonsystem)->ton[index];
}




#endif // precompiled
#endif



///\}
