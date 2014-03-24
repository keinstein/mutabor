/** \file 
 ********************************************************************
 * Debug functions for routing system
 *
 * Copyright:   (c) 2010 TU Dresden
 *              Changes after 2011-11 (c) Tobias Schlemmer
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
 ********************************************************************
 * \addtogroup debug
 * \{
 ********************************************************************/

#include "src/kernel/Defs.h"
#ifdef DEBUG
#include "src/wxGUI/Routing/DebugRoute.h"
#include "src/kernel/routing/Device.h"
#include "src/wxGUI/Routing/DeviceShape.h"
#include "src/wxGUI/MutRouteWnd.h"
#include "src/wxGUI/Routing/BoxShape.h"
#include "src/wxGUI/Routing/GUIRoute-inlines.h"
#include "src/wxGUI/Routing/BoxChannelShape.h"
#include "src/wxGUI/Routing/BoxShape.h"
#include "src/wxGUI/GUIBoxData-inlines.h"

#include "src/kernel/routing/Route-inlines.h"

#include <boost/exception/diagnostic_information.hpp>

#include <set>
#include <algorithm>

#ifndef no_wxGUI
#define wxGUI 1
#else 
#define wxGUI 0
#endif


using namespace mutabor;
namespace mutaborGUI {

#if wxGUI
	typedef std::set<MutRouteWnd *> rwdset;
	static rwdset rwdtoplevels;
#endif

#if 0
	static void CheckOutputDevice(const OutputDevice Out, 
				      const MutBoxChannelShape * channel) 
	{
		DEBUGLOG2(routing,("Output device %p, Channel %p"),Out.get(),channel);
		MutOutputDeviceShapeList & shapes = ToGUIBase(Out).GetShapes();
		bool noshape = true;
		for (MutOutputDeviceShapeList::const_iterator si = shapes.begin();
		     si != shapes.end(); si++) {
			MutOutputDeviceShape * shape = *si;
			mutASSERT ((channel && shape) || !(channel || shape));
			bool found = false;
			const MutBoxChannelShapeList & list = 
				shape->getRoutesList();
			for (MutBoxChannelShapeList::const_iterator i 
				     = list.begin(); i != list.end(); i++)
				if ((*i) == channel) {
					found = true;
					break;
				}
			mutASSERT(found);
			DEBUGLOG2(routing,("Output device shape %p"),shape);
			mutASSERT(shape->GetDevice() == Out);
			mutASSERT(channel->GetOutput() == shape);
			noshape = false;
		}
		if (noshape) {
			DEBUGLOG2(routing,("No output device shape"));
		}
		DEBUGLOG2(routing,
			  ("Output device %p '%s' Type %d:\n%s"),
			  Out.get(),
			  Out->GetName().c_str(),
			  Out->GetType(),
			  Out->TowxString().c_str());
	}

	static void CheckRoute(const RouteClass * route,
			       const MutInputDeviceShape * In) 
	{
		DEBUGLOG2(routing,
			  ("Route %p id %d, Type %d, Input range %d -- %d"),
			  route,
			  route->GetId(),
			  route->GetType(),
			  route->GetInputFrom(), 
			  route->GetInputTo());
		DEBUGLOG2(routing,
			  ("Box %d, active %d, Output range %d -- %d (no Drum: %d)"),
			  route->GetBox(),
			  route->GetActive(),
			  route->GetOutputFrom(), 
			  route->GetOutputTo(), 
			  route->OutputAvoidDrumChannel());

		const MutBoxChannelShapeList & shapes = 
			ToGUIBase(route).GetBoxChannelShapes();
		
		for (MutBoxChannelShapeList::const_iterator i = shapes.begin();
		     i != shapes.end(); i++) {
			MutBoxChannelShape * shape = *i;
			mutASSERT((In && shape ) || !(In || shape));
			if (shape) {
				DEBUGLOG2(routing,("Box channel shape %p"), shape);
				MutBoxShape * box = 
					dynamic_cast<MutBoxShape *> 
					(shape->GetParent());
				DEBUGLOG2(routing,
					  ("Box shape %p box %d"),
					  box,
					  box->GetBoxId());
				mutASSERT(shape->GetRoute() == route);
				mutASSERT(shape->GetInput() == In);
				mutASSERT(box->GetBoxId() == route->GetBox());
			} else {
				DEBUGLOG2(routing,("No Box Channel shape"));
			}
			OutputDevice Out = route->GetOutputDevice();
			if (Out) CheckOutputDevice(Out, shape);
		}
	}

	static void CheckInputDevice(const InputDeviceClass *  In)
	{
		DEBUGLOG2(routing,
			  ("Input device %p '%s' %d:\n%s"), 
			  In.get(),
			  In->GetName().c_str(),
			  In->GetType(),
			  In->TowxString().c_str());

		const routeListType & routes = 
			In->GetRoutes();
		for (routeListType::const_iterator route = routes.begin();
		     route != routes.end();route++)
			CheckRoute(*route, shape);
		
		const MutInputDeviceShapeList & shapes = ToGUIBase(In).GetShapes();
		
		for (MutInputDeviceShapeList::const_iterator i = shapes.begin();
		     i != shapes.end();
		     i++) {
			MutInputDeviceShape * shape = *i;
			if (shape) {
				DEBUGLOG2(routing,("Input device shape %p"),shape);
				mutASSERT (shape->GetDevice() == In);
			} else {
				DEBUGLOG2(routing,("No input device shape"));
			}
		}
	}

#endif


	/** 
	 * Check for duplicate entries in a list.
	 * 
	 * \param list List to be checked.
	 */
	template<class T> 
	static void CheckList(const T & list) {
		DEBUGLOG2(routing,("List at %p has %d entries"),(void*)&list,(int)list.size());
		for (typename T::const_iterator i = list.begin();
		     i != list.end(); i++) {
			typename T::const_iterator j = i;
			j++;
			mutASSERT(std::find(j,list.end(),*i) == list.end());
		}
	}


#if wxGUI
	static void Check(const MutInputDeviceShape * input,
			  const MutBoxChannelShape * route) {
		// both shapes are found. Are they connected?
		mutASSERT(route->GetInput() == input);
		
		const MutBoxChannelShapeList & routelist = 
			input->GetChannels();
		MutBoxChannelShapeList::const_iterator i =
			std::find(routelist.begin(),
				  routelist.end(),
				  route);
		mutASSERT(i != routelist.end());
	}



	static void Check(const MutInputDeviceShape * input,
			  const  RouteClass * route) {
		// input has shape search for route shape
		const MutBoxChannelShapeList & routelist = 
			ToGUIBase(route)->GetBoxChannelShapes();
		CheckList(routelist); // doesn't check for duplicate parents
		bool found = false;
		wxWindow * parent = input->GetParent();
		for (MutBoxChannelShapeList::const_iterator i = routelist.begin();
		     i != routelist.end(); i++) {
			MutBoxChannelShape * channelshape = *i;
			wxWindow * channelparent = channelshape->GetParent();
			if (parent == channelparent->GetParent()) {
				mutASSERT(!found);
				found = true;
				Check(input, channelshape);
			}
		}
		mutASSERT(found);
	}

	static void Check(const InputDeviceClass * input, 
			  const MutBoxChannelShape * route) {
		// route has shape search for input shape
		const MutInputDeviceShapeList & inputlist = 
			ToGUIBase(input)->GetShapes();
		wxWindow * parent = route->GetGrandParent();
		for (MutInputDeviceShapeList::const_iterator i = inputlist.begin();
		     i != inputlist.end(); i++) {
			if ((*i)->GetParent() == parent) {
				Check((*i), route);
				return;
			}
		}
		mutASSERT(false);
	}
#endif

	static void Check(const InputDeviceClass * input,
			  const  RouteClass * route) {
#if wxGUI
		// input and route are associated searching for shapes
		const MutInputDeviceShapeList & inputlist = 
			ToGUIBase(input)->GetShapes();
		for (MutInputDeviceShapeList::const_iterator i = inputlist.begin();
		     i != inputlist.end(); i++) {
			Check(*i,route);
			MutRouteWnd * parent = 
				dynamic_cast<MutRouteWnd *>((*i)->GetParent());
			mutASSERT(parent);
			if (parent) 
				rwdtoplevels.insert(parent);
		}

		const MutBoxChannelShapeList & routelist = 
			ToGUIBase(route)->GetBoxChannelShapes();
		CheckList(routelist);
		for (MutBoxChannelShapeList::const_iterator i = routelist.begin();
		     i != routelist.end(); i++) {
			Check(input, *i);
		}
#endif
	}

	static void Check(const InputDeviceClass * input) {
		DEBUGLOG2(routing,("%s"),(std::string)(*input));
		// associated routes for input device
		const routeListType & routes = input->GetRoutes();
		CheckList(routes);
		for (routeListType::const_iterator i = routes.begin();
		     i != routes.end(); i++) {
			mutASSERT((*i)->GetInputDevice() == input);
			Check(input, (*i).get());
		}
#if wxGUI		
		CheckList(ToGUIBase(input)->GetShapes());
		GUIInputDeviceBase * guibase = ToGUIBase(const_cast<InputDeviceClass *>(input));
		for (rwdset::iterator i = rwdtoplevels.begin();
		     i != rwdtoplevels.end();
		     i++) {
			mutASSERT(guibase->GetShape(*i));
		}

#endif
	}

	static void CheckInputDevices() {
		const InputDeviceList & inputlist = 
			InputDeviceClass::GetDeviceList();
		CheckList(inputlist);
		for (InputDeviceList::const_iterator i = inputlist.begin();
		     i != inputlist.end(); i++) {
			Check((*i).get());
		}
			
	}


#if wxGUI
	static void Check(const MutOutputDeviceShape * output,
			  const MutBoxChannelShape * route) {
		// both shapes are found. Are they connected?
		mutASSERT(route->GetOutput() == output);
		
		const MutBoxChannelShapeList & routelist = 
			output->GetChannels();
		for (MutBoxChannelShapeList::const_iterator i = 
			     routelist.begin();
		     i != routelist.end(); i++) {
			if ((*i) == route) return;
		}
		mutASSERT(false);
	}


	static void Check(const MutOutputDeviceShape * output,
			  const RouteClass * route) {
		// output has shape search for route shape
		const MutBoxChannelShapeList & routelist = 
			ToGUIBase(route)->GetBoxChannelShapes();
		CheckList(routelist);
		wxWindow * parent = output->GetParent();
		for (MutBoxChannelShapeList::const_iterator i = routelist.begin();
		     i != routelist.end(); i++) {
			if (parent == (*i)->GetGrandParent()) {
				Check(output, (*i));
				return;
			}
		}
		mutASSERT(false);
	}

	static void Check(const OutputDeviceClass * output, 
			  const MutBoxChannelShape * route) {
		// route has shape search for input shape
		const MutOutputDeviceShapeList & outputlist = 
			ToGUIBase(output)->GetShapes();
		wxWindow * parent = route->GetGrandParent();
		for (MutOutputDeviceShapeList::const_iterator i 
			     = outputlist.begin();
		     i != outputlist.end(); i++) {
			if ((*i)->GetParent() == parent) {
				Check((*i), route);
				return;
			}
		}
		mutASSERT(false);
	}

#endif

	static void Check(const OutputDeviceClass * output,
			  const RouteClass * route) {
#if wxGUI
		// input and route are associated searching for shapes
		const MutOutputDeviceShapeList & outputlist = 
			ToGUIBase(output)->GetShapes();
		for (MutOutputDeviceShapeList::const_iterator i = 
			     outputlist.begin();
		     i != outputlist.end(); i++) {
			Check(*i,route);
			MutRouteWnd * parent = 
				dynamic_cast<MutRouteWnd *>((*i)->GetParent());
			mutASSERT(parent);
			if (parent) 
				rwdtoplevels.insert(parent);
		}
		
		const MutBoxChannelShapeList & routelist = 
			ToGUIBase(route)->GetBoxChannelShapes();
		CheckList(routelist);
		for (MutBoxChannelShapeList::const_iterator i = routelist.begin();
		     i != routelist.end(); i++) {
			Check(output, *i);
		}
#endif
	}

	static void Check(const OutputDeviceClass * output) {
		DEBUGLOG2(routing,("%s"),(std::string)(*output));
		// associated routes for output device
		const routeListType & routes = output->GetRoutes();
		CheckList(routes);
		for (routeListType::const_iterator i = routes.begin();
		     i != routes.end(); i++) {
			mutASSERT((*i)->GetOutputDevice() == output);
			Check(output, (*i).get());
		}
		
#if wxGUI
		CheckList(ToGUIBase(output)->GetShapes());

		GUIOutputDeviceBase * guibase = ToGUIBase(const_cast<OutputDeviceClass *>(output));
		for (rwdset::iterator i = rwdtoplevels.begin();
		     i != rwdtoplevels.end();
		     i++) {
			mutASSERT(guibase->GetShape(*i));
		}
#endif
	}

	static void CheckOutputDevices() {
		const OutputDeviceList & outputlist = 
			OutputDeviceClass::GetDeviceList();
		CheckList(outputlist);
		for (OutputDeviceList::const_iterator i = outputlist.begin();
		     i != outputlist.end(); i++) {
			Check((*i).get());
		}
			
	}


#if wxGUI
	static void Check(const MutBoxShape * box,
			  const MutBoxChannelShape * route) {
		// both shapes are found. Are they connected?
		mutASSERT(route->GetParent() == box);
		Route & r = route->GetRoute();
		const Box & b = box->GetBox();
		mutASSERT(r->GetBox() == b);
		
		const wxSizer * boxsizer = 
			box->GetChannels();
		const wxSizerItemList & channels 
			= const_cast<wxSizer *>(boxsizer)->GetChildren();
		for (wxSizerItemList::const_iterator i 
			     = channels.begin();
		     i != channels.end(); i++) {
			if ((*i)->GetWindow() == route) return;
		}
		mutASSERT(false);
	}


	static void Check(const MutBoxShape * box,
			  const RouteClass * route) {
		// box has shape search for route shape
		const MutBoxChannelShapeList & routelist = 
			ToGUIBase(route)->GetBoxChannelShapes();
		CheckList(routelist);
		wxWindow * parent = box->GetParent();
		for (MutBoxChannelShapeList::const_iterator i = routelist.begin();
		     i != routelist.end(); i++) {
			if (parent == (*i)->GetGrandParent()) {
				Check(box, (*i));
				return;
			}
		}
		mutASSERT(false);
	}

	static void Check(const BoxClass * box, 
			  const MutBoxChannelShape * route) {
		// route has shape search for input shape
		const BoxData * b = ToGUIBase(box);
		mutASSERT(b);
		wxWindow * parent = route->GetGrandParent();
		mutASSERT(parent);
		const MutBoxShape * shape = b->GetShape(parent);
		mutASSERT(shape);
		Check(shape, route);
	}

	static void Check(const MutBoxShape * shape);

#endif

	static void Check(const BoxClass * box,
			  const RouteClass * route) {
#if wxGUI
		// input and route are associated searching for shapes
		const MutBoxShapeList & boxlist = 
			ToGUIBase(box)->GetShapes();
		for (MutBoxShapeList::const_iterator i = 
			     boxlist.begin();
		     i != boxlist.end(); i++) {
			Check(*i,route);
			MutRouteWnd * parent = 
				dynamic_cast<MutRouteWnd *>((*i)->GetParent());
			mutASSERT(parent);
			if (parent) 
				rwdtoplevels.insert(parent);

			Check(*i);
			
		}
		
		const MutBoxChannelShapeList & routelist = 
			ToGUIBase(route)->GetBoxChannelShapes();
		CheckList(routelist);
		for (MutBoxChannelShapeList::const_iterator i = routelist.begin();
		     i != routelist.end(); i++) {
			Check(box, *i);
		}
#endif
	}

	static void Check(const BoxClass * box) {
		DEBUGLOG2(routing,("%s"),(box->operator std::string()));
		// associated routes for box device
		const routeListType & routes = box->GetRoutes();
		CheckList(routes);
		for (routeListType::const_iterator i = routes.begin();
		     i != routes.end(); i++) {
			mutASSERT((*i)->GetBox() == box);
			Check(box, (*i).get());
		}
		
#if wxGUI
		CheckList(ToGUIBase(box)->GetShapes());
		BoxData * guibase = ToGUIBase(const_cast<BoxClass *>(box));
		for (rwdset::iterator i = rwdtoplevels.begin();
		     i != rwdtoplevels.end();
		     i++) {
			MutBoxShape * box = guibase->GetShape(*i);
			mutASSERT(box);
		}
#endif
	}
	
	static void CheckBoxes() {
		const BoxListType & boxlist = 
			BoxClass::GetBoxList();
		CheckList(boxlist);
		for (BoxListType::const_iterator i = boxlist.begin();
		     i != boxlist.end(); i++) {
			Check((*i).get());
		}
	}

#if wxGUI
	static void Check(const RouteClass * route, 
			  const MutBoxChannelShape * channel) {
		MutRouteWnd * grandparent = 
			dynamic_cast<MutRouteWnd *>(channel->GetGrandParent());
		mutASSERT(grandparent);
		if (grandparent) 
			rwdtoplevels.insert(grandparent);
		MutBoxShape * box = 
			dynamic_cast<MutBoxShape *>(channel->GetParent());
		mutASSERT(box);
		if (!box) return;
		mutASSERT(box->GetBox() == route->GetBox());
		mutASSERT(ToGUIBase(route->GetBox())->GetShape(channel->GetGrandParent()) == box);

#if 0
		const MutBoxShapeList & list = ToGUIBase(route)->GetBoxChannelShapes();
		DEBUGLOG2(routing, ("Box %d: %p == %p (%d entries)"),
			  route->GetBox(),
			  (void*)&list,
			  (void*)&(ToGUIBase(route->GetBox())->GetBoxShapes()),
			  (int)list.size());
		const BoxData * routeboxdata = ToGUIBase(route)->GetBoxData();
		int i;
		for (i = MIN_BOX; i < MAX_BOX && 
			     routeboxdata != &(BoxData::GetBox(route->GetBox())); 
		     i++);
		if (i < MAX_BOX) {
			DEBUGLOG2(routing, ("Box %p has GUI number %d and id %d"),
				  (void*)routeboxdata,
				  i,route->GetBox());
		} else {
			DEBUGLOG2(routing, ("Box %p has no GUI number but id %d"),
				  (void*)routeboxdata,
				  route->GetBox());
		}
		CheckList(list);
		MutBoxShapeList::const_iterator pos = 
			std::find(list.begin(),
				  list.end(),
				  box);
		mutASSERT(pos != list.end());
#endif
	}
#endif

	static void Check(const RouteClass * route) {
		DEBUGLOG2(routing,("%s"),(route->operator std::string()));
#if wxGUI
		const MutBoxChannelShapeList & channels = 
			ToGUIBase(route)->GetBoxChannelShapes();
		
		// associated routes for output device
		CheckList(channels);

		for (MutBoxChannelShapeList::const_iterator i = channels.begin();
		     i != channels.end(); i++) {
			Check(route,*i);
		}
#endif
		TRACE;
		if (route->GetInputDevice())
			Check ((route->GetInputDevice()).get(), route);
		TRACE;
		if (route->GetOutputDevice())
			Check ((route->GetOutputDevice()).get(), route);
		TRACE;

#if wxGUI
		GUIRouteBase * guibase = ToGUIBase(const_cast<RouteClass *>(route));
		for (rwdset::iterator i = rwdtoplevels.begin();
		     i != rwdtoplevels.end();
		     i++) {
			mutASSERT(guibase->GetShape(*i));
		}
#endif
	}

	static void CheckRoutes() {
		const routeListType & routelist = 
			RouteClass::GetRouteList();
		CheckList(routelist);
		for (routeListType::const_iterator i = routelist.begin();
		     i != routelist.end(); i++) {
			Check((*i).get());
		}

	}


#if wxGUI
	static void Check(const MutInputDeviceShape * shape) {
		const InputDeviceList & list = InputDeviceClass::GetDeviceList();
		const InputDevice & dev = shape->GetDevice();
		mutASSERT(dev);
		InputDeviceList::const_iterator pos = 
			std::find(list.begin(),list.end(),dev.get());
		mutASSERT(pos != list.end());
		const MutInputDeviceShapeList & shapelist = 
			ToGUIBase(dev.get())->GetShapes();
		MutInputDeviceShapeList::const_iterator pos2 = 
			std::find(shapelist.begin(),
				  shapelist.end(),
				  shape);
		mutASSERT(pos2 != shapelist.end());
	}

	static void Check(const MutOutputDeviceShape * shape) {
		const OutputDeviceList & list = 
			OutputDeviceClass::GetDeviceList();
		const OutputDevice & dev = shape->GetDevice();
		mutASSERT(dev);
		OutputDeviceList::const_iterator pos = 
			std::find(list.begin(),list.end(),dev.get());
		mutASSERT(pos != list.end());
		const MutOutputDeviceShapeList & shapelist = 
			ToGUIBase(dev)->GetShapes();
		MutOutputDeviceShapeList::const_iterator pos2 = 
			std::find(shapelist.begin(),
				  shapelist.end(),
				  shape);
		mutASSERT(pos2 != shapelist.end());
	}

	static void Check(const MutBoxChannelShape * shape) {
		const Route & route = shape->GetRoute();
		const MutBoxChannelShapeList & list =
			ToGUIBase(route)->GetBoxChannelShapes();
		MutBoxChannelShapeList::const_iterator pos = 
			std::find(list.begin(),list.end(),shape);
		mutASSERT(pos != list.end());
	}

	static void Check(const MutBoxShape * shape) {
		mutASSERT(shape);
		if (!shape) {
			UNREACHABLE;
			return;
		}
		const Box box = shape->GetBox();
		const BoxData * data = ToGUIBase(box);
		mutASSERT(data->GetShape(shape->GetParent()) == shape);

		wxSizer * channels = shape->GetChannels();
		mutASSERT(channels);
		const wxWindowList & children = shape->GetChildren();
		wxSizerItemList & channellist = channels->GetChildren();
		for (wxSizerItemList::iterator i = channellist.begin();
		     i != channellist.end();
		     i++) {
			wxWindow * window = (*i)->GetWindow();
			mutASSERT(window);
			MutBoxChannelShape * channel = 
				dynamic_cast<MutBoxChannelShape *>(window);
			mutASSERT(children.Find(channel));
			mutASSERT(shape);
			Route route = channel->GetRoute();
			mutASSERT(route);
			if (route) {
				mutASSERT(box == route->GetBox());
			}
			Check(channel);
		}

		for (wxWindowList::const_iterator i = children.begin();
		     i != children.end();
		     i++) {
			MutBoxChannelShape * channel = dynamic_cast<MutBoxChannelShape *>(*i);
			if (channel) {
				mutASSERT(channels->GetItem(channel));
			}
		}

	}

	static void Check(const MutRouteWnd * win) {
		if (!win) {
			UNREACHABLE;
			return;
		}
		wxSizer * sizer = win->GetInputDevices();
		wxSizerItemList & inputlist = sizer->GetChildren();
		for (wxSizerItemList::iterator i = inputlist.begin();
		     i != inputlist.end();
		     i++) {
			wxWindow * window = (*i)->GetWindow();
			mutASSERT(window);
			MutInputDeviceShape * shape = 
				dynamic_cast<MutInputDeviceShape *>(window);
			mutASSERT(shape);
			Check(shape);
		}
		sizer = win->GetOutputDevices();
		wxSizerItemList & outputlist = sizer->GetChildren();
		for (wxSizerItemList::iterator i = outputlist.begin();
		     i != outputlist.end();
		     i++) {
			wxWindow * window = (*i)->GetWindow();
			mutASSERT(window);
			MutOutputDeviceShape * shape = 
				dynamic_cast<MutOutputDeviceShape *>(window);
			mutASSERT(shape);
			Check(shape);
		}
		sizer = win->GetBoxes();
		wxSizerItemList & boxlist = sizer->GetChildren();
		for (wxSizerItemList::iterator i = boxlist.begin();
		     i != boxlist.end();
		     i++) {
			wxWindow * window = (*i)->GetWindow();
			mutASSERT(window);
			MutBoxShape * shape = 
				dynamic_cast<MutBoxShape *>(window);
			mutASSERT(shape);
			Check(shape);
		}
	}

	static void CheckWindows() {
		for (rwdset::iterator i = rwdtoplevels.begin(); 
		     i !=  rwdtoplevels.begin(); i++) {
			Check(*i);
		}
	}
#endif

#if wxGUI
	static void MakeTopLevelsInput() {
		const InputDeviceList & inputlist = 
			InputDeviceClass::GetDeviceList();
		CheckList(inputlist);
		for (InputDeviceList::const_iterator i = inputlist.begin();
		     i != inputlist.end(); i++) {
			GUIInputDeviceBase * guidev = ToGUIBase(const_cast<InputDevice &>(*i));
			MutInputDeviceShapeList & shapes = guidev->GetShapes();
			for (MutInputDeviceShapeList::iterator j = shapes.begin();
			     j != shapes.end(); j++) {
				MutRouteWnd * root = dynamic_cast<MutRouteWnd *>((*j)->GetParent());
				mutASSERT(root);
				rwdtoplevels.insert(root);
			}
		}
	}
	static void MakeTopLevelsOutput() {
		const OutputDeviceList & outputlist = 
			OutputDeviceClass::GetDeviceList();
		CheckList(outputlist);
		for (OutputDeviceList::const_iterator i = outputlist.begin();
		     i != outputlist.end(); i++) {
			GUIOutputDeviceBase * guidev = ToGUIBase(const_cast<OutputDevice &>(*i));
			MutOutputDeviceShapeList & shapes = guidev->GetShapes();
			for (MutOutputDeviceShapeList::iterator j = shapes.begin();
			     j != shapes.end(); j++) {
				MutRouteWnd * root = dynamic_cast<MutRouteWnd *>((*j)->GetParent());
				mutASSERT(root);
				rwdtoplevels.insert(root);
			} 
		}
	}
	static void MakeTopLevelsBoxes() {
		const BoxListType & boxlist = 
			BoxClass::GetBoxList();
		CheckList(boxlist);
		for (BoxListType::const_iterator i = boxlist.begin();
		     i != boxlist.end(); i++) {
			BoxData * guidev = ToGUIBase(const_cast<Box &>(*i));
			MutBoxShapeList & shapes = const_cast<MutBoxShapeList& >(guidev->GetShapes());
			for (MutBoxShapeList::iterator j = shapes.begin();
			     j != shapes.end(); j++)  {
				MutRouteWnd * root = dynamic_cast<MutRouteWnd *>((*j)->GetParent());
				mutASSERT(root);
				rwdtoplevels.insert(root);
			}
		}
	}
	static void MakeTopLevelsRoutes() {
		const routeListType & routelist = 
			RouteClass::GetRouteList();
		CheckList(routelist);
		for (routeListType::const_iterator i = routelist.begin();
		     i != routelist.end(); i++) {
			GUIRoute * guiroute = ToGUIBase(const_cast<Route &>(*i));
			MutBoxChannelShapeList & shapes 
				= const_cast<MutBoxChannelShapeList &>(guiroute->GetBoxChannelShapes());
			for (MutBoxChannelShapeList::iterator j = shapes.begin();
			     j != shapes.end(); j++)  {
				MutRouteWnd * root = dynamic_cast<MutRouteWnd *>((*j)->GetGrandParent());
				mutASSERT(root);
				rwdtoplevels.insert(root);
			}
		}
	}
#endif

	void DebugCheckRoutes() {
#if wxGUI
		rwdtoplevels.clear();
		MakeTopLevelsInput();
		MakeTopLevelsOutput();
		MakeTopLevelsBoxes();
		MakeTopLevelsRoutes();
		mutASSERT(rwdtoplevels.find(NULL) == rwdtoplevels.end());
#endif
		CheckInputDevices();
		CheckOutputDevices();
		CheckBoxes();
		CheckRoutes();
#if wxGUI
		CheckWindows();
#endif
	}
}
#endif

///\}
