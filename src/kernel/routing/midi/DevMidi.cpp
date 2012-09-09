/** \file 
 ********************************************************************
 * Midi Port IO (Mutabor layer)
 *
 * Copyright:   (c) 1998-2011 TU Dresden
 * \author  R.Krauße
 * Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 
 * $Date: 2012/01/29 22:08:36 $
 * \version $Revision: 1.16 $
 * \license GPL
 *
 ********************************************************************
 * \addtogroup route
 * \{
 ********************************************************************/

#include "src/kernel/routing/midi/DevMidi.h"
#include "src/kernel/Execute.h"
#include "src/kernel/GrafKern.h"
#include "src/kernel/MidiKern.h"
#include "src/kernel/routing/Route-inlines.h"
#include "wx/msgdlg.h"

// OutputMidiPort ------------------------------------------------------

//static long freq ;

// GET_INDEX is algready defined in MidiKern.h

// berechnet die 'Oktavlage' einer taste bzgl. tonsystem
#define GET_ABSTAND(taste,tonsystem)					\
	( (int)((taste)-( (tonsystem)->anker % (tonsystem)->breite ))	\
	  / (tonsystem)->breite -((int) (tonsystem)->anker		\
				  / (tonsystem)->breite ))

// berechnet die Frequenz in Midi-Form
#define GET_FREQ(taste,tonsystem)					\
	( ( (tonsystem)->ton[GET_INDEX(taste,(tonsystem))]==0) ?	\
	  (long) 0 :							\
	  (long)( (tonsystem)->periode *				\
		  GET_ABSTAND(taste,(tonsystem))  +			\
		  (tonsystem)->ton[GET_INDEX(taste,(tonsystem))]))


#ifdef RTMIDI
#include "RtMidi.h"
#endif


namespace mutabor {
#ifdef RTMIDI
	extern RtMidiOut *rtmidiout;
	
	extern RtMidiIn *rtmidiin;

// Midi-Ausgabe
#define MIDI_OUT3(code1, code2, code3)				\
	{ std::vector<unsigned char> message(3);		\
		message[0]=code1;				\
		message[1]=code2;				\
		message[2]=code3;				\
		DEBUGLOG2(midiio,_T("MIDI OUT %x %x %x"),	\
			  code1,code2,code3);			\
		hMidiOut->sendMessage(&message); }

#define MIDI_OUT2(code1, code2)				\
	{ std::vector<unsigned char> message(2);	\
		message[0]=code1;		\
		message[1]=code2;		\
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
	void OutputMidiPort::Save (tree_storage & config, const RouteClass * route)
	{
#ifdef DEBUG
		wxString oldpath = config.GetPath();
#endif
		mutASSERT(route);
		
		config.toLeaf(_T("Midi Output"));
		config.Write(_T("Avoid Drum Channel"), route->ONoDrum);
		config.Write(_T("Channel Range From"), route->OFrom);
		config.Write(_T("Channel Range To"), route->OTo);
		config.toParent();
		mutASSERT(oldpath == config.GetPath());
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
		Name = config.Read(_T("Device Name"), rtmidiout?(rtmidiout->getPortCount()?
				   muT(rtmidiout->getPortName(0).c_str()):wxString(_("Unknown"))):wxString(_("no device")));
		bending_range = config.Read(_T("Bending Range"),2);
		mutASSERT(oldpath == config.GetPath());
	}

/// Loade route settings (filter settings) for a given route
/** Some route settings (e.g. filter settings) are device type 
 * specific. This function loads them from a tree storage.
 * \argument config (tree_storage *) Storage class, where the data will be restored from.
 * \argument route (Route) Route whos data shall be loaded.
 */
	void OutputMidiPort::Load (tree_storage & config, RouteClass * route)
	{
#ifdef DEBUG
		wxString oldpath = config.GetPath();
#endif
		mutASSERT(route);
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
		mutASSERT(oldpath == config.GetPath());
	}


	bool OutputMidiPort::Open()
	{
		mutASSERT(!isOpen);
		DEBUGLOG (other, _T(""));
		int i;

		for (i = 0; i < 16; i++) {
			Cd[i].Reset();
			ton_auf_kanal[i].active = false;
			ton_auf_kanal[i].inkey = -1;
			ton_auf_kanal[i].outkey = -1;
			ton_auf_kanal[i].channel = 0;
			ton_auf_kanal[i].midi_channel = 0;
			ton_auf_kanal[i].unique_id = 0;
			KeyDir[i] = (char)i; // alle nicht benutzt
		}

		nKeyOn = 0;

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
		mutASSERT(isOpen);
		DEBUGLOG (other, _T(""));
		// alle liegenden Tˆne ausschalten

		for (int i = 0; i < 16; i++)
			if ( KeyDir[i] >= 16 )  // benutzt
				MIDI_OUT3(0x80+i, ton_auf_kanal[i].outkey, 64);

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

	void OutputMidiPort::NoteOn(int box, 
				    int inkey, 
				    int velo, 
				    RouteClass * r, 
				    size_t id, 
				    ChannelData *cd)
	{
		DEBUGLOG (other, _T("box %d, inkey %d, velo %d, id %d"),
			  box, inkey, velo, id);
		int free = 16, freeSus = r->OTo, freeV = 64, freeSusV = 64, s;
		DWORD p;
		long freq;

		if ( box == -2 ) {
			freq = ((long)inkey) << 24;
			box = 255;
		} else
			freq = GET_FREQ (inkey, mut_box[box].tonesystem);

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
					AM += ton_auf_kanal[j].inkey;

			AM /= r->OTo + 1 - r->OFrom;

			for ( j = r->OFrom; j <= r->OTo; j++ )
				if ( j != DRUMCHANNEL || !r->ONoDrum )
					if ( abs(AM - ton_auf_kanal[j].inkey) < abs(AM - ton_auf_kanal[free].inkey) )
						free = j;

			// Ton auf Kanal free ausschalten
			MIDI_OUT3(0x80+free, ton_auf_kanal[free].outkey, 64);

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

		ton_auf_kanal[free].outkey = (freq >> 24) & 0x7f;

		ton_auf_kanal[free].inkey = inkey;
		ton_auf_kanal[free].unique_id = id;
		ton_auf_kanal[free].channel = r->GetId();
		ton_auf_kanal[free].midi_channel = free;
		ton_auf_kanal[free].active = true;
//			MAKE_ID(r, box, inkey, channel);

		MIDI_OUT3(0x90+free, ton_auf_kanal[free].outkey, velo);

		if ( cd->Sustain ) {
			MIDI_OUT3(0xB0+free, 64, cd->Sustain);
			Cd[free].Sustain = cd->Sustain;
		}
	}

	void OutputMidiPort::NoteOff(int box, int inkey, int velo, 
				     RouteClass * r, size_t id)
	{
		if (!r || r == NULL) return;
		DEBUGLOG (midiio, _T("box %d, key %d, velo %d, id %d"),
			  box, inkey, velo, id);

		if ( box == -2 )
			box = MAX_BOX+1;


		if ( !velo ) //3 ?? notwendig?
			velo = 64;

		for (int i = r->OFrom; i <= r->OTo; i++)
			if ( i != DRUMCHANNEL || !r->ONoDrum )
				if ( KeyDir[i] >= 16 && ton_auf_kanal[i].unique_id == id && ton_auf_kanal[i].channel == r->GetId() ) {
					ton_auf_kanal[i].inkey=0;
					ton_auf_kanal[i].active = false;
// ???     ton_auf_kanal[i].id=0;
					MIDI_OUT3(0x80+i, ton_auf_kanal[i].outkey, velo);
					// KeyDir umsortieren
					int oldKeyDir = KeyDir[i];

					for (int k = 0; k < 16; k++)
						if ( KeyDir[k] > oldKeyDir || KeyDir[k] < 16) KeyDir[k]--;

					nKeyOn--;

					KeyDir[i] = 15;
					break;
				}
	}

	inline long LongAbs(long x)
	{
		return (x < 0)? -x : x;
	}

	void OutputMidiPort::NotesCorrect(RouteClass * route)
	{
		DEBUGLOG (midiio, _T(""));
		if (!route || route == NULL) {
			UNREACHABLEC;
			return;
		}

		for (int i = 0; i < 16; i++)
			if ( (KeyDir[i] >= 16 && ton_auf_kanal[i].active) || Cd[i].Sustain ) {
				int RouteID = (ton_auf_kanal[i].channel);
					       
				if (route->GetId() != RouteID) 
					continue;

				DEBUGLOG(midiio,_T("old(hex/dec): channel = %01x/%d, Inkey = %02x/%d, key = %02x/%d, pitch = %06x/%d"), 
					 i,i,ton_auf_kanal[i].inkey,ton_auf_kanal[i].inkey, 
					 ton_auf_kanal[i].outkey,ton_auf_kanal[i].outkey,Cd[i].Pitch,Cd[i].Pitch);

				long freq = GET_FREQ(ton_auf_kanal[i].inkey, mut_box[route->GetBox()].tonesystem);

				// hier kann ein evtl. grˆﬂerer bending_range genutzt werden, um
				// Ton aus und einschalten zu vermeiden
				if ( ton_auf_kanal[i].outkey == ((freq >> 24) & 0x7f) &&
				     Cd[i].Pitch == ((long)freq & 0xFFFFFF) )
					continue;


				long Delta = freq - ((long)ton_auf_kanal[i].outkey << 24);

				bool SwitchTone = (LongAbs(Delta) >= ((long)bending_range << 24));

				// evtl. Ton ausschalten
				if ( SwitchTone ) {
					if ( Cd[i].Sustain ) {
						MIDI_OUT3(0xB0+i, 64, 0);
						Cd[i].Sustain = 0;

						if ( KeyDir[i] < 16 )
							continue;
					}

					MIDI_OUT3(0x80+i, ton_auf_kanal[i].outkey, 0x7F);
					ton_auf_kanal[i].outkey = (freq >> 24) & 0x7F;
					Delta = freq - ((long)ton_auf_kanal[i].outkey << 24);
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
					MIDI_OUT3(0x90+i, ton_auf_kanal[i].outkey, 64);  //3 velo speichern ??
			}
	}

	void OutputMidiPort::Sustain(char on, int channel)
	{
		DEBUGLOG (other, _T(""));

		DWORD chan = channel; // Midi has unsigned channels

		for (int i = 0; i < 16; i++)
			if ( ton_auf_kanal[i].active && ton_auf_kanal[i].channel == channel ) {
				MIDI_OUT3(0xB0+i, 64, on);
				Cd[i].Sustain = on;
			}

	
		
	}

	int OutputMidiPort::GetChannel(int inkey)
	{
		DEBUGLOG (other, _T(""));

		for (int i = 0; i < 16; i++)
			if ( ton_auf_kanal[i].active && (ton_auf_kanal[i].inkey == inkey) )
				return i;

		return -1;
	}

//void Gis(GisToken *token, char turn) {};

#ifdef RTMIDI
	void OutputMidiPort::MidiOut(DWORD data, size_t n)
	{
		std::vector<unsigned char> message;

		while ( n-- ) {
			DEBUGLOG (midiio, _T("sending byte %x"), data & 0xff);
			message.push_back(data & 0xFF);
			data >>= 8;
		}

		hMidiOut->sendMessage(&message);
	}

	void OutputMidiPort::MidiOut(BYTE * data, size_t n)
	{
		std::vector<unsigned char> message;

		while ( n--) {
			DEBUGLOG (midiio, _T("sending byte %x"),(int) *data);
			message.push_back(*(data++) );
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

	void OutputMidiPort::Quite(RouteClass * r)
	{
		DEBUGLOG (other, _T(""));

		for (int i = 0; i < 16; i++)
			if ( ton_auf_kanal[i].active && ton_auf_kanal[i].channel == r->GetId() )
				NoteOff(r->GetBox(), ton_auf_kanal[i].inkey, 64, r, ton_auf_kanal[i].unique_id);
	}

	void OutputMidiPort::Panic()
	{
		DEBUGLOG (other, _T(""));

		for (int i = 0; i < 16; i++) {
			MIDI_OUT3(176+i, 123, 0);  // All notes off */
//			MIDI_OUT3(0xB0+i, 7, 127);  // main volume
			// sound piano
//			MIDI_OUT2(0xC0+i, 0);
			// Merker aufr‰umen
			ton_auf_kanal[i].active = false;
			ton_auf_kanal[i].inkey=0;
			ton_auf_kanal[i].unique_id=0;
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
			channelString += wxString::Format(_T(" ({%d,%d,%d,%d,%ld},%d,[%d,%d,%d,%d,%d])"),
							  Cd[i].Sound,
							  Cd[i].Sustain,
							  Cd[i].BankSelectMSB,
							  Cd[i].BankSelectLSB,
							  Cd[i].Pitch,
							  KeyDir[i],
							  ton_auf_kanal[i].active,
							  ton_auf_kanal[i].inkey,
							  ton_auf_kanal[i].outkey,
							  ton_auf_kanal[i].unique_id,
							  ton_auf_kanal[i].channel
				);
		}
		return OutputDeviceClass::TowxString()
			+ wxString::Format(_T("\
OutputMidiPort:\n\
   hMidiOut = %p\n\
   channels ({sound,sustain,MSB,LSB,pitch},KeyDir,[tasta,outkey,id]):\n\
             %s\n\
   nKeyOn   = %d\n\
"),hMidiOut, (const wxChar *)channelString, nKeyOn);

	}
#endif

// InputMidiPort -------------------------------------------------------

#ifdef RTMIDI

	void mycallback( double deltatime, std::vector< unsigned char > *message, void *userData )
	{
		mutUnused(deltatime);
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
		mutASSERT(oldpath == config.GetPath());
	}

/// Save route settings (filter settings) for a given route
/** Some route settings (e.g. filter settings) are device type 
 * specific. This function saves them in a tree storage.
 * \argument config (tree_storage *) Storage class, where the data will be saved.
 * \argument route (Route ) Route whos data shall be saved.
 */
	void InputMidiPort::Save (tree_storage & config, const RouteClass * route)
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
		mutASSERT(oldpath == config.GetPath());
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
				    (rtmidiin?(	
				    rtmidiin->getPortCount()?
				    muT(rtmidiin->getPortName(0).c_str()):wxString(_("Unknown"))):wxString(_("no device"))));
		mutASSERT(oldpath == config.GetPath());
	}

/// Loade route settings (filter settings) for a given route
/** Some route settings (e.g. filter settings) are device type 
 * specific. This function loads them from a tree storage.
 * \argument config (tree_storage *) Storage class, where the data will be restored from.
 * \argument route (Route ) Route whos data shall be loaded.
 */
	void InputMidiPort::Load (tree_storage & config, RouteClass * route)
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
		mutASSERT(oldpath == config.GetPath());
	}

	bool InputMidiPort::Open()
	{
		mutASSERT(!isOpen);
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
		mutASSERT(isOpen);
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
	}




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
					AddKey(&mut_box[Box], (midiCode >> 8) & 0xff, 0, route->GetId(), NULL);

				if ( route->GetOutputDevice() )
					route->GetOutputDevice()
						->NoteOn(Box, 
							 (midiCode >> 8) & 0xff, 
							 (midiCode >> 16) & 0xff,
							 route.get(),
							 MidiChannel, 
							 &Cd[MidiChannel]);

				break;
			}
			
		case 0x80: // Note Off
			if ( route->Active )
				DeleteKey(&mut_box[Box],(midiCode >> 8) & 0xff, 0, route->GetId());

			if ( route->GetOutputDevice() )
				route->GetOutputDevice()
					->NoteOff(Box, 
						  (midiCode >> 8) & 0xff, 
						  (midiCode >> 16) & 0xff, 
						  route.get(), 
						  MidiChannel);

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
				MidiAnalysis(&mut_box[Box],midiCode & 0xff);
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


		

	mutabor::OutputDeviceClass * MidiPortFactory::DoCreateOutput () const
	{
		OutputMidiPort * port = new OutputMidiPort();
		if (!port) throw DeviceNotCreated();
		return port;
	}

	mutabor::OutputDeviceClass * MidiPortFactory::DoCreateOutput(int devId,
							  const mutStringRef name, 
							  int id) const
	{
		OutputMidiPort * port = new OutputMidiPort(devId,name,id);
		if (!port) throw DeviceNotCreated();
		return port;
	}

	mutabor::OutputDeviceClass *  MidiPortFactory::DoCreateOutput (int devId,
							   const mutStringRef name, 
							   MutaborModeType mode, 
							   int id) const
	{
		OutputMidiPort * port = new OutputMidiPort(devId,name,id);
		if (!port) throw DeviceNotCreated();
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

	mutabor::InputDeviceClass * MidiPortFactory::DoCreateInput () const
		
	{
		InputMidiPort * port = new InputMidiPort();
		if (!port) throw DeviceNotCreated();
		return port;
	}

	mutabor::InputDeviceClass *  MidiPortFactory::DoCreateInput (int devId,
								const mutStringRef name, 
								int id) const
	{
		InputMidiPort * port = 
			new InputMidiPort(devId,name,
					  mutabor::DeviceStop,id);
		if (!port) throw DeviceNotCreated();
		return port;
	}

	mutabor::InputDeviceClass *  MidiPortFactory::DoCreateInput (int devId,
							 const mutStringRef name, 
							 MutaborModeType mode, 
							 int id) const
	{
 		InputMidiPort * port = new InputMidiPort(devId,name,mode,id);
		if (!port) throw DeviceNotCreated();
		return port;
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
			// abort();
		}

		try {
			rtmidiin = new RtMidiIn();
		} catch (RtError &error) {
			error.printMessage();
			// abort();
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
