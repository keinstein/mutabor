// -*- C++ -*-
/** \file
 ********************************************************************
 * Devices base classes. Icons used in route Window.
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/muwx/Routing/RouteIcons.h,v 1.4 2011/09/27 20:13:25 keinstein Exp $
 * \author Rüdiger Krauße <krausze@mail.berlios.de>,
 * Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 2009/11/23
 * $Date: 2011/09/27 20:13:25 $
 * \version $Revision: 1.4 $
 * \license GPL
 *
 * $Log: RouteIcons.h,v $
 * Revision 1.4  2011/09/27 20:13:25  keinstein
 * * Reworked route editing backend
 * * rewireing is done by RouteClass/GUIRoute now
 * * other classes forward most requests to this pair
 * * many bugfixes
 * * Version change: We are reaching beta phase now
 *
 * Revision 1.3  2011-02-20 22:35:59  keinstein
 * updated license information; some file headers have to be revised, though
 *
 * Revision 1.2  2010-11-21 13:15:50  keinstein
 * merged experimental_tobias
 *
 * Revision 1.1.2.1  2009-11-30 12:08:57  keinstein
 * split MutRouteShapes into several files into directory Routing
 *
 * MutRouteShapes.h,v 
 * Revision 1.1.2.2  2009/11/03 12:39:31  keinstein
 * input device dialog: Allow to edit input devices
 * fix a bug on Mac OS X, that prevented Mutabor from starting if no MIDI device is availlable
 *
 * Revision 1.1.2.1  2009/08/10 11:23:12  keinstein
 * merged from wrong tree
 *
 * Revision 1.2  2009/08/10 11:15:47  keinstein
 * some steps towards new route window
 *
 * Revision 1.1  2008/11/03 15:31:54  keinstein
 * Added to the system
 *
 *
 ********************************************************************
 *\addtogroup route
 *\{
 ********************************************************************/

/* we guard a little bit complicated to ensure the references are set right
 */

#if (!defined(MUWX_ROUTING_ROUTEICONS_H) && !defined(PRECOMPILE)) \
	|| (!defined(MUWX_ROUTING_ROUTEICONS_H_PRECOMPILED))
#ifndef PRECOMPILE
#define MUWX_ROUTING_ROUTEICONS_H
#endif

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

#include "Defs.h"
#include "MutIcon.h"

#ifndef MUWX_ROUTING_ROUTEICONS_H_PRECOMPILED
#define MUWX_ROUTING_ROUTEICONS_H_PRECOMPILED

// system headers which do seldom change


namespace mutaborGUI {

	extern MutIcon NewInputDevBitmap;
	extern MutIcon MidiInputDevBitmap;
	extern MutIcon NewOutputDevBitmap;
	extern MutIcon MidiOutputDevBitmap;
	extern MutIcon MidiFileBitmap;
	extern MutIcon GuidoFileBitmap;
	extern MutIcon BoxBitmap;
	extern MutIcon NewBoxBitmap;
	extern MutIcon ActiveChannelBitmap;
	extern MutIcon PassiveChannelBitmap;

	bool initMutIconShapes();
}
#endif				/* MUTROUTEICONS_H_PRECOMPILED */
#endif				/* MUTROUTEICONS_H */
/*
 * \}
 */
