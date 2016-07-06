/** \file               -*- C++ -*-
********************************************************************
* Inline routitnes for the device class
*
* Copyright:   (c) 2011 TU Dresden
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
*
********************************************************************
* \addtogroup route
* \{
********************************************************************/
/* we guard a little bit complicated to ensure the references are set right
 */

#if (!defined(ROUTING_DEVICE_INLINES) && !defined(PRECOMPILE))	\
	|| (!defined(ROUTING_DEVICE_INLINES_PRECOMPILED))
#ifndef PRECOMPILE
#define ROUTING_DEVICE_INLINES
#endif

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

#include "src/kernel/Defs.h"
#include "src/kernel/routing/Device.h"

#ifndef ROUTING_DEVICE_INLINES_PRECOMPILED
#define ROUTING_DEVICE_INLINES_PRECOMPILED

// system headers which do seldom change

namespace mutabor {

	template <class T, class P, class L>
	inline void CommonTypedDeviceAPI<T,P,L>::Destroy()  {
		TRACEC;
		DevicePtr self(static_cast<thistype *>(this));
		TRACEC;
		if (IsOpen()) Close();

		DisconnectFromAll();

		TRACEC;
		debug_destroy_class(this);
		RemoveFromDeviceList(static_cast<thistype *>(this));
		TRACEC;
	}

	template <class T, class P, class L>
	inline void CommonTypedDeviceAPI<T,P,L>::DisconnectFromAll()  {
		Route route (NULL);
		DevicePtr self(static_cast<thistype *>(this));

		routeListType::iterator R;
		while ( (R = routes.begin()) != routes.end() ) {
			TRACEC;
			route = (*R);
			TRACEC;
			disconnect(route,self);
			TRACEC;
		}
	}

}

#endif // precompiled
#endif // header loaded


///\}
