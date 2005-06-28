/** \file
 ********************************************************************
 * Globale Definitionen der DLL
 * \author R. Krauﬂe
 * \version 2.win
 * \date 1997
 ********************************************************************/

#if ! defined (__GLOBAL_H_INCLUDED)
#define __GLOBAL_H_INCLUDED

#include "aktion.h"
#include "anweisung.h"
#include "argument.h"
#include "ausloeser.h"
#include "bad_decl.h"
#include "case_liste.h"
#include "harmonie.h"
#include "heap.h"
#include "instrument.h"
#include "interval.h"
#include "logik.h"
#include "midicalc.h"
#include "mut_tab.h"
#include "parameter.h"
#include "parser.h"
#include "tabgen.h"
#include "taste.h"
#include "ton.h"
#include "tonsystem.h"
#include "umstimmung.h"

#endif



#if 0 
#include "defs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
//#include <ctype.h>
#include <math.h>

#define MAX_BOX 256   ///< Maximale Anzahl der Boxen/Instumente
typedef int maxboxint[MAX_BOX];

/****** Allgemeine Strukturen *******/

/*********  Definition der Tîne als verkettete Liste ********/
/*********  Der Komplexanteil ist eine Folge von Intervallen,
            die zum Grundton addiert werden.  ***********/

/****
enum komplex_typ {komplex_anteil_relativ, komplex_anteil_faktor};
struct komplex_anteil {
    enum komplex_typ komplex_typ;
    union {
        struct {
            double faktor;
            char * linke_grenze;
            char * rechte_grenze;
        } komplex_anteil_relativ;
        struct {
            double faktor;
            char * name;
        } komplex_anteil_faktor;
    } u;
    struct komplex_anteil * next;
};
******/

/********
struct aufruf_liste {
    char * name;
    struct argument_liste * argument_liste;
    struct aufruf_liste * next;
};
******/


/* Gemeinsame Funktionen zwischen Compiler und Parser */

/* void mutabor_codegenerator(char * filename); 
   void write_kompletten_code (FILE * zieldatei); */

/**
void get_new_relativ_anteil (double f,
                          char *linke_grenze, char *rechte_grenze);
*******/


/* void init_umstimmungs_bund_liste (void); */
/* void get_umstimmungs_bund_element (char * name); */





/* Gemeinsame Funktionen zwischen Compiler und Codegenerator */

/* Globale Variablen des Compilers mit dem Parser */

/* Funktionen zur Speicherverwaltung */

/* int loesche_speicher_total( void );
 */
/* Globale Variablen des Compilers mit dem Codegenerator und
                                       dem Tabellengenerator  */

/*********** Es folgen die Wurzeln der Listen.
             Jede Liste ist nur einmal und global vorhanden,
             da die Sprache NICHT rekursiv ist.
***********/






///#define MAXLINE_TONSYSTEM 18
///#define MAXLINE_AKTIONEN 18
/* extern char KeepSound; */

/*void disable_protokoll_frame( void );
void enable_protokoll_frame( void ); */

/* TV_Protokoll

extern char laufzeit_tonsystem_string[MAXLINE_AKTIONEN][30];
extern int protokoll_ausgabezeile;

/* Protokollsteuerung :
extern int protokollfunktionen_aktiv;
extern int protokollfunktion_aktionsausgabe;
extern char * laufzeit_aktionen_string[MAXLINE_AKTIONEN];
extern char laufzeit_tonsystem_string[MAXLINE_AKTIONEN][30];
extern char aktionen_puffer[MAXLINE_AKTIONEN][30];
extern int aktionen_puffer_in;
extern int aktionen_puffer_out; */
#endif
