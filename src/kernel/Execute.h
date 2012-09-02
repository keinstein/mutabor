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

void AddKey(mutabor_box_type * box, int taste, int id);
void DeleteKey(mutabor_box_type * box, int taste, int id);
void MidiAnalysis(mutabor_box_type * box, BYTE midiByte);

void pascal _export KeyboardAnalyse(mutabor_box_type * box, int taste, char isLogic);
void pascal _export KeyboardAnalyseSimple(mutabor_box_type * box, int taste);

void FlushUpdateUI();


/* interal definitions */

#define FLUSH_UPDATE_UI FlushUpdateUI()
#endif // precompiled
#endif



///\}
