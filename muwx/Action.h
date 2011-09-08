/** \file 
 ********************************************************************
 * Actions at UI
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/muwx/Action.h,v 1.5 2011/09/08 18:50:41 keinstein Exp $
 * Copyright:   (c) 2005,2011 TU Dresden
 * \author   R. Krauße
 * Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 2005/09/01
 * $Date: 2011/09/08 18:50:41 $
 * \version $Revision: 1.5 $
 * \license GPL
 *
 * $Log: Action.h,v $
 * Revision 1.5  2011/09/08 18:50:41  keinstein
 * Fix some further update bug
 *
 * Revision 1.4  2011-09-07 13:06:50  keinstein
 * Get rid of WinAttr and Fix window opening and closing
 *
 * Revision 1.3  2011-02-20 22:35:56  keinstein
 * updated license information; some file headers have to be revised, though
 *
 *
 * \addtogroup GUI
 * \{
 ********************************************************************/

#include "Global.h"

void AktionTraceReset();
bool TakeOverActions();
bool ACTChanged(int box);
//char sAktion[2000//int ActLineNumbers;
char *GenerateACTString(int box);
char *GenerateCAWString();



///\}
