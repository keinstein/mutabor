/** \file               -*- C++ -*-
 ********************************************************************
 * Common Midi device base
 *
 * Copyright:   (c) 2012 Tobias Schlemmer
 * \author  Tobias Schlemmer <keinstein@users.sourceforge.net>
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

#if (!defined(ROUTING_MIDICMN_H) && !defined(PRECOMPILE)) \
	|| (!defined(ROUTING_MIDICMN_H_PRECOMPILED))
#ifndef PRECOMPILE
#define ROUTING_MIDICMN_H
#endif

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

#include "src/kernel/Defs.h"
#include "src/kernel/routing/Device.h"
#include "src/kernel/routing/Box.h"
//#include "src/kernel/MidiKern.h"

#ifndef ROUTING_MIDICMN_H_PRECOMPILED
#define ROUTING_MIDICMN_H_PRECOMPILED

// system headers which do seldom change
#include <vector>
#include <cmath>

#define DEFAULT_BENDING_RANGE 2l

namespace mutabor {

	template <class T=char, unsigned int count=16>
	class channel_queue_template : public std::vector<T> {
	public:
		typedef std::vector<T> basetype;
		typedef typename basetype::iterator iterator;
		typedef typename basetype::const_iterator const_iterator;


		/* longest used .. joungest used  .. longest free  .. joungest free .. longest sustained .. joungest sustained */

		channel_queue_template(T size = count):basetype(size),
						      first_free(basetype::begin()),
						      last_sustained(basetype::end()){
			init();
		}


		void init () {
			first_free = this->begin();
			last_sustained = this->end();

			for (T i = 0 ; i < this->size(); i++) {
				(*this)[i] = i;
			}
		}

		iterator find_channel(T nr) {
			return std::find(this->begin(),this->end(),nr);
		}

		const_iterator find_channel(T nr) const {
			return std::find(this->begin(),this->end(),nr);
		}


		template<class F>
		iterator find_matching_channel  (iterator start, F filter) {
			if (start == this->end()) {
				DEBUGLOG (midiio, "No channel found" );
				return start;
			}
			iterator actual = start;
			while (actual != this->end() && (!(filter((int)(*actual))))) {
				DEBUGLOG (midiio, "Not using Channel %d" ,(int)(*actual));
				++actual;
			}
			DEBUGLOG (midiio, "Using Channel %d" ,(actual != this->end()?(int)(*actual):(int)-1));
			return actual;
		}


		/**
		 * Reserves the first free channel.
		 * That is usually the longest unused one.
		 *
		 * \note This can change if certain Channels are
		 * registered to be sustained. In that case they are
		 * postponed until no channels are availlable anymore.
		 *
		 * Sustaining is *not* handled by this class.
		 *
		 * \return number of the first free channel
		 * \retval end() if no free or sustained channel can be found
		 */
		template<class F>
		const_iterator reserve_channel_filtered (F filter) {
			iterator actual = find_matching_channel(first_free, filter);
			return reserve_channel (actual);
		}

		iterator reserve_channel(iterator actual) {
			if (actual != this->end()) {
				if (first_free <= actual) {
					move_to_front(actual,first_free);
					actual = first_free;
					++first_free;
					if (first_free > last_sustained) {
						++last_sustained;
					}
					mutASSERT(first_free == this->end() || first_free <= last_sustained);
				} else {
					// we are rearranging used channels
					// thus first_free doesn't change
					move_to_end(actual, first_free);
					actual = first_free - 1;
				}
			}
			return actual;
		}

		/**
		 * Forcibly reserve given channel regardless of its state.
		 * This function is used if there are no free channels left
		 * and the system frees a channel depending on semantic data.
		 *
		 * \param nr Channel to be reserved
		 *
		 * \return iterator to the channel.
		 */
		iterator reserve_channel(T nr) {
			return reserve_channel(find_channel(nr));
		}

		/**
		 * Find and free a channel.
		 * \note the channel must not be freed already.
		 *
		 * \param nr Channel to bee freed.
		 */
		void free_channel (T nr) {
			free_channel(find_channel(nr));
		}

		/**
		 * Mark a channel to be free.
		 *
		 * \param current iterator pointing to the channel to be regarded as free.
		 */
		void free_channel (iterator current) {
			if (current == this->end()) {
				UNREACHABLEC;
				return;
			}
			if (last_sustained <= current) {
				move_to_front(current,last_sustained);
				++last_sustained;
				return;
			}
			if (first_free <= current) {
				UNREACHABLEC;
				return;
			}
			move_to_end(current,last_sustained);
			--first_free;
		}

		/**
		 * Find and sustain a channel.
		 * \note the channel must not be sustaind already.
		 *
		 * \param nr Channel to bee sustaind.
		 */
		void sustain_channel (T nr, bool sustain = true) {
			if (sustain)
				sustain_channel(find_channel(nr));
			else unsustain_channel(find_channel(nr));
		}

		/**
		 * Mark a channel to be sustained.
		 *
		 * \param current iterator pointing to the channel to be regarded as sustained.
		 */
		iterator sustain_channel (iterator current) {
			if (last_sustained <= current) return current;
			if (first_free <= current) {
				// includes last_sustained <= current
				UNREACHABLEC;
				return this->end();
			}
			move_to_end(current,this->end());
			--last_sustained;
			if (current < first_free) --first_free;
			return this->end() - 1;
		}
		/**
		 * Unmark channel to be sustained;
		 *
		 * \param current iterator pointing to the channel to be regarded as sustained.
		 */
		void unsustain_channel (iterator current) {
			free_channel(current);
		}

		iterator  get_first_free() { return first_free; }
		iterator  get_last_sustained() { return last_sustained; }

	protected:
		iterator first_free;
		iterator last_sustained;

		/**
		 * Move current pointer to the end of a range.
		 *
		 * \param current current position
		 * \param end position after the end position of the element.
		 */
		void move_to_end (iterator current, iterator end) {
			mutASSERT(current < end);
			if (current == this->end()) {
				UNREACHABLEC;
				return;
			}
			std::rotate(current, current+1, end);
		}

		/**
		 * Move current pointer to the beginning of a range.
		 *
		 * \param current current position
		 * \param final position where the element should be moved to
		 */
		void move_to_front (iterator current, iterator final) {
			mutASSERT(final <= current);
			if (current == this->end()) {
				UNREACHABLEC;
				return;
			}
			std::rotate(final, current, current+1);
		}

	};
	typedef channel_queue_template<unsigned char,16> channel_queue_type;

	class pitch_bend_type  {
	public:
		int pitch;
		int bend;

		pitch_bend_type & operator -= (const pitch_bend_type & other) {
			pitch -= other.pitch;
			bend -= other.bend;
			return *this;
		}

		bool operator == (pitch_bend_type & other) {
			return pitch == other.pitch && bend == other.bend;
		}
	};

	typedef struct TAK
	{
		bool active;      //< is this tone active or free?
		int inkey;        //< internal key id. provided by input device
		int velocity;     //< attack velocity or note volume
		pitch_bend_type outkey;
		size_t channel;      //< route that broght the note to this device
		int midi_channel; //< MIDI channel (unsused)
		size_t unique_id; //< unique id defined by input device
		BoxClass::tone tuned_key;   //< tuned key
	} TonAufKanal;




	/**
	 * A simple MIDI output provider describing the API and providing simple means for debugging.
	 *
	 */
	class DebugMidiOutputProvider {
	public:

		// Flawfinder: ignore
		DebugMidiOutputProvider(Device * d):device(d), data(),open(false) {}


		/**
		 * Opens the output.
		 *
		 *
		 * \retval true on success.
		 * \retval false if an error
		 * occurred. In that case assume that everything below
		 * this function has been restored to closed state.
		 */
		bool Open() {
			// Flawfinder: ignore
			mutASSERT(!open);
			open = true;
			WriteTime();
			data += "Opened...\n";
			return true;
		}


		/**
		 * Opens the output.
		 *
		 *
		 * \retval true on success.
		 * \retval false if an error
		 * occurred. In that case assume that everything below
		 * this function has been restored to closed state.
		 */
		void Close() {
			// Flawfinder: ignore
			mutASSERT(open);
			open = false;
			WriteTime();
			data += "...closed.\n";
		}

		/**
		 * Outputs a three-byte message merging the channel into the data.
		 *
		 * \param channel channel to which data shall be sent
		 *        to. How channels are split into tracks or
		 *        subdevices is managed by the OutputProvider
		 * \param byte1 1st byte
		 * \param byte2 2nd byte
		 * \param byte3 3rd byte
		 */
		DebugMidiOutputProvider & operator() (int channel,
						      uint8_t byte1,
						      uint8_t byte2,
						      uint8_t byte3) {
			// Flawfinder: ignore
			mutASSERT(open);
			byte1 |= channel & midi::CHANNEL_MASK;
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
		DebugMidiOutputProvider & RawMsg (int channel,
						  uint8_t byte1,
						  uint8_t byte2,
						  uint8_t byte3) {
			// Flawfinder: ignore
			mutASSERT(open);
			std::string tmp;
			WriteTime();
			tmp = (boost::format("%3d: %02x %02x %02x")
			       % channel % (int) byte1 % (int) byte2 % (int)byte3).str();
			DEBUGLOG (midiio, "MIDI OUT to %s" ,tmp.c_str());
			data += tmp + ("\n");
			return *this;
		}

		/**
		 * Outputs a two-byte message merging the channel into the message.
		 *
		 * \param channel channel to which data shall be sent
		 *        to. How channels are split into tracks or
		 *        subdevices is managed by the OutputProvider
		 * \param byte1 1st byte
		 * \param byte2 2nd byte
		 */
		DebugMidiOutputProvider & operator() (int channel,
						      uint8_t byte1,
						      uint8_t byte2) {
			// Flawfinder: ignore
			mutASSERT(open);
			byte1 |= channel & midi::CHANNEL_MASK;
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
		DebugMidiOutputProvider & RawMsg (int channel,
						  uint8_t byte1,
						  uint8_t byte2) {
			// Flawfinder: ignore
			mutASSERT(open);
			std::string tmp;
			WriteTime();
			tmp = (boost::format("%3d: %02x %02x")
			       % channel % (int) byte1 % (int)byte2).str();
			DEBUGLOG (midiio, "MIDI OUT to %s" ,tmp.c_str());
			data += tmp + "\n";
			return * this;
		}

		/**
		 * Outputs a one-byte message.
		 *
		 * \param channel channel to which data shall be sent
		 *        to. How channels are split into tracks or
		 *        subdevices is managed by the OutputProvider
		 * \param byte1 byte
		 */
		DebugMidiOutputProvider & RawMsg (int channel, uint8_t byte1) {
			// channel is used in multi track environments
			// Flawfinder: ignore
			mutASSERT(open);
			std::string tmp;
			WriteTime();
			tmp = (boost::format("%3d: %02x") % channel % (int)byte1).str();
			DEBUGLOG (midiio, "MIDI OUT to %s" ,tmp.c_str());
			data += tmp + "\n";
			return * this;
		}



		/**
		 * Outputs a System Exclusive Message.
		 *
		 * \param channel channel to which data shall be sent
		 *        to. How channels are split into tracks or
		 *        subdevices is managed by the OutputProvider
		 * \param message byte array containang the message
		 * \param count number of bytes to be sent
		 */
		template < class i>
		DebugMidiOutputProvider & SendSysEx(int channel, i from, i to){
			// channel is used in multi track environments
			// Flawfinder: ignore
			mutASSERT(open);
			if ((*from) & midi::STARTBYTE_MASK) {
				UNREACHABLEC;
				return *this;
			}
			WriteTime();
			std::string tmp = boost::str(boost::format("%3d: SysEx")% channel);
			while ( from != to)
				tmp += boost::str(boost::format(" %02x") % (int)(*(from++)));

			DEBUGLOG (midiio, "MIDI OUT to %s" ,tmp.c_str());
			data += tmp + (" End\n");
			return * this;
		}

		operator std::string () const { return data; }
		void ClearData() { data = ""; }
	protected:
		Device * device;
		/* the data fields not not necessary for and output provider */
		std::string data;
		// Flawfinder: ignore
		bool open;

		/** Put the time into the output provider.
		 *
		 *
		 */
		void WriteTime();
	};


	template<class T, class D>
	class CommonMidiOutput:public D {
	public:
		class TooHighPitchBend:public std::exception {};
		class TooSmallPitchBend:public std::exception {};

		typedef T midiprovider;
		typedef D base;
		typedef CommonMidiOutput<T,D> thistype;

		enum bank_type {
			lsb_first = 0,
			lsb_only,
			msb_only,
			msb_first
		};

		channel_queue_type::const_iterator EmergencyFindChannel(RouteClass * r);

		/**
		 * Update the controller data of a channel. A
		 * smplified characterization would be: copy channnel
		 * data.
		 *
		 * \param channel MIDI output channel whose controller
		 * data should be updated
		 * \param input_channel_data reference ChannelData objecet.
		 */
		void UpdateControllers(int channel,
				       const ChannelData & input_channel_data) {
			ScopedLock<thistype> lock(*this);
			do_UpdateControllers(channel,input_channel_data);
		}

		/**
		 * Copies the program change and bank data from the input channel to the output
		 * choannel and issues the corresponding bank change and prgoram change messages.
		 *
		 * \param input_channel_data input to be copied from
		 * \param output_data output to be copied to
		 * \param channel MIDI channel to output the data to
		 */
		void CopyProgramChange(const ChannelData & input_channel_data,
				       ChannelData & output_data,
				       int channel);



//		midiprovider & GetProvider () { return Out(); }
		void SetBendingRange(int br) {
			ScopedLock<thistype> lock(*this);
			bending_range = br;
			if (!this->isOpen) return;
			int max = GetMaxChannel();
			for (int i = GetMinChannel() ; i < max ; i++) {
				do_SendBendingRange(i);
			}
		}
		int GetBendingRange() const { return bending_range; }

		virtual int GetMaxChannel() const = 0;
		virtual int GetMinChannel() const = 0;

	protected:
		CommonMidiOutput(int b):base(),
					Out(this),
					bending_range(b),
					bank_mode(msb_first),
					channel_queue(),
					nKeyOn(0) {}

		virtual ~CommonMidiOutput() {}

		bool do_Open();
		void do_Close(bool sync=false);

		/**
		 * Really send the beginning of a sounding note.
		 *
		 * \param box   Mutabor box that contains the tuning information
		 * \param taste input key from file or keyboard
		 * \param velo  key press velocity
		 * \param r     route that has been used to transmit the note
		 * \param id    an additional number that is used to make the note unique
		 * \param input_channel_data current device settings (Controllers, Sound, etc.)
		 *
		 * \sa \ref OutputDeviceClass::NoteOn, \ref OutputDeviceClass::NoteOff
		 *
		 * \todo currently portamento and legato switches may not work as
		 * the device does not know which notes from different channels should
		 * be combined
		 *
		 */

		void do_NoteOn(Box box,
			    int inkey,
			    int velocity,
			    RouteClass * r,
			    size_t id,
			    const ChannelData & input_channel_data);

		void do_NoteOff(Box box,
			     int inkey,
			     int velo,
			     RouteClass * r,
			     size_t id,
			     bool is_note_on /* = false */
			);
		void do_UpdateTones(RouteClass * route);
		void do_Controller(size_t mutabor_channel,
				   int controller,
				   int value,
				   size_t id);
		void  do_Controller(ChannelData & output,
				    int channel,
				    int ctrl,
				    int value);

//		void Sustain(int channel, const ChannelData & cd);
		int do_GetChannel(int inkey, size_t channel, size_t id);
		/**
		 * Act or send data according to a given evnt type. The event types are
		 * defined in \ref event.h.
		 *
		 * \note This function acts only on those events that
		 *       are handled equally in all MIDI
		 *       devices. Other events (e.g. META events)
		 *       should be handled in the corresponding subclass.
		 *
		 * \param e event to be acted on.
		 */
		void do_handle_event(event e);
		void do_SplitOut (uint8_t * p, size_t n);
		void do_Quiet(Route r, int type);
		void do_Quiet(Route r, int type, size_t id);
		void do_Panic(int type);
		void do_SendBendingRange(int channel) {
			Cd[channel].set_controller(midi::PITCH_BEND_SENSITIVITY,
						   bending_range);
			controller(channel,midi::REGISTERED_PARAMETER_COARSE,
				   (midi::PITCH_BEND_SENSITIVITY >> 8) & 0x7F);
			controller(channel,midi::REGISTERED_PARAMETER_FINE,
				   midi::PITCH_BEND_SENSITIVITY & 0x7F);
			controller(channel,midi::DATA_ENTRY_COARSE, bending_range);
			controller(channel,midi::DATA_ENTRY_FINE, 0);
		}

		/**
		 * Gis output is unimplemented.
		 * Ignore GIS tokens.
		 */
		void do_Gis(GisToken*, char) {}
		void do_MidiOut(uint8_t *p, size_t n) {
			do_SplitOut(p,n);
		}
		void do_MidiOut(mutabor::Box mutUNUSED(box),
				midi_string data) {
			do_SplitOut(data.data(),data.size());
		}
		void do_UpdateControllers(int channel, const ChannelData & input_channel_data);
		/**
		 * Copy a single controller value and output it apropriately
		 *
		 * \param input   Source
		 * \param output  Destination
		 * \param channel MIDI channel
		 * \param ctrl    controller to be copied
		 */
		void CopyController(const ChannelData & input,
				    ChannelData & output,
				    int channel,
				    int number);

		enum OutputParameterType {
			RPN,
			NRPN
		};

		/**
		 * Outputs a registered or non registered parameter
		 * according to the state of a given \ref ChannelData
		 * object.
		 *
		 * \param data cannel data holding the output mirror
		 * state
		 * \param channel channel the parameter shall be
		 * sent to
		 * \param type type: RPN or NRPN
		 * \param value value: The new value that shall be
		 * transmitted
		 * \param old_value the value that shall be considered
		 * to be the current state of the output device. This
		 * may be different from the current state of data to
		 * allow preprocessing in the calling function
		 * \param ctrl     Controller that shall be transmitted
		 * \param newctrl  New value of the controller for internal use.
		 */
		void OutputParameter(ChannelData & data,
				     int channel,
				     OutputParameterType type,
				     int value,
				     int old_value,
				     int ctrl);

		/**
		 * Sends a pitchbend signal.
		 *
		 * \param channel Channel on which the data shall be sent.
		 * \param value   Data to be sent range has already been honoured Center is at 0.
		 */
		void pitch_bend(int channel, int value) {
			const int pitch_bend_border = 0x40 << 7;
			if (value >= pitch_bend_border)
				BOOST_THROW_EXCEPTION(TooHighPitchBend());
			if (value < -(pitch_bend_border))
				BOOST_THROW_EXCEPTION(TooSmallPitchBend());

			int pb = value + pitch_bend_border;
			DEBUGLOG2(midiio,("MIDI_PITCH(%x/%d,%x/%d) = %x/%d (%x/%d, %x/%d, %x/%d)"),
				  channel,channel,
				  value,value,
				  pb,pb,
				  (int)midi::PITCH_BEND + channel,(int)midi::PITCH_BEND + channel,
				  pb & 0x7f, pb & 0x7f,
				  (0x40 + (pb >> 7) ) & 0x7f,
				  (0x40 + (pb >> 7) ) & 0x7f );
			Out (channel, midi::PITCH_BEND,
			     pb & 0x7f, (pb >> 7) & 0x7f);
		}

		void program_change(int channel, int sound, int lsb, int msb) {
			DEBUGLOG (midiio, "ch: %d, pr: %d, lsb: %d, msb: %d, send mode: %d" , channel, sound, lsb, msb, bank_mode);
			/* if only one bank byte has been set we correct it in case we send
			   msb or lsb only. Otherwise we do not have access to the internal state
			   of the devie and leave it alone with the setting the user provided */
			// check for valid msb/lsb combinations
			if (!(lsb & 0x80)) {
				if (!(msb & 0x80)) {
					switch (bank_mode) {
					case lsb_first:
						controller(channel,midi::BANK_FINE,lsb);
						FALLTHROUGH;
					case msb_only:
						controller(channel,midi::BANK_COARSE,msb);
						break;
					case msb_first:
						controller(channel,midi::BANK_COARSE,msb);
						FALLTHROUGH;
					case lsb_only:
						controller(channel,midi::BANK_FINE,lsb);
						break;
					default:
						UNREACHABLEC;
					}
				} else {
					controller(channel,(bank_mode == msb_only?
							    midi::BANK_COARSE:
							    midi::BANK_FINE),lsb);
				}
			} else {
				if (!(msb & 0x80)) {
					controller(channel,(bank_mode == lsb_only?
							    midi::BANK_FINE:
							    midi::BANK_COARSE),lsb);
				}
			}

			if ( sound != -1 )
				Out(channel,midi::PROGRAM_CHANGE, sound);
		}

		void controller(int channel, int controller, int value) {
			mutASSERT(0 <= value && value < 0x80);
			DEBUGLOG (midiio, "ch: %d, ctrl: %d, value: %d" ,channel, controller, value);
			switch (controller) {
			case midi::CHANNEL_PRESSURE_VAL: {
				Out(channel,midi::CHANNEL_PRESSURE, value);
				break;
			}
			default:
				if (controller >= 0 && controller < 0x80) {
					Out(channel,midi::CONTROLLER, controller, value);
				}
			}
		}

		void note_on(int channel, int pitch, int velocity) {
			Out(channel,midi::NOTE_ON, pitch, velocity);
		}

		void note_off(int channel, int pitch, int velocity) {
			Out(channel,midi::NOTE_OFF, pitch, velocity);
		}

		void key_pressure(int channel, int key, int pressure) {
			Out(channel,midi::KEY_PRESSURE, key, pressure);
		}

		/**
		 * Send a single byte system message.
		 *
		 * \param type Type of the message;
		 */
		void system(int type) {
			Out.RawMsg(-1,type);
		}

		/**
		 * Send a quarter frame event.
		 *
		 * \param type   quarter frame type (may set only the lowest 3 bits)
		 * \param values qarter frame value (may set only the lowest 4 bits)
		 */
		void quarter_frame(int type, int values) {
			if ((type & 0x07) == type
			    && (values & 0x0f) == values) {
				Out.RawMsg(midi::QUARTER_FRAME,
					   (type << 4) | values);
			}
		}

		/**
		 * Send a song positon event.
		 *
		 * \param position Position to be sent. Must be
		 * between 0x0000 and 0x3fff.
		 */
		void song_position(int position) {
			if (position & ~((int) 0x3fff))
				return;
			Out.RawMsg(midi::SONG_POSITION,
				   position & 0x7f,
				   position >> 7);
		}

		void song_select(int song) {
			if (song & ~((int) 0x7f))
				return;
			Out.RawMsg(midi::SONG_SELECT, song);
		}

		long fix_bend(long bend) {
			long retval = bend / bending_range;

			// Midi Pitch bend has 13 bit precision
			// we have 24 bit precision
			// 0x1000000 / 0x2000
			constexpr long divisor = BoxClass::tone::get_semitone() / 0x2000;
			constexpr long divisor2 = divisor >> 1;
			// in order to get correct rounding we add
			// half of the

			long tmp = retval % divisor;
			retval = retval / divisor;
			if (tmp > divisor2)
				retval += 1;
			else if (tmp < -divisor2)
				retval -= 1;

			/* A naive approach assumes that pitch bend ranges
			   from -0x2000 to 0x2000. Actually the range lasts
			   from -0x2000 to 0x1fff.

			   The difference is one step or
			   (pitch_bend_range / 0x1fff). For 12HT pitch bend range
			   this means about 0.3ct.

			   Note: The auditory system has about 4000 receptors,
			   which proviedes an average distance of 3ct. But they
			   are not equally distributed and the amplification
			   is not linear, which makes difference tones to be real,
			   detectable frequencies.

			   In absense of the standard (it's at work) I
			   implemented the complicate correct formula above.
			*/

			// must solve the equation 0x1 00 00 00 / divisor + 0x 3f ff = 0x 7f ff
			return retval;
		}

		pitch_bend_type pitch_and_bend(const BoxClass::tone & tuned_note) {
			pitch_bend_type data;
			data.bend = tuned_note.get_bend();
			data.pitch = tuned_note.get_pitch();
			if (data.bend >= tuned_note.get_quartertone()) {
				data.pitch++;
				data.bend -= tuned_note.get_semitone();
			}

			// must solve the equation 0x 80 00 00 / divisor + 0x 40 00 = 0x 1 00 00
			data.bend = fix_bend(data.bend); //we can't use >> because of negative values

			return  data;
		}

		pitch_bend_type pitch_and_bend(const BoxClass::tone & tuned_note,
					       const pitch_bend_type & old) {

			long interval_centre = old.pitch;
			long delta = tuned_note.get_pitch() - interval_centre;
			long new_bend = tuned_note.get_bend() + (delta * tuned_note.get_semitone());

			long interval_range = bending_range * tuned_note.get_semitone();

			if (std::abs(new_bend) > interval_range)
				return pitch_and_bend(tuned_note);

			pitch_bend_type data;
			data.pitch = interval_centre;
			data.bend = fix_bend(new_bend);

			return  data;
		}





	protected:
		midiprovider Out;
		int bending_range;
		bank_type bank_mode;
		ChannelData Cd[16];
		/*  replace KeyData by channel_queue */
		channel_queue_type channel_queue;
		TonAufKanal ton_auf_kanal[16];
		int nKeyOn;

		CommonMidiOutput():base(),
				   Out(this),
				   bending_range (2),
				   bank_mode(lsb_first),
				   nKeyOn(0) { }

		CommonMidiOutput(std::string name,
				 int id = -1,
				 int bendingRange = 2)
			: base(name, id),
			  Out(this),
			  bending_range (bendingRange),
			  bank_mode(lsb_first),
			  nKeyOn(0)
			{
				TRACEC;
			}
	};


	template<class D>
	class CommonMidiInput:public D {
	public:
		typedef D parenttype;
		void Proceed(const std::vector<unsigned char > &midiCode,
			     int data =0,
			     size_t channel_offset = 0);

		virtual ChannelData & GetChannelData(const InputDeviceClass::current_keys_type::entry & key) const {
			return const_cast<ChannelData &>(channel_data[key.unique_id]);
		}
		using D::SetName;

	protected:

		CommonMidiInput(const std::string name = "",
				MutaborModeType mode = DeviceStop,
				int id = -1):parenttype(name,mode,id) {}

		virtual ~CommonMidiInput() {}

		std::vector<ChannelData> channel_data;
		enum proceed_bool {ProceedYes,ProceedNo,ProceedElse};

		static size_t makeChannel(const std::vector<unsigned char > &midiCode, size_t channel_offset) {
			return (midiCode[0] & 0x0F) + channel_offset;
		}

		void ProceedRoute(const std::vector<unsigned char > &midiCode, Route route, int channel_offset);
		virtual proceed_bool shouldProceed(Route R,
						   const std::vector<unsigned char > &midiCode,
						   int data =0) = 0;
	};

}




#endif // precompiled
#endif // header loaded


///\}
