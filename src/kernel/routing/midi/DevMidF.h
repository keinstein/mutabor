/** \file  -*- C++ -*-
 ********************************************************************
 * Device providing MIDI files.
 *
 * Copyright:   (c) 1998-2011 TU Dresden
 * \author
 * R.Krauße,
 * Tobias Schlemmer <keinstein@users.sourceforge.net>
 * \date
 * $Date: 2011/11/02 14:31:58 $
 * \version $Revision: 1.8 $
 * \license GPL
 *
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
 *
 ********************************************************************
 * \addtogroup route
 * \{
 ********************************************************************/

/* we guard a little bit complicated to ensure the references are set right
 */

#if (!defined(MU32_ROUTING_MIDI_DEVMIDF_H) && !defined(PRECOMPILE)) \
	|| (!defined(MU32_ROUTING_MIDI_DEVMIDF_H_PRECOMPILED))
#ifndef PRECOMPILE
#define MU32_ROUTING_MIDI_DEVMIDF_H
#endif

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

#include "src/kernel/Defs.h"
#include "src/kernel/routing/CommonFileDevice.h"
#include "src/kernel/routing/midi/midicmn.h"
#include "src/kernel/routing/midi/midicmn.h"


#ifndef MU32_ROUTING_MIDI_DEVMIDF_H_PRECOMPILED
#define MU32_ROUTING_MIDI_DEVMIDF_H_PRECOMPILED

// system headers which do seldom change

#include <fstream>
#include <boost/intrusive_ptr.hpp>
#include <boost/unordered_map.hpp>


namespace mutabor {

// Track ------------------------------------------------------------

	class TrackData: public std::vector<uint8_t>
	{
	public:
		typedef std::vector<uint8_t> base;

		class delta_length_error:public std::range_error {
		public:
			explicit delta_length_error (const std::string& what_arg):
				range_error(what_arg) {}
		};
		class invalid_status:public std::range_error {
		public:
			explicit invalid_status (const std::string& what_arg):
				range_error(what_arg) {}
		};
		class message_length_error:public std::range_error {
		public:
			explicit message_length_error (const std::string& what_arg):
				range_error(what_arg) {}
		};
		class wrong_id:public std::range_error {
		public:
			explicit wrong_id (const std::string& what_arg):
				range_error(what_arg) {}
		};

		TrackData(size_t count = 128): base() {
			reserve(count);
		}

		TrackData(const TrackData & o):base(o) {}

		~TrackData() {}

		void WriteDelta(timing_params::ticktype delta) {
			WriteNumber(delta);
		}

		void check_capacity(size_t s) {
			if (capacity() < s + size()) {
				// exponential memory allocation
				// leads (including copyiing) to
				// amortized complexity  O(n)
				// wher n is the number of written bytes
				reserve(capacity()+capacity());
			}
		}

		//uint32_t ReadInt();
		// base ReadMessage();


		template <typename T>
		void WriteNumber(T count) {
			if (!midi::is_valid_length(count))
				BOOST_THROW_EXCEPTION(delta_length_error(_mutN("trying to write number > 0x0FFFFFFF")));
			uint8_t tmp[4];
			int i = 1;
			tmp[0] = count & 0x7f;
			count >>= 7;
			while (count && i < 4) {
				tmp[i++] = (count & 0x7f ) | 0x80;
				count >>= 7;
			}
			check_capacity(i);
			while (i)
				push_back(tmp[--i]);
		}

		void MidiOut(uint8_t c1,
			     uint8_t c2,
			     uint8_t c3) {
			check_capacity(3);
			push_back(c1);
			push_back(c2);
			push_back(c3);
		}

		void MidiOut(uint8_t c1,
			     uint8_t c2) {
			check_capacity(2);
			push_back(c1);
			push_back(c2);
		}

		void MidiOut(uint8_t c1) {
			check_capacity(1);
			push_back(c1);
		}

		template <class i>
		void WriteLongChunk(i from, i to, size_t offset = 0) {
			size_t count = (to - from) + offset;

			size_t c = count+offset;
			check_capacity(c+4);
			WriteNumber(c);
			while (from != to)
 				push_back(*(from++));
		}

		void StartMeta(uint8_t type) {
			if (type & midi::STARTBYTE_MASK) {
				UNREACHABLEC;
				return;
			}
			check_capacity(2);
			push_back(midi::META);
			push_back(type);
		}

		template <class i>
		void SendMeta (uint8_t type,
			       i from, i to) {
			StartMeta(type);
			WriteLongChunk(from,to,0);
		}

		template <class i>
		void SendSysEx (bool running_sysex, i from, i to) {
			if ((*from) & midi::STARTBYTE_MASK) {
				UNREACHABLEC;
				return;
			}
			SendSysExCont(running_sysex, from,to,1);
			check_capacity(1);
			push_back(midi::SYSEX_END);
		}

		template <class i>
		void SendSysExCont (bool running_sysex,
				    i from, i to,
				    size_t offset = 0)
		{
			check_capacity(to-from + offset);
			push_back(running_sysex?midi::SYSEX_END:midi::SYSEX_START);
			WriteLongChunk(from, to, offset);
		}


		void FixSysEx(int sysex_id) {
			check_capacity(6);
			WriteNumber(0);
			push_back(midi::SYSEX_END);
			WriteNumber(4);
			if (sysex_id > 0x10000) {
				push_back(0);
				push_back((sysex_id >> 8) & 0x7F);
				push_back((sysex_id) & 0x7F);
			} else {
				push_back((sysex_id) & 0x7F);
				push_back(0);
				push_back(0);
			}
			push_back(midi::SYSEX_END);
		}

		void SendTempo(long quarter_duration) {
			 uint8_t data[] = {
				 ((uint8_t)((quarter_duration >> 16 ) & 0xFF)),
				 ((uint8_t)((quarter_duration >> 8 ) & 0xFF)),
				 ((uint8_t)(quarter_duration & 0xFF))
			 };
			 SendMeta(midi::META_SET_TEMPO, data, data+3);
		}


		void SendTimeSignature(uint8_t numerator,
				       uint8_t denominator_exponent,
				       uint8_t metronome_click_clocks,
				       uint8_t quarter_duration_in_32th) {
			const uint8_t data[] = { numerator,
						 denominator_exponent,
						 metronome_click_clocks,
						 quarter_duration_in_32th
			};
			SendMeta(midi::META_TIME_SIGNATURE, data, data+4);
		}



#ifdef DEFINE_VECTOR_DATA
		base::value_type * data() { return &(this->at(0)); }
#endif
	};

	class Track: public TrackData {
	private:
		REFPTR_INTERFACE;

	public:
		typedef TrackData base;

		struct status_flags {
			enum flags {
				nothing_sent = 0x00,
				delta_sent = 0x01,
				tempo_sent = 0x02,
				time_signature_sent = 0x04
			};


			status_flags(flags f):data(f) {}
			int operator = (flags f) {
				return data = f;
			}
			int operator |= (flags f) {
				return data |= f;
			}
			int operator & (flags f) const {
				return data & f;
			}

			status_flags & operator = (const status_flags & f) {
				data = f.data;
				return *this;
			}
			status_flags & operator |= (const status_flags & f) {
				data |= f.data;
				return *this;
			}
			status_flags operator & (const status_flags & f) const {
				return status_flags(data & f.data);
			}
		protected:
			unsigned int data;

			status_flags (int f): data(f) {}
		};

		using TrackData::delta_length_error;
		using TrackData::invalid_status;
		using TrackData::message_length_error;
		using TrackData::wrong_id;
		Track(): base(100),
			 intrusive_ptr_refcount(0),
			 flags(status_flags::nothing_sent),
			 Time(),
			 timing(),
			 position(0),
			 current_delta(InputDeviceClass::NO_DELTA(),timing),
			 remaining_delta(0),
			 running_status(0),
			 running_sysex(false),
			 sysex_id() {
			DEBUGLOG (midifile, "%s" , (this)->c_str().c_str());

		}


		Track(const Track & o):base(o),
				       intrusive_ptr_refcount(0),
				       flags(status_flags::nothing_sent),
				       Time(o.Time),
				       timing(o.timing),
				       position(o.position),
				       current_delta(o.current_delta.count(),timing),
				       remaining_delta(o.remaining_delta),
				       running_status(0),
				       running_sysex(false),
				       sysex_id() {
		}

		Track(timing_params p): base(100),
					intrusive_ptr_refcount(0),
					flags(status_flags::nothing_sent),
					Time(),
					timing(p),
					position(0),
					current_delta(InputDeviceClass::NO_DELTA(),timing),
					remaining_delta(0),
					running_status(0),
					running_sysex(false),
					sysex_id() {
			DEBUGLOG (midifile, "%s" , (this->c_str()));
		}


		~Track() {}

		size_t GetPosition() { return position; }
		void ResetPosition(size_t p, bool resettiming = false) {
			position = p;
			running_status = 0;
			running_sysex = false;
			if (resettiming) {
				timing.set_quarter_duration(microseconds(500000)); //  120 bpm
				Time = CurrentTimer::time_point();
				current_delta.set_zero();
				remaining_delta = microseconds::zero();
			}
			DEBUGLOG (midifile, "%s" , (this->c_str()));
 		}

		void ResetDelta() {
			DEBUGLOG (midifile, "resetting remaining delta to 0" );
			remaining_delta = microseconds::zero();
		}

		void Reset() {
			clear();
			ResetPosition(0,true);
		}

		microseconds GetDelta() { return remaining_delta; }
		microseconds ReadDelta();
		microseconds PassDelta(microseconds p) {
			mutASSERT(p >= microseconds::zero());
			mutASSERT(remaining_delta != InputDeviceClass::NO_DELTA());
			mutASSERT(p != InputDeviceClass::NO_DELTA());
			DEBUGLOG (midifile, "remaining_delta = %ld - %ld" ,remaining_delta, p);
			if (p  == InputDeviceClass::NO_DELTA())
				return remaining_delta = InputDeviceClass::NO_DELTA();
			if (remaining_delta == InputDeviceClass::NO_DELTA())
				return remaining_delta;
			return remaining_delta -= p;
		}
		microseconds UpdateDelta() {
			mutASSERT(remaining_delta != InputDeviceClass::NO_DELTA());
			mutASSERT(current_delta != timing_params::miditicks::no_delta());
			DEBUGLOG (midifile, "remaining_delta = %ld + %ld" ,remaining_delta, current_delta.midi_mus());
			if (current_delta  == timing_params::miditicks::no_delta())
				return remaining_delta = InputDeviceClass::NO_DELTA();
			if (remaining_delta == InputDeviceClass::NO_DELTA())
				return remaining_delta;
			return remaining_delta += current_delta.midi_mus();
		}

		timing_params::ticktype WriteDelta();
		bool WriteDelta(microseconds delta) {
			timing_params::ticktype c = delta.count();
			if (delta == InputDeviceClass::NO_DELTA()) {
				c = WriteDelta();
			} else {
				base::WriteDelta(delta.count());
			}
			if (c) {
				flags |= status_flags::delta_sent;
				return true;
			} else return false;
		}

		void SetQuarterDuration(microseconds new_duration,
					bool update = false,
					microseconds offset = microseconds::zero()) {
			if (!update) {
				timing.set_quarter_duration(new_duration);
				return;
			}
			timing_params old(timing);
			timing.set_quarter_duration(new_duration);
			DEBUGLOG(midifile,
				 ("remaining_dellta = %ld, new_duration = %ld, offset = %ld"),
				 remaining_delta,
				 new_duration,
				 offset);
			if (remaining_delta == InputDeviceClass::NO_DELTA())
				return;
			microseconds remaining_remaining_delta = remaining_delta - offset;

			remaining_delta = timing_params::update_duration_midi(remaining_remaining_delta,
									      old,
									      timing)
				+ offset;
			DEBUGLOG (midifile, "remaining delta: %ld" ,remaining_delta);
		}

#if 0
		// this is not needed at the moment
		void SetTicksPerQuarter(mutint64 new_ticks,
					bool update = false,
					mutint64 offset = 0) {
			if (!update) {
				timing.set_ticks(new_ticks);
				return;
			}
			timing_params old(timing);
			timing.set_ticks(new_tiks);
			if (remaining_delta == InputDeviceClass::NO_DELTA())
				return;

			remaining_delta = timing_params::update_duration(remaining_delta-offset,
									 old,
									 timing)
				+ offset;
		}
#endif

		void setTiming(const timing_params & t) {
			timing = t;
		}

		void SetName(const std::string & s) {
			name = s;
		}

		std::pair<uint8_t,uint8_t> getMidiIickSignature() {
			return timing.get_MIDI_tick_signature();
		}

		uint32_t ReadInt();
		base ReadMessage();

		void WriteLength(std::ostream &os, size_t l);

		void MidiOut(uint8_t c1, uint8_t c2, uint8_t c3,
			     microseconds delta = InputDeviceClass::NO_DELTA()) {
			FixSysEx();
			WriteDelta(delta);
			base::MidiOut(c1,c2,c3);
		}

		void MidiOut(uint8_t c1, uint8_t c2,
			     microseconds delta = InputDeviceClass::NO_DELTA()) {
			FixSysEx();
			WriteDelta(delta);
			base::MidiOut(c1,c2);
		}

		void MidiOut(uint8_t c1,
			     microseconds delta = InputDeviceClass::NO_DELTA()) {
			FixSysEx();
			WriteDelta(delta);
			base::MidiOut(c1);
		}

		void StartMeta(uint8_t type,
			       microseconds delta = InputDeviceClass::NO_DELTA()) {
			FixSysEx();
			WriteDelta(delta);
			if (!(WriteDelta(delta)
			      || (flags & status_flags::delta_sent))) {
				switch (type) {
				case midi::META_SET_TEMPO:
					flags |= status_flags::tempo_sent;
					break;
				case midi::META_TIME_SIGNATURE:
					flags |= status_flags::time_signature_sent;
					break;
				}
			}
		}

		template <class i>
		void SendMeta (uint8_t type,
			       i from, i to,
			       microseconds delta = InputDeviceClass::NO_DELTA()) {
			if (type & midi::STARTBYTE_MASK) {
				UNREACHABLEC;
				return;
			}
			StartMeta(type,delta);
			base::SendMeta(type,from,to);
		}

		template <class i>
		void SendSysEx (i from, i to, microseconds delta = InputDeviceClass::NO_DELTA()) {
			if ((*from) & midi::STARTBYTE_MASK) {
				UNREACHABLEC;
				return;
			}
			FixSysEx();
			WriteDelta(delta);
			base::SendSysEx((running_sysex = false), from,to);
		}

		template <class i>
		void SendSysExCont (i from, i to,
				    microseconds delta = InputDeviceClass::NO_DELTA(),
				    size_t offset = 0)
			{


			if (from == to) {
				BOOST_THROW_EXCEPTION(message_length_error(
									    _mutN("The system exclusive message must contain at least a device id.")));
			}

			int tmp_sysex_id = *from ;
			if (tmp_sysex_id == 0) {
				i myfrom = from + 1;
				if (to - myfrom < 2) {
					BOOST_THROW_EXCEPTION(wrong_id(_mutN("System exclusive message contains an invalid device id")));
				}
				tmp_sysex_id = 0x10000 | ((*(myfrom++)) << 8);
				tmp_sysex_id |= ((*myfrom) << 8);
			}

			if (!running_sysex) {
				sysex_id = tmp_sysex_id;
			} else if (sysex_id != tmp_sysex_id) {
				BOOST_THROW_EXCEPTION(wrong_id(_mutN("Device id of continuation package deos not match the id of the system exclusive message")));
			}


			WriteDelta(delta);

			base::SendSysExCont(running_sysex, from, to, offset);

			if (offset == 0 && *(to - 1) != midi::SYSEX_END) {
				running_sysex = true;
			} else {
				running_sysex = false;
			}
		}


		void FixSysEx() {
			if (!running_sysex) return;
			base::FixSysEx(sysex_id);
			running_sysex = false;
		}

		void SendTempo(microseconds delta = InputDeviceClass::NO_DELTA()) {
			StartMeta(midi::META_SET_TEMPO, delta);
			base::SendTempo(timing.get_quarter_duration().count());
		}


		void SendTimeSignature(uint8_t numerator,
				       uint8_t denominator_exponent,
				       uint8_t metronome_click_clocks,
				       uint8_t quarter_duration_in_32th,
				       microseconds delta = InputDeviceClass::NO_DELTA()) {
			StartMeta(midi::META_SET_TEMPO, delta);
			base::SendTimeSignature(numerator,
						denominator_exponent,
						metronome_click_clocks,
						quarter_duration_in_32th);
		}


		void Save(std::ostream &os);
		void Load(std::istream &is,
			  const std::string & Name);


		void Stop() {
			remaining_delta = InputDeviceClass::NO_DELTA();
			current_delta   = timing_params::miditicks::no_delta();
			running_sysex   = false;
			sysex_id        = 0;
			position        = 0;
		}

		operator std::string() const;
		std::string c_str() const { return *this; }

	protected:
		status_flags flags;
		CurrentTimer::time_point Time;//< Time of last action (at least in record mode)
		timing_params timing;
		size_t position;
		timing_params::miditicks current_delta;   //< Difference between last and next event
		microseconds remaining_delta; //< Difference between “now” and the next event
		uint8_t running_status;   //< Save status byte for (de)coding running status
		bool running_sysex;
		int sysex_id;
		std::string name;
	};

	typedef boost::unordered_map<int,boost::intrusive_ptr<Track>> TrackList;

	class MidiFileOutputProvider {
	public:
		MidiFileOutputProvider(Device * d):device(d),Tracks() {}
		~MidiFileOutputProvider() {}

		bool Open() {
			for (auto& i : Tracks)
				i.second->Reset();
			return true;
		}

		void Close() {}
		void Close(std::ostream &os) {
			for (auto & i : Tracks)
				i.second->Save(os);
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
		MidiFileOutputProvider & operator() (int channel,
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
		MidiFileOutputProvider & RawMsg (int channel,
						 uint8_t byte1,
						 uint8_t byte2,
						 uint8_t byte3) {
			GetTrack(channel)->MidiOut(byte1,byte2,byte3);
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
		MidiFileOutputProvider & operator() (int channel,
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
		 MidiFileOutputProvider & RawMsg (int channel,
						  uint8_t byte1,
						  uint8_t byte2) {
			 GetTrack(channel)->MidiOut(byte1,byte2);
			 return *this;
		}

		/**
		 * Outputs a one-byte message.
		 *
		 * \param channel channel to which data shall be sent
		 *        to. How channels are split into tracks or
		 *        subdevices is managed by the OutputProvider
		 * \param byte1 1st byte
		 */
		MidiFileOutputProvider & RawMsg (int channel, uint8_t byte1) {
			GetTrack(channel)->MidiOut(byte1);
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
		MidiFileOutputProvider & SendSysEx (int channel,
						    i from,
						    i to) {
			GetTrack(channel)->SendSysEx(from,to);
			return *this;
		}

		/**
		 * Write the MIDI file to a stream.
		 *
		 * \param os stream to write to
		 */
		void Save(std::ostream &os) {
			std::pair<uint8_t,uint8_t > ticks = Tracks.begin()->second->getMidiIickSignature();
			size_t number = Tracks.size();

			// Let's try to generate Format 0 files: 1 Track including all information.

			uint8_t Header[14] = {
				// File header
				'M', 'T', 'h', 'd', // Chunk type MIDI file header
				0, 0, 0, 6,         // chunk length
				0, 2,               // file type Format 2 = independent tracks
				uint8_t((number & 0xFF00) >> 8) , uint8_t(number & 0xFF), // number of tracks
				ticks.first, ticks.second // Ticks per qaurter or second
				/* Alternatve format last 2 bytes:
				   0x80 & negative_SMPTE_format_in_7bit,
				   ticks_per_frame */
			};

			os.write(reinterpret_cast<char *>(Header), 14);
			for (auto &i : Tracks)
				i.second->Save(os);
		}

	protected:
		Device * device;
		TrackList Tracks;

		boost::intrusive_ptr<Track>  GetTrack(int channel) {
			int channel_id = channel >> 4;
			auto pos = Tracks.find(channel_id);
			if (pos != Tracks.end())
				return pos -> second;
			else
				{
					Tracks[channel_id] = new Track;
					return Tracks[channel_id];
				}

		}
	};



	// OutMidiFile ------------------------------------------------------

	class MidiFileFactory;
	class OutputMidiFile : public CommonMidiOutput<MidiFileOutputProvider,CommonFileOutputDevice>
	{
		friend class MidiFileFactory;
	public:
		typedef CommonMidiOutput<MidiFileOutputProvider,CommonFileOutputDevice> base;

		virtual ~OutputMidiFile() {}

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
		virtual void Load (tree_storage & config, RouteClass * route);


		virtual DevType GetType() const
		{
			return DTMidiFile;
		}


		virtual int GetMaxChannel() const { return 15; }
		virtual int GetMinChannel() const { return 0; }

		virtual std::string GetTypeName () const {
			return _mutN("MIDI output file");
		}

		virtual operator std::string() const;

		void Save(std::ostream &os) {
			Out.Save(os);
		}
	protected:
		OutputMidiFile(): base() {}

		OutputMidiFile(const std::string name,
			       int id = -1,
			       int bendingRange = 2)
			: base(name, id, bendingRange) {}

#if defined(_MSC_VER)
#pragma warning(push) // Save warning settings.
#pragma warning(disable : 4100) // Disable unreferenced formal parameter warnings
#endif

		virtual void do_Gis(GisToken * token, char turn)
		{
			mutUnused(token);
			mutUnused(turn);
		}

		virtual void do_AddTime(frac time)
		{
			mutUnused(time);
		}

#if defined(_MSC_VER)
#pragma warning(pop) // Restore warnings to previous state.
#endif

		virtual void do_Close(bool sync=false);

	};




// InMidiFile -------------------------------------------------------

	class InputMidiFile : public CommonMidiInput<CommonFileInputDevice>
	{
		typedef CommonMidiInput<CommonFileInputDevice> base;
		friend class MidiFileFactory;
	protected:
		InputMidiFile(): base(),
				 FileType(0),
				 Tracks(),
				 Busy(false),
				 timing() { }

		InputMidiFile(std::string name,
			      MutaborModeType mode,
			      int id): base(name,
					    mode,
					    id),
				       FileType(0),
				       Tracks(),
				       Busy(false),
				       timing() {}

	public:
		virtual ~InputMidiFile()
			{}

		using base::Save;
		/// Save route settings (filter settings) for a given route
		/** Some route settings (e.g. filter settings) are device type
		 * specific. This function saves them in a tree storage.
		 * \argument config (tree_storage *) Storage class, where the data will be saved.
		 * \argument route (Route ) Route whos data shall be saved.
		 */
		virtual void Save (tree_storage & config, const RouteClass * route);


		using base::Load;
		/// Loade route settings (filter settings) for a given route
		/** Some route settings (e.g. filter settings) are device type
		 * specific. This function loads them from a tree storage.
		 * \argument config (tree_storage *) Storage class, where the data will be restored from.
		 * \argument route (Route ) Route whos data shall be loaded.
		 */
		virtual void Load (tree_storage & config, RouteClass * route);


		virtual bool Open();
		virtual void Close();
		virtual void Stop();

//	   void Proceed(GisReadArtHead *h, char turn, Route route) {};
//	   void ProceedRoute(GisReadArtHead *h, char turn) {};

#if defined(_MSC_VER)
#pragma warning(push) // Save warning settings.
#pragma warning(disable : 4100) // Disable unreferenced formal parameter warnings
#endif

		virtual frac ReadOn(frac time) {
			mutUnused(time);
			return frac(0, 1);
		}

#if defined(_MSC_VER)
#pragma warning(pop) // Restore warnings to previous state.
#endif

		virtual DevType GetType() const	{
			return DTMidiFile;
		}


		/**
		 * Go on to the next event.
		 * This function must be
		 * provided by the device. It advices it to prepare
		 * the next event and return the time frame in
		 * milliseconds from the start of the piece.
		 *
		 * \return mutint64 Temporal position of the next event in the
		 * piece.
		 */
		virtual microseconds PrepareNextEvent();

		virtual int GetMaxChannel() const { return 15; }
		virtual int GetMinChannel() const { return 0; }
		virtual int GetMaxTrack() const { return 0xFFFF; }
		virtual int GetMinTrack() const { return 0; }

		virtual std::string GetTypeName () const {
			return _mutN("MIDI input file");
		}

		virtual operator std::string() const;

		proceed_bool shouldProceed(Route R,
					   const std::vector<uint8_t > &midiCode,
					   int data =0);
		void Proceed(const std::vector<uint8_t > &midiCode,
			     int data =0,
			     size_t channel_offset = 0);

	protected:
		int FileType;
		std::vector<Track> Tracks;
		microseconds minDelta;        //< time interval to next event μs
		bool Busy;
		timing_params timing;    //< timing parameters
		microseconds ReadMidiProceed(size_t nr, microseconds time);
	};


	class MidiFileFactory:public DeviceFactory {
	public:
		MidiFileFactory(size_t id = DTMidiFile):
			DeviceFactory(id) {}
		virtual ~MidiFileFactory();

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


// Function ---------------------------------------------------------

}

#endif  /* precompiled */
#endif

///\}
