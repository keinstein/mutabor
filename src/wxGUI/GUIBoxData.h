/** \file               -*- C++ -*-
 ********************************************************************
 * GUI Box data.
 *
 * Copyright:   (c) 2011 TU Dresden
 * Changes after 2011-11 (c) Tobias Schlemmer
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

#if (!defined(MUWX_GUIBOXDATA_H) && !defined(PRECOMPILE)) \
	|| (!defined(MUWX_GUIBOXDATA_H_PRECOMPILED))
#ifndef PRECOMPILE
#define MUWX_GUIBOXDATA_H
#endif

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

#include "src/kernel/Defs.h"
#include "src/kernel/treestorage.h"
#include "src/kernel/routing/Box.h"
#include "src/wxGUI/Routing/RouteLists.h"
#include "src/wxGUI/MutEditFile.h"

#ifndef MUWX_GUIBOXDATA_H_PRECOMPILED
#define MUWX_GUIBOXDATA_H_PRECOMPILED

#include <vector>
#include <stdexcept>

// system headers change not so often
#include "wx/config.h"

namespace mutaborGUI {
	class MutChild;
	class MutLogicWnd;

	class BoxData: public mutabor::BoxClass {
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
		typedef mutabor::BoxClass basetype;

		class NoSuchBoxException: std::invalid_argument {
		public:
			int boxnumber ;
			NoSuchBoxException(int i):invalid_argument("No such box."),boxnumber(i) {}
		};

		const MutBoxShape * GetShape(wxWindow * parent) const;
		MutBoxShape * GetShape(wxWindow * parent);


		virtual void set_routefile_id(int id);


		MutEditFile * GetEditor() { return editor; }
		void SetEditor(MutEditFile * edit) { editor = edit; }

		const wxColour & GetBackgroundColour() const {
			return background_colour;
		}

		const wxColour & GetTextColour() const {
			return text_colour;
		}

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

		const MutBoxShapeList & GetShapes() const {
			return shapes;
		}

		/** 
		 * Move the associated box shape to a given position. 
		 * This function handles the GUI part of MoveInList().
		 * 
		 * \param newpos New position of the shape in the
		 *  list. This parameter should reflect the actual
		 *  position of the box in the (non GUI) box list.
		 */
		virtual	void MoveToInList(int newpos);

		virtual	int MoveInList(int count);


		void Add(MutBoxShape * shape);
		bool Remove(MutBoxShape * shape);

		/** 
		 * Destroy the current object.  
		 * This function is
		 * called when an object shall be deleted. It clears
		 * up all references to itself so that it will be deleted if it is not needed anymore.
		 * 
		 * This functions detatches the device from all routes and calls DoDestroy() afterwards. 
		 * Finally the Device is going to removed from the device list.
		 */
		virtual void Destroy();

		void Save(mutabor::tree_storage & config);
		void Load(mutabor::tree_storage &  config);



		static mutabor::Box GetCurrentBox() {
			return curBox;
		}
		static void SetCurrentBox(mutabor::Box b) {
			curBox = b;
		}


		
		/// do the work for opening a box
		virtual bool DoOpen();
		/// do the work for closing a box
		virtual void DoClose();

		void Activate ();

//		mutabor_box_type * GetNonGUIBox() { return box; }
	protected: 
		/** \todo curent_logic and current_tonesystem are set
		 *  but unused as well as current_key_tonesystem and 
		 *  current_key_logic
		 */
		MutBoxShapeList shapes;
		MutEditFile * editor;
		wxColour text_colour;
		wxColour background_colour;

		friend class GUIBoxFactory;

		static mutabor::Box curBox;

		BoxData(int id);

		void runtime_error(mutabor::error_type type, const char * message);
		

/*
		mutabor_box_type * box;
		typedef std::vector<BoxData> BoxVector;
		static BoxVector vector;
		static BoxData GmnBoxData;
		static BoxData NoBoxData;
		static BoxData NewBoxData;
*/

		WinAttr winattr;

	};

	inline BoxData * ToGUIBase(mutabor::BoxClass * b) {
		mutASSERT(!b || dynamic_cast<BoxData *>(b));
		return static_cast<BoxData *>(b);
	}
	inline BoxData * ToGUIBase(mutabor::Box & b) {
		return ToGUIBase(b.get());
	}
	inline const BoxData * ToGUIBase(const mutabor::BoxClass * b) {
		mutASSERT(!b || dynamic_cast<const BoxData *>(b));
		return static_cast<const BoxData *>(b);
	}
	inline const BoxData * ToGUIBase(const mutabor::Box & b) {
		return ToGUIBase(b.get());
	}

	class GUIBoxFactory:public mutabor::BoxFactory {
	public:
		GUIBoxFactory(size_t id = 0) : BoxFactory(id) {}
		virtual ~GUIBoxFactory() {}

		static MutBoxShape * CreateBoxShape(mutabor::Box box,
						    wxWindow * parent) {
			int type = box->GetType();
			if (type < 0) type = 0;
			mutASSERT(type >= 0);
			if (factories.size() <=(size_t) type) {
				boost::throw_exception( FactoryNotFound(type));
				UNREACHABLECT(BoxFactory);
				return NULL;
			}
			if (!factories[type]) 
				boost::throw_exception( FactoryNotFound(type));
			BoxFactory * factory = factories[type];
			mutASSERT(dynamic_cast<GUIBoxFactory *> (factory));
			return (static_cast<GUIBoxFactory *>(factory))->
				DoCreateBoxShape(box,parent);
		}
	protected:
		virtual size_t GetType() const { return 0; }

		virtual mutabor::BoxClass * DoCreateBox (int id = -1) const {
			return new BoxData(id);
		}
			
		virtual MutBoxShape * DoCreateBoxShape(mutabor::Box & box,
						       wxWindow * parent) const;

		
		/// load the routes from a tree based configuration
		/** \param config conifiguration to be read from
		 */
		virtual void DoLoadBoxes(mutabor::tree_storage & config) const {
		}

		/// write the routes to the configuration
		/** \param config configuration to be written to
		 */ 
		virtual void DoSaveBoxes(mutabor::tree_storage & config) const {
		}
	};

	//	void InitGUIBoxFactories();

	inline mutabor::Box GetCurrentBox() {
		return BoxData::GetCurrentBox();
	}
	inline void SetCurrentBox(mutabor::Box b) {
		BoxData::SetCurrentBox(b);
	}

}
 
#endif
#endif

///\}
