/** \file 
 ********************************************************************
 * Description
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/src/kernel/Interval.h,v 1.6 2011/09/27 20:13:21 keinstein Exp $
 * Copyright:   (c) 2008 TU Dresden
 * \author  Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 
 * $Date: 2011/09/27 20:13:21 $
 * \version $Revision: 1.6 $
 * \license GPL
 *
 * $Log: Interval.h,v $
 * Revision 1.6  2011/09/27 20:13:21  keinstein
 * * Reworked route editing backend
 * * rewireing is done by RouteClass/GUIRoute now
 * * other classes forward most requests to this pair
 * * many bugfixes
 * * Version change: We are reaching beta phase now
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
 * \addtogroup templates
 * \{
 ********************************************************************/
// ------------------------------------------------------------------
// Mutabor 2.win, 1997, R.Krauße
// Intervallberechnungen
// ------------------------------------------------------------------


/* we guard a little bit complicated to ensure the references are set right
 */

#if (!defined(MU32_INTERVAL_H) && !defined(PRECOMPILE)) \
	|| (!defined(MU32_INTERVAL_H_PRECOMPILED))
#ifndef PRECOMPILE
#define MU32_INTERVAL_H
#endif

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

#include "Defs.h"

#ifndef MU32_INTERVAL_H_PRECOMPILED
#define MU32_INTERVAL_H_PRECOMPILED

#ifdef __cplusplus
namespace mutabor {
	namespace hidden {
		extern "C" {
#endif

// system headers which do seldom change

int intervall_list_laenge (struct intervall *list);

void berechne_intervalle_absolut (mutabor_box_type * box, struct intervall * list_of_intervalle);

void check_komplex_intervall (mutabor_box_type * box, 
			      struct komplex_intervall * liste,
                              const char * konstrukt_name);

double get_wert_komplex_intervall (mutabor_box_type * box, 
				   struct komplex_intervall * intervall);

#ifdef __cplusplus
		}
	}
}
#endif

#endif /* precompiled */
#endif


///\}
