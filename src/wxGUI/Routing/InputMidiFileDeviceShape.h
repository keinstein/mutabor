// -*- C++ -*-

/** \file
 ********************************************************************
 * MIDI file input device shape.
 *
 * \author Rüdiger Krauße <krausze@mail.berlios.de>,
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
 *
 ********************************************************************
 *\addtogroup route
 *\{
 ********************************************************************/

/* we guard a little bit complicated to ensure the references are set right
 */

#if (!defined(MUWX_ROUTING_INPUTMIDIFILEDEVICESHAPE_H) && !defined(PRECOMPILE)) \
	|| (!defined(MUWX_ROUTING_INPUTMIDIFILEDEVICESHAPE_H_PRECOMPILED))
#ifndef PRECOMPILE
#define MUWX_ROUTING_INPUTMIDIFILEDEVICESHAPE_H
#endif

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

#include "src/kernel/Defs.h"
#include "src/wxGUI/Routing/RouteIcons.h"
#include "src/wxGUI/Routing/DeviceShape.h"
//#include "Device.h"

#ifndef MUWX_ROUTING_INPUTMIDIFILEDEVICESHAPE_H_PRECOMPILED
#define MUWX_ROUTING_INPUTMIDIFILEDEVICESHAPE_H_PRECOMPILED

// system headers which do seldom change
//#include <map>
//#include "wx/defs.h"
//#include "wx/icon.h"
//#include "wx/stattext.h"


namespace mutaborGUI {

	class MidiFileInputFilterPanel : public MidiFileInputFilterPanelBase {
	public:
		MidiFileInputFilterPanel(wxWindow * parent):MidiFileInputFilterPanelBase(parent) {}
		/**
		 * TODO: set limits according to changes: min.max = max.value and max.min = min.value
		 */
		void SetFromChannel(int current, int min, int max) {
			from_channel->SetRange(min,max);
			from_channel->SetValue(current);
		}
		int GetFromChannel() const { return from_channel->GetValue(); }
	
		void SetToChannel(int current, int min, int max) {
			to_channel->SetRange(min,max);
			to_channel->SetValue(current);
		}
		int GetToChannel() const { return to_channel->GetValue(); }
	
		void SetFromTrack(int current, int min, int max) {
			from_track->SetRange(min,max);
			from_track->SetValue(current);
		}
		int GetFromTrack() const 
			{
				return from_track->GetValue();
			}
	
		void SetToTrack(int current, int min, int max) {
			to_track->SetRange(min,max);
			to_track->SetValue(current);
		}
		int GetToTrack() const
			{
				return to_track->GetValue();
			}
	
		void SetRouteType(mutabor::RouteType routetype) {
			wxPanel * panel = NULL;
			switch (routetype) {
			case mutabor::RTall: panel = all_panel; break;
			case mutabor::RTchannel: panel = channel_panel; break;
			case mutabor::RTstaff: panel = track_panel; break;
			case mutabor::RTelse: panel = else_panel; break;
			default:
				std::cerr << "MidiFileInputFilterPanel::SetRouteType: invaid route type " 
					  << routetype << std::endl;
				abort();
			}
			for (size_t i = 0 ; i < type->GetPageCount(); i++) {
				if (type -> GetPage(i) != panel) continue;
				type->SetSelection(i);
			}
		}
	
	
		mutabor::RouteType GetRouteType() const {
			wxWindow * window = type->GetCurrentPage();
			if (window == all_panel)
				return mutabor::RTall;
			else if (window == channel_panel)
				return mutabor::RTchannel;
			else if (window == track_panel)
				return mutabor::RTstaff;
			else if (window == else_panel)
				return mutabor::RTelse;
			else {
				UNREACHABLEC;
				return mutabor::RTall;
			}
		}	
	};


	class MutInputMidiFileDeviceShape:public MutInputDeviceShape
	{
		friend class GUIMidiFileFactory;
	protected:
		MutInputMidiFileDeviceShape():MutInputDeviceShape() {}
		MutInputMidiFileDeviceShape (wxWindow * parent,
					     wxWindowID id, 
					     mutabor::InputDevice & d):
			MutInputDeviceShape() {
			Create (parent,id,d);
		}
	public:
		bool Create (wxWindow * parent, 
			     wxWindowID id, 
			     mutabor::InputDevice & d)
			{
				TRACEC;
				bool ret = MutInputDeviceShape::Create(parent,id,d);
				TRACEC;
				return ret;
			}

		virtual MutIcon & GetMutIcon () 
			{
				TRACEC;
				return MidiFileBitmap;
			}

		void SetLabel(const wxString & st ) {
			fileName = st;
			fileName.Normalize();
			MutInputDeviceShape::SetLabel (fileName.GetFullName());
		}

		virtual wxPanel * GetFilterPanel(wxWindow * parent, 
						      mutabor::Route &  route) const;
		virtual void ReadFilterPanel(wxWindow * panel, 
						  mutabor::Route & route);


	protected: 
		virtual void InitializeDialog(InputDevDlg * in) const;
		virtual bool readDialog (InputDevDlg * in);
		virtual bool CanHandleType (mutabor::DevType  type) { 
			return type == mutabor::DTMidiFile;
		}

		wxFileName fileName;

	private:
		DECLARE_DYNAMIC_CLASS(MutInputMidiFileDeviceShape)

	};

}
#endif				/* InputMidiFileDeviceShape_H_PRECOMPILED */
#endif				/* InputMidiFileDeviceShape_H */
/*
 * \}
 */
