/** \file     -*- C++ -*-
 ********************************************************************
 * Mutabor Bitmaps. We save Bitmaps in global variables as they can be used in several contexts.
 * so their data can be shared if the underlying framework supports it.
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/src/wxGUI/MutBitmaps.h,v 1.3 2011/11/02 14:31:58 keinstein Exp $
 * Copyright:   (c) TU Dresden
 * \author 
 * Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 2011/02/13
 * $Date: 2011/11/02 14:31:58 $
 * \version $Revision: 1.3 $
 * \license GPL
 *
 * $Log: MutBitmaps.h,v $
 * Revision 1.3  2011/11/02 14:31:58  keinstein
 * fix some errors crashing Mutabor on Windows
 *
 * Revision 1.2  2011-09-27 20:13:23  keinstein
 * * Reworked route editing backend
 * * rewireing is done by RouteClass/GUIRoute now
 * * other classes forward most requests to this pair
 * * many bugfixes
 * * Version change: We are reaching beta phase now
 *
 * Revision 1.1  2011-02-16 07:01:33  keinstein
 * added files for global bitmap storage
 *
 *
 * \addtogroup src/wxGUI
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
