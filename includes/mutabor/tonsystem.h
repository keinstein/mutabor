/** \file
 ********************************************************************
 * Alles zu Tonsystemen.
 *
 * \author Tobias Schlemmer <keinstein_junior@gmx.net>
 * \date 2005
 * \version 0.1
 ********************************************************************/

#ifndef __TONSYSTEM_H_INCLUDED
#define __TONSYSTEM_H_INCLUDED

#include "ton.h"
#include "interval.h"

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
