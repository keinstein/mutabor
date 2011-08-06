/** \file               -*- C++ -*-
 ********************************************************************
 * Description
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/muwx/MutDocManager.h,v 1.1 2011/08/06 09:22:27 keinstein Exp $
 * Copyright:   (c) 2011 TU Dresden
 * \author  Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 
 * $Date: 2011/08/06 09:22:27 $
 * \version $Revision: 1.1 $
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
 * $Log: MutDocManager.h,v $
 * Revision 1.1  2011/08/06 09:22:27  keinstein
 * added mutabor document manager class
 *
 *
 *
 ********************************************************************
 * \addtogroup docview
 * \{
 ********************************************************************/

#ifndef MUTABOR_MUTDOCMANAGER_H
#define MUTABOR_MUTDOCMANAGER_H

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

// For compilers that support precompilation, includes "wx/wx.h".
#include "Defs.h"
#include <wx/wx.h>
#include "wx/event.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

namespace mutabor {
	class MutDocManager:public wxDocManager {
	public:
		/// Extend event processing to search the view's event table
		bool ProcessEvent(wxEvent& event);
	protected:
		/// Pass certain events to the Application.
		/** MutDocManager::ProcessEvent is called directly from MutApp event handlers.
		    this leads to endless loops. To prevent these loops, we must be very careful,
		    which kind of events get passed back.
	    
		    Probably no events should be propagatetd.
		*/
		virtual bool TryParent(wxEvent& event);	
	};
}

#endif

///\}
