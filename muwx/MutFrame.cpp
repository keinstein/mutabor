/** \file
 ********************************************************************
 * Mutabor Frame.
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/muwx/MutFrame.cpp,v 1.7 2006/01/18 15:37:02 keinstein Exp $
 * \author Rüdiger Krauße <krausze@mail.berlios.de>
 * \date $Date: 2006/01/18 15:37:02 $
 * \version $Revision: 1.7 $
 *
 * $Log: MutFrame.cpp,v $
 * Revision 1.7  2006/01/18 15:37:02  keinstein
 * no MDI Windows in some environments
 *
 * Revision 1.6  2005/11/07 19:42:54  keinstein
 * Some additional changes
 *
 ********************************************************************/
/////////////////////////////////////////////////////////////////////////////
// Name:        MutFrame.cpp
// Purpose:     Mutabor Frame
// Author:      R. Krauße
// Modified by:
// Created:     12.08.05
// Copyright:   (c) R. Krauße
// Licence:     wxWindows license
/////////////////////////////////////////////////////////////////////////////

// ===========================================================================
// declarations
// ===========================================================================

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#ifndef WX_PRECOMP
    #include "wx/wx.h"
    #include "wx/mdi.h"
#endif

#include "wx/toolbar.h"

#if !defined(__WXMSW__)
    #include "Icon/Mutabor.xpm"
    #include "Icon/Document.xpm"
    #include "Icon/Route.xpm"
    #include "Icon/KeyTextBox.xpm"
    #include "Icon/TSTextBox.xpm"
    #include "Icon/ActTextBox.xpm"
#endif

#include "bitmaps/new.xpm"
#include "bitmaps/open.xpm"
#include "bitmaps/save.xpm"
#include "bitmaps/copy.xpm"
#include "bitmaps/cut.xpm"
#include "bitmaps/paste.xpm"
#include "bitmaps/print.xpm"
#include "bitmaps/help.xpm"

#include <wx/filename.h>
#include <wx/config.h>
#include <wx/confbase.h>
#include <wx/fileconf.h>
#ifdef __WXMSW__
#  include <wx/msw/regconf.h>
#endif
#include <wx/ffile.h>
#include "MutFrame.h"
#include "MutChild.h"
#include "MutEditFile.h"
#include "Mutabor.rh"

#include "Defs.h"
#include "mhDefs.h"
#include "EDevice.h"
#include "Runtime.h"
#include "GrafKern.h"
#include "Action.h"
#include "MutRouteWnd.h"
#include "MutLogicWnd.h"
#include "MutTextBox.h"

#define OPENMENU \
	menu = new wxMenu;

#define CLOSEMENU(name) \
	menuBar->Append(menu, name);

#define MENUITEM(name, id, help) \
	menu->Append(id, name, help)

#define MENUCHECKITEM(name, id, help) \
	menu->AppendCheckItem(id, name, help)

#define MENUITEM_ADD(name, id, help, add) \
	menu->Append(id, name, help, add)

#define MENUITEM_SEPARATOR \
    menu->AppendSeparator()

// ---------------------------------------------------------------------------
// global variables
// ---------------------------------------------------------------------------

#ifndef HAVE_CONFIG_H
#  define PACKAGE_NAME "Mutabor"
#endif

#define APPNAME _(PACKAGE_NAME)

wxString RcfFile = wxT("Routes.cfg");

bool demo = false;

bool asTS = true;
bool SaveEditor = true;
bool UseColorBars = true;
bool OWM = false; // One Window Mode
bool CAW = false; // Common Action Window
bool LogicOn = false;
int curBox = 0;
wxWindow *ChildToClose = NULL;

wxString CompiledFile;

wxString curLogic[MAX_BOX];
wxString curTS[MAX_BOX];
int curTaste[MAX_BOX][2]; // [0] ... ToneSyst, [1] ... Logic

bool TextBoxWanted[] =
  { false, false, false };
char WinName[5][12] = { "KEYWIN", "TONSYSTWIN", "ACTIONWIN", "LOGICWIN", "ROUTEWIN" };

#define SG_NOTHING 1
#define SG_LOGIC   0
#define SG_RECORD  2
#define SG_PLAY    3
#define SG_PAUSE   4

#define Compiled (!CompiledFile.IsEmpty())
#define ROUTE_WIN ((MutRouteWnd*)(Get(WK_ROUTE)->Win))
#define REPAINT_ROUTE if ( IsOpen(WK_ROUTE) ) ROUTE_WIN->Refresh()

// ---------------------------------------------------------------------------
// event tables
// ---------------------------------------------------------------------------

BEGIN_EVENT_TABLE(MutFrame, wxMDIParentFrame)
    EVT_MENU(CM_FILENEW, MutFrame::CmFileNew)
    EVT_MENU(CM_FILEOPEN, MutFrame::CmFileOpen)
    EVT_MENU(CM_FILESAVE, MutFrame::EventPassOn)
    EVT_MENU(CM_DOACTIVATE, MutFrame::CmDoActivate)
    EVT_MENU(CM_STOP, MutFrame::CmStop)
	EVT_UPDATE_UI(CM_ACTIVATE, MutFrame::CeActivate)
	EVT_UPDATE_UI(CM_STOP, MutFrame::CeStop)
    
	EVT_MENU(CM_ROUTES, MutFrame::CmRoutes)

	EVT_MENU(CM_TOGGLEKEY, MutFrame::CmToggleKey)
	EVT_MENU(CM_TOGGLETS, MutFrame::CmToggleTS)
	EVT_MENU(CM_TOGGLEACT, MutFrame::CmToggleAct)
	EVT_MENU(CM_OWM, MutFrame::CmToggleOWM)
	EVT_MENU(CM_CAW, MutFrame::CmToggleCAW)
	EVT_UPDATE_UI(CM_TOGGLEKEY, MutFrame::CeToggleKey)
	EVT_UPDATE_UI(CM_TOGGLETS, MutFrame::CeToggleTS)
	EVT_UPDATE_UI(CM_TOGGLEACT, MutFrame::CeToggleAct)
	EVT_UPDATE_UI(CM_OWM, MutFrame::CeToggleOWM)
	EVT_UPDATE_UI(CM_CAW, MutFrame::CeToggleCAW)
	
	EVT_MENU(CM_INDEVSTOP, MutFrame::CmInDevStop)
	EVT_MENU(CM_INDEVPLAY, MutFrame::CmInDevPlay)
	EVT_MENU(CM_INDEVPAUSE, MutFrame::CmInDevPause)
	EVT_UPDATE_UI(CM_INDEVSTOP, MutFrame::CeInDevStop)
	EVT_UPDATE_UI(CM_INDEVPLAY, MutFrame::CeInDevPlay)
	EVT_UPDATE_UI(CM_INDEVPAUSE, MutFrame::CeInDevPause)

	EVT_MENU(CM_ABOUT, MutFrame::OnAbout)
//    EVT_MENU(MDI_NEW_WINDOW, MutFrame::OnNewWindow)
    EVT_MENU(CM_EXIT, MutFrame::OnQuit)

    EVT_CLOSE(MutFrame::OnClose)
    EVT_MENU(CM_UPDATEUI, MutFrame::UpdateUI)
	EVT_IDLE(MutFrame::OnIdle) 
//    EVT_SIZE(MutFrame::OnSize)
END_EVENT_TABLE()

// ===========================================================================
// implementation
// ===========================================================================

// ---------------------------------------------------------------------------
// MutFrame
// ---------------------------------------------------------------------------

// Define my frame constructor
MutFrame::MutFrame(wxWindow *parent,
                 const wxWindowID id,
                 const wxString& title,
                 const wxPoint& pos,
                 const wxSize& size,
                 const long style)
       : wxMDIParentFrame(parent, id, title, pos, size,
                          style | wxNO_FULL_REPAINT_ON_RESIZE)
{
#if wxUSE_TOOLBAR
    CreateToolBar(wxNO_BORDER | wxTB_FLAT | wxTB_HORIZONTAL);
    InitToolBar(GetToolBar());
#endif // wxUSE_TOOLBAR

    // Accelerators
/*    wxAcceleratorEntry entries[3];
    entries[0].Set(wxACCEL_CTRL, (int) 'N', MDI_NEW_WINDOW);
    entries[1].Set(wxACCEL_CTRL, (int) 'X', MDI_QUIT);
    entries[2].Set(wxACCEL_CTRL, (int) 'A', MDI_ABOUT);
    wxAcceleratorTable accel(3, entries);
    SetAcceleratorTable(accel);*/
}

void MutFrame::EventPassOn(wxCommandEvent& event)
{ 
        if ( event.GetEventObject() == NULL ) // als Flag zur Sicherheit vor Endlosschleifen
                return;
        event.SetEventObject(NULL);
	std::cout << "Skippen? " << event.GetSkipped() << 
	  " Propagate? " << event.ShouldPropagate() << std::endl;
	/*        if (!GetClientWindow()->ProcessEvent(event)) {
		std::cout << "Event ignoriert von:" << GetClientWindow()->GetName().fn_str() << std::endl;
	*/	wxFrame * frame = GetActiveChild();
		if (frame){
		  frame->ProcessEvent(event);
		  std::cout << "Event " << event.ShouldPropagate() << " war da:" 
			    << frame->GetName().fn_str() << std::endl;
		}
		//	}
		std::cout << frame << std::endl;
        event.Skip();
}


void MutFrame::OnClose(wxCloseEvent& event)
{
  /*
    if ( event.CanVeto() && (gs_nFrames > 0) )
    {
        wxString msg;
        msg.Printf(_T("%d windows still open, close anyhow?"), gs_nFrames);
        if ( wxMessageBox(msg, _T("Please confirm"),
                          wxICON_QUESTION | wxYES_NO) != wxYES )
        {
            event.Veto();

            return;
        }
    }
  */
    SaveState();
    event.Skip();
}

void MutFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
    Close();
}

void MutFrame::OnAbout(wxCommandEvent& WXUNUSED(event) )
{
  (void)wxMessageBox(wxString::Format(_("%s\nAuthors: \n%s\nUsage: %s"),
				      mumT(PACKAGE_STRING),
				      _T("Ruediger Krausze <krausze@mail.berlios.de>\n")
				      _T("Tobias Schlemmer <keinstein@mail.berlios.de>\n"),
				      mumT(PACKAGE)),
		     wxString::Format(_("About %s"),mumT(PACKAGE_NAME)));
}

void MutFrame::OnNewWindow(wxCommandEvent& WXUNUSED(event) )
{
/*    // Make another frame, containing a canvas
    MutChild *subframe = new MutChild(this/*frame* /, _T("Canvas Frame"));

    wxString title;
    title.Printf(_T("Canvas Frame %d"), ++gs_nFrames);

    subframe->SetTitle(title);

    // Give it an icon
#ifdef __WXMSW__
    subframe->SetIcon(wxIcon(_T("editor_icn")));
#else
    subframe->SetIcon(wxIcon( mondrian_xpm ));
#endif

    // Make a menubar
    wxMenu *file_menu = new wxMenu;

    file_menu->Append(MDI_NEW_WINDOW, _T("&New window"));
    file_menu->Append(MDI_CHILD_QUIT, _T("&Close child"), _T("Close this window"));
    file_menu->Append(MDI_QUIT, _T("&Exit"));

    wxMenu *option_menu = new wxMenu;

    option_menu->Append(MDI_REFRESH, _T("&Refresh picture"));
    option_menu->Append(MDI_CHANGE_TITLE, _T("Change &title...\tCtrl-T"));
    option_menu->AppendSeparator();
    option_menu->Append(MDI_CHANGE_POSITION, _T("Move frame\tCtrl-M"));
    option_menu->Append(MDI_CHANGE_SIZE, _T("Resize frame\tCtrl-S"));

    wxMenu *help_menu = new wxMenu;
    help_menu->Append(MDI_ABOUT, _T("&About"));

    wxMenuBar *menu_bar = new wxMenuBar;

    menu_bar->Append(file_menu, _T("&File"));
    menu_bar->Append(option_menu, _T("&Child"));
    menu_bar->Append(help_menu, _T("&Help"));

    // Associate the menu bar with the frame
    subframe->SetMenuBar(menu_bar);

#if wxUSE_STATUSBAR
    subframe->CreateStatusBar();
    subframe->SetStatusText(title);
#endif // wxUSE_STATUSBAR

    int width, height;
    subframe->GetClientSize(&width, &height);
    MyCanvas *canvas = new MyCanvas(subframe, wxPoint(0, 0), wxSize(width, height));
    canvas->SetCursor(wxCursor(wxCURSOR_PENCIL));
    subframe->canvas = canvas;

    // Give it scrollbars
    canvas->SetScrollbars(20, 20, 50, 50);

    subframe->Show(true);*/
}
/*
void MutFrame::OnSize(wxSizeEvent& 
                                  #ifdef __WXUNIVERSAL__
                                  event
                                  #else
                                  WXUNUSED(event)
                                  #endif
                                  )
{
    int w, h;
    GetClientSize(&w, &h);

    textWindow->SetSize(0, 0, 200, h);
    GetClientWindow()->SetSize(200, 0, w - 200, h);

    // FIXME: On wxX11, we need the MDI frame to process this
    // event, but on other platforms this should not
    // be done.
#ifdef __WXUNIVERSAL__   
    event.Skip();
#endif
}*/

#if wxUSE_TOOLBAR
void MutFrame::InitToolBar(wxToolBar* toolBar)
{
    wxBitmap* bitmaps[8];

    bitmaps[0] = new wxBitmap( new_xpm );
    bitmaps[1] = new wxBitmap( open_xpm );
    bitmaps[2] = new wxBitmap( save_xpm );
    bitmaps[3] = new wxBitmap( copy_xpm );
    bitmaps[4] = new wxBitmap( cut_xpm );
    bitmaps[5] = new wxBitmap( paste_xpm );
    bitmaps[6] = new wxBitmap( print_xpm );
    bitmaps[7] = new wxBitmap( help_xpm );

    toolBar->AddTool(CM_FILENEW, _("New"), *(bitmaps[0]), _("New file"));
    toolBar->AddTool(CM_FILEOPEN, _("Open"), *bitmaps[1], _("Open file"));
    toolBar->AddTool(CM_FILESAVE, _("Save"), *bitmaps[2], _("Save file"));
    toolBar->AddSeparator();
    toolBar->AddTool(3, _("Copy"), *bitmaps[3], _("Copy"));
    toolBar->AddTool(4, _("Cut"), *bitmaps[4],  _("Cut"));
    toolBar->AddTool(5, _("Paste"), *bitmaps[5], _("Paste"));
    toolBar->AddSeparator();
    toolBar->AddTool(6, _("Print"), *bitmaps[6], _("Print"));
    toolBar->AddSeparator();
    toolBar->AddTool( CM_ABOUT, _("About"), *bitmaps[7], _("Help"));
    toolBar->Realize();

    int i;
    for (i = 0; i < 8; i++)
        delete bitmaps[i];
}
#endif // wxUSE_TOOLBAR

void MutFrame::CmFileNew(wxCommandEvent& WXUNUSED(event))
{
	OpenFile(wxEmptyString);
}

void MutFrame::CmFileOpen(wxCommandEvent& WXUNUSED(event))
{
    static wxString s_extDef;
    wxString path = wxFileSelector(
                                    _("Which Mutabor-file shall be loaded?"),
                                    _T(""), _T(""),
                                    s_extDef,
                                    _("Mutabor tuning file (*.mut)|*.mut|Old Mutabor tuning file (*.mus)|*.mus|All files (*.*)|*.*"),
                                    /*wxCHANGE_DIR |*/ wxFILE_MUST_EXIST | wxOPEN,
                                    this
                                   );

    if ( !path )
        return;

    // it is just a sample, would use wxSplitPath in real program
    s_extDef = path.AfterLast(_T('.'));

    OpenFile(path);
}

/** 
 * open a file in a new frame.
 * \param path Path of the file to open
 * \todo file loading fails silently if it is not in the systems encoding.
 * */

void MutFrame::OpenFile(wxString path)
{
	// Make another frame, containing a canvas
	MutChild *subframe = NewFrame(WK_EDIT, 0, _T("Editor"), ICON(document),
		!path ? _T("noname.mut") : wxFileName(path).GetFullName());
    int width, height;
    subframe->GetClientSize(&width, &height);
#ifdef MDI_FORCE_EXTERN
#if wxUSE_TOOLBAR
    subframe->CreateToolBar(wxNO_BORDER | wxTB_FLAT | wxTB_HORIZONTAL);
    InitToolBar(subframe->GetToolBar());
#endif // wxUSE_TOOLBAR
#else
    /*
#if wxUSE_TOOLBAR
    subframe->CreateToolBar(0l | wxNO_BORDER | wxTB_FLAT | wxTB_HORIZONTAL);
    InitToolBar(subframe->GetToolBar());
#endif // wxUSE_TOOLBAR
    */
#endif
    MutEditFile *client = new MutEditFile(subframe, wxPoint(0, 0), wxSize(width, height));
	if (!(!path))
		client->LoadFile(path);
	subframe->winAttr->Win = subframe->client = client;
	subframe->Show(true);
	client->SetSelection(0, 0);
	client->SetName(!path ? _T("noname.mut") : wxFileName(path).GetFullPath());
}


// Logic-Arbeit: CmDoActivate, CmStop, CmPanic, CmExecute

MutFrame* theFrame = 0;

void UpdateUIcallback()
{
	if ( theFrame )
	{
		wxCommandEvent *event1 = new wxCommandEvent(wxEVT_COMMAND_MENU_SELECTED, CM_UPDATEUI);
		theFrame->AddPendingEvent(*event1);
	}
}

/*void TMutaborApp::CmUpdateUI()
{
  IdleAction(0);
}*/

void MutFrame::CmDoActivate(wxCommandEvent& WXUNUSED(event))
{
	if ( !Compiled )
		return;
	// Routen Übermitteln
	WriteRoutes(RouteConfig);
	ScanDevices(RouteConfig);
	AktionTraceReset();
	// aktivieren
#ifndef NOACTIVATE
	RealTime = true;
	if ( !CheckNeedsRealTime() )
		RealTime = (wxMessageBox(_("There are no realtime instruments in the routes.\n"
			_T("Shall Mutabor translate the files in batch mode, to keep the MIDI files with the original time stamp?\n")
			_T("(This means also, that you can't modify the tunings while playing by computer keyboard.)")),
			_("No realtime => batch mode?"), wxYES_NO | wxICON_QUESTION /*| MB_DEFBUTTON2*/) == wxNO);
	theFrame = this;
	if ( !Activate(RealTime, &UpdateUIcallback) )
		return;
#endif
	// Variablen initialisieren
	for (int instr = 0; instr < MAX_BOX; instr++)
	{
		curLogic[instr] = _T("(INITIAL)");
		curTS[instr] = _T("0");
		curTaste[instr][0] = 0;
		curTaste[instr][1] = 0;
	}
	// curBox checken
	CheckBoxesUsed();
	if ( !BoxUsed[curBox] )
	{
		curBox = 0;
		for (int i = 0; i < MAX_BOX; i++)
			if ( BoxUsed[i] )
			{
				curBox = i;
				break;
			}
	}
	SetAktuellesKeyboardInstrument(curBox);
	// WinAttrs säubern
	for (WinKind kind = WK_KEY; kind <= WK_LOGIC; kind++)
		for (size_t i = 0; i < WinAttrs[kind].GetCount(); i++)
			if ( !BoxUsed[WinAttrs[kind][i].Box] )
				WinAttrs[kind].RemoveAt(i);
	// Fenster außer curBox setzen
	if ( !OWM )
		for (WinKind kind = WK_KEY; kind <= WK_LOGIC; kind++)
			for (size_t i = 0; i < WinAttrs[kind].GetCount(); i++)
				if ( WinAttrs[kind][i].Box != curBox && WinAttrs[kind][i].Wanted )
					if ( kind == WK_LOGIC )
						LogicWinOpen(WinAttrs[kind][i].Box);
					else
						TextBoxOpen(kind, WinAttrs[kind][i].Box);
	// curBox-Fenstersetzen
	LogicWinOpen(curBox);
	LogicOn = true;
	// Toolbar
/*2	ControlBar->Remove(*ButtonActivate);
	ControlBar->Insert(*ButtonStop, TGadgetWindow::Before, ButtonPanic);
	ControlBar->LayoutSession();*/
	// Statusbar
	SetStatus(SG_LOGIC);
	for (REUSE(WinKind) kind = WK_KEY; kind <= WK_ACT; kind++)
		if ( TextBoxWanted[(int)kind] )
			TextBoxOpen(kind, curBox);
		else
			DontWant(kind, curBox);
	// Überschrift in MutWin setzen
	wxFileName s(CompiledFile);
	SetTitle(wxString::Format(_T("%s - %s"), APPNAME, s.GetName().c_str()));
	Get(WK_LOGIC, curBox)->Win->SetFocus();
	REPAINT_ROUTE;
}

void MutFrame::CmStop(wxCommandEvent& event)
{
	if ( LogicOn )
	{
 		LogicOn = false;
		CmInDevStop(event);
		Stop();
        // Ampel umschalten
/*		ControlBar->Remove(*ButtonStop);
		ControlBar->Insert(*ButtonActivate, TGadgetWindow::Before, ButtonPanic);
		ControlBar->LayoutSession();*/
		// Statusleiste
		SetStatus(SG_NOTHING);
//		StatusBar->SetText("");
		// Titel
		SetTitle(APPNAME);
		// alle Fenser schließen
		for (WinKind kind = WK_KEY; kind <= WK_LOGIC; kind++)
			CloseAll(kind);
		AktionTraceReset();
		REPAINT_ROUTE;
	}
}

void MutFrame::CmPanic(wxCommandEvent& WXUNUSED(event))
{
	if ( LogicOn )
		Panic();
}

void MutFrame::CeActivate(wxUpdateUIEvent& event)
{
	event.Enable(!LogicOn && (Compiled || ActiveWinKind == WK_EDIT));
}

void MutFrame::CeStop(wxUpdateUIEvent& event)
{
	event.Enable(LogicOn);
}

// Routenfenster anzeigen

void MutFrame::CmRoutes(wxCommandEvent& WXUNUSED(event))
{
	if ( IsOpen(WK_ROUTE) )
		ROUTE_WIN->GetParent()->SetFocus();
	else
	{
/*    TMDIChild* curChild = Client->GetActiveMDIChild();
    TMDIMutChild *Win = new TMDIMutChild(WK_ROUTE, GetWinAttr(WK_ROUTE, 0), *Client, "Routes", new TRouteWin(0, Module));
    Win->SetIcon(this, IDI_ROUTE);
    Win->SetIconSm(this, IDI_ROUTE);*/
/*    if (curChild && (curChild->GetWindowLong(GWL_STYLE) & WS_MAXIMIZE))
      Win->Attr.Style |= WS_MAXIMIZE;
    Win->Create();*/
	MutChild *subframe = NewFrame(WK_ROUTE, 0, _T("Routes"), ICON(route));
	int width, height;
	subframe->GetClientSize(&width, &height);
	MutRouteWnd *client = new MutRouteWnd(subframe, wxPoint(0, 0), wxSize(width, height));
	subframe->winAttr->Win = subframe->client = client;

	subframe->Show(true);
  }
}

// TextBox-Arbeit: ToggleTextBox, TextBoxOpen, CmToggleKey, CmToggleTS

void MutFrame::LogicWinOpen(int box)
{
//  TMDIChild* curChild = Client->GetActiveMDIChild();
/*  TMDIMutChild *Win = new TMDIMutChild(WK_LOGIC, GeWinAttr(WK_LOGIC, box), *Client, "", new TMutWin(0, Module));
  Win->SetIcon(this, IDI_MUTABOR);
  Win->SetIconSm(this, IDI_MUTABOR);
  if (curChild && (curChild->GetWindowLong(GWL_STYLE) & WS_MAXIMIZE))
	  Win->Attr.Style |= WS_MAXIMIZE;
  Win->Create();*/
	MutChild *subframe = NewFrame(WK_LOGIC, box, _T("Logic"), ICON(mutabor));
    int width, height;
    subframe->GetClientSize(&width, &height);
    MutLogicWnd *client = new MutLogicWnd(subframe, wxPoint(0, 0), wxSize(width, height));
	subframe->winAttr->Win = subframe->client = client;

	subframe->Show(true);
}

void MutFrame::ToggleTextBox(WinKind kind)
{
	TextBoxWanted[kind] = !TextBoxWanted[kind];
	if ( !LogicOn ) return;
	if ( IsOpen(kind, curBox) )
		//Get(kind, curBox)->Win->SendMessage(WM_CLOSE);
		Get(kind, curBox)->Win->Close();
	else
		TextBoxOpen(kind, curBox);
}

void MutFrame::TextBoxOpen(WinKind kind, int box)
{
	char *s;
	switch ( kind )
	{
		case WK_KEY: s = GetKeyString(box, asTS); break;
		case WK_TS:  s = GetTSString(box, asTS); break;
		case WK_ACT: s = CAW ? GenerateCAWString() : GenerateACTString(box); break;
	}
//  TextBox[nr]->NewText(s, TRUE);
//  if (curChild && (curChild->GetWindowLong(GWL_STYLE) & WS_MAXIMIZE))
// 	  Win->Attr.Style |= WS_MAXIMIZE;
#ifdef __WXMSW__
	wxString Icon[3] = { _T("keytextbox_icn"), _T("tstextbox_icn"), _T("acttextbox_icn") };
	MutChild *subframe = NewFrame(kind, box, _T("Textbox"), wxIcon(Icon[kind]));
#else
	wxIcon Icon[3] = { ICON(keytextbox), ICON(tstextbox), ICON(acttextbox) };
	MutChild *subframe = NewFrame(kind, box, _T("Textbox"), Icon[kind]);
#endif
    int width, height;
    subframe->GetClientSize(&width, &height);
    MutTextBox *client = new MutTextBox(subframe, wxPoint(0, 0), wxSize(width, height));
	subframe->winAttr->Win = subframe->client = client;

	subframe->Show(true);
	client->NewText(s, true);
}

void MutFrame::CmToggleKey(wxCommandEvent& WXUNUSED(event))
{
  ToggleTextBox(WK_KEY);
}

void MutFrame::CmToggleTS(wxCommandEvent& WXUNUSED(event))
{
  ToggleTextBox(WK_TS);
}

void MutFrame::CmToggleAct(wxCommandEvent& WXUNUSED(event))
{
  ToggleTextBox(WK_ACT);
}

void MutFrame::CmToggleOWM(wxCommandEvent& WXUNUSED(event))
{
  OWM = !OWM;
  if ( !LogicOn )
    return;
  if ( OWM )
  {
    for (WinKind kind = WK_KEY; kind <= WK_LOGIC; kind++)
      for (size_t i = 0; i < WinAttrs[kind].Count(); i++)
        if ( WinAttrs[kind][i].Box != curBox && WinAttrs[kind][i].Win )
        {
          WinAttrs[kind][i].Wanted = 2; // um Wanted zu erhalten
          WinAttrs[kind][i].Win->Close();
        }
  }
  else
    for (WinKind kind = WK_KEY; kind <= WK_LOGIC; kind++)
      for (size_t i = 0; i < WinAttrs[kind].Count(); i++)
        if ( WinAttrs[kind][i].Box != curBox && WinAttrs[kind][i].Wanted )
          if ( kind == WK_LOGIC )
            LogicWinOpen(WinAttrs[kind][i].Box);
          else
            TextBoxOpen(kind, WinAttrs[kind][i].Box);
}

void MutFrame::CmToggleCAW(wxCommandEvent& WXUNUSED(event))
{
  CAW = !CAW;
  if ( !LogicOn )
    return;
  // ActWin für curBox updaten
  WinAttr *WinAttr = Get(WK_ACT, curBox);
  if ( WinAttr && WinAttr->Win )
    ((MutTextBox*)WinAttr->Win)->NewText(CAW ? GenerateCAWString() : GenerateACTString(curBox), 1);
  // andere Action-Fenster schließen bzw. öffnen
  if ( CAW )
  {
    for (size_t i = 0; i < WinAttrs[WK_ACT].Count(); i++)
      if ( WinAttrs[WK_ACT][i].Box != curBox && WinAttrs[WK_ACT][i].Win )
      {
        WinAttrs[WK_ACT][i].Wanted = 2; // um Wanted zu erhalten
        WinAttrs[WK_ACT][i].Win->Close();
      }
  }
  else
    for (size_t i = 0; i < WinAttrs[WK_ACT].Count(); i++)
      if ( WinAttrs[WK_ACT][i].Box != curBox && WinAttrs[WK_ACT][i].Wanted )
        TextBoxOpen(WK_ACT, WinAttrs[WK_ACT][i].Box);
}

void MutFrame::CeToggleKey(wxUpdateUIEvent& event)
{
	event.Check(TextBoxWanted[WK_KEY]);
}

void MutFrame::CeToggleTS(wxUpdateUIEvent& event)
{
  	event.Check(TextBoxWanted[WK_TS]);
}

void MutFrame::CeToggleAct(wxUpdateUIEvent& event)
{
  	event.Check(TextBoxWanted[WK_ACT]);
}

void MutFrame::CeToggleOWM(wxUpdateUIEvent& event)
{
  	event.Check(OWM);
}

void MutFrame::CeToggleCAW(wxUpdateUIEvent& event)
{
  	event.Check(CAW);
}

void MutFrame::CmSelectBox()
{
/*wx  TPopupMenu *Menu = new TPopupMenu();
  Menu->AppendMenu(0, -1, "Select a box");
  Menu->AppendMenu(MF_SEPARATOR	, -1, "");
  for (int box = 0; box < MAX_BOX; box++)
    if ( BoxUsed[box] )
    {
      char s[80];
      sprintf(s, "Box %d", box);
      Menu->AppendMenu((box == curBox) ? MF_CHECKED : 0, 10000+box, strdup(s));
    }
  TPoint p(200, 180);
  GetMainWindow()->ClientToScreen(p);
  Menu->TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON,
    p, 0, *GetMainWindow(), 0);
  delete Menu;*/
}

void MutFrame::CmCloseChild()
{
  if ( ChildToClose )
    ChildToClose->Close();
}

// OpenWindow -------------------------------------------------------

MutChild* MutFrame::NewFrame(WinKind winKind, int box, const wxString &frameName, wxIcon icon, const wxString &title)
{
	// Make another frame, containing a canvas
	MutChild *subframe = new MutChild(this, winKind, GetWinAttr(winKind, box), frameName);
	gs_nFrames++;

	subframe->SetTitle(title.IsEmpty() ? frameName : title );

    // Give it an icon
    subframe->SetIcon(icon);

    // Make a menubar
    wxMenuBar *menuBar = new wxMenuBar;
	wxMenu *menu;
	OPENMENU;
	MENUITEM(_("&New\tCtrl-N"), CM_FILENEW, _("Create a new child window"));
	MENUITEM(_("&Open...\tCtrl+O"), CM_FILEOPEN, wxT(""));
	MENUITEM(_("&Save\tCtrl+S"), CM_FILESAVE, wxT(""));
	MENUITEM(_("Save &As...\tShift+Ctrl+S"), CM_FILESAVEAS, wxT(""));
	MENUITEM_SEPARATOR;
	MENUITEM(_("&Execute\tCtrl-F9"), CM_EXECUTE, wxT(""));
	MENUITEM_SEPARATOR;
	MENUITEM(_("O&ptions"), CM_SETUP, wxT(""));
	MENUITEM_SEPARATOR;
	MENUITEM(_("E&xit"), CM_EXIT, _("Quit the program"));
	CLOSEMENU(_("&File"));

	OPENMENU;
	MENUITEM(_("&Compile\tAlt-F9"), CM_COMPILE, wxT(""));
	MENUITEM(_("&Activate\tF9"), CM_ACTIVATE, wxT(""));
	MENUITEM(_("&Stop\tF8"), CM_STOP, wxT(""));
	MENUITEM_SEPARATOR;
	MENUITEM(_("&Panic\tF12"), CM_PANIC, wxT(""));
	CLOSEMENU(_("&Logic"));

	OPENMENU;
	MENUITEM(_("&Load routes"), CM_ROUTELOAD, wxT("")); 
	MENUITEM(_("&Save routes"), CM_ROUTESAVE, wxT(""));
	MENUITEM(_("Save routes &as"), CM_ROUTESAVEAS, wxT(""));
	CLOSEMENU(_("&Routes"));

	OPENMENU;
	MENUCHECKITEM(_("&Status bar"), IDW_STATUSBAR, wxT(""));
	MENUCHECKITEM(_("&Toolbar"), IDW_TOOLBAR, wxT(""));
	MENUITEM_SEPARATOR;
	MENUITEM(_("&Routes\tF11"), CM_ROUTES, wxT(""));
	MENUITEM_SEPARATOR;
	MENUCHECKITEM(_("Current ke&ys\tF5"), CM_TOGGLEKEY, wxT(""));
	MENUCHECKITEM(_("&Tone system\tF6"), CM_TOGGLETS, wxT(""));
	MENUCHECKITEM(_("&Actions\tF7"), CM_TOGGLEACT, wxT(""));
	MENUITEM_SEPARATOR;
	MENUCHECKITEM(_("&One window mode"), CM_OWM, wxT(""));
	MENUCHECKITEM(_("One &common action window"), CM_CAW, wxT(""));
	MENUITEM_SEPARATOR;
	MENUITEM(_("Select &Box"), CM_SELECTBOX, wxT(""));
	CLOSEMENU(_("&View"));

	OPENMENU;
	MENUITEM(_("&Play"), CM_INDEVPLAY, wxT(""));
	MENUITEM(_("St&op"), CM_INDEVSTOP, wxT(""));
	MENUITEM(_("P&ause"), CM_INDEVPAUSE, wxT(""));
	CLOSEMENU(_("&Sequencer"));

	OPENMENU;
	MENUITEM(_("&Index"), CM_HELPINDEX, wxT(""));
	MENUITEM(_("&Handbook"), CM_HELPHANDBOOK, wxT(""));
	MENUITEM(_("&Help on help"), CM_HELPONHELP, wxT(""));
	MENUITEM_SEPARATOR;
	MENUITEM(_("&About"), CM_ABOUT, wxT(""));
	CLOSEMENU(_("&Help"));

    // Associate the menu bar with the frame
    subframe->SetMenuBar(menuBar);

#if wxUSE_STATUSBAR
    subframe->CreateStatusBar();
    subframe->SetStatusText(title);
#endif // wxUSE_STATUSBAR
	WindowSize(subframe);
	return subframe;
}

// Windowsize -------------------------------------------------------

wxSize subSize = wxDefaultSize;
 
int WSize[4][3] =
	{ { 640, 530, 252},
	{ 800, 646, 328},
	{1024, 826, 425},
	{1280, 994, 620} };

void MutFrame::WindowSize(MutChild *win)
{
	if ( !subSize.IsFullySpecified() )
	{
		wxScreenDC *sdc = new wxScreenDC();
		wxSize deskSize = sdc->GetSize();
		delete sdc;
		subSize.Set(0, 0);
		for (int i = 0; i < 4; i++)
			if ( deskSize.GetWidth() == WSize[i][0] )
				subSize.Set(WSize[i][1], WSize[i][2]);
	}
	if ( win->winAttr->W )
		win->SetSize(win->winAttr->X, win->winAttr->Y, win->winAttr->W, win->winAttr->H);
	else
	{
		int w, h;
		GetClientSize(&w, &h);
		// Fenstergröße eines Editwindows ermitteln
		int w1 = w * 4 / 5, h1 = h * 2 / 3;
        if ( subSize.GetWidth() != 0 )
		{
			w1 = subSize.GetWidth();
			h1 = subSize.GetHeight();
		}
		if ( w - w1 < 112 )
			w1 = w - 112;
		int n = (NumberOfOpen(win->winKind)-1)*22;
		if ( demo )
			switch ( win->winKind )
			{
				case WK_KEY: win->SetSize(w / 2-n, n, w / 4, h / 2); break;
				case WK_TS: win->SetSize(w / 2 + w / 4-n, n, w / 4, h); break;
				case WK_ACT: win->SetSize(w / 2 + n, h / 2-n, w / 4, h - h / 2); break;
				case WK_LOGIC: win->SetSize(n, n, w / 2, h); break;
				case WK_ROUTE: win->SetSize(n, n, w / 2, h); break;
			}
		else
			switch ( win->winKind )
			{
				case WK_KEY: win->SetSize(w1-n, n, w - w1, h / 2); break;
				case WK_TS: win->SetSize(w1-n, h / 2-n, w - w1, h - h / 2); break;
				case WK_ACT: win->SetSize(w1 * 3 / 4-n, h1-n, w1 - w1 * 3 / 4, h - h1); break;
				case WK_LOGIC: win->SetSize(n, h1-n, w1 * 3 / 4, h - h1); break;
				case WK_ROUTE: win->SetSize(n, h1-n, w1 * 3 / 4, h - h1); break;
			};
	}
}

//
// Save the the position and contents of the windows to the "desktop" file.
//
void MutFrame::SaveState()
{
	wxConfig *config = new wxConfig(wxT(PACKAGE_NAME));
/*	if ( MainWindow->Attr.X >= 0 && MainWindow->Attr.Y >= 0 &&
	 MainWindow->Attr.W > 0 && MainWindow->Attr.H > 0 )*/
	{
		wxPoint pos = GetPosition();
		wxSize size = GetSize();
		int DeskMax = size.GetWidth() < GetClientSize().GetWidth();
		config->Write(_T("DESKTOP"), wxString::Format(_T("%d %d %d %d %d"),
			pos.x, pos.y,
			size.GetWidth(), size.GetHeight(), DeskMax));
	}
/*TODO	wxMutChild *active = GetActiveChild();
	if ( !active )
	{
		if ( Client->GetFirstChild() )
			(Client->GetFirstChild())->SendMessage(WM_ACTIVATE, WA_ACTIVE);
		active = Client->GetActiveChild();
	}
	wxMutChild *child = active;
	if ( active )
	{
		int WinMax = Client->GetClientRect() == active->GetClientRect();
		do
		{
			char s[100];
			child->GetWindowText(s, 100);
			if ( ActiveWinKind == WK_EDIT && strcmp(s, "Untitled") )
  			fprintf(os, "EDITOR = %d %d %d %d %s %d\n",
			child->Attr.X, child->Attr.Y,
			child->Attr.W, child->Attr.H, s, WinMax);
			Client->HandleMessage(WM_MDINEXT, NULL);
			child = Client->GetActiveMDIChild();
		}
		while ( child != active );
	}
	for (TWinKind kind = WK_KEY; kind <= WK_ROUTE; kind++)
		for (int i = 0; i < LENGTH(WinAttrs[kind]); i++)
			if ( WinAttrs[kind][i]->W )
     			fprintf(os, "%s = %d %d %d %d %d %d\n",
						WinName[kind], WinAttrs[kind][i]->Box,
          WinAttrs[kind][i]->X, WinAttrs[kind][i]->Y,
          WinAttrs[kind][i]->W, WinAttrs[kind][i]->H, WinAttrs[kind][i]->Wanted);*/
	config->Write(_T("TONSYST"), asTS);
	config->Write(_T("SAVEEDITOR"), SaveEditor);
	config->Write(_T("COLORBARS"), UseColorBars);
	config->Write(_T("PROTOKOLL"), wxString::Format(_T("%d %d %d"),
		TextBoxWanted[0], TextBoxWanted[1], TextBoxWanted[2]));
	delete config;
	// routes
	wxFFile os(RcfFile, _T("w"));
	if ( os.IsOpened() )
	{
		WriteRoutes(RouteConfig);
		os.Write(_T("# last routes configuration MUTABOR 3.x\n"));
		os.Write(RouteConfig);
	}
}

/*bool CheckMutChild(char *name, char *data)
{
	for (TWinKind kind = WK_KEY; kind <= WK_ROUTE; kind++)
		if ( !stricmp(name, WinName[kind]) )
		{
      int box, x, y, w, h, wanted;
      int test = sscanf (data, " = %d %d %d %d %d %d",
        &box, &x, &y, &w, &h, &wanted);
		  if (test < 5)
		  {
		    break;
		  }
      TWinAttr *WinAttr = GetWinAttr(kind, box);
      WinAttr->X = x; WinAttr->Y = y;
      WinAttr->W = w; WinAttr->H = h;
      WinAttr->Wanted = wanted;
      return true;
	  }
  return false;
}*/

void MutFrame::RestoreState()
{
	int DeskMax = 1, WinMax = 2, HelpMax = 0;
//	TMDIChild *active = NULL;
	wxConfig *config = new wxConfig(wxT(PACKAGE_NAME));
	wxString s;
	int test;
	if ( config->Read(wxT("DESKTOP"), &s) )
	{
		int x, y, w, h;
		test = SSCANF (s.c_str(), _T("%d %d %d %d %d"), &x, &y, &w, &h, &DeskMax);
		if ( test >= 4 )
			SetSize(x, y, w, h);
	}
/*      else if ( !stricmp(param, "EDITOR") )
      {
        int x, y, w, h;
        char title[100];
        test = sscanf (datas, " = %d %d %d %d %s %d", &x, &y, &w, &h, title, &HelpMax);
        if ( test < 5 )
        {
          break;
        }
        TMDIChild* child = new TMDIMutChild(WK_EDIT, GetWinAttr(WK_EDIT), *Client, "", new TEditFileMut(0, 0, 0, x, y, w, h, title));
        child->SetMenuDescr(TMenuDescr(IDM_EDITFILE_CHILD, 0, 2, 0, 0, 0, 0));
        child->SetIcon(this, IDI_DOC);
        child->SetIconSm(this, IDI_DOC);
        child->Attr.X = x; child->Attr.Y = y;
        child->Attr.W = w; child->Attr.H = h;
        if  ( !active ) active = child;
        if ( WinMax == 2 ) WinMax = HelpMax;
        SaveMenuChoice(title);
      }
      else if ( CheckMutChild(param, datas) )
      {
      }*/
	config->Read(_T("TONSYST"), &asTS, true);
	config->Read(_T("SAVEEDITOR"), &SaveEditor, true);
	config->Read(_T("COLORBARS"), &UseColorBars, true);
    if ( config->Read(_T("PROTOKOLL"), &s) )
	{
        int a, b, c;
        test = SSCANF (s.c_str(), _T("%d %d %d"), &a, &b, &c);
        if ( test >= 3 )
        {
	        TextBoxWanted[0] = (a != 0);
		    TextBoxWanted[1] = (b != 0);
			TextBoxWanted[2] = (c != 0);
		}
    }
	// route
	if ( wxFile::Exists(RcfFile) )
	{
		wxFFile ir(RcfFile);
		if ( ir.IsOpened() )
			ir.ReadAll(&RouteConfig);
	}
	if ( !RouteConfig )
	{
		::wxMessageBox(_("Could not find routes file."), _("Disk error"),
		wxOK | wxICON_EXCLAMATION);
		RouteConfig =
			_T("OUTPUT\n")
			_T("  MIDIPORT MIDIPORT_OUT 0 2\n")
			_T("INPUT\n")
			_T("  MIDIPORT MIDIPORT_IN 0\n")
			_T("    ALL 0 0 0 1 0 0 15\n");
	}
	ScanRoutes(RouteConfig);
	if ( Get(WK_ROUTE) && Get(WK_ROUTE)->Wanted )
	{
		wxCommandEvent event1(wxEVT_COMMAND_MENU_SELECTED, CM_ROUTES);
		AddPendingEvent(event1);
	}
	// resliche Initialisierung
/*TODO	Client->CreateChildren();
	if ( active )
	{
	   Client->HandleMessage(WM_MDIACTIVATE, (UINT)active->HWindow);
	   if ( WinMax ) active->Show(SW_SHOWMAXIMIZED);
  }
  if ( DeskMax )
  	 MainWindow->Show(SW_SHOWMAXIMIZED);
  else
  	 MainWindow->Show(SW_SHOW);*/
}

// Recorder-Knöpfe --------------------------------------------------

void MutFrame::CmInDevStop(wxCommandEvent& WXUNUSED(event))
{
  int nr = 0;
  for ( EDevice *In = InEDevices; In; In = In->Next, nr++)
    if ( In->Mode == 1 || In->Mode == 2 )
      {
        In->Mode = 0;
        InDeviceAction(nr, 0);
      }
  REPAINT_ROUTE;
  SetStatus(1-LogicOn);
}

void MutFrame::CmInDevPlay(wxCommandEvent& event)
{
  if ( !LogicOn )
    CmDoActivate(event);
  int nr = 0;
  for ( EDevice *In = InEDevices; In; In = In->Next, nr++)
    if ( In->Mode == 0 || In->Mode == 2 )
      {
        In->Mode = 1;
        InDeviceAction(nr, 1);
      }
  REPAINT_ROUTE;
  SetStatus(SG_PLAY);
}

void MutFrame::CmInDevPause(wxCommandEvent& WXUNUSED(event))
{
  int nr = 0;
  for ( EDevice *In = InEDevices; In; In = In->Next, nr++)
    if ( In->Mode == 1 )
      {
        In->Mode = 2;
        InDeviceAction(nr, 2);
      }
  REPAINT_ROUTE;
  SetStatus(SG_PAUSE);
}

void MutFrame::CeInDevStop(wxUpdateUIEvent& event)
{
  for ( EDevice *In = InEDevices; In; In = In->Next)
    if ( In->DT >= DTMidiFile && (In->Mode == 1 || In->Mode == 2) )
    {
      event.Enable(true);
      return;
    }
  event.Enable(false);
}

void MutFrame::CeInDevPlay(wxUpdateUIEvent& event)
{
  if ( !CompiledFile )
  {
    event.Enable(false);
    return;
  }
  for ( EDevice *In = InEDevices; In; In = In->Next)
    if ( In->DT >= DTMidiFile && (In->Mode == 0 || In->Mode == 2) )
    {
      event.Enable(true);
      return;
    }
  event.Enable(false);
}

void MutFrame::CeInDevPause(wxUpdateUIEvent& event)
{
  char Pause = 0;
  for ( EDevice *In = InEDevices; In; In = In->Next)
    if ( In->DT >= DTMidiFile )
      if ( In->Mode == 1 )
      {
        event.Enable(true);
        if ( curStatusImg != SG_PLAY )
          SetStatus(SG_PLAY);
        return;
      }
      else if ( In->Mode == 2 )
        Pause = 1;
  if ( Pause )
  {
    if ( curStatusImg != SG_PAUSE )
      SetStatus(SG_PAUSE);
  }
  else
    if ( curStatusImg != 1-LogicOn )
      SetStatus(1-LogicOn);
  event.Enable(false);
}

// Updaten der Protokollfenster
void MutFrame::UpdateUI(wxCommandEvent& WXUNUSED(event))
{
	for (int i = 0; i < WinAttrs[WK_KEY].GetCount(); i++)
	{
		WinAttr *winAttr = &WinAttrs[WK_KEY][i];
		if ( winAttr->Win && KeyChanged(winAttr->Box) )
			((MutTextBox*)winAttr->Win)->NewText(GetKeyString(winAttr->Box, asTS), 1);
	}
	for (REUSE(int) i = 0; i < WinAttrs[WK_TS].GetCount(); i++)
	{
		WinAttr *winAttr = &WinAttrs[WK_TS][i];
		if ( winAttr->Win && TSChanged(winAttr->Box) )
			((MutTextBox*)winAttr->Win)->NewText(GetTSString(winAttr->Box, asTS), 1);
	}
	// Aktionen
	if ( TakeOverAktions() )
		if ( CAW )
		{
			WinAttr *winAttr = Get(WK_ACT, curBox);
			if ( winAttr && winAttr->Win )
				((MutTextBox*)winAttr->Win)->NewText(GenerateCAWString(), 1);
		}
		else
		{
			for (int i = 0; i < WinAttrs[WK_ACT].GetCount(); i++)
			{
				WinAttr *winAttr = &WinAttrs[WK_ACT][i];
				if ( winAttr->Win && ACTChanged(winAttr->Box) )
					((MutTextBox*)winAttr->Win)->NewText(GenerateACTString(winAttr->Box), 1);
			}
		}
	// Zeilen/Spalte
/*  if ( ActiveWinKind == WK_EDIT )
  {
    TMDIChild* curChild = Client->GetActiveMDIChild();
    if ( curChild )
	     curChild->SendMessage(WM_COMMAND, CM_GETLINE);
  }
  else
    EditLine = -1;
  if ( EditLine != oldEditLine || EditRow != oldEditRow )
  {
	  char s[10] = "";
	  if ( EditLine != -1 ) sprintf(s, "%d:%d", EditLine, EditRow);
	  IndikatorGadget->SetText(s);
	  oldEditLine = EditLine; oldEditRow = EditRow;
  }*/
	if ( InDevicesChanged() )
	{
		char Mode[256];
		GetInDevicesMode(Mode);
		bool NRT_Finish = false;
		for (EDevice *In = InEDevices; In; In = In->Next)
		{
			if ( In->Nr != -1 )
				if ( Mode[In->Nr] == 4 )
				{
					In->Mode = 0;
					InDeviceAction(In->Nr, 0);
					NRT_Finish = !RealTime;
				}
				else
				{
					In->Mode = Mode[In->Nr];
				}
		}
		REPAINT_ROUTE;
		if ( !RealTime )
			wxMessageBox(_("Translation in batch mode completed. Output was generated."),
				_("Batch translation finished"), wxOK);
	}
}

void MutFrame::OnIdle(wxIdleEvent& event)
{
	wxCommandEvent event1(wxEVT_COMMAND_MENU_SELECTED, CM_UPDATEUI);
	UpdateUI(event1);
	event.Skip();
}

// Route laden, speichern

/*void MutFrame::CmRouteLoad()
{
  *MurFileData.FileName = 0;
  if (TFileOpenDialog(MainWindow, MurFileData, 0, "Load Mutabor Routes").Execute() == IDOK)
  {
    ifstream is(MurFileData.FileName);
    if ( is.bad() )
    {
      MainWindow->MessageBox("Unable to read this route file.", "Disk error",
        MB_OK | MB_ICONEXCLAMATION);
      return;
    }
    char *s = (char*) malloc(30000);
    is.read(s, 30000);
    s[is.gcount()] = 0;
    free(RouteConfig);
    RouteConfig = strdup(s);
    ScanRoutes(RouteConfig);
    REPAINT_ROUTE;
    CmRoutes();
  }
}

void
TMutaborApp::CmRouteSave()
{
  if ( *MurFileData.FileName == 0 )
  {
    CmRouteSaveAs();
    return;
  }
  ofstream os(MurFileData.FileName);
  if ( os.bad() )
  {
    MainWindow->MessageBox("Unable to write this route file.", "Disk error",
      MB_OK | MB_ICONEXCLAMATION);
    return;
  }
  WriteRoutes(&RouteConfig);
  os << "# Mutabor 3.x routes configuration\n" << RouteConfig;
}

void
TMutaborApp::CmRouteSaveAs()
{
  if ( *MurFileData.FileName == 0 )
    strcpy(MurFileData.FileName, "noname.mur");
  if (TFileSaveDialog(MainWindow, MurFileData, 0, "Save Mutabor Routes").Execute() == IDOK)
  {
    ofstream os(MurFileData.FileName);
    if ( os.bad() )
    {
      MainWindow->MessageBox("Unable to write this route file.", "Disk error",
        MB_OK | MB_ICONEXCLAMATION);
      return;
    }
    WriteRoutes(&RouteConfig);
    os << "# Mutabor 3.x routes configuration\n" << RouteConfig;
  }
}
*/
