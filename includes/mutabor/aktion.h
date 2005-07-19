/** \file
 ********************************************************************
 * Alles zu Aktionen.
 *
 * \author Tobias Schlemmer <keinstein_junior@gmx.net>
 * \date 2005
 * \version 0.1
 ********************************************************************/

#ifndef __AKTION_H_INCLUDED
#define __AKTION_H_INCLUDED

#include "mutabor/midicalc.h"
#include "mutabor/argument.h"

#ifdef __cplusplus
namespace mutabor {
  extern "C" {
#endif


    /** Logik kann entweder MIDI-Daten senden oder Aktionen aufrufen. */
    enum aktions_typ {
      aktion_midi_out, /**< MIDI-Daten ausgeben */
      aktion_aufruf /**< Eine andere Aktion aufrufen */
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

    void init_aktions_liste (void);
    void get_new_aktion_aufruf_element (char * name);
    void get_new_aktion_midi_out_element (void);
    void get_aktion_midi_out (void);
    void get_aktion_aufruf (char * name);
    void check_aktionen (struct aktions_liste * aktionen, char * name);
    void print_aktions_liste (struct aktions_liste * lauf);
	 
    struct aktions_liste * get_last_aktions_liste (void);

#ifdef __cplusplus 
  } // extern "C"
} // namespace mutabor
#endif

#endif /* __AKTION_H_INCLUDED */
