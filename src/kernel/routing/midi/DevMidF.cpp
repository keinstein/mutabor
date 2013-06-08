/** \file
 ********************************************************************
 * MIDI-File as device.
 *
 * \author Rüdiger Krauße <krausze@mail.berlios.de>
 *         Tobias Schlemmer <keinstein@users.berlios.de>
 * \date $Date: 2011/11/02 14:31:57 $
 * \version $Revision: 1.13 $
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
// ------------------------------------------------------------------
// Mutabor 3, 1998, R.Krauße
// MIDI-File als Device
// ------------------------------------------------------------------
#include "src/kernel/Defs.h"
#if defined(MUTWIN) && !defined(WX)
#include <owl/pch.h>
#endif

#ifdef RTMIDI
#  include "RtMidi.h"
#else
#ifndef H_MMSYSTEM
//  #define WINVER 0x030a
#include <mmsystem.h>
#define H_MMSYSTEM
#endif
#endif

#include "src/kernel/routing/midi/DevMidF.h"
#include "src/kernel/routing/midi/DevMidi.h"
#include "src/kernel/Execute.h"
#include "src/kernel/GrafKern.h"
#include "src/kernel/Runtime.h"
#include "src/kernel/routing/Route-inlines.h"

#include "wx/wfstream.h"
#include "wx/msgdlg.h"
#include <inttypes.h>

#include "src/kernel/routing/midi/midicmn-inlines.h"

namespace mutabor {
	using namespace midi;
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

	static DWORD ReadLength(mutIFstream &is)
	{
		BYTE a[4] = {0,0,0,0};
		mutReadStream(is,(char*)a, 4);
		return (((DWORD)a[0]) << 24) + (((DWORD)a[1]) << 16) +
			(((DWORD)a[2]) << 8) + ((DWORD)a[3]);
	}



// Tracks -----------------------------------------------------------

	mutint64 Track::ReadDelta()
	{
		mutASSERT(remaining_delta != MUTABOR_NO_DELTA);
		current_delta = ReadInt();
		DEBUGLOG(midifile,_T("%s"),(this->c_str()));
		remaining_delta += timing.get_time_midi(current_delta);
		return remaining_delta;
	}

	void Track::WriteDelta()
	{
		mutint64 newtime = CurrentTime.Get();
		mutint64 Deltatime = std::max(newtime - Time,(mutint64)0);
		// note: Deltatime may be a little bit ahead if get_delta rounds up
		mutint64 Delta = timing.get_delta_midi(Deltatime);
		DEBUGLOG(midifile,
			 _T("Deltatime = %ld, Delta = %ld, get_time_midi(Delta) = %ld, get_delta_midi(get_time_midi(Delta)) = %ld"),
			 Deltatime, Delta, timing.get_time_midi(Delta), timing.get_delta_midi(timing.get_time_midi(Delta)));
		mutASSERT(timing.get_delta_midi(timing.get_time_midi(Delta)) == Delta);
		// we should take care of rounding errors
		//Time = newtime + timing.get_time(Delta) - Deltatime;
		Time += timing.get_time_midi(Delta);

		// if the Delta time is bad wite a correct number
		mutASSERT(0 <= Delta);
		mutASSERT(Delta < 0x0FFFFFFF);
		WriteNumber(Delta < 0x0FFFFFFF ? (0 <= Delta ? Delta : 0): 0x0FFFFFFF);
	}

	uint32_t Track::ReadInt() {
		uint32_t l = 0;
		uint8_t a;

		int i =0 ; 
		do {
			if (++i > 4) {
				throw delta_length_error(gettext_noop("Number contains too many bytes"));
			}
			a = at(position);
			position++;
			l = (l << 7) + (a & 0x7F);
		} while (a & 0x80);
		return l;
	}


	Track::base Track::ReadMessage() {
		uint8_t status, metatype;
		if ((status = at(position)) & 0x80) {
			position++;
			if (midi::reset_running_status (status)) 
				running_status = 0;
			else if (store_running_status(status)) 
				running_status = status;
		} else status = running_status;
		if (! status & 0x80) {
			throw invalid_status (gettext_noop("Invalid status byte"));
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

		data_bytes += offset;
 		base retval(data_bytes,status);
		if (status == midi::META) 
			retval[1] = metatype;

		for (size_t i = offset ; i < (size_t)data_bytes ; i++ ) 
			retval [i] = at(position++); // should throw on access violation.

		return retval;
	}

	void Track::WriteLength(mutOFstream &os, size_t l)
	{
		mutPutC(os,(BYTE) ((l >> 24) & 0xFF));
		mutPutC(os,(BYTE) ((l >> 16) & 0xFF));
		mutPutC(os,(BYTE) ((l >> 8) & 0xFF));
		mutPutC(os,(BYTE) (l & 0xFF));
	}

	void Track::Save(mutOFstream &os)
	{
		mutWriteStream(os,"MTrk",4);

		const uint8_t tempo_events[] = {
			/// \todo Implement Format 2 files with one separate track for each route
			
			/* Tempo map will be needed for Format 1 files
			 * in these files the first track contains all tempo changes
			 */
			
			0x00,                                  // delta 0
			midi::META, midi::META_SET_TEMPO,      // meta event
			0x03,                                  // 3 data bytes
			0x07, 0xD0, 0x00,                      // 462080 μs/qarter
			
			0x00,                                  // delta 0
			midi::META, midi::META_TIME_SIGNATURE, // meta event
			0x04,                                  // 4 data bytes
			0x04,                                  // numerator of 4/4
			0x02,                                  // exp. of denominator of 4/(2^2)
			0x18,                                  // 1 metronome click = 18 clocks
			0x08                                  // 8/32 = 1/4
		};

		static const uint8_t EOT[] = {0x00, midi::META, midi::META_END_OF_TRACK, 0x00};

		WriteLength(os, 15+size()+4);

		mutWriteStream(os,tempo_events,15);
		mutWriteStream(os,data(),size());
		mutWriteStream(os,EOT,4);
	}

	wxString Track::TowxString () {
		return wxString::Format(_T("\
timing: %s\n\
Time = %ld, position = %d/%d, current_delta = %ld, remaining_delta = %ld\n\
Running status = %d (%x), running_sysex = %s, SysEx Id = %d (%x)"),
					timing.TowxString().c_str(),
					Time,position,size(),current_delta,remaining_delta,
					running_status,running_status,running_sysex?_T("true"):_T("false"),sysex_id,sysex_id);
	}

// OutputMidiFile ------------------------------------------------------

/// Save current device settings in a tree storage
/** \argument config (tree_storage) storage class, where the data will be saved.
 */
	void OutputMidiFile::Save (tree_storage & config) 
	{
#ifdef DEBUG
		wxString oldpath = config.GetPath();
#endif
		config.Write(_T("Bending Range"),bending_range);
		config.Write(_T("File Name"),Name);
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
		wxString oldpath = config.GetPath();
#endif
		config.toLeaf(_T("Midi File Output"));
		mutASSERT(route);
		config.Write(_T("Avoid Drum Channel"), route->OutputAvoidDrumChannel());
		config.Write(_T("Channel Range From"), route->GetOutputFrom());
		config.Write(_T("Channel Range To"), route->GetOutputTo());
		config.toParent();
		mutASSERT(oldpath == config.GetPath());
	}


        /// Load current device settings from a tree storage
        /** \argument config (tree_storage) storage class, where the data will be loaded from.
	 */
	void OutputMidiFile::Load (tree_storage & config)
	{
#ifdef DEBUG
		wxString oldpath = config.GetPath();
#endif
		bending_range=config.Read(_T("Bending Range"), bending_range);
		Name = config.Read(_T("File Name"),mutEmptyString);
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
		wxString oldpath = config.GetPath();
#endif
		config.toLeaf(_T("Midi File Output"));
		mutASSERT(route);
		route->OutputAvoidDrumChannel(config.Read (_T("Avoid Drum Channel"), true));
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
			wxMessageBox(wxString::Format(_("The Channel range %d--%d of the MIDI file %s must be inside %d--%d. The current route had to be corrected."),
						      oldfrom,oldto,GetName().c_str(),GetMinChannel(),GetMaxChannel()),
				     _("Warning loading route"),wxICON_EXCLAMATION);
		config.toParent();
		mutASSERT(oldpath == config.GetPath());
	}


	void OutputMidiFile::Close()
	{
		base::Close();

		mutOpenOFstream(os,Name);
		Out.Save(os);
	}



#ifdef WX
	wxString OutputMidiFile::TowxString() const {
		wxString s = OutputDeviceClass::TowxString() +
			wxString::Format(_T("\n  Name = %s\n  DevId = %d\n  Bending Range = %d\n  nKeyOn"),
					 Name.c_str(), DevId, bending_range, nKeyOn);
	
		s.Printf(_T("]\n  ton_auf_kanal = [ t=%d,k=%d,f=%d"), 
			 ton_auf_kanal[0].inkey, 
			 ton_auf_kanal[0].outkey);
		for (int i = 1; i<16; i++)
			s.Printf(_T("; t=%d,k=%d,f=%d"), 
				 ton_auf_kanal[i].inkey, 
				 ton_auf_kanal[i].outkey);
		s+=_T("]");
		return s;
		}
#endif

#if 0
	void OutputMidiFile::ReadData(wxConfigBase * config) 
	{
		bending_range = config->Read(_("Bending_Range"),
					     (long)bending_range);
	}

	void OutputMidiFile::WriteData(wxConfigBase * config) 
	{
		config->Write(_("Bending_Range"), (long)bending_range);
	}
#endif

       
// InputMidiFile -------------------------------------------------------

/*
  void CALLBACK _export MidiTimeFunc(UINT wTimerID, UINT wMsg, DWORD dwUser, DWORD dw1, DWORD dw2)
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
		wxString oldpath = config.GetPath();
#endif
		config.toLeaf(_T("Midi File Input"));
		config.Write(_T("Filter Type"), route->GetType());
		switch(route->GetType()) {
		case RTchannel: 
			config.Write(_T("Channel From"), route->GetInputFrom());
			config.Write(_T("Channel To"), route->GetInputTo());
			break;
		case RTstaff:
			config.Write(_T("Track From"), route->GetInputFrom());
			config.Write(_T("Track To"), route->GetInputTo());
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
		wxString oldpath = config.GetPath();
#endif
		config.toLeaf(_T("Midi File Input"));
		route -> SetType((RouteType) config.Read(_T("Filter Type"), (int)RTchannel));
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
				wxMessageBox(wxString::Format(_("The Channel range %d--%d of the MIDI file %s must be inside %d--%d. The current route had to be corrected."),
							      oldfrom,oldto,GetName().c_str(),GetMinChannel(),GetMaxChannel()),
					     _("Warning loading route"),wxICON_EXCLAMATION);
			break;
		}
		case RTstaff:
		{
			int oldfrom, oldto;
			route -> SetInputFrom(oldfrom = config.Read(_T("Track From"), GetMinTrack()));
			route -> SetInputTo(oldto = config.Read(_T("Track To"), GetMaxTrack()));
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
				wxMessageBox(wxString::Format(_("The Track range %d--%d of the MIDI file %s must be inside %d--%d. The current route had to be corrected."),
							      oldfrom,oldto,GetName().c_str(), GetMinTrack(), GetMaxTrack()),
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


	bool InputMidiFile::Open()
	{
		mutASSERT(!isOpen);
		DEBUGLOG (midifile, _T("start"));
		Tracks.clear();
		char Header[5] = {0,0,0,0,0};   // storage for header mark
		size_t nTrack;
		DWORD l;
		timing.reset();
		

		// read file
		mutOpenIFstream(is, Name);

		if ( mutStreamBad(is) ) {
			DEBUGLOG (midifile, _T("Opening Stream failed"));
			LAUFZEIT_ERROR1(_("Can not open Midi input file '%s'."), Name.c_str());
			goto error_cleanup;
		}

		// Header Chunk
		// Flawfinder: ignore
		mutReadStream(is,Header, 4);
		if (strcmp(Header,"MThd")) {
			LAUFZEIT_ERROR1(_("File '%s' is not a valid midi file."), Name.c_str())	;
			goto error_cleanup;
		}

		l = mutabor::ReadLength(is);

		if (l!=6) {
			LAUFZEIT_ERROR2(_("Unknown header (chunk length %d) in file '%s'."),l, Name.c_str());
			goto error_cleanup;
		}

		BYTE a, b;

		// file type
		a = mutGetC(is); //mutGetC(is,a);
		FileType = ((int)a << 8) + mutGetC(is); //mutGetC(is,FileType);
		if (FileType > 3) {
			LAUFZEIT_ERROR2(_("Unknown file typ %d in file '%s'."), FileType, Name.c_str());
			goto error_cleanup;
		}

		// number of tracks
		a = mutGetC(is); //mutGetC(is,a);
		b = mutGetC(is); // mutGetC(is,b);
		nTrack = (((int)a) << 8) + b;

		// speed info
		a = mutGetC(is); //mutGetC(is,a);
		b = mutGetC(is); //mutGetC(is,b);
		try {
			timing.set_MIDI_tick_signature(a,b);
		} catch (std::range_error e) {
			LAUFZEIT_ERROR(_("Midi file '%s' has corrupted timing information."), Name.c_str())	;
		}
		DEBUGLOG(midifile, 
			 _T("File type: %d; Tracks: %d; Speed: %d Ticks/Qarter"),
			 FileType, 
			 nTrack, 
			 timing.get_ticks());

		// rest of header
		DWORD i;

		for (i = 6; i < l && !mutStreamEOF(is) && mutStreamGood(is); i++ )
			a = mutGetC(is);// mutGetC(is,a);

		// Tracks lesen
		Tracks.resize(nTrack,Track(timing));
		if (Tracks.empty()) {
			LAUFZEIT_ERROR1(_("Could not allocate memory for the track list of file '%s'."), Name.c_str())	;
			goto error_cleanup;
		}

		for (i = 0; i < nTrack; i++ ) {
			mutReadStream(is,Header, 4);
			if (strcmp(Header,"MTrk")) {
				LAUFZEIT_ERROR(_("File '%s' has a broken track header."), Name.c_str())	;
				goto error_cleanup;
			}

			l = mutabor::ReadLength(is);

			Tracks[i].clear();
			try {
				Tracks[i].resize(l);
			} catch (std::bad_alloc e) {
				Tracks[i].clear();
			}

			if ( Tracks[i].size() < l) {
				Mode = DeviceCompileError;
				LAUFZEIT_ERROR(_("Could not allocate data for track %d of MIDI input file '%s'."),
						i, Name.c_str());
				goto error_cleanup;
			}
			
			
			if ( l > 0x10000000) {
				// in order to avoid problems with 32bit integers we read large tracks in 3 chunks
				
				mutReadStream(is, (char*)(Tracks[i].data()), l/3);
				mutReadStream(is, (char*)(Tracks[i].data())+l/3, l/3);
				mutReadStream(is, (char*)(Tracks[i].data())+l/3+l/3,l-l/3- l/3);
			} else
				mutReadStream(is, (char*)(Tracks[i].data()), l);

			if ( mutStreamBad(is) ) {
				LAUFZEIT_ERROR( _("The MIDI input file “%s” is corrupted. This has been detected while reading track %d."),
					  Name.c_str(),i);
				goto error_cleanup;
			}
		}

		mutCloseStream(is);
		
		return base::Open();

	error_cleanup:
		Mode = DeviceCompileError;
		isOpen = false;
		mutCloseStream(is);
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
		minDelta = MUTABOR_NO_DELTA;
		timing.reset();

		for (size_t i = 0; i < Tracks.size(); i++ ) {
			Tracks[i].ResetPosition(0,true);
#warning Implement catching of dalta_length_error
			minDelta = std::min(minDelta, Tracks[i].ReadDelta());
		}
	}

	mutint64 InputMidiFile::PrepareNextEvent()
	{
		mutint64 passedDelta = minDelta;
		mutint64 NewMinDelta = MUTABOR_NO_DELTA;
		for (size_t i = 0; i < Tracks.size(); i++ ) {
			mutint64 delta = Tracks[i].GetDelta();
			DEBUGLOG(midifile,_T("Track: %d, delta: %ld μs"),i,delta);
			if ( delta  == MUTABOR_NO_DELTA ) 
				continue;
			if ( delta <= passedDelta )
				delta = ReadMidiProceed(i, passedDelta);
			else 
				delta = Tracks[i].PassDelta(passedDelta);
			
			if (delta != MUTABOR_NO_DELTA && 
			    delta < NewMinDelta ) {
					NewMinDelta = delta;
			}
 			DEBUGLOG(midifile,_T("Track: %d, delta: %ld μs"),i,Tracks[i].GetDelta());
		}
		DEBUGLOG(midifile,_T("Next event after %ld μs (MUTABOR_NO_DELTA = %ld)"),minDelta,MUTABOR_NO_DELTA);
		minDelta = NewMinDelta;
		return NewMinDelta;
	}

	mutint64 InputMidiFile::ReadMidiProceed(size_t nr, mutint64 deltatime)
	{
		mutint64 Delta = Tracks[nr].GetDelta();
		mutASSERT(Delta >= -1000000);
		mutint64 time = deltatime;

		while ( time >= Delta ) {

			// Delta Time
			mutASSERT(time >= Delta);
			time -= Delta;
			Tracks[nr].PassDelta(Delta);
			Track::base message = Tracks[nr].ReadMessage();

			uint8_t status = message[0];
			int a = status;

			if ( status  <  midi::SYSTEM ) // normaler midi code
			{
				
				int l = message.size();
				mutASSERT(l<4);
				int shift = 8;

				for (int i = 1; i < l; i++)
				{
					a += (int)(message[i]) << shift;
					shift += 8;
				}
			}
			else switch (status) {
				case midi::SYSEX_START:
				case midi::SYSEX_END:
				{
#warning Implement SysEx handling in MIDI files
				} 
				break;
				case midi::META: // meta event
				{
					uint8_t meta_type = message[1];

/// \todo how do we deal with wrong meta event lenghts? If the rest the file is syntactically intact we can proceed.
					switch (meta_type) {
#if 0
// according to the MIDI specification the time signature provides
// interpretation for metronomes, but not for delta times
					case midi::META_TIME_SIGNATURE: 
						if (message.size() >= 2+4) {
							TicksPerQuarter = Track[nr][TrackPos[nr]+2];
							DEBUGLOG(midifile,_T("Change time signature to  %d ticks/qarter"),
								 TicksPerQuarter);
						}
						break;
#endif
					case midi::META_SET_TEMPO:
						if (message.size() >= 2+3) {
							long NewQuarterDuration =
								(((int)message[2]) << 16) +
								(((int)message[3]) << 8) +
								(((int)message[4]));
						
							size_t j,e;
							// file type 0
							// must not
							// have more
							// than 1
							// track file
							// we treat it
							// like type
							// one even
							// though
							// files with
							// multiple
							// tracks are
							// corrupted.
							// type 2 has
							// independent
							// tracks
							if (FileType > 1) {
								j = nr; e = nr+1;
							} else {
								j = 0; e = Tracks.size();
							}
							for (; j < e; j++ )
								Tracks[j].SetQuarterDuration(NewQuarterDuration, 
											     true, 
											     j>nr ? deltatime - time: (mutint64)0);
							
							DEBUGLOG(midifile,
								 _T("Change tempo to %ldμs per quarter (next event after %ld)"),
								 NewQuarterDuration, minDelta);
						}
						break;
					case midi::META_END_OF_TRACK:
						Tracks[nr].Stop();
						return MUTABOR_NO_DELTA;
						break;
					}
				}
				break;
				case midi::SONG_POSITION: 
					a += message[1] << (8 + message[2]) << 16;
					break;
				case midi::SONG_SELECT:
					a += message[1] << 8;
					break;
				}
			Proceed(a, nr);

			Delta = Tracks[nr].ReadDelta();
		
			DEBUGLOG(midifile,
				 _T("Next event on Track %d after %ld μs"),
				 nr, Delta);
		}
#ifdef DEBUG
		mutint64 checktime = 
#endif
			Tracks[nr].PassDelta(time);

#ifdef DEBUG
		mutASSERT(checktime == Delta - time);
#endif
		return Delta - time;
	}

#define MIDICODE(i)				\
	(0xff & (midiCode >> (8*i)))
//(((BYTE*)(&midiCode))[i])

// f¸r bestimmte Route Codeverarbeitung

	
#ifdef WX
	wxString InputMidiFile::TowxString() const {
		return InputDeviceClass::TowxString() +
			wxString::Format(_T("\n\
  FileType = %d\n\
  Tracks: %d\n\
  minDelta = %ld\n				\
  Busy = %d\n"),
					 FileType, 
					 Tracks.size(), 
					 minDelta,
					 Busy);
	}
#endif
	

// Routen testen und jenachdem entsprechend Codeverarbeitung
	InputMidiFile::proceed_bool InputMidiFile::shouldProceed(Route R, DWORD midiCode, int track)
	{
		DEBUGLOG(midifile,_T("midiCode: %x, track %d"),midiCode,track);
		switch ( R->GetType() ) {
		case RTchannel:
			if ( R->Check(midiCode & 0x0F) ) {
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
			break;
			
		case RTall:
			return ProceedYes;
			break;
		default:
			UNREACHABLEC;
		}
		return ProceedNo;
	}
	InputMidiFile::proceed_bool InputMidiFile::shouldProceed(Route R, 
								 const std::vector<unsigned char > * midiCode,
								 int track)
	{
		mutASSERT(midiCode);
		if (midiCode->at(0) != midi::SYSTEM) 
			UNREACHABLEC;

		switch ( R->GetType() ) {
		case RTchannel:
//			if ( R->Check(midiCode & 0x0F) ) {
				return ProceedYes;
//			}
			break;

		case RTstaff:
			if ( R->Check(track) ) {
				return ProceedYes;
			}
			break;
		case RTelse:
//			return ProceedElse;
			return ProceedYes;
			break;
			
		case RTall:
			return ProceedYes;
			break;
		default:
			UNREACHABLEC;
		}
		return ProceedNo;
	}

	MidiFileFactory::~MidiFileFactory() {}

	OutputDeviceClass * MidiFileFactory::DoCreateOutput () const
	{
		return new OutputMidiFile();
	}

	OutputDeviceClass * MidiFileFactory::DoCreateOutput (int devId,
						      const mutStringRef name, 
						      int id) const
	{
		return new OutputMidiFile(devId,name,id);
	}

	OutputDeviceClass * MidiFileFactory::DoCreateOutput (int devId,
						      const mutStringRef name, 
						      MutaborModeType mode, 
						      int id) const
	{
 		STUBC;
		return NULL;
#if 0
		return new OutputMidiFile(devId,name,id);
#endif
	}


	InputDeviceClass * MidiFileFactory::DoCreateInput () const
		
	{
		return new InputMidiFile();
	}

	InputDeviceClass * MidiFileFactory::DoCreateInput (int devId,
							   const mutStringRef name, 
							   int id) const
	{
		return new InputMidiFile(devId,name,DeviceStop,id);
	}

	InputDeviceClass * MidiFileFactory::DoCreateInput (int devId,
							   const mutStringRef name, 
							   MutaborModeType mode, 
							   int id) const
	{
		return new InputMidiFile(devId,name,mode,id);
	}

}


///\}
