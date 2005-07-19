/** \file
 ********************************************************************
 * Alles zu Umstimmungen.
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/libmutabor/umstimmung.c,v 1.2 2005/07/19 15:15:27 keinstein Exp $
 * \author Tobias Schlemmer <keinstein_junior@gmx.net>
 * \date $Date: 2005/07/19 15:15:27 $
 * \version $Revision: 1.2 $
 *
 * $Log: umstimmung.c,v $
 * Revision 1.2  2005/07/19 15:15:27  keinstein
 * Using own Templates
 *
 * Revision 1.1  2005/07/08 14:44:20  keinstein
 * Neue Datei.
 * Aus parser.c herausgelöst.
 *
 ********************************************************************/
#ifdef HAVE_CONFIG_H
#  include "config.h"
/* für HAVE_STDDEF_H, size_t */
#endif
#ifdef HAVE_STDDEF_H
#  include <stddef.h>
#endif
#include <string.h>
#include <stdio.h>
#include "mutabor/umstimmung.h"
#include "mutabor/bad_decl.h"
#include "mutabor/parameter.h"
#include "mutabor/tonsystem.h"
#include "mutabor/logik.h"
#include "mutabor/heap.h"

/** Wurzel der Umstimmungen */
struct umstimmung     *  list_of_umstimmungen;
/** Liste von Umstimmungen */
struct umstimmung * tmp_umstimmung;


/** Zählen der Elemente einer einfach verketteten Umstimmungsliste.
 * \param list Liste der Umstimmungen
 * \return Anzahl der Elemente von \a list
 */
int umstimmungs_list_laenge (struct umstimmung *list)
{ if (list) return 1 + umstimmungs_list_laenge (list -> next);
  return 0;
}

/** Sucht eine Umstimmung in einer Umstimmungsliste.
 * \param name Name der gesuchten Umstimmung
 * \param liste Liste der Umstimmungen, in der die Umstimmung gesucht wird
 * \retval NULL, falls Umstimmung nicht in \a liste
 * \retval Umstimmung, sonst.
 */
struct umstimmung * get_umstimmung (char * name,
                                      struct umstimmung * liste)
{
    if (liste == NULL) return NULL;
    if ( ! strcmp (name, liste->name)) return liste;
    return get_umstimmung (name, liste->next);
}

/********* Einleseroutinen fuer Umstimmungen            *********/
/*         Es wird erst eine leere Umstimmung eingerichtet,    **/
/*            init_umstimmung (name);                          **/
/*         in die dann die Varianten eingetragen werden.       **/
/*         Zuletzt wird diese Umstimmung in die Liste          **/
/*         eingehängt.					                       **/
/*            get_new_umstimmung ();                           **/

/** Erzeugt eine leere Umstimmung auf \c tmp_umstimmung. Vorher wird jedoch
 *  die Umstimmungsliste \c list_of_umstimmungen durchsucht, ob \a name schon
 *  vorhanden ist. Gegebenenfalls wird ein fataler Fehler ausgeworfen.
 * \param name Name der neu einzurichtenden Umstimmung.
 * \warning \c tmp_umstimmnug wird nicht gelöscht. Das muss gegebenenfalls 
 *          extra erledigt werden.
 */
void init_umstimmung (char * name)
{
    struct umstimmung * lauf;
    for (lauf= list_of_umstimmungen; lauf; lauf= lauf -> next) {
        if ( ! strcmp (name, lauf -> name)) {
            fatal_error(13,name); /* Umstimmungsname doppelt */
        }
    }
    
    tmp_umstimmung = (struct umstimmung*) xmalloc ((size_t) sizeof (struct umstimmung));
    tmp_umstimmung -> name            = name;
    tmp_umstimmung -> parameter_liste = NULL;
    tmp_umstimmung -> next            = NULL;
}

/** Hängt \c tmp_umstimmung an list_of_umstimmungen an.
 * \note Es wird immer die gesamte Liste durchsucht. Effektivität?
 */
void get_new_umstimmung (void)
{
    struct umstimmung * * lauf;
    for (lauf= & list_of_umstimmungen; * lauf; lauf= & (*lauf)->next) {
    }
    
    (* lauf) = tmp_umstimmung;
}

/** Hängt die letzte eingelesene Parameterliste an geeigneter Stelle in 
 *  \c tmp_umstimmung ein.
 */
void eintrage_parameterliste_in_umstimmung (void)
{
    tmp_umstimmung -> parameter_liste = get_last_parameter_liste ();
}



/************ Die folgenden Funktionen tragen je eine         */
/*            Version von Umstimmung ein.                     */
/*            Genau eine dieser Funktionen wird zwischen      */
/*            init_umstimmung ()                              */
/*            und                                             */
/*            get_new_umstimmung (name)                       */
/*            aufgerufen.                                     */

/** Baut \c tmp_umstimmung zu einer absoluten Tasten-Umstimmung aus. Wird 
 * nicht-numerisch umgestimmt, und wirde der Parameter nicht definiert, wird
 * ein fataler Fehler ausgelöst.
 * \param argument  Typ des Argumentes der Umstimmung
 * \param zahl_wert Zahlenwert eines numerischen Argumentes.
 *                  Wird ansonsten ignoriert.
 * \param parameter Name des Parameters für die nicht numerische Umstimmung.
 * \todo Typkonvertierung von \c double nach  \c int prüfen
 */
void get_umstimmung_taste_abs (
     enum argument_typ argument, 
     double zahl_wert, char * parameter)
{
    tmp_umstimmung -> umstimmung_typ = umstimmung_taste_abs;
    tmp_umstimmung -> u.umstimmung_taste_abs.
        argument.argument_typ 
          = argument;
    if (argument == zahl) {
        tmp_umstimmung -> u.umstimmung_taste_abs.
            argument.u.zahl.zahl = (int) zahl_wert;
    }
    else {
        int i = parameter_nummer (0, parameter,
                                  tmp_umstimmung->parameter_liste);
        if (i == EOF) {
            fatal_error(31,parameter,tmp_umstimmung->name); /* Parameter n.dekl. */
        }
        tmp_umstimmung -> u.umstimmung_taste_abs.
            argument.u.parameter.
                parameter_nummer = i;
        tmp_umstimmung -> u.umstimmung_taste_abs.
            argument.u.parameter.
                parameter_name = parameter;
    }
}

/** Baut \c tmp_umstimmung zu einer relativen Tasten-Umstimmung aus. Wird 
 * nicht-numerisch umgestimmt, und wirde der Parameter nicht definiert, wird
 * ein fataler Fehler ausgelöst.
 * \param argument   Typ des Argumentes der Umstimmung
 * \param zahl_wert  Zahlenwert eines numerischen Argumentes.
 *                   Wird ansonsten ignoriert.
 * \param parameter  Name des Parameters für die nicht numerische Umstimmung.
 * \param vorzeichen Rechenzeichen für die Umstimmung.
 * \note Rechenzeichen = +/-, also Richtung?
 * \todo Typkonvertierung von \c double nach \c int prüfen.
 */
void get_umstimmung_taste_rel (
     enum argument_typ argument,
     double zahl_wert, char * parameter, char vorzeichen)
{
    tmp_umstimmung -> umstimmung_typ = umstimmung_taste_rel;
    tmp_umstimmung -> u.umstimmung_taste_rel.
        argument.argument_typ 
          = argument;
    if (argument == zahl) {
        tmp_umstimmung -> u.umstimmung_taste_rel.
            argument.u.zahl.zahl = (int) zahl_wert;
    }
    else {
        int i = parameter_nummer (0, parameter,
                                  tmp_umstimmung->parameter_liste);
        if (i == EOF) {
            fatal_error(31,parameter,tmp_umstimmung -> name); /* Parameter n.dekl. */
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

/** Baut \c tmp_umstimmung zu einer absoluten Änderung der Referenz-Breite aus. Wird 
 * nicht-numerisch umgestimmt, und wirde der Parameter nicht definiert, wird
 * ein fataler Fehler ausgelöst.
 * \param argument  Typ des Argumentes der Umstimmung
 * \param zahl_wert Zahlenwert eines numerischen Argumentes.
 *                  Wird ansonsten ignoriert.
 * \param parameter Name des Parameters für die nicht numerische Umstimmung.
 * \todo Typkonvertierung von \c double nauch \c int prüfen.
 */
void get_umstimmung_breite_abs (
     enum argument_typ argument,
     double zahl_wert, char * parameter)
{
    tmp_umstimmung -> umstimmung_typ = umstimmung_breite_abs;
    tmp_umstimmung -> u.umstimmung_breite_abs.
        argument.argument_typ 
          = argument;
    if (argument == zahl) {
        tmp_umstimmung -> u.umstimmung_breite_abs.
            argument.u.zahl.zahl = (int) zahl_wert;
    }
    else {
        int i = parameter_nummer (0, parameter,
                                  tmp_umstimmung->parameter_liste);
        if (i == EOF) {
            fatal_error(31,parameter,tmp_umstimmung->name); /* Parameter n.dekl. */
        }
        tmp_umstimmung -> u.umstimmung_breite_abs.
            argument.u.parameter.
                parameter_nummer = i;
        tmp_umstimmung -> u.umstimmung_breite_abs.
            argument.u.parameter.
                parameter_name = parameter;
    }
}

/** Baut \c tmp_umstimmung zu einer relativen Änderung der Referenz-Breite aus. Wird 
 * nicht-numerisch umgestimmt, und wirde der Parameter nicht definiert, wird
 * ein fataler Fehler ausgelöst.
 * \param argument  Typ des Argumentes der Umstimmung
 * \param zahl_wert Zahlenwert eines numerischen Argumentes.
 *                  Wird ansonsten ignoriert.
 * \param parameter Name des Parameters für die nicht numerische Umstimmung.
 * \param vorzeichen Rechenzeichen für die Umstimmung.
 * \note Rechenzeichen = +/-, also Richtung?
 * \todo Typkonvertierung von \c double nach  \c int prüfen.
 */
void get_umstimmung_breite_rel (
     enum argument_typ argument,
     double zahl_wert, char * parameter, char vorzeichen)
{
    tmp_umstimmung -> umstimmung_typ = umstimmung_breite_rel;
    tmp_umstimmung -> u.umstimmung_breite_rel.
        argument.argument_typ 
          = argument;
    if (argument == zahl) {
        tmp_umstimmung -> u.umstimmung_breite_rel.
            argument.u.zahl.zahl = (int) zahl_wert;
    }
    else {
        int i = parameter_nummer (0, parameter,
                                  tmp_umstimmung->parameter_liste);
        if (i == EOF) {
            fatal_error(31,parameter,tmp_umstimmung->name); /* Parameter n.dekl. */
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

/*********** Bei "tonhöhe verändert" muss wieder die gesamte
             expression eines Tons pro Listeneintrag 
             aufgesammelt werden.
********/

/** Temporäre Tonliste. */
static struct ton * tmp_tonliste;

/** Setzt \c tmp_tonliste auf NULL.
 * \warning Die Liste wird nicht gelöscht. 
 *          Das muss gegebenenfalls vor der Initialiserung manuell erledigt werden.
 */
void init_umstimm_expression_list (void)
{
    tmp_tonliste = NULL;
}

/** Fügt einen einfachen komplexen Ton ans Ende von \a tmp_tonliste an. 
 * Dabei wird sowohl der Name des Tones als auch der des Bezugstones
 * des komplexen Intervalles auf \a name gesetzt. Die komplexe 
 * Intervallliste wird leer initialisiert.
 * \param bezugston Bezeichnung des Tones, der angefügt werden soll 
 * \note Es wird immer die gesamte Liste durchsucht. Effektivität?
 */
void get_new_umstimm_expression (char * bezugston)
{
    struct ton * * lauf;
    for (lauf= & tmp_tonliste; * lauf; lauf= & (*lauf)->next)
        /* Nur Ende der Liste finden */ ;
    
    (* lauf) = (struct ton*) xmalloc ((size_t) sizeof (struct ton));
    (* lauf) -> name                    = bezugston;
    (* lauf) -> ton_typ                 = ton_komplex;
    (* lauf) -> u.ton_komplex.bezugston = bezugston;
    (* lauf) -> u.ton_komplex.komplex_liste = NULL;
    (* lauf) -> next                    = NULL;
    
}


/** Fügt einen komplexen Ton ans Ende von \a tmp_tonliste an. 
 * Dabei wird sowohl der Name des Tones als auch der des Bezugstones
 * des komplexen Intervalles auf \a name gesetzt. Als komplexe 
 * Intervallliste wird die letzte eingelesene eingehängt. 
 * \param bezugston Bezeichnung des Tones, der angefügt werden soll 
 * \note Es wird immer die gesamte Liste durchsucht. Effektivität?
 */
void get_new_umstimm_expression_positive (char * bezugston)
{
    struct ton * * lauf;
    for (lauf= & tmp_tonliste; * lauf; lauf= & (*lauf)->next)
        /* Nur Ende der Liste finden */ ;
    
    (* lauf) = (struct ton*) xmalloc ((size_t) sizeof (struct ton));
    (* lauf) -> name                    = bezugston;
    (* lauf) -> ton_typ                 = ton_komplex;
    (* lauf) -> u.ton_komplex.bezugston = bezugston;
    (* lauf) -> u.ton_komplex.komplex_liste = get_last_komplex_intervall ();
    (* lauf) -> next                    = NULL;
    
}


/** Fügt einen komplexen Ton ans Ende von \a tmp_tonliste an. 
 * Dabei wird sowohl der Name des Tones als auch der des Bezugstones
 * des komplexen Intervalles auf \a name gesetzt. Als komplexe 
 * Intervallliste wird die letzte eingelesene eingehängt.
 * Diese wird jedoch vorher invertiert.
 * \param bezugston Bezeichnung des Tones, der angefügt werden soll 
 * \note Es wird immer die gesamte Liste durchsucht. Effektivität?
 */
void get_new_umstimm_expression_negative (char * bezugston)
{
    struct ton * * lauf;
    for (lauf= & tmp_tonliste; * lauf; lauf= & (*lauf)->next)
        /* Nur Ende der Liste finden */ ;
    
    (* lauf) = (struct ton*) xmalloc ((size_t) sizeof (struct ton));
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


/** Baut \c tmp_umstimmung zu einer Änderung der Tonhöhe aus.
 * Dabei wird \c tmp_tonliste als Tonliste der Veränderung eingehängt.
 */
void get_umstimmung_tonhoehe_veraendert (void)
{
    tmp_umstimmung -> umstimmung_typ = umstimmung_toene_veraendert;
    tmp_umstimmung -> u.umstimmung_toene_veraendert.tonliste
                                = tmp_tonliste;
}

/** Baut \c tmp_umstimmung zu einer absoluten Änderung der
 * Wiederholungsvorschrift aus.
 * Dabei wird die letzte eingelesene komplexe Intervallliste verwendet.
 */
void get_umstimmung_wiederholung_abs (void)
{
    tmp_umstimmung -> umstimmung_typ = umstimmung_wiederholung_abs;
    tmp_umstimmung -> u.umstimmung_wiederholung_abs.komplex_liste
                                = get_last_komplex_intervall ();
}

/** Baut \c tmp_umstimmung zu einer absoluten Änderung der 
 * Wiederholungsvorschrift aus.
 * Dabei wird die letzte eingelesene komplexe Intervallliste verwendet.
 * Diese wird jedoch vorher invertiert. Ist sie leer, wird ein fataler Fehler 
 * ausgelöst.
 */
void get_umstimmung_wiederholung_abs_negative (void)
{
    tmp_umstimmung -> umstimmung_typ = umstimmung_wiederholung_abs;
    {
        struct komplex_intervall * help = get_last_komplex_intervall ();
        if (help == NULL) 
            fatal_error (0, __FILE__, __LINE__);
        help -> faktor *= -1.0;

        tmp_umstimmung -> 
             u.umstimmung_wiederholung_abs.komplex_liste = help;
    }
}


/** Baut \c tmp_umstimmung zu einer relativen änderung der 
 * Wiederholungsvorschrift aus.
 * Dabei wird die letzte eingelesene komplexe Intervallliste verwendet.
 */
void get_umstimmung_wiederholung_rel_positive (void)
{
    tmp_umstimmung -> umstimmung_typ = umstimmung_wiederholung_rel;
    tmp_umstimmung -> u.umstimmung_wiederholung_rel.
                         komplex_liste = get_last_komplex_intervall ();
}

/** Baut \c tmp_umstimmung zu einer relativen Änderung der 
 * Wiederholungsvorschrift aus.
 * Dabei wird die letzte eingelesene komplexe Intervallliste verwendet.
 * Diese wird jedoch vorher invertiert. Ist sie leer, wird ein fataler Fehler 
 * ausgelöst.
 */
void get_umstimmung_wiederholung_rel_negative (void)
{
    tmp_umstimmung -> umstimmung_typ = umstimmung_wiederholung_rel;
    tmp_umstimmung -> u.umstimmung_wiederholung_rel.
                         komplex_liste = get_last_komplex_intervall ();

    tmp_umstimmung -> u.umstimmung_wiederholung_rel.
                         komplex_liste -> faktor      *= - 1.0 ;
}

/*********** Bei "umstimmungsbund" muss wieder eine Liste von
             Aufrufen (mit evtl. Parametern)
             aufgesammelt werden.
********/

/** Baut \c tmp_umstimmung zu einem Umstimmungsbund aus. Dazu wird
 * die letzte eingelesene Aktionsliste verwendet.
 * Falls ein Parameter darin nicht definiert ist, wird ein fataler Fehler 
 * ausgelöst.
 */
void get_umstimmung_umstimmungs_bund (void)
{
    tmp_umstimmung -> umstimmung_typ = umstimmung_umstimmungsbund;
    tmp_umstimmung -> u.umstimmung_umstimmungsbund
                       .aktions_liste = get_last_aktions_liste ();


/* check, ob die Parameter zulässig sind */

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
	              fatal_error(31,argument_lauf->argument.u.parameter.parameter_name,
	                             tmp_umstimmung -> name); /* Parameter n.dekl. */
	            }
	            else {
                  argument_lauf->argument.u.parameter.parameter_nummer = i;
	            } /* if */
	          } /* if */
	        }  /* for argument_lauf */
	     }  /* if (aktions_lauf... */
       }  /* for aktions_lauf */
    }



}
/*
void init_aufruf_liste (void)
{
    tmp_aufruf_liste = NULL;
}
*/
#if 0
void get_umstimmungs_bund_element (char * name)
{
    struct umstimmung * * lauf;
    for (lauf= & tmp_umstimmungsbund_liste; 
         * lauf; 
         lauf= & (*lauf)->next)
        /* Nur Ende der Liste finden */ ;
    
    (* lauf) = xmalloc (sizeof (struct umstimmung));
    (* lauf) -> name                = name;
    (* lauf) -> parameterliste      = get_last_parameter_liste ();
    (* lauf) -> next                = NULL;

/* check, ob die Parameter zulässig sind */

    {
        struct namensliste * params;
        for (params = (* lauf) -> parameterliste;
             params;
             params = params -> next ) {
            if (parameter_nummer (0,params->name, 
                 tmp_umstimmung -> parameterliste)  == EOF ) {
              fatal_error(31,params->name,(*lauf)->name); /* Parameter n.dekl. */
            }
        }
    }

}
#endif


  /**** Umstimmungen prüfen, ob alle Töne und Intervalle
	global deklariert sind, ob Umstimmungsbund und Umstimmungs_case
	keine Rekursion enthält, ob case_labels eindeutig sind,
	und ob die benutzten Parameter
	zu den deklarierten Parametern passen.
  ****/

void check_umstimmungs_konsistenz(void)  
  {
    struct umstimmung * lauf;
    for (lauf = list_of_umstimmungen; lauf; lauf = lauf -> next) {
      switch (lauf -> umstimmung_typ) {
	
      default : 
	fatal_error (0, __FILE__, __LINE__);
        break;
        
      case umstimmung_taste_abs :
      case umstimmung_taste_rel :
      case umstimmung_breite_abs :
      case umstimmung_breite_rel :
        break;
	
      case umstimmung_wiederholung_rel :
	check_komplex_intervall (lauf->u.umstimmung_wiederholung_rel.komplex_liste,
				 lauf->name);
        break;
        
      case umstimmung_wiederholung_abs :
	check_komplex_intervall (lauf->u.umstimmung_wiederholung_abs.komplex_liste,
				 lauf->name);
        break;
        
      case umstimmung_toene_veraendert : {
	struct ton * lauf_ton;
	for (lauf_ton = lauf->u.umstimmung_toene_veraendert.tonliste;
	     lauf_ton; 
	     lauf_ton = lauf_ton -> next) {
	  
	  if (lauf_ton -> name != NULL) {
	    /*  break geht hier wegen Bug in TURBO-C nicht! break for the next tone */
	    
	    if (lauf_ton -> ton_typ == ton_absolut) {
	      fatal_error(48,lauf->name, lauf_ton->name);
	      /* nicht komplexer Ton */
	    }
	    
	    if (strcmp (lauf_ton->name,
			lauf_ton->u.ton_komplex.bezugston)) {
	      fatal_error(0,"umstimmung");
	    }
	    
	    if ((lauf_ton->name[0] != '@') &&
		(get_ton (lauf_ton->name, list_of_toene) == NULL)) {
	      fatal_error(34,lauf_ton->name,lauf->name); 
	      /* Undekl. Ton in Umst. */
	    }

	    check_komplex_intervall (lauf_ton->u.ton_komplex.komplex_liste,
				     lauf->name);
	    
	  }
	}
      }
        break;
	
      case umstimmung_umstimmungsbund : {
	
	/* Hier werden nur die Längen der Parameterlisten
	   verglichen. Die Zyklenfreiheit kommt später
	*/
	
	struct aktions_liste * help_aktionen;
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
		  fatal_error(36,help_aktionen -> u.aktion_aufruf.name
			      ,lauf->name);
		  /* Umst. in Bund */
		}
		else {
		  if (help_aktionen -> u.aktion_aufruf.argument_liste != NULL) {
		    fatal_error (63, lauf -> name , help_aktionen -> u.aktion_aufruf.name);
		  }
		}
	      }
	      else {
		if (help_aktionen -> u.aktion_aufruf.argument_liste != NULL) {
		  fatal_error (63, lauf -> name , help_aktionen -> u.aktion_aufruf.name);
		}
	      }
	    }
	    else {
	      if (argument_list_laenge (help_aktionen -> u.aktion_aufruf.argument_liste)
		  != parameter_list_laenge (umst -> parameter_liste)) {
		fatal_error(60,lauf->name,help_aktionen -> u.aktion_aufruf.name);
	      }
	    }
	  }
	}
      }
        break;
      case umstimmung_umstimmungs_case : {
	
	/* Hier werden nur Eindeutigkeit der case_label
	   und die Längen der Parameterlisten
	   verglichen. Die Zyklenfreiheit kommt später
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
			 lauf -> name);
	  }
	}
	
	
	for (anzahl_defaults = 0,
	       case_lauf = lauf->u.umstimmung_umstimmungs_case.umstimmungs_case_liste;
	     case_lauf;
	     case_lauf = case_lauf -> next ) {
	  
	  if (case_lauf -> is_default) {
	    anzahl_defaults ++;
	    if (anzahl_defaults > 1) {
	      fatal_error (21, lauf -> name);
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
		    fatal_error(36,help_aktionen -> u.aktion_aufruf.name
				,lauf->name);
		    /* Umst. in Bund */
		  }
		  else {
		    if (help_aktionen -> u.aktion_aufruf.argument_liste != NULL) {
		      fatal_error (64, lauf -> name , help_aktionen -> u.aktion_aufruf.name);
		    }
		  }
		}
		else {
		  if (help_aktionen -> u.aktion_aufruf.argument_liste != NULL) {
		    fatal_error (64, lauf -> name , help_aktionen -> u.aktion_aufruf.name);
		  }
		}
	      }
	      else {
		if (argument_list_laenge (help_aktionen -> u.aktion_aufruf.argument_liste)
		    != parameter_list_laenge (umst -> parameter_liste)) {
		  fatal_error(60,lauf->name,help_aktionen -> u.aktion_aufruf.name);
		}
	      }
	    }
	  }
	}
      }
	break;
      }  /* of switch */
    }  /* of for */            

}
