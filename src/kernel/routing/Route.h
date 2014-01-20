// -*- C++ -*-

/** \file
 ********************************************************************
 * Routing. Mutabor Core.
 *
 * \author Rüdiger Krauße <krausze@mail.berlios.de>,
 * Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 1998-2013
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
 ********************************************************************
 *\defgroup route Basic event routing functions
 *
 * This group contains functions and classes that can be used to set
 * up a generic event routing. It uses the RtMidi library for MIDI
 * access, but is kept independent from any GUI library.
 *
 * \{
 ********************************************************************/

/* we guard a little bit complicated to ensure the references are set right
 */

#if (!defined(MU32_ROUTING_ROUTE_H) && !defined(PRECOMPILE)) \
	|| (!defined(MU32_ROUTING_ROUTE_H_PRECOMPILED))
#ifndef PRECOMPILE
#define MU32_ROUTING_ROUTE_H
#endif

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

#include "src/kernel/Defs.h"
#include "src/kernel/MidiKern.h"

#include "src/kernel/treestorage.h"
#include "src/kernel/boost-interface.h"

#ifndef MU32_ROUTING_ROUTE_H_PRECOMPILED
#define MU32_ROUTING_ROUTE_H_PRECOMPILED

// system headers which do seldom change
#include <list>
#include <vector>
#include <stdexcept>
#include "boost/throw_exception.hpp"
//#include "boost/intrusive_ptr.hpp"

#ifdef WX
#include "wx/config.h"
#endif
// Route ------------------------------------------------------------
namespace mutaborGUI {
	class GUIRouteBase;
}

namespace mutabor {
	typedef std::vector<uint8_t> midi_string;


        /// Type of route input filter
	enum RouteType
	{
		RTall,							 /**< all events will pass */
		RTelse,							 /**< all unhandled events will pass */
		RTchannel,						 /**< use only a certain channel range (depends on the input device type) */
		RTstaff							 /**< use only a certain staff/track/… range (depends on the input device type) */
	};
	
	extern const mutString RTName[];
	
	class OutputDeviceClass;
	typedef boost::intrusive_ptr<OutputDeviceClass> OutputDevice;
	class InputDeviceClass;
	typedef boost::intrusive_ptr<InputDeviceClass> InputDevice;	
	class ChannelData;
	class BoxClass;
	typedef boost::intrusive_ptr<BoxClass> Box;	
	
	class RouteFactory;
	
	/// Class for managing routing
	/**
	* As we are using smart pointers the Route gets deleted, when no pointers
	* point to it any more. As we want to interactively manage routes,
	* We must allow routes to have no input device attached to it.
	*/
	template <class I=InputDevice, class O = OutputDevice, class B = Box>
	class TRouteClass
	{
		friend class RouteFactory;
		/// \todo remove this reference after GUI is working again
		friend class mutaborGUI::GUIRouteBase;
	public: // types
		typedef TRouteClass thistype;
		typedef I InputDevice;
		typedef O OutputDevice;
		typedef B Box;

		// To gain a little speed in realtime we use intrusive_ptr
		typedef boost::intrusive_ptr<TRouteClass> Route;
		typedef std::list<Route> routeListType;
		typedef std::list<thistype *> routePtrList;
	protected: // types
		// private members: access only via access functions for debugging purposes

		class NoOutputDevice:std::invalid_argument {
		public:
			Route route;
			NoOutputDevice(const thistype * r):
			invalid_argument(gettext_noop("No such output device")) {
				route = const_cast<thistype *>(r);
			}
			virtual ~NoOutputDevice() throw() {} 
		};
		class NoInputDevice {
		public:
			Route route;
			NoInputDevice(const thistype * r) 
			{
				route = const_cast<thistype *>(r);
			}
		};
	public: // functions
		virtual ~TRouteClass();

		/// Write the route settings into a tree based configuration.
		/** \argument config (tree_storage &) configuration where 
		 * the route settings will be stored
		 */
		virtual void Save(tree_storage & config);

		/// Read the route into from a tree based configuration.
		/** \argument config (tree_storage &) configuration 
		 * where the route settings will be read from
		 */
		virtual void Load(tree_storage & config);
	

		char Check(int i) {
			return (IFrom <= i && i <= ITo);
		}

		const OutputDevice & GetOutputDevice() const {
			return Out;
		}

		const InputDevice & GetInputDevice() const {
			return In;
		}


		void NoteOn(int key,
			    int velocity,
			    size_t make_unique,
			    const ChannelData & input_channel_data,
			    void * userdata ) {
			if (Active) {
				// global C part
				box->AddNote(key, make_unique, session_id, userdata);
				DEBUGLOG(routing,_T("(key = %d, channel = %lu, id = %lu)"),
					 key,
					 (unsigned long)get_session_id(),
					 (unsigned long)make_unique);
			}
			if (Out) {
				Out->NoteOn(box,
					    key, velocity, this, make_unique, 
					    input_channel_data);						    
			}
		}

		void NoteOff(int key,
			     int velocity,
			     size_t make_unique) {
			if (Active) {
				box->DeleteNote(key, 
					       make_unique, 
					       session_id);
			}
			if (Out) {
				Out->NoteOff(box, 
					     key, 
					     velocity,
					     this, 
					     make_unique,
					     false);
			}
		}

		void MidiAnalysis(DWORD midiCode) {
			/// \todo Delegate midi data as Message to the box.
			static const int midilength[8] = {
				3, 3, 3, 3, 2, 2, 3, 1
			};

			if (!(box && box->IsNormal() && Active )) return;
			if (!(midiCode & 0x80)) {
				UNREACHABLEC;
				return;
			}

			int len = midilength[(midiCode & 0x70) >> 4];
			for (int i = 0; i <  len; i++) {
				if (box)
					box->MidiAnalysis(midiCode & 0xff);
				midiCode >>= 8;
			}
		}

		void MidiOut(midi_string & data) {
			if (Out)
				Out->MidiOut(box,data);
		}

		void UpdateTones() {
			if (Out && Out->IsOpen()) 
				Out->UpdateTones(this);
		}

		int GetChannel(int key, size_t channel, size_t id) {
			if (channel == session_id()) 
				return Out->GetChannel(key, channel, id);
			return midi::NO_CHANNEL;
		}

		void Panic(int type) {
			if (box)
				box-> Panic(this,type);
			if (Out) 
				Out -> Quiet(this, type);
		}

		void Panic(int type, size_t unique_id) {
			if (box)
				box-> Panic(this, type, unique_id);
			if (Out) 
				Out -> Quiet(this, type, unique_id);
		}

		void Controller(int controller, int value) {
			if (Out) Out->Controller(session_id, controller, value);
		}

		/// add a new output device
		virtual void Add (OutputDevice & out);
		/// add a new input device
		virtual void Add (InputDevice & in);
		/// add a new box
		virtual void Add(Box & b);
		/// replace an existing output device
		virtual bool Replace (OutputDevice & olddev, 
				      OutputDevice & newdev);
		/// replace an existing input device
		virtual bool Replace (InputDevice & olddev, 
				      InputDevice & newdev);
		/// replace an existing box
		virtual bool Replace (Box & oldbox, Box & newbox);
		/// remove an existing output device
		virtual bool Remove (OutputDevice & out);
		/// remove an existing input device
		virtual bool Remove (InputDevice & in);
		/// remov an existing box
		virtual bool Remove (Box & b);

		void SetDeviceId(int Id,I) {
			inputid = Id;
		}

		void SetDeviceId(int Id,O) {
			outputid = Id;
		}
		void SetBoxId(int Id) {
			boxid = Id;
		}

		int GetDeviceId(I) {
			return inputid;
		}

		int GetDeviceId(O) {
			return outputid;
		}
		int GetBoxId() {
			return boxid;
		}

	
		bool GetActive() const {
			return Active;
		}
	
		void SetActive(bool active) {
			Active = active;
		}
	
		Box GetBox() const {
			return box;
		}
	
		virtual void SetBox(Box b) {
			box = b;
		}
	
		RouteType GetType() const {
			return Type;
		}
	
		void SetType(RouteType type) {
			Type = type;
		}
	
		const mutString & GetTypeName()	{
			return RTName[Type];
		}
	
		int GetInputFrom() const {
			return IFrom;
		}
	
		void SetInputFrom(int i) {
			IFrom = i;
		}
	
		int GetOutputFrom() const {
			return OFrom;
		}
	
		void SetOutputFrom(int o) {
			OFrom = o;
		}
	
		int GetInputTo() const {
			return ITo;
		}
	
		void SetInputTo(int i) {
			ITo = i;
		}
	
		int GetOutputTo() const	{
			return OTo;
		}
	
		void SetOutputTo(int o)	{
			OTo = o;
		}
	
	
		bool OutputAvoidDrumChannel() const {
			return ONoDrum;
		}
		void OutputAvoidDrumChannel(bool avoid) {
			ONoDrum = avoid;
		}
	
#if 0
		Route  GetNext() const {
			return Next;
		}

		void SetNext(Route  route) {
			Next = route;
		}
#endif	
		int get_routefile_id () const {
			return routefile_id;
		}
	
		size_t get_session_id () const {
			return session_id;
		}

		static const  routeListType & GetRouteList() {
			return routeList;
		}
#if 0	
		Route  GetGlobalNext() {
			return globalNext;
		}
#endif


		/// Remove from Route list to be deleted, when it becomes free.
		/**
		 * As we are using smart pointers the Route gets deleted, when no pointers
		 * point to it any more. As we want to interactively manage routes,
		 * We must allow routes to have no input device attached to it. This
		 * function explicitely allows to delete the object when it is not used 
		 * any more.
		 */
		virtual void Destroy();
	
		/// Initialize the internal device identifiers.
		/** This function sets the internal device ids of 
		 *  all input devices, starting from 0 and 
		 *  incrementing by 1
		 */
		static void InitializeIds();

		/// Save the current routes in a tree storage.
		/** This function saves all routes in a tree based storage.
		 *  \argument config (tree_storage *) storage driver to use for saving.
		 */
		static void SaveRoutes(tree_storage & config);

		/// Load the current routes from a tree storage.
		/** This function loads all routs from a tree based storage.
		 *  \argument config (tree_storage *) storage driver to use for saving.
		 */
		static void LoadRoutes(tree_storage & config);

		static void ClearRouteList() {
			TRACET(thistype);
			Route d;
			while (!routeList.empty()) {
				mutASSERT(intrusive_ptr_get_refcount(d.get()) <= 1);
				TRACET(thistype);
				d = routeList.front();
				TRACET(thistype);
				d->Destroy();

				mutASSERT(routeList.empty() || 
					 d != routeList.front());
			}
			mutASSERT(intrusive_ptr_get_refcount(d.get()) <= 1);
			TRACET(thistype);
			d = NULL;
			TRACET(thistype);
		}
#ifdef WX
		virtual wxString TowxString() const;
#endif
	protected: // members
		WATCHEDPTR(void,routing,TRouteClass) userdata;
		OutputDevice Out;
		InputDevice In;
		Box box;
	
		//Route Next;

		// This list is managed automatically and availlable 
		// only to not forget about routes. These references must not be counted
//		Route globalNext;
		static routeListType routeList;
		idtype<TRouteClass<I,O> > session_id;
		int routefile_id;
		int inputid;
		int outputid;
		int boxid;

		
		RouteType Type;
		int IFrom, ITo;
		bool Active;
		int OFrom, OTo;
		bool ONoDrum;

		// functions
		TRouteClass():
			userdata(this,_T("userdata")) {
			TRACEC;
			AppendToRouteList(this);
			InputDevice in (NULL);
			OutputDevice out (NULL);
			Create(in,out,RTall,
			       -1,-1,
			       NULL,
			       false,
			       -1,-1,true);
		}

		TRouteClass(
			InputDevice & in,
			OutputDevice & out,
			RouteType type = RTall,
			int iFrom = -1,
			int iTo = -1,
			Box & box = NULL,
			bool active = false,
			int oFrom = -1,
			int oTo = -1,
			bool oNoDrum = true):
			userdata(this,_T("userdata"))
			{
				TRACEC;
				AppendToRouteList(this);
				Create(in,out,type,
				       iFrom,iTo,
				       box,
				       active,
				       oFrom,oTo,oNoDrum);
			}

		void Create(InputDevice & in,
			    OutputDevice & out,
			    RouteType type = RTall,
			    int iFrom = -1,
			    int iTo = -1,
			    Box box = NULL,
			    bool active = false,
			    int oFrom = -1,
			    int oTo = -1,
			    bool oNoDrum = true);

		virtual void setUserData (void * data);

		virtual void * getUserData() const;
		static void AppendToRouteList (Route route);
		static void RemoveFromRouteList (Route route);
	
		REFPTR_INTERFACE;
	};

	template<class I, class O, class B> 
	typename TRouteClass<I,O, B>::routeListType TRouteClass<I,O, B>::routeList;

	typedef TRouteClass<InputDevice,OutputDevice, Box>::Route Route;
	typedef TRouteClass<InputDevice,OutputDevice, Box> RouteClass;
	typedef TRouteClass<InputDevice,OutputDevice, Box>::routeListType routeListType;
	typedef TRouteClass<InputDevice,OutputDevice, Box>::routePtrList routePtrList;


	Route FindRoute(size_t id);

	// see Route-inlines for the connecting functions:

       /** Class for creation of Routes.   
	* This class will create a
	* route object corresponding to the type given to the Create function.
	* 
	* Though the interface is mainly prepared to provide the
	* necessary means for adding new route types, it currently
	* stores only one route factory.
	*/
	class RouteFactory { 
	
	public:

		/** 
		 * Douplicate route factory exception.
		 * This class is thrown if a routefactory is already set.
		 * 
		 */
		struct FactoryAlreadySet:public std::logic_error {
			RouteFactory * old; 
			RouteFactory * created;
			FactoryAlreadySet(RouteFactory * o, RouteFactory * n): logic_error(gettext_noop("Route factory already set")),
											   old(o), created(n) {}
		};

		struct RouteFactoryNotSet:public std::logic_error {
			RouteFactoryNotSet():logic_error(gettext_noop("Trying to create a route without the correct factory. You (the programmer) must create one!")) {}
		};
			
                /** Creates a route Factory.  
		 * Constructor. Should be overridden if classes inhert from Route.
		 */		
		RouteFactory();

		/** Creates a generic route.  
		 * This functions creates a
		 * route object on the heap and returns a smart
		 * pointer to it. This route will not be preconfigured.
		 * 
		 * \return Route smart pointer to the newly created route
		 */
		static Route Create() {
			if (factory)
				return factory->DoCreate();
			else
				boost::throw_exception(RouteFactoryNotSet());
			return NULL;
		}


		/** Creates a preconfigured route according to the given type. 
		 * This functions creates a
		 * route object on the heap and returns a smart
		 * pointer to it. This route will be preconfigured according 
		 * the data provided in the arguments.
		 * 
		 * \param in InputDevice& Reference to a smart pointer
		 * for the input device where the route starts.
		 * \param out OutputDevice& End point of the route.
		 * \param type RouteType Type of the input filter. See RouteType for more information.
		 * \param iFrom start of the range for the input filter. Its meaning depends on the input filter type.
		 * \param iTo end of the range for the input filter. Its meaning depends on the input filter type.
		 * \param box box to be used. Values less than 0 indicate a pass through route or a GMN box.
		 * \param active indicates whether the events on the route may 
		 * change the tuning of the box. Regardless of this setting the
		 * box referenced by the box parameter will influence the 
		 * tuning of the events in this route.
		 * \param oFrom Start of the range of the output filter (will be interpreted by the output device.
		 * \param oTo End of the reange of the output fileter (will be interpreted by the output device
		 * \param oNoDrum On MIDI like devices avoid the channel usually used for percussion.
		 * 
		 * \return Route created by this function (smart pointer).
		 */
		inline static Route Create(
			InputDevice & in,
			OutputDevice & out,
			RouteType type = RTall,
			int iFrom = -1,
			int iTo = -1,
			Box box = NULL,
			bool active = false,
			int oFrom = -1,
			int oTo = -1,
			bool oNoDrum = true);

		/** 
		 * Destroy the route factory. Call this function instead of deleting the factory.
		 * 
		 */

		static void Destroy() {
			if (factory)
				delete factory;
			else 
				boost::throw_exception( RouteFactoryNotSet());
//				UNREACHABLECT(RouteFactory);
		}


		/// load the routes from a tree based configuration
		/** \param config conifiguration to be read from
		 */
		static void LoadRoutes(tree_storage & config) {
			if (factory)
				factory->DoLoadRoutes(config);
			else 
				boost::throw_exception( RouteFactoryNotSet());
//				UNREACHABLECT(RouteFactory);
		}

		/// write the routes to the configuration
		/** \param config configuration to be written to
		 */ 
		static void SaveRoutes(tree_storage & config) {
			if (factory)
				factory->DoSaveRoutes(config);
			else 
				boost::throw_exception( RouteFactoryNotSet());
			// UNREACHABLECT(RouteFactory);
		}
	protected:
		/** Destructor. 
		 * This destructor will destroy the route factory. It does not touch the 
		 * route objects that are created using this class.
		 *
		 * You should not delete the factory directly as it saves a pointer to 
		 */
		virtual ~RouteFactory();

		/** Creates a generic route.  This functions creates a
		 * route object on the heap and returns a smart
		 * pointer to it. This route will not be preconfigured.
		 *
		 * Each RouteFactory class must override this function
		 * to return a route of its type.
		 * 
		 * \return Route smart pointer to the newly created route
		 */
		virtual RouteClass * DoCreate() const __attribute__ ((malloc));

		/** Creates a preconfigured route. 
		 * This functions creates a
		 * route object on the heap and returns a smart
		 * pointer to it. This route will be preconfigured according 
		 * the data provided in the arguments.
		 *
		 * Each RouteFactory class must override this function
		 * to return a route of its type.
		 * 
		 * \param in InputDevice& Reference to a smart pointer
		 * for the input device where the route starts.
		 * \param out OutputDevice& End point of the route.
		 * \param type RouteType Type of the input filter. See RouteType for more information.
		 * \param iFrom start of the range for the input filter. Its meaning depends on the input filter type.
		 * \param iTo end of the range for the input filter. Its meaning depends on the input filter type.
		 * \param box box to be used. Values less than 0 indicate a pass through route or a GMN box.
		 * \param active indicates whether the events on the route may 
		 * change the tuning of the box. Regardless of this setting the
		 * box referenced by the box parameter will influence the 
		 * tuning of the events in this route.
		 * \param oFrom Start of the range of the output filter (will be interpreted by the output device.
		 * \param oTo End of the reange of the output fileter (will be interpreted by the output device
		 * \param oNoDrum On MIDI like devices avoid the channel usually used for percussion.
		 * 
		 * \return Route created by this function (smart pointer).
		 */
		virtual RouteClass * DoCreate(
			InputDevice & in,
			OutputDevice & out,
			RouteType type,
			int iFrom,
			int iTo,
			Box box,
			bool active,
			int oFrom,
			int oTo,
			bool oNoDrum) const __attribute__ ((malloc));
	
	
		/// load the routes from a tree based configuration
		/** \param config conifiguration to be read from
		 */
		virtual void DoLoadRoutes(tree_storage & config) const;

		/// write the routes to the configuration
		/** \param config configuration to be written to
		 */ 
		virtual void DoSaveRoutes(tree_storage & config) const;

		static RouteFactory * factory;				 /**< Pointer to the current factory */
	};

	class ScopedRoute: public Route {
	public:
		~ScopedRoute();

		ScopedRoute & operator = (element_type * rhs) {
			(*(static_cast<Route *>(this))) = rhs;
			return *this;
		}
		ScopedRoute & operator = (const Route & rhs) {
			(*(static_cast<Route *>(this))) = rhs;
			return *this;
		}
	};

	extern const mutString DevTypeName[];

	/// An empty route to be passed by reference
	/** somtimes we need to pass NULL to a function
	    expecting (Route &). This we define NullRoute
	    that can be used in such situations */
	extern Route NullRoute; 


}
#endif /* PRECOMPILED */
#endif

/*
 * \}
 */

