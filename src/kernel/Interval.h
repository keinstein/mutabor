/** \file 
 ********************************************************************
 * Description
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/src/kernel/Interval.h,v 1.6 2011/09/27 20:13:21 keinstein Exp $
 * Copyright:   (c) 2008 TU Dresden
 * \author  Tobias Schlemmer <keinstein@users.berlios.de>
 * \license GPL
 *
 *    This program is free software; you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation; either version 2 of the License, or
 *    (at your option) any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this program; if not, write to the Free Software
 *    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *
 ********************************************************************
 * \addtogroup kernel
 * \{
 ********************************************************************/
/* ------------------------------------------------------------------ */
/* Mutabor 2.win, 1997, R.Krauße */
/* Intervallberechnungen */
/* ------------------------------------------------------------------ */


/* we guard a little bit complicated to ensure the references are set right
 */

#if (!defined(MU32_INTERVAL_H) && !defined(PRECOMPILE)) \
	|| (!defined(MU32_INTERVAL_H_PRECOMPILED))
#ifndef PRECOMPILE
#define MU32_INTERVAL_H
#endif

/* --------------------------------------------------------------------------- */
/* headers */
/* --------------------------------------------------------------------------- */

#include "Defs.h"

#ifndef MU32_INTERVAL_H_PRECOMPILED
#define MU32_INTERVAL_H_PRECOMPILED

#ifdef __cplusplus
namespace mutabor {
	namespace hidden {
		extern "C" {
#endif

/* system headers which do seldom change */

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


/** \} */
