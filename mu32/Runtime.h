/** \file 
 ********************************************************************
 * Description
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/mu32/Runtime.h,v 1.13 2011/03/06 13:15:41 keinstein Exp $
 * Copyright:   (c) 2008 TU Dresden
 * \author  Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 
 * $Date: 2011/03/06 13:15:41 $
 * \version $Revision: 1.13 $
 * \license GPL
 *
 * $Log: Runtime.h,v $
 * Revision 1.13  2011/03/06 13:15:41  keinstein
 * some rearrangement for update callback kernel->GUI
 *
 * Revision 1.12  2011-02-20 22:35:55  keinstein
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
 * \addtogroup runtime
 * \{
 ********************************************************************/
// ------------------------------------------------------------------
// Mutabor 2.win, 1997, R.Krauﬂe
// Laufzeitfunktionen der DLL
// ------------------------------------------------------------------

#if ! defined (__RUNTIME_H_INCLUDED)
#define __RUNTIME_H_INCLUDED

#include "Defs.h"

#include "wx/wxchar.h"
#include "CompDlg.h"
#if !defined(__WXMSW__)
#ifndef UINT
#define UINT unsigned int
#endif
#define pascal
#endif
#include <setjmp.h>

#include "Device.h"

typedef void UpdateCallback(int Box, bool Logic);

extern "C"
{
	extern bool RealTime;

	extern jmp_buf weiter_gehts_nach_compilerfehler;
	extern UpdateCallback* updatecallback;

#ifndef WX
	char pascal Compile( TDialog *compWin, const char *name );

#else
	char pascal Compile( CompDlg *compDia, const wxChar *name );

#endif
	bool pascal Activate(bool realTime, UpdateCallback* callback);
	void pascal Stop();
	void pascal Panic();

//  void pascal InDeviceActionAll(char action);
	void pascal InDeviceAction(int inDevNr, enum MutaborModeType action);

	bool pascal CheckNeedsRealTime();

	// box = -1 ... weiterlesen in angefangener Liste
	char pascal GetMutTag(char &isLogic, char *text, char *einsttext, char &key, int box = -1);
	char pascal IsLogicKey(char key);
	bool pascal KeyChanged(int box);
	bool pascal TSChanged(int box);
	bool pascal InDevicesChanged();
	void pascal GetInDevicesMode(enum MutaborModeType *mode);
	void pascal GetDrivers(int *driver);
	void pascal SetDrivers(int *driver);
	char pascal GetChannels(char start, int &base, int &from, int &to, int &thru);
	void pascal SetChannels(int base, int from, int to, int thru);
	void pascal SetAktuellesKeyboardInstrument(int instr);
	int  pascal GetAktuellesKeyboardInstrument();

#ifndef WX
	void pascal ScanDevices(char *config);
#endif

	OutDevice * GetOut(int nr);
	void pascal GetTimerData(UINT &min, UINT &max);
}

#endif



///\}
