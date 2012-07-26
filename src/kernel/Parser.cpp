/** \file 
 ********************************************************************
 * Description
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/src/kernel/Parser.cpp,v 1.11 2011/10/13 18:26:13 keinstein Exp $
 * Copyright:   (c) 2008 TU Dresden
 * \author  Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 
 * $Date: 2011/10/13 18:26:13 $
 * \version $Revision: 1.11 $
 * \license GPL
 *
 * $Log: Parser.cpp,v $
 * Revision 1.11  2011/10/13 18:26:13  keinstein
 * Fix a Bug in the kernel:
 * retuning case did not execute the following statements,
 * which lead to unexpected results
 *
 * Revision 1.10  2011-02-20 22:35:55  keinstein
 * updated license information; some file headers have to be revised, though
 *
 *
 *
 ********************************************************************
 * \addtogroup kernel
 * \{
 ********************************************************************/
// ------------------------------------------------------------------
// Mutabor 2.win, 1997, R.Krauﬂe
// Fileparser
// ------------------------------------------------------------------

#include "Global.h"
#include "GrafKern.h"
#include "Interval.h"
#include "Hilfs.h"

/* Globale Variablen des Compilers mit dem Codegenerator und
                                       dem Tabellengenerator  */

/*********** Es folgen die Wurzeln der Listen.
             Jede Liste ist nur einmal und global vorhanden,
             da die Sprache NICHT rekursiv ist.
***********/


struct intervall      *  list_of_intervalle;

struct ton            *  list_of_toene;

struct tonsystem      *  list_of_tonsysteme;

struct umstimmung     *  list_of_umstimmungen;

struct harmonie       *  list_of_harmonien;

struct logik          *  list_of_logiken;

struct instrument     *  list_of_instrumente;

struct instrument     *  list_of_config_instrumente;

struct ton            *  ton_ohne_namen; /* Frequenz=0 */

static void berechne_toene_absolut (struct ton *ton_liste);

static void check_konsistenz (void);

#ifdef DEBUG
static void drucke_ton (struct ton * lauf);
static void drucke_harmonie (struct harmonie * this_);
static void drucke_argument (struct argument * z_or_p);

static void print_ausloeser (struct ausloeser * this_);
//static void print_aktion (struct aktion * that);
static void print_action (struct aktions_liste * action);
static void print_action_list(struct aktions_liste * actionlist);
#endif


/*********  Allgemeine Hilfsfunktionen ********/

void allgemeine_initialisierungen( void )
{
	TRACE;
	ton_ohne_namen=(ton*) xmalloc((size_t) sizeof(struct ton));
	ton_ohne_namen->name=NULL;
	ton_ohne_namen->ton_typ=ton_absolut;
	ton_ohne_namen->u.ton_absolut.ton_wert=0.0;
	ton_ohne_namen->next=NULL;
}

int ton_list_laenge (struct ton *list)

{
	TRACE;
	if (list) return 1 + ton_list_laenge (list -> next);

	return 0;
}

int tonsystem_list_laenge (struct tonsystem *list)
{
	TRACE;
	if (list) return 1 + tonsystem_list_laenge (list -> next);

	return 0;
}

int umstimmungs_list_laenge (struct umstimmung *list)
{
	TRACE;
	if (list) return 1 + umstimmungs_list_laenge (list -> next);

	return 0;
}

int logik_list_laenge (struct logik *list)
{
	TRACE;
	if (list) return 1 + logik_list_laenge (list -> next);

	return 0;
}

int midi_list_laenge (struct midiliste *list)
{
	TRACE;
	if (list) return 1 + midi_list_laenge (list -> next);

	return 0;
}

int get_logik_nummer (const char * name, struct logik * liste)
{
	TRACE;
	if (liste == NULL)
	{
		fatal_error (0, _T(__FILE__), __LINE__);
		return 0;
	} else if ( ! strcmp (name, liste->name))
		return 0;
	else
		return 1 + get_logik_nummer (name, liste->next);
}

int parameter_list_laenge (struct parameter_liste *list)

{
	TRACE;
	if (list) return 1 + parameter_list_laenge (list -> next);

	return 0;
}

int argument_list_laenge (struct argument_liste *list)
{
	TRACE;
	if (list) return 1 + argument_list_laenge (list -> next);

	return 0;
}


struct ton * get_ton (const char * name, struct ton * liste)
{
	TRACE;
	if (name==NULL) return(ton_ohne_namen);

	if (liste == NULL) return NULL;

	if ( ! strcmp (name, liste->name)) return liste;

	return get_ton (name, liste->next);
}


struct intervall * get_intervall (const char * name,
				  struct intervall * liste)
{
	TRACE;
	if (liste == NULL) return NULL;
	if ( ! strcmp (name, liste->name)) return liste;
	return get_intervall (name, liste->next);
}

struct tonsystem * parser_get_tonsystem (const char * name,
			                struct tonsystem * liste)
{
	TRACE;
	if (liste == NULL) return NULL;
	if ( ! strcmp (name, liste->name)) return liste;
	return parser_get_tonsystem (name, liste->next);
}

struct umstimmung * get_umstimmung (const char * name,
				    struct umstimmung * liste)
{
	TRACE;
	if (liste == NULL) return NULL;
	if ( ! strcmp (name, liste->name)) return liste;
	return get_umstimmung (name, liste->next);
}

struct harmonie * get_harmonie (const char * name, struct harmonie * liste)
{
	TRACE;
	if (liste == NULL) return NULL;
	if ( ! strcmp (name, liste->name)) return liste;
	return get_harmonie (name, liste->next);
}


struct logik * get_logik (const char * name, struct logik * liste)
{
	TRACE;
	if (liste == NULL) return NULL;
	if ( ! strcmp (name, liste->name)) return liste;
	return get_logik (name, liste->next);
}


/********* Einleseroutine fuer Integerliste          *********/
/*         Es wird einfach eine Liste of Integer aufgebaut       **/
/*         die allgemein verwendbar ist.                       **/

static struct midiliste * list_of_integers;

void init_integersequenz (void)
{
	TRACE;
	list_of_integers = NULL;
}


void get_new_integer_in_integersequenz (int wert)

{
	struct midiliste * * lauf;
	TRACE;

	for (lauf= & list_of_integers; * lauf; lauf= & (*lauf)->next) {}

	(* lauf) = (midiliste*) xmalloc ((size_t) sizeof (struct midiliste));
	(* lauf) -> midi_code     = wert;
	(* lauf) -> next          = NULL;
}

static struct midiliste * get_last_integersequenz (void)
{
	TRACE;
	return list_of_integers;
}



/********* Einleseroutinen fuer Parameterliste          *********/
/*         Es wird einfach eine Liste of Namen aufgebaut       **/
/*         die allgemein verwendbar ist.                       **/

static struct parameter_liste * list_of_names;

void init_parameter_liste (void)
{
	TRACE;
	list_of_names = NULL;
}


void get_new_name_in_parameterlist (const char * name)

{

	struct parameter_liste * * lauf;
	TRACE;

	for (lauf= & list_of_names; * lauf; lauf= & (*lauf)->next) {
		if ( ! strcmp (name, (*lauf)->name)) {
			fatal_error(17,mutC_STR(name)); /* Parametername doppelt: name */
		}
	}

	(* lauf) = (parameter_liste*) xmalloc ((size_t) sizeof (struct parameter_liste));
	(* lauf) -> name          = name;
	(* lauf) -> next          = NULL;
}

static struct parameter_liste * get_last_parameter_liste (void)
{
	return list_of_names;
}


static int parameter_nummer (int aktueller_index, const char * such_name,

                             struct parameter_liste * knoten)
{
	TRACE;
	if (knoten == NULL) return EOF;

	if ( ! strcmp (such_name, knoten -> name))
		return aktueller_index;

	return parameter_nummer (aktueller_index + 1, such_name,
	                         knoten -> next);
}

void print_argumentliste (struct argument_liste * this_)

{
	TRACE;
	if (this_)
	{
		if (this_ -> argument.argument_typ == zahl)
			printf (" %d ", this_ -> argument.u.zahl.zahl);
		else
			printf (" %s ", this_ -> argument.u.parameter.parameter_name);

		print_argumentliste (this_ -> next);
	}
}


/********* Einleseroutinen fuer Argumentliste          *********/

static struct argument_liste * list_of_argumente;

void init_argument_liste (void)
{
	TRACE;
	list_of_argumente = NULL;
}


void get_new_number_in_argument_list (double parameter_zahl)

{

	struct argument_liste * * lauf;
	TRACE;

	for (lauf= & list_of_argumente; * lauf; lauf= & (*lauf)->next) {}

	(* lauf) = (argument_liste*) xmalloc ((size_t) sizeof (struct argument_liste));
	(* lauf) -> argument.argument_typ = zahl;
	(* lauf) -> argument.u.zahl.zahl  = (int) parameter_zahl;
	(* lauf) -> next                  = NULL;
}


void get_new_name_in_argument_list (const char * parameter_name)
{

	struct argument_liste * * lauf;
	TRACE;

	for (lauf= & list_of_argumente; * lauf; lauf= & (*lauf)->next) {
#if 0

		if ( ! strcmp (name, (*lauf)->name)) {
			fatal_error(17,mutC_STR(name)); /* Parametername doppelt: name */
		}

#endif
	}

	(* lauf) = (argument_liste*) xmalloc ((size_t) sizeof (struct argument_liste));
	(* lauf) -> argument.argument_typ = parameter;
	(* lauf) -> argument.u.parameter.parameter_nummer = 0;
	(* lauf) -> argument.u.parameter.parameter_name = parameter_name;
	(* lauf) -> next          = NULL;
}

static struct argument_liste * get_last_argument_liste (void)
{
	TRACE;
	return list_of_argumente;
}


/********* Einleseroutinen fuer Aktions-liste          *********/

static struct aktions_liste * list_of_aktionen;

void init_aktions_liste (void)
{
	TRACE;
	list_of_aktionen = NULL;
}


void get_new_aktion_aufruf_element (const char * name)

{

	struct aktions_liste * * lauf;
	TRACE;

	for (lauf= & list_of_aktionen; * lauf; lauf= & (*lauf)->next) {}

	(* lauf) = (aktions_liste*) xmalloc ((size_t) sizeof (struct aktions_liste));
	(* lauf) -> aktions_typ           = aktion_aufruf;
	(* lauf) -> u.aktion_aufruf.name  = name;
	(* lauf) -> u.aktion_aufruf.argument_liste = get_last_argument_liste ();
	(* lauf) -> next                  = NULL;
}

void get_new_aktion_midi_out_element (void)

{

	struct aktions_liste * * lauf;
	TRACE;

	for (lauf= & list_of_aktionen; * lauf; lauf= & (*lauf)->next) {}

	(* lauf) = (aktions_liste*) xmalloc ((size_t) sizeof (struct aktions_liste));
	(* lauf) -> aktions_typ           = aktion_midi_out;
	(* lauf) -> u.aktion_midi_out.midi_code = get_last_integersequenz ();
	(* lauf) -> next                  = NULL;
}

static struct aktions_liste * get_last_aktions_liste (void)
{
	TRACE;
	return list_of_aktionen;
}

/* Einleseroutinen fÅr komplex_intervalle  ****/

static struct komplex_intervall * the_komplex_liste;

void init_komplex_ton_list (void)
{
	TRACE;
	the_komplex_liste = NULL;
}

void get_new_faktor_anteil (double f, const char *name)

{

	struct komplex_intervall * * lauf;
	TRACE;

	for (lauf= & the_komplex_liste; * lauf; lauf= & (*lauf)->next)
		/* nur ende der Liste finden */ ;

	(* lauf) = (komplex_intervall*) xmalloc ((size_t) sizeof (struct komplex_intervall));

	(* lauf) -> faktor = f;

	(* lauf) -> name   = name;

	(* lauf) -> next   = NULL;

}

struct komplex_intervall * get_last_komplex_intervall (void)
{
	TRACE;
	return the_komplex_liste;
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



void setze_nummer_von_abstand_und_zentrum (void)
{

	struct logik * lauf;
	TRACE;

	for (lauf=list_of_logiken; lauf; lauf=lauf->next) {

		struct anweisung * lauf_anw;

		for (lauf_anw=lauf->anweisungsliste; 
		     lauf_anw; lauf_anw=lauf_anw->next) {
			if (lauf_anw->aktion->aktions_typ == aktion_aufruf) {

				struct argument_liste * lauf_arg;

				for (lauf_arg=lauf_anw->aktion->u.aktion_aufruf.argument_liste;
				                lauf_arg;
				                lauf_arg=lauf_arg->next) {
					switch (lauf_arg->argument.argument_typ) {

					case zahl:
						TRACE;
						/* OK */
						break;

					case parameter:
						TRACE;
						if ( ! strcmp (lauf_arg->argument.u.parameter.parameter_name,
						                "ABSTAND")) {
							lauf_arg->argument.u.parameter.parameter_nummer
							= 0;
						} else
							if ( ! strcmp (lauf_arg->argument.u.parameter.parameter_name,
							                "DISTANCE")) {
								lauf_arg->argument.u.parameter.parameter_nummer
								= 0;
							} else
								if ( ! strcmp (lauf_arg->argument.u.parameter.parameter_name,
								                "ZENTRUM")) {
									lauf_arg->argument.u.parameter.parameter_nummer
									= 1;
								} else
									if ( ! strcmp (lauf_arg->argument.u.parameter.parameter_name,
									                "CENTER")) {
										lauf_arg->argument.u.parameter.parameter_nummer
										= 1;
									} else
										fatal_error (39,
										             mutC_STR(lauf_arg->argument.u.parameter.parameter_name),
										             mutC_STR(lauf_anw->aktion->u.aktion_aufruf.name),
										             mutC_STR(lauf->name));

						break;

					default:
						TRACE;
						fatal_error (0, _T(__FILE__), __LINE__);

						break;
					}
				}
			}
		}
	}
}


/********* Eintrittspunkt in das File ist hier !! *******/

FILE * quelldatei;

void mutabor_programm_einlesen (const mutChar * filename )
{
	TRACE;

	if ((quelldatei = wxFopen (filename, _T("r"))) == NULL) {
		fatal_error(3,filename);
	}

	list_of_intervalle            = NULL;

	list_of_toene                 = NULL;
	list_of_tonsysteme            = NULL;
	list_of_umstimmungen          = NULL;
	list_of_harmonien             = NULL;
	list_of_logiken               = NULL;
	list_of_instrumente           = NULL;
	list_of_config_instrumente    = NULL;


	DEBUGLOG2(kernel_parser,_T("Start parsing"));

	if (yyparse()) {
		fatal_error(1,-999); /* Wird sowieso nie aufgerufen ... */
	}

	fclose (quelldatei);

	// NEU: wenn kein Intervall oder Ton da, dann Speichermangel
	// also evtl. Dummy
	// (das Problem l‰ﬂt sich sicher auch direkt lˆsen ...)

	if ( !list_of_intervalle )
		get_new_intervall("__TopSecret__RK__Intervall__", 1.0);

	berechne_intervalle_absolut (list_of_intervalle);

	if ( !list_of_toene )
		get_new_ton_absolut("__TopSecret__RK__Ton__", 440.0);

	berechne_toene_absolut (list_of_toene);


	/* Falls kein Instrument angegeben ist: Dann 1 -> 1-16 */

	if (list_of_instrumente == NULL &&
	                list_of_config_instrumente == NULL) {
		get_instrument_dekl (1, 1, 16, 0, & list_of_instrumente);
	} else if (list_of_instrumente == NULL) {
		list_of_instrumente = list_of_config_instrumente;
	}


	setze_nummer_von_abstand_und_zentrum ();

	check_konsistenz ();

#ifdef DEBUG
	

	if (isDebugFlag(kernel_parser)) {
		{ struct intervall * lauf;
			printf ("\n");
			
			for (lauf=list_of_intervalle; lauf; lauf=lauf->next) {
				if (lauf->intervall_typ == intervall_absolut) {
					printf ("Name: %s, Wert: %lf:\n", 
						lauf->name,
						lauf->u.intervall_absolut.intervall_wert );
				} else {
					STUB;
				}
			}
		}

		{ struct ton * lauf;
			printf ("\n");

			for (lauf=list_of_toene; lauf; lauf=lauf->next) {
				drucke_ton (lauf);

			}
		}

		{ struct tonsystem * lauf;
			printf ("\n");

			for (lauf=list_of_tonsysteme; lauf; lauf=lauf->next) {

				struct ton * help;
				printf ("Name: %s, Taste: %d, Periode: %p, "
					"Tonleiter_breite: %d\n",
					lauf->name,
					lauf->taste,
					lauf->periode,
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

			for (lauf=list_of_umstimmungen; lauf; lauf=lauf->next) {

				struct parameter_liste * help;
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

					drucke_argument (
						& lauf -> u.umstimmung_taste_abs.argument);

					printf ("\n");

					break;

				case umstimmung_taste_rel :
					printf ("        umstimmung_taste_rel : ");

					drucke_argument (
						& lauf -> u.umstimmung_taste_rel.argument);

					printf (" Rechenzeichen: \"%c\"\n",
						lauf -> u.umstimmung_taste_rel.rechenzeichen);

					break;

				case umstimmung_breite_abs :
					printf ("        umstimmung_breite_abs : ");

					drucke_argument (
						& lauf -> u.umstimmung_breite_abs.argument);

					printf ("\n");

					break;

				case umstimmung_breite_rel :
					printf ("        umstimmung_breite_rel : ");

					drucke_argument (
						& lauf -> u.umstimmung_breite_rel.argument);

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
					drucke_argument (
						& lauf -> u.umstimmung_umstimmungs_case.argument);

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

			for (lauf=list_of_harmonien; lauf; lauf=lauf->next) {
				printf ("\n");
				drucke_harmonie (lauf);
				printf ("\n");
			}
		}

		printf ("\nLogiken:\n");

		{

			struct logik * lauf;

			for (lauf=list_of_logiken; lauf; lauf=lauf->next) {

				struct anweisung * anw_lauf;
				print_ausloeser (lauf->ausloeser);
				printf ("\nName: %s Einstimmung : %s\n",
					lauf->name,
					lauf->einstimmungs_name ?
					lauf->einstimmungs_name :
					"(NULL)");

				for (anw_lauf = lauf->anweisungsliste;
				     anw_lauf;
				     anw_lauf = anw_lauf -> next) {
					print_ausloeser (anw_lauf->ausloeser);
					print_action (anw_lauf->aktion);
				}
			}
		}

		printf ("\nInstrumente:\n");

		{

			struct instrument * lauf;

			for (lauf=list_of_instrumente; lauf; lauf=lauf->next) {
				printf ("Instrument %d -> %d - %d\n", lauf->midi_in,
					lauf->midi_von, lauf->midi_bis);
			}
		}

	}
#endif

}

#ifdef DEBUG

static void drucke_argument (struct argument * z_or_p)
{
    if (z_or_p -> argument_typ == zahl) {
      printf (" Number: %d ", z_or_p->u.zahl.zahl);
    }
    else {
      printf (" Parameter: %s, Nr: %d ",
                 z_or_p->u.parameter.parameter_name,
                 z_or_p->u.parameter.parameter_nummer);
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
                printf ("%lf\n", lauf->u.ton_absolut.ton_wert);
                break;
            case ton_komplex : {
                 struct komplex_intervall * help = lauf->u.ton_komplex.komplex_liste;
                 printf ("%s ", lauf->u.ton_komplex.bezugston);
                 while (help) {
                     printf ("Faktor: %lf %s ",
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
static void print_ausloeser (struct ausloeser * this_)
{
  if (this_) {
    switch (this_->ausloeser_typ)
    {
    default: fatal_error (0, "print_ausloeser");
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

void get_new_intervall (const char *name, double wert)
{

	struct intervall * * lauf;
	TRACE;

	for (lauf= & list_of_intervalle; * lauf; lauf= &(*lauf)->next) {
		if ( ! strcmp (name, (*lauf)->name)) {
			fatal_error(10,mutC_STR(name)); /* Intervallname doppelt */
		}
	}

	if (fabs (wert) < 0.001)
		fatal_error (46, mutC_STR(name));

	(* lauf) = (intervall*) xmalloc ((size_t) sizeof (struct intervall));

	(* lauf) -> name = name;

	(* lauf) -> intervall_typ = intervall_absolut;

	(* lauf) -> u.intervall_absolut.intervall_wert = wert;

	(* lauf) -> next = NULL;

}

void get_new_intervall_komplex (const char *name)

{

	struct intervall * * lauf;
	TRACE;

	for (lauf= & list_of_intervalle; * lauf; lauf= &(*lauf)->next) {
		if ( ! strcmp (name, (*lauf)->name)) {
			fatal_error(10,mutC_STR(name)); /* Intervallname doppelt */
		}
	}

	(* lauf) = (intervall*) xmalloc ((size_t) sizeof (struct intervall));
	(* lauf) -> name = name;
	(* lauf) -> intervall_typ = intervall_komplex;
	(* lauf) -> u.intervall_komplex.komplex_liste =
	        get_last_komplex_intervall ();
	(* lauf) -> next = NULL;

}

/********* Einleseroutinen fuer die Toene           *********/
/*         Es wird einfach eine Liste of Toenen aufgebaut  **/
/*         Je nach erkanntem Ton_Typ                       **/

void get_new_ton_absolut (const char *name, double wert)
{

	struct ton * * lauf;
	TRACE;

	for (lauf= & list_of_toene; * lauf; lauf= & (*lauf)->next) {
		if ( ! strcmp (name, (* lauf)->name)) {
			fatal_error(11,mutC_STR(name)); /* Tonname doppelt */
		}
	}

	(* lauf) = (ton*) xmalloc ((size_t) sizeof (struct ton));
	(* lauf) -> name                   = name;
	(* lauf) -> ton_typ                = ton_absolut;
	(* lauf) -> u.ton_absolut.ton_wert = wert;
	(* lauf) -> next                   = NULL;

}


void get_new_ton_komplex_positive (const char *name, const char *bezugston)

{

	struct ton * * lauf;
	TRACE;

	for (lauf= & list_of_toene; * lauf; lauf= & (*lauf)->next) {
		if ( ! strcmp (name, (*lauf)->name)) {
			fatal_error(11,mutC_STR(name)); /* Tonname doppelt */
		}
	}

	(* lauf) = (ton*) xmalloc ((size_t) sizeof (struct ton));
	(* lauf) -> name                        = name;
	(* lauf) -> ton_typ                     = ton_komplex;
	(* lauf) -> u.ton_komplex.bezugston     = bezugston;
	(* lauf) -> u.ton_komplex.komplex_liste = get_last_komplex_intervall ();
	(* lauf) -> next                        = NULL;

}

void get_new_ton_komplex_negative (const char *name, const char *bezugston)

{

	struct ton * * lauf;
	TRACE;

	for (lauf= & list_of_toene; * lauf; lauf= & (*lauf)->next) {
		if ( ! strcmp (name, (*lauf)->name)) {
			fatal_error(11,mutC_STR(name)); /* Tonname doppelt */
		}
	}

	(* lauf) = (ton*) xmalloc ((size_t) sizeof (struct ton));
	(* lauf) -> name                        = name;
	(* lauf) -> ton_typ                     = ton_komplex;
	(* lauf) -> u.ton_komplex.bezugston     = bezugston;

	{

		struct komplex_intervall * help = get_last_komplex_intervall ();

		if (help == NULL) {
			fatal_error (0, _T(__FILE__), __LINE__);
		}

		help -> faktor *= -1.0 ;

		(* lauf) -> u.ton_komplex.komplex_liste = help;
	}

	(* lauf) -> next                        = NULL;

}

/********* Einleseroutinen fuer die Tonsysteme          *********/
/*         Es wird einfach eine Liste of Tonsysteme aufgebaut  **/

/* ton_liste dient zum Aufsammeln einzelner Tîne
   wÑhrend eines Tonsystems. Die aufgebaute Liste wird dann
   jeweils an das Tonsystem angehÑngt. */

static struct ton * ton_liste;

void init_ton_liste (void)
{
	TRACE;
	ton_liste = NULL;
}

void get_new_ton_in_tonsystem (const char *name)

{

	struct ton * * lauf;
	TRACE;

	for (lauf= & ton_liste; * lauf; lauf= & (*lauf)->next) {
		/* Hier sind doppelte Tîne zulÑssig !! */
	}

	(* lauf) = (ton*) xmalloc ((size_t) sizeof (struct ton));
	(* lauf) -> name                    = name;
	(* lauf) -> next                    = NULL;

}

void get_new_tonsystem (const char * name, int taste)

{

	struct tonsystem * * lauf;
	TRACE;

	for (lauf= & list_of_tonsysteme; * lauf; lauf= & (*lauf)->next) {
		if ( ! strcmp (name, (*lauf)->name)) {
			fatal_error(12,mutC_STR(name)); /* Tonsystemname doppelt */
		}
	}

	(* lauf) = (struct tonsystem*) xmalloc ((size_t) sizeof (struct tonsystem));
	(* lauf) -> name          = name;
	(* lauf) -> taste         = taste;
	(* lauf) -> periode       = get_last_komplex_intervall ();
	(* lauf) -> toene         = ton_liste;
	(* lauf) -> next          = NULL;

}

void get_new_tonsystem_negative (const char * name, int taste)

{

	struct tonsystem * * lauf;
	TRACE;

	for (lauf= & list_of_tonsysteme; * lauf; lauf= & (*lauf)->next) {
		if ( ! strcmp (name, (*lauf)->name)) {
			fatal_error(12,mutC_STR(name)); /* Tonsystemname doppelt */
		}
	}

	(* lauf) = (struct tonsystem*) xmalloc ((size_t) sizeof (struct tonsystem));
	(* lauf) -> name          = name;
	(* lauf) -> taste         = taste;
	{

		struct komplex_intervall * help = get_last_komplex_intervall ();

		if (help == NULL)
			fatal_error (0, _T(__FILE__), __LINE__);

		help -> faktor *= -1.0 ;

		(* lauf) -> periode = help;
	}

	(* lauf) -> toene         = ton_liste;
	(* lauf) -> next          = NULL;

}


/********* Einleseroutinen fuer Umstimmungen            *********/
/*         Es wird erst eine leere Umstimmung eingerichtet,    **/
/*            init_umstimmung (name);                          **/
/*         in die dann die Varianten eingetragen werden.       **/
/*         Zuletzt wird diese Umstimmung in die Liste          **/
/*         eingehÑngt.					                       **/
/*            get_new_umstimmung ();                           **/

static struct umstimmung * tmp_umstimmung;

void init_umstimmung (const char * name)
{

	struct umstimmung * lauf;
	TRACE;

	for (lauf= list_of_umstimmungen; lauf; lauf= lauf -> next) {
		if ( ! strcmp (name, lauf -> name)) {
			fatal_error(13,mutC_STR(name)); /* Umstimmungsname doppelt */
		}
	}

	tmp_umstimmung = (umstimmung*) xmalloc ((size_t) sizeof (struct umstimmung));

	tmp_umstimmung -> name            = name;
	tmp_umstimmung -> parameter_liste = NULL;
	tmp_umstimmung -> next            = NULL;
}

void get_new_umstimmung (void)

{

	struct umstimmung * * lauf;
	TRACE;

	for (lauf= & list_of_umstimmungen; * lauf; lauf= & (*lauf)->next) {}

	(* lauf) = tmp_umstimmung;
}

void eintrage_parameterliste_in_umstimmung (void)
{
	TRACE;
	tmp_umstimmung -> parameter_liste = get_last_parameter_liste ();
}



/************ Die folgenden Funktionen tragen je eine         */
/*            Version von Umstimmung ein.                     */
/*            Genau eine dieser Funktionen wird zwischen      */
/*            init_umstimmung ()                              */
/*            und                                             */
/*            get_new_umstimmung (name)                       */
/*            aufgerufen.                                     */

void get_umstimmung_taste_abs (
        enum argument_typ argument,

        double zahl_wert, const char * parameter)
{
	TRACE;
	tmp_umstimmung -> umstimmung_typ = umstimmung_taste_abs;
	tmp_umstimmung -> u.umstimmung_taste_abs.
	argument.argument_typ
	= argument;

	if (argument == zahl) {
		tmp_umstimmung -> u.umstimmung_taste_abs.
		argument.u.zahl.zahl = (int) zahl_wert;
	} else {
		int i = parameter_nummer (0, parameter,
		                          tmp_umstimmung->parameter_liste);

		if (i == EOF) {
			fatal_error(31,
			            mutC_STR(parameter),
			            mutC_STR(tmp_umstimmung->name)); /* Parameter n.dekl. */
		}

		tmp_umstimmung -> u.umstimmung_taste_abs.

		argument.u.parameter.
		parameter_nummer = i;
		tmp_umstimmung -> u.umstimmung_taste_abs.
		argument.u.parameter.
		parameter_name = parameter;
	}
}

void get_umstimmung_taste_rel (

        enum argument_typ argument,

        double zahl_wert, const char * parameter, char vorzeichen)
{
	TRACE;
	tmp_umstimmung -> umstimmung_typ = umstimmung_taste_rel;
	tmp_umstimmung -> u.umstimmung_taste_rel.
	argument.argument_typ
	= argument;

	if (argument == zahl) {
		tmp_umstimmung -> u.umstimmung_taste_rel.
		argument.u.zahl.zahl = (int) zahl_wert;
	} else {
		int i = parameter_nummer (0, parameter,
		                          tmp_umstimmung->parameter_liste);

		if (i == EOF) {
			fatal_error(31,
			            mutC_STR(parameter),
			            mutC_STR(tmp_umstimmung -> name)); /* Parameter n.dekl. */
		}

		tmp_umstimmung -> u.umstimmung_taste_rel.

		argument.u.parameter.
		parameter_nummer = i;
		tmp_umstimmung -> u.umstimmung_taste_rel.
		argument.u.parameter.
		parameter_name = parameter;
	}

	tmp_umstimmung -> u.umstimmung_taste_rel.rechenzeichen

	= vorzeichen;
}

void get_umstimmung_breite_abs (

        enum argument_typ argument,

        double zahl_wert, const char * parameter)
{
	TRACE;
	tmp_umstimmung -> umstimmung_typ = umstimmung_breite_abs;
	tmp_umstimmung -> u.umstimmung_breite_abs.
	argument.argument_typ
	= argument;

	if (argument == zahl) {
		tmp_umstimmung -> u.umstimmung_breite_abs.
		argument.u.zahl.zahl = (int) zahl_wert;
	} else {
		int i = parameter_nummer (0, parameter,
		                          tmp_umstimmung->parameter_liste);

		if (i == EOF) {
			fatal_error(31,
			            mutC_STR(parameter),
			            mutC_STR(tmp_umstimmung->name)); /* Parameter n.dekl. */
		}

		tmp_umstimmung -> u.umstimmung_breite_abs.

		argument.u.parameter.
		parameter_nummer = i;
		tmp_umstimmung -> u.umstimmung_breite_abs.
		argument.u.parameter.
		parameter_name = parameter;
	}
}

void get_umstimmung_breite_rel (

        enum argument_typ argument,

        double zahl_wert, const char * parameter, char vorzeichen)
{
	TRACE;
	tmp_umstimmung -> umstimmung_typ = umstimmung_breite_rel;
	tmp_umstimmung -> u.umstimmung_breite_rel.
	argument.argument_typ
	= argument;

	if (argument == zahl) {
		tmp_umstimmung -> u.umstimmung_breite_rel.
		argument.u.zahl.zahl = (int) zahl_wert;
	} else {
		int i = parameter_nummer (0, parameter,
		                          tmp_umstimmung->parameter_liste);

		if (i == EOF) {
			fatal_error(31,
			            mutC_STR(parameter),
			            mutC_STR(tmp_umstimmung->name)); /* Parameter n.dekl. */
		}

		tmp_umstimmung -> u.umstimmung_breite_rel.

		argument.u.parameter.
		parameter_nummer = i;
		tmp_umstimmung -> u.umstimmung_breite_rel.
		argument.u.parameter.
		parameter_name = parameter;
	}

	tmp_umstimmung -> u.umstimmung_breite_rel.rechenzeichen

	= vorzeichen;
}

/*********** Bei "tonhîhe verÑndert" muû wieder die gesamte
             expression eines Tons pro Listeneintrag
             aufgesammelt werden.
********/

static struct ton * tmp_tonliste;

void init_umstimm_expression_list (void)
{
	TRACE;
	tmp_tonliste = NULL;
}

void get_new_umstimm_expression (const char * bezugston)

{

	struct ton * * lauf;
	TRACE;

	for (lauf= & tmp_tonliste; * lauf; lauf= & (*lauf)->next)
		/* Nur Ende der Liste finden */ ;

	(* lauf) = (ton*) xmalloc ((size_t) sizeof (struct ton));

	(* lauf) -> name                    = bezugston;

	(* lauf) -> ton_typ                 = ton_komplex;

	(* lauf) -> u.ton_komplex.bezugston = bezugston;

	(* lauf) -> u.ton_komplex.komplex_liste = NULL;

	(* lauf) -> next                    = NULL;

}


void get_new_umstimm_expression_positive (const char * bezugston)

{

	struct ton * * lauf;

	for (lauf= & tmp_tonliste; * lauf; lauf= & (*lauf)->next)
		/* Nur Ende der Liste finden */ ;

	(* lauf) = (ton*) xmalloc ((size_t) sizeof (struct ton));

	(* lauf) -> name                    = bezugston;

	(* lauf) -> ton_typ                 = ton_komplex;

	(* lauf) -> u.ton_komplex.bezugston = bezugston;

	(* lauf) -> u.ton_komplex.komplex_liste = get_last_komplex_intervall ();

	(* lauf) -> next                    = NULL;

}


void get_new_umstimm_expression_negative (const char * bezugston)

{

	struct ton * * lauf;
	TRACE;

	for (lauf= & tmp_tonliste; * lauf; lauf= & (*lauf)->next)
		/* Nur Ende der Liste finden */ ;

	(* lauf) = (ton*) xmalloc ((size_t) sizeof (struct ton));

	(* lauf) -> name                    = bezugston;

	(* lauf) -> ton_typ                 = ton_komplex;

	(* lauf) -> u.ton_komplex.bezugston = bezugston;

	{

		struct komplex_intervall * help = get_last_komplex_intervall ();
		help->faktor *= -1.0;
		(* lauf) -> u.ton_komplex.komplex_liste = help;
	}

	(* lauf) -> next                    = NULL;

}


void get_umstimmung_tonhoehe_veraendert (void)

{
	tmp_umstimmung -> umstimmung_typ = umstimmung_toene_veraendert;
	tmp_umstimmung -> u.umstimmung_toene_veraendert.tonliste
	= tmp_tonliste;
}

void get_umstimmung_wiederholung_abs (void)
{
	tmp_umstimmung -> umstimmung_typ = umstimmung_wiederholung_abs;
	tmp_umstimmung -> u.umstimmung_wiederholung_abs.komplex_liste
	= get_last_komplex_intervall ();
}

void get_umstimmung_wiederholung_abs_negative (void)
{
	tmp_umstimmung -> umstimmung_typ = umstimmung_wiederholung_abs;
	{

		struct komplex_intervall * help = get_last_komplex_intervall ();

		if (help == NULL)
			fatal_error (0, _T(__FILE__), __LINE__);

		help -> faktor *= -1.0;

		tmp_umstimmung ->
		u.umstimmung_wiederholung_abs.komplex_liste = help;
	}
}


void get_umstimmung_wiederholung_rel_positive (void)
{
	TRACE;
	tmp_umstimmung -> umstimmung_typ = umstimmung_wiederholung_rel;
	tmp_umstimmung -> u.umstimmung_wiederholung_rel.
	komplex_liste = get_last_komplex_intervall ();
}

void get_umstimmung_wiederholung_rel_negative (void)
{
	TRACE;
	tmp_umstimmung -> umstimmung_typ = umstimmung_wiederholung_rel;
	tmp_umstimmung -> u.umstimmung_wiederholung_rel.
	komplex_liste = get_last_komplex_intervall ();

	tmp_umstimmung -> u.umstimmung_wiederholung_rel.
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

	for (lauf= & tmp_umstimmungsbund_liste;
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
			if (parameter_nummer (0,params->name,
			                      tmp_umstimmung -> parameterliste)  == EOF ) {
				fatal_error(31,mutC_STR(params->name),mutC_STR((*lauf)->name)); /* Parameter n.dekl. */
			}
		}
	}

}

#endif

void get_umstimmung_umstimmungs_bund (void)
{
	TRACE;
	tmp_umstimmung -> umstimmung_typ = umstimmung_umstimmungsbund;
	tmp_umstimmung -> u.umstimmung_umstimmungsbund
	.aktions_liste = get_last_aktions_liste ();


	/* check, ob die Parameter zulÑssig sind */

	{

		struct aktions_liste * aktions_lauf;

		for (aktions_lauf = tmp_umstimmung -> u.umstimmung_umstimmungsbund.aktions_liste;
		                aktions_lauf;
		                aktions_lauf = aktions_lauf -> next) {

			if (aktions_lauf -> aktions_typ == aktion_aufruf) {

				struct argument_liste * argument_lauf;

				for (argument_lauf = aktions_lauf -> u.aktion_aufruf.argument_liste;
				                argument_lauf;
				                argument_lauf = argument_lauf -> next ) {
					if (argument_lauf -> argument.argument_typ == parameter) {
						int i = parameter_nummer (0,
						                          argument_lauf->argument.u.parameter.parameter_name,
						                          tmp_umstimmung -> parameter_liste);

						if (i == EOF ) {
							fatal_error(31,
							            mutC_STR(argument_lauf->argument.u.parameter.parameter_name),
							            mutC_STR(tmp_umstimmung -> name)); /* Parameter n.dekl. */
						} else {
							argument_lauf->argument.u.parameter.parameter_nummer = i;
						} /* if */
					} /* if */
				}  /* for argument_lauf */
			}  /* if (aktions_lauf... */
		}  /* for aktions_lauf */
	}



}


/***********************************
      case Umstimmungen:
***********************************/


static struct case_liste * tmp_umstimmungs_case_liste;


#if 0

static struct aufruf_liste * tmp_umstimmungs_case_aufrufs_liste;


void init_umstimmungs_case_aufrufs_liste (void)
{
	TRACE;
	tmp_umstimmungs_case_aufrufs_liste = NULL;
}

static struct umstimmung * get_last_umstimmungs_case_aufrufs_liste (void)
{
	TRACE;
	return tmp_umstimmungs_case_aufrufs_liste;
}


void get_umstimmungs_case_aufrufs_element (const char * aktion)

{

	struct aufruf_liste * * lauf;
	TRACE;

	for (lauf= & tmp_umstimmungs_case_aufrufs_liste;
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
				if (parameter_nummer (0,params->argument.u.parameter.parameter_name,
				                      tmp_umstimmung -> parameter_liste)  == EOF ) {
					fatal_error(31,
					            mutC_STR(params->argument.u.parameter.parameter_name),
					            mutC_STR((*lauf)->name)); /* Parameter n.dekl. */
				}
			}
		}
	}

}

#endif

void get_umstimmungs_case_zahl_element (int konstante)
{

	struct case_liste * * lauf;
	TRACE;

	for (lauf= & tmp_umstimmungs_case_liste;
	                * lauf;
	                lauf= & (*lauf)->next)
		/* Nur Ende der Liste finden */ ;

	(* lauf) = (case_liste*) xmalloc (sizeof (struct case_liste));

	(* lauf) -> case_label          = konstante;

	(* lauf) -> is_default          = 0;

	(* lauf) -> case_aktion         = get_last_aktions_liste ();

	(* lauf) -> next                = NULL;
}

void get_umstimmungs_case_default_element (void)

{

	struct case_liste * * lauf;
	TRACE;

	for (lauf= & tmp_umstimmungs_case_liste;
	                * lauf;
	                lauf= & (*lauf)->next)
		/* Nur Ende der Liste finden */ ;

	(* lauf) = (case_liste*) xmalloc (sizeof (struct case_liste));

	(* lauf) -> case_label          = -1000000; /* als dummy-wert */

	(* lauf) -> is_default          = 1;

	(* lauf) -> case_aktion         = get_last_aktions_liste ();

	(* lauf) -> next                = NULL;
}



void init_umstimmungs_case_liste (void)
{
	TRACE;
	tmp_umstimmungs_case_liste = NULL;
}

void get_umstimmung_umstimm_case_zahl (int selector)
{
	TRACE;
	tmp_umstimmung -> umstimmung_typ = umstimmung_umstimmungs_case;
	tmp_umstimmung -> u.umstimmung_umstimmungs_case
	.argument
	.argument_typ = zahl;
	tmp_umstimmung -> u.umstimmung_umstimmungs_case
	.argument
	.u.zahl.zahl = selector;
	tmp_umstimmung -> u.umstimmung_umstimmungs_case
	.umstimmungs_case_liste = tmp_umstimmungs_case_liste;


	/* check, ob die Parameter zulÑssig sind */

	{

		struct case_liste * case_lauf;

		for (case_lauf = tmp_umstimmung -> u.umstimmung_umstimmungs_case
		                 .umstimmungs_case_liste ;
		                case_lauf;
		                case_lauf = case_lauf -> next) {

			struct aktions_liste * aktions_lauf;

			for (aktions_lauf = case_lauf -> case_aktion;
			                aktions_lauf;
			                aktions_lauf = aktions_lauf -> next) {

				if (aktions_lauf -> aktions_typ == aktion_aufruf) {

					struct argument_liste * argument_lauf;

					for (argument_lauf = aktions_lauf -> u.aktion_aufruf.argument_liste;
					                argument_lauf;
					                argument_lauf = argument_lauf -> next ) {
						if (argument_lauf -> argument.argument_typ == parameter) {
							int i = parameter_nummer (0,
							                          argument_lauf->argument.u.parameter.parameter_name,
							                          tmp_umstimmung -> parameter_liste);

							if (i == EOF ) {
								fatal_error(31,
								            mutC_STR(argument_lauf->argument.u.parameter.parameter_name),
								            mutC_STR(tmp_umstimmung -> name)); /* Parameter n.dekl. */
							} else {
								argument_lauf->argument.u.parameter.parameter_nummer = i;
							} /* if */
						} /* if */
					}  /* for argument_lauf */
				} /* if (aktions_lauf ... */
			}  /* for aktions_lauf */
		}  /* for case_lauf */
	}


}


void get_umstimmung_umstimm_case_parameter (const char * selector)
{
	TRACE;
	tmp_umstimmung -> umstimmung_typ = umstimmung_umstimmungs_case;
	tmp_umstimmung -> u.umstimmung_umstimmungs_case
	.argument
	.argument_typ = parameter;
	tmp_umstimmung -> u.umstimmung_umstimmungs_case
	.argument
	.u.parameter.parameter_name = selector;

	/* und test, ob selector als Parameter deklariert ist. */

	{
		int i = parameter_nummer (0,selector, tmp_umstimmung -> parameter_liste);

		if (i == EOF ) {
			fatal_error(31,
			            mutC_STR(selector),
			            mutC_STR(tmp_umstimmung->name)); /* Parameter n.dekl. */
		} else {
			tmp_umstimmung -> u.umstimmung_umstimmungs_case
			.argument
			.u.parameter.parameter_nummer = i;

		}
	}

	tmp_umstimmung -> u.umstimmung_umstimmungs_case
	.umstimmungs_case_liste = tmp_umstimmungs_case_liste;



	/* check, ob die Parameter zulÑssig sind */

	{

		struct case_liste * case_lauf;

		for (case_lauf = tmp_umstimmung -> u.umstimmung_umstimmungs_case
		                 .umstimmungs_case_liste ;
		                case_lauf;
		                case_lauf = case_lauf -> next) {

			struct aktions_liste * aktions_lauf;

			for (aktions_lauf = case_lauf -> case_aktion;
			                aktions_lauf;
			                aktions_lauf = aktions_lauf -> next) {

				if (aktions_lauf -> aktions_typ == aktion_aufruf) {

					struct argument_liste * argument_lauf;

					for (argument_lauf = aktions_lauf -> u.aktion_aufruf.argument_liste;
					                argument_lauf;
					                argument_lauf = argument_lauf -> next ) {
						if (argument_lauf -> argument.argument_typ == parameter) {
							int i = parameter_nummer (0,
							                          argument_lauf->argument.u.parameter.parameter_name,
							                          tmp_umstimmung -> parameter_liste);

							if (i == EOF ) {
								fatal_error(31,
								            mutC_STR(argument_lauf->argument.u.parameter.parameter_name),
								            mutC_STR(tmp_umstimmung -> name)); /* Parameter n.dekl. */
							} else {
								argument_lauf->argument.u.parameter.parameter_nummer = i;
							} /* if */
						} /* if */
					}  /* for argument_lauf */
				} /* if (aktions_lauf .. */
			}  /* for aktions_lauf */
		}  /* for case_lauf */
	}



}


void get_umstimmung_midi_out (void)

{
	TRACE;
	tmp_umstimmung -> umstimmung_typ = umstimmung_midi_out;
	tmp_umstimmung -> u.umstimmung_midi_out.out_liste
	= get_last_integersequenz ();
}




/******* Einlesen der Harmonien. Pro Harmonie wird eine
         Liste von Tasten festgehalten.
*******/

static struct taste * tmp_tastenliste;

void init_tastenliste (void)
{
	TRACE;
	tmp_tastenliste = NULL;
}

void get_new_taste (int taste, char stern)

{

	struct taste * * lauf;
	TRACE;

	for (lauf= & tmp_tastenliste; * lauf; lauf= & (*lauf)->next)
		/* Nur Ende der Liste finden */ ;

	(* lauf) = (struct taste*) xmalloc (sizeof (struct taste));

	(* lauf) -> code               = taste;

	(* lauf) -> stern               = stern;

	(* lauf) -> next                = NULL;

}

void get_new_harmonie (const char * name, int bezugstaste)
{

	struct harmonie * * lauf;
	TRACE;

	for (lauf= & list_of_harmonien; * lauf; lauf= & (*lauf)->next) {
		if ( ! strcmp (name, (*lauf)->name)) {
			fatal_error(14, mutC_STR(name)); /* Harmoniename doppelt */
		}
	}

	(* lauf) = (harmonie*) xmalloc (sizeof (struct harmonie));
	(* lauf) -> name                = name;
	(* lauf) -> tastenliste         = tmp_tastenliste;
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
	tmp_aktion = xmalloc (sizeof (struct aktion));
	tmp_aktion -> aktions_typ = aktion_midi_out;
	tmp_aktion -> u.aktion_midi_out.midi_code   = get_last_integersequenz ();
}

void get_aktion_aufruf (const char * name)
{
	TRACE;

	tmp_aktion = xmalloc (sizeof (struct aktion));
	tmp_aktion -> aktions_typ = aktion_aufruf;
	tmp_aktion -> u.aktion_aufruf.name        = name;
	tmp_aktion -> u.aktion_aufruf.argument_liste
	= get_last_argument_liste ();
}


#endif



static int        tmp_vor_taste;

static const char *     tmp_name;

static int        tmp_nach_taste;

void get_harmoniebezeichner (int vor_taste,
                             const char * name,
                             int nach_taste)
{
	tmp_vor_taste   = vor_taste;
	tmp_name        = name;
	tmp_nach_taste  = nach_taste;
}

static struct ausloeser * tmp_ausloeser;

void init_ausloeser (void)
{
	TRACE;
	tmp_ausloeser = NULL;
}

struct ausloeser * get_last_ausloeser (void)
{
	TRACE;
	return tmp_ausloeser;
}

void get_ausloeser_default (void)

{
	TRACE;

	tmp_ausloeser = (ausloeser*) xmalloc (sizeof (struct ausloeser));
	tmp_ausloeser -> ausloeser_typ = ausloeser_default;
}

void get_ausloeser_harmonie (void)
{
	TRACE;

	tmp_ausloeser = (ausloeser*) xmalloc (sizeof (struct ausloeser));
	tmp_ausloeser -> ausloeser_typ = ausloeser_harmonie;
	tmp_ausloeser -> u.ausloeser_harmonie.vortaste  = tmp_vor_taste;
	tmp_ausloeser -> u.ausloeser_harmonie.name      = tmp_name;
	tmp_ausloeser -> u.ausloeser_harmonie.nachtaste = tmp_nach_taste;
}

void get_ausloeser_harmonie_form (void)
{
	TRACE;

	tmp_ausloeser = (ausloeser*) xmalloc (sizeof (struct ausloeser));
	tmp_ausloeser -> ausloeser_typ = ausloeser_harmonie_form;
	tmp_ausloeser -> u.ausloeser_harmonie_form.vortaste  = tmp_vor_taste;
	tmp_ausloeser -> u.ausloeser_harmonie_form.name      = tmp_name;
	tmp_ausloeser -> u.ausloeser_harmonie_form.nachtaste = tmp_nach_taste;
}

void get_ausloeser_taste (const char * name)
{
	TRACE;

	tmp_ausloeser = (ausloeser*) xmalloc (sizeof (struct ausloeser));
	tmp_ausloeser -> ausloeser_typ = ausloeser_taste;
	tmp_ausloeser -> u.ausloeser_taste.taste  = name;

	if (strlen (name) != 1) {
		fatal_error (52, mutC_STR(name));
	}

}

void get_ausloeser_midi_in (void)

{
	TRACE;

	tmp_ausloeser = (ausloeser*) xmalloc (sizeof (struct ausloeser));
	tmp_ausloeser -> ausloeser_typ = ausloeser_midi_in;
	tmp_ausloeser -> u.ausloeser_midi_in.midi_code
	= get_last_integersequenz ();
}








static struct anweisung * tmp_anweisungsliste;

void init_anweisungs_liste (void)
{
	TRACE;
	tmp_anweisungsliste = NULL;
}

struct anweisung * get_last_anweisungs_liste (void)
{
	TRACE;
	return tmp_anweisungsliste ;
}

void get_new_anweisung (void)

{

	struct anweisung * * lauf;
	TRACE;

	for (lauf= & tmp_anweisungsliste; * lauf; lauf= & (*lauf)->next)
		/* Nur Ende der Liste finden */ ;

	(* lauf) = (anweisung*) xmalloc (sizeof (struct anweisung));

	(* lauf) -> ausloeser   = get_last_ausloeser ();

	(* lauf) -> aktion      = get_last_aktions_liste ();

	(* lauf) -> next        = NULL;

}

void get_new_logik (const char * name, const char * einstimmung)
{

	struct logik * * lauf;
	TRACE;

	for (lauf= & list_of_logiken; * lauf; lauf= & (*lauf)->next) {
		if ( ! strcmp (name, (*lauf)->name)) {
			fatal_error(15, mutC_STR(name)); /* Logikname doppelt */
		}
	}

	(* lauf) = (logik*) xmalloc (sizeof (struct logik));
	(* lauf) -> name                = name;
	(* lauf) -> ausloeser           = get_last_ausloeser ();
	(* lauf) -> einstimmungs_name   = einstimmung;
	(* lauf) -> anweisungsliste     = NULL;
	(* lauf) -> next                = NULL;

}

void vervollstaendige_logik (void)

{

	struct logik * lauf;
	TRACE;

	for (lauf = list_of_logiken; lauf -> next; lauf = lauf->next) {}

	lauf -> anweisungsliste     = get_last_anweisungs_liste ();
}

/******* Einlesen der Instrumente *******/

void get_instrument_dekl (int midi_in, int midi_von, int midi_bis, int midi_umleit,

                          struct instrument ** list_to_insert)
{
	int temp;

	TRACE;
	/**///for (list_to_insert = & list_of_instrumente;

	for (;
	                * list_to_insert;
	                list_to_insert = & (*list_to_insert)->next)
	{
		if ( midi_in == (*list_to_insert)->midi_in) {
			fatal_error(18, midi_in); /* MIDI-Instrument doppelt */
		}
	}

	if ( midi_von > midi_bis )
	{
		temp=midi_von;       /* Vertauschen der Reihenfolge */
		midi_von=midi_bis;
		midi_bis=temp;

	}

	if ( (midi_in < 1) || (midi_in > 16) )
	{
		fatal_error(45);
	}

	if ( midi_von && midi_bis )
	{
		if ( (midi_von < 1) || (midi_von > 16) )
			fatal_error(45);

		if ( (midi_bis < 1) || (midi_bis > 16) )
			fatal_error(45);
	}

	if ( (midi_umleit < 0) || (midi_umleit > 16) )
	{
		fatal_error(45);
	}


	(* list_to_insert) = (instrument*) xmalloc (sizeof (struct instrument));
	(* list_to_insert) -> midi_in             = midi_in;
	(* list_to_insert) -> midi_von            = midi_von;
	(* list_to_insert) -> midi_bis            = midi_bis;
	(* list_to_insert) -> midi_umleit         = midi_umleit;
	(* list_to_insert) -> next                = NULL;

}




/**************************************************************

            Hier werden die Toene aufgelîst.
            Nach dem Parsing ist nur die Syntax-Struktur
            vorhanden, aber keine fertig ausgerechneten Toene.

            Es wird ein azyklischer Graph der Toene und ihrer
            Untertoene gebildet, der dann nach den
            depth-first-search traversiert wird.
            Dabei bekommt jeder Ton seine Absolutfrequenz berechnet.

****************************************************************/

static int anzahl_toene;       /* so viele Toene wurden gelesen */

static struct ton ** toene;    /* Feld von Toenen zum schnelleren Zugriff

                                  als ueber Listen */

static char * visited;         /* Traversierungsmerker */

static char * matrix;          /* Adjazenzmatrix (auf sie darf nur ueber

                                  das folgende Makro zugegriffen werden !*/

#define adjazent(a,b) matrix [ (a) * anzahl_toene * sizeof (char) \
                             + (b) * sizeof (char)]



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

static int ton_nummer (const char *name)
{
	int i;

	TRACE;
	for (i=0; i<anzahl_toene; i++)
		if ( ! strcmp (name, toene[i]->name)) return i;

	fatal_error(27, mutC_STR(name)); /* Ton n.dekl. */

	return 0; /* to prevent warnings */
}

static void test_zyklen (int startknoten)
{
	int i;

	TRACE;
	for (i=0; i<anzahl_toene; i++) {
		if (adjazent (startknoten, i)) {
			if (visited [i]) {
				fatal_error(65,
				            mutC_STR(toene [startknoten]->name),
				            mutC_STR(toene [i]->name));
			}

			visited [i] = 1;

			test_zyklen (i);
			visited [i] = 0;
		}
	}
}

static void berechne_ton_endgueltig (int k)
{
	int b;
	double help, help2;
	TRACE;

	switch (toene[k]->ton_typ) {

	case ton_absolut:         /* hier nichts zu tun */
		break;

	case ton_komplex:
		b = ton_nummer (toene[k]->u.ton_komplex.bezugston);

		berechne_ton_endgueltig (b);

		help2 = get_wert_komplex_intervall (toene[k]->u.ton_komplex.komplex_liste);

		help = toene[b]->u.ton_absolut.ton_wert;

		toene[k]->ton_typ = ton_absolut;

		toene[k]->u.ton_absolut.ton_wert = help * help2;

		break;

	default:
		fatal_error(0,_C_STR(_("loop")));
	}
}

static void berechne_toene_absolut (struct ton *list_of_toene)
{
	int i,j,k;

	TRACE;
	anzahl_toene = ton_list_laenge (list_of_toene);

	toene = (ton* *) xalloca (sizeof(struct ton *) * anzahl_toene);
	visited = (char*) xalloca (sizeof(char) * anzahl_toene);
	matrix = (char*) xalloca (sizeof(char) * anzahl_toene * anzahl_toene);


	/* Feld mit toenen initialisieren (zum schnelleren Zugriff) */

	belege_toene (toene, list_of_toene);

	/* Adjazenzmatrix initialisieren (Kein Ton hÑngt vom anderen ab) */

	for (i=0; i<anzahl_toene; i++)
	{
		for (j=0; j<anzahl_toene; j++) {
			adjazent (i,j) = 0;
		}
	}

	/* Adjazenzmatrix initialisieren (AbhÑngigkeiten eintragen) */

	for (i=0; i<anzahl_toene; i++)
	{
		if (toene[i]->ton_typ == ton_absolut)  /* alles ok */ ;
		else if (toene[i]->ton_typ == ton_komplex) {
			adjazent (i, ton_nummer (toene[i]->u.ton_komplex.bezugston)) = 1;
		} else {
			fatal_error(0,_C_STR(_("loop")));
		}
	}

#ifdef DEBUG
	/* Adjazenzmatrix anzeigen */
	if (isDebugFlag(kernel_parser)) {
		printf ("Matrix:\n");

		for (i=0; i<anzahl_toene; i++)
		{
			printf ("%s -> ", toene[i]->name);

			for (j=0; j<anzahl_toene; j++) {
				if (adjazent (i,j))
					printf ("%s  ", toene[j]->name);
			}
			
			printf ("\n");
		}

		printf ("\n");
	}

#endif

	/* auf Zyklenfreiheit Pruefen */

	for (k=0; k<anzahl_toene; k++)
		visited [k] = 0;

	for (k=0; k<anzahl_toene; k++)
	{
		visited [k] = 1;
		test_zyklen (k);
		visited [k] = 0;
	}

	/* Toene endgueltig berechnen */

	for (k=0; k<anzahl_toene; k++)
		berechne_ton_endgueltig (k);

#ifdef DEBUG
	/* Adjazenzmatrix anzeigen */

	if (isDebugFlag(kernel_parser)) {
		printf ("Matrix:\n");

		for (i=0; i<anzahl_toene; i++)
		{
			printf ("%s -> ", toene[i]->name);

			for (j=0; j<anzahl_toene; j++) {
				if (adjazent (i,j))
					printf ("%s  ", toene[j]->name);
			}

			printf ("\n");
		}

		printf ("\n");
	}
#endif

	xde_alloca (toene);
	xde_alloca (visited);
	xde_alloca (matrix);

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

static

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


static void check_ausloeser (struct ausloeser * ausloeser, const char * name)
{

	struct harmonie * help_harmonie;
	TRACE;

	if (ausloeser == NULL) return;

	if (ausloeser->ausloeser_typ == ausloeser_harmonie_form)
	{
		help_harmonie = get_harmonie (ausloeser->u.ausloeser_harmonie_form.name, list_of_harmonien);

		if (help_harmonie == NULL) {
			fatal_error (30,
			             mutC_STR(ausloeser->u.ausloeser_harmonie_form.name),
			             mutC_STR(name));
		}

		if (enthalten_in_tastenliste
		                (ausloeser->u.ausloeser_harmonie_form.vortaste,
		                 help_harmonie->tastenliste) ||
		                ausloeser->u.ausloeser_harmonie_form.vortaste
		                == -1 ) {
			/* OK */
		} else {
			compiler_warning (2, mutC_STR(name));
			/* Markierung setzen, fuer unmoeglichen Ausloeser */
			ausloeser->u.ausloeser_harmonie_form.vortaste = -2;
		}

		if (enthalten_in_tastenliste
		                (ausloeser->u.ausloeser_harmonie_form.nachtaste,
		                 help_harmonie->tastenliste) ||
		                ausloeser->u.ausloeser_harmonie_form.nachtaste
		                == -1 ) {
			/* OK */
		} else {
			compiler_warning (2, mutC_STR(name));
			/* Markierung setzen, fuer unmoeglichen Ausloeser */
			ausloeser->u.ausloeser_harmonie_form.vortaste = -2;
		}
	}


	if (ausloeser->ausloeser_typ == ausloeser_harmonie)
	{
		help_harmonie = get_harmonie (ausloeser->u.ausloeser_harmonie.name, list_of_harmonien);

		if (help_harmonie == NULL) {
			fatal_error (30,
			             mutC_STR(ausloeser->u.ausloeser_harmonie.name),
			             mutC_STR(name));
		}

		if (enthalten_in_tastenliste
		                (ausloeser->u.ausloeser_harmonie.vortaste,
		                 help_harmonie->tastenliste) ||
		                ausloeser->u.ausloeser_harmonie.vortaste
		                == -1 ) {
			/* OK */
		} else {
			compiler_warning (2, mutC_STR(name));
			/* Markierung setzen, fuer unmoeglichen Ausloeser */
			ausloeser->u.ausloeser_harmonie.vortaste = -2;
		}

		if (enthalten_in_tastenliste
		                (ausloeser->u.ausloeser_harmonie.nachtaste,
		                 help_harmonie->tastenliste) ||
		                ausloeser->u.ausloeser_harmonie.nachtaste
		                == -1 ) {
			/* OK */
		} else {
			compiler_warning (2, mutC_STR(name));
			/* Markierung setzen, fuer unmoeglichen Ausloeser */
			ausloeser->u.ausloeser_harmonie.vortaste = -2;
		}
	}

	if (ausloeser->ausloeser_typ == ausloeser_midi_in)
	{

		struct midiliste * midi_lauf
					= ausloeser->u.ausloeser_midi_in.midi_code;

		if (midi_lauf -> midi_code < 128 ||
		                midi_lauf -> midi_code > 255 ) {
			fatal_error (50, mutC_STR(name), _C_STR(_("status byte")));
		}

		if (midi_lauf -> midi_code & 0x000F ) {
			midi_lauf -> midi_code &= 0xFFF0;
			compiler_warning(1,mutC_STR(name));
		}

		midi_lauf = midi_lauf -> next;

		while (midi_lauf) {
			if (midi_lauf -> midi_code < 0 ||
			                midi_lauf -> midi_code > 127 ) {
				fatal_error (50, mutC_STR(name), _C_STR(_("data byte")));
			} else
				midi_lauf = midi_lauf -> next;
		}
	}

}



static void check_aktionen (struct aktions_liste * aktionen, const char * name)
{
	TRACE;

	for ( ; aktionen ; aktionen = aktionen -> next )
	{
		if (aktionen->aktions_typ == aktion_midi_out) {

			struct midiliste * midi_lauf
						= aktionen->u.aktion_midi_out.midi_code;

			if (midi_lauf -> midi_code < 128 ||
			                midi_lauf -> midi_code > 255 ) {
				compiler_warning (1, mutC_STR(name));
			}

			while (midi_lauf) {
				if (midi_lauf -> midi_code < 0 ||
				                midi_lauf -> midi_code > 255 ) {
					fatal_error (50, mutC_STR(name), _C_STR(_("byte")));
				}

				midi_lauf = midi_lauf -> next;
			}

		}

		if (aktionen->aktions_typ == aktion_aufruf) {

			struct umstimmung * help_umstimmung =
						        get_umstimmung (aktionen->u.aktion_aufruf.name,
						                        list_of_umstimmungen);

			struct tonsystem * help_tonsystem =
						        parser_get_tonsystem (aktionen->u.aktion_aufruf.name,
						                              list_of_tonsysteme);

			struct logik * help_logik =
						        get_logik (aktionen->u.aktion_aufruf.name,
						                   list_of_logiken);
			int i=0;

			if (help_umstimmung) i++;

			if (help_tonsystem)  i++;

			if (help_logik)      i++;

			if (i == 0) {
				fatal_error (38,
				             mutC_STR(aktionen->u.aktion_aufruf.name),
				             mutC_STR(name));
			}

			if (i > 1) {
				compiler_warning (3, mutC_STR(aktionen->u.aktion_aufruf.name), mutC_STR(name));
			}

			if (help_umstimmung) {
				if (argument_list_laenge (aktionen->u.aktion_aufruf.argument_liste)
				                != parameter_list_laenge (help_umstimmung->parameter_liste)) {

					fatal_error (61, mutC_STR(name), mutC_STR(aktionen->u.aktion_aufruf.name));
				}
			} else if (help_tonsystem) {
				if (argument_list_laenge (aktionen->u.aktion_aufruf.argument_liste)
				                != 0 ) {

					fatal_error (61, mutC_STR(name), mutC_STR(aktionen->u.aktion_aufruf.name));
				}
			} else if (help_logik) {
				if (argument_list_laenge (aktionen->u.aktion_aufruf.argument_liste)
				                != 0 ) {

					fatal_error (61, mutC_STR(name), mutC_STR(aktionen->u.aktion_aufruf.name));
				}
			}

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

static int anzahl_umstimmungen_und_logiken;  /* so viele Umstimmungen wurden gelesen */

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

static struct umst_oder_logik * zyklen_feld;    /* Feld von Umstimmungen

                      zum schnelleren Zugriff als ueber Listen */

static char * u_visited;         /* Traversierungsmerker */

static char * u_matrix; /* Adjazenzmatrix (auf sie darf nur ueber

                                  das folgende Makro zugegriffen werden !*/

#define u_adjazent(a,b) u_matrix [ (a) * anzahl_umstimmungen_und_logiken \
                * sizeof (char) + (b) * sizeof (char)]



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

static int test_zyklen_nummer (const char *name)
{
	int i;
	TRACE;

	for (i=0; i<anzahl_umstimmungen_und_logiken; i++)
		if ( ((zyklen_feld[i].umst_oder_logik_typ == typ_umstimmung) &&
                      (! strcmp (name, zyklen_feld[i].u.umstimmung->name)))
                     ||
                     ((zyklen_feld[i].umst_oder_logik_typ == typ_logik) &&
                      (! strcmp (name, zyklen_feld[i].u.logik->name)))
		   ) return i;

	fatal_error(29,mutC_STR(name)); /* Umst.n.dekl. */

	return 0; /* to prevent warnings */
}

static void u_test_zyklen (int startknoten)
{
	int i;
	TRACE;

	for (i=0; i<anzahl_umstimmungen_und_logiken; i++) {
		if (u_adjazent (startknoten, i)) {
			if (u_visited [i]) {
				fatal_error(66,
				            zyklen_feld [startknoten].umst_oder_logik_typ == typ_umstimmung ?
				            mutC_STR(zyklen_feld [startknoten].u.umstimmung->name) :
				            mutC_STR(zyklen_feld [startknoten].u.logik->name),
				            zyklen_feld [i].umst_oder_logik_typ == typ_umstimmung ?
				            mutC_STR(zyklen_feld [i].u.umstimmung->name) :
				            mutC_STR(zyklen_feld [i].u.logik->name));
			}

			u_visited [i] = 1;

			u_test_zyklen (i);
			u_visited [i] = 0;
		}
	}
}





static void check_konsistenz (void)
{
	TRACE;
	allgemeine_initialisierungen();

	/* Tonsysteme:
	   öberprÅfen, ob Periode und Tîne deklariert sind
	   und ob die Taste im Bereich 36 - 96 liegt.
	*/

	{ struct tonsystem * lauf;

		struct ton * ton_lauf;

		for (lauf = list_of_tonsysteme; lauf; lauf = lauf->next) {
			check_komplex_intervall (lauf->periode, lauf->name);

			if (lauf->taste < 24  ||  lauf->taste > 108) {
				fatal_error(47,lauf->taste,mutC_STR(lauf->name)); /* UngÅlt. Taste */
			}

			for (ton_lauf = lauf->toene;
			                ton_lauf;
			                ton_lauf = ton_lauf->next) {
				if ((ton_lauf->name != NULL) &&
				                (get_ton (ton_lauf->name, list_of_toene) == NULL)) {
					fatal_error(33,mutC_STR(ton_lauf->name),mutC_STR(lauf->name));
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

		for (lauf = list_of_umstimmungen; lauf; lauf = lauf -> next) {
			switch (lauf -> umstimmung_typ) {

			default :
				TRACE;
				fatal_error (0, _T(__FILE__), __LINE__);

				break;

			case umstimmung_taste_abs :
			case umstimmung_taste_rel :
			case umstimmung_breite_abs :
			case umstimmung_breite_rel :
				TRACE;
				break;

			case umstimmung_wiederholung_rel :
				TRACE;
				check_komplex_intervall (lauf->u.umstimmung_wiederholung_rel.komplex_liste,
				                         lauf->name);

				break;

			case umstimmung_wiederholung_abs :
				TRACE;
				check_komplex_intervall (lauf->u.umstimmung_wiederholung_abs.komplex_liste,
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
							fatal_error(48,mutC_STR(lauf->name), mutC_STR(lauf_ton->name));
							/* nicht komplexer Ton */
						}

						if (strcmp (lauf_ton->name,
						                lauf_ton->u.ton_komplex.bezugston)) {
							fatal_error(0,_T(__FILE__),__LINE__,_C_STR(_("retuning")));
						}

						if ((lauf_ton->name[0] != '@') &&
						                (get_ton (lauf_ton->name, list_of_toene) == NULL)) {
							fatal_error(34,mutC_STR(lauf_ton->name),mutC_STR(lauf->name));
							/* Undekl. Ton in Umst. */
						}

						check_komplex_intervall (lauf_ton->u.ton_komplex.komplex_liste,

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
									                        list_of_umstimmungen);

						if (umst == NULL) {

							struct tonsystem * tonsys =
										        parser_get_tonsystem (help_aktionen -> u.aktion_aufruf.name,
										                              list_of_tonsysteme);

							if (tonsys == NULL) {

								struct logik * help_logik;
								help_logik = get_logik (help_aktionen -> u.aktion_aufruf.name,
								                        list_of_logiken);

								if (help_logik == NULL) {
									fatal_error(36,mutC_STR(help_aktionen -> u.aktion_aufruf.name)
									            ,mutC_STR(lauf->name));
									/* Umst. in Bund */
								} else {
									if (help_aktionen -> u.aktion_aufruf.argument_liste != NULL) {
										fatal_error (63, mutC_STR(lauf -> name) ,
										             mutC_STR(help_aktionen -> u.aktion_aufruf.name));
									}
								}
							} else {
								if (help_aktionen -> u.aktion_aufruf.argument_liste != NULL) {
									fatal_error (63, mutC_STR(lauf -> name), mutC_STR(help_aktionen -> u.aktion_aufruf.name));
								}
							}
						} else {
							if (argument_list_laenge (help_aktionen -> u.aktion_aufruf.argument_liste)
							                != parameter_list_laenge (umst -> parameter_liste)) {
								fatal_error(60,mutC_STR(lauf->name),mutC_STR(help_aktionen -> u.aktion_aufruf.name));
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
						fatal_error (22, (int)(case_lauf -> case_label),
						             mutC_STR(lauf -> name));
					}
				}


				for (anzahl_defaults = 0,
				                case_lauf = lauf->u.umstimmung_umstimmungs_case.umstimmungs_case_liste;
				                case_lauf;
				                case_lauf = case_lauf -> next ) {

					if (case_lauf -> is_default) {
						anzahl_defaults ++;

						if (anzahl_defaults > 1) {
							fatal_error (21, mutC_STR(lauf -> name));
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
										                        list_of_umstimmungen);

							if (umst == NULL) {

								struct tonsystem * tonsys =
											        parser_get_tonsystem (help_aktionen -> u.aktion_aufruf.name,
											                              list_of_tonsysteme);

								if (tonsys == NULL) {

									struct logik * help_logik;
									help_logik = get_logik (help_aktionen -> u.aktion_aufruf.name,
									                        list_of_logiken);

									if (help_logik == NULL) {
										fatal_error(36,mutC_STR(help_aktionen -> u.aktion_aufruf.name)
										            ,lauf->name);
										/* Umst. in Bund */
									} else {
										if (help_aktionen -> u.aktion_aufruf.argument_liste != NULL) {
											fatal_error (64, mutC_STR(lauf -> name) ,
											             mutC_STR(help_aktionen -> u.aktion_aufruf.name));
										}
									}
								} else {
									if (help_aktionen -> u.aktion_aufruf.argument_liste != NULL) {
										fatal_error (64, mutC_STR(lauf -> name) ,
										             mutC_STR(help_aktionen -> u.aktion_aufruf.name));
									}
								}
							} else {
								if (argument_list_laenge (help_aktionen -> u.aktion_aufruf.argument_liste)
								                != parameter_list_laenge (umst -> parameter_liste)) {
									fatal_error(60, mutC_STR(lauf->name),
									            mutC_STR(help_aktionen -> u.aktion_aufruf.name));
								}
							}
						}
					}
				}
			}

			break;
			}  /* of switch */
		}  /* of for */

		/**** testzyklen ****/

		{
			int i,j,k;

			anzahl_umstimmungen_und_logiken =
			        umstimmungs_list_laenge (list_of_umstimmungen)
			        + logik_list_laenge (list_of_logiken) ;

			zyklen_feld = (umst_oder_logik*) xalloca (sizeof(struct umst_oder_logik) * anzahl_umstimmungen_und_logiken);
			u_visited = (char*) xalloca (sizeof(char) * anzahl_umstimmungen_und_logiken);
			u_matrix = (char*) xalloca (sizeof(char) * anzahl_umstimmungen_und_logiken
			                            * anzahl_umstimmungen_und_logiken);


			/* Feld mit Umstimmungen initialisieren (zum schnelleren Zugriff) */

			belege_zyklenfeld (zyklen_feld, list_of_umstimmungen, list_of_logiken);

			/* Adjazenzmatrix initialisieren (Keine Umstimmung
			               hÑngt von einer anderen ab) */

			for (i=0; i<anzahl_umstimmungen_und_logiken; i++) {
				for (j=0; j<anzahl_umstimmungen_und_logiken; j++) {
					u_adjazent (i,j) = 0;
				}
			}

			/* Adjazenzmatrix initialisieren (AbhÑngigkeiten eintragen) */

			for (i=0; i<anzahl_umstimmungen_und_logiken; i++) {
				if (zyklen_feld[i].umst_oder_logik_typ == typ_umstimmung &&
				                zyklen_feld[i].u.umstimmung->umstimmung_typ == umstimmung_umstimmungsbund) {

					struct aktions_liste *lauf = zyklen_feld[i].u.umstimmung->u.umstimmung_umstimmungsbund.aktions_liste;

					for ( ; lauf ; lauf = lauf -> next ) {
						if (lauf -> aktions_typ == aktion_aufruf) {
							if (get_umstimmung (lauf -> u.aktion_aufruf.name,
							                    list_of_umstimmungen) != NULL
							                ||
							                get_logik (lauf -> u.aktion_aufruf.name,
							                           list_of_logiken) != NULL
							   ) {
								/* Keine Tonsysteme adjazent eintragen */

								u_adjazent (i, test_zyklen_nummer (lauf->u.aktion_aufruf.name)) = 1;
							}
						}
					}
				} else if (zyklen_feld[i].umst_oder_logik_typ == typ_umstimmung &&
				                zyklen_feld[i].u.umstimmung->umstimmung_typ ==
				                umstimmung_umstimmungs_case) {

					struct case_liste * case_lauf;

					for (case_lauf = zyklen_feld[i].u.umstimmung->u.umstimmung_umstimmungs_case.umstimmungs_case_liste;
					                case_lauf;
					                case_lauf = case_lauf -> next) {

						struct aktions_liste *lauf = case_lauf -> case_aktion;

						for ( ; lauf ; lauf = lauf -> next ) {
							if (lauf -> aktions_typ == aktion_aufruf) {
								if (get_umstimmung (lauf -> u.aktion_aufruf.name,
								                    list_of_umstimmungen) != NULL
								                ||
								                get_logik (lauf -> u.aktion_aufruf.name,
								                           list_of_logiken) != NULL
								   ) {
									/* Keine Tonsysteme adjazent eintragen */

									u_adjazent (i, test_zyklen_nummer (lauf->u.aktion_aufruf.name)) = 1;
								}
							}
						}
					}
				} else if (zyklen_feld[i].umst_oder_logik_typ == typ_logik &&
				                zyklen_feld[i].u.logik->einstimmungs_name) {

					if (get_umstimmung (zyklen_feld[i].u.logik->einstimmungs_name,
					                    list_of_umstimmungen) != NULL) {
						/* Keine Tonsysteme adjazent eintragen */

						u_adjazent (i, test_zyklen_nummer (zyklen_feld[i].u.logik->einstimmungs_name)) = 1;
					}
				}
			}

#ifdef DEBUG_ANZEIGE_2
			/* Adjazenzmatrix anzeigen */

			printf ("U_Matrix:\n");

			for (i=0; i<anzahl_umstimmungen_und_logiken; i++) {
				if (zyklen_feld[i].umst_oder_logik_typ == typ_umstimmung)
					printf ("Umstimmung %s -> ", zyklen_feld[i].u.umstimmung->name);
				else
					printf ("Logik %s -> ", zyklen_feld[i].u.logik->name);

				for (j=0; j<anzahl_umstimmungen_und_logiken; j++) {
					if (u_adjazent (i,j))
						if (zyklen_feld[j].umst_oder_logik_typ == typ_umstimmung)
							printf ("Umstimmung %s ", zyklen_feld[j].u.umstimmung->name);
						else
							printf ("Logik %s -> ", zyklen_feld[j].u.logik->name);
				}

				printf ("\n");
			}

			printf ("\n");

#endif

			/* auf Zyklenfreiheit Pruefen */

			for (k=0; k<anzahl_umstimmungen_und_logiken; k++)
				u_visited [k] = 0;

			for (k=0; k<anzahl_umstimmungen_und_logiken; k++) {
				u_visited [k] = 1;
				u_test_zyklen (k);
				u_visited [k] = 0;
			}


#ifdef DEBUG_ANZEIGE_2
			/* Adjazenzmatrix anzeigen */

			printf ("U_Matrix:\n");

			for (i=0; i<anzahl_umstimmungen_und_logiken; i++) {
				if (zyklen_feld[i].umst_oder_logik_typ == typ_umstimmung)
					printf ("Umstimmung %s -> ", zyklen_feld[i].u.umstimmung->name);
				else
					printf ("Logik %s -> ", zyklen_feld[i].u.logik->name);

				for (j=0; j<anzahl_umstimmungen_und_logiken; j++) {
					if (u_adjazent (i,j))
						if (zyklen_feld[j].umst_oder_logik_typ == typ_umstimmung)
							printf ("Umstimmung %s ", zyklen_feld[j].u.umstimmung->name);
						else
							printf ("Logik %s -> ", zyklen_feld[j].u.logik->name);
				}

				printf ("\n");
			}

			printf ("\n");

#endif

			xde_alloca (zyklen_feld);
			xde_alloca (u_visited);
			xde_alloca (u_matrix);

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

		for (lauf = list_of_logiken; lauf; lauf = lauf->next) {

			struct umstimmung * help_umstimmung;

			check_ausloeser (lauf->ausloeser, lauf->name);

			/* Eine Logik darf nicht mit dem DEFAULT-Auslîser aufgerufen werden */

			if (lauf->ausloeser) {
				if (lauf->ausloeser->ausloeser_typ == ausloeser_default) {
					fatal_error (51, mutC_STR(lauf->name));
				}
			}

			if (lauf->einstimmungs_name!=NULL) {
				if (parser_get_tonsystem (lauf->einstimmungs_name, list_of_tonsysteme) == NULL) {
					if ((help_umstimmung=get_umstimmung (lauf->einstimmungs_name, list_of_umstimmungen)) == NULL) {
						fatal_error(37,mutC_STR(lauf->einstimmungs_name),
						            mutC_STR(lauf->name));
						/* Einst. in Logik */
					} else {
						if (parameter_list_laenge (help_umstimmung -> parameter_liste) != 0) {
							fatal_error(62, mutC_STR(lauf->name),
							            mutC_STR(lauf->einstimmungs_name));
						}
					}
				}
			}

			for (anweisungs_lauf = lauf->anweisungsliste,
			                anzahl_default_ausloeser = 0;
			                anweisungs_lauf;
			                anweisungs_lauf = anweisungs_lauf->next) {

				check_ausloeser (anweisungs_lauf->ausloeser, lauf->name);

				if (anweisungs_lauf->ausloeser == NULL)
					fatal_error (0, _T(__FILE__), __LINE__);
				else {
					if (anweisungs_lauf->ausloeser->ausloeser_typ
					                == ausloeser_default) {
						anzahl_default_ausloeser ++;

						if (anzahl_default_ausloeser > 1) {
							fatal_error (20, mutC_STR(lauf -> name));
						} else {
							if (anweisungs_lauf -> next != NULL)
								compiler_warning (4, mutC_STR(lauf -> name));
						}
					}
				}

				check_aktionen (anweisungs_lauf -> aktion, lauf->name);

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
		struct argument_liste * help;
		printf ("                Umstimmungs-name: %s, Parameter: ",
			action->u.aktion_aufruf.name ? 
			action->u.aktion_aufruf.name : "(NULL)");
		
		for (help = action->u.aktion_aufruf.argument_liste; 
		     help; help = help->next ) {
			drucke_argument ( & help -> argument );
		}
		break;
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

///\}
