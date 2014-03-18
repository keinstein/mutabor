/** \file
 ********************************************************************
 * Midi Port IO (Mutabor layer)
 *
 * Copyright:   (c) 1998-2011 TU Dresden
 * \author  R.Krauße
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
 ********************************************************************
 * \addtogroup route
 * \{
 ********************************************************************/

#include "src/kernel/routing/midi/DevMidi.h"
#include "src/kernel/Execute.h"
//#include "src/kernel/GrafKern.h"
#include "src/kernel/MidiKern.h"
#include "src/kernel/routing/Route-inlines.h"
#include "wx/msgdlg.h"
#include <boost/foreach.hpp>


// OutputMidiPort ------------------------------------------------------

//static long freq ;

#ifdef RTMIDI
#include "RtMidi.h"
#endif

#include "src/kernel/routing/midi/midicmn-inlines.h"

// the following file is not compiled independently
#include "src/kernel/routing/midi/midicmn.cpp"

namespace mutabor {

	template class CommonMidiOutput<MidiPortOutputProvider,OutputDeviceClass>;
	template class CommonMidiInput<InputDeviceClass>;

	using namespace midi;

	extern  RtMidiOut * rtmidiout;
	extern RtMidiIn *rtmidiin;

        /// Save current device settings in a tree storage
        /** \argument config (tree_storage) storage class, where the data will be saved.
	 */
	void OutputMidiPort::Save (tree_storage & config)
	{
		config.Write(_T("Device Id"),DevId);
		config.Write(_T("Device Name"),Name);
		config.Write(_T("Bending Range"),GetBendingRange());
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
		wxString oldpath = config.GetPath();
#endif
		mutASSERT(route);

		config.toLeaf(_T("Midi Output"));
		config.Write(_T("Avoid Drum Channel"), route->OutputAvoidDrumChannel());
		config.Write(_T("Channel Range From"), route->GetOutputFrom());
		config.Write(_T("Channel Range To"), route->GetOutputTo());
		config.toParent();
		mutASSERT(oldpath == config.GetPath());
	}


/// Load current device settings from a tree storage
/** \argument config (tree_storage) storage class, where the data will be loaded from.
 */
	void OutputMidiPort::Load (tree_storage & config)
	{
#ifdef DEBUG
		wxString oldpath = config.GetPath();
#endif
		DevId = config.Read(_T("Device Id"),0);
		Name = config.Read(_T("Device Name"), rtmidiout?(rtmidiout->getPortCount()?
				   muT(rtmidiout->getPortName(0).c_str()):wxString(_("Unknown"))):wxString(_("no device")));
		SetBendingRange(config.Read(_T("Bending Range"),DEFAULT_BENDING_RANGE));
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
		wxString oldpath = config.GetPath();
#endif
		mutASSERT(route);
		config.toLeaf(_T("Midi Output"));
		route->OutputAvoidDrumChannel(config.Read(_T("Avoid Drum Channel"), true));
		int oldfrom, oldto;
		route->SetOutputFrom(oldfrom = config.Read(_T("Channel Range From"), GetMinChannel()));
		route->SetOutputTo(oldto = config.Read(_T("Channel Range To"), GetMaxChannel()));
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
		if (!correct)
			wxMessageBox(wxString::Format(_("The Channel range %d--%d of the MIDI output device %s must be inside %d--%d. The current route had to be corrected."),
						      oldfrom,oldto,GetName().c_str(),GetMinChannel(),GetMaxChannel()),
				     _("Warning loading route"),wxICON_EXCLAMATION);
		config.toParent();
		mutASSERT(oldpath == config.GetPath());
	}



#if 0
	void OutputMidiPort::ReadData(wxConfigBase * config)
	{
		midi.SetBendingRange(config->Read(_("Bending_Range"),
						  DEFAULT_BENDING_RANGE));
	}

	void OutputMidiPort::WriteData(wxConfigBase * config)
	{
		config->Write(_("Bending_Range"), (long)bending_range);
	}
#endif

#ifdef WX
	wxString OutputMidiPort::TowxString() const {
		wxString channelString;
		for (int i = 0 ; i<16; i++) {
			channelString += wxString::Format(_T(" ({not implemented},%d,[in=%d,p=%d,b=%d,u=%d,ch=%d])"),
							  ton_auf_kanal[i].active,
							  ton_auf_kanal[i].inkey,
							  ton_auf_kanal[i].outkey.pitch,
							  ton_auf_kanal[i].outkey.bend,
							  (int)ton_auf_kanal[i].unique_id,
							  (int)ton_auf_kanal[i].channel
				);
		}
		return OutputDeviceClass::TowxString()
			+ wxString::Format(_T("\
OutputMidiPort:\n\
   channels ({sound,sustain,MSB,LSB,pitch},KeyDir,[tasta,outkey,id]):\n\
             %s\n\
   nKeyOn   = %d\n\
"), (const wxChar *)channelString, nKeyOn);

	}
#endif

// InputMidiPort -------------------------------------------------------

#ifdef RTMIDI

	void mycallback( double deltatime, std::vector< unsigned char > *message, void *userData )
	{
		mutUnused(deltatime);

		mutASSERT(userData);
		mutASSERT(message);
		if (!message || !userData) {
			UNREACHABLE;
		}
		InputMidiPort * thisPort = static_cast<InputMidiPort *>(userData);

		thisPort -> Proceed(message, 0, 0);
		return;
	}

#else

	void CALLBACK MidiInPortFunc(HMIDIIN hMidiIn, UINT wMsg, DWORD dwInstance, DWORD dwParam1, DWORD dwParam2)
	{
		//  CurrentTimeStamp = dwParam2;

		if ( wMsg != MIM_DATA || dwParam1 % 256 > 240 ) return;

		// Daten in Midi-Automat
		((InputMidiPort*)dwInstance)->Proceed(dwParam1);
	}

#endif

// InputMidiPort -------------------------------------------------------
/// Save current device settings in a tree storage
/** \argument config (tree_storage) storage class, where the data will be saved.
 */
	void InputMidiPort::Save (tree_storage & config)
	{
#ifdef DEBUG
		wxString oldpath = config.GetPath();
#endif
		config.Write(_T("Device Id"),   DevId);
		config.Write(_T("Device Name"), Name);
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
		wxString oldpath = config.GetPath();
#endif
		config.toLeaf(_T("Midi Input"));
		config.Write(_T("Filter Type"), route->GetType());
		switch(route->GetType()) {
		case RTchannel:
			config.Write(_T("Channel From"), route->GetInputFrom());
			config.Write(_T("Channel To"), route->GetInputTo());
			break;
		case RTstaff:
			config.Write(_T("Key From"), route->GetInputFrom());
			config.Write(_T("Key To"), route->GetInputTo());
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
		wxString oldpath = config.GetPath();
#endif
		DevId = config.Read(_T("Device Id"), 0);
		Name  = config.Read(_T("Device Name"),
				    (rtmidiin?(
				    rtmidiin->getPortCount()?
				    muT(rtmidiin->getPortName(0).c_str()):wxString(_("Unknown"))):wxString(_("no device"))));
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
		wxString oldpath = config.GetPath();
#endif
		config.toLeaf(_T("Midi Input"));
		route->SetType((RouteType) config.Read(_T("Filter Type"), (int) RTchannel));
		switch(route->GetType()) {
		case RTchannel:
		{
			int oldfrom, oldto;
			route->SetInputFrom(oldfrom = config.Read(_T("Channel From"), GetMinChannel()));
			route->SetInputTo(oldto = config.Read(_T("Channel To"), GetMaxChannel()));
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
				wxMessageBox(wxString::Format(_("The Channel range %d--%d of the MIDI input device %s must be inside %d--%d. The current route had to be corrected."),
							      oldfrom,oldto,GetName().c_str(),GetMinChannel(),GetMaxChannel()),
					     _("Warning loading route"),wxICON_EXCLAMATION);
			break;
		}

		case RTstaff:
		{
			int oldfrom, oldto;
			route->SetInputFrom(oldfrom = config.Read(_T("Key From"), GetMinKey()));
			route->SetInputTo(oldto = config.Read(_T("Key To"), GetMaxKey()));
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
			if (!correct)
				wxMessageBox(wxString::Format(_("The Channel range %d--%d of the MIDI input device must be inside %d--%d. The current route had to be corrected."),
							      oldfrom,oldto, GetName().c_str(),GetMinKey(), GetMaxKey()),
					     _("Warning loading route"),wxICON_EXCLAMATION);
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

#ifdef RTMIDI
		try {
			hMidiIn = new RtMidiIn(RtMidi::UNSPECIFIED, PACKAGE_STRING);
		} catch (RtError &error) {
			runtime_error(false,
				      _("Can not open Midi input device no. %d (%s)."),
				      DevId,
				      (const mutChar *)(GetName().c_str()));
			return false;
		}

		try {
			hMidiIn->openPort(DevId,(const char *)(GetName().ToUTF8()));
		} catch (RtError &error) {
			runtime_error(false,
				      _("Can not open Midi input device no. %d (%s):\n%s"),
				      DevId,
				      (const mutChar *)(GetName().c_str()),
				      error.what());
			return false;
		}

		try {
			hMidiIn->setCallback(mycallback, this);
		} catch (RtError & error) {
			runtime_error(false,
				      _("Can not open Midi input device no. %d (%s)."),
				      DevId,
				      (const mutChar *)(GetName().c_str()));
		}

#else
		midiInOpen(&hMidiIn, DevId, (DWORD)MidiInPortFunc, (DWORD)this, CALLBACK_FUNCTION);
		midiInStart(hMidiIn);
#endif
		isOpen = true;
		return true;
	}

	void InputMidiPort::Close()
	{
		mutASSERT(isOpen);
#ifdef RTMIDI
		hMidiIn->closePort();
		delete hMidiIn;
		hMidiIn = NULL;
#else
		midiInStop(hMidiIn);
		midiInReset(hMidiIn);
		midiInClose(hMidiIn);
#endif
		Panic(midi::DEFAULT_PANIC);
		isOpen = false;
	}




#ifdef WX
	wxString InputMidiPort::TowxString() const {
		wxString channelString;
		for (int i = 0; i < 16; i++) {
			channelString += wxString::Format(_T(" {not implemented}"));
		}
		return InputDeviceClass::TowxString()
			+wxString::Format(_T("\
InputMidiPort:\n\
   hMidiIn = %p\n\
   channels {sound,sustain,MSB,LSB,pitch}:\n\
             %s\n\
"), (void*)hMidiIn, (const wxChar *)channelString);

	}
#endif


	InputMidiPort::proceed_bool InputMidiPort::shouldProceed(Route R, const std::vector<unsigned char > * midiCode, int data)
	{
		mutASSERT(midiCode);
		switch ( R->GetType() ) {
		case RTchannel:
			if (R->Check(midiCode->at(0) & 0x0F))
				return ProceedYes;
			break;
		case RTstaff:
			if ( ((midiCode->at(0) & 0xF0) != 0x80 &&
			      (midiCode->at(0) & 0xF0) != 0x90)
			     || R->Check(midiCode->at(1)) )
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


	void InputMidiPort::Proceed(const std::vector<unsigned char > * midiCode, int data, int channel_offset) {
		/** \todo implement system messages */
		BYTE MidiChannel = (midiCode->at(0) & 0x0F) + channel_offset;
		BYTE MidiStatus  = midiCode->at(0);
		DEBUGLOG (midifile, _T("Status: %x"), MidiStatus);

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




	mutabor::OutputDeviceClass * MidiPortFactory::DoCreateOutput(const mutStringRef name,
								     int id) const
	{
		OutputMidiPort * port = new OutputMidiPort(name,id);
		if (!port) BOOST_THROW_EXCEPTION(DeviceNotCreated());
		return port;
	}

/*
	mutabor::OutputDeviceClass *  MidiPortFactory::DoCreateOutput (int devId,
							   const mutStringRef name,
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

	mutabor::InputDeviceClass *  MidiPortFactory::DoCreateInput (const mutStringRef name,
								     MutaborModeType mode,
								     int id) const
	{
 		InputMidiPort * port = new InputMidiPort(name,mode,id);
		if (!port) BOOST_THROW_EXCEPTION(DeviceNotCreated());
		return port;
	}



#ifdef RTMIDI
#include <string>

	using namespace std;
#include "RtMidi.h"
	RtMidiOut *rtmidiout;
	RtMidiIn *rtmidiin;
#endif

	void MidiInit()
	{
#ifdef RTMIDI

		try {
			rtmidiout = new RtMidiOut(RtMidi::UNSPECIFIED, PACKAGE_STRING);
		} catch (RtError &error) {
			error.printMessage();
			// abort();
		}

		try {
			rtmidiin = new RtMidiIn(RtMidi::UNSPECIFIED, PACKAGE_STRING);
		} catch (RtError &error) {
			error.printMessage();
			// abort();
		}

#endif
	}

	void MidiUninit()
	{
#ifdef RTMIDI
		delete rtmidiin;
		delete rtmidiout;
#endif
	}

}

///\}
