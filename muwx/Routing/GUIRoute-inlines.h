/** \file               -*- C++ -*-
 ********************************************************************
 * Interface to separate Mutabor functionality from the GUI
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/muwx/Routing/GUIRoute-inlines.h,v 1.1 2011/09/27 20:13:24 keinstein Exp $
 * Copyright:   (c) 2011 TU Dresden
 * \author  Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 
 * $Date: 2011/09/27 20:13:24 $
 * \version $Revision: 1.1 $
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
 * Revision 1.1  2011/09/27 20:13:24  keinstein
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

#include "Defs.h"
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
		wxASSERT(oldshape);
		wxASSERT(newshape);
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
			wxASSERT(ok);
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
		shape->Add(route);
		
		wxWindow * parent = shape->GetGrandParent();
		wxASSERT(route);
		mutabor::OutputDevice out = route->GetOutputDevice();
		if (out) {
			MutOutputDeviceShape * outshape =
				ToGUIBase(out).GetShape(parent);
			if (outshape) {
				outshape->Add(shape);
				shape->Add(outshape);
			}
			
		}
		mutabor::InputDevice in = route->GetInputDevice();
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
			retval = retval && shape->Remove(in);
			retval = retval && in->Remove(shape);
		}

		MutOutputDeviceShape * out = 
			shape -> GetOutput();
		if (retval && out) {
			DEBUGLOG(routing,_T("Disconnecting %p from %p"),shape,out);
			retval = retval && shape->Remove(out);
			retval = retval && out->Remove(shape);
		}
		
		DEBUGLOG(routing,_T("Disconnecting %p from %p"),shape,route.get());
		if (retval) 
			retval = retval && Remove(shape);

		if (retval)
			retval = retval &&  shape->Remove(route);
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
	inline void GUIfyRoute<T>::Attatch (mutabor::OutputDevice dev) {
		T::Attatch(dev);
		GetGUIRoute().Attatch(dev);
	}

	template<class T> 
	inline void GUIfyRoute<T>::Attatch (mutabor::InputDevice dev) {
		T::Attatch(dev);
		GetGUIRoute().Attatch(dev);
	}
	template<class T> 
	inline void GUIfyRoute<T>::Attatch (int boxid) {
		T::Attatch(boxid);
		GetGUIRoute().Attatch(boxid);
	}

	template<class T> 
	inline bool GUIfyRoute<T>::Reconnect(mutabor::OutputDevice olddev, 
				       mutabor::OutputDevice newdev){
		bool retval = T::Reconnect(olddev, newdev);
		if (retval)
			retval = retval && GetGUIRoute().Reconnect(olddev, newdev);
		return retval;
	}
	template<class T> 
	inline bool GUIfyRoute<T>::Reconnect (mutabor::InputDevice olddev,
					      mutabor::InputDevice newdev) {
		bool retval = T::Reconnect(olddev, newdev);
		if (retval)
			retval = retval && GetGUIRoute().Reconnect(olddev, newdev);
		return retval;
	}
	template<class T> 
	inline bool GUIfyRoute<T>::Reconnect (int oldboxid,
					      int newboxid) {
		bool retval = T::Reconnect(oldboxid, newboxid);
		if (retval)
			retval = retval && GetGUIRoute().Reconnect(oldboxid, 
								   newboxid);
		return retval;
	}

	template<class T> 
	inline bool GUIfyRoute<T>::Detatch (mutabor::OutputDevice dev) {
		bool retval = T::Detatch(dev);
		if (retval)
			retval = retval && GetGUIRoute().Detatch(dev);
		return retval;
	}
	template<class T> 
	inline bool GUIfyRoute<T>::Detatch (mutabor::InputDevice dev) {
		bool retval = T::Detatch(dev);
		if (retval)
			retval &= GetGUIRoute().Detatch(dev);
		return retval;
	}
	template<class T> 
	inline bool GUIfyRoute<T>::Detatch (int boxid) {
		bool retval = T::Detatch(boxid);
		if (retval)
			retval &= GetGUIRoute().Detatch(boxid);
		return retval;
	}

#if 0
	/// add a route
	template<class T> 
	inline  void GUIfyOutputDevice<T>::Add(Route route) {
		T::Add(route);
		GetGUIDevice().Add(route);
	}

	/// replace a route
	template<class T> 
	inline  bool GUIfyOutputDevice<T>::Replace(Route oldroute, 
						   Route newroute) {
		bool retval = T::Replace(oldroute,newroute);
		if (retval) 
			retval = GetGUIDevice().Replace(oldroute,newroute);
		return retval;
	}
	/// remove a route
	template<class T> 
	inline  bool GUIfyOutputDevice<T>::Remove(Route route) {
		bool retval = T::Remove(route);
		if (retval) 
			retval = GetGUIDevice().Remove(route);
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
			wxASSERT(ok);
			if (ok)
				shapes.erase(pos);
		} else {
			UNREACHABLEC;
			ok = false;
		}
		return ok;
	}
		
	inline void GUIOutputDeviceBase::Attatch(MutOutputDeviceShape * shape) {
		if (!shape) {
			UNREACHABLEC;
			return;
		}
		Add(shape);
		shape->Add(device);

		wxWindow * parent = shape->GetParent();
		wxASSERT(device);
		const mutabor::routeListType & routes = device -> GetRoutes();
		for (typename mutabor::routeListType::const_iterator 
			     route = routes.begin();
		     route != routes.end(); route++) {
			MutBoxChannelShape * channel =
				ToGUIBase(*route).GetShape(parent);
			if (channel) {
				shape->Add(channel);
				channel->Add(shape);
			}
			
		}
		
	}

	inline bool GUIOutputDeviceBase::Detatch(MutOutputDeviceShape * shape) {
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
			retval = retval && shape -> Remove(channel);
			retval = retval && channel -> Remove(shape);
		}

		DEBUGLOG(routing,_T("Disconnecting %p from %p"),shape,this);
		if (retval) 
			retval = retval && Remove(shape);
		if (retval)
			retval = retval && shape->Remove(device);
		if (!retval) 
			UNREACHABLEC;
		return retval;
	}

	inline bool GUIOutputDeviceBase::Delete(MutOutputDeviceShape * shape) {
		if (!shape) {
			UNREACHABLEC;
			return false;
		}
		bool retval = Detatch(shape);
		if (retval) 
			shape -> Destroy();
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
	inline  void GUIfyInputDevice<T>::Add(Route route) {
		T::Add(route);
		GetGUIDevice().Add(route);
	}

	/// replace a route
	template<class T> 
	inline  bool GUIfyInputDevice<T>::Replace(Route oldroute, 
						   Route newroute) {
		bool retval = T::Replace(oldroute,newroute);
		if (retval) 
			retval = GetGUIDevice().Replace(oldroute,newroute);
		return retval;
	}
	/// remove a route
	template<class T> 
	inline  bool GUIfyInputDevice<T>::Remove(Route route) {
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
			wxASSERT(ok);
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
		Add(shape);
		shape->Add(device);

		/** see output device */
		wxWindow * parent = shape->GetParent();
		wxASSERT(device);
		const mutabor::routeListType & routes = device -> GetRoutes();
		for (typename mutabor::routeListType::const_iterator 
			     route = routes.begin();
		     route != routes.end(); route++) {
			MutBoxChannelShape * channel =
				ToGUIBase(*route).GetShape(parent);
			if (channel) {
				shape->Add(channel);
				channel->Add(shape);
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
			retval = retval && shape -> Remove(channel);
			retval = retval && channel -> Remove(shape);
		}

		DEBUGLOG(routing,_T("Disconnecting %p from %p"),shape,this);
		
		if (retval) 
			retval = retval && Remove(shape);
		if (retval)
			retval = retval && shape->Remove(device);
		if (!retval) 
			UNREACHABLEC;
		return retval;
	}
	inline bool GUIInputDeviceBase::Delete(MutInputDeviceShape * shape) {
		if (!shape) {
			UNREACHABLEC;
			return false;
		}
		bool retval = Detatch(shape);
		if (retval) 
			shape -> Destroy();
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

		

	inline  GUIInputDeviceBase & ToGUIBase(mutabor::InputDevice d) {
		wxASSERT((GUIfiedInputDevice *)(d.get()));
		wxASSERT((((GUIfiedInputDevice *)(d.get()))
			  -> GetGUIDevice()).IsDevice(d));
		
		return ((GUIfiedInputDevice *)(d.get()))
			-> GetGUIDevice();
	}

	inline  GUIOutputDeviceBase & ToGUIBase(mutabor::OutputDevice d) {
		wxASSERT((GUIfiedOutputDevice *)(d.get()));
		wxASSERT((((GUIfiedOutputDevice *)(d.get()))
			  -> GetGUIDevice()).IsDevice(d));
		
		return ((GUIfiedOutputDevice *)(d.get()))
			-> GetGUIDevice();
	}

	inline MutOutputDeviceShape * GUIDeviceFactory::CreateShape(
		mutabor::OutputDevice device, wxWindow * parent) {
		int type = device->GetType();
		wxASSERT(type >= 0);
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
		mutabor::InputDevice device, wxWindow * parent) {
		int type = device->GetType();
		wxASSERT(type >= 0);
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
