/** \file
 ********************************************************************
 * Alles zu Umstimmungen.
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/libmutabor/harmonie.c,v 1.3 2005/07/20 11:13:46 keinstein Exp $
 * \author Tobias Schlemmer <keinstein_junior@gmx.net>
 * \date $Date: 2005/07/20 11:13:46 $
 * \version $Revision: 1.3 $
 *
 * $Log: harmonie.c,v $
 * Revision 1.3  2005/07/20 11:13:46  keinstein
 * Dateikopf
 * config.h
 * Includes für Doxygen vereinfacht.
 * rudimentäre Debug-ausgabe
 *
 * Revision 1.2  2005/07/19 15:15:27  keinstein
 * Using own Templates
 *
 ********************************************************************/

#ifdef HAVE_CONFIG_H
#  include "config.h"
#endif
#ifdef HAVE_STDDEF_H
#  include <stddef.h>
#endif
#include <stdio.h>
#include <string.h>
#include "mutabor/harmonie.h"
#include "mutabor/taste.h"
#include "mutabor/heap.h"
#include "mutabor/errors.h"

/** Wurzel der Harmonien */
struct harmonie       *  list_of_harmonien;


/** Sucht eine Harmonie in einer Harmonieliste.
 * \param name Name der gesuchten Harmonie
 * \param liste Liste der Harmodien, in der gesucht wird
 * \retval NULL, falls Harmonie nicht in \a liste
 * \retval Harmonie, sonst.
 */
struct harmonie * get_harmonie (char * name, struct harmonie * liste)
{
    if (liste == NULL) return NULL;
    if ( ! strcmp (name, liste->name)) return liste;
    return get_harmonie (name, liste->next);
}

/** Gibt eine Harmonie auf der Standardausgabe aus. 
 * \param[in] this_ Harmonie
 */
void drucke_harmonie (struct harmonie * this_)
{
    struct taste * lauf;
    printf ("Name : %s Bezugstaste : %d \n      ",
             this_->name ? this_->name : "(NULL)",
             this_->bezugstaste);
    for (lauf = this_->tastenliste; lauf; lauf = lauf -> next) {
        printf (" %c%d ,", lauf->stern, lauf->taste);
    }
}

/** Fügt eine Harmonie ans Ende von \c list_of_harmonien an. 
 * Dabei wird die letzte eingelesene Tastenliste (\c tmp_tastenliste) 
 * verwendet.
 * \param name Name der Harmonie
 * \param bezugstaste Bezugstaste für die Harmonie (Schlüssel-C = 60)
 * \note Es wird immer die gesamte Liste durchsucht. Effektivität?
 */
void get_new_harmonie (char * name, int bezugstaste)
{
    struct harmonie * * lauf;
#if (DEBUG)
    if (mutabor_debug_level)
      fprintf (stderr,"Neue Harmonie: %s %d\n",name,bezugstaste);
#endif
    for (lauf= & list_of_harmonien; * lauf; lauf= & (*lauf)->next) {
        if ( ! strcmp (name, (*lauf)->name)) {
            fatal_error(14,name); /* Harmoniename doppelt */
        }
    }
    
    (* lauf) = (struct harmonie*) xmalloc (sizeof (struct harmonie));
    (* lauf) -> name                = name;
    (* lauf) -> tastenliste         = tmp_tastenliste;
    (* lauf) -> bezugstaste         = bezugstaste;
    (* lauf) -> next                = NULL;
    
}

    

/** Sichert die Daten eines Harmoniebezeichners im globalen Zwischenspeicher.
 * \param  vor_taste   Tiefste Taste beim Anschlagen der Harmonie
 * \param  name        Name der Harmonie(-form) 
 * \param  nach_taste  Höchste Teste beim Anschlagen der Harmonie
 */
void get_harmoniebezeichner (int vor_taste,
                             char * name,
                             int nach_taste)
{
    tmp_vor_taste   = vor_taste;
    tmp_name        = name;
    tmp_nach_taste  = nach_taste;
}

