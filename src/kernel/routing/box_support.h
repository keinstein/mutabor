// -*- C++ -*-

/** \file
 ********************************************************************
 * Mutabor Box for C++. Mutabor Core.
 *
 * \author Tobias Schlemmer <keinstein@users.sourceforge.net>
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
 *\addtogroup route
 *\{
 ********************************************************************/

/* we guard a little bit complicated to ensure the references are set right
 */

#if (!defined(ROUTING_BOX_SUPPORT_H) && !defined(PRECOMPILE)) \
	|| (!defined(ROUTING_BOX_SUPPORT_H_PRECOMPILED))
#ifndef PRECOMPILE
#define ROUTING_BOX_SUPPORT_H
#endif

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

#define HIDE_MUTABOR_C_API

#include "src/kernel/Defs.h"

#ifndef ROUTING_BOX_SUPPORT_H_PRECOMPILED
#define ROUTING_BOX_SUPPORT_H_PRECOMPILED

// system headers which do seldom change

#include <vector>


namespace mutabor {
	namespace box_support {

		struct tone_entry {
			double pitch;
			enum {sounding, silent, invalid} flag;
			tone_entry(double p):pitch(p),
					     flag(sounding) {}
			tone_entry():pitch(0.0),
				     flag(silent) {}
		};
		typedef std::vector<tone_entry> tone_list;

		struct tone_system {
			int anchor;
			double period;
			tone_list tones;
		};
	}
}


#endif /* precompiled */
#endif

/*
 * \}
 */
