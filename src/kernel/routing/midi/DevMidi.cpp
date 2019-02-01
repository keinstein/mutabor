/** \file
 ********************************************************************
 * Midi Port IO (Mutabor layer)
 *
 * Copyright:   (c) 1998-2011 TU Dresden
 * \author  R.Krauße
 * Tobias Schlemmer <keinstein@users.sourceforge.net>
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
 * \addtogroup route
 * \{
 ********************************************************************/

#include "src/kernel/routing/midi/DevMidi.h"
#include "src/kernel/Execute.h"
//#include "src/kernel/GrafKern.h"
#include "src/kernel/MidiKern.h"
#include "src/kernel/routing/Route-inlines.h"
#include <boost/foreach.hpp>


// OutputMidiPort ------------------------------------------------------

//static long freq ;

#include "RtMidi.h"

#include "src/kernel/routing/midi/midicmn-inlines.h"

// the following file is not compiled independently
#include "src/kernel/routing/midi/midicmn.cpp"

namespace mutabor {

	template class CommonMidiOutput<MidiPortOutputProvider,minimalOutputDeviceClass>;
	template class CommonMidiInput<InputDeviceClass>;

	using namespace midi;

	extern rtmidi::MidiOut * rtmidiout;
	extern rtmidi::MidiIn  * rtmidiin;

        /// Save current device settings in a tree storage
        /** \argument config (tree_storage) storage class, where the data will be saved.
	 */
	void OutputMidiPort::Save (tree_storage & config)
	{
#ifdef DEBUG
		std::string oldpath = config.GetPath();
#endif
		config.Write("Device Id",DevId->getName(rtmidi::PortDescriptor::STORAGE_PATH |
							rtmidi::PortDescriptor::UNIQUE_PORT_NAME |
							rtmidi::PortDescriptor::INCLUDE_API));
		config.Write("Device Name",Name);
		config.Write("Bending Range",GetBendingRange());
		mutASSERT(oldpath == config.GetPath());
	}

        /// Save route settings (filter settings) for a given route
	/** Some route settings (e.g. filter settings) are device type
	 * specific. This function saves them in a tree storage.
	 * \argument config (tree_storage *) Storage class, where the data will be saved.
	 * \argument route (Route ) Route whos data shall be saved.
	 */
	void OutputMidiPort::Save (tree_storage & config, const RouteClass * route)
	{
#ifdef DEBUG
		std::string oldpath = config.GetPath();
#endif
		mutASSERT(route);

		config.toLeaf("Midi Output");
		config.Write("Avoid Drum Channel", route->OutputAvoidDrumChannel());
		config.Write("Channel Range From", route->GetOutputFrom());
		config.Write("Channel Range To", route->GetOutputTo());
		config.toParent();
		mutASSERT(oldpath == config.GetPath());
	}

/// Load current device settings from a tree storage
/** \argument config (tree_storage) storage class, where the data will be loaded from.
 */
	void OutputMidiPort::Load (tree_storage & config)
	{
#ifdef DEBUG
		std::string oldpath = config.GetPath();
#endif
		std::string idstring = config.Read("Device Id", "");
		Name = config.Read("Device Name", _mut("no device"));
		if (rtmidiout) {
			rtmidi::PortList list = rtmidiout->getPortList(rtmidi::PortDescriptor::OUTPUT);
			if (!list.empty()) {
				DevId = *(list.begin());
				for (rtmidi::PortList::iterator i = list.begin();
				     i != list.end();
				     ++i) {
					try {
						if ((*i)->getName(rtmidi::PortDescriptor::STORAGE_PATH |
								  rtmidi::PortDescriptor::UNIQUE_PORT_NAME |
								  rtmidi::PortDescriptor::INCLUDE_API) == idstring) {
							DevId = *i;
							Name = DevId->getName(rtmidi::PortDescriptor::INCLUDE_API |
									      rtmidi::PortDescriptor::SHORT_NAME |
									      rtmidi::PortDescriptor::UNIQUE_PORT_NAME).c_str();
						}
					} catch (const rtmidi::Error &error) {
						runtime_error(false,
							      str(boost::format(_mut("Could not get the name of the MIDI device with id %d:\n%s"))									  % (*i)->getName(rtmidi::PortDescriptor::INCLUDE_API |
																													rtmidi::PortDescriptor::SESSION_PATH).c_str()
								  % error.what()));
						Name = _mut("invalid device");
						return ;
					}
				}
			}
		}
		SetBendingRange(config.Read("Bending Range",DEFAULT_BENDING_RANGE));
		mutASSERT(oldpath == config.GetPath());
	}

/// Loade route settings (filter settings) for a given route
/** Some route settings (e.g. filter settings) are device type
 * specific. This function loads them from a tree storage.
 * \argument config (tree_storage *) Storage class, where the data will be restored from.
 * \argument route (Route) Route whos data shall be loaded.
 */
	void OutputMidiPort::Load (tree_storage & config, RouteClass * route)
	{
#ifdef DEBUG
		std::string oldpath = config.GetPath();
#endif
		mutASSERT(route);
		config.toLeaf("Midi Output");
		route->OutputAvoidDrumChannel(config.Read("Avoid Drum Channel", true));
		int oldfrom, oldto;
		route->SetOutputFrom(oldfrom = config.Read("Channel Range From", GetMinChannel()));
		route->SetOutputTo(oldto = config.Read("Channel Range To", GetMaxChannel()));
		bool correct = true;
		if (oldfrom < GetMinChannel()) {
			correct = false;
			route->SetOutputFrom(GetMinChannel());
		}
		if (oldfrom > GetMaxChannel()) {
			correct = false;
			route->SetOutputFrom(GetMaxChannel());
		}
		if (oldto < GetMinChannel()) {
			correct = false;
			route->SetOutputTo(GetMinChannel());
		}
		if (oldto > GetMaxChannel()) {
			correct = false;
			route->SetOutputTo(GetMaxChannel());
		}
		if (!correct) {
			runtime_error(mutabor::generic_warning,
				      boost::str(boost::format("The Channel range %d--%d of the MIDI output device %s must be inside %d--%d. The current route had to be corrected.")
					  % oldfrom % oldto % GetName().c_str() % GetMinChannel() % GetMaxChannel()));
		}
		config.toParent();
		mutASSERT(oldpath == config.GetPath());
	}


#if 0
	void OutputMidiPort::ReadData(wxConfigBase * config)
	{
		midi.SetBendingRange(config->Read(_mut("Bending_Range"),
						  DEFAULT_BENDING_RANGE));
	}

	void OutputMidiPort::WriteData(wxConfigBase * config)
	{
		config->Write(_mut("Bending_Range"), (long)bending_range);
	}
#endif

	OutputMidiPort::operator std::string() const {
		std::string channelString;
		for (int i = 0 ; i<16; i++) {
			channelString += boost::str(boost::format(" ({not implemented},%d,[in=%d,p=%d,b=%d,u=%d,ch=%d])")
								  % ton_auf_kanal[i].active
								  % ton_auf_kanal[i].inkey
								  % ton_auf_kanal[i].outkey.pitch
								  % ton_auf_kanal[i].outkey.bend
								  % (int)ton_auf_kanal[i].unique_id
								  % (int)ton_auf_kanal[i].channel
								  );
		}
		return OutputDeviceClass::operator std::string()
			+ boost::str(boost::format("\
OutputMidiPort:\n\
   channels ({sound,sustain,MSB,LSB,pitch},KeyDir,[tasta,outkey,id]):\n\
             %s\n\
   nKeyOn   = %d\n\
") % channelString % nKeyOn);

	}

// InputMidiPort -------------------------------------------------------

	class mycallback:public rtmidi::MidiInterface {
	public:
		mycallback(InputMidiPort * c):
			MidiInterface(),
			appclass(c) {}
		virtual ~mycallback() {}

		void rtmidi_midi_in( double deltatime, std::vector< unsigned char > &message)
		{
			mutUnused(deltatime);
			appclass -> Proceed(message, 0, 0);
			return;
		}

		void delete_me() { delete this; }

	protected:
		InputMidiPort * appclass;
	};

// InputMidiPort -------------------------------------------------------
/// Save current device settings in a tree storage
/** \argument config (tree_storage) storage class, where the data will be saved.
 */
	void InputMidiPort::Save (tree_storage & config)
	{
#ifdef DEBUG
		std::string oldpath = config.GetPath();
#endif
		config.Write("Device Id",DevId->getName(rtmidi::PortDescriptor::STORAGE_PATH |
							rtmidi::PortDescriptor::UNIQUE_PORT_NAME |
							rtmidi::PortDescriptor::INCLUDE_API));
		config.Write("Device Name", Name);
		mutASSERT(oldpath == config.GetPath());
	}

/// Save route settings (filter settings) for a given route
/** Some route settings (e.g. filter settings) are device type
 * specific. This function saves them in a tree storage.
 * \argument config (tree_storage *) Storage class, where the data will be saved.
 * \argument route (Route ) Route whos data shall be saved.
 */
	void InputMidiPort::Save (tree_storage & config, const RouteClass * route)
	{
#ifdef DEBUG
		std::string oldpath = config.GetPath();
#endif
		config.toLeaf("Midi Input");
		config.Write("Filter Type", route->GetType());
		switch(route->GetType()) {
		case RTchannel:
			config.Write("Channel From", route->GetInputFrom());
			config.Write("Channel To", route->GetInputTo());
			break;
		case RTstaff:
			config.Write("Key From", route->GetInputFrom());
			config.Write("Key To", route->GetInputTo());
			break;
		case RTelse:
		case RTall:
			break;
		}
		config.toParent();
		mutASSERT(oldpath == config.GetPath());
	}


/// Load current device settings from a tree storage
/** \argument config (tree_storage) storage class, where the data will be loaded from.
 */
	void InputMidiPort::Load (tree_storage & config)
	{
#ifdef DEBUG
		std::string oldpath = config.GetPath();
#endif
		std::string idstring = config.Read("Device Id", "");
		Name = config.Read("Device Name", _mut("no device"));
		if (rtmidiin) {
			rtmidi::PortList list = rtmidiin->getPortList(rtmidi::PortDescriptor::INPUT);
			if (!list.empty()) {
				DevId = *(list.begin());
				for (rtmidi::PortList::iterator i = list.begin();
				     i != list.end();
				     ++i) {
					try {
						if ((*i)->getName(rtmidi::PortDescriptor::STORAGE_PATH |
								  rtmidi::PortDescriptor::UNIQUE_PORT_NAME |
								  rtmidi::PortDescriptor::INCLUDE_API) == idstring) {
							DevId = *i;
							Name = DevId->getName(rtmidi::PortDescriptor::INCLUDE_API |
									      rtmidi::PortDescriptor::SHORT_NAME |
									      rtmidi::PortDescriptor::UNIQUE_PORT_NAME).c_str();
						}
					} catch (const rtmidi::Error &error) {
						runtime_error(false,
							      str(boost::format(_mut("Could not get the name of the MIDI device with id %d:\n%s"))									  % (*i)->getName(rtmidi::PortDescriptor::INCLUDE_API |
																													rtmidi::PortDescriptor::SESSION_PATH).c_str()
								  % error.what()));
						Name = _mut("invalid device");
						return ;
					}
				}
			}
		}
		mutASSERT(oldpath == config.GetPath());
	}

/// Loade route settings (filter settings) for a given route
/** Some route settings (e.g. filter settings) are device type
 * specific. This function loads them from a tree storage.
 * \argument config (tree_storage *) Storage class, where the data will be restored from.
 * \argument route (Route ) Route whos data shall be loaded.
 */
	void InputMidiPort::Load (tree_storage & config, RouteClass * route)
	{
#ifdef DEBUG
		std::string oldpath = config.GetPath();
#endif
		config.toLeaf("Midi Input");
		route->SetType((RouteType) config.Read("Filter Type", (int) RTchannel));
		switch(route->GetType()) {
		case RTchannel:
		{
			int oldfrom, oldto;
			route->SetInputFrom(oldfrom = config.Read("Channel From", GetMinChannel()));
			route->SetInputTo(oldto = config.Read("Channel To", GetMaxChannel()));
			bool correct = true;
			if (oldfrom < GetMinChannel()) {
				correct = false;
				route->SetInputFrom(GetMinChannel());
			}
			if (oldfrom > GetMaxChannel()) {
				correct = false;
				route->SetInputFrom(GetMaxChannel());
			}
			if (oldto < GetMinChannel()) {
				correct = false;
				route->SetInputTo(GetMinChannel());
			}
			if (oldto > GetMaxChannel()) {
				correct = false;
				route->SetInputTo(GetMaxChannel());
			}
			if (!correct)
				runtime_error(false,boost::str(boost::format(_mut("The Channel range %d--%d of the MIDI input device %s must be inside %d--%d. The current route had to be corrected."))
							       % oldfrom
							       % oldto
							       % GetName().c_str()
							       % GetMinChannel()
							       % GetMaxChannel()));
			break;
		}

		case RTstaff:
		{
			int oldfrom, oldto;
			route->SetInputFrom(oldfrom = config.Read(("Key From"), GetMinKey()));
			route->SetInputTo(oldto = config.Read(("Key To"), GetMaxKey()));
			bool correct = true;
			if (oldfrom < GetMinKey()) {
				correct = false;
				route->SetInputFrom(GetMinKey());
			}
			if (oldfrom > GetMaxKey()) {
				correct = false;
				route->SetInputFrom(GetMaxKey());
			}
			if (oldto < GetMinKey()) {
				correct = false;
				route->SetInputTo(GetMinKey());
			}
			if (oldto > GetMaxKey()) {
				correct = false;
				route->SetInputTo(GetMaxKey());
			}
			if (!correct) {
				runtime_error(false,
					      boost::str(boost::format("The Channel range %d--%d of the MIDI input device must be inside %d--%d. The current route had to be corrected.")
							 % oldfrom % oldto %  GetName().c_str()
							 % GetMinKey() %  GetMaxKey()));
			}
			break;
		}
		case RTelse:
		case RTall:
			break;
		}
		config.toParent();
		mutASSERT(oldpath == config.GetPath());
	}

	bool InputMidiPort::Open()
	{
		mutASSERT(!isOpen);
		for (int i = 0; i < 16; i++)
			channel_data[i].Reset();

		try {
			port = new rtmidi::MidiIn(rtmidi::UNSPECIFIED, PACKAGE_STRING);
		} catch (const rtmidi::Error &error) {
			runtime_error(false,
				      _mut("Can not open MIDI input devices due to memory allocation problems."));
			return false;
		}

		try {
			port->openPort(DevId,(GetName().c_str()));
		} catch (const rtmidi::Error &error) {
			runtime_error(mutabor::generic_warning,
				      boost::str(boost::format(_mut("Can not open MIDI input device %s (%s):\n%s"))
						 % (GetName().c_str())
						 % DevId->getName(rtmidi::PortDescriptor::INCLUDE_API |
								       rtmidi::PortDescriptor::SESSION_PATH).c_str()
						 % error.what()));
			return false;
		}

		try {
			port->setCallback(new mycallback(this));
		} catch (const rtmidi::Error & error) {
			runtime_error(mutabor::generic_warning,
				      boost::str(boost::format(_mut("Can not register callback for MIDI input device %s (%s):\n%s"))
						 % (GetName().c_str())
						 % DevId->getName(rtmidi::PortDescriptor::INCLUDE_API |
								       rtmidi::PortDescriptor::SESSION_PATH).c_str()
						 % error.what()));
		}

		isOpen = true;
		return true;
	}

	void InputMidiPort::Close()
	{
		mutASSERT(isOpen);
		port->closePort();
		delete port;
		port = NULL;
		Panic(midi::DEFAULT_PANIC);
		isOpen = false;
	}




	 InputMidiPort::operator std::string() const {
		std::string channelString;
		for (int i = 0; i < 16; i++) {
			channelString += " {not implemented}";
		}
		return InputDeviceClass::operator std::string()
			+ boost::str(boost::format("\
InputMidiPort:\n\
   port = %p\n\
   channels {sound,sustain,MSB,LSB,pitch}:\n\
             %s\n\
") %  (void*)port % channelString);

	}


	InputMidiPort::proceed_bool InputMidiPort::shouldProceed(Route R,
								 const std::vector<unsigned char > &midiCode,
								 int data)
	{
		mutUnused(data);
		switch ( R->GetType() ) {
		case RTchannel:
			if (R->Check(midiCode[0] & 0x0F))
				return ProceedYes;
			break;
		case RTstaff:
			if ( ((midiCode[0] & 0xF0) != 0x80 &&
			      (midiCode[0] & 0xF0) != 0x90)
			     || R->Check(midiCode[1]) )
				return ProceedYes;
			break;

		case RTelse:
			return ProceedElse;
		case RTall:
			return ProceedYes;
		default:
			UNREACHABLEC;
		}
		return ProceedNo;
	}


	void InputMidiPort::Proceed(const std::vector<unsigned char > &midiCode, int data, int channel_offset) {
		/** \todo implement system messages */
		uint8_t MidiChannel = (midiCode[0] & 0x0F) + channel_offset;
		uint8_t MidiStatus  = midiCode[0];
		DEBUGLOG (midifile, "Status: %x" , MidiStatus);

		switch ( MidiStatus ) {
		case midi::SYSTEM_UNDEFINED1:
		case midi::SYSTEM_UNDEFINED2:
		case midi::SYSEX_END:
		case midi::REALTIME_UNDEFINED:
		case midi::ACTIVE_SENSE:
			/* unimplemented or intentionally ignored */
			return;

		case midi::STOP_PLAY:{
			InputDeviceClass::PauseAll();
			event e = create_event(midiCode, MidiChannel);
			OutputDeviceClass::all_handle_event(e);
		}
			return;
		case midi::START_PLAY:
			InputDeviceClass::StopAll();
			FALLTHROUGH;
		case midi::CONTINUE_PLAY: {
			event e = create_event(midiCode, MidiChannel);
			OutputDeviceClass::all_handle_event(e);
			InputDeviceClass::RealtimePlay();
		}
			return;
		case midi::CLOCK:
		case midi::TICK:
		case midi::SONG_SELECT:
		case midi::SONG_POSITION:
		case midi::QUARTER_FRAME: {
			event e = create_event(midiCode,
						 MidiChannel);
			OutputDeviceClass::all_handle_event(e);
		}
			return;
			// the following are handled by midicmn.cpp
		case midi::TUNE_REQUEST:
		case midi::META:
		case midi::SYSEX_START:
		default:
			break;
		}

		parentType::Proceed(midiCode, data, channel_offset);
	}

	MidiPortFactory::~MidiPortFactory() {}




	mutabor::OutputDeviceClass * MidiPortFactory::DoCreateOutput(const std::string & name,
								     int id) const
	{
		OutputMidiPort * port = new OutputMidiPort(name,id);
		if (!port) BOOST_THROW_EXCEPTION(DeviceNotCreated());
		return port;
	}

/*
	mutabor::OutputDeviceClass *  MidiPortFactory::DoCreateOutput (int devId,
							   const std::string name,
							   MutaborModeType mode,
							   int id) const
	{
		OutputMidiPort * port = new OutputMidiPort(devId,name,id);
		if (!port) throw DeviceNotCreated();
		port->Device::SetId(id);
		switch (mode) {
		case DevicePause:
		case DeviceStop:
		case DevicePlay:
			port -> Open() ;
			break;
		case DeviceUnregistered:
		case DeviceCompileError:
		case DeviceTimingError:
		default:
			UNREACHABLEC;
		}
		return port;
	}
*/

	mutabor::InputDeviceClass *  MidiPortFactory::DoCreateInput (const std::string & name,
								     MutaborModeType mode,
								     int id) const
	{
 		InputMidiPort * port = new InputMidiPort(name,mode,id);
		if (!port) BOOST_THROW_EXCEPTION(DeviceNotCreated());
		return port;
	}



#include <string>

	using namespace std;
#include "RtMidi.h"
	rtmidi::MidiOut * rtmidiout;
	rtmidi::MidiIn  * rtmidiin;

	void MidiInit()
	{
		try {
			rtmidiout = new rtmidi::MidiOut(rtmidi::UNSPECIFIED, PACKAGE_STRING);
		} catch (const rtmidi::Error &error) {
			error.printMessage();
			// abort();
		}

		try {
			rtmidiin = new rtmidi::MidiIn(rtmidi::UNSPECIFIED, PACKAGE_STRING);
		} catch (const rtmidi::Error &error) {
			error.printMessage();
			// abort();
		}

	}

	void MidiUninit()
	{
		delete rtmidiin;
		delete rtmidiout;
	}

}
///\}
