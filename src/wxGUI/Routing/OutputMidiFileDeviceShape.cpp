// -*-C++ -*-
/** \file
********************************************************************
* Midi fiele input device shape for route window.
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
********************************************************************
*\addtogroup GUIroute
*\{
********************************************************************/
#include "src/wxGUI/Routing/OutputMidiFileDeviceShape.h"
#include "src/kernel/routing/Route-inlines.h"
#include "src/kernel/routing/midi/DevMidF.h"
#include "src/wxGUI/Routing/GUIRoute-inlines.h"
#include "src/wxGUI/Routing/OutputDevDlg.h"
#include <limits>

#ifdef max
#undef max
#endif

using namespace mutabor;

MUTABOR_NAMESPACE(mutaborGUI)

class MidiFileOutputFilterPanel : public MidiFileOutputFilterPanelBase {
public:
	MidiFileOutputFilterPanel(wxWindow * parent):MidiFileOutputFilterPanelBase(parent) {}
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



void MutOutputMidiFileDeviceShape::InitializeDialog(OutputDevDlg * out) const
{
	mutASSERT(device);
	mutASSERT(device->GetType() == DTMidiFile);
	mutASSERT(out);
	OutputMidiFile * d = static_cast<OutputMidiFile *>(device.get());
	if (!d) {
		UNREACHABLEC;
		return;
	}
	out -> SetType(DTMidiFile);
	out -> SetMidiFile(d->GetName());
	out -> SetMidiFileBendingRange (d -> GetBendingRange());
}

bool MutOutputMidiFileDeviceShape::readDialog (OutputDevDlg * out)
{
	mutASSERT(device);
	mutASSERT(device->GetType() == DTMidiFile);
	mutASSERT(out);
	mutASSERT (out -> GetType() == DTMidiFile);
	OutputMidiFile * d = dynamic_cast<OutputMidiFile *>(device.get());
	mutASSERT(d);
	d->SetName ((const char * )(out -> GetMidiFile().ToUTF8()));
	d->SetBendingRange (out -> GetMidiFileBendingRange());
	SetLabel (wxString::FromUTF8(device->GetName().c_str()));
	return true;
}

wxPanel * MutOutputMidiFileDeviceShape::GetFilterPanel(wxWindow * parent, 
						       Route & route) const
{
	const int maxint = std::numeric_limits<int>().max();
	MidiFileOutputFilterPanel * panel = new MidiFileOutputFilterPanel(parent);
	if (!panel) return NULL;
	OutputMidiFile * dev = dynamic_cast<OutputMidiFile *> (device.get());
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

void MutOutputMidiFileDeviceShape::ReadFilterPanel(wxWindow * panel, Route & route)
{
	mutASSERT(route);
	MidiFileOutputFilterPanel * pan = dynamic_cast<MidiFileOutputFilterPanel *> (panel);
	if (!pan) {
		UNREACHABLEC;
		return;
	}
	
	route->SetOutputFrom(pan->GetFromChannel());
	route->SetOutputTo(pan->GetToChannel());
	route->OutputAvoidDrumChannel(pan->GetAvoidDrumChannel());
}



IMPLEMENT_DYNAMIC_CLASS(MutOutputMidiFileDeviceShape, MutOutputDeviceShape)

MUTABOR_NAMESPACE_END(mutaborGUI)

/*
 * \}
 */
