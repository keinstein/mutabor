/** \file               -*- C++ -*-
 ********************************************************************
 * Interface to separate Mutabor functionality from the GUI
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/src/wxGUI/Routing/GUIRoute-inlines.h,v 1.5 2011/11/02 14:32:00 keinstein Exp $
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
 ********************************************************************
 * \addtogroup GUI
 * \{
 ********************************************************************/
// availlable groups: GUI, route, kernel, src/wxGUI, debug, docview

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

#include "src/kernel/Defs.h"
#include "src/kernel/routing/Route.h"
#include "src/wxGUI/Routing/GUIRoute.h"
#include "src/wxGUI/Routing/BoxShape.h"
#include "src/wxGUI/Routing/InputDeviceShape.h"
#include "src/wxGUI/Routing/OutputDeviceShape.h"
#ifdef DEBUG
#include "src/wxGUI/MutRouteWnd.h"
#endif

#include "src/kernel/routing/Route-inlines.h"


#ifndef MUWX_ROUTING_GUIROUTE_INLINES_H_PRECOMPILED
#define MUWX_ROUTING_GUIROUTE_INLINES_H_PRECOMPILED

// system headers which do seldom change

namespace mutaborGUI {


	using mutabor::connect;
	
	inline void connect(mutabor::Route & route, MutBoxChannelShape * shape) {
		if (!shape || !route) {
			UNREACHABLE;
			return;
		}
		
		GUIRouteBase * r = ToGUIBase(route.get());
		if (!r) {
			UNREACHABLE;
			return;
		}

		r->Add(shape);
		shape->Add(route);
		
		wxWindow * parent = shape->GetGrandParent();

		mutabor::OutputDevice out = route->GetOutputDevice();
		if (out) {
			MutOutputDeviceShape * outshape =
				ToGUIBase(out) -> GetShape(parent);
			if (outshape) {
				outshape->Add(shape);
				shape->Add(outshape);
			}
		}
		mutabor::InputDevice & in = 
			const_cast<mutabor::InputDevice &>(route->GetInputDevice());
		if (in) {
			MutInputDeviceShape * inshape =
				ToGUIBase(in) -> GetShape(parent);
			if (inshape) {
				inshape->Add(shape);
				shape->Add(inshape);
			}
		}
	}


	inline void connect(MutBoxChannelShape * channel, MutOutputDeviceShape * out) {
		if (!channel || !out)  {
			UNREACHABLE;
			return;
		}
		mutabor::Route r = channel->GetRoute();
		mutabor::OutputDevice dev = out->GetDevice();
		connect(r,dev);
	}

	template <class device_class, class shape_class>
	inline void connect_device_shape(device_class * dev, shape_class * shape) 
	{
 		TRACE;
		DEBUGLOG2(routing,_T("Disconnecting %p"),shape);
		if (!shape || !dev) {
			UNREACHABLE;
			return;
		}
		if (shape->GetDevice()) {
			UNREACHABLE;
			return;
		}

		dev->Add(shape);
		shape->Add(dev->GetDevice());

		wxWindow * parent = shape->GetParent();
		TRACE;
		const mutabor::routeListType & routes = dev -> GetDevice() -> GetRoutes();
		for (mutabor::routeListType::const_iterator 
			     route = routes.begin();
		     route != routes.end(); route++) {
			mutabor::Route & r = const_cast<mutabor::Route & >(*route);
			TRACE;
			MutBoxChannelShape * channel =
				ToGUIBase(r)->GetShape(parent);
			if (channel) {
				shape->Add(channel);
				TRACE;
				channel->Add(shape);
				TRACE;
			}
			
		}

	}
	inline void connect(GUIOutputDeviceBase * out, MutOutputDeviceShape * shape) {
		connect_device_shape(out,shape);
	}
	inline void connect(GUIInputDeviceBase * in, MutInputDeviceShape * shape) {
		connect_device_shape(in,shape);
	}
	inline void connect(mutabor::OutputDevice & d , MutOutputDeviceShape * shape) 
	{
		connect(ToGUIBase(d), shape);
	}

	inline void connect(mutabor::InputDevice & d , MutInputDeviceShape * shape) 
	{
		connect(ToGUIBase(d), shape);
	}


	inline void connect(MutBoxChannelShape * channel, MutInputDeviceShape * in) {
		if (!channel || !in)  {
			UNREACHABLE;
			return;
		}
		mutabor::Route r = channel->GetRoute();
		mutabor::InputDevice dev = in->GetDevice();
		return connect(r,dev);
	}

	inline bool disconnect(mutabor::Route & r, MutBoxChannelShape *  shape) {
		DEBUGLOG2(routing,_T("Disconnecting %p"),shape);
		if (!shape) {
			UNREACHABLE;
			return false;
		}
		bool retval = true; 
		
		MutInputDeviceShape * in = 
			shape -> GetInput();
 		if (retval && in) {
			DEBUGLOG2(routing,_T("Disconnecting %p from %p"),shape,in);
			DEBUGLOG2(smartptr,_T("R.Get(): %p (%d), removing in from shape"),
				 r.get(), 
				 intrusive_ptr_get_refcount(r.get()));
			retval = retval && shape->Remove(in);
			DEBUGLOG2(smartptr,_T("R.Get(): %p (%d), removing shape from in"),
				 r.get(), 
				 intrusive_ptr_get_refcount(r.get()));
			retval = retval && in->Remove(shape);
		}
		DEBUGLOG2(smartptr,_T("R.Get(): %p (%d), disconnecting shapes"),
			 r.get(), 
			 intrusive_ptr_get_refcount(r.get()));

		MutOutputDeviceShape * out = 
			shape -> GetOutput();
		if (retval && out) {
			DEBUGLOG2(routing,_T("Disconnecting %p from %p"),shape,out);
			retval = retval && shape->Remove(out);
			DEBUGLOG2(smartptr,_T("R.Get(): %p (%d), removed out from shap"),
				 r.get(), 
				 intrusive_ptr_get_refcount(r.get()));
			retval = retval && out->Remove(shape);
			DEBUGLOG2(smartptr,_T("R.Get(): %p (%d), removed shape from out"),
				 r.get(), 
				 intrusive_ptr_get_refcount(r.get()));
		}
		
		GUIRouteBase * route = ToGUIBase(r);
		DEBUGLOG2(routing,_T("Disconnecting %p from %p"),shape,route);
		if (retval && route) 
			retval = route->Remove(shape);
			DEBUGLOG2(smartptr,_T("Route: %p (%d), removed shape"),
				  r.get(), 
				  intrusive_ptr_get_refcount(r.get()));

		if (retval && r) {
			retval = shape->Remove(r);
			DEBUGLOG2(smartptr,_T("Route: %p (%d), removed from shape"),
				  r.get(), 
				  intrusive_ptr_get_refcount(r.get()));
		}
		if (!retval) 
			UNREACHABLE;
		return retval;
	}

	inline bool disconnect(MutBoxChannelShape * channel, MutOutputDeviceShape * out) {
		if (!channel || !out)  {
			UNREACHABLE;
			return false;
		}
		mutabor::Route r = channel->GetRoute();
		mutabor::OutputDevice dev = out->GetDevice();
		return disconnect(r,dev);
	}

	inline bool disconnect(MutBoxChannelShape * channel, MutInputDeviceShape * in) {
		if (!channel || !in)  {
			UNREACHABLE;
			return false;
		}
		mutabor::Route r = channel->GetRoute();
		mutabor::InputDevice dev = in->GetDevice();
		return disconnect(r,dev);
	}

	template <class device_class, class shape_class>
	inline bool disconnect_device_shape(device_class * dev, shape_class * shape) 
	{
 		TRACE;
		DEBUGLOG2(routing,_T("Disconnecting %p"),shape);
		if (!shape) {
			UNREACHABLE;
			return false;
		}
		bool retval = true; 
		const MutBoxChannelShapeList & channels = 
			shape->GetChannels();
		DEBUGLOG2(routing,_T("%d channels"), channels.size());
		MutBoxChannelShapeList::const_iterator i;
		while ( (i = channels.begin()) != channels.end()) {
			MutBoxChannelShape * channel = 
				const_cast<MutBoxChannelShape *>(*i);
			DEBUGLOG2(routing,_T("Disconnecting %p from %p"),
				 shape,channel);
			TRACE;
			retval = retval && shape -> Remove(channel);
			TRACE;
			retval = retval && channel -> Remove(shape);
		}

		DEBUGLOG2(routing,_T("Disconnecting %p from %p"),shape,dev);
 		TRACE;
		if (retval) 
			retval = dev->Remove(shape);
 		TRACE;

		// note: the shape keeps a smartptr to dev. So this
		// should be callde after the other Remove.
		if (retval)
			retval = shape->Remove(dev->GetDevice());
 		TRACE;
		if (!retval) 
			UNREACHABLE;
		return retval;
	}
	inline bool disconnect(GUIOutputDeviceBase * out, MutOutputDeviceShape * shape) {
		return disconnect_device_shape(out,shape);
	}
	inline bool disconnect(GUIInputDeviceBase * in, MutInputDeviceShape * shape) {
		return disconnect_device_shape(in,shape);
	}

#if 0
	inline bool disconnect(OutputDeviceClass * d , MutOutputDeviceShape * shape) 
	{
		OutputDevice dev(d);
		return disconnect(GUIOutputDeviceBase::GetGUIOutputDevice(dev), shape);
	}
#endif


	inline bool disconnect(mutabor::OutputDevice & d , MutOutputDeviceShape * shape) 
	{
		return disconnect(ToGUIBase(d), shape);
	}

	inline bool disconnect(mutabor::InputDevice & d , MutInputDeviceShape * shape) 
	{
		return disconnect(ToGUIBase(d), shape);
	}

	inline bool reconnect(mutabor::Route & route,
			      MutBoxShape * oldshape,
			      MutBoxShape * newshape) {
		mutASSERT(oldshape);
		mutASSERT(newshape);
		mutASSERT(route);
		return reconnect(route,
				 oldshape->GetBoxId(),
				 newshape->GetBoxId());
	}

	inline bool reconnect(GUIRoute * route,
			      MutBoxShape * oldshape,
			      MutBoxShape * newshape) {
		mutabor::Route r(route);
		return reconnect(r, oldshape, newshape);
	}

	inline bool reconnect(MutBoxChannelShape* channel, 
			      MutOutputDeviceShape* oldout, 
			      MutOutputDeviceShape* newout) {
		if (oldout && newout && channel) 
			return reconnect(channel->GetRoute(),
					 oldout->GetDevice(),
					 newout->GetDevice());
		else {
			UNREACHABLE;
			return false;
		}
	}
	inline bool reconnect(MutBoxChannelShape* channel, 
			      MutInputDeviceShape* oldin, 
			      MutInputDeviceShape* newin) {
		if (oldin && newin && channel) 
			return reconnect(channel->GetRoute(),
					 oldin->GetDevice(),
					 newin->GetDevice());
		else {
			UNREACHABLE;
			return false;
		}
	}

	inline void GUIRouteBase::Add (mutabor::OutputDevice & dev) {
		GUIOutputDeviceBase * outbase = ToGUIBase(dev);

		for (MutBoxChannelShapeList::iterator i = shapes.begin();
		     i != shapes.end();
		     i++) {

			MutOutputDeviceShape * shape = 
				outbase->GetShape((*i)->GetGrandParent());

			if (shape) {
				(*i)->Add(shape);
				break;
			}
		}
	}

	inline void GUIRouteBase::Add (mutabor::InputDevice & dev) {
		GUIInputDeviceBase * inbase = ToGUIBase(dev);

		for (MutBoxChannelShapeList::iterator i = shapes.begin();
		     i != shapes.end();
		     i++) {

			MutInputDeviceShape * shape = 
				inbase->GetShape((*i)->GetGrandParent());

			if (shape) {
				(*i)->Add(shape);
				break;
			}
		}
	}

	inline void  GUIRouteBase::Add (int boxid) 
	{
		// this can be more effective if the lists were ordered 
		// according to thir parents.
		

		mutASSERT(MIN_BOX <= boxid && boxid < MAX_BOX);
		DEBUGLOG(smartptr,_T("Route; %p (%d), atta(t)ching box %d"),
			 this, 
			 intrusive_ptr_get_refcount(GetRoute()),
			 boxid);
		const MutBoxShapeList & boxshapes = 
			BoxData::GetBox(boxid).GetBoxShapes();
		for (MutBoxChannelShapeList::const_iterator i = shapes.begin();
		     i != shapes.end();
		     i++) {
			wxWindow * parent = (*i)->GetGrandParent();
			for (MutBoxShapeList::const_iterator box
				     = boxshapes.begin();
			     box != boxshapes.end();
			     box++) {
				if ((*box)->GetParent() == parent) {
					MutBoxShape * boxshape = 
						const_cast<MutBoxShape *>(*box);
					boxshape->Add(*i);
					(*i)->Add(boxshape);
					break;
				}
			}
		}
		DEBUGLOG(smartptr,_T("Route; %p (%d), atta(t)ched box %d"),
			 this, 
			 intrusive_ptr_get_refcount(GetRoute()),
			 boxid);
	}

	inline bool GUIRouteBase::Replace (mutabor::OutputDevice & olddev,
					   mutabor::OutputDevice & newdev) 
	{

		// this can be more effective if the lists were ordered 
		// according to thir parents.
		
		bool retval = true;
		mutASSERT(olddev && newdev);
		DEBUGLOG(smartptr,_T("Route; %p (%d), reconnecting output device\
 from %p (%d) to %p (%d)"),
			 this, 
			 intrusive_ptr_get_refcount(GetRoute()),
			 olddev.get(),
			 intrusive_ptr_get_refcount(olddev.get()),
			 newdev.get(),
			 intrusive_ptr_get_refcount(newdev.get()));

		GUIOutputDeviceBase * oldbase = ToGUIBase(olddev);
		GUIOutputDeviceBase * newbase = ToGUIBase(newdev);
		for (MutBoxChannelShapeList::iterator i = shapes.begin();
		     i != shapes.end();
		     i++) {
			wxWindow * parent = (*i)->GetGrandParent();
			MutOutputDeviceShape * oldshape = oldbase->GetShape(parent);
			if (!oldshape) 
				UNREACHABLEC;

			MutOutputDeviceShape * newshape = newbase->GetShape(parent);
			if (!newshape) 
				UNREACHABLEC;

			retval = retval && oldshape && newshape;
			if (oldshape && newshape) {
				(*i) -> Replace(oldshape,newshape);
			} else if (oldshape) {
				(*i) -> Remove(oldshape);
			} else if (newshape) {
				(*i)->Add(newshape);
			}
		}
		DEBUGLOG(smartptr,_T("Route; %p (%d), reconnected output device\
 from %p (%d) to %p (%d)"),
			 this, 
			 intrusive_ptr_get_refcount(GetRoute()),
			 olddev.get(),
			 intrusive_ptr_get_refcount(olddev.get()),
			 newdev.get(),
			 intrusive_ptr_get_refcount(newdev.get()));

		return retval;
	}

	inline bool GUIRouteBase::Replace (mutabor::InputDevice & olddev,
					   mutabor::InputDevice & newdev) 
	{

		// this can be more effective if the lists were ordered 
		// according to thir parents.
		
		bool retval = true;
		mutASSERT(olddev && newdev);
		DEBUGLOG(smartptr,_T("Route; %p (%d), reconnecting input device\
 from %p (%d) to %p (%d)"),
			 this, 
			 intrusive_ptr_get_refcount(GetRoute()),
			 olddev.get(),
			 intrusive_ptr_get_refcount(olddev.get()),
			 newdev.get(),
			 intrusive_ptr_get_refcount(newdev.get()));

		GUIInputDeviceBase * oldbase = ToGUIBase(olddev);
		GUIInputDeviceBase * newbase = ToGUIBase(newdev);
		for (MutBoxChannelShapeList::iterator i = shapes.begin();
		     i != shapes.end();
		     i++) {
			wxWindow * parent = (*i)->GetGrandParent();
			MutInputDeviceShape * oldshape = oldbase->GetShape(parent);
			if (!oldshape) 
				UNREACHABLEC;

			MutInputDeviceShape * newshape = newbase->GetShape(parent);
			if (!newshape) 
				UNREACHABLEC;

			retval = retval && oldshape && newshape;
			if (oldshape && newshape) {
				(*i) -> Replace(oldshape,newshape);
			} else if (oldshape) {
				(*i) -> Remove(oldshape);
			} else if (newshape) {
				(*i)->Add(newshape);
			}
		}
		DEBUGLOG(smartptr,_T("Route; %p (%d), reconnected input device\
 from %p (%d) to %p (%d)"),
			 this, 
			 intrusive_ptr_get_refcount(GetRoute()),
			 olddev.get(),
			 intrusive_ptr_get_refcount(olddev.get()),
			 newdev.get(),
			 intrusive_ptr_get_refcount(newdev.get()));

		return retval;
	}

	inline bool GUIRouteBase::Replace (int oldboxid,
					   int newboxid)
	{

		// this can be more effective if the lists were ordered 
		// according to thir parents.
		
		mutASSERT(MIN_BOX <= oldboxid && oldboxid < MAX_BOX);
		mutASSERT(MIN_BOX <= newboxid && newboxid < MAX_BOX);
		bool retval = true;
		const MutBoxShapeList & oldboxshapes = 
			BoxData::GetBox(oldboxid).GetBoxShapes();
		const MutBoxShapeList & newboxshapes = 
			BoxData::GetBox(newboxid).GetBoxShapes();
		for (MutBoxChannelShapeList::iterator i = shapes.begin();
		     i != shapes.end();
		     i++) {
			bool oldfound = false;
			wxWindow * parent = (*i)->GetGrandParent();
			MutBoxShapeList::const_iterator oldbox;
			for (oldbox = oldboxshapes.begin();
			     oldbox != oldboxshapes.end();
			     oldbox++) {
				if ((*oldbox)->GetParent() == parent) {
					(*oldbox)->Remove(*i);
					oldfound = true;
					break;
				}
			}
			bool newfound = false;
			MutBoxShapeList::const_iterator newbox;
			for (newbox = newboxshapes.begin();
			     newbox != newboxshapes.end();
			     newbox++) {
				if ((*newbox)->GetParent() == parent) {
					(*newbox)->Add(*i);
					newfound = true;
					break;
				}
			}
			retval = retval && oldfound && newfound;
			if (oldfound && newfound) {
				(*i) -> Replace(*oldbox,*newbox);
			} else if (oldfound) {
				(*i) -> Remove(*oldbox);
			} else if (newfound) {
				(*i)->Add(*newbox);
			}
		}
		return retval;
	}

	inline bool GUIRouteBase::Remove (mutabor::OutputDevice & dev) 
	{

		// this can be more effective if the lists were ordered 
		// according to thir parents.
		
		bool retval = false;
		mutASSERT(dev);
		DEBUGLOG(smartptr,
			 _T("Route; %p (%d), deta(t)ching output device %p (%d)"),
			 this, 
			 intrusive_ptr_get_refcount(GetRoute()),
			 dev.get(),
			 intrusive_ptr_get_refcount(dev.get()));

		GUIOutputDeviceBase * outbase = ToGUIBase(dev);

		if (shapes.empty() && outbase -> GetShapes().empty()) 
			return true;

		for (MutBoxChannelShapeList::iterator i = shapes.begin();
		     i != shapes.end();
		     i++) {

			MutOutputDeviceShape * shape = 
				outbase->GetShape((*i)->GetGrandParent());
			if (shape) {
				(*i)->Remove(shape);
				retval = true;
				break;
			}
		}

		DEBUGLOG(smartptr,
			 _T("Route; %p (%d), deta(t)ched output device %p (%d)"),
			 this, 
			 intrusive_ptr_get_refcount(GetRoute()),
			 dev.get(),
			 intrusive_ptr_get_refcount(dev.get()));

		return retval;
	}

	inline bool GUIRouteBase::Remove (mutabor::InputDevice & dev) 
	{
		// this can be more effective if the lists were ordered 
		// according to thir parents.
		
		bool retval = false;
		mutASSERT(dev);
		DEBUGLOG(smartptr,
			 _T("Route; %p (%d), deta(t)ching input device %p (%d)"),
			 this, 
			 intrusive_ptr_get_refcount(GetRoute()),
			 dev.get(),
			 intrusive_ptr_get_refcount(dev.get()));

		GUIInputDeviceBase * inbase = ToGUIBase(dev);

		if (shapes.empty() && inbase -> GetShapes().empty()) 
			return true;

		for (MutBoxChannelShapeList::iterator i = shapes.begin();
		     i != shapes.end();
		     i++) {

			MutInputDeviceShape * shape = 
				inbase->GetShape((*i)->GetGrandParent());
			if (shape) {
				(*i)->Remove(shape);
				retval = true;
				break;
			}
		}

		DEBUGLOG(smartptr,
			 _T("Route; %p (%d), deta(t)ched input device %p (%d)"),
			 this, 
			 intrusive_ptr_get_refcount(GetRoute()),
			 dev.get(),
			 intrusive_ptr_get_refcount(dev.get()));

		return retval;
	}

	inline bool GUIRouteBase::Remove (int boxid) 
	{
		// this can be more effective if the lists were ordered 
		// according to thir parents.
		
		mutASSERT(MIN_BOX <= boxid && boxid < MAX_BOX);
		DEBUGLOG(smartptr,_T("Route; %p (%d), deta(t)ching box %d"),
			 this, 
			 intrusive_ptr_get_refcount(GetRoute()),
			 boxid);
		bool retval = true;
		const MutBoxShapeList & boxshapes =
			BoxData::GetBox(boxid).GetBoxShapes();
		for (MutBoxChannelShapeList::iterator i = shapes.begin();
		     i != shapes.end();
		     i++) {
			wxWindow * parent = (*i)->GetGrandParent();
			for (MutBoxShapeList::const_iterator box 
				     = boxshapes.begin();
			     box != boxshapes.end();
			     box++) {
				if ((*box)->GetParent() == parent) {
					(*box)->Remove(*i);
					(*i)->Remove(*box);
					break;
				} else retval = false;
			}
		}
		DEBUGLOG(smartptr,_T("Route; %p (%d), deta(t)ching box %d"),
			 this, 
			 intrusive_ptr_get_refcount(GetRoute()),
			 boxid);
		return retval;
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

#if 0
	inline bool GUIRouteBase::Delete(MutBoxChannelShape * shape) {
		if (!shape) {
			UNREACHABLEC;
			return false;
		}
		bool retval = Detatch(shape);
		if (retval) 
			shape -> Destroy();
	}

#endif
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

	/// add a new output device
	template<class T> 
	void GUIfiedRoute<T>::Add (mutabor::OutputDevice & out) {
		base::Add(out);
		GUIRouteBase::Add(out);
	}
	/// add a new input device
	template<class T> 
	void GUIfiedRoute<T>::Add (mutabor::InputDevice & in) {
		base::Add(in);
		GUIRouteBase::Add(in);
	}
	/// add a new box
	template<class T> 
	void GUIfiedRoute<T>::Add(int id) {
		base::Add(id);
		GUIRouteBase::Add(id);
	}
	/// replace an existing output device
	template<class T> 
	bool GUIfiedRoute<T>::Replace (mutabor::OutputDevice & olddev, 
		      mutabor::OutputDevice & newdev) {
		bool retval = base::Replace(olddev,newdev);
		if (retval) {
			retval = GUIRouteBase::Replace(olddev,newdev);
		}
		return retval;
	}
	/// replace an existing input device
	template<class T> 
	bool GUIfiedRoute<T>::Replace (mutabor::InputDevice & olddev, 
		      mutabor::InputDevice & newdev) {
		bool retval = GUIRouteBase::Replace(olddev,newdev);
		if (retval) 
			retval = base::Replace(olddev,newdev);
		return retval;
	}
	/// replace an existing box
	template<class T> 
	bool GUIfiedRoute<T>::Replace (int oldbox, int newbox) {
		bool retval = 
			GUIRouteBase::Replace(oldbox,newbox);
		if (retval) 
			retval = base::Replace(oldbox,newbox);
		return retval;
	}
	/// remove an existing output device
	template<class T> 
	bool GUIfiedRoute<T>::Remove (mutabor::OutputDevice & out) {
		bool retval = 
			GUIRouteBase::Remove(out);
		if (retval) 
			retval = base::Remove(out);
		return retval;
	}
	/// remove an existing input device
	template<class T> 
	bool GUIfiedRoute<T>::Remove (mutabor::InputDevice & in) {
		bool retval = 
			GUIRouteBase::Remove(in);
		if (retval)
			retval = base::Remove(in);
		return retval;
	}
	/// remov an existing box
	template<class T> 
	bool GUIfiedRoute<T>::Remove (int id) {
		bool retval =
			GUIRouteBase::Remove(id);
		if (retval)
			retval = base::Remove(id);
		return retval;
	}

	inline void GUIOutputDeviceBase::Add(mutabor::Route & route) {
		// this can be more effective if the lists were ordered 
		// according to thir parents.
		
		mutASSERT(route);
		DEBUGLOG(smartptr,_T("Route; %p (%d), atta(t)ching output device %p (%d)"),
			 route.get(), 
			 intrusive_ptr_get_refcount(route.get()),
			 GetDevice(),
			 intrusive_ptr_get_refcount(GetDevice()));

		GUIRouteBase * r = ToGUIBase(route);

		for (MutOutputDeviceShapeList::iterator out 
			     = shapes.begin();
		     out != shapes.end();
		     out++) {

			MutBoxChannelShape * rs = r->GetShape((*out)->GetParent());
			if (rs) {
				(*out)->Add(rs);
			}
		}

		DEBUGLOG(smartptr,_T("Route; %p (%d), atta(t)ched output device %p (%d)"),
			 route.get(), 
			 intrusive_ptr_get_refcount(route.get()),
			 GetDevice(),
			 intrusive_ptr_get_refcount(GetDevice()));	
	}

	inline bool GUIOutputDeviceBase::Replace(mutabor::Route & oldroute,mutabor::Route & newroute) {
		// this can be more effective if the lists were ordered 
		// according to thir parents.
		
		mutASSERT(oldroute);
		mutASSERT(newroute);

		GUIRouteBase * oldr = ToGUIBase(oldroute);
		GUIRouteBase * newr = ToGUIBase(newroute);

		bool retval = true;

		for (MutOutputDeviceShapeList::iterator out 
			     = shapes.begin();
		     out != shapes.end();
		     out++) {

			MutBoxChannelShape * oldrs = oldr->GetShape((*out)->GetParent());
			MutBoxChannelShape * newrs = newr->GetShape((*out)->GetParent());
			if (oldrs && newrs) {
				retval = (*out) -> Replace(oldrs,newrs);
			} else if (oldrs) {
				(*out) -> Remove(oldrs);
				retval = false;
			} else if (newrs) {
				(*out)->Add(newrs);
				retval = false;
			}
		}
		return retval;

 	}
	inline bool GUIOutputDeviceBase::Remove (mutabor::Route & route) 
	{
		// this can be more effective if the lists were ordered 
		// according to thir parents.
		
		bool retval = true;
		mutASSERT(route);
		DEBUGLOG(smartptr,
			 _T("Route; %p (%d), removing from output device %p (%d)"),
			 route.get(), 
			 intrusive_ptr_get_refcount(route.get()),
			 GetDevice(),
			 intrusive_ptr_get_refcount(GetDevice()));
		GUIRouteBase * r = ToGUIBase(route);
		if (!r) {
			UNREACHABLEC;
			return false;
		}
		for (MutOutputDeviceShapeList::iterator out 
			     = shapes.begin();
		     out != shapes.end();
		     out++) {
			MutBoxChannelShape * rs = r->GetShape((*out)->GetParent());
			if (rs) {
				(*out)->Remove(rs);
			} else retval = false;
		}
		DEBUGLOG(smartptr,
			 _T("Route; %p (%d) removed from output device %p (%d)"),
			 route.get(), 
			 intrusive_ptr_get_refcount(route.get()),
			 GetDevice(),
			 intrusive_ptr_get_refcount(GetDevice()));
		return retval;
	}


#if 0		
	template<class T> 
	inline connect
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

#endif

	/// add a route
	template<class T> 
	inline  void GUIfiedOutputDevice<T>::Add(mutabor::Route & route) {
		TRACEC;
		basetype::Add(route);
		TRACEC;
		GUIOutputDeviceBase::Add(route);
		TRACEC;
	}

	/// replace a route
	template<class T> 
	inline  bool GUIfiedOutputDevice<T>::Replace(mutabor::Route & oldroute, 
						     mutabor::Route & newroute) {
		TRACEC;
		bool retval = basetype::Replace(oldroute,newroute);
		TRACEC;
		if (retval) 
			retval = GUIOutputDeviceBase::Replace(oldroute,newroute);
		TRACEC;
		return retval;
	}
	/// remove a route
	template<class T> 
	inline  bool GUIfiedOutputDevice<T>::Remove(mutabor::Route & route) {
		TRACEC;
		bool retval = GUIOutputDeviceBase::Remove(route);
		TRACEC;
		if (retval) 
			retval = basetype::Remove(route);
		TRACEC;
		return retval;
	}

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
		
#if 0
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
	}
#endif

#if 0
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
#endif

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

	inline void GUIInputDeviceBase::Add(mutabor::Route & route) {
		// this can be more effective if the lists were ordered 
		// according to thir parents.
		
		mutASSERT(route);
		DEBUGLOG(smartptr,_T("Route; %p (%d), atta(t)ching input device %p (%d)"),
			 route.get(), 
			 intrusive_ptr_get_refcount(route.get()),
			 GetDevice(),
			 intrusive_ptr_get_refcount(GetDevice()));

		GUIRouteBase * r = ToGUIBase(route);

		for (MutInputDeviceShapeList::iterator in 
			     = shapes.begin();
		     in != shapes.end();
		     in++) {

			MutBoxChannelShape * rs = r->GetShape((*in)->GetParent());
			if (rs) {
				(*in)->Add(rs);
			}
		}

		DEBUGLOG(smartptr,_T("Route; %p (%d), atta(t)ched input device %p (%d)"),
			 route.get(), 
			 intrusive_ptr_get_refcount(route.get()),
			 GetDevice(),
			 intrusive_ptr_get_refcount(GetDevice()));	
	}


	inline bool GUIInputDeviceBase::Replace(mutabor::Route & oldroute,mutabor::Route & newroute) {
		// this can be more effective if the lists were ordered 
		// according to thir parents.
		
		mutASSERT(oldroute);
		mutASSERT(newroute);

		GUIRouteBase * oldr = ToGUIBase(oldroute);
		GUIRouteBase * newr = ToGUIBase(newroute);

		bool retval = true;

		for (MutInputDeviceShapeList::iterator in 
			     = shapes.begin();
		     in != shapes.end();
		     in++) {

			MutBoxChannelShape * oldrs = oldr->GetShape((*in)->GetParent());
			MutBoxChannelShape * newrs = newr->GetShape((*in)->GetParent());
			if (oldrs && newrs) {
				(*in) -> Replace(oldrs,newrs);
			} else if (oldrs) {
				(*in) -> Remove(oldrs);
				retval = false;
			} else if (newrs) {
				(*in)->Add(newrs);
				retval = false;
			}
		}

		return retval;

	}

	inline bool GUIInputDeviceBase::Remove (mutabor::Route & route) 
	{
		// this can be more effective if the lists were ordered 
		// according to thir parents.
		
		bool retval = true;
		mutASSERT(route);
		DEBUGLOG(smartptr,
			 _T("Route; %p (%d), removing from input device %p (%d)"),
			 route.get(), 
			 intrusive_ptr_get_refcount(route.get()),
			 GetDevice(),
			 intrusive_ptr_get_refcount(GetDevice()));
		GUIRouteBase * r = ToGUIBase(route);
		if (!r) {
			UNREACHABLEC;
			return false;
		}
		for (MutInputDeviceShapeList::iterator in 
			     = shapes.begin();
		     in != shapes.end();
		     in++) {
			MutBoxChannelShape * rs = r->GetShape((*in)->GetParent());
			if (rs) {
				(*in)->Remove(rs);
			} else retval = false;
		}
		DEBUGLOG(smartptr,
			 _T("Route; %p (%d) removed from input device %p (%d)"),
			 route.get(), 
			 intrusive_ptr_get_refcount(route.get()),
			 GetDevice(),
			 intrusive_ptr_get_refcount(GetDevice()));
		return retval;
	}


	/// add a route
	template<class T> 
	inline  void GUIfiedInputDevice<T>::Add(mutabor::Route & route) {
		basetype ::Add(route);
		GUIInputDeviceBase::Add(route);
	}

	/// replace a route
	template<class T> 
	inline  bool GUIfiedInputDevice<T>::Replace(mutabor::Route & oldroute, 
						  mutabor::Route & newroute) {
		bool retval = basetype::Replace(oldroute,newroute);
		if (retval) 
			retval = GUIInputDeviceBase::Replace(oldroute,newroute);
		return retval;
	}
	/// remove a route
	template<class T> 
	inline  bool GUIfiedInputDevice<T>::Remove(mutabor::Route & route) {
		bool retval = basetype::Remove(route);
		if (retval) 
			retval = GUIInputDeviceBase::Remove(route);
		return retval;
	}

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
		
#if 0

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
#endif
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

		
#if 0
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
#endif

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
