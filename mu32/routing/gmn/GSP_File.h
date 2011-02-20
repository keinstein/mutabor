/** \file 
 ********************************************************************
 * Description
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/mu32/routing/gmn/GSP_File.h,v 1.3 2011/02/20 22:35:56 keinstein Exp $
 * Copyright:   (c) 2008 TU Dresden
 * \author  Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 
 * $Date: 2011/02/20 22:35:56 $
 * \version $Revision: 1.3 $
 * \license GPL
 *
 * $Log: GSP_File.h,v $
 * Revision 1.3  2011/02/20 22:35:56  keinstein
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

#ifndef GSP_FILE_H
#define GSP_FILE_H

#include "GSP.h"

extern mutString CurrentLine; //[GSP_MAX_LINE];

extern size_t  CurrentPos;

extern int  Eof;

int OpenFile(const mutString &Name);

int CloseFile();

int ReadNewLine();

#endif


///\}
