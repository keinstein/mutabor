// -*- C++ -*-

/** \file
 ********************************************************************
 * Routing. Mutoabor Core.
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/mu32/routing/Device.h,v 1.8 2011/09/30 09:10:24 keinstein Exp $
 * \author Rüdiger Krauße <krausze@mail.berlios.de>,
 * Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 1998
 * $Date: 2011/09/30 09:10:24 $
 * \version $Revision: 1.8 $
 * \license GPL
 *
 * $Log: Device.h,v $
 * Revision 1.8  2011/09/30 09:10:24  keinstein
 * Further improvements in the routing system.
 *
 * Revision 1.7  2011-09-27 20:13:21  keinstein
 * * Reworked route editing backend
 * * rewireing is done by RouteClass/GUIRoute now
 * * other classes forward most requests to this pair
 * * many bugfixes
 * * Version change: We are reaching beta phase now
 *
 * Revision 1.6  2011-09-04 12:02:08  keinstein
 * require wxWidgets 2.8.5 configure.in
 *
 * Revision 1.5  2011-02-20 22:35:56  keinstein
 * updated license information; some file headers have to be revised, though
 *
 * Revision 1.4  2010-12-13 00:27:53  keinstein
 * compiles in linux as well as in mingw
 *
 * Revision 1.3  2010-11-21 23:39:00  keinstein
 * some corrections for allowing debuild to complete
 *
 * Revision 1.2  2010-11-21 13:15:45  keinstein
 * merged experimental_tobias
 *
 * Revision 1.1.2.7  2010-11-18 21:46:14  keinstein
 * MutFrame: get rid of OnIdle (this may break something, but saves much more CPU cycles
 * Some further steps to get rid of EDevice*
 *
 * Revision 1.1.2.6  2010-11-14 21:28:38  keinstein
 * implement loading and saving old files with new routing system
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
 * Revision 1.9.2.13  2010-07-06 09:06:26  keinstein
 * allow empty input and output devices in routes
 *
 * Revision 1.9.2.12  2010/06/22 15:05:45  keinstein
 * debugging segfault in route check after replacement of MutOutputDevice
 *
 * Revision 1.9.2.11  2010/06/21 14:28:12  keinstein
 * implement deletion of output devices
 *
 * Revision 1.9.2.10  2010/06/15 14:30:14  keinstein
 * allow deleting of input devices in route window
 * several bug fixes
 * rudimentary box deletion support
 *
 * Revision 1.9.2.9  2010/05/07 11:40:27  keinstein
 * actual_settings
 *
 * Revision 1.9.2.8  2010/04/26 15:53:05  keinstein
 * BoxDlg reacts on “Remove Route”. Implementation of routing must be checked.;
 *
 * Revision 1.9.2.7  2010/04/20 17:41:38  keinstein
 * One step towards using Mutabor: Activation of a logic now honours the state of the Device Editor.
 *
 * Revision 1.9.2.6  2010/04/15 09:28:43  keinstein
 * changing routes works, but is not honoured by MIDI, yet
 *
 * Revision 1.9.2.5  2010/03/30 08:40:15  keinstein
 * added rudimentary command line support
 * changed debug system to allow selection of messages via command line
 * further enhancements to the route dialogs
 *
 * Revision 1.9.2.4  2010/02/15 12:08:20  keinstein
 * intermediate update for backup progress
 *
 * Revision 1.9.2.3  2010/01/14 09:34:24  keinstein
 * Checkin searching for a bug
 *
 * Revision 1.9.2.2  2009/11/03 12:39:30  keinstein
 * input device dialog: Allow to edit input devices
 * fix a bug on Mac OS X, that prevented Mutabor from starting if no MIDI device is availlable
 *
 * Revision 1.9.2.1  2009/08/04 11:30:49  keinstein
 * removed mut.h
 *
 *
 ********************************************************************
 *\addtogroup route
 *\{
 ********************************************************************/

/* we guard a little bit complicated to ensure the references are set right
 */

#if (!defined(MU32_ROUTING_DEVICE_H) && !defined(PRECOMPILE)) \
	|| (!defined(MU32_ROUTING_DEVICE_H_PRECOMPILED))
#ifndef PRECOMPILE
#define MU32_ROUTING_DEVICE_H
#endif

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

#include "Defs.h"
#include "GIS.h"
#include "Route.h"

#ifndef MU32_ROUTING_DEVICE_H_PRECOMPILED
#define MU32_ROUTING_DEVICE_H_PRECOMPILED

// system headers which do seldom change

#include <vector>
#include <list>
#include <algorithm>
#include "wx/stopwatch.h"

#define DRUMCHANNEL 9  // Schlagzeugkanal bei General Midi (Kanal 9, bzw. 10)

namespace mutabor {

	enum MutaborModeType {
		DeviceUnregistered = -1,
		DeviceStop,
		DevicePlay,
		DevicePause,
		DeviceCompileError,
		DeviceTimingError
	};

	extern char InDevChanged;

// Device Typen
	enum DevType
	{
		DTNotSet = -1, DTUnknown, DTMidiPort, DTMidiFile, DTGis
	};

#define DeviceMaxType DTGis+1

// channel data -----------------------------------------------------

	class ChannelData
	{

	public:
		int Sound;          // -1 = noch nicht verwendet
		char Sustain;
		int BankSelectMSB;  // -1 .. noch nicht benutzt
		int BankSelectLSB;  // -1 .. noch nicht benutzt
		long Pitch;         // 0 = ungepitcht, kann durchaus auch negativ sein
		ChannelData(int sound = -1, char sustain = 0)
			{
				Sound = sound;
				Sustain = sustain;
				BankSelectMSB = -1;
				BankSelectLSB = -1;
				Pitch = 0;
			}

		void Reset()
			{
				Sound = -1;
				Sustain = 0;
				BankSelectMSB = -1;
				BankSelectLSB = -1;
			}

		bool operator ==(ChannelData &cd)
			{
				return ( Sound == -1 || cd.Sound == -1 || Sound == cd.Sound ) &&
					( Sustain == -1 || cd.Sustain == -1 || Sustain == cd.Sustain ) &&
					( BankSelectMSB == -1 || cd.BankSelectMSB == -1 || BankSelectMSB == cd.BankSelectMSB ) &&
					( BankSelectLSB == -1 || cd.BankSelectLSB == -1 || BankSelectLSB == cd.BankSelectLSB );
			}
	};


	class Device
	{
	private:
		void * userdata;
		int Id;
	protected:
		int DevId;
		mutString Name;
		bool dirty:1;
		bool isOpen:1;
		routeListType routes;
	
		Device():userdata(NULL),Id(-1),
			 DevId(-1),
			 Name(mutEmptyString),
			 dirty(false),
			 isOpen(false),
			 routes() { }
	
		Device(int devid, 
		       const mutStringRef name = mutEmptyString,
		       int id = -1):userdata(NULL),
				    Id(id),
				    DevId(devid),
				    Name(name),
				    dirty(false),
				    isOpen(false),
				    routes() {}
	
	public:
		virtual ~Device() {	}
	
		/// Save current device settings in a tree storage
		/** \argument config (tree_storage) storage class, where the data will be saved.
		 */
		virtual void Save (tree_storage & config) = 0;
	
		/// Save route settings (filter settings) for a given route
		/** Some route settings (e.g. filter settings) are device type 
		 * specific. This function saves them in a tree storage.
		 * \argument config (tree_storage *) Storage class, where the data will be saved.
		 * \argument route (Route) Route whos data shall be saved.
		 */
		virtual void Save (tree_storage & config, 
				   const RouteClass * route) = 0;
	
		/// Load current device settings from a tree storage
		/** \argument config (tree_storage) storage class, where the data will be loaded from.
		 */
		virtual void Load (tree_storage & config) = 0;
	
		/// Load route settings (filter settings) for a given route
		/** Some route settings (e.g. filter settings) are device type 
		 * specific. This function loads them from a tree storage.
		 * \argument config (tree_storage *) Storage class, where the data will be restored from.
		 * \argument route (Route) Route whos data shall be loaded.
		 */
		virtual void Load (tree_storage & config, 
				   RouteClass * route) = 0;
	

		/// add a route
		virtual void Add(Route route) = 0;
		/// replace a route
		virtual bool Replace(Route oldRoute, Route newRoute) = 0;
                /// remove a route
		virtual bool Remove(Route route) = 0;
	protected: /** \todo lift this restrection afer GUI is working again */
		friend class GUIOutputDeviceBase;
		friend class GUIInputDeviceBase;
		virtual void setUserData (void * data) {
			userdata = data; 
		}
		virtual void * getUserData() const { return userdata; }
	public:

		const wxString & GetName() const
			{
				return Name;
			}
	
		virtual void SetName(const wxString & s) 
			{
				Name = s;
			}
	
		int GetDevId() const
			{
				return DevId;
			}
	
		virtual void SetDevId(int id)
			{
				DevId = id;
			}
	
		int GetId() const
			{
				return Id;
			}

		virtual void ReadData(wxConfigBase * config) {};
		virtual void WriteData(wxConfigBase * config) {};	
	
		virtual mutString GetTypeName () const {
			return N_("Device base class");
		}

		virtual bool Open() = 0;
		virtual void Close() = 0;
	
		bool IsDirty() const { return dirty; }
		void Dirty(bool d=true) { dirty = d; }
		bool IsOpen() const { return isOpen; }

#ifdef WX
		virtual wxString TowxString() const;
#endif
	protected:
		void SetId(int id)
			{
				Id = id;
			}
	};

	// A common api for input and output devices that must be typed

	template <class T, class P = boost::intrusive_ptr<T>, 
		  class L = std::list <P> >
	class CommonTypedDeviceAPI: public Device {
	private:
		REFPTR_INTERFACE
		
	public:
		// To gain a little speed in realtime we use intrusive_ptr
		typedef T thistype;
		typedef P DevicePtr;
		typedef L listtype;
	protected:
	        static listtype deviceList;

		CommonTypedDeviceAPI():Device()
			{
				AppendToDeviceList(static_cast<thistype *>(this));
			}

		CommonTypedDeviceAPI(int devId, 
				     const mutStringRef name, 
				     int id = -1):Device(devId, name, id)
			{
				AppendToDeviceList(static_cast<thistype *>(this));
			}


	public:
		virtual ~CommonTypedDeviceAPI();

		virtual void Destroy() {
			RemoveFromDeviceList(static_cast<thistype *>(this));
		}

		/// add a route
		virtual void Add(Route route);
		/// replace a route
		virtual bool Replace(Route oldroute, Route newroute);
                /// remove a route
		virtual bool Remove(Route route);
		/// Move routes to another device 
		virtual bool MoveRoutes (DevicePtr newclass);

        
		/// Attatch to a given route
		void Attatch(Route & route) {
			DEBUGLOG(smartptr,_T("Route; %p"),route.get());
			route -> Attatch(DevicePtr(thisptr()));
			DEBUGLOG(smartptr,_T("Route; %p"),route.get());
		}

		/// Replace a given route 
		void Reconnect(Route & oldroute, Route & newroute) {
			DEBUGLOG(smartptr,_T("oldroute: %p, newroute: %p"),
				 oldroute.get(),newroute.get());
			bool ok = Replace(oldroute,newroute);
			if (ok) {
				oldroute->Remove(thisptr());
				newroute->Add(thisptr());
			}
			DEBUGLOG(smartptr,_T("oldroute: %p, newroute: %p"),
				 oldroute.get(),newroute.get());
		}

		/// Detatch a given route
		void Detatch(Route & route) {
			DEBUGLOG(smartptr,_T("Route; %p"),route.get());
			route -> Detatch(DevicePtr(thisptr()));
			DEBUGLOG(smartptr,_T("Route; %p"),route.get());
		}

	
//		Route GetRoute(int nr);   // counting starts with 0
		size_t nRoutes() { return routes.size(); };
		routeListType & GetRoutes() {
			return routes;
		}


		static const listtype & GetDeviceList() { 
			return deviceList ; 
		}

		/// Initialize the internal device identifiers.
		/** This function sets the internal device ids of 
		 *  all output devices, starting from 0 and 
		 *  incrementing by 1
		 */
		static void InitializeIds();
	
		/// Scan the list of input devices for a given id.
		/** \argument id (int) id to scan for
		 *  \return (OutputDevice) pointer to the input device with the given id if found, NULL else.
		 */
		static DevicePtr GetDevice(int id);

		operator const thistype & () const {
			return *(static_cast <const thistype *>(this));
		}

		operator thistype & () {
			return *(static_cast <thistype *>(this));
		}

		thistype * thisptr () {
			return static_cast<thistype *>(this);
		}

		const thistype * thisptr () const {
			return static_cast<const thistype *>(this);
		}

		static void ClearDeviceList() {
			while (!deviceList.empty()) {
#ifdef DEBUG
				DevicePtr d = deviceList.front();
#endif
				deviceList.front()->Destroy();
#ifdef DEBUG
				wxASSERT(deviceList.empty() || 
					 d != deviceList.front());
#endif
			}
		}
#ifdef WX
		virtual wxString TowxString() const;
#endif
	protected:
		static void AppendToDeviceList (DevicePtr dev);
		static void RemoveFromDeviceList (DevicePtr  dev);
		static typename listtype::iterator FindInDeviceList (DevicePtr dev) {
			typename listtype::iterator i = 
				std::find(deviceList.begin(),
					  deviceList.end(),
					  dev);
			return i;
		}
		static bool IsInDeviceList (const DevicePtr dev) {
			return FindInDeviceList(dev) != deviceList.end();
		}
		static void TruncateDeviceList (DevicePtr dev);

	};

	template<class T, class P, class L> 
	typename CommonTypedDeviceAPI<T,P,L>::listtype 
	CommonTypedDeviceAPI<T,P,L>::deviceList;

// Output devices ---------------------------------------------------
	class DeviceFactory;
	class OutputDeviceCLass;
	typedef CommonTypedDeviceAPI<OutputDeviceClass>::DevicePtr OutputDevice;
	typedef CommonTypedDeviceAPI<OutputDeviceClass>::listtype OutputDeviceList;
	class OutputDeviceClass: public CommonTypedDeviceAPI<OutputDeviceClass>
	{
		friend class DeviceFactory;
	protected:
		// private members: access only via access functions for debugging purposes
		/*
		  OutputDeviceNext;
		  static OutputDevice deviceList;
		*/
		OutputDeviceClass():CommonTypedDeviceAPI<OutputDeviceClass>()
			{
			}

		OutputDeviceClass(int devId, 
				  const mutStringRef name, 
				  int id = -1):
			CommonTypedDeviceAPI<OutputDeviceClass>(devId, name, id)
			{
			}

	public:
		virtual ~OutputDeviceClass() {}
		virtual void NoteOn(int box, int taste, int velo, 
				    RouteClass * r,
				    int channel, ChannelData *cd) = 0;
		virtual void NoteOff(int box, int taste, int velo, 
				     RouteClass * r,
				     int channel) = 0;
		virtual void NotesCorrect(int box) = 0;
		virtual void Sustain(char on, int channel) = 0;
		virtual int  GetChannel(int taste) = 0;
		virtual void Gis(GisToken *token, char turn) = 0;
		virtual void AddTime(frac time) = 0;
		virtual void MidiOut(DWORD data, char n) = 0;
		virtual void MidiOut(BYTE *p, char n) = 0;
		virtual void Quite(RouteClass * r) = 0;
		virtual void Panic() {};

		virtual bool NeedsRealTime() {
			return false;
		}

		virtual DevType GetType() const	{
			return DTUnknown;
		}

		virtual mutString GetTypeName () const {
			return N_("Undefined output device");
		}
#ifdef WX
		virtual wxString TowxString() const;
#endif
	

	
	};



// Input devices -------------------------------------------------
	class InputDeviceClass;
	typedef CommonTypedDeviceAPI<InputDeviceClass>::DevicePtr InputDevice;
	typedef CommonTypedDeviceAPI<InputDeviceClass>::listtype InputDeviceList;
	class InputDeviceClass: public CommonTypedDeviceAPI<InputDeviceClass>
	{
		friend class DeviceFactory;
	protected:
		// private members: access only via access functions for debugging purposes
		/*
		  InDevice *Next;
		  static InDevice * deviceList;
		  Route Routes;
		*/
		//InputDevice Next;

		enum MutaborModeType Mode;

		InputDeviceClass():CommonTypedDeviceAPI<InputDeviceClass>(), 
//			   Next(this,_T("Next")), 
			   Mode(DeviceStop)
			{
			}
	
		InputDeviceClass(int devId, 
				 const mutStringRef name = mutEmptyString, 
				 mutabor::MutaborModeType mode = DeviceStop, 
				 int id = -1):
			CommonTypedDeviceAPI<InputDeviceClass>(devId, name, id), 
//			Next(this,_T("Next")), 
			Mode(mode)
			{
			}

	public:
		virtual ~InputDeviceClass() {}
	
		/// Remove from the input device list to be deleted, when it becomes free.
		/**
		 * As we are using smart pointers the Route gets deleted, when no pointers
		 * point to it any more. As we want to interactively manage routes,
		 * We must allow routes to have no input device attached to it. This
		 * function explicitely allows to delete the object when it is not used 
		 * any more.
		 */
		virtual void Destroy();

		virtual void Close() { 
			Stop();
		}
		virtual void Stop() { 
			Mode = DeviceStop;
		}
		virtual void Play() {
			Mode = DevicePlay;
		}
		virtual void Pause() {
			Mode = DevicePause;
		}
		//	  virtual frac ReadOn(frac time) = 0;

		void Quite(); // all Routes quite
		virtual bool NeedsRealTime()
			{
				return false;
			}

		/// Increase the time in batch conversion
		virtual void IncDelta() {}

		virtual DevType GetType() const
			{
				return DTUnknown;
			}
	
		void SetMode(MutaborModeType m) { Mode = m; }

		MutaborModeType GetMode()
			{
				return Mode;
			}
	

#if 0	
		InputDevice GetNext() const {
			wxASSERT(Next != this);
			return Next; 
		}
	
		void SetNext(InputDevice n) 
			{
				wxASSERT(n != this);
				Next = n;
			}
#endif
		virtual mutString GetTypeName () const {
			return N_("Undefined input device");
		}

#ifdef WX
		virtual wxString TowxString() const; 
#endif
	};


	class DeviceFactory { 
	public:
		DeviceFactory(size_t id = 0);
		virtual ~DeviceFactory();

		static OutputDevice CreateOutput (int type) {
			wxASSERT(type >= 0);
			if (factories.size() <= (size_t)type) {
				UNREACHABLECT(DeviceFactory);
				return NULL;
			}
			return factories[type]->DoCreateOutput();
		}
		static OutputDevice CreateOutput (int type, 
						  int devId,
						  const mutStringRef name, 
						  int id = -1) {
			wxASSERT(type >= 0);
			if (factories.size() <=(size_t) type) {
				UNREACHABLECT(DeviceFactory);
				return NULL;
			}
			return factories[type]->DoCreateOutput(devId,name,id);
		}
		static OutputDevice CreateOutput(int type,
						 int devId, 
						 const mutStringRef name, 
						 MutaborModeType mode, 
						 int id = -1) {
			wxASSERT(type >= 0);
			if (factories.size() <= (size_t)type) {
				UNREACHABLECT(DeviceFactory);
				return NULL;
			}
			return factories[type]->DoCreateOutput(devId, name, mode, id);
		}

		static InputDevice CreateInput (int type) {
			wxASSERT(type >= 0);
			if (factories.size() <= (size_t)type) {
				UNREACHABLECT(DeviceFactory);
				return NULL;
			}
			return factories[type]->DoCreateInput();
		}
		static InputDevice CreateInput (int type, 
						int devId,
						const mutStringRef name, 
						int id = -1) {
			wxASSERT(type >= 0);
			if (factories.size() <= (size_t)type) {
				UNREACHABLECT(DeviceFactory);
				return NULL;
			}
			return factories[type]->DoCreateInput(devId,name,id);
		}
		static InputDevice CreateInput(int type,
					       int devId, 
					       const mutStringRef name, 
					       MutaborModeType mode, 
					       int id = -1) {
			wxASSERT(type >= 0);
			if (factories.size() <= (size_t)type) {
				UNREACHABLECT(DeviceFactory);
				return NULL;
			}
			return factories[type]->DoCreateInput(devId,name, mode, id);
		}

		static void Destroy() {
			if (!factories.empty()) {
				for (factorylist::iterator i = factories.begin();
				     i != factories.end(); i++) {
				        DeviceFactory * factory = *i;
					if (factory)
						delete factory;
				}
				factories.clear();
			} else 
				UNREACHABLECT(DeviceFactory);
		}


		/// load the routes from a tree based configuration
		/** \param config conifiguration to be read from
		 */
		static void LoadOutputDevices(tree_storage & config);

		/// write the routes to the configuration
		/** \param config configuration to be written to
		 */ 
		static void SaveOutputDevices(tree_storage & config);

		/// load the routes from a tree based configuration
		/** \param config conifiguration to be read from
		 */
		static void LoadInputDevices(tree_storage & config);

		/// write the routes to the configuration
		/** \param config configuration to be written to
		 */ 
		static void SaveInputDevices(tree_storage & config);

	protected:
		typedef std::vector<DeviceFactory *> factorylist;
		static factorylist factories;
	
		virtual size_t GetType() const = 0;

		virtual OutputDevice DoCreateOutput() const = 0;
		
		virtual InputDevice DoCreateInput() const = 0;
		virtual OutputDevice DoCreateOutput(int devId,
						    const mutStringRef name, 
						    int id = -1) const = 0;
		
		virtual InputDevice DoCreateInput(int devId,
						  const mutStringRef name, 
						  int id = -1) const = 0;

		virtual OutputDevice DoCreateOutput(int devId,
						    const mutStringRef name, 
						    MutaborModeType mode, 
						    int id = -1) const = 0;
		
		virtual InputDevice DoCreateInput(int devId,
						  const mutStringRef name, 
						  MutaborModeType mode, 
						  int id = -1) const = 0;
	
		/// load the routes from a tree based configuration
		/** \param config conifiguration to be read from
		 */
		virtual void DoLoadOutputDevices(tree_storage & config) const;

		/// write the routes to the configuration
		/** \param config configuration to be written to
		 */ 
		virtual void DoSaveOutputDevices(tree_storage & config) const;
	

		/// load the routes from a tree based configuration
		/** \param config conifiguration to be read from
		 */
		virtual void DoLoadInputDevices(tree_storage & config) const;

		/// write the routes to the configuration
		/** \param config configuration to be written to
		 */ 
		virtual void DoSaveInputDevices(tree_storage & config) const;
	
	};



	class CurrentTimer: public wxStopWatch
	{
	public:
		CurrentTimer(long t = 0):wxStopWatch()
			{
				Start(t);
			}
	
		virtual ~CurrentTimer() {}

		void Set(long t = 0)
			{
				Start(t);
			}

		CurrentTimer& operator = (long t)
			{
				Start(t);
				return * this;
			}

		virtual void  Notify() 
			{
				STUBC;
			}

		operator unsigned int ()
			{
				return (unsigned int) Time();
			}
	
		operator long ()
			{
				return Time();
			}
	};

	extern CurrentTimer CurrentTime;

	void StartCurrentTime();

	void StopCurrentTime();

// functions --------------------------------------------------------



	void OutNotesCorrect(int box);

	bool OutOpen();

	void OutClose();

	void OutAddTime(frac time);

	bool InOpen();

	void InClose();

	bool NeedsRealTime();

//frac InReadOn(frac time);

	void MidiOut(int box, DWORD data, char n = -1);

	void NotesCorrect(int box);

	int GetChannel(int box, int taste);


}

#endif /* precompiled */
#endif

/*
 * \}
 */
