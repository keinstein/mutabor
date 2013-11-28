/** \file     -*- C++ -*-
 ********************************************************************
 * Configuration dialog
 *
 * Copyright:   (c) 2008 TU Dresden
 * \author Tobias Schlemmer <keinstein@users.berlios.de>
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

#if (!defined(MUWX_MUTCONFDLG_H) && !defined(PRECOMPILE)) \
	|| (!defined(MUWX_MUTCONFDLG_H_PRECOMPILED))
#ifndef PRECOMPILE
#define MUWX_MUTCONFDLG_H
#endif

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

#include "src/kernel/Defs.h"
#include "src/wxGUI/resourceload.h"
#include "src/wxGUI/MutFrame.h"
#include "src/wxGUI/MutApp.h"

#ifndef MUWX_MUTCONFDLG_H_PRECOMPILED
#define MUWX_MUTCONFDLG_H_PRECOMPILED

#include "wx/statline.h"
#include "wx/filepicker.h"
#include "wx/html/htmlwin.h"
#include "wx/html/helpctrl.h"
#include "wx/valgen.h"

namespace mutaborGUI {

	class MutConfigDialog : public ConfigDlg {
	public:
	MutConfigDialog(wxWindow * parent = NULL) : ConfigDlg(parent) {

			ToneSystem->SetValidator(wxGenericValidator((int *) &asTS));
			SaveEditor->SetValidator(wxGenericValidator(&mutaborGUI::SaveEditor));
			ColorBars->SetValidator(wxGenericValidator(&UseColorBars));

#if 0
#ifndef __WXMSW__
			wxSizer * buttonSizer = this->wxID_OK->GetParent()->GetSizer();
			buttonSizer->Add(new wxContextHelpButton(this), 0, wxALIGN_CENTER|wxALL, 5);
#endif
#endif    

		}

		~MutConfigDialog() {}

		void CmHelp(wxCommandEvent& event) {
			TRACEC;
			HelpController->Display(_("The setup dialog"));
			event.Skip();
		}
	private:
		DECLARE_EVENT_TABLE()
	};

}
#endif /* precompile */
#endif /* MUTCONFDLG_H */

///\}
