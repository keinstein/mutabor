/** \file    -*- C++ -*-
********************************************************************
* Description
*
* $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/src/kernel/routing/gmn/DevGIS.h,v 1.7 2011/11/02 14:31:57 keinstein Exp $
* Copyright:   (c) 2008 TU Dresden
* \author  Tobias Schlemmer <keinstein@users.berlios.de>
* \date 
* $Date: 2011/11/02 14:31:57 $
* \version $Revision: 1.7 $
* \license GPL
*
* $Log: DevGIS.h,v $
* Revision 1.7  2011/11/02 14:31:57  keinstein
* fix some errors crashing Mutabor on Windows
*
* Revision 1.6  2011-10-02 16:58:41  keinstein
* * generate Class debug information when compile in debug mode
* * InputDeviceClass::Destroy() prevented RouteClass::Destroy() from clearing references -- fixed.
* * Reenable confirmation dialog when closing document while the logic is active
* * Change debug flag management to be more debugger friendly
* * implement automatic route/device deletion check
* * new debug flag --debug-trace
* * generate lots of tracing output
*
* Revision 1.5  2011-09-30 09:10:24  keinstein
* Further improvements in the routing system.
*
* Revision 1.4  2011-09-27 20:13:22  keinstein
* * Reworked route editing backend
* * rewireing is done by RouteClass/GUIRoute now
* * other classes forward most requests to this pair
* * many bugfixes
* * Version change: We are reaching beta phase now
*
* Revision 1.3  2011-02-20 22:35:56  keinstein
* updated license information; some file headers have to be revised, though
*
*
*
********************************************************************
* \addtogroup route
* \{
********************************************************************/
// #################################################################
// Mutabor, GIS - devices
// ##################################################################

/* we guard a little bit complicated to ensure the references are set right
 */

#if (!defined(MU32_ROUTING_GMN_DEVGIS_H) && !defined(PRECOMPILE)) \
	|| (!defined(MU32_ROUTING_GMN_DEVGIS_H_PRECOMPILED))
#ifndef PRECOMPILE
#define MU32_ROUTING_GMN_DEVGIS_H
#endif

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

#include "src/kernel/Defs.h"
//#include "Global.h"
#include "src/kernel/routing/Device.h"
#include "src/kernel/routing/gmn/GIS_Head.h"
//#include "Interpre.h"

#ifndef MU32_ROUTING_GMN_DEVGIS_H_PRECOMPILED
#define MU32_ROUTING_GMN_DEVGIS_H_PRECOMPILED

// system headers which do seldom change

#include "wx/timer.h"

namespace mutabor {
	extern mutString CurrentId;

	extern mutString CurrentSep;

// OutputGis -----------------------------------------------------------


	class GisFactory;
	class OutputGis : public OutputDeviceClass
	{
		friend class GisFactory;

	protected:
		GisWriteHead *Head;

		OutputGis(): OutputDeviceClass()
			{
				Head = 0;
			}

		OutputGis(int devId,
			  const mutStringRef name, 
			  int id = -1) : OutputDeviceClass(devId, name, id)
			{
				Head = new GisWriteHead(0, name);
			}

	public:
		virtual ~OutputGis()
			{
				delete Head;
			}
	
		/// Save current device settings in a tree storage
		/** \argument config (tree_storage) storage class, where the data will be saved.
		 */
		virtual void Save (tree_storage & config);
	
		/// Save route settings (filter settings) for a given route
		/** Some route settings (e.g. filter settings) are device type 
		 * specific. This function saves them in a tree storage.
		 * \argument config (tree_storage *) Storage class, where the data will be saved.
		 * \argument route (Route) Route whos data shall be saved.
		 */
		virtual void Save (tree_storage & config, const RouteClass * route);
	
		/// Load current device settings from a tree storage
		/** \argument config (tree_storage) storage class, where the data will be loaded from.
		 */
		virtual void Load (tree_storage & config);
	
		/// Loade route settings (filter settings) for a given route
		/** Some route settings (e.g. filter settings) are device type 
		 * specific. This function loads them from a tree storage.
		 * \argument config (tree_storage *) Storage class, where the data will be restored from.
		 * \argument route (Route) Route whos data shall be loaded.
		 */
		virtual void Load (tree_storage & config, RouteClass * route);

	
		virtual bool Open()
			{
				return false;
			}

		virtual bool IsOpen() {
			return false;
		}

		virtual void Close()
			{
				CloseAllSubs(Head);
			};

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

#if defined(_MSC_VER)
#pragma warning(push) // Save warning settings.
#pragma warning(disable : 4100) // Disable unreferenced formal parameter warnings
#endif
		virtual void NoteOn(int box, int taste, int velo,
				    RouteClass * r, int channel, ChannelData *cd)
			{};

		virtual void NoteOff(int box, int taste,
				     int velo, RouteClass * r, int channel)
			{};

		virtual void NotesCorrect(int box)
			{};

		virtual void Sustain(char on, int channel)
			{};

		virtual int  GetChannel(int taste)
			{
				return -1;
			}

		virtual void Gis(GisToken *token, char turn);
		virtual void MidiOut(DWORD data, char n)
			{};

		virtual void MidiOut(BYTE *p, char n)
			{};

		virtual void AddTime(frac time)
			{
				Head->AddTime(time);
			}

		virtual void Quite(RouteClass * r)
			{};

#if defined(_MSC_VER)
#pragma warning(pop) // Restore warnings to previous state.
#endif 

		virtual DevType GetType() const
			{
				return DTGis;
			}

		virtual mutString GetTypeName () const {
			return N_("GIS output file.");
		}

#ifdef WX
		virtual wxString TowxString() const {
			return OutputDeviceClass::TowxString() +
				wxString::Format(_T("\n  Name = %s"),
						 Name.c_str());
		}
#endif
	
	};

// InputGis ------------------------------------------------------------

	class InputGis : public InputDeviceClass
	{
		friend class GisFactory;

	protected:
		wxString Id;
		GisToken *Data;
		GisReadArtHead *Head;

		class GisTimer : public wxTimer
		{
			InputGis * file;
                
		public:
			GisTimer(InputGis * f) : wxTimer(),file(f)
				{}

			void Notify()
				{
					file->IncDelta();
				}
		};

		GisTimer timer;


		InputGis()
			: InputDeviceClass(),Id(),timer(this)
			{
				Head = 0;
				Data = 0;
			}

		InputGis(int devId, 
			 const mutStringRef name = mutEmptyString, 
			 mutabor::MutaborModeType mode
			 = mutabor::DeviceStop, 
			 int id = -1)
			: InputDeviceClass(devId,name,mode,id),Id(name),timer(this)
			{
				Head = 0;
				Data = 0;
			}
		InputGis(const mutStringRef name, int id):InputDeviceClass(id,name),
							 Id(name),timer(this)
			{
				Head = 0;
				Data = 0;
			}
	
	public:
		virtual ~InputGis() {}
	
		/// Save current device settings in a tree storage
		/** \argument config (tree_storage) storage class, where the data will be saved.
		 */
		virtual void Save (tree_storage & config);
	
		/// Save route settings (filter settings) for a given route
		/** Some route settings (e.g. filter settings) are device type 
		 * specific. This function saves them in a tree storage.
		 * \argument config (tree_storage *) Storage class, where the data will be saved.
		 * \argument route (Route ) Route whos data shall be saved.
		 */
		virtual void Save (tree_storage & config, const RouteClass * route);
	
	
		/// Load current device settings from a tree storage
		/** \argument config (tree_storage) storage class, where the data will be loaded from.
		 */
		virtual void Load (tree_storage & config);
	
		/// Loade route settings (filter settings) for a given route
		/** Some route settings (e.g. filter settings) are device type 
		 * specific. This function loads them from a tree storage.
		 * \argument config (tree_storage *) Storage class, where the data will be restored from.
		 * \argument route (Route) Route whos data shall be loaded.
		 */
		virtual void Load (tree_storage & config, RouteClass * route);

	
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

		void Proceed(GisReadArtHead *h, char turn, Route route);
		void ProceedRoute(GisReadArtHead *h, char turn);
		virtual long ReadOn(long delta);
		/*		{
				return GisReadArtHeadOn(&Head, time, Proceed);
				}*/

		virtual DevType GetType() const
			{
				return DTGis;
			}

		void IncDelta();

		virtual mutString GetTypeName () const {
			return N_("GIS input file.");
		}

#ifdef WX
		virtual wxString TowxString() const {
			return InputDeviceClass::TowxString() +
				wxString::Format(_T("\n  Id: %s\n  actDelta = %ld\n  minDelta = %ld\n  TimerId = %d\n  Busy = %d"),
						 Id.c_str());
		}
#endif
	

	private:
		long actDelta;  // in ticks
		long minDelta;  // in ticks
		UINT TimerId;
		BOOL Busy;
//    long SpeedFactor;
//    frac LastDelta;

	};

	class GisFactory:public DeviceFactory { 
	public:
		GisFactory(size_t id = 0):
			DeviceFactory(id) {}
		virtual ~GisFactory();

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

}
#endif /* precompiled */
#endif


///\}
