/** \file
 ********************************************************************
 * Routing window
 *
 * Copyright:   (c) 2008-2011 TU Dresden
 * Changes (c) 2012 Tobias Schlemmer
 * \author   R. Krauße
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
 ********************************************************************
 * \addtogroup GUIroute
 * \{
 ********************************************************************/

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

#include "src/kernel/Defs.h"
#include <stdio.h>
#include "wx/list.h"
#include "wx/ffile.h"
#include "wx/log.h"
#include "wx/dc.h"
#include "wx/dcclient.h"
#include "wx/graphics.h"

//#include "src/kernel/Runtime.h"
#include "src/wxGUI/generic/mhDefs.h"
#include "src/wxGUI/MutRouteWnd.h"
#include "src/wxGUI/Routing/InputDevDlg.h"
#include "src/wxGUI/Routing/BoxDlg.h"
#include "src/wxGUI/Routing/OutputDevDlg.h"
#include "src/wxGUI/Routing/NewInputDeviceShape.h"
#include "src/wxGUI/Routing/NewBoxShape.h"
#include "src/wxGUI/Routing/NewOutputDeviceShape.h"
#include "src/wxGUI/Routing/DebugRoute.h"
#include "src/kernel/routing/RouteCompat.h"
#include "src/kernel/routing/Route-inlines.h"
#include "src/wxGUI/MutApp.h"
#include "src/wxGUI/MutFrame.h"
#include "src/wxGUI/GUIBoxData-inlines.h"
#include "src/wxGUI/Routing/GUIRoute-inlines.h"
#include "src/wxGUI/xmltree.h"


#ifndef RTMIDI
#ifndef MMSYSTEM_H
#define MMSYSTEM_H
//  #define WINVER 0x030a
#include <mmsystem.h>
#endif
#endif

//#include "Mutabor.rh"
#include "src/kernel/routing/Device.h"
#include "src/kernel/MidiKern.h"

//#if !defined(__WXMSW__)
#include "wx/image.h"
#if 0
#include "Icon/DevUnknown.xpm"
#include "Icon/DevMidiPort.xpm"
#include "Icon/DevMidiFile.xpm"
#include "Icon/DevGMN.xpm"
#include "Icon/NewPlop.xpm"
#include "Icon/PlayPlop.xpm"
#include "Icon/PausePlop.xpm"
#include "Icon/ErrorPlop.xpm"
#include "Icon/AddStop.xpm"
#include "Icon/AddPlay.xpm"
#include "Icon/AddPause.xpm"
#include "Icon/AddStopDis.xpm"
#endif
//#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif

using namespace mutabor;
using namespace mutaborGUI;

#if wxUSE_EXTENDED_RTTI
WX_DEFINE_FLAGS( MutRouteWndStyle )

wxBEGIN_FLAGS( MutRouteWndStyle )
    // new style border flags, we put them first to
    // use them for streaming out
    wxFLAGS_MEMBER(wxBORDER_SIMPLE)
    wxFLAGS_MEMBER(wxBORDER_SUNKEN)
    wxFLAGS_MEMBER(wxBORDER_DOUBLE)
    wxFLAGS_MEMBER(wxBORDER_RAISED)
    wxFLAGS_MEMBER(wxBORDER_STATIC)
    wxFLAGS_MEMBER(wxBORDER_NONE)

    // old style border flags
    wxFLAGS_MEMBER(wxSIMPLE_BORDER)
    wxFLAGS_MEMBER(wxSUNKEN_BORDER)
    wxFLAGS_MEMBER(wxDOUBLE_BORDER)
    wxFLAGS_MEMBER(wxRAISED_BORDER)
    wxFLAGS_MEMBER(wxSTATIC_BORDER)
    wxFLAGS_MEMBER(wxBORDER)

    // standard window styles
    wxFLAGS_MEMBER(wxTAB_TRAVERSAL)
    wxFLAGS_MEMBER(wxCLIP_CHILDREN)
    wxFLAGS_MEMBER(wxTRANSPARENT_WINDOW)
    wxFLAGS_MEMBER(wxWANTS_CHARS)
    wxFLAGS_MEMBER(wxFULL_REPAINT_ON_RESIZE)
    wxFLAGS_MEMBER(wxALWAYS_SHOW_SB )
    wxFLAGS_MEMBER(wxVSCROLL)
    wxFLAGS_MEMBER(wxHSCROLL)

wxEND_FLAGS( MutRouteWndStyle )

IMPLEMENT_DYNAMIC_CLASS_XTI(MutRouteWnd, wxScrolledWindow,"MutRouteWnd.h")

wxBEGIN_PROPERTIES_TABLE(MutRouteWnd)
    wxPROPERTY_FLAGS( WindowStyle ,
		      MutRouteWndStyle , long ,
		      SetWindowStyleFlag , GetWindowStyleFlag ,
		      EMPTY_MACROVALUE, 0 /*flags*/ ,
		      wxT("Helpstring") , wxT("group")) // style
// style wxTAB_TRAVERSAL
wxEND_PROPERTIES_TABLE()

wxBEGIN_HANDLERS_TABLE(MutRouteWnd)
wxEND_HANDLERS_TABLE()

wxCONSTRUCTOR_5( MutRouteWnd ,
		 wxWindow* ,
		 Parent ,
		 wxWindowID ,
		 Id ,
		 wxPoint ,
		 Position ,
		 wxSize , Size ,
		 long ,
		 WindowStyle )

#else
IMPLEMENT_DYNAMIC_CLASS(MutRouteWnd, wxScrolledWindow)
#endif




BEGIN_EVENT_TABLE(MutRouteWnd, wxScrolledWindow)
	EVT_MENU(CM_MOVE_UP, MutRouteWnd::OnMoveShape)
	EVT_MENU(CM_MOVE_DOWN, MutRouteWnd::OnMoveShape)
	EVT_PAINT(MutRouteWnd::OnPaint)
	EVT_SIZE(MutRouteWnd::OnSize)
//	EVT_LEFT_DOWN(MutRouteWnd::OnLeftDown)
//	EVT_LEFT_DCLICK(MutRouteWnd::OnLeftDClick)
//WX_EVENT_TABLE_CONTROL_CONTAINER(MutRouteWnd)
END_EVENT_TABLE()


//WX_DELEGATE_TO_CONTROL_CONTAINER(MutRouteWnd, wxScrolledWindow)


MutFileDataType MutRouteWnd::MurFileData;

MutRouteWnd::MutRouteWnd(wxWindow *parent, const wxPoint& pos, const wxSize& size)
        : wxScrolledWindow(parent, wxID_ANY, pos, size,
                           wxVSCROLL|wxHSCROLL|wxTAB_TRAVERSAL, wxT("Route")),
	  InputSizer(NULL),
	  OutputSizer(NULL),
	  BoxSizer(NULL)
{
// This leeds to “assert !m_winParent failed in SetContainerWindow(),
//        even if the container is commented out
//        -> m_container is defined elsewhere
// that it works means that we already have a control container
//	m_container.SetContainerWindow(this);
//

        DEBUGLOG (other, _T("this is window %p"), (void*)this);
        SetSizer(new wxFlexGridSizer(3,0,50));
        SetScrollRate(1, 1);
	SetAutoLayout(true);

	InitShapes();
}

void MutRouteWnd::InitShapes()
{
	DebugCheckRoutes();
	mutASSERT(GetSizer());
        wxSizerFlags flags;
        flags.Align(wxALIGN_CENTER_VERTICAL | wxALIGN_CENTER_HORIZONTAL);
        flags.Proportion(1);
        flags.TripleBorder();

	mutASSERT(InputDevices.empty());
	MutInputDeviceShape * newin = new MutNewInputDeviceShape(this,wxID_ANY);
	GetSizer()->Add(newin, flags);
	InputDevices.push_back(newin);

	mutASSERT(Boxes.empty());
	MutBoxShape * boxShape = new NewMutBoxShape(this,wxID_ANY);
	GetSizer()->Add(boxShape, flags);
	Boxes.push_back(boxShape);

	mutASSERT(OutputDevices.empty());
	MutOutputDeviceShape * newout = new MutNewOutputDeviceShape(this,wxID_ANY);
	GetSizer()->Add(newout, flags);
	OutputDevices.push_back(newout);

	createInputDevices(flags);
	createBoxes(flags);
	createOutputDevices(flags);
	createRoutes(flags);
        FitInside();
	newin->SetFocus();

        PRINTSIZER(GetSizer());
	DebugCheckRoutes();
}

void MutRouteWnd::InitDevices()
{
        Freeze();
	createInputDevices(MutInputDeviceShape::GetSizerFlags());
	createBoxes(MutBoxShape::GetSizerFlags());
	createOutputDevices(MutOutputDeviceShape::GetSizerFlags());
	createRoutes(MutBoxShape::GetSizerFlags());
        InvalidateBestSize();
        FitInside();
        Layout();
        Thaw();

        PRINTSIZER(GetSizer());
	DebugCheckRoutes();
}

void MutRouteWnd::ClearDevices()
{
	ClearInputDevices();
	ClearBoxes();
	ClearOutputDevices();
}

void MutRouteWnd::createInputDevices(wxSizerFlags flags)

{
        MutInputDeviceShape::SetSizerFlags(flags);

	if (!InputSizer) {
		InputSizer = new wxGridSizer(1);
		GetSizer()->Add(InputSizer, 0, wxEXPAND);
	}

	const InputDeviceList & list =
		InputDeviceClass::GetDeviceList();
	for ( InputDeviceList::const_iterator In = list.begin();
	      In != list.end(); In++) {
                DEBUGLOG (other, _T("In the loop %p"),
			  (void*)(*In).get());
		TRACEC;
                MutInputDeviceShape * newin =
			GUIDeviceFactory::CreateShape(const_cast<InputDevice &>(*In),
						      this);
		TRACEC;
                mutASSERT(newin);
                InputSizer->Add(newin, flags);
                InputDevices.push_back(newin);
		TRACEC;
        }
}

void MutRouteWnd::ClearInputDevices()
{
	TRACEC;
	InputDevices.clear();
	TRACEC;
	InputSizer->Clear(true);
	TRACEC;
}

void MutRouteWnd::createBoxes(wxSizerFlags flags)
{
	TRACEC;
        MutBoxShape::SetSizerFlags(flags);

	if (!BoxSizer) {
		BoxSizer = new wxGridSizer (1);
		GetSizer()->Add(BoxSizer, 0, wxEXPAND);
	}

	MutBoxShape * boxShape;
	const BoxListType & list = BoxClass::GetBoxList();
        for (BoxListType::const_iterator box = list.begin();
             box != list.end(); ++box) {

		BoxData * Box = const_cast<BoxData *>(ToGUIBase(*box));
		mutASSERT(Box);
		if (!Box) continue;
		mutASSERT(!Box->GetShape(this));
		boxShape =
			GUIBoxFactory::CreateBoxShape(*box,this);
                if (!boxShape) {
                        UNREACHABLEC;
			continue;
                }
		AddBox(boxShape, flags);
        }

}

void MutRouteWnd::createRoutes(wxSizerFlags flags)
{
	//	MutBoxShape * boxShape;
	const routeListType & list = RouteClass::GetRouteList();
        for (routeListType::const_iterator route = list.begin();
             route != list.end(); ++route) {
		TRACEC;
		Route & r = const_cast<Route &>(*route);
		TRACEC;
		mutASSERT(r);
		MutBoxChannelShape * channel =
			GUIRouteFactory::CreateBoxChannelShape(r,this);
		TRACEC;
		AddRoute(channel,flags);
#if 0
		Box b = r->GetBox();
		InputDevice i = r->GetInputDevice();
		OutputDevice o = r->GetOutputDevice();
		MutBoxShape * boxshape = ToGUIBase(b)->GetShape(this);
		if (i) {
			MutInputDeviceShape * inputshape = ToGUIBase(i)->GetShape(this);
			channel->Add(inputshape);
			inputshape->Add(channel);
		}
		if (o) {
			MutOutputDeviceShape * outputshape = ToGUIBase(o)->GetShape(this);
			//		boxshape->Add(channel);
			channel->Add(outputshape);
			outputshape->Add(channel);
		}
#endif
        }
}

void MutRouteWnd::ClearBoxes()
{
	TRACEC;
	Boxes.clear();
	TRACEC;
	BoxSizer->Clear(true);
	TRACEC;
}


void MutRouteWnd::createOutputDevices(wxSizerFlags flags)

{
	TRACEC;
	MutOutputDeviceShape::SetSizerFlags(flags);

	if (!OutputSizer) {
		OutputSizer = new wxGridSizer (1);
		GetSizer()->Add(OutputSizer, 0, wxEXPAND | wxALL,0);
	}

	const OutputDeviceList & list =
		OutputDeviceClass::GetDeviceList();
	for ( OutputDeviceList::const_iterator Out = list.begin();
	      Out != list.end(); Out++) {
		TRACEC;
                MutOutputDeviceShape * newout =
			GUIDeviceFactory::CreateShape(
				const_cast<OutputDevice &>(*Out),this);

		TRACEC;
                OutputSizer->Add(newout, flags);
		TRACEC;
                OutputDevices.push_back(newout);
		TRACEC;
        }
}

void MutRouteWnd::ClearOutputDevices()
{
	TRACEC;
	OutputDevices.clear();
	TRACEC;
	OutputSizer->Clear(true);
	TRACEC;
}


// Route laden, speichern

void MutRouteWnd::CmRouteLoad(wxCommandEvent& event)
{
	// it's our task
	event.Skip(false);

	MutFileDataType filedata = FileNameDialog(wxGetApp().GetTopWindow(),
						  event.GetId());


	switch (filedata.type) {
	case MutFileDataType::Canceled:
		return;
	case MutFileDataType::TextRoute:
	case MutFileDataType::UTF8TextRoute:
	case MutFileDataType::XMLRoute1:
		break;
	case MutFileDataType::Unknown:
	case MutFileDataType::LogicSource:
		UNREACHABLE;
		return;
	}
	if (!filedata.name.IsOk()) {
		wxLogError(_("The string '%s' is not a valid file name."),
		           filedata.name.GetFullPath().c_str());
		return;
	}

	MurFileData = filedata;


	switch (MurFileData.type) {
	case MutFileDataType::TextRoute:
	case MutFileDataType::UTF8TextRoute: {
		wxFFile file(MurFileData.name.GetFullPath());
		if (!file.IsOpened()) {
			wxLogError(_("File '%s' couldn't be loaded"),MurFileData.name.GetFullPath().c_str());
			return;
		}
		wxString text;
		if (file.ReadAll(&text, wxConvUTF8)) {
			MurFileData.type=MutFileDataType::UTF8TextRoute;
		} else if (file.ReadAll(&text, wxConvISO8859_1)) {
			MurFileData.type=MutFileDataType::TextRoute;
		} else {
			wxLogError(_("File '%s' could be opened, but not loaded."),
				   MurFileData.name.GetFullPath().c_str());
			return;
		}
		compat30::LoadRoutes(text);
	}
		break;
	case MutFileDataType::XMLRoute1: {
		xmltree document(_T("mutabor-routes"),false);
		if (!document.Load(MurFileData.name.GetFullPath())) {
			wxLogError(_("File '%s' couldn't be loaded"),MurFileData.name.GetFullPath().c_str());
			return;
		}

		RouteClass::ClearRouteList();
		InputDeviceClass::ClearDeviceList();
		BoxClass::ClearBoxList();
		OutputDeviceClass::ClearDeviceList();

		DebugCheckRoutes();

		mutabor::RouteFactory::LoadRoutes(document);
	}
		break;
	case MutFileDataType::Canceled:
	case MutFileDataType::Unknown:
	case MutFileDataType::LogicSource:
		UNREACHABLE;
		return;
	}

	// Activate the Route window
	wxGetApp().CmRoutes(event);
	MutRouteWnd * routewnd=NULL;
	MutFrame * frame =
	  dynamic_cast<MutFrame*>(wxWindow::FindWindowById(WK_ROUTE));
	if (frame) {
	  wxWindowList & list = frame->GetChildren();
	  for (wxWindowList::iterator i = list.begin();i!= list.end();i++) {
	    routewnd = dynamic_cast<MutRouteWnd *> (*i);
	    if (routewnd) break;
	  }
	}
	mutASSERT(routewnd);

	if (routewnd) {
	  routewnd->InitDevices();
	  routewnd->Layout();
	  routewnd->FitInside();
	  routewnd->Refresh();
	}

	DebugCheckRoutes();

	wxCommandEvent ev(wxEVT_COMMAND_MENU_SELECTED,CM_ROUTES);
	wxGetApp().ProcessEvent(ev);
}

void MutRouteWnd::CmRouteSave(wxCommandEvent& event)
{
	TRACET(MutFrame);
	event.Skip(false);

	switch (MurFileData.type) {
	case MutFileDataType::Canceled:
		return;
	case MutFileDataType::Unknown:
		CmRouteSaveAs(event);
		return;
	case MutFileDataType::TextRoute:
	case MutFileDataType::UTF8TextRoute:
	case MutFileDataType::XMLRoute1:
		if (!MurFileData.name.IsOk() ) {
			CmRouteSaveAs(event);
			return;
		}
		break;
	case MutFileDataType::LogicSource:
		UNREACHABLE;
		return;
	}

	/* not applicable, since the file might not yet exsist
	 if (!MurFileData.name.IsFileWritable()) {
	 wxLogError(_("Cannot write to routes file '%s'."),
	 MurFileData.name.GetFullPath().c_str());
	 return;
	 }
	 */

	switch (MurFileData.type) {
	case MutFileDataType::TextRoute:
	case MutFileDataType::UTF8TextRoute: {
		wxFFile file(MurFileData.name.GetFullPath(), _T("w"));

		if (!file.IsOpened()) {
			wxLogError(_("Cannot open routes file '%s' for writing."),
				   MurFileData.name.GetFullPath().c_str());
			return;
		}

		wxString RouteConfig;

		compat30::SaveRoutes(RouteConfig);

		wxMBConv &converter = MurFileData.type == MutFileDataType::UTF8TextRoute ?
			(wxMBConv&)wxConvUTF8 : (wxMBConv&)wxConvISO8859_1;

		if (file.Write(_T("# Mutabor 3.x routes configuration\n"),
			       converter))
			if (file.Write(RouteConfig, converter)) {
				file.Close();
				return;
			}

		wxLogError(_("Error writing file '%s'."),
			   MurFileData.name.GetFullPath().c_str());
		file.Close();
	}
		break;
	case MutFileDataType::XMLRoute1: {
		xmltree document(_T("mutabor-routes"),true);
		mutabor::RouteFactory::SaveRoutes(document);
		document.Save(MurFileData.name.GetFullPath());

	}
		break;
	case MutFileDataType::Canceled:
	case MutFileDataType::Unknown:
	case MutFileDataType::LogicSource:
		UNREACHABLE;
		return;
	}
}

void MutRouteWnd::CmRouteSaveAs(wxCommandEvent& event)
{
	TRACET(MutFrame);

	// it's our task
	event.Skip(false);


	MutFileDataType file = FileNameDialog(wxGetApp().GetTopWindow(),
					      event.GetId(),
					      MurFileData.name.GetFullPath());

	switch (file.type) {
	case MutFileDataType::Canceled:
		return;
	case MutFileDataType::TextRoute:
	case MutFileDataType::UTF8TextRoute:
	case MutFileDataType::XMLRoute1:
		break;
	case MutFileDataType::Unknown:
	case MutFileDataType::LogicSource:
		UNREACHABLE;
		return;
	}
	if (!file.name.IsOk()) {
		wxLogError(_("The string '%s' is not a valid file name."),
		           file.name.GetFullPath().c_str());
		return;
	}

	MurFileData = file;
	CmRouteSave(event);
}


/*
// Reaktion auf Computertastatur

void TRouteWin::EvChar(uint key, uint repeatCount, uint flags)
{
TWindow::EvChar(key, repeatCount, flags);
if ( LogicOn )
{
if ( 'A' <= key && key <= 'z' || key == VK_TAB
|| key == VK_UP || key == VK_DOWN
|| key == VK_LEFT || key == VK_RIGHT )
{
pubTaste = key;
if ( IsOpen(WK_LOGIC, curBox) )
GetWinAttr(WK_LOGIC, curBox)->Win->SendMessage(WM_COMMAND, CM_TASTE);
else
KeyboardAnalyseSimple(curBox, key);
}
}
}
*/

void MutRouteWnd::FitInside() {
	wxSize size(GetClientSize());
	if (!GetChildren().empty()) {
		size.IncTo(GetBestVirtualSize());
	}
	SetVirtualSize(size);
}

void MutRouteWnd::OnSize(wxSizeEvent& event)
{
	FitInside();
	Layout();
	Refresh(); // we must repaint the entire window on resizing.
	//event.Skip(); // pass the event to enable the sizers to work

#if 0
    if (GetAutoLayout())
        Layout();
#if wxUSE_CONSTRAINTS
#if defined(__WXPM__) && 0
    else
    {
        // Need to properly move child windows under OS/2

        PSWP                        pWinSwp = GetSwp();

        if (pWinSwp->cx == 0 && pWinSwp->cy == 0 && pWinSwp->fl == 0)
        {
            // Uninitialized

            ::WinQueryWindowPos(GetHWND(), pWinSwp);
        }
        else
        {
            SWP                     vSwp;
            int                     nYDiff;

            ::WinQueryWindowPos(GetHWND(), &vSwp);
            nYDiff = pWinSwp->cy - vSwp.cy;
            MoveChildren(nYDiff);
            pWinSwp->cx = vSwp.cx;
            pWinSwp->cy = vSwp.cy;
        }
    }
#endif
#endif // wxUSE_CONSTRAINTS

    event.Skip();
#endif
}

void MutRouteWnd::OnPaint(wxPaintEvent & event)
{
	wxPaintDC dc(this);
	DoPrepareDC(dc);
	dc.DestroyClippingRegion();
	OnDraw(dc);
}



void MutRouteWnd::OnDraw(wxPaintDC& dc)
{
        wxScrolledWindow::OnDraw(dc);
        PRINTSIZER(GetSizer());
//        dc.SetDeviceOrigin(0,0);
	if (!BoxSizer) {
                UNREACHABLEC;
                return;
        }

	wxGraphicsContext * gc = wxGraphicsContext::Create( dc );
	if (!gc) return;

	wxPoint origin(dc.DeviceToLogicalX(0), dc.DeviceToLogicalY(0));

        wxSizerItemList & list = BoxSizer->GetChildren();
        for (wxSizerItemList::const_iterator i = list.begin(); i != list.end(); i++) {
                MutBoxShape * box = static_cast<MutBoxShape * > ((*i)->GetWindow());
		mutASSERT(dynamic_cast<MutBoxShape *> ((*i)->GetWindow()));
		DEBUGLOG(routinggui,_T("Redrawing box %p"),box);
		if (box)
			box->DrawLines(*gc,this, origin);
        }
	delete gc;
}

void MutRouteWnd::OnMoveShape(wxCommandEvent& event) {
	DEBUGLOG(routinggui,_T("Move Event: %d"),(int)event.GetId());
	wxWindow * win = FindFocus();
	if (dynamic_cast<MutBoxShape *>(win) ||
	    dynamic_cast<MutInputDeviceShape *>(win) ||
	    dynamic_cast<MutOutputDeviceShape *>(win)) {
		wxPostEvent(win,event);
	}
}


void MutRouteWnd::MoveShape(wxWindow * shape, int newpos, wxSizer * sizer) {
	Freeze();
 	mutASSERT(sizer);
	wxSizerItemList & list = sizer->GetChildren();
	wxSizerItemList::iterator pos = list.begin();
	while (pos != list.end() && (*pos)->GetWindow() != shape) pos++;
	wxSizerItem * item = *pos;
	wxSizerItem * nextitem = sizer->GetItem(newpos);
	wxWindow * nextsibling = (nextitem ? nextitem->GetWindow() : NULL);
	list.erase(pos);
	list.Insert(newpos,item);
	shape->MoveBeforeInTabOrder(nextsibling);
	GetSizer()->SetItemMinSize(shape, -1 ,-1);

	Thaw();
	InvalidateBestSize();
	Layout();
	FitInside();
	Refresh();
	Update();
}



#if 0
void MutRouteWnd::MoveShape(MutInputDeviceShape * shape, int newpos) {

	mutASSERT(InputSizer);
	Freeze();

	wxSizerItemList & list = InputSizer->GetChildren();
	wxSizerItemList::iterator pos = list.begin();
	while (pos != list.end() && (*pos)->GetWindow() != shape) pos++;
	wxSizerItem * item = *pos;
	wxSizerItem * nextitem = InputSizer->GetItem(newpos);
	/* \todo make this better */
	wxWindow * nextsibling = (nextitem ? nextitem->GetWindow() : NULL);
	list.erase(pos);
	list.Insert(newpos,item);
	shape->MoveBeforeInTabOrder(nextsibling);
	GetSizer()->SetItemMinSize(shape, -1 ,-1);

	Thaw();
	Layout();
	FitInside();
	Update();
}

#endif


///\}
