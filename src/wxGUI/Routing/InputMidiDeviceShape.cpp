// -*-C++ -*-
/** \file
 ********************************************************************
 * MIDI input device shape for route window.
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/src/wxGUI/Routing/InputMidiDeviceShape.cpp,v 1.8 2011/11/02 14:32:00 keinstein Exp $
 * \author Rüdiger Krauße <krausze@mail.berlios.de>,
 * Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 2009/11/23
 * $Date: 2011/11/02 14:32:00 $
 * \version $Revision: 1.8 $
 * \license GPL
 *
 * $Log: InputMidiDeviceShape.cpp,v $
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
 * Revision 1.6  2011-09-30 18:07:05  keinstein
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
 * Revision 1.4  2011-02-20 22:35:58  keinstein
 * updated license information; some file headers have to be revised, though
 *
 * Revision 1.3  2010-12-13 00:27:53  keinstein
 * compiles in linux as well as in mingw
 *
 * Revision 1.2  2010-11-21 13:15:49  keinstein
 * merged experimental_tobias
 *
 * Revision 1.1.2.7  2010-09-29 13:03:30  keinstein
 * config can be stored and restored with new treeconfig
 *
 * Revision 1.1.2.6  2010/03/30 15:57:58  keinstein
 * added editing of existing routes to boxDlg
 *
 * Revision 1.1.2.5  2010/03/30 08:40:15  keinstein
 * added rudimentary command line support
 * changed debug system to allow selection of messages via command line
 * further enhancements to the route dialogs
 *
 * Revision 1.1.2.4  2010/02/15 12:08:21  keinstein
 * intermediate update for backup progress
 *
 * Revision 1.1.2.3  2010/01/14 18:14:20  keinstein
 * fix usage of installation prefix
 * MutInputDeviceShape/MutOutputDeviceShape:
 *     use GetType for type checking in OnChoiceSelected
 *     make InitalizeDialog const
 * MutNewOutputDeviceShape: add InitializeDialog and ReplaceSelfBy
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
#include "src/wxGUI/Routing/InputMidiDeviceShape.h"
#include "src/kernel/routing/Route-inlines.h"
#include "src/kernel/routing/midi/DevMidi.h"
#include <limits>

using namespace mutabor;

namespace mutaborGUI {
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
		dev->SetDevId (in -> GetMidiDevice());
		SetLabel (dev->GetName());
		return true;
	}

	wxPanel * MutInputMidiDeviceShape::GetInputFilterPanel(wxWindow * parent, 
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

	void MutInputMidiDeviceShape::ReadInputFilterPanel(wxWindow * panel, Route & route)
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

}
/*
 * \}
 */
