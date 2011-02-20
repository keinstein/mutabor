/** \file 
 ********************************************************************
 * Debug functions for routing system
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/muwx/Routing/DebugRoute.cpp,v 1.3 2011/02/20 22:35:58 keinstein Exp $
 * Copyright:   (c) 2010 TU Dresden
 * \author  Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 2010/04/13
 * $Date: 2011/02/20 22:35:58 $
 * \version $Revision: 1.3 $
 * \license GPL
 *
 * $Log: DebugRoute.cpp,v $
 * Revision 1.3  2011/02/20 22:35:58  keinstein
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

static void CheckOutputDevice(OutDevice * Out, MutBoxChannelShape * channel) 
{
	DEBUGLOG2(routing,_T("Output device %p, Channel %p"),Out,channel);
	MutOutputDeviceShape * shape = (MutOutputDeviceShape *) (Out->getUserData());
	wxASSERT ((channel && shape) || !(channel || shape));
	if (shape) {
		bool found = false;
		const MutBoxChannelShapeList & list = shape->getRoutesList();
		for (MutBoxChannelShapeList::const_iterator i = list.begin(); i != list.end(); i++)
			if ((*i) == channel) {
				found = true;
				break;
			}
		wxASSERT(found);
		DEBUGLOG2(routing,_T("Output device shape %p"),shape);
		wxASSERT(shape->GetDevice() == Out);
		wxASSERT(channel->GetOutput() == shape);
	} else {
		DEBUGLOG2(routing,_T("No output device shape"));
	}
	DEBUGLOG2(routing,_T("Output device %p '%s' Type %d:\n%s"),Out,Out->GetName().c_str(),Out->GetType(),Out->TowxString().c_str());
}

static void CheckRoute(Route * route, MutInputDeviceShape * In) 
{
	DEBUGLOG2(routing,_T("Route %p id %d, Type %d, Input range %d -- %d"),route,route->GetId(),route->GetType(),
		  route->GetInputFrom(), route->GetInputTo());
	DEBUGLOG2(routing,_T("Box %d, active %d, Output range %d -- %d (no Drum: %d)"),route->GetBox(),
		  route->GetActive(),route->GetOutputFrom(), route->GetOutputTo(), route->OutputAvoidDrumChannel());
	MutBoxChannelShape * shape = (MutBoxChannelShape *) (route->getUserData());
	wxASSERT((In && shape ) || !(In || shape));
	if (shape) {
		DEBUGLOG2(routing,_T("Box channel shape %p"), shape);
		MutBoxShape * box = dynamic_cast<MutBoxShape *> (shape->GetParent());
		DEBUGLOG2(routing,_T("Box shape %p box %d"),box,box->GetBoxId());
		wxASSERT(shape->GetRoute() == route);
		wxASSERT(shape->GetInput() == In);
		wxASSERT(box->GetBoxId() == route->GetBox());
	} else {
		DEBUGLOG2(routing,_T("No Box Channel shape"));
	}
	OutDevice * Out = route->GetOutDevice();
	if (Out) CheckOutputDevice(Out, shape);
}

static void CheckInputDevice(InDevice *In)
{
	DEBUGLOG2(routing,_T("Input device %p '%s' %d:\n%s"), In,In->GetName().c_str(),In->GetType(),In->TowxString().c_str());
	MutInputDeviceShape * shape = (MutInputDeviceShape *) (In->getUserData());
	if (shape) {
		DEBUGLOG2(routing,_T("Input device shape %p"),shape);
		wxASSERT (shape->GetDevice() == In);
	} else {
		DEBUGLOG2(routing,_T("No input device shape"));
	}
	for (Route * route = In->GetRoutes();route;route = route->GetNext())
		CheckRoute(route, shape);
}

void DebugCheckRoutes() {
	for (InDevice *In = InDevice::GetDeviceList(); In; In = In->GetNext())
		CheckInputDevice(In);
}
#endif

///\}
