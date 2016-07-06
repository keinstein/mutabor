// -*-C++ -*-
/** \file
 ********************************************************************
 * MIDI input device shape for route window.
 *
 * \author Rüdiger Krauße <krausze@mail.berlios.de>,
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
#include "src/wxGUI/Routing/OutputMidiDeviceShape.h"
#include "src/kernel/routing/Route-inlines.h"
#include "src/kernel/routing/midi/DevMidi.h"
#include "src/wxGUI/Routing/OutputDevDlg.h"
#include "src/wxGUI/Routing/GUIRoute-inlines.h"
#include <limits>

using namespace mutabor;

namespace mutaborGUI {

	class MidiOutputFilterPanel : public MidiOutputFilterPanelBase {
	public:
		MidiOutputFilterPanel(wxWindow * parent):MidiOutputFilterPanelBase(parent) {}
		/**
		 * TODO: set limits according to changes: min.max = max.value and max.min = min.value
		 */
		void SetFromChannel(int current, int min, int max) {
			from_channel->SetRange(min,max);
			from_channel->SetValue(current);
		}
		int GetFromChannel() const 
		{
			return from_channel->GetValue();
		}
	
		void SetToChannel(int current, int min, int max) {
			to_channel->SetRange(min,max);
			to_channel->SetValue(current);
		}
		int GetToChannel() const
		{
			return to_channel->GetValue();
		}
	
		void SetAvoidDrumChannel(bool avoid) {
			avoid_drum_channel->SetValue(avoid);
		}
		bool GetAvoidDrumChannel() const
		{
			return avoid_drum_channel->GetValue();
		}
	};


	void MutOutputMidiDeviceShape::InitializeDialog(OutputDevDlg * out) const
	{
		DEBUGLOG (other, "Type: %d" ,DTMidiPort);
		mutASSERT(device);
		mutASSERT(device->GetType() == DTMidiPort);
		mutASSERT(out);
		OutputMidiPort * dev = dynamic_cast<OutputMidiPort *> (device.get());
		mutASSERT (dev);
		out -> SetType(DTMidiPort);
		out -> SetMidiDevice(dev->GetDevId());
		out -> SetMidiBendingRange (dev-> GetBendingRange());
	}

	bool MutOutputMidiDeviceShape::readDialog (OutputDevDlg * out)
	{
		mutASSERT(device);
		mutASSERT(device->GetType() == DTMidiPort);
		mutASSERT(out);
		mutASSERT (out -> GetType() == DTMidiPort);
		OutputMidiPort * dev = dynamic_cast<OutputMidiPort *> (device.get());
		if (!dev) return false;
		mutASSERT (dev);
		DEBUGLOG (routing, "New output midi device: %p" ,&(*(out -> GetMidiDevice())));
		dev->SetDevId (out -> GetMidiDevice());
		dev->SetBendingRange (out->GetMidiBendingRange());
		SetLabel (dev->GetName());
		return true;
	}

#ifdef max
#undef max
#endif

	wxPanel * MutOutputMidiDeviceShape::GetFilterPanel(wxWindow * parent, 
								 Route & route) const
	{
		const int maxint = std::numeric_limits<int>().max();
		MidiOutputFilterPanel * panel = new MidiOutputFilterPanel(parent);
		if (!panel) return NULL;
		OutputMidiPort * dev = dynamic_cast<OutputMidiPort *> (device.get());
		const int maxchannel = dev?dev->GetMaxChannel():maxint;
		const int minchannel = dev?dev->GetMinChannel():0;
		if (!route) {
			panel->SetFromChannel(minchannel, minchannel, maxchannel);
			panel->SetToChannel(maxchannel, minchannel, maxchannel);
			panel->SetAvoidDrumChannel(true);
			return panel;
		}
		panel->SetFromChannel(route->GetOutputFrom(), minchannel, maxchannel);
		panel->SetToChannel(route->GetOutputTo(), minchannel, maxchannel);
		panel->SetAvoidDrumChannel(route->OutputAvoidDrumChannel());
		return panel;
	}

	void MutOutputMidiDeviceShape::ReadFilterPanel(wxWindow * panel, Route & route)
	{
		mutASSERT(route);
		MidiOutputFilterPanel * pan = dynamic_cast<MidiOutputFilterPanel *> (panel);
		if (!pan) {
			UNREACHABLEC;
			return;
		}
	
		route->SetOutputFrom(pan->GetFromChannel());
		route->SetOutputTo(pan->GetToChannel());
		route->OutputAvoidDrumChannel(pan->GetAvoidDrumChannel());
	}


	IMPLEMENT_DYNAMIC_CLASS(MutOutputMidiDeviceShape, MutOutputDeviceShape)

}
/*
 * \}
 */
