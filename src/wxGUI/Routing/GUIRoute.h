/** \file               -*- C++ -*-
 ********************************************************************
 * Interface to separate Mutabor functionality from the GUI
 *
 * Copyright:   (c) 2011 TU Dresden,
 *                  2013 Tobias Schlemmer
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
 *
 ********************************************************************
 * \addtogroup GUIroute
 * \{
 *
 * \todo Rewrite shape classes to use GUI-references. In order to do
 * that, a special reference counting function should be provided that
 * use the non-GUI counter.
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
		MutBoxChannelShapeList shapes;

		GUIRouteBase():shapes() {}
 		virtual ~GUIRouteBase() {
			TRACEC;
		}

	public:

#if 0
		void ReconfigureBox(int oldbox, int newbox) {
			box = &(BoxClass::GetBox(newbox,BoxClass::IdTypeFile));

			DEBUGLOG(routing, _T("Set Box data to %p from id %d"),
				 (void*)box, newbox);
			BoxData::ReOpenRoute(oldbox, newbox);
		}

		const BoxData * GetBoxData() const {
			return box;
		}

		BoxData * GetBoxData() {
			return box;
		}
#endif


/*
		void Add(MutBoxShape * shape) {
			Box box = GetRoute()->GetBox();
			if (box) {
				 box->Add(shape);
			} else {
				UNREACHABLECT(GUIRouteBase);
			}
		}
		bool Remove(MutBoxShape * shape) {
			Box box = GetRoute()->GetBox();
			if (box) {
				return box->Remove(shape);
			} else {
				UNREACHABLECT(GUIRouteBase);
				return false;
			}
		}
*/

		/// add a new output device
		virtual void Add (mutabor::OutputDevice & dev);
		/// add a new input device
		virtual void Add (mutabor::InputDevice & dev);
		/// add a new box
		virtual void Add(mutabor::Box & b);
		/// replace an existing output device
		virtual bool Replace (mutabor::OutputDevice & olddev,
				      mutabor::OutputDevice & newdev);
		/// replace an existing input device
		virtual bool Replace (mutabor::InputDevice & olddev,
				      mutabor::InputDevice & newdev);
		/// replace an existing box
		virtual bool Replace(mutabor::Box & oldbox,
				     mutabor::Box & newbox);
		/// remove an existing output device
		virtual bool Remove (mutabor::OutputDevice & out);
		/// remove an existing input device
		virtual bool Remove (mutabor::InputDevice & in);
		/// remov an existing box
		virtual bool Remove (mutabor::Box & b);

/*
		const MutBoxShapeList & GetBoxShapes() const {
			Box box = GetRoute()->GetBox();
			if (!box) {
				UNREACHABLECT(GUIRouteBase);
			}
			return box->GetBoxShapes();
		}

		bool Delete(MutBoxShape * shape) {
			Box box = GetRoute()->GetBox();
			if (box)
				return box -> Delete(shape);
			else {
				UNREACHABLECT(GUIRouteBase);
				return false;
			}
		}
*/

		const MutBoxChannelShapeList &
		GetBoxChannelShapes() const {
			return shapes;
		}
		void Add(MutBoxChannelShape * shape);
		bool Remove(MutBoxChannelShape * shape);


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

		virtual void runtime_error(int type, const mutString& message, va_list & args);
	};


	class GUIRouteFactory;

	template<class T>
	class GUIfiedRoute: public T, public GUIRouteBase {
	public:
		friend class GUIRouteFactory;
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
			     mutabor::Box box = -1,
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
#if 0
		virtual void SetBox(int box) {
			int oldbox = T::GetBox();
			T::SetBox(box);
			ReconfigureBox(oldbox, box);
		}
#endif

		/// add a new output device
		virtual void Add (mutabor::OutputDevice & out);
		/// add a new input device
		virtual void Add (mutabor::InputDevice & in);
		/// add a new box
		virtual void Add(mutabor::Box & b);
		/// replace an existing output device
		virtual bool Replace (mutabor::OutputDevice & olddev,
				      mutabor::OutputDevice & newdev);
		/// replace an existing input device
		virtual bool Replace (mutabor::InputDevice & olddev,
				      mutabor::InputDevice & newdev);
		/// replace an existing box
		virtual bool Replace (mutabor::Box & oldbox,
				      mutabor::Box & newbox);
		/// remove an existing output device
		virtual bool Remove (mutabor::OutputDevice & out);
		/// remove an existing input device
		virtual bool Remove (mutabor::InputDevice & in);
		/// remov an existing box
		virtual bool Remove (mutabor::Box & b);

		virtual mutabor::RouteClass * GetRoute() {
			return static_cast<mutabor::RouteClass *> (this);
		}

		virtual void Destroy();

		virtual void  runtime_error(int type,
					    const mutString& message,
					    va_list & args) {
			GUIRouteBase::runtime_error(type,
						    message,
						    args);
		}
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

		static MutBoxChannelShape * CreateBoxChannelShape(
			mutabor::Route & route,
			wxWindow * parent)
			__attribute__ ((malloc))
		{
			return ((GUIRouteFactory *)factory)->
				DoCreateBoxChannelShape(route,parent);
		}

	protected:
		virtual mutabor::RouteClass * DoCreate() const
			__attribute__ ((malloc));
		virtual mutabor::RouteClass * DoCreate(
			mutabor::InputDevice & in,
			mutabor::OutputDevice & out,
			mutabor::RouteType type,
			int iFrom,
			int iTo,
			mutabor::Box box,
			bool active,
			int oFrom,
			int oTo,
			bool oNoDrum) const __attribute__ ((malloc));

		virtual MutBoxChannelShape *
		DoCreateBoxChannelShape (mutabor::Route & route,
					 wxWindow * parent) const;
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

		MutOutputDeviceShape * GetShape(wxWindow * parent);

		static GUIOutputDeviceBase * GetGUIOutputDevice(mutabor::OutputDeviceClass * d) {
			return static_cast<GUIOutputDeviceBase *>(d->getUserData());
		}
		static const GUIOutputDeviceBase *
		GetGUIOutputDevice(const mutabor::OutputDeviceClass * d) {
			return static_cast<GUIOutputDeviceBase *>(d->getUserData());
		}


		virtual mutabor::OutputDeviceClass * GetDevice() = 0;

		/**
		 * Move the associated device shape to a given
		 * position. This function handles the GUI part of
		 * GUIfiedOutputDevice::MoveInList().
		 *
		 * \param newpos New position of the shape in the
		 *  list. This parameter should reflect the actual
		 *  position of the device in the (non GUI) output
		 *  device list.
		 */
		virtual	void MoveToInList(int newpos);

		void Destroy();

		virtual void runtime_error(int type, const mutStringRef message, va_list & args);
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
		GUIfiedOutputDevice(const mutStringRef name = mutEmptyString,
				    int id = -1):T(name, id),
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

		virtual void DisconnectFromAll();
		virtual	int MoveInList(int count);
		virtual void  runtime_error(int type,
					    const mutString& message,
					    va_list & args) {
			GUIOutputDeviceBase::runtime_error(type,
							   message,
							   args);
		}
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

		virtual void Play();
		virtual void Stop();
		virtual void Pause();
		virtual bool Open();
		virtual void Close();


		MutInputDeviceShape * GetShape(wxWindow * parent);

		static GUIInputDeviceBase * GetGUIInputDevice(mutabor::InputDeviceClass * d) {
			return static_cast<GUIInputDeviceBase *>(d->getUserData());
		}
		static const GUIInputDeviceBase * GetGUIInputDevice(const mutabor::InputDeviceClass * d) {
			return static_cast<GUIInputDeviceBase *>(d->getUserData());
		}

		/**
		 * Move the associated device shape to a given
		 * position. This function handles the GUI part of
		 * GUIInputDevice::MoveInList().
		 *
		 * \param newpos New position of the shape in the
		 *  list. This parameter should reflect the actual
		 *  position of the device in the (non GUI) input
		 *  device list.
		 */
		virtual	void MoveToInList(int newpos);
		void Destroy();
		virtual void runtime_error(int type, const mutStringRef message, va_list & args);
	protected:
		void NotifyShapes();
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
		GUIfiedInputDevice(const mutStringRef name = mutEmptyString,
				   mutabor::MutaborModeType mode
				   = mutabor::DeviceStop,
				   int id = -1):T(name,
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


		virtual void  Play() {
			basetype::Play();
			GUIInputDeviceBase::Play();
		}
		virtual void  Pause() {
			basetype::Pause();
			GUIInputDeviceBase::Pause();
		}
		virtual void  Stop() {
			basetype::Stop();
			GUIInputDeviceBase::Stop();
		}
		virtual bool  Open() {
			bool retval = basetype::Open();
			if (retval) {
				retval &= GUIInputDeviceBase::Open();
				if (!retval)
					basetype::Close();
			}
			return retval;
		}
		virtual void  Close() {
			basetype::Close();
			GUIInputDeviceBase::Close();
		}


		/// add a route
		virtual void Add(mutabor::Route & route);
		/// replace a route
		virtual bool Replace(mutabor::Route & oldroute, mutabor::Route & newroute);
                /// remove a route
		virtual bool Remove(mutabor::Route & route);
		/// Move routes to another device
//		virtual bool MoveRoutes (DevicePtr newclass);

		virtual void DisconnectFromAll();
		virtual	int MoveInList(int count);
		virtual void  runtime_error(int type,
					    const mutString& message,
					    va_list & args) {
			GUIInputDeviceBase::runtime_error(type,
							  message,
							  args);
		}
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

		virtual mutabor::OutputDeviceClass * DoCreateOutput(const mutStringRef name,
								    int id = -1) const;


 		virtual mutabor::InputDeviceClass * DoCreateInput(const mutStringRef name,
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

		virtual mutabor::OutputDeviceClass * DoCreateOutput(const mutStringRef name,
								    int id = -1) const;
		virtual mutabor::InputDeviceClass * DoCreateInput(const mutStringRef name,
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

		virtual size_t GetType() const { return mutabor::DTGis;	}


		virtual mutabor::OutputDeviceClass * DoCreateOutput(const mutStringRef name,
								    int id = -1) const;

		virtual mutabor::InputDeviceClass * DoCreateInput(const mutStringRef name,
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
