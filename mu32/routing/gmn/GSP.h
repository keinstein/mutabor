/** \file 
 ********************************************************************
 * Description
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/mu32/routing/gmn/GSP.h,v 1.6 2011/11/02 14:31:57 keinstein Exp $
 * Copyright:   (c) 2008 TU Dresden
 * \author  Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 
 * $Date: 2011/11/02 14:31:57 $
 * \version $Revision: 1.6 $
 * \license GPL
 *
 * $Log: GSP.h,v $
 * Revision 1.6  2011/11/02 14:31:57  keinstein
 * fix some errors crashing Mutabor on Windows
 *
 * Revision 1.5  2011-09-27 20:13:22  keinstein
 * * Reworked route editing backend
 * * rewireing is done by RouteClass/GUIRoute now
 * * other classes forward most requests to this pair
 * * many bugfixes
 * * Version change: We are reaching beta phase now
 *
 * Revision 1.4  2011-02-20 22:35:56  keinstein
 * updated license information; some file headers have to be revised, though
 *
 *
 *
 ********************************************************************
 * \addtogroup route
 * \{
 ********************************************************************/
// ##################################################################
// header file of gsp (GMN Soft Parser)
// ##################################################################


/* we guard a little bit complicated to ensure the references are set right
 */

#if (!defined(MU32_ROUTING_GMN_GSP_H) && !defined(PRECOMPILE)) \
	|| (!defined(MU32_ROUTING_GMN_GSP_H_PRECOMPILED))
#ifndef PRECOMPILE
#define MU32_ROUTING_GMN_GSP_H
#endif

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

#include "mu32/Defs.h"
#include "mu32/Frac.h"

#ifndef MU32_ROUTING_GMN_GSP_H_PRECOMPILED
#define MU32_ROUTING_GMN_GSP_H_PRECOMPILED

// system headers which do seldom change


// #define GMN_STRICT

#ifndef WX
#define GSP_MAX_SEP 8000  // maximal length of a comment
#define GSP_MAX_LINE 1000  // maximal length of a line
#endif

extern int GspCurrentLineNr;    // curent line parser deals with

extern int GspErrorLineNr;      // line of occured error

extern int GspErrorPos;         // column of occured error in line

extern mutString GspErrorLine;      // text of error line

extern int  GspError;           // error id

#ifdef WX
extern mutString Sep;

#else
extern char[GSP_MAX_SEP];

extern int  SepPos;

#endif

extern const mutTranslationChar *GspErrorText[];

int GspParse(const mutString &FileName);

// extern user defined functions

#include "GIS.h"

#endif /* precompiled */
#endif


///\}
