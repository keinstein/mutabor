/** \file
 ********************************************************************
 * Alles zu Auslösern.
 *
 * \author Tobias Schlemmer <keinstein_junior@gmx.net>
 * \date 2005
 * \version 0.1
 ********************************************************************/

#ifndef __AUSLOESER_H_INCLUDED
#define __AUSLOESER_H_INCLUDED

#include "mutabor/midicalc.h"

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
    
    void print_ausloeser (struct ausloeser * this_);

    void init_ausloeser (void);
    void get_ausloeser_default (void);
    void get_ausloeser_harmonie (void);
    void get_ausloeser_harmonie_form (void);
    void get_ausloeser_taste (char * name);
    void get_ausloeser_midi_in (void);
    void check_ausloeser (struct ausloeser * ausloeser, char * name);

    struct ausloeser * get_last_ausloeser (void);

#ifdef __cplusplus 
  } // extern "C"
} // namespace mutabor
#endif

#endif /* __AUSLOESER_H_INCLUDED */
