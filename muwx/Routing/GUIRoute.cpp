/** \file               -*- C++ -*-
 ********************************************************************
 * Interface to separate Mutabor functionality from the GUI
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/muwx/Routing/GUIRoute.cpp,v 1.3 2011/09/30 18:07:05 keinstein Exp $
 * Copyright:   (c) 2011 TU Dresden
 * \author  Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 
 * $Date: 2011/09/30 18:07:05 $
 * \version $Revision: 1.3 $
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
 * $Log: GUIRoute.cpp,v $
 * Revision 1.3  2011/09/30 18:07:05  keinstein
 * * make compile on windows
 * * s/wxASSERT/mutASSERT/g to get assert handler completely removed
 * * add ax_boost_base for boost detection
 *
 * Revision 1.2  2011-09-29 05:26:59  keinstein
 * debug intrusive_ptr
 * fix storage and retrieving of input/output devices in treestorage
 * save maximum border size in icons
 * Apply the calculated offset in IconShape (box and box channels still missing)
 * Fix debug saving and restoring route information/route window on activation
 * Add wxWANTS_CHARS to MutEditWindow
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

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

#include "Defs.h"
#include "wx/string.h"
#include "wx/window.h"
#include "muwx/Routing/GUIRoute.h"
#include "muwx/Routing/BoxChannelShape.h"
#include "muwx/Routing/OutputDeviceShape.h"
#include "muwx/Routing/OutputMidiDeviceShape.h"
#include "muwx/Routing/OutputMidiDeviceShape.h"
#include "muwx/Routing/OutputMidiFileDeviceShape.h"
#include "muwx/Routing/OutputGuidoFileDeviceShape.h"
#include "muwx/Routing/InputMidiDeviceShape.h"
#include "muwx/Routing/InputMidiFileDeviceShape.h"
#include "muwx/Routing/InputGuidoFileDeviceShape.h"
#include "muwx/Routing/NewBoxShape.h"
#include "muwx/Routing/BoxShape.h"
#include "muwx/Routing/RouteLists.h"
#include "muwx/GUIBoxData-inlines.h"
#include "muwx/Routing/GUIRoute-inlines.h"
#include "muwx/MutRouteWnd.h"
#include "muwx/MutFrame.h"


using namespace mutabor;
namespace mutaborGUI {
	void GUIRouteBase::Attatch (mutabor::OutputDevice dev) 
	{
		// this can be more effective if the lists were ordered 
		// according to thir parents.
		
		mutASSERT(dev);
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
	}

	void  GUIRouteBase::Attatch (mutabor::InputDevice dev) 
	{
		// this can be more effective if the lists were ordered 
		// according to thir parents.
		
		mutASSERT(dev);
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
	}

	void  GUIRouteBase::Attatch (int boxid) 
	{
		// this can be more effective if the lists were ordered 
		// according to thir parents.
		

		mutASSERT(MIN_BOX <= boxid && boxid < MAX_BOX);
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
	}

	bool GUIRouteBase::Reconnect (mutabor::OutputDevice olddev,
				      mutabor::OutputDevice newdev) 
	{

		// this can be more effective if the lists were ordered 
		// according to thir parents.
		
		bool retval = true;
		mutASSERT(olddev && newdev);
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
		return retval;
	}

	bool GUIRouteBase::Reconnect (mutabor::InputDevice olddev,
				      mutabor::InputDevice newdev) 
	{
		// this can be more effective if the lists were ordered 
		// according to thir parents.
		
		// this can be more effective if the lists were ordered 
		// according to thir parents.
		
		mutASSERT(olddev && newdev);
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
 


	bool GUIRouteBase::Detatch (mutabor::OutputDevice dev) 
	{
		// this can be more effective if the lists were ordered 
		// according to thir parents.
		
		bool retval = true;
		mutASSERT(dev);
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
		return retval;
	}

	bool  GUIRouteBase::Detatch (mutabor::InputDevice dev) 
	{
		// this can be more effective if the lists were ordered 
		// according to thir parents.
		
		mutASSERT(dev);
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
		return retval;
	}
	

	bool GUIRouteBase::Detatch (int boxid) 
	{
		// this can be more effective if the lists were ordered 
		// according to thir parents.
		
		mutASSERT(MIN_BOX <= boxid && boxid < MAX_BOX);
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
		return retval;
	}

	void GUIRouteBase::Destroy() {
		MutBoxChannelShapeList::iterator i;
		while ( (i = shapes.begin()) != shapes.end()) {
			MutBoxChannelShape * shape = *i;
			shape -> Detatch(route);
			shape -> Destroy();
		}
//		box -> Detatch(route);
		route = NULL;
	}



	template<class T> 
	void GUIfyRoute<T>::Destroy() 
	{ 
		GUIRouteBase * gui = &GetGUIRoute();
		Route self(this); // prevent us from beeing deleted
		mutASSERT(gui);
		gui->Destroy();    //
		T::Destroy();
		SetGUIRoute(NULL); //
		delete gui;
		mutASSERT(intrusive_ptr_get_refcount(this) <= 2);
	}

	Route GUIRouteFactory::DoCreate() const
	{
		GUIRoute * r = new GUIRoute();
		if (r)
			return r->GetRoute();
		else 
			return NULL;
	}

	Route GUIRouteFactory::DoCreate(mutabor::InputDevice in,
					mutabor::OutputDevice out,
					mutabor::RouteType type,
					int iFrom,
					int iTo,
					int box,
					bool active,
					int oFrom,
					int oTo,
					bool oNoDrum/*,
						      mutabor::Route next*/) const
	{
		GUIRoute * r = new GUIRoute (in,out,type,
					     iFrom,iTo,
					     box,active,
					     oFrom,oTo,
					     oNoDrum/*,next*/);
		if (r)
			return r->GetRoute();
		else 
			return NULL;
	}

	MutBoxShape * GUIRouteFactory::DoCreateBoxShape(int box,
							wxWindow * parent) const {
		MutBoxShape * shape;	
		DEBUGLOG(routing,_T("Adding box shape for box %d (list of %d)"),
			 box,BoxData::GetBox(box).GetBoxShapes().size());
		
	
		if (box == NewBox) 
			shape = new NewMutBoxShape(parent,wxID_ANY);
		else
			/** \todo implement ID sharing between the different
			    shapes of one common route */
			    
			shape = new MutBoxShape(parent, wxID_ANY,box);

		DEBUGLOG(routing,_T("Added box shape for box %d (list of %d)"),
			 box,BoxData::GetBox(box).GetBoxShapes().size());

#if 0 // the box is registered during Create
		if (box >= 0) {
#ifdef DEBUG
			const MutBoxShapeList & list = 
				BoxData::GetBox(box).GetBoxShapes();
			MutBoxShapeList::const_iterator pos = 
				std::find(list.begin(),
					  list.end(),
					  shape);
			mutASSERT(pos == list.end());
#endif
			BoxData::GetBox(box).Attatch(shape);
		}
#endif
		return shape;
	}

	MutBoxChannelShape * 
	GUIRouteFactory::DoCreateBoxChannelShape(mutabor::Route route,
						 wxWindow * parent) const {
		/** \todo implement ID sharing between the different
		    shapes of one common route */
		MutBoxChannelShape * shape = 
			new MutBoxChannelShape (parent,wxID_ANY,route);
                /* MutBoxChannelShape establishes the connection
		if (shape) {
			ToGUIBase(route).Attatch(shape);
		}
		*/
		return shape;
	}

	void GUIOutputDeviceBase::Destroy() {
		MutOutputDeviceShapeList::iterator i;
		while ((i = shapes.begin()) != shapes.end()) {
			MutOutputDeviceShape * shape = *i;
			shape -> Detatch(device);
			shape -> Destroy();
		}
	}

	template<class T>
	void GUIfyOutputDevice<T>::Destroy() {
		GetGUIDevice().Destroy();
		basetype::Destroy();
	}

	void GUIInputDeviceBase::Destroy() {
		MutInputDeviceShapeList::iterator i;
		while ((i = shapes.begin()) != shapes.end()) {
			MutInputDeviceShape * shape = *i;
			shape -> Detatch(device);
			shape -> Destroy();
		}
	}

	template<class T>
	void GUIfyInputDevice<T>::Destroy() {
		GetGUIDevice().Destroy();
		T::Destroy();
	}

	GUIDeviceFactory::~GUIDeviceFactory() {}

#if 0

	OutputDevice GUIDeviceFactory::DoCreateOutput () const
	{
		return new GUIOutputDevice();
	}

	OutputDevice GUIDeviceFactory::DoCreateOutput (const mutStringRef name, 
					       int id) const
	{
		return new GUIOutputDevice(name,id);
	}

	OutputDevice GUIDeviceFactory::DoCreateOutput (int devId,
						      mutString name, 
						      MutaborModeType mode, 
						      int id) const
	{
 		STUBC;
		return NULL;

		GUIOutputDevice * port = new GUIOutputDevice(name,devId);
		port->Device::SetId(id);
		switch (mode) {
		case DevicePause:
		case DeviceStop:
		case DevicePlay:
			port -> Open() ; 
			break;
		case DeviceUnregistered:
		case DeviceCompileError:
		case DeviceTimingError:
		default:
			UNREACHABLEC;
		}
		return port;
	}


	InputDevice GUIDeviceFactory::DoCreateInput () const
		
	{
		return new GUIInputDevice();
	}

	InputDevice GUIDeviceFactory::DoCreateInput ( const mutStringRef name, 
					    int id) const
	{
		return new GUIInputDevice(name,id);
	}

	InputDevice GUIDeviceFactory::DoCreateInput (int devId,
					   mutString name, 
					   MutaborModeType mode, 
					   int id) const
	{
 		STUBC;
		return NULL;

		return new GUIInputDevice(name,devId);
	}
#endif




	GUIMidiPortFactory::~GUIMidiPortFactory() {}


		

	mutabor::OutputDevice GUIMidiPortFactory::DoCreateOutput () const
	{
		GUIOutputMidiPort * port = new GUIOutputMidiPort();
		if (port) {
			OutputDevice dev = port->GetDevice();
			if (LogicOn && !(dev->IsOpen())) 
				dev->Open();
			return dev;
		} else 
			return NULL;
	}

	mutabor::OutputDevice GUIMidiPortFactory::DoCreateOutput(int devId,
							  const mutStringRef name, 
							  int id) const
	{
		GUIOutputMidiPort * port = new GUIOutputMidiPort(devId,name,id);
		if (port)  {
			OutputDevice dev = port->GetDevice();
			if (LogicOn && !(dev->IsOpen())) 
				dev->Open();
			return dev;
		} else 
			return NULL;
	}

	mutabor::OutputDevice GUIMidiPortFactory::DoCreateOutput (int devId,
							   const mutStringRef name, 
							   MutaborModeType mode, 
							   int id) const
	{
 		STUBC;
		return NULL;
#if 0
		GUIOutputMidiPort * port = new GUIOutputMidiPort(name,devId);
		port->MidiPort::SetId(id);
		switch (mode) {
		case MutaborMidiPortPause:
		case MutaborMidiPortStop:
		case MutaborMidiPortPlay:
			port -> Open() ; 
			break;
		case MutaborMidiPortUnregistered:
		case MutaborMidiPortCompileError:
		case MutaborMidiPortTimingError:
		default:
			UNREACHABLEC;
		}
		return port;
#endif
	}


	mutabor::InputDevice GUIMidiPortFactory::DoCreateInput () const
		
	{
		GUIInputMidiPort * port = new GUIInputMidiPort();
		if (port) { 
			InputDevice dev = port->GetDevice();
			if (LogicOn && !(dev->IsOpen())) 
				dev->Open();
			return dev;
		} else 
			return NULL;
	}

	mutabor::InputDevice GUIMidiPortFactory::DoCreateInput (int devId,
								const mutStringRef name, 
								int id) const
	{
		GUIInputMidiPort * port = 
			new GUIInputMidiPort(devId,name,
					     mutabor::DeviceStop,id);
		if (port)  {
			InputDevice dev = port->GetDevice();
			if (LogicOn && !(dev->IsOpen())) 
				dev->Open();
			return dev;
		} else 
			return NULL;
	}

	mutabor::InputDevice GUIMidiPortFactory::DoCreateInput (int devId,
							 const mutStringRef name, 
							 MutaborModeType mode, 
							 int id) const
	{
 		STUBC;
		return NULL;
	}

	MutOutputDeviceShape * 
	GUIMidiPortFactory::DoCreateShape(mutabor::OutputDevice d,
					  wxWindow * parent) const
	{
		/** \todo implement ID sharing between the different
		    shapes of one common route */
		DEBUGLOG(routing,_T("Creating device shape"));
		mutASSERT (d);
		if (!d) return NULL;

		MutOutputMidiDeviceShape * shape = 
			new MutOutputMidiDeviceShape(parent,wxID_ANY,d);
		return shape;
	}

	MutInputDeviceShape * 
	GUIMidiPortFactory::DoCreateShape(mutabor::InputDevice d,
					  wxWindow * parent) const
	{
		/** \todo implement ID sharing between the different
		    shapes of one common route */
		DEBUGLOG(routing,_T("Creating device shape"));
		mutASSERT (d);
		if (!d) return NULL;

		MutInputMidiDeviceShape * shape = 
			new MutInputMidiDeviceShape(parent,wxID_ANY,d);
		return shape;
	}



	GUIMidiFileFactory::~GUIMidiFileFactory() {}

	mutabor::OutputDevice GUIMidiFileFactory::DoCreateOutput () const
	{
		GUIOutputMidiFile * port = new GUIOutputMidiFile();
		if (port)  {
			OutputDevice dev = port->GetDevice();
			if (LogicOn && !(dev->IsOpen())) 
				dev->Open();
			return dev;
		} else 
			return NULL;
	}

	mutabor::OutputDevice GUIMidiFileFactory::DoCreateOutput (int devId,
							   const mutStringRef name, 
							   int id) const
	{
		GUIOutputMidiFile * port = new GUIOutputMidiFile(devId,name,id);
		if (port)  {
			OutputDevice dev = port->GetDevice();
			if (LogicOn && !(dev->IsOpen())) 
				dev->Open();
			return dev;
		} else 
			return NULL;
	}

	mutabor::OutputDevice GUIMidiFileFactory::DoCreateOutput (int devId,
							   const mutStringRef name, 
							   mutabor::MutaborModeType mode, 
							   int id) const
	{
 		STUBC;
		return NULL;
#if 0
		GUIOutputMidiFile * port = new GUIOutputMidiFile(name,devId);
		port->MidiFile::SetId(id);
		switch (mode) {
		case MutaborMidiFilePause:
		case MutaborMidiFileStop:
		case MutaborMidiFilePlay:
			port -> Open() ; 
			break;
		case MutaborMidiFileUnregistered:
		case MutaborMidiFileCompileError:
		case MutaborMidiFileTimingError:
		default:
			UNREACHABLEC;
		}
		return port;
#endif
	}


	mutabor::InputDevice GUIMidiFileFactory::DoCreateInput () const
		
	{
		GUIInputMidiFile * port = new GUIInputMidiFile();
		if (port)  {
			InputDevice dev = port->GetDevice();
			if (LogicOn && !(dev->IsOpen())) 
				dev->Open();
			return dev;
		} else 
			return NULL;
	}

	mutabor::InputDevice GUIMidiFileFactory::DoCreateInput (int devId,
							   const mutStringRef name, 
							   int id) const
	{
		GUIInputMidiFile * port = new GUIInputMidiFile(devId,name,
							       mutabor::DeviceStop,id);
		if (port)  {
			InputDevice dev = port->GetDevice();
			if (LogicOn && !(dev->IsOpen())) 
				dev->Open();
			return dev;
		} else 
			return NULL;
	}

	mutabor::InputDevice GUIMidiFileFactory::DoCreateInput (int devId,
							   const mutStringRef name, 
							   mutabor::MutaborModeType mode, 
							   int id) const
	{
 		STUBC;
		return NULL;
	}


	MutInputDeviceShape * 
	GUIMidiFileFactory::DoCreateShape(mutabor::InputDevice d,
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
	GUIMidiFileFactory::DoCreateShape(mutabor::OutputDevice d,
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

	mutabor::OutputDevice GUIGisFactory::DoCreateOutput () const
	{
		GUIOutputGis * port = new GUIOutputGis();
		if (port)  {
			OutputDevice dev = port->GetDevice();
			if (LogicOn && !(dev->IsOpen())) 
				dev->Open();
			return dev;
		} else 
			return NULL;
	}

	mutabor::OutputDevice GUIGisFactory::DoCreateOutput(int devId,
						const mutStringRef name, 
						int id) const
	{
		GUIOutputGis * port = new GUIOutputGis(devId,name,id);
		if (port)  {
			OutputDevice dev = port->GetDevice();
			if (LogicOn && !(dev->IsOpen())) 
				dev->Open();
			return dev;
		} else 
			return NULL;
	}

	mutabor::OutputDevice GUIGisFactory::DoCreateOutput (int devId,
							     const mutStringRef name, 
							     mutabor::MutaborModeType mode, 
							     int id) const
	{
 		STUBC;
		return NULL;
#if 0
		GUIOutputGis * port = new GUIOutputGis(name,devId);
		port->Gis::SetId(id);
		switch (mode) {
		case MutaborGisPause:
		case MutaborGisStop:
		case MutaborGisPlay:
			port -> Open() ; 
			break;
		case MutaborGisUnregistered:
		case MutaborGisCompileError:
		case MutaborGisTimingError:
		default:
			UNREACHABLEC;
		}
		return port;
#endif
	}


	mutabor::InputDevice GUIGisFactory::DoCreateInput () const
		
	{
		GUIInputGis * port = new GUIInputGis();
		if (port)  {
			InputDevice dev = port->GetDevice();
			if (LogicOn && !(dev->IsOpen())) 
				dev->Open();
			return dev;
		} else 
			return NULL;
	}

	mutabor::InputDevice GUIGisFactory::DoCreateInput (int devId,
					       const mutStringRef name, 
					       int id) const
	{
		GUIInputGis * port = new GUIInputGis(devId,name,
						     mutabor::DeviceStop,
						     id);
		if (port)  {
			InputDevice dev = port->GetDevice();
			if (LogicOn && !(dev->IsOpen())) 
				dev->Open();
			return dev;
		} else 
			return NULL;
	}

	mutabor::InputDevice GUIGisFactory::DoCreateInput (int devId,
					       const mutStringRef name, 
					       mutabor::MutaborModeType mode, 
					       int id) const
	{
 		STUBC;
		return NULL;
	}

	MutInputDeviceShape * 
	GUIGisFactory::DoCreateShape(mutabor::InputDevice d,
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
	GUIGisFactory::DoCreateShape(mutabor::OutputDevice d,
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
		new GUIRouteFactory;
		new GUIMidiPortFactory;
		new GUIMidiFileFactory;
		new GUIGisFactory;
	}
}

///\}
