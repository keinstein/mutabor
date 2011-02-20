// -*-C++ -*-
/** \file
 ********************************************************************
 * MIDI input device shape for route window.
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/muwx/Routing/OutputMidiDeviceShape.cpp,v 1.4 2011/02/20 22:35:59 keinstein Exp $
 * \author Rüdiger Krauße <krausze@mail.berlios.de>,
 * Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 2009/11/23
 * $Date: 2011/02/20 22:35:59 $
 * \version $Revision: 1.4 $
 * \license GPL
 *
 * $Log: OutputMidiDeviceShape.cpp,v $
 * Revision 1.4  2011/02/20 22:35:59  keinstein
 * updated license information; some file headers have to be revised, though
 *
 * Revision 1.3  2010-12-13 00:27:53  keinstein
 * compiles in linux as well as in mingw
 *
 * Revision 1.2  2010-11-21 13:15:50  keinstein
 * merged experimental_tobias
 *
 * Revision 1.1.2.5  2010-11-18 21:46:14  keinstein
 * MutFrame: get rid of OnIdle (this may break something, but saves much more CPU cycles
 * Some further steps to get rid of EDevice*
 *
 * Revision 1.1.2.4  2010-04-15 09:28:43  keinstein
 * changing routes works, but is not honoured by MIDI, yet
 *
 * Revision 1.1.2.3  2010/03/30 08:38:27  keinstein
 * added rudimentary command line support
 * changed debug system to allow selection of messages via command line
 * further enhancements to the route dialogs
 *
 * Revision 1.1.2.2  2010/02/15 12:08:21  keinstein
 * intermediate update for backup progress
 *
 * Revision 1.1.2.1  2010/01/14 10:16:43  keinstein
 * added output device shapes
 *
 * Revision 1.1.2.2  2010/01/11 12:51:52  keinstein
 * fix some problems due to splitting MutRouteShapes.{cpp,h}
 *
 * Revision 1.1.2.1  2009/11/30 12:08:57  keinstein
 * split MutRouteShapes into several files into directory Routing
 *
 * MutRouteShapes.cpp,v
 * Revision 1.1.2.3  2009/11/03 15:07:07  keinstein
 * Compile on Ubuntu 9.10
 * remove several interface and implementation pragmas
 * fixed some file names for case insensitive filesystems
 *
 * Revision 1.1.2.2  2009/11/03 12:39:31  keinstein
 * input device dialog: Allow to edit input devices
 * fix a bug on Mac OS X, that prevented Mutabor from starting if no MIDI device is availlable
 *
 * Revision 1.1.2.1  2009/08/10 11:23:12  keinstein
 * merged from wrong tree
 *
 * Revision 1.2  2009/08/10 11:15:47  keinstein
 * some steps towards new route window
 *
 * Revision 1.1  2008/11/03 15:31:54  keinstein
 * Added to the system
 *
 *
 ********************************************************************
 *\addtogroup route
 *\{
 ********************************************************************/
#include "OutputMidiDeviceShape.h"
#include "DevMidi.h"
#include <limits>

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
	DEBUGLOG (other, _T("Type: %d"),DTMidiPort);
	wxASSERT(device);
	wxASSERT(device->GetType() == DTMidiPort);
	wxASSERT(out);
	OutMidiPort * dev = dynamic_cast<OutMidiPort *> (device);
	wxASSERT (dev);
	out -> SetType(DTMidiPort);
	out -> SetMidiDevice(dev->GetDevId());
	out -> SetMidiBendingRange (dev-> GetBendingRange());
}

bool MutOutputMidiDeviceShape::readDialog (OutputDevDlg * out)
{
	wxASSERT(device);
	wxASSERT(device->GetType() == DTMidiPort);
	wxASSERT(out);
	wxASSERT (out -> GetType() == DTMidiPort);
	OutMidiPort * dev = dynamic_cast<OutMidiPort *> (device);
	if (!dev) return false;
	wxASSERT (dev);
	DEBUGLOG(routing,_T("New midi device: %d"),out -> GetMidiDevice());
	dev->SetDevId (out -> GetMidiDevice());
	dev->SetBendingRange (out->GetMidiBendingRange());
	SetLabel (dev->GetName());
	return true;
}

wxPanel * MutOutputMidiDeviceShape::GetOutputFilterPanel(wxWindow * parent, 
						       Route * route) const
{
	const int maxint = std::numeric_limits<int>().max();
	MidiOutputFilterPanel * panel = new MidiOutputFilterPanel(parent);
	if (!panel) return NULL;
	OutMidiPort * dev = dynamic_cast<OutMidiPort *> (device);
	const int maxchannel = dev?dev->GetMaxChannel():maxint;
	const int minchannel = dev?dev->GetMinChannel():0;
	if (!route) {
		panel->SetFromChannel(minchannel, minchannel, maxchannel);
		panel->SetToChannel(maxchannel, minchannel, maxchannel);
		panel->SetAvoidDrumChannel(true);
		return panel;
	}
	panel->SetFromChannel(route->OFrom, minchannel, maxchannel);
	panel->SetToChannel(route->OTo, minchannel, maxchannel);
	panel->SetAvoidDrumChannel(route->ONoDrum);
	return panel;
}

void MutOutputMidiDeviceShape::ReadOutputFilterPanel(wxWindow * panel, Route * route)
{
	wxASSERT(route);
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

/*
 * \}
 */
