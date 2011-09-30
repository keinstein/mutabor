/** \file 
 ********************************************************************
 * Routing window
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/muwx/MutRouteWnd.cpp,v 1.25 2011/09/30 18:07:05 keinstein Exp $
 * Copyright:   (c) 2008 TU Dresden
 * \author   R. Krauﬂe
 * Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 2005/08/12
 * $Date: 2011/09/30 18:07:05 $
 * \version $Revision: 1.25 $
 * \license GPL
 *
 * $Log: MutRouteWnd.cpp,v $
 * Revision 1.25  2011/09/30 18:07:05  keinstein
 * * make compile on windows
 * * s/wxASSERT/mutASSERT/g to get assert handler completely removed
 * * add ax_boost_base for boost detection
 *
 * Revision 1.24  2011-09-29 05:26:59  keinstein
 * debug intrusive_ptr
 * fix storage and retrieving of input/output devices in treestorage
 * save maximum border size in icons
 * Apply the calculated offset in IconShape (box and box channels still missing)
 * Fix debug saving and restoring route information/route window on activation
 * Add wxWANTS_CHARS to MutEditWindow
 *
 * Revision 1.23  2011-09-27 20:13:23  keinstein
 * * Reworked route editing backend
 * * rewireing is done by RouteClass/GUIRoute now
 * * other classes forward most requests to this pair
 * * many bugfixes
 * * Version change: We are reaching beta phase now
 *
 * Revision 1.22  2011-09-07 15:58:56  keinstein
 * fix compilation on MinGW
 *
 * Revision 1.21  2011-09-05 11:30:08  keinstein
 * Some code cleanups moving some global box arrays into class mutaborGUI::BoxData
 * Restore perspective on logic start
 *
 * Revision 1.20  2011-08-28 11:36:04  keinstein
 * Remove handcrafted painting code. It is unused since the sizer based positioning and object oriented shapes are used.
 * Do not set Background color to be light gray use the system default instead.
 *
 * Revision 1.19  2011-08-24 21:19:36  keinstein
 * first run with 2.9.2+
 *
 * Revision 1.18  2011-08-21 16:52:05  keinstein
 * Integrate a more sophisticated editor menu based on the stc sample
 *
 * Revision 1.17  2011-02-20 22:35:57  keinstein
 * updated license information; some file headers have to be revised, though
 *
 *
 *
 ********************************************************************
 * \addtogroup route
 * \{
 ********************************************************************/
/////////////////////////////////////////////////////////////////////////////
// Name:        MutApp.cpp
// Purpose:     Mutabor Application
// Author:      R. Krauﬂe
// Modified by:
// Created:     12.08.05
// Copyright:   (c) R. Krauﬂe
// Licence:     wxWindows license
/////////////////////////////////////////////////////////////////////////////

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

#include "Defs.h"
#include <stdio.h>
#include "wx/list.h"
#include "wx/ffile.h"
#include "wx/log.h"
#include "wx/dc.h"

#include "Runtime.h"
#include "mhDefs.h"
#include "MutRouteWnd.h"
#include "InputDevDlg.h"
#include "BoxDlg.h"
#include "OutputDevDlg.h"
#include "NewInputDeviceShape.h"
#include "NewBoxShape.h"
#include "NewOutputDeviceShape.h"
#include "DebugRoute.h"
#include "RouteCompat.h"
#include "muwx/MutApp.h"
#include "muwx/MutFrame.h"
#include "GUIBoxData-inlines.h"

#ifndef RTMIDI
#ifndef MMSYSTEM_H
#define MMSYSTEM_H
//  #define WINVER 0x030a
#include <mmsystem.h>
#endif
#endif

//#include "Mutabor.rh"
#include "Device.h"
#include "MidiKern.h"

//#if !defined(__WXMSW__)
#include "Icon/DevUnknown.xpm"
#if 1
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

extern int curBox;

/*wx
  void RightButtonMenu(TWindow *win, TPoint &point);
*/
// help functions ---------------------------------------------------
/*

void TRouteDialog::SetupWindow()
{
TGraySetupDialog::SetupWindow();
if ( Kind == 4 )
SetCaption("Output device");
if ( Kind == 1)
if ( IsDT == DTGis )
R3->SetCaption("box tag");
else
R4->SetCaption((IsDT == DTMidiFile) ? "track" : "key range");
UpDate();
}

*/

BEGIN_EVENT_TABLE(MutRouteWnd, wxScrolledWindow)
//	EVT_SIZE(MutRouteWnd::OnSize)
//	EVT_LEFT_DOWN(MutRouteWnd::OnLeftDown)
//	EVT_LEFT_DCLICK(MutRouteWnd::OnLeftDClick)
END_EVENT_TABLE()



MutRouteWnd::MurFileDataType MutRouteWnd::MurFileData;

MutRouteWnd::MutRouteWnd(wxWindow *parent, const wxPoint& pos, const wxSize& size)
        : wxScrolledWindow(parent, wxID_ANY, pos, size, 
                           wxVSCROLL|wxHSCROLL|wxTAB_TRAVERSAL, wxT("Route")),
	  InputSizer(NULL),
	  OutputSizer(NULL),
	  BoxSizer(NULL)
{
	DevIcon[DTUnknown] = new ICON(devunknown);
	DevIcon[DTMidiPort] = new ICON(devmidiport);
	DevIcon[DTMidiFile] = new ICON(devmidifile);
	DevIcon[DTGis] = new ICON(devgmn);
	ConIcon[0] = new wxBitmap(AddStop_xpm);//, wxBITMAP_TYPE_XPM);
	ConIcon[1] = new wxBitmap(AddPlay_xpm);//, wxBITMAP_TYPE_XPM);
	ConIcon[2] = new wxBitmap(AddPause_xpm);//, wxBITMAP_TYPE_XPM);
	ConIcon[3] = new wxBitmap(AddStopDis_xpm);//, wxBITMAP_TYPE_XPM);
	PlopIcon[0] = new ICON(newplop);
	PlopIcon[1] = new ICON(playplop);
	PlopIcon[2] = new ICON(pauseplop);
	PlopIcon[3] = new ICON(errorplop);
	spacey = 8;
        spacex = 20;
	x1 = 80;
	x2 = 80;
	x3 = 30;
	x4 = 80;
	x5 = 80;


        DEBUGLOG (other, _T("this is window %p"),this);
        SetSizer(new wxFlexGridSizer(3,0,50));
        SetScrollRate(1, 1);

        initMutIconShapes();
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
	DEBUGLOG(routing,_T("Adding box shape for box %d (list of %d)"),
			 NewBox,BoxData::GetBox(NewBox).GetBoxShapes().size());	
	MutBoxShape * boxShape = new NewMutBoxShape(this,wxID_ANY);
	GetSizer()->Add(boxShape, flags);
	Boxes.push_back(boxShape);
	DEBUGLOG(routing,_T("Adding box shape for box %d (list of %d now)"),
			 NewBox,BoxData::GetBox(NewBox).GetBoxShapes().size());	

	mutASSERT(OutputDevices.empty());
	MutOutputDeviceShape * newout = new MutNewOutputDeviceShape(this,wxID_ANY);
	GetSizer()->Add(newout, flags);
	OutputDevices.push_back(newout);

	createInputDevices(flags);
	createBoxes(flags);
	createOutputDevices(flags);
        FitInside();

        PRINTSIZER(GetSizer());
	DebugCheckRoutes();
}

void MutRouteWnd::InitDevices() 
{
	createInputDevices(MutInputDeviceShape::GetSizerFlags());
	createBoxes(MutBoxShape::GetSizerFlags());
	createOutputDevices(MutOutputDeviceShape::GetSizerFlags());
        FitInside();

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
			  (*In).get());
                MutInputDeviceShape * newin = 
			GUIDeviceFactory::CreateShape((*In),this);
                mutASSERT(newin);
                InputSizer->Add(newin, flags);
                InputDevices.push_back(newin);
        }
}

void MutRouteWnd::ClearInputDevices()
{
  InputDevices.clear();
  InputSizer->Clear(true);
}

void MutRouteWnd::createBoxes(wxSizerFlags flags)
{
        MutBoxShape::SetSizerFlags(flags);

	if (!BoxSizer) {
		BoxSizer = new wxGridSizer (1);			
		GetSizer()->Add(BoxSizer, 0, wxEXPAND);
	}

	MutBoxShape * boxShape;
	const routeListType & list = RouteClass::GetRouteList();
        for (routeListType::const_iterator Route = list.begin();
             Route != list.end(); ++Route) {

		mutASSERT(MIN_BOX <= (*Route)->GetBox()
			 && (*Route)->GetBox() < MAX_BOX);
		BoxData & Box = BoxData::GetBox((*Route)->GetBox());
		boxShape = Box.GetBoxShape(this);
		if (!boxShape) {
			boxShape = 
				GUIRouteFactory::CreateBoxShape((*Route)->GetBox(),
								this);
			AddBox(boxShape, flags);
		}


		MutBoxChannelShape * channel =
			GUIRouteFactory::CreateBoxChannelShape((*Route),
							       boxShape);
		boxShape->Add(channel);
        }
	
/*
        for (MutInputDeviceShapeList::iterator iter = InputDevices.begin();
             iter != InputDevices.end(); ++iter) {

                MutInputDeviceShape * device = 
			dynamic_cast<MutInputDeviceShape*>(*iter);
		mutASSERT(device);
                if (!device) continue;

                Route  Route = device->getRoutes();
                while (Route) {
                        mutASSERT(0<= Route->Box && Route->Box < MAX_BOX);
                        if (!BoxPTRs[Route->Box]) {
                                DEBUGLOG (other, _T("Creating box"));
                                BoxPTRs[Route->Box] = boxShape = 
                                        new MutBoxShape(this,wxID_ANY, Route->Box);
                                DEBUGLOG (other, _T("Box shape: %p"),boxShape);
                                mutASSERT(boxShape);
                                if (!boxShape) continue;
                                AddBox(boxShape, flags);
                        } else {
                                boxShape = BoxPTRs[Route->Box];
                                mutASSERT(wxDynamicCast(boxShape,MutBoxShape));
                        }

                        DEBUGLOG (other, _T("Adding Route to Box %p on window %p"),boxShape,this);
                        MutBoxChannelShape * channel =
                                boxShape->AddChannel(Route);
                        channel->Attatch(device);

                        Route = Route->GetNext();
                }
        }
	
	// Adding routes without input device
	Route  route = RouteClass::GetRouteList();
	while (route) {
		mutASSERT(0<= route->Box && route->Box < MAX_BOX);
		
		bool found = false;
		
		wxSizerItemList & list = BoxSizer->GetChildren();
		for (wxSizerItemList::const_iterator i = list.begin(); i != list.end(); i++) {
			MutBoxShape * box = static_cast<MutBoxShape * > ((*i)->GetWindow());
			mutASSERT(dynamic_cast<MutBoxShape *> ((*i)->GetWindow()));
			if (box && box->HasChannel(route)) {
				found = true;
				break;
			}
		}
		if (found) {
			route = route -> GetGlobalNext();
			continue;
		}
		
		if (!BoxPTRs[route->Box]) {
			DEBUGLOG (other, _T("Creating box"));
			BoxPTRs[route->Box] = boxShape = 
			new MutBoxShape(this,wxID_ANY, route->Box);
			DEBUGLOG (other, _T("Box shape: %p"),boxShape);
			mutASSERT(boxShape);
			if (!boxShape) continue;
			AddBox(boxShape, flags);
		} else {
			boxShape = BoxPTRs[route->Box];
			mutASSERT(wxDynamicCast(boxShape,MutBoxShape));
		}
		
		DEBUGLOG (other, _T("Adding Route to Box %p on window %p"),boxShape,this);
		boxShape->AddChannel(route);
		
		route = route->GetGlobalNext();
	}
*/	
}
void MutRouteWnd::ClearBoxes()
{
  Boxes.clear();
  BoxSizer->Clear(true);
}


void MutRouteWnd::createOutputDevices(wxSizerFlags flags)

{
	MutOutputDeviceShape::SetSizerFlags(flags);
	
	if (!OutputSizer) {
		OutputSizer = new wxGridSizer (1);
		GetSizer()->Add(OutputSizer, 0, wxEXPAND | wxALL,0);
	}

	const OutputDeviceList & list = 
		OutputDeviceClass::GetDeviceList();
	for ( OutputDeviceList::const_iterator Out = list.begin(); 
	      Out != list.end(); Out++) {
                MutOutputDeviceShape * newout =  
			GUIDeviceFactory::CreateShape(*Out,this);

                OutputSizer->Add(newout, flags);
                OutputDevices.push_back(newout);

        }
}

void MutRouteWnd::ClearOutputDevices()
{
  OutputDevices.clear();
  OutputSizer->Clear(true);
}


// Route laden, speichern

void MutRouteWnd::CmRouteLoad(wxCommandEvent& event)
{
	// it's our task
	event.Skip(false);
	
	wxString filename = FileNameDialog(wxGetApp().GetTopWindow(),
	                                   event.GetId());
	
	if (!filename) return;
	
	MurFileData.name.Assign(filename);
	
	wxFFile file(filename);
	if (!file.IsOpened()) {
		wxLogError(_("File '%s' couldn't be loaded"),filename.c_str());
		return;
	}
	wxString text;
	if (! file.ReadAll(&text, MurFileData.autoConverter)) {
		wxLogError(_("File '%s' could be opened, but not loaded."),
		           filename.c_str());
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
	  routewnd->ClearDevices();
	}
	
	compat30::LoadRoutes(text);
	
	if (routewnd) {
	  routewnd->InitDevices();
	}
	
	wxCommandEvent ev(wxEVT_COMMAND_MENU_SELECTED,CM_ROUTES);
	wxGetApp().ProcessEvent(ev);
}

void MutRouteWnd::CmRouteSave(wxCommandEvent& event)
{
	DEBUGLOGTYPE(other,MutFrame,_T(""));
	event.Skip(false);
	
	if (!MurFileData.name.IsOk() ) {
		CmRouteSaveAs(event);
		return;
	}
	
	/* not applicable, since the file might not yet exsist
	 if (!MurFileData.name.IsFileWritable()) {
	 wxLogError(_("Cannot write to routes file '%s'."), 
	 MurFileData.name.GetFullPath().c_str());
	 return;
	 }
	 */
	
	wxFFile file(MurFileData.name.GetFullPath(), _T("w"));
	
	if (!file.IsOpened()) {
		wxLogError(_("Cannot open routes file '%s' for writing."),
		           MurFileData.name.GetFullPath().c_str());
		return;
	}
	
	wxString RouteConfig;
	
	compat30::SaveRoutes(RouteConfig);
	
	if (file.Write(_T("# Mutabor 3.x routes configuration\n"),
		       MurFileData.autoConverter))
		if (file.Write(RouteConfig, MurFileData.autoConverter)) {
			file.Close();
			return;
		}
	
	wxLogError(_("Error writing file '%s'."),
		   
	           MurFileData.name.GetFullPath().c_str());
	file.Close();
}

void MutRouteWnd::CmRouteSaveAs(wxCommandEvent& event)
{
	DEBUGLOGTYPE(other,MutFrame,_T(""));
	
	// it's our task
	event.Skip(false);
	
	wxString filename = FileNameDialog(wxGetApp().GetTopWindow(),
	                                   event.GetId(),
	                                   MurFileData.name.GetFullPath());
	
	if (!filename) return;
	
	MurFileData.name.Assign(filename);
	
	if (!MurFileData.name.IsOk()) {
		wxLogError(_("The string '%s' is not a valid file name."),
		           filename.c_str());
		return;
	}
	
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



void MutRouteWnd::OnDraw(wxDC& dc)
{
        wxScrolledWindow::OnDraw(dc);
	wxRect screenpos;
	GetViewStart(&screenpos.x,&screenpos.y);
	GetClientSize(&screenpos.width,&screenpos.height);
        PRINTSIZER(GetSizer());
//        dc.SetDeviceOrigin(0,0);
	mutASSERT(BoxSizer);
        wxSizerItemList & list = BoxSizer->GetChildren();
        for (wxSizerItemList::const_iterator i = list.begin(); i != list.end(); i++) {
                MutBoxShape * box = static_cast<MutBoxShape * > ((*i)->GetWindow());
		mutASSERT(dynamic_cast<MutBoxShape *> ((*i)->GetWindow()));
		if (box)
			box->DrawLines(dc,screenpos);
        }
}



#if 0
// keyboardanalyse, Fenster aufr‰umen, Logiken lesen und anzeigen
void TRouteWin::UpDate(int thekey, bool isLogicKey)
{
// Analyse zuerst
        keyboard_analyse(thekey, isLogicKey);
        curTaste[curInstr][isLogicKey] = thekey;
        TWindow *ToFocus = NULL;
        if ( isLogicKey )
                curTaste[curInstr][0] = 0;
// alte TMutTag-s lˆschen
        ChildBroadcastMessage(WM_CLOSE);
// neue erstellen
        char isLogic, s[100], s1[100], key, isOpen;
        TWindow *aWin;
        nTags = 0;
        if ( GetMutTag(isLogic, s, s1, key, true) )
                do
                {
                        nTags++;
                        if ( (isOpen = (key == curTaste[curInstr][isLogic])) != 0 )
                                if ( isLogic )
                                {
                                        SetString(&(curLogic[curInstr]), s);
                                        if ( !s1[0] )
                                                if ( !curTS[curInstr] )
                                                        sprintf(s1, "(INITIAL)");
                                                else if ( curTS[curInstr][0] != '[' )
                                                        sprintf(s1, "[%s]", curTS[curInstr]);
                                                else strcpy(s1, curTS[curInstr]);
                                        SetString(&(curTS[curInstr]), s1);
                                }
                                else
                                        SetString(&(curTS[curInstr]), s);
                        aWin = new TMutTag(this, isLogic, isOpen,	10, 10, key, s, GetModule());
                        if ( isOpen ) ToFocus = aWin;
                }
                while ( GetMutTag(isLogic, s, s1, key, false) );
// neue TMutTag-s aktivieren
        CreateChildren();
// Fokus setzen
        if ( !ToFocus )
                ToFocus = GetFirstChild();
        ToFocus->SetFocus();
// Tags anordnen
        SendMessage(WM_SIZE);
        SetFocusPos();
        Parent->SendMessage(WM_COMMAND, CM_SBREFRESH);
        MutWinOk = true;
}

#endif


///\}
