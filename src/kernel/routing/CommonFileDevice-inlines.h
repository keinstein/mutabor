/** \file     -*- C++ -*-
 ********************************************************************
 * File player class which solves common tasks of file related devices
 * such as MIDI file players.
 *
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
#include "wx/timer.h"


namespace mutabor {


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
			wxString::Format(_T("\n  Name = %s\n  DevId = %d"), 
					 Name.c_str(), DevId);
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
/** \argument config (tree_storage) storage class, where the data will
 * be loaded from.
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

		Mode = DeviceStop;
		// init
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
		
		if ( Mode == DeviceCompileError )
			return;
		
		if (timer) {
			timer -> Delete();
		}

		referenceTime = 0;
		pauseTime = 0;
		Mode = DeviceStop;
	}

	inline void CommonFileInputDevice::Play(wxThreadKind kind)
	{

		switch (Mode) {
		case DeviceCompileError:
		case DeviceTimingError:
			return;
		case DeviceStop:
			if ( RealTime ) {
				mutASSERT(timer == NULL);
				referenceTime = wxGetLocalTimeMillis();
				pauseTime = 0;

				timer = new FileTimer(this,kind);
				if (!timer) return;
				wxThreadError result = timer -> Create(1024*100); // Stack Size
				if (result == wxTHREAD_NO_ERROR)
					timer -> Run();
				else {
					delete timer;
					timer = NULL;
					return;
				}
			
			}
			break;
		case DevicePause:
			if ( RealTime ) {
				referenceTime += wxGetLocalTimeMillis() - pauseTime;
				pauseTime = 0;
				if (timer) {
					mutASSERT(timer -> IsPaused());
					timer -> Resume();
				}
			}
			break;
		}
		Mode = DevicePlay;
	}

	inline void CommonFileInputDevice::Pause()
	{
		switch (Mode) {
		case DeviceCompileError:
		case DeviceTimingError:
		case DeviceStop:
			break;
		case DevicePlay:
			if ( RealTime ) {
				mutASSERT(timer != wxThread::This());
				if (timer) timer -> Pause();
				pauseTime = wxGetLocalTimeMillis();
			}
			Mode = DevicePause;
			Quite();
			break;
		case DevicePause:
			Play(); // A mechanical Pause button usually is released if pressed twice
			break;
		default:
			mutASSERT(!"Unknown value");
		}
	}

	inline wxThread::ExitCode CommonFileInputDevice::ThreadPlay()
	{
		mutASSERT(wxThread::This() == timer);
		mutASSERT(timer != NULL);
		mutASSERT(Mode != DeviceCompileError );

		wxLongLong nextEvent = 0; // in ms
		wxLongLong reference = 0;
		wxLongLong delta;
		wxThread::ExitCode e;
		do {
			mutASSERT(timer);
			if (timer->TestDestroy()) {
				switch (Mode) {
				case DevicePause:
				case DevicePlay: 
					Mode = DeviceStop;
				case DeviceStop:
					e = 0;
					break;
				case DeviceCompileError:
				default:
		 			e = (void *)1;
					mutASSERT(!"Thread should not have been run!");
				}
				return e;
			}
			nextEvent = PrepareNextEvent();
			reference = referenceTime;
			delta = reference + nextEvent - wxGetLocalTimeMillis();
			if (delta > 0) {
				unsigned long s1;
#ifdef wxLongLong_t
				wxLongLong_t s = delta.GetValue();
				s1 = (s > std::numeric_limits<unsigned long>::max()) ? std::numeric_limits<unsigned long>::max(): s;
#else
				if (delta.GetHi()) 
					s1 = std::numeric_limits<unsigned long>::max();
				else 
					s1 = delta.GetLo();
#endif
				wxThread::Sleep(s1);
			}
		} while (IsDelta(nextEvent));
		switch (Mode) {
		case DevicePlay:
		case DevicePause: 
			Mode = DeviceStop;
		case DeviceStop:
			e = 0;
		case DeviceTimingError:
		case DeviceCompileError:
		default:
			e = (void *)1;
			break;
		}
		referenceTime = 0;
		pauseTime = 0;
		return NULL;
	}

	
#ifdef WX
	inline wxString CommonFileInputDevice::TowxString() const {
		return InputDeviceClass::TowxString() +
			wxString::Format(_T("\n  time zero at = %ld ms\n  paused at  = %ld msx"),
					 referenceTime, pauseTime);
	}
#endif
	
}
///\}
