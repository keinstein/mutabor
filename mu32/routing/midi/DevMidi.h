// -*- C++ -*- 
/** \file 
 ********************************************************************
 * Description
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/mu32/routing/midi/DevMidi.h,v 1.6 2011/09/08 16:51:21 keinstein Exp $
 * Copyright:   (c) 2008 TU Dresden
 * \author  Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 
 * $Date: 2011/09/08 16:51:21 $
 * \version $Revision: 1.6 $
 * \license GPL
 *
 * $Log: DevMidi.h,v $
 * Revision 1.6  2011/09/08 16:51:21  keinstein
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

#ifndef DEVMIDI_H
#define DEVMIDI_H

#include <cassert>

#include "mhDefs.h"
#include "Device.h"
#ifdef RTMIDI
#include "RtMidi.h"
#else
#ifndef H_MMSYSTEM
//  #define WINVER 0x030a
#include <mmsystem.h>
#define H_MMSYSTEM
#endif
#endif

extern RtMidiOut * rtmidiout;
extern RtMidiIn * rtmidiin;

// OutMidiPort ------------------------------------------------------

typedef struct TAK
{
	int taste;
	int key;
	DWORD id;         // (channel << 24) + (Route->Id << 16) + (Box << 8) + Taste
	// zum Identifizieren fürs korrekte Ausschalten
} TonAufKanal;

class OutMidiPort : public OutDevice
{
	int bending_range;
public:
        OutMidiPort():OutDevice(), bending_range (2), hMidiOut(NULL), nKeyOn(0) { }

	OutMidiPort(wxString name, int devId, int bendingRange = 2)
	: OutDevice(devId, name), bending_range (bendingRange), hMidiOut(NULL), nKeyOn(0)
	{
		DEBUGLOG(other,_T(""));
	}

	~OutMidiPort()
		{};
	
	/// Save current device settings in a tree storage
	/** \argument config (tree_storage) storage class, where the data will be saved.
	 */
	virtual void Save (tree_storage & config);
	
	/// Save route settings (filter settings) for a given route
	/** Some route settings (e.g. filter settings) are device type 
	 * specific. This function saves them in a tree storage.
	 * \argument config (tree_storage *) Storage class, where the data will be saved.
	 * \argument route (Route *) Route whos data shall be saved.
	 */
	virtual void Save (tree_storage & config, const Route * route);
	
	
	/// Load current device settings from a tree storage
	/** \argument config (tree_storage) storage class, where the data will be loaded from.
	 */
	virtual void Load (tree_storage & config);
	
	/// Loade route settings (filter settings) for a given route
	/** Some route settings (e.g. filter settings) are device type 
	 * specific. This function loads them from a tree storage.
	 * \argument config (tree_storage *) Storage class, where the data will be restored from.
	 * \argument route (Route *) Route whos data shall be loaded.
	 */
	virtual void Load (tree_storage & config, Route * route);

	
	virtual bool Open();
	virtual void Close();
	virtual void NoteOn(int Box, int taste, int velo, Route *r,
	                    int channel, ChannelData *cd);
	virtual void NoteOff(int Box, int taste, int velo, Route *r, int channel);
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

	virtual void Quite(Route *r);
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
		return _("Midi output device");
	}

	virtual void ReadData(wxConfigBase * config);
	virtual void WriteData(wxConfigBase * config);
	
#ifdef WX
	virtual wxString TowxString() const {
		wxString s = OutDevice::TowxString() +
		wxString::Format(_T("\n  Name = %s\n  DevId = %d\n  Bending Range = %d\n  nKeyOn"),
				 Name.c_str(), DevId, bending_range, nKeyOn);
		s.Printf(_T("\n  KeyDir = [ %d"), KeyDir[0]);
		for (int i = 1; i<16; i++)
			s.Printf(_T(", %d"),KeyDir[i]);
		s.Printf(_T("]\n  ton_auf_kanal = [ t=%d,k=%d"), 
			 ton_auf_kanal[0].taste,
			 ton_auf_kanal[0].key);
		for (int i = 1; i<16; i++)
			s.Printf(_T("; t=%d,k=%d"), 
				 ton_auf_kanal[i].taste,
				 ton_auf_kanal[i].key);
		s+=_T("]");
		return s;
	}
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

// InMidiPort -------------------------------------------------------

class InMidiPort : public InDevice
{

public:
	InMidiPort *NextMidiPort;

        InMidiPort() : InDevice(), NextMidiPort (NULL) { }
                       
	InMidiPort(const mutString &name, int devId)
	: InDevice(devId, name), NextMidiPort (NULL) {}

	virtual ~InMidiPort() {}
	
	/// Save current device settings in a tree storage
	/** \argument config (tree_storage) storage class, where the data will be saved.
	 */
	virtual void Save (tree_storage & config);
	
	/// Save route settings (filter settings) for a given route
	/** Some route settings (e.g. filter settings) are device type 
	 * specific. This function saves them in a tree storage.
	 * \argument config (tree_storage *) Storage class, where the data will be saved.
	 * \argument route (Route *) Route whos data shall be saved.
	 */
	virtual void Save (tree_storage & config, const Route * route);
	
	
	/// Load current device settings from a tree storage
	/** \argument config (tree_storage) storage class, where the data will be loaded from.
	 */
	virtual void Load (tree_storage & config);
	
	/// Loade route settings (filter settings) for a given route
	/** Some route settings (e.g. filter settings) are device type 
	 * specific. This function loads them from a tree storage.
	 * \argument config (tree_storage *) Storage class, where the data will be restored from.
	 * \argument route (Route *) Route whos data shall be loaded.
	 */
	virtual void Load (tree_storage & config, Route * route);

	
	
	virtual bool Open();
	virtual void Close();
	virtual void Stop()
	{};

	virtual void Play()
	{};

	virtual void Pause()
	{};

//	   void Proceed(GisReadArtHead *h, char turn, Route *route) {};
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
		return _("Midi input device");
	}

#ifdef WX
	virtual wxString TowxString() const {
		return InDevice::TowxString();
	}
#endif
	
	
#ifdef RTMIDI
	RtMidiIn *hMidiIn;

#else
	HMIDIIN hMidiIn;

#endif
private:
	ChannelData Cd[16];

	void ProceedRoute(DWORD midiCode, Route *route);
};

void MidiInit();
void MidiUninit();


#endif


///\}
