/** \file          -*- C++ -*-
 ********************************************************************
 * Mutabor runtime functions.
 *
 * Copyright:   (c) 1997-2011 TU Dresden
 * \author Rüdiger Krauße <krausze@mail.berlios.de>
 * Tobias Schlemmer <keinstein@users.berlios.de>
 * \license GPL
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
 ********************************************************************
 * \defgroup runtime Runtime functions
 * \{
 ********************************************************************
 */
#include "src/kernel/Defs.h"

#include "src/kernel/Global.h"
#include "src/kernel/Parser.h"

#include "src/kernel/Hilfs.h"
//#include "src/kernel/GrafKern.h"

#include "src/kernel/Runtime.h"
#include "src/kernel/Execute.h"
//#include "Mutabor.rh"
#include <setjmp.h>

#include "src/kernel/routing/Device.h"
#include "src/kernel/routing/Route-inlines.h"
#include "src/kernel/routing/gmn/DevGIS.h"
#include "src/kernel/routing/midi/DevMidi.h"
#include "src/kernel/routing/midi/DevMidF.h"
#include "wx/msgdlg.h"

#ifdef __cplusplus
namespace mutabor {
	namespace hidden {
		extern "C" {
#endif

jmp_buf weiter_gehts_nach_compilerfehler;

#if 0 
struct keyboard_ereignis *last;
#endif


bool  TSChanged(mutabor_box_type * box) {
	int flag = memcmp(&(box->last_tonesystem),
			  box->tonesystem,
			  (2*sizeof(int)) + sizeof(long) +
			  (box->tonesystem->breite*
			   sizeof(long)) );
	box->last_tonesystem = *(box->tonesystem);
	return flag;
}

void  GetInDevicesMode(enum MutaborModeType *mode) {
	int nr = 0;

	const InputDeviceList & list = 
		InputDeviceClass::GetDeviceList(); 
	for (InputDeviceList::const_iterator In = list.begin();
	     In != list.end(); In++)
		mode[nr] = (*In)->GetMode();
}


char  GetChannels(mutabor_box_type * box, char start, int &base, int &from, int &to, int &thru) {
	if ( start )
		box->file->lauf_instrument = box->file->list_of_config_instrumente;
	else if ( box->file->lauf_instrument )
		box->file->lauf_instrument = box->file->lauf_instrument -> next;

	if ( !box->file->lauf_instrument ) return 0;

	base = box->file->lauf_instrument -> midi_in;

	from = box->file->lauf_instrument -> midi_von;

	to 	 = box->file->lauf_instrument -> midi_bis;

	thru = box->file->lauf_instrument -> midi_umleit;

	return 1;
}

void  SetChannels(mutabor_box_type * box, int base, int from, int to, int thru) {
	get_instrument_dekl (box, base, from, to, thru, &box->file->list_of_config_instrumente);
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

#define GETLINE					\
	if ( !GetELine(config, i, s) )		\
		return


/*
// das nr-ste Output Device
// TODO Nr from 0 or 1?
OutputDevice *GetOut(int nr) {
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

// Timerdaten
void  GetTimerData(UINT &min, UINT &max) {
#if !defined(WX) || defined(__WXMSW__)
	TIMECAPS TimeCaps;
	timeGetDevCaps(&TimeCaps, sizeof(TIMECAPS));
	min = TimeCaps.wPeriodMin;
	max = TimeCaps.wPeriodMax;
#else
	//TODO
#endif
}

*/


#ifdef __cplusplus
		}
	}
}
#endif


/* \} */
