// ------------------------------------------------------------------
// Mutabor 2.win, 1997, R.Krau�e
// Ausgabe-Funktionen
// ------------------------------------------------------------------

#ifdef MUTWIN
  #include <windows.h>
#endif

#include "Global.h"
#include "Interpre.h"
#include "GrafKern.h"
#include "Interval.h"
#include "Mutabor.rh"
#include "Execute.h"
#include <setjmp.h>

#ifdef MUTWIN
#ifdef WX
CompDlg* CompDia1 = NULL;
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

int keys_changed[MAX_BOX];
int keys_changed_sum;

char sd1[100], sd2[100];
#ifdef WX
char sd3[20], sd4[20], sd5[20], sd6[20];
#endif
char Fmeldung[255];

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

void AktionenMessage(int box, char* aktionName)
{
  if ( nAktionen < AKTIONEN_MAX )
  {
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
void InitCompDia(CompDlg *compDia)
{
  CompDia1 = compDia;
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
  if ( withNames)
  {
	 sprintf(sd1, "  logics: %d\n  tones: %d\n  tunes: %d",
		logik_list_laenge(list_of_logiken),
		ton_list_laenge(list_of_toene),
		umstimmungs_list_laenge(list_of_umstimmungen));
	 sprintf(sd2, "  tone systems: %d\n  intervalls; %d\n  read chars: %d",
		tonsystem_list_laenge(list_of_tonsysteme),
		intervall_list_laenge(list_of_intervalle),
		anzahl_eingelesene_zeichen);
  }
  else
  {
#ifdef WX
	 sprintf(sd1, "%d", logik_list_laenge(list_of_logiken));
	 sprintf(sd2, "%d", ton_list_laenge(list_of_toene));
	 sprintf(sd3, "%d", umstimmungs_list_laenge(list_of_umstimmungen));
	 sprintf(sd4, "%d", tonsystem_list_laenge(list_of_tonsysteme));
	 sprintf(sd5, "%d", intervall_list_laenge(list_of_intervalle));
	 sprintf(sd6, "%d", anzahl_eingelesene_zeichen);
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
  }
}

void show_line_number( int n )
{
#ifdef WX
  if ( !CompDia1 ) return;
  wxString s = _T("---      ");
  if ( n != -1 ) s.Format(_T("%d       "), n);
  CompDia1->SetText(IDC_COMP_LINE, s);
#else
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
  vsprintf(Fmeldung,Error_text[nr], arglist );
  longjmp( weiter_gehts_nach_compilerfehler , (nr==0)?255:nr );
}

// Compiler - Warning -----------------------------------------------

#if defined(WX) && defined(MUTWIN) && !defined(__WXMSW__)
	#include <wx/msgdlg.h>
#endif

void compiler_warning( int nr, ... )
{
  char Fmeldung[255];
  va_list arglist;

  va_start(arglist,nr);
  vsprintf(Fmeldung,Warning_text[nr], arglist );

  #ifdef MUTWIN
    #if defined(WX) && !defined(__WXMSW__)
      wxMessageBox(Fmeldung, _("Compiler warning"), wxOK | wxICON_ASTERISK );
    #else
      MessageBox(0, Fmeldung, "Compiler warning", MB_OK | MB_ICONASTERISK );
    #endif
  #endif
}

void laufzeit_message( char * Meldung )
{
  if ( strlen(protokoll_string) + strlen(Meldung) <= PROT_MAXCHARS - 2 )
  {
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

{
}

void laufzeit_protokoll( char * formatstring , ... )
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
  char *s = strstr(Fmeldung, "Zeile");
  if ( !s ) return -1;
  return atol(&(s[5]));
}

