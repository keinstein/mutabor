// -*-C++ -*-
/** \file
 ********************************************************************
 * Input device shape base class for route window.
 *
 * Copyright:   (c) 2011 TU Dresden
 *              (c) 2013 Tobias Schlemmer (changes after 2011-11-01)
 * \author Rüdiger Krauße <krausze@mail.berlios.de>,
 * Tobias Schlemmer <keinstein@users.berlios.de>
 * \license GPL
 *
 *    This program is free software; you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation; either version 2 of the License, or
 *    (at your option) any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this program; if not, write to the Free Software
 *    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *
 ********************************************************************
 *\addtogroup route
 *\{
 ********************************************************************/
#if 0
#include "src/kernel/Defs.h"
#include "src/wxGUI/Routing/BoxChannelShape.h"
#include "src/wxGUI/Routing/BoxShape.h"
#include "src/wxGUI/Routing/InputDeviceShape.h"
#include "src/wxGUI/Routing/InputMidiDeviceShape.h"
#include "src/wxGUI/Routing/InputMidiFileDeviceShape.h"
#include "src/wxGUI/Routing/InputGuidoFileDeviceShape.h"
#include "src/kernel/routing/midi/DevMidi.h"
#include "src/wxGUI/Routing/InputDevDlg.h"
#include "src/wxGUI/Routing/GUIRoute-inlines.h"
#include "src/wxGUI/Routing/BoxDlg.h"
#include "src/wxGUI/Routing/DebugRoute.h"
#include "src/wxGUI/MutFrame.h"

#include "src/kernel/routing/Route-inlines.h"


#if defined(__WXMAC__) && defined(__WXMAC_CARBON__)
#	include "wx/mac/carbon/private.h"
#endif

using namespace mutabor;
namespace mutaborGUI {

	IMPLEMENT_DYNAMIC_CLASS(MutInputDeviceShape, MutDeviceShape)

	//MutInputDeviceShape::stringmaptype MutInputDeviceShape::stringmap;
	wxSizerFlags MutInputDeviceShape::sizerFlags;


	MutInputDeviceShape::~MutInputDeviceShape() {
		TRACEC;
		if (device) {
			disconnect(device,this);
			TRACEC;
		}
		TRACEC;
	}

	bool MutInputDeviceShape::Create (wxWindow * parent,
					  wxWindowID id, 
					  InputDevice & d)
	{
		if (!d) return false;
		
		DEBUGLOG (other,_T ("Checking icon"));
		mutASSERT(MidiInputDevBitmap.IsOk());
		
		TRACEC;

		bool fine = 
			MutDeviceShape::Create (parent, id, d->GetName());

		TRACEC;
		if (fine) 
			connect(d,this);

		TRACEC;
		return fine;
	}

	void MutInputDeviceShape::SetLabel(const wxString & st ) 
	{
		MutDeviceShape::SetLabel(st);
	}

	/// add a route
	void MutInputDeviceShape::Add(mutabor::InputDeviceClass * dev)
	{
		TRACEC;
		if (device)
			UNREACHABLEC;
		else 
			device = dev;
		TRACEC;
	}
	/// replace a dev
	bool MutInputDeviceShape::Replace(mutabor::InputDevice & olddev,
					  mutabor::InputDevice & newdev) 
	{
		TRACEC;
		if (device != olddev) {
			UNREACHABLEC;
			return false;
		} else 
			device = newdev;
		TRACEC;
		return true;
	}
	/// remove a dev
	bool MutInputDeviceShape::Remove(mutabor::InputDeviceClass * dev)
	{
		TRACEC;
		if (device != dev) {
			UNREACHABLEC;
			return false;
		} else 
			device = NULL;
		TRACEC;
		return true;
	}

	void MutInputDeviceShape::DoLeftDblClick() {
		/** \todo replace by command handler and emit command event */
		TRACEC;
		InputDevDlg * in = ShowDeviceDialog();
		int Res = in->ShowModal();
		TRACEC;
		bool destroySelf = false;
		wxWindow * parent = m_parent; // to be availlable after deleten.

		TRACEC;
		if (Res == wxID_OK) {
			DevType type = in->GetType();

			if (CanHandleType (type)) {
				TRACEC;
				readDialog (in);
			} else if (type != DTNotSet) { // assure type is set.
				TRACEC;
				InputDevice indev = 
					DeviceFactory::CreateInput (type);
				if (indev) {
					TRACEC;
					MutInputDeviceShape * newdev = 
						GUIDeviceFactory::CreateShape (indev,
									       GetParent());
					
					if (! newdev) {
					  UNREACHABLEC;
					  return;
					}
					mutASSERT(newdev->device);
					TRACEC;
					newdev -> readDialog (in);
					if (LogicOn && !(newdev->device->IsOpen())) 
						newdev->device->Open();

					TRACEC;
					destroySelf = replaceSelfBy (newdev);
				}
			}
		} else if (Res == ::wxID_REMOVE) {
			TRACEC;
			device -> Destroy();
		}

		// Now, we may be deleted.

		in->Destroy();
		DebugCheckRoutes();
		TRACEC;

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
		// note: this should not be necessary anymore
		// yes: it crashes on Windows
		// if (destroySelf) Destroy();
		TRACE;
	}

	InputDevDlg * MutInputDeviceShape::ShowDeviceDialog() {
		InputDevDlg * in = new InputDevDlg (m_parent);
		int nMidi;

#ifdef RTMIDI
		nMidi = (rtmidiin?rtmidiin->getPortCount():0);

		if ( nMidi )  {
			wxString portName;

			for (int i = 0; i < nMidi; i++) {
				try {
					portName = muT(rtmidiin->getPortName(i).c_str());
					in->AppendPortChoice(portName);
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

	void MoveDevice(int count) {
		if (device) {
			device->move_in_list(count);
		}
	}
	
	bool MutInputDeviceShape::DetachDevice ()
	{
	
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
		TRACEC;
		device->Destroy();
		TRACEC;

		return true;
	}


	bool MutInputDeviceShape::replaceSelfBy (MutInputDeviceShape  * newshape)
	{
		/** \todo transfer this function to GUIRoute */
		
		mutASSERT (newshape);
		mutASSERT (newshape->device);

		TRACEC;
		if (device) // might be zero as in MutNewInputDeviceShape
			device->MoveRoutes(newshape->GetDevice());
		TRACEC;


		newshape->MoveBeforeInTabOrder (this);

		wxSizer * sizer = GetContainingSizer();
		sizer -> Replace (this, newshape, false);

		newshape->SetFocus();
		Hide();	
		wxWindow * parent = m_parent;
		parent->RemoveChild(this);
		parent->Layout();
		parent->FitInside();
		parent->SetVirtualSize(wxDefaultSize);

		TRACEC;
		device->Destroy();
		// at this moment this points to invalid memory
		TRACET(MutInputDeviceShape);
		return true;
	}

	void MutInputDeviceShape::ReadPanel(InputFilterPanel * panel, 
					    MutBoxChannelShape * channel)
	{
		mutASSERT(panel);
		mutASSERT(channel);
		if (!panel || !channel) return;
	
		bool active = panel->IsShown();
	
		MutInputDeviceShape * newShape = panel->GetCurrentSelection();

		Route & route = channel->GetRoute();
		if (!active) {
			TRACEC;
			disconnect(channel,this);
			TRACEC;
			return;
		} else if (newShape != this) {
			TRACEC;
			reconnect(channel,this,newShape);
			TRACEC;
		}
		if (newShape) {
			wxWindow * FilterPanel = panel->GetCurrentDevicePage();
			if (!panel) {
				UNREACHABLEC;
				return;
			}
			TRACEC;
			newShape->ReadInputFilterPanel(FilterPanel,route);
		}
		TRACEC;
	}

}
#endif
/*
 * \}
 */
