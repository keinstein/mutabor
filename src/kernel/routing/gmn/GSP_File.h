/** \file 
 ********************************************************************
 * Description
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/src/kernel/routing/gmn/GSP_File.h,v 1.5 2011/11/02 14:31:57 keinstein Exp $
 * Copyright:   (c) 2008 TU Dresden
 * \author  Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 
 * $Date: 2011/11/02 14:31:57 $
 * \version $Revision: 1.5 $
 * \license GPL
 *
 * $Log: GSP_File.h,v $
 * Revision 1.5  2011/11/02 14:31:57  keinstein
 * fix some errors crashing Mutabor on Windows
 *
 * Revision 1.4  2011-09-27 20:13:22  keinstein
 * * Reworked route editing backend
 * * rewireing is done by RouteClass/GUIRoute now
 * * other classes forward most requests to this pair
 * * many bugfixes
 * * Version change: We are reaching beta phase now
 *
 * Revision 1.3  2011-02-20 22:35:56  keinstein
 * updated license information; some file headers have to be revised, though
 *
 *
 *
 ********************************************************************
 * \addtogroup route
 * \{
 ********************************************************************/
// ##################################################################
// file input of gsp (GMN Soft Parser)
// ##################################################################

/* we guard a little bit complicated to ensure the references are set right
 */

#if (!defined(MU32_ROUTING_GMN_GSP_FILE_H) && !defined(PRECOMPILE)) \
	|| (!defined(MU32_ROUTING_GMN_GSP_FILE_H_PRECOMPILED))
#ifndef PRECOMPILE
#define MU32_ROUTING_GMN_GSP_FILE_H
#endif

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

#include "src/kernel/Defs.h"
#include "src/kernel/routing/gmn/GSP.h"

#ifndef MU32_ROUTING_GMN_GSP_FILE_H_PRECOMPILED
#define MU32_ROUTING_GMN_GSP_FILE_H_PRECOMPILED

// system headers which do seldom change


extern mutString CurrentLine; //[GSP_MAX_LINE];

extern size_t  CurrentPos;

extern int  Eof;

int OpenFile(const mutString &Name);

int CloseFile();

int ReadNewLine();

#endif /* precompile */
#endif


///\}
