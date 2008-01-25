/** \file MutFrame.cpp
 ********************************************************************
 * Mutabor Frame.
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/muwx/MutFrame.cpp,v 1.11 2008/01/25 09:37:11 keinstein Exp $
 * Copyright:   (c) 2005,2006,2007 TU Dresden
 * \author Rüdiger Krauße <krausze@mail.berlios.de>
 * Tobias Schlemmer <keinstein@users.berlios.de>
 * \date $Date: 2008/01/25 09:37:11 $
 * \version $Revision: 1.11 $
 * \license wxWindows license
 *
 * $Log: MutFrame.cpp,v $
 * Revision 1.11  2008/01/25 09:37:11  keinstein
 * Enable CM_ACTIVATE, CM_FILENEW and CM_FILEOPEN in event table
 * Inherit wxFrame
 * Use AUIManager
 * Let Application handle CM_FILENEW/CM_FILEOPEN if we have already a client
 * New titles for Subframes
 * Some Debug output
 * use wxConfig
 *
 * MutFrame::CloseAll,
 * MutFrame::OnSize,
 * MutFrame::OnEraseBackground,
 * MutFrame::OnActivate:        New Functions.
 *
 * Revision 1.10  2007/10/09 14:56:13  keinstein
 * MutFrame::DetermineFrameSize: New Function.
 * MutFrame::MutFrame: Automagic Frame size detection.
 *
 * Revision 1.9  2007/10/08 12:21:50  keinstein
 * Moved major Handling of file opening and new file to MutApp event handler.
 *
 * Revision 1.8  2007/10/05 12:41:44  keinstein
 * first steps towards a real mac version:
 *  - move OnAbout to MutApp
 *  - set ext on frame delete on Quitting, so that program quits too
 *
 * Revision 1.7  2006/01/18 15:37:02  keinstein
 * no MDI Windows in some environments
 *
 * Revision 1.6  2005/11/07 19:42:54  keinstein
 * Some additional changes
 *
 ********************************************************************/


// ===========================================================================
// declarations
// ===========================================================================

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

// For compilers that support precompilation, includes "wx/wx.h".
#include "Defs.h"
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
#include "Mutabor.rh"
#include "MutApp.h"

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

BEGIN_EVENT_TABLE(MutFrame, wxFrame)
    EVT_ERASE_BACKGROUND(MutFrame::OnEraseBackground)
    EVT_SIZE(MutFrame::OnSize)

    EVT_MENU(CM_FILENEW, MutFrame::CmFileNew)
    EVT_MENU(CM_FILEOPEN, MutFrame::CmFileOpen)
    EVT_MENU(CM_FILESAVE, MutFrame::PassEventToEditor)
    EVT_MENU(CM_DOACTIVATE, MutFrame::CmDoActivate)
    EVT_MENU(CM_STOP, MutFrame::CmStop)
    EVT_UPDATE_UI(CM_ACTIVATE, MutFrame::CeActivate)
    EVT_UPDATE_UI(CM_STOP, MutFrame::CeStop)
	
    EVT_MENU(CM_COMPILE, MutFrame::PassEventToEditor)
    EVT_MENU(CM_COMPACT, MutFrame::PassEventToEditor)
    EVT_MENU(CM_ACTIVATE, MutFrame::PassEventToEditor)
    EVT_MENU(CM_GETLINE, MutFrame::PassEventToEditor)
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
    EVT_ACTIVATE(MutFrame::OnActivate)

//	EVT_MENU(CM_ABOUT, MutApp::OnAbout)
//    EVT_MENU(MDI_NEW_WINDOW, MutFrame::OnNewWindow)
//    EVT_MENU(CM_EXIT, MutFrame::OnQuit)

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
       : wxFrame(parent, id, title, pos, size,
                          style | wxNO_FULL_REPAINT_ON_RESIZE)
{

	SetSize (DetermineFrameSize ());
	SetMinSize(wxSize(200,200));
	client = NULL;

	auimanager.SetManagedWindow(this);


#if wxUSE_TOOLBAR
	wxToolBar * tb = new  wxToolBar(this, wxID_ANY, wxDefaultPosition, wxDefaultSize,
                                 wxTB_FLAT | wxTB_NODIVIDER);
//    CreateToolBar(wxNO_BORDER | wxTB_FLAT | wxTB_HORIZONTAL);
//    InitToolBar(GetToolBar());
	InitToolBar(tb);
#endif // wxUSE_TOOLBAR

	auimanager.AddPane(tb, wxAuiPaneInfo().
						Name(_T("tb")).Caption(_("Toolbar")).
						ToolbarPane().Top().
						LeftDockable(false).RightDockable(false));


    // Accelerators
/*    wxAcceleratorEntry entries[3];
    entries[0].Set(wxACCEL_CTRL, (int) 'N', MDI_NEW_WINDOW);
    entries[1].Set(wxACCEL_CTRL, (int) 'X', MDI_QUIT);
    entries[2].Set(wxACCEL_CTRL, (int) 'A', MDI_ABOUT);
    wxAcceleratorTable accel(3, entries);
    SetAcceleratorTable(accel);*/
}

MutFrame::~MutFrame() {
   auimanager.UnInit();
}

void MutFrame::PassEventToEditor(wxCommandEvent &event) {
	if (client) {
		client->ProcessEvent(event);
	}
	event.Skip();
}

void MutFrame::EventPassOn(wxCommandEvent& event)
{ 
	if ( event.GetEventObject() == NULL ) // als Flag zur Sicherheit vor Endlosschleifen
                return;
	event.SetEventObject(NULL);
	
/*	wxAUIPaneInfoArray &info = auimanager.GetAllPanes();
	
	if (!info.empty()) {
		wxAUIPaneInfoArray::iterator it = info.first();
		
	} 
*/	std::cout << "Skippen? " << event.GetSkipped() << 
	  " Propagate? " << event.ShouldPropagate() << std::endl;
	//        if (!GetClientWindow()->ProcessEvent(event)) {
	//	std::cout << "Event ignoriert von:" << GetClientWindow()->GetName().fn_str() << std::endl;
	//	
	
		wxWindow * frame = auimanager.GetManagedWindow();
		if (frame){
		  frame->ProcessEvent(event);
		  std::cout << "Event " << event.ShouldPropagate() << " war da:" 
			    << (frame->GetName().fn_str()) << std::endl;
		}
		//	}text.mb_str(*wxConvFileName)
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
	wxGetApp().UnregisterFrame(this);
    SaveState();
    event.Skip();
}


// TODO: Currently unused; to be deleted.
void MutFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
/*	wxApp &application=wxGetApp();
	wxWindow * window
	application.SetExitOnFrameDelete(true);
	application.SetTopWindow(this);
*/    Close();
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

void MutFrame::CmFileNew(wxCommandEvent& event)
{
#ifdef DEBUG
	printf("MutFrame::CmFileNew\n");
#endif
	if (client) {
		event.Skip(true);
		return;
	}
	OpenFile(wxEmptyString);
}

void MutFrame::CmFileOpen(wxCommandEvent& event)
{
	if (client) {
		event.Skip(true);
		return;
	}

    static wxString s_extDef;
    wxString path = wxFileSelector(
		_("Which Mutabor-file shall be loaded?"),
        _T(""), _T(""),
        s_extDef,
        _("Mutabor tuning file (*.mut)|*.mut|Old Mutabor tuning file (*.mus)|*.mus|All files (*.*)|*.*"),
#ifdef __WXCOCOA__
		0,
#else
        /*wxCHANGE_DIR |*/ wxFILE_MUST_EXIST | wxOPEN,
#endif
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
	wxString filename = !path ? wxString(_("noname.mut")) : wxFileName(path).GetFullName();
	
#ifdef NOAUI
	// Make another frame, containing a canvas
	MutChild *subframe = NewFrame(WK_EDIT, 0, _T("Editor"), ICON(document), filename);
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
#endif
    MutEditFile * editor = new MutEditFile(this, wxPoint(0, 0), wxDefaultSize);
    client = editor;
#ifdef DEBUG
	std::cout << "MutFrame::OpenFile(): Loading " << (path.fn_str()) << std::endl;
#endif
	if (!(!path))
		editor->LoadFile(path);
		
	auimanager.AddPane(client,wxAuiPaneInfo().Caption(filename).CenterPane().PaneBorder(false));
		
//	subframe->winAttr->Win = subframe->client = client;
//	subframe->Show(true);
	editor->SetSelection(0, 0);
//	client->SetName(!path ? wxString(_("noname.mut")) : wxFileName(path).GetFullPath());
	SetTitle(wxString().Format(_("%s -- %s"),APPNAME,filename.c_str()));
	
	auimanager.Update();
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

void MutFrame::CmDoActivate(wxCommandEvent& event)
{
  if (LogicOn) return;

#ifdef DEBUG
  std::cout << "MutFrame::CmDoActivate" << std::endl;
#endif
  if ( !Compiled )
    return;
  // Routen ‹bermitteln
  WriteRoutes(RouteConfig);
#ifdef DEBUG
  std::cout << "MutFrame::CmDoActivate: " 
	    << (RouteConfig.ToUTF8()) 
	    << std::endl;
#endif
  ScanDevices(RouteConfig);
  AktionTraceReset();
	// aktivieren
#ifndef NOACTIVATE
#ifdef DEBUG
  std::cout << "MutFrame::CmDoActivate: Activate" << std::endl;
#endif
  RealTime = true;
  if ( !CheckNeedsRealTime() )
    RealTime = (wxMessageBox(_("There are no realtime \
instruments in the routes.\n\
Shall Mutabor translate the files in batch mode, \
to keep the MIDI files with the original time stamp?\n\
(This means also, that you can't modify the tunings \
while playing by computer keyboard.)"),
			     _("No realtime => batch mode?"), 
			     wxYES_NO | wxICON_QUESTION 
			     /*| MB_DEFBUTTON2*/) == wxNO);
  theFrame = this;
  if ( !Activate(RealTime, &UpdateUIcallback) )
    return;
#endif
#ifdef DEBUG
  std::cout << "MutFrame::CmDoActivate: Initialize state" << std::endl;
#endif
	// Variablen initialisieren
  for (int instr = 0; instr < MAX_BOX; instr++)
    {
      curLogic[instr] = _T("(INITIAL)");
      curTS[instr] = _T("0");
      curTaste[instr][0] = 0;
      curTaste[instr][1] = 0;
    }
#ifdef DEBUG
  std::cout << "MutFrame::CmDoActivate: Check used boxes" << std::endl;
#endif
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
#ifdef DEBUG	
  std::cout << "MutFrame::CmDoActivate: Clear window attributes" << std::endl;
#endif
  for (WinKind kind = WK_KEY; kind < WK_NULL; kind++)
    for (size_t i = 0; i < WinAttrs[kind].GetCount(); i++)
      if ( !BoxUsed[WinAttrs[kind][i].Box] )
	WinAttrs[kind].RemoveAt(i);
#ifdef DEBUG
  std::cout << "MutFrame::CmDoActivate: Open other than logic" << std::endl;
#endif

  // Fenster auﬂer curBox setzen
  if ( !OWM )
    for (WinKind kind = WK_KEY; kind <= WK_LOGIC; kind++)
      for (size_t i = 0; i < WinAttrs[kind].GetCount(); i++)
	if ( WinAttrs[kind][i].Box != curBox && WinAttrs[kind][i].Wanted )
	  if ( kind == WK_LOGIC )
	    LogicWinOpen(WinAttrs[kind][i].Box);
	  else
	    TextBoxOpen(kind, WinAttrs[kind][i].Box);
  
#ifdef DEBUG
  std::cout << "MutFrame::CmDoActivate: Open Logic window" << std::endl;
#endif
  // curBox-Fenstersetzen
  LogicWinOpen(curBox);
  LogicOn = true;
  // Toolbar
  /*2	ControlBar->Remove(*ButtonActivate);
	ControlBar->Insert(*ButtonStop, TGadgetWindow::Before, ButtonPanic);
	ControlBar->LayoutSession();*/
	// Statusbar
  SetStatus(SG_LOGIC);
#ifdef DEBUG
  std::cout << "MutFrame::CmDoActivate: Open Text boxes: " << WK_KEY << "--" <<WK_ACT << std::endl;
#endif
  for (WinKind kind = WK_KEY; kind <= WK_ACT; kind++) 
    {
      if ( TextBoxWanted[kind] )
	TextBoxOpen(kind, curBox);
      else
	DontWant(kind, curBox);
    }
#ifdef DEBUG
  std::cout << "MutFrame::CmDoActivate: Set window title" << std::endl;
#endif
  // Überschrift in MutWin setzen
  wxFileName s(CompiledFile);
  SetTitle(wxString::Format(_("%s -- %s"), APPNAME, s.GetName().c_str()));
  //	Get(WK_LOGIC, curBox)->Win->SetFocus();
#ifdef DEBUG
  std::cout << "MutFrame::CmDoActivate: Repaint route" << std::endl;
#endif
  REPAINT_ROUTE;
#ifdef DEBUG
  std::cout << "MutFrame::CmDoActivate: event.Skip()" << std::endl;
#endif
  event.Skip();
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
		// alle Fenser schlieﬂen
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
  //	event.Enable(!LogicOn && (Compiled || ActiveWinKind == WK_EDIT));
	event.Enable(!LogicOn);
}

void MutFrame::CeStop(wxUpdateUIEvent& event)
{
	event.Enable(LogicOn);
}

// Routenfenster anzeigen

void MutFrame::CmRoutes(wxCommandEvent& event)
{
	if ( IsOpen(WK_ROUTE) )
		ROUTE_WIN->GetParent()->SetFocus();
	else
	{
/*    TMDIChild* curChild = Client->GetActiveMDIChild();
    TMDIMutChild *Win = new TMDIMutChild(WK_ROUTE, GetWinAttr(WK_ROUTE, 0), *Client, 
							"Routes", new TRouteWin(0, Module));
    Win->SetIcon(this, IDI_ROUTE);
    Win->SetIconSm(this, IDI_ROUTE);*/
/*    if (curChild && (curChild->GetWindowLong(GWL_STYLE) & WS_MAXIMIZE))
      Win->Attr.Style |= WS_MAXIMIZE;
    Win->Create();*/

	if (client) {
		event.Skip(true);
		return;
	}

//	MutFrame *subframe = new MutFrame((wxFrame *) NULL,WK_ROUTE, wxString().Format(_("%s -- Routes"),_(PACKAGE_NAME)),
//		wxDefaultPosition,wxDefaultSize,wxDEFAULT_FRAME_STYLE | wxHSCROLL | wxVSCROLL);
//	subframe->SetIcon(ICON(route));
	int width, height;
	GetClientSize(&width, &height);
	client = new MutRouteWnd(this, wxPoint(0, 0), wxSize(width, height));
	auimanager.AddPane(client,wxAuiPaneInfo().Caption(_("Routes")).CenterPane().PaneBorder(false));
	auimanager.Update();
	SetIcon(ICON(route));

//	subframe->Show(true);
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
//	MutChild *subframe = NewFrame(WK_LOGIC, box, _("Logic"), ICON(mutabor));
	


    int width, height;
    GetClientSize(&width, &height);
	width /= 2;
	height /= 2;
    MutLogicWnd *client = new MutLogicWnd(this, box, wxPoint(0, 0), wxSize(width,height));
	wxString Name;
	Name.Printf(_("Logic -- Box %d"),box);
	auimanager.AddPane(client,wxAuiPaneInfo().Name(_("Logic -- Box %d")).Caption(Name).
								Bottom().Floatable(true).CloseButton(true).MaximizeButton(true).Float());
	auimanager.Update();
	
//	subframe->winAttr->Win = subframe->client = client;

//	subframe->Show(true);
}

void MutFrame::ToggleTextBox(WinKind kind)
{
#ifdef DEBUG
  std::cerr << "MutFrame::ToggleTextBox: kind: " << kind << std::endl
	    << "MutFrame::ToggleTextBox: TextBoxWanted:"
	    << TextBoxWanted[kind] << std::endl;
#endif
	TextBoxWanted[kind] = !TextBoxWanted[kind];
#ifdef DEBUG
  std::cerr << "MutFrame::ToggleTextBox: LogicOn"
	    << LogicOn << std::endl;
#endif

	if ( !LogicOn ) return;

#ifdef DEBUG
  std::cerr << "MutFrame::ToggleTextBox: IsOpen(kind, curBox)"
	    << IsOpen(kind, curBox) << std::endl;
#endif
	if ( IsOpen(kind, curBox) ) {
	  wxWindow *win = Get(kind, curBox)->Win;
		//Get(kind, curBox)->Win->SendMessage(WM_CLOSE);
	  auimanager.ClosePane(auimanager.GetPane(win));
	  auimanager.Update();
	  //win->Close();
	  //win->Destroy();
	}
	else
		TextBoxOpen(kind, curBox);
}

void MutFrame::TextBoxOpen(WinKind kind, int box)
{
#ifdef DEBUG	
	std::cout << "Mutframe::TextBoxOpen: Not implemented" << std::cout;
#endif
	char *s;
	wxString title;
	switch ( kind )
	{
		case WK_KEY: 
			s = GetKeyString(box, asTS); 
			title.Printf(_("Current keys at Box %d"),box); 
			break;
		case WK_TS:  
			s = GetTSString(box, asTS); 
			title.Printf(_("Current tone system at Box %d"),box); 
			break;
		case WK_ACT: 
			if (CAW) {
				s = GenerateCAWString(); 
				title=_("Action log"); 
			} else {
				s = GenerateACTString(box); 
				title.Printf(_("Actions at Box %d"),box); 
			}
			break;
	}
//  TextBox[nr]->NewText(s, TRUE);
//  if (curChild && (curChild->GetWindowLong(GWL_STYLE) & WS_MAXIMIZE))
// 	  Win->Attr.Style |= WS_MAXIMIZE;
//#ifdef __WXMSW__
//	wxString Icon[3] = { _T("keytextbox_icn"), _T("tstextbox_icn"), _T("acttextbox_icn") };
//	MutChild *subframe = NewFrame(kind, box, _T("Textbox"), wxIcon(Icon[kind]));
//#else
//	wxIcon Icon[3] = { ICON(keytextbox), ICON(tstextbox), ICON(acttextbox) };
//	MutChild *subframe = NewFrame(kind, box, _T("Textbox"), Icon[kind]);
//#endif
    int width, height;
    GetClientSize(&width, &height);
	width /= 2;
	height /= 2;
//	MutChild * client = new MutChild(this, wxID_ANY, wxPoint(0, 0), wxSize(width, height),
//		kind, GetWinAttr(kind, box));

	MutTextBox *client = new MutChild(kind,
					  GetWinAttr(kind, box),
					  this,
					  -1,
					  wxDefaultPosition,
					  wxSize(width, height));
#ifdef DEBUG
	std::cout << "s:= " << s << std::endl;
#endif

	wxString str;
	if (s)
		str = muT(s);
	else 
		str = wxEmptyString;

//	wxString Name;
//	(title.Printf(_("MutTextBox: %s")),str);
	auimanager.AddPane(client,wxAuiPaneInfo().Caption(title).CloseButton(true).
								MaximizeButton(true).Float().DestroyOnClose(true));
	client->NewText(str, true);
	auimanager.Update();

//	subframe->Show(true);
//	client->NewText(s, true);
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
          auimanager.DetachPane(WinAttrs[kind][i].Win);
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
  // ActWin f¸r curBox updaten
  WinAttr *WinAttr = Get(WK_ACT, curBox);
  if ( WinAttr && WinAttr->Win )
    ((MutTextBox*)WinAttr->Win)->NewText(CAW ? GenerateCAWString() : GenerateACTString(curBox), 1);
  // andere Action-Fenster schlieﬂen bzw. ˆffnen
  if ( CAW )
  {
    for (size_t i = 0; i < WinAttrs[WK_ACT].Count(); i++)
      if ( WinAttrs[WK_ACT][i].Box != curBox && WinAttrs[WK_ACT][i].Win )
      {
        WinAttrs[WK_ACT][i].Wanted = 2; // um Wanted zu erhalten
        auimanager.DetachPane(WinAttrs[WK_ACT][i].Win);
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
/*
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
*/
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
  std::cout << "MutFrame::WindowSize:  not implemented" 
	    << std::endl;
#if 0

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
	if ( win->winAttr->W ) {
	  win->SetSize(win->winAttr->X, win->winAttr->Y, 
		       win->winAttr->W, win->winAttr->H);
	}
	else
	{
		int w, h;
		GetClientSize(&w, &h);
		// get size of editor window
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
#endif
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
		config->SetPath(_T("Desktop"));
		config->Write(_T("X Position"),pos.x);
		config->Write(_T("Y Position"),pos.y);
		config->Write(_T("Width"),size.GetWidth());
		config->Write(_T("Height"),size.GetHeight());
		config->Write(_T("DeskMax"),DeskMax);
		
		config->SetPath(_T(".."));
		
/*		config->Write(_T("DESKTOP"), wxString::Format(_T("%d %d %d %d %d"),
			pos.x, pos.y,
			size.GetWidth(), size.GetHeight(), DeskMax));
*/
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
    config->SetPath(_T("Settings"));
	config->Write(_T("Tone system"), asTS);
	config->Write(_T("Save editor"), SaveEditor);
	config->Write(_T("Color bars"), UseColorBars);

	config->Write(_T("Protocol 1"), TextBoxWanted[0]);
	config->Write(_T("Protocol 2"), TextBoxWanted[1]);
	config->Write(_T("Protocol 3"), TextBoxWanted[2]);
	
	WriteRoutes(config);
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
	int x, y, w, h;

	config->SetPath(_T("Desktop"));
	DeskMax=config->Read(_T("DeskMax"),0l);
	if ((x=config->Read(_T("X Position"),0l)) &&
		(y=config->Read(_T("Y Position"),0l)) &&
		(w=config->Read(_T("Width"),0l)) &&
		(h=config->Read(_T("Height"),0l)))
			SetSize(x, y, w, h);
#ifdef DEBUG
	std::cerr << "x=" << x << ", y=" << y << ", w=" << w << ", h=" << h << std::endl;
#endif

	config->SetPath(_T(".."));

/*	if ( config->Read(wxT("DESKTOP"), &s) )
	{
		int x, y, w, h;
		test = SSCANF (s.c_str(), _T("%d %d %d %d %d"), &x, &y, &w, &h, &DeskMax);
		if ( test >= 4 )
			SetSize(x, y, w, h);
	}
*/
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
    config->SetPath(_T("Settings"));
	asTS=config->Read(_T("Tone system"), true);
	SaveEditor=config->Read(_T("Save editor"), true);
	UseColorBars=config->Read(_T("Color bars"), true);

	TextBoxWanted[0]=config->Read(_T("Protocol 1"), 0l);
	TextBoxWanted[1]=config->Read(_T("Protocol 2"), 0l);
	TextBoxWanted[2]=config->Read(_T("Protocol 3"), 0l);

/*	config->Read(_T("TONSYST"), &asTS, true);
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
*/
	// route
	if ( wxFile::Exists(RcfFile) )
	{
		wxFFile ir(RcfFile);
		if ( ir.IsOpened() )
			ir.ReadAll(&RouteConfig);
	}
#ifdef	DEBUG
	std::cerr << "-" << (RouteConfig.ToUTF8()) << std::endl;
#endif
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

// Recorder-Knˆpfe --------------------------------------------------

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
	std::cout << "MutFrame::CmInDevPlay" << std::endl;
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

/*
void MyFrame::OnUpdateUI(wxUpdateUIEvent& event)
{
    unsigned int flags = m_mgr.GetFlags();

    switch (event.GetId())
    {
/*        case ID_NoGradient:
            event.Check(m_mgr.GetArtProvider()->GetMetric(wxAUI_DOCKART_GRADIENT_TYPE) == wxAUI_GRADIENT_NONE);
            break;
        case ID_VerticalGradient:
            event.Check(m_mgr.GetArtProvider()->GetMetric(wxAUI_DOCKART_GRADIENT_TYPE) == wxAUI_GRADIENT_VERTICAL);
            break;
        case ID_HorizontalGradient:
            event.Check(m_mgr.GetArtProvider()->GetMetric(wxAUI_DOCKART_GRADIENT_TYPE) == wxAUI_GRADIENT_HORIZONTAL);
            break;
        case ID_AllowFloating:
            event.Check((flags & wxAUI_MGR_ALLOW_FLOATING) != 0);
            break;
        case ID_TransparentDrag:
            event.Check((flags & wxAUI_MGR_TRANSPARENT_DRAG) != 0);
            break;
        case ID_TransparentHint:
            event.Check((flags & wxAUI_MGR_TRANSPARENT_HINT) != 0);
            break;
        case ID_VenetianBlindsHint:
            event.Check((flags & wxAUI_MGR_VENETIAN_BLINDS_HINT) != 0);
            break;
        case ID_RectangleHint:
            event.Check((flags & wxAUI_MGR_RECTANGLE_HINT) != 0);
            break;
        case ID_NoHint:
            event.Check(((wxAUI_MGR_TRANSPARENT_HINT |
                          wxAUI_MGR_VENETIAN_BLINDS_HINT |
                          wxAUI_MGR_RECTANGLE_HINT) & flags) == 0);
            break;        
        case ID_HintFade:
            event.Check((flags & wxAUI_MGR_HINT_FADE) != 0);
            break;
        case ID_NoVenetianFade:
            event.Check((flags & wxAUI_MGR_NO_VENETIAN_BLINDS_FADE) != 0);
            break;
            
        case ID_NotebookNoCloseButton:
            event.Check((m_notebook_style & (wxAUI_NB_CLOSE_BUTTON|wxAUI_NB_CLOSE_ON_ALL_TABS|wxAUI_NB_CLOSE_ON_ACTIVE_TAB)) != 0);
            break;
        case ID_NotebookCloseButton:
            event.Check((m_notebook_style & wxAUI_NB_CLOSE_BUTTON) != 0);
            break;
        case ID_NotebookCloseButtonAll:
            event.Check((m_notebook_style & wxAUI_NB_CLOSE_ON_ALL_TABS) != 0);
            break;
        case ID_NotebookCloseButtonActive:
            event.Check((m_notebook_style & wxAUI_NB_CLOSE_ON_ACTIVE_TAB) != 0);
            break;
        case ID_NotebookAllowTabSplit:
            event.Check((m_notebook_style & wxAUI_NB_TAB_SPLIT) != 0);
            break;
        case ID_NotebookAllowTabMove:
            event.Check((m_notebook_style & wxAUI_NB_TAB_MOVE) != 0);
            break;
        case ID_NotebookAllowTabExternalMove:
            event.Check((m_notebook_style & wxAUI_NB_TAB_EXTERNAL_MOVE) != 0);
            break;
        case ID_NotebookScrollButtons:
            event.Check((m_notebook_style & wxAUI_NB_SCROLL_BUTTONS) != 0);
            break;
        case ID_NotebookWindowList:
            event.Check((m_notebook_style & wxAUI_NB_WINDOWLIST_BUTTON) != 0);
            break;
        case ID_NotebookTabFixedWidth:
            event.Check((m_notebook_style & wxAUI_NB_TAB_FIXED_WIDTH) != 0);
            break;
        case ID_NotebookArtGloss:
            event.Check(m_notebook_style == 0);
            break;
        case ID_NotebookArtSimple:
            event.Check(m_notebook_style == 1);
            break;
*
		default: 
			std::cout << _("Fatal error: UpdateUI called with unknown event: ")
					<< (event.GetId()) << std::endl;
    }
}
*/

void MutFrame::OnIdle(wxIdleEvent& event)
{
	wxCommandEvent event1(wxEVT_COMMAND_MENU_SELECTED, CM_UPDATEUI);
	UpdateUI(event1);
	event.Skip();
}

void MutFrame::OnActivate(wxActivateEvent& event) {
	if (event.GetActive()) 
		wxGetApp().SetTopWindow(this);
		
}

void MutFrame::OnEraseBackground(wxEraseEvent& event)
{
	if (client)
		event.Skip();
}

wxAuiDockArt* MutFrame::GetDockArt()
{
	std::cout << "MutFrame::GetDockArt()" << std::endl;
    return auimanager.GetArtProvider();
}



void MutFrame::OnSize(wxSizeEvent& event)
{
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

wxRect MutFrame::DetermineFrameSize () {

    wxSize scr = wxGetDisplaySize();

    // determine default frame position/size
    wxRect normal;
    if (scr.x <= 640) {
        normal.x = 40 / 2;
        normal.width = scr.x - 40;
    }else{
        normal.x = (scr.x - 640) / 2;
        normal.width = 640;
    }
    if (scr.y <= 480) {
        normal.y = 80 / 2;
        normal.height = scr.y - 80;
    }else{
        normal.y = (scr.y - 400) / 2;
        normal.height = 400;
    }

    return normal;
}


void MutFrame::CloseAll(WinKind kind)
{
  for (size_t i = 0; i < WinAttrs[kind].Count(); i++)
    if ( WinAttrs[kind][i].Win )
      {
	WinAttrs[kind][i].Wanted = 2;
	auimanager.ClosePane(auimanager.GetPane(WinAttrs[kind][i].Win));
	WinAttrs[kind][i].Win = 0;
      }
  auimanager.Update();
}
