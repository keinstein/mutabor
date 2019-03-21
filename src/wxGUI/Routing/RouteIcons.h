// -*- C++ -*-
/** \file
********************************************************************
* Devices base classes. Icons used in route Window.
*
* \author Rüdiger Krauße,
* Tobias Schlemmer <keinstein@users.sourceforge.net>
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
*\addtogroup GUIroute
*\{
********************************************************************/

/* we guard a little bit complicated to ensure the references are set right
 */

#if (!defined(MUWX_ROUTING_ROUTEICONS_H) && !defined(PRECOMPILE))	\
	|| (!defined(MUWX_ROUTING_ROUTEICONS_H_PRECOMPILED))
#ifndef PRECOMPILE
#define MUWX_ROUTING_ROUTEICONS_H
#endif

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

#include "src/kernel/Defs.h"
#include "src/wxGUI/MutIcon.h"

#ifndef MUWX_ROUTING_ROUTEICONS_H_PRECOMPILED
#define MUWX_ROUTING_ROUTEICONS_H_PRECOMPILED

// system headers which do seldom change
#include "wx/icon.h"

MUTABOR_NAMESPACE(mutaborGUI)

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
extern MutIcon DevicePlayBitmap;
extern MutIcon DevicePauseBitmap;
extern MutIcon DeviceStopBitmap;
extern MutIcon DeviceRecordBitmap;

bool initMutIconShapes();

MUTABOR_NAMESPACE_END(mutaborGUI)

#endif				/* MUTROUTEICONS_H_PRECOMPILED */
#endif				/* MUTROUTEICONS_H */
/*
 * \}
 */
