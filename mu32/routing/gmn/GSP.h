/** \file 
 ********************************************************************
 * Description
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/mu32/routing/gmn/GSP.h,v 1.4 2011/02/20 22:35:56 keinstein Exp $
 * Copyright:   (c) 2008 TU Dresden
 * \author  Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 
 * $Date: 2011/02/20 22:35:56 $
 * \version $Revision: 1.4 $
 * \license GPL
 *
 * $Log: GSP.h,v $
 * Revision 1.4  2011/02/20 22:35:56  keinstein
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

#ifndef GSP_H
#define GSP_H

#include "Frac.h"

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
#endif


///\}
