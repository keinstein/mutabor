/** \file  -*- C++ -*-
 ********************************************************************
 * File player class which solves common tasks of file related devices such as MIDI file players.
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/src/kernel/routing/midi/DevMidF.h,v 1.8 2011/11/02 14:31:58 keinstein Exp $
 * Copyright:   (c) 2012 Tobias Schlemmer
 * \author  Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 
 * $Date: 2011/11/02 14:31:58 $
 * \version $Revision: 1.8 $
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
 * $Log:$
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


#ifndef MU32_ROUTING_MIDI_COMMONFILEDEVICE_H_PRECOMPILED
#define MU32_ROUTING_MIDI_COMMONFILEDEVICE_H_PRECOMPILED

// system headers which do seldom change

#include "wx/timer.h"

namespace mutabor {

	// OutMidiFile ------------------------------------------------------

	class CommonFileDeviceFactory;
	class CommonFileOutputDevice : public OutputDeviceClass
	{
		friend class CommonFileDeviceFactory;
	protected:
		CommonFileOutputDevice(): OutputDeviceClass() {}

		CommonFileOutputDevice(int devId, 
			       const mutStringRef name, 
			       int id = -1)
			: OutputDeviceClass(devId, name, id) { }
 	public:
		virtual ~CommonFileOutputDevice() {};
	
		/// Save current device settings in a tree storage
		/** \argument config (tree_storage) storage class, where the data will be saved.
		 */
		virtual void Save (tree_storage & config);
	
	
	
		/// Load current device settings from a tree storage
		/** \argument config (tree_storage) storage class, where the data will be loaded from.
		 */
		virtual void Load (tree_storage & config);
	
		virtual bool Open();
		virtual void Close();

		virtual void SetName(const wxString & s) 
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
		

		virtual mutString GetTypeName () const {
			mutASSERT(false);
			return N_("Generic output file");
		}

#ifdef WX
		virtual wxString TowxString() const;
#endif
	protected:
		static unsigned long NRT_Speed;
	};




// InMidiFile -------------------------------------------------------


	class CommonFileInputDevice : public InputDeviceClass
	{
		friend class MidiFileFactory;
	protected:
#if __WXMSW__
		// on Windows wxTimer resolution is too bad to play MIDI files so we must emulate it
		class ostimer
		{
		protected:
			static void CALLBACK Callback(PVOID lpParam, BOOLEAN TimerOrWaitFired);
			static HANDLE TimerQueue;
			HANDLE Timer;

		public:
			ostimer() {
			}
			
			virtual void Notify() = 0;
			
			bool Start(int msec, bool OneShot = false) {
				if (!TimerQueue)
					TimerQueue = CreateTimerQueue();
				if (!TimerQueue) 
					return false;
				if (!CreateTimerQueueTimer( &Timer, 
							    TimerQueue, 
							    (WAITORTIMERCALLBACK)Callback, 
							    this , 
							    msec, 
							    OneShot?0:msec , 
							    WT_EXECUTEDEFAULT))
					return false;
				return true;
			}

			void Stop() {
				DeleteTimerQueueTimer(TimerQueue,Timer,NULL);
			}
		};
#else
		typedef wxTimer ostimer;
#endif
		class MidiTimer : public ostimer
		{
			CommonFileInputDevice * file;

		public:
			MidiTimer(CommonFileInputDevice * f) : ostimer(),file(f)
				{}

			void Notify()
				{
					file->TimerCallback();
				}
		};

		MidiTimer timer;

		CommonFileInputDevice(): InputDeviceClass(),
				 timer (this) { }

		CommonFileInputDevice(int devId,
			      wxString name, 
			      MutaborModeType mode,
			      int id): InputDeviceClass(devId, 
							name, 
							mode, 
							id),
					  timer(this) {}

	public:
		virtual ~CommonFileInputDevice()
			{};
	
		/// Save current device settings in a tree storage
		/** \argument config (tree_storage) storage class, where the data will be saved.
		 */
		virtual void Save (tree_storage & config);
	
		/// Load current device settings from a tree storage
		/** \argument config (tree_storage) storage class, where the data will be loaded from.
		 */
		virtual void Load (tree_storage & config);

	
		virtual bool Open();
		virtual void Close();
		virtual void Stop();
		virtual void Play();
		virtual void Pause();

		virtual void SetName(const wxString & s) 
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
		void TimerCallback();

		virtual mutString GetTypeName () const {
			return N_("Generic input file");
		}
	
#ifdef WX
		virtual wxString TowxString() const;
#endif
	protected:
		long minDelta;
		long actDelta;
		BOOL Busy;
	};


	class MidiFileFactory:public DeviceFactory { 
	public:
		MidiFileFactory(size_t id = 0):
			DeviceFactory(id) {}
		virtual ~MidiFileFactory();

	protected:
		virtual size_t GetType() const
			{
				return DTMidiFile;
			}


		virtual mutabor::OutputDeviceClass * DoCreateOutput() const = 0;
		
		virtual mutabor::InputDeviceClass * DoCreateInput() const = 0;
		virtual mutabor::OutputDeviceClass * DoCreateOutput(int devId,
							     const mutStringRef name, 
							     int id = -1) const = 0;
		
		virtual mutabor::InputDeviceClass * DoCreateInput(int devId,
							   const mutStringRef name, 
							   int id = -1) const = 0;

		virtual mutabor::OutputDeviceClass * DoCreateOutput(int devId,
							     const mutStringRef name, 
							     mutabor::MutaborModeType mode, 
							     int id = -1) const = 0;
		
		virtual mutabor::InputDeviceClass * DoCreateInput(int devId,
							   const mutStringRef name, 
							   mutabor::MutaborModeType mode, 
							   int id = -1) const = 0;
	};


// Function ---------------------------------------------------------

}

#endif  /* precompiled */
#endif

/*
  timeSetEvent

  The timeSetEvent function starts a specified timer event. The multimedia timer runs in its own thread. After the event is activated, it calls the specified callback function or sets or pulses the specified event object.

  This function is obsolete. New applications should use CreateTimerQueueTimer to create a timer-queue timer.

  MMRESULT timeSetEvent(
  UINT           uDelay,
  UINT           uResolution,
  LPTIMECALLBACK lpTimeProc,
  DWORD_PTR      dwUser,
  UINT           fuEvent
  );

Parameters

uDelay

Event delay, in milliseconds. If this value is not in the range of the minimum and maximum event delays supported by the timer, the function returns an error.

uResolution

Resolution of the timer event, in milliseconds. The resolution increases with smaller values; a resolution of 0 indicates periodic events should occur with the greatest possible accuracy. To reduce system overhead, however, you should use the maximum value appropriate for your application.

lpTimeProc

Pointer to a callback function that is called once upon expiration of a single event or periodically upon expiration of periodic events. If fuEvent specifies the TIME_CALLBACK_EVENT_SET or TIME_CALLBACK_EVENT_PULSE flag, then the lpTimeProc parameter is interpreted as a handle to an event object. The event will be set or pulsed upon completion of a single event or periodically upon completion of periodic events. For any other value of fuEvent, the lpTimeProc parameter is interpreted as a function pointer with the following signature: void (CALLBACK)(UINT uTimerID, UINT uMsg, DWORD_PTR dwUser, DWORD_PTR dw1, DWORD_PTR dw2);

dwUser

User-supplied callback data.

fuEvent

Timer event type. This parameter may include one of the following values.
Value 	Meaning
TIME_ONESHOT 	Event occurs once, after uDelay milliseconds.
TIME_PERIODIC 	Event occurs every uDelay milliseconds.

The fuEvent parameter may also include one of the following values.
Value 	Meaning
TIME_CALLBACK_FUNCTION 	When the timer expires, Windows calls the function pointed to by the lpTimeProc parameter. This is the default.
TIME_CALLBACK_EVENT_SET 	When the timer expires, Windows calls the SetEvent function to set the event pointed to by the lpTimeProc parameter. The dwUser parameter is ignored.
TIME_CALLBACK_EVENT_PULSE 	When the timer expires, Windows calls the PulseEvent function to pulse the event pointed to by the lpTimeProc parameter. The dwUser parameter is ignored.
TIME_KILL_SYNCHRONOUS 	Passing this flag prevents an event from occurring after the timeKillEvent() function is called.

Return Values

Returns an identifier for the timer event if successful or an error otherwise. This function returns NULL if it fails and the timer event was not created. (This identifier is also passed to the callback function.)

Remarks

Each call to timeSetEvent for periodic timer events requires a corresponding call to the timeKillEvent function.

Creating an event with the TIME_KILL_SYNCHRONOUS and the TIME_CALLBACK_FUNCTION flag prevents the event from occurring after the timeKillEvent function is called.

Requirements

  Windows XP: Included in Windows XP only.
  Header: Declared in Mmsystem.h; include Windows.h.
  Library: Use Winmm.lib.


 */


///\}
