/** \file  -*- C++ -*-
 ********************************************************************
 * Mutabor Frame.
 *
 * Copyright:   (c) 2005, 2006, 2007, 2008 TU Dresden
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

#if (!defined(MUWX_MUTFRAME_H) && !defined(PRECOMPILE)) \
	|| (!defined(MUWX_MUTFRAME_H_PRECOMPILED))
#ifndef PRECOMPILE
#define MUWX_MUTFRAME_H
#endif

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

#include "src/kernel/Defs.h"
//#include "src/kernel/Global.h"
#include "src/wxGUI/MutChild.h"
#include "src/wxGUI/MutEditFile.h"
#include "src/wxGUI/MutRouteWnd.h"
#include "src/wxGUI/StatusBar.h"

#ifndef MUWX_MUTFRAME_H_PRECOMPILED
#define MUWX_MUTFRAME_H_PRECOMPILED


#include "wx/aui/aui.h"
//#include "wx/toolbar.h"
#include "wx/docview.h"

class wxToolBar;

namespace mutaborGUI {

	class MutView; // see MutView.h
	class MutDocument; // see MutDocument.h

	/// Main mutabor frame class
	/** This class is used to create the main windows
	 */
	class MutFrame : public wxDocChildFrame
	{

	public:
		typedef wxDocChildFrame base;
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

		/**
		 * This function informs the child windows about AUI
		 * events. It is an event handler AUI events.
		 *
		 * \note The AUI manager does not inform the childs
		 * directly.
		 *
		 * \param event Event as passed by wxWidgets.
		 */
		void OnAuiChildEvent(wxAuiManagerEvent & event);

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


//		void WindowSize(MutChild *win);

		void SaveState();

		void RestoreState();

		void LogicWinOpen(mutabor::Box box);

		void ToggleTextBox(WinKind kind);

		static void BoxWindowsOpen(mutabor::Box box, bool update = true) {
			if (ActiveWindow)
				ActiveWindow -> DoBoxWindowsOpen(box,update);
		}

		static void BoxWindowsClose(mutabor::Box box, bool update = true) {
			if (ActiveWindow)
				ActiveWindow -> DoBoxWindowsClose(box,update);
		}

		void DoBoxWindowsOpen(mutabor::Box box, bool update = true);
		void DoBoxWindowsClose(mutabor::Box box, bool update = true);

		void TextBoxOpen(WinKind kind,
				 mutabor::Box & box,
				 bool update_auimanager	= true);

		void CmSelectBox();

		void CmCloseChild();

		void CloseAll(WinKind kind = WK_NULL);

		bool Destroy();

		wxRect DetermineFrameSize ();

		/// retrun true if we have already a client
		bool HasClient()
			{
				return client != NULL;
			}

		void UpdateBoxMenu();
		bool RaiseTheFrame();

		static void repaint_route()
			{
				MutFrame * routewin = dynamic_cast<MutFrame *>(FindWindowById(WK_ROUTE));

				if (routewin) {
					MutRouteWnd * route = dynamic_cast<MutRouteWnd *> (routewin->client);

					if (route) {
						route->Refresh();
						route->Update();
					}
				}
			}

		void SetFileMenu(wxMenu * f) { filemenu = f; }
		void SetEditMenu(wxMenu * e) { editmenu = e; }

		static wxDocument * GetActiveDocument() {
			if (!ActiveWindow) return NULL;
			return ActiveWindow->GetDocument();
		}
		static MutFrame * GetActiveWindow() {
			return ActiveWindow;
		}
		void CloseClientWindow(wxWindow * w, bool update = true) {
			mutASSERT(w);
			if (!w) return;

			w->Disable();
			// if this attribute is not set, whe have forgotten to set it
			// it is needed for User interaction
			mutASSERT(auimanager.GetPane(w).IsDestroyOnClose());
			// undocumented but does what we want
			auimanager.ClosePane(auimanager.GetPane(w));
			DEBUGLOG (other, "Detaching pane." );
			// should be done by ClosePane: auimanager.DetachPane(w);
			if (update) auimanager.Update();

			DEBUGLOG (other, "Closing window." );
			// should be done by ClosePane:	w->Close();
			// win should be invalid now.
		}

	private:

		wxMenu * editmenu;
		wxMenu * filemenu;

		virtual wxStatusBar* OnCreateStatusBar(int number, long style, wxWindowID id, const wxString& name) {
			StatusBar * bar = new StatusBar(this, id, style, name);
			if (!bar) return NULL;
			bar->SetActive(LogicOn);
			bar->SetPlaystate(StatusBar::Hide);
			return bar;
		}

		int curStatusImg;

		wxAuiManager auimanager;
		wxWindow *client;

		static MutFrame * ActiveWindow;
		typedef std::map<int,mutabor::Box> boxCommandMap;
		static boxCommandMap boxCommandIds;
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

}
#endif
#endif
