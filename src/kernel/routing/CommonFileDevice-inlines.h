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
#ifdef DEBUG
		mutASSERT(oldpath == config.GetPath());
#endif
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
#ifdef DEBUG
		mutASSERT(oldpath == config.GetPath());
#endif
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
			wxString::Format(_T("\n  Name = %s\n  session_id = %lu\n  routefile_id = %d"), 
					 Name.c_str(), (unsigned long)session_id(), routefile_id);
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
#ifdef DEBUG
		mutASSERT(oldpath == config.GetPath());
#endif
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
#ifdef DEBUG
		mutASSERT(oldpath == config.GetPath());
#endif
	}
	



	inline bool CommonFileInputDevice::Open()
	{
		mutASSERT(!isOpen);
		DEBUGLOG (other, _T("start"));

		Mode = DeviceStop;
		// init
		Stop();
		DEBUGLOG (other, _T("finished. Mode = %d, this = %p"),Mode,(void*)this);
		isOpen = true;
		return true;
	}

	inline void CommonFileInputDevice::Close()
	{
#ifdef DEBUG
		if (mutabor::CurrentTime.isRealtime()) {
			mutASSERT(isOpen);
		}
#endif
		Stop();
		isOpen = false;
	}

	inline void CommonFileInputDevice::Stop()
	{
		DEBUGLOG(routing,_T("old mode = %d"),Mode);
		if ( Mode == DevicePlay || Mode == DeviceTimingError )
			Pause();
		
		mutASSERT(Mode == DevicePause || !timer);
		if (timer && (timer != wxThread::This())) {
			timer -> ClearFile();
			timer -> Delete();
			timer = NULL;
		}

		referenceTime = 0;
		pauseTime = 0;

		if ( Mode != DeviceCompileError )
			Mode = DeviceStop;
	}

	inline void CommonFileInputDevice::Play(wxThreadKind kind)
	{
		static bool starting = false;

		if (starting) return;
		starting = true;
		
		switch (Mode) {
		case DeviceCompileError:
		case DeviceTimingError:
		case DeviceUnregistered:
			DEBUGLOG(timer,_T("Returnung due to device error."));
			starting = false; 
			return;
		case DeviceStop:
			DEBUGLOG(timer,_T("Stopped. Realtime = %d."),(int)mutabor::CurrentTime.isRealtime());
			referenceTime = CurrentTime.Get();
			pauseTime = 0;

			if ( mutabor::CurrentTime.isRealtime() ) {
				mutASSERT(timer == NULL);

				timer = new FileTimer(this,kind);
				if (!timer) {
					starting = false; 
					return;
				}
				wxThreadError result = timer -> Create(1024*100); // Stack Size
				if (result == wxTHREAD_NO_ERROR)
					timer -> Run();
				else {
					delete timer;
					timer = NULL;
					starting = false; 
					return;
				}
			}
			break;
		case DevicePause:
			DEBUGLOG(timer,_T("Paused. Realtime = %d."),(int)CurrentTime.isRealtime());
			referenceTime += CurrentTime.Get() - pauseTime;
			pauseTime = 0;
			// timer should be 0 in Realtime mode
			mutASSERT(!timer || CurrentTime.isRealtime());
			if (timer) {
				mutASSERT(timer -> IsPaused());
				timer -> Resume();
			}
			break;
		case DevicePlay:
			starting = false; 
			return;
		}
		DEBUGLOG(timer,_T("timer = %p"),(void*)timer);
		Mode = DevicePlay;
		starting = false;
	}

	inline void CommonFileInputDevice::Pause()
	{
		switch (Mode) {
		case DeviceCompileError:
		case DeviceTimingError:
		case DeviceStop:
			break;
		case DevicePlay:
			if ( CurrentTime.isRealtime() ) {
				// we use this function for some cleanup inside Stop()
				// which is called from inside the thread.
				// In this case we shouldn't pause ourselves
				if (timer != wxThread::This()) {
					timer -> Pause();
				}
			}
			pauseTime = CurrentTime.Get();
			Mode = DevicePause;
			Panic();
			break;
		case DevicePause:
			Play(); // A mechanical Pause button usually is released if pressed twice
			break;
		default:
			mutASSERT(!"Unknown value");
		}
	}
	
	/* we use microseconds as errors sum up */

	inline wxThread::ExitCode
	CommonFileInputDevice::ThreadPlay(FileTimer * thistimer)
	{
		/// \todo clean-up race conditions
		mutASSERT(wxThread::This() == timer);
		
		mutASSERT(timer != NULL);
		mutASSERT(Mode != DeviceCompileError );


		/* this looks a little bit strange. But it is hard to
		 * compare two sined and unsiged integers whose size we do not
		 * know. */
		mutint64 maxallowed = (mutint64)(std::numeric_limits<mutint64>::max());
		const unsigned long maxulong = (std::numeric_limits<unsigned long>::max());
		maxallowed /= 1000;
		mutint64 alloweddelta;
		
		if ((unsigned long) maxallowed <= maxulong && 
		    (maxallowed  <= (mutint64) maxulong ||
		     (mutint64) maxulong < 0))
			alloweddelta = std::numeric_limits<mutint64>::max();
		else 
			alloweddelta = 1000*(mutint64)maxulong;


		mutint64 nextEvent = wxLL(0); // in μs
		mutint64 playTime  = wxLL(0); // in μs
		mutint64 reference = wxLL(0); // in μs
		mutint64 delta; // in ms
		wxThread::ExitCode e;
		do {
			if (thistimer->TestDestroy()) {
				break;
			}
			nextEvent = PrepareNextEvent();
			mutASSERT(nextEvent >= 0);
			DEBUGLOG(timer,_T("Preparing next event is at %ld (isdelta=%d)"), nextEvent,IsDelta(nextEvent));
			DEBUGLOG(timer,_T("NoDelta = %ld"), GetNO_DELTA());
			if (IsDelta(nextEvent)) {
				reference = referenceTime;
				playTime += nextEvent;
				DEBUGLOG(timer,_T("time: %ld μs"),CurrentTime.Get());
				delta = reference + playTime - CurrentTime.Get();
				DEBUGLOG(timer,_T("Delta %ld μs."),delta);
				
				if (delta > 0) {
					if (delta > alloweddelta) {
						nextEvent = GetNO_DELTA();
						Mode = DeviceTimingError;
						break;
					}

					DEBUGLOG(timer,_T("Sleeping %ld ms."),(unsigned long)(delta/1000));
					wxThread::Sleep((unsigned long)(delta/1000));
				}
			}
		} while (IsDelta(nextEvent));

		
		switch (Mode) {
		case DevicePlay:
		case DevicePause: 
			Stop();
		case DeviceStop:
			e = 0;
			break;
		case DeviceTimingError:
		case DeviceCompileError:
		default:
			e = (void *)Mode;
			break;
		}

		timer = NULL;
		referenceTime = 0;
		pauseTime = 0;

	        thistimer->ClearFile(); 
                        // this might delete us (smartptr).
		return e;
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
