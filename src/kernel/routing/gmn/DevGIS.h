/** \file    -*- C++ -*-
********************************************************************
* GIS - devices
*
* Copyright:   (c) 1998-2011 TU Dresden
* \author  
* R. Krauße,
* Tobias Schlemmer <keinstein@users.berlios.de>
* \date 
* $Date: 2011/11/02 14:31:57 $
* \version $Revision: 1.7 $
* \license GPL
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
#include "src/kernel/routing/CommonFileDevice.h"
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
		virtual void NoteOn(mutabor_box_type * box, 
				    int taste, 
				    int velo,
				    RouteClass * r, 
				    size_t id, 
				    const ChannelData &cd)
			{};

		virtual void NoteOff(mutabor_box_type * box, 
				     int taste,
				     int velo, 
				     RouteClass * r, 
				     size_t id,
				     bool is_note_on)
			{};

		virtual void NotesCorrect(RouteClass * route)
			{};

		virtual void Controller(int,int,int) {}
/*
		virtual void Sustain(int channel, const ChannelData & cd)
			{};
*/

		virtual int  GetChannel(int taste, int channel, int id)
			{
				return -1;
			}

		virtual void Gis(GisToken *token, char turn);
		virtual void MidiOut(DWORD data, size_t n)
			{};

		virtual void MidiOut(BYTE *p, size_t n)
			{};

		virtual void AddTime(frac time)
			{
				Head->AddTime(time);
			}

		virtual void Quiet(RouteClass * r)
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

	class InputGis : public CommonFileInputDevice
	{
		friend class GisFactory;

	protected:
		wxString Id;
		GisToken *Data;
		GisReadArtHead *Head;

/*
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


*/
		InputGis()
			: CommonFileInputDevice(),Id()
			{
				Head = 0;
				Data = 0;
			}

		InputGis(int devId, 
			 const mutStringRef name = mutEmptyString, 
			 mutabor::MutaborModeType mode
			 = mutabor::DeviceStop, 
			 int id = -1)
			: CommonFileInputDevice(devId,name,mode,id),Id(name)
			{
				Head = 0;
				Data = 0;
			}

/*
		InputGis(const mutStringRef name, int id):CommonFileInputDevice(id,name),
							 Id(name)
			{
				Head = 0;
				Data = 0;
			}
*/	
	public:
		typedef CommonFileInputDevice base;

		virtual ~InputGis() {}
	
		/// Save route settings (filter settings) for a given route
		/** Some route settings (e.g. filter settings) are device type 
		 * specific. This function saves them in a tree storage.
		 * \argument config (tree_storage *) Storage class, where the data will be saved.
		 * \argument route (Route ) Route whos data shall be saved.
		 */
		virtual void Save (tree_storage & config, const RouteClass * route);
	
	
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
		virtual void Panic();

		void Proceed(GisReadArtHead *h, char turn, Route route);
		void ProceedRoute(GisReadArtHead *h, char turn);
		virtual mutint64 ReadOn(mutint64 delta);
		/*		{
				return GisReadArtHeadOn(&Head, time, Proceed);
				}*/

		virtual DevType GetType() const
			{
				return DTGis;
			}

		mutint64 PrepareNextEvent();

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
		mutint64 minDelta;  // in ticks
//		UINT TimerId;
//    long SpeedFactor;
//    frac LastDelta;

	};

	class GisFactory:public DeviceFactory { 
	public:
		GisFactory(size_t id = DTGis):
			DeviceFactory(id) {}
		virtual ~GisFactory();

	protected:
		virtual size_t GetType() const
			{
				return DTMidiFile;
			}


		virtual mutabor::OutputDeviceClass * DoCreateOutput() const;
		
		virtual mutabor::InputDeviceClass * DoCreateInput() const;
		virtual mutabor::OutputDeviceClass * DoCreateOutput(int devId,
							     const mutStringRef name, 
							     int id = -1) const;
		
		virtual mutabor::InputDeviceClass * DoCreateInput(int devId,
							   const mutStringRef name, 
							   int id = -1) const;

		virtual mutabor::OutputDeviceClass * DoCreateOutput(int devId,
							     const mutStringRef name, 
							     mutabor::MutaborModeType mode, 
							     int id = -1) const;
		
		virtual mutabor::InputDeviceClass * DoCreateInput(int devId,
							   const mutStringRef name, 
							   mutabor::MutaborModeType mode, 
							   int id = -1) const;
	};

}
#endif /* precompiled */
#endif


///\}
