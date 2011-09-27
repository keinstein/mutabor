// -*-C++ -*-
/** \file
 ********************************************************************
 * Input device shape base class for route window.
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/muwx/Routing/InputDeviceShape.cpp,v 1.4 2011/09/27 20:13:24 keinstein Exp $
 * \author Rüdiger Krauße <krausze@mail.berlios.de>,
 * Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 1998
 * $Date: 2011/09/27 20:13:24 $
 * \version $Revision: 1.4 $
 * \license GPL
 *
 * $Log: InputDeviceShape.cpp,v $
 * Revision 1.4  2011/09/27 20:13:24  keinstein
 * * Reworked route editing backend
 * * rewireing is done by RouteClass/GUIRoute now
 * * other classes forward most requests to this pair
 * * many bugfixes
 * * Version change: We are reaching beta phase now
 *
 * Revision 1.3  2011-02-20 22:35:58  keinstein
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
#include "Defs.h"
#include "InputDeviceShape.h"
#include "InputMidiDeviceShape.h"
#include "InputMidiFileDeviceShape.h"
#include "InputGuidoFileDeviceShape.h"
#include "DevMidi.h"
#include "BoxChannelShape.h"
#include "InputDevDlg.h"
#include "muwx/Routing/GUIRoute-inlines.h"
#include "muwx/Routing/BoxDlg.h"
#include "muwx/Routing/DebugRoute.h"

//#include "MutApp.h"
//#include "MutIcon.h"
//#include "MutRouteWnd.h"
//#include "Device.h"

#if defined(__WXMAC__) && defined(__WXMAC_CARBON__)
#	include "wx/mac/carbon/private.h"
#endif

using namespace mutabor;
namespace mutaborGUI {

	IMPLEMENT_DYNAMIC_CLASS(MutInputDeviceShape, MutDeviceShape)

	//MutInputDeviceShape::stringmaptype MutInputDeviceShape::stringmap;
	wxSizerFlags MutInputDeviceShape::sizerFlags;


	MutInputDeviceShape::~MutInputDeviceShape() {
		if (device) {
			ToGUIBase(device).Detatch(this);
		}
	}

	bool MutInputDeviceShape::Create (wxWindow * parent,
					  wxWindowID id, 
					  InputDevice d)
	{
		if (!d) return false;
		
		DEBUGLOG (other,_T ("Checking icon"));
		wxASSERT(MidiInputDevBitmap.IsOk());
		
		bool fine = 
			MutDeviceShape::Create (parent, id, d->GetName());

		if (fine) 
			ToGUIBase(d).Attatch(this);

		return fine;
	}

	void MutInputDeviceShape::SetLabel(const wxString & st ) 
	{
		MutDeviceShape::SetLabel(st);
	}

	/// add a route
	void MutInputDeviceShape::Add(mutabor::InputDevice  dev)
	{
		if (device)
			UNREACHABLEC;
		else 
			device = dev;
	}
	/// replace a dev
	bool MutInputDeviceShape::Replace(mutabor::InputDevice olddev,
						  mutabor::InputDevice newdev) 
	{
		if (device != olddev) {
			UNREACHABLEC;
			return false;
		} else 
			device = newdev;
		return true;
	}
	/// remove a dev
	bool MutInputDeviceShape::Remove(mutabor::InputDevice dev)
	{
		if (device != dev) {
			UNREACHABLEC;
			return false;
		} else 
			device = NULL;
		return true;
	}



#if 0
	void MutInputDeviceShape::RemoveRoute(Route  route) {
		if (!route) return;
		Route  r = getRoutes();
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

	void MutInputDeviceShape::AddRoute(Route  route)
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
#endif


	void MutInputDeviceShape::DoLeftDblClick() {
		/** \todo replace by command handler and emit command event */
		InputDevDlg * in = ShowDeviceDialog();
		int Res = in->ShowModal();
		bool destroySelf = false;
		wxWindow * parent = m_parent; // to be availlable after deleten.

		if (Res == wxID_OK) {
			DevType type = in->GetType();

			if (CanHandleType (type)) {
				readDialog (in);
			} else {
				InputDevice indev = 
					DeviceFactory::CreateInput (type);
				if (indev) {
					MutInputDeviceShape * newdev = 
						GUIDeviceFactory::CreateShape (indev,
									       GetParent());
					
					DEBUGLOG (dialog, _T(""));
					newdev -> readDialog (in);
					DEBUGLOG (dialog, _T(""));
					destroySelf = replaceSelfBy (newdev);
				}
			}
		} else if (Res == ::wxID_REMOVE) {
			device -> Destroy();
		}

		// Now, we may be deleted.

		in->Destroy();
		DebugCheckRoutes();
	
		if (Res != ::wxID_REMOVE) {
			Layout();
			InvalidateBestSize();
			Fit();
			Refresh();
		}
		if (parent) {
			parent->Layout();
			parent->InvalidateBestSize();
			parent->FitInside();
			parent->Refresh();
			parent->Update();
		} else if (Res != ::wxID_REMOVE) Update();
		// Signalize to delete this control
		// Unfortunately WXMAC segfaults if we use Destroy(), here.
		// note: this should not be necessary anymore
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
	
#if 0
		for(Route  route = getRoutes();
		    route; route = getRoutes()) 
		{
			void * p = route->getUserData();
			wxASSERT (wxDynamicCast (p,MutBoxChannelShape));
			MutBoxChannelShape * channel = (MutBoxChannelShape *) p;
		
			wxASSERT (channel->GetInput() == this);
			Detatch (channel);
		}
		device->Destroy();
		device = NULL;
#endif

	
		wxWindow * parent = m_parent;
		wxSizer * sizer = GetContainingSizer();
		Hide();
		if (sizer) {
			sizer -> Detach(this);
		}

		if (parent) {
			parent->Layout();
			parent->FitInside();
			parent->SetVirtualSize(wxDefaultSize);
			parent->Refresh();
		}
		device->Destroy();

		return true;
	}


	bool MutInputDeviceShape::replaceSelfBy (MutInputDeviceShape  * newshape)
	{
		/** \todo transfer this function to GUIRoute */
		
		wxASSERT (newshape);
		wxASSERT (newshape->device);

		DEBUGLOG (routing, _T(""));
	
		
		if (device) // might be zero as in MutNewInputDeviceShape
			device->MoveRoutes(newshape->GetDevice());
/*
		for(MutBoxChannelShapeList::iterator i = routes.begin();
		    i != routes.end();
		    i++)
		{
			if (!((*i)->Reconnect(this,newshape))) return false;
		}
*/


		DEBUGLOG (routing, _T(""));
       
		newshape->MoveBeforeInTabOrder (this);

		wxSizer * sizer = GetContainingSizer();
		sizer -> Replace (this, newshape, false);

		Hide();	
		m_parent->Layout();
		m_parent->FitInside();
		m_parent->SetVirtualSize(wxDefaultSize);
		newshape->SetFocus();

		device->Destroy();
		device = NULL;
		return true;
	}

	void MutInputDeviceShape::ReadPanel(InputFilterPanel * panel, 
					    MutBoxChannelShape * channel)
	{
		wxASSERT(panel);
		wxASSERT(channel);
		if (!panel || !channel) return;
	
		bool active = panel->IsShown();
	
		MutInputDeviceShape * newShape = panel->GetCurrentSelection();

		Route  route = channel->GetRoute();
		if (!active) {
			Detatch(route);
			return;
		} else if (newShape != this) {
			channel->Reconnect(this,newShape);
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

}

/*
 * \}
 */
