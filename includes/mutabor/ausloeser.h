/** \file
 ********************************************************************
 * Alles zu Auslösern.
 *
 * $Id: ausloeser.h,v 1.4 2006/03/27 16:53:05 keinstein Exp $
 * \author Tobias Schlemmer <keinstein_junior@gmx.net>
 * \date $Date: 2006/03/27 16:53:05 $
 * \version $Revision: 1.4 $
 ********************************************************************/

#ifndef __AUSLOESER_H_INCLUDED
#define __AUSLOESER_H_INCLUDED

#include "mutabor/midicalc.h"
#include "mutabor/harmonie.h"
#include "mutabor/anweisung.h"

#ifdef __cplusplus
namespace mutabor {
  extern "C" {
#endif

    /**< Typen von auslösenden Ereignissen. */
    enum ausloeser_typ {
      ausloeser_harmonie,      /**< Harmonie */
      ausloeser_harmonie_form, /**< Harmonieform */
      ausloeser_taste,         /**< Taste */
      ausloeser_midi_in,       /**< MIDI-Ereignis */
      ausloeser_default        /**< Standard */
    };

    /** Einzelndes Ereignis, das Logik aktiviert. */
    struct ausloeser {
      enum ausloeser_typ ausloeser_typ; /** Typ des auslösenden Ereignisses. */
      union {
        struct {
	  int vortaste; /**< Tiefste Taste. */
	  char * name; /**< Name. */
	  int nachtaste; /**< Höchste Taste. */
        } ausloeser_harmonie; /**< Wenn von Harmonie ausgelöst */
        struct {
	  int vortaste; /**< Tiefste Taste. */
	  char * name; /**< Name. */
	  int nachtaste; /**< Höchste Taste. */
        } ausloeser_harmonie_form; /**< Wenn von Harmonieform ausgelöst */
        struct {
	  char * taste; /**< Name der Taste */
        } ausloeser_taste; /**< Wenn von Taste ausgelöst */
        struct {
	  struct midiliste * midi_code; /**< MIDI-Sequenz */
        } ausloeser_midi_in; /**< Wenn von MIDI-Sequenz ausgelöst */
      } u; /**< Daten des Auslösers */
    };
    
    /** Tastatur-Eingabe */
    struct keyboard_ereignis {
      char taste; /**< Taste, die gedrückt wurde */
      char * name; /**< Name des Ereignisses */
      struct do_aktion * aktion; /**< Auszuführende Aktion */
      struct logik * the_logik_to_expand; /**< auszuführende Logik */
      struct keyboard_ereignis * next; /**< Nächstes Ereignis */
    };

    /** MIDI-Ereignis in aktueller Logik. */
    struct midi_ereignis {
      int * first_pos; /**< Anfangsposition des MIDI-Scans */
      int * scan_pos; /**< aktuelle Position des MIDI-Scans */
      char * name; /**< Name des Ereignisses */
      struct do_aktion * aktion; /**< Auszuführende Aktion */
      struct logik * the_logik_to_expand; /**< Zu expandierende Logik */
      struct midi_ereignis * next; /**< Nächstes. */
    };

    /** Klaviatur-Eingabe: Harmonien und -formen */
    struct harmonie_ereignis {
      PATTERNN * pattern; /**< zu erkennendes Tastenmuster (Harmonie/-form) */
      char ist_harmonieform; /**< Harmonieform oder Harmonie? */
      int vortaste; /**< linkeste Taste */
      int nachtaste; /**< rechteste Taste */
      char * name; /**< Name */
      struct do_aktion * aktion; /**< auszuführende Aktion */
      struct logik * the_logik_to_expand; /**< zu verwendende Logik */
      struct harmonie_ereignis * next; /**< Nächstes */
    };

    extern struct harmonie_ereignis *  first_harmonie[MAX_BOX];
    extern struct harmonie_ereignis ** last_global_harmonie[MAX_BOX];
    extern struct harmonie_ereignis ** first_lokal_harmonie;
    extern struct keyboard_ereignis *  first_keyboard[MAX_BOX];
    extern struct keyboard_ereignis ** last_global_keyboard[MAX_BOX];
    extern struct keyboard_ereignis ** first_lokal_keyboard;
    extern struct midi_ereignis     *  first_midi[MAX_BOX];
    extern struct midi_ereignis     ** last_global_midi[MAX_BOX];
    extern struct midi_ereignis     ** first_lokal_midi;

    void print_ausloeser (struct ausloeser * this_);

    void init_ausloeser (void);
    void get_ausloeser_default (void);
    void get_ausloeser_harmonie (void);
    void get_ausloeser_harmonie_form (void);
    void get_ausloeser_taste (char * name);
    void get_ausloeser_midi_in (void);
    void check_ausloeser (struct ausloeser * ausloeser, char * name);
    void insert_in_globale_liste (int instrument, struct logik * lauf);
    void expandiere_in_globale_liste (void);
    
    struct midi_ereignis ** get_ende_midi (struct midi_ereignis ** lauf);
    struct keyboard_ereignis ** get_ende_keyboard (struct keyboard_ereignis ** lauf);
    struct harmonie_ereignis ** get_ende_harmonie (struct harmonie_ereignis ** lauf);
    struct ausloeser * get_last_ausloeser (void);

#ifdef __cplusplus 
  } // extern "C"
} // namespace mutabor
#endif

#endif /* __AUSLOESER_H_INCLUDED */
