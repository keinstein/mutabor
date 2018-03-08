// -*- C++ -*-
/** \file
 ********************************************************************
 * Routing. Mutabor Core.
 *
 * \author Rüdiger Krauße <krausze@mail.berlios.de>,
 * Tobias Schlemmer <keinstein@users.sourceforge.net>
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
//#include "src/kernel/GrafKern.h"

namespace mutabor {
// Route ------------------------------------------------------------
	template <> size_t idtype<RouteClass>::idpool(0);

	/*
	template <class I, class O>
	typename TRouteClass<I,O,B>::Route TRouteClass<I,O,B>::routeList;
	*/
	const std::string RTName[] =
	{
		"ALL", "ELSE", "CHANNEL", "STAFF"
	};

	template <class I, class O, class B>
	TRouteClass<I,O,B>::~TRouteClass()
	{
		DEBUGLOG (smartptr, "deleting %p" ,(void*)this);
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
		std::string oldpath = config.GetPath();
#endif
		config.Write("Input Device",  inputid);
		config.Write("Output Device", outputid);
		config.Write("Box",           boxid);
		config.Write("Active",        Active);
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
		std::string oldpath = config.GetPath();
#endif
		connect(this,BoxClass::GetOrCreateBox(config.Read("Box",NoBox)));
		Active = config.Read("Active",true);
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
		Out.reset();
		return true;
	}
	template <class I, class O, class B>
	bool TRouteClass<I,O,B>::Remove (InputDevice & in) {
		if (In != in) {
			UNREACHABLEC;
			return false;
		}
		In.reset();
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
		BoxClass::InitializeIds();
		InputDeviceClass::InitializeIds();
	}

	template <class I, class O, class B>
	void TRouteClass<I,O,B>::SaveRoutes(tree_storage & config)
	{
#ifdef DEBUG
		std::string oldpath = config.GetPath();
#endif
		config.toLeaf("Routes");

		for (typename TRouteClass<I, O>::routeListType::iterator
			     route = routeList.begin();
		     route != routeList.end(); route++) {
			config.toLeaf(("Route"),(*route)->get_routefile_id());
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
		std::string oldpath = config.GetPath();
#endif
		config.toLeaf("Routes");

		int i = config.toFirstLeaf("Route");
		while (i != wxNOT_FOUND) {
			DEBUGLOGTYPE(config,Route,("Loading route with id %d."), i);
			// \todo replace -1 by a correct default
			int inputid = config.Read("Input Device", -1);
			int outputid = config.Read("Output Device", -1);
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
				     ("route is %p (%d)"),
				     (void*)route.get(),
				     (int)intrusive_ptr_get_refcount(route.get()));
			i = config.toNextLeaf("Route");
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
#ifdef DEBUG
		bool erg =
#endif
			routeList.erase(route);
		mutASSERT(erg);
	}

	template <class I, class O, class B>
	TRouteClass<I,O,B>::operator std::string () const
	{
		return boost::str(boost::format("\
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
")
				  % (void *)userdata
				  % (void*)Out.get()
				  % (void*)In.get()
				  % routefile_id
				  % (unsigned long)session_id()
				  % inputid
				  % outputid
				  % box.get()
				  % Type
				  % IFrom
				  % ITo
				  % OFrom
				  % OTo
				  % Active
				  % ONoDrum);
	}

	template class TRouteClass<>;

	const std::string DevTypeName[] =
	{
		_mutN("Unknown"),
		_mutN("Midi Port"),
		_mutN("Midi File"),
		_mutN("GUIDO .gmn File")


	};

#define READCONFIGSTR(config,name,variable,defval)			\
        variable = config.Read((name),defval);			\
        DEBUGLOG2(config,("Read " name " = %s"),variable.c_str());

#define READCONFIGINT(config,name,variable,defval)		\
        variable = config.Read((name),defval);		\
        DEBUGLOG2(config,("Read " name " = %d"),variable);


#if 0
	void LoadRoutes(tree_storage & config)
	{
		DEBUGLOG2(config,("Loading routes."));

		if (! config.HasGroup("Input") && !config.HasGroup("Output")) return;

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

		std::string group;

		std::string defaultPortName = lib/rtmidiout->getPortCount()?
			muT(lib/rtmidiout->getPortName(0).c_str()):std::string(_("Unknown"));

		long group_number;

		// read output devices
		config.toLeaf("Output");
		DEBUGLOG2(config,"Path: %s",config.GetPath().c_str());

		group_number = config.toFirstLeaf("Device");

		for (bool test = true; // we have a default output device
		     test; test = wxNOT_FOUND != (group_number = config.toNextLeaf(("Device")))) {
			DEBUGLOG2(config,("Path: %s"),config.GetPath().c_str());
			std::string name;
			long type, id;
			READCONFIGSTR(config,"Name",name,defaultPortName);

			READCONFIGINT(config,"Type",type,1);
			if (type <= 0 || type >= DeviceMaxType) {
				// Bad device type; try to recover
				std::string type_name;
				READCONFIGSTR(config,"Type_Name",type_name, "Midi Port");

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
			std::string cwd = config.GetPath();
			out->Load(config);
		}

		config.toParent(3);
		DEBUGLOG2(config,"Path: %s",config.GetPath().c_str());

		// read input devices
		config.toLeaf("Input");
		DEBUGLOG2(config,("Path: %s"),config.GetPath().c_str());
		group_number = config.toFirstLeaf(("Device"));

		for (bool test = true; // we have a default output device
		     test; test = wxNOT_FOUND != (group_number = config.toNextLeaf(("Device")))) {
			DEBUGLOG2(config,"Path: %s",config.GetPath().c_str());

			std::string name;
			long type, id;
			READCONFIGSTR(config,"Name",name, defaultPortName);

			READCONFIGINT(config,"Type",type, 1);


			if (type <= DTUnknown || type >= DeviceMaxType) {
				// Bad device type; try to recover
				std::string type_name;
				READCONFIGSTR(config,"Type_Name",type_name, "Midi Port");


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

			config.toLeaf("Routes");
			DEBUGLOG2(config,("Path: %s"),config.GetPath().c_str());
			std::string route_group;
			long route_iterator;
			route_iterator = config.toFirstLeaf("Route");

			for (bool test2 = true; // we need a default route
			     test2; test2 = wxNOT_FOUND != (route_iterator = config.toNextLeaf("Route"))) {
				DEBUGLOG2(config,("Path: %s"),config.GetPath().c_str());

				long type;

				READCONFIGINT(config,"Type",type, 0);

				if (type < 0 || type > 3) {

					// Route type; try to recover
					std::string type_name;
					READCONFIGSTR(config,"Type_Name", type_name, "Midi Port");
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

				DEBUGLOG2(config,("Path: %s"),config.GetPath().c_str());
			}

			config.toParent(3);
			DEBUGLOG2(config,("Path: %s"),config.GetPath().c_str());
		}

		config.toParent(2);
		DEBUGLOG2(config,("Path: %s"),config.GetPath().c_str());

	}
#endif
	RouteFactory * RouteFactory::factory;

	RouteFactory::RouteFactory() {
		if (factory) {
//			UNREACHABLEC;
			BOOST_THROW_EXCEPTION( FactoryAlreadySet(factory,this));
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
		std::string oldpath = config.GetPath();
#endif
		config.toLeaf("Routing");

		BoxFactory::LoadBoxes(config);
		DeviceFactory::LoadInputDevices(config);
		DeviceFactory::LoadOutputDevices(config);
		RouteClass::LoadRoutes(config);

		config.toParent();
		mutASSERT(oldpath == config.GetPath());
	}

	void  RouteFactory::DoSaveRoutes(tree_storage & config) const
	{
#ifdef DEBUG
		std::string oldpath = config.GetPath();
#endif
		config.DeleteGroup(("Routing"));

		config.toLeaf(("Routing"));

		// clean configuration
		// delete unused output devices
		RouteClass::InitializeIds();
#ifdef DEBUG
		mutaborGUI::DebugCheckRoutes();
#endif

		BoxFactory::SaveBoxes(config);
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

