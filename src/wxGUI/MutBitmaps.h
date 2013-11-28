/** \file     -*- C++ -*-
 ********************************************************************
 * Mutabor Bitmaps. We save Bitmaps in global variables as they can be used in several contexts.
 * so their data can be shared if the underlying framework supports it.
 *
 * Copyright:   (c) TU Dresden
 * \author 
 * Tobias Schlemmer <keinstein@users.berlios.de>
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
 * \addtogroup GUI
 * \{
 ********************************************************************/

#if (!defined(MUWX_MUT_BITMAPS_H) && !defined(PRECOMPILE)) \
	|| (!defined(MUWX_MUT_BITMAPS_H_PRECOMPILED))
#ifndef PRECOMPILE
#define MUWX_MUT_BITMAPS_H
#endif

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

#include "src/kernel/Defs.h"

#ifndef MUWX_MUT_BITMAPS_H_PRECOMPILED
#define MUWX_MUT_BITMAPS_H_PRECOMPILED

#include "wx/bitmap.h"

namespace mutaborGUI {

/// Toolbar bitmaps
/** This class provedes the bitmaps for the toolbar.
 */

	class MutToolBarBitmaps {
	private:
		static bool initialized;
	public:
		static bool Init();
		static wxBitmap EmptyBitmap;
		static wxBitmap New;
		static wxBitmap Open;
		static wxBitmap Save;
		static wxBitmap SaveAs;
		static wxBitmap Print;
		static wxBitmap LogicActivate;
		static wxBitmap LogicStop;
		static wxBitmap LogicPanic;
		static wxBitmap Copy;
		static wxBitmap Cut;
		static wxBitmap Paste;
		static wxBitmap Undo;
		static wxBitmap Redo;
		static wxBitmap GoUp;
		static wxBitmap GoDown;
		static wxBitmap RouteLoad;
		static wxBitmap RouteSave;
		static wxBitmap IndevsPlay;
		static wxBitmap IndevsStop;
		static wxBitmap IndevsPause;
		static wxBitmap About;
	};

	class StatusBarBitmaps {
	private:
		static bool initialized;
		static bool DoInit();
	public:
		static bool Init() {
			if (!initialized) return DoInit();
			else return true;
		}

		static wxBitmap Play;
		static wxBitmap Stop;
		static wxBitmap Pause;
		static wxBitmap Active;
	};
}

#endif // precompile
#endif // header loaded

/** \} */
