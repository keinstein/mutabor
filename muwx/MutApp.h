/** \file
 ***********************************************************************
 * Mutabor Application.
 *
 * $Id: MutApp.h,v 1.10 2008/03/11 10:37:34 keinstein Exp $
 * \author R. Krauße <krausze@users.berlios.de>
 * \date $Date: 2008/03/11 10:37:34 $
 * \version $Revision: 1.10 $
 *
 * $Log: MutApp.h,v $
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
class MutApp : public wxApp {
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
  /// Read help about a certain topic
  void CmHelp (wxCommandEvent& event);
  /// Show the helpwindow on the page associated with a certain command id
  /** This function opens a help window according to the current command id.
      \param commandId wxWidgets command id to open help window for. 
  */
  void ShowHelp(int commandId);
  /// Exit the program
  void CmQuit (wxCommandEvent& event);
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

  /// Save global state.
  /** Save the current global settings in the registry or configuration file.
   */
  void SaveState();

  /// Load global state.
  /** Load the current global settings in the registry or configuration file.
   */
  void RestoreState();

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
