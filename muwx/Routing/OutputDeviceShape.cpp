// -*-C++ -*-

/** \file
 ********************************************************************
 * Output device shape for route window.
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/muwx/Routing/OutputDeviceShape.cpp,v 1.6 2011/10/02 16:58:42 keinstein Exp $
 * \author Rüdiger Krauße <krausze@mail.berlios.de>,
 * Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 1998
 * $Date: 2011/10/02 16:58:42 $
 * \version $Revision: 1.6 $
 * \license GPL
 *
 * $Log: OutputDeviceShape.cpp,v $
 * Revision 1.6  2011/10/02 16:58:42  keinstein
 * * generate Class debug information when compile in debug mode
 * * InputDeviceClass::Destroy() prevented RouteClass::Destroy() from clearing references -- fixed.
 * * Reenable confirmation dialog when closing document while the logic is active
 * * Change debug flag management to be more debugger friendly
 * * implement automatic route/device deletion check
 * * new debug flag --debug-trace
 * * generate lots of tracing output
 *
 * Revision 1.5  2011-09-30 18:07:06  keinstein
 * * make compile on windows
 * * s/wxASSERT/mutASSERT/g to get assert handler completely removed
 * * add ax_boost_base for boost detection
 *
 * Revision 1.4  2011-09-27 20:13:25  keinstein
 * * Reworked route editing backend
 * * rewireing is done by RouteClass/GUIRoute now
 * * other classes forward most requests to this pair
 * * many bugfixes
 * * Version change: We are reaching beta phase now
 *
 * Revision 1.3  2011-02-20 22:35:59  keinstein
 * updated license information; some file headers have to be revised, though
 *
 * Revision 1.2  2010-11-21 13:15:49  keinstein
 * merged experimental_tobias
 *
 * Revision 1.1.2.14  2010-11-18 21:46:14  keinstein
 * MutFrame: get rid of OnIdle (this may break something, but saves much more CPU cycles
 * Some further steps to get rid of EDevice*
 *
 * Revision 1.1.2.13  2010-07-06 09:06:26  keinstein
 * allow empty input and output devices in routes
 *
 * Revision 1.1.2.12  2010/06/22 15:05:45  keinstein
 * debugging segfault in route check after replacement of MutOutputDevice
 *
 * Revision 1.1.2.11  2010/06/21 14:28:12  keinstein
 * implement deletion of output devices
 *
 * Revision 1.1.2.10  2010/05/07 11:40:28  keinstein
 * actual_settings
 *
 * Revision 1.1.2.9  2010/04/20 17:41:38  keinstein
 * One step towards using Mutabor: Activation of a logic now honours the state of the Device Editor.
 *
 * Revision 1.1.2.8  2010/04/15 09:28:43  keinstein
 * changing routes works, but is not honoured by MIDI, yet
 *
 * Revision 1.1.2.7  2010/03/30 08:38:27  keinstein
 * added rudimentary command line support
 * changed debug system to allow selection of messages via command line
 * further enhancements to the route dialogs
 *
 * Revision 1.1.2.6  2010/02/22 10:14:02  keinstein
 * transfer files to other computer
 *
 * Revision 1.1.2.5  2010/02/15 12:08:21  keinstein
 * intermediate update for backup progress
 *
 * Revision 1.1.2.4  2010/01/14 18:14:20  keinstein
 * fix usage of installation prefix
 * MutInputDeviceShape/MutOutputDeviceShape:
 *     use GetType for type checking in OnChoiceSelected
 *     make InitalizeDialog const
 * MutNewOutputDeviceShape: add InitializeDialog and ReplaceSelfBy
 *
 * Revision 1.1.2.3  2010/01/14 09:34:24  keinstein
 * Checkin searching for a bug
 *
 * Revision 1.1.2.2  2010/01/11 12:51:52  keinstein
 * fix some problems due to splitting MutRouteShapes.{cpp,h}
 *
 * Revision 1.1.2.1  2009/11/30 12:08:57  keinstein
 * split MutRouteShapes into several files into directory Routing
 *
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
#include "OutputDeviceShape.h"
#include "OutputMidiDeviceShape.h"
#include "OutputMidiFileDeviceShape.h"
#include "OutputGuidoFileDeviceShape.h"
#include "BoxChannelShape.h"
#include "DevMidi.h"
#include "muwx/Routing/GUIRoute-inlines.h"
#include "muwx/Routing/DebugRoute.h"
#include "muwx/Routing/BoxDlg.h"

#if defined(__WXMAC__) && defined(__WXMAC_CARBON__)
#	include "wx/mac/carbon/private.h"
#endif

using namespace mutabor;

namespace mutaborGUI {

	IMPLEMENT_ABSTRACT_CLASS(MutOutputDeviceShape, MutDeviceShape)
	//MutOutputDeviceShape::stringmaptype MutOutputDeviceShape::stringmap;
	wxSizerFlags MutOutputDeviceShape::sizerFlags;

	bool MutOutputDeviceShape:: Create (wxWindow * parent, wxWindowID id, OutputDevice d)
	{
		if (!d) return false;

		DEBUGLOG (other,_T ("Checking icon"));
		mutASSERT(MidiOutputDevBitmap.IsOk());

		bool fine =  MutDeviceShape::Create (parent, id, d->GetName());

		if (fine)
			ToGUIBase(d).Attatch(this);

		return fine;
	}

#if 0
	MutOutputDeviceShape * MutOutputDeviceShape::CreateShape(wxWindow * parent,
								 wxWindowID id,
								 OutputDevice d)
	{
		DEBUGLOGTYPE(routing,MutOutputDeviceShape,_T("Creating device shape"));
		mutASSERT (d);
		if (!d) return NULL;

		DEBUGLOGTYPE(routing,*d,_T("Device Type for device %p"), d.get());
		switch (d->GetType()) {
		case DTMidiPort:
			DEBUGLOGTYPE(routing,MutOutputDeviceShape,
				     _T("Creating MIDI device shape"));
			return new MutOutputMidiDeviceShape(parent,id,d);
		case DTMidiFile:
			DEBUGLOGTYPE(routing,MutOutputDeviceShape,
				     _T("Creating MIDI  file device shape"));
			return new MutOutputMidiFileDeviceShape(parent,id,d);
		case DTGis:
			DEBUGLOGTYPE(routing,MutOutputDeviceShape,
				     _T("Creating MIDI  file device shape"));
			return new MutOutputGuidoFileDeviceShape(parent,id,d);
		default:
			return NULL; 
		}
	}
#endif
	void MutOutputDeviceShape::SetLabel(const wxString & st ) 
	{
		MutDeviceShape::SetLabel(st);
	}

	/// add a route
	void MutOutputDeviceShape::Add(mutabor::OutputDevice  dev)
	{
		if (device)
			UNREACHABLEC;
		else 
			device = dev;
	}
	/// replace a dev
	bool MutOutputDeviceShape::Replace(mutabor::OutputDevice olddev,
						  mutabor::OutputDevice newdev) 
	{
		if (device != olddev) {
			UNREACHABLEC;
			return false;
		} else 
			device = newdev;
		return true;
	}
	/// remove a dev
	bool MutOutputDeviceShape::Remove(mutabor::OutputDevice dev)
	{
		if (device != dev) {
			UNREACHABLEC;
			return false;
		} else 
			device = NULL;
		return true;
	}
#if 0
	void MutOutputDeviceShape::Connect(Route & route) 
	{

		mutASSERT(route);
		mutASSERT(device);
		mutASSERT(route->GetOutputDevice() == device);
		MutBoxChannelShape * channel = (MutBoxChannelShape *) route->getUserData();
		mutASSERT(dynamic_cast<MutIconShape *>(channel));

		// Check for duplicate route insertion.
		for (MutBoxChannelShapeList::const_iterator i = routes.begin() ; i != routes.end() ; i++) {
			if ((*i)->GetRoute() == route) {
				UNREACHABLEC; // maybe just STUB?
				return;
			}
		}

		if (channel) {
			mutASSERT(channel->GetRoute()==route);
			channel->SetOutput(this);
			routes.push_back(channel);
		}
	}

	void MutOutputDeviceShape::Disconnect(Route & route)
	{
		mutASSERT(route);
		MutBoxChannelShape * channel = (MutBoxChannelShape *)route->getUserData();
		mutASSERT(dynamic_cast<MutBoxChannelShape *>(channel));
		mutASSERT(channel->GetRoute() == route);
		mutASSERT(channel->GetOutput() == this);
	
		channel->SetOutput(NULL, channel->GetOutput()==this);
		MutBoxChannelShapeList::iterator i;
		for (i = routes.begin(); i != routes.end(); i++) if (*i == channel) break;
//	if (i == routes.end()) return;
		routes.erase(i);
	}

	void MutOutputDeviceShape::Disconnect(MutBoxChannelShape * route) {
		mutASSERT(route->GetRoute()->getUserData() == route);
		RemoveRoute(route->GetRoute());
	}

	void MutOutputDeviceShape::AddRoute(Route & route) 
	{
		mutASSERT(route);
		mutASSERT(device);
		mutASSERT(route->GetOutputDevice() == device);
		MutBoxChannelShape * channel = (MutBoxChannelShape *) route->getUserData();
		mutASSERT(dynamic_cast<MutIconShape *>(channel));

		// Check for duplicate route insertion.
		for (MutBoxChannelShapeList::const_iterator i = routes.begin() ; i != routes.end() ; i++) {
			if ((*i)->GetRoute() == route) {
				UNREACHABLEC; // maybe just STUB?
				return;
			}
		}

		if (channel) {
			mutASSERT(channel->GetRoute()==route);
			channel->SetOutput(this);
			routes.push_back(channel);
		}
	}

	void MutOutputDeviceShape::RemoveRoute(Route & route)
	{
		mutASSERT(route);
		MutBoxChannelShape * channel = (MutBoxChannelShape *)route->getUserData();
		mutASSERT(dynamic_cast<MutBoxChannelShape *>(channel));
		mutASSERT(channel->GetRoute() == route);
		mutASSERT(channel->GetOutput() == this);
	
		channel->SetOutput(NULL, channel->GetOutput()==this);
		MutBoxChannelShapeList::iterator i;
		for (i = routes.begin(); i != routes.end(); i++) if (*i == channel) break;
//	if (i == routes.end()) return;
		routes.erase(i);
	}

#endif

	void MutOutputDeviceShape::DoLeftDblClick() 
	{
		OutputDevDlg * out = ShowDeviceDialog();
		int Res = out->ShowModal();
		bool destroySelf = false;
		wxWindow * parent = m_parent; // to be availlable after deleten.

		if (Res == wxID_OK) {
			DevType type = out->GetType();

			if (CanHandleType (type)) {
				readDialog (out);
			} else {
				OutputDevice outdev = DeviceFactory::CreateOutput (type);
				if (outdev) {
					MutOutputDeviceShape * newdev = 
						GUIDeviceFactory::CreateShape (outdev,
									       GetParent());
					DEBUGLOG (dialog, _T(""));
 					newdev -> readDialog (out);
					DEBUGLOG (dialog, _T(""));
					destroySelf = replaceSelfBy (newdev);
				}
			}
		} else if (Res == ::wxID_REMOVE) {
			device->Destroy();
		}

		// Now, we may be deleted.

		out->Destroy();
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
		if (destroySelf) DeleteSelf();
	}

	OutputDevDlg * MutOutputDeviceShape::ShowDeviceDialog() 
	{
		OutputDevDlg * out = new OutputDevDlg (m_parent);
		int nMidi = rtmidiout->getPortCount();
		DEBUGLOG (other, _T("Midi ports %d"),nMidi);

#ifdef RTMIDI
		nMidi = rtmidiout->getPortCount();

		if ( nMidi )  {
#ifdef __WXMSW__
			wxString portName;
#else
			std::string portName;
#endif

			for (int i = 0; i < nMidi; i++) {
				try {
					portName = rtmidiout->getPortName(i);
				} catch (RtError &error) {
					error.printMessage();
					break;
				}
#ifdef __WXMSW__
				out->AppendPortChoice(portName);
#else
				out->AppendPortChoice(muT(portName.c_str()));
#endif
			}
		} else
			out->AppendPortChoice(_("no device"));
#else
		/*    nMidi = midiInGetNumDevs();
		      if ( nMidi )
		      {
		      for (int i = 0; i < nMidi; i++)
		      {
		      MIDIINCAPS miin;
		      midiInGetDevCaps(i, &miin, sizeof(MIDIINCAPS));
		      DataR0.Device.AddString(miin.szPname);
		      }
		      }
		      else
		      DataR0.Device.AddString("no device");*/
#endif
		//		in->SetType(DTUnknown);
		out->SetMidiDevice(0);
		out->SetMidiFile(wxEmptyString);
		out->SetGUIDOFile(wxEmptyString);
		out->SetMidiBendingRange(2);
		out->SetMidiFileBendingRange(2);

		InitializeDialog(out);
		
		out->Fit();

		return out;
	}

	bool MutOutputDeviceShape::DetachDevice ()
	{
	
		for (MutBoxChannelShapeList::iterator i = routes.begin(); i!= routes.end(); i = routes.begin()) {
			MutBoxChannelShape *channel = *i;
			mutASSERT(channel);
			Detatch(channel);
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

	bool MutOutputDeviceShape::replaceSelfBy (MutOutputDeviceShape  * newshape)
	{
		mutASSERT (newshape);
		mutASSERT (newshape->device);

		DEBUGLOG (routing, _T(""));
	
		for(MutBoxChannelShapeList::iterator i = routes.begin(); i!=routes.end(); i = routes.begin())
		{
			DEBUGLOG (routing, _T("this = %p ; newshape = %p ; device = %p ; newshape->device = %p ; boxchannel = %p"),
				  this,newshape,device.get(), newshape->device.get(), (*i));
			MutBoxChannelShape * channel = *i;
			mutASSERT(channel->GetRoute()->GetOutputDevice() == device);
			channel->Reconnect(this,newshape);
		}

		DEBUGLOG (routing, _T(""));
       
		newshape->MoveBeforeInTabOrder (this);

		wxSizer * sizer = GetContainingSizer();
		sizer -> Replace (this, newshape, false);
	
  		Hide();
		m_parent->Layout();
		m_parent->FitInside();
		m_parent->SetVirtualSize(wxDefaultSize);
		newshape->SetFocus();

		device -> Destroy();
		device = NULL;
		return true;
	}

	void MutOutputDeviceShape::ReadPanel(OutputFilterPanel * panel, MutBoxChannelShape * channel)
	{
		mutASSERT(panel);
		mutASSERT(channel);
		if (!panel || !channel) return;
		DEBUGLOG(dialog,_T("Reading output device dialog"));
	
		bool active = panel->IsShown();
	
		// newShape may be NULL if the route ends at the box
		MutOutputDeviceShape * newShape = panel->GetCurrentSelection();
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
			newShape->ReadOutputFilterPanel(FilterPanel,route);
		}
	
	}
}

/*
 * \}
 */
