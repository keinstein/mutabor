// -*-C++ -*-

/** \file
 ********************************************************************
 * Output device shape for route window.
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/src/wxGUI/Routing/OutputDeviceShape.cpp,v 1.12 2012/01/29 22:08:36 keinstein Exp $
 * \author Rüdiger Krauße <krausze@mail.berlios.de>,
 * Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 1998
 * $Date: 2012/01/29 22:08:36 $
 * \version $Revision: 1.12 $
 * \license GPL
 *
 *
 *
 ********************************************************************
 *\addtogroup route
 *\{
 ********************************************************************/
#include "src/wxGUI/Routing/OutputDeviceShape.h"
#include "src/wxGUI/Routing/OutputMidiDeviceShape.h"
#include "src/wxGUI/Routing/OutputMidiFileDeviceShape.h"
#include "src/wxGUI/Routing/OutputGuidoFileDeviceShape.h"
#include "src/wxGUI/Routing/BoxChannelShape.h"
#include "src/kernel/routing/midi/DevMidi.h"
#include "src/kernel/routing/Route-inlines.h"
#include "src/wxGUI/Routing/GUIRoute-inlines.h"
#include "src/wxGUI/Routing/DebugRoute.h"
#include "src/wxGUI/Routing/BoxDlg.h"

#if defined(__WXMAC__) && defined(__WXMAC_CARBON__)
#	include "wx/mac/carbon/private.h"
#endif

using namespace mutabor;

namespace mutaborGUI {

	IMPLEMENT_ABSTRACT_CLASS(MutOutputDeviceShape, MutDeviceShape)
	//MutOutputDeviceShape::stringmaptype MutOutputDeviceShape::stringmap;
	wxSizerFlags MutOutputDeviceShape::sizerFlags;
	MutOutputDeviceShape::~MutOutputDeviceShape() {
		if (device) {
			disconnect(device,const_cast<MutOutputDeviceShape *>(this));
		}
		DEBUGLOG(other, _T("Deleting."));
	}

	bool MutOutputDeviceShape:: Create (wxWindow * parent, wxWindowID id, OutputDevice & d)
	{
		if (!d) return false;

		DEBUGLOG (other,_T ("Checking icon"));
		mutASSERT(MidiOutputDevBitmap.IsOk());

		bool fine =  MutDeviceShape::Create (parent, id, d->GetName());

		if (fine)
			connect(d,this);

		return fine;
	}

#if 0
	MutOutputDeviceShape * MutOutputDeviceShape::CreateShape(wxWindow * parent,
								 wxWindowID id,
								 OutputDevice & d)
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
			} else if (type != DTNotSet) {
				OutputDevice outdev = DeviceFactory::CreateOutput (type);
				if (outdev) {
					MutOutputDeviceShape * newdev = 
						GUIDeviceFactory::CreateShape (outdev,
									       GetParent());
					if (! newdev) {
						UNREACHABLEC;
						return;
					}
					TRACEC;
					newdev -> readDialog (out);
					TRACEC;
					destroySelf = replaceSelfBy (newdev);
				}
			}
		} else if (Res == ::wxID_REMOVE) {
			device->Destroy();
		}

		// Now, we may be deleted.

		out->Destroy();
		DebugCheckRoutes();

		if (Res != ::wxID_REMOVE && !destroySelf) {
			Layout();
			InvalidateBestSize();
			Fit();
			Refresh();
		}
		if (parent) {
			parent->InvalidateBestSize();
			parent->Layout();
			parent->FitInside();
			parent->Refresh();
			parent->Update();
		} else if (Res != ::wxID_REMOVE && !destroySelf) Update();
		// Signalize to delete this control
		// Unfortunately WXMAC segfaults if we use Destroy(), here.
		// if (destroySelf) Destroy();
	}

	OutputDevDlg * MutOutputDeviceShape::ShowDeviceDialog() 
	{
		OutputDevDlg * out = new OutputDevDlg (m_parent);
		int nMidi;

#ifdef RTMIDI
		nMidi = (rtmidiout?rtmidiout->getPortCount():0);

		DEBUGLOG (other, _T("Midi ports %d"),nMidi);
		if ( nMidi )  {
			wxString portName;

			for (int i = 0; i < nMidi; i++) {
				try {
					portName = muT(rtmidiout->getPortName(i).c_str());
				} catch (RtError &error) {
					error.printMessage();
					break;
				}
				out->AppendPortChoice(portName);
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
			disconnect(channel,this);
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

		TRACEC;
	
		for(MutBoxChannelShapeList::iterator i = routes.begin(); i!=routes.end(); i = routes.begin())
		{
			DEBUGLOG (routing, _T("this = %p ; newshape = %p ; device = %p ; newshape->device = %p ; boxchannel = %p"),
				  (void*)this,
				  (void*)newshape,
				  (void*)device.get(), 
				  (void*)newshape->device.get(), 
				  (void*)(*i));
			MutBoxChannelShape * channel = *i;
			mutASSERT(channel->GetRoute()->GetOutputDevice() == device);
			reconnect(channel,this,newshape);
		}

		TRACE;
       
		newshape->MoveBeforeInTabOrder (this);

		wxSizer * sizer = GetContainingSizer();
		sizer -> Replace (this, newshape, false);
	
  		Hide();
		wxWindow * parent = m_parent;
		parent->RemoveChild(this);
		parent->Layout();
		parent->FitInside();
		parent->SetVirtualSize(wxDefaultSize);
		newshape->SetFocus();

		device -> Destroy();
		// at this point even “this” is invalid.
		//		device = NULL;
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
			disconnect(channel,this);
			return;
		} else if (newShape != this) {
			reconnect(channel,this,newShape);
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
