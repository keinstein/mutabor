/** \file
 ***********************************************************************
 * Mutabor Application.
 *
 * $Id: MutApp.h,v 1.16 2011/02/19 00:21:19 keinstein Exp $
 * \author R. Krauße <krausze@users.berlios.de>
 *         T. Schlemmer <keinstein@users.berlios.de>
 * \date $Date: 2011/02/19 00:21:19 $
 * \version $Revision: 1.16 $
 *
 * $Log: MutApp.h,v $
 * Revision 1.16  2011/02/19 00:21:19  keinstein
 * change version number
 *
 * Revision 1.15  2010-12-10 09:28:23  keinstein
 * add menu item to help menu, which calls exit(0).
 *
 * Revision 1.14  2010-11-21 13:15:47  keinstein
 * merged experimental_tobias
 *
 * Revision 1.12.2.3  2010-09-30 16:26:26  keinstein
 * remove global variables routewindow and frame
 * move route loading and route saving into MutRouteWnd
 * implement MutRouteWnd::InitShapes.
 * Destroy Route children before loading new route configuration (still some crashes)
 *
 * Revision 1.12.2.2  2010/03/30 08:38:27  keinstein
 * added rudimentary command line support
 * changed debug system to allow selection of messages via command line
 * further enhancements to the route dialogs
 *
 * Revision 1.12.2.1  2009/08/10 11:23:12  keinstein
 * merged from wrong tree
 *
 * Revision 1.13  2009/08/10 11:15:46  keinstein
 * some steps towards new route window
 *
 * Revision 1.12  2008/10/09 15:14:02  keinstein
 * make compile on mingw
 *
 * Revision 1.11  2008/06/30 08:27:10  keinstein
 * New Variable: routewindow
 * OnInit(): Register Ids from Mutabor.rh
 * Implement Loading and Saving routes
 * MustOpenFrame(): New function.
 * On window open: use MustOpenFrame() to determine if new frame must be created
 * CmRoutes(): Implement correct window opening.
 * CmQuit(): Reimplemented Frame deletion to prevent crashes and endless loops on quitting
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
 * Revision 1.9  2008/01/25 09:14:35  keinstein
 * MutApp::OnInit:
 * 	Remove unused i18n demo code.
 * 	output directory constants in Debug compilation
 * 	Add PNG and GIF image handlers.
 * 	Add ZIP filesystem handler
 * 	Load Resource file Mutabor.xrc
 *
 * MutApp::GetResourceName:
 * MutApp::CmSetup:
 * 	New function.
 *
 * Add CM_SETUP event handler.
 *
 *
 * First steps towards a help system
 *
 * Revision 1.8  2007/12/17 12:56:04  keinstein
 * Fix Unicode compilation
 * Catch CM_ROUTES
 * MutApp::CmRoutes: New function.
 * MuttApp::CreateMainFrame: Accept window id as argument.
 *
 * Revision 1.7  2007/10/09 14:57:49  keinstein
 * AppAbout: New class.
 * MutApp::CmAbout: Use AppAbout for displaying about window.
 *
 * Revision 1.6  2007/10/08 12:15:51  keinstein
 * Move FileNew and FileOpen from MutFrame to MutApp
 * Enable multiple main windows
 * MutApp:
 * 	CmFileNew(),
 * 	CmFileOpen()
 * 	CmQuit(),
 * 	RegisterFrame(),
 * 	UnregisterFrame(): New functions.
 * 	Rename OnAbout -> CmAbout
 *
 * 	frames, quitting: New Member variables
 *
 * New Class: FrameHash;
 *
 * Revision 1.5  2007/10/05 12:39:38  keinstein
 * first steps towards a real mac version:
 *  - automagic locale selection
 *  - dont exit on fram delete on Mac
 *  - install own event table
 *  - CreateMainFrame: new function
 *  - move OnAbout from MutFrame
 *
 * Revision 1.4  2006/03/27 17:19:14  keinstein
 * Preliminary localization support
 *
 * Revision 1.3  2006/01/18 15:35:43  keinstein
 * Prevent from double inclusion
 *
 *************************************************************************
 * \dir muwx
 * The directory muwx contains the wxWidgets frontend classes of Mutabor.
 *************************************************************************
 *
 * \defgroup muwx wxWidgets Mutabor GUI
 * While the original frontend of Mutabor was designed using Borland OWL
 * the current one uses the platform independent environment provided by
 * wxWidgets.
 *
 *\{
 */

#ifndef __MUTAPP_H_INCLUDED__
#define __MUTAPP_H_INCLUDED__

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
#include "MutFrame.h"

/// Declare a frame array as an hash table
WX_DECLARE_HASH_MAP( wxFrame *,      // type of the keys
                     wxFrame *,    // type of the values
                     wxPointerHash,     // hasher
                     wxPointerEqual,   // key equality predicate
                     FrameHash); // name of the class

/// Mutabor application class
/** This class is the main application class of Mutabor. It handles
    initialization, exiting and on Mac OS also the application menu.
*/

class MutApp : public wxApp
{

	friend class AppAbout;

private:
	/// Some configuration help for Menu generation
	enum MenuType {
	        ProgramMenu, ///< Mac: common application menu
	        EditorMenu, ///< File editor menu
	        RouteMenu, ///< Route editor menu
	};

public:
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
#ifdef __WIN32__
	void OnUnhandledException() { throw; }
	bool OnExceptionInMainLoop() { throw; }
	void OnFatalException() { throw; }
#endif 
	/// 

	/// Display an about dialog box
	void CmAbout (wxCommandEvent& event);
	/// Display and handle setup dialog.
	void CmSetup (wxCommandEvent& event);
	/// Create an editor file
	void CmFileNew (wxCommandEvent& event);
	/// Open a new editor file
	void CmFileOpen (wxCommandEvent& event);
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
	/// Exit the program
	void CmQuit (wxCommandEvent& event);
#ifdef DEBUG
	/// Exit immediately with exit()
	/** This function meight be helpful in compiling */
	void CmCallExit(wxCommandEvent& event)
	{
	  exit(0);
	}
#endif

	/// Create a main frame
	/** This function create a new Top Level Frame.
	    \param type Flag indicating which parts the menu bar shall contain.
	    \param id Window id
	*/
	MutFrame* CreateMainFrame(MenuType type, wxWindowID id = wxID_ANY);
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

private:

	/// Creates a file menu
	/** This function creates the file menu.
	    \param menuBar Menu bar, where the file menu is to be appended
	    \param type Flags indicating, which menus shall be created. 
	*/
	void MakeFileMenu(wxMenuBar * menuBar, MenuType type);

	/// Creates a mutabor logic menu
	/** This function creates the logic menu.
	    \param menuBar Menu bar, where the file menu is to be appended
	*/
	void MakeLogicMenu(wxMenuBar * menuBar);

	/// Creates a mutabor routes menu
	/** This function creates the roues menu.
	    \param menuBar Menu bar, where the file menu is to be appended
	*/
	void MakeRoutesMenu(wxMenuBar * menuBar);

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

	/// locale data to be used inside the application
	wxLocale m_locale;

	/// list of main frames in the application
	/** \deprecated \see RegisterFrame(), UnregisterFrame()
	 */
	FrameHash frames;

	/// flag indicating, that we are in quitting mode.
	bool quitting;

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


DECLARE_APP(MutApp)



#endif  // __MUTAPP_H_INCLUDED__
///\}
