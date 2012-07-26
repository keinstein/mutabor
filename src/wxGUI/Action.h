/** \file 
 ********************************************************************
 * Actions at UI
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/src/wxGUI/Action.h,v 1.7 2011/11/02 14:31:58 keinstein Exp $
 * Copyright:   (c) 2005,2011 TU Dresden
 * \author   R. Krauße
 * Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 2005/09/01
 * $Date: 2011/11/02 14:31:58 $
 * \version $Revision: 1.7 $
 * \license GPL
 *
 * $Log: Action.h,v $
 * Revision 1.7  2011/11/02 14:31:58  keinstein
 * fix some errors crashing Mutabor on Windows
 *
 * Revision 1.6  2011-09-27 20:13:22  keinstein
 * * Reworked route editing backend
 * * rewireing is done by RouteClass/GUIRoute now
 * * other classes forward most requests to this pair
 * * many bugfixes
 * * Version change: We are reaching beta phase now
 *
 * Revision 1.5  2011-09-08 18:50:41  keinstein
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

#if (!defined(MUWX_ACTION_H) && !defined(PRECOMPILE)) \
	|| (!defined(MUWX_ACTION_H_PRECOMPILED))
#ifndef PRECOMPILE
#define MUWX_ACTION_H
#endif

#include "src/kernel/Global.h"

#ifndef MUWX_ACTION_H_PRECOMPILED
#define MUWX_ACTION_H_PRECOMPILED

void AktionTraceReset();
bool TakeOverActions();
bool ACTChanged(int box);
//char sAktion[2000//int ActLineNumbers;
char *GenerateACTString(int box);
char *GenerateCAWString();

#endif // precompile
#endif // header loaded


///\}
