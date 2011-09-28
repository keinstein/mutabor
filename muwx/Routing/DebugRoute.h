/** \file  -*- C++ -*-
 ********************************************************************
 * Debug functions for routing system
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/muwx/Routing/DebugRoute.h,v 1.5 2011/09/28 07:35:54 keinstein Exp $
 * Copyright:   (c) 2010 TU Dresden
 * \author  Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 2010/04/13
 * $Date: 2011/09/28 07:35:54 $
 * \version $Revision: 1.5 $
 * \license GPL
 *
 * $Log: DebugRoute.h,v $
 * Revision 1.5  2011/09/28 07:35:54  keinstein
 * Make distclean happy
 *
 * Revision 1.4  2011-09-27 20:13:24  keinstein
 * * Reworked route editing backend
 * * rewireing is done by RouteClass/GUIRoute now
 * * other classes forward most requests to this pair
 * * many bugfixes
 * * Version change: We are reaching beta phase now
 *
 * Revision 1.3  2011-02-20 22:35:58  keinstein
 * updated license information; some file headers have to be revised, though
 *
 * Revision 1.2  2010-11-21 13:15:51  keinstein
 * merged experimental_tobias
 *
 * Revision 1.1.2.1  2010-01-11 10:12:59  keinstein
 * added some .cvsignore files
 *
 *
 ********************************************************************
 * \addtogroup route
 * \{
 ********************************************************************/

/* we guard a little bit complicated to ensure the references are set right
 */

#if (!defined(MUWX_ROUTING_DEBUGROUTE_H) && !defined(PRECOMPILE)) \
	|| (!defined(MUWX_ROUTING_DEBUGROUTE_H_PRECOMPILED))
#ifndef PRECOMPILE
#define MUWX_ROUTING_DEBUGROUTE_H
#endif

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

#include "Defs.h"

#ifndef MUWX_ROUTING_DEBUGROUTE_H_PRECOMPILED
#define MUWX_ROUTING_DEBUGROUTE_H_PRECOMPILED

// system headers which do seldom change
// if necessary ;-)

#ifdef DEBUG
namespace mutaborGUI{
	void DebugCheckRoutes();
}
#else
namespace mutaborGUI {
	inline void DebugCheckRoutes() {}
}
#endif

 
#endif // precompiled
#endif
///\}
