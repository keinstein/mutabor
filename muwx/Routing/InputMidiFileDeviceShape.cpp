// -*-C++ -*-

/** \file
********************************************************************
* Midi fiele input device shape for route window.
*
* $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/muwx/Routing/InputMidiFileDeviceShape.cpp,v 1.3 2010/12/13 00:27:53 keinstein Exp $
* \author Rüdiger Krauße <krausze@mail.berlios.de>,
* Tobias Schlemmer <keinstein@users.berlios.de>
* \date 2009/11/23
* $Date: 2010/12/13 00:27:53 $
* \version $Revision: 1.3 $
*
* $Log: InputMidiFileDeviceShape.cpp,v $
* Revision 1.3  2010/12/13 00:27:53  keinstein
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
#include <limits>

void MutInputMidiFileDeviceShape::InitializeDialog(InputDevDlg * in) const
{
	wxASSERT(device);
	wxASSERT(device->GetType() == DTMidiFile);
	wxASSERT(in);
	in -> SetType(DTMidiFile);
	in -> SetMidiFile(device->GetName());
}

bool MutInputMidiFileDeviceShape::readDialog (InputDevDlg * in)
{
	wxASSERT(device);
	wxASSERT(device->GetType() == DTMidiFile);
	wxASSERT(in);
	wxASSERT (in -> GetType() == DTMidiFile);
	device->SetName (in -> GetMidiFile());
	SetLabel (device->GetName());
	return true;
}

wxPanel * MutInputMidiFileDeviceShape::GetInputFilterPanel(wxWindow * parent, 
						       Route * route) const
{
	const int maxint = std::numeric_limits<int>().max();
	MidiFileInputFilterPanel * panel = new MidiFileInputFilterPanel(parent);
	if (!panel) return NULL;
	InMidiFile * dev = dynamic_cast<InMidiFile *> (device);
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
	panel->SetFromChannel(route->IFrom, minchannel, maxchannel);
	panel->SetToChannel(route->ITo, minchannel, maxchannel);
	panel->SetFromTrack(route->IFrom, mintrack, maxtrack);
	panel->SetToTrack(route->ITo, mintrack, maxtrack);
	panel->SetRouteType(route->GetType());
	return panel;
}

void MutInputMidiFileDeviceShape::ReadInputFilterPanel(wxWindow * panel, Route * route)
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

/*
 * \}
 */
