/** \file
 ********************************************************************
 * Output operations
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/src/kernel/GrafKern.cpp,v 1.19 2011/11/02 14:31:57 keinstein Exp $
 * \author Rüdiger Krauße <krausze@mail.berlios.de>
 * \date $Date: 2011/11/02 14:31:57 $
 * \version $Revision: 1.19 $
 * \license GPL
 *
 * $Log: GrafKern.cpp,v $
 * Revision 1.19  2011/11/02 14:31:57  keinstein
 * fix some errors crashing Mutabor on Windows
 *
 * Revision 1.18  2011-09-30 18:07:04  keinstein
 * * make compile on windows
 * * s/wxASSERT/mutASSERT/g to get assert handler completely removed
 * * add ax_boost_base for boost detection
 *
 * Revision 1.17  2011-09-30 09:10:24  keinstein
 * Further improvements in the routing system.
 *
 * Revision 1.16  2011-09-27 20:13:21  keinstein
 * * Reworked route editing backend
 * * rewireing is done by RouteClass/GUIRoute now
 * * other classes forward most requests to this pair
 * * many bugfixes
 * * Version change: We are reaching beta phase now
 *
 * Revision 1.15  2011-09-08 16:51:21  keinstein
 * Set foreground color in box status windows
 * Fix updating box status windows
 * update RtMidi (includes Jack compilation mode)
 *
 * Revision 1.14  2011-09-06 08:09:20  keinstein
 * fix a compiler error showing a corruped error message
 *
 * Revision 1.13  2011-02-20 22:35:55  keinstein
 * updated license information; some file headers have to be revised, though
 *
 * Revision 1.12  2010-11-21 13:15:45  keinstein
 * merged experimental_tobias
 *
 * Revision 1.11.2.2  2010-03-30 08:38:27  keinstein
 * added rudimentary command line support
 * changed debug system to allow selection of messages via command line
 * further enhancements to the route dialogs
 *
 * Revision 1.11.2.1  2009/08/04 11:30:49  keinstein
 * removed mut.h
 *
 * Revision 1.11  2008/10/27 15:00:16  keinstein
 * Adopted VC8-changes to any
 *
 * Revision 1.10  2008/10/19 23:08:32  krausze
 * Dateien und Anpassungen für Microsoft Visual Studio 8 (VC8)
 *
 * Revision 1.9  2008/10/10 08:33:19  keinstein
 * make compile on windws
 *
 * Revision 1.8  2008/10/01 09:30:47  keinstein
 * fixed inclution for XCode build
 *
 * Revision 1.7  2008/08/18 15:02:41  keinstein
 * fixed some const char * warnings
 *
 * Revision 1.6  2008/06/02 16:00:12  keinstein
 * UTF-8
 * don't include Mutabor.rh (already included)
 * access compile dialog static text directly to display line number
 * fix formatting of line numbers
 *
 * Revision 1.5  2006/01/18 15:28:03  keinstein
 * Get translations of error strings
 *
 * Revision 1.4  2005/11/07 19:42:54  keinstein
 * Some additional changes
 *
 *
 ********************************************************************
 * \addtogroup kernel
 * \{
 ********************************************************************/
// ------------------------------------------------------------------
// Mutabor 2.win, 1997, R.Krauße
// Ausgabe-Funktionen
// ------------------------------------------------------------------

#include "src/kernel/Defs.h"
#include "src/wxGUI/generic/mutDebug.h"
#include "src/kernel/Global.h"
#include "src/kernel/Interpre.h"
#include "src/kernel/GrafKern.h"
#include "src/kernel/Interval.h"
//#include "Mutabor.rh"
#include "src/kernel/Execute.h"
#include <setjmp.h>

// Needed at least for Visual C++ 8
#include "src/kernel/Runtime.h"

#ifdef MUTWIN
#ifdef WX
#include "wx/msgdlg.h"
wxStaticText* CompDiaLine = NULL;
#else
HWND CompDiaLine;
#endif
#endif

int protokoll_ausgabezeile = 0;
int aktionen_ausgabezeile = 0;

extern jmp_buf weiter_gehts_nach_compilerfehler;

#define PROT_MAXLINES 30
#define PROT_MAXCHARS PROT_MAXLINES*40
#define AKTIONEN_MAX 100

char protokoll_string[PROT_MAXCHARS];

char sAktionen[AKTIONEN_MAX*50];

unsigned char boxAktionen[AKTIONEN_MAX];

int lAktionen[AKTIONEN_MAX];

int nAktionen = 0;

#ifdef WX
wxString sd1, sd2, sd3, sd4, sd5, sd6;

wxString Fmeldung;

#else
char sd1[100], sd2[100];

char Fmeldung[255];

#endif


// Aktionen ---------------------------------------------------------

void AktionenInit()
{
	nAktionen = 0;
}

#ifdef MUTWIN
/*void aktionen_message( char * Meldung )
{
  while ( aktionen_ausgabezeile >= PROT_MAXLINES ||
	 strlen(aktionen_string) + strlen(Meldung) > PROT_MAXCHARS - 2 )
  {
	 char *s1 = strstr(aktionen_string, "\n");
	 if ( s1 )
    {
      strcpy(aktionen_string, &(s1[2]));
      aktionen_ausgabezeile--;
    }
  }
  if ( aktionen_ausgabezeile ) strcat(aktionen_string, "\n");
  strcat(aktionen_string, Meldung);
  aktionen_ausgabezeile++;
  aktionen_changed = 1;
}*/

void AktionenMessage(int box, const char* aktionName)
{
	if ( nAktionen < AKTIONEN_MAX ) {
		boxAktionen[nAktionen] = ((unsigned char*)&box)[0];
		int l = 0;

		if ( nAktionen )
			l = lAktionen[nAktionen-1];

		strcpy(&sAktionen[l], aktionName);

		lAktionen[nAktionen++] = l + strlen(aktionName);
	}
}

int pascal _export GetActString(unsigned char **box, int **l, char **s)

{
	int n = nAktionen;
	*box = boxAktionen;
	*l = lAktionen;
	*s = sAktionen;
	nAktionen = 0;
	return n;
}

// Compiler-Dialog --------------------------------------------------

#ifdef WX
void InitCompDia(mutaborGUI::CompDlg *compDia, wxString filename)
{
	mutASSERT(compDia);
	CompDiaLine = compDia->GetLine();
}

#else
void InitCompDia(HWND compDiaLine)
{
	CompDiaLine = compDiaLine;
}

#endif

#else

#include <iostream.h>

extern ostream *Echo;

void aktionen_message( char * Meldung )
{
	*Echo << "\n  Action: " << Meldung;
}

#endif

void calc_declaration_numbers(char withNames)
{
#ifdef MUTWIN
#ifdef WX
	sd1 = wxString::Format(_T("%d"), logik_list_laenge(list_of_logiken));
	sd2 = wxString::Format(_T("%d"), ton_list_laenge(list_of_toene));
	sd3 = wxString::Format(_T("%d"), umstimmungs_list_laenge(list_of_umstimmungen));
	sd4 = wxString::Format(_T("%d"), tonsystem_list_laenge(list_of_tonsysteme));
	sd5 = wxString::Format(_T("%d"), intervall_list_laenge(list_of_intervalle));
	sd6 = wxString::Format(_T("%ld"), anzahl_eingelesene_zeichen);
#else
	sprintf(sd1, "%d\n%d\n%d",
	        logik_list_laenge(list_of_logiken),
	        ton_list_laenge(list_of_toene),
	        umstimmungs_list_laenge(list_of_umstimmungen));
	sprintf(sd2, "%d\n%d\n%d",
	        tonsystem_list_laenge(list_of_tonsysteme),
	        intervall_list_laenge(list_of_intervalle),
	        anzahl_eingelesene_zeichen);
#endif
#else

	if ( withNames) {
		sprintf(sd1, "  logics: %d\n  tones: %d\n  tunes: %d",
		        logik_list_laenge(list_of_logiken),
		        ton_list_laenge(list_of_toene),
		        umstimmungs_list_laenge(list_of_umstimmungen));
		sprintf(sd2, "  tone systems: %d\n  intervalls; %d\n  read chars: %d",
		        tonsystem_list_laenge(list_of_tonsysteme),
		        intervall_list_laenge(list_of_intervalle),
		        anzahl_eingelesene_zeichen);
	} else {
		sprintf(sd1, "%d\n%d\n%d",
		        logik_list_laenge(list_of_logiken),
		        ton_list_laenge(list_of_toene),
		        umstimmungs_list_laenge(list_of_umstimmungen));
		sprintf(sd2, "%d\n%d\n%d",
		        tonsystem_list_laenge(list_of_tonsysteme),
		        intervall_list_laenge(list_of_intervalle),
		        anzahl_eingelesene_zeichen);
	}

#endif
}

void show_line_number( int n )

{
#ifdef WX
	DEBUGLOG2(other,_T("No. %d in WX mode"),n);

	if ( !CompDiaLine ) return;

	wxString s = _T("");
	if ( n != -1 ) s << n;

	DEBUGLOG2(other,_T("s = %s"), s.c_str());

	CompDiaLine->SetLabel(s);
	CompDiaLine->Refresh();

#else
	DEBUGLOG2(other,_T("No. %d in non-WX mode"),n);
#ifdef MUTWIN
	if ( !CompDiaLine ) return;

	char s[20] = "---      ";

	if ( n != -1 ) sprintf(s, "%d       ", n);

	::SetWindowText(CompDiaLine, s);

#endif
#endif
}

void fatal_error( int nr, ... )
{
	va_list arglist;
	va_start(arglist,nr);
#ifdef WX
	Fmeldung = wxString::Format(_("Error %d:"),nr) +
		wxString::FormatV(wxGetTranslation(Error_text[nr]), arglist);
#else
	vsprintf( Fmeldung, Error_text[nr], arglist );
#endif
	longjmp( weiter_gehts_nach_compilerfehler , (nr==0)?255:nr );
}

// Compiler - Warning -----------------------------------------------

void compiler_warning( int nr, ... )
{
	va_list arglist;
	va_start(arglist,nr);
#ifdef MUTWIN
	DEBUGLOGBASE (other,_T(""), _T("testing %s"), _T("%s"));
	DEBUGLOGBASE (other,_T(""),
	              _T("Compiler warning %d: %s"),
	              nr,
	              Warning_text[nr]);
#if defined(WX)
	wxMessageBox(wxString::FormatV(wxGetTranslation(Warning_text[nr]),
	                               arglist),
	             _("Compiler warning"),
	             wxOK | wxICON_ASTERISK );
#else
	char Fmeldung[255];
	vsprintf( Fmeldung, Warning_text[nr], arglist );
	MessageBox(0, Fmeldung, "Compiler warning", MB_OK | MB_ICONASTERISK );
#endif
#endif
}

void laufzeit_message(const char * Meldung )
{
	if ( strlen(protokoll_string) + strlen(Meldung) <= PROT_MAXCHARS - 2 ) {
		if ( protokoll_ausgabezeile ) strcat(protokoll_string, "\n");

		strcat(protokoll_string, Meldung);

		protokoll_ausgabezeile++;
	}
}

void init_laufzeit_protokoll( void )

{
	protokoll_ausgabezeile = 0;
	strcpy(protokoll_string, "");
}

void exit_laufzeit_protokoll( void )

{}

void laufzeit_protokoll(const char * formatstring , ... )
{
	char Fmeldung[255];
	va_list arglist;

	va_start(arglist, formatstring); /* hier 0 statt nr */
	vsprintf(Fmeldung, formatstring, arglist );
	laufzeit_message (Fmeldung);
}

#ifdef MUTWIN

char* pascal _export GetKeyString(int box, char asTS)
{
	init_laufzeit_protokoll();

	if ( asTS )
		protokoll_liegende_frequenzen(box);
	else
		protokoll_liegende_relationen(box);

	return protokoll_string;
}

char* pascal _export GetTSString(int box, char asTS)

{
	init_laufzeit_protokoll();

	if ( asTS )
		protokoll_aktuelles_tonsystem(box);
	else
		protokoll_aktuelle_relationen(box);

	return protokoll_string;
}

int pascal _export GetLineNumbers()
{
	return protokoll_ausgabezeile;
}

#endif

int pascal _export GetErrorLine()
{
#if defined(WX)
	int i = Fmeldung.First(_("line"));
	long l;

	if ( i != -1 && Fmeldung.Mid(i+wxString(_("line")).Length()).ToLong(&l) )
		return l;
	else
		return -1;

#else
	char *s = strstr(Fmeldung, "Zeile");

	if ( !s ) return -1;

	return atol(&(s[5]));

#endif
}


///\}
