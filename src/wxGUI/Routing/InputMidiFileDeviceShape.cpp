// -*-C++ -*-

/** \file
 ********************************************************************
 * Midi fiele input device shape for route window.
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/src/wxGUI/Routing/InputMidiFileDeviceShape.cpp,v 1.8 2011/11/02 14:32:00 keinstein Exp $
 * \author Rüdiger Krauße <krausze@mail.berlios.de>,
 * Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 2009/11/23
 * $Date: 2011/11/02 14:32:00 $
 * \version $Revision: 1.8 $
 * \license GPL
 *
 * $Log: InputMidiFileDeviceShape.cpp,v $
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
 * Revision 1.1.2.5  2010-03-30 15:57:58  keinstein
 * added editing of existing routes to boxDlg
 *
 * Revision 1.1.2.4  2010/03/30 08:40:15  keinstein
 * added rudimentary command line support
 * changed debug system to allow selection of messages via command line
 * further enhancements to the route dialogs
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
 ********************************************************************
 *\addtogroup route
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
		device->SetName (in -> GetMidiFile());
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


	IMPLEMENT_DYNAMIC_CLASS(MutInputMidiFileDeviceShape, MutInputDeviceShape)
}
/*
 * \}
 */
