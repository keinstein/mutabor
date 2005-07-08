/** \file
 ********************************************************************
 * Alles zu Argumenten.
 *
 * \author Tobias Schlemmer <keinstein_junior@gmx.net>
 * \date 2005
 * \version 0.1
 ********************************************************************/
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include "mutabor/parameter.h"
#include "mutabor/bad_decl.h"
#include "mutabor/heap.h"

/** Zählen der Elemente einer einfach verketteten Parameterliste.
 * \param list Liste der Parameter
 * \return Anzahl der Elemente von \a list
 */
int parameter_list_laenge (struct parameter_liste *list)
{ if (list) return 1 + parameter_list_laenge (list -> next);
  return 0;
}

/********* Einleseroutinen fuer Parameterliste          *********/
/*         Es wird einfach eine Liste of Namen aufgebaut       **/
/*         die allgemein verwendbar ist.                       **/

/** Allgemein verwendbare Namensliste */
static struct parameter_liste * list_of_names;


/** Setzt Namensliste auf NULL.
 * \warning Die Namensliste wird nicht gelöscht. 
 *          Das muss gegebenenfalls vor der Initialiserung manuell erledigt werden.
 */
void init_parameter_liste (void)
{
    list_of_names = NULL;
}

/** Hängt einen Namen an \a list_of_names an. 
 * Ist der Name schon in der Liste vorhanden, wird ein fataler Fehler ausgelöst.
 * \param name Name, der angehängt werden soll.
 * \todo Fehlercodes sollten per #define in Header-Dateien stehen.
 */
void get_new_name_in_parameterlist (char * name)
{
    struct parameter_liste * * lauf;
    for (lauf= & list_of_names; * lauf; lauf= & (*lauf)->next) {
        if ( ! strcmp (name, (*lauf)->name)) {
            fatal_error(17,name); /* Parametername doppelt: name */
        }
    }
    
    (* lauf) = (struct parameter_liste*) xmalloc ((size_t) sizeof (struct parameter_liste));
    (* lauf) -> name          = name;
    (* lauf) -> next          = NULL;
}

/** Gibt Wurzelelement der allgemeinen Namensliste zurück. */
struct parameter_liste * get_last_parameter_liste (void)
{
    return list_of_names;
}

/** Sucht einen Namen in einer Liste.
 * \param[in] aktueller_index Ausgangswert
 * \param[in] such_name Name, der gesucht werden soll
 * \param[in] knoten Liste, in der der Name gesucht wird
 * \retval EOF, falls \a such_name nicht in \a parameter_liste
 * \retval aktueller_index+Position von \a such_name in \a parameter_liste, falls gefunden.
 * \note Es gibt keine Überprüfung, ob \a aktueller_index in die Nähe von EOF kommt.
 */
int parameter_nummer (int aktueller_index, char * such_name, 
                             struct parameter_liste * knoten)
{
    if (knoten == NULL) return EOF;
    if ( ! strcmp (such_name, knoten -> name)) 
        return aktueller_index;
    return parameter_nummer (aktueller_index + 1, such_name, 
                             knoten -> next);
}
