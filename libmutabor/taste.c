/** \file
 ********************************************************************
 * Tasten usw.
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/libmutabor/taste.c,v 1.1 2005/07/08 14:44:20 keinstein Exp $
 * \author Tobias Schlemmer <keinstein_junior@gmx.net>
 * \date $Date: 2005/07/08 14:44:20 $
 * \version $Revision: 1.1 $
 * \log
 * $Log: taste.c,v $
 * Revision 1.1  2005/07/08 14:44:20  keinstein
 * Neue Datei.
 * Aus parser.c herausgelöst.
 *
 ********************************************************************/

#include <stddef.h>
#include "mutabor/heap.h"
#include "mutabor/taste.h"

/** Eine temporäre Liste von Tasten */
struct taste * tmp_tastenliste;

/** Setzt die temporäre Tastenliste auf \c NULL.
 * \warning Die Argumentliste wird nicht gelöscht. 
 *          Das muss gegebenenfalls vor der Initialiserung manuell erledigt werden.
 */
void init_tastenliste (void)
{
    tmp_tastenliste = NULL;
}

/** Fügt eine Taste ans Ende von \c tmp_tastenliste an. 
 * \param taste Tastennummer (Schlüssel-C = 60)
 * \param stern Stern zur Taste (\c TRUE oder \c FALSE)
 * \note Es wird immer die gesamte Liste durchsucht. Effektivität?
 */
void get_new_taste (int taste, char stern)
{
    struct taste * * lauf;
    for (lauf= &tmp_tastenliste; *lauf; lauf = &(*lauf)->next)
        /* Nur Ende der Liste finden */ ;
    
    (* lauf) = (struct taste*) xmalloc (sizeof (struct taste));
    (* lauf) -> taste               = taste;
    (* lauf) -> stern               = stern;
    (* lauf) -> next                = NULL;
    
}

/** Prüft ob eine Taste in einer Liste von Tasten enthalten ist.
 * \param[in] taste Taste, die gesucht wird
 * \param[in] lauf Tastenliste, in der gesucht wird
 * \retval 1 Taste wurde gefunden
 * \retval 0 Taste wurde nicht gefunden
 */
int enthalten_in_tastenliste (int taste, struct taste * lauf) {
    while (lauf)
        if (lauf -> taste == taste) 
            return 1;
        else
            lauf = lauf -> next;
            
    return 0;
} 

