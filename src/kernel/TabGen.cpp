/** \file 
 ********************************************************************
 * Table genarator
 *
 * Copyright:   (c) 1997-2008 TU Dresden
 * \author  
 * R.Krauße
 * Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 
 * $Date: 2011/10/13 18:26:13 $
 * \version $Revision: 1.7 $
 * \license GPL
 *
 *
 *
 ********************************************************************
 * \addtogroup kernel
 * \{
 ********************************************************************/

#include "Global.h"
#include "Interpre.h"
#include "GrafKern.h"
//#include "MidiKern.h"
#include <math.h>

/*** Das sind die Anfangslisten des Interpreters **/


struct harmonie_ereignis ** first_lokal_harmonie;
struct keyboard_ereignis ** first_lokal_keyboard;
struct midi_ereignis     ** first_lokal_midi;

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

static do_aktion*  expandiere_midi (struct midiliste * liste);


/**************************************************/



double get_komplex_faktor (struct komplex_intervall * lauf)
{
	double ret = 1.0;
	TRACE;

	for ( ; lauf ; lauf = lauf -> next )
	{

		struct intervall * help = get_intervall (lauf->name, list_of_intervalle);

		if (help && help -> intervall_typ == intervall_absolut) {
			ret *= pow (help -> u.intervall_absolut.intervall_wert,
			            lauf->faktor);
		} else {
			fatal_error (0, __FILE__, __LINE__);
		}

	}

	return ret;
}


double get_komplex_frequenz (struct ton * dieser)
{
	double ret = get_ton (dieser->u.ton_komplex.bezugston, list_of_toene)
	             -> u.ton_absolut.ton_wert;
	ret *= get_komplex_faktor (dieser->u.ton_komplex.komplex_liste);
	return ret;
}


void fprint_argument (FILE * zieldatei, struct argument * argument)
{
	TRACE;
	if (argument -> argument_typ == zahl)
	{
		fprintf (zieldatei, ", %d ", argument -> u.zahl.zahl);
	} else if (argument -> argument_typ == parameter)
	{
		fprintf (zieldatei, ", %s ", argument -> u.parameter.parameter_name);
	} else
		fatal_error (0, __FILE__, __LINE__ );
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


#if 0
/***** Diese Zweielementige Liste ist Parameterliste bei Logiken */

static struct interpreter_parameter_liste zentrums_knoten =
        {
	        & laufzeit_zentrum, NULL
        };

static struct interpreter_parameter_liste abstands_knoten =
        {
	        & laufzeit_abstand, & zentrums_knoten
        };

struct interpreter_parameter_liste * start_parameter_liste =
			        & abstands_knoten;
#endif

typedef int * intptr;

static intptr get_cache_konstante (mutabor_box_type * box, int wert)
{

        struct cache_konstanten ** lauf;
        int i;

        for (lauf = & box->cache_konstanten; *lauf; lauf = & (*lauf)->next) {
        if ((*lauf)->konstante == wert)
		        return & (*lauf)->konstante;
        }

        *lauf = (struct cache_konstanten*) xmalloc (sizeof (struct cache_konstanten));
        (*lauf)->konstante = wert;
        (*lauf)->next = NULL;
        return & (*lauf)->konstante;
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

	help = (interpreter_parameter_list*) xmalloc (sizeof (struct interpreter_parameter_list));

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
			fatal_error (0, __FILE__, __LINE__);
	}

		break;

	default:
		fatal_error (0, __FILE__, __LINE__);

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
			fatal_error (0, __FILE__, __LINE__);
			return NULL;
		}
	}

	/*    break; */

	default:
		fatal_error (0, __FILE__, __LINE__);

		return NULL;

		/*    break; */
	}

}


static struct ton_einstell * expand_tonliste (struct ton * the_tonliste)
{

	struct ton_einstell * help;
	TRACE;

	if (the_tonliste == NULL) return NULL;

	help = (ton_einstell*) xmalloc (sizeof (struct ton_einstell));

	switch (the_tonliste -> ton_typ)
	{

	default:
		fatal_error (0, __FILE__, __LINE__);

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
			if ( ! strcmp (the_tonliste->name, "@")) {
				if (the_tonliste->u.ton_komplex.komplex_liste) {
					help -> ton_einstell_typ = einstell_relativ;
					help -> u.einstell_relativ.wert =
					        DOUBLE_TO_LONG (
					                FAKTOR_TO_MIDI (
					                        get_komplex_faktor (the_tonliste->u.ton_komplex.komplex_liste)));
				} else {
					help -> ton_einstell_typ = einstell_gleich;
				}
			} else { /* normaler ton */
				help -> ton_einstell_typ = einstell_absolut;
				help -> u.einstell_absolut.wert =
				        DOUBLE_TO_LONG (
				                FREQUENZ_TO_MIDI (
				                        get_komplex_frequenz (the_tonliste)));

			}

		break;
	}

	help -> next = expand_tonliste (the_tonliste -> next);

	return help;


}


static struct do_aktion * expandiere_tonsystem (

			        struct tonsystem * the_tonsystem)
{

	struct do_aktion * help;
	tone_system * help_tonsystem;
	TRACE;

	help = (do_aktion*) xmalloc (sizeof (struct do_aktion));
	help -> name = the_tonsystem -> name;
	help -> aufruf_typ = aufruf_tonsystem;

	help_tonsystem = (TSYS*) xmalloc (sizeof (tone_system));
	help_tonsystem -> anker = the_tonsystem -> taste;
	help_tonsystem -> breite = ton_list_laenge (the_tonsystem -> toene);
	help_tonsystem -> periode =
	        DOUBLE_TO_LONG (
	                FAKTOR_TO_MIDI (
	                        get_wert_komplex_intervall (
	                                the_tonsystem -> periode)));

	{

		struct ton * ton_lauf;
		int i;

		for (ton_lauf = the_tonsystem -> toene , i = 0 ;
		                ton_lauf;
		                ton_lauf = ton_lauf -> next , i++ ) {
			if (ton_lauf->name) {
				help_tonsystem->ton[i] =
				        DOUBLE_TO_LONG( FREQUENZ_TO_MIDI(
				                                get_ton (
				                                        ton_lauf -> name, list_of_toene)
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

	struct do_aktion * help;
	int i;
	TRACE;

	help = (do_aktion*) xmalloc (sizeof (struct do_aktion));
	help -> name = the_logik -> name;
	help -> aufruf_typ = aufruf_logik;

	if (the_logik -> einstimmungs_name)
	{

		struct tonsystem * help_tonsystem;

		struct umstimmung * help_umstimmung;
		help_tonsystem = parser_get_tonsystem (the_logik->einstimmungs_name,
		                                       list_of_tonsysteme);

		if (help_tonsystem) {
			help -> u.aufruf_logik.einstimmung = expandiere_tonsystem (help_tonsystem);
		} else {
			help_umstimmung = get_umstimmung (the_logik->einstimmungs_name,
			                                  list_of_umstimmungen);

			if (help_umstimmung) {
				help -> u.aufruf_logik.einstimmung = expandiere_umstimmung (box, help_umstimmung, NULL);
			} else {
				fatal_error (0, __FILE__, __LINE__);
				help -> u.aufruf_logik.einstimmung = NULL;
			}
		}
	} else
		help -> u.aufruf_logik.einstimmung = NULL;

	i = get_logik_nummer (the_logik -> name, list_of_logiken);

	help -> u.aufruf_logik.lokal_harmonie = & first_lokal_harmonie [i];

	help -> u.aufruf_logik.lokal_keyboard = & first_lokal_keyboard [i];

	help -> u.aufruf_logik.lokal_midi     = & first_lokal_midi     [i];

	help -> next = NULL;

	return help;
}

static struct do_aktion * expand_aktions_liste (mutabor_box_type * box,
						struct aktions_liste * the_liste,
						struct interpreter_parameter_list * aktuelle_parameter)
{

	struct do_aktion * help_1, * help_2, ** help_3;
	TRACE;

	if (the_liste == NULL) return NULL;

	if (the_liste -> aktions_typ == aktion_aufruf)
	{
		help_1 = expandiere_name (box,
					  the_liste -> u.aktion_aufruf.name,
		                          the_liste -> u.aktion_aufruf.argument_liste,
		                          aktuelle_parameter);
	} else if (the_liste -> aktions_typ == aktion_midi_out)
	{
		help_1 = expandiere_midi (the_liste -> u.aktion_midi_out.midi_code);
	} else
		fatal_error (0, __FILE__, __LINE__);

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

			*ende_liste = (case_element*) xmalloc (sizeof (struct case_element));
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

			*ende_liste = (case_element*) xmalloc (sizeof (struct case_element));
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

	help = (do_aktion*) xmalloc (sizeof (struct do_aktion));
	help -> name = the_umstimmung -> name;

	switch (the_umstimmung -> umstimmung_typ)
	{

	case umstimmung_taste_abs:
		TRACE;
		help -> aufruf_typ = aufruf_umst_taste_abs;

		help -> u.aufruf_umst_taste_abs.wert =
		        get_wert_of_argument (box,
					      & the_umstimmung->u.umstimmung_taste_abs.argument,
					      aktuelle_parameter);

		help -> next = NULL;

		return help;

		/*        break; */

	case umstimmung_breite_abs:
		TRACE;
		help -> aufruf_typ = aufruf_umst_breite_abs;

		help -> u.aufruf_umst_breite_abs.wert =
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
		                        get_wert_komplex_intervall (
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
		                        get_wert_komplex_intervall (
		                                the_umstimmung->u.umstimmung_wiederholung_abs.komplex_liste)));

		help -> next = NULL;

		return help;

		/*        break; */

	case umstimmung_taste_rel:
		TRACE;
		help -> aufruf_typ = aufruf_umst_taste_rel;

		help -> u.aufruf_umst_taste_rel.wert =
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

		help -> u.aufruf_umst_breite_rel.wert =
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
		        expand_tonliste ( the_umstimmung->u.umstimmung_toene_veraendert.tonliste);

		help -> next = NULL;

		return help;

		/*        break; */

	case umstimmung_umstimmungsbund:
		xfree (help);
		TRACE;

		return expand_aktions_liste (box,
					     the_umstimmung->u.umstimmung_umstimmungsbund.aktions_liste,
		                             aktuelle_parameter);

		/*        break; */

	case umstimmung_umstimmungs_case:
		TRACE;
		help -> aufruf_typ = aufruf_umst_umst_case;

		help -> u.aufruf_umst_umst_case.wert =
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
		fatal_error (0, __FILE__, __LINE__);

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


	help_logik = get_logik (name, list_of_logiken);

	if (help_logik)
	{

		return expandiere_logik (box,help_logik);

	} else
	{

		help_tonsystem = parser_get_tonsystem (name, list_of_tonsysteme);

		if (help_tonsystem) {

			return expandiere_tonsystem (help_tonsystem);

		} else {

			help_umstimmung = get_umstimmung (name, list_of_umstimmungen);

			if (help_umstimmung) {

				struct interpreter_parameter_list * aktuelle_parameter;
				aktuelle_parameter = gen_parameter_liste (box, parameter, bezugs_liste);
				return expandiere_umstimmung (box,
							      help_umstimmung,
				                              aktuelle_parameter);

			} else
				fatal_error (0, __FILE__, __LINE__);

			return NULL;
		}
	}

}

static struct do_aktion * expandiere_midi (struct midiliste * liste)
{

	struct do_aktion * help;
	TRACE;

	help = (do_aktion*) xmalloc (sizeof (struct do_aktion));
	help -> name = "MidiOut";
	help -> aufruf_typ = aufruf_midi_out;
	help -> u.aufruf_midi_out.out_liste = liste;
	help -> next = NULL;

	return help;
}


static int * create_midi_scan_liste (struct midiliste * lauf)
{
	int j, k, * ret;
	TRACE;

	j = midi_list_laenge (lauf);

	ret = (int*) xcalloc((size_t)(j+1), sizeof(int));

	for (k=0; lauf; lauf=lauf->next, k++)
		ret [k] = lauf->midi_code;

	ret [k] = -1;

	return ret;
}

PATTERNN * expand_pattern (const char * harmonie_name)

{

	struct harmonie * the_harmonie;
	PATTERNN * help;
	int i;

	struct taste * lauf_taste;
	TRACE;

	the_harmonie = get_harmonie (harmonie_name, list_of_harmonien);

	if (the_harmonie == NULL) {
		fatal_error (0, __FILE__, __LINE__);
	}

	help = (PTRN*) xmalloc (sizeof (PATTERNN));

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


void insert_in_globale_liste (int instrument, struct logik * lauf)

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
			if (lauf->ausloeser->u.ausloeser_harmonie.vortaste == -2)
				/* Dann unmöglicher Harmonieauslöser */
				break;

			/* Neuen Eintrag erzeugen */
			for (temp_harmonie = & mut_box[instrument].first_harmony;
			                *temp_harmonie;
			                temp_harmonie = & (*temp_harmonie)->next)
				;

			*temp_harmonie = (harmonie_ereignis*) xmalloc( (size_t)sizeof(struct harmonie_ereignis));

			(*temp_harmonie) -> pattern=expand_pattern ((lauf->ausloeser)->u.ausloeser_harmonie.name) ;
			(*temp_harmonie) -> ist_harmonieform=0;
			(*temp_harmonie) -> vortaste=(lauf->ausloeser)->u.ausloeser_harmonie.vortaste ;
			(*temp_harmonie) -> nachtaste=(lauf->ausloeser)->u.ausloeser_harmonie.nachtaste ;
			(*temp_harmonie) -> name=lauf->name;
			(*temp_harmonie) -> aktion=NULL;
			(*temp_harmonie) -> the_logik_to_expand=lauf;
			(*temp_harmonie) -> next=NULL;
			break;

		case ausloeser_harmonie_form:
			TRACE;
			if (lauf->ausloeser->u.ausloeser_harmonie_form.vortaste == -2)
				/* Dann unmöglicher Harmonieauslöser */
				break;

			/* Neuen Eintrag erzeugen */
			for (temp_harmonie = & mut_box[instrument].first_harmony;
			                *temp_harmonie;
			                temp_harmonie = & (*temp_harmonie)->next)
				;

			*temp_harmonie  = (harmonie_ereignis*) xmalloc((size_t)sizeof(struct harmonie_ereignis));
			(*temp_harmonie) -> pattern=expand_pattern ((lauf->ausloeser)->u.ausloeser_harmonie_form.name) ;
			(*temp_harmonie) -> ist_harmonieform=1;
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
			for (temp_keyboard = & mut_box[instrument].first_keyboard;
			                *temp_keyboard;
			                temp_keyboard = & (*temp_keyboard)->next)
				;

			*temp_keyboard  = (keyboard_ereignis*) xmalloc((size_t)sizeof(struct keyboard_ereignis));
			(*temp_keyboard) -> taste= (*((lauf->ausloeser)->u.ausloeser_taste.taste)) ;
			(*temp_keyboard) -> name=lauf->name;
			(*temp_keyboard) -> aktion=NULL;
			(*temp_keyboard) -> the_logik_to_expand=lauf;
			(*temp_keyboard) -> next=NULL;
			break;

		case ausloeser_midi_in:
			TRACE;
			/* Neuen Eintrag erzeugen */
			for (temp_midi = & mut_box[instrument].first_midi;
			                *temp_midi;
			                temp_midi = & (*temp_midi)->next)
				;

			*temp_midi  = (midi_ereignis*) xmalloc((size_t)sizeof(struct midi_ereignis));

			/* Werte eintragen */

			(*temp_midi) -> first_pos =
			        (*temp_midi) -> scan_pos =
			                create_midi_scan_liste (lauf->ausloeser->u.ausloeser_midi_in.midi_code);
			(*temp_midi) -> name = lauf->name;
			(*temp_midi) -> aktion=NULL;
			(*temp_midi) -> the_logik_to_expand=lauf;
			(*temp_midi) -> next = NULL;
			break;

		default:
			TRACE;
			fatal_error(0, __FILE__, __LINE__);
		}
	}
}

void insert_in_lokale_liste (mutabor_box_type * box, struct anweisung * lauf,

                             const char * name_der_logik)
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
			if (lauf->ausloeser->u.ausloeser_harmonie.vortaste == -2)
				/* Dann unmöglicher Harmonieauslöser */
				break;

			/* Neuen Eintrag erzeugen */
			for (temp_harmonie = & box->first_harmony;
			                *temp_harmonie != NULL;
			                temp_harmonie = & (*temp_harmonie)->next)
				;

			*temp_harmonie = (harmonie_ereignis*) xmalloc( (size_t)sizeof(struct harmonie_ereignis));

			(*temp_harmonie) -> pattern =expand_pattern ((lauf->ausloeser)->u.ausloeser_harmonie.name) ;

			(*temp_harmonie) -> ist_harmonieform=0;

			(*temp_harmonie) -> vortaste=(lauf->ausloeser)->u.ausloeser_harmonie.vortaste ;

			(*temp_harmonie) -> nachtaste=(lauf->ausloeser)->u.ausloeser_harmonie.nachtaste ;

			(*temp_harmonie) -> name=name_der_logik;

			(*temp_harmonie) -> aktion=
			        expand_aktions_liste (box,lauf->aktion, box->start_parameter_list);

			(*temp_harmonie) -> next=NULL;

			break;

		case ausloeser_harmonie_form:
			TRACE;
			if (lauf->ausloeser->u.ausloeser_harmonie_form.vortaste == -2)
				/* Dann unmöglicher Harmonieauslöser */
				break;

			/* Neuen Eintrag erzeugen */
			for (temp_harmonie = & box->first_harmony;
			                *temp_harmonie != NULL;
			                temp_harmonie = & (*temp_harmonie)->next)
				;

			*temp_harmonie  = (harmonie_ereignis*) xmalloc((size_t)sizeof(struct harmonie_ereignis));

			(*temp_harmonie) -> pattern=expand_pattern ((lauf->ausloeser)->u.ausloeser_harmonie_form.name) ;

			(*temp_harmonie) -> ist_harmonieform=1;

			(*temp_harmonie) -> vortaste=(lauf->ausloeser)->u.ausloeser_harmonie_form.vortaste ;

			(*temp_harmonie) -> nachtaste=(lauf->ausloeser)->u.ausloeser_harmonie_form.nachtaste ;

			(*temp_harmonie) -> name=name_der_logik;

			(*temp_harmonie) -> aktion=
			        expand_aktions_liste (box,lauf->aktion, box->start_parameter_list);

			(*temp_harmonie) -> next=NULL;

			break;

		case ausloeser_default:
			TRACE;
			/* Neuen Eintrag erzeugen */
			for (temp_harmonie = & box->first_harmony;
			                *temp_harmonie != NULL;
			                temp_harmonie = & (*temp_harmonie)->next)
				;

			*temp_harmonie  = (harmonie_ereignis*) xmalloc((size_t)sizeof(struct harmonie_ereignis));

			(*temp_harmonie) -> pattern=NULL ;

			(*temp_harmonie) -> ist_harmonieform=2;

			/* 2 als Wert für ANSONSTEN */

			(*temp_harmonie) -> vortaste=0 ;

			(*temp_harmonie) -> nachtaste=0 ;

			(*temp_harmonie) -> name=name_der_logik;

			(*temp_harmonie) -> aktion=
			        expand_aktions_liste (box, lauf->aktion, box->start_parameter_list);

			(*temp_harmonie) -> next=NULL;

			break;

		case ausloeser_taste:
			TRACE;
			/* Neuen Eintrag erzeugen */
			for (temp_keyboard = & box->first_keyboard;
			                *temp_keyboard != NULL;
			                temp_keyboard = & (*temp_keyboard)->next)
				;

			*temp_keyboard  = (keyboard_ereignis*) xmalloc((size_t)sizeof(struct keyboard_ereignis));

			(*temp_keyboard) -> taste= (*((lauf->ausloeser)->u.ausloeser_taste.taste)) ;

			(*temp_keyboard) -> name=name_der_logik;

			(*temp_keyboard) -> aktion=
			        expand_aktions_liste (box, lauf->aktion, box->start_parameter_list);

			(*temp_keyboard) -> next=NULL;

			break;

		case ausloeser_midi_in:
			TRACE;
			/* Neuen Eintrag erzeugen */
			for (temp_midi = & box->first_midi;
			                *temp_midi != NULL;
			                temp_midi = & (*temp_midi)->next)
				;

			*temp_midi  = (midi_ereignis*) xmalloc((size_t)sizeof(struct midi_ereignis));

			/* Werte eintragen */

			(*temp_midi) -> first_pos =
			        (*temp_midi) -> scan_pos =
			                create_midi_scan_liste (lauf->ausloeser->u.ausloeser_midi_in.midi_code);

			(*temp_midi) -> name=name_der_logik;

			(*temp_midi) -> aktion=
			        expand_aktions_liste (box, lauf->aktion, box->start_parameter_list);

			(*temp_midi) -> next = NULL;

			break;

		default:
			TRACE;
			fatal_error(0, __FILE__, __LINE__);
		}
	}
}


static void expandiere_in_globale_liste (void)
{

	struct harmonie_ereignis * lauf_harmonie [MAX_BOX];

	struct keyboard_ereignis * lauf_keyboard [MAX_BOX];

	struct midi_ereignis     * lauf_midi     [MAX_BOX];
	int i;
	
	TRACE;

	for (i=0; i<MAX_BOX; i++) {
		lauf_harmonie[i] = mut_box[i].first_harmony;
		lauf_keyboard[i] = mut_box[i].first_keyboard;
		lauf_midi    [i] = mut_box[i].first_midi;
	}

	while (lauf_harmonie[0]) {
		int j;


		for (j=0; j<MAX_BOX; j++) {
			lauf_harmonie[j] -> aktion =
				expandiere_logik (&mut_box[j],lauf_harmonie[j] -> the_logik_to_expand);
//			lauf_harmonie[j] -> aktion = lauf_harmonie[0] -> aktion;
		}

		for (j=0; j<MAX_BOX; j++) {
			lauf_harmonie[j] = lauf_harmonie[j] -> next;
		}
	}

	while (lauf_keyboard[0]) {
		int j;


		for (j=0; j<MAX_BOX; j++) {
			lauf_keyboard[j] -> aktion =
				expandiere_logik (&mut_box[j], lauf_keyboard[j] -> the_logik_to_expand);
//			lauf_keyboard[j] -> aktion = lauf_keyboard[0] -> aktion;
		}

		for (j=0; j<MAX_BOX; j++) {
			lauf_keyboard[j] = lauf_keyboard[j] -> next;
		}
	}



	while (lauf_midi[0]) {
		int j;


		for (j=0; j<MAX_BOX; j++) {
			lauf_midi[j] -> aktion =
				expandiere_logik (&mut_box[j],lauf_midi[j] -> the_logik_to_expand);
//			lauf_midi[j] -> aktion = lauf_midi[0] -> aktion;
		}

		for (j=0; j<MAX_BOX; j++) {
			lauf_midi[j] = lauf_midi[j] -> next;
		}
	}

}




static struct harmonie_ereignis **

			get_ende_harmonie (struct harmonie_ereignis ** lauf)
{
	TRACE;
	if (*lauf == NULL) return lauf;

	return get_ende_harmonie (& (*lauf) -> next);
}

static struct keyboard_ereignis **

			get_ende_keyboard (struct keyboard_ereignis ** lauf)
{
	TRACE;
	if (*lauf == NULL) return lauf;

	return get_ende_keyboard (& (*lauf) -> next);
}

static struct midi_ereignis **

			get_ende_midi (struct midi_ereignis ** lauf)
{
	TRACE;
	if (*lauf == NULL) return lauf;

	return get_ende_midi (& (*lauf) -> next);
}


/*==============================================================*/


void mutabor_tabellen_generator (void)
{

	/* Ausgabe der Pointer-Setz-Prozeduren */

	struct logik * lauf;

	struct anweisung * lauf_anweisung;
	int i, j;
	TRACE;


	for (i=0; i<MAX_BOX; i++) {
		mut_box[i].cache_konstanten = NULL;
		mut_box[i].first_midi = NULL;
		mut_box[i].first_keyboard = NULL;
		mut_box[i].first_harmony = NULL;
	}


	for (i=0;i<MAX_BOX;i++) {

		/* Die globalen Listen werden initialisiert: */

		/* Die globalen Auslöser werden in die vorbereiteten Listen eingetragen: */

		for (lauf = list_of_logiken; lauf; lauf = lauf -> next) {

			insert_in_globale_liste (i, lauf);
		}

		mut_box[i].last_global_harmony=get_ende_harmonie (& mut_box[i].first_harmony);

		mut_box[i].last_global_keyboard=get_ende_keyboard (& mut_box[i].first_keyboard);
		mut_box[i].last_global_midi=get_ende_midi (& mut_box[i].first_midi);
	}

	/* Die lokalen Listen werden erzeugt: */
	/* Es wird ein Array mit Anfangszeigern  auf die lokalen
	   Auslöser angelegt. Die Nummer der Logik ist index */

	j = logik_list_laenge (list_of_logiken);

	first_lokal_harmonie = (harmonie_ereignis* *) xcalloc ((size_t)i, sizeof(first_lokal_harmonie[0]));

	first_lokal_keyboard = (keyboard_ereignis* *) xcalloc ((size_t)i, sizeof(first_lokal_keyboard[0]));

	first_lokal_midi     = (midi_ereignis* *) xcalloc ((size_t)i, sizeof(first_lokal_midi[0]));
	
	/* #### Wichtig ist, daß calloc alles auf 0 setzt (NULL)  */

	for (lauf=list_of_logiken, j=0;
	     lauf;
	     lauf=lauf->next, j++ ) {

		for (lauf_anweisung=lauf->anweisungsliste; lauf_anweisung;
		     lauf_anweisung=lauf_anweisung->next) {

			for (i = 0 ; i < MAX_BOX; i++)
				insert_in_lokale_liste (&mut_box[i], lauf_anweisung, lauf->name);
		}
	}
	
	expandiere_in_globale_liste ();

} /* end of mutabor_tabellen_generator */




///\}
