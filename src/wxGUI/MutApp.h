/** \file   -*- C++ -*-
 ***********************************************************************
 * Mutabor Application.
 *
 * \author R. Krauße <krausze@users.berlios.de>
 *         T. Schlemmer <keinstein@users.berlios.de>
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
 *
 *
 *************************************************************************
 * \dir src/wxGUI
 * The directory src/wxGUI contains the wxWidgets frontend classes of Mutabor.
 *************************************************************************
 *
 * \defgroup GUI wxWidgets Mutabor GUI
 * While the original frontend of Mutabor was designed using Borland OWL
 * the current one uses the platform independent environment provided by
 * wxWidgets.
 *
 *\{
 */

#if (!defined(MUWX_MUTAPP_H) && !defined(PRECOMPILE)) \
	|| (!defined(MUWX_MUTAPP_H_PRECOMPILED))
#ifndef PRECOMPILE
#define MUWX_MUTAPP_H
#endif

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

#include "src/kernel/Defs.h"
#include "src/wxGUI/MutFrame.h"
#include "src/wxGUI/MutDocManager.h"

#ifndef MUWX_MUTAPP_H_PRECOMPILED
#define MUWX_MUTAPP_H_PRECOMPILED

/////////////////////////////////////////////////////////////////////////////
// Name:        MutApp.h
// Purpose:     Mutabor Application
// Author:      R. Krauße
// Modified by:
// Created:     12.08.05
// Copyright:   (c) R. Krauße
// Licence:     wxWindows license
/////////////////////////////////////////////////////////////////////////////

//#include "Defs.h"
//#include "wx/intl.h"
#include "wx/app.h"

/// Declare a frame array as an hash table
WX_DECLARE_HASH_MAP( wxFrame *,      // type of the keys
                     wxFrame *,    // type of the values
                     wxPointerHash,     // hasher
                     wxPointerEqual,   // key equality predicate
                     FrameHash); // name of the class


namespace mutaborGUI {

	extern wxHtmlHelpController * HelpController;
#if wxUSE_PRINTING_ARCHITECTURE
//! global print data, to remember settings during the session
	extern wxPrintData *g_printData;
	extern wxPageSetupData *g_pageSetupData;
#endif // wxUSE_PRINTING_ARCHITECTURE


/// Mutabor application class
/** This class is the main application class of Mutabor. It handles
    initialization, exiting and on Mac OS also the application menu.
*/

	class MutApp : public wxApp
	{

		friend class AppAbout;

	public:
		/// Some configuration help for Menu generation
		enum MenuType {
			ProgramMenu, ///< Mac: common application menu
			EditorMenu, ///< File editor menu
			RouteMenu ///< Route editor menu
		};

		/// Initialization
		/** This function does the common setup.
		    \li Application name
		    \li Locale
		    \li Help system
		    \li Settings
		    \li Main window 
		*/
		bool OnInit();
	
		/// Initialize command line arguments
		void OnInitCmdLine(wxCmdLineParser&  parser);
		/// Process command line arguments
		bool OnCmdLineParsed(wxCmdLineParser&  parser);

		void OnUnhandledException();
		bool OnExceptionInMainLoop();
		void OnFatalException();
#ifdef DEBUG
		void OnAssertFailure(const wxChar *file,
				     int line,
				     const wxChar *func,
				     const wxChar *cond,
				     const wxChar *msg);
#endif
		// Extend event processing to search the document manager's event table
		virtual bool ProcessEvent(wxEvent& event);
	
		/// Pass event to document manager
		// some compilers do not support overloading in event tables
		void PassEventToDocManagerCMD(wxCommandEvent& event);
		void PassEventToDocManagerUPD(wxUpdateUIEvent& event);

		/// add handling of last files.
		void OnMRUFile(wxCommandEvent& event);

		/// Display an about dialog box
		void CmAbout (wxCommandEvent& event);
		/// Display and handle setup dialog.
		void CmSetup (wxCommandEvent& event);
		/// Create an editor file
		void CmFileNew (wxCommandEvent& event);
		/// Open a new editor file
		void CmFileOpen (wxCommandEvent& event);
		/// Edit printing settings
		void OnPrintSetup (wxCommandEvent & event);
	
		/// Open a new route editor
		void CmRoutes (wxCommandEvent& event);
		/// Load a Route
		void CmRouteLoad(wxCommandEvent& event)
			{
				MutRouteWnd::CmRouteLoad(event);
			}

		/// Save a Route
		void CmRouteSave(wxCommandEvent& event)
			{
				MutRouteWnd::CmRouteSave(event);
			}

		/// Save a Route under a new name
		void CmRouteSaveAs(wxCommandEvent& event)
			{
				MutRouteWnd::CmRouteSaveAs(event);
			}

		/// Read help about a certain topic
		void CmHelp (wxCommandEvent& event);
		/// Show the helpwindow on the page associated with a certain command id
		/** This function opens a help window according to the current command id.
		    \param commandId wxWidgets command id to open help window for. 
		*/
		void ShowHelp(int commandId);

		/// Show an error message from somewhere in the program
		void CmError(wxCommandEvent& event);

		/// Exit the program
		void CmQuit (wxCommandEvent& event);
#ifdef DEBUG
		/// Exit immediately with exit()
		/** This function meight be helpful in compiling */
		void CmCallExit(wxCommandEvent& event)
			{
				mutUnused(event);
				exit(0);
			}
#endif

		/// Create a main frame
		/** This function create a new Top Level Frame.
		    \param type Flag indicating which parts the menu bar shall contain.
		    \param id Window id
		*/
		MutFrame* CreateMainFrame(MenuType type, wxWindowID id = wxID_ANY);

		/// Initialize a main frame
		/** This function initialises a freshly created Top Level Frame.
		    \param frame frame that will be created
		*/
		MutFrame* InitMainFrame(MenuType type, MutFrame * frame);

		/// Registers a frame
		/** Register the frame in the application specific frame list.
		    Though wxWidgets handles its own \c wxTopLevelWindows,
		    it is not documented and its usage seems not to be encouraged.
		    \param f Frame to be added.
		    \see UnregisterFrame
		*/
		void RegisterFrame(wxFrame * f);
		/// Unregisters a frame
		/** Removes the frame f from the application specific frame list.
		    \param f Frame to be removed
		    \see RegisterFrame
		*/
		void UnregisterFrame (wxFrame * f);

		/// Get a possibly localized resource file name
		/** This function tries to find the file given by \p file in a
		    localized version before returning it unlocalized if that is
		    impossible.
	 
		    For example, the file help.zip is searched for 
		    \li first in \c /usr/share/mutabor/de_DE/help.zip,
		    \li otherwise in \c /usr/share/mutabor/de/help.zip.
		    \li If that fails \c /usr/share/mutabor/help.zip is 
		    returned unchecked.
		    \param file File name to be searched for.
		    \return localized file name.
		*/

		static wxString GetResourceName(const wxString & file);

		/// Callback for program quitting
		/** While quitting wxWidgets calls this virtual function. We use it
		    to save the current setup.*/
		virtual int OnExit();

#ifdef __WXMAC__
		virtual void MacOpenFile(const wxString &fileName);

#endif

		/// Save global state.
		/** Save the current global settings in the registry or configuration file.
		 */
		void SaveState();

		/// Load global state.
		/** Load the current global settings in the registry or configuration file.
		 */
		void RestoreState();

		/// determine if new frame must be opened
		/** Determine we have an empty frame or we must open a new one
		 */
		static bool MustOpenFrame(MutFrame * frame)
			{
				if (frame) {
					if (frame->HasClient())
						return true;
					else return false;
				} else return true;
			}

		/// Allow access to the document manager
		const wxDocManager *GetDocumentManager() const { return document_manager; }

		/// Allow write access to the document manager
		wxDocManager *GetDocumentManager() { return document_manager; }
    

	private:

		/// Creates a file menu
		/** This function creates the file menu.
		    \param menuBar Menu bar, where the file menu is to be appended
		    \param type Flags indicating, which menus shall be created. 
		*/
		wxMenu *  MakeFileMenu(wxMenuBar * menuBar, MenuType type);

		/// Creates an edit menu
		/** This function creates the editor menu.
		    \param menuBar Menu bar, where the file menu is to be appended
		    \param type Flags indicating, which menus shall be created. 
		*/
		void MakeEditMenu(wxMenuBar * menuBar, MenuType type);

		/// Creates a mutabor logic menu
		/** This function creates the logic menu.
		    \param menuBar Menu bar, where the file menu is to be appended
		*/
		void MakeLogicMenu(wxMenuBar * menuBar);

		/// Creates a mutabor routes menu
		/** This function creates the roues menu.
		    \param menuBar Menu bar, where the file menu is to be appended
		*/
		void MakeRoutesMenu(wxMenuBar * menuBar, MenuType type);

		/// Creates a View menu
		/** This function creates the view menu.
		    \param menuBar Menu bar, where the file menu is to be appended
		    \param type Flags indicating, which menus shall be created. 
		*/
		void MakeViewMenu(wxMenuBar * menuBar, MenuType type);

		/// Creates a mutabor sequencer menu
		/** This function creates the sequencer menu.
		    \param menuBar Menu bar, where the file menu is to be appended
		*/
		void MakeSequencerMenu(wxMenuBar * menuBar);

		/// Creates a mutabor help menu
		/** This function creates the help menu.
		    \param menuBar Menu bar, where the file menu is to be appended
		*/
		void MakeHelpMenu(wxMenuBar * menuBar);

		
	protected:

		/// locale data to be used inside the application
		wxLocale m_locale;

		/// Document manager.
		mutaborGUI::MutDocManager * document_manager;

		/// flag indicating, that we are in quitting mode.
		bool quitting;

	
	private:
		DECLARE_EVENT_TABLE()
	};

/// About Dialog
/** This is a manually created about dialog.
    \deprecated It will be replaced by a ressource driven version.
*/

	class AppAbout : public wxDialog
	{

	public:
		/// Constructor creating the window.
		/** \param parent Parent window
		    \param style Dialog style of about window
		*/
		AppAbout (wxWindow *parent=(wxWindow *) NULL, long style = 0);
	};

}


using mutaborGUI::MutApp;
DECLARE_APP(MutApp)




#endif  // __MUTAPP_H precompiled
#endif  // __MUTAPP_H_INCLUDED__
///\}
