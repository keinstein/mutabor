// -*-C++ -*-
/** \file
 ********************************************************************
 * Midi fiele input device shape for route window.
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/src/wxGUI/Routing/OutputMidiFileDeviceShape.cpp,v 1.8 2011/11/02 14:32:00 keinstein Exp $
 * \author Rüdiger Krauße <krausze@mail.berlios.de>,
 * Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 2009/11/23
 * $Date: 2011/11/02 14:32:00 $
 * \version $Revision: 1.8 $
 * \license GPL
 *
 *
 ********************************************************************
 *\addtogroup route
 *\{
 ********************************************************************/
#include "src/wxGUI/Routing/OutputMidiFileDeviceShape.h"
#include "src/kernel/routing/Route-inlines.h"
#include "src/kernel/routing/midi/DevMidF.h"
#include "src/wxGUI/Routing/GUIRoute-inlines.h"
#include <limits>

#ifdef max
#undef max
#endif

using namespace mutabor;

namespace mutaborGUI {

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
		d->SetName (out -> GetMidiFile());
		d->SetBendingRange (out -> GetMidiFileBendingRange());
		SetLabel (device->GetName());
		return true;
	}

	wxPanel * MutOutputMidiFileDeviceShape::GetOutputFilterPanel(wxWindow * parent, 
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

	void MutOutputMidiFileDeviceShape::ReadOutputFilterPanel(wxWindow * panel, Route & route)
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
}
/*
 * \}
 */
