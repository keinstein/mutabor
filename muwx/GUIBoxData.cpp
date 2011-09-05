/** \file               -*- C++ -*-
 ********************************************************************
 * GUI Box data.
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/muwx/GUIBoxData.cpp,v 1.2 2011/09/05 11:30:07 keinstein Exp $
 * Copyright:   (c) 2011 TU Dresden
 * \author  Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 
 * $Date: 2011/09/05 11:30:07 $
 * \version $Revision: 1.2 $
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
 * $Log: GUIBoxData.cpp,v $
 * Revision 1.2  2011/09/05 11:30:07  keinstein
 * Some code cleanups moving some global box arrays into class mutaborGUI::BoxData
 * Restore perspective on logic start
 *
 * Revision 1.1  2011-09-05 06:56:44  keinstein
 * Added GUIBoxData.cpp
 *
 * Revision 1.1  2011-09-05 06:42:47  keinstein
 * Added GUIBoxData.h
 *
 *
 *
 ********************************************************************
 * \addtogroup GUI
 * \{
 ********************************************************************/

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

#include "GUIBoxData.h"

namespace mutaborGUI {
	int curBox = 0;

	BoxData::BoxVector BoxData::vector(MAX_BOX);
	BoxData::BoxData():current_logic(),
			   current_tonesystem(),
			   current_key_tonesystem(0),
			   current_key_logic(0),
			   want_key_window(false),
			   want_tonesystem_window(false),
			   want_actions_window(false)	
	{		
	}

	void BoxData::reset() 
	{
		current_logic = _("(INITIAL)");
		current_tonesystem = _T("0");
		current_key_tonesystem = current_key_logic = 0;
	}


	bool BoxData::Save(wxConfigBase * config) {
		config->Write(_T("KeyWindow"), want_key_window);
		config->Write(_T("ToneSystemWindow"), want_tonesystem_window);
		config->Write(_T("ActionsWindow"), want_actions_window);
	}

	bool BoxData::Load(wxConfigBase * config) {
		want_key_window = config->Read(_T("KeyWindow"), 
					       (long int)false);
		want_tonesystem_window =
			config->Read(_T("ToneSystemWindow"),
				     (long int)false);
		want_actions_window =
			config->Read(_T("ActionsWindow"), 
				     (long int)false);
	}

	bool BoxData::SaveAll(wxConfigBase * config) 
	{
		for (size_t box = 0 ; box < vector.size() ; box++) {
			config->SetPath(wxString::Format(_T("%d"),box));
			vector[box].Save(config);
			config->SetPath(_T(".."));
		}
	}

	bool BoxData::LoadAll(wxConfigBase * config) 
	{
		for (size_t box = 0 ; box < vector.size() ; box++) {
			config->SetPath(wxString::Format(_T("%d"),box));
			vector[box].Load(config);
			config->SetPath(_T(".."));
		}
	}

}
///\}
