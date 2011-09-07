/** \file  -*- C++ -*-
 ********************************************************************
 * Mutabor Frame.
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/muwx/MutFrame.h,v 1.28 2011/09/07 15:58:56 keinstein Exp $
 * Copyright:   (c) 2005, 2006, 2007, 2008 TU Dresden
 * \author Rüdiger Krauße <krausze@mail.berlios.de>
 * Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 2005/08/12
 * $Date: 2011/09/07 15:58:56 $
 * \version $Revision: 1.28 $
 * \license GPL
 *
 * $Log: MutFrame.h,v $
 * Revision 1.28  2011/09/07 15:58:56  keinstein
 * fix compilation on MinGW
 *
 * Revision 1.27  2011-09-07 13:06:50  keinstein
 * Get rid of WinAttr and Fix window opening and closing
 *
 * Revision 1.26  2011-09-05 11:30:07  keinstein
 * Some code cleanups moving some global box arrays into class mutaborGUI::BoxData
 * Restore perspective on logic start
 *
 * Revision 1.25  2011-09-04 12:02:08  keinstein
 * require wxWidgets 2.8.5 configure.in
 *
 * Revision 1.24  2011-08-28 20:09:11  keinstein
 * several impovements for opening and saving files
 *
 * Revision 1.23  2011-08-21 16:52:05  keinstein
 * Integrate a more sophisticated editor menu based on the stc sample
 *
 * Revision 1.22  2011-08-14 18:32:18  keinstein
 * Use of m_childView of wxDocChildFrame instead of own view fixes a bad access.
 * Use wxDocChildFrame::OnCloseWindow
 * remove some unneeded code
 *
 * Revision 1.21  2011-08-11 19:00:48  keinstein
 * get Document/View running.
 * Needs further testing (possible segfaults).
 *
 * Revision 1.20  2011-08-06 09:21:23  keinstein
 * activated and debugged document manager
 *
 * Revision 1.19  2011-07-31 20:16:04  keinstein
 * Implemented opening files from command line using Document/View framework
 *
 * Revision 1.18  2011-07-31 12:40:42  keinstein
 * Added classes and functions for Document/View support
 *
 * Revision 1.17  2011-02-20 22:35:57  keinstein
 * updated license information; some file headers have to be revised, though
 *
 * Revision 1.16  2010-11-21 13:15:47  keinstein
 * merged experimental_tobias
 *
 * Revision 1.14.2.5  2010-11-18 21:46:14  keinstein
 * MutFrame: get rid of OnIdle (this may break something, but saves much more CPU cycles
 * Some further steps to get rid of EDevice*
 *
 * Revision 1.14.2.4  2010-11-14 22:29:53  keinstein
 * Remvoed EDevice.cpp and EDevice.h from the sources list
 * They still reside in the source tree, since they have been used for Midi/GMN
 * file playing. That funcitonality has been disabled so far.
 * After reimplementation the files can be removed.
 *
 * Revision 1.14.2.3  2010-09-30 16:26:26  keinstein
 * remove global variables routewindow and frame
 * move route loading and route saving into MutRouteWnd
 * implement MutRouteWnd::InitShapes.
 * Destroy Route children before loading new route configuration (still some crashes)
 *
 * Revision 1.14.2.2  2010/03/30 08:38:26  keinstein
 * added rudimentary command line support
 * changed debug system to allow selection of messages via command line
 * further enhancements to the route dialogs
 *
 * Revision 1.14.2.1  2009/08/10 11:23:12  keinstein
 * merged from wrong tree
 *
 * Revision 1.15  2009/08/10 11:15:46  keinstein
 * some steps towards new route window
 *
 * Revision 1.14  2008/08/01 16:24:30  keinstein
 * Fix some segfaults on stopping Mutabor
 *
 * Revision 1.13  2008/07/21 09:25:29  keinstein
 * RcfFile: removed
 * TextBoxWanted: one variable per box and type
 * removed ROUTE_WIN and REPAINT_ROUTE definitions
 * reformatted debug logging
 * Implement box selection Menu
 * MutFrame::repaint_route(): New function
 *
 * Revision 1.12  2008/06/30 08:57:17  keinstein
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
 * Revision 1.11  2008/06/02 16:27:08  keinstein
 * Chenged FileNameDialog
 * CmSetTitle(), HasClient(): new functions
 *
 * Revision 1.10  2008/03/11 10:37:34  keinstein
 * Holyday edition
 * put CM_xxx in an enum
 * use wx constants
 * document mutframe
 * some white space formattings
 * make route saving more system specific
 * many other fixes
 *
 * Revision 1.9  2008/02/04 10:22:53  keinstein
 * Fix typo in MutFrame::GetDockArt declaration
 *
 * Revision 1.8  2008/01/25 09:37:11  keinstein
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
 * \addtogroup muwx
 * \{
 ********************************************************************/

#ifndef MUTFRAME_H
#define MUTFRAME_H

#include "Global.h"
#include "MutChild.h"
#include "MutEditFile.h"
#include "MutRouteWnd.h"
#include "wx/aui/aui.h"
#include "wx/toolbar.h"
#include "wx/docview.h"

/// Main mutabor frame class
/** This class is used to create the main windows
 */

namespace mutaborGUI {
	class MutView; // see MutView.h
	class MutDocument; // see MutDocument.h
}

using mutaborGUI::MutView;
using mutaborGUI::MutDocument;

class MutFrame : public wxDocChildFrame
{

public:
	/// Constructor
	/** This constructor creates a new main window.
	 */

	MutFrame(wxFrame *parent, const wxWindowID id, const wxString& title,
	         const wxPoint& pos, const wxSize& size,
	         const long style);

	MutFrame(MutDocument *doc,
		 MutView *v,
		 wxFrame *frame,
		 wxWindowID id,
		 const wxString& title,
		 const wxPoint& pos = wxDefaultPosition,
		 const wxSize& size = wxDefaultSize,
		 long type = wxDEFAULT_FRAME_STYLE,
		 const wxString& name = wxT("Mutabor frame"));


	/// Destructor
	virtual ~MutFrame();

#if wxUSE_TOOLBAR
	/// initialize the toolbar
	/** Initializes the toolbar.
	\param toolBar Toolbar to which the tools shall be added
	*/
	void InitToolBar(wxToolBar* toolBar);

#endif

	/// passes an event to the editor.
	/** This function is used to pass one event to the
	client window. 
	\param event Event to be passed */
	void PassEventToEditor(wxCommandEvent &event);

	/// passes an UpdateUIEvent to the editor.
	/** This function is used to pass one event to the
	client window. 
	\param event Event to be passed */
	void PassEventToEditorUI(wxUpdateUIEvent& event);

	/// passes a FindDialogEvent to the editor.
	/** This function is used to pass one event to the
	client window. 
	\param event Event to be passed */
	void PassEventToEditorFind(wxFindDialogEvent& event);

	/// passes an event to the MDI client window.
	/** \deprecated This function was formerly used to pass one event
	to the client MDI window.

	\param event Event to be passed */
	void EventPassOn(wxCommandEvent& event);

	/// Handles close event.
	/** This function tries to determine, if we can close the current window.
	 */
	void OnCloseWindow(wxCloseEvent& event);

	/// Hande paint events for Document/View framework
	/** This function call the paint function */
	void OnPaint(wxPaintEvent& event);

	/// This function creates a new file editor
	/** Handle new file event if we don't have a client yet. */
	void CmFileNew(wxCommandEvent& WXUNUSED(event));

	/// Open an existing file if we don't have a client yet.
	void CmFileOpen(wxCommandEvent& WXUNUSED(event));

	/// Opens the given file, if we don't have a client yet.
	bool OpenFile(wxString path, bool newfile=false);

	/// Attach a client to the Frame
	bool SetClient (wxWindow * win, const wxString &title);

#if (!defined(__WXMAC__) || defined(__WXCOCOA__)) && !defined(__WXMSW__)
	/// Set the window name, i.e. frame title
	virtual void SetLabel (const wxString &label) { SetTitle(label); }
#endif

	/// Get a file name to open
	///    static wxString FileNameDialog(wxWindow * parent);

	void CmDoActivate(wxCommandEvent& event);

	void RaiseLogic(wxCommandEvent& event);

	wxMenuItem* ClearMenuItem(int id);

	void ClearSubMenu(wxMenuItem * item);

	void DoStop();

	void CmStop(wxCommandEvent& WXUNUSED(event));

	void CmPanic(wxCommandEvent& WXUNUSED(event));

	void CeExecute(wxUpdateUIEvent& event);

	void CeActivate(wxUpdateUIEvent& event);

	void CeStop(wxUpdateUIEvent& event);

	void CmRoutes(wxCommandEvent& event);

	void CmToggleKey(wxCommandEvent& WXUNUSED(event));

	void CmToggleTS(wxCommandEvent& WXUNUSED(event));

	void CmToggleAct(wxCommandEvent& WXUNUSED(event));

	void CmToggleOWM(wxCommandEvent& WXUNUSED(event));

	void CmToggleCAW(wxCommandEvent& WXUNUSED(event));

	void CeToggleKey(wxUpdateUIEvent& event);

	void CeToggleTS(wxUpdateUIEvent& event);

	void CeToggleAct(wxUpdateUIEvent& event);

	void CeToggleOWM(wxUpdateUIEvent& event);

	void CeToggleCAW(wxUpdateUIEvent& event);

	// Recorder-Knˆpfe
	void CmInDevStop(wxCommandEvent& WXUNUSED(event));

	void CmInDevPlay(wxCommandEvent& WXUNUSED(event));

	void CmInDevPause(wxCommandEvent& WXUNUSED(event));

	void StopInDev();

	void CeInDevStop(wxUpdateUIEvent& event);

	void CeInDevPlay(wxUpdateUIEvent& event);

	void CeInDevPause(wxUpdateUIEvent& event);

	void CmSetTitle(wxCommandEvent& event);

	/// Update GUI when the mutabor kernel or file players have acted
	void UpdateUI(wxCommandEvent& WXUNUSED(event));

	//	void OnIdle(wxIdleEvent& WXUNUSED(event));

	//    void OnActivate(wxActivateEvent& event);
	void OnEraseBackground(wxEraseEvent& event);

	void OnSize(wxSizeEvent& event);

	wxAuiDockArt* GetDockArt();

	void WindowSize(MutChild *win);

	void SaveState();

	void RestoreState();

	void LogicWinOpen(int box);

	void ToggleTextBox(WinKind kind);

	void TextBoxOpen(WinKind kind,
			 int box, 
			 bool update_auimanager	= true);

	void CmSelectBox();

	void CmCloseChild();

	void CloseAll(WinKind kind = WK_NULL);

	void SetStatus(int WXUNUSED(imgNr))
	{
		//StatusGadget->SelectImage(curStatusImg = imgNr, true);
	}

	wxRect DetermineFrameSize ();

	/// retrun true if we have already a client
	bool HasClient()
 	{
		return (bool) client;
	}

	void UpdateBoxMenu();
	bool RaiseTheFrame();

	static void repaint_route()
	{
		MutFrame * routewin = dynamic_cast<MutFrame *>(FindWindowById(WK_ROUTE));

		if (routewin) {
			MutRouteWnd * route = dynamic_cast<MutRouteWnd *> (routewin->client);

			if (route) route->Refresh();
		}
	}

	void SetFileMenu(wxMenu * f) { filemenu = f; }
	void SetEditMenu(wxMenu * e) { editmenu = e; }
private:

	wxMenu * editmenu;
	wxMenu * filemenu;
	
	void CloseClientWindow(wxWindow * w)
	{
		wxASSERT(w);
		if (!w) return;

		w->Disable();
		auimanager.ClosePane(auimanager.GetPane(w));
		DEBUGLOG(other, _T("Detaching pane."));
		auimanager.DetachPane(w);
		auimanager.Update();

		DEBUGLOG(other, _T("Closing window."));
		w->Close(); // win should be invalid now.
	}

	int curStatusImg;

	wxAuiManager auimanager;

	wxWindow *keywindows[MAX_BOX];
	wxWindow *tswindows[MAX_BOX];
	wxWindow *actionwindows[MAX_BOX];

	wxWindow *client;

	static MutFrame * ActiveWindow;
	static int boxCommandIds[MAX_BOX];
	DECLARE_EVENT_TABLE()
};

// globals

extern bool asTS;
extern bool SaveEditor;
extern bool UseColorBars;
extern bool OWM; // One Window Mode
extern bool CAW; // Common Action Window
extern bool LogicOn;

/// synchronizes \c used flag of \c mut_box with the routes
void CheckBoxesUsed();

extern wxString CompiledFile;
#endif
