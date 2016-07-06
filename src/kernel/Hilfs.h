/** \file 
 ********************************************************************
 * Description
 *
 * Copyright:   (c) 2008 TU Dresden
 * \author  Tobias Schlemmer <keinstein@users.sourceforge.net>
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

/* we guard a little bit complicated to ensure the references are set right
 */

#if (!defined(MU32_Hilfs_H) && !defined(PRECOMPILE)) \
	|| (!defined(MU32_Hilfs_H_PRECOMPILED))
#ifndef PRECOMPILE
#define MU32_Hilfs_H
#endif

/* --------------------------------------------------------------------------- */
/* headers */
/* --------------------------------------------------------------------------- */

#include "Defs.h"
#include "box.h"

#ifndef MU32_Hilfs_H_PRECOMPILED
#define MU32_Hilfs_H_PRECOMPILED

/* system headers which do seldom change */
#include <stdio.h>


#ifdef __cplusplus 
namespace mutabor {
	namespace hidden {
		extern "C" {
#endif
#define HEAP_PORTION_SYNTAX   /*65536L*/ 64000
#define HEAP_PORTION_LAUFZEIT /*65536L*/ 64000


void xfree (void * pointer);
void * xmalloc (mutabor_box_type * box, size_t size);
void * xrealloc (mutabor_box_type * box, void * block, size_t newsize);
void * xcalloc (mutabor_box_type * box, size_t anzahl, size_t size);

void yfree (void * pointer);
void * ymalloc (mutabor_box_type * box, size_t size);
void * yrealloc (mutabor_box_type * box, void * block, size_t newsize);
void * ycalloc (mutabor_box_type * box, size_t anzahl, size_t size);

int loesche_syntax_speicher (mutabor_box_type * box);
int init_syntax_speicher (mutabor_box_type * box);
int init_laufzeit_speicher ( mutabor_box_type * box );
int loesche_laufzeit_speicher ( mutabor_box_type * box );
void * xalloca (mutabor_box_type * box, size_t size);
void xde_alloca (void * pointer);


#ifdef __cplusplus
		}
	}
}
#endif
			
#endif /* MU32_HILFS_H_PRECOMPILED */

#endif /* MU32_HILFS_H */


/** \} */
