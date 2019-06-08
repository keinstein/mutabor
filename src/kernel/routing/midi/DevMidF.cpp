/** \file
 ********************************************************************
 * MIDI-File as device.
 *
 * \author Rüdiger Krauße,
 *         Tobias Schlemmer <keinstein@users.sourceforge.net>
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
 ********************************************************************
 * \addtogroup route
 * \{
 ********************************************************************/
#include "src/kernel/Defs.h"
#if defined(MUTWIN) && !defined(WX)
#include <owl/pch.h>
#endif

//#include "RtMidi.h"
#include "boost/filesystem.hpp"
#include "boost/filesystem/fstream.hpp"
#include "boost/filesystem/detail/utf8_codecvt_facet.hpp"
#include "boost/chrono/chrono_io.hpp"

#include "src/kernel/routing/midi/DevMidF.h"
//#include "src/kernel/routing/midi/DevMidi.h"
#include "src/kernel/error.h"
#include "src/kernel/Execute.h"
//#include "src/kernel/GrafKern.h"
#include "src/kernel/Runtime.h"
#include "src/kernel/routing/Route-inlines.h"

#include <inttypes.h>
#include <stdio.h>

#include "src/kernel/routing/midi/midicmn-inlines.h"
#include "src/kernel/routing/CommonFileDevice-inlines.h"

// the following file is not compiled independently
#include "src/kernel/routing/midi/midicmn.cpp"



namespace mutabor {
	using namespace midi;

	void DebugMidiOutputProvider::WriteTime() {
		// this function is not inlined to reduce the dependencies on timing.h
		std::string tmp;
		if (!CurrentTime.isRealtime()) {

			tmp = str(boost::format("%ld ")
				  % (CurrentTime.Get()-mutabor::CurrentTimer::time_point()).count());
			data += tmp;
		}
	}

	template class CommonMidiOutput<MidiFileOutputProvider,CommonFileOutputDevice>;

#if 0
// berechnet die Frequenz in Midi-Form
#define GET_FREQ(taste,tonsystem)					\
	( ( (tonsystem)->ton[GET_INDEX(taste,(tonsystem))]==0) ?	\
	  (long) 0 :							\
	  (long)( (tonsystem)->periode *				\
		  GET_ABSTAND(taste,(tonsystem))  +			\
		  (tonsystem)->ton[GET_INDEX(taste,(tonsystem))]))

#define ZWZ 1.059463094 /* 12.Wurzel 2 */
#define LONG_TO_HERTZ( x ) (440.0*pow(ZWZ,((((double)x)/(double)16777216.0))-69))

// Midi-Ausgabe
#define MIDI_OUT3(code1, code2, code3)		\
	Tracks.MidiOut3(code1, code2, code3)

#define MIDI_OUT2(code1, code2)			\
	Tracks.MidiOut2(code1, code2)

	static inline uint8_t bytenr (unsigned long number, int index)
	{
		return (number >> index * 8) & 0xFF;
	}

#endif

	static uint32_t ReadLength(std::istream &is)
	{
		uint8_t a[4] = {0,0,0,0};
		is.read((char*)a, 4);
		return (((uint32_t)a[0]) << 24) + (((uint32_t)a[1]) << 16) +
			(((uint32_t)a[2]) << 8) + ((uint32_t)a[3]);
	}



// Tracks -----------------------------------------------------------

	microseconds Track::ReadDelta()
	{
		mutASSERT(remaining_delta != InputDeviceClass::NO_DELTA());
		current_delta = timing_params::miditicks(ReadInt(),timing);
		DEBUGLOG (midifile, "%s" ,(this->c_str()));
		remaining_delta += current_delta.midi_mus();
		return remaining_delta;
	}

	timing_params::ticktype Track::WriteDelta()
	{
		CurrentTimer::time_point newtime = CurrentTime.Get();
		microseconds newdelta =
			newtime >= Time ?
			boost::chrono::duration_cast<microseconds>(newtime - Time):microseconds::zero();
			;
		microseconds Deltatime = std::max(newdelta,
						  microseconds::zero());
		// note: Deltatime may be a little bit ahead if get_delta rounds up
		timing_params::miditicks Delta (Deltatime,timing,true);
		DEBUGLOG(midifile,
			 ("Deltatime = %ld, Delta = %ld, get_time_midi(Delta) = %ld, get_delta_midi(get_time_midi(Delta)) = %ld"),
			 Deltatime, Delta.count(),
			 Delta.midi_mus().count(),
			 timing_params::miditicks(Delta.midi_mus(),timing,true).count());
		mutASSERT(timing_params::miditicks(Delta.midi_mus(),timing,true) == Delta);
		// we should take care of rounding errors
		//Time = newtime + timing.get_time(Delta) - Deltatime;
		Time += Delta.midi_mus();

		// if the Delta time is bad wite a correct number
		mutASSERT(midi::is_valid_length(Delta.count()));
		uint32_t output = Delta.count_in_range(0,0x0FffFFff);
		base::WriteDelta(output);
		return output;
	}

	uint32_t Track::ReadInt() {
		uint32_t l = 0;
		uint8_t a;

		int i =0 ;
		do {
			if (++i > 4) {
				BOOST_THROW_EXCEPTION(delta_length_error(_mutN("Number contains too many bytes")));
			}
			a = (*this)[position++];
			l = (l << 7) + (a & 0x7F);
		} while (a & 0x80);
		return l;
	}

	Track::base Track::ReadMessage() {
		uint8_t status, metatype = midi::META_SEQUENCER_SPECIFIC;
		if ((status = at(position)) & 0x80) {
			position++;
			if (midi::reset_running_status (status))
				running_status = 0;
			else if (store_running_status(status))
				running_status = status;
		} else status = running_status;
		if (! (status & 0x80)) {
			char * tmp;
			std::string s;
			if (asprintf(&tmp, _mut("Invalid status byte: %x  at position %d"), status, position) > 0) {
				s = tmp;
				free(tmp);
			}
			BOOST_THROW_EXCEPTION(invalid_status (s));
		}

		size_t offset = 1;
		// databytes may be nagative
		int data_bytes = midi::get_data_size(status) - 1;
		if (data_bytes < 0) {
			mutASSERT(status == midi::SYSEX_START ||
				  status == midi::SYSEX_END ||
				  status == midi::META);
			if (status == midi::META) {
				metatype = at(position++);
				offset++;
			}
			data_bytes = ReadInt();
		}
		if (size() - position  < (size_t) data_bytes)
			throw std::out_of_range(_mut("File ended while scanning for end of meta event"));

		data_bytes += offset;
		base retval(data_bytes);
		retval.resize(data_bytes);
		retval[0] = status;
		if (status == midi::META)
			retval[1] = metatype;

		for (size_t i = offset ; i < (size_t)data_bytes ; i++ )
			retval [i] = (*this)[position++]; // should throw on access violation.

		return retval;
	}

	void Track::WriteLength(std::ostream &os, size_t l)
	{
		os.put((uint8_t) ((l >> 24) & 0xFF));
		os.put((uint8_t) ((l >> 16) & 0xFF));
		os.put((uint8_t) ((l >> 8) & 0xFF));
		os.put((uint8_t) (l & 0xFF));
	}

	void Track::Save(std::ostream &os)
	{
		os.write("MTrk",4);
		base metaevents(13);
		if (! (flags & flags.tempo_sent)) {
			metaevents.WriteDelta(0);
			metaevents.SendTempo(timing.get_quarter_duration().count());
		}
		if (! (flags & flags.time_signature_sent)) {
			metaevents.WriteDelta(0);
			metaevents.SendTimeSignature(4,
						     2,
						     24,
						     8);
		}

		static const uint8_t EOT[] = {0x00, midi::META, midi::META_END_OF_TRACK, 0x00};

		WriteLength(os, metaevents.size()+size()+4);
		os.write(reinterpret_cast<const char *>(metaevents.data()),metaevents.size());
		os.write(reinterpret_cast<const char *>((const uint8_t*)data()),size());
		os.write(reinterpret_cast<const char *>(EOT),4);
	}

	void Track::Load(std::istream &is,
			 const std::string & filename) {
		char Header[5] = {0,0,0,0,0};   // storage for header mark
		is.read(Header, 4);
		if (strcmp(Header,"MTrk")) {
			throw_runtime_error(generic_error,
					    boost::str(boost::format(_mut("Track %s of file '%s' has a broken track header."))
						       % name
						       % filename));
		}

		size_t l = mutabor::ReadLength(is);

		clear();
		try {
			resize(l);
		} catch (const std::bad_alloc & e) {
			clear();
		}

		if ( size() < l) {
			throw_runtime_error(generic_error,
					    boost::str(boost::format(_mut("Could not allocate data for track %s of MIDI input file '%s'."))
						       % name % filename));
		}


		if ( l > 0x10000000) {
			// in order to avoid problems with 32bit integers we read large tracks in 3 chunks

			is.read((char*)(data()), l/3);
			is.read((char*)(data())+l/3, l/3);
			is.read((char*)(data())+l/3+l/3,l-l/3- l/3);
		} else
			is.read((char*)(data()), l);

		if ( is.bad() ) {
			throw_runtime_error(generic_error,
					    boost::str(boost::format(_mut("The MIDI input file “%s” is corrupted. This has been detected while reading track %s."))
						       % filename % name));
		}
	}


	Track::operator std::string () const {
		return boost::str(boost::format("\
timing: %s\n\
Time = %ld, position = %d/%d, current_delta = %ld, remaining_delta = %ld\n\
Running status = %d (%x), running_sysex = %s, SysEx Id = %d (%x)")
				  % str(timing).c_str()
				  % Time % (int)position % (int)size() % current_delta % remaining_delta
				  % running_status % running_status
				  % (running_sysex?("true"):("false")) % sysex_id % sysex_id);
	}

// OutputMidiFile ------------------------------------------------------

/// Save current device settings in a tree storage
/** \argument config (tree_storage) storage class, where the data will be saved.
 */
	void OutputMidiFile::Save (tree_storage & config)
	{
#ifdef DEBUG
		std::string oldpath = config.GetPath();
#endif
		config.Write(("Bending Range"),bending_range);
		config.Write(("File Name"),Name);
		mutASSERT(oldpath == config.GetPath());
	}

/// Save route settings (filter settings) for a given route
/** Some route settings (e.g. filter settings) are device type
 * specific. This function saves them in a tree storage.
 * \argument config (tree_storage *) Storage class, where the data will be saved.
 * \argument route (Route ) Route whos data shall be saved.
 */
	void OutputMidiFile::Save (tree_storage & config, const RouteClass * route)
	{
#ifdef DEBUG
		std::string oldpath = config.GetPath();
#endif
		config.toLeaf(("Midi File Output"));
		mutASSERT(route);
		config.Write(("Avoid Drum Channel"), route->OutputAvoidDrumChannel());
		config.Write(("Channel Range From"), route->GetOutputFrom());
		config.Write(("Channel Range To"), route->GetOutputTo());
		config.toParent();
		mutASSERT(oldpath == config.GetPath());
	}


        /// Load current device settings from a tree storage
        /** \argument config (tree_storage) storage class, where the data will be loaded from.
	 */
	void OutputMidiFile::Load (tree_storage & config)
	{
#ifdef DEBUG
		std::string oldpath = config.GetPath();
#endif
		bending_range=config.Read(("Bending Range"), bending_range);
		Name = config.Read(("File Name"),"");
		mutASSERT(oldpath == config.GetPath());
	}

        /// Loade route settings (filter settings) for a given route
	/** Some route settings (e.g. filter settings) are device type
	 * specific. This function loads them from a tree storage.
	 * \argument config (tree_storage *) Storage class, where the data will be restored from.
	 * \argument route (Route ) Route whos data shall be loaded.
	 */
	void OutputMidiFile::Load (tree_storage & config, RouteClass * route)
	{
#ifdef DEBUG
		std::string oldpath = config.GetPath();
#endif
		config.toLeaf(("Midi File Output"));
		mutASSERT(route);
		route->OutputAvoidDrumChannel(config.Read (("Avoid Drum Channel"), true));
		int oldfrom, oldto;
		route->SetOutputFrom(oldfrom = config.Read(("Channel Range From"), GetMinChannel()));
		route->SetOutputTo(oldto = config.Read(("Channel Range To"), GetMaxChannel()));
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
			runtime_error(mutabor::generic_warning,
				      boost::str(boost::format(_mut("The Channel range %d--%d of the MIDI file %s must be inside %d--%d. The current route had to be corrected."))
						 % oldfrom%oldto % GetName().c_str() % GetMinChannel() %GetMaxChannel()));
		config.toParent();
		mutASSERT(oldpath == config.GetPath());
	}


	void OutputMidiFile::do_Close(bool sync)
	{
		base::do_Close(sync);

		/* tell boost that we are using UTF-8 file names */
		boost::filesystem::detail::utf8_codecvt_facet utf8;
		boost::filesystem::path p;
		p.assign(Name, utf8);

		boost::filesystem::ofstream os(p,
					       std::ios::out | std::ios::binary);

		Out.Save(os);
		if (sync)
			os.flush();
	}



	OutputMidiFile::operator std::string() const {
		std::string s = OutputDeviceClass::operator std::string() +
			boost::str(boost::format("\n  Name = %s\n  session_id = %lu\n  routefile_id = %d\n  Bending Range = %d\n  nKeyOn = %d")
				   % Name.c_str() % (unsigned long)session_id() % routefile_id % bending_range % nKeyOn);

		s += boost::str(boost::format("]\n  ton_auf_kanal = [ t=%d,k=%d,b=%d")
				% ton_auf_kanal[0].inkey
				% ton_auf_kanal[0].outkey.pitch
				% ton_auf_kanal[0].outkey.bend);
		for (int i = 1; i<16; i++)
			s += boost::str(boost::format("; t=%d,k=%d,b=%d")
					% ton_auf_kanal[i].inkey
					% ton_auf_kanal[i].outkey.pitch
					% ton_auf_kanal[0].outkey.bend);
		s+=("]");
		return s;
	}

#if 0
	void OutputMidiFile::ReadData(wxConfigBase * config)
	{
		bending_range = config->Read(_mut("Bending_Range"),
					     (long)bending_range);
	}

	void OutputMidiFile::WriteData(wxConfigBase * config)
	{
		config->Write(_mut("Bending_Range"), (long)bending_range);
	}
#endif


// InputMidiFile -------------------------------------------------------

/*
  void CALLBACK MidiTimeFunc(UINT wTimerID, UINT wMsg, uint32_t dwUser, uint32_t dw1, uint32_t dw2)
  {
  ((InputMidiFile*)dwUser)->IncDelta();
  }
*/
	/// \todo: check for array borders


/// Save route settings (filter settings) for a given route
/** Some route settings (e.g. filter settings) are device type
 * specific. This function saves them in a tree storage.
 * \argument config (tree_storage *) Storage class, where the data will be saved.
 * \argument route (Route) Route whos data shall be saved.
 */
	void InputMidiFile::Save (tree_storage & config, const RouteClass * route)
	{
#ifdef DEBUG
		std::string oldpath = config.GetPath();
#endif
		config.toLeaf(("Midi File Input"));
		config.Write(("Filter Type"), route->GetType());
		switch(route->GetType()) {
		case RTchannel:
			config.Write(("Channel From"), route->GetInputFrom());
			config.Write(("Channel To"), route->GetInputTo());
			break;
		case RTstaff:
			config.Write(("Track From"), route->GetInputFrom());
			config.Write(("Track To"), route->GetInputTo());
			break;
		case RTelse:
		case RTall:
			break;
		}
		config.toParent();
		mutASSERT(oldpath == config.GetPath());
	}



	/// Loade route settings (filter settings) for a given route
	/** Some route settings (e.g. filter settings) are device type
	 * specific. This function loads them from a tree storage.
	 * \argument config (tree_storage *) Storage class, where the data will be restored from.
	 * \argument route (Route ) Route whos data shall be loaded.
	 */
	void InputMidiFile::Load (tree_storage & config, RouteClass *  route)
	{
#ifdef DEBUG
		std::string oldpath = config.GetPath();
#endif
		config.toLeaf(("Midi File Input"));
		route -> SetType((RouteType) config.Read(("Filter Type"), (int)RTchannel));
		switch(route->GetType()) {
		case RTchannel:
		{
			int oldfrom, oldto;
			route->SetInputFrom(oldfrom = config.Read(("Channel From"), GetMinChannel()));
			route->SetInputTo(oldto = config.Read(("Channel To"), GetMaxChannel()));
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
				runtime_error(mutabor::generic_warning,
					      boost::str(boost::format(_mut("The Channel range %d--%d of the MIDI file %s must be inside %d--%d. The current route had to be corrected."))
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
			route -> SetInputFrom(oldfrom = config.Read(("Track From"), GetMinTrack()));
			route -> SetInputTo(oldto = config.Read(("Track To"), GetMaxTrack()));
			bool correct = true;
			if (oldfrom < GetMinTrack()) {
				correct = false;
				route->SetInputFrom(GetMinTrack());
			}
			if (oldfrom > GetMaxTrack()) {
				correct = false;
				route->SetInputFrom(GetMaxTrack());
			}
			if (oldto < GetMinTrack()) {
				correct = false;
				route->SetInputTo(GetMinTrack());
			}
			if (oldto > GetMaxTrack()) {
				correct = false;
				route->SetInputTo(GetMaxTrack());
			}
			if (!correct)
				runtime_error(mutabor::generic_warning,
					      boost::str(boost::format(_mut("The Track range %d--%d of the MIDI file %s must be inside %d--%d. The current route had to be corrected."))
								       % oldfrom
								       % oldto
								       % GetName().c_str()
								       % GetMinTrack()
								       % GetMaxTrack()));
			break;
		}
		case RTelse:
		case RTall:
			break;
		}
		config.toParent();
		mutASSERT(oldpath == config.GetPath());
	}


	bool InputMidiFile::Open()
	{
		mutASSERT(!isOpen);
		DEBUGLOG (midifile, "start" );
		Tracks.clear();
		char Header[5] = {0,0,0,0,0};   // storage for header mark
		size_t nTrack;
		uint32_t l;
		timing.reset();

		if (Name.empty()) {
			runtime_error(generic_error,
				      _mut("You instructed me to open a file without file name. I can't do that."));
			Mode = DeviceCompileError;
			isOpen = false;
			Tracks.clear();
			return false;
		}

		// read file
		boost::filesystem::detail::utf8_codecvt_facet utf8;
		boost::filesystem::path p;
		p.assign(Name, utf8);

		boost::filesystem::ifstream is(p,
					       std::ios::in | std::ios::binary);
		if ( is.bad() ) {
			DEBUGLOG (midifile, "Opening Stream failed" );
			runtime_error(generic_error,
				      boost::str(boost::format(_mut("Can not open Midi input file '%s'."))
						 % Name.c_str()));
			goto error_cleanup;
		}

		// Header Chunk
		// Flawfinder: ignore
		is.read(Header, 4);
		if (strcmp(Header,"MThd")) {
			runtime_error(generic_error,
				      boost::str(boost::format(_mut("File '%s' is not a valid midi file."))
						 % Name.c_str()));
			goto error_cleanup;
		}

		l = mutabor::ReadLength(is);

		if (l!=6) {
			runtime_error(generic_error,
				      boost::str(boost::format(_mut("Unknown header (chunk length %d) in file '%s'."))
						 % l % Name.c_str()));
			goto error_cleanup;
		}

		int a, b;

		// file type
		if ((a = is.get()) == EOF) {
			runtime_error(generic_error,
				      boost::str(boost::format(_mut("Unexpected end of MIDI file '%s'."))
						 % Name.c_str()));
			goto error_cleanup;
		}
		if ((b = is.get()) == EOF) {
			runtime_error(generic_error,
				      boost::str(boost::format(_mut("Unexpected end of MIDI file '%s'."))
						 % Name.c_str()));
			goto error_cleanup;
		}
		FileType = (a << 8) | b; //mutGetC(is,FileType);
		if (FileType > 3) {
			runtime_error(generic_error,
				      boost::str(boost::format(_mut("Unknown file type %d in file '%s'."))
						 % FileType % Name.c_str()));
			goto error_cleanup;
		}

		// number of tracks
		if ((a = is.get()) == EOF) {
			runtime_error(generic_error,
				      boost::str(boost::format(_mut("Unexpected end of MIDI file '%s'."))
						 % Name.c_str()));
			goto error_cleanup;
		}
		if ((b = is.get()) == EOF) {
			runtime_error(generic_error,
				      boost::str(boost::format(_mut("Unexpected end of MIDI file '%s'."))
						 % Name.c_str()));
			goto error_cleanup;
		}

		nTrack = (a << 8) | b;

		// speed info
		if ((a = is.get()) == EOF) {
			runtime_error(generic_error,
				      boost::str(boost::format(_mut("Unexpected end of MIDI file '%s'."))
						 % Name.c_str()));
			goto error_cleanup;
		}
		if ((b = is.get()) == EOF) {
			runtime_error(generic_error,
				      boost::str(boost::format(_mut("Unexpected end of MIDI file '%s'."))
						 % Name.c_str()));
			goto error_cleanup;
		}
		try {
			timing.set_MIDI_tick_signature(a,b);
		} catch (const std::range_error & e) {
			runtime_error(generic_error,
				      boost::str(boost::format(_mut("Midi file '%s' has corrupted timing information."))
						 % Name.c_str()));
		}
		DEBUGLOG(midifile,
			 ("File type: %d; Tracks: %d; Speed: %d Ticks/Qarter"),
			 FileType,
			 (int)nTrack,
			 (int)timing.get_ticks());

		// remaining (unknown) part of the header
		for (uint32_t i = 6; i < l && !is.eof() && is.good(); i++ )
			a = is.get();// mutGetC(is,a);

		// Tracks lesen
		Tracks.resize(nTrack);
		channel_data.resize(16*nTrack);
		if (Tracks.empty()) {
			runtime_error(generic_error,
				      boost::str(boost::format(_mut("Could not allocate memory for the track list of file '%s'."))
						 %Name.c_str()));
			goto error_cleanup;
		}

		try {
			for (size_t i = 0 ; i < Tracks.size() ; ++i ) {
				auto & t = Tracks[i];

				t.setTiming(timing);
				t.SetName(boost::lexical_cast<std::string>(i));
				t.Load(is,Name);
			}

			for (auto & c : channel_data) {
				c.Reset();
			}
		} catch (const mutabor::error::runtime_exception & e) {
			Mode = DeviceCompileError;
			runtime_error(e.get_type(),e.what());
			goto error_cleanup;
		}
#if 0
		for (size_t i = 0; i < nTrack; i++ ) {

			is.read(Header, 4);
			if (strcmp(Header,"MTrk")) {
				runtime_error(error,
					      boost::str(boost::format(_mut("File '%s' has a broken track header."))
							 % Name.c_str()));
				goto error_cleanup;
			}

			l = mutabor::ReadLength(is);

			Tracks[i].clear();
			try {
				Tracks[i].resize(l);
			} catch (const std::bad_alloc & e) {
				Tracks[i].clear();
			}

			if ( Tracks[i].size() < l) {
				Mode = DeviceCompileError;
				runtime_error(error,
					      boost::str(boost::format(_mut("Could not allocate data for track %d of MIDI input file '%s'."))
							 % i % Name.c_str()));
				goto error_cleanup;
			}


			if ( l > 0x10000000) {
				// in order to avoid problems with 32bit integers we read large tracks in 3 chunks

				is.read((char*)(Tracks[i].data()), l/3);
				is.read((char*)(Tracks[i].data())+l/3, l/3);
				is.read((char*)(Tracks[i].data())+l/3+l/3,l-l/3- l/3);
			} else
				is.read((char*)(Tracks[i].data()), l);

			if ( is.bad() ) {
				runtime_error(error,
					      boost::str(boost::format(_mut("The MIDI input file “%s” is corrupted. This has been detected while reading track %d."))
							 % Name.c_str() % i));
				goto error_cleanup;
			}

			channel_data[i].Reset();
		}
#endif

		return base::Open();

	error_cleanup:
		Mode = DeviceCompileError;
		isOpen = false;
		Tracks.clear();
		return false;
	}

	void InputMidiFile::Close()
	{
		base::Close();

		if ( Mode == DeviceCompileError )
			return;

		Tracks.clear();
	}

	void InputMidiFile::Stop()
	{
		base::Stop();

		// OK ?
		if ( Mode == DeviceCompileError )
			return;

		// Delta-Times lesen
		minDelta = NO_DELTA();
		timing.reset();

		for (size_t i = 0; i < Tracks.size(); i++ ) {
			Tracks[i].ResetPosition(0,true);
			try {
				minDelta = std::min(minDelta, Tracks[i].ReadDelta());
			} catch (...) {
				exception_error(false);
			}
		}
	}

	microseconds InputMidiFile::PrepareNextEvent()
	{
		microseconds passedDelta = minDelta;
		microseconds NewMinDelta = NO_DELTA();
		for (size_t i = 0; i < Tracks.size(); i++ ) {
			microseconds delta = Tracks[i].GetDelta();
			DEBUGLOG (midifile, "Track: %d, delta: %ld μs" ,(int)i,delta);
			if ( delta  == NO_DELTA() )
				continue;
			if ( delta <= passedDelta )
				delta = ReadMidiProceed(i, passedDelta);
			else
				delta = Tracks[i].PassDelta(passedDelta);

			if (delta != NO_DELTA() &&
			    delta < NewMinDelta ) {
					NewMinDelta = delta;
			}
			DEBUGLOG (midifile, "Track: %d, delta: %ld μs" ,(int)i,Tracks[i].GetDelta());
		}
		DEBUGLOG (midifile, "Next event after %ld μs (MUTABOR_NO_DELTA = %ld)" ,minDelta,NO_DELTA());
		minDelta = NewMinDelta;
		return NewMinDelta;
	}

	microseconds InputMidiFile::ReadMidiProceed(size_t nr, microseconds deltatime)
	{
		microseconds Delta = Tracks[nr].GetDelta();
		mutASSERT(Delta >= microseconds(-1000000));
		microseconds time = deltatime;

		while ( time >= Delta ) {

			// Delta Time
			mutASSERT(time >= Delta);
			time -= Delta;
			Tracks[nr].PassDelta(Delta);
			Track::base message = Tracks[nr].ReadMessage();

			if (message.size() >= 2 && message[0] == midi::META) {
				switch (message[1]) {
				case midi::META_END_OF_TRACK:
					Tracks[nr].Stop();
					Delta = NO_DELTA();
					break;
				case midi::META_SET_TEMPO: {
					size_t j,e;
					set_tempo_event *ev
						= static_cast<set_tempo_event*>
						(create_event(message,-1));
					if (!ev) {
						break;
					}
					event guard = ev;

					// file type 0 must not have more than
					// 1 track file we treat it like type
					// one even though files with multiple
					// tracks are corrupted.  type 2 has
					// independent tracks
					if (FileType > 1) {
						j = nr; e = nr+1;
					} else {
						j = 0; e = Tracks.size();
					}
					for (; j < e; j++ )
						Tracks[j].SetQuarterDuration(ev->get_tempo(),
									     true,
									     j>nr ? deltatime - time: (microseconds::zero()));

					DEBUGLOG(midifile,
						 ("Change tempo to %ldμs per quarter (next event after %ld)"),
						 ev->get_tempo(), minDelta);
				}

				}
			}

			Proceed(message, nr, nr << 4);

			if (Delta ==  NO_DELTA())
				return Delta;

			Delta = Tracks[nr].ReadDelta();

			DEBUGLOG(midifile,
				 ("Next event on Track %d after %ld μs"),
				 (int)nr, Delta);
		}
#ifdef DEBUG
		microseconds checktime =
#endif
			Tracks[nr].PassDelta(time);

#ifdef DEBUG
		mutASSERT(checktime == Delta - time);
#endif
		return Delta - time;
	}


	void InputMidiFile::Proceed(const std::vector<unsigned char > &midiCode,
				    int data,
				    size_t channel_offset) {
		/** \todo implement system messages */
		size_t MidiChannel = makeChannel(midiCode,
						 channel_offset);
		uint8_t MidiStatus  = midiCode[0];
		DEBUGLOG (midifile, "Status: %x" , MidiStatus);

		switch ( MidiStatus ) {
		case midi::CLOCK:
		case midi::TICK:
		case midi::SYSTEM_UNDEFINED1:
		case midi::SYSTEM_UNDEFINED2:
		case midi::SYSEX_END:
		case midi::REALTIME_UNDEFINED:
		case midi::ACTIVE_SENSE:
		case midi::STOP_PLAY:
		case midi::START_PLAY:
		case midi::CONTINUE_PLAY:
		case midi::QUARTER_FRAME:
			/* unimplemented or intentionally ignored */
			return;
		case midi::SONG_SELECT:
		case midi::SONG_POSITION: {
			event e = create_event(midiCode,
					       MidiChannel);
			OutputDeviceClass::all_handle_event(e);
		}
			return;
			// the following are handled by midicmn.cpp
		case midi::META:
		case midi::TUNE_REQUEST:
		case midi::SYSEX_START:
		default:
			break;
		}

		base::Proceed(midiCode, data, channel_offset);
	}


	InputMidiFile::operator std::string() const {
		return InputDeviceClass::operator std::string() +
			boost::str(boost::format("\n\
  FileType = %d\n\
  Tracks: %d\n\
  minDelta = %ld\n				\
  Busy = %d\n")
				   % FileType
				   % (int)Tracks.size()
				   % minDelta
				   % Busy);
	}


	InputMidiFile::proceed_bool InputMidiFile::shouldProceed(Route R,
								 const std::vector<unsigned char > &midiCode,
								 int track)
	{
		//		DEBUGLOG (midifile, "midiCode: %x, track %d" ,midiCode,track);
		switch ( R->GetType() ) {
		case RTchannel:
			if ( R->Check(midiCode[0] & 0x0F) ) {
				return ProceedYes;
			}
			break;

		case RTstaff:
			if ( R->Check(track) ) {
				return ProceedYes;
			}
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

	MidiFileFactory::~MidiFileFactory() {}

	OutputDeviceClass * MidiFileFactory::DoCreateOutput (const std::string & name,
							     int id) const
	{
		return new OutputMidiFile(name,id);
	}

	InputDeviceClass * MidiFileFactory::DoCreateInput (const std::string & name,
							   MutaborModeType mode,
							   int id) const
	{
		return new InputMidiFile(name,mode,id);
	}

}


///\}
