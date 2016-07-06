/** \file               -*- C++ -*-
 ********************************************************************
 * Description
 *
 * Copyright:   (c) 2013 Tobias Schlemmer
 * \author  Tobias Schlemmer <keinstein@users.sourceforge.net>
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
 * \addtogroup debug
 * \{
 ********************************************************************/
/* available groups: GUI, Parser, route, kernel, debug, docview, config, GUIroute */

/* we guard a little bit complicated to ensure the references are set right
 */

#if (!defined(WXGUI_TESTINITIALIZER_H) && !defined(PRECOMPILE)) \
	|| (!defined(WXGUI_TESTINITIALIZER_H_PRECOMPILED))
#ifndef PRECOMPILE
#define WXGUI_TESTINITIALIZER_H
#endif

/* ---------------------------------------------------------------------------
 * headers
 * --------------------------------------------------------------------------- */

#include "src/kernel/Defs.h"

#ifndef WXGUI_TESTINITIALIZER_H_PRECOMPILED
#define WXGUI_TESTINITIALIZER_H_PRECOMPILED

/* system headers which do seldom change */

class wxInitializer;
/// An abstraction of wxInitializer
/** the main purpose of this class is to increase the call stack for the objects that are created by 
 *   the wxWidgets library.
 *
 * When using ThreadSanitizer some suppressions are
 * needed. Unfortunately it is not always possible to access the right
 * function inside the binary blob of a shared object file. So we wrap
 * them, here, and we add corresponding suppressions in the test
 * folders.
 */
class mutwxInitializer {
public:
	/// constructor
	/** The constructor checks whether the compiler options are
	 * compatible for linking the library and creates a
	 * wxInitializer object.
	 */
	mutwxInitializer();

	/// destructor
	/** The destructor deltees the wxInitializer object.
	 */
	~mutwxInitializer();
protected:
	wxInitializer * initializer; //< Object holding the (de-)initalization instance.
};


#endif /* precompiled */
#endif /* header loaded */


/** \} */
