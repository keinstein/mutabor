/** \file 
 ********************************************************************
 * Table generators for the Mutabor engine
 *
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


/* we guard a little bit complicated to ensure the references are set right
 */

#if (!defined(SRC_KERNEL_TABGEN_H) && !defined(PRECOMPILE)) \
	|| (!defined(SRC_KERNEL_TABGEN_H_PRECOMPILED))
#ifndef PRECOMPILE
#define SRC_KERNEL_TABGEN_H
#endif

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

#include "Defs.h"

#ifndef SRC_KERNEL_TABGEN_H_PRECOMPILED
#define SRC_KERNEL_TABGEN_H_PRECOMPILED

// system headers which do seldom change

#ifdef __cplusplus 
namespace mutabor {
	namespace hidden {
		extern "C" {
#endif


/* TabGen.cpp */
void expand_decition_tree (mutabor_box_type * box);

#ifdef __cplusplus 
		} // extern "C"
	} // namespace hidden
} // namespace mutabor
#endif

#endif // precompiled
#endif


///\}
