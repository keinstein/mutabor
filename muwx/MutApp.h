/** \file
 ***********************************************************************
 * Mutabor Application.
 *
 * $Id: MutApp.h,v 1.5 2007/10/05 12:39:38 keinstein Exp $
 * \author R. Krauße <krausze@users.berlios.de>
 * \date $Date: 2007/10/05 12:39:38 $
 * \version $Revision: 1.5 $
 *
 * $Log: MutApp.h,v $
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

// Define a new application
class MutApp : public wxApp
{
 public:
    bool OnInit();
	void OnAbout (wxCommandEvent& event);
	MutFrame* CreateMainFrame();
 private:
    wxLocale m_locale;
	DECLARE_EVENT_TABLE()
};

DECLARE_APP(MutApp)

#endif  // __MUTAPP_H_INCLUDED__ 
