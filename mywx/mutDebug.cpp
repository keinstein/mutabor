/** \file 
 ********************************************************************
 * Description
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/mywx/mutDebug.cpp,v 1.5 2011/10/02 16:58:42 keinstein Exp $
 * Copyright:   (c) 2010,2011 TU Dresden
 * \author  Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 
 * $Date: 2011/10/02 16:58:42 $
 * \version $Revision: 1.5 $
 * \license GPL
 *
 * $Log: mutDebug.cpp,v $
 * Revision 1.5  2011/10/02 16:58:42  keinstein
 * * generate Class debug information when compile in debug mode
 * * InputDeviceClass::Destroy() prevented RouteClass::Destroy() from clearing references -- fixed.
 * * Reenable confirmation dialog when closing document while the logic is active
 * * Change debug flag management to be more debugger friendly
 * * implement automatic route/device deletion check
 * * new debug flag --debug-trace
 * * generate lots of tracing output
 *
 * Revision 1.4  2011-08-24 21:19:36  keinstein
 * first run with 2.9.2+
 *
 * Revision 1.3  2011-02-20 22:35:59  keinstein
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
#include <list>

debugFlags::flagtype debugFlags::flags;


debugFlags::flagtype::flagtype() 
{
#define DEBUGFLAG(flag,description) \
	flags.flag = false;
#include "mutDebugFlags.h"
#undef DEBUGFLAG	

	// manual overrides for debug purposes
	flags.smartptr = true;
}


void debugFlags::InitCommandLine(wxCmdLineParser&  parser) 
{
#if wxCHECK_VERSION(2,9,0)
#define DEBUGFLAG(flag,description) \
    { wxCMD_LINE_SWITCH, "", ("debug-"#flag), (const char *)wxString(description) },
#else
#define DEBUGFLAG(flag,description) \
    { wxCMD_LINE_SWITCH, wxEmptyString, _T("debug-"#flag), description },
#endif
	static const wxCmdLineEntryDesc cmdLineDesc[] =
	{
#include "mutDebugFlags.h"		
		{ wxCMD_LINE_NONE }
	};
#undef DEBUGFLAG
	parser.SetDesc(cmdLineDesc);
}

void debugFlags::ProcessCommandLine(wxCmdLineParser&  parser) 
{
#define DEBUGFLAG(flag,description) \
  debugFlags::flags.flag = parser.Found(_T("debug-"#flag));
#include "mutDebugFlags.h"
#undef DEBUGFLAG	
}

typedef std::list<void *> ptrlist;
static ptrlist debug_save_pointers;

void debug_destroy_class(void * ptr) 
{
	debug_save_pointers.push_back(ptr);
}
void debug_destruct_class(void * ptr) 
{
	debug_save_pointers.remove(ptr);
}
void debug_print_pointers()
{
	for (ptrlist::iterator i = debug_save_pointers.begin();
	     i != debug_save_pointers.end();
	     i++) {
		fprintf(stderr, "\nUndeleted pointer: %p",(void *)(*i));
	}
	fprintf(stderr,"\n");
}
bool debug_is_all_deleted()
{
	return debug_save_pointers.empty();
}


#endif

///\}
