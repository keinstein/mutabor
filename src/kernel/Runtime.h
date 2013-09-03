/** \file 
 ********************************************************************
 * Description
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/src/kernel/Runtime.h,v 1.15 2011/11/02 14:31:57 keinstein Exp $
 * Copyright:   (c) 2008 TU Dresden
 * \author  Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 
 * $Date: 2011/11/02 14:31:57 $
 * \version $Revision: 1.15 $
 * \license GPL
 *
 *
 ********************************************************************
 * \addtogroup runtime
 * \{
 ********************************************************************/
// ------------------------------------------------------------------
// Mutabor 2.win, 1997, R.Krauﬂe
// Laufzeitfunktionen der DLL
// ------------------------------------------------------------------

/* we guard a little bit complicated to ensure the references are set right
 */

#if (!defined(MU32_RUNTIME_H) && !defined(PRECOMPILE)) \
	|| (!defined(MU32_RUNTIME_H_PRECOMPILED))
#ifndef PRECOMPILE
#define MU32_RUNTIME_H
#endif

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

#include "src/kernel/Defs.h"
#include "src/wxGUI/CompDlg.h"
#include "src/kernel/routing/Device.h"

#ifndef MU32_RUNTIME_H_PRECOMPILED
#define MU32_RUNTIME_H_PRECOMPILED

// system headers which do seldom change


#include "wx/wxchar.h"
#if !defined(__WXMSW__)
#ifndef UINT
#define UINT unsigned int
#endif
#endif
#include <setjmp.h>


extern jmp_buf weiter_gehts_nach_compilerfehler;


//  void  InDeviceActionAll(char action);
//void  InDeviceAction(int inDevNr, enum mutabor::MutaborModeType action);

#if 0
char  IsLogicKey(mutabor_box_type * box, char key);
// box = -1 ... weiterlesen in angefangener Liste
char  GetMutTag(char &isLogic, char **text, char *einsttext, char &key, mutabor_box_type * box);
bool  KeyChanged(int box);
bool  TSChanged(int box);
bool  InDevicesChanged();
void  GetInDevicesMode(enum mutabor::MutaborModeType *mode);
void  GetDrivers(int *driver);
void  SetDrivers(int *driver);
char  GetChannels(char start, int &base, int &from, int &to, int &thru);
void  SetChannels(int base, int from, int to, int thru);
void  SetAktuellesKeyboardInstrument(int instr);
mutabor_box_type *  GetAktuellesKeyboardInstrument();

#ifndef WX
void  ScanDevices(char *config);
#endif

mutabor::OutputDevice GetOut(int nr);
void  GetTimerData(UINT &min, UINT &max);
#endif 

#endif /* precompiled */
#endif



///\}
