/** \file
 ***********************************************************************
 * Output functions.
 *
 * $Id: GrafKern.h,v 1.14 2011/11/02 14:31:57 keinstein Exp $
 * \author R. Krauße <krausze@users.berlios.de>
 * \date $Date: 2011/11/02 14:31:57 $
 * \version $Revision: 1.14 $
 *
 * $Log: GrafKern.h,v $
 * Revision 1.14  2011/11/02 14:31:57  keinstein
 * fix some errors crashing Mutabor on Windows
 *
 * Revision 1.13  2011-10-02 16:58:40  keinstein
 * * generate Class debug information when compile in debug mode
 * * InputDeviceClass::Destroy() prevented RouteClass::Destroy() from clearing references -- fixed.
 * * Reenable confirmation dialog when closing document while the logic is active
 * * Change debug flag management to be more debugger friendly
 * * implement automatic route/device deletion check
 * * new debug flag --debug-trace
 * * generate lots of tracing output
 *
 * Revision 1.12  2011-09-27 20:13:21  keinstein
 * * Reworked route editing backend
 * * rewireing is done by RouteClass/GUIRoute now
 * * other classes forward most requests to this pair
 * * many bugfixes
 * * Version change: We are reaching beta phase now
 *
 * Revision 1.11  2011-02-20 22:35:55  keinstein
 * updated license information; some file headers have to be revised, though
 *
 * Revision 1.10  2010-11-21 13:15:45  keinstein
 * merged experimental_tobias
 *
 * Revision 1.9.2.1  2009-08-04 11:30:49  keinstein
 * removed mut.h
 *
 * Revision 1.9  2008/10/14 08:07:59  keinstein
 * added Errors.h and started to define Error symbols
 *
 * Revision 1.8  2008/10/01 09:30:47  keinstein
 * fixed inclution for XCode build
 *
 * Revision 1.7  2008/08/18 15:05:29  keinstein
 * fixed some const char * warnings and charset issues
 *
 * Revision 1.6  2008/07/22 07:57:06  keinstein
 * solved some valgrind issues
 *
 * Revision 1.5  2008/06/02 16:00:34  keinstein
 * InitCompDia: new interface
 *
 * Revision 1.4  2006/01/18 15:29:56  keinstein
 * New header and translations at display time
 *
 *
 ********************************************************************
 * \addtogroup kernel
 * \{
 ********************************************************************/

/* we guard a little bit complicated to ensure the references are set right
 */

#if (!defined(MU32_GRAFKERN_H) && !defined(PRECOMPILE)) \
	|| (!defined(MU32_GRAFKERN_H_PRECOMPILED))
#ifndef PRECOMPILE
#define MU32_GRAFKERN_H
#endif

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

#include "Defs.h"
#include "Errors.h"

#ifndef MU32_GRAFKERN_H_PRECOMPILED
#define MU32_GRAFKERN_H_PRECOMPILED




void scanner_protokoll(int zeichen);
void AktionenInit();

void AktionenMessage(int box, const char *meldung );

void fatal_error( int nummer, ... ) __attribute__ ((noreturn));

void compiler_warning( int nummer, ... );

void laufzeit_protokoll(const char * formatstring , ... );

void init_laufzeit_protokoll( void );

void exit_laufzeit_protokoll( void );

void protokoll_aktion(const char * name);

void clear_protokoll_screen( void );

void calc_declaration_numbers(char withNames = 0);

void show_line_number( int n );

#ifdef MUTWIN
#ifdef WX
#include "src/wxGUI/CompDlg.h"
void InitCompDia(mutaborGUI::CompDlg *compDia, wxString filename);

#else
void InitCompDia(HWND compDiaLine);

#endif
#endif

void drucke_keyboard_liste( int instr );

void update_keyboard_liste( int instr );

void enable_protokoll_frame( void );

extern int scanner_echo;

#ifdef MUTWIN
extern "C"
{
	int pascal GetActString(unsigned char **box, int **l, char **s);
	char* pascal GetKeyString(int box, char asTS);
	char* pascal GetTSString(int box, char asTS);
	int pascal GetLineNumbers();
	int pascal GetErrorLine();
}

#endif

#ifdef WX
extern wxString sd1, sd2, sd3, sd4, sd5, sd6;

extern wxString Fmeldung;

#define LAUFZEIT_ERROR0(format) Fmeldung = format
#define LAUFZEIT_ERROR1(format, a) Fmeldung = wxString::Format(format, a)
#define LAUFZEIT_ERROR2(format, a, b) Fmeldung = wxString::Format(format, a, b)
#else
extern char sd1[100], sd2[100];

extern char Fmeldung[255];

#define LAUFZEIT_ERROR0(format, a) strcpy(Fmeldung, format)
#define LAUFZEIT_ERROR1(format, a) sprintf(Fmeldung, format, a)
#define LAUFZEIT_ERROR2(format, a, b) sprintf(Fmeldung, format, a, b)
#endif

#endif // precompiled
#endif


///\}
