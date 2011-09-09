// -*- C++ -*-
/** \file
 ********************************************************************
 * Routing. Mutabor Core.
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/mu32/routing/Route.cpp,v 1.5 2011/09/09 09:29:10 keinstein Exp $
 * \author Rüdiger Krauße <krausze@mail.berlios.de>,
 * Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 1998
 * $Date: 2011/09/09 09:29:10 $
 * \version $Revision: 1.5 $
 * \license GPL
 *
 * $Log: Route.cpp,v $
 * Revision 1.5  2011/09/09 09:29:10  keinstein
 * fix loading of routing configuration
 *
 * Revision 1.4  2011-02-20 22:35:56  keinstein
 * updated license information; some file headers have to be revised, though
 *
 * Revision 1.3  2011-01-29 20:00:14  keinstein
 * include Device.h
 *
 * Revision 1.2  2010-11-21 13:15:45  keinstein
 * merged experimental_tobias
 *
 * Revision 1.1.2.5  2010-09-29 15:06:40  keinstein
 * Reset config before saving routing information and fix two bugs concerned with the deletion of boxes
 *
 * Revision 1.1.2.4  2010-09-29 13:03:30  keinstein
 * config can be stored and restored with new treeconfig
 *
 * Revision 1.1.2.3  2010-09-15 17:58:01  keinstein
 * old configuration can be loaded again.
 *
 * Revision 1.1.2.2  2010-08-10 15:54:29  keinstein
 * new, direct route configuration on init
 *
 * Revision 1.3.2.2  2010-07-06 09:06:26  keinstein
 * allow empty input and output devices in routes
 *
 * Revision 1.3.2.1  2009/08/04 11:30:49  keinstein
 * removed mut.h
 *
 *
 ********************************************************************
 *\addtogroup route
 *\{
 ********************************************************************/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "Route.h"
#include "Device.h"

// Route ------------------------------------------------------------

int Route::maxRouteId = 1;

WATCHEDPTR(Route,routing,Route) Route::routeList(NULL,_T("Route::routeList"));

const mutString RTName[] =
{
_T("ALL"), _T("ELSE"), _T("CHANNEL"), _T("STAFF")
};

void Route::Save(tree_storage & config) 
{
#ifdef DEBUG
	wxString oldpath = config.GetPath();
#endif
	config.Write(_T("Box"),Box);
	config.Write(_T("Active"),Active);
	if (In)
		((InDevice *)In)->Save(config,this);
	if (Out)
		((OutDevice *) Out)->Save(config,this);
	wxASSERT(oldpath == config.GetPath());
}

void Route::Load(tree_storage & config) 
{
#ifdef DEBUG
	wxString oldpath = config.GetPath();
#endif
	Box = config.Read(_T("Box"),NoBox);
	Active = config.Read(_T("Active"),true);
	if (In)
		((InDevice *) In)->Load(config,this);
	if (Out)
		((OutDevice *) Out)->Load(config,this);
	wxASSERT(oldpath == config.GetPath());
}


void Route::InitializeIds() 
{
	OutDevice::InitializeIds();
	int i = 0;
	Route * route = GetRouteList();
	while (route) {
		route -> Id = i++;
		route -> inputid = -1;
		Device * d =  static_cast<Device *>(route->GetOutDevice());
		route -> outputid = d ? d ->GetId(): -1 ;
		route=route->GetGlobalNext();
	}
	InDevice::InitializeIds();
}

void Route::SaveRoutes(tree_storage & config) 
{
#ifdef DEBUG
	wxString oldpath = config.GetPath();
#endif
	config.toLeaf(_T("Routes"));
	
	for (Route * route = GetRouteList(); route; 
	     route = route->GetGlobalNext()) {
		config.toLeaf(_T("Route"),route->GetId());
		config.Write(_T("Input Device"), route->inputid);
		config.Write(_T("Output Device"), route->outputid);
		route -> Save (config);
		config.toParent();
	}
	
	config.toParent();	
	wxASSERT(oldpath == config.GetPath());
}

void Route::LoadRoutes(tree_storage & config) 
{
#ifdef DEBUG
	wxString oldpath = config.GetPath();
#endif
	config.toLeaf(_T("Routes"));
	
	int i = config.toFirstLeaf(_T("Route"));
	while (i != wxNOT_FOUND) {
		DEBUGLOGTYPE(config,Route,_T("Loading route with id %d."), i);
		// \todo replace -1 by a correct default
		int inputid = config.Read(_T("Input Device"), -1);
		int outputid = config.Read(_T("Output Device"), -1);
		InDevice * in = InDevice::GetDevice(inputid);
		OutDevice * out = OutDevice::GetDevice(outputid);
		Route * route = new Route(in,out);
		if (in && route)
			in->AddRoute(route);
		if (route)
			route -> Load(config);
		i = config.toNextLeaf(_T("Route"));
	}
	
	config.toParent(2);
	wxASSERT(oldpath == config.GetPath());
}


void Route::AppendToRouteList (Route * route) 
{
        if (!routeList) {
                routeList = route; 
                return;
        }
	
        Route * r = routeList ;
	Route * r2;
        while ((r2 = r->globalNext)) {
		wxASSERT(r != route);
		r = r2;
	}
        r->globalNext = route;
}

void Route::RemoveFromRouteList (Route * route) 
{
        if (!routeList) return;
        
        if (routeList == route) {
                routeList = route -> globalNext; 
                route -> globalNext = NULL;
                return;
        }
	
        Route * d = routeList;
        while (d -> globalNext != route && d -> globalNext) d = d -> globalNext;
        if (d -> globalNext) {
                d -> globalNext = (route -> globalNext);
                route -> globalNext = NULL;
        }
}

const mutString DevTypeName[] =
{
N_("Unknown"),
N_("Midi Port"),
N_("Midi File"),
N_("GUIDO .gmn File")
};

#define READCONFIGSTR(config,name,variable,defval) \
        variable = config.Read(_T(name),defval); \
        DEBUGLOG2(config,_T("Read " name " = %s"),variable.c_str());

#define READCONFIGINT(config,name,variable,defval) \
        variable = config.Read(_T(name),defval); \
        DEBUGLOG2(config,_T("Read " name " = %d"),variable);


#if 0
void LoadRoutes(tree_storage & config)
{
	DEBUGLOG2(config,_T("Loading routes."));
	
	if (! config.HasGroup(_T("Input")) && !config.HasGroup(_T("Output"))) return;
	
	// clear device lists
	InDevice * InDevices = InDevice::GetDeviceList();
	if ( InDevices ) {
		delete InDevices;
		InDevices = NULL;
	}
	
	Route * Routes = Route :: GetRouteList();
	if (Routes) {
		delete Routes;
		Routes = NULL;
	}
	
	OutDevice * OutDevices = OutDevice::GetDeviceList();
	if ( OutDevices ) {
		delete OutDevices;
		OutDevices = NULL;
	}
	
	// Zerlegen von config
	
	wxString group;
	
	wxString defaultPortName = rtmidiout->getPortCount()?
	muT(rtmidiout->getPortName(0).c_str()):wxString(_("Unknown"));
	
	long group_number;
	
	// read output devices
	config.toLeaf(_T("Output"));
	DEBUGLOG2(config,_T("Path: %s"),config.GetPath().c_str());
	
	group_number = config.toFirstLeaf(_T("Device"));
	
	for (bool test = true; // we have a default output device
	     test; test = wxNOT_FOUND != (group_number = config.toNextLeaf(_T("Device")))) {
		DEBUGLOG2(config,_T("Path: %s"),config.GetPath().c_str());
		wxString name;
		long type, id;
		READCONFIGSTR(config,"Name",name,defaultPortName);

		READCONFIGINT(config,"Type",type,1);		
		if (type <= 0 || type >= DeviceMaxType) {
			// Bad device type; try to recover
			wxString type_name;
			READCONFIGSTR(config,"Type_Name",type_name, _("Midi Port"));
			
			int i;
			
			for (i = 1; i < DeviceMaxType; i++)
				if (wxGetTranslation(DevTypeName[i]) == type_name) break;
			
			if (i == DeviceMaxType) type = 0;
			else type = i;
		}
		
		READCONFIGINT(config,"Device_Id", id, 0);
		
		Device *out = OutDevice::CreateDevice((DevType) type, name, id);
		if (!out) {
			/// \todo implement output device error checking for config reading
			STUB;
		}
		wxString cwd = config.GetPath();
		out->Load(config);
	}
	
	config.toParent(3);
	DEBUGLOG2(config,_T("Path: %s"),config.GetPath().c_str());
	
	// read input devices
	config.toLeaf(_T("Input"));
	DEBUGLOG2(config,_T("Path: %s"),config.GetPath().c_str());
	group_number = config.toFirstLeaf(_T("Device"));
	
	for (bool test = true; // we have a default output device
	     test; test = wxNOT_FOUND != (group_number = config.toNextLeaf(_T("Device")))) {
		DEBUGLOG2(config,_T("Path: %s"),config.GetPath().c_str());
		
		wxString name;
		long type, id;
		READCONFIGSTR(config,"Name",name, defaultPortName);
		
		READCONFIGINT(config,"Type",type, 1);
		
		
		if (type <= DTUnknown || type >= DeviceMaxType) {
			// Bad device type; try to recover
			wxString type_name;
			READCONFIGSTR(config,"Type_Name",type_name, _("Midi Port"));
			
			
			int i;
			
			for (i = 1; i < DeviceMaxType; i++)
				if (wxGetTranslation(DevTypeName[i]) == type_name) break;
			
			if (i == DeviceMaxType) {
				i = 0;
				STUB;
			}
		}
		
		READCONFIGINT(config,"Device_Id",id, 0);
		
		InDevice *in = InDevice::CreateDevice((DevType) type, name, id);
		
		config.toLeaf(_T("Routes"));
		DEBUGLOG2(config,_T("Path: %s"),config.GetPath().c_str());
		wxString route_group;
		long route_iterator;
		route_iterator = config.toFirstLeaf(_T("Route"));
		
		for (bool test2 = true; // we need a default route
		     test2; test2 = wxNOT_FOUND != (route_iterator = config.toNextLeaf(_T("Route")))) {
			DEBUGLOG2(config,_T("Path: %s"),config.GetPath().c_str());
			
			long type;
			
			READCONFIGINT(config,"Type",type, 0);
			
			if (type < 0 || type > 3) {
				
				// Route type; try to recover
				wxString type_name;
				READCONFIGSTR(config,"Type_Name", type_name, _("Midi Port"));
				int i;
				
				for (i = 1; i < 4; i++)
					if (muT(RTName[i]) == type_name) break;
				
				if (i == 4) type = 0;
				else type = i;
			}
			
			long IFrom, ITo, Box, Active, OutDev, OFrom, OTo, ONoDrum;
			
			READCONFIGINT(config,"Input_from",IFrom, 0);
			READCONFIGINT(config,"Input_to",ITo, 0);
			READCONFIGINT(config,"Box",Box, 0);
			READCONFIGINT(config,"Active",Active, 1);
			READCONFIGINT(config,"Output_device",OutDev, 0);
			READCONFIGINT(config,"Output_from",OFrom, 0);
			READCONFIGINT(config,"Output_to",OTo, 15);
			READCONFIGINT(config,"No_Drum",ONoDrum, 1);
			
			in->AddRoute(new Route((RouteType) type, IFrom, ITo, Box, Active,
					       OutDevice::Get(OutDev), in, OFrom, OTo, ONoDrum));
			
			DEBUGLOG2(config,_T("Path: %s"),config.GetPath().c_str());
		}

		config.toParent(3);
		DEBUGLOG2(config,_T("Path: %s"),config.GetPath().c_str());
	}
	
	config.toParent(2);
	DEBUGLOG2(config,_T("Path: %s"),config.GetPath().c_str());
	
}
#endif


void LoadRoutes(tree_storage & config)
{
#ifdef DEBUG
	wxString oldpath = config.GetPath();
#endif
	config.toLeaf(_T("Routing"));
	
	InDevice::LoadDevices(config);
	OutDevice::LoadDevices(config);
	Route::LoadRoutes(config);
	
	config.toParent();
	wxASSERT(oldpath == config.GetPath());
}

void  SaveRoutes(tree_storage & config)
{
#ifdef DEBUG
	wxString oldpath = config.GetPath();
#endif
	config.DeleteGroup(_T("Routing"));

	config.toLeaf(_T("Routing"));
	
	// clean configuration
	// delete unused output devices
	Route::InitializeIds();
	
	InDevice::SaveDevices(config);
	OutDevice::SaveDevices(config);
	Route::SaveRoutes(config);
	
	config.toParent();
	wxASSERT(oldpath == config.GetPath());
}


/*
 * \}
 */

