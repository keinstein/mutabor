/** \file               -*- C++ -*-
 ********************************************************************
 * GUI Box data.
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/src/wxGUI/GUIBoxData.cpp,v 1.7 2011/11/02 14:31:58 keinstein Exp $
 * Copyright:   (c) 2011 TU Dresden
 * \author  Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 
 * $Date: 2011/11/02 14:31:58 $
 * \version $Revision: 1.7 $
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
 * Revision 1.7  2011/11/02 14:31:58  keinstein
 * fix some errors crashing Mutabor on Windows
 *
 * Revision 1.6  2011-09-30 18:07:04  keinstein
 * * make compile on windows
 * * s/wxASSERT/mutASSERT/g to get assert handler completely removed
 * * add ax_boost_base for boost detection
 *
 * Revision 1.5  2011-09-30 09:10:24  keinstein
 * Further improvements in the routing system.
 *
 * Revision 1.4  2011-09-27 20:13:22  keinstein
 * * Reworked route editing backend
 * * rewireing is done by RouteClass/GUIRoute now
 * * other classes forward most requests to this pair
 * * many bugfixes
 * * Version change: We are reaching beta phase now
 *
 * Revision 1.3  2011-09-07 13:06:50  keinstein
 * Get rid of WinAttr and Fix window opening and closing
 *
 * Revision 1.2  2011-09-05 11:30:07  keinstein
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
#include "src/kernel/routing/Route.h"
#include "src/kernel/routing/Route-inlines.h"
#include "src/wxGUI/MutFrame.h"

namespace mutaborGUI {
	size_t curBox = 0;

	// don't initialize these classes before WX is intialized
	BoxData::BoxVector BoxData::vector; 
	BoxData BoxData::GmnBoxData;
	BoxData BoxData::NoBoxData;
	BoxData BoxData::NewBoxData;
	BoxData::BoxData():box(NULL),
			   shapes(),
			   current_logic(),
			   current_tonesystem(),
			   current_key_tonesystem(0),
			   current_key_logic(0),
			   winattr()
	{		
	}

	void BoxData::reset() 
	{
		current_logic = _("(INITIAL)");
		current_tonesystem = _T("0");
		current_key_tonesystem = current_key_logic = 0;
		mutASSERT(!winattr.key_window);
		mutASSERT(!winattr.tonesystem_window);
		mutASSERT(!winattr.actions_window);
		mutASSERT(!winattr.logic_window);
	}


	void BoxData::CloseRoute(int boxid) {
		// if logic is off we are not resposible
		if (!LogicOn) return;
		// check whether the windows should be closed
		const mutabor::routeListType & list 
			= mutabor::RouteClass::GetRouteList();
		for (mutabor::routeListType::const_iterator i
			     = list.begin();
		     i != list.end(); i++) {
			if ((*i)->GetBox() ==  boxid) return;
		}
		CloseBox(boxid);
	}

	void BoxData::CloseBox(int boxid) {
		if (!(MIN_BOX <= boxid && boxid < MAX_BOX)) {
			UNREACHABLECT(BoxData);
			return;
		}
		
		if (boxid < 0) return;

		int tmp = minimal_box_used;
		if (boxid == tmp) {
			if (mut_box[tmp].next_used) {
				minimal_box_used = mut_box[tmp].next_used;
			}
		} else {
			if (mut_box[tmp].next_used != boxid) {
				do {
					tmp = mut_box[tmp].next_used;
					mutASSERT(tmp);
				} while (tmp && mut_box[tmp].next_used != boxid) ;
				if (!tmp) {
					UNREACHABLECT(BoxData);
					return;
				}
			}
			// box 0 is valid, here
			mut_box[tmp].next_used = mut_box[boxid].next_used;
		}
		mut_box[boxid].used = 0;
		mut_box[boxid].next_used = 0;
		MutFrame::BoxWindowsClose(boxid,true);
	}

	
	void BoxData::OpenRoute(int boxid) {
		// if logic is off we are not resposible
		if (!LogicOn) return;
		// in contrast to CloseRoute we do not have to precheck the routes
		OpenBox(boxid);
	}
	void BoxData::OpenBox(int boxid) {
		if (!(MIN_BOX <= boxid && boxid < MAX_BOX)) {
			UNREACHABLECT(BoxData);
			return;
		}
		
		size_t box = boxid;
		if (boxid < 0) return;
		if (!(mut_box[minimal_box_used].used)) {
			mutASSERT(!minimal_box_used);
			minimal_box_used=box;
			mut_box[box].next_used = 0;
		} else if (box < minimal_box_used) {
			mut_box[box].next_used = minimal_box_used;
			minimal_box_used = box;
		} else {
			size_t tmp = minimal_box_used;
			if (box == tmp) return;
			while (mut_box[tmp].next_used 
			       && mut_box[tmp].next_used < boxid) {
				tmp = mut_box[tmp].next_used;
				if (tmp == box) return;
			}
			if (mut_box[tmp].next_used == boxid) return;
			mut_box[box].next_used = mut_box[tmp].next_used;
			mut_box[tmp].next_used = box;
			
		}
		mut_box[box].used = 1;
		MutFrame::BoxWindowsOpen(box,true);
	}

	void BoxData::ReOpenRoute(int old_boxid, int new_boxid) {
		// if logic is off we are not resposible
		if (!LogicOn || old_boxid == new_boxid) return;
		// in contrast to CloseRoute we do not have to precheck the routes
		ReOpenBox(old_boxid, new_boxid);
	}
	void BoxData::ReOpenBox(int old_boxid, int new_boxid) {
		/// \todo if possible, let windows as they are
		CloseRoute(old_boxid);
		OpenRoute(new_boxid);
	}

	bool BoxData::Save(wxConfigBase * config) {
		config->Write(_T("KeyWindow"), 
			      winattr.want_key_window);
		config->Write(_T("ToneSystemWindow"), 
			      winattr.want_tonesystem_window);
		config->Write(_T("ActionsWindow"), 
			      winattr.want_actions_window);
		return true;
	}

	bool BoxData::Load(wxConfigBase * config) {
		winattr.want_key_window = config->Read(_T("KeyWindow"), 
						       (long int)false) != 0l;
		winattr.want_tonesystem_window =
			config->Read(_T("ToneSystemWindow"),
				     (long int)false) != 0l;
		winattr.want_actions_window =
			config->Read(_T("ActionsWindow"), 
				     (long int)false) != 0l;
		return true;
	}

	bool BoxData::SaveAll(wxConfigBase * config) 
	{
		bool retval = true;
		for (size_t box = 0 ; box < vector.size() ; box++) {
			config->SetPath(wxString::Format(_T("%d"),box));
			retval &= vector[box].Save(config);
			config->SetPath(_T(".."));
		}
		return retval;
	}

	bool BoxData::LoadAll(wxConfigBase * config) 
	{
		bool retval = true;
		for (size_t box = 0 ; box < vector.size() ; box++) {
			config->SetPath(wxString::Format(_T("%d"),box));
			retval &= vector[box].Load(config);
			config->SetPath(_T(".."));
		}
		return retval;
	}

}
///\}
