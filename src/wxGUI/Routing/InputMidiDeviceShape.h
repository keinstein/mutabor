// -*- C++ -*-
/** \file
 ********************************************************************
 * MIDI input device shape for route window.
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
 *
 ********************************************************************
 *\Addtogroup route
 *\{
 ********************************************************************/

/* we guard a little bit complicated to ensure the references are set right
 */

#if (!defined(MUWX_ROUTING_INPUTMIDIDEVICESHAPE_H) && !defined(PRECOMPILE)) \
	|| (!defined(MUWX_ROUTING_INPUTMIDIDEVICESHAPE_H_PRECOMPILED))
#ifndef PRECOMPILE
#define MUWX_ROUTING_INPUTMIDIDEVICESHAPE_H
#endif

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

#include "src/kernel/Defs.h"
#include "src/kernel/routing/Device.h"
#include "src/wxGUI/Routing/GUIRoute.h"
#include "src/wxGUI/Routing/RouteIcons.h"
#include "src/wxGUI/Routing/DeviceShape.h"
#include "src/wxGUI/resourceload.h"
//#include "Device.h"

#ifndef MUWX_ROUTING_INPUTMIDIDEVICESHAPE_H_PRECOMPILED
#define MUWX_ROUTING_INPUTMIDIDEVICESHAPE_H_PRECOMPILED

// system headers which do seldom change

//#include <map>

//#include "wx/defs.h"
//#include "wx/icon.h"
//#include "wx/stattext.h"

namespace mutaborGUI {

	class MidiInputFilterPanel : public MidiInputFilterPanelBase {
	public:
		typedef mutabor::RouteType RouteType;
		MidiInputFilterPanel(wxWindow * parent):MidiInputFilterPanelBase(parent) {}
		/**
		 * TODO: set limits according to changes: min.max = max.value and max.min = min.value
		 */
		void SetFromChannel(int current, int min, int max) {
			from_channel->SetRange(min,max);
			from_channel->SetValue(current);
		}
		int GetFromChannel() const{ return from_channel->GetValue(); }
	
		void SetToChannel(int current, int min, int max) {
			to_channel->SetRange(min,max);
			to_channel->SetValue(current);
		}
		int GetToChannel() const{ return to_channel->GetValue(); }
	
		void SetFromKey(int current, int min, int max) {
			from_key->SetRange(min,max);
			from_key->SetValue(current);
		}
		int GetFromKey() const{ return from_key->GetValue(); }
	
		void SetToKey(int current, int min, int max) {
			to_key->SetRange(min,max);
			to_key->SetValue(current);
		}
		int GetToKey() const { return to_key->GetValue(); }
	
		void SetRouteType(RouteType routetype) {
			wxPanel * panel;
			switch (routetype) {
			case mutabor::RTall: panel = all_panel; break;
			case mutabor::RTchannel: panel = channel_panel; break;
			case mutabor::RTstaff: panel = key_panel; break;
			case mutabor::RTelse: panel = else_panel; break;
			default:
				UNREACHABLEC;
				std::cerr << "MidiInputFilterPanel::SetRouteType: invaid route type " 
					  << routetype << std::endl;
				abort();
				panel = NULL;
			}
			for (size_t i = 0 ; i < type->GetPageCount(); i++) {
				if (type -> GetPage(i) != panel) continue;
				type->SetSelection(i);
			}
		}
	
		RouteType GetRouteType() const {
			wxWindow * window = type->GetCurrentPage();
			if (window == all_panel)
				return mutabor::RTall;
			else if (window == channel_panel)
				return mutabor::RTchannel;
			else if (window == key_panel)
				return mutabor::RTstaff;
			else if (window == else_panel)
				return mutabor::RTelse;
			else {
				UNREACHABLEC;
				return mutabor::RTall;
			}
		}
	};

	class MutInputMidiDeviceShape:public MutInputDeviceShape
	{
		friend class GUIMidiPortFactory;
	protected:
		MutInputMidiDeviceShape():MutInputDeviceShape() {}
		MutInputMidiDeviceShape (wxWindow * parent,
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
				return MutInputDeviceShape::Create(parent,id,d);
			}

		virtual MutIcon & GetMutIcon () 
			{
				TRACEC;
				return MidiInputDevBitmap;
			}
	
		virtual wxPanel * GetFilterPanel(wxWindow * parent, 
						      mutabor::Route & route) const;
		virtual void ReadFilterPanel(wxWindow * panel, 
						  mutabor::Route & route);


	protected: 
		virtual void InitializeDialog(InputDevDlg * in) const;
		virtual bool readDialog (InputDevDlg * in);
		virtual bool CanHandleType (mutabor::DevType  type) { 
			return type == mutabor::DTMidiPort; 
		}


	private:
		DECLARE_DYNAMIC_CLASS(MutInputMidiDeviceShape)

	};
}
#endif				/* INPUTMIDIDEVICESHAPE_H_PRECOMPILE */
#endif				/* INPUTMIDIDEVICESHAPE_H */
/*
 * \}
 */
