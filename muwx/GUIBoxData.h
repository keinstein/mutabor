/** \file               -*- C++ -*-
 ********************************************************************
 * GUI Box data.
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/muwx/GUIBoxData.h,v 1.3 2011/09/05 11:30:07 keinstein Exp $
 * Copyright:   (c) 2011 TU Dresden
 * \author  Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 
 * $Date: 2011/09/05 11:30:07 $
 * \version $Revision: 1.3 $
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
 * $Log: GUIBoxData.h,v $
 * Revision 1.3  2011/09/05 11:30:07  keinstein
 * Some code cleanups moving some global box arrays into class mutaborGUI::BoxData
 * Restore perspective on logic start
 *
 * Revision 1.2  2011-09-05 06:56:44  keinstein
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

#ifndef MUWX_GUIBOXDATA_H
#define MUWX_GUIBOXDATA_H

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

// For compilers that support precompilation, includes "wx/wx.h".
#include "Defs.h"
#include <wx/wxprec.h>

#ifdef __BORLANDC__
    #pragma hdrstop
#endif


namespace mutaborGUI {
	extern int curBox;

	class BoxData {
	public:
		BoxData();

		void reset();
		/// Sets the name of the currently active logic
		/** \param s wxString name of the logic
		*/
		void SetLogic(const wxString & s) { current_logic = s; }
		/// Returns the name of the currently active logic
		/** \return wxString name of the logic
		 */
		wxString GetLogic() const { return current_logic; }
		
		/// Sets the name of the currently active tone system
		/** \param s wxString name of the tone system
		*/
		void SetTonesystem(const wxString & s) { current_tonesystem = s; }
		/// Returns the name of the currently active tone system
		/** \return wxString name of the tone system
		 */
		wxString GetTonesystem() const { return current_tonesystem; }

		/// Sets the key of the currently active tone system
		/** \param nr int number of the key
		*/
		void SetKeyTonesystem(int nr) { current_key_tonesystem = nr; }
		/// Returns the key of the currently active tone system
		/** \return int number of the key
		 */
		int GetKeyTonesystem() const { return current_key_tonesystem; }

		/// Sets the key of the currently active logic
		/** \param nr int number of the key
		*/
		void SetKeyLogic(int nr) { current_key_logic = nr; }
		/// Returns the key of the currently active tone system
		/** \return int key of the tone system
		 */
		int GetKeyLogic() const { return current_key_logic; }

		bool WantKeyWindow() const { return want_key_window; }
		bool WantTonesystemWindow() const { return want_tonesystem_window; }
		bool WantActionsWindow() const { return want_actions_window; }

		void WantKeyWindow (bool yesno) { want_key_window = yesno; }
		void WantTonesystemWindow (bool yesno) 
			{ 
				want_tonesystem_window = yesno; 
			}
		void WantActionsWindow (bool yesno) { want_actions_window = yesno; }

		bool ToggleKeyWindow () {
			bool retval = want_key_window;
			want_key_window = !want_key_window;
		}
		
		bool ToggleTonesystemWindow () {
			bool retval = want_tonesystem_window;
			want_tonesystem_window = !want_tonesystem_window;
		}
		
		bool ToggleActionsWindow () {
			bool retval = want_actions_window;
			want_actions_window = !want_actions_window;
		}
		
		static BoxData & GetBox(size_t nr) 
		{ 
			return vector[nr]; 
		}

		bool Save(wxConfigBase * config);
		bool Load(wxConfigBase * config);

		static bool SaveAll(wxConfigBase * config);
		static bool LoadAll(wxConfigBase * config);

	protected: 
		/** \todo curent_logic and current_tonesystem are set
		 *  but unused as well as current_key_tonesystem and 
		 *  current_key_logic
		 */
		wxString current_logic;
		wxString current_tonesystem;
		int current_key_tonesystem; // 0
		int current_key_logic; // 1
		typedef std::vector<BoxData> BoxVector;

		static BoxVector vector;

		bool want_key_window:1;
		bool want_tonesystem_window:1;
		bool want_actions_window:1;
	};

	inline BoxData & GetCurrentBox() {
		return BoxData::GetBox(curBox);
	}

}
 
#endif
///\}
