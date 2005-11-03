/** \file
 ********************************************************************
 * Mutabor Interpreter.
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/libmutabor/interpreter.c,v 1.1 2005/11/03 14:07:19 keinstein Exp $
 * \author Tobias Schlemmer <keinstein@users.berlios.de>
 * \date $Date: 2005/11/03 14:07:19 $
 * \version $Revision: 1.1 $
 *
 * $Log: interpreter.c,v $
 * Revision 1.1  2005/11/03 14:07:19  keinstein
 * initial revision
 *
 ********************************************************************/

#ifdef HAVE_CONFIG_H
#  include "config.h"
#endif

#ifdef HAVE_STDLIB_H
#  include <stdlib.h>
#endif
#include "mutabor/interpreter.h"
#include "mutabor/parameter.h"
#include "mutabor/heap.h"
#include "mutabor/ausloeser.h"
#include "mutabor/logik.h"

/** Diese Zweielementige Liste ist Parameterliste bei Logiken */
static struct interpreter_parameter_liste zentrums_knoten =
     { & laufzeit_zentrum, NULL };

/** Diese Zweielementige Liste ist Parameterliste bei Logiken */
static struct interpreter_parameter_liste abstands_knoten =
     { & laufzeit_abstand, & zentrums_knoten };

/** Diese Zweielementige Liste ist Parameterliste bei Logiken */
struct interpreter_parameter_liste * start_parameter_liste =
    & abstands_knoten;

int laufzeit_zentrum[MAX_BOX];
int laufzeit_abstand[MAX_BOX];

/** \c cache_konstanten enthält alle jemals als Wert benutzten
      Konstanten (ohne doppelte).
*******/

struct cache_konstanten {
    int konstante [MAX_BOX];
    struct cache_konstanten * next;
};

static struct cache_konstanten * cache_konstanten = NULL;

/** Sichert, dass ein Wert in #cache_konstanten vorhanden ist
 *  und gibt das entsprechende Element der Liste zurück. Bei neuen
 *  Einträgen werden alle Einträge des entsprechenden Feldes \c konstante
 *  auf den übergebenen Wert gesetzt.
 *  \param wert Wert, dessen Element zurückgegeben werden soll
 */
int (* get_cache_konstante (int wert) ) [MAX_BOX]
{
    struct cache_konstanten ** lauf;
    int i;

    for (lauf = & cache_konstanten; *lauf; lauf = & (*lauf)->next) {
        if ((*lauf)->konstante[0] == wert)
            return & (*lauf)->konstante;
    }
    *lauf = (struct cache_konstanten*) xmalloc (sizeof (struct cache_konstanten));
    for (i=0; i<MAX_BOX; i++)
        (*lauf)->konstante[i] = wert;
    (*lauf)->next = NULL;
    return & (*lauf)->konstante;
}


/** Initialisiert die Mutabor-Tabellen.
 * Dabei werden die globalen und die lokalen Auslöser initialisiert.
 */
void mutabor_tabellen_generator (void)
{
    /* Ausgabe der Pointer-Setz-Prozeduren */

    struct logik * lauf;
    struct anweisung * lauf_anweisung;
    int i;


  /* Neu:  extra Löschungen */
    cache_konstanten = NULL;

    for (i=0; i<MAX_BOX; i++) {
        first_midi     [i] = NULL;
        first_keyboard [i] = NULL;
        first_harmonie [i] = NULL;
    }


    for (i=0;i<MAX_BOX;i++) {

    /* Die globalen Listen werden initialisiert: */

    /* Die globalen Auslöser werden in die vorbereiteten Listen eingetragen: */
        for (lauf = list_of_logiken; lauf; lauf = lauf -> next) {

            insert_in_globale_liste (i, lauf);
        }

        last_global_harmonie[i]=get_ende_harmonie (& first_harmonie[i]);
        last_global_keyboard[i]=get_ende_keyboard (& first_keyboard[i]);
        last_global_midi[i]=get_ende_midi (& first_midi[i]);
    }

    /* Die lokalen Listen werden erzeugt: */
    /* Es wird ein Array mit Anfangszeigern  auf die lokalen
       Auslöser angelegt. Die Nummer der Logik ist index */

    i = logik_list_laenge (list_of_logiken);
    first_lokal_harmonie = (struct harmonie_ereignis* *) xcalloc ((size_t)i, sizeof(first_lokal_harmonie[0]));
    first_lokal_keyboard = (struct keyboard_ereignis* *) xcalloc ((size_t)i, sizeof(first_lokal_keyboard[0]));
    first_lokal_midi     = (struct midi_ereignis* *) xcalloc ((size_t)i, sizeof(first_lokal_midi[0]));
    /* #### Wichtig ist, dass calloc alles auf 0 setzt (NULL)  */

    for (lauf=list_of_logiken, i=0;
         lauf;
         lauf=lauf->next, i++ ) {

        for (lauf_anweisung=lauf->anweisungsliste; lauf_anweisung;
                    lauf_anweisung=lauf_anweisung->next) {
        
            insert_in_lokale_liste (i, lauf_anweisung, lauf->name);
        }
    }


    expandiere_in_globale_liste ();

} /* end of mutabor_tabellen_generator */



