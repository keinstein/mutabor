/** \file
 ********************************************************************
 * Alles zu Tonsystemen.
 *
 * $Id: tonsystem.h,v 1.3 2005/11/03 14:37:57 keinstein Exp $
 * \author Tobias Schlemmer <keinstein_junior@gmx.net>
 * \date $Date: 2005/11/03 14:37:57 $
 * \version $Revision: 1.3 $
 * 
 * $Log: tonsystem.h,v $
 * Revision 1.3  2005/11/03 14:37:57  keinstein
 * new file header
 * includes corrected
 * interpreter data structures
 *
 ********************************************************************/

#ifndef __TONSYSTEM_H_INCLUDED
#define __TONSYSTEM_H_INCLUDED

#include "ton.h"
#include "interval.h"
#include "bad_decl.h"

#ifdef __cplusplus
namespace mutabor {
  extern "C" {
#endif

    /**  Definition der Tonsysteme als verkettete Liste.  Tonsystem
     *   enthält eine Liste mit den enthaltenen Tönen. Der Name eines
     *   Tons ist \c NULL wenn dieser Ton nicht gültig ist, ansonsten
     *   der Name des Tons.
     *
     *   \remark Im Sinne der Theorie sollte man es vielleicht eher
     *   Stimmung oder Temperatur oder anders nennen.
     */
    struct tonsystem {
      char *name; /**< Name des Tonsystems */
      int taste; /**< Ankertaste */
      struct komplex_intervall *periode; /**< Veränderung des Grundtones nach einer Periode */
      struct ton *toene; /**< Töne für die Tasten */
      struct tonsystem *next; /**< Nächstes */
    };

    /** Einzelnes Tonsystem. Enthält die aktuellen Daten für den Interpreter.*/

    typedef struct TSYS {
      int anker; /**< Verankerungstaste */
      int breite; /**< Tonsystembreite */
      long periode; /**< Perioden-Faktor */
      long ton[MAX_BREITE]; /**< Töne. */
    } TONSYST;
    

    void get_new_tonsystem (char *name, int taste);
    void get_new_tonsystem_negative (char *name, int taste);
    int tonsystem_list_laenge (struct tonsystem *list);

    struct tonsystem * parser_get_tonsystem (char * name, struct tonsystem * liste);
    void check_tonsystem_konsistenz(void);

    struct tonsystem      *  list_of_tonsysteme;


#ifdef __cplusplus 
  } // extern "C"
} // namespace mutabor
#endif

#endif /* __TONSYSTEM_H_INCLUDED */
