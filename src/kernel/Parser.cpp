/** \file 
********************************************************************
* Some additional data for the parser
*
* Copyright:   (c) 2008 TU Dresden
* \author  Tobias Schlemmer <keinstein@users.berlios.de>
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
*
********************************************************************
* \addtogroup kernel
* \{
********************************************************************/

#include "Global.h"
#include "Execute.h"
#include "Interval.h"
#include "Hilfs.h"
#include "Parser.h"

#ifdef _
#undef _
#endif
#define _ _mut

#undef mutC_STR
#undef C_STR

#ifdef __cplusplus
namespace mutabor {
	namespace hidden {
		extern "C" {
#endif
/* Globale Variablen des Compilers mit dem Codegenerator und
   dem Tabellengenerator  */

static void berechne_toene_absolut (mutabor_box_type * box, struct ton *ton_liste);

static void check_konsistenz (mutabor_box_type * box);

#ifdef DEBUG
static void drucke_ton (struct ton * lauf);
static void drucke_harmonie (struct harmonie * this_);
static void drucke_argument (struct argument * z_or_p);

static void print_ausloeser (mutabor_box_type * box, struct ausloeser * this_);
//static void print_aktion (struct aktion * that);
static void print_action (struct aktions_liste * action);
static void print_action_list(struct aktions_liste * actionlist);
#endif


/*********  Allgemeine Hilfsfunktionen ********/

void allgemeine_initialisierungen( mutabor_box_type * box)
{
	TRACE;
	box->file->ton_ohne_namen=(ton*) xmalloc(box,(size_t) sizeof(struct ton));
	box->file->ton_ohne_namen->name=NULL;
	box->file->ton_ohne_namen->ton_typ=ton_absolut;
	box->file->ton_ohne_namen->u.ton_absolut.ton_wert=0.0;
	box->file->ton_ohne_namen->next=NULL;
}

int ton_list_laenge (const struct ton *list)

{
	TRACE;
	int count = 0;
	for (const struct ton * tmp = list;
	     tmp; tmp = tmp->next)
		count++;
	return count;
}

int tonsystem_list_laenge (const struct tonsystem *list)
{
	TRACE;
	int count = 0;
	for (const struct tonsystem * tmp = list;
	     tmp; tmp = tmp->next)
		count++;
	return count;
}

int umstimmungs_list_laenge (const struct umstimmung *list)
{
	TRACE;
	int count = 0;
	for (const struct umstimmung * tmp = list;
	     tmp; tmp = tmp->next)
		count++;
	return count;
}

int logik_list_laenge (const struct logik *list)
{
	TRACE;
	int count = 0;
	for (const struct logik * tmp = list;
	     tmp; tmp = tmp->next)
		count++;
	return count;
}

int midi_list_laenge (const struct midiliste *list)
{

	TRACE;
	int count = 0;
	for (const struct midiliste * tmp = list;
	     tmp; tmp = tmp->next)
		count++;
	return count;
}

int get_logik_nummer (mutabor_box_type * box, const char * name, struct logik * liste)
{
	TRACE;
	if (liste == NULL) {
		mutabor_error_message(box,
				      internal_error,
				      _("The logic was not intialized. Found in %s, %d"),
				      _T(__FILE__), __LINE__);
		return 0;
	} else if ( ! strcasecmp (name, liste->name))
		return 0;
	
	return 1 + get_logik_nummer (box, name, liste->next);
}

int parameter_list_laenge (struct parameter_list *list)

{
	TRACE;
	if (list) return 1 + parameter_list_laenge (list -> next);

	return 0;
}

int argument_list_laenge (struct argument_list *list)
{
	TRACE;
	if (list) return 1 + argument_list_laenge (list -> next);

	return 0;
}


struct ton * get_ton (mutabor_box_type * box, const char * name, struct ton * liste)
{
	TRACE;
	if (name==NULL) return(box->file->ton_ohne_namen);
	if (liste == NULL) return NULL;
 	if ( ! strcasecmp (name, liste->name)) return liste;
	return get_ton (box, name, liste->next);
}


struct intervall * get_intervall (const char * name,
				  struct intervall * liste)
{
	TRACE;
	if (liste == NULL) return NULL;
	if ( ! strcasecmp (name, liste->name)) return liste;
	return get_intervall (name, liste->next);
}

struct tonsystem * parser_get_tonsystem (const char * name,
					 struct tonsystem * liste)
{
	TRACE;
	if (liste == NULL) return NULL;
	if ( ! strcasecmp (name, liste->name)) return liste;
	return parser_get_tonsystem (name, liste->next);
}

struct umstimmung * get_umstimmung (const char * name,
				    struct umstimmung * liste)
{
	TRACE;
	if (liste == NULL) return NULL;
	if ( ! strcasecmp (name, liste->name)) return liste;
	return get_umstimmung (name, liste->next);
}

struct harmonie * get_harmonie (const char * name, struct harmonie * liste)
{
	TRACE;
	if (liste == NULL) return NULL;
	if ( ! strcasecmp (name, liste->name)) return liste;
	return get_harmonie (name, liste->next);
}


struct logik * get_logik (const char * name, struct logik * liste)
{
	TRACE;
	if (liste == NULL) return NULL;
	if ( ! strcasecmp (name, liste->name)) return liste;
	return get_logik (name, liste->next);
}


/********* Einleseroutine fuer Integerliste          *********/
/*         Es wird einfach eine Liste of Integer aufgebaut       **/
/*         die allgemein verwendbar ist.                       **/


void init_integersequenz (mutabor_box_type * box)
{
	TRACE;
	box->file->list_of_integers = NULL;
}


void get_new_integer_in_integersequenz (mutabor_box_type * box, int wert)

{
	struct midiliste * * lauf;
	TRACE;

	for (lauf= & box->file->list_of_integers; * lauf; lauf= & (*lauf)->next) {}

	(* lauf) = (midiliste*) xmalloc (box, (size_t) sizeof (struct midiliste));
	(* lauf) -> midi_code     = wert;
	(* lauf) -> next          = NULL;
}

static struct midiliste * get_last_integersequenz (mutabor_box_type * box)
{
	TRACE;
	return box->file->list_of_integers;
}



/********* Einleseroutinen fuer Parameterliste          *********/
/*         Es wird einfach eine Liste of Namen aufgebaut       **/
/*         die allgemein verwendbar ist.                       **/

void init_parameter_liste (mutabor_box_type * box)
{
	TRACE;
	box->file->list_of_names = NULL;
}


struct parameter_list * 
get_new_name_in_parameterlist (mutabor_box_type * box, const char * name)
{

	struct parameter_list * retval;
	TRACE;
	retval = (parameter_list*) 
	    xmalloc (box, (size_t) sizeof (struct parameter_list));
	retval -> name = name;
	retval -> next = NULL;
	return retval;
}

void enumerate_parameters (mutabor_box_type * box, struct parameter_list * parameters) {
    size_t i = 0;
    while (parameters != NULL) {
	parameters -> index = i++;
	parameters = parameters -> next;
    }
    if (box->file->parameter_count < i) 
	box->file->parameter_count = i;
}

		    /*
static struct parameter_liste * get_last_parameter_liste (mutabor_box_type * box)
{
	return box->file->list_of_names;
}
		    */


static struct parameter_list * 
get_parameter_by_name (mutabor_box_type * box, 
		       const char * search_name,
		       struct parameter_list * node)
{
	TRACE;
	if (node == NULL) return NULL;
	while ( strcasecmp (search_name, node -> name)) {
		node = node->next;
		if (node == NULL) return NULL;
	}
	return node;
}

void print_argumentliste (struct argument_list * this_)

{
	TRACE;
	if (this_)
		{
			switch (this_ -> argument.argument_type) {
				
			case mutabor_argument_integer:
				printf (" %d ", this_ -> argument.u.integer.number);
				break;
			case mutabor_argument_parameter:
				printf (" %s ", this_ -> argument.u.parameter.name);
				break;
			case mutabor_argument_distance:
			    printf (" %s ", _("DISTANCE"));
				break;
			case mutabor_argument_anchor:
			    printf (" %s ",_("CENTER"));
				break;
			default:
				printf ("{unknown argument type}");
			}

			print_argumentliste (this_ -> next);
		}
}


/********* Einleseroutinen fuer Argumentliste          *********/

void init_argument_liste (mutabor_box_type * box)
{
	TRACE;
	box->file->list_of_argumente = NULL;
}


struct argument_list *
get_new_number_in_argument_list (mutabor_box_type * box, 
				 double number)

{

	struct argument_list * token;
	TRACE;

	token = (argument_list*) xmalloc (box, (size_t) sizeof (struct argument_list));
	token -> argument.argument_type = mutabor_argument_integer;
	token -> argument.u.integer.number = (int) number;
	token -> next = NULL;
	return token;
}

struct argument_list *
get_new_name_in_argument_list (mutabor_box_type * box, 
			       const char * parameter_name)
{

	struct argument_list * lauf;
	TRACE;

	lauf = (argument_list*) xmalloc (box, (size_t) sizeof (struct argument_list));
	lauf -> argument.argument_type = mutabor_argument_parameter;
	lauf -> argument.u.parameter.parameter = NULL;
	lauf -> argument.u.parameter.name = parameter_name;
	lauf -> next = NULL;
	return lauf;
}

struct argument_list *
get_new_distance_in_argument_list (mutabor_box_type * box)

{

	struct argument_list * token;
	TRACE;

	token = (argument_list*) xmalloc (box, (size_t) sizeof (struct argument_list));
	token -> argument.argument_type = mutabor_argument_distance;
	token -> next = NULL;
	return token;
}
struct argument_list *
get_new_anchor_in_argument_list (mutabor_box_type * box)

{

	struct argument_list * token;
	TRACE;

	token = (argument_list*) xmalloc (box, (size_t) sizeof (struct argument_list));
	token -> argument.argument_type = mutabor_argument_anchor;
	token -> next = NULL;
	return token;
}

#if 0
static struct argument_list * get_last_argument_liste (mutabor_box_type * box)
{
	TRACE;
	return box->file->list_of_argumente;
}
#endif


/********* Einleseroutinen fuer Aktions-liste          *********/

void init_aktions_liste (mutabor_box_type * box)
{
	TRACE;
	box->file->list_of_aktionen = NULL;
}


void get_new_aktion_aufruf_element (mutabor_box_type * box,
				    const char * name,
				    struct argument_list * arguments)

{

	struct aktions_liste * * lauf;
	TRACE;

	for (lauf= & box->file->list_of_aktionen; * lauf; lauf= & (*lauf)->next) {}

	(* lauf) = (aktions_liste*) xmalloc (box,(size_t) sizeof (struct aktions_liste));
	(* lauf) -> aktions_typ           = aktion_aufruf;
	(* lauf) -> u.aktion_aufruf.name  = name;
	(* lauf) -> u.aktion_aufruf.argument_liste = arguments;
	(* lauf) -> next                  = NULL;
}

void get_new_aktion_midi_out_element (mutabor_box_type * box)

{

	struct aktions_liste * * lauf;
	TRACE;

	for (lauf= & box->file->list_of_aktionen; * lauf; lauf= & (*lauf)->next) {}

	(* lauf) = (aktions_liste*) xmalloc (box, (size_t) sizeof (struct aktions_liste));
	(* lauf) -> aktions_typ           = aktion_midi_out;
	(* lauf) -> u.aktion_midi_out.midi_code = get_last_integersequenz (box);
	(* lauf) -> next                  = NULL;
}

void get_new_aktion_harmony_analysis(mutabor_box_type * box)
{
	struct aktions_liste * * lauf;
	TRACE;

	for (lauf= & box->file->list_of_aktionen; * lauf; lauf= & (*lauf)->next) {}

	(* lauf) = (aktions_liste*) xmalloc (box, (size_t) sizeof (struct aktions_liste));
	(* lauf) -> aktions_typ           = aktion_harmony_analysis;
	(* lauf) -> next                  = NULL;
}

static struct aktions_liste * get_last_aktions_liste (mutabor_box_type * box)
{
	TRACE;
	return box->file->list_of_aktionen;
}

/* Einleseroutinen fÅr komplex_intervalle  ****/

void init_komplex_ton_list (mutabor_box_type * box)
{
	TRACE;
	box->file->the_komplex_liste = NULL;
}

void get_new_faktor_anteil (mutabor_box_type * box, double f, const char *name)

{

	struct komplex_intervall * * lauf;
	TRACE;

	for (lauf= & box->file->the_komplex_liste; * lauf; lauf= & (*lauf)->next)
		/* nur ende der Liste finden */ ;

	(* lauf) = (komplex_intervall*) xmalloc (box, (size_t) sizeof (struct komplex_intervall));

	(* lauf) -> faktor = f;

	(* lauf) -> name   = name;

	(* lauf) -> next   = NULL;

}

struct komplex_intervall * get_last_komplex_intervall (mutabor_box_type * box)
{
	TRACE;
	return box->file->the_komplex_liste;
}

#if 0

void get_new_relativ_anteil (double f,
                             const char *linke_grenze, const char *rechte_grenze)
{

	struct komplex_anteil * * lauf;

	TRACE;
	for (lauf= & komplex_liste; * lauf; lauf= & (*lauf)->next)
		/* nur ende der Liste finden */ ;

	(* lauf) = xmalloc ((size_t) sizeof (struct komplex_anteil));

	(* lauf) -> komplex_typ                     = komplex_anteil_relativ;

	(* lauf) -> u.komplex_anteil_relativ.faktor        = f;

	(* lauf) -> u.komplex_anteil_relativ.linke_grenze  = linke_grenze;

	(* lauf) -> u.komplex_anteil_relativ.rechte_grenze = rechte_grenze;

	(* lauf) -> next                                   = NULL;

}

#endif


/************************/


#if 0
void setze_nummer_von_abstand_und_zentrum (mutabor_box_type * box)
{

	struct logik * lauf;
	TRACE;

	for (lauf=box->file->list_of_logiken; lauf; lauf=lauf->next) {

		struct anweisung * lauf_anw;

		for (lauf_anw=lauf->anweisungsliste; 
		     lauf_anw; lauf_anw=lauf_anw->next) {
			if (lauf_anw->aktion->aktions_typ == aktion_aufruf) {

				struct argument_list * lauf_arg;

				for (lauf_arg=lauf_anw->aktion->u.aktion_aufruf.argument_liste;
				     lauf_arg;
				     lauf_arg=lauf_arg->next) {
					switch (lauf_arg->argument.argument_type) {

					case mutabor_argument_integer:
						TRACE;
						/* OK */
						break;

					case mutabor_argument_parameter:
						TRACE;
						if ( (! strcasecmp (lauf_arg->argument.u.parameter.parameter_name, "ABSTAND")) 
|| !strcasecmp (lauf_arg->argument.u.parameter.parameter_name, "DISTANCE")) {
							lauf_arg->argument.u.parameter.parameter_number = interpreter_parameter_distance;
						} else if ( (!strcasecmp (lauf_arg->argument.u.parameter.parameter_name,
								      "ZENTRUM"))|| !strcasecmp (lauf_arg->argument.u.parameter.parameter_name,
											     "CENTER")) {
							lauf_arg->argument.u.parameter.parameter_number	= interpreter_parameter_anchor;
						} else
							mutabor_error_message(box,
									      false,
									      _("Undefined parameter: %s (in call %s from logic %s)"),    
									      (lauf_arg->argument.u.parameter.parameter_name),
									      (lauf_anw->aktion->u.aktion_aufruf.name),
									      (lauf->name));
						break;

					case mutabor_argument_distance:
						TRACE;
						lauf_arg->argument.u.parameter.parameter_number = interpreter_parameter_distance;
						break;

					case mutabor_argument_anchor:
						lauf_arg->argument.u.parameter.parameter_number	= interpreter_parameter_anchor;
						break;

					default:
						TRACE;
						mutabor_error_message(box,
								      internal_error,
								      _("Invalid argument type %d detected at\n%s:%n"),
								      lauf_arg->argument.argument_type,
								      _T(__FILE__), __LINE__);

						break;
					}
				}
			}
		}
	}
}
#endif


int yyparse(mutabor_box_type * box);
bool mutabor_programm_einlesen (mutabor_box_type * box, const char * logic )
{
	TRACE;

	/*
	if ((quelldatei = wxFopen (filename, _T("r"))) == NULL) {
		mutabor_error_message(box,
				      false,
				      _("Can't open file: %s"),
				      filename);
	}
	*/
	
	box->scanner = (mutabor_scanner_data *) calloc(1, sizeof(struct mutabor_scanner_data));
	box->scanner->data = logic;
	box->scanner->pos = box->scanner->data;

	box->file = (mutabor_logic_parsed *) calloc(1,sizeof(struct mutabor_logic_parsed));
	box->file->list_of_constants             = NULL;
	box->file->list_of_intervalle            = NULL;
	box->file->list_of_toene                 = NULL;
	box->file->list_of_tonsysteme            = NULL;
	box->file->list_of_umstimmungen          = NULL;
	box->file->list_of_harmonien             = NULL;
	box->file->list_of_logiken               = NULL;
	box->file->list_of_instrumente           = NULL;
	box->file->list_of_config_instrumente    = NULL;


	DEBUGLOG2(kernel_parser,_T("Start parsing"));

	if (yyparse(box)) {
		return false;
	}


	// NEU: wenn kein Intervall oder Ton da, dann Speichermangel
	// also evtl. Dummy
	// (das Problem l‰ﬂt sich sicher auch direkt lˆsen ...)

	if ( !box->file->list_of_intervalle )
		get_new_intervall(box,"__TopSecret__RK__Intervall__", 1.0);
			   
	berechne_intervalle_absolut (box,box->file->list_of_intervalle);
			   
	if ( !box->file->list_of_toene )
		get_new_ton_absolut(box,"__TopSecret__RK__Ton__", 440.0);

	berechne_toene_absolut (box,box->file->list_of_toene);


	/* Falls kein Instrument angegeben ist: Dann 1 -> 1-16 */

	if (box->file->list_of_instrumente == NULL &&
	    box->file->list_of_config_instrumente == NULL) {
		get_instrument_dekl (box,1, 1, 16, 0, & (box->file->list_of_instrumente));
	} else if (box->file->list_of_instrumente == NULL) {
		box->file->list_of_instrumente = box->file->list_of_config_instrumente;
	}


	//	setze_nummer_von_abstand_und_zentrum (box);

	check_konsistenz (box);

#ifdef DEBUG
	

	if (isDebugFlag(kernel_parser)) {
		{ struct intervall * lauf;
			printf ("\n");
			
			for (lauf=box->file->list_of_intervalle; lauf; lauf=lauf->next) {
				if (lauf->intervall_typ == intervall_absolut) {
					printf ("Name: %s, Wert: %f:\n", 
						lauf->name,
						lauf->u.intervall_absolut.intervall_wert );
				} else {
					STUB;
				}
			}
		}

		{ struct ton * lauf;
			printf ("\n");

			for (lauf=box->file->list_of_toene; lauf; lauf=lauf->next) {
				drucke_ton (lauf);

			}
		}

		{ struct tonsystem * lauf;
			printf ("\n");

			for (lauf=box->file->list_of_tonsysteme; lauf; lauf=lauf->next) {

				struct ton * help;
				printf ("Name: %s, Taste: %d, Periode: %p, "
					"Tonleiter_breite: %d\n",
					lauf->name,
					lauf->taste,
					(void *)(lauf->periode),
					ton_list_laenge (lauf->toene));

				for (help = lauf->toene; help; help = help->next ) {
					printf ("%s , ", help->name ? help->name : "(NULL)");
				}

				printf ("\n");
			}
		}

		printf ("Umstimmungen:\n");

		{

			struct umstimmung * lauf;
			printf ("\n");

			for (lauf=box->file->list_of_umstimmungen; lauf; lauf=lauf->next) {

				struct parameter_list * help;
				printf ("\nName: %s, Parameter: ", lauf->name);

				for (help = lauf->parameter_liste; help; help = help->next ) {
					printf ("%s , ", help->name ? help->name : "(NULL)");
				}

				printf ("\n");

				switch (lauf -> umstimmung_typ) {
				case umstimmung_midi_out:
					STUB;

				case umstimmung_taste_abs :
					printf ("        umstimmung_taste_abs : ");

#if 0
					drucke_argument (
							 & lauf -> u.umstimmung_taste_abs.argument);
#endif

					printf ("\n");

					break;

				case umstimmung_taste_rel :
					printf ("        umstimmung_taste_rel : ");
#if 0
					drucke_argument (
							 & lauf -> u.umstimmung_taste_rel.argument);
#endif
					printf (" Rechenzeichen: \"%c\"\n",
						lauf -> u.umstimmung_taste_rel.rechenzeichen);

					break;

				case umstimmung_breite_abs :
					printf ("        umstimmung_breite_abs : ");
#if 0
					drucke_argument (
							 & lauf -> u.umstimmung_breite_abs.argument);
#endif
					printf ("\n");

					break;

				case umstimmung_breite_rel :
					printf ("        umstimmung_breite_rel : ");
#if 0
					drucke_argument (
							 & lauf -> u.umstimmung_breite_rel.argument);
#endif
					printf (" Rechenzeichen: \"%c\"\n",
						lauf -> u.umstimmung_breite_rel.rechenzeichen);

					break;

				case umstimmung_toene_veraendert : {

					struct ton * help;
					printf ("        umstimmung_toene_veraendert : \n");

					for (help = lauf -> u.umstimmung_toene_veraendert.tonliste;
					     help;
					     help = help -> next) {
						printf ("        ");
						drucke_ton (help);
					}

					break;
				}

				case umstimmung_wiederholung_abs :
					printf ("        umstimmung_wiederholung_abs :");

					STUB;
					/*
					  printf ("Name : %s \n",
					  lauf -> u.umstimmung_wiederholung_abs.name);
					*/
					break;

				case umstimmung_wiederholung_rel :
					printf ("        umstimmung_wiederholung_rel : ");

					STUB;
					/*					drucke_argument (
										& lauf -> u.umstimmung_wiederholung_rel.komplex_liste);

										printf (" R-zeichen: \"%c\"\n",
										lauf -> u.umstimmung_wiederholung_rel.rechenzeichen);
					*/
					break;

				case umstimmung_umstimmungsbund : {

					printf ("        umstimmung_umstimmungsbund : \n");
					print_action_list (lauf->u.umstimmung_umstimmungsbund.aktions_liste);

					/*

					  for (help_umst = lauf->u.umstimmung_umstimmungsbund.aktions_liste;
					  help_umst;
					  help_umst = help_umst -> next ) {
					  print_action(help_umst);
					  }

					*/

				}

					break;

				case umstimmung_umstimmungs_case : {

					struct case_liste * help_case;
					printf ("        umstimmung_umstimmungs_case : \n");
#if 0
					drucke_argument (
							 & lauf -> u.umstimmung_umstimmungs_case.argument);
#endif

					for (help_case = lauf -> u.umstimmung_umstimmungs_case.umstimmungs_case_liste;
					     help_case;
					     help_case = help_case -> next) {

						if (help_case->is_default)
							printf ("(ANSONSTEN)");
						else
							printf ("%d ", 
								help_case->case_label);

						print_action_list(
								  help_case->case_aktion);
 					}
				}

					break;
				} /* end of switch */
			}
		}

		printf ("\nHarmonien:\n");

		{

			struct harmonie * lauf;

			for (lauf=box->file->list_of_harmonien; lauf; lauf=lauf->next) {
				printf ("\n");
				drucke_harmonie (lauf);
				printf ("\n");
			}
		}

		printf ("\nLogiken:\n");

		{

			struct logik * lauf;

			for (lauf=box->file->list_of_logiken; lauf; lauf=lauf->next) {

				struct anweisung * anw_lauf;
				print_ausloeser (box, lauf->ausloeser);
				printf ("\nName: %s Einstimmung : %s\n",
					lauf->name,
					lauf->einstimmungs_name ?
					lauf->einstimmungs_name :
					"(NULL)");

				for (anw_lauf = lauf->anweisungsliste;
				     anw_lauf;
				     anw_lauf = anw_lauf -> next) {
					print_ausloeser (box, anw_lauf->ausloeser);
					print_action (anw_lauf->aktion);
				}
			}
		}

		printf ("\nInstrumente:\n");

		{

			struct instrument * lauf;

			for (lauf=box->file->list_of_instrumente; lauf; lauf=lauf->next) {
				printf ("Instrument %d -> %d - %d\n", lauf->midi_in,
					lauf->midi_von, lauf->midi_bis);
			}
		}

	}
#endif
	return true;
}

#ifdef DEBUG

static void drucke_argument (struct argument * z_or_p)
{
	switch (z_or_p -> argument_type) {
	case mutabor_argument_integer: {
		printf (" Number: %d ", z_or_p->u.integer.number);
		break;
	}
	case mutabor_argument_parameter: {
		printf (" Parameter: %s, Ptr: %p , Nr:  %d ",
			z_or_p->u.parameter.name,
			(void *)z_or_p->u.parameter.parameter,
			z_or_p->u.parameter.parameter?
			z_or_p->u.parameter.parameter->index:0);
		break;
	}
	case mutabor_argument_distance: {
		printf (" ANCHOR ");
		break;
	}
	case mutabor_argument_anchor: {
		printf (" ANCHOR ");
		break;
	}
	default:
		printf (" {unknown argument type} ");
	}
}

static void drucke_ton (struct ton * lauf)
{
	printf ("Name: %s, Typ: %s:\n",
		lauf->name ? lauf->name : "(NULL)",
		lauf->ton_typ == ton_absolut ? "absolut" :
		lauf->ton_typ == ton_komplex ? "komplex" :
		"undefined" );

	if (lauf->name == NULL) return;

	switch (lauf->ton_typ) {
	case ton_absolut :
                printf ("%f\n", lauf->u.ton_absolut.ton_wert);
                break;
	case ton_komplex : {
		struct komplex_intervall * help = lauf->u.ton_komplex.komplex_liste;
		printf ("%s ", lauf->u.ton_komplex.bezugston);
		while (help) {
			printf ("Faktor: %f %s ",
				help->faktor,
				help->name);
			help = help->next;
		}
	}
                break;
	}
	printf ("\n");
}

static void drucke_harmonie (struct harmonie * this_)
{
	struct taste * lauf;
	printf ("Name : %s Bezugstaste : %d \n      ",
		this_->name ? this_->name : "(NULL)",
		this_->bezugstaste);
	for (lauf = this_->tastenliste; lauf; lauf = lauf -> next) {
		printf (" %c%d ,", lauf->stern, lauf->code);
	}
}
#endif
/************/

void print_integersequenz (struct midiliste * this_)
{
	if (this_)
		{
			printf (" %d ",this_->midi_code);
			print_integersequenz (this_->next);
		}
}

#ifdef DEBUG
static void print_ausloeser (mutabor_box_type * box, struct ausloeser * this_)
{
	if (this_) {
		switch (this_->ausloeser_typ)
			{
			case ausloeser_default:
				printf ("ANSONSTEN\n");
				break;
			case ausloeser_harmonie:
				printf ("Harmonie  Vor-Taste: %d"
					" Harmonie-Name: %s"
					" Nach-Taste: %d \n",
					this_->u.ausloeser_harmonie.vortaste,
					this_->u.ausloeser_harmonie.name,
					this_->u.ausloeser_harmonie.nachtaste);
				break;
			case ausloeser_harmonie_form:
				printf ("Harmonie FORM  Vor-Taste: %d"
					" Harmonie-Name: %s"
					" Nach-Taste: %d \n",
					this_->u.ausloeser_harmonie_form.vortaste,
					this_->u.ausloeser_harmonie_form.name,
					this_->u.ausloeser_harmonie_form.nachtaste);
				break;
			case ausloeser_taste:
				printf ("TASTE  %s\n",
					this_->u.ausloeser_taste.taste);
				break;
			case ausloeser_midi_in:
				printf ("MIDI-IN: ");
				print_integersequenz (this_->u.ausloeser_midi_in.midi_code);
				break;
			default:
				mutabor_error_message(box,
						      internal_error,
						      _("Invalid event type %d detected at\n%s:%d"),
						      (this_->ausloeser_typ),
						      __FILE__,__LINE__);
			}
	}
	else
		printf ("Kein Ausloeser\n");
}

#endif
/********
	 static void print_aktions_liste (struct aktions_liste * this)
	 {
	 switch (this->aktions_typ)
	 {
	 case aktion_midi_out:
         printf ("Aktion MIDI-OUT: ");
         print_integersequenz (this->u.aktion_midi_out.midi_code);
         break;
	 case aktion_aufruf:
         printf ("Aktion Aufruf: %s ", this->u.aktion_aufruf.name);
         print_argumentliste (this->u.aktion_aufruf.argument_liste);
         break;
	 }
	 }
***********/




/********* Einleseroutine fuer die Intervalle           *********/
/*         Es wird einfach eine Liste of Intervallen aufgebaut **/

void get_new_intervall (mutabor_box_type * box, const char *name, double wert)
{

	struct intervall * * lauf;
	TRACE;

	for (lauf= & box->file->list_of_intervalle; * lauf; lauf= &(*lauf)->next) {
		if ( ! strcasecmp (name, (*lauf)->name)) {
			mutabor_error_message(box,
					      compiler_error,
					      _("The interval name %s was used twice"),
					      (name)); /* Intervallname doppelt */
		}
	}

	if (fabs (wert) < 0.001)
		mutabor_error_message(box,
				      compiler_error,
				      _("Bad interval value in %s"),
				      (name));

	(* lauf) = (intervall*) xmalloc (box, (size_t) sizeof (struct intervall));
	(* lauf) -> name = name;
 	(* lauf) -> intervall_typ = intervall_absolut;
	(* lauf) -> u.intervall_absolut.intervall_wert = wert;
	(* lauf) -> next = NULL;
}

void get_new_intervall_komplex (mutabor_box_type * box, const char *name)

{

	struct intervall * * lauf;
	TRACE;

	for (lauf= & box->file->list_of_intervalle; * lauf; lauf= &(*lauf)->next) {
		if ( ! strcasecmp (name, (*lauf)->name)) {
			mutabor_error_message(box,
					      compiler_error,
					      _("The interval name %s was used twice"),
					      (name)); /* Intervallname doppelt */
		}
	}

	(* lauf) = (intervall*) xmalloc (box, (size_t) sizeof (struct intervall));
	(* lauf) -> name = name;
	(* lauf) -> intervall_typ = intervall_komplex;
	(* lauf) -> u.intervall_komplex.komplex_liste =
	        get_last_komplex_intervall (box);
	(* lauf) -> next = NULL;

}

/********* Einleseroutinen fuer die Toene           *********/
/*         Es wird einfach eine Liste of Toenen aufgebaut  **/
/*         Je nach erkanntem Ton_Typ                       **/

void get_new_ton_absolut (mutabor_box_type * box, const char *name, double wert)
{

	struct ton * * lauf;
	TRACE;

	for (lauf= & box->file->list_of_toene; * lauf; lauf= & (*lauf)->next) {
		if ( ! strcasecmp (name, (* lauf)->name)) {
			mutabor_error_message(box,
					      compiler_error,
					      _("The tone name %s was used twice."),
					      (name)); /* Tonname doppelt */
		}
	}

	(* lauf) = (ton*) xmalloc (box, (size_t) sizeof (struct ton));
	(* lauf) -> name                   = name;
	(* lauf) -> ton_typ                = ton_absolut;
	(* lauf) -> u.ton_absolut.ton_wert = wert;
	(* lauf) -> next                   = NULL;

}


void get_new_ton_komplex_positive (mutabor_box_type * box, const char *name, const char *bezugston)

{

	struct ton * * lauf;
	TRACE;

	for (lauf= & box->file->list_of_toene; * lauf; lauf= & (*lauf)->next) {
		if ( ! strcasecmp (name, (*lauf)->name)) {
			mutabor_error_message(box,
					      compiler_error,
					      _("The tone name %s was used twice."),
					      (name)); /* Tonname doppelt */
		}
	}

	(* lauf) = (ton*) xmalloc (box, (size_t) sizeof (struct ton));
	(* lauf) -> name                        = name;
	(* lauf) -> ton_typ                     = ton_komplex;
	(* lauf) -> u.ton_komplex.bezugston     = bezugston;
	(* lauf) -> u.ton_komplex.komplex_liste = get_last_komplex_intervall (box);
	(* lauf) -> next                        = NULL;

}

void get_new_ton_komplex_negative (mutabor_box_type * box, const char *name, const char *bezugston)

{

	struct ton * * lauf;
	TRACE;

	for (lauf= & box->file->list_of_toene; * lauf; lauf= & (*lauf)->next) {
		if ( ! strcasecmp (name, (*lauf)->name)) {
			mutabor_error_message(box,
					      compiler_error,
					      _("The tone name %s was used twice."),
					      (name)); /* Tonname doppelt */
		}
	}

	(* lauf) = (ton*) xmalloc (box, (size_t) sizeof (struct ton));
	(* lauf) -> name                        = name;
	(* lauf) -> ton_typ                     = ton_komplex;
	(* lauf) -> u.ton_komplex.bezugston     = bezugston;

	{

		struct komplex_intervall * help = get_last_komplex_intervall (box);

		if (help == NULL) {
			mutabor_error_message(box,
					      internal_error,
					      _("Internal error while creating interval “%s” at\n%s:%d"),
					      ((*lauf)->name),
					      _T(__FILE__),
					      __LINE__);
		}

		help -> faktor *= -1.0 ;

		(* lauf) -> u.ton_komplex.komplex_liste = help;
	}

	(* lauf) -> next                        = NULL;

}

/********* Einleseroutinen fuer die Tonsysteme          *********/
/*         Es wird einfach eine Liste of Tonsysteme aufgebaut  **/

void init_ton_liste (mutabor_box_type * box)
{
	TRACE;
	box->file->ton_liste = NULL;
}

void get_new_ton_in_tonsystem (mutabor_box_type * box, const char *name)

{

	struct ton * * lauf;
	TRACE;

	for (lauf= & box->file->ton_liste; * lauf; lauf= & (*lauf)->next) {
		/* Hier sind doppelte Tîne zulÑssig !! */
	}

	(* lauf) = (ton*) xmalloc (box, (size_t) sizeof (struct ton));
	(* lauf) -> name                    = name;
	(* lauf) -> next                    = NULL;

}

void get_new_tonsystem (mutabor_box_type * box, const char * name, int taste)

{

	struct tonsystem * * lauf;
	TRACE;

	for (lauf= & box->file->list_of_tonsysteme; * lauf; lauf= & (*lauf)->next) {
		if ( ! strcasecmp (name, (*lauf)->name)) {
			mutabor_error_message(box,
					      compiler_error,
					      _("The tone system name “%s” was used twice"),
					      (name)); /* Tonsystemname doppelt */
		}
	}

	(* lauf) = (struct tonsystem*) xmalloc (box, (size_t) sizeof (struct tonsystem));
	(* lauf) -> name          = name;
	(* lauf) -> taste         = taste;
	(* lauf) -> periode       = get_last_komplex_intervall (box);
	(* lauf) -> toene         = box->file->ton_liste;
	(* lauf) -> next          = NULL;

}

void get_new_tonsystem_negative (mutabor_box_type * box, const char * name, int taste)

{

	struct tonsystem * * lauf;
	TRACE;

	for (lauf= & box->file->list_of_tonsysteme; * lauf; lauf= & (*lauf)->next) {
		if ( ! strcasecmp (name, (*lauf)->name)) {
			mutabor_error_message(box,
					      compiler_error,
					      _("The tone system name “%s” was used twice"),
					      (name)); /* Tonsystemname doppelt */
		}
	}

	(* lauf) = (struct tonsystem*) xmalloc (box, (size_t) sizeof (struct tonsystem));
	(* lauf) -> name          = name;
	(* lauf) -> taste         = taste;
	{

		struct komplex_intervall * help = get_last_komplex_intervall (box);

		if (help == NULL)
			mutabor_error_message(box,
					      internal_error,
					      _("Internal error while creating interval “%s” at\n%s:%d"),
					      ((*lauf)->name),
					      _T(__FILE__),
					      __LINE__);

		help -> faktor *= -1.0 ;

		(* lauf) -> periode = help;
	}

	(* lauf) -> toene         = box->file->ton_liste;
	(* lauf) -> next          = NULL;
}


/********* Einleseroutinen fuer Umstimmungen            *********/
/*         Es wird erst eine leere Umstimmung eingerichtet,    **/
/*            init_umstimmung (name);                          **/
/*         in die dann die Varianten eingetragen werden.       **/
/*         Zuletzt wird diese Umstimmung in die Liste          **/
/*         eingehÑngt.					                       **/
/*            get_new_umstimmung ();                           **/


void init_umstimmung (mutabor_box_type * box, const char * name)
{

	struct umstimmung * lauf;
	TRACE;

	for (lauf= box->file->list_of_umstimmungen; lauf; lauf= lauf -> next) {
		if ( ! strcasecmp (name, lauf -> name)) {
			mutabor_error_message(box,
					      compiler_error,
					      _("The retuning name %s was used twice"),
					      (name)); /* Umstimmungsname doppelt */
		}
	}

	box->file->tmp_umstimmung = (umstimmung*) xmalloc (box, (size_t) sizeof (struct umstimmung));

	box->file->tmp_umstimmung -> name            = name;
	box->file->tmp_umstimmung -> parameter_liste = NULL;
	box->file->tmp_umstimmung -> next            = NULL;
}

inline static void link_arguments_to_parameters(mutabor_box_type * box,
						struct argument_list * arguments,
						struct parameter_list * parameters,
						struct umstimmung * retuning)
{
	for (argument_list * entry = arguments;
	     entry; entry = entry -> next) {
		switch (entry->argument.argument_type) {
		case mutabor_argument_parameter: {
			entry->argument.u.parameter.parameter
				= get_parameter_by_name(box, 
							entry->argument.u.parameter.name,
							parameters);

			if (entry->argument.u.parameter.parameter == NULL) {
				mutabor_error_message(box,
						      compiler_error,
						      _("Undefined parameter name “%s” in “%s”."),
						      entry->argument.u.parameter.name,
						      retuning->name); /* Parameter n.dekl. */
			}
			break;
		}
		case mutabor_argument_integer:
		case mutabor_argument_distance:
		case mutabor_argument_anchor:
			break;
		default:
			mutabor_error_message(box,
					      internal_error,
					      _("Invalid parameter argument type %d in retuning “%s” while calling %s. Please, report the error to the MUTABOR team."),
					      entry->argument.argument_type,
					      retuning->name,
					      __FUNCTION__);
		}
	}
}

void get_new_umstimmung (mutabor_box_type * box)

{

	struct umstimmung * * lauf;
	TRACE;
	link_arguments_to_parameters(box, 
				     box->file->tmp_umstimmung -> argument_liste, 
				     box->file->tmp_umstimmung -> parameter_liste, 
				     box->file->tmp_umstimmung);
	for (lauf= & box->file->list_of_umstimmungen; * lauf; lauf= & (*lauf)->next) {}
	(* lauf) = box->file->tmp_umstimmung;
	
}





void eintrage_parameterliste_in_umstimmung (mutabor_box_type * box,
					    struct umstimmung * ret,
					    parameter_list * list)
{
	TRACE;
	ret -> parameter_liste = list;
}

/************ Die folgenden Funktionen tragen je eine         */
/*            Version von Umstimmung ein.                     */
/*            Genau eine dieser Funktionen wird zwischen      */
/*            init_umstimmung ()                              */
/*            und                                             */
/*            get_new_umstimmung (name)                       */
/*            aufgerufen.                                     */

void get_umstimmung_taste_abs (mutabor_box_type * box,
			       argument_list *  argument)
{
	TRACE;
	box->file->tmp_umstimmung -> umstimmung_typ  = umstimmung_taste_abs;
	box->file->tmp_umstimmung -> argument_liste = argument;
	//	box->file->tmp_umstimmung -> parameter_liste = get_new_name_in_parameterlist (box, _("key"));
}

void get_umstimmung_taste_rel (mutabor_box_type * box, 
			       argument_list * argument,
			       char vorzeichen)
{
	TRACE;
	box->file->tmp_umstimmung -> umstimmung_typ = umstimmung_taste_rel;
	box->file->tmp_umstimmung -> u.umstimmung_taste_rel.rechenzeichen = vorzeichen;
	box->file->tmp_umstimmung -> argument_liste = argument;
	//	box->file->tmp_umstimmung -> parameter_liste = get_new_name_in_parameterlist (box, _("key difference"));
}

void get_umstimmung_breite_abs (mutabor_box_type * box, 
				argument_list * argument)
{
	TRACE;
	box->file->tmp_umstimmung -> umstimmung_typ = umstimmung_breite_abs;
	box->file->tmp_umstimmung -> argument_liste = argument;
	// box->file->tmp_umstimmung -> parameter_liste = get_new_name_in_parameterlist (box, _("width"));
}

void get_umstimmung_breite_rel (mutabor_box_type * box, 
				argument_list * argument,
				char vorzeichen)
{
	TRACE;
	box->file->tmp_umstimmung -> umstimmung_typ = umstimmung_breite_rel;
	box->file->tmp_umstimmung -> argument_liste = argument;
	box->file->tmp_umstimmung -> u.umstimmung_breite_rel.rechenzeichen
		= vorzeichen;
	// box->file->tmp_umstimmung -> parameter_liste = get_new_name_in_parameterlist (box, _("width difference"));
}

/*********** Bei "tonhîhe verÑndert" muû wieder die gesamte
             expression eines Tons pro Listeneintrag
             aufgesammelt werden.
********/

void init_umstimm_expression_list (mutabor_box_type * box)
{
	TRACE;
	box->file->tmp_tonliste = NULL;
}

void get_new_umstimm_expression (mutabor_box_type * box, 
				 const char * bezugston)

{

	struct ton * * lauf;
	TRACE;

	for (lauf= & box->file->tmp_tonliste; * lauf; lauf= & (*lauf)->next)
		/* Nur Ende der Liste finden */ ;

	(* lauf) = (ton*) xmalloc (box, (size_t) sizeof (struct ton));

	(* lauf) -> name                    = bezugston;

	(* lauf) -> ton_typ                 = ton_komplex;

	(* lauf) -> u.ton_komplex.bezugston = bezugston;

	(* lauf) -> u.ton_komplex.komplex_liste = NULL;

	(* lauf) -> next                    = NULL;

}


void get_new_umstimm_expression_positive (mutabor_box_type * box,
					  const char * bezugston)

{

	struct ton * * lauf;

	for (lauf= & box->file->tmp_tonliste; * lauf; lauf= & (*lauf)->next)
		/* Nur Ende der Liste finden */ ;

	(* lauf) = (ton*) xmalloc (box, (size_t) sizeof (struct ton));

	(* lauf) -> name                    = bezugston;

	(* lauf) -> ton_typ                 = ton_komplex;

	(* lauf) -> u.ton_komplex.bezugston = bezugston;

	(* lauf) -> u.ton_komplex.komplex_liste = get_last_komplex_intervall (box);

	(* lauf) -> next                    = NULL;

}


void get_new_umstimm_expression_negative (mutabor_box_type * box, const char * bezugston)

{

	struct ton * * lauf;
	TRACE;

	for (lauf= & box->file->tmp_tonliste; * lauf; lauf= & (*lauf)->next)
		/* Nur Ende der Liste finden */ ;

	(* lauf) = (ton*) xmalloc (box, (size_t) sizeof (struct ton));

	(* lauf) -> name                    = bezugston;

	(* lauf) -> ton_typ                 = ton_komplex;

	(* lauf) -> u.ton_komplex.bezugston = bezugston;

	{

		struct komplex_intervall * help = get_last_komplex_intervall (box);
		help->faktor *= -1.0;
		(* lauf) -> u.ton_komplex.komplex_liste = help;
	}

	(* lauf) -> next                    = NULL;

}


void get_umstimmung_tonhoehe_veraendert (mutabor_box_type * box)

{
	box->file->tmp_umstimmung -> umstimmung_typ = umstimmung_toene_veraendert;
	box->file->tmp_umstimmung -> u.umstimmung_toene_veraendert.tonliste
		= box->file->tmp_tonliste;
}

void get_umstimmung_wiederholung_abs (mutabor_box_type * box)
{
	box->file->tmp_umstimmung -> umstimmung_typ = umstimmung_wiederholung_abs;
	box->file->tmp_umstimmung -> u.umstimmung_wiederholung_abs.komplex_liste
		= get_last_komplex_intervall (box);
}

void get_umstimmung_wiederholung_abs_negative (mutabor_box_type * box)
{
	box->file->tmp_umstimmung -> umstimmung_typ = umstimmung_wiederholung_abs;
	{

		struct komplex_intervall * help = get_last_komplex_intervall (box);

		if (help == NULL)
			mutabor_error_message(box,
					      internal_error,
					      _("Internal error at\n%s:%d"),
					      _T(__FILE__),
					      __LINE__);
		else
			help -> faktor *= -1.0;

		box->file->tmp_umstimmung ->
			u.umstimmung_wiederholung_abs.komplex_liste = help;
	}
}


void get_umstimmung_wiederholung_rel_positive (mutabor_box_type * box)
{
	TRACE;
	box->file->tmp_umstimmung -> umstimmung_typ = umstimmung_wiederholung_rel;
	box->file->tmp_umstimmung -> u.umstimmung_wiederholung_rel.
		komplex_liste = get_last_komplex_intervall (box);
}

void get_umstimmung_wiederholung_rel_negative (mutabor_box_type * box)
{
	TRACE;
	box->file->tmp_umstimmung -> umstimmung_typ = umstimmung_wiederholung_rel;
	box->file->tmp_umstimmung -> u.umstimmung_wiederholung_rel.
		komplex_liste = get_last_komplex_intervall (box);

	box->file->tmp_umstimmung -> u.umstimmung_wiederholung_rel.
		komplex_liste -> faktor      *= - 1.0 ;
}

/*********** Bei "umstimmungsbund" muû wieder eine Liste von
             Aufrufen (mit evtl. Parametern)
             aufgesammelt werden.
********/

/*
  void init_aufruf_liste (void)
  {
  tmp_aufruf_liste = NULL;
  }
*/
#if 0

void get_umstimmungs_bund_element (const char * name)
{

	struct umstimmung * * lauf;
	TRACE;

	for (lauf= & box->file->tmp_umstimmungsbund_liste;
	     * lauf;
	     lauf= & (*lauf)->next)
		/* Nur Ende der Liste finden */ ;

	(* lauf) = xmalloc (sizeof (struct umstimmung));

	(* lauf) -> name                = name;

	(* lauf) -> parameterliste      = get_last_parameter_liste ();

	(* lauf) -> next                = NULL;

	/* check, ob die Parameter zulÑssig sind */

	{

		struct namensliste * params;

		for (params = (* lauf) -> parameterliste;
		     params;
		     params = params -> next ) {
			if (parameter_nummer (box,
					      params->name,
			                      box->file->tmp_umstimmung -> parameterliste)  == EOF ) {
				mutabor_error_message(box,
internal_error,
						      _T("Error 31"),(params->name),((*lauf)->name)); /* Parameter n.dekl. */
			}
		}
	}

}

#endif

void get_umstimmung_umstimmungs_bund (mutabor_box_type * box)
{
	TRACE;
	box->file->tmp_umstimmung -> umstimmung_typ = umstimmung_umstimmungsbund;
	box->file->tmp_umstimmung -> u.umstimmung_umstimmungsbund
		.aktions_liste = get_last_aktions_liste (box);


	/* check for valid parameters */

	{

		struct aktions_liste * aktions_lauf;

		for (aktions_lauf = box->file->tmp_umstimmung -> u.umstimmung_umstimmungsbund.aktions_liste;
		     aktions_lauf;
		     aktions_lauf = aktions_lauf -> next) {

			if (aktions_lauf -> aktions_typ == aktion_aufruf) {


				link_arguments_to_parameters(box,
							    aktions_lauf -> u.aktion_aufruf.argument_liste,
							    box->file->tmp_umstimmung -> parameter_liste,
							    box->file->tmp_umstimmung);

#if 0							    
				struct argument_list * argument_lauf;

				for (argument_lauf = aktions_lauf -> u.aktion_aufruf.argument_liste;
				     argument_lauf;
				     argument_lauf = argument_lauf -> next ) {
#warning make switch
					if (argument_lauf -> argument.argument_type 
					    == mutabor_argument_parameter) {
					    struct parameter_list * param
						= get_parameter_by_name (box,
									 argument_lauf->argument.u.parameter.name,
									 box->file->tmp_umstimmung -> parameter_liste);
						if (param == NULL ) {
							mutabor_error_message(box,
									      compiler_error,
									      _("Undefined parameter name “%s” in “%s”."),
									      (argument_lauf->argument.u.parameter.name),
									      (box->file->tmp_umstimmung->name)); /* Parameter n.dekl. */
						} else {
							argument_lauf->argument.u.parameter.parameter = param;
						} /* if */
					} /* if */
				}  /* for argument_lauf */
#endif
			}  /* if (aktions_lauf... */
		}  /* for aktions_lauf */
	}



}


/***********************************
      case Umstimmungen:
***********************************/
#if 0

static struct aufruf_liste * tmp_umstimmungs_case_aufrufs_liste;


void init_umstimmungs_case_aufrufs_liste (void)
{
	TRACE;
	box->file->tmp_umstimmungs_case_aufrufs_liste = NULL;
}

static struct umstimmung * get_last_umstimmungs_case_aufrufs_liste (void)
{
	TRACE;
	return box->file->tmp_umstimmungs_case_aufrufs_liste;
}


void get_umstimmungs_case_aufrufs_element (const char * aktion)

{

	struct aufruf_liste * * lauf;
	TRACE;

	for (lauf= & box->file->tmp_umstimmungs_case_aufrufs_liste;
	     * lauf;
	     lauf= & (*lauf)->next)
		/* Nur Ende der Liste finden */ ;

	(* lauf) = xmalloc (sizeof (struct aufruf_liste));
	(* lauf) -> name                = aktion;
	(* lauf) -> argument_liste      = get_last_argument_liste ();
	(* lauf) -> next                = NULL;

	/* check, ob die Parameter zulÑssig sind */

	{

		struct argument_liste * params;

		for (params = (* lauf) -> argument_liste;
		     params;
		     params = params -> next ) {
			if (params -> argument.argument_typ == parameter) {
				if (parameter_nummer (box,
						      params->argument.u.parameter.parameter_name,
				                      box->file->tmp_umstimmung -> parameter_liste)  == EOF ) {
					mutabor_error_message(box,
							      _T("Parameter “%s” could not been found in call to '%s'."),
					            (params->argument.u.parameter.parameter_name),
					            ((*lauf)->name)); /* Parameter n.dekl. */
				}
			}
		}
	}

}

#endif

 void get_umstimmungs_case_zahl_element (mutabor_box_type * box, int konstante)
{

	struct case_liste * * lauf;
	TRACE;

	for (lauf= & box->file->tmp_umstimmungs_case_liste;
	     * lauf;
	     lauf= & (*lauf)->next)
		/* Nur Ende der Liste finden */ ;

	(* lauf) = (case_liste*) xmalloc (box, sizeof (struct case_liste));
	(* lauf) -> case_label          = konstante;
	(* lauf) -> is_default          = 0;
	(* lauf) -> case_aktion         = get_last_aktions_liste (box);
	(* lauf) -> next                = NULL;
}

void get_umstimmungs_case_default_element (mutabor_box_type * box)

{

	struct case_liste * * lauf;
	TRACE;

	for (lauf= & box->file->tmp_umstimmungs_case_liste;
	     * lauf;
	     lauf= & (*lauf)->next)
		/* Nur Ende der Liste finden */ ;

	(* lauf) = (case_liste*) xmalloc (box, sizeof (struct case_liste));
	(* lauf) -> case_label          = MUTABOR_NO_CASE_LABEL; /* als dummy-xwert */
	(* lauf) -> is_default          = 1;
	(* lauf) -> case_aktion         = get_last_aktions_liste (box);
	(* lauf) -> next                = NULL;
}



void init_umstimmungs_case_liste (mutabor_box_type * box)
{
	TRACE;
	box->file->tmp_umstimmungs_case_liste = NULL;
}

void get_umstimmung_umstimm_case (mutabor_box_type * box,
				  argument_list *  argument)
{
	TRACE;
	box->file->tmp_umstimmung -> umstimmung_typ = umstimmung_umstimmungs_case;
	box->file->tmp_umstimmung -> argument_liste = argument;
	box->file->tmp_umstimmung -> u.umstimmung_umstimmungs_case
		.umstimmungs_case_liste = box->file->tmp_umstimmungs_case_liste;
	// box->file->tmp_umstimmung -> parameter_liste = get_new_name_in_parameterlist (box, _("choice"));

	/* check, ob die Parameter zulÑssig sind */

	{
			
		struct case_liste * case_lauf;

		for (case_lauf = box->file->tmp_umstimmung -> u.umstimmung_umstimmungs_case
			     .umstimmungs_case_liste ;
		     case_lauf;
		     case_lauf = case_lauf -> next) {

			struct aktions_liste * aktions_lauf;

			for (aktions_lauf = case_lauf -> case_aktion;
			     aktions_lauf;
			     aktions_lauf = aktions_lauf -> next) {

				if (aktions_lauf -> aktions_typ != aktion_aufruf) 
					continue;

				link_arguments_to_parameters(box,
							     aktions_lauf -> u.aktion_aufruf.argument_liste,
							     box->file->tmp_umstimmung -> parameter_liste,
							     box->file->tmp_umstimmung);
#if 0
				struct argument_list * argument_lauf;

				for (argument_lauf = aktions_lauf -> u.aktion_aufruf.argument_liste;
				     argument_lauf;
				     argument_lauf = argument_lauf -> next ) {
#warning make switch
					if (argument_lauf -> argument.argument_type != mutabor_argument_parameter)
						continue;
					struct parameter_list * param 
					    = get_parameter_by_name (box,
								     argument_lauf->argument.u.parameter.name,
								     box->file->tmp_umstimmung -> parameter_liste);

					if (param == NULL) {
						mutabor_error_message(box,
								      compiler_error,
								      _("Undefined parameter name “%s” in “%s”."),
								      (argument_lauf->argument.u.parameter.name),
								      (box->file->tmp_umstimmung->name)); /* Parameter n.dekl. */
					} else {
						argument_lauf->argument.u.parameter.parameter = param;
					} /* if */
				}  /* for argument_lauf */
#endif
			}  /* for aktions_lauf */
		}  /* for case_lauf */
	}


}

#if 0
 void get_umstimmung_umstimm_case_parameter (mutabor_box_type * box, const char * selector)
{
	TRACE;
	box->file->tmp_umstimmung -> umstimmung_typ = umstimmung_umstimmungs_case;
	initialize_argument(box,
			    &(box->file->tmp_umstimmung -> u.umstimmung_umstimmungs_case
			      .argument),
			    mutabor_argument_parameter,
			    0, 
			    selector);
	box->file->tmp_umstimmung -> u.umstimmung_umstimmungs_case
		.umstimmungs_case_liste = box->file->tmp_umstimmungs_case_liste;

#if 0
	/* arguments to actions are checked as soon as they are parsed 
	   this will change when we use return parameters of reduction rules.
	   Then, this part must be rewritten and reactivated */
	/* check whether the argumets are valid */
	{

	    struct case_liste * case_lauf;

	    for (case_lauf = box->file->tmp_umstimmung -> u.umstimmung_umstimmungs_case
		     .umstimmungs_case_liste ;
		 case_lauf;
		 case_lauf = case_lauf -> next) {

		struct aktions_liste * aktions_lauf;

		for (aktions_lauf = case_lauf -> case_aktion;
		     aktions_lauf;
		     aktions_lauf = aktions_lauf -> next) {

		    if (aktions_lauf -> aktions_typ != aktion_aufruf) 
			continue;

		    struct argument_list * argument_lauf;

		    for (argument_lauf = aktions_lauf -> u.aktion_aufruf.argument_liste;
			 argument_lauf;
			 argument_lauf = argument_lauf -> next ) {
#warning make extra function assign_parameters_to_arguments
			if (argument_lauf -> argument.argument_type == mutabor_argument_parameter) 
			    continue;
			int i = parameter_nummer (box,
						  argument_lauf->argument.u.parameter.parameter_name,
						  box->file->tmp_umstimmung -> parameter_liste);

			if (i == EOF ) {
			    mutabor_error_message(box,
						  compiler_error,
						  _("Undefined parameter name “%s” in “%s”."),
						  (argument_lauf->argument.u.parameter.parameter_name),
						  (box->file->tmp_umstimmung->name)); /* Parameter n.dekl. */
			} else {
			    argument_lauf->argument.u.parameter.parameter_number = i;
			} /* if */
		    }  /* for argument_lauf */
		}  /* for aktions_lauf */
	    }  /* for case_lauf */
	}
#endif
}
#endif


void get_umstimmung_midi_out (mutabor_box_type * box)

{
	TRACE;
	box->file->tmp_umstimmung -> umstimmung_typ = umstimmung_midi_out;
	box->file->tmp_umstimmung -> u.umstimmung_midi_out.out_liste
		= get_last_integersequenz (box);
}




/******* Einlesen der Harmonien. Pro Harmonie wird eine
         Liste von Tasten festgehalten.
*******/

void init_tastenliste (mutabor_box_type * box)
{
	TRACE;
	box->file->tmp_tastenliste = NULL;
}

 void get_new_taste (mutabor_box_type * box, int taste, char stern)

{

	struct taste * * lauf;
	TRACE;

	for (lauf= & box->file->tmp_tastenliste; * lauf; lauf= & (*lauf)->next)
		/* Nur Ende der Liste finden */ ;

	(* lauf) = (struct taste*) xmalloc (box, sizeof (struct taste));

	(* lauf) -> code               = taste;

	(* lauf) -> stern               = stern;

	(* lauf) -> next                = NULL;

}

 void get_new_harmonie (mutabor_box_type * box, const char * name, int bezugstaste)
{

	struct harmonie * * lauf;
	TRACE;

	for (lauf= & box->file->list_of_harmonien; * lauf; lauf= & (*lauf)->next) {
		if ( ! strcasecmp (name, (*lauf)->name)) {
			mutabor_error_message(box,
					      compiler_error,
					      _("The pattern name %s was used twice"),
					      (name)); /* Harmoniename doppelt */
		}
	}

	(* lauf) = (harmonie*) xmalloc (box, sizeof (struct harmonie));
	(* lauf) -> name                = name;
	(* lauf) -> tastenliste         = box->file->tmp_tastenliste;
	(* lauf) -> bezugstaste         = bezugstaste;
	(* lauf) -> next                = NULL;

}

/******* Einlesen der Logiken. Pro Logik wird eine
         Liste von Anweisungen festgehalten.
*******/


#if 0

static struct aktion * tmp_aktion;

struct aktion * get_last_aktion (void)
{
	TRACE;
	return tmp_aktion;
}

void get_aktion_midi_out (void)

{
	TRACE;
	tmp_aktion = xmalloc (box, sizeof (struct aktion));
	tmp_aktion -> aktions_typ = aktion_midi_out;
	tmp_aktion -> u.aktion_midi_out.midi_code   = get_last_integersequenz ();
}

void get_aktion_aufruf (const char * name)
{
	TRACE;

	tmp_aktion = xmalloc (box, sizeof (struct aktion));
	tmp_aktion -> aktions_typ = aktion_aufruf;
	tmp_aktion -> u.aktion_aufruf.name        = name;
	tmp_aktion -> u.aktion_aufruf.argument_liste
		= get_last_argument_liste ();
}


#endif



 void get_harmoniebezeichner (mutabor_box_type * box,
			      int vor_taste,
			      const char * name,
			      int nach_taste)
{
	box->file->tmp_vor_taste   = vor_taste;
	box->file->tmp_name        = name;
	box->file->tmp_nach_taste  = nach_taste;
}


void init_ausloeser (mutabor_box_type * box)
{
	TRACE;
	box->file->tmp_ausloeser = NULL;
}

struct ausloeser * get_last_ausloeser (mutabor_box_type * box)
{
	TRACE;
	return box->file->tmp_ausloeser;
}

void get_ausloeser_default (mutabor_box_type * box)

{
	TRACE;

	box->file->tmp_ausloeser = (ausloeser*) xmalloc (box, sizeof (struct ausloeser));
	box->file->tmp_ausloeser -> ausloeser_typ = ausloeser_default;
}

void get_ausloeser_harmonie (mutabor_box_type * box)
{
	TRACE;

	box->file->tmp_ausloeser = (ausloeser*) xmalloc (box, sizeof (struct ausloeser));
	box->file->tmp_ausloeser -> ausloeser_typ = ausloeser_harmonie;
	box->file->tmp_ausloeser -> u.ausloeser_harmonie.vortaste  = box->file->tmp_vor_taste;
	box->file->tmp_ausloeser -> u.ausloeser_harmonie.name      = box->file->tmp_name;
	box->file->tmp_ausloeser -> u.ausloeser_harmonie.nachtaste = box->file->tmp_nach_taste;
}

void get_ausloeser_harmonie_form (mutabor_box_type * box)
{
	TRACE;

	box->file->tmp_ausloeser = (ausloeser*) xmalloc (box, sizeof (struct ausloeser));
	box->file->tmp_ausloeser -> ausloeser_typ = ausloeser_harmonie_form;
	box->file->tmp_ausloeser -> u.ausloeser_harmonie_form.vortaste  = box->file->tmp_vor_taste;
	box->file->tmp_ausloeser -> u.ausloeser_harmonie_form.name      = box->file->tmp_name;
	box->file->tmp_ausloeser -> u.ausloeser_harmonie_form.nachtaste = box->file->tmp_nach_taste;
}

 void get_ausloeser_taste (mutabor_box_type * box, const char * name)
{
	TRACE;

	box->file->tmp_ausloeser = (ausloeser*) xmalloc (box, sizeof (struct ausloeser));
	box->file->tmp_ausloeser -> ausloeser_typ = ausloeser_taste;
	box->file->tmp_ausloeser -> u.ausloeser_taste.taste  = name;

	if (strlen (name) != 1) {
		mutabor_error_message(box,
				      compiler_error,
				      _("A Key needs to be a single character (got “%s”)"),
				      (name));
	}

}

void get_ausloeser_midi_in (mutabor_box_type * box)

{
	TRACE;

	box->file->tmp_ausloeser = (ausloeser*) xmalloc (box, sizeof (struct ausloeser));
	box->file->tmp_ausloeser -> ausloeser_typ = ausloeser_midi_in;
	box->file->tmp_ausloeser -> u.ausloeser_midi_in.midi_code
		= get_last_integersequenz (box);
}








 void init_anweisungs_liste (mutabor_box_type * box)
{
	TRACE;
	box->file->tmp_anweisungsliste = NULL;
}

struct anweisung * get_last_anweisungs_liste (mutabor_box_type * box)
{
	TRACE;
	return box->file->tmp_anweisungsliste ;
}

void get_new_anweisung (mutabor_box_type * box)

{

	struct anweisung * * lauf;
	TRACE;

	for (lauf= & box->file->tmp_anweisungsliste; * lauf; lauf= & (*lauf)->next)
		/* Nur Ende der Liste finden */ ;

	(* lauf) = (anweisung*) xmalloc (box, sizeof (struct anweisung));
	(* lauf) -> ausloeser   = get_last_ausloeser (box);
	(* lauf) -> aktion      = get_last_aktions_liste (box);
	(* lauf) -> next        = NULL;

}

 void get_new_logik (mutabor_box_type * box, const char * name, const char * einstimmung)
{

	struct logik * * lauf;
	TRACE;

	for (lauf= & box->file->list_of_logiken; * lauf; lauf= & (*lauf)->next) {
		if ( ! strcasecmp (name, (*lauf)->name)) {
			mutabor_error_message(box,
					      compiler_error,
					      _("The logic name %s was used twice"),
					      (name)); /* Logikname doppelt */
		}
	}

	(* lauf) = (logik*) xmalloc (box, sizeof (struct logik));
	(* lauf) -> name                = name;
	(* lauf) -> ausloeser           = get_last_ausloeser (box);
	(* lauf) -> einstimmungs_name   = einstimmung;
	(* lauf) -> anweisungsliste     = NULL;
	(* lauf) -> harmony_list        = NULL;
	(* lauf) -> keystroke_list      = NULL;
	(* lauf) -> midi_input_list     = NULL;
	(* lauf) -> next                = NULL;

}

void vervollstaendige_logik (mutabor_box_type * box)

{

	struct logik * lauf;
	TRACE;

	for (lauf = box->file->list_of_logiken; lauf -> next; lauf = lauf->next) {}

	lauf -> anweisungsliste     = get_last_anweisungs_liste (box);
}

/******* Einlesen der Instrumente *******/

 void get_instrument_dekl (mutabor_box_type * box, 
			   int midi_in, 
			   int midi_von, 
			   int midi_bis, 
			   int midi_umleit,
			   struct instrument ** list_to_insert)
{
	TRACE;
	/**///for (list_to_insert = & list_of_instrumente;

	for (;
	     * list_to_insert;
	     list_to_insert = & (*list_to_insert)->next)
		{
			if ( midi_in == (*list_to_insert)->midi_in) {
				mutabor_error_message(box,
						      compiler_error,
						      _("The MIDI-Instrument %d was used twice"),
						      midi_in); /* MIDI-Instrument doppelt */
			}
		}

	if ( midi_von > midi_bis )
		{
			int temp = midi_von;
			/* Vertauschen der Reihenfolge */
			midi_von=midi_bis;
			midi_bis=temp;

		}

	if ( (midi_in < 1) || (midi_in > 16) )
		{
			mutabor_error_message(box,
					      compiler_error,
					      _("Bad MIDI channel %d (valid: 1...16)"),
					      midi_in);
		}

	if ( midi_von && midi_bis )
		{
			if ( (midi_von < 1) || (midi_von > 16) )
				mutabor_error_message(box,
						      compiler_error,
						      _("Bad MIDI from channel %d (valid: 1...16)"),
						      midi_von);
			
			if ( (midi_bis < 1) || (midi_bis > 16) )
				mutabor_error_message(box,
						      compiler_error,
						      _("Bad MIDI to channel %d (valid: 1...16)"),
						      midi_bis);
		}

	if ( (midi_umleit < 0) || (midi_umleit > 16) )
		{
			mutabor_error_message(box,
					      compiler_error,
					      _("Bad MIDI rerouting channel %d (valid: 1...16)"),
					      midi_umleit);
		}


	(* list_to_insert) = (instrument*) xmalloc (box, sizeof (struct instrument));
	(* list_to_insert) -> midi_in             = midi_in;
	(* list_to_insert) -> midi_von            = midi_von;
	(* list_to_insert) -> midi_bis            = midi_bis;
	(* list_to_insert) -> midi_umleit         = midi_umleit;
	(* list_to_insert) -> next                = NULL;

}

static void belege_toene (struct ton **toene, struct ton * liste)
{
	TRACE;
	while (liste)
		{
			*toene = liste;
			toene++;
			liste = liste->next;
		}
}

 static int ton_nummer (mutabor_box_type * box, 
			const char *name)
{
	int i;

	TRACE;
	for (i=0; i<box->file->anzahl_toene; i++)
		if ( ! strcasecmp (name, box->file->toene[i]->name)) return i;

	mutabor_error_message(box,
			      compiler_error,
			      _("Undefined tone: %s"),
			      (name)); /* Ton n.dekl. */

	return 0; /* to prevent warnings */
}

 static void test_zyklen (mutabor_box_type * box, int startknoten)
{
	int i;

	TRACE;
	for (i=0; i<box->file->anzahl_toene; i++) {
		if (mutabor_adjacent (box->file->tone_matrix, startknoten, i)) {
			if (box->file->visited_tones [i]) {
				mutabor_error_message(box,
						      compiler_error,
						      _("Tones %s and %s depend on each other."),
						      (box->file->toene [startknoten]->name),
						      (box->file->toene [i]->name));
			}

			box->file->visited_tones [i] = 1;

			test_zyklen (box,i);
			box->file->visited_tones [i] = 0;
		}
	}
}

static void berechne_ton_endgueltig (mutabor_box_type * box, int k)
{
	int b;
	double help, help2;
	TRACE;

	switch (box->file->toene[k]->ton_typ) {

	case ton_absolut:         /* hier nichts zu tun */
		break;

	case ton_komplex:
		b = ton_nummer (box,box->file->toene[k]->u.ton_komplex.bezugston);

		berechne_ton_endgueltig (box,b);

		help2 = get_wert_komplex_intervall (box,
						    box->file->toene[k]->u.ton_komplex.komplex_liste);

		help = box->file->toene[b]->u.ton_absolut.ton_wert;

		box->file->toene[k]->ton_typ = ton_absolut;

		box->file->toene[k]->u.ton_absolut.ton_wert = help * help2;

		break;

	default:
		mutabor_error_message(box,
				      internal_error,
				      _("Invalid tone type %d detected at\n%s:%d"),
				      box->file->toene[k]->ton_typ,
				      (__FILE__),
				      __LINE__);
	}
}

 static void berechne_toene_absolut (mutabor_box_type * box, struct ton *list_of_toene)
{
	int i,j,k;

	TRACE;
	box->file->anzahl_toene = ton_list_laenge (list_of_toene);

	box->file->toene = (ton* *) xalloca (box, sizeof(struct ton *) * box->file->anzahl_toene);
	box->file->visited_tones = (char*) xalloca (box, sizeof(char) * box->file->anzahl_toene);
	box->file->tone_matrix = (char*) xalloca (box, sizeof(char) * box->file->anzahl_toene * box->file->anzahl_toene);


	/* Feld mit toenen initialisieren (zum schnelleren Zugriff) */

	belege_toene (box->file->toene, list_of_toene);

	/* Adjazenzmatrix initialisieren (Kein Ton hÑngt vom anderen ab) */

	for (i=0; i<box->file->anzahl_toene; i++)
		{
			for (j=0; j<box->file->anzahl_toene; j++) {
				mutabor_adjacent (box->file->tone_matrix, i,j) = 0;
			}
		}

	/* Adjazenzmatrix initialisieren (AbhÑngigkeiten eintragen) */

	for (i=0; i<box->file->anzahl_toene; i++)
		{
			switch (box->file->toene[i]->ton_typ) {
			case ton_absolut: break;  /* alles ok */ ;
			case ton_komplex:
				mutabor_adjacent (box->file->tone_matrix, 
						  i, 
						  ton_nummer (box, box->file->toene[i]->u.ton_komplex.bezugston)) = 1;
				break;
			default:
				mutabor_error_message(box,
						      internal_error,
						      _("Invalid tone type %d detected at\n%s:%d"),
						      box->file->toene[i]->ton_typ,
						      (__FILE__),
						      __LINE__);
			}
		}

#ifdef DEBUG
	/* Adjazenzmatrix anzeigen */
	if (isDebugFlag(kernel_parser)) {
		printf ("Matrix:\n");

		for (i=0; i<box->file->anzahl_toene; i++)
			{
				printf ("%s -> ", box->file->toene[i]->name);

				for (j=0; j<box->file->anzahl_toene; j++) {
					if (mutabor_adjacent (box->file->tone_matrix, i,j))
						printf ("%s  ", box->file->toene[j]->name);
				}
			
				printf ("\n");
			}

		printf ("\n");
	}

#endif

	/* auf Zyklenfreiheit Pruefen */

	for (k=0; k<box->file->anzahl_toene; k++)
		box->file->visited_tones [k] = 0;

	for (k=0; k<box->file->anzahl_toene; k++)
		{
			box->file->visited_tones [k] = 1;
			test_zyklen (box,k);
			box->file->visited_tones [k] = 0;
		}

	/* Toene endgueltig berechnen */

	for (k=0; k<box->file->anzahl_toene; k++)
		berechne_ton_endgueltig (box, k);

#ifdef DEBUG
	/* Adjazenzmatrix anzeigen */

	if (isDebugFlag(kernel_parser)) {
		printf ("Matrix:\n");

		for (i=0; i<box->file->anzahl_toene; i++)
			{
				printf ("%s -> ", box->file->toene[i]->name);

				for (j=0; j<box->file->anzahl_toene; j++) {
					if (mutabor_adjacent (box->file->tone_matrix, i,j))
						printf ("%s  ", box->file->toene[j]->name);
				}

				printf ("\n");
			}

		printf ("\n");
	}
#endif

	xde_alloca (box->file->toene);
	xde_alloca (box->file->visited_tones);
	xde_alloca (box->file->tone_matrix);

}

/************** Hier wird die innere Konsistenz des
                ganzen MUTABOR-Programms geprÅft.
                Bei Fehlern wird einfach abgebrochen,
                ansonsten hat diese Funktion keine
                verÑndernde Wirkung auf die Listen.

                Eintrittspunkt ist "check_konsistenz".

**************/

int enthalten_in_tastenliste (int taste, struct taste * lauf)
{
	TRACE;
	while (lauf)
		if (lauf -> code == taste)
			return 1;
		else
			lauf = lauf -> next;

	return 0;
}


int case_label_enthalten_in_case_liste (double case_label, struct case_liste * lauf)
{
	TRACE;
	if (lauf == NULL)
		return 0;
	else if ( ! lauf -> is_default  &&
		  ( (int)(case_label) == (int)(lauf -> case_label) ) )
		return 1;
	else
		return case_label_enthalten_in_case_liste (case_label, lauf -> next);
}


 static void check_ausloeser (mutabor_box_type * box, struct ausloeser * ausloeser, const char * name)
{

	struct harmonie * help_harmonie;
	TRACE;

	if (ausloeser == NULL) return;

	if (ausloeser->ausloeser_typ == ausloeser_harmonie_form)
		{
			help_harmonie = get_harmonie (ausloeser->u.ausloeser_harmonie_form.name,
						      box->file->list_of_harmonien);

			if (help_harmonie == NULL) {
				mutabor_error_message(box,
						      compiler_error,
						      _("Undefined harmony “%s” in logic %s."),
						      (ausloeser->u.ausloeser_harmonie_form.name),
						      (name));
			}

			if (enthalten_in_tastenliste(ausloeser->u.ausloeser_harmonie_form.vortaste,
						     help_harmonie->tastenliste)
			    || ausloeser->u.ausloeser_harmonie_form.vortaste == MUTABOR_NO_KEY ) {
				/* OK */
			} else {
				mutabor_error_message(box,
						      compiler_warning,
						      _("Lowest chroma %d of harmonic form %s in logic %s is not a member of that harmony. This harmonic form trigger will be ignored."),
						      ausloeser->u.ausloeser_harmonie_form.vortaste,
						      (ausloeser->u.ausloeser_harmonie_form.name),
						      (name));
				/* Markierung setzen, fuer unmoeglichen Ausloeser */
				ausloeser->u.ausloeser_harmonie_form.vortaste = MUTABOR_INVALID_KEY;
			}

			if (enthalten_in_tastenliste
			    (ausloeser->u.ausloeser_harmonie_form.nachtaste,
			     help_harmonie->tastenliste) ||
			    ausloeser->u.ausloeser_harmonie_form.nachtaste
			    == MUTABOR_NO_KEY ) {
				/* OK */
			} else {
				mutabor_error_message(box,
						      compiler_warning,
						      _("Highest chroma %d of harmonic form %s in logic %s is not a member of that harmony. This harmonic form trigger will be ignored."),
						      ausloeser->u.ausloeser_harmonie_form.nachtaste,
						      (ausloeser->u.ausloeser_harmonie_form.name),
						      (name));
				/* Markierung setzen, fuer unmoeglichen Ausloeser */
				ausloeser->u.ausloeser_harmonie_form.nachtaste = MUTABOR_INVALID_KEY;
			}
		}


	if (ausloeser->ausloeser_typ == ausloeser_harmonie)
		{
			help_harmonie = get_harmonie (ausloeser->u.ausloeser_harmonie.name, box->file->list_of_harmonien);

			if (help_harmonie == NULL) {
				mutabor_error_message(box,
						      compiler_error,
						      _("Undefined harmony: %s (in logic %s)"),
						      
						      (ausloeser->u.ausloeser_harmonie.name),
						      (name));
			}

			if (enthalten_in_tastenliste
			    (ausloeser->u.ausloeser_harmonie.vortaste,
			     help_harmonie->tastenliste) ||
			    ausloeser->u.ausloeser_harmonie.vortaste
			    == MUTABOR_NO_KEY ) {
				/* OK */
			} else {
				mutabor_error_message(box,
						      compiler_warning,
						      _("Lowest chroma %d of harmony %s in logic %s is not a member of that harmony. This harmony trigger will be ignored."),
						      ausloeser->u.ausloeser_harmonie.vortaste,
						      (ausloeser->u.ausloeser_harmonie.name),
						      (name));
				/* Markierung setzen, fuer unmoeglichen Ausloeser */
				ausloeser->u.ausloeser_harmonie.vortaste = MUTABOR_INVALID_KEY;
			}

			if (enthalten_in_tastenliste
			    (ausloeser->u.ausloeser_harmonie.nachtaste,
			     help_harmonie->tastenliste) ||
			    ausloeser->u.ausloeser_harmonie.nachtaste
			    == MUTABOR_NO_KEY ) {
				/* OK */
			} else {
				mutabor_error_message(box,
						      compiler_warning,
						      _("Lowest chroma %d of harmony %s in logic %s is not a member of that harmony. This harmony trigger will be ignored."),
						      ausloeser->u.ausloeser_harmonie.nachtaste,
						      (ausloeser->u.ausloeser_harmonie.name),
						      (name));
				/* Markierung setzen, fuer unmoeglichen Ausloeser */
				ausloeser->u.ausloeser_harmonie.nachtaste = MUTABOR_INVALID_KEY;
			}
		}

	if (ausloeser->ausloeser_typ == ausloeser_midi_in)
		{

			struct midiliste * midi_lauf
				= ausloeser->u.ausloeser_midi_in.midi_code;

			if (midi_lauf -> midi_code < 0x80 ||
			    midi_lauf -> midi_code > 0xff ) {
				mutabor_error_message(box,
						      compiler_error,
						      _("Bad MIDI-Code %x in logic %s (expecting status byte %s )"),
						      midi_lauf->midi_code, 
						      (name), 
						      (_("status byte")));
			}

			if (midi_lauf -> midi_code & 0x000F ) {
				int oldmidicode = midi_lauf->midi_code;
				midi_lauf -> midi_code &= 0xFFF0;
				mutabor_error_message(box,
						      compiler_warning,
						      _("MIDI event in logic %s does not start with channel 0 status byte.\nGot byte #%x. Value corrected to #%x."),
						      (name),
						      oldmidicode,
						      midi_lauf -> midi_code);
			}

			midi_lauf = midi_lauf -> next;

			while (midi_lauf) {
				if (midi_lauf -> midi_code < 0 ||
				    midi_lauf -> midi_code > 0x7f ) {
					mutabor_error_message(box,
							      compiler_error,
							      _("Bad MIDI-Code #%x in logic %s (expecting a data byte in the range #00...#7f )"),
							      midi_lauf->midi_code,
							      (name));
				} else
					midi_lauf = midi_lauf -> next;
			}
		}

}



 static void check_aktionen (mutabor_box_type * box, struct aktions_liste * aktionen, const char * name)
{
	bool may_do_harmony_analysis;
	TRACE;

	for ( ; aktionen ; aktionen = aktionen -> next ) {
		switch (aktionen->aktions_typ) {
		case aktion_midi_out: {
			/** \todo split up midi messages and check each message separately */
			struct midiliste * midi_lauf
				= aktionen->u.aktion_midi_out.midi_code;

			while (midi_lauf) {
				if (midi_lauf -> midi_code < 0 ||
				    midi_lauf -> midi_code > 0xffffff) {
					mutabor_error_message(box,
							      compiler_error,
							      _("Bad MIDI-Code in logic %s, expecting a byte I got %d=#%x.\n\
Note: Each number can hold at maximum 3 bytes.\n\
Trying to recover..."),
							      (name), 
							      midi_lauf->midi_code,
							      midi_lauf->midi_code);
				}
				while (midi_lauf -> midi_code < 0 ||
				       midi_lauf -> midi_code > 0xff) {
					struct midiliste * tmp = (struct midiliste *)(xcalloc(box,
											      1,
											      sizeof(struct midiliste)));
					tmp -> midi_code = midi_lauf -> midi_code & 0xFF;
					midi_lauf -> midi_code >>= 8;
					tmp -> next = midi_lauf->next;
					midi_lauf->next = tmp;
				}


				midi_lauf = midi_lauf -> next;
			}

			midi_lauf
				= aktionen->u.aktion_midi_out.midi_code;

			if (midi_lauf -> midi_code < 0x80 ||
			    midi_lauf -> midi_code > 0xff ) {
				mutabor_error_message(box,
						      compiler_warning,
						      _("MIDI event in logic %s does not start with status byte.\n\
Got byte #%x. This will be probably ignored by your MIDI device."),
						      (name),
						      midi_lauf -> midi_code);
			}

			if (midi_lauf -> midi_code >= 0x80 &&
			    midi_lauf -> midi_code < 0xf0 && midi_lauf->midi_code & 0x0f ) {
				mutabor_error_message(box,
						      compiler_warning,
						      _("MIDI event in logic %s must be defined for channel 0, only.\n\
Got byte %x. Value corrected."),
						      (name),
						      midi_lauf -> midi_code & 0x0f);
				midi_lauf->midi_code &= 0x0f;
			}


			break;
		}
		case aktion_aufruf: {
			may_do_harmony_analysis = true;
			struct umstimmung * help_umstimmung =
				get_umstimmung (aktionen->u.aktion_aufruf.name,
						box->file->list_of_umstimmungen);

			struct tonsystem * help_tonsystem =
				parser_get_tonsystem (aktionen->u.aktion_aufruf.name,
						      box->file->list_of_tonsysteme);

			struct logik * help_logik =
				get_logik (aktionen->u.aktion_aufruf.name,
					   box->file->list_of_logiken);
			int i=0;

			if (help_umstimmung) i++;

			if (help_tonsystem)  i++;

			if (help_logik)      i++;

			if (i == 0) {
				mutabor_error_message(box,
						      compiler_error,
						      _("Undefined action: %s (in logic %s)"),
						      aktionen->u.aktion_aufruf.name,
						      name);
			}

			if (i > 1) {
				mutabor_error_message(box,
						      compiler_warning,
						      _("Non well defined event %s in logic %s"),
						      (aktionen->u.aktion_aufruf.name), 
						      (name));
			}

			if (help_umstimmung) {
				if (argument_list_laenge (aktionen->u.aktion_aufruf.argument_liste)
				    > parameter_list_laenge (help_umstimmung->parameter_liste)) {
					mutabor_error_message(box,
							      compiler_error,
							      _("In logic %s: Too many parameters while calling retuning %s."),
							      (name), 
							      (aktionen->u.aktion_aufruf.name));
				} else if (argument_list_laenge (aktionen->u.aktion_aufruf.argument_liste)
					   < parameter_list_laenge (help_umstimmung->parameter_liste)) {
					mutabor_error_message(box,
							      compiler_error,
							      _("In logic %s: Too few parameters while calling retuning %s."),
							      (name), 
							      (aktionen->u.aktion_aufruf.name));
				}

			} else if (help_tonsystem) {
				if (argument_list_laenge (aktionen->u.aktion_aufruf.argument_liste)
				    != 0 ) {

					mutabor_error_message(box,
							      compiler_error,
							      _("In logic %s: Tonesystem %s must be called without parameters."),
							      (name), 
							      (aktionen->u.aktion_aufruf.name));
				}
			} else if (help_logik) {
				if (argument_list_laenge (aktionen->u.aktion_aufruf.argument_liste)
				    != 0 ) {

					mutabor_error_message(box,
							      compiler_error,
							      _("In logic %s: Logic %s must be called without parameters."),
							      (name),
							      (aktionen->u.aktion_aufruf.name));
				}
			}
			break;

		}
		case aktion_harmony_analysis: {
			if (!may_do_harmony_analysis) {
				mutabor_error_message(box,
						      compiler_error,
						      _("In logic %s: Harmony analysis may be performed only after a logic or tonesystem change."),
						      (name));
			}
			break;
		}
		default:
			mutabor_error_message(box,
					      internal_error,
					      _("Internal error in check_aktionen() while processing logic %s.\n\
Unknown action type %d.\n\
Please, report this error to the Mutabor team."),
					      name,
					      aktionen->aktions_typ);


		}
	}
}


/**************************************************************

            Hier sind einige Hilfsfunktionen zum Testen,
            daû UmstimmungsbÅnde und die Einstimmungen der
            Logiken sich nicht rekursiv enthalten.

            Es wird ein azyklischer Graph der Umstimmungen
            gebildet, der dann nach den
            depth-first-search traversiert wird.
            Dabei wird ein beliebiger Zyklus festgestellt.

****************************************************************/

static void belege_zyklenfeld (struct umst_oder_logik *zyklen_feld,
                               struct umstimmung * liste1,
                               struct logik * liste2)
{
	int i = 0;
	TRACE;

	while (liste1)
		{
			zyklen_feld[i].umst_oder_logik_typ = typ_umstimmung;
			zyklen_feld[i].u.umstimmung = liste1;
			liste1 = liste1->next;
			i++;
		}

	while (liste2)
		{
			zyklen_feld[i].umst_oder_logik_typ = typ_logik;
			zyklen_feld[i].u.logik = liste2;
			liste2 = liste2->next;
			i++;
		}
}

 static int test_zyklen_nummer (mutabor_box_type * box, const char *name)
{
	int i;
	TRACE;

	for (i=0; i<box->file->anzahl_umstimmungen_und_logiken; i++)
		if ( ((box->file->zyklen_feld[i].umst_oder_logik_typ == typ_umstimmung) &&
                      (! strcasecmp (name, box->file->zyklen_feld[i].u.umstimmung->name)))
                     ||
                     ((box->file->zyklen_feld[i].umst_oder_logik_typ == typ_logik) &&
                      (! strcasecmp (name, box->file->zyklen_feld[i].u.logik->name)))
		     ) return i;

	mutabor_error_message(box,
			      compiler_error,
			      _("Undefined retuning: %s"),
			      (name)); /* Umst.n.dekl. */
	
	return 0; /* to prevent warnings */
}

 static void u_test_zyklen (mutabor_box_type * box, int startknoten)
{
	int i;
	TRACE;

	for (i=0; i<box->file->anzahl_umstimmungen_und_logiken; i++) {
		if (mutabor_u_adjacent (box->file->u_matrix, startknoten, i)) {
			if (box->file->u_visited [i]) {
				mutabor_error_message(box,
						      compiler_error,
						      _("Retunings/logics %s and %s depend on each other"),
						      box->file->zyklen_feld [startknoten].umst_oder_logik_typ == typ_umstimmung ?
						      (box->file->zyklen_feld [startknoten].u.umstimmung->name) :
						      (box->file->zyklen_feld [startknoten].u.logik->name),
						      box->file->zyklen_feld [i].umst_oder_logik_typ == typ_umstimmung ?
						      (box->file->zyklen_feld [i].u.umstimmung->name) :
						      (box->file->zyklen_feld [i].u.logik->name));
			}

			box->file->u_visited [i] = 1;

			u_test_zyklen (box,i);
			box->file->u_visited [i] = 0;
		}
	}
}





static void check_konsistenz (mutabor_box_type * box)
{
	TRACE;
	allgemeine_initialisierungen(box);

	/* Tonsysteme:
	   öberprÅfen, ob Periode und Tîne deklariert sind
	   und ob die Taste im Bereich 36 - 96 liegt.
	*/

	{ struct tonsystem * lauf;

		struct ton * ton_lauf;

		for (lauf = box->file->list_of_tonsysteme; lauf; lauf = lauf->next) {
			check_komplex_intervall (box,
						 lauf->periode, lauf->name);

			if (lauf->taste < MUTABOR_KEYRANGE_MIN_KEY  ||  lauf->taste > MUTABOR_KEYRANGE_MAX_KEY) {
				mutabor_error_message(box,
						      compiler_error,
						      _("Bad key %d (valid: %d...%d) in tonesystem %s"),
						      lauf->taste,
						      MUTABOR_KEYRANGE_MIN_KEY,
						      MUTABOR_KEYRANGE_MAX_KEY,
						      (lauf->name)); /* UngÅlt. Taste */
			}

			for (ton_lauf = lauf->toene;
			     ton_lauf;
			     ton_lauf = ton_lauf->next) {
				if ((ton_lauf->name != NULL) &&
				    (get_ton (box, ton_lauf->name, box->file->list_of_toene) == NULL)) {
					mutabor_error_message(box,
							      compiler_error,
							      _("Undefined tone: %s (in tone system %s)"),
							      (ton_lauf->name),
							      (lauf->name));
				}
			}
		}
	}


	/**** Umstimmungen prÅfen, ob alle Tîne und Intervalle
	      global deklariert sind, ob Umstimmungsbund und Umstimmungs_case
	      keine Rekursion enthÑlt, ob case_labels eindeutig sind,
	      und ob die benutzten Parameter
	      zu den deklarierten Parametern passen.
	****/

	{

		struct umstimmung * lauf;

		for (lauf = box->file->list_of_umstimmungen; lauf; lauf = lauf -> next) {
			switch (lauf -> umstimmung_typ) {
			case umstimmung_taste_abs :
			case umstimmung_taste_rel :
			case umstimmung_breite_abs :
			case umstimmung_breite_rel :
				TRACE;
				break;

			case umstimmung_wiederholung_rel :
				TRACE;
				check_komplex_intervall (box,
							 lauf->u.umstimmung_wiederholung_rel.komplex_liste,
				                         lauf->name);

				break;

			case umstimmung_wiederholung_abs :
				TRACE;
				check_komplex_intervall (box,
							 lauf->u.umstimmung_wiederholung_abs.komplex_liste,
				                         lauf->name);

				break;

			case umstimmung_toene_veraendert : {
				struct ton * lauf_ton;
				TRACE;

				for (lauf_ton = lauf->u.umstimmung_toene_veraendert.tonliste;
				     lauf_ton;
				     lauf_ton = lauf_ton -> next) {

					if (lauf_ton -> name != NULL) {
						/*  break geht hier wegen Bug in TURBO-C nicht! break for the next tone */

						if (lauf_ton -> ton_typ == ton_absolut) {
							mutabor_error_message(box,
									      internal_error,
									      _("Fixed tone %s in retuning %s"),
									      (lauf_ton->name),
									      (lauf->name));
							/* nicht komplexer Ton */
						}

						if (strcasecmp (lauf_ton->name,
							    lauf_ton->u.ton_komplex.bezugston)) {
							mutabor_error_message(box,
									      internal_error,
									      _("Tone does %s not match its reference tone %s. Dectected in retuning code at %s:%d"),
									      (lauf_ton->name),
									      (lauf_ton->u.ton_komplex.bezugston),
									      _T(__FILE__),
									      __LINE__);
						}

						if ((lauf_ton->name[0] != '@') &&
						    (get_ton (box, lauf_ton->name, box->file->list_of_toene) == NULL)) {
							mutabor_error_message(box,
									      compiler_error,
									      _("Undefined tone: %s (in retuning %s)"),
									      (lauf_ton->name),
									      (lauf->name));
							/* Undekl. Ton in Umst. */
						}

						check_komplex_intervall (box,
									 lauf_ton->u.ton_komplex.komplex_liste,
						                         lauf->name);

					}
				}
			}

				break;

			case umstimmung_umstimmungsbund : {

				/* Hier werden nur die LÑngen der Parameterlisten
				   verglichen. Die Zyklenfreiheit kommt spÑter
				*/

				struct aktions_liste * help_aktionen;
				TRACE;

				for (help_aktionen = lauf -> u.umstimmung_umstimmungsbund.aktions_liste;
				     help_aktionen;
				     help_aktionen = help_aktionen -> next) {
					if (help_aktionen -> aktions_typ == aktion_aufruf) {
						
						struct umstimmung * umst =
							get_umstimmung (help_aktionen -> u.aktion_aufruf.name,
									box->file->list_of_umstimmungen);

						if (umst == NULL) {
							
							struct tonsystem * tonsys =
								parser_get_tonsystem (help_aktionen -> u.aktion_aufruf.name,
										      box->file->list_of_tonsysteme);

							if (tonsys == NULL) {

								struct logik * help_logik;
								help_logik = get_logik (help_aktionen -> u.aktion_aufruf.name,
								                        box->file->list_of_logiken);

								if (help_logik == NULL) {
									mutabor_error_message(box,
											      compiler_error,
											      _("Undefined retuning: %s (in retuning %s)."),
											      (help_aktionen -> u.aktion_aufruf.name),
											      (lauf->name));
									/* Umst. in Bund */
								} else {
									if (help_aktionen -> u.aktion_aufruf.argument_liste != NULL) {
										mutabor_error_message(box,
												      compiler_error,
												      _("In collection %s : call to %s mustn't have parameters."),
												      (lauf -> name) ,
												      (help_aktionen -> u.aktion_aufruf.name));
									}
								}
							} else {
								if (help_aktionen -> u.aktion_aufruf.argument_liste != NULL) {
									mutabor_error_message(box,
											      compiler_error,
											      _("In collection %s : call to %s mustn't have parameters"),
											      (lauf -> name), 
											      (help_aktionen -> u.aktion_aufruf.name));
								}
							}
						} else {
							if (argument_list_laenge (help_aktionen -> u.aktion_aufruf.argument_liste)
							    != parameter_list_laenge (umst -> parameter_liste)) {
								mutabor_error_message(box,
										      compiler_error,
										      _("In retuning %s and %s : Bad parameters"),
										      (lauf->name),
										      (help_aktionen -> u.aktion_aufruf.name));
							}
						}
					}
				}
			}

				break;

			case umstimmung_umstimmungs_case : {
				TRACE;

				/* Hier werden nur Eindeutigkeit der case_label
				   und die LÑngen der Parameterlisten
				   verglichen. Die Zyklenfreiheit kommt spÑter
				*/

				struct case_liste * case_lauf;
				int anzahl_defaults;

				struct aktions_liste * help_aktionen;


				for (case_lauf = lauf->u.umstimmung_umstimmungs_case.umstimmungs_case_liste;
				     case_lauf;
				     case_lauf = case_lauf -> next ) {
					if (  !  case_lauf -> is_default  &&
					      case_label_enthalten_in_case_liste (case_lauf -> case_label,
										  case_lauf -> next ) ) {
						mutabor_error_message(box,
								      compiler_error,
								      _("The alternative %d is used twice in %s"),
								      (int)(case_lauf -> case_label),
								      (lauf -> name));
					}
				}


				for (anzahl_defaults = 0,
					     case_lauf = lauf->u.umstimmung_umstimmungs_case.umstimmungs_case_liste;
				     case_lauf;
				     case_lauf = case_lauf -> next ) {

					if (case_lauf -> is_default) {
						anzahl_defaults ++;

						if (anzahl_defaults > 1) {
							mutabor_error_message(box,
									      compiler_error,
									      _("Retuning %s contains more than one ELSE statement"),
									      (lauf -> name));
						}

						if (case_lauf -> next != NULL) {
							/* compiler_warning ( ?? ANSONSTEN ist nicht letztes
							   Element der case_liste  */
						}
					}

					for (help_aktionen = case_lauf -> case_aktion;
					     help_aktionen;
					     help_aktionen = help_aktionen -> next) {
						if (help_aktionen -> aktions_typ == aktion_aufruf) {

							struct umstimmung * umst =
								get_umstimmung (help_aktionen -> u.aktion_aufruf.name,
										box->file->list_of_umstimmungen);

							if (umst == NULL) {

								struct tonsystem * tonsys =
									parser_get_tonsystem (help_aktionen -> u.aktion_aufruf.name,
											      box->file->list_of_tonsysteme);

								if (tonsys == NULL) {

									struct logik * help_logik;
									help_logik = get_logik (help_aktionen -> u.aktion_aufruf.name,
									                        box->file->list_of_logiken);

									if (help_logik == NULL) {
										mutabor_error_message(box,
												      compiler_error,
												      _("Undefined retuning: %s (in retuning %s)"),
												      (help_aktionen -> u.aktion_aufruf.name),
												      lauf->name);
										/* Umst. in Bund */
									} else {
										if (help_aktionen -> u.aktion_aufruf.argument_liste != NULL) {
											mutabor_error_message(box,
													      compiler_error,
													      _("In case %s : call to %s mustn't have parameters"),
													      (lauf -> name) ,
													      (help_aktionen -> u.aktion_aufruf.name));
										}
									}
								} else {
									if (help_aktionen -> u.aktion_aufruf.argument_liste != NULL) {
										mutabor_error_message(box,
												      compiler_error,
												      _("In case %s : call to %s mustn't have parameters"),
												      (lauf -> name) ,
												      (help_aktionen -> u.aktion_aufruf.name));
									}
								}
							} else {
								if (argument_list_laenge (help_aktionen -> u.aktion_aufruf.argument_liste)
								    != parameter_list_laenge (umst -> parameter_liste)) {
									mutabor_error_message(box,
											      compiler_error,
											      _("In retuning %s and %s : Bad parameters"),
											      (lauf->name),
											      (help_aktionen -> u.aktion_aufruf.name));
								}
							}
						}
					}
				}
			}

				break;
			default :
				TRACE;
				mutabor_error_message(box,
						      internal_error,
						      _("Undefined returning type %d detected in\n%s:%d"),
						      _T(__FILE__),
						      __LINE__);
				
				break;
			}  /* of switch */
		}  /* of for */

		/**** testzyklen ****/

		{
			int i,j,k;

			box->file->anzahl_umstimmungen_und_logiken =
			        umstimmungs_list_laenge (box->file->list_of_umstimmungen)
			        + logik_list_laenge (box->file->list_of_logiken) ;

			box->file->zyklen_feld = 
				(umst_oder_logik*) xalloca (box, sizeof(struct umst_oder_logik) 
							    * box->file->anzahl_umstimmungen_und_logiken);
			box->file->u_visited = (char*) xalloca (box, sizeof(char) * box->file->anzahl_umstimmungen_und_logiken);
			box->file->u_matrix = (char*) xalloca (box, sizeof(char) * box->file->anzahl_umstimmungen_und_logiken
			                            * box->file->anzahl_umstimmungen_und_logiken);


			/* Feld mit Umstimmungen initialisieren (zum schnelleren Zugriff) */

			belege_zyklenfeld (box->file->zyklen_feld, box->file->list_of_umstimmungen, box->file->list_of_logiken);

			/* Adjazenzmatrix initialisieren (Keine Umstimmung
			   hÑngt von einer anderen ab) */

			for (i=0; i<box->file->anzahl_umstimmungen_und_logiken; i++) {
				for (j=0; j<box->file->anzahl_umstimmungen_und_logiken; j++) {
					mutabor_u_adjacent (box->file->u_matrix, i,j) = 0;
				}
			}

			/* Adjazenzmatrix initialisieren (AbhÑngigkeiten eintragen) */

			for (i=0; i<box->file->anzahl_umstimmungen_und_logiken; i++) {
				if (box->file->zyklen_feld[i].umst_oder_logik_typ == typ_umstimmung &&
				    box->file->zyklen_feld[i].u.umstimmung->umstimmung_typ == umstimmung_umstimmungsbund) {

					struct aktions_liste *lauf = box->file->zyklen_feld[i].u.umstimmung->u.umstimmung_umstimmungsbund.aktions_liste;

					for ( ; lauf ; lauf = lauf -> next ) {
						if (lauf -> aktions_typ == aktion_aufruf) {
							if (get_umstimmung (lauf -> u.aktion_aufruf.name,
							                    box->file->list_of_umstimmungen) != NULL
							    ||
							    get_logik (lauf -> u.aktion_aufruf.name,
								       box->file->list_of_logiken) != NULL
							    ) {
								/* Keine Tonsysteme adjazent eintragen */

								mutabor_u_adjacent (box->file->u_matrix, 
										    i, 
										    test_zyklen_nummer (box,
													lauf->u.aktion_aufruf.name)) = 1;
							}
						}
					}
				} else if (box->file->zyklen_feld[i].umst_oder_logik_typ == typ_umstimmung &&
					   box->file->zyklen_feld[i].u.umstimmung->umstimmung_typ ==
					   umstimmung_umstimmungs_case) {

					struct case_liste * case_lauf;

					for (case_lauf = box->file->zyklen_feld[i].u.umstimmung->u.umstimmung_umstimmungs_case.umstimmungs_case_liste;
					     case_lauf;
					     case_lauf = case_lauf -> next) {

						struct aktions_liste *lauf = case_lauf -> case_aktion;

						for ( ; lauf ; lauf = lauf -> next ) {
							if (lauf -> aktions_typ == aktion_aufruf) {
								if (get_umstimmung (lauf -> u.aktion_aufruf.name,
								                    box->file->list_of_umstimmungen) != NULL
								    ||
								    get_logik (lauf -> u.aktion_aufruf.name,
									       box->file->list_of_logiken) != NULL
								    ) {
									/* Keine Tonsysteme adjazent eintragen */

									mutabor_u_adjacent (box->file->u_matrix, 
											    i, 
											    test_zyklen_nummer (box,
														lauf->u.aktion_aufruf.name)) = 1;
								}
							}
						}
					}
				} else if (box->file->zyklen_feld[i].umst_oder_logik_typ == typ_logik &&
					   box->file->zyklen_feld[i].u.logik->einstimmungs_name) {

					if (get_umstimmung (box->file->zyklen_feld[i].u.logik->einstimmungs_name,
					                    box->file->list_of_umstimmungen) != NULL) {
						/* Keine Tonsysteme adjazent eintragen */

						mutabor_u_adjacent (box->file->u_matrix, 
								    i, 
								    test_zyklen_nummer (box,
											box->file->zyklen_feld[i].u.logik->einstimmungs_name)) = 1;
					}
				}
			}

#ifdef DEBUG_ANZEIGE_2
			/* Adjazenzmatrix anzeigen */

			printf ("U_Matrix:\n");

			for (i=0; i<box->file->anzahl_umstimmungen_und_logiken; i++) {
				if (box->file->zyklen_feld[i].umst_oder_logik_typ == typ_umstimmung)
					printf ("Umstimmung %s -> ", box->file->zyklen_feld[i].u.umstimmung->name);
				else
					printf ("Logik %s -> ", box->file->zyklen_feld[i].u.logik->name);

				for (j=0; j<box->file->anzahl_umstimmungen_und_logiken; j++) {
					if (mutabor_u_adjacent (box->file->u_matrix, i,j))
						if (box->file->zyklen_feld[j].umst_oder_logik_typ == typ_umstimmung)
							printf ("Umstimmung %s ", box->file->zyklen_feld[j].u.umstimmung->name);
						else
							printf ("Logik %s -> ", box->file->zyklen_feld[j].u.logik->name);
				}

				printf ("\n");
			}

			printf ("\n");

#endif

			/* auf Zyklenfreiheit Pruefen */

			for (k=0; k<box->file->anzahl_umstimmungen_und_logiken; k++)
				box->file->u_visited [k] = 0;

			for (k=0; k<box->file->anzahl_umstimmungen_und_logiken; k++) {
				box->file->u_visited [k] = 1;
				u_test_zyklen (box,k);
				box->file->u_visited [k] = 0;
			}


#ifdef DEBUG_ANZEIGE_2
			/* Adjazenzmatrix anzeigen */

			printf ("U_Matrix:\n");

			for (i=0; i<box->file->anzahl_umstimmungen_und_logiken; i++) {
				if (box->file->zyklen_feld[i].umst_oder_logik_typ == typ_umstimmung)
					printf ("Umstimmung %s -> ", box->file->zyklen_feld[i].u.umstimmung->name);
				else
					printf ("Logik %s -> ", box->file->zyklen_feld[i].u.logik->name);

				for (j=0; j<box->file->anzahl_umstimmungen_und_logiken; j++) {
					if (mutabor_u_adjacent (box->file->u_matrix, i,j))
						if (box->file->zyklen_feld[j].umst_oder_logik_typ == typ_umstimmung)
							printf ("Umstimmung %s ", box->file->zyklen_feld[j].u.umstimmung->name);
						else
							printf ("Logik %s -> ", box->file->zyklen_feld[j].u.logik->name);
				}

				printf ("\n");
			}

			printf ("\n");

#endif

			xde_alloca (box->file->zyklen_feld);
			xde_alloca (box->file->u_visited);
			xde_alloca (box->file->u_matrix);

		}


		/******* ende testzyklen **/

	}


	/* Logiken:
	   öberprÅfen, ob Einstimmung deklariert ist
	   und ob die Anweisungen korrekt deklariert sind.
	*/


#if 1

	{ struct logik * lauf;

		struct anweisung * anweisungs_lauf;
		int anzahl_default_ausloeser;

		for (lauf = box->file->list_of_logiken; lauf; lauf = lauf->next) {

			check_ausloeser (box,lauf->ausloeser, lauf->name);

			/* Eine Logik darf nicht mit dem DEFAULT-Auslîser aufgerufen werden */

			if (lauf->ausloeser) {
				if (lauf->ausloeser->ausloeser_typ == ausloeser_default) {
					mutabor_error_message(box,
							      compiler_error,
							      _("Logic %s must not be called by ELSE"),
							      (lauf->name));
				}
			}

			if (lauf->einstimmungs_name!=NULL) {
				if (parser_get_tonsystem (lauf->einstimmungs_name, box->file->list_of_tonsysteme) == NULL) {
					struct umstimmung * help_umstimmung
						= get_umstimmung (lauf->einstimmungs_name, box->file->list_of_umstimmungen);
					if (help_umstimmung == NULL) {
						mutabor_error_message(box,
								      compiler_error,
								      _("Undefined initial tuning: %s (in logic %s)"),
								      (lauf->einstimmungs_name),
								      (lauf->name));
						/* Einst. in Logik */
					} else {
						if (parameter_list_laenge (help_umstimmung -> parameter_liste) != 0) {
							mutabor_error_message(box,
									      compiler_error,
									      _("In logik %s : initial tuning %s mustn't have parameters"),
									      (lauf->name),
									      (lauf->einstimmungs_name));
						}
					}
				}
			}

			for (anweisungs_lauf = lauf->anweisungsliste,
				     anzahl_default_ausloeser = 0;
			     anweisungs_lauf;
			     anweisungs_lauf = anweisungs_lauf->next) {

				check_ausloeser (box,anweisungs_lauf->ausloeser, lauf->name);

				if (anweisungs_lauf->ausloeser == NULL)
					mutabor_error_message(box,
							      compiler_error,
							      _("No event defined for action %s. Detected at\n%s:%d"),
							      (lauf->name),
							      _T(__FILE__),
							      __LINE__);
				else {
					if (anweisungs_lauf->ausloeser->ausloeser_typ
					    == ausloeser_default) {
						anzahl_default_ausloeser ++;

						if (anzahl_default_ausloeser > 1) {
							mutabor_error_message(box,
									      compiler_error,
									      _("Logik %s contains more than one ELSE statement"),
									      (lauf -> name));
						} else {
							if (anweisungs_lauf -> next != NULL)
								mutabor_error_message(box,
										      compiler_warning,
										      _("Event ELSE is last in %s"), 
										      (lauf -> name));
						}
					}
				}

				check_aktionen (box,anweisungs_lauf -> aktion, lauf->name);

			}
		}
	}
#endif
}

#if defined(DEBUG_ANZEIGE) || defined(DEBUG) 

static void print_action (struct aktions_liste * action) 
{

	switch (action -> aktions_typ) {
	case aktion_midi_out:
		STUB;
		break;
	case aktion_aufruf: {
		struct argument_list * help;
		printf ("                Umstimmungs-name: %s, Parameter: ",
			action->u.aktion_aufruf.name ? 
			action->u.aktion_aufruf.name : "(NULL)");
		
		for (help = action->u.aktion_aufruf.argument_liste; 
		     help; help = help->next ) {
			drucke_argument ( & help -> argument );
		}
		break;
	}
	case aktion_harmony_analysis: {
		printf("                Harmony analysis");
	}
	default:
		UNREACHABLE;
	}

	printf ("\n");

}


static void print_action_list(struct aktions_liste * actionlist)
{ 
 	TRACE;
	printf("{\n");
	struct aktions_liste * help_umst;
	for (help_umst = actionlist;
	     help_umst;
	     help_umst = help_umst -> next ) {
		print_action(help_umst);
	}
	
	printf("}\n");
}



#endif

#ifdef __cplusplus
		}
	}
}
#endif
///\}
