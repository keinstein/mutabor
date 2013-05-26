// -*- C++ -*-

/** \file
 ********************************************************************
 * Routing. Mutoabor Core.
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/src/kernel/routing/Device.h,v 1.11 2011/11/02 14:31:57 keinstein Exp $
 * \author Rüdiger Krauße <krausze@mail.berlios.de>,
 * Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 1998
 * $Date: 2011/11/02 14:31:57 $
 * \version $Revision: 1.11 $
 * \license GPL
 *
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

#include "src/kernel/Defs.h"
#include "src/kernel/routing/gmn/GIS.h"
#include "src/kernel/routing/Route.h"
#include "src/kernel/routing/timing.h"
#include "src/kernel/MidiKern.h"

#ifndef MU32_ROUTING_DEVICE_H_PRECOMPILED
#define MU32_ROUTING_DEVICE_H_PRECOMPILED

// system headers which do seldom change

#include <vector>
#include <list>
#include <algorithm>
#include <sstream>
#include "wx/thread.h"
#include "wx/stopwatch.h"
#include <boost/unordered_set.hpp>

#define DRUMCHANNEL 9  // Schlagzeugkanal bei General Midi (Kanal 9, bzw. 10)

namespace mutaborGUI {
	class GUIOutputDeviceBase;
	class GUIInputDeviceBase;
}

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
		typedef std::vector<int8_t> controller_vector;

		ChannelData(int sound = -1, int8_t sustain = 0):controller(128,-1),
								controller_changed(128,-1),
								first_unchanged(0),
								looped(false),
								Sound(sound),
								bank_coarse(-1),
								bank_fine(-1),
								bend(0)
			{
				controller[midi::HOLD_PEDAL_ON_OFF] = sustain;
				if (sustain != 0) {
					controller_changed[first_unchanged] 
						= midi::HOLD_PEDAL_ON_OFF;
					first_unchanged++;
				}
			}

		void Reset()
			{
				for (controller_vector::iterator i = controller.begin();
				     i != controller.end();
				     i++) *i = -1;
				for (controller_vector::iterator i = controller_changed.begin();
				     i != controller_changed.end();
				     i++) *i = -1;
				first_unchanged = 0;
				looped = false;
				Sound = -1;
				bank_coarse = -1;
				bank_fine = -1;
				bend = 0;
				
				
			}

		int8_t set_controller(int8_t number, int8_t data) {
			int8_t retval = controller[number];
			DEBUGLOG(midiio,_T("ctrl: %d, %d => %d"),(int)number,(int)retval,(int)data);

			controller[number] = data;
			bool found = false;
			size_t index;
			for (int i = 0; i < (looped?controller.size():first_unchanged);i++) {
				if (controller_changed[i] == number) {
					controller_vector :: iterator beg = controller_changed.begin();
					std::rotate(beg + i,beg+i+1 ,beg +first_unchanged);
					found = true;
					index = i;
					break;
				}
			}
			if (!found) 
				index = first_unchanged++;

			controller_changed[index] = number;

			return retval;
		}

		int8_t get_controller(int8_t number) const {
			return controller[number];
		}

		controller_vector::const_iterator get_first_changed_controller(const ChannelData & other) const {
			controller_vector::const_iterator retval = controller_changed.begin();
			if (*retval == -1 || controller[*retval]==other.controller[*retval])
				return retval;
			return get_next_changed_controller(other,retval);
		}
		controller_vector::const_iterator get_next_changed_controller(const ChannelData & other, controller_vector::const_iterator last) const {
			mutASSERT(controller_changed.begin() <= last);
			mutASSERT(last < controller_changed.end());
			controller_vector::const_iterator retval = last;
			do {
				retval++;
			} while (retval != controller_changed.end() && (*retval != -1) && controller[*retval] == other.controller[*retval]);
			return retval;
		}

		bool is_changed_controller(controller_vector::const_iterator actual) const {
			mutASSERT(controller_changed.begin() <= actual);
			mutASSERT(actual<= controller_changed.end());
			if (actual == controller_changed.end()) return false;
			if (*actual == -1) return false;
			mutASSERT(0<= *actual);
			mutASSERT(*actual < controller.size());
			return true;
		}

		void program_change(int program) {
			Sound = program;
			int8_t data = controller[midi::BANK_COARSE];
			if (data != -1) bank_coarse = data;
			data = controller[midi::BANK_FINE];
			if (data != -1) bank_fine = data;
		}

		void program_change(const ChannelData & o) {
			Sound = o.Sound;
			bank_coarse = o.bank_coarse;
			bank_fine = o.bank_fine;
		}
 
		bool is_compatible (const ChannelData &cd) const {
			/* \todo check that ignoring pitch bend is ok */
			if (Sound != -1 && cd.Sound != -1 
			    && Sound != cd.Sound) return false;
			if (controller.size() 
			    != cd.controller.size()) return false;
				
			/* \todo optimization */
			for (size_t i = 0 ; i < controller.size() ; i++) {
				if (controller[i] != -1 
				    && cd.controller[i] != -1 
				    && controller[i] != cd.controller[i]) return false;
			}
			return true;
		}

		int get_bend() { return bend; }
		int set_bend(int b) { bend = b; }

		int get_program() const {return Sound; }
		int get_bank_coarse() const { return bank_coarse; }
		int get_bank_fine() const { return bank_fine; }
	protected:
		controller_vector controller;
		controller_vector controller_changed;
		size_t first_unchanged;
		bool looped;
		int Sound;                // -1 = noch nicht verwendet
		uint8_t bank_coarse;      // MSB as saved during last program change
		uint8_t bank_fine;        // LSB as saved during last program change
		int bend;                 // 0 = ungepitcht, kann durchaus auch negativ sein
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
		virtual ~Device() { TRACEC; }
	
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
		virtual void Add(Route & route) = 0;
		/// replace a route
		virtual bool Replace(Route & oldRoute, Route & newRoute) = 0;
                /// remove a route
		virtual bool Remove(Route & route) = 0;

		/// reset the device if requested
		virtual void Panic() = 0;

	protected: /** \todo lift this restrection afer GUI is working again */
		friend class ::mutaborGUI::GUIOutputDeviceBase;
		friend class ::mutaborGUI::GUIInputDeviceBase;
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

#if defined(_MSC_VER)
#pragma warning(push) // Save warning settings.
#pragma warning(disable : 4100) // Disable unreferenced formal parameter warnings
#endif
		virtual void ReadData(wxConfigBase * config) {};
		virtual void WriteData(wxConfigBase * config) {};	
#if defined(_MSC_VER)
#pragma warning(pop) // Restore warnings to previous state.
#endif 
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

		virtual void Destroy();

		/// add a route
		virtual void Add(Route & route);
		/// replace a route
		virtual bool Replace(Route & oldroute, 
				     Route & newroute);
                /// remove a route
		virtual bool Remove(Route & route);
		/// Move routes to another device 
		virtual bool MoveRoutes (DevicePtr & newclass);
	
//		Route GetRoute(int nr);   // counting starts with 0
		size_t nRoutes() { return routes.size(); };

		const routeListType & GetRoutes() const {
			return routes;
		}

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
				mutASSERT(deviceList.empty() || 
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
		virtual ~OutputDeviceClass() { 
			TRACEC;
			wxASSERT(!IsOpen());
			TRACEC;
		}
		virtual void Destroy() {
			TRACEC;
			CommonTypedDeviceAPI<OutputDeviceClass>::Destroy();
			TRACEC;
		}
		virtual void NoteOn(mutabor_box_type * box, 
				    int taste, 
				    int velo, 
				    RouteClass * r,
				    size_t id, 
				    const ChannelData & input_channel_data) = 0;
		virtual void NoteOff(mutabor_box_type * box, 
				     int taste, 
				     int velo, 
				     RouteClass * r,
				     size_t id,
				     bool is_note_on) = 0;
		virtual void NotesCorrect(RouteClass * route) = 0;
		virtual void Controller(int mutabor_channel, int controller, int value) = 0;
//		virtual void Sustain(int channel, const ChannelData & cd) = 0;
		virtual int  GetChannel(int inkey, int channel, int id) = 0;
		virtual void Gis(GisToken *token, char turn) = 0;
		virtual void AddTime(frac time) = 0;
		virtual void MidiOut(BYTE *p, size_t n) = 0;
		virtual void Quiet(RouteClass * r) = 0;
		virtual void Panic() { STUBC; };
		virtual bool Open() { return true; }

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
		struct current_keys_type {
			struct entry {
				int key;
				int unique_id;
				int velocity;
				Route route;
				entry(int k, int u, int v, Route &R): key(k),
								      unique_id(u),
								      velocity(v),
								      route (R) {}

				bool operator == (const entry & e) const {
					return e.key == key && e.unique_id == unique_id && e.route == route;
				}
			};

			struct hash_type {
				uint8_t operator () (const entry & val) const {
					size_t seed = 0;
					boost::hash_combine(seed, val.key);
					boost::hash_combine(seed, val.unique_id);
					boost::hash_combine(seed, val.route.get());
					return seed & 0xFF;
				}
			};
			
			typedef boost::unordered_multiset<entry, hash_type> map_type;
			typedef map_type::iterator iterator;
			typedef map_type::const_iterator const_iterator;

			void add (int key,
				  int velocity,
				  int unique_id, 
				  Route & R) {
				map.insert(entry(key,unique_id,velocity, R));
			}

			void remove(int key,
				    int velocity,
				    int unique_id, 
				    Route & R) {
				std::pair<map_type::iterator, map_type::iterator> range = map.equal_range(entry(key,unique_id,velocity, R));
				if (range.first != map.end()) {
					map.erase(range.first);
				}
			}

			void remove (iterator i ) {
				map.erase(i);
			}

			iterator begin() { return map.begin(); }
			const_iterator begin() const { return map.begin(); }

			iterator end() { return map.end(); }
			const_iterator end() const { return map.end(); } 
		protected:
			map_type map;
		};

		virtual ~InputDeviceClass() { TRACEC; }
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

                /** Command the device to play music. 
		 * This function starts playing the music of the device at the curren position.
		 * 
		 * \param tk Kind of thread to be created. It can be
		 * wxTHREAD_DETACHED or wxTHREAD_JOINABLE. This parameter is used only on devices
		 * that start a new thread for playing the music. Otherwise it is ignored.
		 */
		virtual void Play(wxThreadKind tk = wxTHREAD_DETACHED) {
			if (Mode == DeviceStop || Mode == DevicePause)
				Mode = DevicePlay;
		}

                /** Play all input devices in batch mode
		 * The batch mode allows for direct conversion of data in a complex route environment.
		 * In contrast to the normal Play() function this function doesn't use timers, but simulates
		 * timing.
		 */
		static bool BatchPlay();

                /** Play all input devices in realtime mode
		 * The the realtime mode allows interactive playing together with the integrated sequencer.
		 */
		static void RealtimePlay();

#if (!wxCHECK_VERSION(2,9,2))
		enum wxThreadWait {
			wxTHREAD_WAIT_BLOCK,
			wxTHREAD_WAIT_YIELD,
			wxTHREAD_WAIT_DEFAULT
		};
#endif

                /** Wait for the thread started with Play().
		 * This
		 * function can be used to wait for the device to
		 * finish playing. It can be used for joinable
		 * threads, only. For detached threads its behaviour
		 * is undefined.
		 * 
		 * \param flags Indicators how to wait see wxThread::Wait for more detail.
		 * 
		 * \return exit code from the thread after it has ended. Non-threaded devices will return NULL.
		 */
		virtual wxThread::ExitCode WaitForDeviceFinish(wxThreadWait flags=wxTHREAD_WAIT_BLOCK) { return NULL; }

		virtual void Pause() {
			Mode = DevicePause;
		}
		//	  virtual frac ReadOn(frac time) = 0;

		
		virtual bool NeedsRealTime() {
			return false;
		}


		/** 
		 * Go on to the next event. 
		 *
		 * This function must be provided by the device. It is
		 * asked to prepare the next event and return the time
		 * to wait in microseconds from the start of the
		 * piece. Though the timer has only milliseconds
		 * resolution, the errors will sum up so that we need
		 * a much higher resolution, here.
		 *
		 * Here, we use the measure that is used in the SMF
		 * standard. It has been designed to reduce the
		 * deviation of a 4 minutes piece at 120 bpm to
		 * 500μs. If it were 500ms it would be unusable.
		 * 
		 * \return uint_fast64_t Absolute temporal position of the next event in the
		 * piece in μs.
		 */
		virtual mutint64 PrepareNextEvent() {}

		void NoteOn(Route &R, int key, int velocity,
			    size_t make_unique,
			    const ChannelData & input_channel_data,
			    void * userdata) {
			current_keys.add(key, make_unique, velocity, R);
			if (R) {
				R->NoteOn(key,velocity,make_unique, input_channel_data, userdata);
			}
		}

		void NoteOff(Route & R,
			     int key,
			     int velocity,
			     size_t make_unique) {
			current_keys.remove(key, make_unique, velocity, R);
			if (R) {
				R->NoteOff(key,velocity,make_unique);
			}
		}


		void Panic() { Panic(true); } // is virtual in Device
		void Panic(bool global);
			

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
			mutASSERT(Next != this);
			return Next; 
		}
	
		void SetNext(InputDevice n) 
			{
				mutASSERT(n != this);
				Next = n;
			}
#endif
		virtual mutString GetTypeName () const {
			return N_("Undefined input device");
		}

		static mutint64 GetNO_DELTA() {
			return mutint64(std::numeric_limits<mutint64>::max());
		}

		bool IsDelta(mutint64 d) {
			return d != GetNO_DELTA();
		}

#ifdef WX
		virtual wxString TowxString() const; 
#endif

	protected:
		enum MutaborModeType Mode;
		current_keys_type current_keys;
	};


	class DeviceFactory { 
	public:
		struct DeviceNotCreated:public std::exception {};
		struct FactoryNotFound:public std::exception {
			int id;
			std::string message_;
			FactoryNotFound(int i):std::exception(), id(i) {
				std::ostringstream writer(message_);
				writer << "Factory for device type " << i << " has not been registered.";
				message_ = writer.str();
			}

			virtual ~FactoryNotFound() throw () {}

			//! Returns the thrown error message as a c-style string.
			virtual const char* what( void ) const throw() { return message_.c_str(); }
			
		};
		DeviceFactory(size_t id = 0);
		virtual ~DeviceFactory();

		static OutputDevice  CreateOutput (int type) {
			mutASSERT(type >= 0);
			if (factories.size() <= (size_t)type) {
				throw FactoryNotFound(type);
				UNREACHABLECT(DeviceFactory);
				return NULL;
			}
			if (!factories[type]) 
				throw FactoryNotFound(type);

			return factories[type]->DoCreateOutput();
		}
		static OutputDevice CreateOutput (int type, 
						  int devId,
						  const mutStringRef name, 
						  int id = -1) {
			mutASSERT(type >= 0);
			if (factories.size() <=(size_t) type) {
				throw FactoryNotFound(type);
				UNREACHABLECT(DeviceFactory);
				return NULL;
			}
			if (!factories[type]) 
				throw FactoryNotFound(type);
			return factories[type]->DoCreateOutput(devId,name,id);
		}
		static OutputDevice CreateOutput(int type,
						 int devId, 
						 const mutStringRef name, 
						 MutaborModeType mode, 
						 int id = -1) {
			mutASSERT(type >= 0);
			if (factories.size() <= (size_t)type) {
				throw FactoryNotFound(type);
				UNREACHABLECT(DeviceFactory);
				return NULL;
			}
			if (!factories[type]) 
				throw FactoryNotFound(type);
			return factories[type]->DoCreateOutput(devId, name, mode, id);
		}

		static InputDevice CreateInput (int type) {
			mutASSERT(type >= 0);
			if (factories.size() <= (size_t)type) {
				throw FactoryNotFound(type);
				UNREACHABLECT(DeviceFactory);
				return NULL;
			}
			
			if (!factories[type]) 
				throw FactoryNotFound(type);
			return factories[type]->DoCreateInput();
		}
		static InputDevice CreateInput (int type, 
						int devId,
						const mutStringRef name, 
						int id = -1) {
			mutASSERT(type >= 0);
			if (factories.size() <= (size_t)type) {
				throw FactoryNotFound(type);
				UNREACHABLECT(DeviceFactory);
				return NULL;
			}
			if (!factories[type]) 
				throw FactoryNotFound(type);
			return factories[type]->DoCreateInput(devId,name,id);
		}
		static InputDevice CreateInput(int type,
					       int devId, 
					       const mutStringRef name, 
					       MutaborModeType mode, 
					       int id = -1) {
			mutASSERT(type >= 0);
			if (factories.size() <= (size_t)type) {
				throw FactoryNotFound(type);
				UNREACHABLECT(DeviceFactory);
				return NULL;
			}
			if (!factories[type]) 
				throw FactoryNotFound(type);
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

		virtual OutputDeviceClass * DoCreateOutput() const = 0;
		
		virtual InputDeviceClass * DoCreateInput() const = 0;
		virtual OutputDeviceClass * DoCreateOutput(int devId,
						    const mutStringRef name, 
						    int id = -1) const = 0;
		
		virtual InputDeviceClass * DoCreateInput(int devId,
						  const mutStringRef name, 
						  int id = -1) const = 0;

		virtual OutputDeviceClass * DoCreateOutput(int devId,
						    const mutStringRef name, 
						    MutaborModeType mode, 
						    int id = -1) const = 0;
		
		virtual InputDeviceClass * DoCreateInput(int devId,
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

	void InitDeviceFactories();



// functions --------------------------------------------------------



//	void OutNotesCorrect(mutabor_box_type *  box);

	bool OutOpen();

	void OutClose();

	void OutAddTime(frac time);

	bool InOpen();

	void InClose();

	bool NeedsRealTime();

//frac InReadOn(frac time);

	
	void MidiOut(mutabor_box_type * box, struct midiliste * outliste);

	void NotesCorrect(mutabor_box_type *  box);

	int GetChannel(int box, int taste, int channel, int id);


}

#endif /* precompiled */
#endif

/*
 * \}
 */
