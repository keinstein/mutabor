/** \file  -*- C++ -*-
 ********************************************************************
 * Device providing MIDI files.
 *
 * Copyright:   (c) 1998-2011 TU Dresden
 * \author 
 * R.Krauße,
 * Tobias Schlemmer <keinstein@users.berlios.de>
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

#ifdef WX
//#include "src/wxGUI/generic/mhArray.h"
#endif

#ifndef MU32_ROUTING_MIDI_DEVMIDF_H_PRECOMPILED
#define MU32_ROUTING_MIDI_DEVMIDF_H_PRECOMPILED

// system headers which do seldom change

#include <fstream>
#include "wx/timer.h"



namespace mutabor {

// Track ------------------------------------------------------------

	class Track: public std::vector<uint8_t>
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

		Track(): base(), 
			 Time(0),
			 timing(),
			 position(0), 
			 current_delta(MUTABOR_NO_DELTA), 
			 remaining_delta(0),
			 running_status(0),
			 running_sysex(false),
			 sysex_id() {
			reserve(100);
			DEBUGLOG(midifile,_T("%s"), (this->c_str()));
				 
		}

		Track(timing_params p): base(),
					Time(0),
					timing(p),
					position(0),
					current_delta(MUTABOR_NO_DELTA),
					remaining_delta(0),
					running_status(0),
					running_sysex(false),
					sysex_id() {
			reserve(100);
			DEBUGLOG(midifile,_T("%s"), (this->c_str()));
		}
					

		~Track() {}

		size_t GetPosition() { return position; }
		void ResetPosition(size_t p, bool resettiming = false) { 
			position = 0; 
			running_status = 0;
			running_sysex = false;
			if (resettiming) {
				timing.set_quarter_duration(500000); //  120 bpm
				Time = 0;
				current_delta = remaining_delta = 0;
			}
			DEBUGLOG(midifile,_T("%s"), (this->c_str()));
 		}

		void ResetDelta() { 
			DEBUGLOG(midifile,_T("resetting remaining delta to 0"));
			remaining_delta = 0;
		}
		mutint64 GetDelta() { return remaining_delta; }
		mutint64 ReadDelta();
		mutint64 PassDelta(mutint64 p) { 
			mutASSERT(p >= 0);
			mutASSERT(remaining_delta != MUTABOR_NO_DELTA);
			mutASSERT(p != MUTABOR_NO_DELTA);
			DEBUGLOG(midifile,_T("remaining_delta = %ld - %ld"),remaining_delta, p);
			if (p  == MUTABOR_NO_DELTA) 
				return remaining_delta = MUTABOR_NO_DELTA;
			if (remaining_delta == MUTABOR_NO_DELTA)
				return remaining_delta;
			return remaining_delta -= p; 
		}
		mutint64 UpdateDelta() { 
			mutASSERT(remaining_delta != MUTABOR_NO_DELTA);
			mutASSERT(current_delta != MUTABOR_NO_DELTA);
			DEBUGLOG(midifile,_T("remaining_delta = %ld + %ld"),remaining_delta, current_delta);
			if (current_delta  == MUTABOR_NO_DELTA) 
				return remaining_delta = MUTABOR_NO_DELTA;
			if (remaining_delta == MUTABOR_NO_DELTA) 
				return remaining_delta;
			return remaining_delta += current_delta; 
		}
		void WriteDelta();

		void SetQuarterDuration(mutint64 new_duration,
					bool update = false, 
					mutint64 offset = 0) {
			if (!update) {
				timing.set_quarter_duration(new_duration);
				return;
			}
			timing_params old(timing);
			timing.set_quarter_duration(new_duration);
			DEBUGLOG(midifile,
				 _T("remaining_dellta = %ld, new_duration = %ld, offset = %ld"),
				 remaining_delta,
				 new_duration,
				 offset);
			if (remaining_delta == MUTABOR_NO_DELTA)
				return;
			mutint64 remaining_remaining_delta = remaining_delta - offset;
			
			remaining_delta = timing_params::update_duration_midi(remaining_remaining_delta,
									      old,
									      timing)
				+ offset;
			DEBUGLOG(midifile, _T("remaining delta: %ld"),remaining_delta);
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
			if (remaining_delta == MUTABOR_NO_DELTA) 
				return;

			remaining_delta = timing_params::update_duration(remaining_delta-offset,
									 old,
									 timing)
				+ offset;
		}
#endif

		std::pair<uint8_t,uint8_t> getMidiIickSignature() {
			return timing.get_MIDI_tick_signature();
		}

		uint32_t ReadInt();
		base ReadMessage();

		void WriteNumber(size_t count) {
			uint8_t tmp[4];
			int i = 0;
			tmp[0] = count & 0x7f;
			while (count && i < 4) {
				tmp[i++] = count & 0x7f;
				count >>= 7;
			}
			if (count) 
				BOOST_THROW_EXCEPTION(delta_length_error(gettext_noop("trying to write number > 0x0FFFFFFF")));

			if (i == 0) i++;
			while (--i) 
				push_back(tmp[i] | 0x80);
			push_back(tmp[0]);
		}
		void WriteLength(mutOFstream &os, size_t l);
	
		void MidiOut(uint8_t c1, uint8_t c2, uint8_t c3) {
			FixSysEx();
			WriteDelta();
			push_back(c1);
			push_back(c2);
			push_back(c3);
		}

		void MidiOut(uint8_t c1, uint8_t c2) {
			FixSysEx();
			WriteDelta();
			push_back(c1);
			push_back(c2);
		}

		void MidiOut(uint8_t c1) {
			FixSysEx();
			WriteDelta();
			push_back(c1);
		}

		template <class i>
		void WriteLongChunk(i from, i to, size_t offset = 0) {
			size_t count = (to - from) + offset;
			
			size_t c = count+offset;
			if (capacity() < size()+c+4) 
				reserve (size()+c+4);
			WriteNumber(count+offset);
			while (from != to)
				push_back(*(from++));
		}

		template <class i> 
		void SendMeta (uint8_t type, i from, i to, mutint64 delta = MUTABOR_NO_DELTA) {
			if (type & midi::STARTBYTE_MASK) {
				UNREACHABLEC;
				return;
			}
			FixSysEx();
			if (delta == MUTABOR_NO_DELTA) {
				WriteDelta();
			} else {
				WriteNumber(delta);
			}
			push_back(midi::META);
			push_back(type);
			WriteLongChunk(from,to,delta,0);
		}

		template <class i> 
		void SendSysEx (i from, i to, mutint64 delta = MUTABOR_NO_DELTA) {
			if ((*from) & midi::STARTBYTE_MASK) {
				UNREACHABLEC;
				return;
			}
			FixSysEx();
			SendSysExCont(from,to,delta,1);
			push_back(midi::SYSEX_END);
			running_sysex = false;
		}

		template <class i>
		void SendSysExCont (i from, i to, 
				    mutint64 delta = MUTABOR_NO_DELTA, 
				    size_t offset = 0)
			{
			 

			if (from == to) {
				BOOST_THROW_EXCEPTION(message_length_error(
									    gettext_noop("The system exclusive message must contain at least a device id.")));
			}

			int tmp_sysex_id = *from ;
			if (tmp_sysex_id == 0) {
				i myfrom = from + 1;
				if (to - myfrom < 2) {
					BOOST_THROW_EXCEPTION(wrong_id(gettext_noop("System exclusive message contains an invalid device id")));
				}		
				tmp_sysex_id = 0x10000 | ((*(myfrom++)) << 8);
				tmp_sysex_id |= ((*myfrom) << 8);
			}

			if (!running_sysex) {
				sysex_id = tmp_sysex_id;
			} else if (sysex_id != tmp_sysex_id) {
				BOOST_THROW_EXCEPTION(wrong_id(gettext_noop("Device id of continuation package deos not match the id of the system exclusive message")));
			}

			if (delta == MUTABOR_NO_DELTA) {
				WriteDelta();
			} else {
				WriteNumber(delta);
			}
			
			push_back(running_sysex?midi::SYSEX_END:midi::SYSEX_START);
			WriteLongChunk(from, to, offset);

			if (offset == 0 && *(to - 1) != midi::SYSEX_END) {
				running_sysex = true;
			} else {
				running_sysex = false;
			}
		}


		void FixSysEx() {
			if (!running_sysex) return;
			if (capacity() < size() + 10)
				reserve(size()+6);
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
			running_sysex = false;
		}


		void Save(mutOFstream &os);

		void Stop() {
			remaining_delta = current_delta = MUTABOR_NO_DELTA;
			running_sysex   = false;
			sysex_id        = 0;
			position        = 0;
		}

#ifdef DEFINE_VECTOR_DATA
		base::value_type * data() { return &(this->at(0)); }
#endif

		wxString TowxString ();
		const mutChar * c_str() {
			return (this->TowxString ()).c_str();
		}
	protected:
		mutint64 Time;            //< Time of last action (at least in record mode)
		timing_params timing;
		size_t position;
		mutint64 current_delta;   //< Difference between last and next event
		mutint64 remaining_delta; //< Difference between “now” and the next event
		uint8_t running_status;   //< Save status byte for (de)coding running status
		bool running_sysex;
		int sysex_id;

	};

	typedef std::vector<Track> TrackList;

	class MidiFileOutputProvider {
	public:
		MidiFileOutputProvider(Device * d):device(d),Tracks() {}
		~MidiFileOutputProvider() {}

		bool Open() {
			Tracks.clear();
			return true;
		}

		void Close() {}
		void Close(mutOFstream &os) {
			Tracks.Save(os);
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
			Tracks.MidiOut(byte1,byte2,byte3);
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
			Tracks.MidiOut(byte1,byte2);
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
			Tracks.MidiOut(byte1);
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
			Tracks.SendSysEx(from,to);
			return *this;
		}

		/** 
		 * Write the MIDI file to a stream.
		 * 
		 * \param os stream to write to
		 */
		void Save(mutOFstream &os) {
			std::pair<uint8_t,uint8_t > ticks = Tracks.getMidiIickSignature();

			// Let's try to generate Format 0 files: 1 Track including all information.

			uint8_t Header[14] = { 
				// File header
				'M', 'T', 'h', 'd', // Chunk type MIDI file header
				0, 0, 0, 6,         // chunk length
				0, 0,               // file type Format 2 = independent tracks
				0, 1,               // number of tracks
				ticks.first, ticks.second // Ticks per qaurter or second
				/* Alternatve format last 2 bytes:
				   0x80 & negative_SMPTE_format_in_7bit,
				   ticks_per_frame */
			};

			mutWriteStream(os,Header, 14);
			Tracks.Save(os);
		}

	protected:
		Device * device;
		Track Tracks;
	};
	


	// OutMidiFile ------------------------------------------------------

	class MidiFileFactory;
	class OutputMidiFile : public CommonMidiOutput<MidiFileOutputProvider,CommonFileOutputDevice>
	{
		friend class MidiFileFactory;
	public:
		typedef CommonMidiOutput<MidiFileOutputProvider,CommonFileOutputDevice> base;

		virtual ~OutputMidiFile() {};
	
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

	
		virtual void Close();
		virtual void SetName(const wxString & s) 
			{
				if (s != Name) {
					bool reopen = IsOpen();
					if (reopen) 
						Close();

					Name = s;

					if (reopen)
						Open();
				}
			}
		

		virtual DevType GetType() const
			{
				return DTMidiFile;
			}

	
		virtual int GetMaxChannel() const { return 15; }
		virtual int GetMinChannel() const { return 0; }
	
		virtual mutString GetTypeName () const {
			return N_("MIDI output file");
		}

#ifdef WX
		virtual wxString TowxString() const;
#endif

		void Save(mutOFstream &os) {
			Out.Save(os);
		}
	protected:
		OutputMidiFile(): base() {}

		OutputMidiFile(const mutStringRef name, 
			       int id = -1, 
			       int bendingRange = 2)
			: base(name, id, bendingRange) {}

#if defined(_MSC_VER)
#pragma warning(push) // Save warning settings.
#pragma warning(disable : 4100) // Disable unreferenced formal parameter warnings
#endif

		virtual void do_Gis(GisToken * token, char turn)
			{};

		virtual void do_AddTime(frac time)
			{};

#if defined(_MSC_VER)
#pragma warning(pop) // Restore warnings to previous state.
#endif 

	};




// InMidiFile -------------------------------------------------------

	class InputMidiFile : public CommonMidiInput<CommonFileInputDevice>
	{
		typedef CommonMidiInput<CommonFileInputDevice> base;
		friend class MidiFileFactory;
	protected:
		InputMidiFile(): base(),
				 Tracks(),
				 Busy(false),
				 timing() { }

		InputMidiFile(mutString name, 
			      MutaborModeType mode,
			      int id): base(name, 
					    mode, 
					    id),
				       Tracks(),
				       Busy(false), 
				       timing() {}

	public:
		virtual ~InputMidiFile()
			{};
	
		/// Save route settings (filter settings) for a given route
		/** Some route settings (e.g. filter settings) are device type 
		 * specific. This function saves them in a tree storage.
		 * \argument config (tree_storage *) Storage class, where the data will be saved.
		 * \argument route (Route ) Route whos data shall be saved.
		 */
		virtual void Save (tree_storage & config, const RouteClass * route);
	
	
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
		virtual mutint64 PrepareNextEvent();
	
		virtual int GetMaxChannel() const { return 15; }
		virtual int GetMinChannel() const { return 0; }
		virtual int GetMaxTrack() const { return 0xFFFF; }
		virtual int GetMinTrack() const { return 0; }

		virtual mutString GetTypeName () const {
			return N_("MIDI input file");
		}
	
#ifdef WX
		virtual wxString TowxString() const;
#endif

		proceed_bool shouldProceed(Route R,
					   const std::vector<unsigned char > * midiCode,
					   int data =0);
		void Proceed(const std::vector<unsigned char > * midiCode, int data =0, int channel_offset = 0);

	protected:
		int FileType;
		TrackList Tracks;
		mutint64 minDelta;        //< time interval to next event μs
		BOOL Busy;
		timing_params timing;    //< timing parameters
		mutint64 ReadMidiProceed(size_t nr, mutint64 time);
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


		virtual mutabor::OutputDeviceClass * DoCreateOutput(const mutStringRef name, 
								    int id = -1) const;
		
		virtual mutabor::InputDeviceClass * DoCreateInput(const mutStringRef name, 
								  mutabor::MutaborModeType mode, 
								  int id = -1) const;
	};


// Function ---------------------------------------------------------

}

#endif  /* precompiled */
#endif

///\}
