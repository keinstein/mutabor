/** \file               -*- C++ -*-
 ********************************************************************
 * A mutabor event class.
 *
 * Copyright:   (c) 2013 Tobias Schlemmer
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

#if (!defined(SRC_KERNEL_ROUTING_EVENT_H) && !defined(PRECOMPILE)) \
	|| (!defined(SRC_KERNEL_ROUTING_EVENT_H_PRECOMPILED))
#ifndef PRECOMPILE
#define SRC_KERNEL_ROUTING_EVENT_H
#endif

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

#include "src/kernel/Defs.h"
#include "src/kernel/routing/Device.h"
#include "boost/chrono/duration.hpp"

#ifndef SRC_KERNEL_ROUTING_EVENT_H_PRECOMPILED
#define SRC_KERNEL_ROUTING_EVENT_H_PRECOMPILED

#include <limits>

// system headers which do seldom change

namespace mutabor {
	namespace hidden {
		extern "C" {
			struct mutabor_event_type {
				int type;          //< uses midi::... constants
				size_t route_channel;
				int input_channel;
				size_t unique_id;
				union {
					struct {
						int note;
						int pressure;
					} aftertouch;
					struct {
						int number;
						int value;
					} controller;
					struct {
						int type;
						int values;
					} quarter_frame;
					struct {
						int position;
					} song_position;
					struct {
						int number;
					} song_select;
					struct {
						int number;
					} sequence;
					struct {
						int number;
					} channel;
					struct {
						int ms_per_s;
					} tempo;
					struct {
						int hour;
						int minute:8;
						int secound:8;
						int frame_100ths:16;
					} smpte;
					struct {
						int numerator;
						int denominator;
						int clocksperclick;
						int quarter_in32ths;
					} time_signature;
					struct {
						int sharps;
						bool ismajor;
					} key_signature;
					struct {
						const unsigned char * data;
					} sysex;
					struct {
						const unsigned char * data;
					} meta;
					struct {
						const char * text;
					} text;
				};
			};
		}
	}
	using hidden::mutabor_event_type;

	class event_class: protected hidden::mutabor_event_type {
	public:
		event_class() { type = midi::UNKNOWN_EVENT; }
		virtual ~event_class() {}
		virtual int get_type() { return type; }

		virtual void set_box(Box & b) {
			box = b;
		}

		virtual void set_route(Route & r) {
			route_channel = r->get_session_id();
		}

		size_t get_unique_id() {
			return unique_id;
		}

		size_t get_route_channel() {
			return route_channel;
		}
	protected:
		REFPTR_INTERFACE;
		Box box;
	};

	class key_pressure_event: public event_class {
	public:
		key_pressure_event(int channel,
				   size_t id,
				   int n,
				   int p) {
			type = midi::KEY_PRESSURE;
			input_channel = channel;
			route_channel = std::numeric_limits<size_t>::max();
			unique_id = id;
			aftertouch.note = n;
			aftertouch.pressure = p;
		}

		int get_note() { return aftertouch.note; }
		int get_pressure() { return aftertouch.pressure; }

	};

	class controller_event: public event_class {
	public:
		controller_event(int channel,
				 size_t id,
				 int ctrl,
				 int val) {
			type = midi::CONTROLLER;
			input_channel = channel;
			route_channel = std::numeric_limits<size_t>::max();
			unique_id = id;
			controller.number = ctrl;
			controller.value = val;
		}

		int get_controller() { return controller.number; }
		int get_value() { return controller.value; }

	};

	class quarter_frame_event: public event_class {
	public:
		quarter_frame_event(size_t id,
				    int type,
				    int values) {
			type = midi::QUARTER_FRAME;
			input_channel = -1;
			route_channel = std::numeric_limits<size_t>::max();
			unique_id = id;
			quarter_frame.type = type;
			quarter_frame.values = values;
		}

		int get_quarter_type()   { return quarter_frame.type; }
		int get_quarter_values() { return quarter_frame.values; }

	};

	class song_position_event: public event_class {
	public:
		song_position_event(size_t id,
				    int position) {
			type = midi::SONG_POSITION;
			input_channel = -1;
			route_channel = std::numeric_limits<size_t>::max();
			unique_id = id;
			song_position.position = position;
		}

		int get_position()   { return song_position.position; }
	};
	class song_select_event: public event_class {
	public:
		song_select_event(size_t id,
				    int number) {
			type = midi::SONG_SELECT;
			input_channel = -1;
			route_channel = std::numeric_limits<size_t>::max();
			unique_id = id;
			song_select.number = number;
		}

		int get_song()   { return song_select.number; }
	};

	template <int t>
	class system_byte_event: public event_class {
	public:
		system_byte_event (size_t id) {
			type = t;
			input_channel = -1;
			route_channel = std::numeric_limits<size_t>::max();
			unique_id = id;
		}
	};

	typedef system_byte_event<midi::SYSTEM_UNDEFINED1> system_common_midi_undef1_event;
	typedef system_byte_event<midi::SYSTEM_UNDEFINED2> system_common_midi_undef2_event;
	typedef system_byte_event<midi::TUNE_REQUEST>      tune_request_event;
	typedef system_byte_event<midi::SYSEX_END>         sysex_end_event;
	typedef system_byte_event<midi::CLOCK>             system_realtime_clock_event;
	typedef system_byte_event<midi::TICK>              system_realtime_tick_event;
	typedef system_byte_event<midi::START_PLAY>        start_play_event;
	typedef system_byte_event<midi::CONTINUE_PLAY>     continue_play_event;
	typedef system_byte_event<midi::STOP_PLAY>         stop_play_event;
	typedef system_byte_event<midi::REALTIME_UNDEFINED> system_realtime_midi_undef2;
	typedef system_byte_event<midi::ACTIVE_SENSE>      active_sense_event;
	typedef system_byte_event<midi::RESET>             reset_event;


	class sysex_event: public event_class {
	public:
		sysex_event(size_t id):msg() {
			type = midi::SYSEX_START;
			input_channel = -1;
			route_channel = std::numeric_limits<size_t>::max();
			unique_id = id;
		}

		sysex_event(size_t id,
			    const std::vector<unsigned char> & data):msg(data.begin()+1, data.end()-1) {
			type = midi::SYSEX_START;
			input_channel = -1;
			route_channel = std::numeric_limits<size_t>::max();
			unique_id = id;
			mutASSERT(data[0] == 0xF0);
			mutASSERT(*(data.rbegin()) == 0xF7);
			sysex.data = msg.data();
		}

		const std::vector<unsigned char> & get_message() { return msg; }

	protected:
		// note: sysex.data must be updated everytime msg changes.
		std::vector <unsigned char> msg;
	};

	class meta_event: public event_class {
	public:
		meta_event(size_t id,
			   const std::vector<unsigned char> & data):msg(data) {
			type = midi::UNKNOWN_META;
			input_channel = -1;
			route_channel = std::numeric_limits<size_t>::max();
			unique_id = id;
			meta.data = msg.data();
		}

		const std::vector<unsigned char> & get_message() { return msg; }

	protected:
		// note: sysex.data must be updated everytime msg changes.
		std::vector <unsigned char> msg;
	};



	class sequence_number_event: public event_class {
	public:
		sequence_number_event(size_t id, int number) {
			type = midi::SEQUENCE_NUMBER;
			input_channel = -1;
			route_channel = std::numeric_limits<size_t>::max();
			unique_id = id;
			sequence.number = number;
		}
	};


	template <int t>
	class generic_text_event: public event_class {
	public:
		generic_text_event(size_t id,
				   const unsigned char * s,
				   int len) {
			type = t;
			input_channel = -1;
			route_channel = std::numeric_limits<size_t>::max();
			unique_id = id;
			str.resize(len);
			std::string::iterator i = str.begin();
			while (len--) {
				*(i++) = *(s++);
			}
			text.text = str.c_str();
		}

		const std::string & get_text() { return str; }
	protected:
		std::string str;
	};

	typedef generic_text_event<midi::EVENT_TEXT> text_event;
	typedef generic_text_event<midi::COPYRIGHT_NOTICE> copyright_event;
	typedef generic_text_event<midi::SEQUENCE_NAME> sequence_name_event;
	typedef generic_text_event<midi::TRACK_NAME> track_name_event;
	typedef generic_text_event<midi::INSTRUMENT_NAME> instrument_name_event;
	typedef generic_text_event<midi::LYRIC> lyric_event;
	typedef generic_text_event<midi::MARKER> marker_event;
	typedef generic_text_event<midi::CUE_POINT> cue_point_event;

	class channel_select_event: public event_class {
	public:
		channel_select_event(size_t id, int number) {
			type = midi::CHANNEL_SELECT;
			input_channel = -1;
			route_channel = std::numeric_limits<size_t>::max();
			unique_id = id;
			channel.number = number;
		}
	};

	typedef system_byte_event<midi::END_OF_TRACK> end_track_event;

	class set_tempo_event: public event_class {
	public:
		set_tempo_event(size_t id, int number) {
			type = midi::SET_TEMPO;
			input_channel = -1;
			route_channel = std::numeric_limits<size_t>::max();
			unique_id = id;
			tempo.ms_per_s = number;
		}
		boost::chrono::microseconds get_tempo() { return boost::chrono::microseconds(tempo.ms_per_s); }
	};


	class smpte_event: public event_class {
	public:
		smpte_event(size_t id,
			    int hour,
			    uint8_t minute,
			    uint8_t secound,
			    uint8_t frame,
			    uint8_t frame_hundredths) {
			type = midi::SMPTE_OFFSET;
			input_channel = -1;
			route_channel = std::numeric_limits<size_t>::max();
			unique_id = id;
			smpte.hour = hour;
			smpte.minute = minute;
			smpte.secound = secound;
			smpte.frame_100ths
				= 100 * frame + frame_hundredths;
		}
		int get_hour() { return smpte.hour; }
		uint8_t get_minute() { return smpte.minute; }
		uint8_t get_secound() { return smpte.secound; }
		int get_frame_100ths() { return smpte.frame_100ths; }
	};


	class time_signature_event: public event_class {
	public:
		time_signature_event(size_t id,
				     int denominator,
				     int numerator,
				     int clocksperclick,
				     int quarter_in32ths) {
			type = midi::TIME_SIGNATURE;
			input_channel = -1;
			route_channel = std::numeric_limits<size_t>::max();
			unique_id = id;
			time_signature.numerator = numerator;
			time_signature.denominator = denominator;
			time_signature.clocksperclick = clocksperclick;
			time_signature.quarter_in32ths = quarter_in32ths;
		}
		int get_numerator() { return time_signature.numerator; }
		int get_denominator() { return time_signature.denominator; }
		int get_clocks_per_click() { return time_signature.clocksperclick; }
		int get_quarter_in_32ths() { return time_signature.quarter_in32ths; }
	};

	class key_signature_event: public event_class {
	public:
		key_signature_event(size_t id,
				     int sharps,
				     bool ismajor) {
			type = midi::KEY_SIGNATURE;
			input_channel = -1;
			route_channel = std::numeric_limits<size_t>::max();
			unique_id = id;
			key_signature.sharps = sharps;
			key_signature.ismajor = ismajor;
		}
		int get_sharps() { return key_signature.sharps; }
		int get_ismajor() { return key_signature.ismajor; }
	};

	class sequencer_specific_meta_event: public event_class {
	public:
		sequencer_specific_meta_event(size_t id,
			    const std::vector<unsigned char> & data):msg(data) {
			type = midi::SEQUENCER_SPECIFIC;
			input_channel = -1;
			route_channel = std::numeric_limits<size_t>::max();
			unique_id = id;
			meta.data = msg.data();
		}

		const std::vector<unsigned char> & get_message() { return msg; }

	protected:
		// note: sysex.data must be updated everytime msg changes.
		std::vector <unsigned char> msg;
	};


	inline event_class * create_meta_event(const std::vector<unsigned char> &code,
					      size_t unique_id) {
		if (code.size() < 2) {
			return new meta_event(unique_id, code);
		}


		switch (code.at(1)) {
		case midi::META_SEQUENCE_NUMBER: {
			if (code.size() >= 4) {
				return new sequence_number_event(unique_id,
								 (code.at(2) << 8) & code.at(3));
			}
		}
			break;
		case midi::META_EVENT_TEXT: {
			if (code.size() >= 3)
				return new text_event(unique_id,
						      &(code.at(2)),
						      code.size()-2);
		}
			break;
		case midi::META_COPYRIGHT_NOTICE: {
			if (code.size() >= 3)
				return new copyright_event(unique_id,
							   &(code.at(2)),
							   code.size()-2);
		}
			break;
		case midi::META_SEQUENCE_NAME: {
			if (code.size() >= 3) {
				// Sequcence and track are something different in MIDI.
				// Nevertheless they share the same id.
				if (false)
					return new sequence_name_event(unique_id,
								       &(code.at(2)),
								       code.size()-2);
				else
					return new track_name_event(unique_id,
								    &(code.at(2)),
								    code.size()-2);
			}
		}
			break;

		case midi::META_INSTRUMENT_NAME: {
			if (code.size() >= 3)
				return new instrument_name_event(unique_id,
								 &(code.at(2)),
								 code.size()-2);
		}
			break;
		case midi::META_LYRIC: {
			if (code.size() >= 3)
				return new lyric_event(unique_id,
						       &(code.at(2)),
						       code.size()-2);
		}
			break;
		case midi::META_MARKER: {
			if (code.size() >= 3)
				return new marker_event(unique_id,
							&(code.at(2)),
							code.size()-2);
		}
			break;
		case midi::META_CUE_POINT: {
			if (code.size() >= 3)
				return new cue_point_event(unique_id,
							   &(code.at(2)),
							   code.size()-2);
		}
			break;
		case midi::META_CHANNEL_PREFIX: {
			if (code.size() >= 3)
				return new channel_select_event(unique_id,
								(code.at(2)));
		}
			break;
		case midi::META_END_OF_TRACK: {
			return new end_track_event(unique_id);
		}
			break;
		case midi::META_SET_TEMPO: {
			if (code.size() >= 5)
				return new set_tempo_event(unique_id,
							   (code.at(2) << 16) | (code.at(3) << 8) | code.at(4));
		}
			break;
		case midi::META_SMPTE_OFFSET: {
			if (code.size() >= 7)
				return new smpte_event(unique_id,
						       code.at(2),
						       code.at(3),
						       code.at(4),
						       code.at(5),
						       code.at(6));
		}
			break;
		case midi::META_TIME_SIGNATURE: {
			if (code.size() >= 6)
				return new time_signature_event(unique_id,
								code.at(2),
								1 << code.at(3),
								code.at(4),
								code.at(5));
		}
			break;
		case midi::META_KEY_SIGNATURE: {
			if (code.size() >= 3)
				return new key_signature_event(unique_id,
							       code.at(2),
							       ! code.at(3));
		}
			break;
		case midi::META_SEQUENCER_SPECIFIC:
			return new sequencer_specific_meta_event(unique_id, code);
		default:
			return new meta_event(unique_id, code);
		}
		return new meta_event(unique_id, code);
	}

	inline event_class * create_system_event(const std::vector<unsigned char> &code,
						 size_t unique_id) {
		switch (code.at(0)) {
		case midi::SYSEX_START:
			if (code.size() < 2) {
				std::vector<unsigned char> tmp;
				return new sysex_event(unique_id);
			}
			return new sysex_event (unique_id,code);
		case midi::QUARTER_FRAME:
			if (code.size() > 1)
				return new quarter_frame_event(unique_id,
							       (code.at(1) & 0x70) >> 4,
							       code.at(1) & 0x0F);
			break;
		case midi::SONG_POSITION:
			if (code.size() > 2)
				return new song_position_event(unique_id,
							       code.at(1)
							       | (code . at(2) << 7));
			break;
		case midi::SONG_SELECT:
			if (code.size() > 1)
				return new song_select_event(unique_id,
							     code.at(1));
			break;
		case midi::SYSTEM_UNDEFINED1:
			return new system_common_midi_undef1_event(unique_id);
		case midi::SYSTEM_UNDEFINED2:
			return new system_common_midi_undef2_event(unique_id);
		case midi::TUNE_REQUEST:
			return new tune_request_event(unique_id);
		case midi::SYSEX_END:
			return new sysex_end_event(unique_id);
		case midi::CLOCK:
			return new system_realtime_clock_event(unique_id);
		case midi::TICK:
			return new system_realtime_tick_event(unique_id);
		case midi::START_PLAY:
			return new start_play_event(unique_id);
		case midi::CONTINUE_PLAY:
			return new continue_play_event(unique_id);
		case midi::STOP_PLAY:
			return new stop_play_event(unique_id);
		case midi::REALTIME_UNDEFINED:
			return new system_realtime_midi_undef2(unique_id);
		case midi::ACTIVE_SENSE:
			return new active_sense_event(unique_id);
		case midi::META:
			if (code.size() > 1)
				return create_meta_event(code,unique_id);
			else
				return new reset_event(unique_id);
		}
		return NULL;

	}

	inline event_class * create_event(const std::vector<unsigned char> &code,
				   size_t unique_id) {
		unsigned char midiStatus = code.at(0) & 0xF0;
		/* invalid midi messsages are handled by the default branch */
		switch (midiStatus) {
		case midi::SYSTEM:
			return create_system_event(code,unique_id);
		case midi::CHANNEL_PRESSURE:
			if (code.size() > 1)
				return new controller_event(code.at(0) & 0x0f,
							    unique_id,
							    midi::CHANNEL_PRESSURE_VAL,
							    code.at(1));
			FALLTHROUGH;
		case midi::KEY_PRESSURE:
			if (code.size() > 2)
				return new key_pressure_event(code.at(0) & 0x0f,
							      unique_id,
							      code.at(1),
							      code.at(2));
			FALLTHROUGH;
		case midi::CONTROLLER:
			if (code.size() > 2)
				return new controller_event(code.at(0) & 0x0f,
							    unique_id,
							    code.at(1),
							    code.at(2));
			FALLTHROUGH;
		default:
			return new event_class;
		}
	}

	typedef boost::intrusive_ptr<event_class> event;

}


#endif // precompiled
#endif // header loaded


///\}
