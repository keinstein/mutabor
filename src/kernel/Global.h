/** \file
 ********************************************************************
 * Global definitions (formerly in mutabor DLL)
 *
 * Copyright:   (c) 1997--2008 TU Dresden
 * \author R. Krauße,
 * Tobias Schlemmer <keinstein@users.berlios.de>
 * \license GPL
 *
 *    This program is free software; you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation; either version 2 of the License, or
 *    (at your option) any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this program; if not, write to the Free Software
 *    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *
 ********************************************************************
 * \addtogroup kernel
 * \{
 ********************************************************************/

#ifndef WX
#define GERMAN
#endif

/* we guard a little bit complicated to ensure the references are set right
 */

#if (!defined(MU32_GLOBAL_H) && !defined(PRECOMPILE)) \
	|| (!defined(MU32_GLOBAL_H_PRECOMPILED))
#ifndef PRECOMPILE
#define MU32_GLOBAL_H
#endif

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

#include "Defs.h"

#ifndef MU32_GLOBAL_H_PRECOMPILED
#define MU32_GLOBAL_H_PRECOMPILED

// system headers which do seldom change

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string>
#include <math.h>


#ifdef __cplusplus
namespace mutabor {
	namespace hidden {
		extern "C" {
#endif
/* #define alloca xmalloc */
#define bcopy(from,to,n) memcpy((to),(from),(n))
#define bzero(s,n) memset((s),0,(n))
#define bcmp(b1,b2,len) memcmp((b1),(b2),(len))

/* originial values were: 72, 36, 96 */
#define MUTABOR_KEYRANGE_MAX_WIDTH 128
#define MUTABOR_KEYRANGE_MIN_KEY 0
#define MUTABOR_KEYRANGE_MAX_KEY 128
/* (=Maximale Breite eines Tonsystems */
#define MAX_MIDI 32
/* (=Max. Anzahl Bytes in MIDIOUT / MIDIIN) */

#define FREQUENZ_TO_MIDI(x) (log((x)/440.0)/0.05776226504666210908 + 69)
/* Die Zahl 0.0577... ist log(Zwoelfte Wurzel aus zwei) */

#define FAKTOR_TO_MIDI(x) (17.31234049066756089 * log(x))
/* 17.31... ist 12/log(2)  */

//#define MAX_BOX 256   // Anzahl der Boxen/Instumente
#define MUTABOR_NO_KEY (INT_MIN+1)
#define MUTABOR_INVALID_KEY (INT_MIN)

//void init_yylex (void);

/****** Allgemeine Strukturen *******/

struct parameter_liste
{
	const char * name;
	struct parameter_liste * next;
};

typedef int parameter_typ;

enum argument_typ {zahl, parameter};

struct argument
{
	enum argument_typ argument_typ ;
	union {
		struct {
			int zahl;
		} zahl;

		struct {
			int parameter_nummer;
                        /* Der soundsovielte , der deklariert ist. */
			const char * parameter_name;
		} parameter;
	} u;
};

struct argument_liste
{
	struct argument argument;
	struct argument_liste * next;
};

struct midiliste
{
	int midi_code;
	struct midiliste * next;
};

/*********  Definition der Intervalle als verkettete Liste ********/

enum intervall_typ {intervall_absolut, intervall_komplex};

struct intervall
{
	const char * name;
	enum intervall_typ intervall_typ;
	union
	{
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
            const char * linke_grenze;
            const char * rechte_grenze;
        } komplex_anteil_relativ;
        struct {
            double faktor;
            const char * name;
        } komplex_anteil_faktor;
    } u;
    struct komplex_anteil * next;
};
******/

struct komplex_intervall
{
	double faktor;
	const char * name;
	struct komplex_intervall * next;
};

enum ton_typ {ton_absolut, ton_komplex};

struct ton
{
	const char * name;
	enum ton_typ ton_typ;
	union
	{
		struct {
			double ton_wert;
		} ton_absolut;

		struct {
			const char * bezugston;
			struct komplex_intervall * komplex_liste;
		} ton_komplex;
	} u;

	struct ton * next;
};

/*********  Definition der Tonsysteme als verkettete Liste ********/
/********   Ein Tonsystem enthält eine Liste mit den enthaltenen
            Tönen. Der Name eines Tons ist (NULL) wenn dieser Ton
            nicht gültig ist, ansonsten der Name des Tons.
*******/


struct tonsystem
{
	const char *name;
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
    const char * name;
    struct argument_liste * argument_liste;
    struct aufruf_liste * next;
};
******/

struct case_liste
{
	int case_label;
	char is_default;
	struct aktions_liste * case_aktion;
	struct case_liste * next;
};

struct umstimmung
{
	const char *name;
	struct parameter_liste * parameter_liste;
	enum umstimmung_typ umstimmung_typ;

	union
	{
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

struct taste
{
	int code;     //int taste - Namensprobleme
	char stern;      /* TRUE oder FALSE, ob Stern deklariert ist */

	struct taste * next;
};

struct harmonie
{
	const char * name;

	struct taste * tastenliste;

	int bezugstaste;

	struct harmonie * next;
};

/*********  Definition der Logiken als verkettete Liste ********/


enum ausloeser_typ {ausloeser_harmonie, ausloeser_harmonie_form,
                    ausloeser_taste, ausloeser_midi_in,
                    ausloeser_default};

struct ausloeser
{
	enum ausloeser_typ ausloeser_typ;
	union {
		struct {
			int vortaste;
			const char * name;
			int nachtaste;
		} ausloeser_harmonie;

		struct {
			int vortaste;
			const char * name;
			int nachtaste;
		} ausloeser_harmonie_form;

		struct {
			const char * taste;
		} ausloeser_taste;

		struct {
			struct midiliste * midi_code;
		} ausloeser_midi_in;
	} u;
};


enum aktions_typ {
	aktion_midi_out,
	aktion_aufruf,
	aktion_harmony_analysis
};

struct aktions_liste
{
	enum aktions_typ aktions_typ;
	union {

		struct {

			struct midiliste * midi_code;
		} aktion_midi_out;

		struct {
			const char * name;
			struct argument_liste * argument_liste;
		} aktion_aufruf;
#if 0
		// currently empty
		struct {
		} aktion_harmony_analysis;
#endif
	} u;

	struct aktions_liste * next;
};




struct anweisung
{

	struct ausloeser * ausloeser;
	struct aktions_liste * aktion;
	struct anweisung * next;
};



struct logik
{
	const char * name;
	struct ausloeser * ausloeser;
	const char * einstimmungs_name;
	struct anweisung * anweisungsliste;
	struct logik * next;
	struct do_aktion * einstimmung;
	struct harmonie_ereignis * harmony_list;
	struct keyboard_ereignis * keystroke_list;
	struct midi_ereignis * midi_input_list;
};

/*********  Definition der Instrumente als verkettete Liste ********/

struct instrument
{
	int midi_in;
	int midi_von;
	int midi_bis;
	int midi_umleit;

	struct instrument * next;
};

void xfree (void * pointer);


/* Gemeinsame Funktionen zwischen Compiler und Parser */

void mutabor_codegenerator(const char * filename);
void write_kompletten_code (FILE * zieldatei);

/**
void get_new_relativ_anteil (double f,
                          char *linke_grenze, char *rechte_grenze);
*******/
void get_new_number_in_parameterlist (double wert);





/* void init_umstimmungs_bund_liste (void); */

/* void get_umstimmungs_bund_element (const char * name); */

void init_umstimmungs_case_aktions_liste (void);



void get_umstimmungs_case_aktions_element (const char * aktion);



void get_aktion_midi_out (void);

void get_aktion_aufruf (const char * name);

/* Funktionen zur Speicherverwaltung */

int init_speicher_total( void );

int loesche_speicher_total( void );


/* Globale Variablen des Compilers mit dem Codegenerator und
                                       dem Tabellengenerator  */




///#define MAXLINE_ton_system 18
///#define MAXLINE_AKTIONEN 18
#define LINE_DRAW_QUANTUM 17

			//extern char KeepSound;

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


#ifdef __cplusplus
		} // extern "C"
	} // namespace hidden
} // namespace mutabor
#endif

#endif // precompiled
#endif


///\}
