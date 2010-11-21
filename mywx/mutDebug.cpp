/*
 *  mutDebug.cpp
 *  Mutabor
 *
 *  Created by Tobias Schlemmer on 25.03.10.
 *  Copyright 2010 TU Dresden. All rights reserved.
 *
 */

#include "Defs.h"
#ifdef DEBUG
#include "mutDebug.h"

debugFlags::debugFlagSet debugFlags::flags;


void debugFlags::InitCommandLine(wxCmdLineParser&  parser) {
#define DEBUGFLAG(flag,description) \
    { wxCMD_LINE_SWITCH, wxEmptyString, _T("debug-"#flag), description },
	static const wxCmdLineEntryDesc cmdLineDesc[] =
	{
#include "mutDebugFlags.h"		
		{ wxCMD_LINE_NONE }
	};
#undef DEBUGFLAG
	parser.SetDesc(cmdLineDesc);
}
void debugFlags::ProcessCommandLine(wxCmdLineParser&  parser) {
#define DEBUGFLAG(flag,description) \
  debugFlags::flags[flag]=parser.Found(_T("debug-"#flag));
#include "mutDebugFlags.h"
#undef DEBUGFLAG	
}

#endif
