// -*-C++ -*-
/** \file
********************************************************************
* MIDI input device shape for route window.
*
* \author Rüdiger Krauße,
* Tobias Schlemmer <keinstein@users.sourceforge.net>
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
*\addtogroup GUIroute
*\{
********************************************************************/
#include "src/wxGUI/Routing/InputMidiDeviceShape.h"
#include "src/kernel/routing/Route-inlines.h"
#include "src/wxGUI/Routing/InputDevDlg.h"
#include "src/kernel/routing/midi/DevMidi.h"
#include <limits>

using namespace mutabor;

MUTABOR_NAMESPACE(mutaborGUI)

void MutInputMidiDeviceShape::InitializeDialog(InputDevDlg * in) const
{
	mutASSERT(device);
	mutASSERT(device->GetType() == DTMidiPort);
	mutASSERT(in);
	InputMidiPort * dev = dynamic_cast<InputMidiPort *> (device.get());
	mutASSERT (dev);
	in -> SetType(DTMidiPort);
	in -> SetMidiDevice(dev->GetDevId());
}

bool MutInputMidiDeviceShape::readDialog (InputDevDlg * in)
{
	mutASSERT(device);
	mutASSERT(device->GetType() == DTMidiPort);
	mutASSERT(in);
	mutASSERT (in -> GetType() == DTMidiPort);
	InputMidiPort * dev = dynamic_cast<InputMidiPort *> (device.get());
	if (!dev) return false;
	mutASSERT (dev);
	DEBUGLOG (routing, "New input midi device: %p" ,&(*(in -> GetMidiDevice())));
	dev->SetDevId (in -> GetMidiDevice());
	SetLabel (dev->GetName());
	return true;
}

wxPanel * MutInputMidiDeviceShape::GetFilterPanel(wxWindow * parent, 
						  Route & route) const
{
	//const int maxint = std::numeric_limits<int>().max();
	MidiInputFilterPanel * panel = new MidiInputFilterPanel(parent);
	if (!panel) return NULL;
	InputMidiPort * dev = dynamic_cast<InputMidiPort *> (device.get());
	const int maxchannel = dev?dev->GetMaxChannel():MIDI_MAX_CHANNEL;
	const int minchannel = dev?dev->GetMinChannel():MIDI_MIN_CHANNEL;
	const int maxkey = dev?dev->GetMaxKey():MIDI_MAX_KEY;
	const int minkey = dev?dev->GetMinKey():MIDI_MIN_KEY;
	if (!route) {
		panel->SetFromChannel(minchannel, minchannel, maxchannel);
		panel->SetToChannel(maxchannel, minchannel, maxchannel);
		panel->SetFromKey(minkey, minkey, maxkey);
		panel->SetToKey(maxkey, minkey, maxkey);
		panel->SetRouteType(RTall);
		return panel;
	}
	panel->SetFromChannel(route->GetInputFrom(), minchannel, maxchannel);
	panel->SetToChannel(route->GetInputTo(), minchannel, maxchannel);
	panel->SetFromKey(route->GetInputFrom(), minkey, maxkey);
	panel->SetToKey(route->GetInputTo(), minkey, maxkey);
	panel->SetRouteType(route->GetType());
	return panel;
}

void MutInputMidiDeviceShape::ReadFilterPanel(wxWindow * panel, Route & route)
{
	MidiInputFilterPanel * pan = dynamic_cast<MidiInputFilterPanel *> (panel);
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
		route->SetInputFrom(pan->GetFromKey());
		route->SetInputTo(pan->GetToKey());
		break;
	default:
		UNREACHABLEC;
		break;
	}
	return;
}



IMPLEMENT_DYNAMIC_CLASS(MutInputMidiDeviceShape, MutInputDeviceShape)

MUTABOR_NAMESPACE_END(mutaborGUI)

/*
 * \}
 */
