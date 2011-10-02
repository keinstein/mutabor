// -*- C++ -*- 
/** \file 
 ********************************************************************
 * Description
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/mu32/routing/midi/DevMidi.h,v 1.9 2011/10/02 16:58:41 keinstein Exp $
 * Copyright:   (c) 2008 TU Dresden
 * \author  Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 
 * $Date: 2011/10/02 16:58:41 $
 * \version $Revision: 1.9 $
 * \license GPL
 *
 * $Log: DevMidi.h,v $
 * Revision 1.9  2011/10/02 16:58:41  keinstein
 * * generate Class debug information when compile in debug mode
 * * InputDeviceClass::Destroy() prevented RouteClass::Destroy() from clearing references -- fixed.
 * * Reenable confirmation dialog when closing document while the logic is active
 * * Change debug flag management to be more debugger friendly
 * * implement automatic route/device deletion check
 * * new debug flag --debug-trace
 * * generate lots of tracing output
 *
 * Revision 1.8  2011-09-30 09:10:24  keinstein
 * Further improvements in the routing system.
 *
 * Revision 1.7  2011-09-27 20:13:22  keinstein
 * * Reworked route editing backend
 * * rewireing is done by RouteClass/GUIRoute now
 * * other classes forward most requests to this pair
 * * many bugfixes
 * * Version change: We are reaching beta phase now
 *
 * Revision 1.6  2011-09-08 16:51:21  keinstein
 * Set foreground color in box status windows
 * Fix updating box status windows
 * update RtMidi (includes Jack compilation mode)
 *
 * Revision 1.5  2011-09-07 15:54:40  keinstein
 * fix some compilation issues
 *
 * Revision 1.4  2011-02-20 22:35:56  keinstein
 * updated license information; some file headers have to be revised, though
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

#include "Defs.h"
#include "mhDefs.h"
#include "Device.h"

#ifndef MU32_ROUTING_MIDI_DEVMIDI_H_PRECOMPILED
#define MU32_ROUTING_MIDI_DEVMIDI_H_PRECOMPILED

// system headers which do seldom change

#include <cassert>

#ifdef RTMIDI
#include "RtMidi.h"
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
		int taste;
		int key;
		DWORD id;         // (channel << 24) + (Route->Id << 16) + (Box << 8) + Taste
		// zum Identifizieren fürs korrekte Ausschalten
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
		virtual void NoteOn(int Box, int taste, int velo, RouteClass * r,
				    int channel, ChannelData *cd);
		virtual void NoteOff(int Box, int taste, int velo, 
				     RouteClass * r, int channel);
		virtual void NotesCorrect(int box);
		virtual void Sustain(char on, int channel);
		virtual int  GetChannel(int taste);
		virtual void Gis(GisToken *token, char turn)
			{};

		virtual void AddTime(frac time)
			{};

		virtual void MidiOut(DWORD data, char n);
		virtual void MidiOut(BYTE *p, char n)
			{};

		virtual void Quite(RouteClass * r);
		virtual void Panic();
		virtual bool NeedsRealTime()
			{
				return true;
			}

		virtual void SetDevId (int id) {
			DevId = id;            
			Name = muT (rtmidiout->getPortName (DevId).c_str());
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
		virtual frac ReadOn(frac time)
			{
				return frac(0,1);
			};

		virtual bool NeedsRealTime()
			{
				return true;
			}

		virtual void SetDevId (int id) {
			DevId = id;            
			Name = muT (rtmidiin->getPortName (DevId).c_str());
		}

		virtual int GetDevId() 
			{
				return DevId; 
			}

		virtual wxString &GetName()
			{
				return Name;
			}

		virtual void SetName(const wxString & s) 
			{
				assert (false);
				//Name = s;
			}

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
		MidiPortFactory(size_t id = 0):
			DeviceFactory(id) {}
		virtual ~MidiPortFactory();

	protected:
		virtual size_t GetType() const
			{
				return DTMidiFile;
			}


		virtual mutabor::OutputDeviceClass * DoCreateOutput() const = 0;
		
		virtual mutabor::InputDeviceClass * DoCreateInput() const = 0;
		virtual mutabor::OutputDeviceClass * DoCreateOutput(int devId,
							     const mutStringRef name, 
							     int id = -1) const = 0;
		
		virtual mutabor::InputDeviceClass * DoCreateInput(int devId,
								  const mutStringRef name, 
								  int id = -1) const = 0;

		virtual mutabor::OutputDeviceClass * DoCreateOutput(int devId,
								    const mutStringRef name, 
								    mutabor::MutaborModeType mode, 
								    int id = -1) const = 0;
		
		virtual mutabor::InputDeviceClass * DoCreateInput(int devId,
								  const mutStringRef name, 
								  mutabor::MutaborModeType mode, 
								  int id = -1) const = 0;
	};



	void MidiInit();
	void MidiUninit();

}
#endif /* precompiled */
#endif


///\}
