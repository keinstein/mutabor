/** \file
 ***********************************************************************
 * Mutabor Application.
 *
 * $Id: MutApp.h,v 1.8 2007/12/17 12:56:04 keinstein Exp $
 * \author R. Krauße <krausze@users.berlios.de>
 * \date $Date: 2007/12/17 12:56:04 $
 * \version $Revision: 1.8 $
 *
 * $Log: MutApp.h,v $
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

#include "MutFrame.h"

// Declare a frame array as an hash table
WX_DECLARE_HASH_MAP( wxFrame *,      // type of the keys
                     wxFrame *,    // type of the values
                     wxPointerHash,     // hasher
                     wxPointerEqual,   // key equality predicate
                     FrameHash); // name of the class

// Define a new application
class MutApp : public wxApp
{
	friend class AppAbout;
 public:
    bool OnInit();
	void CmAbout (wxCommandEvent& event);
	void CmFileNew (wxCommandEvent& event);
	void CmFileOpen (wxCommandEvent& event);
	void CmRoutes (wxCommandEvent& event);
	void CmQuit (wxCommandEvent& event);
	MutFrame* CreateMainFrame(wxWindowID id = wxID_ANY);
	void RegisterFrame(wxFrame * f);
	void UnregisterFrame (wxFrame * f);
 private:
    wxLocale m_locale;
	DECLARE_EVENT_TABLE()
	
	FrameHash frames;
	bool quitting;
};


class AppAbout : public wxDialog
{
	public:
		AppAbout (wxWindow *parent=(wxWindow *) NULL, long style = 0);
};


DECLARE_APP(MutApp)

#endif  // __MUTAPP_H_INCLUDED__ 
