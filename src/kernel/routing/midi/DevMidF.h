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
		wxLongLong Time;
		Track(): base(), Time() {
			reserve(100);
		}

		~Track() {}

		void WriteDelta();
		void WriteNumber(size_t count) {
			int i = 0;
			size_t mask = 0x7F << 7;
			while(count & mask) {
				i++;
			}
			mutASSERT(i<6);// 32bit/7bit = 4.571 > 4 
			for (;i>=0;i--) 
				push_back((count >> i*7) & 0x7F);
		}
		void WriteLength(mutOFstream &os, size_t l);
	
		void MidiOut(uint8_t c1, uint8_t c2, uint8_t c3) {
			WriteDelta();
			push_back(c1);
			push_back(c2);
			push_back(c3);
		}

		void MidiOut(uint8_t c1, uint8_t c2) {
			WriteDelta();
			push_back(c1);
			push_back(c2);
		}

		void MidiOut(uint8_t c1) {
			WriteDelta();
			push_back(c1);
		}

		void SendSysEx (uint8_t * data, size_t count) {
			if (data[0] == midi::SYSEX_START 
			    || data[count-1] == midi::SYSEX_END) {
				UNREACHABLEC;
				return;
			}

			WriteDelta();
			push_back(midi::SYSEX_START);
			WriteNumber(count+1);
			for (size_t i = 0 ; i < count ; i++) {
				push_back(data[i-1]);
			}
			push_back(midi::SYSEX_END);
		}


		void Save(mutOFstream &os);
	};


	class MidiFileOutputProvider {
	public:
		MidiFileOutputProvider():Tracks() {}
		~MidiFileOutputProvider() {}

		bool Open() {
			Tracks.clear();
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
		 * Outputs a system exclusive message.
		 * 
		 * \param channel channel to which data shall be sent
		 *        to. How channels are split into tracks or
		 *        subdevices is managed by the OutputProvider (ignored)
		 * \param byte1 1st byte
		 */
		MidiFileOutputProvider & SendSysEx (int channel,
						    BYTE * data,
						    size_t count) {
			Tracks.SendSysEx(data,count);
			return *this;
		}

		/** 
		 * Write the MIDI file to a stream.
		 * 
		 * \param os stream to write to
		 */
		void Save(mutOFstream &os) {
			Tracks.Save(os);
		}

	protected:

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
#if defined(_MSC_VER)
#pragma warning(push) // Save warning settings.
#pragma warning(disable : 4100) // Disable unreferenced formal parameter warnings
#endif

		virtual void Gis(GisToken * token, char turn)
			{};

		virtual void AddTime(frac time)
			{};

#if defined(_MSC_VER)
#pragma warning(pop) // Restore warnings to previous state.
#endif 

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
	protected:
		OutputMidiFile(): base() {}

		OutputMidiFile(int devId, 
			       const mutStringRef name, 
			       int id = -1, 
			       int bendingRange = 2)
			: base(devId, name, id, bendingRange) {}
	};




// InMidiFile -------------------------------------------------------

	class InputMidiFile : public CommonFileInputDevice
	{
		typedef CommonFileInputDevice base;
		friend class MidiFileFactory;
	protected:
		InputMidiFile(): CommonFileInputDevice(),
				 Track(NULL), 
				 TrackPos(NULL),
				 curDelta(NULL),
				 StatusByte(NULL) { }

		InputMidiFile(int devId,
			      wxString name, 
			      MutaborModeType mode,
			      int id): CommonFileInputDevice(devId, 
							name, 
							mode, 
							id),
					  Track(NULL),
					  TrackPos(NULL),
					  curDelta(NULL),
					  StatusByte(NULL) {}

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

		virtual frac ReadOn(frac time)
			{
				return frac(0, 1);
			}

#if defined(_MSC_VER)
#pragma warning(pop) // Restore warnings to previous state.
#endif 
	
		virtual DevType GetType() const
			{
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
	protected:
		int FileType;
		size_t nTrack;
		int Speed;
		BYTE **Track;
		DWORD *TrackPos;
		mutint64 *curDelta;
		mutint64 minDelta;
		BYTE *StatusByte;
		ChannelData Cd[16];
		//  UINT TimerId;
		BOOL Busy;
		DWORD TicksPerQuarter;
		mutint64 MMSPerQuarter;
		void Proceed(DWORD midiCode, int track);
		void ProceedRoute(DWORD midiCode, Route route);
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


		virtual mutabor::OutputDeviceClass * DoCreateOutput() const;
		
		virtual mutabor::InputDeviceClass * DoCreateInput() const;
		virtual mutabor::OutputDeviceClass * DoCreateOutput(int devId,
							     const mutStringRef name, 
							     int id = -1) const;
		
		virtual mutabor::InputDeviceClass * DoCreateInput(int devId,
							   const mutStringRef name, 
							   int id = -1) const;

		virtual mutabor::OutputDeviceClass * DoCreateOutput(int devId,
							     const mutStringRef name, 
							     mutabor::MutaborModeType mode, 
							     int id = -1) const;
		
		virtual mutabor::InputDeviceClass * DoCreateInput(int devId,
							   const mutStringRef name, 
							   mutabor::MutaborModeType mode, 
							   int id = -1) const;
	};


// Function ---------------------------------------------------------

}

#endif  /* precompiled */
#endif

///\}
