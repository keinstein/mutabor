/** \file MutFrame.cpp
 ********************************************************************
 * Mutabor Frame.
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/muwx/MutFrame.cpp,v 1.57 2011/10/04 17:16:14 keinstein Exp $
 * Copyright:   (c) 2005,2006,2007 TU Dresden
 * \author Rüdiger Krauße <krausze@mail.berlios.de>
 * Tobias Schlemmer <keinstein@users.berlios.de>
 * \date $Date: 2011/10/04 17:16:14 $
 * \version $Revision: 1.57 $
 * \license GPL
 *
 * $Log: MutFrame.cpp,v $
 * Revision 1.57  2011/10/04 17:16:14  keinstein
 * make program compile on Mac (wx 2.9) and fix some memory corruption
 *
 * Revision 1.56  2011-10-03 15:50:21  keinstein
 * Fix focus issues in the route window. This includes:
 *  * Using templates to describe the base class of MutIconShape.
 *  * Rename MutIconShape->MutIconShapeClass.
 *  * typedef MutIconShapeClass<wxControl> MutIconShape
 *  * Expand the control container macros in MutPanel.
 *  * Disable most of the control container behaviour as we don't need it, currently
 *  * Focus NewInputDevice on window creation.
 *  * MutBoxChannelShape focuses its parent on focus (which can be done only by mouse so far).
 *  * Display focused Window with sunken border
 *
 * Revision 1.55  2011-10-02 16:58:41  keinstein
 * * generate Class debug information when compile in debug mode
 * * InputDeviceClass::Destroy() prevented RouteClass::Destroy() from clearing references -- fixed.
 * * Reenable confirmation dialog when closing document while the logic is active
 * * Change debug flag management to be more debugger friendly
 * * implement automatic route/device deletion check
 * * new debug flag --debug-trace
 * * generate lots of tracing output
 *
 * Revision 1.54  2011-09-30 18:07:05  keinstein
 * * make compile on windows
 * * s/wxASSERT/mutASSERT/g to get assert handler completely removed
 * * add ax_boost_base for boost detection
 *
 * Revision 1.53  2011-09-30 09:10:25  keinstein
 * Further improvements in the routing system.
 *
 * Revision 1.52  2011-09-29 05:26:59  keinstein
 * debug intrusive_ptr
 * fix storage and retrieving of input/output devices in treestorage
 * save maximum border size in icons
 * Apply the calculated offset in IconShape (box and box channels still missing)
 * Fix debug saving and restoring route information/route window on activation
 * Add wxWANTS_CHARS to MutEditWindow
 *
 * Revision 1.51  2011-09-27 20:13:23  keinstein
 * * Reworked route editing backend
 * * rewireing is done by RouteClass/GUIRoute now
 * * other classes forward most requests to this pair
 * * many bugfixes
 * * Version change: We are reaching beta phase now
 *
 * Revision 1.50  2011-09-08 20:35:29  keinstein
 * fix some compile errors
 *
 * Revision 1.49  2011-09-08 16:51:21  keinstein
 * Set foreground color in box status windows
 * Fix updating box status windows
 * update RtMidi (includes Jack compilation mode)
 *
 * Revision 1.48  2011-09-07 15:58:56  keinstein
 * fix compilation on MinGW
 *
 * Revision 1.47  2011-09-07 13:06:50  keinstein
 * Get rid of WinAttr and Fix window opening and closing
 *
 * Revision 1.46  2011-09-05 11:30:07  keinstein
 * Some code cleanups moving some global box arrays into class mutaborGUI::BoxData
 * Restore perspective on logic start
 *
 * Revision 1.45  2011-09-05 06:42:47  keinstein
 * Added GUIBoxData.h
 *
 * Revision 1.44  2011-09-05 06:30:15  keinstein
 * Save AUI data
 *
 * Revision 1.43  2011-09-04 16:25:05  keinstein
 * Do not manage ToolBar from AUI manager -- fixes Toolbar on Mac OS X and wx 2.9.2
 *
 * Revision 1.42  2011-09-04 12:02:08  keinstein
 * require wxWidgets 2.8.5 configure.in
 *
 * Revision 1.41  2011-08-28 21:24:56  keinstein
 * added file properties dialog
 *
 * Revision 1.40  2011-08-28 20:09:11  keinstein
 * several impovements for opening and saving files
 *
 * Revision 1.39  2011-08-27 17:44:44  keinstein
 * Implemented Search and Search/Replace
 *
 * Revision 1.38  2011-08-24 21:19:36  keinstein
 * first run with 2.9.2+
 *
 * Revision 1.37  2011-08-21 16:52:05  keinstein
 * Integrate a more sophisticated editor menu based on the stc sample
 *
 * Revision 1.36  2011-08-20 17:50:39  keinstein
 * use  wxSTC for the editor windows
 *
 * Revision 1.35  2011-08-16 20:20:03  keinstein
 * Fix compiling on Mac OS X 10.5
 *
 * Revision 1.34  2011-08-14 18:32:18  keinstein
 * Use of m_childView of wxDocChildFrame instead of own view fixes a bad access.
 * Use wxDocChildFrame::OnCloseWindow
 * remove some unneeded code
 *
 * Revision 1.33  2011-08-11 19:00:48  keinstein
 * get Document/View running.
 * Needs further testing (possible segfaults).
 *
 * Revision 1.32  2011-08-06 09:21:23  keinstein
 * activated and debugged document manager
 *
 * Revision 1.31  2011-07-31 21:32:21  keinstein
 * Slightly improved window positioning
 * Suppress route window, when a Window is opened from the command line
 *
 * Revision 1.30  2011-07-31 20:16:04  keinstein
 * Implemented opening files from command line using Document/View framework
 *
 * Revision 1.29  2011-07-31 12:40:42  keinstein
 * Added classes and functions for Document/View support
 *
 * Revision 1.28  2011-03-06 13:15:41  keinstein
 * some rearrangement for update callback kernel->GUI
 *
 * Revision 1.27  2011-02-20 22:35:57  keinstein
 * updated license information; some file headers have to be revised, though
 *
 * Revision 1.26  2011-02-13 17:20:46  keinstein
 * Implemented missing toolbar icons (except search and edit funcitons)
 *
 * Revision 1.25  2011-01-13 21:12:37  keinstein
 * reactivate config restore on Activate in debug mode
 *
 * Revision 1.24  2010-12-11 02:10:09  keinstein
 * make 2.9.1 build but Mutabor crashes still at runtime in an infinite recursion :-(
 *
 * Revision 1.23  2010-11-21 13:15:47  keinstein
 * merged experimental_tobias
 *
 * Revision 1.21.2.10  2010-11-20 21:58:16  keinstein
 * reactivate midi playback
 *
 * Revision 1.21.2.9  2010-11-18 21:46:14  keinstein
 * MutFrame: get rid of OnIdle (this may break something, but saves much more CPU cycles
 * Some further steps to get rid of EDevice*
 *
 * Revision 1.21.2.8  2010-11-14 22:29:53  keinstein
 * Remvoed EDevice.cpp and EDevice.h from the sources list
 * They still reside in the source tree, since they have been used for Midi/GMN
 * file playing. That funcitonality has been disabled so far.
 * After reimplementation the files can be removed.
 *
 * Revision 1.21.2.7  2010-09-30 16:26:26  keinstein
 * remove global variables routewindow and frame
 * move route loading and route saving into MutRouteWnd
 * implement MutRouteWnd::InitShapes.
 * Destroy Route children before loading new route configuration (still some crashes)
 *
 * Revision 1.21.2.6  2010/04/20 17:41:38  keinstein
 * One step towards using Mutabor: Activation of a logic now honours the state of the Device Editor.
 *
 * Revision 1.21.2.5  2010/04/15 09:28:43  keinstein
 * changing routes works, but is not honoured by MIDI, yet
 *
 * Revision 1.21.2.4  2010/03/30 08:38:26  keinstein
 * added rudimentary command line support
 * changed debug system to allow selection of messages via command line
 * further enhancements to the route dialogs
 *
 * Revision 1.21.2.3  2010/02/15 12:08:21  keinstein
 * intermediate update for backup progress
 *
 * Revision 1.21.2.2  2010/01/14 09:34:24  keinstein
 * Checkin searching for a bug
 *
 * Revision 1.21.2.1  2009/08/10 11:23:12  keinstein
 * merged from wrong tree
 *
 * Revision 1.22  2009/08/10 11:15:46  keinstein
 * some steps towards new route window
 *
 * Revision 1.21  2008/10/09 15:14:02  keinstein
 * make compile on mingw
 *
 * Revision 1.20  2008/10/01 09:33:49  keinstein
 * fixed inclution for XCode build
 *
 * Revision 1.19  2008/08/18 15:10:37  keinstein
 * Fix subwindow creation when on other window
 *
 * Revision 1.18  2008/08/01 16:24:30  keinstein
 * Fix some segfaults on stopping Mutabor
 *
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

#include "Defs.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#include "wx/toolbar.h"

#if !defined(__WXMSW__) && 0
#include "Icon/Mutabor.xpm"
#include "Icon/Document.xpm"
#include "Icon/KeyTextBox.xpm"
#include "Icon/TSTextBox.xpm"
#include "Icon/ActTextBox.xpm"
#endif

#include "Icon/Route.xpm"


#if 0
#include "bitmaps/new.xpm"
#include "bitmaps/open.xpm"
#include "bitmaps/save.xpm"
#include "bitmaps/copy.xpm"
#include "bitmaps/cut.xpm"
#include "bitmaps/paste.xpm"
#include "bitmaps/print.xpm"
#include "bitmaps/help.xpm"
#endif

#include "wx/filename.h"
#include "wx/config.h"
#include "wx/confbase.h"
#include "wx/fileconf.h"
#ifdef __WXMSW__
#  include <wx/msw/regconf.h>
#endif
#include "wx/ffile.h"
#include "GUIBoxData.h"
#include "MutFrame.h"
#include "MutDocument.h"
#include "MutView.h"
#include "MutChild.h"
//#include "Mutabor.rh"
#include "MutApp.h"

#include "Defs.h"
#include "mhDefs.h"
#include "Runtime.h"
#include "GrafKern.h"
#include "Action.h"
#include "MutRouteWnd.h"
#include "MutLogicWnd.h"
#include "MutTextBox.h"
#include "MutBitmaps.h"
#include "GUIBoxData.h"
#include "DebugRoute.h"

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
		if (filemenu) {
			if (wxGetApp().GetDocumentManager()) 
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
		event.Skip(false);

		if (dynamic_cast<MutEditFile*>(client)) {
			wxPostEvent(client,event);
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
		DEBUGLOG(other,_T("frame: %p"),frame);

		event.Skip();

	}

	void MutFrame::OnCloseWindow(wxCloseEvent& event)
	{

		TRACEC;
		DEBUGLOG (other, _T("%x == %x"),this,ActiveWindow);

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
		STUBC;
		return;

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
	}

/**
 * open a file in a new frame.
 * \param path Path of the file to open
 * \todo file loading fails silently if it is not in the systems encoding.
 * */

	bool MutFrame::OpenFile (wxString path, bool newfile)
	{
		STUBC;
		return false;

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
	
		DEBUGLOG(docview,_T("Setting client of %x to %x with title '%s'"),
			 this,
			 win,
			 (const wxChar *)title.c_str());

		client = win;
		SetTitle(title);
		auimanager.AddPane(client,wxAuiPaneInfo().
				   Caption(title).CenterPane().PaneBorder(false));
		auimanager.Update();
		return true;
	}


// Logic-Arbeit: CmDoActivate, CmStop, CmPanic, CmExecute


	void UpdateUIcallback(int box,bool logic_changed)
	{
		BoxData & boxdata = BoxData::GetBox(box);

		wxCommandEvent event(wxEVT_COMMAND_MENU_SELECTED,
				     CM_UPDATEUI);

		MutChild * win = boxdata.GetKeyWindow();
		if (win) {
			if (win) wxPostEvent(win,event);
		}

		if (logic_changed) {
			win = boxdata.GetActionsWindow();
			if (win) wxPostEvent(win,event);

			win = boxdata.GetTonesystemWindow();
			if (win) wxPostEvent(win,event);
		}
	}

	void MutFrame::CmDoActivate(wxCommandEvent& event)
	{
		if (LogicOn) return;

		DEBUGLOG (gui, _T(""));

		if ( !Compiled )
			return;

		wxGetApp().SaveState();

#ifdef DEBUG
		DEBUGLOG (gui, _T("Restoring state for debugging"));
		wxGetApp().RestoreState();

		DebugCheckRoutes();
#endif

		AktionTraceReset();

		// aktivieren
#ifndef NOACTIVATE
		DEBUGLOG(other,_T("Activate"));

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

		ActiveWindow = this;

		if ( !Activate(RealTime, &UpdateUIcallback) )
			return;

#endif

		DEBUGLOG(other,_T("Initialize state"));

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

		if ( !mut_box[curBox].used ) {
			curBox = minimal_box_used;
		}

		SetAktuellesKeyboardInstrument(curBox);


#if 0
		// WinAttrs säubern
		DEBUGLOG (gui, _T("Clear window attributes"));

		for (WinKind kind = WK_KEY; kind < WK_NULL; kind++) {
			size_t i;

			while ( (i = WinAttrs[kind].GetCount()) > 0)
				if ( !mut_box[WinAttrs[kind][i].Box].used )
					WinAttrs[kind].RemoveAt(i);
		}
#endif

		DEBUGLOG (gui, _T("Open other than logic; One window mode: %d"),OWM);


		UpdateBoxMenu();
		MutFrame * routewin = dynamic_cast<MutFrame *>(FindWindowById(WK_ROUTE));
		if ( routewin ) routewin->UpdateBoxMenu();
		DEBUGLOG (gui, _T("Open Logic window"));
		// curBox-Fenstersetzen
		//  LogicWinOpen(curBox);
		LogicOn = true;

		// Toolbar
		/*2	ControlBar->Remove(*ButtonActivate);
		  ControlBar->Insert(*ButtonStop, TGadgetWindow::Before, ButtonPanic);
		  ControlBar->LayoutSession();*/
		// Statusbar
		SetStatus(SG_LOGIC);

		DEBUGLOG (other, _T("Open Text boxes: %d -- %d"),WK_KEY,WK_ACT);

		// set windows except curBox setzen
//	if ( !OWM ) {
		
		Freeze();

		size_t i = minimal_box_used;
		do {
			BoxWindowsOpen(i,false);
			i = mut_box[i].next_used;
		} while (i);
//	}

		wxConfigBase *config = wxConfig::Get();
		if (config) {
			wxString oldpath = config -> GetPath();
			config->SetPath(_T("/Window Layout"));
			wxString auidata;
			auidata = config->Read(_T("AUI data"),wxEmptyString);
			if (!auidata.empty())
				auimanager.LoadPerspective(auidata,false);
			config->SetPath(oldpath);

			// some panes might still be hidden
			wxAuiPaneInfoArray & panes = auimanager.GetAllPanes();
			int pane_i, pane_count = panes.GetCount();
			for (pane_i = 0; pane_i < pane_count; ++pane_i)
			{
				wxAuiPaneInfo& p = panes.Item(pane_i);
				p.Show();
			}
		}

		Thaw();
		auimanager.Update();

		DEBUGLOG (other, _T("Repaint route"));

		repaint_route();

		DEBUGLOG (other, _T("event.Skip()"));
		event.Skip(false);
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
			  item);

		if (! menu) return;

		menu->AppendSeparator(); // just to make sure, the item group is finished.


		wxMenuItemList& l = menu->GetMenuItems();

		DEBUGLOG (other, _T(" %d items"),l.GetCount());

		for (wxMenuItemList::iterator i = l.begin(); i!=l.end(); i=l.begin()) {
			wxMenuItem * node = *i;
			DEBUGLOG (other, _T("ptr %x handling %s"), node,(node->GetItemLabel()).c_str());

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

		size_t i = 0;

		while (i < MAX_BOX && boxCommandIds[i] != event.GetId()) i++;

		mutASSERT(i!=MAX_BOX);

		DEBUGLOG (other, _T("%d"),i);

		curBox = i;

		BoxData & boxdata = ::GetCurrentBox();
		MutLogicWnd * w = boxdata.GetLogicWindow();
		if (w) {
			w->SetFocus();

			wxFrame * win =
				dynamic_cast<wxFrame *>(w->GetParent());

			if (win) win->Raise();

			DEBUGLOG (other, _T("Parent type: %s"), 
				  muT(typeid(*( w->GetParent())).name()).c_str());

			GetMenuBar()->Check(event.GetId(),true);
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
			mutASSERT(boxSelector->IsSubMenu());

			ActiveWindow -> CloseAll();

			AktionTraceReset();

			repaint_route();
			ActiveWindow = NULL;
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
		bool enable = !LogicOn && (dynamic_cast<MutEditFile *>(client)); 
		event.Enable(enable);
		event.Show(enable);
	}

	void MutFrame::CeStop(wxUpdateUIEvent& event)
	{
		event.Enable(LogicOn);
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

	void MutFrame::LogicWinOpen(int box)
	{
		int width, height;
		GetClientSize(&width, &height);
		width /= 2;
		height /= 2;
		MutLogicWnd *client = new MutLogicWnd(this, box,
						      wxPoint(0, 0),
						      wxSize(width,height));
		wxString Name;
		Name.Printf(_("Logic -- Box %d"),box);
		DEBUGLOG (other, _T("Adding pane '%s' with caption '%s'"), 
			  Name.Format(_T("Logic%d"),box).c_str(),Name.c_str());
		auimanager.AddPane(client,
				   wxAuiPaneInfo().Name(Name.Format(_T("Logic%d"),
								    box)
					   )
				   .Bottom()
				   .Floatable(true)
				   .CloseButton(false)
				   .MaximizeButton(true)
				   .Float()
				   .Caption(Name));
		client->SetFocus();
		auimanager.Update();
	}

	void MutFrame::ToggleTextBox(WinKind kind)
	{

		if (ActiveWindow && (ActiveWindow != this)) {
			ActiveWindow->ToggleTextBox(kind);
			return;
		}

		BoxData & box = BoxData::GetBox(curBox);
		bool openclose;
		MutChild * win;
		switch (kind) {
		case WK_KEY: 
			openclose = box.ToggleKeyWindow();
			win = box.GetKeyWindow();
			break;
		case WK_TS: 
			openclose = box.ToggleTonesystemWindow();
			win = box.GetTonesystemWindow();
			break;
		case WK_ACT: 
			openclose = box.ToggleActionsWindow();
			win = box.GetActionsWindow();
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

		DEBUGLOG(gui,_T("IsOpen(%d, %d) = %d"),kind,curBox,IsOpen(kind, curBox));
		mutASSERT(IsOpen(kind,curBox) == !openclose);

		if (openclose) {
			TextBoxOpen(kind, curBox);
		} else if (win) {
			auimanager.DetachPane(win);
			win->Close();
			auimanager.Update();
		} 
	}


	void MutFrame::DoBoxWindowsOpen(int box, bool update) {
		mutabor_box_type & b = mut_box[box];
		BoxData * boxdata = static_cast<BoxData *> 
			(b.userdata);
		if (boxdata) {
			if (boxdata->WantKeyWindow())
				TextBoxOpen(WK_KEY, box);
			if (boxdata->WantTonesystemWindow())
				TextBoxOpen(WK_TS, box);
			if (boxdata->WantActionsWindow())
				TextBoxOpen(WK_ACT, box);
		}

		LogicWinOpen(box); // updates already

		// if (!update) return;

		// we do not save the window properties on 
		// a per box state so we cannot just load the 
		// data from the config.
		// auimanager.Update();
	}
		
	void MutFrame::DoBoxWindowsClose(int box,bool update) {
		if (MIN_BOX> box || box >= MAX_BOX) {
			UNREACHABLEC;
			return;
		}
			
		BoxData & boxdata = BoxData::GetBox(box);
		wxWindow * win;
		win = boxdata.GetLogicWindow();
		if (win) 
			CloseClientWindow(win);
		win = boxdata.GetKeyWindow();
		if (win) 
			CloseClientWindow(win);
		win = boxdata.GetTonesystemWindow();
		if (win) 
			CloseClientWindow(win);
		win = boxdata.GetActionsWindow();
		if (win) 
			CloseClientWindow(win);

		if (update)
			auimanager.Update();
	}



	void MutFrame::TextBoxOpen(WinKind kind, int box, bool update_auimanager)
	{
		DEBUGLOG (other, _T("%d,%d"),kind,box);

		char *s = NULL;
		wxString title;

		switch ( kind ) {

		case WK_KEY:
			s = GetKeyString(box, asTS);
			title.Printf(_("Keys -- Box %d"),box);
			break;

		case WK_TS:
			s = GetTSString(box, asTS);
			title.Printf(_("Tone system -- Box %d"),box);
			break;

		case WK_ACT:
			if (CAW) {
				s = GenerateCAWString();
				title=_("Action log");
			} else {
				s = GenerateACTString(box);
				title.Printf(_("Actions -- Box %d"),box);
			}
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

		int width, height;

		GetClientSize(&width, &height);
		width /= 2;
		height /= 2;

		MutTextBox *client = new MutChild(kind,
						  box,
						  this,
						  -1,
						  wxDefaultPosition,
						  wxSize(width, height));
		DEBUGLOG (other, _T("client->winKind=%d"),client->GetKind());
		DEBUGLOG (other, _T("s:= %s"),s);
		DEBUGLOG (other, _T("client->winKind=%d"),client->GetKind());

		wxString str;

		if (s)
			str = muT(s);
		else
			str = wxEmptyString;

		DEBUGLOG (other, _T("client->winKind=%d"),client->GetKind());
		DEBUGLOG (other, _T("pane title = %s"),(const wxChar *)title);

		auimanager.AddPane(client,wxAuiPaneInfo().Caption(title)
				   .CaptionVisible(true)
				   .CloseButton(true).MaximizeButton(true)
				   .Float()
				   .Name(wxString::Format(_T("WK_%d_%d"),kind,box)));

		DEBUGLOG (other, _T("client->winKind=%d"),client->GetKind());

		client->NewText(str, true);

		DEBUGLOG (other, _T("client->winKind=%d"),client->GetKind());

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
		event.Check(BoxData::GetBox(curBox).WantKeyWindow());
	}

	void MutFrame::CeToggleTS(wxUpdateUIEvent& event)
	{
		event.Check(BoxData::GetBox(curBox).WantTonesystemWindow());
	}

	void MutFrame::CeToggleAct(wxUpdateUIEvent& event)
	{
		event.Check(BoxData::GetBox(curBox).WantActionsWindow());
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
		DEBUGLOG (other, _T(""));

		if ( !LogicOn )
			CmDoActivate(event);

		const InputDeviceList & list = 
			InputDeviceClass::GetDeviceList();
		for ( InputDeviceList::const_iterator In = list.begin(); 
		      In != list.end(); In++) {
			if ( (*In)->GetMode() == DeviceStop ||
			     (*In)->GetMode() == DevicePause ) {
				boost::const_pointer_cast<InputDeviceClass>(*In)
					-> Play();
			}
		}
	
		repaint_route();

		SetStatus(SG_PLAY);
	}

	void MutFrame::CmInDevPause(wxCommandEvent& WXUNUSED(event))
	{
		const InputDeviceList & list = 
			InputDeviceClass::GetDeviceList();
		for ( InputDeviceList::const_iterator In = list.begin(); 
		      In != list.end(); In++) {
			if ( (*In)->GetMode() == DevicePlay ) {
				boost::const_pointer_cast<InputDeviceClass>(*In)
					-> Pause();
			}
		}
		repaint_route();
		SetStatus(SG_PAUSE);
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
				  (*In).get());

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
		bool Pause = 0;
  
		const InputDeviceList & list = 
			InputDeviceClass::GetDeviceList();
		for ( InputDeviceList::const_iterator In = list.begin(); 
		      In != list.end(); In++) {
			if ( (*In)->GetType() >= DTMidiFile ) {
				if ((*In)->GetMode() == DevicePlay ) {
					event.Enable(true);
				
					if ( curStatusImg != SG_PLAY )
						SetStatus(SG_PLAY);
	
					return;
				} else if ( (*In)->GetMode() == DevicePause )
					Pause = true;
			}
		}
		if ( Pause ) {
			if ( curStatusImg != SG_PAUSE )
				SetStatus(SG_PAUSE);
		} else if ( curStatusImg != 1-LogicOn )
			SetStatus(1-LogicOn);
 
		event.Enable(false);
	}

	void MutFrame::CmSetTitle(wxCommandEvent& event)
	{
		SetTitle(wxString::Format(_("%s -- %s"), APPNAME, event.GetString().c_str()));
	}

// Updaten der Protokollfenster
	void MutFrame::UpdateUI(wxCommandEvent& WXUNUSED(event))
	{

#if 0
		bool takeoveractions = TakeOverActions();
		bool update_per_box = takeoveractions && !CAW;

		size_t box = minimal_box_used;
		do {
			mutabor_box_type & b = mut_box[box];
			BoxData * boxdata = static_cast<BoxData *>(b.userdata);
		
		
			if (boxdata) {
				MutChild * win = boxdata -> GetKeyWindow();
				if (KeyChanged(box) && win) 
					win = boxdata -> GetTonesystemWindow();
				if (TSChanged(box) && win)
					win -> NewText(GetTSString(box, asTS));
				if (update_per_box) {
					win = boxdata -> GetActionsWindow();
					if (win && ACTChanged(box)) 
						win -> NewText(GenerateACTString(box));
				}
			}
			box = b.next_used;
		} while (box);

		// Aktionen
		if ( takeoveractions && CAW ) {
			BoxData & boxdata = GetCurrentBox();
		
			MutChild * win = boxdata.GetActionsWindow();
	
			if (win)
				win ->NewText(GenerateCAWString());
		}
#endif
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


#if 0 
		if ( InDevicesChanged() ) {
			const InputDeviceList & list = 
				InputDeviceClass::GetDeviceList(); 
			
			for (InputDeviceList::const_iterator In = list.begin();
			     In != list.end(); ++In) {
				if ( (*In)->GetMode() 
				     == DeviceCompileError ) 
					continue;
				if ( (*In)->GetMode() 
				     ==  DeviceTimingError ) {
					(*In)->SetMode(DeviceStop);
					(*In)->Stop();
				}
			}

			repaint_route();

			if ( !RealTime )
				wxMessageBox(_("Translation in batch mode completed.\
 Output was generated."),
					     _("Batch translation finished"), wxOK);
		}
#endif
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
		DEBUGLOG (other, _T(""));

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

/// Close all child windows of given kind
/** This function closes all child windows of the given kind.
 *
 * \param kind any wk_kind, that describes which kind of windows shall
 * be closed. Use WK_NULL to close all windows.
 */
	void MutFrame::CloseAll(WinKind kind)
	{
		DEBUGLOG (other, _T(""));

		auimanager.Update();

		Freeze();

		wxWindow * win; 
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
						CloseClientWindow(win);
					win = boxdata -> GetTonesystemWindow();
					if (win) 
						CloseClientWindow(win);
					win = boxdata -> GetActionsWindow();
					if (win) 
						CloseClientWindow(win);
					win = boxdata -> GetLogicWindow();
					break;
				default:
					wxLogError(_("Unexpected window kind: %d"), kind);
					UNREACHABLEC;
				}
				if (win)
					CloseClientWindow(win);
			}
			box = b.next_used;
		} while (box);
		Thaw();
		auimanager.Update();
	}

	void MutFrame::UpdateBoxMenu()
	{
		DEBUGLOG(other,_T("MutFrame::CmDoActivate: Set Box selection menu"));
		wxMenuItem * boxSelector = ClearMenuItem(CM_SELECTBOX);
		mutASSERT(boxSelector->IsSubMenu());
		wxMenu * boxMenu = boxSelector->GetSubMenu();
		mutASSERT(boxMenu);
		DEBUGLOG (other, _T("boxMenu = %p"),boxMenu);
		//  wxID_HIGHEST
		//  wxMenu *

		for (size_t i = 0; i < MAX_BOX; i++) {
			if (mut_box[i].used) {
				//if (ActiveWindow == this) LogicWinOpen(i);

				if (!boxCommandIds[i]) {
					boxCommandIds[i]=wxNewId();
					DEBUGLOG (other, _("Box %d got id %d"),i,boxCommandIds[i]);
				}

				DEBUGLOG (other, _("Currently %d items in box menu"),boxMenu->GetMenuItemCount());

				DEBUGLOG (other, _("Appending menu for box %d with id %d"),i,boxCommandIds[i]);
				wxString name = wxString::Format(_("Select box %d\tCtrl+%d"),i,i);
				wxString description = wxString::Format(_("Select box %d as the active Box for box specific commands."),i);
				mutASSERT(!(GetMenuBar()->FindItem(boxCommandIds[i])));
				wxMenuItem * item = new wxMenuItem(boxMenu,boxCommandIds[i],
								   name,
								   description,
								   wxITEM_RADIO);
				boxMenu->Append(item);

				if (i == curBox) boxMenu->Check(boxCommandIds[i],true);

				DEBUGLOG (other, _("Connecting command with id %d for box %d"),
					  i,boxCommandIds[i]);

				Connect( boxCommandIds[i],
					 wxEVT_COMMAND_MENU_SELECTED,
					 wxCommandEventHandler(MutFrame::RaiseLogic) );

			}
		}
	}

	bool MutFrame::RaiseTheFrame()
	{
		if (this == ActiveWindow) return true;

		ActiveWindow->Raise();

		return false;
	}


	void CheckBoxesUsed()
	{
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
						mut_box[(*R)->GetBox()].used = true;
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


	int SmallestBoxUsed()
		
	{
		int Box = MAX_BOX; // unused value

		const InputDeviceList & list = 
			InputDeviceClass::GetDeviceList();
		for ( InputDeviceList::const_iterator In = list.begin(); 
		      In != list.end(); In++) {
			const routeListType & routes = (*In)->GetRoutes();
			for ( routeListType::const_iterator R = routes.begin(); 
			      R != routes.end(); R++) {
				if ( (*R)->GetBox() >= 0 ) {
					Box = STD_PRE::min(Box, (*R)->GetBox());
				}
			}
		}
		if ( Box == MAX_BOX )
			return 0;
		else
			return Box;
	}

}
//\}
