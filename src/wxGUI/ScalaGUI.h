/** \file               -*- C++ -*-
 ********************************************************************
 * GUI components of the Scala import/export mechanism
 *
 * Copyright:   (c) 2016 Tobias Schlemmer
 * \author  Tobias Schlemmer <keinstein@users.sf.net>
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
 ********************************************************************
 * \addtogroup GUI
 * \{
 ********************************************************************/
/* available groups: GUI, Parser, route, kernel, debug, docview, config, GUIroute */

/* we guard a little bit complicated to ensure the references are set right
 */

#if (!defined(SRC_WXGUI_SCALAGUI_H) && !defined(PRECOMPILE)) \
	|| (!defined(SRC_WXGUI_SCALAGUI_H_PRECOMPILED))
#ifndef PRECOMPILE
#define SRC_WXGUI_SCALAGUI_H
#endif

/* ---------------------------------------------------------------------------
 * headers
 * --------------------------------------------------------------------------- */

#include "src/kernel/Defs.h"
#include "src/kernel/parsers/scala/scala.h"
#include "src/wxGUI/resourceload.h"

#ifndef SRC_WXGUI_SCALAGUI_H_PRECOMPILED
#define SRC_WXGUI_SCALAGUI_H_PRECOMPILED

/* system headers which do seldom change */

/** not for headers */
#ifdef __BORLANDC__
    #pragma hdrstop
#endif

namespace mutaborGUI {
	/// Scala import dialog with enhanced logic
	/**
	 * This class provides the real interface to the Scala import dialog.
	 */
	class ScalaImportDialog: public ScalaImportDialogBase
	{
	public:
		ScalaImportDialog(wxWindow * parent):ScalaImportDialogBase(parent) {}
		virtual ~ScalaImportDialog() {}
		void GetData(mutabor::scala_parser::mutabor_writer_options &options) {
			options.prefix = IntervalPrefix -> GetValue().ToUTF8();
			options.tone_prefix = TonePrefix -> GetValue().ToUTF8();
			options.tonesystem_name = ToneSystem -> GetValue().ToUTF8();;
			options.logic_name = Logic -> GetValue().ToUTF8();
		}
		wxFileName GetScalaFile() {
			if (!ScalaFile) return wxFileName("");
			return ScalaFile->GetFileName();
		}
		wxFileName GetKeymapFile() {
			if (!KeyMap) return wxFileName("");
			return KeyMap->GetFileName();
		}
	};
}

#endif /* precompiled */
#endif /* header loaded */


/** \} */
