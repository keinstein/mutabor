/** \file               -*- C++ -*-
********************************************************************
* GUI Box data.
*
* Copyright:   (c) 2011 TU Dresden
*             Changes after 2011-11 (c) by the authors
* \author  Tobias Schlemmer <keinstein@users.berlios.de>
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
#include "src/wxGUI/Routing/NewBoxShape.h"
#include "wx/msgdlg.h"

namespace mutaborGUI {
	mutabor::Box BoxData::curBox(NULL);

	// don't initialize these classes before WX is intialized
//	BoxData::BoxVector BoxData::vector; 
//	BoxData BoxData::GmnBoxData;
//	BoxData BoxData::NoBoxData;
//	BoxData BoxData::NewBoxData;
	BoxData::BoxData(int id):BoxClass(id),
				 shapes(),
/*
  current_logic(),
  current_tonesystem(),
  current_key_tonesystem(0),
  current_key_logic(0),
*/
				 winattr()
	{		
	}

	void BoxData::set_routefile_id(int id) {
		BoxClass::set_routefile_id(id);
		if (box)
			id = box->id;

		switch (id) {
		case mutabor::NewBox:
		case mutabor::NoBox:
		case mutabor::GmnBox: 
			background_colour = wxNullColour;
			text_colour = *wxBLACK;
			break;
		default:
			int r = ((id & 0x01) << 7 ) | ((id & 0x08) << 3) | ((id & 0x40) >> 1) |
				((id & 0x200) >> 5) | ((id & 0x1000) >> 9) | ((id & 0x8000) >> 13) |
				((id & 0x40000) >> 17) | ((id & 0x200000) >> 21) ;
			r = r?r-1:0;
			int g = ((id & 0x02) << 6 ) | ((id & 0x10) << 2) | ((id & 0x80) >> 2) |
				((id & 0x400) >> 6) | ((id & 0x2000) >> 10) | ((id & 0x10000) >> 14) |
				((id & 0x80000) >> 18) | ((id & 0x400000) >> 22);
			g = g?g-1:0;
			int b = ((id & 0x04) << 5 ) | ((id & 0x20) << 1) | ((id & 0x100) >> 3) |
				((id & 0x800) >> 7) | ((id & 0x4000) >> 11) | ((id & 0x20000) >> 15) |
				((id & 0x100000) >> 19) | ((id & 0x800000) >> 23);
			b = b?b-1:0;
			DEBUGLOG2(other,_T("Box %d color %x,%x,%x"),id-1,r,g,b);
			if (r+b+g < 0x180) 
				text_colour = *wxWHITE;
			else
				text_colour = *wxBLACK;
			background_colour = wxColour(r,g,b);
		}
	}
		
#if 0
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
#endif


#if 0
	void BoxData::CloseRoute(mutabor::Box) {
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
#endif

	void BoxData::Save(mutabor::tree_storage & config) {
		mutabor::BoxClass::Save(config);
		config.Write(_T("KeyWindow"), 
			     winattr.want_key_window);
		config.Write(_T("ToneSystemWindow"), 
			     winattr.want_tonesystem_window);
		config.Write(_T("ActionsWindow"), 
			     winattr.want_actions_window);
	}

	void BoxData::Load(mutabor::tree_storage & config) {
		mutabor::BoxClass::Load(config);
		winattr.want_key_window = config.Read(_T("KeyWindow"), 
						       (long int)false) != 0l;
		winattr.want_tonesystem_window =
			config.Read(_T("ToneSystemWindow"),
				     (long int)false) != 0l;
		winattr.want_actions_window =
			config.Read(_T("ActionsWindow"), 
				     (long int)false) != 0l;
	}

#if 0
	bool BoxData::SaveAll(wxConfigBase * config) 
	{
		bool retval = true;
		for (size_t box = 0 ; box < vector.size() ; box++) {
			config->SetPath(wxString::Format(_T("%d"),(int)box));
			retval &= vector[box].Save(config);
			config->SetPath(_T(".."));
		}
		return retval;
	}

	bool BoxData::LoadAll(wxConfigBase * config) 
	{
		bool retval = true;
		for (size_t box = 0 ; box < vector.size() ; box++) {
			config->SetPath(wxString::Format(_T("%d"),(int)box));
			retval &= vector[box].Load(config);
			config->SetPath(_T(".."));
		}
		return retval;
	}
#endif

	void BoxData::runtime_error(bool iswarning, const char * message) {
		wxString str = wxString::FromUTF8(message);
		wxMessageBox(str, iswarning?_("Warning"):_("Error"), 
			     wxOK | (iswarning?wxICON_WARNING:wxICON_ERROR) );
	}


	MutBoxShape * GUIBoxFactory::DoCreateBoxShape(mutabor::Box & box,
						      wxWindow * parent) const {
		MutBoxShape * shape;	
		DEBUGLOG(routing,_T("Adding box shape for box %p (list of %d)"),
			 box.get(),(int)(ToGUIBase(box)->GetShapes().size()));
		
	
		if (box == NULL) 
			shape = new NewMutBoxShape(parent,wxID_ANY);
		else
			/** \todo implement ID sharing between the different
			    shapes of one common route */
			    
			shape = new MutBoxShape(parent, wxID_ANY,box);

		DEBUGLOG(routing,_T("Added box shape for box %p (list of %d)"),
			 box.get(),(int)(ToGUIBase(box)->GetShapes().size()));

		return shape;
	}


}
///\}
