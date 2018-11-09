/** \file     -*- C++ -*-
 ********************************************************************
 * File player class which solves common tasks of file related devices
 * such as MIDI file players.
 *
 * Copyright:   (c) 2012 Tobias Schlemmer
 * \author Tobias Schlemmer <keinstein@users.sourceforge.net>
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
#include <boost/chrono/chrono_io.hpp>

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

	inline void CommonFileOutputDevice::do_Close(bool mutUNUSED(sync))
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
#if 0
			DEBUGLOG(thread,
				 ("Thread %s locking at threadsignal = %x"),
				 Thread::get_current_string_id().c_str(),
				 threadsignal.get());
			ScopedLock<> locker(playerActive);
			DEBUGLOG(thread,
				 ("Thread %s locked at threadsignal = %x"),
				 Thread::get_current_string_id().c_str(),
				 threadsignal.get());
#endif
			thread_command |= RequestPause;


			/* creating threads might be expensive. So we
			   create it here, as Play() must be
			   considered to be a realtime function
			   synchronized with other devices */
			try {
				timer = new FileTimer(this);
				if (!timer) {
					Mode = DeviceTimingError;
					Close();
					return false;
				}
			} catch (const boost::thread_resource_error & e) {
				DEBUGLOG(thread,
					 "Thread %s could not aquire thread resources for timer",
					 Thread::get_current_string_id().c_str());
				delete timer;
				timer = NULL;
				Mode = DeviceTimingError;
				Close();
				return false;
			} catch (const std::exception & e) {
				DEBUGLOG(thread,
					 "Thread %s got an exception while creating timer: %s",
					 Thread::get_current_string_id().c_str(),
					 e.what());
				delete timer;
				timer = NULL;
				Mode = DeviceTimingError;
				Close();
				return false;
			} catch (...) {
				delete timer;
				timer = NULL;
				Mode = DeviceTimingError;
				Close();
				return false;
			}
			timer->Run();
			/* wait until the timer thread has locked the activeCondition.
			 * After signalling the player thread we won't continue before
			 * playerActive is unlocked which is the case when the player is idle.
			 */
			{
				ScopedLock<> lock(thread_state.get_mutex());
				int currentstate = thread_state;
				while (!(currentstate & RequestPause)) {
					DEBUGLOG(thread,
						 ("Thread %s waiting at threadsignal = %x"),
						 Thread::get_current_string_id().c_str(),
						 currentstate);

					currentstate = thread_state.wait_for_data_change(currentstate,
											 lock);
				}
				DEBUGLOG(thread,
					 ("Thread %s continue at threadsignal = %x"),
					 Thread::get_current_string_id().c_str(),
					 currentstate);
			}
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
		{
			ScopedLock<> lock(thread_state.get_mutex());
			int currentstate = thread_state;
			if (timer)
				while (!(currentstate & RequestPause)) {
					DEBUGLOG(thread,
						 ("Thread %s waiting at threadsignal = %x"),
						 Thread::get_current_string_id().c_str(),
						 currentstate);

					currentstate = thread_state.wait_for_data_change(currentstate,
											 lock);
				}

			DEBUGLOG(thread,
				 ("Thread %s continue at threadsignal = %x"),
				 Thread::get_current_string_id().c_str(),
				 currentstate);
		}

		DEBUGLOG (thread, "timer = %p" ,(void *)timer);
		if (timer) {
			// prepare exit when the thread is paused.
			thread_command |= RequestExit;
			DEBUGLOG(thread,
				 ("Thread %s broadcasting at threadsignal = %x"),
				 Thread::get_current_string_id().c_str(),
				 (int)thread_command);
			thread_command.notify_all();
#if 0
			// we don't detach threads anymore
			/* detached status must be checked before a
			   detached thead may be deleted. */
			bool must_join = !timer->IsDetached();
			// timer = NULL;
			// tmp -> ClearFile();
			//pauseCondition.Broadcast();
			// playerActive.Unlock();
			// tmp -> Delete();
			//timer -> ClearFile();
#endif
			timer -> Wait();
			delete timer;
			timer = NULL;
		}
		isOpen = false;
	}

	inline void CommonFileInputDevice::Stop()
	{
		bool lock_active = (timer && Thread::get_current_id() != timer->get_id());
		{
#if 0
			ScopedLock<> modelock(lockMode);
			DEBUGLOG (routing, "old mode = %d" ,Mode);
#endif
			if ( Mode == DevicePlay || Mode == DeviceTimingError ) {
				pauseTime = CurrentTime.Get();
				if ( CurrentTime.isRealtime() ) {
					// we use this function for some cleanup inside Stop()
					// which is called from inside the thread.
					// In this case we shouldn't pause ourselves
					thread_command |= RequestPause; // should be atomic
					thread_command.notify_all();
				}
			}

		}
		if (lock_active) {
			ScopedLock<> lock(thread_state.get_mutex());
			int currentstate = thread_state;
			while (!(currentstate & RequestPause)) {
				DEBUGLOG(thread,
					 ("Thread %s waiting at threadsignal = %x"),
					 Thread::get_current_string_id().c_str(),
					 currentstate);

				currentstate = thread_state.wait_for_data_change(currentstate,
										 lock);
			}
		}
		{
			ScopedLock<CommonFileInputDevice> lock(*this);
			current_keys.clear();
			thread_command |= ResetTime;
			referenceTime = CurrentTimer::time_point();
			pauseTime = CurrentTimer::time_point();
			if ( Mode != DeviceCompileError )
				Mode = DeviceStop;
		}
	}

	inline void CommonFileInputDevice::Play()
	{
		static bool starting = false; // should be atomic

		if (starting) return;
		starting = true;

		{
			ScopedLock<CommonFileInputDevice> modelock(*this);
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
				referenceTime = CurrentTimer::time_point();
				pauseTime = CurrentTimer::time_point();
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
			referenceTime = CurrentTimer::time_point(referenceTime) + ((CurrentTime.Get() - pauseTime));
			pauseTime = CurrentTimer::time_point();
		}

		// timer should be 0 in Realtime mode
		// we must unlock *this so that the player can
		// reach the synchronisation point
		mutASSERT((!timer && !CurrentTime.isRealtime())
			  || (CurrentTime.isRealtime() && timer));
		if (timer) {
			thread_command &= ~(int)RequestPause; // threadsignal should be atomic
			DEBUGLOG(thread,
				 ("Thread %s is changing thread command = %x"),
				 Thread::get_current_string_id().c_str(),
				 thread_command);
			thread_command.notify_all();
			ScopedLock<> lock(thread_state.get_mutex());
			while (thread_state & RequestPause ||
			       ((thread_command & ResetTime) &&
				!(thread_state & ResetTime))) {
				thread_state.wait(lock);
			}
			thread_command &= ~(int)ResetTime;
			thread_command.notify_all();
		}
		DEBUGLOG (timer, "timer = %p" ,(void*)timer);
		{
			ScopedLock<CommonFileInputDevice> modelock(*this);
			Mode = DevicePlay;
		}
		/* we should not nest modeLock and playerActive, here. Otherwise we might deadlock. */

		starting = false;
		//mutASSERT(timer);
	}

	inline void CommonFileInputDevice::Pause()
	{
		ScopedLock<CommonFileInputDevice> modelock(*this);
		switch (Mode) {
		case DeviceCompileError:
		case DeviceTimingError:
		case DeviceStop:
		case DeviceKilled:
			break;
		case DevicePlay:
			{
				pauseTime = CurrentTime.Get();
				if ( CurrentTime.isRealtime() ) {
					// we use this function for some cleanup inside Stop()
					// which is called from inside the thread.
					// In this case we shouldn't pause ourselves
					thread_command |= RequestPause;
				}
				thread_command.notify_all();
			}
			Mode = DevicePause;
			break;
		case DevicePause: {
			unlock();
			Play(); // A mechanical Pause button usually is released if pressed twice
			lock();
		}
			break;
		default:
			mutASSERT(!"Unknown value");
		}
	}



	/* we use microseconds as errors sum up */
	inline int
	CommonFileInputDevice::ThreadPlay(FileTimer * thistimer)
	{
		/// \todo clean-up race conditions
		mutASSERT(Thread::get_current_id() == timer->get_id());

		mutASSERT(timer != NULL);
		mutASSERT(Mode != DeviceCompileError );


		{
			ScopedLock<CommonFileInputDevice> modelock(*this);
			if (Mode == DeviceInitializing)
				Mode = DeviceStop;
		}
		DEBUGLOG(thread,
			 ("Thread %s locking at threadsignal = %x"),
			 Thread::get_current_string_id().c_str(),
			 thread_command);
		/* We use manual locking and unlocking, here */
		/* tell the main thread that we are initialized */
		int e = 0;
		{

			CurrentTimer::time_point nextEvent;
			CurrentTimer::time_point reference;
			microseconds playTime(0); // in μs
			microseconds eventDelta(0); // in μs
			try {
				while (true) {
					if (thread_command & RequestPause) {
						if (thread_command & RequestPanic ) {
							this->Panic(midi::DEFAULT_PANIC);
							thread_state |= RequestPanic;
							// TODO: Reset panic flag
						} else {
							SilenceKeys(false);
						}
						DEBUGLOG(thread,
							 ("Thread %s waiting at threadsignal = %x"),
							 Thread::get_current_string_id().c_str(),
							 thread_command);
						try
							{
								thread_state &= ~(int) ResetTime;
								thread_state |= RequestPause;
								thread_state.notify_all();
								ScopedLock<> lock(thread_command.get_mutex());
								while ((thread_command & RequestPause) &&
								       !(thread_command & RequestExit))
									thread_command.wait(lock);
								if (!(thread_command & RequestPause)) {
									thread_state &= ~(int)RequestPause;
									thread_state.notify_all();
								}
							}
						catch (const boost::thread_interrupted & e) {
							Stop();
						}
						DEBUGLOG(thread,
							 ("Thread %s continuing and locking at threadsignal = %x"),
							 Thread::get_current_string_id().c_str(),
							 thread_command);
						if (thread_command & ResetTime) {
							eventDelta = microseconds::zero(); // in μs
							playTime  = microseconds::zero(); // in μs
							doResetTime();
							ScopedLock<> lock(thread_state.get_mutex());
							thread_state |= ResetTime;
							thread_state.notify_all();
						}
						reference = referenceTime;
						nextEvent = reference + playTime;
						ResumeKeys();
					} else if (thistimer -> TestDestroy()) {
						{
							e = (Mode + (size_t)0x100);
							// unlocking
						}
						break;
					} else if (!IsDelta(eventDelta)) {
						Stop();
					} else if (!(thread_command & (ResetTime | RequestExit | RequestPause))) {
						try {
							CurrentTime.Sleep(nextEvent,thread_command);
						}
						catch (const boost::thread_interrupted & e) {
							Stop();
						}
					}
					// some shortcuts after the pause
					if (thread_command & RequestExit) {
						e = 0;
						break;
					}

					if (thread_command & RequestPause) {
						continue;
					}

					mutASSERT(IsDelta(eventDelta));
					// we must evaluate the time again as spurious
					// wakeups may occur and we wake up the thread
					// on certain status changes. Furthermore the
					// delay from the previous code also take some
					// time.
					if (nextEvent <= CurrentTime.Get()) {
						try {
							eventDelta = PrepareNextEvent();
						} catch (...) {
							exception_error();
						}
						mutASSERT(eventDelta >= microseconds::zero());
						DEBUGLOG(timer,
							 ("Preparing next event is at %ld (isdelta=%d)"),
							 eventDelta,
							 IsDelta(eventDelta));
						DEBUGLOG (timer, "NoDelta = %ld" , NO_DELTA());
						if (IsDelta(eventDelta)) {
							playTime += eventDelta;
							nextEvent += eventDelta;
						}
					}
				}
			}  catch (const boost::thread_interrupted & e) {}
		}
		DEBUGLOG (timer, "returning" );
		{
			ScopedLock<CommonFileInputDevice> modelock(*this);
			switch (Mode) {
			case DevicePlay:
			case DevicePause:
			case DeviceKilled:
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
			 ("Thread %s unlocking at threadsignal = %x"),
			 Thread::get_current_string_id().c_str(),
			 thread_command);
		// assure that Close() has done its worke before exiting
		threadCleanUp();
		return e;
	}


	inline CommonFileInputDevice::operator std::string() const {
		return InputDeviceClass::operator std::string() +
			boost::str(boost::format("\n  time zero at = %s\n  paused at  = %s")
				   % (referenceTime.load(std::memory_order_relaxed))
				   % (pauseTime.load(std::memory_order_relaxed)));
	}

}
///\}
