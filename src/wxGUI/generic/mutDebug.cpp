/** \file
 ********************************************************************
 * Some functions and classes to help to debug Mutabor
 *
 * Copyright:   (c) 2010,2011 TU Dresden
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
 ********************************************************************
 * \addtogroup debug
 * \{
 ********************************************************************/
/*
 *  mutDebug.cpp
 *  Mutabor
 *
 *  Created by Tobias Schlemmer on 25.03.10.
 *  Copyright 2010 TU Dresden. All rights reserved.
 *
 */

#include "src/kernel/Defs.h"
#include "src/wxGUI/MutApp.h"
#include "wx/apptrait.h"
#include "wx/log.h"

#include "mutDebug.h"
#include <list>
#if __WXMSW__
#include <iostream>
#include <fstream>
#include <conio.h>
#include <stdio.h>
#endif

#include "src/kernel/routing/Route-inlines.h"

#ifdef DEBUG
void InitDebugCommandLine(wxCmdLineParser&  parser)
{
#if wxCHECK_VERSION(2,9,0)
#  ifdef N_
#    undef N_
#  endif
#  define N_(text) text
#  define DEBUGFLAG(flag,description)					\
        { wxCMD_LINE_SWITCH, "", ("debug-"#flag), (description) },
#else
#  define DEBUGFLAG(flag,description)					\
	{ wxCMD_LINE_SWITCH, wxEmptyString, _T("debug-"#flag), description },
#endif
	static const wxCmdLineEntryDesc cmdLineDesc[] =	{
#include "src/kernel/debugFlags.h"
			{ wxCMD_LINE_NONE }
		};
#undef DEBUGFLAG
	parser.SetDesc(cmdLineDesc);
}

void ProcessDebugCommandLine(wxCmdLineParser&  parser)
{
#define DEBUGFLAG(flag,description)					\
	mutabor::mutabor_debug_flags.flag = parser.Found(_T("debug-"#flag));
#include "src/kernel/debugFlags.h"
#undef DEBUGFLAG
	mutabor::mutabor_debug_flags.always = true;
}
#endif


///\}
