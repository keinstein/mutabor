/** \file 
 ********************************************************************
 * Table genarator
 *
 * Copyright:   (c) 1997-2011 TU Dresden
 *               Changes after 2011-11 (c) by the authors
 * \author  R.Krauße,
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

#include "Global.h"
#include "box.h"
#include "Interpre.h"
#include "Interval.h"
#include "Parser.h"
#include "Execute.h"
#include "Hilfs.h"
//#include "MidiKern.h"
#include <math.h>

#ifdef _
#undef _
#endif
#define _ _mut

#ifdef __cplusplus
namespace mutabor {
	namespace hidden {
		extern "C" {
#endif

/*** Das sind die Anfangslisten des Interpreters **/



long anzahl_eingelesene_zeichen;

/***** Dies ist die Hauptprozedur um eine Aktion in die
       Laufzeit-Tabellen einzutragen. Liefert Zeiger auf
       neu allokierte Aktion zurück.
*****/

static do_aktion*   expandiere_name (mutabor_box_type * box,
				       const char * name,
				       struct argument_liste * parameter,
				       struct interpreter_parameter_list * bezugs_liste);

static do_aktion*  expandiere_umstimmung (mutabor_box_type * box,
					     struct umstimmung * the_umstimmung,
					     struct interpreter_parameter_list * aktuelle_parameter);

static do_aktion*  expandiere_midi (mutabor_box_type * box, struct midiliste * liste);
static struct do_aktion * expand_harmony_analysis(mutabor_box_type * box) ;

void insert_in_lokale_liste (mutabor_box_type * box,
			     struct do_aktion * action,
			     struct anweisung * lauf,
                             struct logik * logic);



/**************************************************/



double get_komplex_faktor (mutabor_box_type * box, struct komplex_intervall * lauf)
{
	double ret = 1.0;
	TRACE;

	for ( ; lauf ; lauf = lauf -> next )
	{

		struct intervall * help = get_intervall (lauf->name, box->file->list_of_intervalle);

		if (help) {
			switch (help -> intervall_typ) {
			case intervall_absolut: 
				ret *= pow (help -> u.intervall_absolut.intervall_wert,
					    lauf->faktor);
				break;
			case intervall_komplex: 
				ret *= pow (get_komplex_faktor(box,
							       help -> u.intervall_komplex.komplex_liste),
					    lauf->faktor);
				break;
			default:
				mutabor_error_message(box,
						      false,
						      _("Unknown interval type %d detected at\n%s:%d"),
						      __FILE__, __LINE__);
			}
		} else {
			mutabor_error_message(box,
					      false,
					      _("Could not get interval %s."),
					      (lauf->name));
		}

	}

	return ret;
}


double get_komplex_frequenz (mutabor_box_type * box, struct ton * dieser)
{
	double ret = get_ton (box, dieser->u.ton_komplex.bezugston, box->file->list_of_toene)
	             -> u.ton_absolut.ton_wert;
	ret *= get_komplex_faktor (box, dieser->u.ton_komplex.komplex_liste);
	return ret;
}


 void fprint_argument (mutabor_box_type * box, FILE * zieldatei, struct argument * argument)
 {
	 TRACE;
	if (argument -> argument_typ == zahl)
		{
		fprintf (zieldatei, ", %d ", argument -> u.zahl.zahl);
	} else if (argument -> argument_typ == parameter)
	{
		fprintf (zieldatei, ", %s ", argument -> u.parameter.parameter_name);
	} else
		mutabor_error_message(box,
				      false,
				      _("Unknown parameter type %d detected at %s:%d"),
				      _T(__FILE__), 
				      __LINE__ );
}

/*
static int enthaelt_nur_konstante_toene (struct ton * lauf)
{
    while (lauf) {
        if (lauf -> name != NULL           &&
            lauf -> ton_typ == ton_komplex &&
            lauf -> u.ton_komplex.bezugston [0] == '@' ) {
            return 0;
        }
        lauf = lauf -> next;
    }
    return 1;
}

*/



/******** Haupt-Expandier-Routine **************/


typedef int * intptr;

static intptr get_cache_konstante (mutabor_box_type * box, int wert)
{

        struct constant_memory ** lauf;

        for (lauf = & box->file->list_of_constants; *lauf; lauf = & (*lauf)->next) {
        if ((*lauf)->constant == wert)
		        return & (*lauf)->constant;
        }

        *lauf = (struct constant_memory*) xmalloc (box, sizeof (struct constant_memory));
        (*lauf)->constant = wert;
        (*lauf)->next = NULL;
        return & (*lauf)->constant;
}

static struct interpreter_parameter_list * 
gen_parameter_liste (mutabor_box_type * box,
		     struct argument_liste * liste,
		     struct interpreter_parameter_list * bezugs_liste)
{

	struct interpreter_parameter_list * help;
	TRACE;

	if (liste == NULL)
		return NULL;

	help = (interpreter_parameter_list*) xmalloc (box, sizeof (struct interpreter_parameter_list));

	switch (liste->argument.argument_typ)
	{

	case zahl:
		help->value_field = get_cache_konstante (box,liste->argument.u.zahl.zahl);
		break;

	case parameter: {
		int i;

		struct interpreter_parameter_list * lauf;

		for (lauf = bezugs_liste, i=liste->argument.u.parameter.parameter_nummer;
		     lauf && i;
		     lauf = lauf -> next, i--)
			;

		if (lauf)
			help->value_field = lauf -> value_field;
		else
			mutabor_error_message(box,
					      false,
					      _("Unknown parameter number %d detected at \n%s:%d."),
					      liste->argument.u.parameter.parameter_nummer,
					      _T(__FILE__), 
					      __LINE__ );
	}

		break;

	default:
		mutabor_error_message(box,
				      false,
				      _("Unknown argument type %d detected at \n%s:%d."),
				      liste->argument.argument_typ,
				      _T(__FILE__), 
				      __LINE__ );
		
		break;
	}

	help->next = gen_parameter_liste (box,liste->next, bezugs_liste);

	return help;
}

static int * get_wert_of_argument (mutabor_box_type * box,
				   struct argument * argument,
				   struct interpreter_parameter_list * aktuelle_parameter)
{
	TRACE;
	switch (argument->argument_typ)
	{

	case zahl:
		return get_cache_konstante (box,argument->u.zahl.zahl);

		/*    break; */

	case parameter: {

		struct interpreter_parameter_list * lauf;
		int i;

		for (lauf=aktuelle_parameter, i=argument->u.parameter.parameter_nummer;
		                lauf && i;
		                lauf = lauf -> next, i--)
			;

		if (lauf)
			return lauf->value_field;
		else {
			mutabor_error_message(box,
					      false,
					      _("Unknown parameter number %d detected at \n%s:%d."),
					      argument->u.parameter.parameter_nummer,
					      _T(__FILE__), 
					      __LINE__ );
			return NULL;
		}
	}

	/*    break; */

	default:
		mutabor_error_message(box,
				      false,
				      _("Unknown argument type %d detected at \n%s:%d."),
				      argument->argument_typ,
				      _T(__FILE__), 
				      __LINE__ );

		return NULL;

		/*    break; */
	}

}


static struct ton_einstell * expand_tonliste (mutabor_box_type * box,
					      struct ton * the_tonliste)
{

	struct ton_einstell * help;
	TRACE;

	if (the_tonliste == NULL) return NULL;

	help = (ton_einstell*) xmalloc (box, sizeof (struct ton_einstell));

	switch (the_tonliste -> ton_typ)
	{

	case ton_absolut:
		if (the_tonliste->name) {
			help -> ton_einstell_typ = einstell_absolut;
			help -> u.einstell_absolut.wert =
			        DOUBLE_TO_LONG (
			                FREQUENZ_TO_MIDI(
			                        the_tonliste->u.ton_absolut.ton_wert));
		} else {
			help -> ton_einstell_typ = einstell_stumm;
		}

		break;

	case ton_komplex:
		if (the_tonliste->name == NULL) {
			help -> ton_einstell_typ = einstell_stumm;
		} else
			if ( ! strcasecmp (the_tonliste->name, "@")) {
				if (the_tonliste->u.ton_komplex.komplex_liste) {
					help -> ton_einstell_typ = einstell_relativ;
					help -> u.einstell_relativ.wert =
					        DOUBLE_TO_LONG (
					                FAKTOR_TO_MIDI (
									get_komplex_faktor (box, the_tonliste->u.ton_komplex.komplex_liste)));
				} else {
					help -> ton_einstell_typ = einstell_gleich;
				}
			} else { /* normaler ton */
				help -> ton_einstell_typ = einstell_absolut;
				help -> u.einstell_absolut.wert =
				        DOUBLE_TO_LONG (
				                FREQUENZ_TO_MIDI (
								  get_komplex_frequenz (box,the_tonliste)));

			}

		break;
	default:
		mutabor_error_message(box,
				      false,
				      _("Unknown tone type %d detected at\n%s:%d"),
				      the_tonliste -> ton_typ,
				      __FILE__, __LINE__);

	}

	help -> next = expand_tonliste (box, the_tonliste -> next);

	return help;


}


static struct do_aktion * expandiere_tonsystem (mutabor_box_type * box,
						struct tonsystem * the_tonsystem)
{

	struct do_aktion * help;
	tone_system * help_tonsystem;
	TRACE;

	help = (do_aktion*) xmalloc (box, sizeof (struct do_aktion));
	help -> name = the_tonsystem -> name;
	help -> aufruf_typ = aufruf_tonsystem;

	help_tonsystem = (TSYS*) xmalloc (box, sizeof (tone_system));
	help_tonsystem -> anker = the_tonsystem -> taste;
	help_tonsystem -> breite = ton_list_laenge (the_tonsystem -> toene);
	help_tonsystem -> periode =
	        DOUBLE_TO_LONG (
	                FAKTOR_TO_MIDI (
					get_wert_komplex_intervall (box,
								    the_tonsystem -> periode)));

	{

		struct ton * ton_lauf;
		int i;

		for (ton_lauf = the_tonsystem -> toene , i = 0 ;
		                ton_lauf;
		                ton_lauf = ton_lauf -> next , i++ ) {
			if (ton_lauf->name) {
				help_tonsystem->ton[i] =
				        DOUBLE_TO_LONG( FREQUENZ_TO_MIDI(get_ton (box,
										  ton_lauf -> name, 
										  box->file->list_of_toene)
				                                -> u.ton_absolut.ton_wert));
			} else {
				help_tonsystem->ton[i] = 0 ;
			}
		}
	}

	help -> u.aufruf_tonsystem.tonsystem = help_tonsystem;
	help -> next = NULL;

	return help;
}


static struct do_aktion * expandiere_logik (mutabor_box_type * box,
					    struct logik * the_logik)
{
	mutASSERT(the_logik != NULL);

	struct do_aktion * help;
	int i;
	TRACE;

	help = (do_aktion*) xmalloc (box, sizeof (struct do_aktion));
	help -> name = the_logik -> name;
	help -> aufruf_typ = aufruf_logik;
	help -> u.aufruf_logik.logic = the_logik;

	if (the_logik -> einstimmungs_name &&
	    the_logik -> einstimmung == NULL )
	{
		struct tonsystem * help_tonsystem;
		struct umstimmung * help_umstimmung;

		/* Guard against circular expansion */
		the_logik -> einstimmung = (struct do_aktion *)NULL + 1;
		help_tonsystem = parser_get_tonsystem (the_logik->einstimmungs_name,
		                                       box->file->list_of_tonsysteme);
		if (help_tonsystem) {
			the_logik -> einstimmung = expandiere_tonsystem (box, help_tonsystem);
		} else {
			help_umstimmung = get_umstimmung (the_logik->einstimmungs_name,
			                                  box->file->list_of_umstimmungen);
			if (help_umstimmung) {
				the_logik -> einstimmung = expandiere_umstimmung (box, help_umstimmung, NULL);
			} else {
				mutabor_error_message(box,
						      false,
						      _("Unable to find the initial tuning or retuning ‘%s’"),
						      (the_logik->einstimmungs_name));
				/* reset the guard */
				/** \todo prevent multiple error messages. maybe use a dummy retuning */
				the_logik -> einstimmung = NULL;
			}
		}
	}
#if 0
	else
		help -> u.aufruf_logik.einstimmung = NULL;

	i = get_logik_nummer (box, the_logik -> name, box->file->list_of_logiken);

	help -> u.aufruf_logik.lokal_harmonie = & box->first_local_harmony [i];
	help -> u.aufruf_logik.lokal_keyboard = & box->first_local_keyboard [i];
	help -> u.aufruf_logik.lokal_midi     = & box->first_local_midi     [i];
#endif

	help -> next = NULL;

	/* fill the local trigger lists that describe the action of the current logic */
	if (the_logik->harmony_list == NULL &&
	    the_logik->keystroke_list == NULL &&
	    the_logik->midi_input_list == NULL) {
		for (struct anweisung * lauf_anweisung=the_logik->anweisungsliste;
		     lauf_anweisung;
		     lauf_anweisung=lauf_anweisung->next) {
			insert_in_lokale_liste (box, help, lauf_anweisung, the_logik);
		}
	}

	return help;
}

static struct do_aktion * expand_aktions_liste (mutabor_box_type * box,
						struct aktions_liste * the_liste,
						struct interpreter_parameter_list * aktuelle_parameter)
{

	struct do_aktion * help_1, * help_2, ** help_3;
	TRACE;

	if (the_liste == NULL) return NULL;
	
	switch (the_liste -> aktions_typ) {
	case aktion_aufruf:
		help_1 = expandiere_name (box,
					  the_liste -> u.aktion_aufruf.name,
		                          the_liste -> u.aktion_aufruf.argument_liste,
		                          aktuelle_parameter);
		break;
	case aktion_midi_out:
		help_1 = expandiere_midi (box, the_liste -> u.aktion_midi_out.midi_code);
		break;
	case aktion_harmony_analysis:
		help_1 = expand_harmony_analysis(box);
	default:
		mutabor_error_message(box,
				      false,
				      _("Unknown action type %d detected at\n%s:%d"),
				      the_liste -> aktions_typ,
				      __FILE__, __LINE__);
	}

	help_2 = expand_aktions_liste (box, the_liste -> next, aktuelle_parameter);

	for (help_3 = & help_1; * help_3; help_3 = & (*help_3)->next)
		;

	* help_3 = help_2;

	return help_1;

}


static struct case_element * expand_case_liste (mutabor_box_type * box,
						struct case_liste * the_liste,
						struct interpreter_parameter_list * aktuelle_parameter)
{
	TRACE;

	struct case_element * start_liste = NULL;
	struct case_element ** ende_liste = & start_liste;
	struct case_liste * lauf_liste;

	for (lauf_liste = the_liste; lauf_liste; lauf_liste = lauf_liste -> next)
	{
		if ( ! lauf_liste -> is_default ) {

			*ende_liste = (case_element*) xmalloc (box, sizeof (struct case_element));
			(*ende_liste) -> case_wert = lauf_liste -> case_label;
			(*ende_liste) -> is_default = 0;
			(*ende_liste) -> case_aktion =
			        expand_aktions_liste (box,
						      lauf_liste -> case_aktion,
						      aktuelle_parameter);
			(*ende_liste) -> next = NULL;
			ende_liste = & (*ende_liste) -> next;
		}
	}

	for (lauf_liste = the_liste; lauf_liste; lauf_liste = lauf_liste -> next)
	{
		if ( lauf_liste -> is_default ) {

			*ende_liste = (case_element*) xmalloc (box, sizeof (struct case_element));
			(*ende_liste) -> case_wert = lauf_liste -> case_label;
			(*ende_liste) -> is_default = 1;
			(*ende_liste) -> case_aktion =
			        expand_aktions_liste (box,
						      lauf_liste -> case_aktion,
						      aktuelle_parameter);
			(*ende_liste) -> next = NULL;
			ende_liste = & (*ende_liste) -> next;
		}
	}

	return start_liste;
}


static struct do_aktion * expandiere_umstimmung (mutabor_box_type * box,
						 struct umstimmung * the_umstimmung,
						 struct interpreter_parameter_list * aktuelle_parameter)
{

	struct do_aktion * help;
	TRACE;

	help = (do_aktion*) xmalloc (box, sizeof (struct do_aktion));
	help -> name = the_umstimmung -> name;

	switch (the_umstimmung -> umstimmung_typ)
	{

	case umstimmung_taste_abs:
		TRACE;
		help -> aufruf_typ = aufruf_umst_taste_abs;

		help -> u.aufruf_umst_taste_abs.keynr =
		        get_wert_of_argument (box,
					      & the_umstimmung->u.umstimmung_taste_abs.argument,
					      aktuelle_parameter);

		help -> next = NULL;

		return help;

		/*        break; */

	case umstimmung_breite_abs:
		TRACE;
		help -> aufruf_typ = aufruf_umst_breite_abs;

		help -> u.aufruf_umst_breite_abs.width =
		        get_wert_of_argument (box,
					      & the_umstimmung->u.umstimmung_breite_abs.argument,
					      aktuelle_parameter);

		help -> next = NULL;

		return help;

		/*        break; */

	case umstimmung_wiederholung_abs:
		TRACE;
		help -> aufruf_typ = aufruf_umst_wiederholung_abs;

		help -> u.aufruf_umst_wiederholung_abs.faktor =
		        DOUBLE_TO_LONG (
		                FAKTOR_TO_MIDI (
						get_wert_komplex_intervall (box,
									    the_umstimmung->u.umstimmung_wiederholung_abs.komplex_liste)));

		help -> next = NULL;

		return help;

		/*        break; */

	case umstimmung_wiederholung_rel:
		TRACE;
		help -> aufruf_typ = aufruf_umst_wiederholung_rel;

		help -> u.aufruf_umst_wiederholung_rel.faktor =
		        DOUBLE_TO_LONG (
		                FAKTOR_TO_MIDI (
						get_wert_komplex_intervall (box,
									    the_umstimmung->u.umstimmung_wiederholung_abs.komplex_liste)));

		help -> next = NULL;

		return help;

		/*        break; */

	case umstimmung_taste_rel:
		TRACE;
		help -> aufruf_typ = aufruf_umst_taste_rel;

		help -> u.aufruf_umst_taste_rel.distance =
		        get_wert_of_argument ( box,
					       & the_umstimmung->u.umstimmung_taste_rel.argument,
		                               aktuelle_parameter);

		help -> u.aufruf_umst_taste_rel.rechenzeichen = the_umstimmung->u.umstimmung_taste_rel.rechenzeichen;

		help -> next = NULL;

		return help;

		/*        break; */

	case umstimmung_breite_rel:
		TRACE;
		help -> aufruf_typ = aufruf_umst_breite_rel;

		help -> u.aufruf_umst_breite_rel.difference =
		        get_wert_of_argument ( box,
					       & the_umstimmung->u.umstimmung_breite_rel.argument,
		                               aktuelle_parameter);

		help -> u.aufruf_umst_breite_rel.rechenzeichen = the_umstimmung->u.umstimmung_breite_rel.rechenzeichen;

		help -> next = NULL;

		return help;

		/*        break; */

	case umstimmung_toene_veraendert:
		TRACE;
		help -> aufruf_typ = aufruf_umst_toene_veraendert;

		help -> u.aufruf_umst_toene_veraendert.tonliste =
		        expand_tonliste (box, the_umstimmung->u.umstimmung_toene_veraendert.tonliste);

		help -> next = NULL;

		return help;

		/*        break; */

	case umstimmung_umstimmungsbund:
		TRACE;
		/* Technically we could omit the initial action, but then we also lose the name of the 
		   compound, which is needed elsewhere. */
		help -> next = expand_aktions_liste (box,
						     the_umstimmung->u.umstimmung_umstimmungsbund.aktions_liste,
						     aktuelle_parameter);

		if (help->name && help->name[0]) {
			help -> aufruf_typ = aufruf_umst_umst_bund;
		} else {
			help = help->next;
			xfree(help);
		}
		return help;

		/*        break; */

	case umstimmung_umstimmungs_case:
		TRACE;
		help -> aufruf_typ = aufruf_umst_umst_case;

		help -> u.aufruf_umst_umst_case.choice =
		        get_wert_of_argument ( box,
					       & the_umstimmung->u.umstimmung_umstimmungs_case.argument,
		                               aktuelle_parameter);

		help -> u.aufruf_umst_umst_case.umst_case =
		        expand_case_liste (box,
					   the_umstimmung->u.umstimmung_umstimmungs_case.umstimmungs_case_liste,
		                           aktuelle_parameter);

		help -> next = NULL;

		return help;

		/*        break; */

	case umstimmung_midi_out:
		TRACE;
		help -> aufruf_typ = aufruf_midi_out;

		help -> u.aufruf_midi_out.out_liste =
		        the_umstimmung->u.umstimmung_midi_out.out_liste;

		help -> next = NULL;
		return help;

		/*        break; */

	default:
		mutabor_error_message(box,
				      false,
				      _("Unknown retuning type %d detected at\n%s:%d"),
				      the_umstimmung -> umstimmung_typ,
				      __FILE__, __LINE__);
		return NULL;

	}
}



static struct do_aktion * expandiere_name (mutabor_box_type * box,
					   const char * name,
					   struct argument_liste * parameter,
					   struct interpreter_parameter_list * bezugs_liste)
{
	struct logik * help_logik;
	struct tonsystem * help_tonsystem;
	struct umstimmung * help_umstimmung;
	TRACE;


	if (name == NULL) return NULL;


	help_logik = get_logik (name, box->file->list_of_logiken);

	if (help_logik)
	{
		return expandiere_logik (box,help_logik);

	} else
	{

		help_tonsystem = parser_get_tonsystem (name, box->file->list_of_tonsysteme);

		if (help_tonsystem) {
			

			return expandiere_tonsystem (box,help_tonsystem);

		} else {

			help_umstimmung = get_umstimmung (name, box->file->list_of_umstimmungen);

			if (help_umstimmung) {

				struct interpreter_parameter_list * aktuelle_parameter;
				aktuelle_parameter = gen_parameter_liste (box, parameter, bezugs_liste);
				return expandiere_umstimmung (box,
							      help_umstimmung,
				                              aktuelle_parameter);

			} else
				/** \todo check that the conversion succeeds always */
				mutabor_error_message(box,
						      false,
						      _("Unknown tuning or logic ‘%s’"),
						      name,
						      __FILE__, __LINE__);

			return NULL;
		}
	}

}

static struct do_aktion * expandiere_midi (mutabor_box_type * box, struct midiliste * liste)
{

	struct do_aktion * help;
	TRACE;

	help = (do_aktion*) xmalloc (box, sizeof (struct do_aktion));
	help -> name = _("MIDI out");
	help -> aufruf_typ = aufruf_midi_out;
	help -> u.aufruf_midi_out.out_liste = liste;
	help -> next = NULL;

	return help;
}

static struct do_aktion * expand_harmony_analysis(mutabor_box_type * box) 
{

	struct do_aktion * help;
	TRACE;

	help = (do_aktion*) xmalloc (box, sizeof (struct do_aktion));
	help -> name = _("harmony analysis");
	help -> aufruf_typ = aufruf_harmony_analysis;
	help -> next = NULL;

	return help;
}

static int * create_midi_scan_liste (mutabor_box_type * box, struct midiliste * lauf)
{
	int j, k, * ret;
	TRACE;

	j = midi_list_laenge (lauf);

	ret = (int*) xcalloc(box, (size_t)(j+1), sizeof(int));

	for (k=0; lauf; lauf=lauf->next, k++)
		ret [k] = lauf->midi_code;

	ret [k] = -1;

	return ret;
}

 PATTERNN * expand_pattern (mutabor_box_type * box, const char * harmonie_name)

{

	struct harmonie * the_harmonie;
	PATTERNN * help;
	int i;

	struct taste * lauf_taste;
	TRACE;

	the_harmonie = get_harmonie (harmonie_name, box->file->list_of_harmonien);

	if (the_harmonie == NULL) {
		mutabor_error_message(box,
				      false,
				      _("Harmony ‘%s’ could not be found."),
				      harmonie_name);
	}

	help = (PTRN*) xmalloc (box, sizeof (PATTERNN));

	for (i=0;i<MUTABOR_KEYRANGE_MAX_WIDTH;i++) help->tonigkeit[i]=1; /* Off */

	for (lauf_taste = the_harmonie->tastenliste;
	                lauf_taste;
	                lauf_taste = lauf_taste -> next) {
		if (lauf_taste->stern=='*')
			help->tonigkeit[lauf_taste->code]=0; /* Egal */
		else
			help->tonigkeit[lauf_taste->code]=2; /* On */
	}

	return help;
}


void insert_in_globale_liste (mutabor_box_type * box, struct logik * lauf)

{

	struct harmonie_ereignis ** temp_harmonie;
	struct keyboard_ereignis ** temp_keyboard;
	struct midi_ereignis     ** temp_midi;

	TRACE;
	mutASSERT(lauf && lauf != NULL);

	if (lauf->ausloeser)
	{
		switch ((lauf->ausloeser)->ausloeser_typ) {

		case ausloeser_harmonie:
			TRACE;
			if (lauf->ausloeser->u.ausloeser_harmonie.vortaste == MUTABOR_INVALID_KEY)
				/* Dann unmöglicher Harmonieauslöser */
				break;

			/* Neuen Eintrag erzeugen */
			for (temp_harmonie = &box->file->global_harmonies;
			     *temp_harmonie;
			     temp_harmonie = & (*temp_harmonie)->next);

			*temp_harmonie = (harmonie_ereignis*) xmalloc(box, (size_t)sizeof(struct harmonie_ereignis));

			(*temp_harmonie) -> pattern=expand_pattern (box, 
								    (lauf->ausloeser)->u.ausloeser_harmonie.name) ;
			(*temp_harmonie) -> ist_harmonieform=mutabor_is_no_harmonic_form;
			(*temp_harmonie) -> vortaste=(lauf->ausloeser)->u.ausloeser_harmonie.vortaste ;
			(*temp_harmonie) -> nachtaste=(lauf->ausloeser)->u.ausloeser_harmonie.nachtaste ;
			(*temp_harmonie) -> name=lauf->name;
			(*temp_harmonie) -> aktion=NULL;
			(*temp_harmonie) -> the_logik_to_expand=lauf;
			(*temp_harmonie) -> next=NULL;
			break;

		case ausloeser_harmonie_form:
			TRACE;
			if (lauf->ausloeser->u.ausloeser_harmonie_form.vortaste == MUTABOR_INVALID_KEY)
				/* Dann unmöglicher Harmonieauslöser */
				break;

			/* Neuen Eintrag erzeugen */
			for (temp_harmonie = & box->file->global_harmonies;
			     *temp_harmonie;
			     temp_harmonie = & (*temp_harmonie)->next) ;

			*temp_harmonie  = (harmonie_ereignis*) xmalloc(box, (size_t)sizeof(struct harmonie_ereignis));
			(*temp_harmonie) -> pattern=expand_pattern (box,
								    (lauf->ausloeser)->u.ausloeser_harmonie_form.name) ;
			(*temp_harmonie) -> ist_harmonieform=mutabor_is_harmonic_form;
			(*temp_harmonie) -> vortaste=(lauf->ausloeser)->u.ausloeser_harmonie_form.vortaste ;
			(*temp_harmonie) -> nachtaste=(lauf->ausloeser)->u.ausloeser_harmonie_form.nachtaste ;
			(*temp_harmonie) -> name=lauf->name;
			(*temp_harmonie) -> aktion=NULL;
			(*temp_harmonie) -> the_logik_to_expand=lauf;
			(*temp_harmonie) -> next=NULL;

			break;

		case ausloeser_taste:
			TRACE;
			/* Neuen Eintrag erzeugen */
			for (temp_keyboard = & box->file->global_keystrokes;
			     *temp_keyboard;
			     temp_keyboard = & (*temp_keyboard)->next) ;

			*temp_keyboard  = (keyboard_ereignis*) xmalloc(box, (size_t)sizeof(struct keyboard_ereignis));
			(*temp_keyboard) -> taste= (*((lauf->ausloeser)->u.ausloeser_taste.taste)) ;
			(*temp_keyboard) -> name=lauf->name;
			(*temp_keyboard) -> aktion=NULL;
			(*temp_keyboard) -> the_logik_to_expand=lauf;
			(*temp_keyboard) -> next=NULL;
			break;

		case ausloeser_midi_in:
			TRACE;
			/* Neuen Eintrag erzeugen */
			for (temp_midi = & box->file->global_midi_inputs;
			     *temp_midi;
			     temp_midi = & (*temp_midi)->next) ;

			*temp_midi  = (midi_ereignis*) xmalloc(box, (size_t)sizeof(struct midi_ereignis));

			/* Werte eintragen */

			(*temp_midi) -> first_pos =
			        (*temp_midi) -> scan_pos =
				create_midi_scan_liste (box, lauf->ausloeser->u.ausloeser_midi_in.midi_code);
			(*temp_midi) -> name = lauf->name;
			(*temp_midi) -> aktion=NULL;
			(*temp_midi) -> the_logik_to_expand=lauf;
			(*temp_midi) -> next = NULL;
			break;

		default:
			TRACE;
			mutabor_error_message(box,
					      false,
					      _("Unknown event type %d detected at\n%s:%d"),
					      (lauf->ausloeser)->ausloeser_typ,
					      __FILE__, __LINE__);
		}
	}
}

void insert_in_lokale_liste (mutabor_box_type * box,
			     struct do_aktion * action,
			     struct anweisung * lauf,
                             struct logik * logic)
{
	struct harmonie_ereignis ** temp_harmonie;
	struct keyboard_ereignis ** temp_keyboard;
	struct midi_ereignis     ** temp_midi;
	TRACE;

	if (lauf->ausloeser)
	{
		switch ((lauf->ausloeser)->ausloeser_typ) {

		case ausloeser_harmonie:
			TRACE;
			if (lauf->ausloeser->u.ausloeser_harmonie.vortaste == MUTABOR_INVALID_KEY)
				/* Dann unmöglicher Harmonieauslöser */
				break;

			/* Neuen Eintrag erzeugen */
			for (temp_harmonie = & logic->harmony_list;
			     *temp_harmonie != NULL;
			     temp_harmonie = & (*temp_harmonie)->next);

			*temp_harmonie = (harmonie_ereignis*) xmalloc(box, (size_t)sizeof(struct harmonie_ereignis));

			(*temp_harmonie) -> pattern =expand_pattern (box,
								     (lauf->ausloeser)->u.ausloeser_harmonie.name) ;
			(*temp_harmonie) -> ist_harmonieform=mutabor_is_no_harmonic_form;
 			(*temp_harmonie) -> vortaste=(lauf->ausloeser)->u.ausloeser_harmonie.vortaste ;
			(*temp_harmonie) -> nachtaste=(lauf->ausloeser)->u.ausloeser_harmonie.nachtaste ;
			(*temp_harmonie) -> name = logic->name;
			(*temp_harmonie) -> aktion=
			        expand_aktions_liste (box,lauf->aktion, box->start_parameter_list);

			(*temp_harmonie) -> next=NULL;

			break;

		case ausloeser_harmonie_form:
			TRACE;
			if (lauf->ausloeser->u.ausloeser_harmonie_form.vortaste == MUTABOR_INVALID_KEY)
				/* Dann unmöglicher Harmonieauslöser */
				break;

			/* Neuen Eintrag erzeugen */
			for (temp_harmonie = & logic->harmony_list;
			     *temp_harmonie != NULL;
			     temp_harmonie = & (*temp_harmonie)->next);

			*temp_harmonie  = (harmonie_ereignis*) xmalloc(box, (size_t)sizeof(struct harmonie_ereignis));
			(*temp_harmonie) -> pattern=expand_pattern (box,
								    (lauf->ausloeser)->u.ausloeser_harmonie_form.name) ;
			(*temp_harmonie) -> ist_harmonieform=mutabor_is_harmonic_form;
			(*temp_harmonie) -> vortaste=(lauf->ausloeser)->u.ausloeser_harmonie_form.vortaste ;
			(*temp_harmonie) -> nachtaste=(lauf->ausloeser)->u.ausloeser_harmonie_form.nachtaste ;
			(*temp_harmonie) -> name=logic->name;
			(*temp_harmonie) -> aktion=
			        expand_aktions_liste (box,lauf->aktion, box->start_parameter_list);
			(*temp_harmonie) -> next=NULL;
			break;

		case ausloeser_default:
			TRACE;
			/* Neuen Eintrag erzeugen */
			for (temp_harmonie = & logic->harmony_list;
			     *temp_harmonie != NULL;
			     temp_harmonie = & (*temp_harmonie)->next)
				;

			*temp_harmonie  = (harmonie_ereignis*) xmalloc(box, (size_t)sizeof(struct harmonie_ereignis));
			(*temp_harmonie) -> pattern=NULL ;
			(*temp_harmonie) -> ist_harmonieform=mutabor_is_else_path;
			(*temp_harmonie) -> vortaste=0 ;
			(*temp_harmonie) -> nachtaste=0 ;
			(*temp_harmonie) -> name=logic->name;
			(*temp_harmonie) -> aktion=
			        expand_aktions_liste (box,lauf->aktion, box->start_parameter_list);
			(*temp_harmonie) -> next=NULL;

			break;

		case ausloeser_taste:
			TRACE;
			/* Neuen Eintrag erzeugen */
			for (temp_keyboard = & logic->keystroke_list;
			     *temp_keyboard != NULL;
			     temp_keyboard = & (*temp_keyboard)->next)
				;

			*temp_keyboard  = (keyboard_ereignis*) xmalloc(box, (size_t)sizeof(struct keyboard_ereignis));
			(*temp_keyboard) -> taste= (*((lauf->ausloeser)->u.ausloeser_taste.taste)) ;
			(*temp_keyboard) -> name=logic->name;
			(*temp_keyboard) -> aktion=
			        expand_aktions_liste (box,lauf->aktion, box->start_parameter_list);
			(*temp_keyboard) -> next=NULL;

			break;

		case ausloeser_midi_in:
			TRACE;
			/* Neuen Eintrag erzeugen */
			for (temp_midi = & logic->midi_input_list;
			     *temp_midi != NULL;
			     temp_midi = & (*temp_midi)->next);

			*temp_midi  = (midi_ereignis*) xmalloc(box, (size_t)sizeof(struct midi_ereignis));
			/* Werte eintragen */
			(*temp_midi) -> first_pos =
			        (*temp_midi) -> scan_pos =
				create_midi_scan_liste (box, lauf->ausloeser->u.ausloeser_midi_in.midi_code);
			(*temp_midi) -> name = logic->name;
			(*temp_midi) -> aktion=
			        expand_aktions_liste (box,lauf->aktion, box->start_parameter_list);
			(*temp_midi) -> next = NULL;
			break;

		default:
			TRACE;
			mutabor_error_message(box,
					      false,
					      _("Unknown event type %d detected at\n%s:%d"),
					      (lauf->ausloeser)->ausloeser_typ,
					      __FILE__, __LINE__);
		}
	}
}


static void expandiere_in_globale_liste (mutabor_box_type * box)
{

	struct harmonie_ereignis * lauf_harmonie;
	struct keyboard_ereignis * lauf_keyboard;
	struct midi_ereignis     * lauf_midi    ;
	//int i;
	
	TRACE;

	lauf_harmonie = box->file->global_harmonies;
	while (lauf_harmonie) {
		mutASSERT(lauf_harmonie);
		DEBUGLOG2(kernel_tabgen,_T("lauf_harmonie(=%p)->the_logic_to_expand = %p"),
			  (void*)lauf_harmonie,(void*)lauf_harmonie -> the_logik_to_expand);
		lauf_harmonie -> aktion =
			expandiere_logik (box,lauf_harmonie -> the_logik_to_expand);
//			lauf_harmonie -> aktion = lauf_harmonie[i] -> aktion;

		lauf_harmonie = lauf_harmonie -> next;
	}

	lauf_keyboard = box->file->global_keystrokes;
	while (lauf_keyboard) {
		lauf_keyboard -> aktion =
			expandiere_logik (box, lauf_keyboard -> the_logik_to_expand);
//			lauf_keyboard -> aktion = lauf_keyboard[i] -> aktion;

		lauf_keyboard = lauf_keyboard -> next;
	}



	lauf_midi = box->file->global_midi_inputs;
	while (lauf_midi) {
		lauf_midi -> aktion =
			expandiere_logik (box,lauf_midi -> the_logik_to_expand);
//			lauf_midi -> aktion = lauf_midi -> aktion;
		lauf_midi = lauf_midi -> next;
	}

}



#if 0
static struct harmonie_ereignis **
get_ende_harmonie (struct harmonie_ereignis ** lauf)
{
	TRACE;
	while(*lauf != NULL) lauf = & (*lauf)->next;
	return lauf;
}

static struct keyboard_ereignis **
get_ende_keyboard (struct keyboard_ereignis ** lauf)
{
	TRACE;
	while(*lauf != NULL) lauf = & (*lauf)->next;
	return lauf;
}

static struct midi_ereignis **
get_ende_midi (struct midi_ereignis ** lauf)
{
	TRACE;
	while(*lauf != NULL) lauf = & (*lauf)->next;
	return lauf;
}
#endif

/*==============================================================*/


void mutabor_tabellen_generator (mutabor_box_type * box)
{

	/** \todo find out the semantics of global and local lists */
	/** \todo combine the loops this depends on: */
	/** \todo ensure that the logics of the different boxes are independent */
	/* Ausgabe der Pointer-Setz-Prozeduren */

	struct logik * lauf;

	/*	struct anweisung * lauf_anweisung;
	int i, j;
	*/
	TRACE;

#if 0
	box->first_harmony = NULL;
	box->last_global_harmony = NULL;
	box->first_local_harmony = NULL;
	box->first_keyboard = NULL;
	box->last_global_keyboard = NULL;
	box->first_local_keyboard = NULL;
	box->first_midi = NULL;
	box->last_global_midi = NULL;
	box->first_local_midi = NULL;
#endif

	/* so far we do not mix logics so we assure that the global lists are properly cleared */
	mutASSERT(box->file->global_harmonies == NULL);
	mutASSERT(box->file->global_keystrokes == NULL);
	mutASSERT(box->file->global_midi_inputs == NULL);


	/* Die globalen Listen werden initialisiert: */
	/* Die globalen Auslöser werden in die vorbereiteten Listen eingetragen: */

	for (lauf = box->file->list_of_logiken; lauf; lauf = lauf -> next) {
		insert_in_globale_liste (box, lauf);
	}

#if 0
	box->last_global_harmony  = get_ende_harmonie (& box->first_harmony);
	box->last_global_keyboard = get_ende_keyboard (& box->first_keyboard);
	box->last_global_midi     = get_ende_midi     (& box->first_midi);

	/* Die lokalen Listen werden erzeugt: */
	/* Es wird ein Array mit Anfangszeigern  auf die lokalen
	   Auslöser angelegt. Die Nummer der Logik ist index */

	i = logik_list_laenge (box->file->list_of_logiken);

	/* important: calloc must clear all data (fill with 0 */
	box->first_local_harmony  = (harmonie_ereignis* *) xcalloc (box, (size_t)i, sizeof(harmonie_ereignis *));
	box->first_local_keyboard = (keyboard_ereignis* *) xcalloc (box, (size_t)i, sizeof(keyboard_ereignis *));
	box->first_local_midi     = (midi_ereignis* *)     xcalloc (box, (size_t)i, sizeof(midi_ereignis *));

	/* ensure compatibility with original code */
	mutASSERT(sizeof(box->first_local_harmony[0])  == sizeof(harmonie_ereignis *));
	mutASSERT(sizeof(box->first_local_keyboard[0]) == sizeof(keyboard_ereignis *));
	mutASSERT(sizeof(box->first_local_midi[0])     == sizeof(midi_ereignis *));

	/* this must be somehow separated from insert_in_globale_liste to prevent endless loops */
	for (lauf=box->file->list_of_logiken, i=0;
	     lauf;
	     lauf=lauf->next, i++ ) {

		for (lauf_anweisung=lauf->anweisungsliste;
		     lauf_anweisung;
		     lauf_anweisung=lauf_anweisung->next) {
			insert_in_lokale_liste (box, i, lauf_anweisung, lauf->name);
		}
	}
#endif
	
	expandiere_in_globale_liste (box);

} /* end of mutabor_tabellen_generator */



#ifdef __cplusplus
		}
	}
}
#endif

///\}
