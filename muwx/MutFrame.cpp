/** \file MutFrame.cpp
 ********************************************************************
 * Mutabor Frame.
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/muwx/MutFrame.cpp,v 1.17 2008/07/22 07:57:06 keinstein Exp $
 * Copyright:   (c) 2005,2006,2007 TU Dresden
 * \author Rüdiger Krauße <krausze@mail.berlios.de>
 * Tobias Schlemmer <keinstein@users.berlios.de>
 * \date $Date: 2008/07/22 07:57:06 $
 * \version $Revision: 1.17 $
 * \license wxWindows license
 *
 * $Log: MutFrame.cpp,v $
 * Revision 1.17  2008/07/22 07:57:06  keinstein
 * solved some valgrind issues
 *
 * Revision 1.16  2008/07/21 09:25:29  keinstein
 * RcfFile: removed
 * TextBoxWanted: one variable per box and type
 * removed ROUTE_WIN and REPAINT_ROUTE definitions
 * reformatted debug logging
 * Implement box selection Menu
 * MutFrame::repaint_route(): New function
 *
 * Revision 1.15  2008/06/30 08:57:17  keinstein
 * Fix UPDATE_UI for CM_PANIC and CM_EXECUTE
 * MurFileData: new struct
 * theFrame: new variable
 * ~MutFrame(): empty event loop
 * PassEventToEditor(): Runtime Class check for client
 * OnClose(): implement Veto if logic is active
 * 	stop logic if running
 * 	close all clients before deletion to make AUI on reopening happy
 * CmDoActivate(): Separate Logic window creation from other windows
 * 	Create box selection submenu
 * ClearMenuItem(), ClearSubMenu(), RaiseLogic(), CmStop(), CeActivate(): New functions.
 * CmRoutes(): Raise window and return if we have a route window already.
 * 	Set window ID.
 * LogicWinOpen(): remove close button
 * 	Set unique name
 * TextBoxOpen(): don't destroy on close
 * 	set unique window name
 * StopInDev(): new function.
 * CmInDevStop(): sooutsourcing to StopInDev().
 * CmRouteLoad(): New function.
 * CmRouteSave(), CmRouteSaveAs(): New funcitons.
 * CloseAll(): Some reorganization.
 * ActiveWindow, BoxCommandIds: new Attributes.
 *
 * Revision 1.14  2008/06/02 16:25:26  keinstein
 * don't include Mutabor.rh
 * implement CM_EXECUTE action
 * disable CM_COMPILE, CM_EXECUTE, CM_DOACTIVATE if logic is active
 * implement CM_SETTITLE for setting the window title
 * FileNameDialog(): reimplemented
 * CmFileOpen() and other: correct Event Skipping.
 * MutFrame::ToggleTextBox(), CloseAll():
 * use DetachPane and Close instead of ClosePane
 *
 * Revision 1.13  2008/04/28 08:21:33  keinstein
 * Silence a warning since it is issued every normal start.
 *
 * Revision 1.12  2008/03/11 10:37:34  keinstein
 * Holyday edition
 * put CM_xxx in an enum
 * use wx constants
 * document mutframe
 * some white space formattings
 * make route saving more system specific
 * many other fixes
 *
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
 * Revision 1.7  2006/01/18 15:37:02  kewxWindows licenseinstein
 * no MDI Windows in some environments
 *
 * Revision 1.6  2005/11/07 19:42:54  keinstein
 * Some additional changes
 *
 * \addtogroup muwx
 * \{
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
//#include "Mutabor.rh"
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

//wxString RcfFile = wxT("Routes.cfg");
struct MurFileDataType {
  wxFileName name;
  muConvAuto autoConverter;
} MurFileData;

MutFrame* theFrame = 0;
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

bool TextBoxWanted[MAX_BOX][3] = {
  { false, false, false },
  { false, false, false },
  { false, false, false },
  { false, false, false },
  { false, false, false },
  { false, false, false },
  { false, false, false },
  { false, false, false },
  { false, false, false },
  { false, false, false },
  { false, false, false },
  { false, false, false },
  { false, false, false },
  { false, false, false },
  { false, false, false },
  { false, false, false }
};
char WinName[5][12] = { "KEYWIN", "TONSYSTWIN", "ACTIONWIN", "LOGICWIN", "ROUTEWIN" };

int MutFrame::boxCommandIds[MAX_BOX];

#define SG_NOTHING 1
#define SG_LOGIC   0
#define SG_RECORD  2
#define SG_PLAY    3
#define SG_PAUSE   4

#define Compiled (!CompiledFile.IsEmpty())
//#define ROUTE_WIN ((MutRouteWnd*)(Get(WK_ROUTE)->Win))
//#define REPAINT_ROUTE if ( IsOpen(WK_ROUTE) ) ROUTE_WIN->Refresh()

// ---------------------------------------------------------------------------
// event tables
// ---------------------------------------------------------------------------

BEGIN_EVENT_TABLE(MutFrame, wxFrame)
    EVT_ERASE_BACKGROUND(MutFrame::OnEraseBackground)
    EVT_SIZE(MutFrame::OnSize)

    EVT_MENU(CM_FILENEW, MutFrame::CmFileNew)
    EVT_MENU(CM_FILEOPEN, MutFrame::CmFileOpen)
    EVT_MENU(CM_EXECUTE, MutFrame::CmFileOpen)
    EVT_MENU(CM_FILESAVE, MutFrame::PassEventToEditor)
//    EVT_MENU(CM_FILESAVEAS, MutFrame::CmFileOpen)
    EVT_MENU(CM_DOACTIVATE, MutFrame::CmDoActivate)
    EVT_MENU(CM_STOP, MutFrame::CmStop)
    EVT_MENU(CM_PANIC, MutFrame::CmPanic)
    EVT_UPDATE_UI(CM_EXECUTE, MutFrame::CeExecute)
    EVT_UPDATE_UI(CM_ACTIVATE, MutFrame::CeActivate)
    EVT_UPDATE_UI(CM_COMPILE, MutFrame::CeActivate)
    EVT_UPDATE_UI(CM_DOACTIVATE, MutFrame::CeActivate)
    EVT_UPDATE_UI(CM_STOP, MutFrame::CeStop)
    EVT_UPDATE_UI(CM_PANIC, MutFrame::CeStop)  
    EVT_MENU(CM_COMPILE, MutFrame::PassEventToEditor)
    EVT_MENU(CM_COMPACT, MutFrame::PassEventToEditor)
    EVT_MENU(CM_ACTIVATE, MutFrame::PassEventToEditor)
    EVT_MENU(CM_GETLINE, MutFrame::PassEventToEditor)
//    EVT_MENU(CM_ROUTES, MutFrame::CmRoutes)

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
//    EVT_ACTIVATE(MutFrame::OnActivate)

    EVT_CLOSE(MutFrame::OnClose)
    EVT_MENU(CM_UPDATEUI, MutFrame::UpdateUI)
    EVT_IDLE(MutFrame::OnIdle) 
    EVT_MENU(CM_SETTITLE, MutFrame::CmSetTitle)
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
		 style | wxNO_FULL_REPAINT_ON_RESIZE),
  curStatusImg(0){

	SetSize (DetermineFrameSize ());
	SetMinSize(wxSize(200,200));
	client = NULL;

	auimanager.SetManagedWindow(this);


#if wxUSE_TOOLBAR
	wxToolBar * tb = new  wxToolBar(this, 
					wxID_ANY, 
					wxDefaultPosition, 
					wxDefaultSize,
					wxTB_FLAT | wxTB_NODIVIDER);
	InitToolBar(tb);

	auimanager.AddPane(tb, wxAuiPaneInfo().
			   Name(_T("tb")).Caption(_("Toolbar")).
			   ToolbarPane().Top().
			   LeftDockable(false).RightDockable(false));
#endif // wxUSE_TOOLBAR


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
  while (wxGetApp().Pending()) wxGetApp().Dispatch();
}

#if wxUSE_TOOLBAR
void MutFrame::InitToolBar(wxToolBar* toolBar)
{
    wxBitmap* bitmaps[8];

    /* \todo use PNG images from resources */
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
    toolBar->AddSeparator();
    toolBar->Realize();

    int i;
    for (i = 0; i < 8; i++)
        delete bitmaps[i];
}
#endif // wxUSE_TOOLBAR

void MutFrame::PassEventToEditor(wxCommandEvent &event) {
	event.Skip(false);
	if (dynamic_cast<MutEditFile*>(client)) {
		client->ProcessEvent(event);
	}
}

void MutFrame::EventPassOn(wxCommandEvent& event)
{ 
	if ( event.GetEventObject() == NULL ) 
	  // als Flag zur Sicherheit vor Endlosschleifen
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
  DEBUGLOG(_T("%x == %x"),this,theFrame);

  if ( event.CanVeto() && theFrame == this ) {
    wxString msg;
    msg.Printf(_("This logic is currently active. On closing it will be deactivated. Really close this window?"));
    if ( wxMessageBox(msg, _("Please confirm closing."),
		      wxICON_QUESTION | wxYES_NO) != wxYES ) {
      event.Veto();
      return;
    }
  }

  if (theFrame == this) {
    DoStop();
  }

  if (client) {
#ifdef DEBUG
    std::cout << "MutFame::OnClose: Deleting Client" << std::endl;
#endif
    auimanager.DetachPane(client);
    client->Close();
    client = NULL;
  }
  //while (wxGetApp().Pending()) wxGetApp().Dispatch();
  

  SaveState();
  wxGetApp().UnregisterFrame(this);
  Destroy();
  event.Skip(false);
}



void MutFrame::CmFileNew(wxCommandEvent& event)
{
#ifdef DEBUG
  printf("MutFrame::CmFileNew\n");
#endif
  if (client) {
    event.Skip(true);
    return ;
  }

  event.Skip(false); // Its our task to try create the file

  OpenFile(wxEmptyString);
}


void MutFrame::CmFileOpen(wxCommandEvent& event)
{
  if (client) {
    event . Skip (true);
    return;
  }

  event . Skip (false); // it's our task to try to open that file
  
  wxString path = FileNameDialog(this, event.GetId());

  if ( !path )
    return;
  

#ifdef DEBUG
  std::cerr << "MutFrame:CmFileOpen " << CM_EXECUTE << " == " 
	    << event . GetId () << "?" << std::endl;
#endif


  switch (event.GetId()) {
  case CM_FILEOPEN:
    OpenFile(path); 
    break;
  case CM_EXECUTE: 
    {
      OpenFile(path);
      wxCommandEvent e (wxEVT_COMMAND_MENU_SELECTED, CM_ACTIVATE);
      ProcessEvent (e);
    }
    break;
  case CM_FILESAVEAS:
    event.SetString(path);
    PassEventToEditor(event);
    break;
  default:
    wxLogError(_("Unexpected Event in MutFrame::CmFileOpen: %d"),event.GetId());
  }
}

/** 
 * open a file in a new frame.
 * \param path Path of the file to open
 * \todo file loading fails silently if it is not in the systems encoding.
 * */

bool MutFrame::OpenFile (wxString path, bool newfile)
{
  if (client) return false;
  wxString filename = !path ? wxString(_("noname.mut")) 
    : wxFileName(path).GetFullName();
	
    MutEditFile * editor = new MutEditFile(this, wxPoint(0, 0), wxDefaultSize);
    client = editor;

#ifdef DEBUG
    std::cout << "MutFrame::OpenFile(): Loading " << (path.fn_str()) << std::endl;
#endif
    if (!(!path))
      editor->LoadFile(path);
    
    auimanager.AddPane(client,wxAuiPaneInfo().
		       Caption(filename).CenterPane().PaneBorder(false));
    
    editor->SetSelection(0, 0);
    SetTitle(wxString().Format(_("%s -- %s"),APPNAME,filename.c_str()));
	
    auimanager.Update();
    return true;
}


// Logic-Arbeit: CmDoActivate, CmStop, CmPanic, CmExecute


void UpdateUIcallback()
{
	if ( theFrame )
	{
		wxCommandEvent *event1 = 
		  new wxCommandEvent(wxEVT_COMMAND_MENU_SELECTED, 
				     CM_UPDATEUI);
		theFrame->AddPendingEvent(*event1);
		delete (event1);
	}
}

void MutFrame::CmDoActivate(wxCommandEvent& event)
{
  if (LogicOn) return;

#ifdef DEBUG
  std::cout << "MutFrame::CmDoActivate" << std::endl;
#endif
  if ( !Compiled )
    return;

  wxGetApp().SaveState();
#ifdef DEBUG
  DEBUGLOG(_T("Restoring state for debugging"));
  wxGetApp().RestoreState();
#endif

  ScanDevices();
  AktionTraceReset();

  // aktivieren
#ifndef NOACTIVATE
#ifdef DEBUG
  std::cerr << "MutFrame::CmDoActivate: Activate" << std::endl;
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
  std::cerr << "MutFrame::CmDoActivate: Initialize state" << std::endl;
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
  if ( !BoxUsed[curBox] ) {
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
  std::cout << "MutFrame::CmDoActivate: One window mode: " << OWM << std::endl;
#endif
  // Fenster außer curBox setzen
  if ( !OWM )
    for (WinKind kind = WK_KEY; kind < WK_LOGIC; kind++)
      for (size_t i = 0; i < WinAttrs[kind].GetCount(); i++)
	if ( WinAttrs[kind][i].Box != curBox
	     &&  WinAttrs[kind][i].Wanted )
	  TextBoxOpen(kind, WinAttrs[kind][i].Box);
  
  UpdateBoxMenu();  
  MutFrame * routewin = dynamic_cast<MutFrame *>(FindWindowById(WK_ROUTE));
  if ( routewin ) routewin->UpdateBoxMenu();

#ifdef DEBUG
  std::cout << "MutFrame::CmDoActivate: Open Logic window" << std::endl;
#endif
  // curBox-Fenstersetzen
  //  LogicWinOpen(curBox);
  LogicOn = true;
  // Toolbar
  /*2	ControlBar->Remove(*ButtonActivate);
	ControlBar->Insert(*ButtonStop, TGadgetWindow::Before, ButtonPanic);
	ControlBar->LayoutSession();*/
	// Statusbar
  SetStatus(SG_LOGIC);
#ifdef DEBUG
  std::cout << "MutFrame::CmDoActivate: Open Text boxes: " 
	    << WK_KEY << "--" <<WK_ACT << std::endl;
#endif
  for (size_t i = 0; i < MAX_BOX; i++)
    for (WinKind kind = WK_KEY; kind <= WK_ACT; kind++) {
      if ( TextBoxWanted[i][kind] )
	TextBoxOpen(kind, i);
      else
	DontWant(kind, i);
  }



#ifdef DEBUG
  std::cout << "MutFrame::CmDoActivate: Set window title" << std::endl;
#endif
  //	Get(WK_LOGIC, curBox)->Win->SetFocus();
#ifdef DEBUG
  std::cout << "MutFrame::CmDoActivate: Repaint route" << std::endl;
#endif
  repaint_route();
#ifdef DEBUG
  std::cout << "MutFrame::CmDoActivate: event.Skip()" << std::endl;
#endif
  event.Skip(false);
}

wxMenuItem * MutFrame::ClearMenuItem(int id) {
  wxMenuItem * item = GetMenuBar()->FindItem(id);
  if (item->IsSubMenu()) 
    ClearSubMenu(item);
  return item;
}

void MutFrame::ClearSubMenu(wxMenuItem * item) {

  wxMenu * menu = item->GetSubMenu();
#ifdef DEBUG
  std::cout << "MutFrame::ClearSubMenu: " 
	    << (item->GetText()).ToUTF8()
	    << " (" << item << ")"
	    << std::endl;
#endif
  if (! menu) return;

  

  wxMenuItemList& l = menu->GetMenuItems();
#ifdef DEBUG
  std::cout << l.GetCount() << " items"
	    << std::endl;
#endif
  while (wxMenuItemList::Node * node = l.GetFirst()) {
    wxMenuItem * i = node->GetData();
#ifdef DEBUG
    std::cout << "MutFrame::ClearSubMenu: ptr" << i << std::endl;
    std::cout << "MutFrame::ClearSubMenu: handling " 
	      << (i->GetText()).ToUTF8()
	      << std::endl;
#endif
    if (i->IsSubMenu()) 
      ClearSubMenu(i);
    Disconnect(i->GetId(),wxEVT_COMMAND_MENU_SELECTED);
#ifdef DEBUG
    std::cout << "MutFrame:: ClearSubMenu: destroying " 
	      << (i->GetText()).ToUTF8()
	      << std::endl;
#endif
    //    node->GetNext();
    menu->Destroy(i);
  }
}

void MutFrame::RaiseLogic(wxCommandEvent& event) {
  if (!RaiseTheFrame()) {
    DEBUGLOG(_T("Calling Logic frame for id %d"), event.GetId());
    theFrame -> RaiseLogic(event);
    return;
  }

  DEBUGLOG(_T("Reached logic frame"));
  wxASSERT(theFrame == this);
  DEBUGLOG(_T("%d"),event.GetId());

  size_t i = 0;
  while (i < MAX_BOX && boxCommandIds[i] != event.GetId()) i++;
  wxASSERT(i!=MAX_BOX);

  DEBUGLOG(_T("%d"),i);

  curBox = i;

  if (WinAttrs[WK_LOGIC][i].Win) {
    WinAttrs[WK_LOGIC][i].Win->SetFocus();
    
    wxFrame * win = 
      dynamic_cast<wxFrame *>(WinAttrs[WK_LOGIC][i].Win->GetParent());
    if (win) win->Raise();
    DEBUGLOG(_T("Parent type: ")) 
      << typeid(*( WinAttrs[WK_LOGIC][i].Win->GetParent())).name()
      << std::endl;

    GetMenuBar()->Check(event.GetId(),true);
  }
}

void MutFrame::DoStop() 
{
  if ( LogicOn ) {
    LogicOn = false;
    StopInDev();
    Stop();

    // Ampel umschalten
    /*		ControlBar->Remove(*ButtonStop);
		ControlBar->Insert(*ButtonActivate, TGadgetWindow::Before, ButtonPanic);
		ControlBar->LayoutSession();*/
    // Statusleiste
    SetStatus(SG_NOTHING);
    //		StatusBar->SetText("");
    // Titel
    //    SetTitle(APPNAME);
		// alle Fenser schlieﬂen
    wxMenuItem * boxSelector = ClearMenuItem(CM_SELECTBOX);
    wxASSERT(boxSelector->IsSubMenu());

    for (WinKind kind = WK_KEY; kind <= WK_LOGIC; kind++)
      theFrame->CloseAll(kind);
    
    AktionTraceReset();
    repaint_route();
    theFrame = NULL;
  }
}

void MutFrame::CmStop(wxCommandEvent& event)
{
  DoStop();
}

void MutFrame::CmPanic(wxCommandEvent& WXUNUSED(event))
{
  if ( LogicOn )
    Panic();
}

void MutFrame::CeExecute(wxUpdateUIEvent& event)
{
  //	event.Enable(!LogicOn && (Compiled || ActiveWinKind == WK_EDIT));
	event.Enable(!LogicOn);
}


void MutFrame::CeActivate(wxUpdateUIEvent& event)
{
  //	event.Enable(!LogicOn && (Compiled || ActiveWinKind == WK_EDIT));
  event.Enable(!LogicOn && (dynamic_cast<MutEditFile *>(client)));
}

void MutFrame::CeStop(wxUpdateUIEvent& event)
{
	event.Enable(LogicOn);
}

// Routenfenster anzeigen

void MutFrame::CmRoutes(wxCommandEvent& event)
{
  if ( GetId()== WK_ROUTE ) {
#ifdef DEBUG
    std::cerr << "MutFrame::CmRoutes: setting Focus" << std::endl;
#endif
    auimanager.Update();
    Raise();
    return;
  }
  
  if (client) {
    event.Skip(true);
    return;
  }

//	MutFrame *subframe = new MutFrame((wxFrame *) NULL,WK_ROUTE, wxString().Format(_("%s -- Routes"),_(PACKAGE_NAME)),
//		wxDefaultPosition,wxDefaultSize,wxDEFAULT_FRAME_STYLE | wxHSCROLL | wxVSCROLL);
//	subframe->SetIcon(ICON(route));

  SetId(WK_ROUTE);
  int width, height;
  GetClientSize(&width, &height);
  client = new MutRouteWnd(this, wxPoint(0, 0), wxSize(width, height));
  auimanager.AddPane(client,wxAuiPaneInfo().Caption(_("Routes")).CenterPane().PaneBorder(false));
  auimanager.Update();
  SetIcon(ICON(route));
  if (LogicOn) UpdateBoxMenu();

//	subframe->Show(true);
  
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
    MutLogicWnd *client = new MutLogicWnd(this, box, 
					  wxPoint(0, 0), 
					  wxSize(width,height));
    wxString Name;
    Name.Printf(_("Logic -- Box %d"),box);
#ifdef DEBUG
    std::cout << "Adding pane '" 
	      << Name.Format(_T("Logic%d"),box).ToUTF8()
	      << "' with caption '" << Name.ToUTF8() << "'"
	      << std::endl;
#endif
    auimanager.AddPane(client,
		       wxAuiPaneInfo().Name(Name.Format(_T("Logic%d"),box))
		       .Caption(Name)
		       .Bottom()
		       .Floatable(true)
		       .CloseButton(false)
		       .MaximizeButton(true)
		       .Float());
    client->SetFocus();
    auimanager.Update();
}

void MutFrame::ToggleTextBox(WinKind kind)
{
#ifdef DEBUG
  std::cerr << "MutFrame::ToggleTextBox: kind: " << kind << std::endl
	    << "MutFrame::ToggleTextBox: TextBoxWanted:"
	    << TextBoxWanted[curBox][kind] << std::endl;
#endif
  TextBoxWanted[curBox][kind] = !TextBoxWanted[curBox][kind];
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
    auimanager.DetachPane(win);
    win->Close();
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
  std::cout << "Mutframe::TextBoxOpen: " << box << std::cout;
#endif
	char *s = NULL;
	wxString title;
	switch ( kind ) {
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
	case WK_LOGIC:
	  wxLogWarning(_("Unexpected value: WK_LOGIC"));
	  break;
	case WK_ROUTE:
	  wxLogWarning(_("Unexpected value: WK_ROUTE"));
	  break;
	case WK_EDIT:
	  wxLogWarning(_("Unexpected value: WK_EDIT"));
	  break;
	case WK_NULL:
	  wxLogWarning(_("Unexpected value: WK_NULL"));
	  break;
	default:
	  wxLogError(_("Unexpected window kind: %d"), kind); 
	}

	int width, height;
	GetClientSize(&width, &height);
	width /= 2;
	height /= 2;

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

	auimanager.AddPane(client,wxAuiPaneInfo().Caption(title)
			   .CloseButton(true).MaximizeButton(true)
			   .Float()
			   .Name(wxString::Format(_T("WK_%d_%d"),kind,box)));
	client->NewText(str, true);
	auimanager.Update();
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
	event.Check(TextBoxWanted[curBox][WK_KEY]);
}

void MutFrame::CeToggleTS(wxUpdateUIEvent& event)
{
  	event.Check(TextBoxWanted[curBox][WK_TS]);
}

void MutFrame::CeToggleAct(wxUpdateUIEvent& event)
{
  	event.Check(TextBoxWanted[curBox][WK_ACT]);
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

// Windowsize -------------------------------------------------------

wxSize subSize = wxDefaultSize;
 
int WSize[4][3] =
	{ { 640, 530, 252},
	{ 800, 646, 328},
	{1024, 826, 425},
	{1280, 994, 620} };

void MutFrame::WindowSize(MutChild *win)
{
  wxLogWarning(_("MutFrame::WindowSize:  not implemented" ));
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
  wxConfigBase *config = wxConfig::Get();

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
  //  int DeskMax = 1, WinMax = 2, HelpMax = 0;
  wxConfigBase *config = wxConfig::Get();
  int x=0, y=0, w=0, h=0;
  
  config->SetPath(_T("Desktop"));
  //  DeskMax=config->Read(_T("DeskMax"),0l);
  if ((x=config->Read(_T("X Position"),0l)) &&
      (y=config->Read(_T("Y Position"),0l)) &&
      (w=config->Read(_T("Width"),0l)) &&
      (h=config->Read(_T("Height"),0l))) {
    SetSize(x, y, w, h);

#ifdef DEBUG
    std::cerr << "x=" << x << ", y=" << y << ", w=" << w << ", h=" << h << std::endl;
#endif
  }
  config->SetPath(_T(".."));
  //  wxLogWarning(_("MutFrame::RestoreState() doesn't handle multiple windows"));
}

// Recorder-Knöpfe --------------------------------------------------

void MutFrame::StopInDev() {
  int nr = 0;
  for ( EDevice *In = InEDevices; In; In = In->Next, nr++)
    if ( In->Mode == MutaborDevicePlay || In->Mode == MutaborDevicePause )
      {
        In->Mode = MutaborDeviceStop;
        InDeviceAction(nr, In->Mode);
      }
  SetStatus(1-LogicOn);
}


void MutFrame::CmInDevStop(wxCommandEvent& WXUNUSED(event))
{
  StopInDev();
  repaint_route();
  SetStatus(1-LogicOn);
}

void MutFrame::CmInDevPlay(wxCommandEvent& event)
{
  DEBUGLOG(_T(""));
  if ( !LogicOn )
    CmDoActivate(event);
  int nr = 0;
  for ( EDevice *In = InEDevices; In; In = In->Next, nr++)
    if ( In->Mode == MutaborDeviceStop || 
	 In->Mode == MutaborDevicePause )
      {
        In->Mode = MutaborDevicePlay;
        InDeviceAction(nr, In->Mode);
      }
  repaint_route();
  SetStatus(SG_PLAY);
}

void MutFrame::CmInDevPause(wxCommandEvent& WXUNUSED(event))
{
  int nr = 0;
  for ( EDevice *In = InEDevices; In; In = In->Next, nr++)
    if ( In->Mode == MutaborDevicePlay )
      {
        In->Mode = MutaborDevicePause;
        InDeviceAction(nr, In->Mode);
      }
  repaint_route();
  SetStatus(SG_PAUSE);
}

void MutFrame::CeInDevStop(wxUpdateUIEvent& event)
{
  for ( EDevice *In = InEDevices; In; In = In->Next)
    if ( In->DT >= DTMidiFile && 
	 (In->Mode == MutaborDevicePlay || 
	  In->Mode == MutaborDevicePause) )
    {
      event.Enable(true);
      return;
    }
  event.Enable(false);
}

void MutFrame::CeInDevPlay(wxUpdateUIEvent& event)
{
  if ( !LogicOn ) {
    DEBUGLOG(_T("Logic is off"));
    event.Enable(false);
    return;
  }

  for ( EDevice *In = InEDevices; In; In = In->Next) {
    DEBUGLOG(_T("checking Device type %d >= %d with mode %d for pointer %p"),
	     In->DT,
	     DTMidiFile,
	     In->Mode,
	     In);
    if ( In->DT >= DTMidiFile && 
	 (In->Mode == MutaborDeviceStop || 
	  In->Mode == MutaborDevicePause) ) {
      DEBUGLOG(_T("Device can be activated"));
      event.Enable(true);
      return;
    }
    DEBUGLOG(_T("Device can not be activated"));
  }
  event.Enable(false);
}

void MutFrame::CeInDevPause(wxUpdateUIEvent& event)
{
  bool Pause = 0;
  for ( EDevice *In = InEDevices; In; In = In->Next)
    if ( In->DT >= DTMidiFile )
      if ( In->Mode == MutaborDevicePlay ) {
        event.Enable(true);
        if ( curStatusImg != SG_PLAY )
          SetStatus(SG_PLAY);
        return;
      }
      else if ( In->Mode == MutaborDevicePause )
        Pause = true;
  if ( Pause ) {
    if ( curStatusImg != SG_PAUSE )
      SetStatus(SG_PAUSE);
  } else if ( curStatusImg != 1-LogicOn )
      SetStatus(1-LogicOn);

  event.Enable(false);
}

void MutFrame::CmSetTitle(wxCommandEvent& event) {
  SetTitle(wxString::Format(_("%s -- %s"), APPNAME, event.GetString().c_str()));
}

// Updaten der Protokollfenster
void MutFrame::UpdateUI(wxCommandEvent& WXUNUSED(event))
{
  for (size_t i = 0; i < WinAttrs[WK_KEY].GetCount(); i++) {
      WinAttr *winAttr = &WinAttrs[WK_KEY][i];
      if ( winAttr->Win && KeyChanged(winAttr->Box) )
	((MutTextBox*)winAttr->Win)->
	  NewText(GetKeyString(winAttr->Box, asTS), 1);
  }
  for (size_t i = 0; i < WinAttrs[WK_TS].GetCount(); i++) {
    WinAttr *winAttr = &WinAttrs[WK_TS][i];
    if ( winAttr->Win && TSChanged(winAttr->Box) )
      ((MutTextBox*)winAttr->Win)->
	NewText(GetTSString(winAttr->Box, asTS), 1);
  }

  // Aktionen
  if ( TakeOverAktions() )
    if ( CAW ) {
      WinAttr *winAttr = Get(WK_ACT, curBox);
      if ( winAttr && winAttr->Win )
	((MutTextBox*)winAttr->Win)->NewText(GenerateCAWString(), 1);
    } else {
      for (size_t i = 0; i < WinAttrs[WK_ACT].GetCount(); i++) {
	WinAttr *winAttr = &WinAttrs[WK_ACT][i];
	if ( winAttr->Win && ACTChanged(winAttr->Box) )
	  ((MutTextBox*)winAttr->Win)->
	    NewText(GenerateACTString(winAttr->Box), 1);
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
  if ( InDevicesChanged() ) {
    enum MutaborModeType Mode[256];
    GetInDevicesMode(Mode);
    bool NRT_Finish = false;
    for (EDevice *In = InEDevices; In; In = In->Next) {
      if ( In->Nr != -1 )
	if ( Mode[In->Nr] == 4 ) {
	  In->Mode = MutaborDeviceStop;
	  InDeviceAction(In->Nr, In->Mode);
	  NRT_Finish = !RealTime;
	} else {
	  In->Mode = Mode[In->Nr];
	}
    }

    repaint_route();
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

void MutFrame::CmRouteLoad(wxCommandEvent& event)
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

  //  RouteConfig = text;
  ScanRoutes(text);

  wxCommandEvent ev(wxEVT_COMMAND_MENU_SELECTED,CM_ROUTES);
  wxGetApp().ProcessEvent(ev);
  
}

void
MutFrame::CmRouteSave(wxCommandEvent& event)
{
  DEBUGLOGTYPE(MutFrame,_T(""));
  event.Skip(false);
  
  if (!MurFileData.name.IsOk() )
  {
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
  WriteRoutes(RouteConfig);
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

void
MutFrame::CmRouteSaveAs(wxCommandEvent& event)
{
  DEBUGLOGTYPE(MutFrame,_T("")); 

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

wxRect MutFrame::DetermineFrameSize () {
  DEBUGLOG(_T(""));

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

/// Close all child windows of given kind
/** This function closes all child windows of the given kind. 
 *
 * \param kind any wk_kind, that describes which kind of windows shall
 * be closed.  
 */
void MutFrame::CloseAll(WinKind kind) {
  DEBUGLOG(_T(""));

  auimanager.Update();
  for (size_t i = WinAttrs[kind].Count(); i >0; i--) {
    DEBUGLOG(_T("kind %d (%d of %d)"),kind,i,WinAttrs[kind].Count());
    WinAttr &win = WinAttrs[kind].Item(i-1);
    if ( win.Win )
      {
	
	win.Wanted = 2;

	DEBUGLOG(_T("Update."));
	auimanager.ClosePane(auimanager.GetPane(win.Win));
	auimanager.DetachPane(win.Win);
	DEBUGLOG(_T("Detaching pane."));
	auimanager.Update();
	//	auimanager.DetachPane(win.Win);

	//       	win.Win->Close();

	DEBUGLOG(_T("Destroying window."));
	win.Win->Close(); // win should be invalid now.
      }
  }
}

void MutFrame::UpdateBoxMenu() {
#ifdef DEBUG
  std::cout << "MutFrame::CmDoActivate: Set Box selection menu" << std::endl;
#endif
  wxMenuItem * boxSelector = ClearMenuItem(CM_SELECTBOX);
  wxASSERT(boxSelector->IsSubMenu());
  wxMenu * boxMenu = boxSelector->GetSubMenu();
  //  wxID_HIGHEST
  //  wxMenu * 

  for (size_t i = 0, j=0; i < MAX_BOX; i++) {
    if (BoxUsed[i]) {
      if (theFrame == this) LogicWinOpen(i);
      if (!boxCommandIds[i]) {
	boxCommandIds[i]=wxNewId();
	DEBUGLOG(_("Box %d got id %d"),i,boxCommandIds[i]);
      }
      DEBUGLOG(_("Appending menu for box %d with id %d"),i,boxCommandIds[i]);
      boxMenu->Append(boxCommandIds[i],
		      wxString::Format(_("Select box %d\tCtrl+%d"),i,i),
		      wxString::Format(_("Select box %d as the active Box for box specific commands."),i), wxITEM_RADIO);
      if (i == curBox) boxMenu->Check(boxCommandIds[i],true);
      DEBUGLOG(_("Connecting command with id %d for box %d"),
	       i,boxCommandIds[i]);
      Connect( boxCommandIds[i],
	       wxEVT_COMMAND_MENU_SELECTED,
	       wxCommandEventHandler(MutFrame::RaiseLogic) );

    }
  }
}

bool MutFrame::RaiseTheFrame() {
  if (this == theFrame) return true;

  theFrame->Raise();
  return false;
}
//\}
