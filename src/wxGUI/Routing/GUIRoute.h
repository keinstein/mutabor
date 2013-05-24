/** \file               -*- C++ -*-
 ********************************************************************
 * Interface to separate Mutabor functionality from the GUI
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/src/wxGUI/Routing/GUIRoute.h,v 1.6 2011/11/03 17:20:15 keinstein Exp $
 * Copyright:   (c) 2011 TU Dresden,
 *                  2013 Tobias Schlemmer
 * \author  Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 
 * $Date: 2011/11/03 17:20:15 $
 * \version $Revision: 1.6 $
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
 * Revision 1.6  2011/11/03 17:20:15  keinstein
 * fix some focus issues on msw
 *
 * Revision 1.5  2011-11-02 14:32:00  keinstein
 * fix some errors crashing Mutabor on Windows
 *
 * Revision 1.4  2011-10-04 17:16:14  keinstein
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
// availlable groups: GUI, route, kernel, src/wxGUI, debug, docview

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

#include "src/kernel/Defs.h"
#include "src/kernel/routing/Device.h"
#include "src/kernel/routing/midi/DevMidi.h"
#include "src/kernel/routing/midi/DevMidF.h"
#include "src/kernel/routing/gmn/DevGIS.h"
#include "src/kernel/routing/Route.h"
#include "src/wxGUI/GUIBoxData.h"
#include "src/wxGUI/Routing/RouteLists.h"

#ifndef MUWX_ROUTING_GUIROUTE_H_PRECOMPILED
#define MUWX_ROUTING_GUIROUTE_H_PRECOMPILED

// system headers which do seldom change

#include <algorithm>

class wxWindow;

namespace mutaborGUI {
	class GUIRouteBase;
 	class GUIInputDeviceBase;
 	class GUIOutputDeviceBase;

	class GUIRouteBase {
	protected:
		BoxData * box;
		MutBoxChannelShapeList shapes;

		GUIRouteBase():box(NULL),shapes() {}
 		virtual ~GUIRouteBase() {
			TRACEC;
		}

	public:

		void ReconfigureBox(int oldbox, int newbox) {
			box = &(BoxData::GetBox(newbox));

			DEBUGLOG(routing, _T("Set Box data to %p from id %d"),
				 box, newbox);
			BoxData::ReOpenRoute(oldbox, newbox);
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

		/// add a new output device
		virtual void Add (mutabor::OutputDevice & dev);
		/// add a new input device
		virtual void Add (mutabor::InputDevice & dev);
		/// add a new box
		virtual void Add(int id);
		/// replace an existing output device
		virtual bool Replace (mutabor::OutputDevice & olddev, 
				      mutabor::OutputDevice & newdev);
		/// replace an existing input device
		virtual bool Replace (mutabor::InputDevice & olddev, 
				      mutabor::InputDevice & newdev);
		/// replace an existing box
		virtual bool Replace (int oldbox, int newbox);
		/// remove an existing output device
		virtual bool Remove (mutabor::OutputDevice & out);
		/// remove an existing input device
		virtual bool Remove (mutabor::InputDevice & in);
		/// remov an existing box
		virtual bool Remove (int id);

#if 0
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

		bool Reconnect(MutBoxShape * oldshape,
			       MutBoxShape * newshape);

#endif 
		bool Delete(MutBoxShape * shape) {
			if (box) 
				return box -> Delete(shape);
			else {
				UNREACHABLECT(GUIRouteBase);
				return false;
			}
		}
			     

		const MutBoxChannelShapeList & 
		GetBoxChannelShapes() const {
			return shapes;
		}
		void Add(MutBoxChannelShape * shape);
		bool Remove(MutBoxChannelShape * shape);

#if 0
		void Attatch(MutBoxChannelShape * shape);
		bool Detatch(MutBoxChannelShape * shape);
		bool Delete(MutBoxChannelShape * shape);
#endif
		
		static GUIRouteBase * GetGUIRoute(mutabor::Route & r) {
			return static_cast<GUIRouteBase *>(r->getUserData());
		}
		virtual mutabor::RouteClass * GetRoute() = 0;	

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

#if 0
	protected:

		void InitializeRoute() {
			if (route) 
				static_cast<GUIfyRoute
					<mutabor::RouteClass> *>(route)
					-> SetGUIRoute (this);
			ReconfigureBox(NewBox, route->GetBox());
		}
#endif
	};



	template<class T> 
	class GUIfiedRoute: public T, public GUIRouteBase {
		friend class GUIRouteFactory;
	public:
		typedef GUIfiedRoute<T> thistype;
		typedef T base;
	protected:
		GUIfiedRoute():base() {
			this -> userdata = static_cast<GUIRouteBase *> (this);
		}

		GUIfiedRoute(mutabor::InputDevice & in,
			     mutabor::OutputDevice & out,
			     mutabor::RouteType type = mutabor::RTall,
			     int iFrom = -1,
			     int iTo = -1,
			     int box = -1,
			     bool active = false,
			     int oFrom = -1,
			     int oTo = -1,
			     bool oNoDrum = true):
			base(),GUIRouteBase() {
			this -> Create(in,out,type,
				iFrom,iTo,
				box,active,
				oFrom, oTo, oNoDrum);
			this -> userdata = static_cast<GUIRouteBase *> (this);
		}
	public:
		virtual ~GUIfiedRoute() { 
			TRACEC; 
		}

		bool IsRoute(const mutabor::RouteClass * r) const {
			return static_cast<mutabor::RouteClass *>(this) == r;
		}

		virtual void SetBox(int box) {
			int oldbox = T::GetBox();
			T::SetBox(box);
			ReconfigureBox(oldbox, box);
		}

		/// add a new output device
		virtual void Add (mutabor::OutputDevice & out);
		/// add a new input device
		virtual void Add (mutabor::InputDevice & in);
		/// add a new box
		virtual void Add(int id);
		/// replace an existing output device
		virtual bool Replace (mutabor::OutputDevice & olddev, 
				      mutabor::OutputDevice & newdev);
		/// replace an existing input device
		virtual bool Replace (mutabor::InputDevice & olddev, 
				      mutabor::InputDevice & newdev);
		/// replace an existing box
		virtual bool Replace (int oldbox, int newbox);
		/// remove an existing output device
		virtual bool Remove (mutabor::OutputDevice & out);
		/// remove an existing input device
		virtual bool Remove (mutabor::InputDevice & in);
		/// remov an existing box
		virtual bool Remove (int id);

		virtual mutabor::RouteClass * GetRoute() {
			return static_cast<mutabor::RouteClass *> (this);
		}


#if 0
		// static looks strange, here.
		static void Add(MutBoxShape * shape) {
			if (T::Box >= 0) {
				BoxData::GetBox(T::Box).Add(shape);
			} else {
				UNREACHABLECT(thistype);
			}
		}
		static bool Remove(MutBoxShape * shape) {
			if (T::Box >= 0) {
				return BoxData::GetBox(T::Box).Remove(shape);
			} else {
				UNREACHABLECT(thistype);
			}
		}
#endif
		

#if 0
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
				UNREACHABLECT(thistype);
			}
		}
		static bool Detatch(MutBoxShape * shape) {
			if (T::Box >= 0)
				return BoxData::GetBox(T::Box).Detatch(shape);
			else {
				UNREACHABLECT(thistype);
			}
		}
		static bool Delete(MutBoxShape * shape) {
			if (T::Box >= 0) 
				return BoxData::GetBox(T::Box).Delete(shape);
			else {
				UNREACHABLECT(thistype);
			}
		}
#endif


#if 0
		// should be already included
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
#endif

		virtual void Destroy();
	};


	/// Prototype of any GUI based route class
	/** This class is the prototype for any GUI based route.
	    Since the base class remains RouteClass we must not 
	    any fields to it.
	*/
	

	typedef GUIfiedRoute<mutabor::RouteClass> GUIRoute;

	inline GUIRoute * ToGUIBase(mutabor::RouteClass *  r) {
		return static_cast<GUIRoute *>(r);
	}
	inline const GUIRoute * ToGUIBase(const mutabor::RouteClass *  r) {
		return static_cast<const GUIRoute *>(r);
	}
	inline GUIRoute * ToGUIBase(mutabor::Route & r) {
		return ToGUIBase(r.get());
	}
	inline const GUIRoute * ToGUIBase(const mutabor::Route & r) {
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
			bool oNoDrum) const __attribute__ ((malloc));
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
	class GUIOutputDeviceBase {
	protected:
		MutOutputDeviceShapeList shapes;
	public:

		const MutOutputDeviceShapeList & GetShapes() const {
			return shapes;
		}
		MutOutputDeviceShapeList & GetShapes() {
			return shapes;
		}

#if 0 // maybe useful functions
		bool IsDevice(const mutabor::OutputDeviceClass * d) const {
			return device == d;
		}

		operator mutabor::OutputDeviceClass &() {
			return *GetDevice();
		}

#endif

		/// add a route
		virtual void Add(mutabor::Route & route);
		/// replace a route
		virtual bool Replace(mutabor::Route & oldroute, mutabor::Route & newroute);
                /// remove a route
		virtual bool Remove(mutabor::Route & route);
		/// Move routes to another device 
		//virtual bool MoveRoutes (DevicePtr newclass);

		void Add(MutOutputDeviceShape * shape);
		bool Remove(MutOutputDeviceShape * shape);

#if 0		
		void Attatch(MutOutputDeviceShape * shape);
		bool Detatch(MutOutputDeviceShape * shape);
		bool Delete(MutOutputDeviceShape * shape);
#endif
		
		MutOutputDeviceShape * GetShape(wxWindow * parent);

		static GUIOutputDeviceBase * GetGUIOutputDevice(mutabor::OutputDeviceClass * d) {
			return static_cast<GUIOutputDeviceBase *>(d->getUserData());
		}
		static const GUIOutputDeviceBase * GetGUIOutputDevice(const mutabor::OutputDeviceClass * d) {
			return static_cast<GUIOutputDeviceBase *>(d->getUserData());
		}

		
		virtual mutabor::OutputDeviceClass * GetDevice() = 0;	
		
		void Destroy();

	};

	template<class T> 
	class GUIfiedOutputDevice: public T, public GUIOutputDeviceBase {
		friend class GUIMidiPortFactory;
		friend class GUIMidiFileFactory;
		friend class GUIGisFactory;
	public:
		typedef T basetype;
		typedef GUIfiedOutputDevice<T> thistype;
	protected:
		GUIfiedOutputDevice():T() {
			this->setUserData(static_cast<GUIOutputDeviceBase *>(this));
		}
		GUIfiedOutputDevice(int devId,
				  const mutStringRef name = mutEmptyString, 
				  int id = -1):T(devId, name, id),
					       GUIOutputDeviceBase() {
			this->setUserData(static_cast<GUIOutputDeviceBase *>(this));
		}
	public:

		virtual ~GUIfiedOutputDevice() { TRACEC; }


		/// add a route
		virtual void Add(mutabor::Route & route);
		/// replace a route
		virtual bool Replace(mutabor::Route & oldroute, mutabor::Route & newroute);
                /// remove a route
		virtual bool Remove(mutabor::Route & route);
//		/// Move routes to another device 
//		virtual bool MoveRoutes (DevicePtr newclass);

		virtual mutabor::OutputDeviceClass * GetDevice() {
			return static_cast<basetype *>(this);
		}

		virtual void Destroy();
	};

	inline GUIOutputDeviceBase * ToGUIBase(mutabor::OutputDeviceClass * d) {
		return GUIOutputDeviceBase::GetGUIOutputDevice(d);
	}
	inline GUIOutputDeviceBase * ToGUIBase(mutabor::OutputDevice & d) {
		return ToGUIBase(d.get());
	}
	inline const GUIOutputDeviceBase * ToGUIBase(const mutabor::OutputDeviceClass * d) {
		return GUIOutputDeviceBase::GetGUIOutputDevice(d);
	}
	inline const GUIOutputDeviceBase * ToGUIBase(const mutabor::OutputDevice & d) {
		return ToGUIBase(d.get());
	}

//------------------------------------


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
	
	class GUIInputDeviceBase {
	protected:
		MutInputDeviceShapeList shapes;
	public:
#if 0 // maybe useful functions
		bool IsDevice(const mutabor::InputDeviceClass * d) const {
			return device == GetDevice();
		}

		operator mutabor::InputDeviceClass &() {
			return *GetDevice();
		}

#endif

		virtual mutabor::InputDeviceClass * GetDevice () = 0;

		const MutInputDeviceShapeList & GetShapes() const {
			return shapes;
		}
		MutInputDeviceShapeList & GetShapes() {
			return shapes;
		}

		/// add a route
		virtual void Add(mutabor::Route & route);
		/// replace a route
		virtual bool Replace(mutabor::Route & oldroute, mutabor::Route & newroute);
                /// remove a route
		virtual bool Remove(mutabor::Route &  route);
		/// Move routes to another device 
//		virtual bool MoveRoutes (DevicePtr newclass);

		void Add(MutInputDeviceShape * shape);
		bool Remove(MutInputDeviceShape * shape);
		
#if 0
		void Attatch(MutInputDeviceShape * shape);
		bool Detatch(MutInputDeviceShape * shape);
		bool Delete(MutInputDeviceShape * shape);
#endif


		MutInputDeviceShape * GetShape(wxWindow * parent);
		
		static GUIInputDeviceBase * GetGUIInputDevice(mutabor::InputDeviceClass * d) {
			return static_cast<GUIInputDeviceBase *>(d->getUserData());
		}
		static const GUIInputDeviceBase * GetGUIInputDevice(const mutabor::InputDeviceClass * d) {
			return static_cast<GUIInputDeviceBase *>(d->getUserData());
		}

		void Destroy();
	};


	template<class T> 
	class GUIfiedInputDevice: public T, public GUIInputDeviceBase {
		friend class GUIMidiPortFactory;
		friend class GUIMidiFileFactory;
		friend class GUIGisFactory;
	public:
		typedef T basetype;
		typedef GUIfiedInputDevice<T> thistype;

	protected:
		GUIfiedInputDevice():T() {
			this->setUserData(static_cast<GUIInputDeviceBase *>(this));
		}

		GUIfiedInputDevice(int devId, 
				 const mutStringRef name = mutEmptyString, 
				 mutabor::MutaborModeType mode
				 = mutabor::DeviceStop, 
				 int id = -1):T(devId,
						name,
						mode,
						id) {
			this->setUserData(static_cast<GUIInputDeviceBase *>(this));
		}
	public:
		const basetype * GetDevice() const {
			return static_cast<basetype *>(this);
		}

		basetype * GetDevice() {
			return static_cast<basetype *>(this);
		}

		/// add a route
		virtual void Add(mutabor::Route & route);
		/// replace a route
		virtual bool Replace(mutabor::Route & oldroute, mutabor::Route & newroute);
                /// remove a route
		virtual bool Remove(mutabor::Route & route);
		/// Move routes to another device 
//		virtual bool MoveRoutes (DevicePtr newclass);

		virtual void Destroy();
	};


	inline GUIInputDeviceBase * ToGUIBase(mutabor::InputDeviceClass * d) {
		return GUIInputDeviceBase::GetGUIInputDevice(d);
	}
	inline GUIInputDeviceBase * ToGUIBase(mutabor::InputDevice & d) {
		return ToGUIBase(d.get());
	}
	inline const GUIInputDeviceBase * ToGUIBase(const mutabor::InputDeviceClass * d) {
		return GUIInputDeviceBase::GetGUIInputDevice(d);
	}
	inline const GUIInputDeviceBase * ToGUIBase(const mutabor::InputDevice & d) {
		return ToGUIBase(d.get());
	}

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



	typedef GUIfiedOutputDevice<mutabor::OutputMidiPort> GUIOutputMidiPort;
	typedef GUIfiedInputDevice<mutabor::InputMidiPort> GUIInputMidiPort;

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


	typedef GUIfiedOutputDevice<mutabor::OutputMidiFile> GUIOutputMidiFile;
	typedef GUIfiedInputDevice<mutabor::InputMidiFile> GUIInputMidiFile;

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

	typedef GUIfiedOutputDevice<mutabor::OutputGis> GUIOutputGis;
	typedef GUIfiedInputDevice<mutabor::InputGis> GUIInputGis;

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
