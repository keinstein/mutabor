/** \file 
 ********************************************************************
 * Debug functions for routing system
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/muwx/Routing/DebugRoute.cpp,v 1.7 2011/11/02 14:31:59 keinstein Exp $
 * Copyright:   (c) 2010 TU Dresden
 * \author  Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 2010/04/13
 * $Date: 2011/11/02 14:31:59 $
 * \version $Revision: 1.7 $
 * \license GPL
 *
 * $Log: DebugRoute.cpp,v $
 * Revision 1.7  2011/11/02 14:31:59  keinstein
 * fix some errors crashing Mutabor on Windows
 *
 * Revision 1.6  2011-10-02 16:58:42  keinstein
 * * generate Class debug information when compile in debug mode
 * * InputDeviceClass::Destroy() prevented RouteClass::Destroy() from clearing references -- fixed.
 * * Reenable confirmation dialog when closing document while the logic is active
 * * Change debug flag management to be more debugger friendly
 * * implement automatic route/device deletion check
 * * new debug flag --debug-trace
 * * generate lots of tracing output
 *
 * Revision 1.5  2011-09-30 18:07:05  keinstein
 * * make compile on windows
 * * s/wxASSERT/mutASSERT/g to get assert handler completely removed
 * * add ax_boost_base for boost detection
 *
 * Revision 1.4  2011-09-27 20:13:24  keinstein
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

#include "mu32/Defs.h"
#ifdef DEBUG
#include "muwx/Routing/DebugRoute.h"
#include "mu32/routing/Device.h"
#include "muwx/Routing/InputDeviceShape.h"
#include "muwx/Routing/OutputDeviceShape.h"
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
			DEBUGLOG2(routing,_T("Output device shape %p"),shape);
			mutASSERT(shape->GetDevice() == Out);
			mutASSERT(channel->GetOutput() == shape);
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

	static void CheckRoute(const RouteClass * route,
			       const MutInputDeviceShape * In) 
	{
		DEBUGLOG2(routing,
			  _T("Route %p id %d, Type %d, Input range %d -- %d"),
			  route,
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
			mutASSERT((In && shape ) || !(In || shape));
			if (shape) {
				DEBUGLOG2(routing,_T("Box channel shape %p"), shape);
				MutBoxShape * box = 
					dynamic_cast<MutBoxShape *> 
					(shape->GetParent());
				DEBUGLOG2(routing,
					  _T("Box shape %p box %d"),
					  box,
					  box->GetBoxId());
				mutASSERT(shape->GetRoute() == route);
				mutASSERT(shape->GetInput() == In);
				mutASSERT(box->GetBoxId() == route->GetBox());
			} else {
				DEBUGLOG2(routing,_T("No Box Channel shape"));
			}
			OutputDevice Out = route->GetOutputDevice();
			if (Out) CheckOutputDevice(Out, shape);
		}
	}

	static void CheckInputDevice(const InputDeviceClass *  In)
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
				mutASSERT (shape->GetDevice() == In);
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
			mutASSERT(std::find(j,list.end(),*i) == list.end());
		}
	}


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
		mutASSERT(false);
	}

	static void Check(const InputDeviceClass * input, 
			  const MutBoxChannelShape * route) {
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
		mutASSERT(false);
	}


	static void Check(const InputDeviceClass * input,
			  const  RouteClass * route) {
		// input and route are associated searching for shapes
		const MutInputDeviceShapeList & inputlist = 
			ToGUIBase(input).GetShapes();
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
			ToGUIBase(route).GetBoxChannelShapes();
		CheckList(routelist);
		for (MutBoxChannelShapeList::const_iterator i = routelist.begin();
		     i != routelist.end(); i++) {
			Check(input, *i);
		}
	}

	static void Check(const InputDeviceClass * input) {
		DEBUGLOG2(routing,_T("%s"),(const wxChar *)(input->TowxString()));
		// associated routes for input device
		const routeListType & routes = input->GetRoutes();
		CheckList(routes);
		for (routeListType::const_iterator i = routes.begin();
		     i != routes.end(); i++) {
			mutASSERT((*i)->GetInputDevice() == input);
			Check(input, (*i).get());
		}
		
		CheckList(ToGUIBase(input).GetShapes());
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
		mutASSERT(false);
	}

	static void Check(const OutputDeviceClass * output, 
			  const MutBoxChannelShape * route) {
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
		mutASSERT(false);
	}


	static void Check(const OutputDeviceClass * output,
			  const RouteClass * route) {
		// input and route are associated searching for shapes
		const MutOutputDeviceShapeList & outputlist = 
			ToGUIBase(output).GetShapes();
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
			ToGUIBase(route).GetBoxChannelShapes();
		CheckList(routelist);
		for (MutBoxChannelShapeList::const_iterator i = routelist.begin();
		     i != routelist.end(); i++) {
			Check(output, *i);
		}
	}

	static void Check(const OutputDeviceClass * output) {
		DEBUGLOG2(routing,_T("%s"),(const wxChar *)(output->TowxString()));
		// associated routes for output device
		const routeListType & routes = output->GetRoutes();
		CheckList(routes);
		for (routeListType::const_iterator i = routes.begin();
		     i != routes.end(); i++) {
			mutASSERT((*i)->GetOutputDevice() == output);
			Check(output, (*i).get());
		}
		
		CheckList(ToGUIBase(output).GetShapes());
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
		mutASSERT(box->GetBoxId() == route->GetBox());
		const MutBoxShapeList & list = ToGUIBase(route).GetBoxShapes();
		DEBUGLOG2(routing, _T("Box %d: %p == %p (%d entries)"),
			  route->GetBox(),
			  &list,
			  &(BoxData::GetBox(route->GetBox()).GetBoxShapes()),
			  list.size());
		const BoxData * routeboxdata = ToGUIBase(route).GetBoxData();
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
		mutASSERT(pos != list.end());
	}

	static void Check(const RouteClass * route) {
		DEBUGLOG2(routing,_T("%s"),(const wxChar *)(route->TowxString()));
		const MutBoxChannelShapeList & channels = 
			ToGUIBase(route).GetBoxChannelShapes();
		
		// associated routes for output device
		CheckList(channels);

		for (MutBoxChannelShapeList::const_iterator i = channels.begin();
		     i != channels.end(); i++) {
			Check(route,*i);
		}
		TRACE;
		if (route->GetInputDevice())
			Check ((route->GetInputDevice()).get(), route);
		TRACE;
		if (route->GetOutputDevice())
			Check ((route->GetOutputDevice()).get(), route);
		TRACE;
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


	static void Check(const MutInputDeviceShape * shape) {
		const InputDeviceList & list = InputDeviceClass::GetDeviceList();
		const InputDevice & dev = shape->GetDevice();
		mutASSERT(dev);
		InputDeviceList::const_iterator pos = 
			std::find(list.begin(),list.end(),dev.get());
		mutASSERT(pos != list.end());
		const MutInputDeviceShapeList & shapelist = 
			ToGUIBase(dev.get()).GetShapes();
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
			ToGUIBase(dev).GetShapes();
		MutOutputDeviceShapeList::const_iterator pos2 = 
			std::find(shapelist.begin(),
				  shapelist.end(),
				  shape);
		mutASSERT(pos2 != shapelist.end());
	}

	static void Check(const MutBoxChannelShape * shape) {
		const Route & route = shape->GetRoute();
		const MutBoxChannelShapeList & list =
			ToGUIBase(route).GetBoxChannelShapes();
		MutBoxChannelShapeList::const_iterator pos = 
			std::find(list.begin(),list.end(),shape);
		mutASSERT(pos != list.end());
	}

	static void Check(const MutBoxShape * shape) {
		int id = shape->GetBoxId();
		BoxData & data = BoxData::GetBox(id);
		const MutBoxShapeList & list = data.GetBoxShapes();
		MutBoxShapeList::const_iterator pos = 
			std::find(list.begin(),list.end(),shape);
		mutASSERT(pos != list.end());

		wxSizer * channels = shape->GetChannels();
		mutASSERT(channels);
		wxSizerItemList & channellist = channels->GetChildren();
		for (wxSizerItemList::iterator i = channellist.begin();
		     i != channellist.end();
		     i++) {
			wxWindow * window = (*i)->GetWindow();
			mutASSERT(window);
			MutBoxChannelShape * channel = 
				dynamic_cast<MutBoxChannelShape *>(window);
			mutASSERT(shape);
			Route route = channel->GetRoute();
			mutASSERT(route);
			if (route) {
				mutASSERT(id == route->GetBox());
			}
			Check(channel);
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

	void DebugCheckRoutes() {
		mutASSERT(!NullRoute);
		rwdtoplevels.clear();
		CheckInputDevices();
		CheckOutputDevices();
		CheckRoutes();
		CheckWindows();
		mutASSERT(!NullRoute);
	}
}
#endif

///\}
