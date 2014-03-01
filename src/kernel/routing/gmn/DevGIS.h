/** \file    -*- C++ -*-
********************************************************************
* GIS - devices
*
* Copyright:   (c) 1998-2011 TU Dresden
* \author
* R. Krauße,
* Tobias Schlemmer <keinstein@users.berlios.de>
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
* \todo Implement handling of controllers
********************************************************************
* \addtogroup route
* \{
********************************************************************/
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

		OutputGis(const mutStringRef name,
			  int id = -1) : OutputDeviceClass(name, id)
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

		virtual DevType GetType() const
			{
				return DTGis;
			}

		virtual mutString GetTypeName () const {
			return N_("GIS output file");
		}

#ifdef WX
		virtual wxString TowxString() const {
			return OutputDeviceClass::TowxString() +
				wxString::Format(_T("\n  Name = %s"),
						 Name.c_str());
		}
#endif
	protected:

		virtual bool do_Open()
			{
				return false;
			}

#if defined(_MSC_VER)
#pragma warning(push) // Save warning settings.
#pragma warning(disable : 4100) // Disable unreferenced formal parameter warnings
#endif
		virtual void do_NoteOn(mutabor::Box box,
				    int taste,
				    int velo,
				    RouteClass * r,
				    size_t id,
				    const ChannelData &cd)
			{};

		virtual void do_NoteOff(mutabor::Box box,
				     int taste,
				     int velo,
				     RouteClass * r,
				     size_t id,
				     bool is_note_on)
			{};

		virtual void do_UpdateTones(RouteClass * route) {};

		virtual void do_Controller(int,int,int,size_t) {}
/*
		virtual void Sustain(int channel, const ChannelData & cd)
			{};
*/

		virtual int  do_GetChannel(int taste, size_t channel, size_t id)
			{
				return midi::NO_CHANNEL;
			}

		virtual void do_Gis(GisToken *token, char turn);
		virtual void do_MidiOut(DWORD data, size_t n) {};
		virtual void do_MidiOut(BYTE *p, size_t n)	{};
		virtual void do_MidiOut(mutabor::Box box, midi_string data) {};
		virtual void do_handle_event(event e) {};
		virtual void do_AddTime(frac time)
			{
				Head->AddTime(time);
			}

		virtual void do_Quiet(Route r, int type)
			{};
		virtual void do_Quiet(Route r, int type, size_t id)
			{};

#if defined(_MSC_VER)
#pragma warning(pop) // Restore warnings to previous state.
#endif


	};

// InputGis ------------------------------------------------------------

	class InputGis : public CommonFileInputDevice
	{
		friend class GisFactory;

	protected:
		GisToken *Data;
		GisReadArtHead *Head;

		InputGis(const mutStringRef name = mutEmptyString,
			 mutabor::MutaborModeType mode
			 = mutabor::DeviceStop,
			 int id = -1)
			: CommonFileInputDevice(name,mode,id)
			{
				Head = 0;
				Data = 0;
			}

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
		virtual void doResetTime();

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
			return N_("GIS input file");
		}

		virtual ChannelData & GetChannelData(const current_keys_type::entry & key) const {
			return const_cast<ChannelData &>(channel_data);
		}


#ifdef WX
		virtual wxString TowxString() const {
			return InputDeviceClass::TowxString() +
				wxString::Format(_T("\n\
  Id: %s\n  minDelta = %ld\n"),
						 Name.c_str(),
						 minDelta);
		}
#endif


	private:
		static const ChannelData channel_data; /// currently unused
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


		virtual mutabor::OutputDeviceClass * DoCreateOutput(const mutStringRef name,
								    int id = -1) const;

		virtual mutabor::InputDeviceClass * DoCreateInput(const mutStringRef name,
								  mutabor::MutaborModeType mode,
								  int id = -1) const;
	};

}
#endif /* precompiled */
#endif


///\}
