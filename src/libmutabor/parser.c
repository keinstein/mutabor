/** \file
********************************************************************
* Mutabor Fileparser.
*
* $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/libmutabor/parser.c,v 1.4 2005/11/03 14:56:11 keinstein Exp $
* \author R. Krau√üe <krausze@users.berlios.de>
* \version $Revision: 1.4 $
* \date $Date: 2005/11/03 14:56:11 $
*
* $Log: parser.c,v $
* Revision 1.4  2005/11/03 14:56:11  keinstein
* type in printf call
*
* Revision 1.3  2005/07/20 12:24:52  keinstein
* CVS-Kopf
* config.h
* includes f√ºr Doxygen optimiert" parameter.c
* Formatierung
* Compilierbar gemacht
* rudiment√§re Debug-Ausgabe
*
* Revision 1.2  2005/07/19 15:15:27  keinstein
* Using own Templates
*
********************************************************************
* \note Eventuell Listen-Z‰hlen mit while-Schleife 
* \note Eventuell Listen-Z‰hlen als Template
*/
#include <string.h>
#include "mutabor/parser.h"
#include "mutabor/tonsystem.h"
#include "mutabor/umstimmung.h"
#include "mutabor/harmonie.h"
#include "mutabor/logik.h"
#include "mutabor/mut_tab.h"
#include "mutabor/instrument.h"
#include "mutabor/parameter.h"
#include "mutabor/heap.h"
#include "mutabor/errors.h"

/* Globale Variablen des Compilers mit dem Codegenerator und
   dem Tabellengenerator  */

/*********** Es folgen die Wurzeln der Listen.
             Jede Liste ist nur einmal und global vorhanden,
             da die Sprache NICHT rekursiv ist.
***********/

/** Wurzel der Instrumente */
struct instrument     *  list_of_instrumente;
/** Wurzel der Instrumentenkonfiguration */
struct instrument     *  list_of_config_instrumente;

/*
  static void print_aktion (struct aktion * this);
*/


/*********  Allgemeine Hilfsfunktionen ********/

/** Allgemeine Initialisierungen. Definiert \a ton_ohne_namen als
 * ,,Nullton``.
 */
void allgemeine_initialisierungen( void ) {
	init_nullton();
}




/************************/



/********* Eintrittspunkt in das File ist hier !! *******/

/** Quelldatei f¸r das Mutabor-Programm */
FILE * mutabor_parser_in;

/** Liest ein Mutabor-Programm ein.
 * Ist \c DEBUG_ANZEIGE definiert, dann werden die erzeugten Strukturen 
 * auf der Standard-Ausgabe angezeigt.
 * \note Eigentlich sollte die Debug-Ausgabe auf die Standardfehlerausgabe.
 */
void mutabor_programm_einlesen ( char *filename )
{

#ifdef DEBUG
	if (mutabor_debug_level)
		fprintf(stderr,"Datei ˆffnen: %s\n",filename);
#endif
  
	if ((mutabor_parser_in = fopen (filename, "r")) == NULL) {
		fatal_error(3,filename);
	}

#ifdef DEBUG
	if (mutabor_debug_level)
		fprintf(stderr,"Datei geˆffnet: %s\n",filename);
#endif
  
  
	list_of_intervalle            = NULL;
	list_of_toene                 = NULL;
	list_of_tonsysteme            = NULL;
	list_of_umstimmungen          = NULL;
	list_of_harmonien             = NULL;
	list_of_logiken               = NULL;
	list_of_instrumente           = NULL;
	list_of_config_instrumente    = NULL;

  
#ifdef DEBUG
	if (mutabor_debug_level) 
		fprintf (stderr,"\nStart parsing\n");
#endif
  
	if (mutabor_parser_parse()) {
		fatal_error(7,__FILE__,__LINE__); /* Wird sowieso nie aufgerufen ... */
	}
  
	fclose (mutabor_parser_in);

#ifdef DEBUG
	if (mutabor_debug_level) 
		fprintf (stderr,"\nEnd parsing\n");
#endif
  
  
	/*
	// NEU: wenn kein Intervall oder Ton da, dann Speichermangel
	// also evtl. Dummy
	// (das Problem l‰ﬂt sich sicher auch direkt lˆsen ...)
	*/
  
	if ( !list_of_intervalle )
		get_new_intervall("__TopSecret__RK__Intervall__", 1.0);

#ifdef DEBUG
	if (mutabor_debug_level) 
		fprintf (stderr,"Calculate absolute interval values\n");
#endif
 
	berechne_intervalle_absolut (list_of_intervalle);
  
	if ( !list_of_toene )
		get_new_ton_absolut("__TopSecret__RK__Ton__", 440.0);

	berechne_toene_absolut (list_of_toene);
  
  
#ifdef DEBUG
	if (mutabor_debug_level) 
		fprintf (stderr,"Calculate instruments\n");
#endif
	/* Falls kein Instrument angegeben ist: Dann 1 -> 1-16 */
  
	if (list_of_instrumente == NULL &&
	    list_of_config_instrumente == NULL) { 
		get_instrument_dekl (1, 1, 16, 0, & list_of_instrumente);
	}
	else if (list_of_instrumente == NULL) {
		list_of_instrumente = list_of_config_instrumente;
	}
  
  
#ifdef DEBUG
	if (mutabor_debug_level) 
		fprintf (stderr,"Calculate number of distance and center\n");
#endif
	setze_nummer_von_abstand_und_zentrum ();
  
#ifdef DEBUG
	if (mutabor_debug_level) 
		fprintf (stderr,"Check consistency\n");
#endif
	check_konsistenz ();
  
	if (mutabor_debug_level) {
		{ 
			struct intervall * lauf;
			printf ("\n");
			for (lauf=list_of_intervalle; lauf; lauf=lauf->next) {
				if (lauf->intervall_typ==intervall_absolut)
					printf ("Name: %s, Wert: %f:\n", lauf->name,
						lauf->u.intervall_absolut.intervall_wert );
				else printf ("Komplexes Intervall: Name: %s\n",lauf->name);
			}
		}
    
		{ 
			struct ton * lauf;
			printf ("\n");
			for (lauf=list_of_toene; lauf; lauf=lauf->next) {
				drucke_ton (lauf);
	
			}
		}
    
		{ 
			struct tonsystem * lauf;
			printf ("\n");
			for (lauf=list_of_tonsysteme; lauf; lauf=lauf->next) {
				struct ton * help;
				printf ("Name: %s, Taste: %d, Periode: %s, "
					"Tonleiter_breite: %d\n", 
					lauf->name,
					lauf->taste,
					lauf->periode->name, 
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
					printf ("Name : %s \n",
						lauf -> u.umstimmung_wiederholung_abs.komplex_liste->name);
					break;
				case umstimmung_wiederholung_rel :
					printf ("        umstimmung_wiederholung_rel : %s",
						lauf->u.umstimmung_wiederholung_rel.komplex_liste->name);
					/*	    drucke_argument (
						    lauf -> u.umstimmung_wiederholung_rel.komplex_liste);
						    printf (" R-zeichen: \"%c\"\n",
						    lauf -> u.umstimmung_wiederholung_rel.rechenzeichen);
					*/
					break;
				case umstimmung_umstimmungsbund : {
					struct aktions_liste * help_umst;
					printf ("        umstimmung_umstimmungsbund : \n");
					print_aktions_liste (lauf->u.umstimmung_umstimmungsbund.aktions_liste);
					/*
					  for (help_umst = lauf->u.umstimmung_umstimmungsbund.aktions_liste;
					  help_umst;
					  help_umst = help_umst -> next ) {
					  struct argument_liste * help;
					  printf ("                Umstimmungs-name: %s, Parameter: ",
					  help_umst->name ? help_umst->name : "(NULL)");
					  for (help = help_umst->argument_liste; help; help = help->next ) {
					  drucke_argument ( & help -> argument );
					  }
					  printf ("\n");
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
						struct aktions_liste * help_umst;

						if (help_case->is_default)
							printf ("(ANSONSTEN)");
						else
							printf ("%d ", help_case->case_label);
		
						for (help_umst = help_case->case_aktion;
						     help_umst;
						     help_umst = help_umst -> next ) {
							struct argument_liste * help;
							print_aktions_liste(help_umst);
							/*
							  printf ("                Aktions-name: %s, Parameter: ",
							  help_umst->name ? help_umst->name : "(NULL)");
		  
							  for (help = help_umst->argument_liste; help; help = help->next ) {
							  drucke_argument ( & help->argument);
							  }
							*/
							printf ("\n");
						}
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
				printf ("Anweisungsliste drucken .... ");
				/*
				  for (anw_lauf = lauf->anweisungsliste;
				  anw_lauf;
				  anw_lauf = anw_lauf->next) {
				  print_ausloeser (anw_lauf->ausloeser);
				  print_aktion (anw_lauf->aktion); 
				  }*/
	 
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
	} /* Ende des Debug_bereiches */

    
}

/************/


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





/******* Einlesen der Harmonien. Pro Harmonie wird eine
         Liste von Tasten festgehalten.
*******/
/******* Einlesen der Logiken. Pro Logik wird eine
         Liste von Anweisungen festgehalten.
*******/


#if 0

static struct aktion * tmp_aktion;

struct aktion * get_last_aktion (void)
{
	return tmp_aktion;
}

void get_aktion_midi_out (void)
{
	tmp_aktion = xmalloc (sizeof (struct aktion));
	tmp_aktion -> aktions_typ = aktion_midi_out;
	tmp_aktion -> u.aktion_midi_out.midi_code   = get_last_integersequenz ();
}
    
void get_aktion_aufruf (char * name)
{
	tmp_aktion = xmalloc (sizeof (struct aktion));
	tmp_aktion -> aktions_typ = aktion_aufruf;
	tmp_aktion -> u.aktion_aufruf.name        = name;
	tmp_aktion -> u.aktion_aufruf.argument_liste
		= get_last_argument_liste ();
}


#endif
    







/************** Hier wird die innere Konsistenz des
                ganzen MUTABOR-Programms geprÅft.
                Bei Fehlern wird einfach abgebrochen,
                ansonsten hat diese Funktion keine
                verÑndernde Wirkung auf die Listen.
                
                Eintrittspunkt ist "check_konsistenz".
                
**************/


/**************************************************************

            Hier sind einige Hilfsfunktionen zum Testen,
            daû UmstimmungsbÅnde und die Einstimmungen der
            Logiken sich nicht rekursiv enthalten.
            
            Es wird ein azyklischer Graph der Umstimmungen
            gebildet, der dann nach den
            depth-first-search traversiert wird.
            Dabei wird ein beliebiger Zyklus festgestellt.
            
****************************************************************/

static int anzahl_umstimmungen_und_logiken;  /**< so viele Umstimmungen wurden gelesen */

/** Typbezeichner */
enum umst_oder_logik_typ { typ_umstimmung, typ_logik };
struct umst_oder_logik {
	enum umst_oder_logik_typ umst_oder_logik_typ; /**< Typ */
	union {
		struct umstimmung * umstimmung;  /**< Umstimmung */
		struct logik * logik;            /**< Logik */
	} u;
};

static struct umst_oder_logik * zyklen_feld;    /**< Feld von Umstimmungen
						   zum schnelleren Zugriff als ueber Listen */

static char * u_visited;         /**< Traversierungsmerker */

static char * u_matrix; /**< Adjazenzmatrix (auf sie darf nur ueber
			   das folgende Makro zugegriffen werden !*/

/** Adjazenz-Matrix Eintrag von \c u_matrix 
 * \param[in] a Zeile
 * \param[in] b Spalte
 */
#define u_adjazent(a,b) u_matrix [ (a) * anzahl_umstimmungen_und_logiken \
				   * sizeof (char) + (b) * sizeof (char)]
  


/** Erzeugt ein Array, in dem alle Umstimmungen und Logiken enthalten sind.
 * \param[out] zyklen_feld Feld mit den Umstimmungen und Logiken
 * \param[in]  liste1      einfach verkettete Liste mit Umstimmungen
 * \param[in]  liste2      einfach verkettete Liste mit Logiken
 */
static void belege_zyklenfeld (struct umst_oder_logik *zyklen_feld,
			       struct umstimmung * liste1,
			       struct logik * liste2)
{
	int i = 0;
	while (liste1) {
		zyklen_feld[i].umst_oder_logik_typ = typ_umstimmung;
		zyklen_feld[i].u.umstimmung = liste1;
		liste1 = liste1->next;
		i++;
	}
	while (liste2) {
		zyklen_feld[i].umst_oder_logik_typ = typ_logik;
		zyklen_feld[i].u.logik = liste2;
		liste2 = liste2->next;
		i++;
	}
}

/** Sucht eine Umstimmung oder eine Logik in \c zyklen_feld.
 * Wird der Name nicht gefunden, wird ein fataler Fehler ausgelˆst.
 * \param[in] name Name der Umstimmung oder der Logik
 * \return Nummer der gefundenen Umstimmung oder Logik
 */
static int test_zyklen_nummer (char *name)
{ int i;

	for (i=0; i<anzahl_umstimmungen_und_logiken; i++)
		if ( ((zyklen_feld[i].umst_oder_logik_typ == typ_umstimmung) &&
		      (! strcmp (name, zyklen_feld[i].u.umstimmung->name)))
		     ||
		     (
			     (zyklen_feld[i].umst_oder_logik_typ == typ_logik) &&
			     (! strcmp (name, zyklen_feld[i].u.logik->name)))
			) return i;
      
	fatal_error(29,name); /* Umst.n.dekl. */
  
	return 0; /* to prevent warnings */
}
  
/** Sucht nach Kreisen in der Adjazenzmatrix \c u_matrix 
 * \param startknoten Knoten, von dem ausgegangen werden soll
 */
static void u_test_zyklen (int startknoten)
{
	int i;
	for (i=0; i<anzahl_umstimmungen_und_logiken; i++) {
		if (u_adjazent (startknoten, i)) {
			if (u_visited [i]) {
				fatal_error(66,
					    zyklen_feld [startknoten].umst_oder_logik_typ == typ_umstimmung ?
					    zyklen_feld [startknoten].u.umstimmung->name :
					    zyklen_feld [startknoten].u.logik->name,
					    zyklen_feld [i].umst_oder_logik_typ == typ_umstimmung ?
					    zyklen_feld [i].u.umstimmung->name :
					    zyklen_feld [i].u.logik->name);
			}
			u_visited [i] = 1;
			u_test_zyklen (i);
			u_visited [i] = 0;
		}
	}
}



/** Testet das gesamte Mutabor-Programm auf Konsistenz.
 * \li Tonsysteme: 
 *     ‹berpr¸fen, ob Periode und Tˆne deklariert sind
 *     und ob die Taste im Bereich 36 - 96 liegt.
 * \li Umstimmungen:
 *    pr¸fen, ob alle Tˆne und Intervalle
 *      global deklariert sind, ob Umstimmungsbund und \c umstimmungs_case
 *     keine Rekursion enth‰lt, ob \c case_labels eindeutig sind,
 *     und ob die benutzten Parameter
 *     zu den deklarierten Parametern passen.
 * \li Logiken: 
 *     öberprÅfen, ob Einstimmung deklariert ist
 *     und ob die Anweisungen korrekt deklariert sind.
 *
 * Gegebenenfalls werden Warnungen und fatale Fehler ausgelˆst.
 ****/

void check_konsistenz (void)
{
#ifdef DEBUG
	if (mutabor_debug_level) 
		fprintf (stderr,"Initializing consistency check\n");
#endif
  

	allgemeine_initialisierungen();

#ifdef DEBUG
	if (mutabor_debug_level) 
		fprintf (stderr,"Checking Tone systems\n");
#endif

	check_tonsystem_konsistenz();

#ifdef DEBUG
	if (mutabor_debug_level) 
		fprintf (stderr,"Checking retunings\n");
#endif
	check_umstimmungs_konsistenz();
    
#ifdef DEBUG
	if (mutabor_debug_level) 
		fprintf (stderr,"Checking for cycles\n");
#endif
	/**** testzyklen ****/
    
	{ 
		int i,j,k;
      
		anzahl_umstimmungen_und_logiken =
			umstimmungs_list_laenge (list_of_umstimmungen)
			+ logik_list_laenge (list_of_logiken) ;
		zyklen_feld = (struct umst_oder_logik*) xalloca (sizeof(struct umst_oder_logik) * anzahl_umstimmungen_und_logiken);
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
			}
			else if (zyklen_feld[i].umst_oder_logik_typ == typ_umstimmung &&
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
			}
			else if (zyklen_feld[i].umst_oder_logik_typ == typ_logik &&
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

	check_logik_konsistenz();
}
  
  
