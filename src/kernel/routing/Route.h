// -*- C++ -*-

/** \file
 ********************************************************************
 * Routing. Mutabor Core.
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/src/kernel/routing/Route.h,v 1.8 2011/11/02 14:31:57 keinstein Exp $
 * \author Rüdiger Krauße <krausze@mail.berlios.de>,
 * Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 1998
 * $Date: 2011/11/02 14:31:57 $
 * \version $Revision: 1.8 $
 * \license GPL
 *
 * $Log: Route.h,v $
 * Revision 1.8  2011/11/02 14:31:57  keinstein
 * fix some errors crashing Mutabor on Windows
 *
 * Revision 1.7  2011-10-02 16:58:41  keinstein
 * * generate Class debug information when compile in debug mode
 * * InputDeviceClass::Destroy() prevented RouteClass::Destroy() from clearing references -- fixed.
 * * Reenable confirmation dialog when closing document while the logic is active
 * * Change debug flag management to be more debugger friendly
 * * implement automatic route/device deletion check
 * * new debug flag --debug-trace
 * * generate lots of tracing output
 *
 * Revision 1.6  2011-09-30 18:07:04  keinstein
 * * make compile on windows
 * * s/wxASSERT/mutASSERT/g to get assert handler completely removed
 * * add ax_boost_base for boost detection
 *
 * Revision 1.5  2011-09-30 09:10:24  keinstein
 * Further improvements in the routing system.
 *
 * Revision 1.4  2011-09-27 20:13:21  keinstein
 * * Reworked route editing backend
 * * rewireing is done by RouteClass/GUIRoute now
 * * other classes forward most requests to this pair
 * * many bugfixes
 * * Version change: We are reaching beta phase now
 *
 * Revision 1.3  2011-02-20 22:35:56  keinstein
 * updated license information; some file headers have to be revised, though
 *
 * Revision 1.2  2010-11-21 13:15:46  keinstein
 * merged experimental_tobias
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
 * Revision 1.3.2.9  2010-07-06 09:06:26  keinstein
 * allow empty input and output devices in routes
 *
 * Revision 1.3.2.8  2010/06/15 14:30:14  keinstein
 * allow deleting of input devices in route window
 * several bug fixes
 * rudimentary box deletion support
 *
 * Revision 1.3.2.7  2010/06/02 11:20:08  keinstein
 * Route.h:
 * 	new enum BoxType
 * 	new box type NewBox
 *
 * IconShape.cpp:
 * 	Hide shape in MutIconShape::DeleteSelf
 *
 * MutChild.h:
 * 	Changes on the increment value for Clientsize
 *
 * MutLogicWnd:
 * 	smaller whitespace fixes
 *
 * MutRouteWnd.cpp:
 * 	save sizerflags for MutBoxShape too
 *
 * BoxChannelShape.cpp:
 * 	rename CreateRouteShape to CreateRoutePanel
 * 	replace some wxDynamicCast by dynamic_cast
 * 	add Box “New Box“ if current box is not found
 * 	delete Route if route panel is disabled
 *
 * BoxChannelShape.h:
 * 	Update BoxShape layout  if necessary
 *
 * BoxDlg.cpp:
 * 	RoutePanel::AddBox: allow NULL boxShape
 * 	Fix Bug that didn't preselect GUIDO boxes and Through mode
 *
 * BoxShape.cpp:
 * 	fix color mapping for box numbers (shift right by 1 bit).
 * 	Add MutBoxShape::sizerFlags
 * 	SetBoxId: New function
 * 	Use SetBoxId for setting Box Id an Label in sync
 * 	AddChannel: call Layout()
 * 	implement replacement in DoLeftDblClick (enables New Box)
 * 	ShowBoxDialog: use dynamic_cast
 * 	ReadDialog: Add Channel only if new route is enabled (not deleted)
 * 	ReplaceSelfBy: new function (Unreachable as only needed for
 * 		class NewMutBoxShape)
 *
 * NewBoxShape.cpp/.h:
 * 	replaceSelfBy: new function
 * 	initialize Box id as NewBox
 *
 * *.po/mutabor.pot/ *.gmo
 *  	Sync with sources
 *
 * Revision 1.3.2.6  2010/04/15 09:28:43  keinstein
 * changing routes works, but is not honoured by MIDI, yet
 *
 * Revision 1.3.2.5  2010/03/30 15:57:58  keinstein
 * added editing of existing routes to boxDlg
 *
 * Revision 1.3.2.4  2010/03/30 08:40:15  keinstein
 * added rudimentary command line support
 * changed debug system to allow selection of messages via command line
 * further enhancements to the route dialogs
 *
 * Revision 1.3.2.3  2010/02/15 12:08:20  keinstein
 * intermediate update for backup progress
 *
 * Revision 1.3.2.2  2010/01/14 09:34:24  keinstein
 * Checkin searching for a bug
 *
 * Revision 1.3.2.1  2009/08/04 11:30:49  keinstein
 * removed mut.h
 *
 *
 ********************************************************************
 *\addtogroup route
 *\{
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
#include "src/kernel/box.h"

#include "src/kernel/treestorage.h"

#ifndef MU32_ROUTING_ROUTE_H_PRECOMPILED
#define MU32_ROUTING_ROUTE_H_PRECOMPILED

// system headers which do seldom change
#include <boost/intrusive_ptr.hpp>
#include <list>

#ifdef WX
#include "wx/config.h"
#endif
// Route ------------------------------------------------------------

namespace mutabor {
        /// Type of route input filter
	enum RouteType
	{
		RTall, RTelse, RTchannel, RTstaff
	};
	
	extern const mutString RTName[];
	
	class OutputDeviceClass;
	typedef boost::intrusive_ptr<OutputDeviceClass> OutputDevice;
	class InputDeviceClass;
	typedef boost::intrusive_ptr<InputDeviceClass> InputDevice;	
	
	class RouteFactory;
	
	/// Class for managing routing
	/**
	* As we are using smart pointers the Route gets deleted, when no pointers
	* point to it any more. As we want to interactively manage routes,
	* We must allow routes to have no input device attached to it.
	*/
	template <class I=InputDevice, class O = OutputDevice>
	class TRouteClass
	{
		friend class RouteFactory;
	public:
		typedef TRouteClass thistype;
		typedef I InputDevice;
		typedef O OutputDevice;

		// To gain a little speed in realtime we use intrusive_ptr
		typedef boost::intrusive_ptr<TRouteClass> Route;
		typedef std::list<Route> routeListType;
		typedef std::list<thistype *> routePtrList;
	protected:
		// private members: access only via access functions for debugging purposes

		WATCHEDPTR(void,routing,TRouteClass) userdata;
		OutputDevice Out;
		InputDevice In;
	
		//Route Next;

		// This list is managed automatically and availlable 
		// only to not forget about routes. These references must not be counted
//		Route globalNext;
		static routeListType routeList;
		int Id;
		int inputid;
		int outputid;
		int Box;

		TRouteClass():
			userdata(this,_T("userdata")) {
			TRACEC;
			AppendToRouteList(this);
			InputDevice in (NULL);
			OutputDevice out (NULL);
			Create(in,out,RTall,
			       -1,-1,
			       -1,false,
			       -1,-1,true);
		}

		TRouteClass(
			InputDevice & in,
			OutputDevice & out,
			RouteType type = RTall,
			int iFrom = -1,
			int iTo = -1,
			int box = NoBox,
			bool active = false,
			int oFrom = -1,
			int oTo = -1,
			bool oNoDrum = true/*,
					     Route next = NULL*/):
			userdata(this,_T("userdata"))
			/*,  globalNext(NULL)*/
			{
				TRACEC;
				AppendToRouteList(this);
				Create(in,out,type,
				       iFrom,iTo,
				       box,active,
				       oFrom,oTo,oNoDrum/*,
							  next*/);
			}

		void Create(
			InputDevice & in,
			OutputDevice & out,
			RouteType type = RTall,
			int iFrom = -1,
			int iTo = -1,
			int box = NoBox,
			bool active = false,
			int oFrom = -1,
			int oTo = -1,
			bool oNoDrum = true/*,
					     Route next = NULL*/)
			{
				DEBUGLOG(smartptr,_T("Route %p (%d)"),
					 this, 
					 intrusive_ptr_get_refcount(this));
				DEBUGLOG(smartptr,_T("input device %p (%d)"),
					in.get(),
					intrusive_ptr_get_refcount(in.get()));
				DEBUGLOG(smartptr,_T("output device %p (%d)"),
					out.get(),
					intrusive_ptr_get_refcount(out.get()));
				if (in) 
					Attatch(in);
				else 
					In = NULL;
				if (out)
					Attatch(out);
				else 
					Out = NULL;
				Type = type;
				IFrom = iFrom;
				ITo = iTo;
				Box = box;
				Active = active;
				OFrom = oFrom;
				OTo = oTo;
				ONoDrum = oNoDrum;
				Id = NextRouteId();
				// Next=next;
			}

		
	public:
		RouteType Type;
		int IFrom, ITo;
		bool Active;
		int OFrom, OTo;
		bool ONoDrum;
		static int maxRouteId;

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
	
		static unsigned int NextRouteId() {
			return maxRouteId++;
		}


		char Check(int i) {
			return (IFrom <= i && i <= ITo);
		}
        protected:
		virtual void setUserData (void * data);

		virtual void * getUserData() const;
	public:

		const OutputDevice & GetOutputDevice() const {
			return Out;
		}

		const InputDevice & GetInputDevice() const {
			return In;
		}

		/// add a new output device
		virtual void Add (OutputDevice & out);
		/// add a new input device
		virtual void Add (InputDevice & in);
		/// add a new box
		virtual void Add(int id);
		/// replace an existing output device
		virtual bool Replace (OutputDevice & olddev, 
				      OutputDevice & newdev);
		/// replace an existing input device
		virtual bool Replace (InputDevice & olddev, 
				      InputDevice & newdev);
		/// replace an existing box
		virtual bool Replace (int oldbox, int newbox);
		/// remove an existing output device
		virtual bool Remove (OutputDevice & out);
		/// remove an existing input device
		virtual bool Remove (InputDevice & in);
		/// remov an existing box
		virtual bool Remove (int id);

		/// Attatch a new output device
		virtual void Attatch (OutputDevice & dev);

		/// Attatch a new input device
		virtual void Attatch (InputDevice & dev);

		/// Attach a new box
		virtual void Attatch (int boxid) {
			Add(boxid);
		}

		/// Replace current output device with a new one
		virtual bool Reconnect(OutputDevice & olddev, 
				       OutputDevice & newdev);

		/// Replace current input device with a new one
		virtual bool Reconnect(InputDevice & olddev, 
				       InputDevice & newdev);

		/// Replace current box with a new one
		virtual bool Reconnect(int oldboxid,
			       int newboxid) {
			return Replace(oldboxid,newboxid);
		}

		/// Detatch current output device
		virtual bool Detatch(OutputDevice & dev);

		/// Detatch current input device
		virtual bool Detatch(InputDevice & dev);

		/// Detach a current box
		virtual bool Detatch(int boxid) {
			return Remove(boxid);
		}

	
		void SetDeviceId(int Id,I) {
			inputid = Id;
		}

		void SetDeviceId(int Id,O) {
			outputid = Id;
		}
		int GetDeviceId(I) {
			return inputid;
		}

		int GetDeviceId(O) {
			return outputid;
		}

	
		bool GetActive() const 
			{
				return Active;
			}
	
		void SetActive(bool active) 
			{
				Active = active;
			}
	
		int GetBox() const
			{
				return Box;
			}
	
		virtual void SetBox(int box)
			{
				Box = box;
			}
	
		RouteType GetType() const
			{
				return Type;
			}
	
		void SetType(RouteType type)
			{
				Type = type;
			}
	
		const mutString & GetTypeName()
			{
				return RTName[Type];
			}
	
		int GetInputFrom() const
			{
				return IFrom;
			}
	
		void SetInputFrom(int i)
			{
				IFrom = i;
			}
	
		int GetOutputFrom() const
			{
				return OFrom;
			}
	
		void SetOutputFrom(int o)
			{
				OFrom = o;
			}
	
		int GetInputTo() const
			{
				return ITo;
			}
	
		void SetInputTo(int i)
			{
				ITo = i;
			}
	
		int GetOutputTo() const
			{
				return OTo;
			}
	
		void SetOutputTo(int o)
			{
				OTo = o;
			}
	
	
		bool OutputAvoidDrumChannel() const
			{
				return ONoDrum;
			}
		void OutputAvoidDrumChannel(bool avoid) 
			{
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
		int GetId() const {
			return Id;
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
		virtual void Destroy() {
			debug_destroy_class(this);
			RemoveFromRouteList(this);
			if (In) Detatch(In);
			if (Out) Detatch(Out);
		}
	
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
	protected:
		static void AppendToRouteList (Route route);
		static void RemoveFromRouteList (Route route);
	
		REFPTR_INTERFACE
	};

	template<class I, class O> 
	typename TRouteClass<I,O>::routeListType TRouteClass<I,O>::routeList;

	typedef TRouteClass<InputDevice,OutputDevice>::Route Route;
	typedef TRouteClass<InputDevice,OutputDevice> RouteClass;
	typedef TRouteClass<InputDevice,OutputDevice>::routeListType routeListType;
	typedef TRouteClass<InputDevice,OutputDevice>::routePtrList routePtrList;

	class RouteFactory { 
	protected:
		static RouteFactory * factory;
	
		RouteFactory();
		virtual ~RouteFactory();

		virtual RouteClass * DoCreate() const __attribute__ ((malloc));
		virtual RouteClass * DoCreate(
			InputDevice & in,
			OutputDevice & out,
			RouteType type,
			int iFrom,
			int iTo,
			int box,
			bool active,
			int oFrom,
			int oTo,
			bool oNoDrum /*,
				       Route next*/) const __attribute__ ((malloc));
	
		/// load the routes from a tree based configuration
		/** \param config conifiguration to be read from
		 */
		virtual void DoLoadRoutes(tree_storage & config) const;

		/// write the routes to the configuration
		/** \param config configuration to be written to
		 */ 
		virtual void DoSaveRoutes(tree_storage & config) const;
	
	public:
		static Route Create() {
			if (factory)
				return factory->DoCreate();
			else
				UNREACHABLECT(RouteFactory);
			return NULL;
		}
		static Route Create(
			InputDevice & in,
			OutputDevice & out,
			RouteType type = RTall,
			int iFrom = -1,
			int iTo = -1,
			int box = -1,
			bool active = false,
			int oFrom = -1,
			int oTo = -1,
			bool oNoDrum = true /*,
					      Route next = 0*/);
		static void Destroy() {
			if (factory)
				delete factory;
			else 
				UNREACHABLECT(RouteFactory);
		}


		/// load the routes from a tree based configuration
		/** \param config conifiguration to be read from
		 */
		static void LoadRoutes(tree_storage & config) {
			if (factory)
				factory->DoLoadRoutes(config);
			else 
				UNREACHABLECT(RouteFactory);
		}

		/// write the routes to the configuration
		/** \param config configuration to be written to
		 */ 
		static void SaveRoutes(tree_storage & config) {
			if (factory)
				factory->DoSaveRoutes(config);
			else 
				UNREACHABLECT(RouteFactory);
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

