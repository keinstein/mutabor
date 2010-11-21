// -*- C++ -*-

/** \file
 ********************************************************************
 * Routing. Compatibility functions.
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/mu32/routing/RouteCompat.h,v 1.2 2010/11/21 13:15:46 keinstein Exp $
 * \author Rüdiger Krauße <krausze@mail.berlios.de>,
 * Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 1998
 * $Date: 2010/11/21 13:15:46 $
 * \version $Revision: 1.2 $
 *
 * $Log: RouteCompat.h,v $
 * Revision 1.2  2010/11/21 13:15:46  keinstein
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

#ifndef MUTABOR_ROUTECOMPAT_H
#define MUTABOR_ROUTECOMPAT_H

#include "Defs.h"

#ifdef WX
#include "wx/config.h"
#endif

#include "treestorage.h"

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

#endif

/*
 * \}
 */

