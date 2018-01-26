/** \file               -*- C++ -*-
 ********************************************************************
 * Interface_dependent functions.
 *
 * Copyright:   (c) 2013 Tobias Schlemmer
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
 * \addtogroup templates
 * \{
 ********************************************************************/
/* availlable groups: GUI, Parser, route, kernel, debug, docview, config, GUIroute
 */

/* we guard a little bit complicated to ensure the references are set right
 */

#if (!defined(SRC_KERNEL_INTERFACE_DEPS_H) && !defined(PRECOMPILE)) \
	|| (!defined(SRC_KERNEL_INTERFACE_DEPS_H_PRECOMPILED))
#ifndef PRECOMPILE
#define SRC_KERNEL_INTERFACE_DEPS_H
#endif

/* ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------*/

#include "src/kernel/Defs.h"

#ifndef SRC_KERNEL_INTERFACE_DEPS_H_PRECOMPILED
#define SRC_KERNEL_INTERFACE_DEPS_H_PRECOMPILED

#if defined(DEBUG) || defined(CPPUNIT)
/* system headers which do seldom change */
#define mutASSERT(expr)							\
	if (!(expr)) {							\
		mutabor_assert_fail(__FILE__,				\
				    __LINE__,				\
				    __func__,				\
				    #expr,				\
				    "");				\
	}

#else
#define mutASSERT(exp)
#endif

#ifdef __cplusplus 
extern "C" {
#endif

void mutabor_assert_fail(const char *file,
			 int line,
			 const char *func,
			 const char *cond,
			 const char *msg);

#ifdef __cplusplus 
}
#endif

#endif /* precompiled */
#endif /* header loaded */


/** \} */
