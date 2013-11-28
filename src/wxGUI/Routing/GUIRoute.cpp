/** \file               -*- C++ -*-
 ********************************************************************
 * Interface to separate Mutabor functionality from the GUI
 *
 * Copyright:   (c) 2011 TU Dresden
 *              changes after 2011-11 (c) by the authors
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
 *
 ********************************************************************
 * \addtogroup GUIroute
 * \{
 ********************************************************************/

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

#include "src/kernel/Defs.h"
#include "wx/string.h"
#include "wx/window.h"
#include "wx/msgdlg.h"
#include "src/kernel/routing/Route.h"
#include "src/wxGUI/Routing/GUIRoute.h"
#include "src/wxGUI/Routing/BoxChannelShape.h"
#include "src/wxGUI/Routing/DeviceShape.h"
#include "src/wxGUI/Routing/OutputMidiDeviceShape.h"
#include "src/wxGUI/Routing/OutputMidiDeviceShape.h"
#include "src/wxGUI/Routing/OutputMidiFileDeviceShape.h"
#include "src/wxGUI/Routing/OutputGuidoFileDeviceShape.h"
#include "src/wxGUI/Routing/InputMidiDeviceShape.h"
#include "src/wxGUI/Routing/InputMidiFileDeviceShape.h"
#include "src/wxGUI/Routing/InputGuidoFileDeviceShape.h"
#include "src/wxGUI/Routing/NewBoxShape.h"
#include "src/wxGUI/Routing/BoxShape.h"
#include "src/wxGUI/Routing/RouteLists.h"
#include "src/wxGUI/MutRouteWnd.h"
#include "src/wxGUI/MutFrame.h"
#include "src/wxGUI/StatusBar.h"


#include "src/kernel/routing/Route-inlines.h"
#include "src/wxGUI/GUIBoxData-inlines.h"
#include "src/wxGUI/Routing/GUIRoute-inlines.h"

using namespace mutabor;
namespace mutaborGUI {
#if 0
	void GUIRouteBase::Attatch (mutabor::OutputDevice & dev)
	{
		// this can be more effective if the lists were ordered
		// according to thir parents.

		mutASSERT(dev);
		DEBUGLOG(smartptr,_T("Route; %p (%d), atta(t)ching output device %p (%d)"),
			 route,
			 intrusive_ptr_get_refcount(route),
			 dev.get(),
			 intrusive_ptr_get_refcount(dev.get()));
		MutOutputDeviceShapeList & outshapes = ToGUIBase(dev).GetShapes();
		for (MutBoxChannelShapeList::iterator i = shapes.begin();
		     i != shapes.end();
		     i++) {
			wxWindow * parent = (*i)->GetGrandParent();
			for (MutOutputDeviceShapeList::iterator out
				     = outshapes.begin();
			     out != outshapes.end();
			     out++) {
				if ((*out)->GetParent() == parent) {
					(*out)->Add(*i);
					(*i)->Add(*out);
					break;
				}
			}
		}
		DEBUGLOG(smartptr,_T("Route; %p (%d), atta(t)ched output device %p (%d)"),
			 route,
			 intrusive_ptr_get_refcount(route),
			 dev.get(),
			 intrusive_ptr_get_refcount(dev.get()));
	}

	void  GUIRouteBase::Attatch (mutabor::InputDevice & dev)
	{
		// this can be more effective if the lists were ordered
		// according to thir parents.

		mutASSERT(dev);
		DEBUGLOG(smartptr,_T("Route; %p (%d), atta(t)ching input device %p (%d)"),
			 route,
			 intrusive_ptr_get_refcount(route),
			 dev.get(),
			 intrusive_ptr_get_refcount(dev.get()));
		MutInputDeviceShapeList & inshapes = ToGUIBase(dev).GetShapes();
		for (MutBoxChannelShapeList::iterator i = shapes.begin();
		     i != shapes.end();
		     i++) {
			wxWindow * parent = (*i)->GetGrandParent();
			for (MutInputDeviceShapeList::iterator in
				     = inshapes.begin();
			     in != inshapes.end();
			     in++) {
				if ((*in)->GetParent() == parent) {
					(*in)->Add(*i);
					(*i)->Add(*in);
					break;
				}
			}
		}
		DEBUGLOG(smartptr,_T("Route; %p (%d), atta(t)ed input device %p (%d)"),
			 route,
			 intrusive_ptr_get_refcount(route),
			 dev.get(),
			 intrusive_ptr_get_refcount(dev.get()));
	}

	void  GUIRouteBase::Attatch (int boxid)
	{
		// this can be more effective if the lists were ordered
		// according to thir parents.


		mutASSERT(MIN_BOX <= boxid && boxid < MAX_BOX);
		DEBUGLOG(smartptr,_T("Route; %p (%d), atta(t)ching box %d"),
			 route,
			 intrusive_ptr_get_refcount(route),
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
			 route,
			 intrusive_ptr_get_refcount(route),
			 boxid);
	}

	bool GUIRouteBase::Reconnect (mutabor::OutputDevice & olddev,
				      mutabor::OutputDevice & newdev)
	{

		// this can be more effective if the lists were ordered
		// according to thir parents.

		bool retval = true;
		mutASSERT(olddev && newdev);
		DEBUGLOG(smartptr,_T("Route; %p (%d), reconnecting output device\
 from %p (%d) to %p (%d)"),
			 route,
			 intrusive_ptr_get_refcount(route),
			 olddev.get(),
			 intrusive_ptr_get_refcount(olddev.get()),
			 newdev.get(),
			 intrusive_ptr_get_refcount(newdev.get()));
		MutOutputDeviceShapeList & oldoutshapes =
			ToGUIBase(olddev).GetShapes();
		MutOutputDeviceShapeList & newoutshapes =
			ToGUIBase(newdev).GetShapes();
		for (MutBoxChannelShapeList::iterator i = shapes.begin();
		     i != shapes.end();
		     i++) {
			bool oldfound = false;
			wxWindow * parent = (*i)->GetGrandParent();
			MutOutputDeviceShapeList::iterator oldout;
			for (oldout = oldoutshapes.begin();
			     oldout != oldoutshapes.end();
			     oldout++) {
				if ((*oldout)->GetParent() == parent) {
					(*oldout)->Remove(*i);
					oldfound = true;
					break;
				}
			}
			bool newfound = false;
			MutOutputDeviceShapeList::iterator newout;
			for (newout = newoutshapes.begin();
			     newout != newoutshapes.end();
			     newout++) {
				if ((*newout)->GetParent() == parent) {
					(*newout)->Add(*i);
					newfound = true;
					break;
				}
			}
			retval = retval && oldfound && newfound;
			if (oldfound && newfound) {
				(*i) -> Replace(*oldout,*newout);
			} else if (oldfound) {
				(*i) -> Remove(*oldout);
			} else if (newfound) {
				(*i)->Add(*newout);
			}
		}
		DEBUGLOG(smartptr,_T("Route; %p (%d), reconnected output device\
 from %p (%d) to %p (%d)"),
			 route,
			 intrusive_ptr_get_refcount(route),
			 olddev.get(),
			 intrusive_ptr_get_refcount(olddev.get()),
			 newdev.get(),
			 intrusive_ptr_get_refcount(newdev.get()));

		return retval;
	}

	bool GUIRouteBase::Reconnect (mutabor::InputDevice & olddev,
				      mutabor::InputDevice & newdev)
	{
		// this can be more effective if the lists were ordered
		// according to thir parents.

		// this can be more effective if the lists were ordered
		// according to thir parents.

		mutASSERT(olddev && newdev);
		DEBUGLOG(smartptr,_T("Route; %p (%d), reconnecting input device\
 from %p (%d) to %p (%d)"),
			 route,
			 intrusive_ptr_get_refcount(route),
			 olddev.get(),
			 intrusive_ptr_get_refcount(olddev.get()),
			 newdev.get(),
			 intrusive_ptr_get_refcount(newdev.get()));
		bool retval = true;
		MutInputDeviceShapeList & oldinshapes =
			ToGUIBase(olddev).GetShapes();
		MutInputDeviceShapeList & newinshapes =
			ToGUIBase(newdev).GetShapes();
		for (MutBoxChannelShapeList::iterator i = shapes.begin();
		     i != shapes.end();
		     i++) {
			bool oldfound = false;
			wxWindow * parent = (*i)->GetGrandParent();
			mutASSERT(dynamic_cast<MutRouteWnd *>(parent));
			MutInputDeviceShapeList::iterator oldin;
			for (oldin = oldinshapes.begin();
			     oldin != oldinshapes.end();
			     oldin++) {
				if ((*oldin)->GetParent() == parent) {
					(*oldin)->Remove(*i);
					oldfound = true;
					break;
				}
			}
			bool newfound = false;
			MutInputDeviceShapeList::iterator newin;
			for (newin = newinshapes.begin();
			     newin != newinshapes.end();
			     newin++) {
				if ((*newin)->GetParent() == parent) {
					(*newin)->Add(*i);
					newfound = true;
					break;
				}
			}
			retval = retval && oldfound && newfound;
			if (oldfound && newfound) {
				(*i) -> Replace(*oldin,*newin);
			} else if (oldfound) {
				(*i) -> Remove(*oldin);
			} else if (newfound) {
				(*i)->Add(*newin);
			}
		}
		DEBUGLOG(smartptr,_T("Route; %p (%d), reconnected input device\
 from %p (%d) to %p (%d)"),
			 route,
			 intrusive_ptr_get_refcount(route),
			 olddev.get(),
			 intrusive_ptr_get_refcount(olddev.get()),
			 newdev.get(),
			 intrusive_ptr_get_refcount(newdev.get()));
		return retval;
	}

	bool GUIRouteBase::Reconnect (int oldboxid,
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



	bool GUIRouteBase::Detatch (mutabor::OutputDevice & dev)
	{
		// this can be more effective if the lists were ordered
		// according to thir parents.

		bool retval = true;
		mutASSERT(dev);
		DEBUGLOG(smartptr,_T("Route; %p (%d), deta(t)ching output device\
 %p (%d)"),
			 route,
			 intrusive_ptr_get_refcount(route),
			 dev.get(),
			 intrusive_ptr_get_refcount(dev.get()));
		MutOutputDeviceShapeList & outshapes = ToGUIBase(dev).GetShapes();
		for (MutBoxChannelShapeList::iterator i = shapes.begin();
		     i != shapes.end();
		     i++) {
			wxWindow * parent = (*i)->GetGrandParent();
			for (MutOutputDeviceShapeList::iterator out
				     = outshapes.begin();
			     out != outshapes.end();
			     out++) {
				if ((*out)->GetParent() == parent) {
					(*out)->Remove(*i);
					(*i)->Remove(*out);
					break;
				} else retval = false;
			}
		}
		DEBUGLOG(smartptr,_T("Route; %p (%d), deta(t)ched output device\
 %p (%d)"),
			 route,
			 intrusive_ptr_get_refcount(route),
			 dev.get(),
			 intrusive_ptr_get_refcount(dev.get()));
		return retval;
	}

	bool  GUIRouteBase::Detatch (mutabor::InputDevice & dev)
	{
		// this can be more effective if the lists were ordered
		// according to thir parents.

		mutASSERT(dev);
		DEBUGLOG(smartptr,_T("Route; %p (%d), deta(t)ching input device\
 %p (%d)"),
			 route,
			 intrusive_ptr_get_refcount(route),
			 dev.get(),
			 intrusive_ptr_get_refcount(dev.get()));
		bool retval = true;
		MutInputDeviceShapeList & inshapes = ToGUIBase(dev).GetShapes();
		for (MutBoxChannelShapeList::iterator i = shapes.begin();
		     i != shapes.end();
		     i++) {
			wxWindow * parent = (*i)->GetGrandParent();
			for (MutInputDeviceShapeList::iterator in
				     = inshapes.begin();
			     in != inshapes.end();
			     in++) {
				if ((*in)->GetParent() == parent) {
					(*in)->Remove(*i);
					(*i)->Remove(*in);
					break;
				} else retval = false;
			}
		}
		DEBUGLOG(smartptr,
			 _T("Route; %p (%d), deta(t)ched input device %p (%d)"),
			 route,
			 intrusive_ptr_get_refcount(route),
			 dev.get(),
			 intrusive_ptr_get_refcount(dev.get()));
		return retval;
	}


	bool GUIRouteBase::Detatch (int boxid)
	{
		// this can be more effective if the lists were ordered
		// according to thir parents.

		mutASSERT(MIN_BOX <= boxid && boxid < MAX_BOX);
		DEBUGLOG(smartptr,_T("Route; %p (%d), deta(t)ching box %d"),
			 route,
			 intrusive_ptr_get_refcount(route),
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
			 route,
			 intrusive_ptr_get_refcount(route),
			 boxid);
		return retval;
	}
#endif


	void GUIRouteBase::Destroy() {
		Route r(GetRoute());
		DEBUGLOG(smartptr,_T("Route: %p (%d), disconnecting shapes"),
			 (void*)r.get(),
			 (int)intrusive_ptr_get_refcount(r.get()));
		MutBoxChannelShapeList::iterator i;
		while ( (i = shapes.begin()) != shapes.end()) {
			MutBoxChannelShape * shape = *i;
			DEBUGLOG(smartptr,_T("Route: %p (%d), disconnecting shapes"),
				 (void*)r.get(),
				 (int)intrusive_ptr_get_refcount(r.get()));
			disconnect(r,shape);
			DEBUGLOG(smartptr,_T("Route: %p (%d), disconnecting shapes"),
				 (void*)r.get(),
				 (int)intrusive_ptr_get_refcount(r.get()));
			shape -> Destroy();
			DEBUGLOG(smartptr,_T("Route: %p (%d), disconnecting shapes"),
				 (void*)r.get(),
				 (int)intrusive_ptr_get_refcount(r.get()));
		}
		DEBUGLOG(smartptr,_T("Route; %p (%d), disconnected shapes"),
			 (void*)r.get(),
			 (int)intrusive_ptr_get_refcount(r.get()));
//		box -> Detatch(route);
		r = NULL;
	}

	void GUIRouteBase::runtime_error(bool iswarning, const mutString& message, va_list & args) {
		wxString error = wxString::FormatV(message,args);
		wxMessageBox(error, iswarning?_("Warning"):_("Error"),
			     wxOK | (iswarning?wxICON_WARNING:wxICON_ERROR) );
	}


	template<class T>
	void GUIfiedRoute<T>::Destroy()
	{
//		int saveboxid = T::GetBox();
		DEBUGLOG(smartptr,_T("Route; %p (%d), saving pointer"),
			 (void*)this,
			 (int)intrusive_ptr_get_refcount(this));
		Route self(this); // prevent us from beeing deleted
		DEBUGLOG(smartptr,_T("Route; %p (%d), calling T::Destroy()"),
			 (void*) this,
			 (int)intrusive_ptr_get_refcount(this));
		// Disconnecting the Route before destroying the GUI
		// part is slow, but safe as this path must work
		// anyway.
		T::Destroy();
		DEBUGLOG(smartptr,_T("Route; %p (%d), destroying GUI"),
			 (void*)this,
			 (int)intrusive_ptr_get_refcount(this));
		GUIRouteBase::Destroy();    //
		mutASSERT(intrusive_ptr_get_refcount(this) <= 2);
		DEBUGLOG(smartptr,_T("Route; %p (%d), leaving function"),
			 (void*)this,
			 (int)intrusive_ptr_get_refcount(this));
//		BoxData::CloseRoute(saveboxid);
	}

	RouteClass * GUIRouteFactory::DoCreate() const
	{
		GUIRoute * r = new GUIRoute();
		if (r)
			return (r->GetRoute());
		else
			return NULL;
	}

	RouteClass * GUIRouteFactory::DoCreate(mutabor::InputDevice & in,
					       mutabor::OutputDevice & out,
					       mutabor::RouteType type,
					       int iFrom,
					       int iTo,
					       Box box,
					       bool active,
					       int oFrom,
					       int oTo,
					       bool oNoDrum/*,
							     mutabor::Route next*/) const
	{
		DEBUGLOG(smartptr,_T("input device %p (%d)"),
			 (void*)in.get(),
			 (int)intrusive_ptr_get_refcount(in.get()));
		DEBUGLOG(smartptr,_T("output device %p (%d)"),
			 (void*)out.get(),
			 (int)intrusive_ptr_get_refcount(out.get()));
		GUIRoute * r = new GUIRoute (in,out,type,
					     iFrom,iTo,
					     box,active,
					     oFrom,oTo,
					     oNoDrum/*,next*/);
		if (r) {
			DEBUGLOG(smartptr,_T("Route; %p (%d), created"),
				 (void*)r->GetRoute(),
				 (int)intrusive_ptr_get_refcount(r->GetRoute()));
			return (r->GetRoute());
		} else
			return NULL;
	}
#if 0
	MutBoxShape * GUIRouteFactory::DoCreateBoxShape(mutabor::Box & box,
							wxWindow * parent) const {
		MutBoxShape * shape;
		DEBUGLOG(routing,_T("Adding box shape for box %d (list of %d)"),
			 box,(int)ToGUIBase(box)->GetShapes().size());


		if (box == NULL)
			shape = new NewMutBoxShape(parent,wxID_ANY);
		else
			/** \todo implement ID sharing between the different
			    shapes of one common route */

			shape = new MutBoxShape(parent, wxID_ANY,box);

		DEBUGLOG(routing,_T("Added box shape for box %d (list of %d)"),
			 box,(int)BoxData::GetBox(box).GetBoxShapes().size());

		return shape;
	}
#endif

	MutBoxChannelShape *
	GUIRouteFactory::DoCreateBoxChannelShape(mutabor::Route & route,
						 wxWindow * parent) const {
		/** \todo implement ID sharing between the different
		    shapes of one common route */
		DEBUGLOG(smartptr,_T("Route; %p (%d), new shape"),
			 (void*)route.get(),
			 (int)intrusive_ptr_get_refcount(route.get()));

		mutASSERT(route);
		Box box = route->GetBox();
		MutBoxShape * boxshape = NULL;
		if (!box) {
			box = BoxFactory::Create(mutabor::NoBox);
			connect (route,box);
			boxshape = GUIBoxFactory::CreateBoxShape(box, parent);
			MutRouteWnd * root = dynamic_cast<MutRouteWnd *>(parent);
			root->AddBox(boxshape,MutBoxShape::GetSizerFlags());
		} else {
			boxshape = const_cast<MutBoxShape *>(ToGUIBase(box)->GetShape(parent));
		}
		MutBoxChannelShape * shape =
			new MutBoxChannelShape (boxshape,
						wxID_ANY,
						route);
                /* MutBoxChannelShape establishes the connection
		if (shape) {
			ToGUIBase(route).Attatch(shape);
		}
		*/
		DEBUGLOG(smartptr,_T("Route; %p (%d), shape created"),
			 (void*)route.get(),
			 (int)intrusive_ptr_get_refcount(route.get()));
		return shape;
	}

	void GUIOutputDeviceBase::Destroy() {
		TRACEC;
		OutputDevice Out(GetDevice());
		MutOutputDeviceShapeList::iterator i;
		while ((i = shapes.begin()) != shapes.end()) {
			MutOutputDeviceShape * shape = *i;
			TRACEC;
			disconnect(this,shape);
			TRACEC;
			shape -> Destroy();
		}
		TRACEC;
		Out = NULL;
		TRACEC;
	}

	void GUIOutputDeviceBase::runtime_error(bool iswarning, const mutString& message, va_list & args) {
		wxString error = wxString::FormatV(message,args);
		wxMessageBox(error, iswarning?_("Warning"):_("Error"),
			     wxOK | (iswarning?wxICON_WARNING:wxICON_ERROR) );
	}


	template<class T>
	void GUIfiedOutputDevice<T>::DisconnectFromAll() {
		TRACEC;
		basetype::DisconnectFromAll();

		GUIOutputDeviceBase::Destroy();
		TRACEC;
	}


	void GUIInputDeviceBase::Play() {
		StatusBar::AllSetPlaystate(StatusBar::Play);
		NotifyShapes();
	}

	void GUIInputDeviceBase::Stop() {
		StatusBar::AllSetPlaystate(StatusBar::Stop);
		NotifyShapes();
	}

	void GUIInputDeviceBase::Pause() {
		StatusBar::AllSetPlaystate(StatusBar::Pause);
		NotifyShapes();
	}

	bool GUIInputDeviceBase::Open() {
		NotifyShapes();
		return true;
	}

	void GUIInputDeviceBase::Close() {
		NotifyShapes();
	}


	void GUIInputDeviceBase::Destroy() {
		TRACEC;
		InputDevice In(GetDevice());
		MutInputDeviceShapeList::iterator i;
		while ((i = shapes.begin()) != shapes.end()) {
			MutInputDeviceShape * shape = *i;
			TRACEC;
			disconnect(this,shape);
			TRACEC;
			shape -> Destroy();
		}
		TRACEC;
		In = NULL;
		TRACEC;
	}

	void GUIInputDeviceBase::runtime_error(bool iswarning, const mutString& message, va_list & args) {
		wxString error = wxString::FormatV(message,args);
		wxMessageBox(error, iswarning?_("Warning"):_("Error"),
			     wxOK | (iswarning?wxICON_WARNING:wxICON_ERROR) );
	}

	void GUIInputDeviceBase::NotifyShapes()
	{
		wxCommandEvent event(wxEVT_COMMAND_MENU_SELECTED,
				     CM_DEVICE_STATE_CHANGED);
		for (MutInputDeviceShapeList::iterator i = shapes.begin();
		     i != shapes.end();
		     i++) {
			wxPostEvent(*i,event);
		}
	}

	template<class T>
	void GUIfiedInputDevice<T>::DisconnectFromAll() {
		TRACEC;
		basetype::DisconnectFromAll();
		TRACEC;
		GUIInputDeviceBase::Destroy();
		TRACEC;
	}

	GUIDeviceFactory::~GUIDeviceFactory() {}


	GUIMidiPortFactory::~GUIMidiPortFactory() {}


	mutabor::OutputDeviceClass * GUIMidiPortFactory::DoCreateOutput(const mutStringRef name,
									int id) const
	{
		TRACEC;
		GUIOutputMidiPort * port = new GUIOutputMidiPort(name,id);
		TRACEC;
		if (port)  {
			OutputDeviceClass * dev = port->GetDevice();
			TRACEC;
			if (LogicOn && !(dev->IsOpen()))
				dev->Open();
			return dev;
		} else
			return NULL;
	}


	mutabor::InputDeviceClass *  GUIMidiPortFactory::DoCreateInput (const mutStringRef name,
									MutaborModeType mode,
									int id) const
	{
		TRACEC;
		GUIInputMidiPort * port =
			new GUIInputMidiPort(name,mode,id);
		TRACEC;
		if (port)  {
			InputDeviceClass * dev = port->GetDevice();
			TRACEC;
			if (LogicOn && !(dev->IsOpen()))
				dev->Open();
			return dev;
		} else
			return NULL;
	}

	MutOutputDeviceShape *
	GUIMidiPortFactory::DoCreateShape(mutabor::OutputDevice & d,
					  wxWindow * parent) const
	{
		/** \todo implement ID sharing between the different
		    shapes of one common route */
		DEBUGLOG(routing,_T("Creating device shape"));
		mutASSERT (d);
		if (!d) return NULL;

		TRACEC;
		MutOutputMidiDeviceShape * shape =
			new MutOutputMidiDeviceShape(parent,wxID_ANY,d);
		TRACEC;
		return shape;
	}

	MutInputDeviceShape *
	GUIMidiPortFactory::DoCreateShape(mutabor::InputDevice & d,
					  wxWindow * parent) const
	{
		/** \todo implement ID sharing between the different
		    shapes of one common route */
		DEBUGLOG(routing,_T("Creating device shape"));
		mutASSERT (d);
		if (!d) return NULL;

		TRACEC;
		MutInputMidiDeviceShape * shape =
			new MutInputMidiDeviceShape(parent,wxID_ANY,d);
		TRACEC;
		return shape;
	}



	GUIMidiFileFactory::~GUIMidiFileFactory() {}

	mutabor::OutputDeviceClass * GUIMidiFileFactory::DoCreateOutput (const mutStringRef name,
									 int id) const
	{
		TRACEC;
		GUIOutputMidiFile * port = new GUIOutputMidiFile(name,id);
		TRACEC;
		if (port)  {
			OutputDeviceClass * dev = port->GetDevice();
			TRACEC;
			if (LogicOn && !(dev->IsOpen()))
				dev->Open();
			return dev;
		} else
			return NULL;
	}

	mutabor::InputDeviceClass * GUIMidiFileFactory::DoCreateInput (const mutStringRef name,
								       mutabor::MutaborModeType mode,
								       int id) const
	{
		TRACEC;
		GUIInputMidiFile * port =
			new GUIInputMidiFile(name,mode,id);
		TRACEC;
		if (port)  {
			InputDeviceClass * dev = port->GetDevice();
			TRACEC;
			if (LogicOn && !(dev->IsOpen()))
				dev->Open();
			return dev;
		} else
			return NULL;
	}

	MutInputDeviceShape *
	GUIMidiFileFactory::DoCreateShape(mutabor::InputDevice & d,
					  wxWindow * parent) const
	{
		DEBUGLOG(routing,_T("Creating device shape"));
		mutASSERT (d);
		if (!d) return NULL;

		MutInputMidiFileDeviceShape * shape =
			new MutInputMidiFileDeviceShape(parent,wxID_ANY,d);
		return shape;
	}

	MutOutputDeviceShape *
	GUIMidiFileFactory::DoCreateShape(mutabor::OutputDevice & d,
					  wxWindow * parent) const
	{
		DEBUGLOG(routing,_T("Creating device shape"));
		mutASSERT (d);
		if (!d) return NULL;

		MutOutputMidiFileDeviceShape * shape =
			new MutOutputMidiFileDeviceShape(parent,wxID_ANY,d);
		return shape;
	}


	GUIGisFactory::~GUIGisFactory() {}

	mutabor::OutputDeviceClass * GUIGisFactory::DoCreateOutput(const mutStringRef name,
								   int id) const
	{
		TRACEC;
		GUIOutputGis * port = new GUIOutputGis(name,id);
		TRACEC;
		if (port)  {
			OutputDeviceClass * dev = port->GetDevice();
			TRACEC;
			if (LogicOn && !(dev->IsOpen()))
				dev->Open();
			return dev;
		} else
			return NULL;
	}

	mutabor::InputDeviceClass * GUIGisFactory::DoCreateInput (const mutStringRef name,
								  mutabor::MutaborModeType mode,
								  int id) const
	{
		TRACEC;
		GUIInputGis * port = new GUIInputGis(name,
						     mode,
						     id);
		TRACEC;
		if (port)  {
			InputDeviceClass * dev = port->GetDevice();
			TRACEC;
			if (LogicOn && !(dev->IsOpen()))
				dev->Open();
			return dev;
		} else
			return NULL;
	}

	MutInputDeviceShape *
	GUIGisFactory::DoCreateShape(mutabor::InputDevice & d,
				     wxWindow * parent) const
	{
		DEBUGLOG(routing,_T("Creating device shape"));
		mutASSERT (d);
		if (!d) return NULL;

		MutInputGuidoFileDeviceShape * shape =
			new MutInputGuidoFileDeviceShape(parent,wxID_ANY,d);
		return shape;
	}

	MutOutputDeviceShape *
	GUIGisFactory::DoCreateShape(mutabor::OutputDevice & d,
				     wxWindow * parent) const
	{
		DEBUGLOG(routing,_T("Creating device shape"));
		mutASSERT (d);
		if (!d) return NULL;

		MutOutputGuidoFileDeviceShape * shape =
			new MutOutputGuidoFileDeviceShape(parent,wxID_ANY,d);
		return shape;
	}

	void InitGUIRouteFactories()
	{
		new GUIBoxFactory;
		new GUIRouteFactory;
		new GUIMidiPortFactory;
		new GUIMidiFileFactory;
		new GUIGisFactory;
	}
}

///\}
