// -*- C++ -*-

/** \file
 ********************************************************************
 * Routing. Compatibility functions.
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/src/kernel/routing/RouteCompat.h,v 1.5 2011/11/02 14:31:57 keinstein Exp $
 * \author Rüdiger Krauße <krausze@mail.berlios.de>,
 * Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 1998
 * $Date: 2011/11/02 14:31:57 $
 * \version $Revision: 1.5 $
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
 *
 ********************************************************************
 *\addtogroup route
 *\{
 ********************************************************************/

/* we guard a little bit complicated to ensure the references are set right
 */

#if (!defined(MU32_ROUTING_ROUTECOMPAT_H) && !defined(PRECOMPILE)) \
	|| (!defined(MU32_ROUTING_ROUTECOMPAT_H_PRECOMPILED))
#ifndef PRECOMPILE
#define MU32_ROUTING_ROUTECOMPAT_H
#endif

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

#include "src/kernel/Defs.h"
#include "src/kernel/treestorage.h"

#ifndef MU32_ROUTING_ROUTECOMPAT_H_PRECOMPILED
#define MU32_ROUTING_ROUTECOMPAT_H_PRECOMPILED

#ifdef WX
#include "wx/config.h"
#endif


namespace compat30 {
	
	/// load the routes from a text string
	/** \param config string to be read from
	 */
	void LoadRoutes(const mutStringRef);

	/// write the routes to the given string
	/** \param config string to be written to
	 */
	void SaveRoutes(mutStringRef);
}

#endif /* PRECOMPILED */
#endif

/*
 * \}
 */

