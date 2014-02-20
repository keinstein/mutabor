// -*- C++ -*-

/** \file
 ********************************************************************
 * Routing. Mutoabor Core.
 *
 * \author Rüdiger Krauße <krausze@mail.berlios.de>,
 * Tobias Schlemmer <keinstein@users.berlios.de>
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
#include <limits.h>
#include <algorithm>
#include <sstream>
#include <stdarg.h>
#include "wx/thread.h"
#include "wx/stopwatch.h"
#include <boost/unordered_set.hpp>

#define DRUMCHANNEL 9  // Schlagzeugkanal bei General Midi (Kanal 9, bzw. 10)

namespace mutaborGUI {
	class GUIOutputDeviceBase;
	class GUIInputDeviceBase;
}

namespace mutabor {
	typedef std::vector<uint8_t> midi_string;

	enum MutaborModeType {
		DeviceUnregistered = -1, //< Unregistered device – currently unused
		DeviceInitializing,      //< Intitialization phase (e.g. thread creation)
		DeviceStop,              //< Device is OK, but no playback.
		DevicePlay,              //< Playback is running
		DevicePause,             //< Playback is paused
		DeviceCompileError,      //< Error while compiling/decoding the file (file propably corrupted)
		DeviceTimingError,       //< Timing problems e.g. backwards runnig time in a file. May be reset after Stop()
		DeviceKilled             //< A problem that makes the device (probably) unusable.
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
		typedef std::vector<int> controller_vector;
		static const size_t IGNORE_UNIQUE_ID = ULONG_MAX;

		ChannelData(int sound = -1/*,
					    int8_t sustain = 0*/):controller(128,-1),
						controller_changed(256,-1),
						first_unchanged(0),
						looped(false),
						data_is_rpn(true),
						Sound(sound),
						bank_coarse(-1),
						bank_fine(-1),
						bend(0)
		{
			/*
			controller[midi::HOLD_PEDAL_ON_OFF] = sustain;
			if (sustain != 0) {
				controller_changed[first_unchanged]
					= midi::HOLD_PEDAL_ON_OFF;
				first_unchanged++;
			}
			*/
		}

		void Reset()
		{
			for (controller_vector::iterator i = controller.begin();
			     i != controller.end();
			     ++i) *i = -1;
			for (controller_vector::iterator i = controller_changed.begin();
			     i != controller_changed.end();
			     ++i) *i = -1;
			first_unchanged = 0;
			looped = false;
			Sound = -1;
			bank_coarse = -1;
			bank_fine = -1;
			bend = 0;
		}

		/**
		 * Reset the controllers according to the MIDI
		 * standard.
		 *
		 * This function resets the Midi Controllers according
		 * to RP15 from the MMA.
		 *
		 * \sa http://www.midi.org/techspecs/rp15.php
		 *
		 */
		void MidiReset();

		int set_controller(size_t number, int data) {

			if (controller.size() <= number)
				controller.resize(number +1,-1);
			int retval = controller[number];
			int param = -1;
			DEBUGLOG(midiio,_T("ctrl: %d, %d => %d"),(int)number,(int)retval,(int)data);
			controller[number] = data;

			// we allow to set a controller to an udefined state.
			if (data < 0) return retval;

			switch (number) {
			case midi::NON_REGISTERED_PARAMETER_FINE:
			case midi::NON_REGISTERED_PARAMETER_COARSE:
				data_is_rpn = false;
				break;
			case midi::REGISTERED_PARAMETER_FINE:
			case midi::REGISTERED_PARAMETER_COARSE:
				data_is_rpn = true;
				break;
			case midi::DATA_ENTRY_COARSE:
			case midi::DATA_ENTRY_FINE:
			case midi::DATA_BUTTON_INCREMENT:
			case midi::DATA_BUTTON_DECREMENT:
				if (!data_is_rpn
				    && controller[midi::NON_REGISTERED_PARAMETER_FINE] != -1
				    && controller[midi::NON_REGISTERED_PARAMETER_COARSE] != -1
				    && controller[midi::NON_REGISTERED_PARAMETER_FINE] != 0x7f
				    && controller[midi::NON_REGISTERED_PARAMETER_COARSE] != 0x7f) {
					param = midi::FIRST_NRPN
						| controller[midi::NON_REGISTERED_PARAMETER_COARSE] << 8
						| controller[midi::NON_REGISTERED_PARAMETER_FINE];
				} else if (data_is_rpn
					   && controller[midi::REGISTERED_PARAMETER_FINE] != -1
					   && controller[midi::REGISTERED_PARAMETER_COARSE] != -1
					   && controller[midi::REGISTERED_PARAMETER_FINE] != 0x7f
					   && controller[midi::REGISTERED_PARAMETER_COARSE] != 0x7f) {
					param = midi::FIRST_RPN
						| controller[midi::REGISTERED_PARAMETER_COARSE] << 8
						| controller[midi::REGISTERED_PARAMETER_FINE];
				}
				if (param != -1) {
					if (controller.size() <= (size_t) param)
						controller.resize(param+1,-1);
					switch (number) {
					case midi::DATA_BUTTON_INCREMENT:
						if (!(controller[param]&0x80)) {
							// skip the sign bit for lsb
							int value = controller[param];
							value++;
							if (value & 0x80) {
								if (!(value & 0x8000))
									value += 0x100;
								value &= ~((int)0xff);
							}
							controller[param] = value;
						}
						break;
					case midi::DATA_BUTTON_DECREMENT:
						if (!(controller[param]&0x80)) {
							int value = controller[param];
							bool hasmsb = !(value & 0x8000);
							value--;
							if (value & 0x80) {
								if (!hasmsb) {
									value |= 0xFF00;
								}
								value &= ~((int)0x80);
							}
						}
						break;
					case midi::DATA_ENTRY_COARSE: {
						int value = (controller[param] & 0xFF) | ((data & 0xFF) << 8);
						if (controller[param] != value)
							set_controller(param,value);
					}
						break;
					case midi::DATA_ENTRY_FINE: {
						int value = (controller[param] & 0xff00)| (data & 0xff);
						if (controller[param] != value)
							set_controller(param,value);
					}
						break;
					}
				}
				break;
			}



			bool found = false;
			size_t index;
			for (size_t i = 0; i < (looped?controller.size():first_unchanged);i++) {
				if (controller_changed[i] == (int)number) {
					controller_vector :: iterator beg = controller_changed.begin();
					std::rotate(beg + i,beg+i+1 ,beg +first_unchanged);
					found = true;
					index = first_unchanged-1;
					break;
				}
			}
			if (!found)
				index = first_unchanged++;

			controller_changed[index] = number;

			return retval;
		}

		int get_index(int message) {

			switch (message) {
			case midi::PITCH_BEND_SENSITIVITY:
				return -1;
#if 0
				// Don't send the parameter at this
				// moment.  the parameter should be
				// sent when data is stored in the corresponding
				// RPN/NRPN parameter
				// nevertheess we may preprogramm the register
				// address for later use, so return not -1
			case midi::NON_REGISTERED_PARAMETER_FINE:
			case midi::NON_REGISTERED_PARAMETER_COARSE:
				if (controller[midi::NON_REGISTERED_PARAMETER_FINE] != -1
				    && controller[midi::NON_REGISTERED_PARAMETER_COARSE] != -1
				    && controller[midi::NON_REGISTERED_PARAMETER_FINE] != 0x7f
				    && controller[midi::NON_REGISTERED_PARAMETER_COARSE] != 0x7f) {
					return 0x20000
						| controller[midi::NON_REGISTERED_PARAMETER_COARSE] << 8
						| controller[midi::NON_REGISTERED_PARAMETER_FINE];
				}
				return -1;
			case midi::REGISTERED_PARAMETER_FINE:
			case midi::REGISTERED_PARAMETER_COARSE:
				if (controller[midi::REGISTERED_PARAMETER_FINE] != -1
				    && controller[midi::REGISTERED_PARAMETER_COARSE] != -1
				    && controller[midi::REGISTERED_PARAMETER_FINE] != 0x7f
				    && controller[midi::REGISTERED_PARAMETER_COARSE] != 0x7f)
					return get_index(0x10000
							 | controller[midi::REGISTERED_PARAMETER_COARSE] << 8
							 | controller[midi::REGISTERED_PARAMETER_FINE]);
				return -1;
#endif
			case midi::DATA_ENTRY_COARSE:
			case midi::DATA_ENTRY_FINE:
			case midi::DATA_BUTTON_INCREMENT:
			case midi::DATA_BUTTON_DECREMENT:
				if (!data_is_rpn
				    && controller[midi::NON_REGISTERED_PARAMETER_FINE] != -1
				    && controller[midi::NON_REGISTERED_PARAMETER_COARSE] != -1
				    && controller[midi::NON_REGISTERED_PARAMETER_FINE] != 0x7f
				    && controller[midi::NON_REGISTERED_PARAMETER_COARSE] != 0x7f) {
					return 0x20000
						| controller[midi::NON_REGISTERED_PARAMETER_COARSE] << 8
						| controller[midi::NON_REGISTERED_PARAMETER_FINE];
				} else if (data_is_rpn
					   && controller[midi::REGISTERED_PARAMETER_FINE] != -1
					   && controller[midi::REGISTERED_PARAMETER_COARSE] != -1
					   && controller[midi::REGISTERED_PARAMETER_FINE] != 0x7f
					   && controller[midi::REGISTERED_PARAMETER_COARSE] != 0x7f) {
					return 0x10000
						| controller[midi::REGISTERED_PARAMETER_COARSE] << 8
						| controller[midi::REGISTERED_PARAMETER_FINE];
				}
				return -1;
			}
			return message;

		}

		int get_controller(size_t number) const {
			if (number >= controller.size()) return -1;
			return controller[number];
		}

		/**
		 * Check whether one of the hold switches is active
		 *
		 * \retval true if the channel is holding notes
		 * \retval false if the notes are expected to stop
		 * immediately
		 *
		 * \sa \ref midi::is_hold()
		 */
		bool get_hold() const {
			return (get_controller(midi::HOLD_PEDAL_ON_OFF) >= midi::CONTROLLER_MIN_ON
				|| get_controller(midi::SOSTENUTO_ON_OFF) >= midi::CONTROLLER_MIN_ON
				|| get_controller(midi::LEGATO_PEDAL_ON_OFF) >= midi::CONTROLLER_MIN_ON
				|| get_controller(midi::HOLD_2_PEDAL_ON_OFF) >= midi::CONTROLLER_MIN_ON);
		}


		/**
		 * Get the first changed controller.
		 *
		 *
		 * \return Iterator to the first changed controller.
		 *
		 * \todo Provide changed_controller iterator type
		 */
		controller_vector::const_iterator get_first_changed_controller() const {
			controller_vector::const_iterator retval = controller_changed.begin();
			if (retval == controller_changed.end())
				return retval;
			if (*retval != -1)
				return retval;
			return get_next_changed_controller(retval);
		}
		/**
		 * Get the first changed controller that differs from
		 * the corresponding controller in another channel.
		 *
		 * \param other The channel data we compare ourselves to.
		 *
		 * \return iterator to the first differently changed controller.
		 */
		controller_vector::const_iterator get_first_changed_controller(const ChannelData & other) const {
			controller_vector::const_iterator retval = controller_changed.begin();
			if (retval == controller_changed.end())
				return retval;
			if (*retval >= 0  && other.controller.size() <= (size_t)*retval)
				return retval;
			if (*retval != -1 && controller[*retval] != other.controller[*retval])
				return retval;
			return get_next_changed_controller(other,retval);
		}

		/**
		 * Get the first changed controller.
		 *
		 * \param last last position of the iterator.
		 *
		 * \return Iterator to the first changed controller.
		 *
		 * \todo Provide changed_controller iterator type
		 */
		controller_vector::const_iterator get_next_changed_controller(controller_vector::const_iterator last) const {
			mutASSERT(controller_changed.begin() <= last);
			mutASSERT(last < controller_changed.end());
			controller_vector::const_iterator retval = last;
			do {
				++retval;
				mutASSERT(retval == controller_changed.end()
					  || *retval == -1
					  || (size_t)(*retval) < controller.size());
			} while (retval != controller_changed.end()
				 && (*retval == -1));
			return retval;
		}

		/**
		 * Get the first changed controller that differs from
		 * the corresponding controller in another channel.
		 *
		 * \param other The channel data we compare ourselves to.
		 * \param last last position of the iterator.
		 *
		 * \return iterator to the first differently changed controller.
		 */
		controller_vector::const_iterator get_next_changed_controller(const ChannelData & other,
									      controller_vector::const_iterator last) const {
			mutASSERT(controller_changed.begin() <= last);
			mutASSERT(last < controller_changed.end());
			controller_vector::const_iterator retval = last;
			do {
				++retval;
				mutASSERT(retval == controller_changed.end()
					  || *retval == -1
					  || (size_t)(*retval) < controller.size());
			} while (retval != controller_changed.end()
				 && ((*retval == -1)
				     || ( *retval >= 0
					  && (size_t)(*retval) < other.controller.size()
					  && controller[*retval] == other.controller[*retval])));
			return retval;
		}

		bool is_changed_controller(controller_vector::const_iterator actual) const {
			mutASSERT(controller_changed.begin() <= actual);
			mutASSERT(actual<= controller_changed.end());
			if (actual == controller_changed.end()) return false;
			if (*actual == -1) return false;
			mutASSERT(0<= *actual);
			mutASSERT((size_t)(*actual) < controller.size());
			return true;
		}

		void program_change(int program) {
			Sound = program;
			int8_t data = controller[midi::BANK_COARSE];
			if (data != -1) {
				bank_coarse = data;
				controller[midi::BANK_COARSE] = -1;
			}

			data = controller[midi::BANK_FINE];
			if (data != -1) {
				bank_fine = data;
				controller[midi::BANK_FINE] = -1;
			}
		}

		void program_change(const ChannelData & o) {
			Sound = o.Sound;
			bank_coarse = o.bank_coarse;
			if (controller[midi::BANK_COARSE] == bank_coarse)
				controller[midi::BANK_COARSE] = -1;
			bank_fine = o.bank_fine;
			if (controller[midi::BANK_FINE] == bank_coarse)
				controller[midi::BANK_FINE] = -1;
		}

		bool is_compatible (const ChannelData &cd) const {
			/* \todo check that ignoring pitch bend is ok */
			if (Sound != -1 && cd.Sound != -1
			    && Sound != cd.Sound) return false;
			if (controller.size()
			    != cd.controller.size()) return false;

			/* \todo optimization */
			for (size_t i = 0 ; i < std::min(controller.size(),cd.controller.size()) ; i++) {
				if (controller[i] != -1
				    && cd.controller[i] != -1
				    && controller[i] != cd.controller[i]) return false;
			}
			return true;
		}

		int get_bend() { return bend; }
		void set_bend(int b) { bend = b; }

		int get_program() const {return Sound; }
		int get_bank_coarse() const { return bank_coarse; }
		int get_bank_fine() const { return bank_fine; }
	protected:
		controller_vector controller;
		controller_vector controller_changed;
		size_t first_unchanged;
		bool looped;
		bool data_is_rpn;         //< false if current Data entry is for NRPN
		int Sound;                //< Programe -1 if unused
		uint8_t bank_coarse;      //< MSB as saved during last program change
		uint8_t bank_fine;        //< LSB as saved during last program change
		int bend;                 //< pitch bend value as integer -8192 – +8191
	};

	class Device
	{
	public:
		/* this will be used to get the right Id */
		enum devidtype {
			IDTypeSession,
			IDTypeFile,
			IDTypeHardware
		};

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
		virtual void Panic(int type) = 0;


		// The following functions can be used both for playback and recording.
		// Nevertheless they should not be availlable without a proper device type.

		/**
		 * Start playback or recording of the device.
		 *
		 */
		virtual void Play() {}


		/**
		 * Pause playback or recording of the device.
		 *
		 */
		virtual void Pause() {}

		/**
		 * Stop playback or recording of the device.
		 *
		 */
		virtual void Stop() {}

		virtual void SetMode(MutaborModeType m) { Mode = m; }

		MutaborModeType GetMode() {
			return Mode;
		}

		/// Process an error message
		void runtime_error(int type, mutString message, ...) {
			va_list args;
			va_start(args,message);
			runtime_error(type,message,args);
		}

		/// Process an error message (doing the real work)
		virtual void runtime_error(int type, const mutStringRef message, va_list & args);


		const wxString & GetName() const {
			return Name;
		}

		virtual void SetName(const wxString & s) {
			Name = s;
		}

                /*
		int GetDevId() const {
			return DevId;
		}

		virtual void SetDevId(int id) {
			DevId = id;
		}
		*/


		size_t get_session_id() const {
			return session_id;
		}

		int get_routefile_id() const {
			return routefile_id;
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
		/** \todo lift this restrection afer GUI is working again */
		friend class ::mutaborGUI::GUIOutputDeviceBase;
		friend class ::mutaborGUI::GUIInputDeviceBase;
		/**
		   Id used during runtime;
		 */
		idtype<Device> session_id;
		int routefile_id;
		mutString Name;
		bool dirty:1;
		bool isOpen:1;
		enum MutaborModeType Mode;
		routeListType routes;

		Device(const mutStringRef name = mutEmptyString,
		       int id = -1):session_id(),
				    routefile_id(id),
				    Name(name),
				    dirty(false),
				    isOpen(false),
				    Mode(DeviceInitializing),
				    routes(),
				    userdata(NULL)
		{}

		virtual void setUserData (void * data) {
			userdata = data;
		}
		virtual void * getUserData() const { return userdata; }

		void set_routefile_id(int id) {
			routefile_id = id;
		}

	private:
		void * userdata;

	};

	// A common api for input and output devices that must be typed

	template <class T, class P = boost::intrusive_ptr<T>,
		  class L = std::vector <P> >
	class CommonTypedDeviceAPI: public Device {
	private:
		REFPTR_INTERFACE;

	public:
		// To gain a little speed in realtime we use intrusive_ptr
		typedef T thistype;
		typedef P DevicePtr;
		typedef L listtype;
	protected:
	        static listtype deviceList;

		CommonTypedDeviceAPI():Device()	{
			AppendToDeviceList(static_cast<thistype *>(this));
		}

		CommonTypedDeviceAPI(const mutStringRef name,
				     int id = -1):Device(name, id) {
			AppendToDeviceList(static_cast<thistype *>(this));
		}

	public:
		virtual ~CommonTypedDeviceAPI();

		/**
		 * Destroy the current object.
		 * This function is
		 * called when an object shall be deleted. It clears
		 * up all references to itself so that it will be deleted if it is not needed anymore.
		 *
		 * This functions detatches the device from all routes and calls DoDestroy() afterwards.
		 * Finally the Device is going to removed from the device list.
		 */
		virtual void Destroy();


		/**
		 * Disconnect the device from all pairings with routes GUI data or something else.
		 *
		 * This function should be extended in subclasses so
		 * that after calling it only temporary pointers
		 * (variables in functions or temporary objects) point
		 * to the object.
		 */
		virtual void DisconnectFromAll();

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
		static DevicePtr GetDevice(int id, devidtype kind);

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

		/**
		 * Move the device in the device list.
		 *
		 * \param count Number of places the device should be
		 * moved up. Negative values indicate downwards
		 * direction.
		 *
		 * \return new position in the device list.
		 */
		virtual	int MoveInList(int count);

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
	public:
		virtual ~OutputDeviceClass() {
			TRACEC;
			wxASSERT(!IsOpen());
			TRACEC;
		}
		void NoteOn(Box box,
			    int taste,
			    int velo,
			    RouteClass * r,
			    size_t id,
			    const ChannelData & input_channel_data) {
			ScopedLock lock(write_lock);
			do_NoteOn(box,taste,velo,r,id,input_channel_data);

		}
		void NoteOff(Box box,
			     int taste,
			     int velo,
			     RouteClass * r,
			     size_t id,
			     bool is_note_on) {
			ScopedLock lock(write_lock);
			do_NoteOff(box,taste,velo,r,id,is_note_on);
		}
		void UpdateTones(RouteClass * route) {
			ScopedLock lock(write_lock);
			do_UpdateTones(route);
		}
		void Controller(int mutabor_channel,
				int controller,
				int value,
				size_t id) {
			ScopedLock lock(write_lock);
			do_Controller(mutabor_channel,
				      controller,
				      value,
				      id);
		}
//		virtual void Sustain(int channel, const ChannelData & cd) = 0;
		int  GetChannel(int inkey, size_t channel, size_t id) {
			ScopedLock lock(write_lock);
			return do_GetChannel(inkey,channel,id);
		}
		void Gis(GisToken *token, char turn) {
			ScopedLock lock(write_lock);
			do_Gis(token,turn);
		}
		void AddTime(frac time) {
			ScopedLock lock(write_lock);
			do_AddTime(time);
		}
		void MidiOut(mutabor::Box box, midi_string data) {
			ScopedLock lock(write_lock);
			do_MidiOut(box,data);
		}
		void MidiOut(BYTE *p, size_t n) {
			ScopedLock lock(write_lock);
			do_MidiOut(p,n);
		}

		void handle_event(event e) {
			ScopedLock lock(write_lock);
			do_handle_event(e);
		}
		void Quiet(Route r, int type) {
			ScopedLock lock(write_lock);
			do_Quiet(r,type);
		}
		void Quiet(Route r,int type, size_t id) {
			ScopedLock lock(write_lock);
			do_Quiet(r,type,id);
		}

		void Panic(int type) {
			ScopedLock lock(write_lock);
			do_Panic(type);
		};
		bool Open() {
			ScopedLock lock(write_lock);
			return do_Open();
		}

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

	protected:
		Mutex write_lock;
		// private members: access only via access functions for debugging purposes
		/*
		  OutputDeviceNext;
		  static OutputDevice deviceList;
		*/
		OutputDeviceClass():CommonTypedDeviceAPI<OutputDeviceClass>(),
				    write_lock() {}

		OutputDeviceClass(const mutStringRef name,
				  int id = -1):
			CommonTypedDeviceAPI<OutputDeviceClass>(name, id),
			write_lock() {}

		/**
		 * Really Send the beginning of a sounding note.
		 *
		 * \param box   Mutabor box that contains the tuning information
		 * \param taste input key from file or keyboard
		 * \param velo  key press velocity
		 * \param r     route that has been used to transmit the note
		 * \param id    an additional number that is used to make the note unique
		 * \param input_channel_data current device settings (Controllers, Sound, etc.)
		 *
		 * \sa \ref OutputDeviceClass::NoteOn, \ref OutputDeviceClass::NoteOff
		 */
		virtual void do_NoteOn(Box box,
				    int taste,
				    int velo,
				    RouteClass * r,
				    size_t id,
				    const ChannelData & input_channel_data) = 0;
		virtual void do_NoteOff(Box box,
				     int taste,
				     int velo,
				     RouteClass * r,
				     size_t id,
				     bool is_note_on) = 0;
		virtual void do_UpdateTones(RouteClass * route) = 0;
		virtual void do_Controller(int mutabor_channel,
					   int controller,
					   int value,
					   size_t id) = 0;
//		virtual void Sustain(int channel, const ChannelData & cd) = 0;
		virtual int  do_GetChannel(int inkey, size_t channel, size_t id) = 0;
		virtual void do_Gis(GisToken *token, char turn) = 0;
		virtual void do_AddTime(frac time) = 0;
		virtual void do_MidiOut(mutabor::Box box, midi_string data) = 0;
		virtual void do_MidiOut(BYTE *p, size_t n) = 0;
		virtual void do_handle_event(event & e) = 0;
		virtual void do_Quiet(Route r, int type) = 0;
		virtual void do_Quiet(Route r, int type, size_t id) = 0;
		virtual void do_Panic(int type) { STUBC; };
		virtual bool do_Open() { return true; }

	};



// Input devices -------------------------------------------------
	class InputDeviceClass;
	typedef CommonTypedDeviceAPI<InputDeviceClass>::DevicePtr InputDevice;
	typedef CommonTypedDeviceAPI<InputDeviceClass>::listtype InputDeviceList;
	class InputDeviceClass: public CommonTypedDeviceAPI<InputDeviceClass>
	{
		friend class DeviceFactory;
	public:
		struct current_keys_type {
			struct entry {
				int key;
				size_t unique_id;
				int velocity;
				Route route;
				InputDevice device;
				const ChannelData * settings;
				void * userdata;
				entry(int k,
				      int u,
				      int v,
				      Route &R,
				      InputDevice i,
				      const ChannelData * c,
				      void * d): key(k),
						 unique_id(u),
						 velocity(v),
						 route (R),
						 device(i),
						 settings(c),
						 userdata(d){}

				bool operator == (const entry & e) const {
					return e.key == key
						&& e.unique_id == unique_id
						&& e.route == route;
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
				  Route & R,
				  InputDevice i,
				  const ChannelData & c,
				  void * userdata) {
				map.insert(entry(key,
						 unique_id,
						 velocity,
						 R,
						 i,
						 &c,
						 userdata));
				DEBUGLOG(routing,_T("(key = %d, channel = %lu, id = %lu)"),
					 key,
					 (unsigned long)R->get_session_id(),
					 (unsigned long)unique_id);
			}
			void add (entry e) {
				map.insert(e);
			}

			void remove(int key,
				    int velocity,
				    int unique_id,
				    Route & R) {
				std::pair<map_type::iterator, map_type::iterator> range =
					map.equal_range(entry(key,unique_id,velocity, R, NULL, NULL, NULL));
				if (range.first != map.end()) {
					map.erase(range.first);
					DEBUGLOG(routing,_T("(key = %d, channel = %lu, id = %lu)"),
						 key,
						 (unsigned long)R->get_session_id(),
						 (unsigned long)unique_id);
				}
			}

			void remove (iterator i ) {
				map.erase(i);
			}

			void clear() {
				map.clear();
			}

			void rehash(size_t n) {
				map.rehash(n);
			}

			iterator begin() { return map.begin(); }
			const_iterator begin() const { return map.begin(); }

			iterator end() { return map.end(); }
			const_iterator end() const { return map.end(); }
		protected:
			map_type map;
		};

		virtual ~InputDeviceClass() { TRACEC; }

		virtual void Close() {
			Stop();
		}
		virtual void Stop() {
			Panic(midi::DEFAULT_PANIC);
			Mode = DeviceStop;
		}

                /** Command the device to play music.
		 * This function starts playing the music of the device at the curren position.
		 */
		virtual void Play() {
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
		virtual mutint64 PrepareNextEvent() { return MUTABOR_NO_DELTA; }

		virtual DevType GetType() const
		{
			return DTUnknown;
		}

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

		void NoteOn(Route &R, int key, int velocity,
			    size_t make_unique,
			    const ChannelData & input_channel_data,
			    void * userdata) {
			ScopedLock lock(write_lock);
			DEBUGLOG(routing,_T("(key = %d, channel = %lu, id = %lu)"),
				 key,
				 (unsigned long)R->get_session_id(),
				 (unsigned long)make_unique);

			current_keys.add(key,
					 velocity,
					 make_unique,
					 R,
					 this,
					 input_channel_data,
					 userdata);
			if (R) {
				R->NoteOn(key,
					  velocity,
					  make_unique,
					  input_channel_data,
					  userdata);
			}
		}

		void NoteOff(Route & R,
			     int key,
			     int velocity,
			     size_t make_unique) {
			ScopedLock lock(write_lock);
			DoNoteOff(R, key, velocity, make_unique);
		}

		void DoNoteOff(Route & R,
			       int key,
			       int velocity,
			       size_t make_unique) {
			if (R) {
				R->NoteOff(key,velocity,make_unique);
			}
			current_keys.remove(key, velocity, make_unique, R);
			DEBUGLOG(routing,_T("(key = %d, channel = %lu, id = %lu)"),
				 key,
				 (unsigned long)R->get_session_id(),
				 (unsigned long)make_unique);
		}

		void SilenceKeys(bool remove) {
			ScopedLock lock(write_lock);
			DoSilenceKeys(remove);
		}
		void DoSilenceKeys(bool remove);
		void ResumeKeys();

		void Panic(int type);
		void Panic(int type, size_t unique_id);


		virtual ChannelData & GetChannelData(const current_keys_type::entry & key) const  = 0;

	protected:
		current_keys_type current_keys;
		Mutex write_lock;

		InputDeviceClass(const mutStringRef name = mutEmptyString,
				 mutabor::MutaborModeType m = DeviceStop,
				 int id = -1):
			CommonTypedDeviceAPI<InputDeviceClass>(name, id)
		{
			Mode = m;
		}

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

		static OutputDevice CreateOutput (int type,
						  const mutStringRef name = mutEmptyString,
						  MutaborModeType mode = DeviceStop,
						  int id = -1) {
			/* \todo implement output device record/pause */
			mutASSERT(type >= 0);
			if (factories.size() <=(size_t) type) {
				BOOST_THROW_EXCEPTION(FactoryNotFound(type));
				UNREACHABLECT(DeviceFactory);
				return NULL;
			}
			if (!factories[type])
				BOOST_THROW_EXCEPTION(FactoryNotFound(type));
			return factories[type]->DoCreateOutput(name,id);
		}


		static InputDevice CreateInput(int type,
					       const mutStringRef name = mutEmptyString,
					       MutaborModeType mode = DeviceStop,
					       int id = -1) {
			mutASSERT(type >= 0);
			if (factories.size() <= (size_t)type) {
				BOOST_THROW_EXCEPTION(FactoryNotFound(type));
				UNREACHABLECT(DeviceFactory);
				return NULL;
			}
			if (!factories[type])
				BOOST_THROW_EXCEPTION(FactoryNotFound(type));
			return factories[type]->DoCreateInput(name, mode, id);
		}

		template<class T> static T Create(int type,
						  const mutStringRef name = mutEmptyString,
						  MutaborModeType mode = DeviceStop,
						  int id = -1);

		static void Destroy() {
			if (!factories.empty()) {
				for (factorylist::iterator i = factories.begin();
				     i != factories.end(); ++i) {
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

		virtual OutputDeviceClass * DoCreateOutput(const mutStringRef name,
							   int id = -1) const = 0;

		virtual InputDeviceClass * DoCreateInput(const mutStringRef name,
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

	template <>
	inline InputDevice DeviceFactory::Create<InputDevice>(int type,
						       const mutStringRef name,
						       MutaborModeType mode,
						       int id) {
	        return CreateInput(type,name,mode,id);
	}

	template<>
	inline OutputDevice DeviceFactory::Create<OutputDevice>(int type,
						       const mutStringRef name,
						       MutaborModeType mode,
						       int id) {
	        return CreateOutput(type,name,mode,id);
	}

	void InitDeviceFactories();

	class ScopedInputDevice: public InputDevice {
	public:
		~ScopedInputDevice() {
			if (get())
				get()->Destroy();
		}

		ScopedInputDevice & operator = (InputDeviceClass * rhs) {
			(*(static_cast<InputDevice *>(this))) = rhs;
			return *this;
		}
		ScopedInputDevice & operator = (const InputDevice & rhs) {
			(*(static_cast<InputDevice *>(this))) = rhs;
			return *this;
		}
	};

	class ScopedOutputDevice: public OutputDevice {
	public:
		~ScopedOutputDevice() {
			if (get())
				get()->Destroy();
		}
		ScopedOutputDevice & operator = (OutputDeviceClass * rhs) {
			(*(static_cast<OutputDevice *>(this))) = rhs;
			return *this;
		}
		ScopedOutputDevice & operator = (const OutputDevice & rhs) {
			(*(static_cast<OutputDevice *>(this))) = rhs;
			return *this;
		}
	};



// functions --------------------------------------------------------



//	void OutNotesCorrect(mutabor_box_type *  box);


	bool OutOpen();

	void OutClose();

	void OutAddTime(frac time);

	bool InOpen();

	void InClose();

	bool NeedsRealTime();

//frac InReadOn(frac time);




}

#endif /* precompiled */
#endif

/*
 * \}
 */
