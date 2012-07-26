/** \file 
 ********************************************************************
 * Description
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/mu32/Execute.h,v 1.8 2011/09/27 20:13:21 keinstein Exp $
 * Copyright:   (c) 2008 TU Dresden
 * \author  Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 
 * $Date: 2011/09/27 20:13:21 $
 * \version $Revision: 1.8 $
 * \license GPL
 *
 * $Log: Execute.h,v $
 * Revision 1.8  2011/09/27 20:13:21  keinstein
 * * Reworked route editing backend
 * * rewireing is done by RouteClass/GUIRoute now
 * * other classes forward most requests to this pair
 * * many bugfixes
 * * Version change: We are reaching beta phase now
 *
 * Revision 1.7  2011-07-27 20:48:32  keinstein
 * started to move arrays using MAX_BOX into struct mutabor_box_type
 *
 * Revision 1.6  2011-03-06 13:15:40  keinstein
 * some rearrangement for update callback kernel->GUI
 *
 * Revision 1.5  2011-02-20 22:35:55  keinstein
 * updated license information; some file headers have to be revised, though
 *
 * Revision 1.2  2010-11-21 13:15:51  keinstein
 * merged experimental_tobias
 *
 * Revision 1.1.2.1  2010-01-11 10:12:59  keinstein
 * added some .cvsignore files
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


void KeyboardIn(int box, const mutChar *keys);

void MutResetKeys();
void GlobalReset();

void AddKey(int box, int taste, int id);

void DeleteKey(int box, int taste, int id);

void MidiAnalysis(int box, BYTE midiByte);

void protokoll_aktuelles_tonsystem( int instr );

void protokoll_liegende_frequenzen( int instr );

void protokoll_aktuelle_relationen( int instr );

void protokoll_liegende_relationen( int instr );

void FlushUpdateUI();

#define FLUSH_UPDATE_UI FlushUpdateUI()
#endif // precompiled
#endif



///\}
