/** \file
 ********************************************************************
 * Alles zu Anweisungen.
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/libmutabor/anweisung.c,v 1.2 2005/07/19 15:15:27 keinstein Exp $
 * \author Tobias Schlemmer <keinstein_junior@gmx.net>
 * \date $Date: 2005/07/19 15:15:27 $
 * \version $Revision: 1.2 $
 *
 * $Log: anweisung.c,v $
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
#include "mutabor/anweisung.h"
#include "mutabor/ausloeser.h"
#include "mutabor/aktion.h"
#include "mutabor/heap.h"

/** Globaler Zwischenspeicher für genau eine Anweisungsliste. */
static struct anweisung * tmp_anweisungsliste;

/** Setzt globalen Anweisungs-Zwischenspeicher auf NULL.
 * \warning Die Liste wird nicht gelöscht. 
 *          Das muss gegebenenfalls vor der Initialiserung manuell erledigt werden.
 */
void init_anweisungs_liste (void)
{
    tmp_anweisungsliste = NULL;
}

/** Gibt Wurzelelement von \a #tmp_anweisungs_liste zurück */
struct anweisung * get_last_anweisungs_liste (void)
{
    return tmp_anweisungsliste ;
}

/** Fügt eine neue Anweisung ans Ende von \a tmp_anweisungsliste an. 
 * Dabei werden der letzte eingelesene Auslöser und 
 * die letzte Aktionsliste verwendet.
 * \note Es wird immer die gesamte Liste durchsucht. Effektivität?
 */
void get_new_anweisung (void)
{
    struct anweisung * * lauf;
    for (lauf= & tmp_anweisungsliste; * lauf; lauf= & (*lauf)->next)
        /* Nur Ende der Liste finden */ ;

    (* lauf) = (struct anweisung*) xmalloc (sizeof (struct anweisung));
    (* lauf) -> ausloeser   = get_last_ausloeser ();
    (* lauf) -> aktion      = get_last_aktions_liste ();
    (* lauf) -> next        = NULL;
    
}

