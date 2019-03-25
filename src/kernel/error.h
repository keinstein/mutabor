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
#include <stdio.h>

/** not for headers */
#ifdef __BORLANDC__
    #pragma hdrstop
#endif

MUTABOR_NAMESPACE(mutabor)
MUTABOR_NAMESPACE(hidden)
MUTABOR_EXTERN_C

struct mutabor_box_type_struct;
typedef struct mutabor_box_type_struct mutabor_box_type;


enum mutabor_error_type {
	generic_warning,
	compiler_warning,
	runtime_warning,
	generic_error,
	internal_error,
	compiler_error,
	runtime_error,
	allocation_error
};

struct mutabor_logic_parsed;


typedef void (* mutabor_callback_update_type) (mutabor_box_type * box,
					       unsigned int flags);
typedef void (* mutabor_callback_midi_out_type) (mutabor_box_type * box,
						 struct midiliste * outliste);
typedef void (* mutabor_callback_error_message_type)(mutabor_box_type * box,
						     enum mutabor_error_type type,
						     const char * message);
typedef void (*mutabor_callback_update_display)(mutabor_box_type * box, int line_number);
typedef void (*mutabor_callback_log_action)(mutabor_box_type * box,
					    const char * action);

typedef void (*mutabor_callback_lock_logic)(struct mutabor_logic_parsed * logic);



struct mutabor_callback_type {
	mutabor_callback_update_type  update;
	mutabor_callback_midi_out_type  midi_out;
	mutabor_callback_error_message_type  error_message;
	mutabor_callback_update_display  update_display;
	mutabor_callback_log_action  log_action;
	mutabor_callback_lock_logic  lock_logic;
	mutabor_callback_lock_logic  unlock_logic;
	mutabor_callback_lock_logic  free_mutex;
};

extern struct mutabor_callback_type * mutabor_callbacks;


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

#ifdef __cplusplus
#include <stdexcept>

namespace error {
	using mutabor::hidden::mutabor_error_type;
	using mutabor::hidden::generic_warning;
	using mutabor::hidden::compiler_warning;
	using mutabor::hidden::runtime_warning;
	using mutabor::hidden::generic_error;
	using mutabor::hidden::internal_error;
	using mutabor::hidden::compiler_error;
	using mutabor::hidden::runtime_error;
	using mutabor::hidden::allocation_error;

	class runtime_exception: public std::runtime_error{
	public:
		typedef std::runtime_error base;

		runtime_exception(enum mutabor_error_type t,
				  const std::string & message): base(make_what(t,message)),
								type(t) {}
		enum mutabor_error_type get_type() const { return type; }
	protected:
		enum mutabor_error_type type;

		std::string make_what(enum mutabor_error_type type,
				      const std::string & message) {
			return boost::str(make_format(type) % message);
		}
		boost::format make_format(enum mutabor_error_type type) {
			switch (type) {
			case generic_warning:
				return boost::format(_mut("Warning: %s"));
			case compiler_warning:
				return boost::format(_mut("Compiler warning: %s"));
			case runtime_warning:
				return boost::format(_mut("Runtime Warning: %s"));
			case generic_error:
				return boost::format(_mut("Error: %s"));
			case internal_error:
				return boost::format(_mut("Internal error: %s"));
			case compiler_error:
				return boost::format(_mut("Compiler error: %s"));
			case ::mutabor::error::runtime_error:
				return boost::format(_mut("Runtime error: %s"));
			case ::mutabor::error::allocation_error:
				return boost::format(_mut("Allocation failed: %s"));
			default:
				return boost::format(_mut("Unknown error (Type %d): %s")) %type;
			}
		}

	};
}

static inline void  __attribute__((__noreturn__)) throw_runtime_error(enum error::mutabor_error_type type,
								      const std::string & message) {
	BOOST_THROW_EXCEPTION(error::runtime_exception(type,message));
}

#endif

MUTABOR_NAMESPACE_END(mutabor)


#endif /* precompiled */
#endif /* header loaded */


/** \} */
