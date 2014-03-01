// -*- C++ -*- 
/** \file 
 ********************************************************************
 * Classes for midi port
 *
 * Copyright:   (c) 2008-2011 TU Dresden
 * \author  Tobias Schlemmer <keinstein@users.berlios.de>
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
xs *
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

#ifdef RTMIDI
#include "lib/rtmidi/RtMidi.h"
#else
#ifndef H_MMSYSTEM
//  #define WINVER 0x030a
#include <mmsystem.h>
#define H_MMSYSTEM
#endif
#endif

namespace mutabor {

	extern RtMidiOut * rtmidiout;
	extern RtMidiIn * rtmidiin;

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

		bool Open(int id, const mutStringRef name) {
#ifdef RTMIDI
			try {
				port = new RtMidiOut(RtMidi::UNSPECIFIED, PACKAGE_STRING);
			} catch (RtError &error) {
				device->runtime_error(false,
						      _("Can not open ouput Midi devices due to memory allocation  problems."));
				return false;
			}
			
			try {
				port->openPort(id,(const char *)name.ToUTF8());
			} catch (RtError &error) {
				device->runtime_error(false,
						      _("Can not open output Midi device no. %d (%s)"), 
						      id, (const mutChar *)(name.c_str()));
				return false;
			}

#else
			midiOutOpen(&hMidiOut, DevId, NULL, NULL, NULL);

#endif
			return true;
		}
		
		bool Open() {
			// Should be done by device.
			if (!port) return false;
			return true;
		}

		void Close() {
#ifdef RTMIDI
			port->closePort();
			delete port;
			port = NULL;
#else
			midiOutClose(hMidiOut);

#endif
			
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
			std::vector<unsigned char> message(3);
			message[0] = byte1;
			message[1] = byte2;
			message[2] = byte3;
			
			port->sendMessage(&message);
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
			std::vector<unsigned char> message(2);
			message[0] = byte1;
			message[1] = byte2;
			
			port->sendMessage(&message);
			return *this;
		}

		/** 
		 * Outputs a one-byte message.
		 * 
		 * \param byte1 1st byte
		 */
		MidiPortOutputProvider & RawMsg (int channel, uint8_t byte1) {
			mutASSERT(channel == -1);
			std::vector<unsigned char> message(1);
			message[0] = byte1;
			
			port->sendMessage(&message);
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
		 */
		template<class i>
		MidiPortOutputProvider & SendSysEx (int channel,
						    i from,
						    i to) {
			if (from == to) return * this;
			if ((*from) & midi::STARTBYTE_MASK) {
				UNREACHABLEC;
				return *this;
			}

			std::vector<unsigned char> message(to - from + 1);
			message[0] = midi::SYSEX_START;
			size_t i = 1;
			while (from != to) {
				message[i++] = (*(from++));
			}
			
			port->sendMessage(&message);
			return *this;
		}

	protected:
		RtMidiOut * port;
		mutabor::Device * device;
	};

	class OutputMidiPort : public CommonMidiOutput<MidiPortOutputProvider, OutputDeviceClass>
	{
		friend class MidiPortFactory;
	protected:
	public:

		typedef CommonMidiOutput<MidiPortOutputProvider, OutputDeviceClass> base;
		
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

		virtual void SetDevId (int id) {
			bool reopen = false;
			if (id != DevId) {
				DevId = id;
				if ((reopen = IsOpen()))
					Close();
			}
			if (rtmidiout) 
				Name = muT (rtmidiout->getPortName (DevId).c_str());
			else
				Name = _("no device");
			if (reopen) {
				Open();
			}
		}
		
		int GetDevId() { return DevId; }

		virtual DevType GetType() const
			{
				return DTMidiPort;
			}

		virtual mutString GetTypeName () const {
			return N_("Midi output device");
		}

#if 0
		virtual void ReadData(wxConfigBase * config);
		virtual void WriteData(wxConfigBase * config);
#endif
	
#ifdef WX
		virtual wxString TowxString() const;
#endif

		virtual int GetMaxChannel() const { return 15; }
		virtual int GetMinChannel() const { return 0; }
	
	protected:
		int DevId; //< Id of the hardware MIDI device
#if 0
#ifdef RTMIDI
		RtMidiOut *hMidiOut;
#else
		HMIDIOUT hMidiOut;
#endif
#endif
		
		OutputMidiPort(wxString name = mutEmptyString, 
			       int id = -1, 
			       int bendingRange = 2):
			base(name, id, bendingRange),
			DevId(-1) {
			TRACEC;
		}
		bool do_Open() {
			bool retval = Out.Open(DevId, Name);
			if (!retval) return false;
			return base::do_Open();
		}
	
#if defined(_MSC_VER)
#pragma warning(push) // Save warning settings.
#pragma warning(disable : 4100) // Disable unreferenced formal parameter warnings
#endif

		void do_Gis(GisToken *token, char turn)
			{};

		void do_AddTime(frac time)
			{};

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
		virtual void Play(wxThreadKind tk = wxTHREAD_DETACHED) {};
		virtual void Pause() {};

//	   void Proceed(GisReadArtHead *h, char turn, Route route) {};
//	   void ProceedRoute(GisReadArtHead *h, char turn) {};
#if defined(_MSC_VER)
#pragma warning(push) // Save warning settings.
#pragma warning(disable : 4100) // Disable unreferenced formal parameter warnings
#endif

		virtual frac ReadOn(frac time)
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

		virtual void SetDevId (int id) {
			bool reopen = false;
			if (id != DevId) {
				DevId = id;
				if ((reopen = IsOpen())) 
					Close();
			}
			if (rtmidiin)
				Name = muT (rtmidiin->getPortName (DevId).c_str());
			else
				Name = _("no device");
			if (reopen) {
				Open();
			}
		}

		virtual int GetDevId() 
			{
				return DevId; 
			}

		virtual wxString &GetName()
			{
				return Name;
			}

#if defined(_MSC_VER)
#pragma warning(push) // Save warning settings.
#pragma warning(disable : 4100) // Disable unreferenced formal parameter warnings
#endif

		virtual void SetName(const wxString & s) 
			{
				assert (false);
				//Name = s;
			}

#if defined(_MSC_VER)
#pragma warning(pop) // Restore warnings to previous state.
#endif 

		proceed_bool shouldProceed(Route R, 
					   const std::vector<unsigned char > * midiCode,  
					   int data =0);
	
		void Proceed(const std::vector<unsigned char > * midiCode, int data =0, int channel_offset = 0);


		virtual int GetMaxChannel() const { return 15; }
		virtual int GetMinChannel() const { return 0; }
		virtual int GetMaxKey() const { return 127; }
		virtual int GetMinKey() const { return 0; }	
	

		virtual DevType GetType() const
			{
				return DTMidiPort;
			}

		virtual mutString GetTypeName () const {
			return N_("Midi input device");
		}

#ifdef WX
		virtual wxString TowxString() const;
#endif


	protected:
		int DevId; //< Id of the hardware MIDI device;
	
#ifdef RTMIDI
		RtMidiIn *hMidiIn;

#else
		HMIDIIN hMidiIn;

#endif
		InputMidiPort(const mutStringRef name = mutEmptyString,
			      MutaborModeType mode = DeviceStop,
			      int id = -1):
			parentType (name,mode,id),
			DevId(-1),
			hMidiIn (NULL) {
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


		virtual mutabor::OutputDeviceClass * DoCreateOutput(const mutStringRef name, 
								    int id = -1) const;
		
		virtual mutabor::InputDeviceClass * DoCreateInput(const mutStringRef name, 
								  mutabor::MutaborModeType mode, 
								  int id = -1) const;
	};



	void MidiInit();
	void MidiUninit();

}
#endif /* precompiled */
#endif


///\}
