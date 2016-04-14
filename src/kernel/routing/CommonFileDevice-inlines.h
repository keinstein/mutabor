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

	inline void CommonFileOutputDevice::do_Close(bool sync)
	{
		mutASSERT(isOpen);
		isOpen = false;
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
			ScopedLock locker(playerActive);
			DEBUGLOG(thread,
				 ("Thread %p locked at threadsignal = %x"),
				 Thread::This(),
				 threadsignal.get());

			/* creating threads might be expensive. So we
			   create it here, as Play() must be
			   considered to be a realtime function
			   synchronized with other devices */
			timer = new FileTimer(this);
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
			threadsignal = RequestPause;
			timer->Run();
			DEBUGLOG(thread,
				 ("Thread %p waiting at threadsignal = %x"),
				 Thread::This(),
				 threadsignal.get());
			/* wait until the timer thread has locked the activeCondition.
			 * After signalling the player thread we won't continue before
			 * playerActive is unlocked which is the case when the player is idle.
			 */
			pauseCondition.Wait();
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
#ifdef DEBUG
		if (mutabor::CurrentTime.isRealtime()) {
			mutASSERT(isOpen);
		}
#endif
		Stop();
		playerActive.Lock();

		DEBUGLOG (thread, "timer = %p" ,(void *)timer);
		if (timer) {
			DEBUGLOG(thread,
				 ("Thread %p locking at threadsignal = %x"),
				 Thread::This(),
				 threadsignal.get());
			// prepare exit when the thread is paused.
			threadsignal |= RequestExit;
			DEBUGLOG(thread,
				 ("Thread %p broadcasting at threadsignal = %x"),
				 Thread::This(),
				 threadsignal.get());
			/* detached status must be checked before a
			   detached thead may be deleted. */
			bool must_join = !timer->IsDetached();
			// timer = NULL;
			// tmp -> ClearFile();
			pauseCondition.Broadcast();
			playerActive.Unlock();
			// tmp -> Delete();
			if (must_join) {
				timer->ClearFile();
#if wxCHECK_VERSION(2,9,2)
				timer -> Wait(wxTHREAD_WAIT_BLOCK);
#else
				timer -> Wait();
#endif
			}
			timer = NULL;
		} else playerActive.Unlock();

		isOpen = false;
	}

	inline void CommonFileInputDevice::Stop()
	{
		bool lock_active = (Thread::This() != timer);
		{
			ScopedLock modelock(lockMode);
			DEBUGLOG (routing, "old mode = %d" ,Mode);
			if ( Mode == DevicePlay || Mode == DeviceTimingError ) {
				pauseTime = CurrentTime.Get();
				if ( CurrentTime.isRealtime() ) {
					// we use this function for some cleanup inside Stop()
					// which is called from inside the thread.
					// In this case we shouldn't pause ourselves
					threadsignal |= RequestPause; // should be atomic
				}
			}

		}
		{
			if (lock_active) {
				{
					// wake the sleeping thread up.
					ScopedLock lock(waitMutex);
					waitCondition.Broadcast();
				}
				playerActive.Lock(); // Wait until Player stops
			}
			{
				ScopedLock lock(write_lock);
				current_keys.clear();
			}
			{
				ScopedLock lock(lockMode);
				threadsignal |= ResetTime;
				referenceTime = 0;
				pauseTime = 0;
				if ( Mode != DeviceCompileError )
					Mode = DeviceStop;
			}
			if (lock_active)
				playerActive.Unlock(); // Player can start again, now
		}
	}

	inline void CommonFileInputDevice::Play()
	{
		static bool starting = false; // should be atomic

		if (starting) return;
		starting = true;

		{
			ScopedLock modelock(lockMode);
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
				break;
			case DevicePlay:
				starting = false;
				return;

			}

			DEBUGLOG(timer,
				 ("Paused. Realtime = %d."),
				 (int)CurrentTime.isRealtime());
			// threadsignal |= ResetTime;
			referenceTime += CurrentTime.Get() - pauseTime;
			pauseTime = 0;

			// timer should be 0 in Realtime mode
			mutASSERT(!timer || CurrentTime.isRealtime());
			if (timer) {
				threadsignal &= ~(int)RequestPause; // threadsignal should be atomic
				DEBUGLOG(thread,
					 ("Thread %p locking at threadsignal = %x"),
					 Thread::This(),
					 threadsignal.get());
				DEBUGLOG(thread,
					 ("Thread %p broadcasting at threadsignal = %x"),
					 Thread::This(),
					 threadsignal.get());
			}
			DEBUGLOG (timer, "timer = %p" ,(void*)timer);
			Mode = DevicePlay;
		}
		/* we should not nest modeLock and playerActive, here. Otherwise we might deadlock. */
		{
			ScopedLock pauselock(playerActive);
			pauseCondition.Broadcast();
		}

		starting = false;
	}

	inline void CommonFileInputDevice::Pause()
	{
		ScopedLock modelock(lockMode);
		switch (Mode) {
		case DeviceCompileError:
		case DeviceTimingError:
		case DeviceStop:
			break;
		case DevicePlay:
			{
				ScopedLock waitlock(waitMutex);
				pauseTime = CurrentTime.Get();
				if ( CurrentTime.isRealtime() ) {
					// we use this function for some cleanup inside Stop()
					// which is called from inside the thread.
					// In this case we shouldn't pause ourselves
					threadsignal |= RequestPause;
				}
				waitCondition.Broadcast();
			}
			Mode = DevicePause;
			break;
		case DevicePause:
			lockMode.Unlock();
			Play(); // A mechanical Pause button usually is released if pressed twice
			lockMode.Lock(); // avoid problems with modelock
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
		playerActive.Lock();
		DEBUGLOG(thread,
			 ("Thread %p broadcasting at threadsignal = %x"),
			 Thread::This(),
			 threadsignal.get());
		pauseCondition.Broadcast();
		waitMutex.Lock();
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
				waitMutex.Unlock();
				while ((threadsignal & RequestPause) &&
				       !(threadsignal & RequestExit))
					pauseCondition.Wait();
				waitMutex.Lock();

				DEBUGLOG(thread,
					 ("Thread %p continuing and locking at threadsignal = %x"),
					 Thread::This(),
					 threadsignal.get());
				if (threadsignal & ResetTime) {
					nextEvent = (0); // in μs
					playTime  = (0); // in μs
					doResetTime();
					threadsignal &= ~(int)ResetTime;
				}
				reference = referenceTime;
				ResumeKeys();
			} else if (thistimer -> TestDestroy()) {
				{
					ScopedLock modelock(lockMode);
					e = (void *) (Mode + (size_t)0x100);
					// unlocking
				}
				break;
			} else if (!IsDelta(nextEvent)) {
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
				delta = std::max(reference + playTime - CurrentTime.Get(),(mutint64)0);
				DEBUGLOG (timer, "Delta %ld μs." ,delta);

				CurrentTime.Sleep(delta,waitCondition);
			}
			// some shortcuts after the pause
			if (threadsignal & RequestExit) {
				ScopedLock modelock(lockMode);
				e = (void *)Mode;
				break;
			}

			if (threadsignal & RequestPause) {
				continue;
			}

			mutASSERT(IsDelta(nextEvent));
			// we must evaluate the time again as spurious
			// wakeups may occur and we wake up the thread
			// on certain status changes. Furthermore the
			// delay from the previous code also take some
			// time.
			if (reference + playTime - CurrentTime.Get() <= 0) {
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
		}
		DEBUGLOG (timer, "returning" );
		{
			ScopedLock modelock(lockMode);
			switch (Mode) {
			case DevicePlay:
			case DevicePause:
				Stop();
			case DeviceStop:
				break;
			case DeviceTimingError:
			case DeviceCompileError:
			default:
				break;
			}
		}
		DEBUGLOG(thread,
			 ("Thread %p unlocking at threadsignal = %x"),
			 Thread::This(),
			 threadsignal.get());
		// assure that Close() has done its worke before exiting
		threadCleanUp();
		waitMutex.Unlock();
		playerActive.Unlock();
		return e;
	}


	inline CommonFileInputDevice::operator std::string() const {
		return InputDeviceClass::operator std::string() +
			boost::str(boost::format("\n  time zero at = %ld ms\n  paused at  = %ld msx")
				   % (mutint64)(referenceTime)
				   % (mutint64)(pauseTime));
	}

}
///\}
