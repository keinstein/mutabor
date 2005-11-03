/** \file
 ********************************************************************
 * Alles zu Argumenten.
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/libmutabor/argument.c,v 1.3 2005/11/03 14:45:58 keinstein Exp $
 * \author Tobias Schlemmer <keinstein_junior@gmx.net>
 * \date $Date: 2005/11/03 14:45:58 $
 * \version $Revision: 1.3 $
 *
 * $Log: argument.c,v $
 * Revision 1.3  2005/11/03 14:45:58  keinstein
 * new includes
 * interpreter functions
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
#include <stdio.h>

#include "mutabor/argument.h"
#include "mutabor/heap.h"
#include "mutabor/interpreter.h"
#include "mutabor/errors.h"

/** Zählen der Elemente einer einfach verketteten Argumentliste.
 * \param list Liste der Argumente
 * \return Anzahl der Elemente von \a list
 */
int argument_list_laenge (struct argument_liste *list)
{ if (list) return 1 + argument_list_laenge (list -> next);
  return 0;
}

/** Gibt eine Argumentliste auf der Standardausgabe aus.
 * \param[in] this_ Liste der Argumente, die ausgegeben werden sollen.
 */
void print_argumentliste (struct argument_liste * this_)
{
    if (this_) {
        if (this_ -> argument.argument_typ == zahl)
            printf (" %d ", this_ -> argument.u.zahl.zahl);
        else
            printf (" %s ", this_ -> argument.u.parameter.parameter_name);
            
        print_argumentliste (this_ -> next);
    }
}


/********* Einleseroutinen fuer Argumentliste          *********/

/** Argumentliste. */
static struct argument_liste * list_of_argumente;


/** Setzt Argumentliste auf NULL.
 * \warning Die Argumentliste wird nicht gelöscht. 
 *          Das muss gegebenenfalls vor der Initialiserung manuell erledigt werden.
 */
void init_argument_liste (void)
{
    list_of_argumente = NULL;
}

/** Fügt eine Zahl ans Ende von \a list_of_argumente an. 
 * \param parameter_zahl Zahl, die angefügt werden soll 
 * \note Es wird immer die gesamte Liste durchsucht. Effektivität?
 * \todo Typkonvertierung von \c double nach \c int prüfen
 */
void get_new_number_in_argument_list (double parameter_zahl)
{
    struct argument_liste * * lauf;
    for (lauf= & list_of_argumente; * lauf; lauf= & (*lauf)->next) {
    }
    
    (* lauf) = (struct argument_liste*) xmalloc ((size_t) sizeof (struct argument_liste));
    (* lauf) -> argument.argument_typ = zahl;
    (* lauf) -> argument.u.zahl.zahl  = (int) parameter_zahl;
    (* lauf) -> next                  = NULL;
}


/** Fügt einen Namen ans Ende von \a list_of_argumente an. 
 * \param parameter_name Name, der angefügt werden soll 
 * \note Es wird immer die gesamte Liste durchsucht. Effektivität?
 */
void get_new_name_in_argument_list (char * parameter_name)
{
    struct argument_liste * * lauf;
    for (lauf= & list_of_argumente; * lauf; lauf= & (*lauf)->next) {
#if 0
        if ( ! strcmp (name, (*lauf)->name)) {
            fatal_error(17,name); /* Parametername doppelt: name */
        }
#endif
    }
    
    (* lauf) = (struct argument_liste*) xmalloc ((size_t) sizeof (struct argument_liste));
    (* lauf) -> argument.argument_typ = parameter;
    (* lauf) -> argument.u.parameter.parameter_nummer = 0;
    (* lauf) -> argument.u.parameter.parameter_name = parameter_name;
    (* lauf) -> next          = NULL;
}

/** Gibt die Wurzel von \a list_of_argumente zurück. */
struct argument_liste * get_last_argument_liste (void)
{
    return list_of_argumente;
}


/** Gibt ein Argument auf der Standardausgabe aus. 
 * \param[in] z_or_p Argument.
 */
void drucke_argument (struct argument * z_or_p)
{
    if (z_or_p -> argument_typ == zahl) {
        printf (" Zahl: %d ", z_or_p->u.zahl.zahl);
    }
    else {
        printf (" Parameter: %s, Nr: %d ", 
                 z_or_p->u.parameter.parameter_name,
                 z_or_p->u.parameter.parameter_nummer);
    }
}

/** Schreibt ein Argument in eine Zieldatei. Das Argument wird je nach Typ
 * als Zeichenkette oder Zahl ausgegeben. Ist der Typ unbekannt, wird ein fataler
 * Fehler ausgegeben.
 * \param zieldatei Datei, in die geschrieben werden soll. Diese muss 
 *                  schon für das Schreiben geöffnet sein.
 * \param argument  Argument, das geschrieben werden soll.
 */
void fprint_argument (FILE * zieldatei, struct argument * argument)
{
    if (argument -> argument_typ == zahl) {
        fprintf (zieldatei, ", %c ", argument -> u.zahl.zahl);
    }
    else if (argument -> argument_typ == parameter) {
        fprintf (zieldatei, ", %s ", argument -> u.parameter.parameter_name);
    }
    else
        fatal_error (MUTABOR_ERROR_UNDEFINED, __FILE__, __LINE__ );
}

/** Gibt das Wertefeld eines Argumentes zurück.
 * \param argument Argument, das gesucht werden soll.
 * \param aktuelle_parameter Interpreter-Parameter-Liste mit Wertefeldern für 
 * nichtnumerische Argumente.
 */
int * get_wert_of_argument (
                 struct argument * argument,
                 struct interpreter_parameter_liste * aktuelle_parameter
                 )
{
    switch (argument->argument_typ) {
    case zahl:
        return * get_cache_konstante (argument->u.zahl.zahl);
/*    break; */
    case parameter: {
        struct interpreter_parameter_liste * lauf;
        int i;
        for (lauf=aktuelle_parameter, i=argument->u.parameter.parameter_nummer;
             lauf && i;
             lauf = lauf -> next, i--)
        ;
        if (lauf)
            return * lauf->werte_feld;
        else {
            fatal_error (MUTABOR_ERROR_UNDEFINED, __FILE__, __LINE__);
            return NULL;
        }
    }
/*    break; */
    default: 
        fatal_error (MUTABOR_ERROR_UNDEFINED, __FILE__, __LINE__);
        return NULL;
/*    break; */
    }
    
}
