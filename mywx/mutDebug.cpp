/** \file 
 ********************************************************************
 * Description
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/mywx/mutDebug.cpp,v 1.3 2011/02/20 22:35:59 keinstein Exp $
 * Copyright:   (c) 2008 TU Dresden
 * \author  Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 
 * $Date: 2011/02/20 22:35:59 $
 * \version $Revision: 1.3 $
 * \license GPL
 *
 * $Log: mutDebug.cpp,v $
 * Revision 1.3  2011/02/20 22:35:59  keinstein
 * updated license information; some file headers have to be revised, though
 *
 * Revision 1.2  2010-11-21 13:15:51  keinstein
 * merged experimental_tobias
 *
 * Revision 1.1.2.1  2010-01-11 10:12:59  keinstein
 * added some .cvsignore files
 *
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

///\}
