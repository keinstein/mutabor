// -*-C++ -*-
/** \file
 ********************************************************************
 * Input device shape base class for route window.
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/muwx/Routing/InputDeviceShape.cpp,v 1.3 2011/02/20 22:35:58 keinstein Exp $
 * \author Rüdiger Krauße <krausze@mail.berlios.de>,
 * Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 1998
 * $Date: 2011/02/20 22:35:58 $
 * \version $Revision: 1.3 $
 * \license GPL
 *
 * $Log: InputDeviceShape.cpp,v $
 * Revision 1.3  2011/02/20 22:35:58  keinstein
 * updated license information; some file headers have to be revised, though
 *
 * Revision 1.2  2010-11-21 13:15:49  keinstein
 * merged experimental_tobias
 *
 * Revision 1.1.2.10  2010-07-06 09:06:26  keinstein
 * allow empty input and output devices in routes
 *
 * Revision 1.1.2.9  2010/06/21 14:28:12  keinstein
 * implement deletion of output devices
 *
 * Revision 1.1.2.8  2010/06/15 14:30:14  keinstein
 * allow deleting of input devices in route window
 * several bug fixes
 * rudimentary box deletion support
 *
 * Revision 1.1.2.7  2010/05/07 11:40:28  keinstein
 * actual_settings
 *
 * Revision 1.1.2.6  2010/04/15 09:28:43  keinstein
 * changing routes works, but is not honoured by MIDI, yet
 *
 * Revision 1.1.2.5  2010/03/30 15:57:58  keinstein
 * added editing of existing routes to boxDlg
 *
 * Revision 1.1.2.4  2010/03/30 08:38:27  keinstein
 * added rudimentary command line support
 * changed debug system to allow selection of messages via command line
 * further enhancements to the route dialogs
 *
 * Revision 1.1.2.3  2010/02/15 12:08:21  keinstein
 * intermediate update for backup progress
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
//#include "Defs.h"
//#include "wx/wx.h"
#include "InputDeviceShape.h"
#include "InputMidiDeviceShape.h"
#include "InputMidiFileDeviceShape.h"
#include "InputGuidoFileDeviceShape.h"
#include "DevMidi.h"
#include "BoxChannelShape.h"

//#include "MutApp.h"
//#include "MutIcon.h"
//#include "MutRouteWnd.h"
//#include "InputDevDlg.h"
//#include "Device.h"

#if defined(__WXMAC__) && defined(__WXMAC_CARBON__)
#	include "wx/mac/carbon/private.h"
#endif

IMPLEMENT_DYNAMIC_CLASS(MutInputDeviceShape, MutDeviceShape)

//MutInputDeviceShape::stringmaptype MutInputDeviceShape::stringmap;
wxSizerFlags MutInputDeviceShape::sizerFlags;

bool MutInputDeviceShape:: Create (wxWindow * parent, wxWindowID id, InDevice * d)
{
	device = d;
	if (!d) return false;

	d->setUserData (this);

	DEBUGLOG (other,_T ("Checking icon"));
	wxASSERT(MidiInputDevBitmap.IsOk());
	
	return MutDeviceShape::Create (parent, id, d->GetName());
}

MutInputDeviceShape * MutInputDeviceShape::CreateShape(wxWindow * parent,
						       wxWindowID id,
						       InDevice * d)
{
	DEBUGLOGTYPE(other,MutInputDeviceShape,_T("Creating device shape"));
        wxASSERT (d);
	if (!d) return NULL;

	DEBUGLOGTYPE(other,*d,_T("Device Type"));
	switch (d->GetType()) {
	case DTMidiPort:
		DEBUGLOGTYPE(other,MutInputDeviceShape,
			     _T("Creating MIDI device shape"));
		return new MutInputMidiDeviceShape(parent,id,d);
	case DTMidiFile:
		DEBUGLOGTYPE(other,MutInputDeviceShape,
			     _T("Creating MIDI  file device shape"));
		return new MutInputMidiFileDeviceShape(parent,id,d);
	case DTGis:
		DEBUGLOGTYPE(other,MutInputDeviceShape,
			     _T("Creating MIDI  file device shape"));
		return new MutInputGuidoFileDeviceShape(parent,id,d);
	default:
		return NULL; 
	}
}

MutInputDeviceShape::~MutInputDeviceShape() {
	if (device) {
		wxASSERT (device -> getUserData() == this);
		device -> setUserData (NULL);
	}
}

void MutInputDeviceShape::SetLabel(const wxString & st ) {
	MutDeviceShape::SetLabel(st);
}

void MutInputDeviceShape::RemoveRoute(Route * route) {
	if (!route) return;
	Route * r = getRoutes();
	if (!r) return;

	if (r == route) {
		device->SetRoute(route->GetNext());
		route->SetNext(NULL);
		return;
	}
	
	do {
		if (r->GetNext() == route) {
			r->SetNext(route->GetNext());
			route->SetNext(NULL);
			return;
		}
	} while ((r = r->GetNext()));
	wxASSERT(!r);
}

void MutInputDeviceShape::AddRoute(Route * route)
{
	if (!device) return;
	if (!route) {
		UNREACHABLEC;
		return;
	}
	wxASSERT(!route->GetNext());
	route->SetNext(device->GetRoutes());
	device->SetRoute(route);
}


void MutInputDeviceShape::DoLeftDblClick() {
	InputDevDlg * in = ShowDeviceDialog();
	int Res = in->ShowModal();
	bool destroySelf = false;

	if (Res == wxID_OK) {
		DevType type = in->GetType();

		if (CanHandleType (type)) {
			readDialog (in);
		} else {
			InDevice * indev = InDevice::CreateDevice (type);
			if (indev) {
				MutInputDeviceShape * newdev = 
					MutInputDeviceShape::CreateShape (indev);
				newdev -> readDialog (in);
				destroySelf = replaceSelfBy (newdev);
				m_parent->Layout();
				m_parent->FitInside();
				m_parent->SetVirtualSize(wxDefaultSize);
				m_parent->Refresh();
			}
		}
	} else if (Res == ::wxID_REMOVE) {
		destroySelf = DetachDevice();
	}

	in->Destroy();
	DebugCheckRoutes();
	
	// Signalize to delete this control
	// Unfortunately WXMAC segfaults if we use Destroy(), here.
	if (destroySelf) DeleteSelf();
}

InputDevDlg * MutInputDeviceShape::ShowDeviceDialog() {
	InputDevDlg * in = new InputDevDlg (m_parent);
	int nMidi = rtmidiin->getPortCount();

#ifdef RTMIDI
	nMidi = rtmidiin->getPortCount();

	if ( nMidi )  {
#ifdef __WXMSW__
		wxString portName;
#else
		std::string portName;
#endif

		for (int i = 0; i < nMidi; i++) {
			try {
				portName = rtmidiin->getPortName(i);
#ifdef __WXMSW__
				in->AppendPortChoice(portName);
#else
				in->AppendPortChoice(muT(portName.c_str()));
#endif
			} catch (RtError &error) {
				error.printMessage();
				break;
			}
		}
	} else
		in->AppendPortChoice(_("no device"));
#else
	STUBC;
#endif
	//		in->SetType(DTUnknown);
	in->SetMidiDevice(0);
	in->SetMidiFile(wxEmptyString);
	in->SetGUIDOFile(wxEmptyString);

	InitializeDialog(in);
		
	in->Fit();

	return in;
}

bool MutInputDeviceShape::DetachDevice ()
{
	
	for(Route * route = getRoutes();
	    route; route = getRoutes()) 
	{
		void * p = route->getUserData();
		wxASSERT (wxDynamicCast (p,MutBoxChannelShape));
		MutBoxChannelShape * channel = (MutBoxChannelShape *) p;
		
		wxASSERT (channel->GetInput() == this);
		channel->SetInput (NULL);
		
		RemoveRoute(route);
	}
	
	device->Destroy();
	device = NULL;
	
	wxWindow * parent = m_parent;
	wxSizer * sizer = GetContainingSizer();
	if (sizer) {
		sizer -> Detach(this);
	}
	if (parent) {
		parent->Layout();
		parent->FitInside();
		parent->SetVirtualSize(wxDefaultSize);
		parent->Refresh();
	}
	
	
	return true;
}


bool MutInputDeviceShape::replaceSelfBy (MutInputDeviceShape  * newshape)
{
	wxASSERT (newshape);
	wxASSERT (newshape->device);

	for(Route * route = newshape->device->ReplaceDevice (device);
	    route; route = route->GetNext()) 
	{
		void * p = route->getUserData();
		wxASSERT (wxDynamicCast (p,MutBoxChannelShape));
		MutBoxChannelShape * channel = (MutBoxChannelShape *) p;

		wxASSERT (channel->GetInput() == this);
		channel->SetInput (newshape);

		
	}

	device->Destroy();
	device = NULL;

	newshape->MoveBeforeInTabOrder (this);

	wxSizer * sizer = GetContainingSizer();
	sizer -> Replace (this, newshape, false);

	if (FindFocus()==this) {
		m_parent->Layout();
		m_parent->FitInside();
		m_parent->SetVirtualSize(wxDefaultSize);
		newshape->SetFocus();
	}
	
	Hide();	
	return true;
}

void MutInputDeviceShape::ReadPanel(InputFilterPanel * panel, MutBoxChannelShape * channel)
{
	wxASSERT(panel);
	wxASSERT(channel);
	if (!panel || !channel) return;
	
	bool active = panel->IsShown();
	
	MutInputDeviceShape * newShape = panel->GetCurrentSelection();

	Route * route = channel->GetRoute();
	if (!active) {
		RemoveRoute(route);
		channel->SetInput(NULL);
		return;
	} else if (newShape != this) {
		RemoveRoute(route);
		channel->SetInput(newShape);
		if (newShape)
			newShape->AddRoute(route);
	}
	if (newShape) {
		wxWindow * FilterPanel = panel->GetCurrentDevicePage();
		if (!panel) {
			UNREACHABLEC;
			return;
		}
		newShape->ReadInputFilterPanel(FilterPanel,route);
	}
}



/*
 * \}
 */
