/** \file     -*- C++ -*-
 ********************************************************************
 * File player class which solves common tasks of file related devices
 * such as MIDI file players.
 *
 * Copyright:   (c) 2012 Tobias Schlemmer
 * \author Tobias Schlemmer <keinstein@users.berlios.de>
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
//#include "src/kernel/GrafKern.h"
#include "src/kernel/Runtime.h"

#if 0
#include "wx/wfstream.h"
#include "wx/msgdlg.h"
#include "wx/timer.h"
#endif

#if _XOPEN_SOURCE >= 600 || _POSIX_C_SOURCE >= 200112L
#include <time.h>
#include <errno.h>
#endif


namespace mutabor {


// OutputMidiFile ------------------------------------------------------

/// Save current file name in a tree storage
/** \argument config (tree_storage) storage class, where the data will be saved.
 */
	inline void CommonFileOutputDevice::Save (tree_storage & config) 
	{
#ifdef DEBUG
		std::string oldpath = config.GetPath();
#endif
		config.Write(("File Name"),Name);
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
		std::string oldpath = config.GetPath();
#endif
		Name = config.Read(("File Name"),"");
#ifdef DEBUG
		mutASSERT(oldpath == config.GetPath());
#endif
	}

	inline bool CommonFileOutputDevice::do_Open()
	{
		mutASSERT(!isOpen);
		isOpen = true;
		return isOpen;
	}

	inline void CommonFileOutputDevice::do_Close()
	{
		mutASSERT(isOpen);
		isOpen = false;
	}

	inline CommonFileOutputDevice::operator std::string() const {
		std::string s = OutputDeviceClass::operator std::string() +
			boost::str(boost::format("\n  Name = %s\n  session_id = %lu\n  routefile_id = %d")
				   % Name.c_str() % (unsigned long)session_id() % routefile_id);
		return s;
	}



	
// CommonFileInputDevice -------------------------------------------------------


/// Save current device settings in a tree storage
/** \argument config (tree_storage) storage class, where the data will be saved.
 */

	inline void CommonFileInputDevice::Save (tree_storage & config)
	{
#ifdef DEBUG
		std::string oldpath = config.GetPath();
#endif
		config.Write(("File Name"),Name);
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
		std::string oldpath = config.GetPath();
#endif
		Name = config.Read(("File Name"),"");
#ifdef DEBUG
		mutASSERT(oldpath == config.GetPath());
#endif
	}
	



	inline bool CommonFileInputDevice::Open()
	{
		
		mutASSERT(!isOpen);
		DEBUGLOG (other, "start" );

		Mode = DeviceStop;
		// init
		Stop();
		DEBUGLOG (other, 
			  ("finished. Mode = %d, this = %p"),
			  Mode,
			  (void*)this);

		
		if ( mutabor::CurrentTime.isRealtime() ) {
			mutASSERT(timer == NULL);
			DEBUGLOG(thread,
				 ("Thread %p locking at threadsignal = %x"),
				 Thread::This(),
				 threadsignal.get());
			ScopedLock locker(waitMutex);
			DEBUGLOG(thread,
				 ("Thread %p locked at threadsignal = %x"),
				 Thread::This(),
				 threadsignal.get());
			
			/* creating threads might be expensive. So we
			   create it here, as Play() must be
			   considered to be a realtime function
			   synchronized with other devices */
			timer = new FileTimer(this,threadkind);
			if (!timer) {
				Mode = DeviceTimingError;
				Close();
				return false;
			}
			wxThreadError result = timer -> Create(1024*100); // Stack Size
			if (result != wxTHREAD_NO_ERROR) {
				delete timer;
				timer = NULL;
				Mode = DeviceTimingError;
				Close();
				return false;
			}
			timer->Run();
			threadsignal = RequestPause;
			/* wait until the timer thread has been initialized */
			DEBUGLOG(thread,
				 ("Thread %p waiting at threadsignal = %x"),
				 Thread::This(),
				 threadsignal.get());
			waitCondition.Wait();
			DEBUGLOG(thread,
				 ("Thread %p continue at threadsignal = %x"),
				 Thread::This(),
				 threadsignal.get());
		}

		DEBUGLOG (timer, "timer = %p" ,(void*)timer);
		isOpen = true;
		return true;
	}

	inline void CommonFileInputDevice::Close()
	{
		exitLock.Lock();
#ifdef DEBUG
		if (mutabor::CurrentTime.isRealtime()) {
			mutASSERT(isOpen);
		}
#endif
		Stop();
		
		DEBUGLOG (thread, "timer = %p" ,(void *)timer);
		if (timer) {
			DEBUGLOG(thread,
				 ("Thread %p locking at threadsignal = %x"),
				 Thread::This(),
				 threadsignal.get());
			waitMutex.Lock();
			// prepare exit when the thread is paused.
			threadsignal |= RequestExit;
			DEBUGLOG(thread,
				 ("Thread %p broadcasting at threadsignal = %x"),
				 Thread::This(),
				 threadsignal.get());
			FileTimer *tmp = timer;
			/* detached status must be checked before a
			   detached thead may be deleted. */
			bool must_join = !timer->IsDetached(); 
			timer = NULL;
			tmp -> ClearFile();
			waitCondition.Broadcast();
			waitMutex.Unlock();
			exitLock.Unlock();
			// tmp -> Delete();
			if (must_join) {
#if wxCHECK_VERSION(2,9,2)
				tmp -> Wait(wxTHREAD_WAIT_BLOCK);
#else
				tmp -> Wait();
#endif
			        delete tmp;
			}
		} else exitLock.Unlock();
		
		isOpen = false;
	}

	inline void CommonFileInputDevice::Stop()
	{
		ScopedLock modelock(lockMode);
		DEBUGLOG (routing, "old mode = %d" ,Mode);
		if ( Mode == DevicePlay || Mode == DeviceTimingError ) {
			threadsignal |= RequestPanic;
			Pause();
		}
		
		threadsignal |= ResetTime;
		referenceTime = 0;
		pauseTime = 0;

		if ( Mode != DeviceCompileError )
			Mode = DeviceStop;
	}

	inline void CommonFileInputDevice::Play()
	{
		static bool starting = false;
		ScopedLock modelock(lockMode);

		if (starting) return;
		starting = true;
		
		switch (Mode) {
		case DeviceCompileError:
		case DeviceTimingError:
		case DeviceUnregistered:
		case DeviceKilled:
			DEBUGLOG(timer,
				 ("Returnung due to device error."));
			starting = false; 
			return;
		case DeviceInitializing: 
			// this will eventually change to DeviceStop
			// DevicePause case will wait until the device is initialized.
		case DeviceStop:
			referenceTime = 0;
			pauseTime = 0;
		case DevicePause:
			DEBUGLOG(timer,
				 ("Paused. Realtime = %d."),
				 (int)CurrentTime.isRealtime());
			// threadsignal |= ResetTime;
			referenceTime += CurrentTime.Get() - pauseTime;
			pauseTime = 0;

			// timer should be 0 in Realtime mode
			mutASSERT(!timer || CurrentTime.isRealtime());
			if (timer) {
				threadsignal &= ~(int)RequestPause;
				DEBUGLOG(thread,
					 ("Thread %p locking at threadsignal = %x"),
					 Thread::This(),
					 threadsignal.get());
				waitMutex.Lock();
				DEBUGLOG(thread,
					 ("Thread %p broadcasting at threadsignal = %x"),
					 Thread::This(),
					 threadsignal.get());
				waitCondition.Broadcast();
				waitMutex.Unlock();
			}
			break;
		case DevicePlay:
			starting = false; 
			return;
			
		}
		DEBUGLOG (timer, "timer = %p" ,(void*)timer);
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
				threadsignal |= RequestPause;
			}
			pauseTime = CurrentTime.Get();
			Mode = DevicePause;
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



		if (Mode == DeviceInitializing) 
			Mode = DeviceStop;
		/* tell the main thread that we are initialized */
		DEBUGLOG(thread,
			 ("Thread %p locking at threadsignal = %x"),
			 Thread::This(),
			 threadsignal.get());
		waitMutex.Lock(); 
		DEBUGLOG(thread,
			 ("Thread %p broadcasting at threadsignal = %x"),
			 Thread::This(),
			 threadsignal.get());
		waitCondition.Broadcast();
		DEBUGLOG(thread,
			 ("Thread %p locking again at threadsignal = %x"),
			 Thread::This(),
			 threadsignal.get());
		/* leave Mutex locked */
		/*
		waitMutex.Lock();
		DEBUGLOG(thread,
			 ("Thread %p locked at threadsignal = %x"),
			 Thread::This(),
			 threadsignal.get());
		*/

		mutint64 nextEvent = (0); // in μs
		mutint64 playTime  = (0); // in μs
		mutint64 reference = (0); // in μs
		mutint64 delta = GetNO_DELTA(); // in ms
		wxThread::ExitCode e = 0;
		while (true) {
			if (threadsignal & RequestPause) {
				if (threadsignal & RequestPanic ) {
					this->Panic(midi::DEFAULT_PANIC);
					threadsignal &= ~(int)RequestPanic;
				} else {
					SilenceKeys(false);
				}
				DEBUGLOG(thread,
					 ("Thread %p waiting at threadsignal = %x"),
					 Thread::This(),
					 threadsignal.get());
				waitCondition.Wait();
				DEBUGLOG(thread,
					 ("Thread %p continuing and locking at threadsignal = %x"),
					 Thread::This(),
					 threadsignal.get());
#if 0
				waitMutex.Lock();
				DEBUGLOG(thread,
					 ("Thread %p Locked at threadsignal = %x"),
					 Thread::This(),
					 threadsignal.get());
#endif
				if (threadsignal & RequestExit)
					break;
				if (threadsignal & ResetTime) {
					nextEvent = (0); // in μs
					playTime  = (0); // in μs
					doResetTime();
					threadsignal &= ~(int)ResetTime;
				} 
				reference = referenceTime;
				ResumeKeys();
			} else if (thistimer -> TestDestroy()) {
				return (void *) (Mode + (size_t)0x100);
			}
			mutASSERT(IsDelta(nextEvent));
			if (!delta && IsDelta(nextEvent)) {
				nextEvent = PrepareNextEvent();
				mutASSERT(nextEvent >= 0);
				DEBUGLOG(timer,
					 ("Preparing next event is at %ld (isdelta=%d)"), 
					 nextEvent,
					 IsDelta(nextEvent));
				DEBUGLOG (timer, "NoDelta = %ld" , GetNO_DELTA());
				if (IsDelta(nextEvent)) {
					reference = referenceTime;
					playTime += nextEvent;
				}
			}
			if (!IsDelta(nextEvent)) {
				{ 
					ScopedLock modelock(lockMode);
					switch (Mode) {
					case DevicePlay:
					case DevicePause: 
					case DeviceStop:
						break;
					case DeviceTimingError:
					case DeviceCompileError:
					default:
						e = (void *)Mode;
						break;
					}
					// unlocking
				}
				Stop();
			} else if (!(threadsignal & (ResetTime | RequestExit | RequestPause))) {
				DEBUGLOG (timer, "time: %ld μs" ,CurrentTime.Get());
				delta = reference + playTime - CurrentTime.Get();
				DEBUGLOG (timer, "Delta %ld μs." ,delta);

				/* we wake up in regular time intervals in order
				   to assure that external commands (stop/close)
				   can be handled in reasonable time) 

				   The delta slices should be smaller than the 
				   resolution that is forced in the test suite.
				   Currently (as this comment is created) the
				   maximum allowed difference is 10 ms.
				*/
				if (delta > 2000) {
					CurrentTime.Sleep(2000);
				} else {
					if (delta > 0) 
						CurrentTime.Sleep(delta);
					delta = 0;
				}
			}
		}
		DEBUGLOG (timer, "returning" );
		switch (Mode) {
		case DevicePlay:
		case DevicePause: 
			Stop();
		case DeviceStop:
			break;
		case DeviceTimingError:
		case DeviceCompileError:
		default:
			e = (void *)Mode;
			break;
		}
		DEBUGLOG(thread,
			 ("Thread %p unlocking at threadsignal = %x"),
			 Thread::This(),
			 threadsignal.get());
		// assure that Close() has done its worke before exiting
		exitLock.Lock();
		threadCleanUp();
		waitMutex.Unlock();
		exitLock.Unlock();
		return e;
	}

	
	inline CommonFileInputDevice::operator std::string() const {
		return InputDeviceClass::operator std::string() +
			boost::str(boost::format("\n  time zero at = %ld ms\n  paused at  = %ld msx")
				   % referenceTime % pauseTime);
	}

}
///\}
