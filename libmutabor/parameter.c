/** \file
 ********************************************************************
 * Alles zu Argumenten.
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/libmutabor/parameter.c,v 1.4 2005/11/03 14:55:39 keinstein Exp $
 *
 * \author Tobias Schlemmer <keinstein_junior@gmx.net>
 * \date $Date: 2005/11/03 14:55:39 $
 * \version $Revision: 1.4 $
 * \todo Portabilisierung von:
 *
 * $Log: parameter.c,v $
 * Revision 1.4  2005/11/03 14:55:39  keinstein
 * includes
 * interpreter functions
 *
 * Revision 1.3  2005/07/20 12:22:38  keinstein
 * CVS-Kopf
 * config.h
 * includes für Doxygen optimiert
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
#include <string.h>
#include <stdio.h>
#include "mutabor/parameter.h"
#include "mutabor/heap.h"
#include "mutabor/interpreter.h"

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

/** Generiert eine Interpreter-Parameterliste aus eine Argumentliste. Dabei
 * wird eine Bezugsliste verwendet, die für parametrische argumente die 
 * Wertefelder zur Verfügung stellt. Taucht ein unerwartetes Ereignis auf, wird ein
 * fataler Fehler ausgelöst.
 * \param liste Liste der Argumente, die in die Interpreter-Liste eingetragen werden sollen.
 * \param bezugs_liste Liste mit den Bezügen/Wertefeldern, die für nichtnumerische Argumente
 *                     verwendet werden soll.
 */
struct interpreter_parameter_liste * gen_parameter_liste (
           struct argument_liste * liste,
           struct interpreter_parameter_liste * bezugs_liste)
{
    struct interpreter_parameter_liste * help;

    if (liste == NULL)
        return NULL;
    help = (struct interpreter_parameter_liste*) xmalloc (sizeof (struct interpreter_parameter_liste));
    switch (liste->argument.argument_typ) {
    case zahl:
        help->werte_feld = get_cache_konstante (liste->argument.u.zahl.zahl);
    break;
    case parameter: {
        int i;
        struct interpreter_parameter_liste * lauf;
        for (lauf = bezugs_liste, i=liste->argument.u.parameter.parameter_nummer;
             lauf && i;
             lauf = lauf -> next, i--)
        ;
        if (lauf)
            help->werte_feld = lauf -> werte_feld;
        else
            fatal_error (0, __FILE__, __LINE__);
    }
    break;
    default:
        fatal_error (0, __FILE__, __LINE__);
    break;
    }
    help->next = gen_parameter_liste (liste->next, bezugs_liste);
    return help;
}

