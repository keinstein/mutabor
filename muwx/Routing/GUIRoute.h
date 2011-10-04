/** \file               -*- C++ -*-
 ********************************************************************
 * Interface to separate Mutabor functionality from the GUI
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/muwx/Routing/GUIRoute.h,v 1.4 2011/10/04 17:16:14 keinstein Exp $
 * Copyright:   (c) 2011 TU Dresden
 * \author  Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 
 * $Date: 2011/10/04 17:16:14 $
 * \version $Revision: 1.4 $
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
 * $Log: GUIRoute.h,v $
 * Revision 1.4  2011/10/04 17:16:14  keinstein
 * make program compile on Mac (wx 2.9) and fix some memory corruption
 *
 * Revision 1.3  2011-10-02 16:58:42  keinstein
 * * generate Class debug information when compile in debug mode
 * * InputDeviceClass::Destroy() prevented RouteClass::Destroy() from clearing references -- fixed.
 * * Reenable confirmation dialog when closing document while the logic is active
 * * Change debug flag management to be more debugger friendly
 * * implement automatic route/device deletion check
 * * new debug flag --debug-trace
 * * generate lots of tracing output
 *
 * Revision 1.2  2011-09-30 18:07:05  keinstein
 * * make compile on windows
 * * s/wxASSERT/mutASSERT/g to get assert handler completely removed
 * * add ax_boost_base for boost detection
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

/* we guard a little bit complicated to ensure the references are set right
 */

#if (!defined(MUWX_ROUTING_GUIROUTE_H) && !defined(PRECOMPILE)) \
	|| (!defined(MUWX_ROUTING_GUIROUTE_H_PRECOMPILED))
#ifndef PRECOMPILE
#define MUWX_ROUTING_GUIROUTE_H
#endif

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

#include "Defs.h"
#include "mu32/routing/Device.h"
#include "mu32/routing/midi/DevMidi.h"
#include "mu32/routing/midi/DevMidF.h"
#include "mu32/routing/gmn/DevGIS.h"
#include "mu32/routing/Route.h"
#include "muwx/GUIBoxData.h"
#include "muwx/Routing/RouteLists.h"

#ifndef MUWX_ROUTING_GUIROUTE_H_PRECOMPILED
#define MUWX_ROUTING_GUIROUTE_H_PRECOMPILED

// system headers which do seldom change

#include <algorithm>

class wxWindow;

namespace mutaborGUI {
	class GUIRouteBase;
	template<class T> class TGUIRoute;

 	class GUIInputDeviceBase;
	const GUIInputDeviceBase & ToGUIBase(const mutabor::InputDevice & d);
	GUIInputDeviceBase & ToGUIBase(mutabor::InputDevice & d);
 	class GUIOutputDeviceBase;
	const GUIOutputDeviceBase & ToGUIBase(const mutabor::OutputDevice & d);
	GUIOutputDeviceBase & ToGUIBase(mutabor::OutputDevice & d);


	template<class T> 
	class GUIfyRoute: public T {
		friend class GUIRouteBase;
	protected:
		typedef TGUIRoute<T> GUIData;
		virtual void setUserData (void * data) 
			{ 
				GetGUIRoute().setUserData(data);
				UNREACHABLEC;
			}

		virtual void * getUserData()
			{ 
				UNREACHABLEC;
				return GetGUIRoute().getUserData();; 
			}
		void SetGUIRoute (GUIRouteBase * r) {
			mutabor::RouteClass::setUserData(r);
		}
	public:
		virtual ~GUIfyRoute() { 
			GUIRouteBase * gui = &GetGUIRoute();
			mutASSERT(gui);
			delete gui;
			TRACEC; 
		}
		GUIData & GetGUIRoute() 
			{
				void * d = mutabor::RouteClass::getUserData();
				return *((GUIData *)d);
			}
		const GUIData & GetGUIRoute() const
			{
				void * d = mutabor::RouteClass::getUserData();
				return *((GUIData *)d);
			}

		virtual void SetBox(int box) {
			T::SetBox(box);
			GetGUIRoute().ReconfigureBox();
		}

		static void Add(MutBoxShape * shape) {
			if (T::Box >= 0) {
				BoxData::GetBox(T::Box).Add(shape);
			} else {
				UNREACHABLECT(GUIRouteBase);
			}
		}
		static bool Remove(MutBoxShape * shape) {
			if (T::Box >= 0) {
				return BoxData::GetBox(T::Box).Remove(shape);
			} else {
				UNREACHABLECT(GUIRouteBase);
			}
		}

		
		/// Attatch a new output device
		virtual void Attatch (mutabor::OutputDevice & dev);
		/// Attatch a new input device
		virtual void Attatch (mutabor::InputDevice & dev);
		/// Replace current output device with a new one
		virtual bool Reconnect(mutabor::OutputDevice & olddev, 
				       mutabor::OutputDevice & newdev);
		/// Replace current input device with a new one
		virtual bool Reconnect(mutabor::InputDevice & olddev,
				       mutabor::InputDevice & newdev);
		/// Detatch current output device
		virtual bool Detatch(mutabor::OutputDevice & dev);
		/// Detatch current input device
		virtual bool Detatch(mutabor::InputDevice & dev);


		// Handle the box
		/// Attatch a new box
		virtual void Attatch (int id);
		/// Replace by a new one
		virtual bool Reconnect(int oldboxid,
			       int newboxid);
		/// Detach a current box
		virtual bool Detatch(int boxid);


		static void Attatch(MutBoxShape * shape) {
			if (T::Box >= 0)
				BoxData::GetBox(T::Box).Attatch(shape);
			else {
				UNREACHABLECT(GUIRouteBase);
			}
		}
		static bool Detatch(MutBoxShape * shape) {
			if (T::Box >= 0)
				return BoxData::GetBox(T::Box).Detatch(shape);
			else {
				UNREACHABLECT(GUIRouteBase);
			}
		}
		static bool Delete(MutBoxShape * shape) {
			if (T::Box >= 0) 
				return BoxData::GetBox(T::Box).Delete(shape);
			else {
				UNREACHABLECT(GUIRouteBase);
			}
		}

		void Add(MutBoxChannelShape * shape) {
			GetGUIRoute().Add(shape);
		}
		bool Remove(MutBoxChannelShape * shape) {
			return GetGUIRoute().Remove(shape);
		}

		void Attatch(MutBoxChannelShape * shape) {
			return GetGUIRoute().Attatch(shape);
		}

		bool Detatch(MutBoxChannelShape * shape) {
			DEBUGLOG(smartptr,_T("Route: %p (%d), disconnecting shapes"),
				 this, 
				 intrusive_ptr_get_refcount(this));
			return GetGUIRoute().Detatch(shape);
		}

		bool Delete(MutBoxChannelShape * shape) {
			return GetGUIRoute().Delete(shape);
		}

		virtual void Destroy();
	};



	class GUIRouteBase {
	protected:
		mutabor::RouteClass * route;
		void * userdata;
		BoxData * box;
		MutBoxChannelShapeList shapes;
	public:
//		GUIRouteBase():Route(),userdata(NULL),boxShapes(),shapes() {}
 		virtual ~GUIRouteBase() {
			TRACEC;
			Destroy();
		}

		virtual void * getUserData() {
			return userdata;
		}
		virtual void setUserData(void * data) {
			userdata = data;
		}

		bool IsRoute(const mutabor::RouteClass * r) const {
			return route == r;
		}

		mutabor::RouteClass * GetRoute() {
			return route;
		}

		operator mutabor::RouteClass & () {
			return *route;
		}

		void ReconfigureBox() {
			box = &(BoxData::GetBox(route->GetBox()));
			DEBUGLOG(routing, _T("Set Box data to %p from id %d"),
				 box, route->GetBox());
		}

		const BoxData * GetBoxData() const {
			return box;
		}

		BoxData * GetBoxData() {
			return box;
		}

		const MutBoxShapeList & GetBoxShapes() const {
			if (!box) {
				UNREACHABLECT(GUIRouteBase);
			}
			return box->GetBoxShapes();
		}
		void Add(MutBoxShape * shape) {
			if (box) {
				 box->Add(shape);
			} else {
				UNREACHABLECT(GUIRouteBase);
			}
		}
		bool Remove(MutBoxShape * shape) {
			if (box) {
				return box->Remove(shape);
			} else {
				UNREACHABLECT(GUIRouteBase);
				return false;
			}
		}

		/// Attatch a new output device
		virtual void Attatch (mutabor::OutputDevice & dev);
		/// Attatch a new input device
		virtual void Attatch (mutabor::InputDevice & dev);
		/// Replace current output device with a new one
		virtual bool Reconnect(mutabor::OutputDevice & olddev, 
				       mutabor::OutputDevice & newdev);
		/// Replace current input device with a new one
		virtual bool Reconnect(mutabor::InputDevice & olddev,
				       mutabor::InputDevice & newdev);
		/// Detatch current output device
		virtual bool Detatch(mutabor::OutputDevice & dev);
		/// Detatch current input device
		virtual bool Detatch(mutabor::InputDevice & dev);

		/// Attatch a new box
		virtual void Attatch (int boxid);
		/// Replace by a new one
		virtual bool Reconnect(int oldboxid,
				       int newboxid);
		/// Detach a current box
		virtual bool Detatch(int boxid);

		void Attatch(MutBoxShape * shape) {
			if (box)
				box->Attatch(shape);
			else {
				UNREACHABLECT(GUIRouteBase);
			}
		}
		bool Detatch(MutBoxShape * shape) {
			if (box)
				return box->Detatch(shape);
			else {
				UNREACHABLECT(GUIRouteBase);
				return false;
			}
		}
		bool Delete(MutBoxShape * shape) {
			if (box) 
				return box -> Delete(shape);
			else {
				UNREACHABLECT(GUIRouteBase);
				return false;
			}
		}
		bool Reconnect(MutBoxShape * oldshape,
			       MutBoxShape * newshape);
			     

		const MutBoxChannelShapeList & 
		GetBoxChannelShapes() const {
			return shapes;
		}
		void Add(MutBoxChannelShape * shape);
		bool Remove(MutBoxChannelShape * shape);

		void Attatch(MutBoxChannelShape * shape);
		bool Detatch(MutBoxChannelShape * shape);
		bool Delete(MutBoxChannelShape * shape);
		
		virtual void Destroy();

		/// return the shape that corresponds to the current window
		/** To use common naming the window is named parent
		    though it is actually the grandparent of the
		    returned channel shape 

		    \param parent wxWindow* window which shall contain
		    the searched shape
		    \return shape displaying this on window parent.
		*/
		MutBoxChannelShape * GetShape(wxWindow * parent);

	protected:

		void InitializeRoute() {
			if (route) 
				static_cast<GUIfyRoute
					<mutabor::RouteClass> *>(route)
					-> SetGUIRoute (this);
			ReconfigureBox();
		}
	};


	template<class T>
	class TGUIRoute: public GUIRouteBase {
	public:
		typedef T RouteType;
		operator RouteType & () {
			return *static_cast<RouteType *>(route);
		}

		virtual ~TGUIRoute() { TRACEC; }
	};

	/// Prototype of any GUI based route class
	/** This class is the prototype for any GUI based route.
	    Since the base class remains RouteClass we must not 
	    any fields to it.
	*/
	

	class GUIfiedRoute: public GUIfyRoute<mutabor::RouteClass> {
		friend class GUIRoute;
		friend class GUIRouteFactory;
	protected:
		GUIfiedRoute(void * gui,
			     mutabor::InputDevice & in,
			     mutabor::OutputDevice & out,
			     mutabor::RouteType type = mutabor::RTall,
			     int iFrom = -1,
			     int iTo = -1,
			     int box = -1,
			     bool active = false,
			     int oFrom = -1,
			     int oTo = -1,
			     bool oNoDrum = true/*,
						  mutabor::Route next
		= NULL*/):

			GUIfyRoute<mutabor::RouteClass>() {
			DEBUGLOG(smartptr,_T("Route; %p (%d), entering create"),
				 this, 
				 intrusive_ptr_get_refcount(this));

			mutabor::TRouteClass<
				InputDevice,
				OutputDevice
				>::setUserData(gui);
			mutabor::TRouteClass<
				InputDevice,
				OutputDevice
				>::Create(in,out,type,
					    iFrom,iTo,
					    box,active,
					    oFrom, oTo, oNoDrum/*,
								 next*/);
			DEBUGLOG(smartptr,_T("Route; %p (%d), after create"),
				 this, 
				 intrusive_ptr_get_refcount(this));
		}
		
		virtual ~GUIfiedRoute() { TRACEC; }
	};

	class GUIRoute:public TGUIRoute<GUIfiedRoute> {
		friend class GUIRouteFactory;
	protected:

		GUIRoute():TGUIRoute<GUIfiedRoute>() {
			mutabor::InputDevice in;
			mutabor::OutputDevice out;

			route = new GUIfiedRoute(this,
						 in,out);
			DEBUGLOG(smartptr,_T("Route; %p (%d), entering create"),
				 route, 
				 intrusive_ptr_get_refcount(route));
			InitializeRoute();
			DEBUGLOG(smartptr,_T("Route; %p (%d), entering create"),
				 route, 
				 intrusive_ptr_get_refcount(route));
			ReconfigureBox();
			DEBUGLOG(smartptr,_T("Route; %p (%d), entering create"),
				 route, 
				 intrusive_ptr_get_refcount(route));
		}
		GUIRoute(mutabor::InputDevice & in,
			 mutabor::OutputDevice & out,
			 mutabor::RouteType type = mutabor::RTall,
			 int iFrom = -1,
			 int iTo = -1,
			 int box = -1,
			 bool active = false,
			 int oFrom = -1,
			 int oTo = -1,
			 bool oNoDrum = true
/*, mutabor::Route next = NULL*/
			):TGUIRoute<GUIfiedRoute>() {
			DEBUGLOG(smartptr,_T("Route: %8p, entering create"),
				 (void *)route//, 
				 /* leeds to errors 
				    intrusive_ptr_get_refcount(route)*/);
			route = new GUIfiedRoute(this,
						 in,out,type,
						 iFrom,iTo,box,active,
						 oFrom,oTo,oNoDrum/*,next*/);
			DEBUGLOG(smartptr,_T("Route; %p (%d), entering create"),
				 route, 
				 intrusive_ptr_get_refcount(route));
			InitializeRoute();
			DEBUGLOG(smartptr,_T("Route; %p (%d), entering create"),
				 route, 
				 intrusive_ptr_get_refcount(route));
			ReconfigureBox();
			DEBUGLOG(smartptr,_T("Route; %p (%d), entering create"),
				 route, 
				 intrusive_ptr_get_refcount(route));
		}
		
	public:
		virtual ~GUIRoute() { TRACEC; }

	};

	inline  const GUIRouteBase & ToGUIBase(
		const mutabor::RouteClass * r) {
		mutASSERT(dynamic_cast<const GUIfiedRoute *>(r));
		mutASSERT(((static_cast<const GUIfiedRoute *>(r))
			  -> GetGUIRoute()).IsRoute(r));
		
		return static_cast<const GUIfiedRoute *>(r) 
			-> GetGUIRoute();
	}

	inline  GUIRouteBase & ToGUIBase(mutabor::RouteClass * r) {
		mutASSERT(dynamic_cast<GUIfiedRoute *>(r));
		mutASSERT(((static_cast<GUIfiedRoute *>(r))
			  -> GetGUIRoute()).IsRoute(r));
		
		return static_cast<GUIfiedRoute *>(r) 
			-> GetGUIRoute();
	}

	inline  const GUIRouteBase & ToGUIBase(const mutabor::Route & r) {
		return ToGUIBase(r.get());
	}
	inline  GUIRouteBase & ToGUIBase(mutabor::Route & r) {
		return ToGUIBase(r.get());
	}

	class GUIRouteFactory:public mutabor::RouteFactory { 
	public:
		GUIRouteFactory() {};
		virtual ~GUIRouteFactory() {};

	protected:
		virtual mutabor::RouteClass * DoCreate() const
			__attribute__ ((malloc));
		virtual mutabor::RouteClass * DoCreate(
			mutabor::InputDevice & in,
			mutabor::OutputDevice & out,
			mutabor::RouteType type,
			int iFrom,
			int iTo,
			int box,
			bool active,
			int oFrom,
			int oTo,
			bool oNoDrum /*,
				       Route next*/) const __attribute__ ((malloc));
		virtual MutBoxShape * DoCreateBoxShape(int box,
			wxWindow * parent) const;

		virtual MutBoxChannelShape * 
		DoCreateBoxChannelShape (mutabor::Route & route,
					 wxWindow * parent) const;
	public:
		static MutBoxShape * CreateBoxShape(int box,
						    wxWindow * parent) {
			mutASSERT(dynamic_cast<GUIRouteFactory *> (factory));
			return ((GUIRouteFactory *)factory)->
				DoCreateBoxShape(box,parent);
		}
			
		static MutBoxChannelShape * CreateBoxChannelShape(
			mutabor::Route & route,
			wxWindow * parent) {
			return ((GUIRouteFactory *)factory)->
				DoCreateBoxChannelShape(route,parent);
		}
	};

/********************************************************************************/
	class GUIOutputDeviceBase;	
	template<class T> class TGUIOutputDevice;

	template<class T> T * static_cast_to(mutabor::OutputDevice & o,
					     T * type) {
		return static_cast<T *>(o.get());
	}
	template<class T> T * dynamic_cast_to(mutabor::OutputDevice & o,
					     T * type) {
		return dynamic_cast<T *>(o.get());
	}
	template<class T> const T * static_cast_to(const mutabor::OutputDevice & o,
					     const T * type) {
		return static_cast<const T *>(o.get());
	}
	template<class T> const T * dynamic_cast_to(const mutabor::OutputDevice & o,
					     const T * type) {
		return dynamic_cast<const T *>(o.get());
	}

	/// Prototype of any GUI based output device class
	/** This class is the prototype for any GUI based output device.
	    Since the base class remains OutputDeviceClass we must not 
	    add any fields or new virtal functions to it. Overloading of 
	    existing virtals should be allowed.
	*/

	template<class T> 
	class GUIfyOutputDevice: public T {
		friend class GUIOutputDeviceBase;
	protected:
		typedef T basetype;
		typedef TGUIOutputDevice<T> GUIData;
		GUIfyOutputDevice():T() {}
		GUIfyOutputDevice(int devId,
				  const mutStringRef name, 
				  int id = -1):T(devId, name, id)
			{
			}
		virtual void setUserData (void * data) { 
			UNREACHABLEC;
			GetGUIDevice().setUserData(data); 
		}

		virtual void * getUserData() { 
			UNREACHABLEC;
			return GetGUIDevice().getUserData(); 
		}
		
		void SetGUIDevice (GUIOutputDeviceBase * dev) {
			mutabor::OutputDeviceClass::setUserData(dev);
		}
		
	public:
		const GUIData & GetGUIDevice() const {
			void * d = mutabor::OutputDeviceClass::getUserData();
			return *((const TGUIOutputDevice<T> *)d);
		}
		GUIData & GetGUIDevice() {
			void * d = mutabor::OutputDeviceClass::getUserData();
			return *((TGUIOutputDevice<T> *)d);
		}

#if 0
		/// add a route
		virtual void Add(Route & route);
		/// replace a route
		virtual bool Replace(Route & oldroute, Route & newroute);
                /// remove a route
		virtual bool Remove(Route & route);
//		/// Move routes to another device 
//		virtual bool MoveRoutes (DevicePtr newclass);
#endif

		void Add(MutOutputDeviceShape * shape) {
			GetGUIDevice().Add(shape);
		}
		bool Remove(MutOutputDeviceShape * shape) {
			return GetGUIDevice().Remove(shape);
		}

		void Attatch(MutOutputDeviceShape * shape) {
			return GetGUIDevice().Attatch(shape);
		}

		bool Detatch(MutOutputDeviceShape * shape) {
			return GetGUIDevice().Detatch(shape);
		}

		bool Delete(MutOutputDeviceShape * shape) {
			return GetGUIDevice().Delete(shape);
		}

		virtual void Destroy();
	};


	class GUIOutputDeviceBase {
	protected:
		mutabor::OutputDeviceClass * device;
		void * userdata;
		MutOutputDeviceShapeList shapes;
	public:

		virtual void * getUserData() {
			return userdata;
		}
		virtual void setUserData(void * data) {
			userdata = data;
		}

		bool IsDevice(const mutabor::OutputDeviceClass * d) const {
			return device == d;
		}

		operator mutabor::OutputDeviceClass & () {
			return *device;
		}

		mutabor::OutputDeviceClass * GetDevice () { return device; }

		const MutOutputDeviceShapeList & GetShapes() const {
			return shapes;
		}
		MutOutputDeviceShapeList & GetShapes() {
			return shapes;
		}

#if 0
		/// add a route
		virtual void Add(Route & route);
		/// replace a route
		virtual bool Replace(Route & oldroute, Route & newroute);
                /// remove a route
		virtual bool Remove(Route & route);
		/// Move routes to another device 
		//virtual bool MoveRoutes (DevicePtr newclass);
#endif

		void Add(MutOutputDeviceShape * shape);
		bool Remove(MutOutputDeviceShape * shape);
		
		void Attatch(MutOutputDeviceShape * shape);
		bool Detatch(MutOutputDeviceShape * shape);
		bool Delete(MutOutputDeviceShape * shape);
		
		virtual void Destroy();
		MutOutputDeviceShape * GetShape(wxWindow * parent);
	protected:

		void InitializeOutputDevice() {
			if (device) 
				static_cast<GUIfyOutputDevice 
					<mutabor::OutputDeviceClass> *>(device)
					-> SetGUIDevice (this);
		}
	};


	template<class T>
	class TGUIOutputDevice: public GUIOutputDeviceBase {
	public:
		typedef T OutputDeviceType;
		operator OutputDeviceType &() {
			return *static_cast<OutputDeviceType *>(device);
		}
	protected:
		TGUIOutputDevice(OutputDeviceType * dev = NULL):
			GUIOutputDeviceBase() {
			device = dev;
			InitializeOutputDevice();
		}
	};

	

	class GUIfiedOutputDevice: 
		public GUIfyOutputDevice<mutabor::OutputDeviceClass> {
	protected:
		GUIfiedOutputDevice(void * gui):
		GUIfyOutputDevice<mutabor::OutputDeviceClass>() {
			OutputDeviceClass::setUserData(gui);
		}
	
		GUIfiedOutputDevice(void * gui,
				    int devId, 
				    const mutStringRef name = mutEmptyString, 
				    int id = -1):
			GUIfyOutputDevice<mutabor::OutputDeviceClass>(devId,
								      name,
								      id) {
			OutputDeviceClass::setUserData(gui);
		}

	public:
		virtual ~GUIfiedOutputDevice() { TRACEC; }
	};

	class GUIOutputDevice:public TGUIOutputDevice<GUIfiedOutputDevice> {
	protected:
		GUIOutputDevice():TGUIOutputDevice<GUIfiedOutputDevice>() {	}
	
		GUIOutputDevice(int devId, 
				const mutStringRef name = mutEmptyString, 
				int id = -1):
			TGUIOutputDevice<GUIfiedOutputDevice>(NULL)
/*
			TGUIOutputDevice(new GUIfiedOutputDevice(this,devId,name,id))
*/
			{
				ABSTRACT_FUNCTIONC;
			}
		
	public:
		virtual ~GUIOutputDevice() { TRACEC; }

	};



	class GUIInputDeviceBase;
	template<class T> class TGUIInputDevice;

	template<class T> T * static_cast_to(mutabor::InputDevice & o,
					     T *) {
		return static_cast<T *>(o.get());
	}
	template<class T> T * dynamic_cast_to(mutabor::InputDevice & o,
					     T *) {
		return dynamic_cast<T *>(o.get());
	}
	template<class T> const T * static_cast_to(const mutabor::InputDevice & o,
					     const T *) {
		return static_cast<const T *>(o.get());
	}
	template<class T> const T * dynamic_cast_to(const mutabor::InputDevice & o,
					     const T *) {
		return dynamic_cast<const T *>(o.get());
	}

	/// Prototype of any GUI based input device class
	/** This class is the prototype for any GUI based input device.
	    Since the base class remains InputDeviceClass we must not 
	    add any fields or new virtal functions to it. Overloading of 
	    existing virtals should be allowed.
	*/
	
	template<class T> 
	class GUIfyInputDevice: public T {
		friend class GUIInputDeviceBase;
	protected:
		typedef T basetype;
		typedef TGUIInputDevice<T> GUIData;

		GUIfyInputDevice():T() {}
		GUIfyInputDevice(int devId, 
				 const mutStringRef name = mutEmptyString, 
				 mutabor::MutaborModeType mode
				 = mutabor::DeviceStop, 
				 int id = -1):T(devId,
						name,
						mode,
						id) {}
	protected:
		virtual void setUserData (void * data) { 
			UNREACHABLEC;
			GetGUIDevice().setUserData(data); 
		}

		virtual void * getUserData() { 
			UNREACHABLEC;
			return GetGUIDevice().getUserData(); 
		}
		void SetGUIDevice (GUIInputDeviceBase * dev) {
			mutabor::InputDeviceClass::setUserData(dev);
		}
		
	public:
		const GUIData & GetGUIDevice() const {
			void * d = mutabor::InputDeviceClass::getUserData();
			return *((const GUIData *)d);
		}

		GUIData & GetGUIDevice() {
			void * d = mutabor::InputDeviceClass::getUserData();
			return *((GUIData *)d);
		}

#if 0
		/// add a route
		virtual void Add(Route & route);
		/// replace a route
		virtual bool Replace(Route & oldroute, Route & newroute);
                /// remove a route
		virtual bool Remove(Route & route);
		/// Move routes to another device 
//		virtual bool MoveRoutes (DevicePtr newclass);
#endif


		void Add(MutInputDeviceShape * shape) {
			GetGUIDevice().Add(shape);
		}
		bool Remove(MutInputDeviceShape * shape) {
			return GetGUIDevice().Remove(shape);
		}

		void Attatch(MutInputDeviceShape * shape) {
			return GetGUIDevice().Attatch(shape);
		}

		bool Detatch(MutInputDeviceShape * shape) {
			return GetGUIDevice().Detatch(shape);
		}

		bool Delete(MutInputDeviceShape * shape) {
			return GetGUIDevice().Delete(shape);
		}

		virtual void Destroy();
	};



	class GUIInputDeviceBase {
	protected:
		mutabor::InputDeviceClass * device;
		void * userdata;
		MutInputDeviceShapeList shapes;
	public:
		virtual void * getUserData() {
			return userdata;
		}
		virtual void setUserData(void * data) {
			userdata = data;
		}

		bool IsDevice(const mutabor::InputDeviceClass * d) const {
			return device == d;
		}

		mutabor::InputDeviceClass * GetDevice () { return device; }

		operator mutabor::InputDeviceClass &() {
			return *device;
		}

		const MutInputDeviceShapeList & GetShapes() const {
			return shapes;
		}
		MutInputDeviceShapeList & GetShapes() {
			return shapes;
		}

#if 0
		/// add a route
		virtual void Add(Route & route);
		/// replace a route
		virtual bool Replace(Route & oldroute, Route & newroute);
                /// remove a route
		virtual bool Remove(Route &  route);
		/// Move routes to another device 
//		virtual bool MoveRoutes (DevicePtr newclass);
#endif

		void Add(MutInputDeviceShape * shape);
		bool Remove(MutInputDeviceShape * shape);
		
		void Attatch(MutInputDeviceShape * shape);
		bool Detatch(MutInputDeviceShape * shape);
		bool Delete(MutInputDeviceShape * shape);


		MutInputDeviceShape * GetShape(wxWindow * parent);
		
		virtual void Destroy();
	protected:

		void InitializeInputDevice() {
			if (device) {
				
				static_cast<GUIfyInputDevice 
					<mutabor::InputDeviceClass> *>(device)
					-> SetGUIDevice (this);
			}
		}
	};


	template<class T>
	class TGUIInputDevice: public GUIInputDeviceBase {
	public:
		typedef T InputDeviceType;
		operator InputDeviceType & () {
			return *static_cast<InputDeviceType *>(device);
		}
	protected:
		TGUIInputDevice(InputDeviceType * dev=NULL):GUIInputDeviceBase() {
			device = dev;
			InitializeInputDevice();
		}
	};

	class GUIfiedInputDevice: 
		public GUIfyInputDevice<mutabor::InputDeviceClass> {
	protected:
		GUIfiedInputDevice(void * gui):
		GUIfyInputDevice<mutabor::InputDeviceClass>()
			{
				InputDeviceClass::setUserData(gui);
			}
	
		GUIfiedInputDevice(void * gui,
				    int devId, 
				    const mutStringRef name = mutEmptyString, 
				   mutabor::MutaborModeType mode
				   = mutabor::DeviceStop, 
				    int id = -1):
			GUIfyInputDevice<mutabor::InputDeviceClass>(devId,
								    name,
								    mode,
								    id) {
			InputDeviceClass::setUserData(gui);
		}

	public:
		virtual ~GUIfiedInputDevice() {}
	};

	class GUIInputDevice:public TGUIInputDevice<GUIfiedInputDevice> {
		GUIInputDevice():TGUIInputDevice<GUIfiedInputDevice>() {	}
	
		GUIInputDevice(int devId, 
			       const mutStringRef name = mutEmptyString, 
			       mutabor::MutaborModeType mode
			       = mutabor::DeviceStop, 
			       int id = -1):
			TGUIInputDevice<GUIfiedInputDevice>(NULL)
			/*
			TGUIInputDevice(new GUIfiedInputDevice(this,devId,name,mode,id));
			*/
			{}
		
	public:
		virtual ~GUIInputDevice() { TRACEC; }

	};



	class GUIDeviceFactory:public mutabor::DeviceFactory { 
	protected:
		GUIDeviceFactory(size_t id = 0):
			DeviceFactory(id) {}
	public:
		virtual ~GUIDeviceFactory();

	protected:
		// see DeviceFactory for additional pure virtual functions

		virtual MutOutputDeviceShape * DoCreateShape(
			mutabor::OutputDevice & device,
			wxWindow * parent) const = 0;
		virtual MutInputDeviceShape * DoCreateShape(
			mutabor::InputDevice & device,
			wxWindow * parent) const = 0;
	public:
		static MutOutputDeviceShape * CreateShape(
			mutabor::OutputDevice & device, wxWindow * parent);

		static MutInputDeviceShape * CreateShape(
			mutabor::InputDevice & device, wxWindow * parent);
			
	};



	/// Attatch OutputMidiPort to GUIOutputMidiPort
	class GUIfiedOutputMidiPort: 
		public GUIfyOutputDevice<mutabor::OutputMidiPort> {
	public:
		GUIfiedOutputMidiPort(void * gui):
		GUIfyOutputDevice<mutabor::OutputMidiPort>() {
			OutputMidiPort::setUserData(gui);
		}
	
		GUIfiedOutputMidiPort(void * gui,
				      int devId, 
				      const mutStringRef name = mutEmptyString, 
				      int id = -1):
			GUIfyOutputDevice<mutabor::OutputMidiPort>(devId,name,id) {
			OutputMidiPort::setUserData(gui);
		}

		virtual ~GUIfiedOutputMidiPort() { TRACEC;}
	};

	class GUIOutputMidiPort:public TGUIOutputDevice<GUIfiedOutputMidiPort> {
	public:

		GUIOutputMidiPort():
			TGUIOutputDevice<GUIfiedOutputMidiPort>(new GUIfiedOutputMidiPort(this)) 
			{	
			}
	
		GUIOutputMidiPort(int devId, 
				const mutStringRef name = mutEmptyString, 
				int id = -1):
			TGUIOutputDevice<GUIfiedOutputMidiPort>(new GUIfiedOutputMidiPort(this,
								   devId,
								   name,
								   id))
			{}
		
		virtual ~GUIOutputMidiPort() {  TRACEC;}

	};



	/// Attatch InputMidiPort to GUIInputMidiPort
	class GUIfiedInputMidiPort: 
		public GUIfyInputDevice<mutabor::InputMidiPort> {
	public:
		GUIfiedInputMidiPort(void * gui):
		GUIfyInputDevice<mutabor::InputMidiPort>() {
			InputMidiPort::setUserData(gui);
		}
	
		GUIfiedInputMidiPort(void * gui,
				     int devId, 
				     const mutStringRef name = mutEmptyString, 
				     mutabor::MutaborModeType mode
				     = mutabor::DeviceStop, 
				     int id = -1):
			GUIfyInputDevice<mutabor::InputMidiPort>(devId,name,mode,id) {
			InputMidiPort::setUserData(gui);
		}
		
		virtual ~GUIfiedInputMidiPort() { TRACEC;}
	};

	class GUIInputMidiPort:public TGUIInputDevice<GUIfiedInputMidiPort> {
	public:

		GUIInputMidiPort():
			TGUIInputDevice<GUIfiedInputMidiPort>(
				new GUIfiedInputMidiPort(this)) 
			{	
			}

		GUIInputMidiPort(int devId, 
				 const mutStringRef name = mutEmptyString, 
				 mutabor::MutaborModeType mode
				 = mutabor::DeviceStop, 
				 int id = -1):
			TGUIInputDevice<GUIfiedInputMidiPort>(
				new GUIfiedInputMidiPort(this,
							 devId,
							 name,
							 mode,id))
			{}
		
		virtual ~GUIInputMidiPort() { TRACEC; }

	};

	class GUIMidiPortFactory:public GUIDeviceFactory { 
	public:
		GUIMidiPortFactory(size_t id = mutabor::DTMidiPort):
			GUIDeviceFactory(id) {}
		virtual ~GUIMidiPortFactory();

	protected:
		virtual size_t GetType() const
			{
				return mutabor::DTMidiPort;
			}


		virtual mutabor::OutputDeviceClass * DoCreateOutput() const;
		
		virtual mutabor::InputDeviceClass * DoCreateInput() const;
		virtual mutabor::OutputDeviceClass * DoCreateOutput(int devId,
							     const mutStringRef name, 
							     int id = -1) const;
		
		virtual mutabor::InputDeviceClass * DoCreateInput(int devId,
							   const mutStringRef name, 
							   int id = -1) const;

		virtual mutabor::OutputDeviceClass * DoCreateOutput(int devId,
							     const mutStringRef name, 
							     mutabor::MutaborModeType mode, 
							     int id = -1) const;
		
		virtual mutabor::InputDeviceClass * DoCreateInput(int devId,
							   const mutStringRef name, 
							   mutabor::MutaborModeType mode, 
							   int id = -1) const;

		virtual MutOutputDeviceShape * DoCreateShape(
			mutabor::OutputDevice & device,
			wxWindow * parent) const;
		virtual MutInputDeviceShape * DoCreateShape(
			mutabor::InputDevice & device,
			wxWindow * parent) const;
	};






	/// Attatch OutputMidiFile to GUIOutputMidiFile
	class GUIfiedOutputMidiFile: 
		public GUIfyOutputDevice<mutabor::OutputMidiFile> {
	public:
		GUIfiedOutputMidiFile(void * gui):
		GUIfyOutputDevice<mutabor::OutputMidiFile>() {
			OutputMidiFile::setUserData(gui);
		}
	
		GUIfiedOutputMidiFile(void * gui,
				      int devId,
				      const mutStringRef name, 
				      int id = -1):
			GUIfyOutputDevice<mutabor::OutputMidiFile>(devId,name,id) {
			OutputMidiFile::setUserData(gui);
		}

		virtual ~GUIfiedOutputMidiFile() { TRACEC;}
	};

	class GUIOutputMidiFile:public TGUIOutputDevice<GUIfiedOutputMidiFile> {
	public:

		GUIOutputMidiFile():
			TGUIOutputDevice<GUIfiedOutputMidiFile>(
				new GUIfiedOutputMidiFile(this)) 
			{ 
			}

		GUIOutputMidiFile(int devId,
				  const mutStringRef name, 
				  int id = -1):
			TGUIOutputDevice<GUIfiedOutputMidiFile>(
				new GUIfiedOutputMidiFile(this,
							  devId,
							  name,
							  id))
			{}
		
		virtual ~GUIOutputMidiFile() { TRACEC; }

	};

	/// Attatch InputMidiFile to GUIInputMidiFile
	class GUIfiedInputMidiFile: 
		public GUIfyInputDevice<mutabor::InputMidiFile> {
	public:
		GUIfiedInputMidiFile(void * gui):
		GUIfyInputDevice<mutabor::InputMidiFile>() {
			InputMidiFile::setUserData(gui);
		}
	
		GUIfiedInputMidiFile(void * gui,
				     int devId, 
				     const mutStringRef name = mutEmptyString, 
				     mutabor::MutaborModeType mode
				     = mutabor::DeviceStop, 
				     int id = -1):
			GUIfyInputDevice<mutabor::InputMidiFile>(devId,name,mode,id) {
			InputMidiFile::setUserData(gui);
		}

		virtual ~GUIfiedInputMidiFile() { TRACEC;}
	};

	class GUIInputMidiFile:public TGUIInputDevice<GUIfiedInputMidiFile> {
	public:

		GUIInputMidiFile():
			TGUIInputDevice<GUIfiedInputMidiFile>(
				new GUIfiedInputMidiFile(this)) {}

		GUIInputMidiFile(int devId, 
				 const mutStringRef name = mutEmptyString, 
				 mutabor::MutaborModeType mode
				 = mutabor::DeviceStop, 
				 int id = -1):
			TGUIInputDevice<GUIfiedInputMidiFile>(
				new GUIfiedInputMidiFile(this,
							 devId,
							 name,
							 mode,
							 id))
			{}
		
		virtual ~GUIInputMidiFile() { TRACEC;}

	};


	class GUIMidiFileFactory:public GUIDeviceFactory { 
	public:
		GUIMidiFileFactory(size_t id = mutabor::DTMidiFile):
			GUIDeviceFactory(id) {}
		virtual ~GUIMidiFileFactory();

	protected:
		virtual size_t GetType() const
			{
				return mutabor::DTMidiFile;
			}


		virtual mutabor::OutputDeviceClass * DoCreateOutput() const;
		
		virtual mutabor::InputDeviceClass * DoCreateInput() const;
		virtual mutabor::OutputDeviceClass * DoCreateOutput(int devId,
							     const mutStringRef name, 
							     int id = -1) const;
		
		virtual mutabor::InputDeviceClass * DoCreateInput(int devId,
							   const mutStringRef name, 
							   int id = -1) const;

		virtual mutabor::OutputDeviceClass * DoCreateOutput(int devId,
							     const mutStringRef name, 
							     mutabor::MutaborModeType mode, 
							     int id = -1) const;
		
		virtual mutabor::InputDeviceClass * DoCreateInput(int devId,
							   const mutStringRef name, 
							   mutabor::MutaborModeType mode, 
							   int id = -1) const;
		virtual MutOutputDeviceShape * DoCreateShape(
			mutabor::OutputDevice & device,
			wxWindow * parent) const;
		virtual MutInputDeviceShape * DoCreateShape(
			mutabor::InputDevice & device,
			wxWindow * parent) const;
	};




	/// Attatch OutputGis to GUIOutputGis
	class GUIfiedOutputGis: 
		public GUIfyOutputDevice<mutabor::OutputGis> {
	public:
		GUIfiedOutputGis(void * gui):GUIfyOutputDevice<mutabor::OutputGis>() {
			OutputGis::setUserData(gui);
		}
	
		GUIfiedOutputGis(void * gui,
				 int devId,
				 const mutStringRef name, 
				 int id = -1):
			GUIfyOutputDevice<mutabor::OutputGis>(devId,name,id) {
			OutputGis::setUserData(gui);
		}

		virtual ~GUIfiedOutputGis() { TRACEC;}
	};

	class GUIOutputGis:public TGUIOutputDevice<GUIfiedOutputGis> {
	public:

		GUIOutputGis():TGUIOutputDevice<GUIfiedOutputGis>(
			new GUIfiedOutputGis(this)) 
			{ 
			}

		GUIOutputGis(int devId,
			     const mutStringRef name, 
			     int id = -1):
			TGUIOutputDevice<GUIfiedOutputGis>(
				new GUIfiedOutputGis(this,
						     devId,
						     name,
						     id))
			{}
		
		virtual ~GUIOutputGis() { TRACEC; }

	};


	/// Attatch InputGis to GUIInputGis
	class GUIfiedInputGis: 
		public GUIfyInputDevice<mutabor::InputGis> {
	public:
		GUIfiedInputGis(void * gui):GUIfyInputDevice<mutabor::InputGis>() {
			InputGis::setUserData(gui);
		}
	
		GUIfiedInputGis(void * gui,
				int devId, 
				const mutStringRef name = mutEmptyString, 
				mutabor::MutaborModeType mode
				= mutabor::DeviceStop, 
				int id = -1):
			GUIfyInputDevice<mutabor::InputGis>(devId,name,mode,id)  {
			InputGis::setUserData(gui);
		}

		virtual ~GUIfiedInputGis() { TRACEC;}
	};

	class GUIInputGis:public TGUIInputDevice<GUIfiedInputGis> {
	public:

		GUIInputGis():TGUIInputDevice<GUIfiedInputGis>(
			new GUIfiedInputGis(this))
			{
			}

		GUIInputGis(int devId, 
			    const mutStringRef name = mutEmptyString, 
			    mutabor::MutaborModeType mode
			    = mutabor::DeviceStop, 
			    int id = -1):
			TGUIInputDevice<GUIfiedInputGis>(
				new GUIfiedInputGis(this,
						    devId,
						    name,
						    mode,
						    id))
			{}
		
		virtual ~GUIInputGis() { TRACEC; }

	};


	class GUIGisFactory:public GUIDeviceFactory { 
	public:
		GUIGisFactory(size_t id = mutabor::DTGis):
			GUIDeviceFactory(id) {}
		virtual ~GUIGisFactory();

	protected:
		
		virtual size_t GetType() const
			{
				return mutabor::DTGis;
			}


		virtual mutabor::OutputDeviceClass * DoCreateOutput() const;
		
		virtual mutabor::InputDeviceClass * DoCreateInput() const;
		virtual mutabor::OutputDeviceClass * DoCreateOutput(int devId,
							     const mutStringRef name, 
							     int id = -1) const;
		
		virtual mutabor::InputDeviceClass * DoCreateInput(int devId,
							   const mutStringRef name, 
							   int id = -1) const;

		virtual mutabor::OutputDeviceClass * DoCreateOutput(int devId,
							     const mutStringRef name, 
							     mutabor::MutaborModeType mode, 
							     int id = -1) const;
		
		virtual mutabor::InputDeviceClass * DoCreateInput(int devId,
							   const mutStringRef name, 
							   mutabor::MutaborModeType mode, 
							   int id = -1) const;
		virtual MutOutputDeviceShape * DoCreateShape(
			mutabor::OutputDevice & device,
			wxWindow * parent) const;
		virtual MutInputDeviceShape * DoCreateShape(
			mutabor::InputDevice & device,
			wxWindow * parent) const;
	};

	void InitGUIRouteFactories();

}
#endif /* precompiled */
#endif
///\}
