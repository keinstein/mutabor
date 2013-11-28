/** \file               -*- C++ -*-
 ********************************************************************
 * Forward declarations for several lists used in the code base.
 *
 * Copyright:   (c) 2011 TU Dresden
 * \author  Tobias Schlemmer <keinstein@users.berlios.de>
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
 *
 ********************************************************************
 * \addtogroup GUIroute
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
