// -*- C++ -*- 
/** \file 
 ********************************************************************
 * Description
 *
 * Copyright:   (c) 2008-2011 TU Dresden
 * \author  Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 
 * $Date: 2012/01/29 22:08:36 $
 * \version $Revision: 1.11 $
 * \license GPL
 *
 *
 *
 ********************************************************************
 * \addtogroup route
 * \{
 ********************************************************************/
// ------------------------------------------------------------------
// Mutabor 3, 1998, R.Krauﬂe
// MidiPort Klassen
// ------------------------------------------------------------------

/* we guard a little bit complicated to ensure the references are set right
 */

#if (!defined(MU32_ROUTING_MIDI_DEVMIDI_H) && !defined(PRECOMPILE)) \
	|| (!defined(MU32_ROUTING_MIDI_DEVMIDI_H_PRECOMPILED))
#ifndef PRECOMPILE
#define MU32_ROUTING_MIDI_DEVMIDI_H
#endif

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

#include "src/kernel/Defs.h"
#include "src/wxGUI/generic/mhDefs.h"
#include "src/kernel/routing/Device.h"

#ifndef MU32_ROUTING_MIDI_DEVMIDI_H_PRECOMPILED
#define MU32_ROUTING_MIDI_DEVMIDI_H_PRECOMPILED

// system headers which do seldom change

#include <cassert>

#ifdef RTMIDI
#include "lib/rtmidi/RtMidi.h"
#else
#ifndef H_MMSYSTEM
//  #define WINVER 0x030a
#include <mmsystem.h>
#define H_MMSYSTEM
#endif
#endif

namespace mutabor {

	extern RtMidiOut * rtmidiout;
	extern RtMidiIn * rtmidiin;

// OutputMidiPort ------------------------------------------------------

	typedef struct TAK
	{
		bool active; //< is this tone active or free?
		int inkey;   //< internal key id. provided by input device
		int outkey;  //< key that has been output to the MIDI device
		int channel; //< route that broght the note to this device
		int midi_channel; //< MIDI channel (unsused)
		size_t unique_id; //< unique id defined by input device
	} TonAufKanal;


	class MidiPortFactory;
	class OutputMidiPort : public OutputDeviceClass
	{
		friend class MidiPortFactory;
	protected:
		int bending_range;
		OutputMidiPort():OutputDeviceClass(), 
				 bending_range (2), 
				 hMidiOut(NULL), 
				 nKeyOn(0) { }

		OutputMidiPort(int devId, 
			       wxString name, 
			       int id = -1, 
			       int bendingRange = 2)
			: OutputDeviceClass(devId, name, id),
			  bending_range (bendingRange), 
			  hMidiOut(NULL), 
			  nKeyOn(0)
			{
				DEBUGLOG(other,_T(""));
			}

	public:
		~OutputMidiPort()
			{};
	
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
		virtual void Load (tree_storage & config, RouteClass *  route);

	
		virtual bool Open();
		virtual void Close();
		virtual void NoteOn(int Box, 
				    int taste, 
				    int velo, 
				    RouteClass * r,
				    size_t id, 
				    ChannelData *cd);
		virtual void NoteOff(int Box, 
				     int taste, 
				     int velo, 
				     RouteClass * r, 
				     size_t id);
		virtual void NotesCorrect(RouteClass * route);
		virtual void Sustain(char on, int channel);
		virtual int  GetChannel(int taste);

#if defined(_MSC_VER)
#pragma warning(push) // Save warning settings.
#pragma warning(disable : 4100) // Disable unreferenced formal parameter warnings
#endif

		virtual void Gis(GisToken *token, char turn)
			{};

		virtual void AddTime(frac time)
			{};

		virtual void MidiOut(DWORD data, size_t n);
		virtual void MidiOut(BYTE * p, size_t n);
#if defined(_MSC_VER)
#pragma warning(pop) // Restore warnings to previous state.
#endif 

		virtual void Quite(RouteClass * r);
		virtual void Panic();
		virtual bool NeedsRealTime()
			{
				return true;
			}

		virtual void SetDevId (int id) {
			bool reopen = false;
			if (id != DevId) {
				DevId = id;
				if ((reopen = IsOpen()))
					Close();
			}
			if (rtmidiout) 
				Name = muT (rtmidiout->getPortName (DevId).c_str());
			else
				Name = _("no device");
			if (reopen) {
				Open();
			}
		}
		
		void SetBendingRange (int r) {
			bending_range = r;
		}

		int GetBendingRange() {
			return bending_range;
		}
        

		virtual DevType GetType() const
			{
				return DTMidiPort;
			}

		virtual mutString GetTypeName () const {
			return N_("Midi output device");
		}

		virtual void ReadData(wxConfigBase * config);
		virtual void WriteData(wxConfigBase * config);
	
#ifdef WX
		virtual wxString TowxString() const;
#endif

		virtual int GetMaxChannel() const { return 15; }
		virtual int GetMinChannel() const { return 0; }
	
	private:

#ifdef RTMIDI
		RtMidiOut *hMidiOut;
#else
		HMIDIOUT hMidiOut;
#endif
		ChannelData Cd[16];
		char KeyDir[16];
		TonAufKanal ton_auf_kanal[16];
		int nKeyOn;
	};

// InputMidiPort -------------------------------------------------------

	class InputMidiPort : public InputDeviceClass
	{
		friend class MidiPortFactory;
	protected:
		InputMidiPort *NextMidiPort;

		InputMidiPort() : InputDeviceClass(), NextMidiPort (NULL) { }
                       
		InputMidiPort(int devId, 
			      const mutStringRef name,
			      MutaborModeType mode,
			      int id):
			InputDeviceClass (devId,name,mode,id),
			NextMidiPort(NULL) {}
		InputMidiPort(const mutStringRef name, int devId)
			: InputDeviceClass(devId, name), NextMidiPort (NULL) {}

	public:
		virtual ~InputMidiPort() {}
	
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
		virtual void Save (tree_storage & config, const RouteClass *  route);
	
	
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

	
	
		virtual bool Open();
		virtual void Close();
		virtual void Stop()
			{};

		virtual void Play()
			{};

		virtual void Pause()
			{};

//	   void Proceed(GisReadArtHead *h, char turn, Route route) {};
//	   void ProceedRoute(GisReadArtHead *h, char turn) {};
#if defined(_MSC_VER)
#pragma warning(push) // Save warning settings.
#pragma warning(disable : 4100) // Disable unreferenced formal parameter warnings
#endif

		virtual frac ReadOn(frac time)
			{
				return frac(0,1);
			};

#if defined(_MSC_VER)
#pragma warning(pop) // Restore warnings to previous state.
#endif 

		virtual bool NeedsRealTime()
			{
				return true;
			}

		virtual void SetDevId (int id) {
			bool reopen = false;
			if (id != DevId) {
				DevId = id;
				if ((reopen = IsOpen())) 
					Close();
			}
			if (rtmidiin)
				Name = muT (rtmidiin->getPortName (DevId).c_str());
			else
				Name = _("no device");
			if (reopen) {
				Open();
			}
		}

		virtual int GetDevId() 
			{
				return DevId; 
			}

		virtual wxString &GetName()
			{
				return Name;
			}

#if defined(_MSC_VER)
#pragma warning(push) // Save warning settings.
#pragma warning(disable : 4100) // Disable unreferenced formal parameter warnings
#endif

		virtual void SetName(const wxString & s) 
			{
				assert (false);
				//Name = s;
			}

#if defined(_MSC_VER)
#pragma warning(pop) // Restore warnings to previous state.
#endif 

		void Proceed(DWORD midiCode);
	
		virtual int GetMaxChannel() const { return 15; }
		virtual int GetMinChannel() const { return 0; }
		virtual int GetMaxKey() const { return 127; }
		virtual int GetMinKey() const { return 0; }	
	

		virtual DevType GetType() const
			{
				return DTMidiPort;
			}

		virtual mutString GetTypeName () const {
			return N_("Midi input device");
		}

#ifdef WX
		virtual wxString TowxString() const;
#endif
	
	
#ifdef RTMIDI
		RtMidiIn *hMidiIn;

#else
		HMIDIIN hMidiIn;

#endif
	private:
		ChannelData Cd[16];

		void ProceedRoute(DWORD midiCode, Route route);
	};

	class MidiPortFactory:public DeviceFactory { 
	public:
		MidiPortFactory(size_t id =  mutabor::DTMidiPort):
			DeviceFactory(id) {}
		virtual ~MidiPortFactory();

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



	void MidiInit();
	void MidiUninit();

}
#endif /* precompiled */
#endif


///\}
