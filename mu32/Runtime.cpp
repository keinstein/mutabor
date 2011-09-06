/** \file
 ********************************************************************
 * Mutabor runtime functions.
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/mu32/Runtime.cpp,v 1.19 2011/09/06 08:09:20 keinstein Exp $
 * Copyright:   (c) 1997-2007 TU Dresden
 * \author R√ºdiger Krau√üe <krausze@mail.berlios.de>
 * Tobias Schlemmer <keinstein@users.berlios.de>
 * \date $Date: 2011/09/06 08:09:20 $
 * \version $Revision: 1.19 $
 * \license GPL
 *
 * $Log: Runtime.cpp,v $
 * Revision 1.19  2011/09/06 08:09:20  keinstein
 * fix a compiler error showing a corruped error message
 *
 * Revision 1.18  2011-07-27 20:48:32  keinstein
 * started to move arrays using MAX_BOX into struct mutabor_box_type
 *
 * Revision 1.17  2011-03-06 13:15:41  keinstein
 * some rearrangement for update callback kernel->GUI
 *
 * Revision 1.16  2011-02-20 22:35:55  keinstein
 * updated license information; some file headers have to be revised, though
 *
 * Revision 1.15  2010-11-21 13:15:45  keinstein
 * merged experimental_tobias
 *
 * Revision 1.14.2.9  2010-11-20 21:58:16  keinstein
 * reactivate midi playback
 *
 * Revision 1.14.2.8  2010-11-14 22:29:53  keinstein
 * Remvoed EDevice.cpp and EDevice.h from the sources list
 * They still reside in the source tree, since they have been used for Midi/GMN
 * file playing. That funcitonality has been disabled so far.
 * After reimplementation the files can be removed.
 *
 * Revision 1.14.2.7  2010-05-07 11:40:27  keinstein
 * actual_settings
 *
 * Revision 1.14.2.6  2010/04/15 09:28:43  keinstein
 * changing routes works, but is not honoured by MIDI, yet
 *
 * Revision 1.14.2.5  2010/03/30 08:38:27  keinstein
 * added rudimentary command line support
 * changed debug system to allow selection of messages via command line
 * further enhancements to the route dialogs
 *
 * Revision 1.14.2.4  2010/01/14 09:34:24  keinstein
 * Checkin searching for a bug
 *
 * Revision 1.14.2.3  2009/11/03 12:39:31  keinstein
 * input device dialog: Allow to edit input devices
 * fix a bug on Mac OS X, that prevented Mutabor from starting if no MIDI device is availlable
 *
 * Revision 1.14.2.2  2009/08/10 11:15:46  keinstein
 * some steps towards new route window
 *
 * Revision 1.14.2.1  2009/08/04 11:30:49  keinstein
 * removed mut.h
 *
 * Revision 1.14  2008/10/27 14:57:51  keinstein
 * Moved CurrentTimer stuff to Device
 *
 * Revision 1.13  2008/10/19 23:08:32  krausze
 * Dateien und Anpassungen f¸r Microsoft Visual Studio 8 (VC8)
 *
 * Revision 1.12  2008/10/10 08:33:19  keinstein
 * make compile on windws
 *
 * Revision 1.11  2008/10/01 09:31:07  keinstein
 * Routing broken
 *
 * Revision 1.10  2008/07/21 09:03:11  keinstein
 * Use symbolic enum values for device modes and device actions
 * move FlushUpdateUI() to Execute.cpp
 *
 * Revision 1.9  2008/06/02 16:02:00  keinstein
 * dont include Mutabor.rh since it is already included now
 * New interfache for IntCompDia
 * Set status dialog fields directly
 *
 * Revision 1.8  2008/03/11 10:37:34  keinstein
 * Holyday edition
 * put CM_xxx in an enum
 * use wx constants
 * document mutframe
 * some white space formattings
 * make route saving more system specific
 * many other fixes
 *
 *
 ********************************************************************
 * \defgroup runtime Runtime functions
 * \{
 ********************************************************************
 */
#include "Defs.h"

#include "Global.h"

#include "Hilfs.h"
#include "GrafKern.h"

#include "Runtime.h"
#include "Execute.h"
//#include "Mutabor.rh"
#include <setjmp.h>

#include "Device.h"
#include "DevGIS.h"
#include "DevMidi.h"
#include "DevMidF.h"

#ifdef __cplusplus
extern "C"
{
#endif
	bool RealTime = false;

	jmp_buf weiter_gehts_nach_compilerfehler;

	char pascal _export Compile(CompDlg *compDia, const wxChar *name) {
		InitCompDia(compDia, name);
		
		if (!setjmp(weiter_gehts_nach_compilerfehler)) {
			loesche_syntax_speicher();
			init_yylex ();

			mutabor_programm_einlesen ( name );

			calc_declaration_numbers();

			compDia->SetStatus(sd1,sd2,sd3,sd4,sd5,sd6);

			//	 show_line_number(-1);

			compDia->SetButtonText(_("Generating tables"));
			compDia->Refresh();

			mutabor_tabellen_generator();


			compDia->SetButtonText(_("Translation successful"));
			compDia->SetMessage(_("No error occured."));
			compDia->Refresh();

			return 1;
		} else {
			//show_line_number(-1);
			compDia->SetButtonText(_("Translation interrupted."));

			compDia->SetMessage(Fmeldung);
			compDia->Refresh();

			return 0;
		}
	}

	UpdateCallback* updatecallback;

	bool pascal _export Activate(bool realTime, UpdateCallback* callback) {
		RealTime = realTime;
		GlobalReset();
		AktionenInit();
		updatecallback = callback;
#if !defined(WX) || defined(__WXMSW__)

		if ( RealTime )
			timeBeginPeriod(1);

#endif
		bool ok = OutOpen();

		if ( ok && !InOpen() ) {
			ok = false;
			OutClose();
		}

		if ( !ok ) {
#if !defined(WX) || defined(__WXMSW__)
			if ( RealTime )
				timeEndPeriod(1);
#endif
			wxMessageBox(Fmeldung, _("Activation error"), wxOK | wxICON_ASTERISK );
			return false;
		}

		if ( RealTime )
			StartCurrentTime();
		else
			CurrentTime = 0;
		return true;
	}

	void pascal _export Stop() {
		if ( RealTime )
			StopCurrentTime();

		InClose();

		OutClose();

#if !defined(WX) || defined(__WXMSW__)
		if ( RealTime )
			timeEndPeriod(1);

#endif
		GlobalReset();
	}


// NoRealTime - Aktionen

	void NRT_Play() {
		// start all devices

		for (InDevice *In = InDevice::GetDeviceList(); In; In = In->GetNext())
			In->Play();

		// time slices
		bool Working = true;

		while ( Working ) {
			Working = false;

			for (InDevice *In = InDevice::GetDeviceList(); In; In = In->GetNext())
				if ( In->GetMode() == 1 && In->GetType() == DTMidiFile ) {
					((InMidiFile*)In)->IncDelta();
					Working = true;
				}

			CurrentTime.Notify();
		}

		// close all devices
		for (InDevice *In1 = InDevice::GetDeviceList(); In1; In1 = In1->GetNext())
			In1->Stop();

		InDevChanged = 1;
	}

	void pascal _export InDeviceAction(int inDevNr, enum MutaborModeType action) {
//  return; entkoppeln (zum debuggen)

		if ( !RealTime ) {
			NRT_Play();
			return;
		}

		InDevice *In = InDevice::GetDeviceList();

		while ( In && inDevNr ) {
			In = In->GetNext();
			inDevNr--;
		}

		if ( !In || In->GetMode() == MutaborDeviceCompileError ) return;
		switch ( action ) {

		case MutaborDeviceStop:
			In->Stop();
			break;

		case MutaborDevicePlay:
			In->Play();
			break;

		case MutaborDevicePause:
			In->Pause();
			break;

                case MutaborDeviceUnregistered:
                        std::cerr << "Device is unregistered. Aborting.";
                        abort();

                case MutaborDeviceCompileError:
                        std::cerr << "Unhandled compile error. Aborting.";
                        abort();

                case MutaborDeviceTimingError:
                        std::cerr << "Unhandled timing error. Aborting.";
                        abort();
		}
	}

	void pascal _export Panic() {
		OutDevice *Out = OutDevice::GetDeviceList();
		while ( Out ) {
			Out->Panic();
			Out = Out->GetNext();
		}
                MutResetKeys();
                for (int i = 0; i<MAX_BOX ; i++) 
                {
                        updatecallback(i,false);
                }
	}

	bool pascal _export CheckNeedsRealTime() {
		return NeedsRealTime();
	}

	struct keyboard_ereignis *last;

	char pascal _export GetMutTag(char &isLogic, char *text, char *einsttext, char &key, int box) {
		if ( box != -1 )
			last = first_keyboard[box];
		else
			if ( last ) last = last->next;

		if ( !last ) return 0;

		key = last->taste;

		strncpy(text, last->aktion->name, 20);

		isLogic = ( last->the_logik_to_expand != NULL );

		if ( isLogic && last->the_logik_to_expand->einstimmungs_name )
			strncpy(einsttext, last->the_logik_to_expand->einstimmungs_name, 20);
		else
			strcpy(einsttext, "");

		return 1;
	}

	char pascal _export IsLogicKey(char key) {

		struct keyboard_ereignis *last = first_keyboard[aktuelle_keyboard_box];

		while ( last ) {
			if ( key == last->taste )
				return last->the_logik_to_expand != NULL;

			last = last->next;
		}

		return 2;
	}

	bool pascal _export KeyChanged(int box) {
		int flag = keys_changed[box];
		keys_changed[box] = 0;
		return flag;
	}

	tone_system last_tonsystem[MAX_BOX];

	bool pascal _export TSChanged(int box) {
		int flag = memcmp(&(last_tonsystem[box]),
		                  mut_box[box].tonesystem,
		                  (2*sizeof(int)) + sizeof(long) +
		                  (mut_box[box].tonesystem->breite*
		                   sizeof(long)) );
		last_tonsystem[box] = *(mut_box[box].tonesystem);
		return flag;
	}

	bool pascal _export InDevicesChanged() {
		char flag = InDevChanged;
		InDevChanged = 0;
		return flag;
	}

	void pascal _export GetInDevicesMode(enum MutaborModeType *mode) {
		int nr = 0;

		for (InDevice *In = InDevice::GetDeviceList(); In; In = In->GetNext(),nr++)
			mode[nr] = In->GetMode();
	}

	struct instrument * lauf_instrument;

	char pascal _export GetChannels(char start, int &base, int &from, int &to, int &thru) {
		if ( start )
			lauf_instrument = list_of_config_instrumente;
		else if ( lauf_instrument )
			lauf_instrument = lauf_instrument -> next;

		if ( !lauf_instrument ) return 0;

		base = lauf_instrument -> midi_in;

		from = lauf_instrument -> midi_von;

		to 	 = lauf_instrument -> midi_bis;

		thru = lauf_instrument -> midi_umleit;

		return 1;
	}

	void pascal _export SetChannels(int base, int from, int to, int thru) {
		get_instrument_dekl (base, from, to, thru, &list_of_config_instrumente);
	}

	void pascal _export SetAktuellesKeyboardInstrument(int instr) {
		aktuelle_keyboard_box = instr;
	}

	int pascal _export GetAktuellesKeyboardInstrument() {
		return aktuelle_keyboard_box;
	}

// scan-Hilfsfunktionen ---------------------------------------------

	bool GetELine(const wxString& p, size_t& i, wxString &s);

	DevType Str2DT(const wxString& type);

// aus p eine Zeile in s lesen, p wird verschoben
	bool GetLine(char **p, char *s) {
		if ( !p || !(*p)[0] )
			return FALSE;

		while ( (*p)[0] == ' ' || (*p)[0] == '\n' || (*p)[0] == '\r' )
			*p = &(*p)[1];

		if ( !(*p)[0] )
			return FALSE;

		char *p1 = *p;

		*p = strchr(p1, '\n');

		if ( !p )
			*p = &p1[strlen(p1)];

		int i = (*p)-p1;

		strncpy(s, p1, i);

		s[i] = 0;

		return TRUE;
	}

#define GETLINE \
  if ( !GetELine(config, i, s) ) \
    return


// das nr-ste Output Device
// TODO Nr from 0 or 1?
	OutDevice *GetOut(int nr) {
		DEBUGLOG2(other,_T("Nr.: %d"),nr);

		if ( nr < 0 )
			return 0;

		OutDevice *Out = OutDevice::GetDeviceList();

		while ( Out ) {
			if (Out->GetDevId() == nr) break;

			Out = Out->GetNext();

			DEBUGLOG2(other,_T("Nr.: %d, Out: %x"),nr, Out);
		}

		return Out;
	}

#if 0
// Device aus einem String scannen
	void pascal _export ScanDevices(const wxString &config) {
		// Listen s‚Ä∞ubern

		if ( InDevice::GetDeviceList() ) {
			delete InDevice::GetDeviceList();
		}

		if ( OutDevices ) {
			delete OutDevices;
			OutDevices = 0;
		}

		// Zerlegen von config
		wxString s;

		size_t i = 0;

		GETLINE;

		while ( !s.StartsWith(_T("OUTPUT" ))) {
			GETLINE;
		}

		GETLINE;

		// Output lesen
		OutDevice **PreOut = &OutDevices;

		while ( !s.StartsWith(_T("INPUT") )) {
			wxChar Type[80], Name[400];
			int DevId, BendingRange;
#if (wxUSE_UNICODE || wxUSE_WCHAR_T)
			int test = SSCANF (s, _T("%ls \"%l[^\"]\" %d %d"), Type, Name, &DevId, &BendingRange);

			if ( test < 2 )
				test = SSCANF (s, _T("%ls %ls %d %d"), Type, Name, &DevId, &BendingRange);

#else
			int test = SSCANF (s, _T("%s \"%[^\"]\" %d %d"), Type, Name, &DevId, &BendingRange);

			if ( test < 2 )
				test = SSCANF (s, _T("%s %s %d %d"), Type, Name, &DevId, &BendingRange);

#endif
			if ( test < 2 ) {
				//3 ??
			}

			OutDevice *Out;

			switch ( Str2DT(Type) ) {

			case DTUnknown:
				std::cerr << "Unknown device: " << Type << std::endl;

				//3 ??

			case DTGis:
				Out = new OutGis(Name);

				break;

			case DTMidiPort:
				Out = new OutMidiPort(Name, DevId, BendingRange);

				break;

			case DTMidiFile:
				Out = new OutMidiFile(Name, DevId, BendingRange);

				break;
			}

			*PreOut = Out;

			PreOut = &(Out->Next);
			GETLINE;
		}

		GETLINE;

		// Input lesen

		while ( 1 ) {
			// Device lesen
			wxChar Type[80], Name[400];
			int DevId = -1;
#if (wxUSE_UNICODE || wxUSE_WCHAR_T)
			int test = SSCANF (s, _T("%ls \"%l[^\"]\" %d"), Type, Name, &DevId);

			if ( test < 2 )
				test = SSCANF (s, _T("%ls %ls %d"), Type, Name, &DevId);

#else
			int test = SSCANF (s, _T("%s \"%[^\"]\" %d"), Type, Name, &DevId);

			if ( test < 2 )
				test = SSCANF (s, _T("%s %s %d"), Type, Name, &DevId);

#endif
			if ( test < 2 ) {
				//3 ??
			}

			InDevice *In;

			switch ( Str2DT(muT(Type)) ) {

			case DTUnknown:
				//3 ??

			case DTGis:
				In = new InGis(Name, _T("GIS"));

				break;

			case DTMidiPort:
				In = new InMidiPort(Name, DevId);

				break;

			case DTMidiFile:
				In = new InMidiFile(Name, 0);

				break;
			}


			GETLINE;
			// Routen lesen

			while ( Str2DT(s) == DTUnknown ) {
				// Route lesen
				wxChar Type[40];
				int IFrom = 0, ITo = 0, Box = 0, BoxActive = 0, OutDev = -1, OFrom = -1, OTo = -1, ONoDrum = 1;
#if (wxUSE_UNICODE || wxUSE_WCHAR_T)
				test = SSCANF(s, _("%ls %d %d %d %d %d %d %d %d"),
				              Type, &IFrom, &ITo, &Box, &BoxActive, &OutDev, &OFrom, &OTo, &ONoDrum);
#else
				test = SSCANF(s, _("%s %d %d %d %d %d %d %d %d"),
				              Type, &IFrom, &ITo, &Box, &BoxActive, &OutDev, &OFrom, &OTo, &ONoDrum);
#endif

				if ( test < 2 ) {
					//3 ??
				}

				if ( Box == -2 ) // zur Sicherheit
					BoxActive = 0;

				In->AddRoute(new Route(Str2RT(Type), IFrom, ITo, Box, BoxActive, GetOut(OutDev), OFrom, OTo, ONoDrum));

				GETLINE;
			}
		}
	}

#endif

// Timerdaten
	void pascal _export GetTimerData(UINT &min, UINT &max) {
#if !defined(WX) || defined(__WXMSW__)
		TIMECAPS TimeCaps;
		timeGetDevCaps(&TimeCaps, sizeof(TIMECAPS));
		min = TimeCaps.wPeriodMin;
		max = TimeCaps.wPeriodMax;
#else
		//TODO
#endif
	}

} // Extern C

/* \} */
