/** \file     -*- C++ -*-
 ********************************************************************
 * File player class which solves common tasks of file related devices such as MIDI file players.
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/src/kernel/routing/midi/DevMidF.cpp,v 1.13 2011/11/02 14:31:57 keinstein Exp $
 * Copyright:   (c) 2012 Tobias Schlemmer
 * \author Tobias Schlemmer <keinstein@users.berlios.de>
 * \date $Date: 2011/11/02 14:31:57 $
 * \version $Revision: 1.13 $
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
 *
 * $Log$
 *
 ********************************************************************
 * \addtogroup route
 * \{
 ********************************************************************/
#include "src/kernel/Defs.h"

#include "src/kernel/routing/CommonFileDevice.h"
#include "src/kernel/Execute.h"
#include "src/kernel/GrafKern.h"
#include "src/kernel/Runtime.h"

#include "wx/wfstream.h"
#include "wx/msgdlg.h"


namespace mutabor {


#define NO_DELTA 0x7fffffffl //2147483647  // long max-Zahl
	
	unsigned long CommonFileOutputDevice::NRT_Speed=0l;


// OutputMidiFile ------------------------------------------------------

/// Save current file name in a tree storage
/** \argument config (tree_storage) storage class, where the data will be saved.
 */
	inline void CommonFileOutputDevice::Save (tree_storage & config) 
	{
#ifdef DEBUG
		wxString oldpath = config.GetPath();
#endif
		config.Write(_T("File Name"),Name);
		mutASSERT(oldpath == config.GetPath());
	}



/// Load current device settings from a tree storage
/** \argument config (tree_storage) storage class, where the data will be loaded from.
 */
	inline void CommonFileOutputDevice::Load (tree_storage & config)
	{
#ifdef DEBUG
		wxString oldpath = config.GetPath();
#endif
		Name = config.Read(_T("File Name"),mutEmptyString);
		mutASSERT(oldpath == config.GetPath());
	}

	inline bool CommonFileOutputDevice::Open()
	{
		mutASSERT(!isOpen);
		isOpen = true;
		return isOpen;
	}

	inline void CommonFileOutputDevice::Close()
	{
		mutASSERT(isOpen);
		isOpen = false;
	}

#ifdef WX
	inline wxString CommonFileOutputDevice::TowxString() const {
		wxString s = OutputDeviceClass::TowxString() +
			wxString::Format(_T("\n  Name = %s\n  DevId = %d"), Name.c_str(), DevId);
		return s;
	}
#endif



	
// CommonFileInputDevice -------------------------------------------------------


/// Save current device settings in a tree storage
/** \argument config (tree_storage) storage class, where the data will be saved.
 */
	inline void CommonFileInputDevice::Save (tree_storage & config)
	{
#ifdef DEBUG
		wxString oldpath = config.GetPath();
#endif
		config.Write(_T("File Name"),Name);
		mutASSERT(oldpath == config.GetPath());
	}


/// Load current device settings from a tree storage
/** \argument config (tree_storage) storage class, where the data will be loaded from.
 */
	inline void CommonFileInputDevice::Load (tree_storage & config)
	{
#ifdef DEBUG
		wxString oldpath = config.GetPath();
#endif
		Name = config.Read(_T("File Name"),mutEmptyString);
		mutASSERT(oldpath == config.GetPath());
	}
	



	inline bool CommonFileInputDevice::Open()
	{
		mutASSERT(!isOpen);
		DEBUGLOG (other, _T("start"));
		// Mode setzen
		Mode = DeviceStop;
		// initialisieren
		Stop();
		DEBUGLOG (other, _T("finished. Mode = %d, this = %p"),Mode,this);
		isOpen = true;
		return true;
	}

	inline void CommonFileInputDevice::Close()
	{
		mutASSERT(isOpen);
		Stop();
		isOpen = false;
	}

	inline void CommonFileInputDevice::Stop()
	{
		DEBUGLOG(routing,_T("old mode = %d"),Mode);
		if ( Mode == DevicePlay || Mode == DeviceTimingError )
			Pause();

		// OK ?
		if ( Mode == DeviceCompileError )
			return;

		// Delta-Times lesen
		minDelta = 0;
		actDelta = -1;
		Mode = DeviceStop;
	}

	inline void CommonFileInputDevice::Play()
	{
		if ( RealTime ) {
			if (!timer.Start(2,wxTIMER_CONTINUOUS)) {
				return;
			}
		}

		Busy = FALSE;

		Mode = DevicePlay;
	}

	inline void CommonFileInputDevice::Pause()
	{
		if ( RealTime )
			timer.Stop();

		Mode = DevicePause;

		Quite();
	}

	inline void CommonFileInputDevice::TimerCallback()
	{
		actDelta++;
		if ( Busy ) {
			return;
		}

		if ( actDelta < minDelta )
			return;

		// Zeitpunkt ist ran, also verarbeiten
		Busy = TRUE;

		actDelta -= minDelta;

		IncDelta();


		if ( minDelta == NO_DELTA ) {
			// we have reached the end of all tracks
//			InDevChanged = 1;
			Stop();
			//		Mode = DeviceTimingError;
		}

#if (DEBUG && WX)
		mutASSERT(minDelta > 0);
		DEBUGLOG(midifile,_T("new mindelta = %d"),minDelta);
#endif

		Busy = FALSE;
	}
	
#ifdef WX
	inline wxString CommonFileInputDevice::TowxString() const {
		return InputDeviceClass::TowxString() +
			wxString::Format(_T("\n  minDelta = %ld\n  actDelta = %ld\n  Busy = %d"),
					 minDelta, actDelta, 
					 Busy);
	}
#endif
	
}
///\}
