/** \file
 ***********************************************************************
 * Output functions.
 *
 * $Id: GrafKern.h,v 1.6 2008/07/22 07:57:06 keinstein Exp $
 * \author R. Krauße <krausze@users.berlios.de>
 * \date $Date: 2008/07/22 07:57:06 $
 * \version $Revision: 1.6 $
 *
 * $Log: GrafKern.h,v $
 * Revision 1.6  2008/07/22 07:57:06  keinstein
 * solved some valgrind issues
 *
 * Revision 1.5  2008/06/02 16:00:34  keinstein
 * InitCompDia: new interface
 *
 * Revision 1.4  2006/01/18 15:29:56  keinstein
 * New header and translations at display time
 *
 */

// ------------------------------------------------------------------
// Mutabor 2.win, 1997, R.Krauße
// Ausgabe-Funktionen
// ------------------------------------------------------------------

#ifndef GRAFKERN_H
#define GRAFKERN_H

#include "Defs.h"


#if defined(WX)
#include <wx/wx.h>
extern wxString Error_text[]; /* Liste der Fehlermeldungen */
extern wxString Warning_text[]; /* Liste der Warnungen */
#else
extern char * Error_text[]; /* Liste der Fehlermeldungen */
extern char * Warning_text[]; /* Liste der Warnungen */
#endif

void scanner_protokoll(int zeichen);
void AktionenInit();
void AktionenMessage(int box, char *meldung );
void fatal_error( int nummer, ... );
void compiler_warning( int nummer, ... );
void laufzeit_protokoll( char * formatstring , ... );
void init_laufzeit_protokoll( void );
void exit_laufzeit_protokoll( void );
void protokoll_aktion(char * name);
void clear_protokoll_screen( void );

void calc_declaration_numbers(char withNames = 0);
void show_line_number( int n );

#ifdef MUTWIN
#ifdef WX
#include "CompDlg.h"
void InitCompDia(CompDlg *compDia, wxString filename);
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

#endif

