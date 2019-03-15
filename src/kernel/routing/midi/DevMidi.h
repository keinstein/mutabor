// -*- C++ -*-
/** \file
 ********************************************************************
 * Classes for midi port
 *
 * Copyright:   (c) 2008-2011 TU Dresden
 * \author  Tobias Schlemmer <keinstein@users.sourceforge.net>
 *
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
 * \addtogroup route
 * \{
 ********************************************************************/

/* we guard a little bit complicated to ensure the references are set right
 */

#if (!defined(MU32_ROUTING_MIDI_DEVMIDI_H) && !defined(PRECOMPILE)) \
	|| (!defined(MU32_ROUTING_MIDI_DEVMIDI_H_PRECOMPILED))
#ifndef PRECOMPILE
#define MU32_ROUTING_MIDI_DEVMIDI_H
#endif

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

#include "src/kernel/Defs.h"
#include "src/kernel/routing/midi/midicmn.h"
//#include "src/wxGUI/generic/mhDefs.h"
#include "src/kernel/routing/Device.h"
//#include "src/kernel/GrafKern.h"

#ifndef MU32_ROUTING_MIDI_DEVMIDI_H_PRECOMPILED
#define MU32_ROUTING_MIDI_DEVMIDI_H_PRECOMPILED

// system headers which do seldom change

#include <cassert>
#include "boost/format.hpp"

#include "lib/rtmidi/RtMidi.h"

namespace mutabor {

	extern rtmidi::MidiOut * rtmidiout;
	extern rtmidi::MidiIn  * rtmidiin;

	/**
	 * Get a MIDI port name from a port descriptor for visible output.
	 *
	 * \param id Port descriptor.
	 *
	 * \return String that represents a MIDI port with a unique name.
	 */
	inline std::string MidiDevIdVisualName(const rtmidi::PortPointer & id) {
		// JACKd2 needs LONG_NAME for meaningful output.
		// This is not necessary for client/port trees
		return id -> getName(rtmidi::PortDescriptor::INCLUDE_API |
				     rtmidi::PortDescriptor::LONG_NAME |
				     rtmidi::PortDescriptor::UNIQUE_PORT_NAME);
	}

	/**
	 * Get a MIDI port name from a port descriptor for configuration.
	 *
	 * \param id Port descriptor.
	 *
	 * \return String that represents a MIDI port with a unique name.
	 */
	inline std::string MidiDevIdStoragePath(const rtmidi::PortPointer & id) {
		// JACKd2 needs LONG_NAME for meaningful output.
		// This is not necessary for client/port trees
		return id -> getName(rtmidi::PortDescriptor::STORAGE_PATH |
				     rtmidi::PortDescriptor::UNIQUE_PORT_NAME |
				     rtmidi::PortDescriptor::INCLUDE_API);
	}

	// OutputMidiPort ------------------------------------------------------
	class MidiPortFactory;

	class MidiPortOutputProvider {
	public:
		MidiPortOutputProvider(Device * p):port(NULL),
						   device(p) {}
		~MidiPortOutputProvider() {
			if (port && port != NULL) {
				Close();
			}
		}

		bool Open(rtmidi::PortDescriptor & id, const std::string name) {
			try {
				port = new rtmidi::MidiOut(rtmidi::UNSPECIFIED, PACKAGE_STRING);
			} catch (const rtmidi::Error &error) {
				device->runtime_error(false,
						      _mut("Can not open MIDI output devices due to memory allocation problems."));
				return false;
			}

			try {
				port->openPort(id, name);
			} catch (const rtmidi::Error &error) {
				device->runtime_error(false,
						      str(boost::format(_mut("Can not open output Midi device %s (%s):\n%s"))
							  % name.c_str()
							  % id.getName(rtmidi::PortDescriptor::INCLUDE_API |
								       rtmidi::PortDescriptor::SESSION_PATH).c_str()
							  % error.what()));
				return false;
			}
			return true;
		}

		bool Open() {
			// Should be done by device.
			if (!port) return false;
			return true;
		}

		void Close() {
			port->closePort();
			delete port;
			port = NULL;
		}

		/**
		 * Outputs a three-byte message.
		 *
		 * \param channel channel to which data shall be sent
		 *        to. How channels are split into tracks or
		 *        subdevices is managed by the OutputProvider
		 * \param byte1 1st byte
		 * \param byte2 2nd byte
		 * \param byte3 3rd byte
		 */
		MidiPortOutputProvider & operator() (int channel,
						      uint8_t byte1,
						      uint8_t byte2,
						      uint8_t byte3) {
			if ((byte1 & midi::TYPE_MASK) != midi::SYSTEM) {
				mutASSERT(!(byte1 & midi::CHANNEL_MASK));
				mutASSERT(channel < 0x10);
				byte1 |= channel;
			} else {
				UNREACHABLEC;
			}
			return RawMsg(channel,byte1,byte2,byte3);
		}
		/**
		 * Outputs a raw three-byte message.
		 *
		 * \param channel channel to which data shall be sent
		 *        to. How channels are split into tracks or
		 *        subdevices is managed by the OutputProvider
		 * \param byte1 1st byte
		 * \param byte2 2nd byte
		 * \param byte3 3rd byte
		 */
		MidiPortOutputProvider & RawMsg (int channel,
						  uint8_t byte1,
						  uint8_t byte2,
						  uint8_t byte3) {
			mutUnused(channel);
			std::vector<unsigned char> message(3);
			message[0] = byte1;
			message[1] = byte2;
			message[2] = byte3;

			port->sendMessage(message);
			return *this;
		}

		/**
		 * Outputs a two-byte message.
		 *
		 * \param channel channel to which data shall be sent
		 *        to. How channels are split into tracks or
		 *        subdevices is managed by the OutputProvider
		 * \param byte1 1st byte
		 * \param byte2 2nd byte
		 */
		MidiPortOutputProvider & operator() (int channel,
						      uint8_t byte1,
						      uint8_t byte2) {
			if ((byte1 & midi::TYPE_MASK) != midi::SYSTEM) {
				mutASSERT(!(byte1 & midi::CHANNEL_MASK));
				mutASSERT(channel < 0x10);
				byte1 |= channel;
			} else {
				UNREACHABLEC;
			}

			return RawMsg(channel,byte1,byte2);
		}

		/**
		 * Outputs a two-byte message.
		 *
		 * \param channel channel to which data shall be sent
		 *        to. How channels are split into tracks or
		 *        subdevices is managed by the OutputProvider
		 * \param byte1 1st byte
		 * \param byte2 2nd byte
		 */
		 MidiPortOutputProvider & RawMsg (int channel,
						  uint8_t byte1,
						  uint8_t byte2) {
			 mutUnused(channel);
			 std::vector<unsigned char> message(2);
			 message[0] = byte1;
			 message[1] = byte2;

			 port->sendMessage(message);
			 return *this;
		}

		/**
		 * Outputs a one-byte message.
		 *
		 * \param byte1 1st byte
		 */
		MidiPortOutputProvider & RawMsg (int channel,
						 uint8_t byte1) {
			mutUnused(channel);
			mutASSERT(channel == -1);
			std::vector<unsigned char> message(1);
			message[0] = byte1;

			port->sendMessage(message);
			return *this;
		}

		/**
		 * Outputs a system exclusive message. The message must include
		 * a valid device id.
		 *
		 * \param channel channel to which data shall be sent
		 *        to. How channels are split into tracks or
		 *        subdevices is managed by the OutputProvider (ignored)
		 * \param from iterator pointing to the beginning of the message.
		 * \param to iterator pointing just after the end of the message.
		 * \note the final 0xf7 is sent automatically.
		 */
		template<class iterator>
		MidiPortOutputProvider & SendSysEx (int channel,
						    iterator from,
						    iterator to) {
			mutUnused(channel);
			if (from == to) return * this;
			if ((*from) & midi::STARTBYTE_MASK) {
				UNREACHABLEC;
				return *this;
			}

			std::vector<unsigned char> message(to - from + 2);
			message[0] = midi::SYSEX_START;
			size_t i = 1;
			while (from != to) {
				message[i++] = (*(from++));
			}
			message[i] = midi::SYSEX_END;

			port->sendMessage(message);
			return *this;
		}

	protected:
		rtmidi::MidiOut * port;
		mutabor::Device * device;
	};

	class OutputMidiPort : public CommonMidiOutput<MidiPortOutputProvider, minimalOutputDeviceClass>
	{
		friend class MidiPortFactory;
	protected:
	public:

		typedef CommonMidiOutput<MidiPortOutputProvider, minimalOutputDeviceClass> base;

		~OutputMidiPort() {};

		/// Save current device settings in a tree storage
		/** \argument config (tree_storage) storage class, where the data will be saved.
		 */
		virtual void Save (tree_storage & config);

		/// Save route settings (filter settings) for a given route
		/** Some route settings (e.g. filter settings) are device type
		 * specific. This function saves them in a tree storage.
		 * \argument config (tree_storage *) Storage class, where the data will be saved.
		 * \argument route (Route ) Route whos data shall be saved.
		 */
		virtual void Save (tree_storage & config, const RouteClass * route);


		/// Load current device settings from a tree storage
		/** \argument config (tree_storage) storage class, where the data will be loaded from.
		 */
		virtual void Load (tree_storage & config);

		/// Loade route settings (filter settings) for a given route
		/** Some route settings (e.g. filter settings) are device type
		 * specific. This function loads them from a tree storage.
		 * \argument config (tree_storage *) Storage class, where the data will be restored from.
		 * \argument route (Route ) Route whos data shall be loaded.
		 */
		virtual void Load (tree_storage & config, RouteClass *  route);



		virtual bool NeedsRealTime()
			{
				return true;
			}

		virtual void SetDevId (rtmidi::PortPointer id) {
			bool reopen = false;
			if (id != DevId && (!id || !DevId || ! (*id == *DevId))) {
				DevId = id;
				if ((reopen = IsOpen()))
					Close(false);
			}
			if (id) {
				try {
					// jackd2 is unusable without long names
					Name = MidiDevIdVisualName(DevId);
				} catch (const rtmidi::Error &error) {
					runtime_error(false,
						      str(boost::format(_mut("Could not get the name of the MIDI device with id %d:\n%s"))
							  % id->getName(rtmidi::PortDescriptor::INCLUDE_API |
									rtmidi::PortDescriptor::SESSION_PATH).c_str()
							  % error.what()));
					Name = _mut("invalid device");
					return ;
				}

			} else
				Name = _mut("no device");
			if (reopen) {
				Open();
			}
		}

		rtmidi::PortPointer GetDevId() { return DevId; }

		virtual DevType GetType() const
		{
			return DTMidiPort;
		}

		virtual std::string GetTypeName () const {
			return _mutN("Midi output device");
		}

#if 0
		virtual void ReadData(wxConfigBase * config);
		virtual void WriteData(wxConfigBase * config);
#endif

		virtual operator std::string() const;

		virtual int GetMaxChannel() const { return 15; }
		virtual int GetMinChannel() const { return 0; }

	protected:
		rtmidi::PortPointer DevId; //< Id of the hardware MIDI device

		OutputMidiPort(std::string name = "",
			       int id = -1,
			       int bendingRange = 2):
			base(name, id, bendingRange),
			DevId(NULL) {
			TRACEC;
		}
		bool do_Open() {
			bool retval = Out.Open(*DevId, Name);
			if (!retval) return false;
			return base::do_Open();
		}

#if defined(_MSC_VER)
#pragma warning(push) // Save warning settings.
#pragma warning(disable : 4100) // Disable unreferenced formal parameter warnings
#endif

		void do_Gis(GisToken * mutUNUSED(token),
			    char mutUNUSED(turn)) {
		}

		void do_AddTime(frac mutUNUSED(time)) {
		}

//		virtual void MidiOut(DWORD data, size_t n);
#if defined(_MSC_VER)
#pragma warning(pop) // Restore warnings to previous state.
#endif
	};

// InputMidiPort -------------------------------------------------------

	class InputMidiPort : public CommonMidiInput<InputDeviceClass>
	{
		friend class MidiPortFactory;
		typedef CommonMidiInput<InputDeviceClass> parentType;
	public:
		virtual ~InputMidiPort() {}

		/// Save current device settings in a tree storage
		/** \argument config (tree_storage) storage class, where the data will be saved.
		 */
		virtual void Save (tree_storage & config);

		/// Save route settings (filter settings) for a given route
		/** Some route settings (e.g. filter settings) are device type
		 * specific. This function saves them in a tree storage.
		 * \argument config (tree_storage *) Storage class, where the data will be saved.
		 * \argument route (Route ) Route whos data shall be saved.
		 */
		virtual void Save (tree_storage & config, const RouteClass *  route);


		/// Load current device settings from a tree storage
		/** \argument config (tree_storage) storage class, where the data will be loaded from.
		 */
		virtual void Load (tree_storage & config);

		/// Loade route settings (filter settings) for a given route
		/** Some route settings (e.g. filter settings) are device type
		 * specific. This function loads them from a tree storage.
		 * \argument config (tree_storage *) Storage class, where the data will be restored from.
		 * \argument route (Route ) Route whos data shall be loaded.
		 */
		virtual void Load (tree_storage & config, RouteClass * route);



		virtual bool Open();
		virtual void Close();
		virtual void Stop() { Panic(midi::DEFAULT_PANIC); };
//		virtual void Play(wxThreadKind tk = wxTHREAD_DETACHED) {};
		virtual void Pause() {};

//	   void Proceed(GisReadArtHead *h, char turn, Route route) {};
//	   void ProceedRoute(GisReadArtHead *h, char turn) {};
#if defined(_MSC_VER)
#pragma warning(push) // Save warning settings.
#pragma warning(disable : 4100) // Disable unreferenced formal parameter warnings
#endif

		virtual frac ReadOn(frac mutUNUSED(time))
		{
			return frac(0,1);
		};

#if defined(_MSC_VER)
#pragma warning(pop) // Restore warnings to previous state.
#endif

		virtual bool NeedsRealTime()
		{
			return true;
		}

		virtual void SetDevId (rtmidi::PortPointer id) {
			bool reopen = false;
			if (id != DevId && (!id || !DevId || !(*id == *DevId))) {
				DevId = id;
				if ((reopen = IsOpen()))
					Close();
			}
			if (id) {
				try {
					// jackd2 needs long names
					Name = MidiDevIdVisualName(DevId);
				} catch (const rtmidi::Error &error) {
					runtime_error(false,
						      str(boost::format(_mut("Could not get the name of the MIDI device with id %d:\n%s"))
							  % id->getName(rtmidi::PortDescriptor::INCLUDE_API |
									rtmidi::PortDescriptor::SESSION_PATH).c_str()
							  % error.what()));
					Name = _mut("invalid device");
					return ;
				}

			} else
				Name = _mut("no device");
			if (reopen) {
				Open();
			}
		}


		virtual rtmidi::PortPointer GetDevId()
		{
			return DevId;
		}

		virtual const std::string& GetName()
		{
			return Name;
		}

#if defined(_MSC_VER)
#pragma warning(push) // Save warning settings.
#pragma warning(disable : 4100) // Disable unreferenced formal parameter warnings
#endif

		virtual void SetName(const std::string & s)
		{
			mutUnused(s);
			parentType::SetName(s);
			assert (false);
			//Name = s;
		}

#if defined(_MSC_VER)
#pragma warning(pop) // Restore warnings to previous state.
#endif

		proceed_bool shouldProceed(Route R,
					   const std::vector<unsigned char > &midiCode,
					   int data =0);

		void Proceed(const std::vector<unsigned char > &midiCode, int data =0, int channel_offset = 0);


		virtual int GetMaxChannel() const { return 15; }
		virtual int GetMinChannel() const { return 0; }
		virtual int GetMaxKey() const { return 127; }
		virtual int GetMinKey() const { return 0; }


		virtual DevType GetType() const
			{
				return DTMidiPort;
			}

		virtual std::string GetTypeName () const {
			return _mutN("Midi input device");
		}

		virtual operator std::string() const;


	protected:
		rtmidi::PortPointer DevId; //< Id of the hardware MIDI device;
		rtmidi::MidiIn *port;
		InputMidiPort(const std::string name = "",
			      MutaborModeType mode = DeviceStop,
			      int id = -1):
			parentType (name,mode,id),
			DevId(NULL),
			port (NULL) {
			channel_data.resize(16);
		}


	};

	class MidiPortFactory:public DeviceFactory {
	public:
		MidiPortFactory(size_t id =  mutabor::DTMidiPort):
			DeviceFactory(id) {}
		virtual ~MidiPortFactory();

	protected:
		virtual size_t GetType() const
			{
				return DTMidiFile;
			}


		virtual mutabor::OutputDeviceClass * DoCreateOutput(const std::string &name,
								    int id = -1) const;

		virtual mutabor::InputDeviceClass * DoCreateInput(const std::string &name,
								  mutabor::MutaborModeType mode,
								  int id = -1) const;
	};



	void MidiInit();
	void MidiUninit();

}
#endif /* precompiled */
#endif


///\}
