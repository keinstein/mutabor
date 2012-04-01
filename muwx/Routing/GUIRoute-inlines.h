/** \file               -*- C++ -*-
 ********************************************************************
 * Interface to separate Mutabor functionality from the GUI
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/muwx/Routing/GUIRoute-inlines.h,v 1.5 2011/11/02 14:32:00 keinstein Exp $
 * Copyright:   (c) 2011 TU Dresden
 * \author  Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 
 * $Date: 2011/11/02 14:32:00 $
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
 * $Log: GUIRoute-inlines.h,v $
 * Revision 1.5  2011/11/02 14:32:00  keinstein
 * fix some errors crashing Mutabor on Windows
 *
 * Revision 1.4  2011-10-04 17:16:14  keinstein
 * make program compile on Mac (wx 2.9) and fix some memory corruption
 *
 * Revision 1.3  2011-10-02 16:58:42  keinstein
 * * generate Class debug information when compile in debug mode
 * * InputDeviceClass::Destroy() prevented RouteClass::Destroy() from clearing references -- fixed.
 * * Reenable confirmation dialog when closing document while the logic is active
 * * Change debug flag management to be more debugger friendly
 * * implement automatic route/device deletion check
 * * new debug flag --debug-trace
 * * generate lots of tracing output
 *
 * Revision 1.2  2011-09-30 18:07:05  keinstein
 * * make compile on windows
 * * s/wxASSERT/mutASSERT/g to get assert handler completely removed
 * * add ax_boost_base for boost detection
 *
 * Revision 1.1  2011-09-27 20:13:24  keinstein
 * * Reworked route editing backend
 * * rewireing is done by RouteClass/GUIRoute now
 * * other classes forward most requests to this pair
 * * many bugfixes
 * * Version change: We are reaching beta phase now
 *
 *
 *
 ********************************************************************
 * \addtogroup GUI
 * \{
 ********************************************************************/
// availlable groups: GUI, route, kernel, muwx, debug, docview

/* we guard a little bit complicated to ensure the references are set right
 */

#if (!defined(MUWX_ROUTING_GUIROUTE_INLINES_H) && !defined(PRECOMPILE)) \
	|| (!defined(MUWX_ROUTING_GUIROUTE_INLINES_H_PRECOMPILED))
#ifndef PRECOMPILE
#define MUWX_ROUTING_GUIROUTE_INLINES_H
#endif

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

#include "mu32/Defs.h"
#include "muwx/Routing/GUIRoute.h"
#include "muwx/Routing/BoxShape.h"
#include "muwx/Routing/InputDeviceShape.h"
#include "muwx/Routing/OutputDeviceShape.h"

#ifndef MUWX_ROUTING_GUIROUTE_INLINES_H_PRECOMPILED
#define MUWX_ROUTING_GUIROUTE_INLINES_H_PRECOMPILED

// system headers which do seldom change

namespace mutaborGUI {

	inline bool GUIRouteBase::Reconnect(MutBoxShape * oldshape,
					    MutBoxShape * newshape) {
		mutASSERT(oldshape);
		mutASSERT(newshape);
		return route->Reconnect(oldshape->GetBoxId(),
					newshape->GetBoxId());
	}


	inline void GUIRouteBase::Add(MutBoxChannelShape * shape) {
		if (shape) {
			shapes.push_back(shape);
		} else {
			UNREACHABLEC;
		}
	}
	inline bool GUIRouteBase::Remove(MutBoxChannelShape * shape) {
		bool ok = false;
		if (shape) {
			MutBoxChannelShapeList::iterator pos = 
				std::find(shapes.begin(),shapes.end(),shape);
			ok = (pos != shapes.end()); 
			mutASSERT(ok);
			if (ok)
				shapes.erase(pos);
		} else {
			UNREACHABLEC;
			ok = false;
		}
		return ok;
	}

	inline void GUIRouteBase::Attatch(MutBoxChannelShape * shape) {
		if (!shape) {
			UNREACHABLEC;
			return;
		}
		Add(shape);
		mutabor::Route r(route);
		shape->Add(r);
		
		wxWindow * parent = shape->GetGrandParent();
		mutASSERT(route);
		mutabor::OutputDevice out = route->GetOutputDevice();
		if (out) {
			MutOutputDeviceShape * outshape =
				ToGUIBase(out).GetShape(parent);
			if (outshape) {
				outshape->Add(shape);
				shape->Add(outshape);
			}
			
		}
		mutabor::InputDevice & in = 
			const_cast<mutabor::InputDevice &>(route->GetInputDevice());
		if (in) {
			MutInputDeviceShape * inshape =
				ToGUIBase(in).GetShape(parent);
			if (inshape) {
				inshape->Add(shape);
				shape->Add(inshape);
			}
			
		}
	}

	inline bool GUIRouteBase::Detatch(MutBoxChannelShape * shape) {
		DEBUGLOG(routing,_T("Disconnecting %p"),shape);
		if (!shape) {
			UNREACHABLEC;
			return false;
		}
		bool retval = true; 
		
		MutInputDeviceShape * in = 
			shape -> GetInput();
 		if (retval && in) {
			DEBUGLOG(routing,_T("Disconnecting %p from %p"),shape,in);
			DEBUGLOG(smartptr,_T("Route: %p (%d), removing in from shape"),
				 route, 
				 intrusive_ptr_get_refcount(route));
			retval = retval && shape->Remove(in);
			DEBUGLOG(smartptr,_T("Route: %p (%d), removing shape from in"),
				 route, 
				 intrusive_ptr_get_refcount(route));
			retval = retval && in->Remove(shape);
		}
		DEBUGLOG(smartptr,_T("Route: %p (%d), disconnecting shapes"),
			 route, 
			 intrusive_ptr_get_refcount(route));

		MutOutputDeviceShape * out = 
			shape -> GetOutput();
		if (retval && out) {
			DEBUGLOG(routing,_T("Disconnecting %p from %p"),shape,out);
			retval = retval && shape->Remove(out);
			DEBUGLOG(smartptr,_T("Route: %p (%d), removed out from shap"),
				 route, 
				 intrusive_ptr_get_refcount(route));
			retval = retval && out->Remove(shape);
			DEBUGLOG(smartptr,_T("Route: %p (%d), removed shape from out"),
				 route, 
				 intrusive_ptr_get_refcount(route));
		}
		
		DEBUGLOG(routing,_T("Disconnecting %p from %p"),shape,route);
		if (retval) 
			retval = Remove(shape);
			DEBUGLOG(smartptr,_T("Route: %p (%d), removed shape"),
				 route, 
				 intrusive_ptr_get_refcount(route));

		if (retval) {
			mutabor::Route r (route);
			retval = shape->Remove(r);
			DEBUGLOG(smartptr,_T("Route: %p (%d), removed from shape"),
				 route, 
				 intrusive_ptr_get_refcount(route));
		}
		if (!retval) 
			UNREACHABLEC;
		return retval;
	}

	inline bool GUIRouteBase::Delete(MutBoxChannelShape * shape) {
		if (!shape) {
			UNREACHABLEC;
			return false;
		}
		bool retval = Detatch(shape);
		if (retval) 
			shape -> Destroy();
	}

	inline MutBoxChannelShape * 
	GUIRouteBase::GetShape(wxWindow * parent) {
		if (!parent) return NULL;
		for (MutBoxChannelShapeList::iterator out 
			     = shapes.begin();
		     out != shapes.end();
		     out++) {
			if ((*out)->GetGrandParent() == parent) {
				return *out;
			}
		}
		return NULL;
	}
		
	template<class T> 
	inline void GUIfyRoute<T>::Attatch (mutabor::OutputDevice & dev) {
		TRACEC;
		T::Attatch(dev);
		TRACEC;
		GetGUIRoute().Attatch(dev);
		TRACEC;
	}

	template<class T> 
	inline void GUIfyRoute<T>::Attatch (mutabor::InputDevice & dev) {
		TRACEC;
		T::Attatch(dev);
		TRACEC;
		GetGUIRoute().Attatch(dev);
		TRACEC;
	}
	template<class T> 
	inline void GUIfyRoute<T>::Attatch (int boxid) {
		TRACEC;
		T::Attatch(boxid);
		TRACEC;
		GetGUIRoute().Attatch(boxid);
		TRACEC;
	}

	template<class T> 
	inline bool GUIfyRoute<T>::Reconnect(mutabor::OutputDevice & olddev, 
					     mutabor::OutputDevice & newdev){
		TRACEC;
		bool retval = T::Reconnect(olddev, newdev);
		TRACEC;
		if (retval)
			retval = GetGUIRoute().Reconnect(olddev, newdev);
		TRACEC;
		return retval;
	}
	template<class T> 
	inline bool GUIfyRoute<T>::Reconnect (mutabor::InputDevice & olddev,
					      mutabor::InputDevice & newdev) {
		TRACEC;
		bool retval = T::Reconnect(olddev, newdev);
		TRACEC;
		if (retval)
			retval = GetGUIRoute().Reconnect(olddev, newdev);
		TRACEC;
		return retval;
	}
	template<class T> 
	inline bool GUIfyRoute<T>::Reconnect (int oldboxid,
					      int newboxid) {
		TRACEC;
		bool retval = T::Reconnect(oldboxid, newboxid);
		TRACEC;
		if (retval)
			retval = GetGUIRoute().Reconnect(oldboxid, 
								   newboxid);
		TRACEC;
		return retval;
	}

	template<class T> 
	inline bool GUIfyRoute<T>::Detatch (mutabor::OutputDevice & dev) {
		TRACEC;
		bool retval = GetGUIRoute().Detatch(dev);
		TRACEC;
		if (retval)
			retval = T::Detatch(dev);
		TRACEC;
		return retval;
	}
	template<class T> 
	inline bool GUIfyRoute<T>::Detatch (mutabor::InputDevice & dev) {
		TRACEC;
		bool retval = GetGUIRoute().Detatch(dev);
		TRACEC;
		if (retval)
			retval = T::Detatch(dev);
		TRACEC;
		return retval;
	}
	template<class T> 
	inline bool GUIfyRoute<T>::Detatch (int boxid) {
		TRACEC;
		bool retval = GetGUIRoute().Detatch(boxid);
		TRACEC;
		if (retval)
			retval = T::Detatch(boxid);
		TRACEC;
		return retval;
	}

#if 0
	/// add a route
	template<class T> 
	inline  void GUIfyOutputDevice<T>::Add(Route & route) {
		TRACEC;
		T::Add(route);
		TRACEC;
		GetGUIDevice().Add(route);
		TRACEC;
	}

	/// replace a route
	template<class T> 
	inline  bool GUIfyOutputDevice<T>::Replace(Route & oldroute, 
						   Route & newroute) {
		TRACEC;
		bool retval = T::Replace(oldroute,newroute);
		TRACEC;
		if (retval) 
			retval = GetGUIDevice().Replace(oldroute,newroute);
		TRACEC;
		return retval;
	}
	/// remove a route
	template<class T> 
	inline  bool GUIfyOutputDevice<T>::Remove(Route & route) {
		TRACEC;
		bool retval = T::Remove(route);
		TRACEC;
		if (retval) 
			retval = GetGUIDevice().Remove(route);
		TRACEC;
		return retval;
	}
#endif

	inline void GUIOutputDeviceBase::Add(MutOutputDeviceShape * shape) {
		if (shape) {
			shapes.push_back(shape);
		} else {
			UNREACHABLEC;
		}
	}
	inline bool GUIOutputDeviceBase::Remove(MutOutputDeviceShape * shape) {
		bool ok = false;
		if (shape) {
			MutOutputDeviceShapeList::iterator pos = 
				std::find(shapes.begin(),shapes.end(),shape);
			ok = (pos != shapes.end()); 
			mutASSERT(ok);
			if (ok)
				shapes.erase(pos);
		} else {
			UNREACHABLEC;
			ok = false;
		}
		return ok;
	}
		
	inline void GUIOutputDeviceBase::Attatch(MutOutputDeviceShape * shape) {
 		TRACEC;
		if (!shape) {
			UNREACHABLEC;
			return;
		}
 		TRACEC;
		Add(shape);
 		TRACEC;
		shape->Add(device);
 		TRACEC;

		wxWindow * parent = shape->GetParent();
		mutASSERT(device);
		TRACEC;
		const mutabor::routeListType & routes = device -> GetRoutes();
		for (mutabor::routeListType::const_iterator 
			     route = routes.begin();
		     route != routes.end(); route++) {
			mutabor::Route & r = const_cast<mutabor::Route & >(*route);
			TRACEC;
			MutBoxChannelShape * channel =
				ToGUIBase(r).GetShape(parent);
			if (channel) {
				shape->Add(channel);
				TRACEC;
				channel->Add(shape);
				TRACEC;
			}
			
		}
		
	}

	inline bool GUIOutputDeviceBase::Detatch(MutOutputDeviceShape * shape) {
 		TRACEC;
		DEBUGLOG(routing,_T("Disconnecting %p"),shape);
		if (!shape) {
			UNREACHABLEC;
			return false;
		}
		bool retval = true; 
		const MutBoxChannelShapeList & channels = 
			shape->GetChannels();
		MutBoxChannelShapeList::const_iterator i;
		while ( (i = channels.begin()) != channels.end()) {
			MutBoxChannelShape * channel = 
				const_cast<MutBoxChannelShape *>(*i);
			DEBUGLOG(routing,_T("Disconnecting %p from %p"),
				 shape,channel);
			TRACEC;
			retval = retval && shape -> Remove(channel);
			TRACEC;
			retval = retval && channel -> Remove(shape);
		}

		DEBUGLOG(routing,_T("Disconnecting %p from %p"),shape,this);
 		TRACEC;
		if (retval) 
			retval = Remove(shape);
 		TRACEC;
		if (retval)
			retval = shape->Remove(device);
 		TRACEC;
		if (!retval) 
			UNREACHABLEC;
		return retval;
	}

	inline bool GUIOutputDeviceBase::Delete(MutOutputDeviceShape * shape) {
		if (!shape) {
			UNREACHABLEC;
			return false;
		}
 		TRACEC;
		bool retval = Detatch(shape);
 		TRACEC;
		if (retval) 
			shape -> Destroy();
 		TRACEC;
	}

	inline MutOutputDeviceShape * 
	GUIOutputDeviceBase::GetShape(wxWindow * parent) {
		if (!parent) return NULL;
		for (MutOutputDeviceShapeList::iterator out 
			     = shapes.begin();
		     out != shapes.end();
		     out++) {
			if ((*out)->GetParent() == parent) {
				return *out;
			}
		}
		return NULL;
	}



#if 0
	/// add a route
	template<class T> 
	inline  void GUIfyInputDevice<T>::Add(Route & route) {
		T::Add(route);
		GetGUIDevice().Add(route);
	}

	/// replace a route
	template<class T> 
	inline  bool GUIfyInputDevice<T>::Replace(Route & oldroute, 
						  Route & newroute) {
		bool retval = T::Replace(oldroute,newroute);
		if (retval) 
			retval = GetGUIDevice().Replace(oldroute,newroute);
		return retval;
	}
	/// remove a route
	template<class T> 
	inline  bool GUIfyInputDevice<T>::Remove(Route & route) {
		bool retval = T::Remove(route);
		if (retval) 
			retval = GetGUIDevice().Remove(route);
		return retval;
	}
#endif

	inline void GUIInputDeviceBase::Add(MutInputDeviceShape * shape) {
		if (shape) {
			shapes.push_back(shape);
		} else {
			UNREACHABLEC;
		}
	}
	inline bool GUIInputDeviceBase::Remove(MutInputDeviceShape * shape) {
		bool ok = false;
		if (shape) {
			MutInputDeviceShapeList::iterator pos = 
				std::find(shapes.begin(),shapes.end(),shape);
			ok = (pos != shapes.end()); 
			mutASSERT(ok);
			if (ok)
				shapes.erase(pos);
		} else {
			UNREACHABLEC;
			ok = false;
		}
		return ok;
	}
		
	inline void GUIInputDeviceBase::Attatch(MutInputDeviceShape * shape) {
		if (!shape) {
			UNREACHABLEC;
			return;
		}
 		TRACEC;
		Add(shape);
 		TRACEC;
		mutabor::InputDevice In(device);
		shape->Add(In);
 		TRACEC;

		/** see output device */
		wxWindow * parent = shape->GetParent();
		mutASSERT(device);
		const mutabor::routeListType & routes = device -> GetRoutes();
		for (mutabor::routeListType::const_iterator 
			     route = routes.begin();
		     route != routes.end(); route++) {
			mutabor::Route & r = const_cast<mutabor::Route & >(*route);
			MutBoxChannelShape * channel =
				ToGUIBase(r).GetShape(parent);
			if (channel) {
				TRACEC;
				shape->Add(channel);
				TRACEC;
				channel->Add(shape);
				TRACEC;
			}
			
		}
	}
	inline bool GUIInputDeviceBase::Detatch(MutInputDeviceShape * shape) {
		DEBUGLOG(routing,_T("Disconnecting %p"), shape);
		if (!shape) {
			UNREACHABLEC;
			return false;
		}
		bool retval = true; 
		const MutBoxChannelShapeList & channels = 
			shape->GetChannels();
		DEBUGLOG(routing,_T("%d channels"), channels.size());
		MutBoxChannelShapeList::const_iterator i;
		while ( (i = channels.begin()) != channels.end()) {
			MutBoxChannelShape * channel = 
				const_cast<MutBoxChannelShape *>(*i);
			DEBUGLOG(routing,_T("Disconnecting %p from %p"),
				 shape, channel);
			TRACEC;
			retval = retval && shape -> Remove(channel);
			TRACEC;
			retval = retval && channel -> Remove(shape);
			TRACEC;
		}

		DEBUGLOG(routing,_T("Disconnecting %p from %p"),shape,this);
		
 		TRACEC;
		if (retval) 
			retval = Remove(shape);
 		TRACEC;
		if (retval) {
			mutabor::InputDevice In(device);
			retval =  shape->Remove(In);
		}
 		TRACEC;
		if (!retval) 
			UNREACHABLEC;
		return retval;
	}
	inline bool GUIInputDeviceBase::Delete(MutInputDeviceShape * shape) {
		if (!shape) {
			UNREACHABLEC;
			return false;
		}
 		TRACEC;
		bool retval = Detatch(shape);
 		TRACEC;
		if (retval) 
			shape -> Destroy();
 		TRACEC;
	}

	inline MutInputDeviceShape * 
	GUIInputDeviceBase::GetShape(wxWindow * parent) {
		if (!parent) return NULL;
		for (MutInputDeviceShapeList::iterator in 
			     = shapes.begin();
		     in != shapes.end();
		     in++) {
			if ((*in)->GetParent() == parent) {
				return *in;
			}
		}
		return NULL;
	}

		

	inline  const GUIInputDeviceBase & 
	ToGUIBase(const mutabor::InputDeviceClass * d) {
		mutASSERT((const GUIfiedInputDevice *)(d));
		mutASSERT((((const GUIfiedInputDevice *)(d))
			  -> GetGUIDevice()).IsDevice(d));
		
		return ((const GUIfiedInputDevice *)(d))
			-> GetGUIDevice();
	}

	inline  GUIInputDeviceBase & ToGUIBase(mutabor::InputDeviceClass * d) {
		mutASSERT((GUIfiedInputDevice *)(d));
		mutASSERT((((GUIfiedInputDevice *)(d))
			  -> GetGUIDevice()).IsDevice(d));
		
		return ((GUIfiedInputDevice *)(d))
			-> GetGUIDevice();
	}

	inline  const GUIOutputDeviceBase & 
	ToGUIBase(const mutabor::OutputDeviceClass * d) {
		mutASSERT((const GUIfiedOutputDevice *)(d));
		mutASSERT((((const GUIfiedOutputDevice *)(d))
			  -> GetGUIDevice()).IsDevice(d));
		
		return ((const GUIfiedOutputDevice *)(d))
			-> GetGUIDevice();
	}
	inline  GUIOutputDeviceBase & ToGUIBase(mutabor::OutputDeviceClass * d) {
		mutASSERT((GUIfiedOutputDevice *)(d));
		mutASSERT((((GUIfiedOutputDevice *)(d))
			  -> GetGUIDevice()).IsDevice(d));
		
		return ((GUIfiedOutputDevice *)(d))
			-> GetGUIDevice();
	}

	inline  const GUIInputDeviceBase & 
	ToGUIBase(const mutabor::InputDevice &  d) {
		return ToGUIBase(d.get());
	}

	inline  GUIInputDeviceBase & ToGUIBase(mutabor::InputDevice & d) {
		return ToGUIBase(d.get());
	}

	inline  const GUIOutputDeviceBase & 
	ToGUIBase(const mutabor::OutputDevice & d) {
		return ToGUIBase(d.get());
	}

	inline  GUIOutputDeviceBase & ToGUIBase(mutabor::OutputDevice & d) {
		return ToGUIBase(d.get());
	}

	inline MutOutputDeviceShape * GUIDeviceFactory::CreateShape(
		mutabor::OutputDevice & device, wxWindow * parent) {
		int type = device->GetType();
		mutASSERT(type >= 0);
		if (factories.size() <= (size_t)type) {
			UNREACHABLECT(DeviceFactory);
			return NULL;
		}
		GUIDeviceFactory * factory = 
			dynamic_cast<GUIDeviceFactory *>(factories[type]);
		if (factory) 
			return factory->DoCreateShape(device, parent);
		else {
			UNREACHABLECT(GUIDeviceFactory);
			return NULL;
		}
	}

	inline MutInputDeviceShape * GUIDeviceFactory::CreateShape(
		mutabor::InputDevice & device, wxWindow * parent) {
		int type = device->GetType();
		mutASSERT(type >= 0);
		if (factories.size() <= (size_t)type) {
			UNREACHABLECT(DeviceFactory);
			return NULL;
		}
		GUIDeviceFactory * factory = 
			dynamic_cast<GUIDeviceFactory *>(factories[type]);
		if (factory) 
			return factory->DoCreateShape(device, parent);
		else {
			UNREACHABLECT(GUIDeviceFactory);
			return NULL;
		}
	}
			

}
#endif // precompiled
#endif
///\}
