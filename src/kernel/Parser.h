/** \file -*- C -*-
 ********************************************************************
 * Parser data sturctures and functions
 *
 * Copyright:   (c) 2013 Tobias Schlemmer
 * \author  Tobias Schlemmer <keinstein@users.sourceforge.net>
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
/* availlable groups: GUI, route, kernel, muwx, debug, docview, config, docview */

/* we guard a little bit complicated to ensure the references are set right
 */

#if (!defined(SRC_KERNEL_PARSER_H) && !defined(PRECOMPILE)) \
	|| (!defined(SRC_KERNEL_PARSER_H_PRECOMPILED))
#ifndef PRECOMPILE
#define SRC_KERNEL_PARSER_H
#endif

/* --------------------------------------------------------------------------- */
/* headers */
/* --------------------------------------------------------------------------- */

#include "src/kernel/Defs.h"
#include "src/kernel/box.h"
#include "src/kernel/Global.h"

#ifndef SRC_KERNEL_PARSER_H_PRECOMPILED
#define SRC_KERNEL_PARSER_H_PRECOMPILED

#include <limits.h>
#define MUTABOR_NO_CASE_LABEL INT_MIN
#ifdef __cplusplus
namespace mutabor {
	namespace hidden {
		extern "C" {
#endif
/* system headers which do seldom change */

struct mutabor_scanner_data {
	const char * data;
	const char * pos;
	size_t anzahl_eingelesene_zeichen;
};

enum umst_oder_logik_typ
	{
		typ_umstimmung, typ_logik
	};

struct umst_oder_logik
{
	enum umst_oder_logik_typ umst_oder_logik_typ;
	union {

		struct umstimmung * umstimmung;

		struct logik * logik;
	} u;
};

struct heap_element;
struct mutabor_syntax_heap {
	struct heap_element * syntax_heap;
	struct heap_element * heap_to_use_syntax;
};

/** Cache of constant values.
 *   each value is stored only once (and equal for all boxes)
 *
 *  As constants are usually parameters in functions that can be
 *  called with arbitrary parameters we use this to avoid the need of
 *  duplicate functions.
 */
struct constant_memory
{
	int constant;
	struct constant_memory * next;
};

struct mutabor_logic_parsed {
	int refcount;
	void * mutex;
	struct intervall      *  list_of_intervalle;
	struct ton            *  list_of_toene;
	struct tonsystem      *  list_of_tonsysteme;
	struct umstimmung     *  list_of_umstimmungen;
	struct harmonie       *  list_of_harmonien;
	struct logik          *  list_of_logiken;
	struct instrument     *  list_of_instrumente;
	struct instrument     *  list_of_config_instrumente;
	struct ton            *  ton_ohne_namen; /* Frequenz=0 */
	struct constant_memory * list_of_constants;

	/* temporary data */
	/**
	 * Collect the different tones of a tone system
	 * This list will be emptied after a tone system is read
	 */
	struct ton * ton_liste;
	enum harmony_type  tmp_harmony_flags;
	int          tmp_vor_taste;
	const char * tmp_name;
	int          tmp_nach_taste;
	struct ausloeser * tmp_ausloeser;
	struct anweisung * tmp_anweisungsliste;
	struct umstimmung * tmp_umstimmung;
	struct ton * tmp_tonliste;
	struct case_liste * tmp_umstimmungs_case_liste;
	struct midiliste * list_of_integers;
	struct parameter_list * list_of_names;
	struct argument_list * list_of_argumente;
	struct aktions_liste * list_of_aktionen;
	struct komplex_intervall * the_komplex_liste;
	struct taste * tmp_tastenliste;
	struct instrument * lauf_instrument;

	struct interpreter_parameter_list start_parameters;
	size_t constant_count;
	size_t parameter_count;


	/* some triggers that are always active if the logic is active. E.g., the main triggers of logics */
	struct harmonie_ereignis * global_harmonies; /*< harmony triggers that are always active */
	struct keyboard_ereignis * global_keystrokes; /*< keyboard triggers that are always active */
	struct midi_ereignis * global_midi_inputs; /*< MIDI in triggers that are always active */

	struct mutabor_syntax_heap heap;

        /**************************************************************

            Hier werden die Toene aufgelîst.
            Nach dem Parsing ist nur die Syntax-Struktur
            vorhanden, aber keine fertig ausgerechneten Toene.

            Es wird ein azyklischer Graph der Toene und ihrer
            Untertoene gebildet, der dann nach den
            depth-first-search traversiert wird.
            Dabei bekommt jeder Ton seine Absolutfrequenz berechnet.

	****************************************************************/

	/* some variables to support loop checking */
	size_t interval_count;              /*< size of read intervals */
	struct intervall ** check_intervals; /*< fast access to intervals */
	char * visited_intervals;                     /*< mark traversed nodes */
	char * interval_matrix;            /*< directed graph containing the loops */

	int anzahl_toene;       /*< Number of read tones */
	struct ton ** toene;    /*< faster access than using lists */
	char * visited_tones;         /* marker for traversing */
	char * tone_matrix;          /* Adjacency matrix access only using the macro mutabor_adjacent */

	/**************************************************************
            Es wird ein azyklischer Graph der Umstimmungen
            gebildet, der dann nach den
            depth-first-search traversiert wird.
            Dabei wird ein beliebiger Zyklus festgestellt.

	****************************************************************/
	int anzahl_umstimmungen_und_logiken;  /* so viele Umstimmungen wurden gelesen */
	struct umst_oder_logik * zyklen_feld;    /* Feld von Umstimmungen
						    zum schnelleren Zugriff als ueber Listen */
 	char * u_visited;         /* Traversierungsmerker */
	char * u_matrix; /* Adjazenzmatrix (auf sie darf nur ueber
			    das folgende Makro zugegriffen werden !*/

};

#define mutabor_adjacent(matrix,a,b) matrix [ (a) * box->file->anzahl_toene * sizeof (char) \
			       + (b) * sizeof (char)]
#define mutabor_u_adjacent(u_matrix,a,b) u_matrix [ (a) * box->file->anzahl_umstimmungen_und_logiken \
				   * sizeof (char) + (b) * sizeof (char)]


int ton_list_laenge (const struct ton *list);
int tonsystem_list_laenge (const struct tonsystem *list);
int umstimmungs_list_laenge (const struct umstimmung *list);
int logik_list_laenge (const struct logik *list);
int midi_list_laenge (const struct midiliste *list);
int get_logik_nummer (mutabor_box_type * box, const char * name, struct logik * liste);

struct ton * get_ton (mutabor_box_type * box, const char * name, struct ton * liste);
struct intervall * get_intervall (const char * name,
				  struct intervall * liste);
struct tonsystem * parser_get_tonsystem (const char * name, struct tonsystem * liste);
struct umstimmung * get_umstimmung (const char * name, struct umstimmung * liste);
struct harmonie * get_harmonie (const char * name, struct harmonie * liste);
struct logik * get_logik (const char * name, struct logik * liste);

void init_integersequenz (mutabor_box_type * box);
void get_new_integer_in_integersequenz (mutabor_box_type * box, int wert);
		    /*void init_parameter_liste (mutabor_box_type * box); */
struct parameter_list * get_new_name_in_parameterlist (mutabor_box_type * box, const char * name);
void enumerate_parameters (mutabor_box_type * box, struct parameter_list * parameters);
		    /*void init_argument_liste (mutabor_box_type * box); */
struct argument_list * get_new_number_in_argument_list (mutabor_box_type * box, double number);
struct argument_list * get_new_name_in_argument_list (mutabor_box_type * box, const char * parameter);
struct argument_list * get_new_distance_in_argument_list (mutabor_box_type * box);
struct argument_list * get_new_anchor_in_argument_list (mutabor_box_type * box);


void init_aktions_liste (mutabor_box_type * box);
void get_new_aktion_aufruf_element (mutabor_box_type * box,
				    const char * name,
				    struct argument_list * arguments);

void get_new_aktion_midi_out_element (mutabor_box_type * box);
void get_new_aktion_harmony_analysis(mutabor_box_type * box);
void init_komplex_ton_list (mutabor_box_type * box);
void get_new_faktor_anteil (mutabor_box_type * box, double f, const char *name);

bool mutabor_programm_einlesen (mutabor_box_type * box, const char * logic);

void get_new_intervall (mutabor_box_type * box, const char * name, double wert);
void get_new_intervall_komplex (mutabor_box_type * box, const char * name);
void get_new_ton_absolut (mutabor_box_type * box, const char * name, double wert);
void get_new_ton_komplex_positive (mutabor_box_type * box, const char *name, const char *bezugston);
void get_new_ton_komplex_negative (mutabor_box_type * box, const char *name, const char *bezugston);

void init_ton_liste (mutabor_box_type * box);
void get_new_ton_in_tonsystem (mutabor_box_type * box, const char *name);
void get_new_tonsystem (mutabor_box_type * box, const char *name, int taste);
void get_new_tonsystem_negative (mutabor_box_type * box, const char *name, int taste);
void init_umstimmung (mutabor_box_type * box, const char * name);
void get_new_umstimmung (mutabor_box_type * box);
void eintrage_parameterliste_in_umstimmung (mutabor_box_type * box,
					    struct umstimmung * ret,
					    struct parameter_list * list);


void get_umstimmung_taste_abs (mutabor_box_type * box,
			       struct argument_list * argument);
void get_umstimmung_taste_rel (mutabor_box_type * box,
			       struct argument_list * argument,
			       char vorzeichen);
void get_umstimmung_breite_abs (mutabor_box_type * box,
				struct argument_list * argument);
void get_umstimmung_breite_rel (mutabor_box_type * box,
				struct argument_list * argument,
				char vorzeichen);
void init_umstimm_expression_list (mutabor_box_type * box);
void get_new_umstimm_expression (mutabor_box_type * box,
				 const char * bezugston);
void get_new_umstimm_expression_positive (mutabor_box_type * box,
					  const char * bezugston);
void get_new_umstimm_expression_negative (mutabor_box_type * box,
					   const char * bezugston);
void get_umstimmung_tonhoehe_veraendert (mutabor_box_type * box);
void get_umstimmung_wiederholung_abs (mutabor_box_type * box);
void get_umstimmung_wiederholung_abs_negative (mutabor_box_type * box);
void get_umstimmung_wiederholung_rel_positive (mutabor_box_type * box);
void get_umstimmung_wiederholung_rel_negative (mutabor_box_type * box);
void get_umstimmung_umstimmungs_bund (mutabor_box_type * box);
void get_umstimmungs_case_zahl_element (mutabor_box_type * box, int konstante);
void get_umstimmungs_case_default_element (mutabor_box_type * box);
void init_umstimmungs_case_liste (mutabor_box_type * box);
void get_umstimmung_umstimm_case (mutabor_box_type * box, struct argument_list * argument);
void get_umstimmung_midi_out (mutabor_box_type * box);
void init_tastenliste (mutabor_box_type * box);
void get_new_taste (mutabor_box_type * box, int taste, char stern);
void get_new_harmonie (mutabor_box_type * box, const char * name, int bezugstaste);
/**
 * Save a harmony temporary harmony descriptor in the parser data.
 *
 * \param box        Box the parser belongs to.
 * \param flags      Flags that tell which keys to use.
 * \param vor_taste  Lowest key of the described harmony.
 * \param name       Name of the harmony that shall be used
 * \param nach_taste Highest key of the described harmony
 */
void get_harmoniebezeichner (mutabor_box_type * box,
			     enum harmony_type flags,
			     int vor_taste,
                             const char * name,
                             int nach_taste);
void init_ausloeser (mutabor_box_type * box);
void get_ausloeser_default (mutabor_box_type * box);
void get_ausloeser_harmonie (mutabor_box_type * box);
void get_ausloeser_harmonie_form (mutabor_box_type * box);
void get_ausloeser_taste (mutabor_box_type * box, const char * name);
void get_ausloeser_midi_in (mutabor_box_type * box);
void init_anweisungs_liste (mutabor_box_type * box);
void get_new_anweisung (mutabor_box_type * box);
void get_new_logik (mutabor_box_type * box, const char * name);
void vervollstaendige_logik (mutabor_box_type * box);
void get_instrument_dekl (mutabor_box_type * box, int midi_in, int midi_von, int midi_bis, int midi_umleit,
                          struct instrument ** list_to_insert);

#ifdef __cplusplus
		}
	}
}
#endif


#endif /* precompiled */
#endif /* header loaded */


/** \} */
