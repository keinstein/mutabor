/** \file
 ********************************************************************
 * Alles zu Logiken.
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/libmutabor/logik.c,v 1.3 2005/07/20 12:01:01 keinstein Exp $
 * \author Tobias Schlemmer <keinstein_junior@gmx.net>
 * \date $Date: 2005/07/20 12:01:01 $
 * \version $Revision: 1.3 $
 *
 * $Log: logik.c,v $
 * Revision 1.3  2005/07/20 12:01:01  keinstein
 * Kopf korrigiert
 * Includes bereinigt.
 * config.h
 *
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
#endif
#ifdef HAVE_STDDEF_H
#  include <stddef.h>
#endif
#include <string.h>
#include "mutabor/logik.h"
#include "mutabor/anweisung.h"
#include "mutabor/heap.h"
#include "mutabor/tonsystem.h"
#include "mutabor/umstimmung.h"
#include "mutabor/parameter.h"

/** Wurzel der Logiken */
struct logik          *  list_of_logiken;

/** Zählen der Elemente einer einfach verketteten Logikliste.
 * \param list Liste der Logiken
 * \return Anzahl der Elemente von \a list
 */
int logik_list_laenge (struct logik *list)
{ if (list) return 1 + logik_list_laenge (list -> next);
  return 0;
}

/** Ermitteln der Position einer Logik. 
 * Falls \a liste leer wird eine Fehlermeldung ausgegeben.
 * \param[in] name Name der zu suchenden Logik
 * \param[in] liste Liste, in der die Logik gesucht wird
 * \return Nummer der Logik in der Liste
 */
int get_logik_nummer (char * name, struct logik * liste)
{  if (liste == NULL) {
       fatal_error (0, __FILE__, __LINE__);
       return 0;
   }
   else if ( ! strcmp (name, liste->name))
       return 0;
   else
       return 1 + get_logik_nummer (name, liste->next);
}

/** Sucht eine Logik in einer Logikliste.
 * \param name Name der gesuchten Logik
 * \param liste Liste der Logiken, in der gesucht wird
 * \retval NULL, falls Logik nicht in \a liste
 * \retval Logik, sonst.
 */
struct logik * get_logik (char * name, struct logik * liste)
{
    if (liste == NULL) return NULL;
    if ( ! strcmp (name, liste->name)) return liste;
    return get_logik (name, liste->next);
}


/** Setzt Paramater-Nummern von Abstand und Zentrum.
 * Durchsucht die Logikliste \a list_of_logiken und setzt bei jedem Argument 
 * jeder Aktion jeder anweisung die Parameter-Nummer auf
 * \li 0, wenn der Parameter-Name ,,ABSTAND`` heißt, und
 * \li 1, wenn der Parameter-Name ,,ZENTRUM`` heißt.
 */
void setze_nummer_von_abstand_und_zentrum (void)
{
    struct logik * lauf;
    for (lauf=list_of_logiken; lauf; lauf=lauf->next) {
        struct anweisung * lauf_anw;
        for (lauf_anw=lauf->anweisungsliste; lauf_anw; lauf_anw=lauf_anw->next) {
            if (lauf_anw->aktion->aktions_typ == aktion_aufruf) {
                struct argument_liste * lauf_arg;
                for (lauf_arg=lauf_anw->aktion->u.aktion_aufruf.argument_liste;
                     lauf_arg;
                     lauf_arg=lauf_arg->next) {
                    switch (lauf_arg->argument.argument_typ) {
                    case zahl:
                               /* OK */
						  break;
                    case parameter:
                        if ( ! strcmp (lauf_arg->argument.u.parameter.parameter_name,
                                       "ABSTAND")) {
                            lauf_arg->argument.u.parameter.parameter_nummer 
                                             = 0;
                        }
                        else
                        if ( ! strcmp (lauf_arg->argument.u.parameter.parameter_name,
                                       "DISTANCE")) {
                            lauf_arg->argument.u.parameter.parameter_nummer 
                                             = 0;
								}
                        else
                        if ( ! strcmp (lauf_arg->argument.u.parameter.parameter_name,
                                       "ZENTRUM")) {
                            lauf_arg->argument.u.parameter.parameter_nummer 
                                             = 1;
                        }
                        else
                        if ( ! strcmp (lauf_arg->argument.u.parameter.parameter_name,
                                       "CENTER")) {
                            lauf_arg->argument.u.parameter.parameter_nummer 
                                             = 1;
								}
                        else
                            fatal_error (39,
                                         lauf_arg->argument.u.parameter.parameter_name,
                                         lauf_anw->aktion->u.aktion_aufruf.name,
                                         lauf->name);
                    break;
                    default:
                        fatal_error (0, __FILE__, __LINE__);
                    break;
                    }
                }
	    }
        }
    }
}
/** Fügt eine neue Logik ans Ende von \a list_of_logiken an. 
 * Dabei wird der letzte eingelesene Auslöser verwendet.
 * Die Anweisungsliste wird zunächst als Leer deklariert. 
 * \param  name         Name der Logik
 * \param  einstimmung  Name der Einstimmnug der Logik
 * \note Es wird immer die gesamte Liste durchsucht. Effektivität?
 */
void get_new_logik (char * name, char * einstimmung)
{
    struct logik * * lauf;
    for (lauf= & list_of_logiken; * lauf; lauf= & (*lauf)->next) {
        if ( ! strcmp (name, (*lauf)->name)) {
            fatal_error(15,name); /* Logikname doppelt */
        }
    }
    
    (* lauf) = (struct logik*) xmalloc (sizeof (struct logik));
    (* lauf) -> name                = name;
    (* lauf) -> ausloeser           = get_last_ausloeser ();
    (* lauf) -> einstimmungs_name   = einstimmung;
    (* lauf) -> anweisungsliste     = NULL;
    (* lauf) -> next                = NULL;
    
}

/** Hängt die letzte eingelesene Anweisung in der letzten Logik von 
 * \c list_of_logiken ein. 
 * \note Es wird immer die gesamte Liste durchsucht. Effektivität?
 * \warning Die Anweisungsliste wird nicht gelöscht. Das muss gegebenenfalls 
 * vorher extra getan werden.
 */
void vervollstaendige_logik (void)
{
    struct logik * lauf;
    for (lauf = list_of_logiken; lauf -> next; lauf = lauf->next) {
    }
    
    lauf -> anweisungsliste     = get_last_anweisungs_liste ();
}

  /* Logiken: 
     überprüfen, ob Einstimmung deklariert ist
     und ob die Anweisungen korrekt deklariert sind.
  */
  

void check_logik_konsistenz(void)
  {
    struct logik * lauf;
    struct anweisung * anweisungs_lauf;
    int anzahl_default_ausloeser;
    for (lauf = list_of_logiken; lauf; lauf = lauf->next) {
      struct umstimmung * help_umstimmung;
      
      check_ausloeser (lauf->ausloeser, lauf->name);
      
      /* Eine Logik darf nicht mit dem DEFAULT-Auslöser aufgerufen werden */
      
      if (lauf->ausloeser) {
	if (lauf->ausloeser->ausloeser_typ == ausloeser_default) {
	  fatal_error (51, lauf->name);
	}
      }
      
      if (lauf->einstimmungs_name!=NULL) {
	if (parser_get_tonsystem (lauf->einstimmungs_name, list_of_tonsysteme) == NULL) {
	  if ((help_umstimmung=get_umstimmung (lauf->einstimmungs_name, list_of_umstimmungen)) == NULL) {
	    fatal_error(37,lauf->einstimmungs_name,lauf->name);
	    /* Einst. in Logik */
	  }
	  else {
	    if (parameter_list_laenge (help_umstimmung -> parameter_liste) != 0) {
	      fatal_error(62,lauf->name, lauf->einstimmungs_name);
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
	  fatal_error (0, __FILE__, __LINE__);
	else {
	  if (anweisungs_lauf->ausloeser->ausloeser_typ
	      == ausloeser_default) {
	    anzahl_default_ausloeser ++;
	    if (anzahl_default_ausloeser > 1) {
	      fatal_error (20, lauf -> name);
	    }
	    else {
	      if (anweisungs_lauf -> next !=(struct anweisung *) NULL)
		compiler_warning (4, lauf -> name);
	    }
	  }
	}

	check_aktionen (anweisungs_lauf -> aktion, lauf->name);
	
      }
    }
  }

