/** \file 
 ********************************************************************
 * Debug functions for routing system
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/muwx/Routing/DebugRoute.cpp,v 1.4 2011/09/27 20:13:24 keinstein Exp $
 * Copyright:   (c) 2010 TU Dresden
 * \author  Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 2010/04/13
 * $Date: 2011/09/27 20:13:24 $
 * \version $Revision: 1.4 $
 * \license GPL
 *
 * $Log: DebugRoute.cpp,v $
 * Revision 1.4  2011/09/27 20:13:24  keinstein
 * * Reworked route editing backend
 * * rewireing is done by RouteClass/GUIRoute now
 * * other classes forward most requests to this pair
 * * many bugfixes
 * * Version change: We are reaching beta phase now
 *
 * Revision 1.3  2011-02-20 22:35:58  keinstein
 * updated license information; some file headers have to be revised, though
 *
 * Revision 1.2  2010-11-21 13:15:51  keinstein
 * merged experimental_tobias
 *
 * Revision 1.1.2.1  2010-01-11 10:12:59  keinstein
 * added some .cvsignore files
 *
 *
 ********************************************************************
 * \addtogroup route
 * \{
 ********************************************************************/

#include "Defs.h"
#ifdef DEBUG
#include "DebugRoute.h"
#include "Device.h"
#include "InputDeviceShape.h"
#include "OutputDeviceShape.h"
#include "muwx/MutRouteWnd.h"
#include "muwx/Routing/BoxShape.h"
#include "muwx/Routing/GUIRoute-inlines.h"
#include <set>
#include <algorithm>

using namespace mutabor;
namespace mutaborGUI {
#if 0
	static void CheckOutputDevice(const OutputDevice Out, 
				      const MutBoxChannelShape * channel) 
	{
		DEBUGLOG2(routing,_T("Output device %p, Channel %p"),Out.get(),channel);
		MutOutputDeviceShapeList & shapes = ToGUIBase(Out).GetShapes();
		bool noshape = true;
		for (MutOutputDeviceShapeList::const_iterator si = shapes.begin();
		     si != shapes.end(); si++) {
			MutOutputDeviceShape * shape = *si;
			wxASSERT ((channel && shape) || !(channel || shape));
			bool found = false;
			const MutBoxChannelShapeList & list = 
				shape->getRoutesList();
			for (MutBoxChannelShapeList::const_iterator i 
				     = list.begin(); i != list.end(); i++)
				if ((*i) == channel) {
					found = true;
					break;
				}
			wxASSERT(found);
			DEBUGLOG2(routing,_T("Output device shape %p"),shape);
			wxASSERT(shape->GetDevice() == Out);
			wxASSERT(channel->GetOutput() == shape);
			noshape = false;
		}
		if (noshape) {
			DEBUGLOG2(routing,_T("No output device shape"));
		}
		DEBUGLOG2(routing,
			  _T("Output device %p '%s' Type %d:\n%s"),
			  Out.get(),
			  Out->GetName().c_str(),
			  Out->GetType(),
			  Out->TowxString().c_str());
	}

	static void CheckRoute(const Route  route,const MutInputDeviceShape * In) 
	{
		DEBUGLOG2(routing,
			  _T("Route %p id %d, Type %d, Input range %d -- %d"),
			  route.get(),
			  route->GetId(),
			  route->GetType(),
			  route->GetInputFrom(), 
			  route->GetInputTo());
		DEBUGLOG2(routing,
			  _T("Box %d, active %d, Output range %d -- %d (no Drum: %d)"),
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
			wxASSERT((In && shape ) || !(In || shape));
			if (shape) {
				DEBUGLOG2(routing,_T("Box channel shape %p"), shape);
				MutBoxShape * box = 
					dynamic_cast<MutBoxShape *> 
					(shape->GetParent());
				DEBUGLOG2(routing,
					  _T("Box shape %p box %d"),
					  box,
					  box->GetBoxId());
				wxASSERT(shape->GetRoute() == route);
				wxASSERT(shape->GetInput() == In);
				wxASSERT(box->GetBoxId() == route->GetBox());
			} else {
				DEBUGLOG2(routing,_T("No Box Channel shape"));
			}
			OutputDevice Out = route->GetOutputDevice();
			if (Out) CheckOutputDevice(Out, shape);
		}
	}

	static void CheckInputDevice(const InputDevice In)
	{
		DEBUGLOG2(routing,
			  _T("Input device %p '%s' %d:\n%s"), 
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
				DEBUGLOG2(routing,_T("Input device shape %p"),shape);
				wxASSERT (shape->GetDevice() == In);
			} else {
				DEBUGLOG2(routing,_T("No input device shape"));
			}
		}
	}

#endif
	typedef std::set<MutRouteWnd *> rwdset;
	static rwdset rwdtoplevels;
	
	template<class T> 
	static void CheckList(const T & list) {
		DEBUGLOG2(routing,_T("List at %p has %d entries"),&list,list.size());
		for (typename T::const_iterator i = list.begin();
		     i != list.end(); i++) {
			typename T::const_iterator j = i;
			j++;
			wxASSERT(std::find(j,list.end(),*i) == list.end());
		}
	}


	static void Check(MutInputDeviceShape * input,
			  MutBoxChannelShape * route) {
		// both shapes are found. Are they connected?
		wxASSERT(route->GetInput() == input);
		
		const MutBoxChannelShapeList & routelist = 
			input->GetChannels();
		MutBoxChannelShapeList::const_iterator i =
			std::find(routelist.begin(),
				  routelist.end(),
				  route);
		wxASSERT(i != routelist.end());
	}



	static void Check(MutInputDeviceShape * input, Route route) {
		// input has shape search for route shape
		const MutBoxChannelShapeList & routelist = 
			ToGUIBase(route).GetBoxChannelShapes();
		CheckList(routelist);
		wxWindow * parent = input->GetParent();
		for (MutBoxChannelShapeList::const_iterator i = routelist.begin();
		     i != routelist.end(); i++) {
			if (parent == (*i)->GetGrandParent()) {
				Check(input, (*i));
				return;
			}
		}
		wxASSERT(false);
	}

	static void Check(InputDevice input, MutBoxChannelShape * route) {
		// route has shape search for input shape
		const MutInputDeviceShapeList & inputlist = 
			ToGUIBase(input).GetShapes();
		wxWindow * parent = route->GetGrandParent();
		for (MutInputDeviceShapeList::const_iterator i = inputlist.begin();
		     i != inputlist.end(); i++) {
			if ((*i)->GetParent() == parent) {
				Check((*i), route);
				return;
			}
		}
		wxASSERT(false);
	}


	static void Check(InputDevice input, Route route) {
		// input and route are associated searching for shapes
		MutInputDeviceShapeList & inputlist = 
			ToGUIBase(input).GetShapes();
		for (MutInputDeviceShapeList::const_iterator i = inputlist.begin();
		     i != inputlist.end(); i++) {
			Check(*i,route);
			MutRouteWnd * parent = 
				dynamic_cast<MutRouteWnd *>((*i)->GetParent());
			wxASSERT(parent);
			if (parent) 
				rwdtoplevels.insert(parent);
		}

		const MutBoxChannelShapeList & routelist = 
			ToGUIBase(route).GetBoxChannelShapes();
		CheckList(routelist);
		for (MutBoxChannelShapeList::const_iterator i = routelist.begin();
		     i != routelist.end(); i++) {
			Check(input, *i);
		}
	}

	static void Check(InputDevice input) {
		DEBUGLOG2(routing,_T("%s"),(const wxChar *)(input->TowxString()));
		// associated routes for input device
		const routeListType & routes = input->GetRoutes();
		CheckList(routes);
		for (routeListType::const_iterator i = routes.begin();
		     i != routes.end(); i++) {
			wxASSERT((*i)->GetInputDevice() == input);
			Check(input, *i);
		}
		
		CheckList(ToGUIBase(input).GetShapes());
	}

	static void CheckInputDevices() {
		const InputDeviceList & inputlist = 
			InputDeviceClass::GetDeviceList();
		CheckList(inputlist);
		for (InputDeviceList::const_iterator i = inputlist.begin();
		     i != inputlist.end(); i++) {
			Check(*i);
		}
			
	}


	static void Check(MutOutputDeviceShape * output,
			  MutBoxChannelShape * route) {
		// both shapes are found. Are they connected?
		wxASSERT(route->GetOutput() == output);
		
		const MutBoxChannelShapeList & routelist = 
			output->GetChannels();
		for (MutBoxChannelShapeList::const_iterator i = routelist.begin();
		     i != routelist.end(); i++) {
			if ((*i) == route) return;
		}
		wxASSERT(false);
	}



	static void Check(MutOutputDeviceShape * output, Route route) {
		// output has shape search for route shape
		const MutBoxChannelShapeList & routelist = 
			ToGUIBase(route).GetBoxChannelShapes();
		CheckList(routelist);
		wxWindow * parent = output->GetParent();
		for (MutBoxChannelShapeList::const_iterator i = routelist.begin();
		     i != routelist.end(); i++) {
			if (parent == (*i)->GetGrandParent()) {
				Check(output, (*i));
				return;
			}
		}
		wxASSERT(false);
	}

	static void Check(OutputDevice output, MutBoxChannelShape * route) {
		// route has shape search for input shape
		const MutOutputDeviceShapeList & outputlist = 
			ToGUIBase(output).GetShapes();
		wxWindow * parent = route->GetGrandParent();
		for (MutOutputDeviceShapeList::const_iterator i 
			     = outputlist.begin();
		     i != outputlist.end(); i++) {
			if ((*i)->GetParent() == parent) {
				Check((*i), route);
				return;
			}
		}
		wxASSERT(false);
	}


	static void Check(OutputDevice output, Route route) {
		// input and route are associated searching for shapes
		MutOutputDeviceShapeList & outputlist = 
			ToGUIBase(output).GetShapes();
		for (MutOutputDeviceShapeList::const_iterator i = outputlist.begin();
		     i != outputlist.end(); i++) {
			Check(*i,route);
			MutRouteWnd * parent = 
				dynamic_cast<MutRouteWnd *>((*i)->GetParent());
			wxASSERT(parent);
			if (parent) 
				rwdtoplevels.insert(parent);
		}
		
		const MutBoxChannelShapeList & routelist = 
			ToGUIBase(route).GetBoxChannelShapes();
		CheckList(routelist);
		for (MutBoxChannelShapeList::const_iterator i = routelist.begin();
		     i != routelist.end(); i++) {
			Check(output, *i);
		}
	}

	static void Check(OutputDevice output) {
		DEBUGLOG2(routing,_T("%s"),(const wxChar *)(output->TowxString()));
		// associated routes for output device
		routeListType & routes = output->GetRoutes();
		CheckList(routes);
		for (routeListType::const_iterator i = routes.begin();
		     i != routes.end(); i++) {
			wxASSERT((*i)->GetOutputDevice() == output);
			Check(output, *i);
		}
		
		CheckList(ToGUIBase(output).GetShapes());
	}

	static void CheckOutputDevices() {
		const OutputDeviceList & outputlist = 
			OutputDeviceClass::GetDeviceList();
		CheckList(outputlist);
		for (OutputDeviceList::const_iterator i = outputlist.begin();
		     i != outputlist.end(); i++) {
			Check(*i);
		}
			
	}


	static void Check(Route route, MutBoxChannelShape * channel) {
		MutRouteWnd * grandparent = 
			dynamic_cast<MutRouteWnd *>(channel->GetGrandParent());
		wxASSERT(grandparent);
		if (grandparent) 
			rwdtoplevels.insert(grandparent);
		MutBoxShape * box = 
			dynamic_cast<MutBoxShape *>(channel->GetParent());
		wxASSERT(box);
		if (!box) return;
		wxASSERT(box->GetBoxId() == route->GetBox());
		const MutBoxShapeList & list = ToGUIBase(route).GetBoxShapes();
		DEBUGLOG2(routing, _T("Box %d: %p == %p (%d entries)"),
			  route->GetBox(),
			  &list,
			  &(BoxData::GetBox(route->GetBox()).GetBoxShapes()),
			  list.size());
		BoxData * routeboxdata = ToGUIBase(route).GetBoxData();
		int i;
		for (i = MIN_BOX; i < MAX_BOX && 
			     routeboxdata != &(BoxData::GetBox(route->GetBox())); 
		     i++);
		if (i < MAX_BOX) {
			DEBUGLOG2(routing, _T("Box %p has GUI number %d and id %d"),
				  routeboxdata,
				  i,route->GetBox());
		} else {
			DEBUGLOG2(routing, _T("Box %p has no GUI number but id %d"),
				  routeboxdata,
				  route->GetBox());
		}
		CheckList(list);
		MutBoxShapeList::const_iterator pos = 
			std::find(list.begin(),
				  list.end(),
				  box);
		wxASSERT(pos != list.end());
	}

	static void Check(Route route) {
		DEBUGLOG2(routing,_T("%s"),(const wxChar *)(route->TowxString()));
		const MutBoxChannelShapeList & channels = 
			ToGUIBase(route).GetBoxChannelShapes();
		
		// associated routes for output device
		CheckList(channels);

		for (MutBoxChannelShapeList::const_iterator i = channels.begin();
		     i != channels.end(); i++) {
			Check(route,*i);
		}
		if (route->GetInputDevice())
			Check (route->GetInputDevice(), route);
		if (route->GetOutputDevice())
			Check (route->GetOutputDevice(), route);
	}

	static void CheckRoutes() {
		const routeListType & routelist = 
			RouteClass::GetRouteList();
		CheckList(routelist);
		for (routeListType::const_iterator i = routelist.begin();
		     i != routelist.end(); i++) {
			Check(*i);
		}
			
	}


	static void Check(MutInputDeviceShape * shape) {
		const InputDeviceList & list = InputDeviceClass::GetDeviceList();
		InputDevice dev = shape->GetDevice();
		wxASSERT(dev);
		InputDeviceList::const_iterator pos = 
			std::find(list.begin(),list.end(),dev);
		wxASSERT(pos != list.end());
		const MutInputDeviceShapeList & shapelist = 
			ToGUIBase(dev).GetShapes();
		MutInputDeviceShapeList::const_iterator pos2 = 
			std::find(shapelist.begin(),
				  shapelist.end(),
				  shape);
		wxASSERT(pos2 != shapelist.end());
	}

	static void Check(MutOutputDeviceShape * shape) {
		const OutputDeviceList & list = OutputDeviceClass::GetDeviceList();
		OutputDevice dev = shape->GetDevice();
		wxASSERT(dev);
		OutputDeviceList::const_iterator pos = 
			std::find(list.begin(),list.end(),dev);
		wxASSERT(pos != list.end());
		const MutOutputDeviceShapeList & shapelist = 
			ToGUIBase(dev).GetShapes();
		MutOutputDeviceShapeList::const_iterator pos2 = 
			std::find(shapelist.begin(),
				  shapelist.end(),
				  shape);
		wxASSERT(pos2 != shapelist.end());
	}

	static void Check(MutBoxChannelShape * shape) {
		Route route = shape->GetRoute();
		const MutBoxChannelShapeList & list =
			ToGUIBase(route).GetBoxChannelShapes();
		MutBoxChannelShapeList::const_iterator pos = 
			std::find(list.begin(),list.end(),shape);
		wxASSERT(pos != list.end());
	}

	static void Check(MutBoxShape * shape) {
		int id = shape->GetBoxId();
		BoxData & data = BoxData::GetBox(id);
		const MutBoxShapeList & list = data.GetBoxShapes();
		MutBoxShapeList::const_iterator pos = 
			std::find(list.begin(),list.end(),shape);
		wxASSERT(pos != list.end());

		wxSizer * channels = shape->GetChannels();
		wxASSERT(channels);
		wxSizerItemList & channellist = channels->GetChildren();
		for (wxSizerItemList::iterator i = channellist.begin();
		     i != channellist.end();
		     i++) {
			wxWindow * window = (*i)->GetWindow();
			wxASSERT(window);
			MutBoxChannelShape * channel = 
				dynamic_cast<MutBoxChannelShape *>(window);
			wxASSERT(shape);
			Route route = channel->GetRoute();
			wxASSERT(route);
			if (route) {
				wxASSERT(id == route->GetBox());
			}
			Check(channel);
		}

	}

	static void Check(MutRouteWnd * win) {
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
			wxASSERT(window);
			MutInputDeviceShape * shape = 
				dynamic_cast<MutInputDeviceShape *>(window);
			wxASSERT(shape);
			Check(shape);
		}
		sizer = win->GetOutputDevices();
		wxSizerItemList & outputlist = sizer->GetChildren();
		for (wxSizerItemList::iterator i = outputlist.begin();
		     i != outputlist.end();
		     i++) {
			wxWindow * window = (*i)->GetWindow();
			wxASSERT(window);
			MutOutputDeviceShape * shape = 
				dynamic_cast<MutOutputDeviceShape *>(window);
			wxASSERT(shape);
			Check(shape);
		}
		sizer = win->GetBoxes();
		wxSizerItemList & boxlist = sizer->GetChildren();
		for (wxSizerItemList::iterator i = boxlist.begin();
		     i != boxlist.end();
		     i++) {
			wxWindow * window = (*i)->GetWindow();
			wxASSERT(window);
			MutBoxShape * shape = 
				dynamic_cast<MutBoxShape *>(window);
			wxASSERT(shape);
			Check(shape);
		}
	}

	static void CheckWindows() {
		for (rwdset::iterator i = rwdtoplevels.begin(); 
		     i !=  rwdtoplevels.begin(); i++) {
			Check(*i);
		}
	}

	void DebugCheckRoutes() {
		rwdtoplevels.clear();
		CheckInputDevices();
		CheckOutputDevices();
		CheckRoutes();
		CheckWindows();
	}
}
#endif

///\}
