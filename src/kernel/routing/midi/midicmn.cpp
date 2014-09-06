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
	void CommonMidiOutput<T,D>::do_Close(bool sync) {
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

		for (j = r->GetOutputFrom(); j <= r->GetOutputTo(); j++)
			if ( j != DRUMCHANNEL || !r->OutputAvoidDrumChannel() ) {
				if (!ton_auf_kanal[j].tuned_key.is_active()) {
					return channel_queue.reserve_channel(j);
				}
				AM += ton_auf_kanal[j].tuned_key.get_value();
			}

		AM /= r->GetOutputTo() + 1 - r->GetOutputFrom();
		mutint64 reference = AM;
		int free = 0;


		for ( j = r->GetOutputFrom(); j <= r->GetOutputTo(); j++ ) {
			if ( j == DRUMCHANNEL && r->OutputAvoidDrumChannel() )
				continue;

			mutint64 current
				= abs(AM - ton_auf_kanal[j].tuned_key.get_value());
			if (current < reference) {
				reference = current;
				free = j;
			}
		}

		note_off(free, ton_auf_kanal[free].outkey.pitch, 64);

		return channel_queue.reserve_channel(free);
	}

	template<class T, class D>
	void CommonMidiOutput<T,D>::do_UpdateControllers(int channel, const ChannelData & input) {

		// a simple implementation with room for improvements
		// first pass: revert changes that have been made
		for(ChannelData::controller_vector::const_iterator i
			    = Cd[channel].get_first_changed_controller(input);
		    Cd[channel].is_changed_controller(i);
		    i = Cd[channel].get_next_changed_controller(input,i)) {
			int number =  *i;

			// avoid setting controllers that are hard to undo
			switch (number) {
				// data entry helper are marked as to be set
			case midi::DATA_ENTRY_COARSE:
			case midi::DATA_ENTRY_FINE:
			case midi::DATA_BUTTON_INCREMENT:
			case midi::DATA_BUTTON_DECREMENT:
			case midi::NON_REGISTERED_PARAMETER_FINE:
			case midi::NON_REGISTERED_PARAMETER_COARSE:
			case midi::REGISTERED_PARAMETER_FINE:
			case midi::REGISTERED_PARAMETER_COARSE:
				Cd[channel].set_controller(number,-1);
				continue;
			}

			CopyController(input, Cd[channel], channel, number);
		}


		for(ChannelData::controller_vector::const_iterator i
			    = input.get_first_changed_controller(Cd[channel]);
		    input.is_changed_controller(i);
		    i = input.get_next_changed_controller(Cd[channel],i)) {
			int number =  *i;
			CopyController(input, Cd[channel], channel, number);
		}
	}

	template<class T, class D>
	void
	CommonMidiOutput<T,D>::CopyController(const ChannelData & input,
					      ChannelData & output,
					      int channel,
					      int number) {

		int value = input.get_controller(number);
		if (value < 0)
			return;
		do_Controller(output, channel, number, value);
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
			set_sound = true;
		bank_fine = input_channel_data.get_bank_fine();
		bank_coarse = input_channel_data.get_bank_coarse();

		if (bank_fine != -1 && output_data.get_bank_fine() != bank_fine) {
			set_sound = true;
			if (bank_coarse == -1)
				bank_coarse = output_data.get_bank_coarse();
		} else if (bank_coarse != -1 && output_data.get_bank_coarse() != bank_coarse) {
			set_sound = true;
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

		for(ChannelData::controller_vector::const_iterator i
			    = input_channel_data.get_first_changed_controller();
		    input_channel_data.is_changed_controller(i);
		    i = input_channel_data.get_next_changed_controller(i)) {
			switch (*i) {
			case midi::BANK_COARSE:
			case midi::BANK_FINE:
				int value = input_channel_data.get_controller(*i);
				if (value >= 0) {
					controller(channel,*i,value);
					output_data.set_controller(*i,value);
				}
			}
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

		DEBUGLOG (midiio, "box %p, inkey %d, velocity %d, id %d" ,
			  box.get(), inkey, velocity, (int)id);
		//		int free = 16, freeSus = r->OTo, freeVelocitycity = 64, freeSusVelocitycity = 64, s;
		//		DWORD p;

		BoxClass::tone freq(inkey);

		if ( box ) {
			freq = box->get_frequency(inkey);
		}

		if ( !freq.is_active() )
			return;

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

		/** \todo write a test that checks for negative controller values */
		for (const int * i = midi::get_holds();
		     *i >= 0; i++) {
			if ( output_data.get_controller(*i) !=
			     (controller_value
			      = input_channel_data.get_controller(*i)) ) {
				if (controller_value >= 0) {
					controller(channel,*i, controller_value);
					output_data.set_controller(*i, controller_value);
				}
			}
		}

		if ( note.bend != output_data.get_bend() ) {
			pitch_bend(channel,note.bend);
			output_data.set_bend(note.bend);

			// Switch off any hold pedal if necessary
			for (const int * i = midi::get_holds();
			     *i >= 0; i++) {
				if ( output_data.get_controller(*i) > midi::CONTROLLER_OFF) {
					controller(channel,
						   *i,
						   midi::CONTROLLER_OFF);
					output_data.set_controller(*i,
								   midi::CONTROLLER_OFF);
				}
			}
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
		DEBUGLOG (midiio, "box %p, key %d, velo %d, id %d" ,
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
					    || Cd[i].get_hold())
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
			      || Cd[channel].get_hold())
			     && ton_auf_kanal[channel].channel == route->get_session_id()) {

				TAK & tone = ton_auf_kanal[channel];

				DEBUGLOG(midiio,
					 ("old(hex/dec): channel = %01x/%d, Inkey = %02x/%d, key = %02x/%d, pitch = %06x/%d"),
					 channel,channel,
					 tone.inkey,tone.inkey,
					 tone.outkey.pitch,tone.outkey.pitch,
					 Cd[channel].get_bend(),Cd[channel].get_bend());

				BoxClass::tone freq
					= route->GetBox()->get_frequency(tone.inkey);

				if (freq == tone.tuned_key) continue;

				pitch_bend_type oldpb = tone.outkey;
				pitch_bend_type newpb = pitch_and_bend(freq,oldpb);

				bool SwitchTone = (newpb.pitch != oldpb.pitch);

				// evtl. Ton ausschalten
				if ( SwitchTone ) {
					/* temporary switch hold off */
					for (const int * i = midi::get_holds();
					     *i >= 0; i++) {
						if ( Cd[channel].get_controller(*i)
						     > midi::CONTROLLER_OFF ) {
							controller(channel,*i,
								   midi::CONTROLLER_OFF);
						}
					}

					note_off(channel,tone.outkey.pitch, 0);

					for (const int * i = midi::get_holds();
					     *i >= 0; i++) {
						if (Cd[channel].get_controller(*i)
						    > midi::CONTROLLER_OFF) {
							controller(channel,*i,
								   Cd[channel].get_controller(*i));
						}
					}

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
				 || Cd[i].get_hold())) {
				do_Controller(Cd[i], i, ctrl, value);
			}
	}

	template<class T, class D>
	void  CommonMidiOutput<T,D>::do_Controller(ChannelData & output,
						   int channel,
						   int ctrl,
						   int value)
	{
		mutASSERT(this->isOpen
			  || ctrl == midi::PITCH_BEND_SENSITIVITY
			  || ctrl == midi::LOCAL_ON_OFF
			  || ctrl == midi::OMNI_ON
			  || ctrl == midi::POLY_ON);

		switch (ctrl) {
		case midi::ALL_CONTROLLERS_OFF: {
#if 0
			ChannelData data;
			data.MidiReset();
			do_UpdateControllers(channel, data);
#endif
			/** \todo handle chord hold */
			/** \todo implement immediate
			    controller reset, don't
			    wait for the next tone */
		}
		case midi::ALL_SOUND_OFF:
		case midi::ALL_NOTES_OFF:
		case midi::OMNI_OFF:
		case midi::OMNI_ON:
		case midi::MONO_ON:
		case midi::POLY_ON:
			return;
		}


		int newctrl = output.get_index(ctrl);
		int old_value = output.get_controller(newctrl);

		if (output.get_controller(ctrl) == value ||
		    (ctrl == newctrl && output.get_controller(newctrl) == value)) {
			switch (ctrl) {
			case midi::DATA_ENTRY_COARSE:
			case midi::DATA_ENTRY_FINE:
			case midi::DATA_BUTTON_INCREMENT:
			case midi::DATA_BUTTON_DECREMENT:
				break;
			default:
				return;
			}
		}

		// this might change the index (e.g. RPN/NRPN coarse/fine)
		switch (ctrl) {
		case midi::LOCAL_ON_OFF:
			newctrl = ctrl;
			break;
		default:
			output.set_controller(ctrl, value);
			newctrl = output.get_index(ctrl);
			if (newctrl != ctrl)
				value = output.get_controller(newctrl);

		}

		switch (newctrl) {
		case midi::CONTROLLER_UNKNOWN:
			return;
		case midi::PITCH_BEND_SENSITIVITY:
			value = bending_range << 8;
			break;
		}

		if (newctrl < midi::FIRST_RPN) {
			mutASSERT(value < 0x80);
			controller(channel, newctrl, value);
		} else if (midi::FIRST_RPN <= newctrl
			   && newctrl <= midi::LAST_RPN) {
			OutputParameter(output,
					channel,
					RPN,
					value,
					old_value,
					newctrl);
		} else if (newctrl >= midi::FIRST_NRPN &&
			   newctrl <= midi::LAST_NRPN) {
			OutputParameter(output,
					channel,
					NRPN,
					value,
					old_value,
					newctrl);
		}

		// sustained section contains only inactive MIDI channels
		if (midi::is_hold(newctrl)
		    && !ton_auf_kanal[channel].active) {
			channel_queue.sustain_channel(channel, output.get_hold());
		}
	}

	template<class T, class D>
	void  CommonMidiOutput<T,D>::OutputParameter(ChannelData & data,
						     int channel,
						     OutputParameterType type,
						     int value,
						     int old_value,
						     int ctrl) {
		if (old_value == value)
			return;

		int minctrl, maxctrl, coarse_number, fine_number;
		switch (type) {
		case RPN:
			minctrl = midi::FIRST_RPN;
			maxctrl = midi::LAST_RPN;
			coarse_number = midi::REGISTERED_PARAMETER_COARSE;
			fine_number = midi::REGISTERED_PARAMETER_FINE;
			break;
		case NRPN:
			minctrl = midi::FIRST_NRPN;
			maxctrl = midi::LAST_NRPN;
			coarse_number = midi::NON_REGISTERED_PARAMETER_COARSE;
			fine_number = midi::NON_REGISTERED_PARAMETER_FINE;
			break;
		default:
			UNREACHABLEC;
		}
		int tmpctrl = data.get_index(midi::DATA_ENTRY_COARSE);
		if(minctrl > tmpctrl
		   ||  tmpctrl > maxctrl
		   || data.get_controller(coarse_number)
		   != ((ctrl >> 8) & 0x7f)
		   || data.get_controller(fine_number)
		   != (ctrl & 0x7f)) {
			controller(channel, coarse_number, (ctrl >> 8) & 0x7F);
			data.set_controller(coarse_number, (ctrl >> 8) & 0x7F);
			controller(channel, fine_number, ctrl & 0x7F);
			data.set_controller(fine_number, ctrl & 0x7F);
		}


		if ((old_value & (0x7F << 8)) != (value & (0x7F << 8))) {
			controller(channel, midi::DATA_ENTRY_COARSE, (value >> 8) & 0x7F);
		}
		if ((old_value & 0x7F) != (value & 0x7F)) {
			controller(channel, midi::DATA_ENTRY_FINE, value & 0x7F);
		}
		if (old_value != value)
			data.set_controller(ctrl,value);
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
	void CommonMidiOutput<T,D>::do_SplitOut (uint8_t * p, size_t n) {
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
	void CommonMidiOutput<T,D>::do_handle_event(event e) {
		switch(e->get_type()) {
		case midi::KEY_PRESSURE: {
			key_pressure_event *ev
				= static_cast<key_pressure_event *>(e.get());
			int key = ev->get_note();
			int channel = do_GetChannel(key,
						    ev->get_route_channel(),
						    ev->get_unique_id());
			if (channel != midi::NO_CHANNEL)
				key_pressure(channel,
					     key,
					     ev->get_pressure());
		}
			break;
		case midi::CONTROLLER: {
			controller_event *ev
				= static_cast<controller_event *>(e.get());
			do_Controller(ev->get_route_channel(),
				      ev->get_controller(),
				      ev->get_value(),
				      ev->get_unique_id());
		}
			break;
		case midi::CLOCK:
		case midi::TICK:
		case midi::START_PLAY:
		case midi::CONTINUE_PLAY:
		case midi::STOP_PLAY:
		case midi::RESET:
		case midi::TUNE_REQUEST:
		case midi::ACTIVE_SENSE:
		case midi::SYSTEM_UNDEFINED1:
		case midi::SYSTEM_UNDEFINED2:
		case midi::SYSEX_END:
		case midi::REALTIME_UNDEFINED:
			system(e->get_type());
			break;
		case midi::QUARTER_FRAME:{
			quarter_frame_event * ev
				= static_cast<quarter_frame_event *>(e.get());
			quarter_frame(ev->get_quarter_type(),
				      ev->get_quarter_values());
		}
			break;
		case midi::SONG_POSITION: {
			song_position_event * ev
				= static_cast<song_position_event *>(e.get());

			song_position(ev->get_position());
		}
			break;
		case midi::SONG_SELECT: {
			song_select_event * ev
				= static_cast<song_select_event *>(e.get());

			song_select(ev->get_song());
		}
			break;

		case midi::SYSEX_START: {
			sysex_event * ev
				= static_cast<sysex_event *>(e.get());

			const std::vector<unsigned char> & msg
				= ev->get_message();
			Out.SendSysEx(-1,msg.begin(),msg.end());
		}
			break;

		default:
			; // ignore;
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
				mutASSERT(ton_auf_kanal[i].channel
					  != r->get_session_id() );
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

		for (int i = 0; i < GetMaxChannel(); i++) {
			controller(i,type,0);
			ton_auf_kanal[i].active = false;
			ton_auf_kanal[i].inkey=0;
			ton_auf_kanal[i].unique_id=0;
			Cd[i].Reset();
		}

		channel_queue.init();

		nKeyOn = 0;
	}



	template <class D>
	void CommonMidiInput<D>::ProceedRoute(const std::vector<unsigned char > * midiCode, Route route, int channel_offset)
	{

		if (!route) {
			UNREACHABLEC;
			return;
		}
		DEBUGLOG (midifile, "Code: %p, Active: %d, Out: %p" ,
			  (void*)midiCode,
			  route->GetActive(),
			  (void*)route->GetOutputDevice().get());
		Box box = route->GetBox();
		unsigned char MidiChannel = (midiCode->at(0) & 0x0F) + channel_offset;
		unsigned char MidiStatus  = midiCode->at(0) & 0xF0;
		DEBUGLOG (midifile, "Status: %x" , MidiStatus);

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
				reset = true;
			case midi::ALL_SOUND_OFF:
			case midi::ALL_NOTES_OFF:
			case midi::OMNI_OFF:
			case midi::OMNI_ON:
			case midi::MONO_ON:
			case midi::POLY_ON:
			case midi::LOCAL_ON_OFF:
				propagate = false;
				panic = true;
				break;
				/*
				  case midi::CHORD_HOLD_PEDAL_ON_OFF:
				  propagate = false;
				  break;
				*/
			}

			if (propagate)
				channel_data[MidiChannel].set_controller(midiCode->at(1),
									 midiCode->at(2));
			if (panic)
				this->Panic(midiCode->at(1),MidiChannel);
			if (reset)
				channel_data[MidiChannel].MidiReset();

			event e = create_event(midiCode,
					       MidiChannel);
			e -> set_route(route);
			route -> handle_event (e);
		}
			break;
		case midi::CHANNEL_PRESSURE:
			channel_data[MidiChannel].set_controller(midi::CHANNEL_PRESSURE_VAL,
								 midiCode->at(1));
			// … and create a proper event.
		case midi::KEY_PRESSURE: {
			event e = create_event(midiCode,
					       MidiChannel);
			e -> set_route(route);
			route -> handle_event (e);
		}

			break;
		case midi::SYSTEM:
			/** \todo handle all these messages in mutabor */
			switch(midiCode->at(0)) {
			case midi::SYSTEM_UNDEFINED1:
			case midi::SYSTEM_UNDEFINED2:
			case midi::SYSEX_END:
			case midi::REALTIME_UNDEFINED:
			case midi::CLOCK:
			case midi::TICK:
			case midi::SONG_SELECT:
			case midi::SONG_POSITION:
			case midi::QUARTER_FRAME:
			case midi::START_PLAY:
			case midi::CONTINUE_PLAY:
			case midi::STOP_PLAY:
			case midi::TUNE_REQUEST:
			case midi::ACTIVE_SENSE:
				/* unimplemented or intentionally ignored */
				break;

			case midi::META:
				if (midiCode->size() == 1)
					break;
			case midi::SYSEX_START: {
				event e = create_event(midiCode,
						       MidiChannel);
				e -> set_route(route);
				route -> handle_event (e);
			}
				break;
			}
		}


		route->MidiAnalysis(midiCode);
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

		unsigned char MidiStatus  = midiCode->at(0);
		unsigned char MidiChannel = (midiCode->at(0) & 0x0F) + channel_offset;

		switch ( MidiStatus ) {
		case midi::SYSTEM_UNDEFINED1:
		case midi::SYSTEM_UNDEFINED2:
		case midi::SYSEX_END:
		case midi::REALTIME_UNDEFINED:
		case midi::ACTIVE_SENSE:
		case midi::STOP_PLAY:
		case midi::START_PLAY:
		case midi::CONTINUE_PLAY:
		case midi::CLOCK:
		case midi::TICK:
		case midi::QUARTER_FRAME:
			// song select and song position should be handled
			// in the input device
		case midi::SONG_SELECT:
		case midi::SONG_POSITION:
			return;
			/* unimplemented or intentionally ignored */
		case midi::TUNE_REQUEST: {
			event e = create_event(midiCode,
						 MidiChannel);
			OutputDeviceClass::all_handle_event(e);
		}
			return;
		case midi::META:
			if (midiCode->size() == 1) {
				// this is the position where we must reset Mutabor
				return;
			} // otherwise we pass the event to the output devices
		case midi::SYSEX_START: {
			event e = create_event(midiCode,
						 MidiChannel);
			this->outputs_handle_event(e);
		}
			return;
		}



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


}


///\}
