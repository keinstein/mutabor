/** \file 
 ********************************************************************
 * Actions at UI
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/muwx/Action.h,v 1.3 2011/02/20 22:35:56 keinstein Exp $
 * Copyright:   (c) 2005,2011 TU Dresden
 * \author   R. Krauﬂe
 * Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 2005/09/01
 * $Date: 2011/02/20 22:35:56 $
 * \version $Revision: 1.3 $
 * \license GPL
 *
 * $Log: Action.h,v $
 * Revision 1.3  2011/02/20 22:35:56  keinstein
 * updated license information; some file headers have to be revised, though
 *
 *
 * \addtogroup GUI
 * \{
 ********************************************************************/

#include "Global.h"

void AktionTraceReset();
bool TakeOverAktions();
bool ACTChanged(int box);
//char sAktion[2000];
//int ActLineNumbers;
char *GenerateACTString(int box);
char *GenerateCAWString();



///\}
