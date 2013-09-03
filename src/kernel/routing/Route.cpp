// -*- C++ -*-
/** \file
 ********************************************************************
 * Routing. Mutabor Core.
 *
 $
 * \author Rüdiger Krauße <krausze@mail.berlios.de>,
 * Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 1998
 * $Date: 2011/10/02 16:58:41 $
 * \version $Revision: 1.9 $
 * \license GPL
 *
 *
 *
 ********************************************************************
 *\addtogroup route
 *\{
 ********************************************************************/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "src/kernel/routing/Route.h"
#include "src/kernel/routing/Route-inlines.h"
#include "Device.h"
#include <algorithm>
#include "src/wxGUI/Routing/DebugRoute.h"
#include "src/kernel/GrafKern.h"

namespace mutabor {
// Route ------------------------------------------------------------
	template <> size_t idtype<RouteClass>::idpool(0);


	Route NullRoute(NULL); 

	/*
	template <class I, class O>
	typename TRouteClass<I,O,B>::Route TRouteClass<I,O,B>::routeList;
	*/
	const mutString RTName[] =
	{
		_T("ALL"), _T("ELSE"), _T("CHANNEL"), _T("STAFF")
	};

	template <class I, class O, class B>
	TRouteClass<I,O,B>::~TRouteClass() 
	{
		DEBUGLOG(smartptr,_T("deleting %p"),(void*)this);
#ifdef DEBUG
		typename routeListType::iterator r = 
			std::find(routeList.begin(),
				  routeList.end(),
				  this);
		mutASSERT(r == routeList.end());
		TRACEC;
#endif
		debug_destruct_class(this);
	}


	template <class I, class O, class B>
	void TRouteClass<I,O,B>::Save(tree_storage & config) 
	{
#ifdef DEBUG
		wxString oldpath = config.GetPath();
#endif
		config.Write(_T("Box"),box);
		config.Write(_T("Active"),Active);
		if (In)
			In->Save(config,this);
		if (Out)
			Out->Save(config,this);
		mutASSERT(oldpath == config.GetPath());
	}

	template <class I, class O, class B>
	void TRouteClass<I,O,B>::Load(tree_storage & config) 
	{
#ifdef DEBUG
		wxString oldpath = config.GetPath();
#endif
		SetBox(BoxClass::GetOrCreateBox(config.Read(_T("Box"),NoBox)));
		Active = config.Read(_T("Active"),true);
		if (In)
			In->Load(config,this);
		if (Out)
			Out->Load(config,this);
		mutASSERT(oldpath == config.GetPath());
	}

#if 0
	template <class I, class O, class B>
	int TRouteClass<I,O,B>::GetNextFreeBox ()
	{
		int retval = 0;
		bool changed = false;
		const routeListType & list = GetRouteList();
		typename routeListType::const_iterator begin = list.begin();
		typename routeListType::const_iterator end = list.end();
		do {
			changed = false;
			for (typename routeListType::const_iterator i = begin;
			     i != end;
			     i++) {
				if ((*i)->GetBox() == retval) {
					retval++;
					changed = true;
				}
			}
		} while (changed);
		return retval;
	}
#endif
	

	template <class I, class O, class B>
	void TRouteClass<I,O,B>::setUserData (void * data) 
	{ 
		userdata = data; 
	}

	template <class I, class O, class B>
	void * TRouteClass<I,O,B>::getUserData() const 
	{ 
		return userdata; 
	}


	template <class I, class O, class B>
	void TRouteClass<I,O,B>::Add (OutputDevice & out) {
		Out = out;
	}
	template <class I, class O, class B>
	void TRouteClass<I,O,B>::Add (InputDevice & in) {
		In = in;
	}
	template <class I, class O, class B>
	void TRouteClass<I,O,B>::Add (Box & b) {
		SetBox(b);
	}

	template <class I, class O, class B>
	bool TRouteClass<I,O,B>::Replace (OutputDevice & olddev,
					OutputDevice & newdev) {
		if (Out != olddev) {
			UNREACHABLEC;
			return false;
		}
		Out = newdev;
		return true;
	}
	template <class I, class O, class B>
	bool TRouteClass<I,O,B>::Replace (InputDevice & olddev,
					InputDevice & newdev) {
		if (In != olddev) {
			UNREACHABLEC;
			return false;
		}
		In = newdev;
		return true;
	}
	template <class I, class O, class B>
	bool TRouteClass<I,O,B>::Replace (Box & oldbox,
					  Box & newbox) {
		if (box != oldbox) {
			UNREACHABLEC;
			return false;
		}
		SetBox(newbox);
		return true;
	}

	template <class I, class O, class B>
	bool TRouteClass<I,O,B>::Remove (OutputDevice & out) {
		if (out != Out) {
			UNREACHABLEC;
			return false;
		}
		Out = NULL;
		return true;
	}
	template <class I, class O, class B>
	bool TRouteClass<I,O,B>::Remove (InputDevice & in) {
		if (In != in) {
			UNREACHABLEC;
			return false;
		}
		In = NULL;
		return true;
	}
	template <class I, class O, class B>
	bool TRouteClass<I,O,B>::Remove (Box & b ) {
		if (box != b) {
			UNREACHABLEC;
			return false;
		}
		SetBox(NULL);
		return true;
	}
	

	template <class I, class O, class B>
	void TRouteClass<I,O,B>::InitializeIds() 
	{
		OutputDeviceClass::InitializeIds();
		int i = 0;
		for (typename routeListType::iterator r = routeList.begin();
		     r != routeList.end(); r++) {
			(*r) -> routefile_id = i++;
		}
		InputDeviceClass::InitializeIds();
	}

	template <class I, class O, class B>
	void TRouteClass<I,O,B>::SaveRoutes(tree_storage & config) 
	{
#ifdef DEBUG
		wxString oldpath = config.GetPath();
#endif
		config.toLeaf(_T("Routes"));

		for (typename TRouteClass<I, O>::routeListType::iterator  
			     route = routeList.begin();
		     route != routeList.end(); route++) {
			config.toLeaf(_T("Route"),(*route)->get_routefile_id());
			config.Write(_T("Input Device"), (*route)->inputid);
			config.Write(_T("Output Device"), (*route)->outputid);
			(*route) -> Save (config);
			config.toParent();
		}
	
		config.toParent();	
		mutASSERT(oldpath == config.GetPath());
	}

	template <class I, class O, class B>
	void TRouteClass<I,O,B>::LoadRoutes(tree_storage & config) 
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
			TRACET(thistype);
			InputDevice in = InputDeviceClass::GetDevice(inputid, Device::IDTypeFile);
			TRACET(thistype);
			OutputDevice out = OutputDeviceClass::GetDevice(outputid, Device::IDTypeFile);
			TRACET(thistype);
			Route route = RouteFactory::Create(in,out);
			TRACET(thistype);
			if (route)
				route -> Load(config);
			DEBUGLOGTYPE(smartptr,thistype,
				     _T("route is %p (%d)"),
				     (void*)route.get(),
				     (int)intrusive_ptr_get_refcount(route.get()));
			i = config.toNextLeaf(_T("Route"));
		}
	
		config.toParent(2);
		mutASSERT(oldpath == config.GetPath());
	}


	template <class I, class O, class B>
	void TRouteClass<I,O,B>::AppendToRouteList (Route  route) 
	{
#ifdef DEBUG
		typename TRouteClass<I, O>::routeListType::iterator r = 
			std::find(routeList.begin(),
				  routeList.end(),
				  route.get());
		mutASSERT(r == routeList.end());
#endif
		TRACET(thistype);
		routeList.push_back(route);
	}

	template <class I, class O, class B>
	void TRouteClass<I,O,B>::RemoveFromRouteList (Route route) 
	{
		typename TRouteClass<I, O>::routeListType::iterator r = 
			std::find(routeList.begin(),
				  routeList.end(),
				  route.get());
		mutASSERT(r != routeList.end());

		if (r != routeList.end()) {
			routeList.erase(r);
		}
	}

	template <class I, class O, class B>
	wxString TRouteClass<I,O,B>::TowxString () const 
	{
		return wxString::Format(_T("\
TRouteClass<I,O,B>:\n\
   userdata = %p\n\
   Out      = %p\n\
   In       = %p\n\
   fileid   = %d\n\
   sess.id  = %lu\n\
   inputid  = %d\n\
   outputid = %d\n\
   Box      = %p\n\
   Type     = %d\n\
   IFrom    = %d\n\
   ITo      = %d\n\
   OFrom    = %d\n\
   OTo      = %d\n\
   flags:     Active:%d, ONoDrum:%d\n\
"),(void *)userdata,(void*)Out.get(),(void*)In.get(),routefile_id,(unsigned long)session_id(),inputid,outputid,box.get(),Type,IFrom,ITo,OFrom,OTo,
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
	
		wxString defaultPortName = lib/rtmidiout->getPortCount()?
			muT(lib/rtmidiout->getPortName(0).c_str()):wxString(_("Unknown"));
	
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
//			UNREACHABLEC;
			throw FactoryAlreadySet(factory,this);
			/*
			  delete factory;
			  factory = this;
			*/
			
		} else factory = this;
	}
	RouteFactory::~RouteFactory() {}

	RouteClass * RouteFactory::DoCreate() const
	{
		return new RouteClass ();
	}

	RouteClass * RouteFactory::DoCreate(InputDevice & in,
					    OutputDevice & out,
					    RouteType type,
					    int iFrom,
					    int iTo,
					    Box box,
					    bool active,
					    int oFrom,
					    int oTo,
					    bool oNoDrum) const
	{
		return new RouteClass (in,out,type,
				       iFrom,iTo,
				       box,active,
				       oFrom,oTo,
				       oNoDrum);
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
		mutASSERT(oldpath == config.GetPath());
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
#ifdef DEBUG
		mutaborGUI::DebugCheckRoutes();
#endif
	
		DeviceFactory::SaveInputDevices(config);
		DeviceFactory::SaveOutputDevices(config);
		RouteClass::SaveRoutes(config);
	
		config.toParent();
		mutASSERT(oldpath == config.GetPath());
	}


}


/*
 * \}
 */

