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

#include <limits>
#include "wx/thread.h"

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
	};




// CommonFileInputDevice -------------------------------------------------------


	class CommonFileInputDevice : public InputDeviceClass
	{
		friend class MidiFileFactory;
	public:
 		class FileTimer: public wxThread
		{
	      
			boost::intrusive_ptr<CommonFileInputDevice> file;
		public:
			FileTimer(CommonFileInputDevice * f,
				  wxThreadKind kind = wxTHREAD_DETACHED) : wxThread(kind),
									   file(f)
				{}

			virtual ~FileTimer() {
				if (file) {
					if (file->timer == this)
						file -> timer = NULL;
				}
			}

			ExitCode Entry() {
				ExitCode e = file->ThreadPlay(this);
				return e;
			}

			void OnExit() {
				if (file) {
					if (file->timer == this)
						file -> timer = NULL;
				}
				file = NULL;
			}
			
			void ClearFile() {
				file = NULL;
			}

			bool HasFile(CommonFileInputDevice * f) {
				return file == f;
			}
		};
		friend class FileTimer;

	protected:
		
		FileTimer * timer;

		CommonFileInputDevice(): InputDeviceClass(),
					 timer (NULL),
					 referenceTime(0),
					 pauseTime(0) { }

		CommonFileInputDevice(int devId,
				      wxString name, 
				      MutaborModeType mode,
				      int id): InputDeviceClass(devId, 
								name, 
								mode, 
								id),
					       timer(NULL),
					       referenceTime(0),
					       pauseTime(0) {}

	public:
		virtual ~CommonFileInputDevice() {
			mutASSERT(timer == NULL);
		};
	
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
		virtual void Play(wxThreadKind kind = wxTHREAD_DETACHED);
		virtual void Pause();

		virtual void SetName(const wxString & s) {
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
		 * Play the file.
		 * This function is called from the
		 * thread object. It plays the file using sleep
		 * operations.
		 */
		wxThread::ExitCode ThreadPlay(FileTimer * timer);
		wxThread::ExitCode WaitForDeviceFinish(wxThreadWait flags=wxTHREAD_WAIT_BLOCK) {
			mutASSERT(timer);
			if (timer) {
				mutASSERT(wxThread::This() != timer);
				if (wxThread::This() != timer) {
#if wxCHECK_VERSION(2,9,2)
					return (timer -> Wait(flags));
#else
					return (timer -> Wait());
#endif
				} else return timer;
			}
		}

		virtual mutString GetTypeName () const {
			return N_("Generic input file");
		}
	
#ifdef WX
		virtual wxString TowxString() const;
#endif
		
	protected:
		/** 
		 * Fixed offset for the relative time the file returns.
		 */
		mutint64 referenceTime; // ms
		mutint64 pauseTime;     // ms
	};


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


///\}
