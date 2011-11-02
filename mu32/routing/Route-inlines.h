/** \file               -*- C++ -*-
 ********************************************************************
 * Inline functions from Route.h
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/mu32/routing/Route-inlines.h,v 1.4 2011/11/02 14:31:57 keinstein Exp $
 * Copyright:   (c) 2011 TU Dresden
 * \author  Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 
 * $Date: 2011/11/02 14:31:57 $
 * \version $Revision: 1.4 $
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
 * $Log: Route-inlines.h,v $
 * Revision 1.4  2011/11/02 14:31:57  keinstein
 * fix some errors crashing Mutabor on Windows
 *
 * Revision 1.3  2011-10-02 16:58:41  keinstein
 * * generate Class debug information when compile in debug mode
 * * InputDeviceClass::Destroy() prevented RouteClass::Destroy() from clearing references -- fixed.
 * * Reenable confirmation dialog when closing document while the logic is active
 * * Change debug flag management to be more debugger friendly
 * * implement automatic route/device deletion check
 * * new debug flag --debug-trace
 * * generate lots of tracing output
 *
 * Revision 1.2  2011-09-30 09:10:24  keinstein
 * Further improvements in the routing system.
 *
 * Revision 1.1  2011-09-27 20:18:30  keinstein
 * add a file missed during last commit
 *
 ********************************************************************
 * \addtogroup templates
 * \{
 ********************************************************************/
// availlable groups: GUI, route, kernel, muwx, debug, docview

/* we guard a little bit complicated to ensure the references are set right
 */

#if (!defined(MU32_ROUTING_ROUTE_INLINES_H) && !defined(PRECOMPILE)) \
	|| (!defined(MU32_ROUTING_ROUTE_INLINES_H_PRECOMPILED))
#ifndef PRECOMPILE
#define MU32_ROUTING_ROUTE_INLINES_H
#endif

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

#include "mu32/Defs.h"
#include "mu32/routing/Route.h"

#ifndef MU32_ROUTING_ROUTE_INLINES_H_PRECOMPILED
#define MU32_ROUTING_ROUTE_INLINES_H_PRECOMPILED

// system headers which do seldom change
#include "Device.h"


namespace mutabor {

	template <class I, class O>
	inline void TRouteClass<I,O>::Attatch (OutputDevice & dev) {
			TRACEC;	
			Add(dev)		;
			TRACEC;		
			Route r(this);
			TRACEC;	
			dev->Add(r);
			TRACEC;
	}
	
	template <class I, class O>
	inline void TRouteClass<I,O>::Attatch (InputDevice & dev) {
			TRACEC;
			Add(dev);
			Route r(this);
			dev->Add(r);
	}

	template <class I, class O>
	inline bool TRouteClass<I,O>::Reconnect(OutputDevice & olddev, 
				       OutputDevice & newdev) {
			bool retval = Replace(olddev,newdev);
 			Route r(this);
			if (retval) {
				retval = retval && olddev->Remove(r);
			}
			if (retval) {
				newdev->Add(r);
			} else
				mutASSERT(false);
				// Check taht olddev is correcty disconnected
			return retval;
	}

	template <class I, class O>
	inline bool TRouteClass<I,O>::Reconnect(InputDevice & olddev, 
				       InputDevice & newdev) {
			bool retval = Replace(olddev,newdev);
			Route r(this);
			if (retval) {
				retval = retval && olddev->Remove(r);
			}
			if (retval) {
				newdev->Add(r);
			} else 
				mutASSERT(false);
			return retval;
	}

	/// Detatch current output device
	template <class I, class O>
	inline bool TRouteClass<I,O>::Detatch(OutputDevice & dev) {
			Route r (this);
			bool retval = dev->Remove(r);
			if (retval) {
				// this might delete dev
				retval = Remove(dev);
			}
			return retval;
		}
		/// Detatch current input device
	template <class I, class O>
	inline bool TRouteClass<I,O>::Detatch(InputDevice & dev) {
			Route r(this);
			bool retval = dev->Remove(r);
			if (retval) {
				// this might delete dev
				retval = Remove(dev);
			}
			return retval;
		}

	inline Route RouteFactory::Create(
		InputDevice & in,
		OutputDevice & out,
		RouteType type,
		int iFrom,
		int iTo,
		int box,
		bool active,
		int oFrom,
		int oTo,
		bool oNoDrum /*,
			       Route next*/) {
		DEBUGLOGTYPE(smartptr,RouteFactory,_T("input device %p (%d)"),
			in.get(),
			intrusive_ptr_get_refcount(in.get()));
		DEBUGLOGTYPE(smartptr,RouteFactory,_T("output device %p (%d)"),
			out.get(),
			intrusive_ptr_get_refcount(out.get()));
		if (factory) {
			RouteClass * r = factory->DoCreate(in,out,type,iFrom,iTo,
						 box,active,
						    oFrom,oTo,oNoDrum/*,next*/);
			DEBUGLOGTYPE(smartptr,RouteFactory,
				     _T("Shipping %p from factory"),
				     r);
			return r;
		} else {
			UNREACHABLECT(RouteFactory);
			return NULL;
		}
			
	}
}


#endif // precompiled
#endif // header loaded


///\}
