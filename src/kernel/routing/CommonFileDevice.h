/** \file  -*- C++ -*-
 ********************************************************************
 * File player class which solves common tasks of file related devices
 * such as MIDI file players.
 *
 * Copyright:   (c) 2012 Tobias Schlemmer
 * \author  Tobias Schlemmer <keinstein@users.sourceforge.net>
 * \license GPL
 *
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
/* we guard a little bit complicated to ensure the references are set right
 */

#if (!defined(MU32_ROUTING_MIDI_COMMONFILEDEVICE_H) && !defined(PRECOMPILE)) \
	|| (!defined(COMMONFILEDEVICE_PRECOMPILED))
#ifndef PRECOMPILE
#define MU32_ROUTING_MIDI_COMMONFILEDEVICE_H
#endif

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

#include "src/kernel/Defs.h"
#include "src/kernel/routing/Device.h"
#include "src/kernel/routing/thread.h"
#include "src/kernel/routing/timing.h"


#ifndef MU32_ROUTING_MIDI_COMMONFILEDEVICE_H_PRECOMPILED
#define MU32_ROUTING_MIDI_COMMONFILEDEVICE_H_PRECOMPILED

// system headers which do seldom change

#include <limits>
#include <cstdio>
#include <atomic>

namespace mutabor {
	// OutMidiFile ------------------------------------------------------

	class CommonFileDeviceFactory;
	class CommonFileOutputDevice : public OutputDeviceClass
	{
		friend class CommonFileDeviceFactory;
	protected:
		CommonFileOutputDevice(): OutputDeviceClass() {}

		CommonFileOutputDevice(const std::string name,
				       int id = -1)
			: OutputDeviceClass(name, id) { }
 	public:
		virtual ~CommonFileOutputDevice() {}

		using OutputDeviceClass::Save;
		/// Save current device settings in a tree storage
		/** \argument config (tree_storage) storage class, where the data will be saved.
		 */
		virtual void Save (tree_storage & config);


		using OutputDeviceClass::Load;
		/// Load current device settings from a tree storage
		/** \argument config (tree_storage) storage class, where the data will be loaded from.
		 */
		virtual void Load (tree_storage & config);

		virtual bool do_Open();
		virtual void do_Close(bool sync = false);

		virtual void SetName(const std::string & s)
		{
			if (s != Name) {
				bool reopen = IsOpen();
				if (reopen)
					Close();

				Name = s;

				if (reopen)
					Open();
			}
		}

		virtual std::string GetTypeName () const {
			mutASSERT(false);
			return _mutN("Generic output file");
		}

		virtual operator std::string() const;
	};




// CommonFileInputDevice -------------------------------------------------------


	class CommonFileInputDevice : public InputDeviceClass
	{
		friend class MidiFileFactory;
	public:
 		class FileTimer: public Thread
		{

			boost::intrusive_ptr<CommonFileInputDevice> file;
		public:
			FileTimer(CommonFileInputDevice * f) : Thread(),
							       file(f)
			{}

			virtual ~FileTimer() {}

			int Entry() {
				int e;
				try {
					e = file->ThreadPlay(this);
				} catch (...) {
					e =  file->exception_error();
				}
				return e;
			}


			void OnExit() {}

			void ClearFile() {
				file.reset();
			}

			bool HasFile(CommonFileInputDevice * f) {
				return file == f;
			}
		protected:
		};


		friend class FileTimer;

	public:
		virtual ~CommonFileInputDevice() {
			if (isOpen) Close();
			mutASSERT(timer == NULL);
#ifdef DEBUG
#if 0
			if (!waitMutex.TryLock()) {
				DEBUGLOG(thread,"Error: waitMutex is still busy");
			} else waitMutex.Unlock();
			if (!threadReady.TryLock()) {
				DEBUGLOG(thread, "Error: threadReady is still busy");
			} else threadReady.Unlock();
			if (!lockMode.TryLock()) {
				DEBUGLOG(thread, "Error: lockMode is still busy");
			} else lockMode.Unlock();
			if (!playerActive.TryLock()) {
				DEBUGLOG(thread, "Error: playerActive is still busy");
			} else playerActive.Unlock();
#endif
#endif
		};

		using InputDeviceClass::Save;
		/// Save current device settings in a tree storage
		/** \argument config (tree_storage) storage class, where the data will be saved.
		 */
		virtual void Save (tree_storage & config);

		using InputDeviceClass::Load;
		/// Load current device settings from a tree storage
		/** \argument config (tree_storage) storage class, where the data will be loaded from.
		 */
		virtual void Load (tree_storage & config);


		virtual bool Open();
		virtual void Close();
		virtual void Stop();
		virtual void Play();
		virtual void Pause();

		/**
		 * Reset the timing and music data after stopping the device.
		 *
		 */
		virtual void doResetTime() {}

		/**
		 * Do some cleanup if necessary after stopping the thread.
		 *
		 */
		virtual void threadCleanUp() {}

		virtual void SetName(const std::string & s) {
			if (s != Name) {
				bool reopen = IsOpen();
				if (reopen)
					Close();

				Name = s;

				if (reopen)
					Open();
			}
		}


		/**
		 * Issue an error message and stop the device.
		 *
		 *
		 * \return Error exit code.
		 */
		int exception_error(bool doStop=true);

		/**
		 * Play the file.
		 * This function is called from the
		 * thread object. It plays the file using sleep
		 * operations.
		 */
		int ThreadPlay(FileTimer * timer);


		int WaitForDeviceFinish(bool blocking = true) {
			mutUnused(blocking);
			mutASSERT(timer);
			if (timer) {
				mutASSERT(boost::this_thread::get_id() != timer->get_id());
				if (boost::this_thread::get_id() != timer->get_id()) {
#if 0
					DEBUGLOG(thread,
						 ("Thread %s locking at threadsignal = %x"),
						 Thread::get_current_string_id().c_str(),
						 threadsignal.get());
					ScopedLock<> lock(playerActive);
					DEBUGLOG(thread,
						 ("Thread %s locked at threadsignal = %x"),
						 Thread::get_current_string_id().c_str(),
						 threadsignal.get());
#endif
					ScopedLock<> lock(thread_state.get_mutex());
					int currentstate = thread_state;
					while (!(currentstate & RequestPause))
						currentstate = thread_state.wait_for_data_change(currentstate,
												 lock);

					//if (timer->IsDetached()) {
						switch (Mode) {
						case DevicePlay:
						case DevicePause:
						case DeviceStop:
							return 0;
						case DeviceTimingError:
						case DeviceCompileError:
						default:
							return Mode;

						}
						//}
				} else return -1;
			}
			return 0;
		}

		virtual std::string GetTypeName () const {
			return _mutN("Generic input file");
		}

		virtual operator std::string() const;

	protected:
		FileTimer * timer;             //< timer thread for the file player
		/// Signals to communicate with the player thread
		enum ThreadCommunication: int {
			Nothing       = 0,     //< proceed, no change
			RequestExit   = 1,     //< exit the thread as soon as possible
			RequestPause  = 2,     //< stop the thread execution as soon as possible
			ResetTime     = 4,      /**< restart counting
						the time of the
						thread. This should
						be used only to sigal
						a start after the
						playback has been
						stopped */
			RequestPanic = 8       //< request Panic() before stopping the device
		};
		/* volatile is handled inside the class */
		ThreadSignal<int> thread_command, thread_state; //< signal
		//Mutex<> waitMutex, threadReady, lockMode, playerActive;
		//ThreadCondition<> waitCondition, pauseCondition;
		/**
		 * Fixed offset for the relative time the file returns.
		 */
		std::atomic<CurrentTimer::time_point> referenceTime; // ms
		std::atomic<CurrentTimer::time_point> pauseTime;     // ms
		timing_params timing;

		CommonFileInputDevice(): InputDeviceClass(),
					 timer (NULL),
					 thread_command (Nothing),
					 thread_state (Nothing),
					 /*					 waitMutex(),
					 threadReady(),
					 lockMode(),
					 playerActive(),
					 waitCondition(waitMutex),
					 pauseCondition(playerActive),
					 */
					 referenceTime(CurrentTimer::time_point()),
					 pauseTime(CurrentTimer::time_point()) { }

		CommonFileInputDevice(std::string name,
				      MutaborModeType mode,
				      int id): InputDeviceClass(name,
								mode,
								id),
					       timer(NULL),
					       thread_command (Nothing),
					       thread_state (Nothing),
					       /*
					       waitMutex(),
					       threadReady(),
					       lockMode(),
					       playerActive(),
					       waitCondition(waitMutex),
					       pauseCondition(playerActive),
					       */
					       referenceTime(CurrentTimer::time_point()),
					       pauseTime(CurrentTimer::time_point()) {}

	};


#if 0
	/* For completeness we show how a factory would look like.
	   This is not used as (Input|Output)DeviceClass are abstract
	   classes.
	*/
	class CommonFileDeviceFactory:public DeviceFactory {
	public:
		CommonFileDeviceFactory(size_t id = 0):
			DeviceFactory(id) {}
		virtual ~CommonFileDeviceFactory();

	protected:
		virtual size_t GetType() const
			{
				return DTMidiFile;
			}


		//		virtual mutabor::OutputDeviceClass * DoCreateOutput() const = 0;


		virtual mutabor::InputDeviceClass * DoCreateInput() const = 0;
		virtual mutabor::OutputDeviceClass * DoCreateOutput(int devId,
							     const std::string name,
							     int id = -1) const = 0;

		virtual mutabor::InputDeviceClass * DoCreateInput(int devId,
							   const std::string name,
							   int id = -1) const = 0;

		virtual mutabor::OutputDeviceClass * DoCreateOutput(int devId,
							     const std::string name,
							     mutabor::MutaborModeType mode,
							     int id = -1) const = 0;

		virtual mutabor::InputDeviceClass * DoCreateInput(int devId,
							   const std::string name,
							   mutabor::MutaborModeType mode,
							   int id = -1) const = 0;
	};

#endif
// Function ---------------------------------------------------------

}

#endif  /* precompiled */
#endif


///\}
