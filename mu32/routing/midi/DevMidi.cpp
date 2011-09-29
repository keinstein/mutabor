/** \file 
 ********************************************************************
 * Description
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/mu32/routing/midi/DevMidi.cpp,v 1.10 2011/09/29 05:26:58 keinstein Exp $
 * Copyright:   (c) 2008 TU Dresden
 * \author  Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 
 * $Date: 2011/09/29 05:26:58 $
 * \version $Revision: 1.10 $
 * \license GPL
 *
 * $Log: DevMidi.cpp,v $
 * Revision 1.10  2011/09/29 05:26:58  keinstein
 * debug intrusive_ptr
 * fix storage and retrieving of input/output devices in treestorage
 * save maximum border size in icons
 * Apply the calculated offset in IconShape (box and box channels still missing)
 * Fix debug saving and restoring route information/route window on activation
 * Add wxWANTS_CHARS to MutEditWindow
 *
 * Revision 1.9  2011-09-27 20:13:22  keinstein
 * * Reworked route editing backend
 * * rewireing is done by RouteClass/GUIRoute now
 * * other classes forward most requests to this pair
 * * many bugfixes
 * * Version change: We are reaching beta phase now
 *
 * Revision 1.8  2011-09-09 09:29:10  keinstein
 * fix loading of routing configuration
 *
 * Revision 1.7  2011-09-08 16:51:21  keinstein
 * Set foreground color in box status windows
 * Fix updating box status windows
 * update RtMidi (includes Jack compilation mode)
 *
 * Revision 1.6  2011-09-07 15:54:40  keinstein
 * fix some compilation issues
 *
 * Revision 1.5  2011-07-27 20:48:32  keinstein
 * started to move arrays using MAX_BOX into struct mutabor_box_type
 *
 * Revision 1.4  2011-02-20 22:35:56  keinstein
 * updated license information; some file headers have to be revised, though
 *
 *
 *
 ********************************************************************
 * \addtogroup 
 * \{
 ********************************************************************/
// ------------------------------------------------------------------
// Mutabor 3, 1998, R.Krauﬂe
// MidiPort Klassen
// ------------------------------------------------------------------

#include "DevMidi.h"
#include "Execute.h"
#include "GrafKern.h"
#include "MidiKern.h"
#include "wx/msgdlg.h"

// OutputMidiPort ------------------------------------------------------

//static long freq ;

// GET_INDEX is algready defined in MidiKern.h

// berechnet die 'Oktavlage' einer taste bzgl. tonsystem
#define GET_ABSTAND(taste,tonsystem) \
     ( (int)((taste)-( (tonsystem)->anker % (tonsystem)->breite ))  \
           / (tonsystem)->breite -((int) (tonsystem)->anker         \
           / (tonsystem)->breite ))

// berechnet die Frequenz in Midi-Form
#define GET_FREQ(taste,tonsystem)  \
	( ( (tonsystem)->ton[GET_INDEX(taste,(tonsystem))]==0) ?       \
	  (long) 0 :                                       \
     (long)( (tonsystem)->periode *                   \
              GET_ABSTAND(taste,(tonsystem))  +                         \
                   (tonsystem)->ton[GET_INDEX(taste,(tonsystem))]))

#define ZWZ 1.059463094 /* 12.Wurzel 2 */
//#define LONG_TO_HERTZ( x ) (440.0*pow(ZWZ,((((double)x)/16777216.0l))-69))
//#define LONG_TO_CENT( x ) ( ((double)x)/167772.13l  )

#ifdef RTMIDI
#include "RtMidi.h"
#endif


namespace mutabor {
#ifdef RTMIDI
	extern RtMidiOut *rtmidiout;
	
	extern RtMidiIn *rtmidiin;

// Midi-Ausgabe
#define MIDI_OUT3(code1, code2, code3)				\
	{ std::vector<unsigned char> message;			\
		message.push_back(code1);			\
		message.push_back(code2);			\
		message.push_back(code3);			\
		DEBUGLOG2(midiio,_T("MIDI OUT %x %x %x"),	\
			  code1,code2,code3);			\
		hMidiOut->sendMessage(&message); }

#define MIDI_OUT2(code1, code2)				\
	{ std::vector<unsigned char> message;		\
		message.push_back(code1);		\
		message.push_back(code2);		\
		DEBUGLOG2(midiio,_T("MIDI OUT %x %x"),	\
			  code1,code2);			\
		hMidiOut->sendMessage(&message); }
#else
#define MIDI_OUT3(code1, code2, code3)			\
	midiOutShortMsg(hMidiOut,			\
			((DWORD) (code3) << 16) +	\
			((DWORD) (code2) << 8) +	\
			((DWORD) (code1)))

#define MIDI_OUT2(code1, code2)				\
	midiOutShortMsg(hMidiOut,			\
			((DWORD) (code2) << 8) +	\
			((DWORD) (code1)))
#endif

// Zugriffe
//#define zugriff  ((unsigned char*) &freq)
//#define zgf  ((unsigned char*) &pb)

// Pitch
/* zugriff: 00000000111111112222222233333333
   22222222000000 + 111111

   zugriff: 0 1 2 3 4 5 6 7 | 8 9 10 11 12 13 14 15 |
   16 17 18 19 20 21 22 23 | 24 25 26 27 28 29 30 31
   zugriff[2] << 6 =  0  0  0  0  0  0 16 17 18 19 20 21 22 23
   zugriff[1] >> 2 = 10 11 12 13 14 15
   pb            = ( 10 11 12 13 14 15 16 17 18 19 20 21 22 23 ) / bending_range;
   zgf0 >> 1 =          11 12 13 14 16 16 17
   zgf1 +64 =                                18 19 20 21 22 23 "1"
   pb & 0xff >> 1  =    11 12 13 14 15 16 17
   (pb>>8+0x4000)&0x7f00 =                   18 19 20 21 22 23 "1"

*/
#define MIDI_PITCH(i,freq)						\
	{ unsigned int pb = ( ((freq & 0xffffff) / bending_range) >> 11) ; \
		DEBUGLOG2(midiio,_T("MIDI_PITCH(%x/%d,%x/%d) = %x/%d (%x/%d, %x/%d, %x/%d)"), \
			  i,i,freq,freq,pb,pb,0xE0 + i,0xE0 + i, pb & 0x7f, pb & 0x7f,  (0x40 + (pb >> 7) ) & 0x7f, \
			  (0x40 + (pb >> 7) ) & 0x7f );			\
		MIDI_OUT3 (0xE0 + i, pb & 0x7f, (0x40 + (pb >> 7) ) & 0x7f) }

//	int pb = ( (((int)zugriff[2])<<6) + (zugriff[1]>>2) ) / bending_range; 
//	MIDI_OUT3(0xE0+i, zgf[0] >> 1 , 64+zgf[1])

// Sound
#define MIDI_SOUND(i, sound)				\
	if ( sound != -1 ) MIDI_OUT2(0xC0+i, sound)

// ID errechnen
#define MAKE_ID(route, box, taste, channel)				\
	((((DWORD)channel) << 24) + (((DWORD)route->GetId()&0xff) << 16) + ((DWORD)box << 8) + taste)


/// Save current device settings in a tree storage
/** \argument config (tree_storage) storage class, where the data will be saved.
 */
	void OutputMidiPort::Save (tree_storage & config) 
	{
		config.Write(_T("Device Id"),DevId);
		config.Write(_T("Device Name"),Name);
		config.Write(_T("Bending Range"),bending_range);
	}

/// Save route settings (filter settings) for a given route
/** Some route settings (e.g. filter settings) are device type 
 * specific. This function saves them in a tree storage.
 * \argument config (tree_storage *) Storage class, where the data will be saved.
 * \argument route (Route ) Route whos data shall be saved.
 */
	void OutputMidiPort::Save (tree_storage & config, const Route route)
	{
#ifdef DEBUG
		wxString oldpath = config.GetPath();
#endif
		wxASSERT(route);
		
		config.toLeaf(_T("Midi Output"));
		config.Write(_T("Avoid Drum Channel"), route->ONoDrum);
		config.Write(_T("Channel Range From"), route->OFrom);
		config.Write(_T("Channel Range To"), route->OTo);
		config.toParent();
		wxASSERT(oldpath == config.GetPath());
	}


/// Load current device settings from a tree storage
/** \argument config (tree_storage) storage class, where the data will be loaded from.
 */
	void OutputMidiPort::Load (tree_storage & config)
	{
#ifdef DEBUG
		wxString oldpath = config.GetPath();
#endif
		DevId = config.Read(_T("Device Id"),0);
		Name = config.Read(_T("Device Name"), rtmidiout->getPortCount()?
				   muT(rtmidiout->getPortName(0).c_str()):wxString(_("Unknown")));
		bending_range = config.Read(_T("Bending Range"),2);
		wxASSERT(oldpath == config.GetPath());
	}

/// Loade route settings (filter settings) for a given route
/** Some route settings (e.g. filter settings) are device type 
 * specific. This function loads them from a tree storage.
 * \argument config (tree_storage *) Storage class, where the data will be restored from.
 * \argument route (Route) Route whos data shall be loaded.
 */
	void OutputMidiPort::Load (tree_storage & config, Route route)
	{
#ifdef DEBUG
		wxString oldpath = config.GetPath();
#endif
		wxASSERT(route);
		config.toLeaf(_T("Midi Output"));
		route->ONoDrum = config.Read(_T("Avoid Drum Channel"), true);
		int oldfrom, oldto;
		oldfrom = route->OFrom = config.Read(_T("Channel Range From"), GetMinChannel());
		oldto = route->OTo = config.Read(_T("Channel Range To"), GetMaxChannel());
		bool correct = true;
		if (route->OFrom < GetMinChannel()) {
			correct = false;
			route->OFrom = GetMinChannel();
		}
		if (route->OTo > GetMaxChannel()) {
			correct = false;
			route->OTo = GetMaxChannel();
		}
		if (!correct)
			wxMessageBox(wxString::Format(_("The Channel range %d--%d of the MIDI output device %s must be inside %d--%d. The current route had to be corrected."),
						      oldfrom,oldto,GetName().c_str(),GetMinChannel(),GetMaxChannel()),
				     _("Warning loading route"),wxICON_EXCLAMATION);
		config.toParent();
		wxASSERT(oldpath == config.GetPath());
	}


	bool OutputMidiPort::Open()
	{
		wxASSERT(!isOpen);
		DEBUGLOG (other, _T(""));
		int i;

		for (i = 0; i < 16; i++) {
			Cd[i].Reset();
			ton_auf_kanal[i].taste = 0;
			ton_auf_kanal[i].id = 0;
		}

		nKeyOn = 0;

		for (i = 0; i < 16; i++)
			KeyDir[i] = (char)i; // alle nicht benutzt

#ifdef RTMIDI
		// RtMidiIn constructor
		try {
			hMidiOut = new RtMidiOut(PACKAGE_STRING);
		} catch (RtError &error) {
			LAUFZEIT_ERROR0(_("Can not open ouput Midi devices."));
			return false;
		}

		try {
			hMidiOut->openPort(DevId,(const char *)(GetName().ToUTF8()));
		} catch (RtError &error) {
			LAUFZEIT_ERROR2(_("Can not open output Midi device nr. %d (%s)"), DevId, (GetName().c_str()));
			return false;
		}

#else
		midiOutOpen(&hMidiOut, DevId, NULL, NULL, NULL);

#endif
		for (i = 0; i < 16; i++) {
			MIDI_OUT3(0xE0+i, 0x00, 0x40); // pitch auf 0
			MIDI_OUT3(0xB0+i, 122, 0);  // local off
			MIDI_OUT3(0xB0+i, 125, 0);  // omni on
			MIDI_OUT3(0xB0+i, 127, 0);  // poly on
		}

		isOpen = true;
		return true;
	}

	void OutputMidiPort::Close()

	{
		wxASSERT(isOpen);
		DEBUGLOG (other, _T(""));
		// alle liegenden Tˆne ausschalten

		for (int i = 0; i < 16; i++)
			if ( KeyDir[i] >= 16 )  // benutzt
				MIDI_OUT3(0x80+i, ton_auf_kanal[i].key, 64);

		/*  for (int i = 0; i < 16; i++)
		    MidiOut3(176+i, 122, 1);  // local on */
		// Device schlieﬂen
#ifdef RTMIDI
		hMidiOut->closePort();

		delete hMidiOut;

#else
		midiOutClose(hMidiOut);

#endif
		isOpen = false;
	}

	void OutputMidiPort::NoteOn(int box, int taste, int velo, Route r, int channel, ChannelData *cd)
	{
		DEBUGLOG (other, _T("box %d, key %d, velo %d, channel %d"),
			  box, taste, velo, channel);
		int free = 16, freeSus = r->OTo, freeV = 64, freeSusV = 64, s;
		DWORD p;
		long freq;

		if ( box == -2 ) {
			freq = ((long)taste) << 24;
			box = 255;
		} else
			freq = GET_FREQ (taste, mut_box[box].tonesystem);

		// testen, ob nicht belegte Taste
		if ( !freq )
			return;

		for ( int j = r->OFrom; j <= r->OTo; j++ ) 
			if ( j != DRUMCHANNEL || !r->ONoDrum ) {
				if ( Cd[j].Sustain ) {
					if ( KeyDir[j] < freeSusV ) {
						freeSus = j;
						freeSusV = KeyDir[j];
					}
				} else {
					if ( KeyDir[j] < freeV ) {
						free = j;
						freeV = KeyDir[j];
					}
				}
			}
		if ( freeV >= 16 ) {
			free = freeSus;
			freeV = freeSusV;
		}

		if ( freeV >= 16 )  // keinen freien gefunden
		{
			// "mittelste Taste weglassen"
			int AM = 0; // arithmetisches Mittel der Tasten
			int j;

			for (j = r->OFrom; j <= r->OTo; j++)
				if ( j != DRUMCHANNEL || !r->ONoDrum )
					AM += ton_auf_kanal[j].taste;

			AM /= r->OTo + 1 - r->OFrom;

			for ( j = r->OFrom; j <= r->OTo; j++ )
				if ( j != DRUMCHANNEL || !r->ONoDrum )
					if ( abs(AM - ton_auf_kanal[j].taste) < abs(AM - ton_auf_kanal[free].taste) )
						free = j;

			// Ton auf Kanal free ausschalten
			MIDI_OUT3(0x80+free, ton_auf_kanal[free].key, 64);

			// evtl. Sustain ausschalten
			if ( Cd[free].Sustain )
				MIDI_OUT3(0xB0+free, 64, 0);

			// KeyDir umsortieren
			BYTE oldKeyDir = KeyDir[free];

			for (int k = 0; k < 16; k++)
				if ( KeyDir[k] > oldKeyDir ) KeyDir[k]--;

			KeyDir[free] = (char)(15+nKeyOn);
		} else {
			nKeyOn++;
			KeyDir[free] = (char)(15 + nKeyOn);
		}

		// freier Kanal = free

		// evtl. Sustain ausschalten
		if ( Cd[free].Sustain ) {
			MIDI_OUT3(0xB0+free, 64, 0);
			Cd[free].Sustain = 0;
		}

		// Sound testen
		if ( (s = cd->Sound) != Cd[free].Sound ) {
			MIDI_SOUND(free, s);
			Cd[free].Sound = s;
		}

		// Bank testen
		if ( (s = cd->BankSelectMSB) != Cd[free].BankSelectMSB && s != -1 ) {
			MIDI_OUT3(0xB0+free, 0, (BYTE) s);
			Cd[free].BankSelectMSB = s;
		}

		if ( (s = cd->BankSelectLSB) != Cd[free].BankSelectLSB && s != -1 ) {
			MIDI_OUT3(0xB0+free, 32, (BYTE) s);
			Cd[free].BankSelectLSB = s;
		}

		// Pitch testen
		if ( (long)(p = (freq & 0xFFFFFF)) != Cd[free].Pitch ) {
			MIDI_PITCH(free, freq);
			Cd[free].Pitch = p;
		}

		ton_auf_kanal[free].key = (freq >> 24) & 0x7f;

		ton_auf_kanal[free].taste = taste;
		ton_auf_kanal[free].id = MAKE_ID(r, box, taste, channel);
		MIDI_OUT3(0x90+free, ton_auf_kanal[free].key, velo);

		if ( cd->Sustain ) {
			MIDI_OUT3(0xB0+free, 64, cd->Sustain);
			Cd[free].Sustain = cd->Sustain;
		}
	};

	void OutputMidiPort::NoteOff(int box, int taste, int velo, Route r, int channel)
	{
		DEBUGLOG (midiio, _T("box %d, key %d, velo %d, channel %d"),
			  box, taste, velo, channel);

		if ( box == -2 )
			box = MAX_BOX+1;

		DWORD id = MAKE_ID(r, box, taste, channel);

		if ( !velo ) //3 ?? notwendig?
			velo = 64;

		for (int i = r->OFrom; i <= r->OTo; i++)
			if ( i != DRUMCHANNEL || !r->ONoDrum )
				if ( KeyDir[i] >= 16 && ton_auf_kanal[i].id == id ) {
					ton_auf_kanal[i].taste=0;
// ???     ton_auf_kanal[i].id=0;
					MIDI_OUT3(0x80+i, ton_auf_kanal[i].key, velo);
					// KeyDir umsortieren
					int oldKeyDir = KeyDir[i];

					for (int k = 0; k < 16; k++)
						if ( KeyDir[k] > oldKeyDir || KeyDir[k] < 16) KeyDir[k]--;

					nKeyOn--;

					KeyDir[i] = 15;
				}
	}

	inline long LongAbs(long x)
	{
		return (x < 0)? -x : x;
	}

	void OutputMidiPort::NotesCorrect(int box)
	{
		DEBUGLOG (midiio, _T(""));

		for (int i = 0; i < 16; i++)
			if ( (KeyDir[i] >= 16 && ton_auf_kanal[i].id) || Cd[i].Sustain ) {
				int Box = (ton_auf_kanal[i].id >> 8) & 0xFF;

				if ( Box != box )
					break;

				DEBUGLOG(midiio,_T("old(hex/dec): channel = %01x/%d, Taste = %02x/%d, key = %02x/%d, pitch = %06x/%d"), 
					 i,i,ton_auf_kanal[i].taste,ton_auf_kanal[i].taste, 
					 ton_auf_kanal[i].key,ton_auf_kanal[i].key,Cd[i].Pitch,Cd[i].Pitch);

				long freq = GET_FREQ(ton_auf_kanal[i].taste, mut_box[Box].tonesystem);

				// hier kann ein evtl. grˆﬂerer bending_range genutzt werden, um
				// Ton aus und einschalten zu vermeiden
				if ( ton_auf_kanal[i].key == ((freq >> 24) & 0x7f) &&
				     Cd[i].Pitch == ((long)freq & 0xFFFFFF) )
					continue;


				long Delta = freq - ((long)ton_auf_kanal[i].key << 24);

				bool SwitchTone = (LongAbs(Delta) >= ((long)bending_range << 24));

				// evtl. Ton ausschalten
				if ( SwitchTone ) {
					if ( Cd[i].Sustain ) {
						MIDI_OUT3(0xB0+i, 64, 0);
						Cd[i].Sustain = 0;

						if ( KeyDir[i] < 16 )
							continue;
					}

					MIDI_OUT3(0x80+i, ton_auf_kanal[i].key, 0x7F);
					ton_auf_kanal[i].key = (freq >> 24) & 0x7F;
					Delta = freq - ((long)ton_auf_kanal[i].key << 24);
				} else if ( Delta == Cd[i].Pitch )
					continue;

				// Spezialbending (groﬂer Range)
				Cd[i].Pitch = Delta;

				Delta /= bending_range;
				Delta = Delta >> 11;
				Delta +=  0x40 << 7; // we have to add here as Delta can be negative
				DEBUGLOG(midiio,_T("new freq = %08x/%d, Pitch= %06x/%d, Delta = %06x/%d, i=%d"), 
					 freq, freq, Cd[i].Pitch, Cd[i].Pitch, Delta, Delta, i);
				//      MIDI_OUT3(0xE0+i, ((BYTE*)&Delta)[1] >> 1, (((BYTE*)&Delta)[2]));
				MIDI_OUT3(0xE0+i, Delta & 0x7f, (Delta >> 7) & 0x7f );

				// evtl. Ton einschalten
				if ( SwitchTone )
					MIDI_OUT3(0x90+i, ton_auf_kanal[i].key, 64);  //3 velo speichern ??
			}
	}

	void OutputMidiPort::Sustain(char on, int channel)
	{
		DEBUGLOG (other, _T(""));
		DWORD chan = channel; // Midi has unsigned channels

		for (int i = 0; i < 16; i++)
			if ( ton_auf_kanal[i].id && (ton_auf_kanal[i].id >> 24) == chan ) {
				MIDI_OUT3(0xB0+i, 64, on);
				Cd[i].Sustain = on;
			}
	}

	int OutputMidiPort::GetChannel(int taste)
	{
		DEBUGLOG (other, _T(""));

		for (int i = 0; i < 16; i++)
			if ( ton_auf_kanal[i].id && (ton_auf_kanal[i].taste == taste) )
				return i;

		return -1;
	}

//void Gis(GisToken *token, char turn) {};

#ifdef RTMIDI
	void OutputMidiPort::MidiOut(DWORD data, char n)
	{
		std::vector<unsigned char> message;

		while ( n-- ) {
			DEBUGLOG (other, _T("sending byte %x"), data & 0xff);
			message.push_back(data & 0xFF);
			data >>= 8;
		}

		hMidiOut->sendMessage(&message);
	}

#else
	void OutputMidiPort::MidiOut(DWORD data, char n)
	{
		DEBUGLOG (other, _T("without RtMidi"));
		midiOutShortMsg(hMidiOut, data);
	}

#endif

	void OutputMidiPort::Quite(Route r)
	{
		DEBUGLOG (other, _T(""));

		for (int i = 0; i < 16; i++)
			if ( (char)((ton_auf_kanal[i].id >> 16) & 0x0FF) == r->GetId() )
				NoteOff(r->GetBox(), ton_auf_kanal[i].id % 256, 64, r,  ton_auf_kanal[i].id >> 24);
	}

	void OutputMidiPort::Panic()
	{
		DEBUGLOG (other, _T(""));

		for (int i = 0; i < 16; i++) {
			MIDI_OUT3(176+i, 123, 0);  // All notes off */
			MIDI_OUT3(0xB0+i, 7, 127);  // main volume
			// sound piano
			MIDI_OUT2(0xC0+i, 0);
			// Merker aufr‰umen
			ton_auf_kanal[i].taste=0;
			ton_auf_kanal[i].id=0;
			Cd[i].Sound = 0;
			Cd[i].Sustain = 0;
			KeyDir[i] = i; // alle nicht benutzt
		}

		nKeyOn = 0;
	}

	void OutputMidiPort::ReadData(wxConfigBase * config) 
	{
		bending_range = config->Read(_("Bending_Range"),
					     (long)bending_range);
	}

	void OutputMidiPort::WriteData(wxConfigBase * config) 
	{
		config->Write(_("Bending_Range"), (long)bending_range);
	}


#ifdef WX
	wxString OutputMidiPort::TowxString() const {
		wxString channelString;
		for (int i = 0 ; i<16; i++) {
			channelString += wxString::Format(_T(" ({%d,%d,%d,%d,%ld},%d,[%d,%d,%d])"),
							  Cd[i].Sound,
							  Cd[i].Sustain,
							  Cd[i].BankSelectMSB,
							  Cd[i].BankSelectLSB,
							  Cd[i].Pitch,
							  KeyDir[i],
							  ton_auf_kanal[i].taste,
							  ton_auf_kanal[i].key,
							  ton_auf_kanal[i].id);
		}
		return OutputDeviceClass::TowxString()
			+ wxString::Format(_T("\
OutputMidiPort:\n\
   hMidiOut = %p\n\
   channels ({sound,sustain,MSB,LSB,pitch},KeyDir,[tasta,key,id]):\n\
             %s\n\
   nKeyOn   = %d\n\
"),hMidiOut, (const wxChar *)channelString, nKeyOn);

	}
#endif

// InputMidiPort -------------------------------------------------------

#ifdef RTMIDI

	void mycallback( double deltatime, std::vector< unsigned char > *message, void *userData )
	{
		DWORD data = 0;

		for (int i = message->size()-1; i >= 0; i--)
			data = ((data << 8) | ((unsigned char)(*message)[i]));

		((InputMidiPort*)userData)->Proceed(data);
	}

#else

	void CALLBACK _export MidiInPortFunc(HMIDIIN hMidiIn, UINT wMsg, DWORD dwInstance, DWORD dwParam1, DWORD dwParam2)
	{
		//  CurrentTimeStamp = dwParam2;

		if ( wMsg != MIM_DATA || dwParam1 % 256 > 240 ) return;

		// Daten in Midi-Automat
		((InputMidiPort*)dwInstance)->Proceed(dwParam1);
	}

#endif

// InputMidiPort -------------------------------------------------------
/// Save current device settings in a tree storage
/** \argument config (tree_storage) storage class, where the data will be saved.
 */
	void InputMidiPort::Save (tree_storage & config) 
	{
#ifdef DEBUG
		wxString oldpath = config.GetPath();
#endif
		config.Write(_T("Device Id"),   DevId);
		config.Write(_T("Device Name"), Name);
		wxASSERT(oldpath == config.GetPath());
	}

/// Save route settings (filter settings) for a given route
/** Some route settings (e.g. filter settings) are device type 
 * specific. This function saves them in a tree storage.
 * \argument config (tree_storage *) Storage class, where the data will be saved.
 * \argument route (Route ) Route whos data shall be saved.
 */
	void InputMidiPort::Save (tree_storage & config, const Route route)
	{
#ifdef DEBUG
		wxString oldpath = config.GetPath();
#endif
		config.toLeaf(_T("Midi Input"));
		config.Write(_T("Filter Type"), route->Type);
		switch(route->Type) {
		case RTchannel: 
			config.Write(_T("Channel From"), route->IFrom);
			config.Write(_T("Channel To"), route->ITo);
			break;
		case RTstaff:
			config.Write(_T("Key From"), route->IFrom);
			config.Write(_T("Key To"), route->ITo);
			break;
		case RTelse:
		case RTall:
			break;
		}
		config.toParent();
		wxASSERT(oldpath == config.GetPath());
	}


/// Load current device settings from a tree storage
/** \argument config (tree_storage) storage class, where the data will be loaded from.
 */
	void InputMidiPort::Load (tree_storage & config)
	{
#ifdef DEBUG
		wxString oldpath = config.GetPath();
#endif
		DevId = config.Read(_T("Device Id"), 0);
		Name  = config.Read(_T("Device Name"), 	
				    rtmidiout->getPortCount()?
				    muT(rtmidiout->getPortName(0).c_str()):wxString(_("Unknown")));
		wxASSERT(oldpath == config.GetPath());
	}

/// Loade route settings (filter settings) for a given route
/** Some route settings (e.g. filter settings) are device type 
 * specific. This function loads them from a tree storage.
 * \argument config (tree_storage *) Storage class, where the data will be restored from.
 * \argument route (Route ) Route whos data shall be loaded.
 */
	void InputMidiPort::Load (tree_storage & config, Route route)
	{
#ifdef DEBUG
		wxString oldpath = config.GetPath();
#endif
		config.toLeaf(_T("Midi Input"));
		route->Type = (RouteType) config.Read(_T("Filter Type"), (int) RTchannel);
		switch(route->Type) {
		case RTchannel: 
		{
			int oldfrom, oldto;
			oldfrom = route->IFrom = config.Read(_T("Channel From"), GetMinChannel());
			oldto = route->ITo = config.Read(_T("Channel To"), GetMaxChannel());
			bool correct = true;
			if (route->IFrom < GetMinChannel()) {
				correct = false;
				route->IFrom = GetMinChannel();
			}
			if (route->ITo > GetMaxChannel()) {
				correct = false;
				route->ITo = GetMaxChannel();
			}
			if (!correct)
				wxMessageBox(wxString::Format(_("The Channel range %d--%d of the MIDI input device %s must be inside %d--%d. The current route had to be corrected."),
							      oldfrom,oldto,GetName().c_str(),GetMinChannel(),GetMaxChannel()),
					     _("Warning loading route"),wxICON_EXCLAMATION);
			break;
		}
		case RTstaff:
		{
			int oldfrom, oldto;
			route->IFrom = oldfrom = config.Read(_T("Key From"), GetMinKey());
			route->ITo = oldto = config.Read(_T("Key To"), GetMaxKey());
			bool correct = true;
			if (route->IFrom < GetMinKey()) {
				correct = false;
				route->IFrom = GetMinKey();
			}
			if (route->ITo > GetMaxKey()) {
				correct = false;
				route->ITo = GetMaxKey();
			}
			if (!correct)
				wxMessageBox(wxString::Format(_("The Channel range %d--%d of the MIDI input device must be inside %d--%d. The current route had to be corrected."),
							      oldfrom,oldto, GetName().c_str(),GetMinKey(), GetMaxKey()),
					     _("Warning loading route"),wxICON_EXCLAMATION);
			break;
		}
		case RTelse:
		case RTall:
			break;
		}
		config.toParent();
		wxASSERT(oldpath == config.GetPath());
	}

	bool InputMidiPort::Open()
	{
		wxASSERT(!isOpen);
		for (int i = 0; i < 16; i++)
			Cd[i].Reset();

#ifdef RTMIDI
		try {
			hMidiIn = new RtMidiIn(PACKAGE_STRING);
		} catch (RtError &error) {
			LAUFZEIT_ERROR0(_("Can not open Midi input devices."));
			return false;
		}

		try {
			hMidiIn->openPort(DevId,(const char *)(GetName().ToUTF8()));
		} catch (RtError &error) {
			LAUFZEIT_ERROR2(_("Can not open Midi input device no. %d (%s)."), DevId, (GetName().c_str()));
			return false;
		}

		hMidiIn->setCallback(mycallback, this);

#else
		midiInOpen(&hMidiIn, DevId, (DWORD)MidiInPortFunc, (DWORD)this, CALLBACK_FUNCTION);
		midiInStart(hMidiIn);
#endif
		isOpen = true;
		return true;
	}

	void InputMidiPort::Close()
	{
		wxASSERT(isOpen);
#ifdef RTMIDI
		hMidiIn->closePort();
		delete hMidiIn;
#else
		midiInStop(hMidiIn);
		midiInReset(hMidiIn);
		midiInClose(hMidiIn);
#endif
		Quite();
		isOpen = false;
	};




#ifdef WX
	wxString InputMidiPort::TowxString() const {
		wxString channelString;
		for (int i = 0; i < 16; i++) {
			channelString += wxString::Format(_T(" {%d,%d,%d,%d,%ld}"),
							  Cd[i].Sound,
							  Cd[i].Sustain,
							  Cd[i].BankSelectMSB,
							  Cd[i].BankSelectLSB,
							  Cd[i].Pitch);
		}
		return InputDeviceClass::TowxString()
			+wxString::Format(_T("\
InputMidiPort:\n\
   hMidiOut = %p\n\
   channels {sound,sustain,MSB,LSB,pitch}:\n\
             %s\n\
"), hMidiIn, (const wxChar *)channelString);

	}
#endif








/*#define MIDICODE(i)                           \
  (((BYTE*)(&midiCode))[i])
*/
// f¸r bestimmte Route Codeverarbeitung
	void InputMidiPort::ProceedRoute(DWORD midiCode, Route route)
	{
#ifdef DEBUG
		if (midiCode != 0xf8)
			DEBUGLOG(midiio,_T("midiCode = %x"), midiCode);
#endif
		int Box = route->GetBox();
		BYTE MidiChannel = midiCode & 0x0F;
		BYTE MidiStatus = midiCode & 0xF0;

		switch ( MidiStatus ) {

		case 0x90: // Note On
			if ( (midiCode & 0x7f0000) > 0 ) {
				if ( route->Active )
					AddKey(Box, (midiCode >> 8) & 0xff, route->GetId());

				if ( route->GetOutputDevice() )
					route->GetOutputDevice()->NoteOn(Box, 
									 (midiCode >> 8) & 0xff, 
									 (midiCode >> 16) & 0xff,
									 route, MidiChannel, &Cd[MidiChannel]);

				break;
			}
			
		case 0x80: // Note Off
			if ( route->Active )
				DeleteKey(Box,(midiCode >> 8) & 0xff, route->GetId());

			if ( route->GetOutputDevice() )
				route->GetOutputDevice()->NoteOff(Box, (midiCode >> 8) & 0xff, (midiCode >> 16) & 0xff, route, MidiChannel);

			break;

		case 0xC0: // Programm Change
			Cd[MidiChannel].Sound = (midiCode >> 8) & 0xff;

			break;

		case 0xB0: // Control Change
		{ int control = (midiCode >> 8) & 0xff;
				int data = (midiCode >> 16) & 0xff;
				if ( control == 64 ) {
					Cd[MidiChannel].Sustain = data;

					if ( route->GetOutputDevice() )
						route->GetOutputDevice()->Sustain(Cd[MidiChannel].Sustain, MidiChannel);

					break;
				} else if ( control == 0 ) // BankSelectMSB
				{
					Cd[MidiChannel].BankSelectMSB = data;
					break;
				} else if ( control == 32 ) // BankSelectLSB
				{
					Cd[MidiChannel].BankSelectLSB =data;
					break;
				}
		}
		case 0xA0:

		case 0xD0: // Key Pressure, Controler, Channel Pressure
			//3 ??
			break;
		}

		// Midianalyse
		int lMidiCode[8] = {
			3, 3, 3, 3, 2, 2, 3, 1
		};

		if ( Box >= 0 && route->Active )
			for (int i = 0; i < lMidiCode[MidiStatus >> 5]; i++) {
				MidiAnalysis(Box,midiCode & 0xff);
				midiCode >>= 8;
			}
	}

// Routen testen und jenachdem entsprechend Codeverarbeitung
	void InputMidiPort::Proceed(DWORD midiCode)
	{
		char DidOut = 0;

		for (routeListType::iterator R = routes.begin(); 
		     R!= routes.end(); R++)
			switch ( (*R)->Type ) {

			case RTchannel:
				if ( (*R)->Check(midiCode & 0x0F) ) {
					ProceedRoute(midiCode, (*R));
					DidOut = 1;
				}

				break;

			case RTstaff:
				if ( ((midiCode & 0xF0) != 0x80 && 
				      (midiCode & 0xF0) != 0x90) 
				     || (*R)->Check((midiCode >> 8) & 0xFF) ) {
					ProceedRoute(midiCode, (*R));
					DidOut = 1;
				}

				break;

			case RTelse:
				if ( DidOut )
					break;

			case RTall:
				ProceedRoute(midiCode, *R);
			}

		FLUSH_UPDATE_UI;
	}

	MidiPortFactory::~MidiPortFactory() {}

	OutputDevice MidiPortFactory::DoCreateOutput () const
	{
		return new OutputMidiPort();
	}

	OutputDevice MidiPortFactory::DoCreateOutput (int devId,
						      const mutStringRef name, 
						      int id) const
	{
		return new OutputMidiPort(devId,name,id);
	}

	OutputDevice MidiPortFactory::DoCreateOutput (int devId,
						      const mutStringRef name, 
						      MutaborModeType mode, 
						      int id) const
	{
		OutputMidiPort * port = new OutputMidiPort(devId,name,id);
		port->Device::SetId(id);
		switch (mode) {
		case DevicePause:
		case DeviceStop:
		case DevicePlay:
			port -> Open() ; 
			break;
		case DeviceUnregistered:
		case DeviceCompileError:
		case DeviceTimingError:
		default:
			UNREACHABLEC;
		}
		return port;
	}


	InputDevice MidiPortFactory::DoCreateInput () const
		
	{
		return new InputMidiPort();
	}

	InputDevice MidiPortFactory::DoCreateInput ( int devId,
					   const mutStringRef name, 
					    int id) const
	{
		return new InputMidiPort(devId,name,DeviceStop,id);
	}

	InputDevice MidiPortFactory::DoCreateInput (int devId,
					   const mutStringRef name, 
					   MutaborModeType mode, 
					   int id) const
	{
		return new InputMidiPort(devId,name,mode,id);
	}



#ifdef RTMIDI
#include <string>

	using namespace std;
#include "RtMidi.h"
	RtMidiOut *rtmidiout;
	RtMidiIn *rtmidiin;
#endif

	void MidiInit()
	{
#ifdef RTMIDI

		try {
			rtmidiout = new RtMidiOut();
		} catch (RtError &error) {
			error.printMessage();
			abort();
		}

		try {
			rtmidiin = new RtMidiIn();
		} catch (RtError &error) {
			error.printMessage();
			abort();
		}

#endif
	}

	void MidiUninit()
	{
		delete rtmidiin;
		delete rtmidiout;
	}

}

///\}
