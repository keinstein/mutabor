/** \file
 ********************************************************************
 * Harmonien.
 *
 * \author Tobias Schlemmer <keinstein_junior@gmx.net>
 * \date 2005
 * \version 0.1
 ********************************************************************/

#ifndef __HARMONIE_H_INCLUDED
#define __HARMONIE_H_INCLUDED

#include "mutabor/interval.h"

#ifdef __cplusplus
namespace mutabor {
  extern "C" {
#endif

    /*********  Definition der Harmonien als verkettete Liste ********/
    
    /** Harmonien als einfach verkettette Liste. */
    struct harmonie {
      char * name;                   /**< Name der Harmonie */
      struct taste * tastenliste;    /**< Angeschlagene Töne */
      int bezugstaste;               /**< Bezugstaste der Harmonie */
      struct harmonie * next;        /**< Nächste Harmonie */
    };

    void drucke_harmonie (struct harmonie * this_);

    void get_new_harmonie (char * name, int bezugstaste);
    void get_harmoniebezeichner (int vor_taste,
				 char * name,
				 int nach_taste);

    struct harmonie * get_harmonie (char * name, struct harmonie * liste);

    extern struct harmonie       *  list_of_harmonien;
    int        tmp_vor_taste; /**< Zwischenspeicher für tiefste Taste einer Harmonie */
    char *     tmp_name; /**< Zwischenspeicher für Name einer Harmonie */
    int        tmp_nach_taste; /**< Zwischenspeicher für höchste Taste einer Harmonie */

#ifdef __cplusplus 
  } // extern "C"
} // namespace mutabor
#endif

#endif /* __HARMONIE_H_INCLUDED */
