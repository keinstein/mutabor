/** \file
 ********************************************************************
 * Alles zu Aktionen.
 *
 * $Id: aktion.h,v 1.4 2005/11/03 14:22:44 keinstein Exp $
 * \author Tobias Schlemmer <keinstein@users.berlios.de>
 * \date $Date: 2005/11/03 14:22:44 $
 * \version $Revision: 1.4 $
 *
 * $Log: aktion.h,v $
 * Revision 1.4  2005/11/03 14:22:44  keinstein
 * new file header
 * interpreter structures etc.
 *
 ********************************************************************/

#ifndef __AKTION_H_INCLUDED
#define __AKTION_H_INCLUDED

#include "mutabor/midicalc.h"
#include "mutabor/argument.h"
#include "mutabor/umstimmung.h"
#include "mutabor/tonsystem.h"
#include "mutabor/parameter.h"
#include "mutabor/logik.h"

#ifdef __cplusplus
namespace mutabor {
  extern "C" {
#endif


    /** Logik kann entweder MIDI-Daten senden oder Aktionen aufrufen. */
    enum aktions_typ {
      aktion_midi_out, /**< MIDI-Daten ausgeben */
      aktion_aufruf /**< Eine andere Aktion aufrufen */
    };
    
    /** Nochmal Typ eines Aufrufes/einer Aktion (Interpreter). 
	\todo Doppelte Datentypen: muss das sein? */
    enum aufruf_typ { 
      aufruf_logik, /**< Logik aktivieren */
      aufruf_tonsystem, /**< Tonsystem laden */
      aufruf_umst_taste_abs, /**< Neuer Wert für Anker-Taste */
      aufruf_umst_breite_abs, /**< Änderung der absoluten Breite des Tonsystems */
      aufruf_umst_wiederholung_abs, /**< Neuer Widerholungsfaktor */
      aufruf_umst_wiederholung_rel, /**< Änderung des Widerholungsfaktors */
      aufruf_umst_taste_rel, /**< Änderung der Anker-Taste */
      aufruf_umst_breite_rel, /**< Änderung der Breite des Tonsystems */
      aufruf_umst_toene_veraendert, /**< Änderung der Töne im Tonsystem */
      aufruf_umst_umst_bund, /**< Umstimmungs-Bund, also mehrere Aktionen */
      aufruf_umst_umst_case, /**< Umstimmungs-Case-Anweisung, also eine von mehreren Aktionen */
      aufruf_midi_out /**< Ausgabe eines festgelegten MIDI-Codes */
    };
    
    /** Aktionen als einfach verkettete Liste. */
    struct aktions_liste {
      enum aktions_typ aktions_typ; /**< Typ der Aktion */
      union {
        struct {
	  struct midiliste * midi_code;  /**< MIDI-Sequenz */
        } aktion_midi_out; /**< Daten für MIDI-Ausgabe */
        struct {
	  char * name;     /**< Name der aufgerufenen Aktion */
	  struct argument_liste * argument_liste; 
	  /**< Argumente der aufgerufenen Aktion */
        } aktion_aufruf; /**< Daten für einen Aktions-Aufruf */
      } u; /**< Daten */
      struct aktions_liste * next; /**< Nächste Aktion */
    };


    /** Nochmal Aktionen als einfach verkettete Liste für den Interpreter. 
     \todo Doppelte Strukturen: Muss das sein? */
    struct do_aktion {
/*
    parameter_liste * parameter;
*/
      char * name;
      enum aufruf_typ aufruf_typ;
      union {
        struct {
	  struct do_aktion * einstimmung; /**< Aktionsliste einer Logik */
	  struct harmonie_ereignis ** lokal_harmonie; /**< Harmonie-Ereignisse einer Logik */
	  struct keyboard_ereignis ** lokal_keyboard; /**< Tastatur-Eingaben einer Logik */
	  struct midi_ereignis     ** lokal_midi; /**< MIDI-Ereignis einer Logik */
        } aufruf_logik; /**< Daten einer aufgerufenen Logik */
        struct {
	  TONSYST * tonsystem;  /**< Das neue Tonsystem */
        } aufruf_tonsystem; /**< Daten für eine Tonsystem-Änderung */
        struct { 
	  int * wert; /**< Neuer Wert der Anker-Taste */
        } aufruf_umst_taste_abs; /**< Daten für eine neue Ankertaste */
        struct { 
	  int * wert; /**< Neuer Wert für die Tonsystem-Breite */
        } aufruf_umst_breite_abs; /**< Daten für eine neue Tonsytem-Breite. */
        struct { 
	  long faktor; /**< Neuer Faktor für die Tonsystem-Wiederholung */
        } aufruf_umst_wiederholung_abs; /**< Daten für einen neuen  Wiederholungsfaktor. */
        struct { 
	  long faktor; /**< Faktor für die Änderung des Wiederholungsfaktors für das Tonsystem */
        } aufruf_umst_wiederholung_rel; /**< Daten für die Änderung des Wiederholungsfaktors für das Tonsystem */
        struct { 
	  int * wert; /**< Betrag der Verschiebung der Ankertaste */
	  char rechenzeichen; /**< Richtung der Verschiebung der Ankertaste 
			       \todo warum nicht mit in Wert kodiert? */
        } aufruf_umst_taste_rel; /**< Daten für eine Verschiebung der Anker-Taste. */
        struct { 
	  int * wert; /**< Betrag der Breitenänderung des Fundamentalsystems */
	  char rechenzeichen; /**< Vorzeichen der Breitenänderung */
        } aufruf_umst_breite_rel; /**< Daten für eine Breitenänderung des Fundamentalsystems */
        struct { 
	  struct ton_einstell * tonliste; /**< Liste mit den neuen Tönen */
        } aufruf_umst_toene_veraendert; /**< Daten für eine Änderung der Töne im Fundamentalsystem */
        struct { 
	  int * wert; /**< Betrachteter Wert */
	  struct case_element * umst_case; /**< Alternativen */
        } aufruf_umst_umst_case; /**< Daten einer Mehrfach-Auswahl */
        struct { 
	  struct midiliste * out_liste; /**< Midi-Sequenz */
        } aufruf_midi_out; /**< Daten einer Festgelegten MIDI-Ausgabe */
      } u;
      struct do_aktion * next; /**< Nächste Aktion. */
    };

    void init_aktions_liste (void);
    void get_new_aktion_aufruf_element (char * name);
    void get_new_aktion_midi_out_element (void);
    void get_aktion_midi_out (void);
    void get_aktion_aufruf (char * name);
    void check_aktionen (struct aktions_liste * aktionen, char * name);
    void print_aktions_liste (struct aktions_liste * lauf);
	 
    struct aktions_liste * get_last_aktions_liste (void);

    struct do_aktion * expandiere_name (char * name,
			struct argument_liste * parameter,
			struct interpreter_parameter_liste * bezugs_liste);
    struct do_aktion * expandiere_umstimmung (struct umstimmung * the_umstimmung,
		      struct interpreter_parameter_liste * aktuelle_parameter);
    struct do_aktion * expandiere_midi (struct midiliste * liste);
    struct do_aktion * expand_aktions_liste (
			 struct aktions_liste * the_liste,
			 struct interpreter_parameter_liste * aktuelle_parameter);
    struct do_aktion * expandiere_tonsystem (struct tonsystem * the_tonsystem);
#ifdef __cplusplus 
  } // extern "C"
} // namespace mutabor
#endif

#endif /* __AKTION_H_INCLUDED */
