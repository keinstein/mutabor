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
 * $Log: OutputMidiFileDeviceShape.cpp,v $
 * Revision 1.8  2011/11/02 14:32:00  keinstein
 * fix some errors crashing Mutabor on Windows
 *
 * Revision 1.7  2011-10-02 16:58:42  keinstein
 * * generate Class debug information when compile in debug mode
 * * InputDeviceClass::Destroy() prevented RouteClass::Destroy() from clearing references -- fixed.
 * * Reenable confirmation dialog when closing document while the logic is active
 * * Change debug flag management to be more debugger friendly
 * * implement automatic route/device deletion check
 * * new debug flag --debug-trace
 * * generate lots of tracing output
 *
 * Revision 1.6  2011-09-30 18:07:06  keinstein
 * * make compile on windows
 * * s/wxASSERT/mutASSERT/g to get assert handler completely removed
 * * add ax_boost_base for boost detection
 *
 * Revision 1.5  2011-09-27 20:13:25  keinstein
 * * Reworked route editing backend
 * * rewireing is done by RouteClass/GUIRoute now
 * * other classes forward most requests to this pair
 * * many bugfixes
 * * Version change: We are reaching beta phase now
 *
 * Revision 1.4  2011-02-20 22:35:59  keinstein
 * updated license information; some file headers have to be revised, though
 *
 * Revision 1.3  2010-12-13 00:27:53  keinstein
 * compiles in linux as well as in mingw
 *
 * Revision 1.2  2010-11-21 13:15:50  keinstein
 * merged experimental_tobias
 *
 * Revision 1.1.2.5  2010-06-22 15:05:45  keinstein
 * debugging segfault in route check after replacement of MutOutputDevice
 *
 * Revision 1.1.2.4  2010/04/15 09:28:43  keinstein
 * changing routes works, but is not honoured by MIDI, yet
 *
 * Revision 1.1.2.3  2010/03/30 08:40:15  keinstein
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
 ********************************************************************
 *\addtogroup route
 *\{
 ********************************************************************/
#include "src/wxGUI/Routing/OutputMidiFileDeviceShape.h"
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
		panel->SetFromChannel(route->OFrom, minchannel, maxchannel);
		panel->SetToChannel(route->OTo, minchannel, maxchannel);
		panel->SetAvoidDrumChannel(route->ONoDrum);
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
