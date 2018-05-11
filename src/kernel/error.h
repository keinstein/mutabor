/** \file               -*- C++ -*-
 ********************************************************************
 * Description
 *
 * Copyright:   (c) 2016 Tobias Schlemmer
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
/* available groups: GUI, Parser, route, kernel, debug, docview, config, GUIroute */

/* we guard a little bit complicated to ensure the references are set right
 */

#if (!defined(SRC_KERNEL_ERROR_H_INCLUDED) && !defined(PRECOMPILE)) \
	|| (!defined(SRC_KERNEL_ERROR_H_INCLUDED_PRECOMPILED))
#ifndef PRECOMPILE
#define SRC_KERNEL_ERROR_H_INCLUDED
#endif

/* ---------------------------------------------------------------------------
 * headers
 * --------------------------------------------------------------------------- */

#include "src/kernel/Defs.h"

#ifndef SRC_KERNEL_ERROR_H_INCLUDED_PRECOMPILED
#define SRC_KERNEL_ERROR_H_INCLUDED_PRECOMPILED

/* system headers which do seldom change */

/** not for headers */
#ifdef __BORLANDC__
    #pragma hdrstop
#endif

MUTABOR_NAMESPACE(mutabor)
MUTABOR_NAMESPACE(hidden)
MUTABOR_EXTERN_C

enum mutabor_error_type {
	warning,
	compiler_warning,
	runtime_warning,
	error,
	internal_error,
	compiler_error,
	runtime_error
};

const char * mutabor_error_type_to_string(enum mutabor_error_type type);


static inline void mutabor_error_message(mutabor_box_type * box,
					 enum mutabor_error_type type,
					 const char * message,
					 ...) {
	char * formatted;
	va_list args;
	bool allocated = true;
	va_start(args,message);
	if (vasprintf(&formatted,message,args) == -1) {
		allocated = false;
		formatted = (char *)_mut("Error in Error: Could not allocate buffer for error message.");
		if (!formatted) {
			formatted = 
				(char *) "Error in Error: Could not allocate buffer for error message.";
		}
	}
	va_end(args);
	mutabor_callbacks->error_message(box,type,formatted);
	if (allocated)
		free(formatted);
}

MUTABOR_EXTERN_C_END
MUTABOR_NAMESPACE_END(hidden)
MUTABOR_NAMESPACE_END(mutabor)


#endif /* precompiled */
#endif /* header loaded */


/** \} */
