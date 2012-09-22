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
#include "src/kernel/routing/midi/midicmn.cpp"
#include "src/kernel/MidiKern.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif


// everything should be already in midicmn.cpp
#if 0
namespace mutabor {
	bool CommonMidiOutput::Open() {
		int i;
		mutASSERT(!isOpen);
		DEBUGLOG (midiio, _T(""));


		for (i = 0; i < 16; i++) {
			Cd[i].Reset();
			ton_auf_kanal[i].active = false;
			ton_auf_kanal[i].inkey = -1;
			ton_auf_kanal[i].outkey = -1;
			ton_auf_kanal[i].channel = 0;
			ton_auf_kanal[i].midi_channel = 0;
			ton_auf_kanal[i].unique_id = 0;
		}
		
		channel_queue.init();

		nKeyOn = 0;

		bool retval = provider.Open();
		if (!retval) return false;

		bool retval = base::Open();
		if (!retval) return false;

		for (i = GetMinChannel(); i <= GetMaxChannel(); i++) {
			pitch_bend(i,0);
			controller(i,LOCAL_ON_OFF, CONTROLLER_OFF );
			controller(i,OMNI_ON_OFF, CONTROLLER_OFF );
			controller(i,POLY_ON_OFF, CONTROLLER_OFF );
		}

		isOpen = true;
		return true;

	}

	void CommonMidiOutput::Close() {
		mutASSERT(isOpen);
		DEBUGLOG (midiio, _T(""));

		for (channel_queue_type::iterator i = channel_queue.begin();
		     i != channel_queue.get_first_free();
		     i++) {
			note_off(*i,ton_auf_kanal[*i].outkey,64);
		}

		provider.Close();
		isOpen = false;
	}


	class ChannelFilter {
	public:
		ChannelFilter(RouteClass * r):route(r) {}
		operator () (int channel) {
			return channel <= r->OFrom && channel >= r->OTo &&
				(!r->ONoDrum || channel != DRUMCHANNEL);
		}
		
		bool check() {
			return r->OFrom <= r->OTo;
		}
	protected:
		RouteClass * route;
	};


	channel_queue_type::iterator CommonMidiOutput::EmergencyFindChannel(route * r) {
		// "mittelste Taste weglassen"
		mutint64 AM = 0; // arithmetisches Mittel der Tasten
		int j;

		for (j = r->OFrom; j <= r->OTo; j++)
			if ( j != DRUMCHANNEL || !r->ONoDrum )
				AM += ton_auf_kanal[j].tunedkey;

		AM /= r->OTo + 1 - r->OFrom;

		for ( j = r->OFrom; j <= r->OTo; j++ )
			if ( j != DRUMCHANNEL || !r->ONoDrum )
				if ( abs(AM - ton_auf_kanal[j].tunedkey) < abs(AM - ton_auf_kanal[free].tunedkey) )
					free = j;


		note_off(free, ton_auf_kanal[free].outkey, 64);

		return channel_queue.reserve_channel(free);
	}

	void CommonMidiOutput::UpdateControllers(int channel, ChannelData & input_channel_data) {
#pragma message "implement UpdateControllers"
	}
		
#pragma message "Fix gmn box"

	void CommonMidiOutput::CopyProgramChange(const ChannelData & input_channel_data,
						   ChannelData & output_data) {
		int sound, bank_fine, bank_coarse;
		bool set_sound = false;
		sound = input_channel_data.Sound;
		if (sound != -1 && output_data.Sound != sound)
			set_sound =true;
		bank_fine = input_channel_data.bank_fine;
		bank_coarse = input_channel_data.bank_coarse;

		if (bank_fine != -1 && output_data.bank_fine != bank_fine) {
			set_sound =true;
			if (bank_coarse == -1) 
				bank_coarse = output_data.bank_coarse;
		} else if (bank_coarse != -1 && output_data.bank_coarse != bank_coarse) {
			set_sound =true;
			if (bank_fine == -1) 
				bank_fine = output_data.bank_fine;
		}
		if (set_sound !! sound == -1) 
			sound = output_data.Sound;

		if (set_sound) {
			program_change(channel,sound,bank_fine,bank_coarse);
			output_data.Sound = sound;
			output_data.bank_coarse = bank_coarse;
			output_data.bank_fine = bank_fine;
		}	      
	}

	void CommonMidiOutput::NoteOn(mutabor_box_type * box, 
				      int inkey, 
				      int velocity, 
				      RouteClass * r, 
				      size_t id, 
				      const ChannelData & input_channel_data)
	{
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

		channel_queue_type::iterator pos = 
			channel_queue.reserve_channel(ChannelFilter(r));
		if (pos == channel_queue.end()) {
			pos = EmergencyFindChannel(r,cd);
		} else {
			nKeyOn++;
		}

		int channel = *pos;
		ChannelData & output_data = Cd[channel];
 		pitch_bend_type note = pitch_and_bend(freq);
		int8_t controller_value;
		int sound;
 
		if ( note.bend != output_data.bend ) {
			pitch_bend(channel,note.bend);
			output_data.bend = note.bend;

			// Switch off sustain if necessary
			if ( output_data.controller[HOLD_PEDAL_ON_OFF]) {
				controller(channel,
					   HOLD_PEDAL_ON_OFF,
					   CONTROLLER_OFF);
				output_data.set_controller(HOLD_PEDAL_ON_OFF,
							   CONTROLLER_OFF);
			}
		}

		if ( output_data.controller[HOLD_PEDAL_ON_OFF] !=
		     (controller_value = input_channel_data.controller[HOLD_PEDAL_ON_OFF]) ) {
			controller(channel,
				   HOLD_PEDAL_ON_OFF,
				   controller_value);
			output_data.set_controller(HOLD_PEDAL_ON_OFF,
						   controller_value);
		}

		CopyProgramChange(input_channel_data, output_data);

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

	void CommonMidiOutput::NoteOff(mutabor_box_type * box, 
				       int inkey, 
				       int velo, 
				       RouteClass * r, 
				       size_t id,
				       bool is_note_on /* = false */
		)
	{
		if (!r || r == NULL) return;
		DEBUGLOG (midiio, _T("box %p, key %d, velo %d, id %d"),
			  box, inkey, velo, id);


		/* This schouldn't be necessary
		if ( !velo ) //3 ?? notwendig?
			velo = 64;
		*/

		for (int i = r->OFrom; i <= r->OTo; i++)
			if ( i != DRUMCHANNEL || !r->ONoDrum )
				if ( ton_auf_kanal[i].active 
				     && ton_auf_kanal[i].unique_id == id 
				     && ton_auf_kanal[i].channel == r->GetId() ) {

					
					DEBUGLOG(midiio,_T("%s"), makekeydirstring (KeyDir, ton_auf_kanal).c_str());

					ton_auf_kanal[i].active = false;

					/* note on is used on some devices as special note on 
					   while on others it means note off */

					if (is_note_on) 
						note_on(i, ton_auf_kanal[i].outkey, 0);
					else
						note_off(i, ton_auf_kanal[i].outkey, velo);
						

					if (is_note_on || Cd[i].controller[HOLD_PEDAL_ON_OFF])
						channel_queue.sustain_channel(i);
					else
						channel_queue.free_channel(i);
					nKeyOn--;
					break;
				}
		DEBUGLOG(midiio,_T("%s"), makekeydirstring (KeyDir, ton_auf_kanal).c_str());
	}

	void CommonMidiOutput::NotesCorrect(RouteClass * route)
	{
		DEBUGLOG (midiio, _T(""));
		if (!route || route == NULL) {
			UNREACHABLEC;
			return;
		}

		for (int channel = 0; channel < 16; channel++)
			if ( (ton_auf_kanal[channel].active || Cd[channel].controller[HOLD_PEDAL_ON_OFF] ) 
			     && ton_auf_kanal[channel].channel == route->id) {

				TAK & tone = tone;
				
				DEBUGLOG(midiio,
					 _T("old(hex/dec): channel = %01x/%d, Inkey = %02x/%d, key = %02x/%d, pitch = %06x/%d"), 
					 channel,channel,
					 tone.inkey,tone.inkey, 
					 tone.outkey.pitch,tone.outkey.pitch,
					 Cd[channel].Pitch,Cd[channel].Pitch);

				long freq = GET_FREQ(tone.inkey, mut_box[route->GetBox()].tonesystem);
				
				if (freq == tone.tuned_key) continue;

				pitch_bend_type oldpb = tone.outkey;
				pitch_bend_type newpb = pitch_and_bend(freq,oldpb);

				bool SwitchTone = (newpb.pitch != oldpb.pitch);

				// evtl. Ton ausschalten
				if ( SwitchTone ) {
					bool sustain = Cd[channel].controller[HOLD_PEDAL_ON_OFF];
					if ( sustain ) {
						/* temporary sowith hold off */
						controller(channel,HOLD_PEDAL_ON_OFF,0);
					}
					
					note_off(channel,tone.outkey.pitch, 0);

					if (sustain) 
						controller(channel,HOLD_PEDAL_ON_OFF,
							Cd[channel].controller[HOLD_PEDAL_ON_OFF]);

				} else if (newpb.bend == oldpb.bend) continue;

				Cd[channel].bend = newpb.bend;
				tone.outkey = newpb;
				pitch_bend(channel, newpb.bend);

				// evtl. Ton einschalten
				if ( SwitchTone ) {
					note_on(channel, tone.outkey.pitch, tone.velocity);
				}
			}
	}
	

	void CommonMidiOutput::Sustain(int channel, const ChannelData & cd)
	{
		for (int i = 0; i < 16; i++)
			if ( ton_auf_kanal[i].active && ton_auf_kanal[i].channel == channel ) {
				DEBUGLOG(midiio,_T("%s"), makekeydirstring (KeyDir, ton_auf_kanal).c_str());
				int8_t controller_value = cd.controller[HOLD_PEDAL_ON_OFF];
				controller(i, HOLD_PEDAL_ON_OFF, controller_value);
				Cd[i].controller[HOLD_PEDAL_ON_OFF] = controller_value;
				
				channel_queue.sustain_channel(i);
			}
	}

	int CommonMidiOutput::GetChannel(int inkey, int channel)
	{
		DEBUGLOG (midiio, _T(""));

		for (int i = 0; i < 16; i++)
			if ( ton_auf_kanal[i].active 
			     && (ton_auf_kanal[i].channel == channel)
			     && (ton_auf_kanal[i].inkey == inkey) )
				return ton_auf_kanal[i].midi_channel;

		return -1;
	}

	void CommonMidiOutput::SplitOut (BYTE * p, size_t n) {
		size_t pos = 0;
		size_t datalength;
		uint_8 last_command;
		while (pos < n) {
			uint8_t command = p[pos] & TYPE_MASK;
			uint8_t channel = p[pos] & CHANNEL_MASK;
			switch (command) {
			NOTE_OFF:
			NOTE_ON:
			AFTER_TOUCH:
			CONTROLLER:
			PITCH_BEND:
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
					datalenghth = 2;
				}
				break;
			PROGRAM_CHANGE:
			CHANNEL_PRESSURE:
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
				
			SYSTEM:
				if (!(channel & 0x08)) datalength = 0;
				switch (p[pos]) {
				SYSEX_START:
					size_t counter = 0;
					while (counter < n && p[counter] != SYSEX_END) {
						if (p[counter] & 0x80) {
							break;
						}
						counter++;
					}
					if (p[pos] == SYSEX_END) counter++;
					Out(&p[pos],counter-pos-1);
					pos = counter;
					break;
				QUARTER_FRAME:
				SONG_SELECT:
					if (n-pos < 2) 
						return;
					if (p[pos+1] & 0x80) {
						pos++;
					} else {
						Out(channel, command, p[pos+1]);
						pos += 2; 
					}
					break;
				SONG_POSITION:
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

				SYSEX_END:
				CLOCK:
				TUNE_REQUEST:
				TICK:
				START_PLAY:
				CONTINUE_PLAY:
				STOP_PLAY:
				ACTIVE_SENSE:
 				RESET:
					Out(p[pos]);
				default:
					pos++
				}
			default: 
				command = last_command & TYPE_MASK;
				channel = last_command & CHANNEL_MASK;
				switch (datalength) {
				2: 
					if (n-pos < 2) 
						return;
					if (p[pos+1] & 0x80) {
						pos++;
					} else {
						Out(channel,command,p[pos],p[pos+1]);
						pos += 2;
					}
					break;
				1: 
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
	
	void CommonMidiOutput::Quiet(RouteClass * r)
	{
		DEBUGLOG (midiio, _T(""));

		for (int i = 0; i < 16; i++) {
			if ( ton_auf_kanal[i].active && ton_auf_kanal[i].channel == r->GetId() )
				NoteOff(r->GetBox(), ton_auf_kanal[i].inkey, 64, r, ton_auf_kanal[i].unique_id);
		}
	}

	void CommonMidiOutput::Panic()
	{
		DEBUGLOG (midiio, _T(""));

		for (int i = 0; i < 16; i++) {
			controller(i,ALL_NOTES_OFF,0);
			ton_auf_kanal[i].active = false;
			ton_auf_kanal[i].inkey=0;
			ton_auf_kanal[i].unique_id=0;
			Cd[i].Sound = 0;
			Cd[i].Sustain = 0;
		}

		channel_queue.init();
		
		nKeyOn = 0;
	}


}
#endif

///\}
