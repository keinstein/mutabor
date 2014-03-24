// -*-C++ -*-

/** \file
 ********************************************************************
 * Midi fiele input device shape for route window.
 *
 * \author Rüdiger Krauße <krausze@mail.berlios.de>,
 * Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 2009/11/23
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
 ********************************************************************
 *\addtogroup GUIroute
 *\{
 ********************************************************************/
#include "InputMidiFileDeviceShape.h"
#include "src/wxGUI/Routing/InputDevDlg.h"
#include "src/kernel/routing/Route-inlines.h"
#include "src/wxGUI/resourceload.h"
#include <limits>

using namespace mutabor;

namespace mutaborGUI {
	void MutInputMidiFileDeviceShape::InitializeDialog(InputDevDlg * in) const
	{
		mutASSERT(device);
		mutASSERT(device->GetType() == DTMidiFile);
		mutASSERT(in);
		in -> SetType(DTMidiFile);
		in -> SetMidiFile(device->GetName());
	}

	/** configure device from dialog data
	 * This function reads the data from a device dialog, so that the data entered 
	 * by the user can be realized. 
	 * The following paameters are read:
	 *  - file name
	 *
	 * \todo implement return value
	 * 
	 * \param in Device Dialog.
	 * 
	 * \return true in case of success (currently don't rely on it)
	 */
	bool MutInputMidiFileDeviceShape::readDialog (InputDevDlg * in)
	{
		mutASSERT(device);
		mutASSERT(device->GetType() == DTMidiFile);
		mutASSERT(in);
		mutASSERT (in -> GetType() == DTMidiFile);
		device->SetName ((const char *)(in -> GetMidiFile().ToUTF8()));
		SetLabel (device->GetName());
		return true;
	}
#ifdef max
#undef max
#endif

	/** transfers the configuration data of an input filter from a route object to a dialog panel.
	 * Filter data is currently stored in some variables of the route class. These variables are reused for 
	 * several purposes. depending on the corresponding input device..
	 *
	 * This function creates an input filter panel for a route dialog and initializes it with 
	 * the appropriate values of the route as they are inerpred by a MIDI file input device class.
	 * 
	 * \param parent Parent window of the panel (usually a dialog or panel)
	 * \param route Route to read the data from
	 * 
	 * \return A panel, that is correctly initialized to communicate the filter data with the user. 
	 *           The calling function must take care of it's deletion (or delegate it)
	 */
	wxPanel * MutInputMidiFileDeviceShape::GetFilterPanel(wxWindow * parent, 
								   Route & route) const
	{
		const int maxint = std::numeric_limits<int>().max();
		MidiFileInputFilterPanel * panel = new MidiFileInputFilterPanel(parent);
		if (!panel) return NULL;
		InputMidiFile * dev = dynamic_cast<InputMidiFile *> (device.get());
		const int maxchannel = dev?dev->GetMaxChannel():maxint;
		const int minchannel = dev?dev->GetMinChannel():0;
		const int maxtrack = dev?dev->GetMaxTrack():maxint;
		const int mintrack = dev?dev->GetMinTrack():0;
		if (!route) {
			panel->SetFromChannel(minchannel, minchannel, maxchannel);
			panel->SetToChannel(maxchannel, minchannel, maxchannel);
			panel->SetFromTrack(mintrack, mintrack, maxtrack);
			panel->SetToTrack(maxtrack, mintrack, maxtrack);
			panel->SetRouteType(RTall);
			return panel;
		}
		panel->SetFromChannel(route->GetInputFrom(), minchannel, maxchannel);
		panel->SetToChannel(route->GetInputTo(), minchannel, maxchannel);
		panel->SetFromTrack(route->GetInputFrom(), mintrack, maxtrack);
		panel->SetToTrack(route->GetInputTo(), mintrack, maxtrack);
		panel->SetRouteType(route->GetType());
		return panel;
	}

	/** transfers the configuration data of an input filter from a dialog panel to the route object
	 * Filter data is currently stored in some variables of the route class. These varibles are reused for 
	 * several purposes. depending on the corresponding input device..
	 *
	 * This function reads data from an input filter panel of the route dialog and stores them 
	 * in the appropriate variables as they are inerpred by a MIDI file input device class.
	 *
	 * \todo Separate filters from route.
	 * 
	 * \param panel Panel with the data the user entered
	 * \param route Route object 
	 */
	void MutInputMidiFileDeviceShape::ReadFilterPanel(wxWindow * panel, Route & route)
	{
		MidiFileInputFilterPanel * pan = dynamic_cast<MidiFileInputFilterPanel *> (panel);
		if (!pan) {
			UNREACHABLEC;
			return;
		}
		route->SetType(pan->GetRouteType());
		switch (route->GetType()) {
		case RTall:
		case RTelse:
			// those have no data
			break;
		case RTchannel:
			route->SetInputFrom(pan->GetFromChannel());
			route->SetInputTo(pan->GetToChannel());
			break;
		case RTstaff:
			route->SetInputFrom(pan->GetFromTrack());
			route->SetInputTo(pan->GetToTrack());
			break;
		default:
			UNREACHABLEC;
			break;
		}
		return;
	}

	void MutInputMidiFileDeviceShape::DoDeviceNotification(wxCommandEvent & event)
	{
		if (device && device->IsOpen() && !playbuttons) {
			createPlayButtons();
		}
		MutInputDeviceShape::DoDeviceNotification(event);
	}

	IMPLEMENT_DYNAMIC_CLASS(MutInputMidiFileDeviceShape, MutInputDeviceShape)
}
/*
 * \}
 */
