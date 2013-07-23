/** \file               -*- C++ -*-
 ********************************************************************
 * Forward declarations for several lists used in the code base.
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/src/wxGUI/Routing/RouteLists.h,v 1.2 2011/11/02 14:32:01 keinstein Exp $
 * Copyright:   (c) 2011 TU Dresden
 * \author  Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 
 * $Date: 2011/11/02 14:32:01 $
 * \version $Revision: 1.2 $
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
 * $Log: RouteLists.h,v $
 * Revision 1.2  2011/11/02 14:32:01  keinstein
 * fix some errors crashing Mutabor on Windows
 *
 * Revision 1.1  2011-09-27 20:13:25  keinstein
 * * Reworked route editing backend
 * * rewireing is done by RouteClass/GUIRoute now
 * * other classes forward most requests to this pair
 * * many bugfixes
 * * Version change: We are reaching beta phase now
 *
 * Revision 1.4  2011-08-06 09:16:22  keinstein
 * added “official” license descripiton
 *
 * Revision 1.3  2011-02-20 22:36:00  keinstein
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
 * \addtogroup GUI
 * \{
 ********************************************************************/
// availlable groups: GUI, route, kernel, src/wxGUI, debug, docview

/* we guard a little bit complicated to ensure the references are set right
 */

#if (!defined(MUWX_ROUTING_ROUTELISTS_H) && !defined(PRECOMPILE)) \
	|| (!defined(MUWX_ROUTING_ROUTELISTS_H_PRECOMPILED))
#ifndef PRECOMPILE
#define MUWX_ROUTING_ROUTELISTS_H
#endif

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

#include "src/kernel/Defs.h"

#ifndef MUWX_ROUTING_ROUTELISTS_H_PRECOMPILED
#define MUWX_ROUTING_ROUTELISTS_H_PRECOMPILED

// system headers which do seldom change
#include <list>

namespace mutaborGUI {
	class MutBoxShape;
	typedef std::list <MutBoxShape *> MutBoxShapeList;

	template<class T>
	class MutDeviceShape;
	
	struct outputdevicetypes;
	struct inputdevicetypes;

	typedef MutDeviceShape<inputdevicetypes> MutInputDeviceShape;
	typedef std::list<MutInputDeviceShape *> MutInputDeviceShapeList;

	typedef MutDeviceShape<outputdevicetypes> MutOutputDeviceShape;
	typedef std::list<MutOutputDeviceShape *> MutOutputDeviceShapeList;

	class MutBoxShape;
	typedef std::list<MutBoxShape *> MutBoxShapeList;

	class MutBoxChannelShape;
	typedef std::list<MutBoxChannelShape *> MutBoxChannelShapeList;
}

#endif /* PRECOMPILED */
#endif


///\}
