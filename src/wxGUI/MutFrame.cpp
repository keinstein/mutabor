/** \file MutFrame.cpp
********************************************************************
* Mutabor Frame.
*
* Copyright:   (c) 2005,2006,2007-2011 TU Dresden
* changes by Tobias Schlemmer (c) 2012
* \author Rüdiger Krauße <krausze@mail.berlios.de>
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
* \addtogroup GUI
* \{
********************************************************************/


// ===========================================================================
// declarations
// ===========================================================================

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

#include "src/kernel/Defs.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#include "wx/toolbar.h"
#include "wx/image.h"

#include "Images/Icons/xpm/Route.xpm"

#include "wx/filename.h"
#include "wx/config.h"
#include "wx/confbase.h"
#include "wx/fileconf.h"
#include "wx/stc/stc.h"
#ifdef __WXMSW__
#  include <wx/msw/regconf.h>
#endif
#include "wx/ffile.h"
#include "src/wxGUI/GUIBoxData.h"
#include "src/wxGUI/MutFrame.h"
#include "src/wxGUI/MutDocument.h"
#include "src/wxGUI/MutView.h"
#include "src/wxGUI/MutChild.h"
#include "src/wxGUI/MutApp.h"

#include "src/wxGUI/generic/mhDefs.h"
#include "src/kernel/Runtime.h"
#include "src/wxGUI/MutRouteWnd.h"
#include "src/wxGUI/MutLogicWnd.h"
#include "src/wxGUI/MutTextBox.h"
#include "src/wxGUI/MutBitmaps.h"
#include "src/wxGUI/GUIBoxData.h"
#include "src/wxGUI/Routing/DebugRoute.h"
#include "src/kernel/routing/Route-inlines.h"

using namespace mutabor;
using namespace mutaborGUI;

namespace mutaborGUI {

#define OPENMENU				\
	menu = new wxMenu;

#define CLOSEMENU(name)				\
	menuBar->Append(menu, name);

#define MENUITEM(name, id, help)		\
	menu->Append(id, name, help)

#define MENUCHECKITEM(name, id, help)		\
	menu->AppendCheckItem(id, name, help)

#define MENUITEM_ADD(name, id, help, add)	\
	menu->Append(id, name, help, add)

#define MENUITEM_SEPARATOR			\
	menu->AppendSeparator()

// ---------------------------------------------------------------------------
// global variables
// ---------------------------------------------------------------------------

#ifndef HAVE_CONFIG_H
#  define PACKAGE_NAME "Mutabor"
#endif

#define APPNAME _(PACKAGE_NAME)

//wxString RcfFile = wxT("Routes.cfg");
	bool demo = false;

	bool asTS = true;
	bool SaveEditor = true;
	bool UseColorBars = true;
	bool OWM = false; // One Window Mode
	bool CAW = false; // Common Action Window
	bool LogicOn = false;
	wxWindow *ChildToClose = NULL;

	wxString CompiledFile;

	char WinName[5][12] = { "KEYWIN", "TONSYSTWIN", "ACTIONWIN", "LOGICWIN", "ROUTEWIN" };

	std::map<int,mutabor::Box> MutFrame::boxCommandIds;

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

	BEGIN_EVENT_TABLE(MutFrame, wxDocChildFrame)
	EVT_ERASE_BACKGROUND(MutFrame::OnEraseBackground)
	EVT_SIZE(MutFrame::OnSize)

	//        EVT_MENU(CM_EXECUTE, MutFrame::CmFileOpen)
	//	EVT_MENU(CM_FILESAVE, MutFrame::PassEventToEditor)
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
	EVT_UPDATE_UI(wxID_UNDO, MutFrame::PassEventToEditorUI)
	EVT_UPDATE_UI(wxID_REDO, MutFrame::PassEventToEditorUI)
	EVT_MENU(CM_COMPILE, MutFrame::PassEventToEditor)
	EVT_MENU(CM_COMPACT, MutFrame::PassEventToEditor)
	EVT_MENU(CM_ACTIVATE,MutFrame::PassEventToEditor)
        EVT_MENU(CM_PROPERTIES, MutFrame::PassEventToEditor)
	EVT_MENU(CM_GETLINE, MutFrame::PassEventToEditor)
	EVT_MENU(CM_MOVE_UP, MutFrame::PassEventToEditor)
	EVT_MENU(CM_MOVE_DOWN, MutFrame::PassEventToEditor)
	EVT_MENU (wxID_CLEAR,            MutFrame::PassEventToEditor)
	EVT_MENU (wxID_CUT,              MutFrame::PassEventToEditor)
	EVT_MENU (wxID_COPY,             MutFrame::PassEventToEditor)
	EVT_MENU (wxID_PASTE,            MutFrame::PassEventToEditor)
	EVT_MENU (CM_INDENTINC,        MutFrame::PassEventToEditor)
	EVT_MENU (CM_INDENTRED,        MutFrame::PassEventToEditor)
	EVT_MENU (wxID_SELECTALL,        MutFrame::PassEventToEditor)
	EVT_MENU (CM_SELECTLINE,       MutFrame::PassEventToEditor)
	EVT_MENU (wxID_REDO,             MutFrame::PassEventToEditor)
	EVT_MENU (wxID_UNDO,             MutFrame::PassEventToEditor)
	// find
	EVT_MENU (wxID_FIND,             MutFrame::PassEventToEditor)
	EVT_MENU (CM_FINDNEXT,         MutFrame::PassEventToEditor)

	EVT_MENU (wxID_REPLACE,          MutFrame::PassEventToEditor)
	EVT_MENU (CM_REPLACENEXT,      MutFrame::PassEventToEditor)
	EVT_MENU (CM_BRACEMATCH,       MutFrame::PassEventToEditor)
	EVT_MENU (CM_GOTO,             MutFrame::PassEventToEditor)
	EVT_FIND(wxID_ANY,               MutFrame::PassEventToEditorFind)
	EVT_FIND_NEXT(wxID_ANY,          MutFrame::PassEventToEditorFind)
	EVT_FIND_REPLACE(wxID_ANY,       MutFrame::PassEventToEditorFind)
	EVT_FIND_REPLACE_ALL(wxID_ANY,   MutFrame::PassEventToEditorFind)
	EVT_FIND_CLOSE(wxID_ANY,         MutFrame::PassEventToEditorFind)
	// view
	EVT_MENU_RANGE (CM_HILIGHTFIRST, CM_HILIGHTLAST,
			MutFrame::PassEventToEditor)
	EVT_MENU (CM_DISPLAYEOL,       MutFrame::PassEventToEditor)
	EVT_MENU (CM_INDENTGUIDE,      MutFrame::PassEventToEditor)
	EVT_MENU (CM_LINENUMBER,       MutFrame::PassEventToEditor)
	EVT_MENU (CM_LONGLINEON,       MutFrame::PassEventToEditor)
	EVT_MENU (CM_WHITESPACE,       MutFrame::PassEventToEditor)
	EVT_MENU (CM_FOLDTOGGLE,       MutFrame::PassEventToEditor)
	EVT_MENU (CM_OVERTYPE,         MutFrame::PassEventToEditor)
	EVT_MENU (CM_READONLY,         MutFrame::PassEventToEditor)
	EVT_MENU (CM_WRAPMODEON,       MutFrame::PassEventToEditor)
	// extra
	EVT_MENU (CM_CHANGELOWER,      MutFrame::PassEventToEditor)
	EVT_MENU (CM_CHANGEUPPER,      MutFrame::PassEventToEditor)
	EVT_MENU (CM_CONVERTCR,        MutFrame::PassEventToEditor)
	EVT_MENU (CM_CONVERTCRLF,      MutFrame::PassEventToEditor)
	EVT_MENU (CM_CONVERTLF,        MutFrame::PassEventToEditor)
	EVT_MENU (CM_CHARSETANSI,      MutFrame::PassEventToEditor)
	EVT_MENU (CM_CHARSETMAC,       MutFrame::PassEventToEditor)
	EVT_MENU (CM_CHARSETUTF8,       MutFrame::PassEventToEditor)
	//    EVT_MENU(CM_ROUTES, MutFrame::CmRoutes)

#if wxCHECK_VERSION(2,9,4)
	EVT_AUI_PANE_ACTIVATED(MutFrame::OnAuiChildEvent)
#endif
	EVT_AUI_PANE_CLOSE(MutFrame::OnAuiChildEvent)
	EVT_MENU(CM_TOGGLEKEY, MutFrame::CmToggleKey)
	EVT_MENU(CM_TOGGLETS, MutFrame::CmToggleTS)
	EVT_MENU(CM_TOGGLEACT, MutFrame::CmToggleAct)
	EVT_MENU(CM_OWM, MutFrame::CmToggleOWM)
	EVT_MENU(CM_CAW, MutFrame::CmToggleCAW)
	EVT_MENU(CM_BOX, MutFrame::RaiseLogic)

	EVT_UPDATE_UI(CM_TOGGLEKEY, MutFrame::CeToggleKey)
	EVT_UPDATE_UI(CM_TOGGLETS, MutFrame::CeToggleTS)
	EVT_UPDATE_UI(CM_TOGGLEACT, MutFrame::CeToggleAct)
	EVT_UPDATE_UI(CM_OWM, MutFrame::CeToggleOWM)
	EVT_UPDATE_UI(CM_CAW, MutFrame::CeToggleCAW)
	EVT_UPDATE_UI(CM_BOX, MutFrame::CeStop)

	EVT_MENU(CM_INDEVSTOP, MutFrame::CmInDevStop)
	EVT_MENU(CM_INDEVPLAY, MutFrame::CmInDevPlay)
	EVT_MENU(CM_INDEVPAUSE, MutFrame::CmInDevPause)
	EVT_UPDATE_UI(CM_INDEVSTOP, MutFrame::CeInDevStop)
	EVT_UPDATE_UI(CM_INDEVPLAY, MutFrame::CeInDevPlay)
	EVT_UPDATE_UI(CM_INDEVPAUSE, MutFrame::CeInDevPause)
	//    EVT_ACTIVATE(MutFrame::OnActivate)

	EVT_CLOSE(MutFrame::OnCloseWindow)
	EVT_MENU(CM_UPDATEUI, MutFrame::UpdateUI)
	//	EVT_IDLE(MutFrame::OnIdle)
	EVT_MENU(CM_SETTITLE, MutFrame::CmSetTitle)
	//    EVT_SIZE(MutFrame::OnSize)
	END_EVENT_TABLE()

	// ========================================================================
	// implementation
	// ========================================================================

	// ------------------------------------------------------------------------
	// MutFrame
	// ------------------------------------------------------------------------

	MutFrame * MutFrame::ActiveWindow = NULL;

	// Define my frame constructor
	MutFrame::MutFrame(wxFrame *parent,

			   const wxWindowID id,
			   const wxString& title,
			   const wxPoint& pos,
			   const wxSize& size,
			   const long style): wxDocChildFrame(NULL,
							      NULL,
							      parent,
							      id,
							      title,
							      pos,
							      size,
							      style | wxNO_FULL_REPAINT_ON_RESIZE |wxTAB_TRAVERSAL),
					      curStatusImg(0),
					      auimanager(this,wxAUI_MGR_DEFAULT |
							 wxAUI_MGR_ALLOW_ACTIVE_PANE | wxAUI_MGR_LIVE_RESIZE)
	{

		SetSize (DetermineFrameSize ());
		client = NULL;
		editmenu = filemenu = NULL;

#if wxUSE_TOOLBAR
#if 0
		wxToolBar * tb = new  wxToolBar(this,
						wxID_ANY,
						wxDefaultPosition,
						wxDefaultSize);
#else
		wxToolBar * tb = CreateToolBar(wxTB_DOCKABLE);
#endif
		InitToolBar(tb);

#if 0
		auimanager.AddPane(tb, wxAuiPaneInfo().
				   Name(_T("tb")).Caption(_("Toolbar")).
				   ToolbarPane().Top().
				   LeftDockable(false).RightDockable(false));
#endif
#endif // wxUSE_TOOLBAR


		// Accelerators
		/*    wxAcceleratorEntry entries[3];
		      entries[0].Set(wxACCEL_CTRL, (int) 'N', MDI_NEW_WINDOW);
		      entries[1].Set(wxACCEL_CTRL, (int) 'X', MDI_QUIT);
		      entries[2].Set(wxACCEL_CTRL, (int) 'A', MDI_ABOUT);
		      wxAcceleratorTable accel(3, entries);
		      SetAcceleratorTable(accel);*/
	}

	MutFrame::MutFrame(MutDocument *doc,
			   MutView *v,
			   wxFrame *frame,
			   wxWindowID id,
			   const wxString& title,
			   const wxPoint& pos,
			   const wxSize& size,
			   long type,
			   const wxString& name):
		wxDocChildFrame(doc,v,frame,id,title,pos,size,type|wxTAB_TRAVERSAL,name),
		curStatusImg(0)
	{

		SetSize (DetermineFrameSize ());
		client = NULL;
		editmenu = filemenu = NULL;

		auimanager.SetManagedWindow(this);


#if wxUSE_TOOLBAR
#if 0
		wxToolBar * tb = new  wxToolBar(this,
						wxID_ANY,
						wxDefaultPosition,
						wxDefaultSize,
						0);
#else
		wxToolBar * tb = CreateToolBar(wxTB_DOCKABLE);
#endif
		InitToolBar(tb);

#if 0
		auimanager.AddPane(tb, wxAuiPaneInfo().
				   Name(_T("tb")).Caption(_("Toolbar")).
				   ToolbarPane().Top().
				   LeftDockable(false).RightDockable(false));
#endif
#endif // wxUSE_TOOLBAR


		// Accelerators
		/*    wxAcceleratorEntry entries[3];
		      entries[0].Set(wxACCEL_CTRL, (int) 'N', MDI_NEW_WINDOW);
		      entries[1].Set(wxACCEL_CTRL, (int) 'X', MDI_QUIT);
		      entries[2].Set(wxACCEL_CTRL, (int) 'A', MDI_ABOUT);
		      wxAcceleratorTable accel(3, entries);
		      SetAcceleratorTable(accel);*/
	}




	MutFrame::~MutFrame()

	{
		if (filemenu && wxGetApp().GetDocumentManager()) {
			wxGetApp().GetDocumentManager()->FileHistoryRemoveMenu(filemenu);
		}
		if (m_childView) {
			mutASSERT(dynamic_cast<MutView *>(m_childView));
			MutView * v = (MutView *) m_childView;
			v->SetFrame(NULL);
			v->SetTextsw(NULL);
		}
		auimanager.UnInit();

//	while (wxGetApp().Pending()) wxGetApp().Dispatch();
	}

#if wxUSE_TOOLBAR
	void MutFrame::InitToolBar(wxToolBar* toolBar)
	{

		// Stock Id's are currently not availlable for wxToolBar() :-(
		MutToolBarBitmaps::Init();
		toolBar->SetToolBitmapSize(wxSize(16,16));
		toolBar->AddTool(CM_FILENEW, _("New"), MutToolBarBitmaps::New, _("New file"));
		toolBar->AddTool(CM_FILEOPEN, _("Open"), MutToolBarBitmaps::Open , _("Open file"));
		toolBar->AddTool(CM_FILESAVE, _("Save"), MutToolBarBitmaps::Save, _("Save file"));
		toolBar->AddTool(CM_FILESAVEAS, _("Save as"), MutToolBarBitmaps::SaveAs, _("Save file with new name"));
		toolBar->AddTool(wxID_PRINT, _("Print"), MutToolBarBitmaps::Print, _("Print"));
		toolBar->AddSeparator();
		toolBar->AddTool(CM_ACTIVATE, _("Activate"), MutToolBarBitmaps::LogicActivate, _("Activate the logic"));
		toolBar->AddTool(CM_STOP, _("Stop"), MutToolBarBitmaps::LogicStop, _("Stop the logic"));
		toolBar->AddTool(CM_PANIC, _("Panic"), MutToolBarBitmaps::LogicPanic, _("Panic: switch all notes off"));
		toolBar->AddSeparator();
		toolBar->AddTool(wxID_UNDO, _("Undo"), MutToolBarBitmaps::Undo, _("Undo last changes"));
		toolBar->AddTool(wxID_REDO, _("Redo"), MutToolBarBitmaps::Redo,  _("Redo last undone changes"));
		toolBar->AddTool(wxID_COPY, _("Copy"), MutToolBarBitmaps::Copy, _("Copy"));
		toolBar->AddTool(wxID_CUT, _("Cut"), MutToolBarBitmaps::Cut,  _("Cut"));
		toolBar->AddTool(wxID_PASTE, _("Paste"), MutToolBarBitmaps::Paste, _("Paste"));
		toolBar->AddSeparator();
		// \todo implement search and replace and corresponding toolbar buttons
		// toolBar->AddSeparator();
		toolBar->AddTool(CM_ROUTELOAD,_("&Load routes"), MutToolBarBitmaps::RouteLoad,
				 _("Load the current route configuration from a file"));
		toolBar->AddTool(CM_ROUTESAVE,_("&Save routes"), MutToolBarBitmaps::RouteSave,
				 _("Save current route configuration to a file."));
		toolBar->AddSeparator();
		toolBar->AddTool(CM_MOVE_UP,_("&Move Icon up"), MutToolBarBitmaps::GoUp,
				 _("Moves the device or box upwards in the window."));
		toolBar->AddTool(CM_MOVE_DOWN,_("&Move Icon down"), MutToolBarBitmaps::GoDown,
				 _("Moves the device or box downwards in the window."));
		toolBar->AddSeparator();
		toolBar->AddTool(CM_INDEVPLAY,_("&Play"), MutToolBarBitmaps::IndevsPlay,
				 _("Start playing the music from input file devices"));
		toolBar->AddTool(CM_INDEVSTOP,_("St&op"), MutToolBarBitmaps::IndevsStop,
				 _("Stop playing the music from input file devices"));
		toolBar->AddTool(CM_INDEVPAUSE,_("P&ause"), MutToolBarBitmaps::IndevsPause,
				 _("Pause plaing the music from input file devices"));
		toolBar->AddSeparator();
		toolBar->AddTool( CM_ABOUT, _("About"), MutToolBarBitmaps::About, _("Help"));
		toolBar->AddSeparator();
		toolBar->Realize();
	}

#endif // wxUSE_TOOLBAR

	void MutFrame::PassEventToEditor(wxCommandEvent &event)
	{
		if (event.GetEventType() != wxEVT_STC_STYLENEEDED) {
			event.Skip(false);
			switch (event.GetId()) {
			case CM_MOVE_UP:
			case CM_MOVE_DOWN:
				if (dynamic_cast<MutRouteWnd*>(client)) {
					wxPostEvent(client,event);
				}
				break;
			default:
				if (dynamic_cast<MutEditFile*>(client)) {
					wxPostEvent(client,event);
				}
			}
		}
	}

	void MutFrame::PassEventToEditorUI(wxUpdateUIEvent &event)
	{
		event.Skip(false);

		if (dynamic_cast<MutEditFile*>(client)) {
			client->GetEventHandler()->ProcessEvent(event);
		}
	}

	void MutFrame::PassEventToEditorFind(wxFindDialogEvent &event)
	{
		event.Skip(false);

		if (dynamic_cast<MutEditFile*>(client)) {
			client->GetEventHandler()->ProcessEvent(event);
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
		*/
		DEBUGLOG(eventqueue,_T("Skippen? %d, Propagate? %d"),
			 event.GetSkipped(), event.ShouldPropagate());


		//        if (!GetClientWindow()->ProcessEvent(event)) {
		//	std::cout << "Event ignoriert von:" << GetClientWindow()->GetName().fn_str() << std::endl;
		//

		wxWindow * frame = auimanager.GetManagedWindow();

		if (frame) {
			wxPostEvent(frame,event);
			std::cout << "Event " << event.ShouldPropagate() << " war da:"
				  << (frame->GetName().fn_str()) << std::endl;
		}

		//	}text.mb_str(*wxConvFileName)
		DEBUGLOG(other,_T("frame: %p"),(void*)frame);

		event.Skip();

	}

	void MutFrame::OnAuiChildEvent(wxAuiManagerEvent & event) {
		wxAuiPaneInfo * pane = event.GetPane();
		if (!pane) return;
		wxWindow * win = pane->window;
		int level = event.StopPropagation();
		win->GetEventHandler()->ProcessEvent(event);
		event.ResumePropagation(level);
	}

	void MutFrame::OnCloseWindow(wxCloseEvent& event)
	{

		TRACEC;
		DEBUGLOG (other, _T("%p == %p"),(void*)this,(void*)ActiveWindow);

		if ( event.CanVeto() ) {
			if (!static_cast<MutDocument *>(GetDocument())
			    ->CheckLogic()) {
				event.Veto();
				return;
			}
		}

		SaveState();


		// wxDocChildFrame will veto if there is no View associated
		if (m_childView) {
#if wxCHECK_VERSION(2,9,0)
			wxDocChildFrame::CloseView(event);
#else
			wxDocChildFrame::OnCloseWindow(event);
#endif
		} else
			Destroy();
	}

	void MutFrame::OnPaint(wxPaintEvent& event)
	{

		wxPaintDC dc(this);

		STUBC;
		mutUnused(event);
/* this code is just copied and must be changed
   to paint into the subwindow which is managed by
   the AUI manager.

   Propably it must be simply moved to the client window.
*/

		if (m_childView)
			m_childView->OnDraw(&dc);
	}




	void MutFrame::CmFileNew(wxCommandEvent& event)
	{
		STUBC;
		return;
#if 0
#ifdef DEBUG
		printf("MutFrame::CmFileNew\n");
#endif

		if (client) {
			event.Skip(true);
			return ;
		}

		event.Skip(false); // Its our task to try create the file

		OpenFile(wxEmptyString);
#endif
	}


	void MutFrame::CmFileOpen(wxCommandEvent& event)
	{
		STUBC;
		return;
#if 0
		if (client) {
			event . Skip (true);
			return;
		}

		event . Skip (false); // it's our task to try to open that file

		wxString path = FileNameDialog(this, event.GetId());

		if ( !path )
			return;


		DEBUGLOG(other,_T("%d == %d?"),(int)CM_EXECUTE, event.GetId());

		switch (event.GetId()) {

		case CM_FILEOPEN:
			OpenFile(path);

			break;

		case CM_EXECUTE: {
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
			UNREACHABLEC;
		}
#endif
	}

/**
 * open a file in a new frame.
 * \param path Path of the file to open
 * \todo file loading fails silently if it is not in the systems encoding.
 * */

	bool MutFrame::OpenFile (wxString path, bool newfile)
	{
		STUBC;
		mutUnused(newfile);
		return false;
#if 0
		if (client) return false;

		wxString filename = !path ? wxString(_("noname.mut"))
			: wxFileName(path).GetFullName();

		MutEditFile * editor = new MutEditFile(this, wxPoint(0, 0), wxDefaultSize);

		DEBUGLOG(other,_T("Loading %s"),(const wxChar *)path);

		if (!(!path))
			editor->LoadFile(path);

		editor->SetSelection(0, 0);
		SetTitle(wxString().Format(_("%s -- %s"),APPNAME,filename.c_str()));

		return SetClient(editor,filename);
#endif
	}
/**
 * Attach a client
 * \param window to  be attached as the client.
 * */

	bool MutFrame::SetClient (wxWindow * win, const wxString &title)
	{
		if (client || !win) {
			mutASSERT(!client);
			mutASSERT(win);
			return false;
		}

		DEBUGLOG(docview,_T("Setting client of %p to %p with title '%s'"),
			 (void*)this,
			 (void*)win,
			 (const wxChar *)title.c_str());

		client = win;
		SetTitle(title);
		auimanager.AddPane(client,wxAuiPaneInfo().
				   Caption(title).CenterPane().PaneBorder(false));
		auimanager.Update();
		return true;
	}


// Logic-Arbeit: CmDoActivate, CmStop, CmPanic, CmExecute

#if 0
	// Box Callback (updateuicallback)
	void MutFrame::BoxChanged(bool logic_changed) {
		BoxData & boxdata = ToGUIBase(box);

		wxCommandEvent event(wxEVT_COMMAND_MENU_SELECTED,
				     CM_UPDATEUI);

		MutChild * win = boxdata.GetKeyWindow();
		if (win) {
			wxPostEvent(win,event);
		}

		if (logic_changed) {
			win = boxdata.GetActionsWindow();
			if (win) wxPostEvent(win,event);

			win = boxdata.GetTonesystemWindow();
			if (win) wxPostEvent(win,event);
		}
	}
#endif


	void MutFrame::CmDoActivate(wxCommandEvent& event)
	{
		if (LogicOn) return;

		TRACEC;

		if ( !Compiled )
			return;

		wxGetApp().SaveState();



		// aktivieren
#ifndef NOACTIVATE
		DEBUGLOG(other,_T("Activate"));


		bool realtime = true;
		if ( !NeedsRealTime() ) {
			realtime = (wxMessageBox(_("There are no realtime \
instruments in the routes.\n	\
Shall Mutabor translate the files in batch mode, \
to keep the MIDI files with the original time stamp?\n \
(This means also, that you can't modify the tunings \
while playing by computer keyboard.)"),
						 _("No realtime ⇒ batch mode?"),
						 wxYES_NO | wxICON_QUESTION) != wxYES);
		}
		ActiveWindow = this;

		if (!mutabor::BoxClass::ActivateAll(realtime) )
			return;

#endif

		DEBUGLOG(other,_T("Initialize state"));

#if 0
// this should be done during ActivateAll

		mutabor::Box::ResetActions();

		// Initialize boxes
		// assure that all boxes are initialized as we might activeate
		// them during operation later

		for (int box = 0; box < MAX_BOX; box++) {
			BoxData & boxdata = BoxData::GetBox(box);
			boxdata.reset();
		}

		DEBUGLOG(other,_T("Check used boxes"));

		// curBox checken
		CheckBoxesUsed();


		// should be done by GUIBoxData

		if ( !mut_box[curBox].used ) {
			curBox = minimal_box_used;
		}



		size_t i = minimal_box_used;
		if (mut_box[i].used) {
			do {
				BoxWindowsOpen(i,false);
				i = mut_box[i].next_used;
			} while (i);
		}


#endif
		UpdateBoxMenu();
		MutFrame * routewin = dynamic_cast<MutFrame *>(FindWindowById(WK_ROUTE));
		if ( routewin ) routewin->UpdateBoxMenu();

		DEBUGLOG (gui, _T("Open other than logic; One window mode: %d"),OWM);


		DEBUGLOG (gui, _T("Open Logic window"));
		// curBox-Fenstersetzen
		//  LogicWinOpen(curBox);
		LogicOn = true;

		// Statusbar
		StatusBar::AllSetActive(LogicOn);
		StatusBar::AllSetPlaystate(StatusBar::Stop,false);

		DEBUGLOG (other, _T("Open Text boxes: %d -- %d"),WK_KEY,WK_ACT);

		Freeze();

		wxConfigBase *config = wxConfig::Get();
		if (config) {
			wxString oldpath = config -> GetPath();
			config->SetPath(_T("/Window Layout"));
			wxString auidata;
			auidata = config->Read(_T("AUI data"),wxEmptyString);
			if (!auidata.empty())
				auimanager.LoadPerspective(auidata,false);
			config->SetPath(oldpath);

			// some panes might have incorrect data (e.g. from earlier builds).
			wxAuiPaneInfoArray & panes = auimanager.GetAllPanes();
			int pane_i, pane_count = panes.GetCount();
			for (pane_i = 0; pane_i < pane_count; ++pane_i)
			{
				wxAuiPaneInfo& p = panes.Item(pane_i);
				p.Show();
				p.DestroyOnClose(true);
				MutChildApi * win = dynamic_cast<MutChildApi *>(p.window);
				if (win) p.Caption(win->MakeTitle());
			}
		}

		Thaw();
		auimanager.Update();

		DEBUGLOG (other, _T("Repaint route"));

		repaint_route();

		if (!realtime) {
			wxMessageBox(_("Please, configure the initial tuning, now.\n\
To start the translation hit the play button or select “Play” from the “Sequencer” Menu.\n"),
				     _("Realtime play"),
				     wxOK);
		}
		const mutabor::BoxListType & boxlist = mutabor::BoxClass::GetBoxList();
		for (mutabor::BoxListType::const_iterator boxptr = boxlist.begin();
		     boxptr != boxlist.end();
		     ++boxptr) {
			const BoxData * guibox = ToGUIBase(*boxptr);
			if (!guibox) continue;
			wxWindow * logic = guibox->GetLogicWindow();
			if (!logic) continue;
			logic -> SetFocus();
			break;
		}
	}

	wxMenuItem * MutFrame::ClearMenuItem(int id)
	{
		wxMenuItem * item = GetMenuBar()->FindItem(id);

		if (item->IsSubMenu())
			ClearSubMenu(item);

		return item;
	}

	void MutFrame::ClearSubMenu(wxMenuItem * item)
	{

		wxMenu * menu = item->GetSubMenu();
		DEBUGLOG (other, _T("item: '%s' on %p\n"),
			  (item->GetItemLabel()).c_str(),
			  (void*)item);

		if (! menu) return;

		menu->AppendSeparator(); // just to make sure, the item group is finished.


		wxMenuItemList& l = menu->GetMenuItems();

		DEBUGLOG (other, _T(" %d items"),(int)l.GetCount());

		for (wxMenuItemList::iterator i = l.begin(); i!=l.end(); i=l.begin()) {
			wxMenuItem * node = *i;
			DEBUGLOG (other, _T("ptr %p handling %s"),
				  (void*)node,(node->GetItemLabel()).c_str());

			if (node->IsSubMenu())
				ClearSubMenu(node);

			Disconnect(node->GetId(),wxEVT_COMMAND_MENU_SELECTED);

			DEBUGLOG (other, _T("destroying %s"),(node->GetItemLabel()).c_str());

			//    node->GetNext();
			menu->Destroy(node);
		}
	}

	void MutFrame::RaiseLogic(wxCommandEvent& event)
	{
		if (!RaiseTheFrame()) {
			DEBUGLOG (other, _T("Calling Logic frame for id %d"), event.GetId());
			ActiveWindow -> RaiseLogic(event);
			return;
		}

		DEBUGLOG (other, _T("Reached logic frame"));

		mutASSERT(ActiveWindow == this);
		DEBUGLOG (other, _T("%d"),event.GetId());

		bool is_current = (event.GetId() == CM_BOX);
		mutabor::Box box =
			is_current?
			GetCurrentBox():
			boxCommandIds[event.GetId()];
		if (!box) return;

		if (!is_current)
			SetCurrentBox(box);

		BoxData * boxdata = ToGUIBase(box);
		MutLogicWnd * w = boxdata->GetLogicWindow();
		if (w) {

			wxFrame * win =
				dynamic_cast<wxFrame *>(w->GetParent());

			if (win) win->Raise();

			DEBUGLOG (other, _T("Parent type: %s"),
				  muT(typeid(*( w->GetParent())).name()).c_str());

			if (!is_current)
				GetMenuBar()->Check(event.GetId(),true);
			w->SetFocus();
		}
	}

	void MutFrame::DoStop()
	{
		TRACEC;
		if ( LogicOn ) {
			wxConfigBase *config = wxConfig::Get();
			if (config) {
				wxString oldpath = config -> GetPath();
				config->SetPath(_T("/Window Layout"));
				config->Write(_T("AUI data"),
					      auimanager.SavePerspective());
				config->SetPath(oldpath);
			}
			LogicOn = false;
			StopInDev();
			mutabor::BoxClass::StopAll();

			// Statusleiste
			StatusBar::AllSetActive(LogicOn);
			StatusBar::AllSetPlaystate(StatusBar::Hide,true);
			// Titel
			//    SetTitle(APPNAME);
			// alle Fenser schlieﬂen
#ifdef DEBUG
			wxMenuItem * boxSelector =
#endif
				ClearMenuItem(CM_SELECTBOX);
			mutASSERT(boxSelector->IsSubMenu());

			repaint_route();
			ActiveWindow = NULL;
		}
	}

	void MutFrame::CmStop(wxCommandEvent& event)
	{
		mutUnused(event);
		DoStop();
	}

	void MutFrame::CmPanic(wxCommandEvent& WXUNUSED(event))
	{
		if ( LogicOn )
			Panic(midi::DEFAULT_PANIC);
	}

	void MutFrame::CeExecute(wxUpdateUIEvent& event)
	{
		event.Enable(!LogicOn);
	}


	void MutFrame::CeActivate(wxUpdateUIEvent& event)
	{
		//	event.Enable(!LogicOn && (Compiled || ActiveWinKind == WK_EDIT));
		bool enable = !LogicOn && (dynamic_cast<MutEditFile *>(client));
		event.Enable(enable);

		// this does not work as wxWidgets does not support hiding toolbar buttons
		event.Show(enable);
	}

	void MutFrame::CeStop(wxUpdateUIEvent& event)
	{
		event.Enable(LogicOn);

		// this does not work as wxWidgets does not support hiding toolbar buttons
		event.Show(LogicOn);
	}

	// Routenfenster anzeigen
	void MutFrame::CmRoutes(wxCommandEvent& event)
	{
		if ( GetId()== WK_ROUTE ) {
			DEBUGLOG (other, _T("setting Focus"));
			auimanager.Update();
			Raise();
			return;
		}

		if (client) {
			event.Skip(true);
			return;
		}

		SetId(WK_ROUTE);

		int width, height;
		GetClientSize(&width, &height);

		client = new MutRouteWnd(this,
					 wxPoint(0, 0),
					 wxSize(width, height));

		auimanager.AddPane(client,
				   wxAuiPaneInfo().Caption(_("Routes"))
				   .CenterPane().PaneBorder(false));
		auimanager.Update();

		SetIcon(ICON(route));

		if (LogicOn) UpdateBoxMenu();

		SetSize(wxDefaultSize);
	}

// TextBox-Arbeit: ToggleTextBox, TextBoxOpen, CmToggleKey, CmToggleTS

	void MutFrame::LogicWinOpen(mutabor::Box box)
	{
		int width, height;
		GetClientSize(&width, &height);
		width /= 2;
		height /= 2;
		MutLogicWnd *client = new MutLogicWnd(this, box,
						      wxPoint(0, 0),
						      wxSize(width,height));
		auimanager.AddPane(client,
				   wxAuiPaneInfo().Name(wxString::Format(_T("Logic %s"),
									 (box?box->GetLabel()
									  :wxString(_("(unknown)"))).c_str()))
				   .Bottom()
				   .Floatable(true)
				   .CloseButton(false)
				   .MaximizeButton(true)
				   .Float()
				   .Caption(client->MakeTitle())
				   .DestroyOnClose(true));
		client->SetFocus();
		auimanager.Update();
		UpdateBoxMenu();
		MutFrame * routewin = dynamic_cast<MutFrame *>(FindWindowById(WK_ROUTE));
		if ( routewin ) routewin->UpdateBoxMenu();
	}

	void MutFrame::ToggleTextBox(WinKind kind)
	{

		if (ActiveWindow && (ActiveWindow != this)) {
			ActiveWindow->ToggleTextBox(kind);
			return;
		}

		mutabor::Box b = GetCurrentBox();
		BoxData * box = ToGUIBase(b);
		if (!box) return;
		bool openclose = false;
		MutChild * win = NULL;
		switch (kind) {
		case WK_KEY:
			openclose = box->ToggleKeyWindow();
			win = box->GetKeyWindow();
			break;
		case WK_TS:
			openclose = box->ToggleTonesystemWindow();
			win = box->GetTonesystemWindow();
			break;
		case WK_ACT:
			openclose = box->ToggleActionsWindow();
			win = box->GetActionsWindow();
			break;
		case WK_LOGIC:
			wxLogWarning(_("Unexpected value: WK_LOGIC"));
			UNREACHABLEC;
			break;
		case WK_ROUTE:
			wxLogWarning(_("Unexpected value: WK_ROUTE"));
			UNREACHABLEC;
			break;
		case WK_EDIT:
			wxLogWarning(_("Unexpected value: WK_EDIT"));
			UNREACHABLEC;
			break;
		case WK_NULL:
			wxLogWarning(_("Unexpected value: WK_NULL"));
			UNREACHABLEC;
			break;
		default:
			wxLogError(_("Unexpected window kind: %d"), kind);
			UNREACHABLEC;
		}

		DEBUGLOG(gui,_T("LogicOn %d"),LogicOn);

		if ( !LogicOn ) return;

		DEBUGLOG(gui,_T("IsOpen(%d, %p) = %d"),kind,GetCurrentBox().get(),IsOpen(kind, b));
		mutASSERT(IsOpen(kind,b) == !openclose);

		if (openclose) {
			TextBoxOpen(kind, b);
		} else if (win) {
			CloseClientWindow(win,true);
		}
	}


	void MutFrame::DoBoxWindowsOpen(mutabor::Box box, bool update) {
		mutUnused(update);
		BoxData * boxdata = ToGUIBase(box);
		mutUnused(boxdata);
		STUBC;


		// if (!update) return;

		// we do not save the window properties on
		// a per box state so we cannot just load the
		// data from the config.
		// auimanager.Update();
	}

	void MutFrame::DoBoxWindowsClose(mutabor::Box box,bool update) {
		if (!box) {
			UNREACHABLEC;
			return;
		}

		BoxData * boxdata = ToGUIBase(box);
		wxWindow * win;
		win = boxdata->GetLogicWindow();
		if (win)
			CloseClientWindow(win,false);
		win = boxdata->GetKeyWindow();
		if (win)
			CloseClientWindow(win,false);
		win = boxdata->GetTonesystemWindow();
		if (win)
			CloseClientWindow(win,false);
		win = boxdata->GetActionsWindow();
		if (win)
			CloseClientWindow(win,false);

		if (update) {
			auimanager.Update();
			UpdateBoxMenu();
			MutFrame * routewin = dynamic_cast<MutFrame *>(FindWindowById(WK_ROUTE));
			if ( routewin ) routewin->UpdateBoxMenu();
		}
	}



	void MutFrame::TextBoxOpen(WinKind kind, Box & box, bool update_auimanager)
	{
		DEBUGLOG (other, _T("%d,%p"),kind,box.get());

		int width, height;

		GetClientSize(&width, &height);
		width /= 2;
		height /= 2;

		MutChild *client = new MutChild(kind,
						box,
						this,
						-1,
						wxDefaultPosition,
						wxSize(width, height));
		DEBUGLOG (gui, _T("client->winKind=%d"),client->GetKind());
		DEBUGLOG (gui, _T("client->winKind=%d"),client->GetKind());

		wxString str = wxEmptyString;

		DEBUGLOG (gui, _T("client->winKind=%d"),client->GetKind());
		DEBUGLOG (gui, _T("client->winKind=%d"),client->GetKind());

		switch ( kind ) {
		case WK_KEY:
			client->GetKeys(asTS);
			break;

		case WK_TS:
			client->GetToneSystem(asTS);
			break;

		case WK_ACT:
			/* nothing to be done.
			   The actions window starts empty. */
#if 0
			if (CAW) {
				client->GetAllActions();
			} else {
				client->GetBoxActions();
			}
#endif
			break;

		case WK_LOGIC:
			wxLogWarning(_("Unexpected value: WK_LOGIC"));
			UNREACHABLEC;
			break;
		case WK_ROUTE:
			wxLogWarning(_("Unexpected value: WK_ROUTE"));
			UNREACHABLEC;
			break;
		case WK_EDIT:
			wxLogWarning(_("Unexpected value: WK_EDIT"));
			UNREACHABLEC;
			break;
		case WK_NULL:
			wxLogWarning(_("Unexpected value: WK_NULL"));
			UNREACHABLEC;
			break;
		default:
			wxLogError(_("Unexpected window kind: %d"), kind);
			UNREACHABLEC;
		}

		DEBUGLOG (gui, _T("client->winKind=%d"),client->GetKind());

		auimanager.AddPane(client,wxAuiPaneInfo()
				   .CaptionVisible(true).Caption(client->MakeTitle())
				   .CloseButton(true).MaximizeButton(true)
				   .Float()
				   .Name(wxString::Format(_T("WK_%d_%d"),kind,
							  box?box->get_routefile_id():NoBox))
				   .DestroyOnClose(true));

		mutASSERT(auimanager.GetPane(client).IsDestroyOnClose());

		if (update_auimanager)
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


		STUBC;
/*
  if ( OWM ) {
  for (WinKind kind = WK_KEY; kind <= WK_LOGIC; kind++)
  for (size_t i = 0; i < WinAttrs[kind].Count(); i++)
  if ( WinAttrs[kind][i].Box != curBox && WinAttrs[kind][i].Win ) {
  WinAttrs[kind][i].Wanted = 2; // um Wanted zu erhalten
  auimanager.DetachPane(WinAttrs[kind][i].Win);
  }
  } else
  for (WinKind kind = WK_KEY; kind <= WK_LOGIC; kind++)
  for (size_t i = 0; i < WinAttrs[kind].Count(); i++)
  if ( WinAttrs[kind][i].Box != curBox && WinAttrs[kind][i].Wanted )
  {
  if ( kind == WK_LOGIC )
  LogicWinOpen(WinAttrs[kind][i].Box);
  else
  TextBoxOpen(kind, WinAttrs[kind][i].Box);

  }
*/
	}

	void MutFrame::CmToggleCAW(wxCommandEvent& WXUNUSED(event))
	{
		CAW = !CAW;

		if ( !LogicOn )
			return;


		STUBC;
/*
// ActWin curBox updaten
WinAttr *WinAttr = Get(WK_ACT, curBox);

if ( WinAttr && WinAttr->Win )
((MutTextBox*)WinAttr->Win)->NewText(CAW ? GenerateCAWString() : GenerateACTString(curBox), 1);

// andere Action-Fenster schlieﬂen bzw. ˆffnen
if ( CAW ) {
for (size_t i = 0; i < WinAttrs[WK_ACT].Count(); i++)
if ( WinAttrs[WK_ACT][i].Box != curBox && WinAttrs[WK_ACT][i].Win ) {
WinAttrs[WK_ACT][i].Wanted = 2; // um Wanted zu erhalten
auimanager.DetachPane(WinAttrs[WK_ACT][i].Win);
}
} else
for (size_t i = 0; i < WinAttrs[WK_ACT].Count(); i++)
if ( WinAttrs[WK_ACT][i].Box != curBox && WinAttrs[WK_ACT][i].Wanted )
TextBoxOpen(WK_ACT, WinAttrs[WK_ACT][i].Box);
*/
	}

	void MutFrame::CeToggleKey(wxUpdateUIEvent& event)
	{
		mutabor::Box box = GetCurrentBox();
		if (box) {
			event.Enable(true);
			event.Show(true);
		} else {
			event.Enable(false);
			event.Show(false);
			DEBUGLOG(menu,_T("box: %d, Checked: %d"),
				 box?box->get_routefile_id():-10000,
				 event.GetChecked());
			return;
		}
		BoxData * guibox = ToGUIBase(box);
		event.Check(guibox?guibox->WantKeyWindow():false);
		DEBUGLOG(menu,_T("box: %d, guibox: %p, Checked: %d, Enabled: %d, Shown: %d"),
			 guibox?box->get_routefile_id():-10000,
			 guibox,
			 event.GetChecked(),
			 event.GetEnabled(),
			 event.GetShown());
	}

	void MutFrame::CeToggleTS(wxUpdateUIEvent& event)
	{
		mutabor::Box box = GetCurrentBox();
		BoxData * guibox = ToGUIBase(box);
		event.Check(guibox?guibox->WantTonesystemWindow():false);
	}

	void MutFrame::CeToggleAct(wxUpdateUIEvent& event)
	{
		mutabor::Box box = GetCurrentBox();
		BoxData * guibox = ToGUIBase(box);
		event.Check(guibox?guibox->WantActionsWindow():false);
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
		  if ( mut_box[box].used )
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

#if 0

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
		STUBC;

		if ( !subSize.IsFullySpecified() ) {
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
		} else {
			int w, h;
			GetClientSize(&w, &h);
			// get size of editor window
			int w1 = w * 4 / 5, h1 = h * 2 / 3;

			if ( subSize.GetWidth() != 0 ) {
				w1 = subSize.GetWidth();
				h1 = subSize.GetHeight();
			}

			if ( w - w1 < 112 )
				w1 = w - 112;

			int n = (NumberOfOpen(win->winKind)-1)*22;

			if ( demo )
				switch ( win->winKind ) {

				case WK_KEY:
					win->SetSize(w / 2-n, n, w / 4, h / 2);

					break;

				case WK_TS:
					win->SetSize(w / 2 + w / 4-n, n, w / 4, h);

					break;

				case WK_ACT:
					win->SetSize(w / 2 + n, h / 2-n, w / 4, h - h / 2);

					break;

				case WK_LOGIC:
					win->SetSize(n, n, w / 2, h);

					break;

				case WK_ROUTE:
					win->SetSize(n, n, w / 2, h);

					break;
				}
			else
				switch ( win->winKind ) {

				case WK_KEY:
					win->SetSize(w1-n, n, w - w1, h / 2);

					break;

				case WK_TS:
					win->SetSize(w1-n, h / 2-n, w - w1, h - h / 2);

					break;

				case WK_ACT:
					win->SetSize(w1 * 3 / 4-n, h1-n, w1 - w1 * 3 / 4, h - h1);

					break;

				case WK_LOGIC:
					win->SetSize(n, h1-n, w1 * 3 / 4, h - h1);

					break;

				case WK_ROUTE:
					win->SetSize(n, h1-n, w1 * 3 / 4, h - h1);

					break;
				};
		}

	}
#endif

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

	void MutFrame::RestoreState()
	{

		/** \todo implement this function */
#if 0
		//  int DeskMax = 1, WinMax = 2, HelpMax = 0;
		wxConfigBase *config = wxConfig::Get();

		/* The current implementation does not check that the
		   window is inside the accesible area of the screen. */
		int x=0, y=0, w=0, h=0;

		config->SetPath(_T("Desktop"));
		//  DeskMax=config->Read(_T("DeskMax"),0l);

		if ((x=config->Read(_T("X Position"),0l)) &&
		    (y=config->Read(_T("Y Position"),0l)) &&
		    (w=config->Read(_T("Width"),0l)) &&
		    (h=config->Read(_T("Height"),0l))) {
			SetSize(x, y, w, h);

		}

		config->SetPath(_T(".."));
#endif
	}

// Recorder-Knöpfe --------------------------------------------------

	void MutFrame::StopInDev()
	{
		StatusBar::AllSetPlaystate(StatusBar::Stop,true);

		InputDeviceClass::StopAll();
		event e = new stop_play_event(-1);
		OutputDeviceClass::all_handle_event(e);

#if 0
		const InputDeviceList & list =
			InputDeviceClass::GetDeviceList();
		for ( InputDeviceList::const_iterator In = list.begin();
		      In != list.end(); In++) {
			if ( (*In)->GetMode() == DevicePlay
			     || (*In)->GetMode() == DevicePause ) {
				//	    In->Mode = DeviceStop;
				//		InDeviceAction(nr, In->Mode);
				boost::const_pointer_cast<InputDeviceClass>(*In)
					-> Stop();
			}
		}
#endif
	}


	void MutFrame::CmInDevStop(wxCommandEvent& WXUNUSED(event))
	{
		StopInDev();
		repaint_route();
		// SetStatus(1-LogicOn);
	}

	void MutFrame::CmInDevPlay(wxCommandEvent& ev)
	{
		TRACEC;

		if ( !LogicOn )
			CmDoActivate(ev);

		StatusBar::AllSetPlaystate(StatusBar::Play,true);
		if (CurrentTime.isRealtime()) {
			event e;
			if (InputDeviceClass::was_last_stop()) {
				e = new start_play_event(-1);
			} else {
				e = new continue_play_event(-1);
			}
			OutputDeviceClass::all_handle_event(e);

			InputDeviceClass::RealtimePlay();
			//SetStatus(SG_PLAY);
		} else {
			if ( InputDeviceClass::BatchPlay() ) {
				wxMessageBox(_("The conversion finished successfully."),
					     _("Conversion error"),
					     wxOK | wxICON_INFORMATION );
			}
#if 0
			// Centralized Error collector has not been implemented.
			else {
				wxMessageBox(Fmeldung, _("Conversion error"),
					     wxOK | wxICON_ERROR );
			}
#endif
		}

		repaint_route();
	}

	void MutFrame::CmInDevPause(wxCommandEvent& WXUNUSED(ev))
	{
		StatusBar::AllSetPlaystate(StatusBar::Pause,true);
		InputDeviceClass::PauseAll();
		event e = new stop_play_event(-1);
		OutputDeviceClass::all_handle_event(e);

#if 0
		const InputDeviceList & list =
			InputDeviceClass::GetDeviceList();
		for ( InputDeviceList::const_iterator In = list.begin();
		      In != list.end(); In++) {
			if ( (*In)->GetMode() == DevicePlay ) {
				boost::const_pointer_cast<InputDeviceClass>(*In)
					-> Pause();
			}
		}
#endif
		repaint_route();
		// SetStatus(SG_PAUSE);
	}

	void MutFrame::CeInDevStop(wxUpdateUIEvent& event)
	{
		const InputDeviceList & list =
			InputDeviceClass::GetDeviceList();
		for ( InputDeviceList::const_iterator In = list.begin();
		      In != list.end(); In++) {
			if ( (*In)->GetType() >= DTMidiFile &&
			     ((*In)->GetMode() == DevicePlay ||
			      (*In)->GetMode() == DevicePause) ) {
				event.Enable(true);
				return;
			}
		}
		event.Enable(false);
	}

	void MutFrame::CeInDevPlay(wxUpdateUIEvent& event)
	{
		if ( !LogicOn ) {
			DEBUGLOG (other, _T("Logic is off"));
			event.Enable(false);
			return;
		}

		const InputDeviceList & list =
			InputDeviceClass::GetDeviceList();
		for ( InputDeviceList::const_iterator In = list.begin();
		      In != list.end(); In++) {
			DEBUGLOG (routing,
				  _T("checking Device type %d >= %d with mode %d for pointer %p"),
				  (*In)->GetType(),
				  DTMidiFile,
				  (*In)->GetMode(),
				  (void*)(*In).get());

			if ( (*In)->GetType() >= DTMidiFile &&
			     ((*In)->GetMode() == DeviceStop ||
			      (*In)->GetMode() == DevicePause) ) {
				DEBUGLOG (routing, _T("Device can be activated"));
				event.Enable(true);
				return;
			}

			DEBUGLOG (routing, _T("Device can not be activated"));
		}

		event.Enable(false);
	}

	void MutFrame::CeInDevPause(wxUpdateUIEvent& event)
	{
		//		bool Pause = 0;

		const InputDeviceList & list =
			InputDeviceClass::GetDeviceList();
		for ( InputDeviceList::const_iterator In = list.begin();
		      In != list.end(); In++) {
			if ( (*In)->GetType() >= DTMidiFile ) {
				if ((*In)->GetMode() == DevicePlay ) {
					event.Enable(true);

					//if ( curStatusImg != SG_PLAY )
					//			SetStatus(SG_PLAY);

					return;
				}
					/*
					else if ( (*In)->GetMode() == DevicePause )
					Pause = true;
					*/
			}
		}
/*
  if ( Pause ) {
  if ( curStatusImg != SG_PAUSE )
  SetStatus(SG_PAUSE);
  } else if ( curStatusImg != 1-LogicOn )
  SetStatus(1-LogicOn);
*/
		event.Enable(false);
	}

	void MutFrame::CmSetTitle(wxCommandEvent& event)
	{
		SetTitle(wxString::Format(_("%s -- %s"), APPNAME, event.GetString().c_str()));
	}

// Updaten der Protokollfenster
	void MutFrame::UpdateUI(wxCommandEvent& WXUNUSED(event))
	{

	}


#if 0
	void MutFrame::OnIdle(wxIdleEvent& event)
	{
		/// \todo check if this is correct
		//	wxCommandEvent event1(wxEVT_COMMAND_MENU_SELECTED, CM_UPDATEUI);
		//	UpdateUI(event1);
		event.Skip();
	}
#endif

	void MutFrame::OnEraseBackground(wxEraseEvent& event)
	{
		if (client)
			event.Skip();
	}

	wxAuiDockArt* MutFrame::GetDockArt()
	{
		return auimanager.GetArtProvider();
	}



	void MutFrame::OnSize(wxSizeEvent& event)
	{
		event.Skip();
	}



	wxRect MutFrame::DetermineFrameSize ()
	{
		TRACEC;

		wxSize scr = wxGetDisplaySize();

		// determine default frame position/size
		wxRect normal;
		wxPoint currpos = GetPosition();

		if (scr.x <= 800) {
			normal.x = 40 / 2;
			normal.width = scr.x - 40;
		} else {
			normal.x = currpos.x;
			normal.width = 800;
		}

		if (scr.y <= 600) {
			normal.y = 80 / 2;
			normal.height = scr.y - 80;
		} else {
			normal.y = currpos.y;
			normal.height = 600;
		}

		return normal;
	}

#if 0
/// Close all child windows of given kind
/** This function closes all child windows of the given kind.
 *
 * \param kind any wk_kind, that describes which kind of windows shall
 * be closed. Use WK_NULL to close all windows.
 */
	void MutFrame::CloseAll(WinKind kind)
	{


#warning reimplement this or remove the function
		TRACEC;

		auimanager.Update();

		Freeze();

		wxWindow * win = NULL;
		size_t box = minimal_box_used;
		do {
			mutabor_box_type & b = mut_box[box];
			BoxData * boxdata = static_cast<BoxData *>(b.userdata);

			if (boxdata) {
				switch (kind) {
				case WK_KEY:
					win = boxdata -> GetKeyWindow();
					break;
				case WK_TS:
					win = boxdata -> GetTonesystemWindow();
					break;
				case WK_ACT:
					win = boxdata -> GetActionsWindow();
					break;
				case WK_LOGIC:
					win = boxdata -> GetLogicWindow();
					break;
				case WK_ROUTE:
					wxLogWarning(_("Unexpected value: WK_ROUTE"));
					UNREACHABLEC;
					break;
				case WK_EDIT:
					wxLogWarning(_("Unexpected value: WK_EDIT"));
					UNREACHABLEC;
					break;
				case WK_NULL:
					win = boxdata -> GetKeyWindow();
					if (win)
						CloseClientWindow(win,false);
					win = boxdata -> GetTonesystemWindow();
					if (win)
						CloseClientWindow(win,false);
					win = boxdata -> GetActionsWindow();
					if (win)
						CloseClientWindow(win,false);
					win = boxdata -> GetLogicWindow();
					break;
				default:
					wxLogError(_("Unexpected window kind: %d"), kind);
					UNREACHABLEC;
				}
				if (win)
					CloseClientWindow(win,false);

			}
			box = b.next_used;
		} while (box);
		Thaw();
		auimanager.Update();
	}
#endif

	bool MutFrame::Destroy() {
		bool retval = base::Destroy();
		if (retval)
			boxCommandIds.clear();
		return retval;
	}

	void MutFrame::UpdateBoxMenu()
	{
		/* the current implementation saves unused box command
		   ids for further usage.  Thus the map of command ids
		   will never get smaller.

		   On the other hand, the number of used command ids
		   equals the largest number of boxes that have been
		   active simultaniously.

		   This set of command ids is copied once per call. So
		   the complexity of this function can be roughly
		   estimated by $#(boxes) * max\{#(used_boxes_so_far)\}$.
		*/
		DEBUGLOG(other,_T("MutFrame::CmDoActivate: Set Box selection menu"));
		wxMenuItem * boxSelector = ClearMenuItem(CM_SELECTBOX);
		mutASSERT(boxSelector->IsSubMenu());
		wxMenu * boxMenu = boxSelector->GetSubMenu();
		mutASSERT(boxMenu);
		DEBUGLOG (other, _T("boxMenu = %p"),(void*)boxMenu);
		//  wxID_HIGHEST
		//  wxMenu *


		// At least on wxGTK a checked menu item does not send any events
		// so we add a special item for the current box.
		wxMenuItem * item = new wxMenuItem(boxMenu,
						   CM_BOX,
						   _("&Raise current box\tCtrl+B"),
						   _("This item activates the window of the currently selectcd box"));
		boxMenu->Append(item);
		boxMenu->AppendSeparator();
		boxCommandMap tmpmap;
		tmpmap.swap(boxCommandIds);


		const mutabor::BoxListType &list = mutabor::BoxClass::GetBoxList();
		for (mutabor::BoxListType::const_iterator i = list.begin();
		     i != list.end();
		     ++i) {
			mutabor::Box box = *i;
			BoxData * guibox = ToGUIBase(box);
			if (!(guibox->GetLogicWindow()))
				continue;
			int id = box->get_routefile_id();

			// use an arbitrary command id that may not be a box command id
			// maybe CM_ACTIVATE is somewhat descriptive, here.
			int command_id = CM_ACTIVATE;
			boxCommandMap::iterator freecmd = tmpmap.end();
			for (boxCommandMap::iterator i = tmpmap.begin();
			     i != tmpmap.end();
			     ++i) {
				if (i->second == box) {
					command_id = i->first;
					tmpmap.erase(i);
					break;
				}

				// this means that the command id was
				// in use but is currently not
				if (!(i->second)) {
					freecmd = i;
				}
			}

			if (command_id == CM_ACTIVATE) {
				if (freecmd == tmpmap.end()) {
					command_id = wxNewId();
				} else {
					command_id = freecmd->first;
					tmpmap.erase(freecmd);
				}
				DEBUGLOG (menu, _("Box %d got a new id %d"),
					  id,command_id);
			}

			boxCommandIds[command_id]=box;

			DEBUGLOG (menu, _("Currently %d items in box menu"),
				  (int)(boxMenu->GetMenuItemCount()));

			DEBUGLOG (menu, _("Appending menu for box %d with id %d"),
				  id,command_id);
			wxString name = wxString::Format(_("Select box %d\tCtrl+%d"),
							 id,id);
			wxString description =
				wxString::Format(_("Select box %d as the active Box for box specific commands."),
						 id);
			mutASSERT(!(GetMenuBar()->FindItem(command_id)));
			mutASSERT(boxCommandIds[command_id]==box);
			wxMenuItem * item = new wxMenuItem(boxMenu,
							   command_id,
							   name,
							   description,
							   wxITEM_RADIO);
			boxMenu->Append(item);

			if (box == BoxData::GetCurrentBox())
				boxMenu->Check(command_id,
					       true);

			DEBUGLOG (menu, _("Connecting command with id %d for box command %d"),
				  id,command_id);

			// already used command ids got disconnected
			// by ClearSubMenu() so we reconnect, here
			Connect( command_id,
				 wxEVT_COMMAND_MENU_SELECTED,
				 wxCommandEventHandler(MutFrame::RaiseLogic) );
		}

		// save the remaining command ids for further usage.
		for (boxCommandMap::iterator i = tmpmap.begin();
			     i != tmpmap.end();
			     ++i) {
			boxCommandIds[i->first].reset();
		}
	}

	bool MutFrame::RaiseTheFrame()
	{
		if (this == ActiveWindow) return true;

		ActiveWindow->Raise();

		return false;
	}


#if 0
	void CheckBoxesUsed()
	{
#warning Check whether CheckBoxesUsed is in use
		for (int i = 0; i < MAX_BOX; i++) {
			mutabor_box_type & b = mut_box[i];
			b.id = i;
			b.used = false;
			b.userdata = &(BoxData::GetBox(i));
		}

		const InputDeviceList & list =
			InputDeviceClass::GetDeviceList();
		for ( InputDeviceList::const_iterator In = list.begin();
		      In != list.end(); In++) {
			const routeListType & routes = (*In)->GetRoutes();
			for ( routeListType::const_iterator R = routes.begin();
			      R != routes.end(); R++) {
				if ( (*R)->GetBox() >= 0 ) {
					if ((*R)->GetBox() >= MAX_BOX) UNREACHABLE;
					else
						mut_box[(*R)->GetBox()].used = 1;
				}
			}
		}
		int last_used = 0;
		int j;
		for (int i = MAX_BOX; i > 0 ; i=j) {
			j = i - 1;
			mutabor_box_type & b = mut_box[j];
			if (b.used) {
				b.next_used = last_used;
				last_used = j;
			} else b.next_used = 0;
		}
		minimal_box_used = last_used;
	}
#endif

}
//\}
