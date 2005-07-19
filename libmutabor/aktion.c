/** \file
 ********************************************************************
 * Alles zu Argumenten.
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/libmutabor/aktion.c,v 1.2 2005/07/19 15:15:27 keinstein Exp $
 * \author Tobias Schlemmer <keinstein_junior@gmx.net>
 * \date $Date: 2005/07/19 15:15:27 $
 * \version $Revision: 1.2 $
 *
 * $Log: aktion.c,v $
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
#include "mutabor/aktion.h"
#include "mutabor/argument.h"
#include "mutabor/heap.h"
#include "mutabor/umstimmung.h"
#include "mutabor/tonsystem.h"
#include "mutabor/logik.h"
#include "mutabor/parameter.h"

/********* Einleseroutinen fuer Aktions-liste          *********/

/** Liste von Aktionen */
static struct aktions_liste * list_of_aktionen;

/** Setzt Aktionsliste auf \c NULL.
 * \warning Die Argumentliste wird nicht gelöscht. 
 *          Das muss gegebenenfalls vor der Initialiserung manuell erledigt werden.
 */
void init_aktions_liste (void)
{
    list_of_aktionen = NULL;
}


/** Fügt eine Aufruf-Aktion ans Ende von \a list_of_argumente an. 
 * Der Aufruf erhält die letzte eingelesene Argumentliste.
 * \param name Bezeichnung des Aufrufs, der angefügt werden soll 
 * \note Es wird immer die gesamte Liste durchsucht. Effektivität?
 */
void get_new_aktion_aufruf_element (char * name)
{
    struct aktions_liste * * lauf;
    for (lauf= & list_of_aktionen; * lauf; lauf= & (*lauf)->next) {
    }
    
    (* lauf) = (struct aktions_liste*) xmalloc ((size_t) sizeof (struct aktions_liste));
    (* lauf) -> aktions_typ           = aktion_aufruf;
    (* lauf) -> u.aktion_aufruf.name  = name;
    (* lauf) -> u.aktion_aufruf.argument_liste = get_last_argument_liste ();
    (* lauf) -> next                  = NULL;
}

/** Fügt eine Midi-Ausgabe-Aktion ans Ende von \a list_of_aktionen
 * an. Dazu wird die letzte Integersequenz verwendet.
 * \note Es wird immer die gesamte Liste durchsucht. Effektivität?
 */
void get_new_aktion_midi_out_element (void)
{
    struct aktions_liste * * lauf;
    for (lauf= & list_of_aktionen; * lauf; lauf= & (*lauf)->next) {
    }
    
    (* lauf) = (struct aktions_liste*) xmalloc ((size_t) sizeof (struct aktions_liste));
    (* lauf) -> aktions_typ           = aktion_midi_out;
    (* lauf) -> u.aktion_midi_out.midi_code = get_last_integersequenz ();
    (* lauf) -> next                  = NULL;
}

/** Gibt die Wurzel von \a list_of_aktionen zurück. */
struct aktions_liste * get_last_aktions_liste (void)
{
    return list_of_aktionen;
}


void print_aktions_liste (struct aktions_liste * lauf)
{ 
  fprintf(stderr,"print_aktions_liste() undefined.\n");
  /*
  struct aktions_liste * help_umst;
    for (help_umst = lauf->u.umstimmung_umstimmungsbund.aktions_liste;
	 help_umst;
	 help_umst = help_umst -> next ) {
      struct argument_liste * help;
      printf ("                Umstimmungs-name: %s, Parameter: ",
	      help_umst->name ? help_umst->name : "(NULL)");
      for (help = help_umst->argument_liste; help; help = help->next ) {
	drucke_argument ( & help -> argument );
      }
      printf ("\n");
    }
  */
};




/** Testet eine Liste von Aktionen auf Zulässigkeit. Wird eine nicht zulässige oder erreichbare
 * Konfiguration gefunden, wird je nach Situation ein fataler Fehler oder eine Compiler-Warnung
 * ausgelöst.
 * \param[in] aktionen Aktionsliste, die geprüft werden soll
 * \param[in] name Name für Meldungen 
 */
void check_aktionen (struct aktions_liste * aktionen, char * name) {

    for ( ; aktionen ; aktionen = aktionen -> next ) {
	    if (aktionen->aktions_typ == aktion_midi_out) {
	              struct midiliste * midi_lauf 
	                   = aktionen->u.aktion_midi_out.midi_code;
	              if (midi_lauf -> midi_code < 128 || 
	                  midi_lauf -> midi_code > 255 ) {
	                    compiler_warning (1, name);
	              }
	              while (midi_lauf) {
	                  if (midi_lauf -> midi_code < 0 ||
	                      midi_lauf -> midi_code > 255 ) {
	                      fatal_error (50, name);
	                  }
                      midi_lauf = midi_lauf -> next;
	              }
	          
	     }
	     
	    if (aktionen->aktions_typ == aktion_aufruf) {
	        struct umstimmung * help_umstimmung =
	            get_umstimmung (aktionen->u.aktion_aufruf.name,
	                            list_of_umstimmungen);
	        struct tonsystem * help_tonsystem =
	            parser_get_tonsystem (aktionen->u.aktion_aufruf.name,
	                           list_of_tonsysteme);
	        struct logik * help_logik = 
	            get_logik (aktionen->u.aktion_aufruf.name,
	                       list_of_logiken);
	        int i=0;
	                   
	        if (help_umstimmung) i++;
	        if (help_tonsystem)  i++;
	        if (help_logik)      i++;
	
	        if (i == 0) {
	            fatal_error (38, aktionen->u.aktion_aufruf.name, name);
	        }
	        
	        if (i > 1) {
	            compiler_warning (3, aktionen->u.aktion_aufruf.name, name);
	        }
	        
	        if (help_umstimmung) {
	            if (argument_list_laenge (aktionen->u.aktion_aufruf.argument_liste)
	                != parameter_list_laenge (help_umstimmung->parameter_liste)) {
	                
	                fatal_error (61, name, aktionen->u.aktion_aufruf.name);
	            }
	        }
	        
	        else if (help_tonsystem) {
	            if (argument_list_laenge (aktionen->u.aktion_aufruf.argument_liste)
	                != 0 ) {
	                
	                fatal_error (61, name, aktionen->u.aktion_aufruf.name);
	            }
	        }
	
	        
	        else if (help_logik) {
	            if (argument_list_laenge (aktionen->u.aktion_aufruf.argument_liste)
	                != 0 ) {
	                
	                fatal_error (61, name, aktionen->u.aktion_aufruf.name);
	            }
	        }
	
	    }
	    
	}
}



