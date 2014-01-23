/** \file               -*- C++ -*-
 ********************************************************************
 * Common midi functions
 *
 * Copyright:   (c) 2012 Tobias Schlemmer
 * \author  Tobias Schlemmer <keinstein@users.berlios.de>
 * \date
 * $Date: 2011/09/27 20:13:26 $
 * \version $Version$
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
// availlable groups: GUI, route, kernel, muwx, debug, docview

/* we guard a little bit complicated to ensure the references are set right
 */

#include "src/kernel/Defs.h"
#include "src/kernel/routing/midi/midicmn.h"
#include "src/kernel/MidiKern.h"
#include "src/kernel/Execute.h"
#include "src/kernel/Runtime.h"


#ifdef __BORLANDC__
    #pragma hdrstop
#endif


namespace mutabor {
	template<class T, class D>
	bool CommonMidiOutput<T,D>::do_Open() {
		int i;
		mutASSERT(!this->isOpen);
		TRACEC;


		for (i = 0; i < 16; i++) {
			Cd[i].Reset();
			ton_auf_kanal[i].active = false;
			ton_auf_kanal[i].inkey = -1;
			ton_auf_kanal[i].outkey.pitch = -1;
			ton_auf_kanal[i].outkey.bend = 0;
			ton_auf_kanal[i].channel = 0;
			ton_auf_kanal[i].midi_channel = 0;
			ton_auf_kanal[i].unique_id = 0;
		}

		channel_queue.init();

		nKeyOn = 0;

		bool retval = Out.Open();
		if (!retval) return false;

		retval = base::do_Open();
		if (!retval) {
			Out.Close();
			return false;
		}

		for (i = 0; i < 16; i++) {
			pitch_bend(i,0);
			// omni and poly act on 0
			Cd[i].set_controller(midi::LOCAL_ON_OFF,
					     midi::CONTROLLER_OFF );
			Cd[i].set_controller(midi::OMNI_ON,
					     midi::CONTROLLER_OFF );
			Cd[i].set_controller(midi::POLY_ON,
					     midi::CONTROLLER_OFF );
			// we must set the controllers manually
			controller(i,midi::LOCAL_ON_OFF,
				   midi::CONTROLLER_OFF );
			controller(i,midi::OMNI_ON,
				   midi::CONTROLLER_OFF );
			controller(i,midi::POLY_ON,
				   midi::CONTROLLER_OFF );
			do_SendBendingRange(i);
		}

		this->isOpen = true;
		return true;

	}

	template<class T, class D>
	void CommonMidiOutput<T,D>::Close() {
		ScopedLock lock(this->write_lock);
#ifdef DEBUG
		if (mutabor::CurrentTime.isRealtime()) {
			mutASSERT(this->isOpen);
		}
#endif
		TRACEC;

		for (channel_queue_type::iterator i = channel_queue.begin();
		     i != channel_queue.get_first_free();
		     i++) {
			note_off(*i,ton_auf_kanal[*i].outkey.pitch,64);
		}

		Out.Close();
		this->isOpen = false;
	}


	class ChannelFilter {
	public:
		ChannelFilter(const RouteClass * r):route(r) {}

		bool operator () (int channel) {
			return channel >= route->GetOutputFrom()
				&& channel <= route->GetOutputTo()
				&& (!route->OutputAvoidDrumChannel()
				    || channel != DRUMCHANNEL);
		}

		bool check() {
			return route->GetOutputFrom() <= route->GetOutputTo();
		}
	protected:
		const RouteClass * route;
	};


	template<class T, class D>
	typename channel_queue_type::const_iterator
	CommonMidiOutput<T,D>::EmergencyFindChannel(RouteClass * r) {
		mutASSERT(this->isOpen);
		// "mittelste Taste weglassen"
		mutint64 AM = 0; // arithmetisches Mittel der Tasten
		int j;
		int free = 0;

		for (j = r->GetOutputFrom(); j <= r->GetOutputTo(); j++)
			if ( j != DRUMCHANNEL || !r->OutputAvoidDrumChannel() )
				AM += ton_auf_kanal[j].tuned_key;

		AM /= r->GetOutputTo() + 1 - r->GetOutputFrom();

		for ( j = r->GetOutputFrom(); j <= r->GetOutputTo(); j++ )
			if ( j != DRUMCHANNEL || !r->OutputAvoidDrumChannel() )
				if ( abs(AM - (ton_auf_kanal[j].tuned_key))
				     < abs(AM - (ton_auf_kanal[free].tuned_key) ))
					free = j;


		note_off(free, ton_auf_kanal[free].outkey.pitch, 64);

		return channel_queue.reserve_channel(free);
	}

	template<class T, class D>
	void CommonMidiOutput<T,D>::do_UpdateControllers(int channel, const ChannelData & input) {
		// a simple implementation with room for improvements
		for(ChannelData::controller_vector::const_iterator i = input.get_first_changed_controller(Cd[channel]);
		    input.is_changed_controller(i);
		    i = input.get_next_changed_controller(Cd[channel],i)) {
			int number =  *i;
			int value =   input.get_controller(number);
			int ctrl = Cd[channel].get_index(number);
			
			if (ctrl == number && 
			    Cd[channel].get_controller(ctrl) == value) 
				continue;
			
			// this might change the index
			Cd[channel].set_controller(number,value);
			ctrl = Cd[channel].get_index(number);

			if (ctrl == -1) continue;
			
			if (ctrl < 0x10000) {
				mutASSERT(value < 0x80);
				controller(channel, ctrl, value);
			} else if (0x10000 <= ctrl && ctrl < 0x20000) {
				controller(channel,midi::REGISTERED_PARAMETER_COARSE, (ctrl >> 8) & 0x7F);
				controller(channel,midi::REGISTERED_PARAMETER_FINE, ctrl & 0x7F);
				
				controller(channel,midi::DATA_ENTRY_COARSE, value >> 7 & 0x7F);
				controller(channel,midi::DATA_ENTRY_FINE, value & 0x7F);
			} else if (ctrl <= 0x30000) {
				controller(channel,midi::REGISTERED_PARAMETER_COARSE, (ctrl >> 8) & 0x7F);
				controller(channel,midi::REGISTERED_PARAMETER_FINE, ctrl & 0x7F);
				
				controller(channel,midi::DATA_ENTRY_COARSE, value >> 7 & 0x7F);
				controller(channel,midi::DATA_ENTRY_FINE, value & 0x7F);
			}
		}
	}


	template<class T, class D>
	void
	CommonMidiOutput<T,D>::CopyProgramChange(const ChannelData & input_channel_data,
						 ChannelData & output_data,
						 int channel) {
		int sound, bank_fine, bank_coarse;
		bool set_sound = false;
		sound = input_channel_data.get_program();
		if (sound != -1 && output_data.get_program() != sound)
			set_sound =true;
		bank_fine = input_channel_data.get_bank_fine();
		bank_coarse = input_channel_data.get_bank_coarse();

		if (bank_fine != -1 && output_data.get_bank_fine() != bank_fine) {
			set_sound =true;
			if (bank_coarse == -1)
				bank_coarse = output_data.get_bank_coarse();
		} else if (bank_coarse != -1 && output_data.get_bank_coarse() != bank_coarse) {
			set_sound =true;
			if (bank_fine == -1)
				bank_fine = output_data.get_bank_fine();
		}
		if (set_sound && sound == -1)
			sound = output_data.get_program();

		if (set_sound) {
			program_change(channel,sound,bank_fine,bank_coarse);
			output_data.set_controller(midi::BANK_COARSE,bank_coarse);
			output_data.set_controller(midi::BANK_FINE,bank_fine);
			output_data.program_change(sound);
		}
	}

	template<class T, class D>
	void CommonMidiOutput<T,D>::do_NoteOn(Box box,
				      int inkey,
				      int velocity,
				      RouteClass * r,
				      size_t id,
				      const ChannelData & input_channel_data)
	{
		mutASSERT(this->isOpen);
		if (!ChannelFilter(r).check()) {
			UNREACHABLEC;
			return;
		}

		DEBUGLOG (midiio, _T("box %p, inkey %d, velocity %d, id %d"),
			  box.get(), inkey, velocity, (int)id);
//		int free = 16, freeSus = r->OTo, freeVelocitycity = 64, freeSusVelocitycity = 64, s;
//		DWORD p;
		long freq;

		if ( !box ) {
			freq = ((long)inkey) << 24;
		} else
			freq = box->get_frequency(inkey);

		if ( !freq ) return;

		channel_queue_type::const_iterator pos =
			channel_queue.reserve_channel_filtered(ChannelFilter(r));
		if (pos == channel_queue.end()) {
			pos = EmergencyFindChannel(r);
		} else {
			nKeyOn++;
		}

		int channel = *pos;
		ChannelData & output_data = Cd[channel];
 		pitch_bend_type note = pitch_and_bend(freq);
		int8_t controller_value;

		if ( note.bend != output_data.get_bend() ) {
			pitch_bend(channel,note.bend);
			output_data.set_bend(note.bend);

			// Switch off sustain if necessary
			if ( output_data.get_controller(midi::HOLD_PEDAL_ON_OFF)) {
				controller(channel,
					   midi::HOLD_PEDAL_ON_OFF,
					   midi::CONTROLLER_OFF);
				output_data.set_controller(midi::HOLD_PEDAL_ON_OFF,
							   midi::CONTROLLER_OFF);
			}
		}

		if ( output_data.get_controller(midi::HOLD_PEDAL_ON_OFF) !=
		     (controller_value
		      = input_channel_data.get_controller(midi::HOLD_PEDAL_ON_OFF)) ) {
			controller(channel,
				   midi::HOLD_PEDAL_ON_OFF,
				   controller_value);
			output_data.set_controller(midi::HOLD_PEDAL_ON_OFF,
						   controller_value);
		}

		CopyProgramChange(input_channel_data, output_data, channel);

		ton_auf_kanal[channel].active = true;
		ton_auf_kanal[channel].inkey = inkey;
		ton_auf_kanal[channel].velocity = velocity;
		ton_auf_kanal[channel].outkey = note;
		ton_auf_kanal[channel].channel = r->get_session_id();
		ton_auf_kanal[channel].midi_channel = channel;
		ton_auf_kanal[channel].unique_id = id;
		ton_auf_kanal[channel].tuned_key = freq;

		note_on(channel, note.pitch, velocity);

		do_UpdateControllers(channel, input_channel_data);
	}

	template<class T, class D>
	void CommonMidiOutput<T,D>::do_NoteOff(Box box,
				       int inkey,
				       int velo,
				       RouteClass * r,
				       size_t id,
				       bool is_note_on /* = false */
		)
	{
		mutASSERT(this->isOpen);
		if (!r || r == NULL) {
			UNREACHABLEC;
			return;
		}
		DEBUGLOG (midiio, _T("box %p, key %d, velo %d, id %d"),
			  box.get(), inkey, velo, (int)id);


		/* This schouldn't be necessary
		if ( !velo ) //3 ?? notwendig?
			velo = 64;
		*/


		/* Note: though unique_id can be used to memorize
		   certain keys, this is an optional feature. e.g. in
		   MIDI mode two tones which have the same pitch can
		   not easily distinguished. */


		for (int i = r->GetOutputFrom(); i <= r->GetOutputTo(); i++)
			if ( i != DRUMCHANNEL || !r->OutputAvoidDrumChannel() )
				if ( ton_auf_kanal[i].active
				     && ton_auf_kanal[i].inkey == inkey
				     && ton_auf_kanal[i].unique_id == id
				     && ton_auf_kanal[i].channel == r->get_session_id() ) {

					ton_auf_kanal[i].active = false;

					/* note on is used on some devices as special note on
					   while on others it means note off */

					if (is_note_on)
						note_on(i, ton_auf_kanal[i].outkey.pitch, 0);
					else
						note_off(i, ton_auf_kanal[i].outkey.pitch, velo);


					if (is_note_on
					    || Cd[i].get_controller(midi::HOLD_PEDAL_ON_OFF))
						channel_queue.sustain_channel(i);
					else
						channel_queue.free_channel(i);
					nKeyOn--;
					break;
				}
	}

	template<class T, class D>
	void CommonMidiOutput<T,D>::do_UpdateTones(RouteClass * route)
	{
		mutASSERT(this->isOpen);
		TRACEC;
		if (!route || route == NULL) {
			UNREACHABLEC;
			return;
		}

		for (int channel = 0; channel < 16; channel++)
			if ( (ton_auf_kanal[channel].active
			      || Cd[channel].get_controller(midi::HOLD_PEDAL_ON_OFF)>0 )
			     && ton_auf_kanal[channel].channel == route->get_session_id()) {

				TAK & tone = ton_auf_kanal[channel];

				DEBUGLOG(midiio,
					 _T("old(hex/dec): channel = %01x/%d, Inkey = %02x/%d, key = %02x/%d, pitch = %06x/%d"),
					 channel,channel,
					 tone.inkey,tone.inkey,
					 tone.outkey.pitch,tone.outkey.pitch,
					 Cd[channel].get_bend(),Cd[channel].get_bend());

				long freq = route->GetBox()->get_frequency(tone.inkey);

				if (freq == tone.tuned_key) continue;

				pitch_bend_type oldpb = tone.outkey;
				pitch_bend_type newpb = pitch_and_bend(freq,oldpb);

				bool SwitchTone = (newpb.pitch != oldpb.pitch);

				// evtl. Ton ausschalten
				if ( SwitchTone ) {
					bool sustain = Cd[channel].get_controller(midi::HOLD_PEDAL_ON_OFF);
					if ( sustain ) {
						/* temporary sowith hold off */
						controller(channel,midi::HOLD_PEDAL_ON_OFF,0);
					}

					note_off(channel,tone.outkey.pitch, 0);

					if (sustain)
						controller(channel,midi::HOLD_PEDAL_ON_OFF,
							   Cd[channel].get_controller(midi::HOLD_PEDAL_ON_OFF));

				} else if (newpb.bend == oldpb.bend) continue;

				Cd[channel].set_bend(newpb.bend);
				tone.outkey = newpb;
				pitch_bend(channel, newpb.bend);

				// evtl. Ton einschalten
				if ( SwitchTone ) {
					note_on(channel, tone.outkey.pitch, tone.velocity);
				}
			}
	}

	template<class T, class D>
	void  CommonMidiOutput<T,D>::do_Controller(int mutabor_channel,
						   int ctrl,
						   int value,
						   size_t id)
	{


		mutASSERT(ctrl < 0x20000);
		mutASSERT(value < 0x4000);
		mutASSERT(this->isOpen
			  || ctrl == midi::PITCH_BEND_SENSITIVITY
			  || ctrl == midi::LOCAL_ON_OFF
			  || ctrl == midi::OMNI_ON
			  || ctrl == midi::POLY_ON);
		for (int i = 0; i < 16; i++)
			if ( ton_auf_kanal[i].channel == mutabor_channel
			     && (id == ChannelData::IGNORE_UNIQUE_ID
				 || ton_auf_kanal[i].unique_id == id)
			     && (ton_auf_kanal[i].active
				 || Cd[i].get_controller(midi::HOLD_PEDAL_ON_OFF) > 0x40)) {
				if (Cd[i].get_controller(ctrl) == value) {
					switch (ctrl) {
					case midi::DATA_ENTRY_COARSE:
					case midi::DATA_ENTRY_FINE:
#warning also increment/decrement must continue
						break;
					default:
						continue;
					}
				}

				int newctrl = Cd[i].get_index(ctrl);
				if (ctrl == newctrl && Cd[i].get_controller(newctrl) == value)
				    continue;

				// this might change the index (e.g. RPN/NRPN coarse/fine)
				Cd[i].set_controller(ctrl, value);



				newctrl = Cd[i].get_index(ctrl);

				if (newctrl == -1) continue;

				if (newctrl < 0x10000) {
					mutASSERT(value < 0x80);
					controller(i, newctrl, value);
				} else if (0x10000 <= newctrl && newctrl < 0x20000) {
					controller(i,midi::REGISTERED_PARAMETER_COARSE, (newctrl >> 8) & 0x7F);
					controller(i,midi::REGISTERED_PARAMETER_FINE, newctrl & 0x7F);

					controller(i,midi::DATA_ENTRY_COARSE, value >> 7 & 0x7F);
					controller(i,midi::DATA_ENTRY_FINE, value & 0x7F);
				} else if (newctrl <= 0x30000) {
					controller(i,midi::REGISTERED_PARAMETER_COARSE, (newctrl >> 8) & 0x7F);
					controller(i,midi::REGISTERED_PARAMETER_FINE, newctrl & 0x7F);

					controller(i,midi::DATA_ENTRY_COARSE, value >> 7 & 0x7F);
					controller(i,midi::DATA_ENTRY_FINE, value & 0x7F);
				}

				// sustained section contains only inactive MIDI channels
				if (newctrl == midi::HOLD_PEDAL_ON_OFF
				    && !ton_auf_kanal[i].active) {
					channel_queue.sustain_channel(i, value > 0x40);
				}
			}
	}

	/*
	void CommonMidiOutput<T,D>::Sustain(int channel, const ChannelData & cd)
	{
		mutASSERT(this->isOpen);
		for (int i = 0; i < 16; i++)
			if ( ton_auf_kanal[i].active && ton_auf_kanal[i].channel == channel ) {
				int8_t controller_value = cd.get_controller(midi::HOLD_PEDAL_ON_OFF);
				controller(i, midi::HOLD_PEDAL_ON_OFF, controller_value);
				Cd[i].set_controller(midi::HOLD_PEDAL_ON_OFF, controller_value);

				channel_queue.sustain_channel(i);
			}
	}
	*/

	template<class T, class D>
	int CommonMidiOutput<T,D>::do_GetChannel(int inkey, size_t channel, size_t id)
	{
		mutASSERT(this->isOpen);
		TRACEC;

		for (int i = 0; i < 16; i++)
			if ( ton_auf_kanal[i].active
			     && (ton_auf_kanal[i].unique_id == id)
			     && (ton_auf_kanal[i].inkey == inkey)
			     && (ton_auf_kanal[i].channel == channel) )
				return ton_auf_kanal[i].midi_channel;

		return midi::NO_CHANNEL;
	}

	template<class T, class D>
	void CommonMidiOutput<T,D>::do_SplitOut (BYTE * p, size_t n) {
		mutASSERT(this->isOpen);
		size_t pos = 0;
		size_t datalength = 0;
		uint8_t last_command = 0;
		while (pos < n) {
			uint8_t command = p[pos] & midi::TYPE_MASK;
			int channel = p[pos] & midi::CHANNEL_MASK;
			switch (command) {
			case midi::NOTE_OFF:
			case midi::NOTE_ON:
			case midi::AFTER_TOUCH:
			case midi::CONTROLLER:
			case midi::PITCH_BEND:
				if (n-pos < 3)
					return;
				if (p[pos+1] & 0x80) {
					pos++;
				} else if (p[pos+2] & 0x80) {
					pos += 2;
				} else {
					Out(channel, command, p[pos+1], p[pos+2]);
					last_command = p[pos];
					pos += 3;
					datalength = 2;
				}
				break;
			case midi::PROGRAM_CHANGE:
			case midi::CHANNEL_PRESSURE:
				if (n-pos < 2)
					return;
				if (p[pos+1] & 0x80) {
					pos++;
				} else {
					Out(channel, command, p[pos+1]);
					last_command = p[pos];
					pos += 2;
					datalength = 1;
				}
				break;

			case midi::SYSTEM:
				if (!(channel & 0x08)) datalength = 0;
				channel = -1;
				switch (p[pos]) {
				case midi::SYSEX_START:
					{
						size_t counter = pos + 1;
						while (counter < n &&
						       p[counter] != midi::SYSEX_END) {
							if (p[counter] & 0x80) {
								break;
							}
							counter++;
						}
						if (p[pos] == midi::SYSEX_END) counter++;
						// Dont interfere with sysex messages as some
						// devices require proper timing
						Out.SendSysEx(channel,&p[pos+1],p + counter);
						pos = counter;
					}
					break;
				case midi::QUARTER_FRAME:
				case midi::SONG_SELECT:
					if (n-pos < 2)
						return;
					if (p[pos+1] & 0x80) {
						pos++;
					} else {
						Out(channel, command, p[pos+1]);
						pos += 2;
					}
					break;
				case midi::SONG_POSITION:
					if (n-pos < 3)
						return;
					if (p[pos+1] & 0x80) {
						pos++;
					} else if (p[pos+2] & 0x80) {
						pos += 2;
					} else {
						Out(channel, command, p[pos+1], p[pos+2]);
						pos += 3;
					}
					break;

				case midi::SYSEX_END:
				case midi::CLOCK:
				case midi::TUNE_REQUEST:
				case midi::TICK:
				case midi::START_PLAY:
				case midi::CONTINUE_PLAY:
				case midi::STOP_PLAY:
				case midi::ACTIVE_SENSE:
 				case midi::RESET:
					Out.RawMsg(channel, p[pos]);
				default:
					pos++;
				}
			default:
				command = last_command & midi::TYPE_MASK;
				channel = last_command & midi::CHANNEL_MASK;
				switch (datalength) {
				case 2:
					if (n-pos < 2)
						return;
					if (p[pos+1] & 0x80) {
						pos++;
					} else {
						Out(channel,command,p[pos],p[pos+1]);
						pos += 2;
					}
					break;
				case 1:
					Out(channel,command,p[pos++]);
					break;
				default:
					// highest bit = 0 -> no command
					// scan for the next command
					pos++;
				}
			}

		}
	}

	template<class T, class D>
	void CommonMidiOutput<T,D>::do_Quiet(Route r, int type)
	{
		if (!this->isOpen) return;
		TRACEC;
#ifdef DEBUG
		for (int i = 0; i < 16; i++) {
			if ( ton_auf_kanal[i].active )
				mutASSERT(ton_auf_kanal[i].channel != r->get_session_id() );
					//do_NoteOff(r->GetBox(), ton_auf_kanal[i].inkey, 64, r, ton_auf_kanal[i].unique_id, false);
		}
#endif
	}

	template<class T, class D>
	void CommonMidiOutput<T,D>::do_Quiet(Route r, int type, size_t id)
	{
		if (!this->isOpen) return;
		TRACEC;

#ifdef DEBUG
		for (int i = 0; i < 16; i++) {
			if ( ton_auf_kanal[i].active && ton_auf_kanal[i].channel == r->get_session_id() )
				do_NoteOff(r->GetBox(), ton_auf_kanal[i].inkey, 64, r.get(), ton_auf_kanal[i].unique_id, false);
		}
#endif
	}

	template<class T, class D>
	void CommonMidiOutput<T,D>::do_Panic(int type)
	{
		if (!this->isOpen) return;
		TRACEC;

		for (int i = 0; i < 16; i++) {
			controller(i,type,0);
			ton_auf_kanal[i].active = false;
			ton_auf_kanal[i].inkey=0;
			ton_auf_kanal[i].unique_id=0;
			Cd[i].Reset();
		}

		channel_queue.init();

		nKeyOn = 0;

		for (int i = 0; i < GetMaxChannel(); i++) {
			controller(i,type,0);
		}
	}

	template <class D>
	void CommonMidiInput<D>::ProceedRoute(DWORD midiCode, Route route, int channel_offset)
	{
		if (!route) {
			UNREACHABLEC;
			return;
		}
		DEBUGLOG (midifile, _T("Code: %x, Active: %d, Out: %p"),midiCode,
			  route->GetActive(),
			  (void*)route->GetOutputDevice().get());
		BYTE MidiChannel = midiCode & 0x0F;
		BYTE MidiStatus  = midiCode & 0xF0;
		DEBUGLOG (midifile, _T("Status: %x"), MidiStatus);

		switch ( MidiStatus ) {

		case midi::NOTE_ON: // Note On
			if ( (midiCode & 0x7f0000) > 0 ) {
				this->NoteOn(route,
				       (midiCode >> 8) & 0xff,
				       (midiCode >> 16) & 0xff,
				       MidiChannel,
				       channel_data[MidiChannel],
				       NULL);
				break;
			}

		case midi::NOTE_OFF: // Note Off
			this->NoteOff(route,
				(midiCode >> 8) & 0xff,
				(midiCode >> 16) & 0xff,
				MidiChannel);
			break;

		case midi::PROGRAM_CHANGE: // Programm Change
			channel_data[MidiChannel].program_change((midiCode >> 8) & 0xff);
			break;

		case midi::CONTROLLER: {
			/* defaults for normal controllers */
			bool propagate = true;
			bool panic = false;
			bool reset = false;
			/* cases that need special treatment */
			switch ((midiCode >> 8) & 0xff) {
			case midi::ALL_CONTROLLERS_OFF:
				propagate = panic = reset = true;
				break;
			case midi::ALL_SOUND_OFF:
			case midi::ALL_NOTES_OFF:
			case midi::OMNI_OFF:
			case midi::OMNI_ON:
			case midi::MONO_ON:
			case midi::POLY_ON:
				propagate = false;
				panic = true;
				break;
			case midi::LOCAL_ON_OFF:
				panic = true;
				break;
			}

			if (propagate)
				channel_data[MidiChannel].set_controller((midiCode >>  8) & 0xff,
									 (midiCode >> 16) & 0xff);

			if (panic)
				this->Panic((midiCode >> 8) & 0xff,MidiChannel);

			if (reset)
				channel_data[MidiChannel].Reset();

			// always propagate as we need to store the correct result.
			route -> Controller((midiCode >>  8) & 0xff,
					    (midiCode >> 16) & 0xff,
					    MidiChannel);
		}
			break;
		case midi::KEY_PRESSURE:
#warning "implement key_pressure"
		case midi::CHANNEL_PRESSURE: // Key Pressure, Controler, Channel Pressure
#warning "implement channel_pressure"
			break;

		case midi::SYSTEM:
#warning "implement system messsages"
#if 0
			if ( route->GetOutputDevice() )
				route->GetOutputDevice()->MidiOut(pData,nData);
#else
                        ;
#endif

		}

		route->MidiAnalysis(midiCode);

	}

	template <class D>
	void CommonMidiInput<D>::ProceedRoute(const std::vector<unsigned char > * midiCode, Route route, int channel_offset)
	{
#warning "Unimplemented SysEx ProceedRoute"
		return;

		DEBUGLOG (midifile, _T("Code: %p, Active: %d, Out: %p"),
			  (void*)midiCode,
			  route->GetActive(),
			  (void*)route->GetOutputDevice().get());
		Box box = route->GetBox();
		BYTE MidiChannel = (midiCode->at(0) & 0x0F) + channel_offset;
		BYTE MidiStatus  = midiCode->at(0) & 0xF0;
		DEBUGLOG (midifile, _T("Status: %x"), MidiStatus);

		switch ( MidiStatus ) {

		case midi::NOTE_ON: // Note On
			if ( (midiCode->at(2) & 0x7f) > 0 ) {
				this->NoteOn(route,
					     midiCode->at(1),
					     midiCode->at(2),
					     MidiChannel,
					     channel_data[MidiChannel],
					     NULL);
				break;
			}

		case midi::NOTE_OFF: // Note Off
			this->NoteOff(route,
				      midiCode->at(1),
				      midiCode->at(2),
				      MidiChannel);
			break;

		case midi::PROGRAM_CHANGE: // Programm Change
			channel_data[MidiChannel].program_change(midiCode->at(1));

			break;

		case midi::CONTROLLER: {
			/* defaults for normal controllers */
			bool propagate = true;
			bool panic = false;
			bool reset = false;
			/* cases that need special treatment */
			switch (midiCode -> at(1)) {
			case midi::ALL_CONTROLLERS_OFF:
				propagate = panic = reset = true;
				break;
			case midi::ALL_SOUND_OFF:
			case midi::ALL_NOTES_OFF:
			case midi::OMNI_OFF:
			case midi::OMNI_ON:
			case midi::MONO_ON:
			case midi::POLY_ON:
				propagate = false;
				panic = true;
				break;
			case midi::LOCAL_ON_OFF:
				panic = true;
				break;
			}
			break;

			if (propagate)
				channel_data[MidiChannel].set_controller(midiCode->at(1),
							       midiCode->at(2));
			if (panic)
				this->Panic(midiCode->at(1),MidiChannel);
			if (reset)
				channel_data[MidiChannel].Reset();
			if (propagate)
				route -> Controller(midiCode->at(1),
						    midiCode->at(2),
						    MidiChannel);
		}
			break;
		case midi::KEY_PRESSURE:
#warning "implement key_pressure"
		case midi::CHANNEL_PRESSURE: // Key Pressure, Controler, Channel Pressure
#warning "implement channel_pressure"
			break;

		case midi::SYSTEM:
#warning "implement system messsages"
#if 0
			if ( route->GetOutputDevice() )
				route->GetOutputDevice()->MidiOut(pData,
                                nData);
#else
                        ;
#endif

		}

		// Midianalyse
		static const int midilength[8] = {
			3, 3, 3, 3, 2, 2, 3, 1
		};

		if ( box->get_routefile_id() >= 0 && route->GetActive() )
			for (int i = 0; i < midilength[MidiStatus >> 5]; i++) {
				box->MidiAnalysis(midiCode->at(i));
			}
	}


	/**
	 * Check which routes shall work on the midi code and forward the code.
	 *
	 * \param midiCode Code to be processed
	 * \param data     Additional data that might be necessardy
	 */// Routen testen und jenachdem entsprechend Codeverarbeitung

	template <class D>
	void CommonMidiInput<D>::Proceed(DWORD midiCode, int data, int channel_offset)
	{
		bool DidOut = 0;
		routeListType elseroutes;

		for (routeListType::iterator R = this->routes.begin();
		     R != this->routes.end(); R++)
			switch (shouldProceed(*R,midiCode, data)) {
			case ProceedYes:
				ProceedRoute(midiCode, *R, channel_offset);
				DidOut = 1;
				break;
			case ProceedNo:
				break;
			case ProceedElse:
				elseroutes.push_back(*R);
				break;
			default:
				UNREACHABLEC;
			}
		if (!DidOut) {
			for (routeListType::iterator R = elseroutes.begin();
			     R != elseroutes.end(); R++) {
				ProceedRoute(midiCode,*R, channel_offset);
			}
		}
	}

	/**
	 * Check which routes shall work on the midi code and forward the code.
	 *
	 * \param midiCode Code to be processed
	 * \param data     Additional data that might be necessardy
	 */// Routen testen und jenachdem entsprechend Codeverarbeitung

	template <class D>
	void CommonMidiInput<D>::Proceed(const std::vector<unsigned char > * midiCode, int data, int channel_offset)
	{
		bool DidOut = 0;
		routeListType elseroutes;

		for (routeListType::iterator R = this->routes.begin();
		     R != this->routes.end(); R++)
			switch (shouldProceed(*R,midiCode, data)) {
			case ProceedYes:
				ProceedRoute(midiCode, *R, channel_offset);
				DidOut = 1;
				break;
			case ProceedNo:
				break;
			case ProceedElse:
				elseroutes.push_back(*R);
				break;
			default:
				UNREACHABLEC;
			}
		if (!DidOut) {
			for (routeListType::iterator R = elseroutes.begin();
			     R != this->routes.end(); R++) {
				ProceedRoute(midiCode,*R, channel_offset);
			}
		}
	}


}


///\}
