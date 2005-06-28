/** \file
 ********************************************************************
 * Zu korrigierende Querabhängigkeiten zur GUI und sonstige komische
 * Deklarationen.
 *
 * \author Tobias Schlemmer <keinstein_junior@gmx.net>
 * \date 2005
 * \version 0.1
 ********************************************************************/

#ifndef __BAD_DECL_H_INCLUDED
#define __BAD_DECL_H_INCLUDED

#ifdef __cplusplus
namespace mutabor {
  extern "C" {
#endif

#define bool unsigned int
#define MAX_BOX 256   /**< Maximale Anzahl der Boxen/Instumente */

    void fatal_error( int nummer, ... );
    void show_line_number( int n );
    extern int keys_changed[MAX_BOX];
    extern bool RealTime;

#define GERMAN

    /** Maximale Breite eines Tonsystems */
#define MAX_BREITE 72
    
    /** Maximale Anzahl Bytes in MIDIOUT / MIDIIN */
#define MAX_MIDI 32

#ifdef __cplusplus 
  }
}
#endif

#endif /* __BAD_DECL_H_INCLUDED */
