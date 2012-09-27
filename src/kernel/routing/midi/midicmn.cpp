/** \file               -*- C++ -*-
 ********************************************************************
 * Common midi functunos
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
 * \addtogroup templates
 * \{
 ********************************************************************/
// availlable groups: GUI, route, kernel, muwx, debug, docview

/* we guard a little bit complicated to ensure the references are set right
 */

#include "src/kernel/Defs.h"
#include "src/kernel/routing/midi/midicmn.h"
#include "src/kernel/MidiKern.h"
#include "src/kernel/Execute.h"


#ifdef __BORLANDC__
    #pragma hdrstop
#endif


namespace mutabor {
	template<class T, class D>
	bool CommonMidiOutput<T,D>::Open() {
		int i;
		mutASSERT(!this->isOpen);
		DEBUGLOG (midiio, _T(""));


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

		retval = base::Open();
		if (!retval) {
			Out.Close();
			return false;
		}

		for (i = this->GetMinChannel(); i <= this->GetMaxChannel(); i++) {
			pitch_bend(i,0);
			controller(i,midi::LOCAL_ON_OFF, midi::CONTROLLER_OFF );
			controller(i,midi::OMNI_ON, midi::CONTROLLER_OFF );
			controller(i,midi::POLY_ON_OFF, midi::CONTROLLER_OFF );
		}

		this->isOpen = true;
		return true;

	}

	template<class T, class D>
	void CommonMidiOutput<T,D>::Close() {
		mutASSERT(this->isOpen);
		DEBUGLOG (midiio, _T(""));

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
			return channel >= route->OFrom 
				&& channel <= route->OTo 
				&& (!route->ONoDrum 
				    || channel != DRUMCHANNEL);
		}
		
		bool check() {
			return route->OFrom <= route->OTo;
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

		for (j = r->OFrom; j <= r->OTo; j++)
			if ( j != DRUMCHANNEL || !r->ONoDrum )
				AM += ton_auf_kanal[j].tuned_key;

		AM /= r->OTo + 1 - r->OFrom;

		for ( j = r->OFrom; j <= r->OTo; j++ )
			if ( j != DRUMCHANNEL || !r->ONoDrum )
				if ( abs(AM - (ton_auf_kanal[j].tuned_key)) 
				     < abs(AM - (ton_auf_kanal[free].tuned_key) ))
					free = j;


		note_off(free, ton_auf_kanal[free].outkey.pitch, 64);

		return channel_queue.reserve_channel(free);
	}

	template<class T, class D>
	void CommonMidiOutput<T,D>::UpdateControllers(int channel, const ChannelData & input) {
		// a simple implementation with room for improvements
		for(ChannelData::controller_vector::const_iterator i = input.get_first_changed_controller(Cd[channel]);
		    input.is_changed_controller(i);
		    i = input.get_next_changed_controller(Cd[channel],i)) {
			int number =  *i;
			int value =   input.get_controller(number);
			mutASSERT(number < 0x80);
			mutASSERT(value < 0x80);
			Cd[channel].set_controller(number,value);
			controller(channel,number,value);
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
	void CommonMidiOutput<T,D>::NoteOn(mutabor_box_type * box, 
				      int inkey, 
				      int velocity, 
				      RouteClass * r, 
				      size_t id, 
				      const ChannelData & input_channel_data)
	{
#warning "Fix gmn box"
		mutASSERT(this->isOpen);
		if (!ChannelFilter(r).check()) {
			UNREACHABLEC;
			return;
		}

		DEBUGLOG (midiio, _T("box %d, inkey %d, velocity %d, id %d"),
			  box, inkey, velocity, id);
//		int free = 16, freeSus = r->OTo, freeVelocitycity = 64, freeSusVelocitycity = 64, s;
//		DWORD p;
		long freq;

		if ( box == NULL ) {
			freq = ((long)inkey) << 24;
		} else
			freq = GET_FREQ (inkey, box->tonesystem);

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
		int sound;
 
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
		ton_auf_kanal[channel].channel = r->GetId();
		ton_auf_kanal[channel].midi_channel = channel;
		ton_auf_kanal[channel].unique_id = id;
		ton_auf_kanal[channel].tuned_key = freq;

		note_on(channel, note.pitch, velocity);

		UpdateControllers(channel, input_channel_data);
	}

	template<class T, class D>
	void CommonMidiOutput<T,D>::NoteOff(mutabor_box_type * box, 
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
			  box, inkey, velo, id);


		/* This schouldn't be necessary
		if ( !velo ) //3 ?? notwendig?
			velo = 64;
		*/


		/* Note: though unique_id can be used to memorize
		   certain keys, this is an optional feature. e.g. in
		   MIDI mode two tones which have the same pitch can
		   not easily distinguished. */


		for (int i = r->OFrom; i <= r->OTo; i++)
			if ( i != DRUMCHANNEL || !r->ONoDrum )
				if ( ton_auf_kanal[i].active 
				     && ton_auf_kanal[i].inkey == inkey
				     && ton_auf_kanal[i].unique_id == id 
				     && ton_auf_kanal[i].channel == r->GetId() ) {

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
	void CommonMidiOutput<T,D>::NotesCorrect(RouteClass * route)
	{
		mutASSERT(this->isOpen);
		DEBUGLOG (midiio, _T(""));
		if (!route || route == NULL) {
			UNREACHABLEC;
			return;
		}

		for (int channel = 0; channel < 16; channel++)
			if ( (ton_auf_kanal[channel].active 
			      || Cd[channel].get_controller(midi::HOLD_PEDAL_ON_OFF)>0 ) 
			     && ton_auf_kanal[channel].channel == route->GetId()) {

				TAK & tone = ton_auf_kanal[channel];
				
				DEBUGLOG(midiio,
					 _T("old(hex/dec): channel = %01x/%d, Inkey = %02x/%d, key = %02x/%d, pitch = %06x/%d"), 
					 channel,channel,
					 tone.inkey,tone.inkey, 
					 tone.outkey.pitch,tone.outkey.pitch,
					 Cd[channel].get_bend(),Cd[channel].get_bend());

				long freq = GET_FREQ(tone.inkey, mut_box[route->GetBox()].tonesystem);
				
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
	void  CommonMidiOutput<T,D>::Controller(int mutabor_channel, int ctrl, int value)
	{
		mutASSERT(ctrl < 0x80);
		mutASSERT(value < 0x80);
		mutASSERT(this->isOpen);
		for (int i = 0; i < 16; i++)
			if ( ton_auf_kanal[i].channel == mutabor_channel
			     && (ton_auf_kanal[i].active 
				 || Cd[i].get_controller(midi::HOLD_PEDAL_ON_OFF) > 0x40)) {
				controller(i, ctrl, value);
				Cd[i].set_controller(ctrl, value);
				
				// sustained section contains only inactive MIDI channels
				if (ctrl == midi::HOLD_PEDAL_ON_OFF
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
	int CommonMidiOutput<T,D>::GetChannel(int inkey, int channel, int id)
	{
		mutASSERT(this->isOpen);
		DEBUGLOG (midiio, _T(""));

		for (int i = 0; i < 16; i++)
			if ( ton_auf_kanal[i].active 
			     && (ton_auf_kanal[i].unique_id == id)
			     && (ton_auf_kanal[i].inkey == inkey) 
			     && (ton_auf_kanal[i].channel == channel) )
				return ton_auf_kanal[i].midi_channel;

		return -1;
	}

	template<class T, class D>
	void CommonMidiOutput<T,D>::SplitOut (BYTE * p, size_t n) {
		mutASSERT(this->isOpen);
		size_t pos = 0;
		size_t datalength;
		uint8_t last_command;
		while (pos < n) {
			uint8_t command = p[pos] & midi::TYPE_MASK;
			uint8_t channel = p[pos] & midi::CHANNEL_MASK;
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
					size_t counter = pos;
					while (counter < n && p[counter] 
					       != midi::SYSEX_END) {
						if (p[counter] & 0x80) {
							break;
						}
						counter++;
					}
					if (p[pos] == midi::SYSEX_END) counter++;
					Out.SendSysEx(channel,&p[pos+1],counter-pos-1);
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
	void CommonMidiOutput<T,D>::Quiet(RouteClass * r)
	{
		if (!this->isOpen) return;
		DEBUGLOG (midiio, _T(""));

		for (int i = 0; i < 16; i++) {
			if ( ton_auf_kanal[i].active && ton_auf_kanal[i].channel == r->GetId() )
				NoteOff(&mut_box[r->GetBox()], ton_auf_kanal[i].inkey, 64, r, ton_auf_kanal[i].unique_id, false);
		}
	}

	template<class T, class D>
	void CommonMidiOutput<T,D>::Panic()
	{
		if (!this->isOpen) return;
		DEBUGLOG (midiio, _T(""));

		for (int i = 0; i < 16; i++) {
			controller(i,midi::ALL_NOTES_OFF,0);
			ton_auf_kanal[i].active = false;
			ton_auf_kanal[i].inkey=0;
			ton_auf_kanal[i].unique_id=0;
			Cd[i].Reset();
		}

		channel_queue.init();
		
		nKeyOn = 0;
	}


}


///\}
