/** \file MutFrame.cpp
 ********************************************************************
 * Mutabor Frame.
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/muwx/MutFrame.h,v 1.13 2008/07/21 09:25:29 keinstein Exp $
 * Copyright:   (c) 2005, 2006, 2007, 2008 TU Dresden
 * \author Rüdiger Krauße <krausze@mail.berlios.de>
 * Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 2005/08/12
 * $Date: 2008/07/21 09:25:29 $
 * \version $Revision: 1.13 $
 * \license GPL
 *
 * $Log: MutFrame.h,v $
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

/// Main mutabor frame class
/** This class is used to create the main windows
 */
class MutFrame : public wxFrame
{
public:
  /// Constructor 
  /** This constructor creates a new main window. 
   */
    MutFrame(wxWindow *parent, const wxWindowID id, const wxString& title,
            const wxPoint& pos, const wxSize& size,
			 const long style);
			 
    /// Destructor
    ~MutFrame();

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

    /// passes an event to the MDI client window.
    /** \deprecated This function was formerly used to pass one event
	to the client MDI window.

	\param event Event to be passed */
    void EventPassOn(wxCommandEvent& event);

    /// Handles close event.
    /** This function tries to determine, if we can close the current window.
     */
    void OnClose(wxCloseEvent& event);
    
    /// This function creates a new file editor
    /** Handle new file event if we don't have a client yet. */
    void CmFileNew(wxCommandEvent& WXUNUSED(event));

    /// Open an existing file if we don't have a client yet.
    void CmFileOpen(wxCommandEvent& WXUNUSED(event));
    
    /// Opens the given file, if we don't have a client yet.
    bool OpenFile(wxString path, bool newfile=false);

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
    static void CmRouteLoad(wxCommandEvent& event);
    static void CmRouteSave(wxCommandEvent& event);
    static void CmRouteSaveAs(wxCommandEvent& event);

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

    // Idle
    void UpdateUI(wxCommandEvent& WXUNUSED(event));
    void OnIdle(wxIdleEvent& WXUNUSED(event));
    //    void OnActivate(wxActivateEvent& event);
    void OnEraseBackground(wxEraseEvent& event);
    void OnSize(wxSizeEvent& event);
    wxAuiDockArt* GetDockArt();
    
    void WindowSize(MutChild *win);
    void SaveState();
    void RestoreState();

    void LogicWinOpen(int box);
    void ToggleTextBox(WinKind kind);
    void TextBoxOpen(WinKind kind, int box);
    void CmSelectBox();
    void CmCloseChild();
    void CloseAll(WinKind kind);

    void SetStatus(int WXUNUSED(imgNr))
    {
      //StatusGadget->SelectImage(curStatusImg = imgNr, true);
    }
	
    wxRect DetermineFrameSize ();

    /// retrun true if we have already a client
    bool HasClient() { return (bool) client; }

    void UpdateBoxMenu();
    bool RaiseTheFrame();

    static void repaint_route() {
      MutFrame * routewin = dynamic_cast<MutFrame *>(FindWindowById(WK_ROUTE));
      if (routewin) {
	MutRouteWnd * route = dynamic_cast<MutRouteWnd *> (routewin->client);
	if (route) route->Refresh();
      }
    }

    
 private:
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
extern int curBox;

extern wxString CompiledFile;

extern wxString curLogic[MAX_BOX];
extern wxString curTS[MAX_BOX];
extern int curTaste[MAX_BOX][2];
extern bool TextBoxWanted[][3];

#endif
