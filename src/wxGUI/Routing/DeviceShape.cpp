// -*-C++ -*-
/** \file
********************************************************************
* Device shape base class for route window.
*
* \author Rüdiger Krauße,
* Tobias Schlemmer <keinstein@users.sourceforge.net>
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
*\addtogroup GUIroute
*\{
********************************************************************/
#include "src/kernel/Defs.h"
#include "src/kernel/error.h"
#include "src/wxGUI/MutFrame.h"
#include "src/wxGUI/Routing/GUIRoute.h"
#include "src/wxGUI/Routing/DeviceShape.h"
#include "src/wxGUI/Routing/RouteIcons.h"
#include "src/wxGUI/Routing/DebugRoute.h"
#include "src/wxGUI/Routing/BoxChannelShape.h"
#include "src/wxGUI/Routing/BoxDlg.h"
#include "src/wxGUI/Routing/InputDevDlg.h"
#include "src/wxGUI/Routing/OutputDevDlg.h"
#include "src/wxGUI/Routing/GUIRoute-inlines.h"
#include <algorithm>
#include "wx/defs.h"
#include "wx/bmpbuttn.h"
#include "wx/msgdlg.h"
//#include "MutApp.h"
//#include "MutIcon.h"
//#include "MutRouteWnd.h"
//#include "InputDevDlg.h"
//#include "Device.h"



// common part of the macros below
#define wxIMPLEMENT_CLASS_COMMON_TEMPLATE1(name, basename, baseclsinfo2, func, T1) \
	template<>							\
	wxClassInfo name<T1>::ms_classInfo(wxT(#name "<" #T1 ">"),	\
					   &basename::ms_classInfo,	\
					   baseclsinfo2,		\
					   (int) sizeof(name<T1>),	\
					   (wxObjectConstructorFn) func); \
	template<>							\
	wxClassInfo *name<T1>::GetClassInfo() const			\
        { return &name<T1>::ms_classInfo; }

#define wxIMPLEMENT_CLASS_COMMON1_TEMPLATE1(name, basename, func, T1)	\
	wxIMPLEMENT_CLASS_COMMON_TEMPLATE1(name, basename, NULL, func, T1)


// Single inheritance with one base class

#define IMPLEMENT_ABSTRACT_CLASS_TEMPLATE1(name, basename, T1)		\
	wxIMPLEMENT_CLASS_COMMON1_TEMPLATE1(name, basename, NULL, T1)


// Single inheritance with one base class
#define IMPLEMENT_DYNAMIC_CLASS_TEMPLATE1(name, basename, T1)		\
	template<>							\
	wxObject* name<T1>::wxCreateObject()				\
        { return new name<T1>; }					\
	wxIMPLEMENT_CLASS_COMMON1_TEMPLATE1(name, basename,		\
					    name<T1>::wxCreateObject, T1)

using namespace mutaborGUI;

using namespace mutabor;




BEGIN_EVENT_TABLE_TEMPLATE1(MutDeviceShape, MutIconShape, T)
EVT_KEY_DOWN(MutDeviceShape::OnKeyDown)
EVT_LEFT_DCLICK(MutDeviceShape::LeftDblClickEvent)
EVT_MENU(CM_MOVE_UP, MutDeviceShape::CmMoveIcon)
EVT_MENU(CM_MOVE_DOWN, MutDeviceShape::CmMoveIcon)
EVT_MENU(CM_DEVICE_STATE_CHANGED, MutDeviceShape::CmDeviceNotification)
EVT_BUTTON(CM_PLAYDEVICE, MutDeviceShape::PlayButtonPressed)
EVT_BUTTON(CM_PAUSEDEVICE, MutDeviceShape::PlayButtonPressed)
EVT_BUTTON(CM_STOPDEVICE, MutDeviceShape::PlayButtonPressed)
END_EVENT_TABLE()

MUTABOR_NAMESPACE(mutaborGUI)


template<class T>
MutDeviceShape<T>::~MutDeviceShape() {
	TRACEC;
	if (device) {
		try {
			disconnect(device,this);
			TRACEC;
		} catch (const mutabor::error::unreachable_exception & e) {
			mutabor::unhandled_exception_handler();
		}
	}
	if (playbuttons) delete playbuttons;
	TRACEC;
}
template<class T>
bool MutDeviceShape<T>::Create (wxWindow * parent,
				wxWindowID id,
				devicetype & d)
{
	if (!d) return false;

	DEBUGLOG (other, ("Checking icon"));
	mutASSERT(MidiInputDevBitmap.IsOk());
	mutASSERT(MidiOutputDevBitmap.IsOk());

	TRACEC;

	bool fine =
		Create (parent, id, d->GetName());

	TRACEC;
	if (fine)
		connect(d,this);

	TRACEC;
	return fine;
}


template<class T>
void MutDeviceShape<T>::Add(MutBoxChannelShape *  route)
{
#ifdef DEBUG
	MutBoxChannelShapeList::iterator pos =
		std::find(routes.begin(),routes.end(),route);
	mutASSERT(pos == routes.end());
#endif
	routes.push_back(route);
	//		ClearPerimeterPoints();
	Refresh();
	Update();
}

template<class T>
bool MutDeviceShape<T>::Replace(MutBoxChannelShape * oldroute,
				MutBoxChannelShape * newroute)
{
#ifdef DEBUG
	MutBoxChannelShapeList::iterator pos =
		std::find(routes.begin(),routes.end(),oldroute);
	mutASSERT(pos != routes.end());
#endif
	bool retval = Remove(oldroute);
	Add(newroute);
	Recompute();
	return retval;
}

template<class T>
bool MutDeviceShape<T>::Remove(MutBoxChannelShape * route)
{
	MutBoxChannelShapeList::iterator pos =
		std::find(routes.begin(),routes.end(),route);
	if (pos == routes.end()) {
		UNREACHABLEC;
		return false;
	} else {
		routes.erase(pos);
	}
	Recompute();
	return true;
}

template<class T>
bool MutDeviceShape<T>::MoveRoutes (MutDeviceShape * newclass)
{
	routes.swap(newclass->routes);
	Recompute();
	return true;
}

template<class T>
bool MutDeviceShape<T>::Recompute()
{
	//		ClearPerimeterPoints();
	SetIcon(GetMutIcon());
	//  SetLabel (filename.GetFullName());
	return GetIcon().IsOk();
}



template<class T>
void MutDeviceShape<T>::ReadPanel(FilterPanel * panel,
				  MutBoxChannelShape * channel)
{
	mutASSERT(panel);
	mutASSERT(channel);
	if (!panel || !channel) return;

	bool active = panel->IsShown();

	thistype * newShape = panel->GetCurrentSelection();

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
		wxWindow * subpanel = panel->GetCurrentDevicePage();
		if (!panel) {
			UNREACHABLEC;
			return;
		}
		TRACEC;
		newShape->ReadFilterPanel(subpanel,route);
	}
	TRACEC;
}


template<class T>
void MutDeviceShape<T>::OnKeyDown (wxKeyEvent & event) {
	if (event.HasModifiers()) {
		event.Skip();
		return;
	}

	/* Other inspirations:
	   case WXK_DELETE:
	   // cursor keys
	   */
	switch (event.GetKeyCode()) {
	case WXK_NUMPAD_ENTER:
	case WXK_RETURN:
	case WXK_SPACE:
	case WXK_NUMPAD_SPACE:
	case WXK_NUMPAD_ADD:
	case WXK_ADD:
	case WXK_WINDOWS_MENU:
	case WXK_MENU:
		{
			wxCommandEvent command(wxEVT_COMMAND_MENU_SELECTED,
					       CM_LEFT_DOUBLE_CLICK);
			wxPostEvent(this,command);
			return;
		}
	default:
		event.Skip();
	}
}

/**
 * Move the corresponding device in the device list and
 * update the GUI according to the new order.
 *
 * \param event wxCommandEvent containing the request
 */
template <class T>
void MutDeviceShape<T>::CmMoveIcon (wxCommandEvent & event) {
	switch (event.GetId()) {
	case CM_MOVE_UP:
		MoveDevice(-1);
		break;
	case CM_MOVE_DOWN:
		MoveDevice(+1);
		break;
	}
}

template <class T>
void MutDeviceShape<T>::DoDeviceNotification(wxCommandEvent & mutUNUSED(event))
{
	if (!device || !playbuttons) return;
	MutaborModeType mode = device->GetMode();
	bool open = device->IsOpen();
	bool hidePlay  = !open;
	bool hidePause = hidePlay,
		hideStop  = hidePlay;
	if (open) {
		switch (mode) {
		case DevicePlay:
			hidePlay  = true;
			break;
		case DeviceStop:
			hideStop  = true;
			break;
		case DevicePause:
			hidePause = true;
			break;
		case DeviceKilled:
		case DeviceUnregistered:
		case DeviceInitializing:
		case DeviceCompileError:
		case DeviceTimingError:
			return;
		}
	}

	bool dolayout = false;
	wxSizerItemList & playlist = playbuttons->GetChildren();
	for (wxSizerItemList::iterator i = playlist.begin();
	     i != playlist.end(); i++) {
		wxWindow * button = (*i)->GetWindow();
		bool hide = !open;
		switch (button -> GetId()) {
		case CM_PLAYDEVICE:
			hide = hidePlay;
			break;
		case CM_STOPDEVICE:
			hide = hideStop;
			break;
		case CM_PAUSEDEVICE:
			hide = hidePause;
			break;
		}
		if (hide) {
			if (playbuttons->IsShown(button)) {
				playbuttons->Hide(button);
				dolayout = true;
			}
		} else {
			if (!playbuttons->IsShown(button)) {
				playbuttons->Show(button);
				dolayout = true;
			}
		}
	}
	if (dolayout) {
		playbuttons->Layout();
		wxSize size = playbuttons->GetMinSize();
		playbuttons->SetDimension(0,0,size.GetWidth(),size.GetHeight());
		Update();
	}
}

template <class T>
void MutDeviceShape<T>::createPlayButtons()
{
	mutASSERT(!playbuttons);
	playbuttons = new wxBoxSizer(wxVERTICAL);
	if (!playbuttons) return;
	wxBitmapButton * button =
		new wxBitmapButton(this,CM_PLAYDEVICE,DevicePlayBitmap);
	playbuttons->Add(button);
	button =
		new wxBitmapButton(this,CM_PAUSEDEVICE,DevicePauseBitmap);
	playbuttons->Add(button);
	button =
		new wxBitmapButton(this,CM_STOPDEVICE,DeviceStopBitmap);
	playbuttons->Add(button);
	playbuttons->Layout();
	wxSize size = playbuttons->GetMinSize();
	playbuttons->SetDimension(0,0,size.GetWidth(),size.GetHeight());
}

template <class T>
void MutDeviceShape<T>::createPauseButton()
{
	mutASSERT(!playbuttons);
	playbuttons = new wxBoxSizer(wxVERTICAL);
	if (!playbuttons) return;
	wxBitmapButton * button =
		new wxBitmapButton(this,CM_PAUSEDEVICE,DevicePauseBitmap);
	playbuttons->Add(button);
	playbuttons->Layout();
	wxSize size = playbuttons->GetMinSize();
	playbuttons->SetDimension(0,0,size.GetWidth(),size.GetHeight());
}
template <class T>
void MutDeviceShape<T>::createRecordButtons()
{
	mutASSERT(!playbuttons);
	playbuttons = new wxBoxSizer(wxVERTICAL);
	if (!playbuttons) return;
	wxBitmapButton * button =
		new wxBitmapButton(this,CM_PLAYDEVICE,DeviceRecordBitmap);
	playbuttons->Add(button);
	button =
		new wxBitmapButton(this,CM_PAUSEDEVICE,DevicePauseBitmap);
	playbuttons->Add(button);
	button =
		new wxBitmapButton(this,CM_STOPDEVICE,DeviceStopBitmap);
	playbuttons->Add(button);
	playbuttons->Layout();
	wxSize size = playbuttons->GetMinSize();
	playbuttons->SetDimension(0,0,size.GetWidth(),size.GetHeight());
}

template <class T>
void MutDeviceShape<T>::PlayButtonPressed(wxCommandEvent & event)
{
	if (!device) return;
	if (!device->IsOpen()) return;
	switch (event.GetId()) {
	case CM_PLAYDEVICE:
		device -> Play();
		break;
	case CM_PAUSEDEVICE:
		device -> Pause();
		break;
	case CM_STOPDEVICE:
		device -> Stop();
		break;
	}
}


template <class T>
void MutDeviceShape<T>::DoLeftDblClick() {
	TRACEC;
	DeviceDialog * dlg = ShowDeviceDialog();
	int Res = dlg->ShowModal();
	TRACEC;
	bool destroySelf = false;
	wxWindow * parent = m_parent; // to be availlable after deleten.

	TRACEC;
	if (Res == wxID_OK) {
		DevType type = dlg->GetType();

		if (CanHandleType (type)) {
			TRACEC;
			readDialog (dlg);
		} else if (type != DTNotSet) { // assure type is set.
			TRACEC;
			devicetype dev =
				DeviceFactory::Create<devicetype>(type);
			if (dev) {
				TRACEC;
				thistype * newdev =
					GUIDeviceFactory::CreateShape (dev,
								       GetParent());

				if (! newdev) {
					dlg->Destroy();
					UNREACHABLEC;
					return;
				}
				mutASSERT(newdev->device);
				TRACEC;
				newdev -> readDialog (dlg);
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

	dlg->Destroy();
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
	/* we don't need to destroy this control.
	   This should have been done during device destruction
	*/
	TRACE;
}

template<class T>
typename MutDeviceShape<T>::DeviceDialog * MutDeviceShape<T>::ShowDeviceDialog() {
	ABSTRACT_FUNCTIONC;
	abort();
}

template <class T>
bool MutDeviceShape<T>::DetachDevice ()
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
		parent->Update();
	}
	TRACEC;
	device->Destroy();
	TRACEC;

	return true;
}


template<class T>
bool MutDeviceShape<T>::replaceSelfBy (thistype  * newshape)
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


// instantiate MutInputDeviceShape

template<>
InputDevDlg * MutInputDeviceShape::ShowDeviceDialog() {
	InputDevDlg * in = new InputDevDlg (m_parent);

#ifdef RTMIDI
	if (rtmidiin) {
		try {
			rtmidi::PortList ports = rtmidiin->getPortList();
			if (ports.empty()) {
				in->AppendPortChoiceNoDevice();
			}
			else for (rtmidi::PortList::iterator i = ports.begin();
				  i != ports.end();
				  ++i) {
					in->AppendPortChoice(*i);
				}
		} catch (const rtmidi::Error &error) {
			error.printMessage();
			in->AppendPortChoiceNoDevice();
		}
	}
#else
	STUBC;
#endif
	//		in->SetType(DTUnknown);
	in->SelectMidiDevice(0);
	in->SetMidiFile(wxEmptyString);
	in->SetGUIDOFile(wxEmptyString);

	InitializeDialog(in);

	in->Fit();

	return in;
}

template<>
OutputDevDlg * MutOutputDeviceShape::ShowDeviceDialog()
{
	OutputDevDlg * out = new OutputDevDlg (m_parent);

#ifdef RTMIDI
	if (rtmidiout) {
		try {
			rtmidi::PortList ports = rtmidiout->getPortList();
			if (ports.empty()) {
				out->AppendPortChoiceNoDevice();
			}
			else for (rtmidi::PortList::iterator i = ports.begin();
				  i != ports.end();
				  ++i) {
					out->AppendPortChoice(*i);
				}
		} catch (const rtmidi::Error &error) {
			wxMessageBox(error.getMessage());
			error.printMessage();
			out->AppendPortChoiceNoDevice();
		}
	}

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
	out->SelectMidiDevice(0);
	out->SetMidiFile(wxEmptyString);
	out->SetGUIDOFile(wxEmptyString);
	out->SetMidiBendingRange(2);
	out->SetMidiFileBendingRange(2);

	InitializeDialog(out);

	out->Fit();

	return out;
}

IMPLEMENT_ABSTRACT_CLASS_TEMPLATE1(MutDeviceShape, MutIconShape, inputdevicetypes)
IMPLEMENT_ABSTRACT_CLASS_TEMPLATE1(MutDeviceShape, MutIconShape, outputdevicetypes)

template class MutDeviceShape<inputdevicetypes>;
template class MutDeviceShape<outputdevicetypes>;

MUTABOR_NAMESPACE_END(mutaborGUI)


template class std::list<mutaborGUI::MutInputDeviceShape *>;
template class std::list<mutaborGUI::MutOutputDeviceShape *>;

/*
 * \}
 */
