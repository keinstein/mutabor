// -*- C++ -*-
/** \file
 ********************************************************************
 * Routing. Mutabor Core.
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/mu32/routing/Route.cpp,v 1.7 2011/09/30 09:10:24 keinstein Exp $
 * \author Rüdiger Krauße <krausze@mail.berlios.de>,
 * Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 1998
 * $Date: 2011/09/30 09:10:24 $
 * \version $Revision: 1.7 $
 * \license GPL
 *
 * $Log: Route.cpp,v $
 * Revision 1.7  2011/09/30 09:10:24  keinstein
 * Further improvements in the routing system.
 *
 * Revision 1.6  2011-09-27 20:13:21  keinstein
 * * Reworked route editing backend
 * * rewireing is done by RouteClass/GUIRoute now
 * * other classes forward most requests to this pair
 * * many bugfixes
 * * Version change: We are reaching beta phase now
 *
 * Revision 1.5  2011-09-09 09:29:10  keinstein
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

#include "mu32/routing/Route.h"
#include "mu32/routing/Route-inlines.h"
#include "Device.h"
#include <algorithm>
#include "muwx/Routing/DebugRoute.h"

namespace mutabor {
// Route ------------------------------------------------------------

	template <class I, class O>
	int TRouteClass<I,O>::maxRouteId = 1;

/*
	template <class I, class O>
	typename TRouteClass<I,O>::Route TRouteClass<I,O>::routeList;
*/
	const mutString RTName[] =
	{
		_T("ALL"), _T("ELSE"), _T("CHANNEL"), _T("STAFF")
	};

	template <class I, class O>
	TRouteClass<I,O>::~TRouteClass() 
	{
		DEBUGLOG(smartptr,_T("deleting %p"),this);
#ifdef DEBUG
		typename routeListType::iterator r = 
			std::find(routeList.begin(),
				  routeList.end(),
				  this);
		wxASSERT(r == routeList.end());
#endif
	}


	template <class I, class O>
	void TRouteClass<I,O>::Save(tree_storage & config) 
	{
#ifdef DEBUG
		wxString oldpath = config.GetPath();
#endif
		config.Write(_T("Box"),Box);
		config.Write(_T("Active"),Active);
		if (In)
			In->Save(config,this);
		if (Out)
			Out->Save(config,this);
		wxASSERT(oldpath == config.GetPath());
	}

	template <class I, class O>
	void TRouteClass<I,O>::Load(tree_storage & config) 
	{
#ifdef DEBUG
		wxString oldpath = config.GetPath();
#endif
		SetBox(config.Read(_T("Box"),NoBox));
		Active = config.Read(_T("Active"),true);
		if (In)
			In->Load(config,this);
		if (Out)
			Out->Load(config,this);
		wxASSERT(oldpath == config.GetPath());
	}

	template <class I, class O>
	void TRouteClass<I,O>::setUserData (void * data) 
	{ 
		userdata = data; 
	}

	template <class I, class O>
	void * TRouteClass<I,O>::getUserData() const 
	{ 
		return userdata; 
	}


	template <class I, class O>
	void TRouteClass<I,O>::Add (OutputDevice out) {
		Out = out;
	}
	template <class I, class O>
	void TRouteClass<I,O>::Add (InputDevice in) {
		In = in;
	}
	template <class I, class O>
	void TRouteClass<I,O>::Add (int id) {
		SetBox(id);
	}

	template <class I, class O>
	bool TRouteClass<I,O>::Replace (OutputDevice olddev,
					      OutputDevice newdev) {
		if (Out != olddev) {
			UNREACHABLEC;
			return false;
		}
		Out = newdev;
		return true;
	}
	template <class I, class O>
	bool TRouteClass<I,O>::Replace (InputDevice olddev,
					      InputDevice newdev) {
		if (In != olddev) {
			UNREACHABLEC;
			return false;
		}
		In = newdev;
		return true;
	}
	template <class I, class O>
	bool TRouteClass<I,O>::Replace (int oldbox,
					   int newbox) {
		if (Box != oldbox) {
			UNREACHABLEC;
			return false;
		}
		SetBox(newbox);
		return true;
	}

	template <class I, class O>
	bool TRouteClass<I,O>::Remove (OutputDevice out) {
		if (out != Out) {
			UNREACHABLEC;
			return false;
		}
		Out = NULL;
		return true;
	}
	template <class I, class O>
	bool TRouteClass<I,O>::Remove (InputDevice in) {
		if (In != in) {
			UNREACHABLEC;
			return false;
		}
		In = NULL;
		return true;
	}
	template <class I, class O>
	bool TRouteClass<I,O>::Remove (int id) {
		if (Box != id) {
			UNREACHABLEC;
			return false;
		}
		SetBox(NoBox);
		return true;
	}
	

	template <class I, class O>
	void TRouteClass<I,O>::InitializeIds() 
	{
		OutputDeviceClass::InitializeIds();
		int i = 0;
		for (typename routeListType::iterator r = routeList.begin();
		     r != routeList.end(); r++) {
			(*r) -> Id = i++;
		}
		InputDeviceClass::InitializeIds();
	}

	template <class I, class O>
	void TRouteClass<I,O>::SaveRoutes(tree_storage & config) 
	{
#ifdef DEBUG
		wxString oldpath = config.GetPath();
#endif
		config.toLeaf(_T("Routes"));

		for (typename TRouteClass<I, O>::routeListType::iterator  
			     route = routeList.begin();
		     route != routeList.end(); route++) {
			config.toLeaf(_T("Route"),(*route)->GetId());
			config.Write(_T("Input Device"), (*route)->inputid);
			config.Write(_T("Output Device"), (*route)->outputid);
			(*route) -> Save (config);
			config.toParent();
		}
	
		config.toParent();	
		wxASSERT(oldpath == config.GetPath());
	}

	template <class I, class O>
	void TRouteClass<I,O>::LoadRoutes(tree_storage & config) 
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
			InputDevice in = InputDeviceClass::GetDevice(inputid);
			OutputDevice out = OutputDeviceClass::GetDevice(outputid);
			Route route = RouteFactory::Create(in,out);
			if (route)
				route -> Load(config);
			i = config.toNextLeaf(_T("Route"));
		}
	
		config.toParent(2);
		wxASSERT(oldpath == config.GetPath());
	}


	template <class I, class O>
	void TRouteClass<I,O>::AppendToRouteList (Route  route) 
	{
#ifdef DEBUG
		typename TRouteClass<I, O>::routeListType::iterator r = 
			std::find(routeList.begin(),
				  routeList.end(),
				  route);
		wxASSERT(r == routeList.end());
#endif
		routeList.push_back(route);
	}

	template <class I, class O>
	void TRouteClass<I,O>::RemoveFromRouteList (Route route) 
	{
		typename TRouteClass<I, O>::routeListType::iterator r = 
			std::find(routeList.begin(),
				  routeList.end(),
				  route);
		wxASSERT(r != routeList.end());
		if (r != routeList.end()) {
			routeList.erase(r);
		}
	}

	template <class I, class O>
	wxString TRouteClass<I,O>::TowxString () const 
	{
		return wxString::Format(_T("\
TRouteClass<I,O>:\n\
   userdata = %p\n\
   Out      = %p\n\
   In       = %p\n\
   Id       = %d\n\
   inputid  = %d\n\
   outputid = %d\n\
   Box      = %d\n\
   Type     = %d\n\
   IFrom    = %d\n\
   ITo      = %d\n\
   OFrom    = %d\n\
   OTo      = %d\n\
   flags:     Active:%d, ONoDrum:%d\n\
"),(void *)userdata,Out.get(),In.get(),inputid,outputid,Box,Type,IFrom,ITo,OFrom,OTo,
					Active,ONoDrum);
	}

	template class TRouteClass<>;

	const mutString DevTypeName[] =
	{
		N_("Unknown"),
		N_("Midi Port"),
		N_("Midi File"),
		N_("GUIDO .gmn File")


	};

#define READCONFIGSTR(config,name,variable,defval)			\
        variable = config.Read(_T(name),defval);			\
        DEBUGLOG2(config,_T("Read " name " = %s"),variable.c_str());

#define READCONFIGINT(config,name,variable,defval)		\
        variable = config.Read(_T(name),defval);		\
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
	
		Route  Routes = Route :: GetRouteList();
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
	RouteFactory * RouteFactory::factory;

	RouteFactory::RouteFactory() {
		if (factory) {
			UNREACHABLEC;
			delete factory;
			factory = this;
		} else factory = this;
	}
	RouteFactory::~RouteFactory() {}

	Route RouteFactory::DoCreate() const
	{
		return new RouteClass ();
	}

	Route RouteFactory::DoCreate(InputDevice in,
				     OutputDevice out,
				     RouteType type,
				     int iFrom,
				     int iTo,
				     int box,
				     bool active,
				     int oFrom,
				     int oTo,
				     bool oNoDrum/*,
						   Route next*/) const
	{
		return new RouteClass (in,out,type,
				       iFrom,iTo,
				       box,active,
				       oFrom,oTo,
				       oNoDrum/*,next*/);
	}

	void RouteFactory::DoLoadRoutes(tree_storage & config) const
	{
#ifdef DEBUG
		wxString oldpath = config.GetPath();
#endif
		config.toLeaf(_T("Routing"));
	
		DeviceFactory::LoadInputDevices(config);
		DeviceFactory::LoadOutputDevices(config);
		RouteClass::LoadRoutes(config);
	
		config.toParent();
		wxASSERT(oldpath == config.GetPath());
	}

	void  RouteFactory::DoSaveRoutes(tree_storage & config) const
	{
#ifdef DEBUG
		wxString oldpath = config.GetPath();
#endif
		config.DeleteGroup(_T("Routing"));

		config.toLeaf(_T("Routing"));
	
		// clean configuration
		// delete unused output devices
		RouteClass::InitializeIds();
		mutaborGUI::DebugCheckRoutes();
	
		DeviceFactory::SaveInputDevices(config);
		DeviceFactory::SaveOutputDevices(config);
		RouteClass::SaveRoutes(config);
	
		config.toParent();
		wxASSERT(oldpath == config.GetPath());
	}

}


/*
 * \}
 */

