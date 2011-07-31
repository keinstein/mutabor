/** \file 
 ********************************************************************
 * Document/View Document class for Mutabor source files.
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/muwx/MutDocument.h,v 1.1 2011/07/31 12:40:42 keinstein Exp $
 * Copyright:   (c) 2011 TU Dresden
 * \author  Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 
 * $Date: 2011/07/31 12:40:42 $
 * \version $Revision: 1.1 $
 * \license GPL
 *
 * $Log: MutDocument.h,v $
 * Revision 1.1  2011/07/31 12:40:42  keinstein
 * Added classes and functions for Document/View support
 *
 *
 *
 ********************************************************************
 * \addtogroup templates
 * \{
 ********************************************************************/
// availlable groups: GUI, route, kernel, muwx, debug

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

#ifndef MUTABOR_MUT_DOCUMENT_H
#define MUTABOR_MUT_DOCUMENT_H

// For compilers that support precompilation, includes "wx/wx.h".
#include "Defs.h"
#include <wx/wxprec.h>

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#include <wx/wx.h>
#include <wx/docview.h>

namespace mutaborGUI {

	class MutDocument : public wxDocument
	{
		DECLARE_DYNAMIC_CLASS(MutDocument)
			public:
		MutDocument();
		~MutDocument();

		// save and load methods go here
#if wxUSE_STD_IOSTREAM
		virtual wxSTD ostream& SaveObject(wxSTD ostream& stream);
		virtual wxSTD istream& LoadObject(wxSTD istream& stream);
#else
		virtual wxOutputStream& SaveObject(wxOutputStream& stream);
		virtual wxInputStream& LoadObject(wxInputStream& stream);
#endif

		virtual bool OnCreate(const wxString& path, long flags);
		virtual void Modify(bool modify);
		// event handlers go here
		void CmdNewView(wxCommandEvent& event);
		void OnNewViewUpdateUI(wxUpdateUIEvent& event);
		void CmdUpdateAllViews(wxCommandEvent& event);
	private:
		DECLARE_EVENT_TABLE()
			
        };

}

#endif

///\}
