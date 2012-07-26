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
 * $Log: RouteCompat.h,v $
 * Revision 1.5  2011/11/02 14:31:57  keinstein
 * fix some errors crashing Mutabor on Windows
 *
 * Revision 1.4  2011-09-27 20:13:22  keinstein
 * * Reworked route editing backend
 * * rewireing is done by RouteClass/GUIRoute now
 * * other classes forward most requests to this pair
 * * many bugfixes
 * * Version change: We are reaching beta phase now
 *
 * Revision 1.3  2011-02-20 22:35:56  keinstein
 * updated license information; some file headers have to be revised, though
 *
 * Revision 1.2  2010-11-21 13:15:46  keinstein
 * merged experimental_tobias
 *
 * Revision 1.1.2.1  2010-10-15 18:15:16  keinstein
 * Add commandline option --enable-xcode and XCode detection to configure
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

