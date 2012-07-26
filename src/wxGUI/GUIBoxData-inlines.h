/** \file               -*- C++ -*-
 ********************************************************************
 * GUI Box data. Inline functions that must not be defined at class declaration time
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/src/wxGUI/GUIBoxData-inlines.h,v 1.4 2011/11/02 14:31:58 keinstein Exp $
 * Copyright:   (c) 2011 TU Dresden
 * \author  Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 
 * $Date: 2011/11/02 14:31:58 $
 * \version $Revision: 1.4 $
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
 * $Log: GUIBoxData-inlines.h,v $
 * Revision 1.4  2011/11/02 14:31:58  keinstein
 * fix some errors crashing Mutabor on Windows
 *
 * Revision 1.3  2011-10-04 17:16:13  keinstein
 * make program compile on Mac (wx 2.9) and fix some memory corruption
 *
 * Revision 1.2  2011-09-30 18:07:04  keinstein
 * * make compile on windows
 * * s/wxASSERT/mutASSERT/g to get assert handler completely removed
 * * add ax_boost_base for boost detection
 *
 * Revision 1.1  2011-09-27 20:13:22  keinstein
 * * Reworked route editing backend
 * * rewireing is done by RouteClass/GUIRoute now
 * * other classes forward most requests to this pair
 * * many bugfixes
 * * Version change: We are reaching beta phase now
 *
 * Revision 1.5  2011-09-07 13:06:50  keinstein
 * Get rid of WinAttr and Fix window opening and closing
 *
 * Revision 1.4  2011-09-06 08:09:21  keinstein
 * fix a compiler error showing a corruped error message
 *
 * Revision 1.3  2011-09-05 11:30:07  keinstein
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

#if (!defined(MUWX_GUIBOXDATA_INLINES_H) && !defined(PRECOMPILE)) \
	|| (!defined(MUWX_GUIBOXDATA_INLINES_H_PRECOMPILED))
#ifndef PRECOMPILE
#define MUWX_GUIBOXDATA_INLINES_H
#endif

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

#include "src/kernel/Defs.h"
#include "src/kernel/box.h"
#include "src/wxGUI/Routing/RouteLists.h"
#include "src/wxGUI/GUIBoxData.h"
#include "src/wxGUI/Routing/BoxShape.h"

#ifndef MUWX_GUIBOXDATA_INLINES_H_PRECOMPILED
#define MUWX_GUIBOXDATA_INLINES_H_PRECOMPILED

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------


namespace mutaborGUI {
		inline MutBoxShape * BoxData::GetBoxShape(wxWindow * parent) {
			for (MutBoxShapeList::iterator shape = shapes.begin();
			     shape != shapes.end(); shape++) {
				if ((*shape)->GetParent() == parent) 
					return *shape;
			}
			return NULL;
		}

		inline void BoxData::Add(MutBoxShape * shape) {
			if (shape) {
				shapes.push_back(shape);
			} else {
				UNREACHABLEC;
			}
		}
		inline bool BoxData::Remove(MutBoxShape * shape) {
			bool ok = false;
			if (shape) {
				MutBoxShapeList::iterator pos = 
					std::find(shapes.begin(),shapes.end(),shape);
				ok = (pos != shapes.end()); 
				mutASSERT(ok);
				if (ok)
					shapes.erase(pos);
			} else {
				UNREACHABLEC;
				ok = false;
			}
			return ok;
		}

		inline void BoxData::Attatch(MutBoxShape * shape) {
			if (!shape) {
				UNREACHABLEC;
				return;
			}
			Add(shape);
			shape->Add(this);
		}
		inline bool BoxData::Detatch(MutBoxShape * shape) {
			if (!shape) {
				UNREACHABLEC;
				return false;
			}
			bool retval = Remove(shape);
			if (retval)
				retval = retval && shape->Remove(this);
			return retval;
		}
		inline bool BoxData::Delete(MutBoxShape * shape) {
			if (!shape) {
				UNREACHABLEC;
				return false;
			}
			bool retval = Detatch(shape);
			if (retval) 
				shape -> Destroy();
		}
}
#endif // MUWX_GUIBOXDATA_INLINES_H_PRECOMPILED
#endif // MUWX_GUIBOXDATA_INLINES_H
///\}
