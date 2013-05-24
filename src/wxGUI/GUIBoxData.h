/** \file               -*- C++ -*-
 ********************************************************************
 * GUI Box data.
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/src/wxGUI/GUIBoxData.h,v 1.9 2011/11/02 14:31:58 keinstein Exp $
 * Copyright:   (c) 2011 TU Dresden
 * \author  Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 
 * $Date: 2011/11/02 14:31:58 $
 * \version $Revision: 1.9 $
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

#if (!defined(MUWX_GUIBOXDATA_H) && !defined(PRECOMPILE)) \
	|| (!defined(MUWX_GUIBOXDATA_H_PRECOMPILED))
#ifndef PRECOMPILE
#define MUWX_GUIBOXDATA_H
#endif

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

#include "src/kernel/Defs.h"
#include "src/kernel/box.h"
#include "src/kernel/Execute.h"
#include "src/wxGUI/Routing/RouteLists.h"


#ifndef MUWX_GUIBOXDATA_H_PRECOMPILED
#define MUWX_GUIBOXDATA_H_PRECOMPILED

#include <vector>

// system headers change not so often
#include "wx/config.h"

namespace mutaborGUI {
	class MutChild;
	class MutLogicWnd;
	extern size_t curBox;

	class BoxData {
	protected:
		struct WinAttr {
			WinAttr():
				key_window(NULL),
				tonesystem_window(NULL),
				actions_window(NULL),
				logic_window(NULL),
				want_key_window(false),
				want_tonesystem_window(false),
				want_actions_window(false)
				{}

			MutChild * key_window;
			MutChild * tonesystem_window;
			MutChild * actions_window;
			MutLogicWnd * logic_window;

			bool want_key_window:1;
			bool want_tonesystem_window:1;
			bool want_actions_window:1;
		};
	public:

		class NoSuchBoxException {
		public:
			int boxnumber ;
			NoSuchBoxException(int i):boxnumber(i) {}
		};

		BoxData();

		int GetId() {
			if (box) return box->id;
			if (this == &NewBoxData) 
				return NewBox;
			if (this == &GmnBoxData)
				return GmnBox;
			return NoBox;
		}

		void reset();

		MutBoxShape * GetBoxShape(wxWindow * parent);

		void KeyboardAnalyse(int taste, char isLogic) {
			if (!box) return;
			::KeyboardAnalyse(box,taste,isLogic);
		}

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

		bool WantKeyWindow() const { 
			return winattr.want_key_window; 
		}
		void SetKeyWindow(MutChild * w, bool reset = false) { 
			winattr.key_window = w; 
			if (w || reset)
				WantKeyWindow(w != NULL);
		}
		MutChild * GetKeyWindow() const {
			return winattr.key_window; 
		}
		bool WantTonesystemWindow() const { 
			return winattr.want_tonesystem_window; 
		}
		void SetTonesystemWindow(MutChild * w, bool reset = false) { 
			winattr.tonesystem_window = w; 
			if (w || reset)
				WantTonesystemWindow(w != NULL);
		}
		MutChild * GetTonesystemWindow() const { 
			return winattr.tonesystem_window; 
		}
		bool WantActionsWindow() const { 
			return winattr.want_actions_window; 
		}
		void SetActionsWindow(MutChild * w, bool reset = false) { 
			winattr.actions_window = w; 
			if (w || reset)
				WantActionsWindow(w != NULL);
		}
		MutChild * GetActionsWindow() const { 
			return winattr.actions_window; 
		}

		void WantKeyWindow (bool yesno) { 
			winattr.want_key_window = yesno; 
		}
		void WantTonesystemWindow (bool yesno) { 
			winattr.want_tonesystem_window = yesno; 
		}
		void WantActionsWindow (bool yesno) { 
			winattr.want_actions_window = yesno; 
		}

		bool ToggleKeyWindow () {
			return winattr.want_key_window = !winattr.want_key_window;
		}
		
		bool ToggleTonesystemWindow () {
			return winattr.want_tonesystem_window 
				= !winattr.want_tonesystem_window;
		}
		
		bool ToggleActionsWindow () {
			return winattr.want_actions_window 
				= !winattr.want_actions_window;
		}
		
		void SetLogicWindow(MutLogicWnd * w) { 
			winattr.logic_window = w; 
		}

		MutLogicWnd * GetLogicWindow() const { 
			return winattr.logic_window; 
		}

		const MutBoxShapeList & GetBoxShapes() const {
			return shapes;
		}

		void Add(MutBoxShape * shape);
		bool Remove(MutBoxShape * shape);
		
		void Attatch(MutBoxShape * shape);
		bool Detatch(MutBoxShape * shape);
		bool Delete(MutBoxShape * shape);
		
		static BoxData & GetBox(int nr) 
		{ 
			if (nr < Box0) {
				switch(nr) {
				case NewBox: 
					return NewBoxData;
					break;
				case NoBox:
					return NoBoxData;
					break;
				case GmnBox:
					return GmnBoxData;
					break;
				case Box0:
				default:
					UNREACHABLECT(BoxData);
					throw NoSuchBoxException(nr);
				}
			}
			if (nr >= vector.size()) {
				UNREACHABLECT(BoxData);
				throw NoSuchBoxException(nr);
			}
			return vector[nr]; 
		}

		static void InitializeBoxes(size_t count = MAX_BOX) {
			vector.resize(count);
			for (size_t i = 0 ; i < vector.size() ; i++) {
				vector[i].box = &(mut_box[i]);
				mut_box[i].userdata = &(vector[i]);
			}
		}


		/// Check whether a closed route means closing a box
		/** this function calls CloseBox(int boxid) in case 
		    the box boxid has no routes attatched anymore */
		static void CloseRoute(int boxid);
		/// Close all windows associated to the box boxid
		static void CloseBox(int boxid);
		
		/// Check whether a new route means new a box
		/** this function is the counterpart to CloseRoute(int).
		 */
		static void OpenRoute(int boxid);
		/// Open all wanted windows associated to the box boxid
		static void OpenBox(int boxid);

		/// Check whether a new box id on a route means new a box
		/** this function is the counterpart to CloseRoute(int).
		 */
		static void ReOpenRoute(int old_boxid, int new_boxid);
		/// Reopen all wanted windows associated to the box boxid
		static void ReOpenBox(int old_boxid, int new_boxid);

		bool Save(wxConfigBase * config);
		bool Load(wxConfigBase * config);

		static bool SaveAll(wxConfigBase * config);
		static bool LoadAll(wxConfigBase * config);


		mutabor_box_type * GetNonGUIBox() { return box; }
	protected: 
		/** \todo curent_logic and current_tonesystem are set
		 *  but unused as well as current_key_tonesystem and 
		 *  current_key_logic
		 */
		mutabor_box_type * box;
		MutBoxShapeList shapes;
		wxString current_logic;
		wxString current_tonesystem;
		int current_key_tonesystem; // 0
		int current_key_logic; // 1

		typedef std::vector<BoxData> BoxVector;
		static BoxVector vector;
		static BoxData GmnBoxData;
		static BoxData NoBoxData;
		static BoxData NewBoxData;

		WinAttr winattr;

	};

	inline BoxData & GetCurrentBox() {
		return BoxData::GetBox(curBox);
	}
}
 
#endif
#endif

///\}
