/** \file 
 ********************************************************************
 * Mutabor Bitmaps. We save Bitmaps in global variables as they can be used in several contexts.
 * so their data can be shared if the underlying framework supports it.
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/muwx/MutBitmaps.h,v 1.1 2011/02/16 07:01:33 keinstein Exp $
 * Copyright:   (c) TU Dresden
 * \author 
 * Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 2011/02/13
 * $Date: 2011/02/16 07:01:33 $
 * \version $Revision: 1.1 $
 * \license GPL
 *
 * $Log: MutBitmaps.h,v $
 * Revision 1.1  2011/02/16 07:01:33  keinstein
 * added files for global bitmap storage
 *
 *
 * \addtogroup muwx
 * \{
 ********************************************************************/

#ifndef MUTBITMAPS_H
#define MUTBITMAPS_H

#include "Global.h"
#include "wx/bitmap.h"

/// Toolbar bitmaps
/** This class provedes the bitmaps for the toolbar.
 */

class MutToolBarBitmaps {
private:
	static bool initialized;
public:
	static bool Init();
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
        static wxBitmap RouteLoad;
        static wxBitmap RouteSave;
        static wxBitmap IndevsPlay;
        static wxBitmap IndevsStop;
        static wxBitmap IndevsPause;
        static wxBitmap About;
};

/** \} */
#endif
