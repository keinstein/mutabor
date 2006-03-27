/** \file
 ***********************************************************************
 * Mutabor Application.
 *
 * $Id: MutApp.h,v 1.4 2006/03/27 17:19:14 keinstein Exp $
 * \author R. Krauße <krausze@users.berlios.de>
 * \date $Date: 2006/03/27 17:19:14 $
 * \version $Revision: 1.4 $
 *
 * $Log: MutApp.h,v $
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



// Define a new application
class MutApp : public wxApp
{
 public:
    bool OnInit();
 private:
    wxLocale m_locale;
};

#endif  // __MUTAPP_H_INCLUDED__ 
