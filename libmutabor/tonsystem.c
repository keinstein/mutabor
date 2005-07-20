/** \file
 ********************************************************************
 * Alles zu Tonsystemen.
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/libmutabor/tonsystem.c,v 1.3 2005/07/20 12:33:41 keinstein Exp $
 * \author Tobias Schlemmer <keinstein_junior@gmx.net>
 * \date $Date: 2005/07/20 12:33:41 $
 * \version $Revision: 1.3 $
 *
 * $Log: tonsystem.c,v $
 * Revision 1.3  2005/07/20 12:33:41  keinstein
 * Kopf
 * config.h
 * header aufgeräumt für Doxygen
 *
 * Revision 1.2  2005/07/19 15:15:27  keinstein
 * Using own Templates
 *
 ********************************************************************/
#ifdef HAVE_CONFIG_H
#  include "config.h"
/* für HAVE_STDDEF_H, size_t */
#endif
#ifdef HAVE_STDDEF_H
#  include <stddef.h>
#endif
#include<string.h>
#include "mutabor/tonsystem.h"
#include "mutabor/interval.h"
#include "mutabor/heap.h"

/** Wurzel der Tonsysteme */
struct tonsystem      *  list_of_tonsysteme;

/** Zählen der Elemente einer einfach verketteten Tonsystemliste.
 * \param list Liste der Tönsysteme
 * \return Anzahl der Elemente von \a list
 */
int tonsystem_list_laenge (struct tonsystem *list)
{ if (list) return 1 + tonsystem_list_laenge (list -> next);
  return 0;
}

/** Sucht ein Tonsystem in einer Tonsystemliste.
 * \param name Name des gesuchten Tonsystems
 * \param liste Liste der Tonsysteme, in der das System gesucht wird
 * \retval NULL, falls Tonsystem nicht in \a liste
 * \retval Tonsystem, sonst.
 */
struct tonsystem * parser_get_tonsystem (char * name,
                                      struct tonsystem * liste)
{
    if (liste == NULL) return NULL;
    if ( ! strcmp (name, liste->name)) return liste;
    return parser_get_tonsystem (name, liste->next);
}

/********* Einleseroutinen fuer die Tonsysteme          *********/
/*         Es wird einfach eine Liste of Tonsysteme aufgebaut  **/

/** Dient zum Aufsammeln einzelner Töne 
   während eines Tonsystems. Die aufgebaute Liste wird dann
   jeweils an das Tonsystem angehängt. */
static struct ton * ton_liste; 

/** Setzt \c ton_liste auf NULL.
 * \warning Die Liste wird nicht gelöscht. 
 *          Das muss gegebenenfalls vor der Initialiserung manuell erledigt werden.
 */
void init_ton_liste (void)
{
    ton_liste = NULL;
}

/** Fügt einen Ton ans Ende von \a ton_liste an. 
 * \param name Name des Tones
 * \note Es wird immer die gesamte Liste durchsucht. Effektivität?
 */
void get_new_ton_in_tonsystem (char *name)
{ 
    struct ton * * lauf;
    for (lauf= & ton_liste; * lauf; lauf= & (*lauf)->next) {
        /* Hier sind doppelte Töne zulässig !! */
    }
    
    (* lauf) = (struct ton*) xmalloc ((size_t) sizeof (struct ton));
    (* lauf) -> name                    = name;
    (* lauf) -> next                    = NULL;
    
}

/** Fügt ein Tonsystem ans Ende von \a list_of_tonsysteme an. 
 * Der Aufruf erhält das letzte eingelesene Tonsystem.
 * \param name  Bezeichnung des Tonsystems, das angefügt werden soll 
 * \param taste Bezugstaste für das Tonsystem
 * \note Es wird immer die gesamte Liste durchsucht. Effektivität?
 */
void get_new_tonsystem (char * name, int taste)
{
    struct tonsystem * * lauf;
    for (lauf= & list_of_tonsysteme; * lauf; lauf= & (*lauf)->next) {
        if ( ! strcmp (name, (*lauf)->name)) {
            fatal_error(12,name); /* Tonsystemname doppelt */
        }
    }
    
    (* lauf) = (struct tonsystem*) xmalloc ((size_t) sizeof (struct tonsystem));
    (* lauf) -> name          = name;
    (* lauf) -> taste         = taste;
    (* lauf) -> periode       = get_last_komplex_intervall ();
    (* lauf) -> toene         = ton_liste;
    (* lauf) -> next          = NULL;
    
}

/** Fügt ein Tonsystem ans Ende von \a list_of_tonsysteme an. 
 * Der Aufruf erhält das letzte eingelesene Tonsystem in invertierter Form.
 * \param name  Bezeichnung des Tonsystems, das angefügt werden soll 
 * \param taste Bezugstaste für das Tonsystem
 * \note Es wird immer die gesamte Liste durchsucht. Effektivität?
 */
void get_new_tonsystem_negative (char * name, int taste)
{
    struct tonsystem * * lauf;
    for (lauf= & list_of_tonsysteme; * lauf; lauf= & (*lauf)->next) {
        if ( ! strcmp (name, (*lauf)->name)) {
            fatal_error(12,name); /* Tonsystemname doppelt */
        }
    }
    
    (* lauf) = (struct tonsystem*) xmalloc ((size_t) sizeof (struct tonsystem));
    (* lauf) -> name          = name;
    (* lauf) -> taste         = taste;
    {
        struct komplex_intervall * help = get_last_komplex_intervall ();
        if (help == NULL) 
            fatal_error (0, __FILE__, __LINE__);
        help -> faktor *= -1.0 ;
        (* lauf) -> periode = help;
    }
    (* lauf) -> toene         = ton_liste;
    (* lauf) -> next          = NULL;
    
}

/** Tonsysteme testen. 
     Überprüfen, ob Periode und Töne deklariert sind
     und ob die Taste im Bereich 24 -- 108 liegt.
  */
  
void check_tonsystem_konsistenz(void)
  { 
    struct tonsystem * lauf;
    struct ton * ton_lauf;
    for (lauf = list_of_tonsysteme; lauf; lauf = lauf->next) {
      check_komplex_intervall (lauf->periode, lauf->name);
      if (lauf->taste < 24  ||  lauf->taste > 108) {
	fatal_error(47,lauf->taste,lauf->name); /* Ungült. Taste */
      }
      for (ton_lauf = lauf->toene;
	   ton_lauf;
	   ton_lauf = ton_lauf->next) {
	if ((ton_lauf->name != NULL) &&
	    (get_ton (ton_lauf->name, list_of_toene) == NULL)) {
	  fatal_error(33,ton_lauf->name,lauf->name);
	}
      }
    }
  }


