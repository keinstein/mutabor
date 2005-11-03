/** \file
 ********************************************************************
 * Alles zu Argumenten.
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/libmutabor/aktion.c,v 1.4 2005/11/03 14:45:19 keinstein Exp $
 * \author Tobias Schlemmer <keinstein_junior@gmx.net>
 * \date $Date: 2005/11/03 14:45:19 $
 * \version $Revision: 1.4 $
 *
 * $Log: aktion.c,v $
 * Revision 1.4  2005/11/03 14:45:19  keinstein
 * parser and interpreter groups for doxygen
 * includes corrected
 * interpreter functions
 *
 * Revision 1.3  2005/07/20 09:46:09  keinstein
 * Includes verschönert für Doxygen
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
/* für HAVE_STDDEF_H, size_t */
#endif
#ifdef HAVE_STDDEF_H
#  include <stddef.h>
#endif
#ifdef HAVE_STRING_H
#  include<string.h>
#endif

/* aktion.h ist in umstimmung.h und in logik.h enthalten */
#include "mutabor/heap.h"
#include "mutabor/umstimmung.h"
#include "mutabor/tonsystem.h"
#include "mutabor/logik.h"
#include "mutabor/parameter.h"

/** \defgroup Parser
 * \{
 */

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
}




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

/** \} 
 * \defgroup Interpreter
 * \{
 */

/** Expandiert eine Tonliste in eine einfach verkettete Liste von Einstellungen.
 * \param the_tonliste Liste von Tönen. 
 */
struct ton_einstell * expand_tonliste (struct ton * the_tonliste)
{
    struct ton_einstell * help;
    
    if (the_tonliste == NULL) return NULL;
    
    help = (struct ton_einstell*) xmalloc (sizeof (struct ton_einstell));

    switch (the_tonliste -> ton_typ) {
    default: fatal_error (0, __FILE__, __LINE__);
    case ton_absolut:
        if (the_tonliste->name) {
            help -> ton_einstell_typ = einstell_absolut;
            help -> u.einstell_absolut.wert =
                  DOUBLE_TO_LONG (
                       FREQUENZ_TO_MIDI(
                               the_tonliste->u.ton_absolut.ton_wert));
        } else {
            help -> ton_einstell_typ = einstell_stumm;
        }               
    break;
    case ton_komplex:
        if (the_tonliste->name == NULL) {
            help -> ton_einstell_typ = einstell_stumm;
        }
        else
            if ( ! strcmp (the_tonliste->name, "@")) {
                if (the_tonliste->u.ton_komplex.komplex_liste) {
                    help -> ton_einstell_typ = einstell_relativ;
                    help -> u.einstell_relativ.wert =
                         DOUBLE_TO_LONG (
                             FAKTOR_TO_MIDI (
                               get_komplex_faktor (the_tonliste->u.ton_komplex.komplex_liste)));
                }
                else {
                    help -> ton_einstell_typ = einstell_gleich;
                }
            }
            else { /* normaler ton */
                help -> ton_einstell_typ = einstell_absolut;
                help -> u.einstell_absolut.wert =
                     DOUBLE_TO_LONG (
                            FREQUENZ_TO_MIDI (
                                  get_komplex_frequenz (the_tonliste)));
                  
            }

    break;
    }
    
    help -> next = expand_tonliste (the_tonliste -> next);

    return help;
    

}

/** Wandelt ein Tonsystem in eine Aktion um. 
 * Dazu werden Tonnamen expandiert und die
 *   einzelnen Töne in MIDI-Werte umgerechnet.
 * \param the_tonsystem Tonsystem. */
struct do_aktion * expandiere_tonsystem (
           struct tonsystem * the_tonsystem)
{
    struct do_aktion * help;
    TONSYST * help_tonsystem;

    help = (struct do_aktion*) xmalloc (sizeof (struct do_aktion));
    help -> name = the_tonsystem -> name;
    help -> aufruf_typ = aufruf_tonsystem;

    help_tonsystem = (struct TSYS*) xmalloc (sizeof (TONSYST));
    help_tonsystem -> anker = the_tonsystem -> taste;
    help_tonsystem -> breite = ton_list_laenge (the_tonsystem -> toene);
    help_tonsystem -> periode = 
         DOUBLE_TO_LONG ( 
             FAKTOR_TO_MIDI (
                 get_wert_komplex_intervall (
                         the_tonsystem -> periode)));

    {
        struct ton * ton_lauf;
        int i; 

        for (ton_lauf = the_tonsystem -> toene , i = 0 ;
             ton_lauf;
             ton_lauf = ton_lauf -> next , i++ ) {
            if (ton_lauf->name) {
                help_tonsystem->ton[i] = 
                    DOUBLE_TO_LONG( FREQUENZ_TO_MIDI(
                                     get_ton (
                                      ton_lauf -> name, list_of_toene)
                                        -> u.ton_absolut.ton_wert));
            }
            else {
               help_tonsystem->ton[i] = 0 ;
            }
        }
    }      

    help -> u.aufruf_tonsystem.tonsystem = help_tonsystem;
    help -> next = NULL;
    
    return help;
}

/** Ersetzt Parameter in einer Aktionsliste durch ihre aktuellen Werte. 
 * \param the_liste Ausgangs-Liste mit den Aktionen, deren Parameter ersetzt werden sollon.
 * \param aktuelle_parameter Liste mit den Aktuellen Parametern, die ersetzt werden können.
 * \note Neu hinzukommende Aktionen werden erhalten. Kann das passieren?
 */
struct do_aktion * expand_aktions_liste (
           struct aktions_liste * the_liste,
           struct interpreter_parameter_liste * aktuelle_parameter)
{
    struct do_aktion * help_1, * help_2, ** help_3;
    
    if (the_liste == NULL) return NULL;
    
    if (the_liste -> aktions_typ == aktion_aufruf) {
        help_1 = expandiere_name (the_liste -> u.aktion_aufruf.name,
                              the_liste -> u.aktion_aufruf.argument_liste,
                              aktuelle_parameter);
    }
    else if (the_liste -> aktions_typ == aktion_midi_out) {
        help_1 = expandiere_midi (the_liste -> u.aktion_midi_out.midi_code);
    }
    else
        fatal_error (0, __FILE__, __LINE__);
                                      
    help_2 = expand_aktions_liste (the_liste -> next, aktuelle_parameter);
    
    for (help_3 = & help_1; * help_3; help_3 = & (*help_3)->next)
    ;

    * help_3 = help_2;
    
    return help_1;
    
}
    
/** Ersetzt die Parameter einer Umstimmung durch deren Werte.
 * \param the_umstimmung Umstimmung, die bearbeitet werden soll.
 * \param aktuelle_parameter Liste der Parameter, die ersetzt werden können
 */  
struct do_aktion * expandiere_umstimmung (
           struct umstimmung * the_umstimmung,
           struct interpreter_parameter_liste * aktuelle_parameter)
{
    struct do_aktion * help;

    help = (struct do_aktion*) xmalloc (sizeof (struct do_aktion));
    help -> name = the_umstimmung -> name;
    
    switch (the_umstimmung -> umstimmung_typ) {
    case umstimmung_taste_abs:
        help -> aufruf_typ = aufruf_umst_taste_abs;
        help -> u.aufruf_umst_taste_abs.wert = 
                 get_wert_of_argument ( & the_umstimmung->u.umstimmung_taste_abs.argument,
                                        aktuelle_parameter);
        help -> next = NULL;
        return help;
/*        break; */

    case umstimmung_breite_abs:
        help -> aufruf_typ = aufruf_umst_breite_abs;
        help -> u.aufruf_umst_breite_abs.wert = 
                 get_wert_of_argument ( & the_umstimmung->u.umstimmung_breite_abs.argument,
                                        aktuelle_parameter);
        help -> next = NULL;
        return help;
/*        break; */

    case umstimmung_wiederholung_abs:
        help -> aufruf_typ = aufruf_umst_wiederholung_abs;
        help -> u.aufruf_umst_wiederholung_abs.faktor =
             DOUBLE_TO_LONG (
                  FAKTOR_TO_MIDI (
                       get_wert_komplex_intervall (
                             the_umstimmung->u.umstimmung_wiederholung_abs.komplex_liste)));
        help -> next = NULL;
        return help;
/*        break; */

    case umstimmung_wiederholung_rel:
        help -> aufruf_typ = aufruf_umst_wiederholung_rel;
        help -> u.aufruf_umst_wiederholung_rel.faktor = 
             DOUBLE_TO_LONG (
                  FAKTOR_TO_MIDI (
                       get_wert_komplex_intervall (
                             the_umstimmung->u.umstimmung_wiederholung_abs.komplex_liste)));
        help -> next = NULL;
        return help;
/*        break; */

    case umstimmung_taste_rel:
        help -> aufruf_typ = aufruf_umst_taste_rel;
        help -> u.aufruf_umst_taste_rel.wert = 
                   get_wert_of_argument ( & the_umstimmung->u.umstimmung_taste_rel.argument,
                                         aktuelle_parameter);

        help -> u.aufruf_umst_taste_rel.rechenzeichen = the_umstimmung->u.umstimmung_taste_rel.rechenzeichen;
        help -> next = NULL;
        return help;
/*        break; */
                              
    case umstimmung_breite_rel:
        help -> aufruf_typ = aufruf_umst_breite_rel;
        help -> u.aufruf_umst_breite_rel.wert = 
                   get_wert_of_argument ( & the_umstimmung->u.umstimmung_breite_rel.argument,
                                         aktuelle_parameter);
        help -> u.aufruf_umst_breite_rel.rechenzeichen = the_umstimmung->u.umstimmung_breite_rel.rechenzeichen;
        help -> next = NULL;
        return help;
/*        break; */

    case umstimmung_toene_veraendert:
        help -> aufruf_typ = aufruf_umst_toene_veraendert;
        help -> u.aufruf_umst_toene_veraendert.tonliste = 
                   expand_tonliste ( the_umstimmung->u.umstimmung_toene_veraendert.tonliste);
        help -> next = NULL;
        return help;
/*        break; */
                              
    case umstimmung_umstimmungsbund:
        xfree (help);
        return expand_aktions_liste (the_umstimmung->u.umstimmung_umstimmungsbund.aktions_liste,
                                    aktuelle_parameter);
/*        break; */
                              
    case umstimmung_umstimmungs_case:
        help -> aufruf_typ = aufruf_umst_umst_case;
        help -> u.aufruf_umst_umst_case.wert = 
                   get_wert_of_argument ( & the_umstimmung->u.umstimmung_umstimmungs_case.argument,
                                         aktuelle_parameter);
        help -> u.aufruf_umst_umst_case.umst_case =
                  expand_case_liste (the_umstimmung->u.umstimmung_umstimmungs_case.umstimmungs_case_liste,
                                     aktuelle_parameter);
        help -> next = NULL;
        return help;
/*        break; */

    case umstimmung_midi_out:
        help -> aufruf_typ = aufruf_midi_out;
        help -> u.aufruf_midi_out.out_liste = 
                    the_umstimmung->u.umstimmung_midi_out.out_liste;
        help -> next = NULL;
        return help;
/*        break; */
                       
    default:
        fatal_error (0, __FILE__, __LINE__);
        return NULL;

    }
}

/** Sucht nach einer Logik, einem Tonsystem bzw. einer Umstimmung in dieser
 * Reihenfolge. Wird eine Umstimmung zurückgeliefert, so werden gleich auch
 * deren Parameter ersetzt.
 * \param name         Name der zu suchenden Logik, des Tonsystems oder der Umstimmung.
 * \param parameter    Argumente, für die Parameter-Ersetzung
 * \param bezugs_liste Liste mit den Interpreter-Parametern, aus denen die 
 *                     aktuellen Parameter für die Expansion der Umstimmung generiert
 *                     werden.
 */     
    
struct do_aktion * expandiere_name (
           char * name,
           struct argument_liste * parameter,
           struct interpreter_parameter_liste * bezugs_liste)
{
    struct logik * help_logik;
    struct tonsystem * help_tonsystem;
    struct umstimmung * help_umstimmung;

    if (name == NULL) return NULL;

    
    help_logik = get_logik (name, list_of_logiken);
    if (help_logik) {
        
        return expandiere_logik (help_logik);        
        
    }
    else {

    help_tonsystem = parser_get_tonsystem (name, list_of_tonsysteme);
    if (help_tonsystem) {
    
        return expandiere_tonsystem (help_tonsystem);
            
    }
    else {
    
    help_umstimmung = get_umstimmung (name, list_of_umstimmungen);
    if (help_umstimmung) {

        struct interpreter_parameter_liste * aktuelle_parameter;
        aktuelle_parameter = gen_parameter_liste (parameter, bezugs_liste);
        return expandiere_umstimmung (help_umstimmung,
                                      aktuelle_parameter);
        
    }
    else
        fatal_error (0, __FILE__, __LINE__);
        return NULL;
    }}
    
}

/** Wandelt eine MIDI-Liste in eine MIDI-Ausgabe-Aktion um
 *  \param[in] liste MIDI-Liste, die umgewandelt werden soll
 */
struct do_aktion * expandiere_midi (struct midiliste * liste)
{
    struct do_aktion * help;

    help = (struct do_aktion*) xmalloc (sizeof (struct do_aktion));
    help -> name = "MidiOut";
    help -> aufruf_typ = aufruf_midi_out;
    help -> u.aufruf_midi_out.out_liste = liste;
    help -> next = NULL;
    
    return help;
}

/** \} */
