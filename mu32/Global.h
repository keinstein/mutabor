// ------------------------------------------------------------------
// Mutabor 2.win, 1997, R.Krauﬂe
// Globale Defiitionen der DLL
// ------------------------------------------------------------------

#ifndef WX
#define GERMAN
#endif

#if ! defined (__GLOBAL_H_INCLUDED)
#define __GLOBAL_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string>
#include <math.h>
#include "Defs.h"

/* #define alloca xmalloc */
#define bcopy(from,to,n) memcpy((to),(from),(n))
#define bzero(s,n) memset((s),0,(n))
#define bcmp(b1,b2,len) memcmp((b1),(b2),(len))

#define MAX_BREITE 72
/* (=Maximale Breite eines Tonsystems */
#define MAX_MIDI 32
/* (=Max. Anzahl Bytes in MIDIOUT / MIDIIN) */

#define FREQUENZ_TO_MIDI(x) (log((x)/440.0)/0.05776226504666210908 + 69)
               /* Die Zahl 0.0577... ist log(Zwoelfte Wurzel aus zwei) */

#define FAKTOR_TO_MIDI(x) (17.31234049066756089 * log(x))
               /* 17.31... ist 12/log(2)  */

#define MAX_BOX 256   // Anzahl der Boxen/Instumente

void init_yylex (void);

/****** Allgemeine Strukturen *******/

struct parameter_liste {
    char * name;
    struct parameter_liste * next;
};

typedef int parameter_typ;

enum argument_typ {zahl, parameter};
struct argument {
         enum argument_typ argument_typ ;
         union {
             struct {
                 int zahl;
             } zahl;
             struct {
                 int parameter_nummer;   /* Der soundsovielte ,
                                            der deklariert ist. */
                 char * parameter_name;
             } parameter;
         } u;
};

struct argument_liste {
    struct argument argument;
    struct argument_liste * next;
};

struct midiliste {
    int midi_code;
    struct midiliste * next;
};

/*********  Definition der Intervalle als verkettete Liste ********/

enum intervall_typ {intervall_absolut, intervall_komplex};
struct intervall {
    char * name;
    enum intervall_typ intervall_typ;
    union {
        struct {
            double intervall_wert;
        } intervall_absolut;
        struct {
            struct komplex_intervall * komplex_liste;
        } intervall_komplex;
    } u;
    struct intervall *next;
};

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

struct komplex_intervall {
    double faktor;
    char * name;
    struct komplex_intervall * next;
};

enum ton_typ {ton_absolut, ton_komplex};
struct ton {
    char * name;
    enum ton_typ ton_typ;
    union {
        struct {
            double ton_wert;
        } ton_absolut;
        struct {
            char * bezugston;
            struct komplex_intervall * komplex_liste;
        } ton_komplex;
    } u;
    struct ton * next;
};

/*********  Definition der Tonsysteme als verkettete Liste ********/
/********   Ein Tonsystem enthÑlt eine Liste mit den enthaltenen
            Tînen. Der Name eines Tons ist (NULL) wenn dieser Ton
            nicht gÅltig ist, ansonsten der Name des Tons.
*******/


struct tonsystem {
    char *name;
    int taste;
    struct komplex_intervall *periode;
    struct ton *toene;
    struct tonsystem *next;
};

/*********  Definition der Umstimmungen als verkettete Liste ********/

enum umstimmung_typ {
         umstimmung_taste_abs,
         umstimmung_taste_rel,
         umstimmung_breite_abs,
         umstimmung_breite_rel,
         umstimmung_toene_veraendert,
         umstimmung_wiederholung_abs,
         umstimmung_wiederholung_rel,
         umstimmung_umstimmungsbund,
         umstimmung_umstimmungs_case,
         umstimmung_midi_out
};

/********
struct aufruf_liste {
    char * name;
    struct argument_liste * argument_liste;
    struct aufruf_liste * next;
};
******/
struct case_liste {
    int case_label;
    char is_default;
    struct aktions_liste * case_aktion;
    struct case_liste * next;
};

struct umstimmung {
    char *name;
    struct parameter_liste * parameter_liste;
    enum umstimmung_typ umstimmung_typ;
    union {
        struct {
            struct argument argument;
        } umstimmung_taste_abs;
        struct {
            struct argument argument;
            char rechenzeichen;
        } umstimmung_taste_rel;
        struct {
            struct argument argument;
        } umstimmung_breite_abs;
        struct {
            struct argument argument;
            char rechenzeichen;
        } umstimmung_breite_rel;
        struct {
            struct ton * tonliste;
        } umstimmung_toene_veraendert;
        struct {
            struct komplex_intervall * komplex_liste;
        } umstimmung_wiederholung_abs;
        struct {
            struct komplex_intervall * komplex_liste;
        } umstimmung_wiederholung_rel;
        struct {
            struct aktions_liste * aktions_liste;
        } umstimmung_umstimmungsbund;
        struct {
            struct argument argument;
            struct case_liste * umstimmungs_case_liste;
        } umstimmung_umstimmungs_case;
        struct {
            struct midiliste * out_liste;
        } umstimmung_midi_out;
    } u;
    struct umstimmung * next;
};

/*********  Definition der Harmonien als verkettete Liste ********/

struct taste {
	int code;     //int taste - Namensprobleme
    char stern;      /* TRUE oder FALSE, ob Stern deklariert ist */
    struct taste * next;
};

struct harmonie {
    char * name;
    struct taste * tastenliste;
    int bezugstaste;
    struct harmonie * next;
};

/*********  Definition der Logiken als verkettete Liste ********/


enum ausloeser_typ {ausloeser_harmonie, ausloeser_harmonie_form,
                    ausloeser_taste, ausloeser_midi_in,
                    ausloeser_default};
struct ausloeser {
    enum ausloeser_typ ausloeser_typ;
    union {
        struct {
            int vortaste;
            char * name;
            int nachtaste;
        } ausloeser_harmonie;
        struct {
            int vortaste;
            char * name;
            int nachtaste;
        } ausloeser_harmonie_form;
        struct {
            char * taste;
        } ausloeser_taste;
        struct {
            struct midiliste * midi_code;
        } ausloeser_midi_in;
    } u;
};


enum aktions_typ {aktion_midi_out, aktion_aufruf};
struct aktions_liste {
    enum aktions_typ aktions_typ;
    union {
        struct {
            struct midiliste * midi_code;
        } aktion_midi_out;
        struct {
            char * name;
            struct argument_liste * argument_liste;
        } aktion_aufruf;
    } u;
    struct aktions_liste * next;
};




struct anweisung {
    struct ausloeser * ausloeser;
    struct aktions_liste * aktion;
    struct anweisung * next;
};



struct logik {
    char * name;
    struct ausloeser * ausloeser;
    char * einstimmungs_name;
    struct anweisung * anweisungsliste;
    struct logik * next;
};

/*********  Definition der Instrumente als verkettete Liste ********/

struct instrument {
    int midi_in;
    int midi_von;
    int midi_bis;
    int midi_umleit;
    struct instrument * next;
};

void xfree (void * pointer);
void * xmalloc (size_t size);
void * xrealloc (void * block, size_t newsize);
void * xcalloc (size_t anzahl, size_t size);


/* Gemeinsame Funktionen zwischen Compiler und Parser */

int yylex();
void yyerror(char *);
int yyparse ();

void mutabor_programm_einlesen (const wxChar * filename) ;
void mutabor_tabellen_generator (void);
void mutabor_codegenerator(char * filename);
void write_kompletten_code (FILE * zieldatei);

void get_new_intervall (char * name, double wert);
void get_new_intervall_komplex (char * name);
double get_wert_komplex_intervall (struct komplex_intervall * intervall);

void get_new_ton_absolut (char * name, double wert);
void init_komplex_ton_list (void);
void get_new_faktor_anteil (double f, char *name);
/**
void get_new_relativ_anteil (double f,
                          char *linke_grenze, char *rechte_grenze);
*******/
void get_new_ton_komplex_positive (char *name, char *bezugston);
void get_new_ton_komplex_negative (char *name, char *bezugston);

void init_ton_liste (void);
void get_new_ton_in_tonsystem (char *name);
void get_new_tonsystem (char *name, int taste);
void get_new_tonsystem_negative (char *name, int taste);


void init_parameter_liste (void);
void get_new_name_in_parameterlist (char * name);
void get_new_number_in_parameterlist (double wert);

void init_argument_liste (void);
void get_new_name_in_argument_list (char * parameter);
void get_new_number_in_argument_list (double parameter);

void init_aktions_liste (void);
void get_new_aktion_aufruf_element (char * name);
void get_new_aktion_midi_out_element (void);

void init_umstimmung (char * name);
void eintrage_parameterliste_in_umstimmung (void);
void get_new_umstimmung (void);

void get_umstimmung_taste_abs (
     enum argument_typ argument, //zahl_oder_parameter_typ zahl_oder_parameter,
     double zahl_wert, char * parameter);
void get_umstimmung_taste_rel (
     enum argument_typ argument,
     double zahl_wert, char * parameter, char vorzeichen);
void get_umstimmung_breite_abs (
     enum argument_typ argument,
     double zahl_wert, char * parameter);
void get_umstimmung_breite_rel (
     enum argument_typ argument,
     double zahl_wert, char * parameter, char vorzeichen);
void init_umstimm_expression_list (void);
void get_umstimmung_tonhoehe_veraendert (void);
void get_new_umstimm_expression (char * bezugston);
void get_new_umstimm_expression_positive (char * bezugston);
void get_new_umstimm_expression_negative (char * bezugston);
void get_umstimmung_wiederholung_abs (void);
void get_umstimmung_wiederholung_abs_negative (void);
void get_umstimmung_wiederholung_rel_positive (void);
void get_umstimmung_wiederholung_rel_negative (void);
/* void init_umstimmungs_bund_liste (void); */
void get_umstimmung_umstimmungs_bund (void);
/* void get_umstimmungs_bund_element (char * name); */

void init_umstimmungs_case_liste (void);
void get_umstimmung_umstimm_case_zahl (int selector);
void get_umstimmung_umstimm_case_parameter (char * selector);
void init_umstimmungs_case_aktions_liste (void);
void get_umstimmungs_case_zahl_element (int konstante);
void get_umstimmungs_case_default_element (void);
void get_umstimmungs_case_aktions_element (char * aktion);
void get_umstimmung_midi_out (void);


void init_tastenliste (void);
void get_new_harmonie (char * name, int bezugstaste);
void get_new_taste (int taste, char stern);

void init_ausloeser (void);
void get_aktion_midi_out (void);
void get_aktion_aufruf (char * name);
void init_ausloeser (void);
void get_ausloeser_default (void);
void get_ausloeser_harmonie (void);
void get_ausloeser_harmonie_form (void);
void get_ausloeser_taste (char * name);
void get_ausloeser_midi_in (void);
void init_anweisungs_liste (void);
void vervollstaendige_logik (void);
void init_integersequenz (void);
void get_new_integer_in_integersequenz (int wert);


void init_anweisungs_liste (void);
void get_new_logik (char * name, char * einstimmung);
void get_new_anweisung (void);
void get_harmoniebezeichner (int vor_taste,
                             char * name,
                             int nach_taste);

void get_instrument_dekl (int midi_in, int midi_von, int midi_bis, int midi_umleit,
                          struct instrument ** list_to_insert);

/* Gemeinsame Funktionen zwischen Compiler und Codegenerator */

int ton_list_laenge (struct ton *list);
int tonsystem_list_laenge (struct tonsystem *list);
int umstimmungs_list_laenge (struct umstimmung *list);
int logik_list_laenge (struct logik *list);
int midi_list_laenge (struct midiliste *list);
int get_logik_nummer (char * name, struct logik * liste);
struct ton * get_ton (char * name, struct ton * liste);
struct intervall * get_intervall (char * name,
                                      struct intervall * liste);
struct tonsystem * parser_get_tonsystem (char * name, struct tonsystem * liste);
struct umstimmung * get_umstimmung (char * name, struct umstimmung * liste);
struct harmonie * get_harmonie (char * name, struct harmonie * liste);
struct logik * get_logik (char * name, struct logik * liste);

int  intern_fgetc( FILE *stream );
int  intern_ungetc( int c, FILE *stream );

/* Globale Variablen des Compilers mit dem Parser */

extern FILE * quelldatei;
extern long anzahl_eingelesene_zeichen;

/* Funktionen zur Speicherverwaltung */

int init_speicher_total( void );
int loesche_speicher_total( void );
int init_laufzeit_speicher( void );
int loesche_laufzeit_speicher( void );

/* Globale Variablen des Compilers mit dem Codegenerator und
                                       dem Tabellengenerator  */

/*********** Es folgen die Wurzeln der Listen.
             Jede Liste ist nur einmal und global vorhanden,
             da die Sprache NICHT rekursiv ist.
***********/


extern struct intervall      *  list_of_intervalle;
extern struct ton            *  list_of_toene;
extern struct tonsystem      *  list_of_tonsysteme;
extern struct umstimmung     *  list_of_umstimmungen;
extern struct harmonie       *  list_of_harmonien;
extern struct logik          *  list_of_logiken;
extern struct instrument     *  list_of_instrumente;
extern struct instrument     *  list_of_config_instrumente;

extern int geheimcode;


void show_line_number( int n );

///#define MAXLINE_TONSYSTEM 18
///#define MAXLINE_AKTIONEN 18
#define LINE_DRAW_QUANTUM 17

extern int keys_changed[MAX_BOX];
extern int keys_changed_sum;
extern char KeepSound;

/*void disable_protokoll_frame( void );
void enable_protokoll_frame( void ); */

/* TV_Protokoll

extern char laufzeit_tonsystem_string[MAXLINE_AKTIONEN][30];
extern int protokoll_ausgabezeile;*/

/* Protokollsteuerung :
extern int protokollfunktionen_aktiv;
extern int protokollfunktion_aktionsausgabe;
extern char * laufzeit_aktionen_string[MAXLINE_AKTIONEN];
extern char laufzeit_tonsystem_string[MAXLINE_AKTIONEN][30];
extern char aktionen_puffer[MAXLINE_AKTIONEN][30];
extern int aktionen_puffer_in;
extern int aktionen_puffer_out; */
#endif

